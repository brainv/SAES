/**
 * @file CodiFileWrapper.cxx
 * @brief Body codi file wrapper
 * @date 23/02/2012
 * @author Yadickson Soto
 */

#include "CodiFileWrapper.hxx"
#include "CodiFileManager.hxx"
#include <Resources/election-string-resources-manager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/IO/File.h>
#include <System/Utils/StringUtils.hxx>
#include <System/IO/Path.h>
#include <System/IO/Directory.h>
#include <time.h>
#include "CodiFile.h"
#include "CodiBuffer.hxx"
#include "CodiInfo.hxx"
#include "X7SCodiFileWrapper.hxx"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

#define MAX_REGISTER_G 3 ///< max register G
#define MAX_REGISTER_S 15 ///< max register S
#define MAX_REGISTER_L 31 ///< max register L
#define MAX_REGISTER_C 35 ///< max register C
#define MAX_REGISTER_H  7 ///< max register H
#define MAX_REGISTER_T  7 ///< max register T

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::System::Utils;

ISMTTLog* CodiFileWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.CodiFileWrapper",GETTEXT_PACKAGE);

CodiFileWrapper::CodiFileWrapper()
{
	this->electoralConfiguration = NULL;
	this->directories = NULL;
}

CodiFileWrapper::~CodiFileWrapper()
{

}

void CodiFileWrapper::init(ElectoralConfiguration * electoralConfiguration,
	SaesDirectories * directories)
{
	this->electoralConfiguration = electoralConfiguration;
	this->directories = directories;
	this->separator = SAESConfigurationManager::Current()->getPrintVoteConfiguration().getBallotOptionNameSeparator();

	this->customniscode = "";
	this->codiMachine = "";

	this->registerS = SAESConfigurationManager::Current()->getCodiFileConfiguration().getRegisterS();
	this->registerL = SAESConfigurationManager::Current()->getCodiFileConfiguration().getRegisterL();
	this->registerC = SAESConfigurationManager::Current()->getCodiFileConfiguration().getRegisterC();
}

void CodiFileWrapper::update()
{
	VotingDevice::Voting_booths::Voting_boothSequence seq = electoralConfiguration->getVotingDevice()->getVotingBooths().getVoting_booth();
	std::string votingBoothCustomCode;

	if (seq.size() > 0)
	{
		VotingDevice::Voting_booth & vb = seq[0];
		votingBoothCustomCode = vb.getCustom_code();

		std::string find = SAESConfigurationManager::Current()->getCodiFileConfiguration().getSeparatorVotingDevice();
		std::vector <std::string> vector;
		StringUtils::split(votingBoothCustomCode, find, vector);

		if (vector.size() >= 2)
		{
			codiMachine = vector[1];
		}
		if (vector.size() >= 3)
		{
			customniscode = vector[2];
		}
	}

	std::list <Region_category> & list (electoralConfiguration->getRegionCategoryList());
	std::list <Region_category>::reverse_iterator it;

	RegionNameCodiConfig regionName = SAESConfigurationManager::Current()->getCodiFileConfiguration().getRegionName();

	if (regionName == RegionNameCodiConfig::CONFIGURATION_VOTING_VOTE_CUSTOM_CODE)
	{
		currentRegion = votingBoothCustomCode;
	}
	else if (regionName == RegionNameCodiConfig::CONFIGURATION_LAST)
	{
		if (list.size() > 0)
		{
			Region_category category = (*(list.rbegin()));
			currentRegion = ElectionStringResourcesManager::Current()->getResource(category.getRegion().getName_key());
		}
	}
	else
	{
		CategoryLevel level;

		switch(regionName)
		{
			case RegionNameCodiConfig::CONFIGURATION_FIRST_REGION:
				level = CategoryLevel::VOTING_DEVICES_FIRST_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_SECOND_REGION:
				level = CategoryLevel::VOTING_DEVICES_SECOND_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_THIRD_REGION:
				level = CategoryLevel::VOTING_DEVICES_THIRD_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_FOURTH_REGION:
				level = CategoryLevel::VOTING_DEVICES_FOURTH_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_FIFTH_REGION:
				level = CategoryLevel::VOTING_DEVICES_FIFTH_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_SIXTH_REGION:
				level = CategoryLevel::VOTING_DEVICES_SIXTH_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_SEVENTH_REGION:
				level = CategoryLevel::VOTING_DEVICES_SEVENTH_LEVEL;
				break;

			case RegionNameCodiConfig::CONFIGURATION_EIGHTH_REGION:
				level = CategoryLevel::VOTING_DEVICES_EIGHTH_LEVEL;
				break;

			default:
				level = CategoryLevel::VOTING_DEVICES_FIRST_LEVEL;
				break;
		}

		for (it = list.rbegin();
				it != list.rend();
				it++)
		{
			Region_category category = (*it);

			if (category.getCategory_level().present() &&
					category.getCategory_level().get() == level)
			{
				currentRegion = ElectionStringResourcesManager::Current()->getResource(category.getRegion().getName_key());
				break;
			}
		}
	}

	if (list.size() > 0)
	{
		Region_category category = (*(list.rbegin()));

		if (category.getCategory_level().present())
		{
			switch(category.getCategory_level().get())
			{
				case CategoryLevel::VOTING_DEVICES_FIRST_LEVEL: // Pays
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_SECOND_LEVEL: // Region
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_THIRD_LEVEL: // Province
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_FOURTH_LEVEL: // Arrondissement
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_FIFTH_LEVEL: // Province District
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_SIXTH_LEVEL: // Canton
					codiVotingType = "K";
					break;
				case CategoryLevel::VOTING_DEVICES_SEVENTH_LEVEL: // Commune and Commune avec Districts
					codiVotingType = "M";
					break;
				case CategoryLevel::VOTING_DEVICES_EIGHTH_LEVEL: // District
					codiVotingType = "I";
					break;
			}
		}
		else
		{
			logger->Debug("ERROR - category level not found");
			codiVotingType = "X";
		}
	}
	else
	{
		logger->Debug("ERROR - region category not found");
	}
}

void CodiFileWrapper::persistCodiFiles(StationTallyWrapper * stationTally)
	throw (CryptoException,
			SignedException,
			XmlException,
			CodiException)
{

	update();

	std::list <Contest> & contest = electoralConfiguration->getContestList();
	std::list <Contest>::iterator it;

	std::string inputDirDom = directories->getCodiFilesFolderFullPath(BasePathType::CONFIGURATION_DOM);
	std::string inputDirFlash = directories->getCodiFilesFolderFullPath(BasePathType::CONFIGURATION_FLASH);

	std::string outputDirDom = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_DOM);
	std::string outputDirFlash = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_FLASH);

	Directory::Mkdir(outputDirDom);
	Directory::Mkdir(outputDirFlash);

	for (it = contest.begin(); it != contest.end(); it++)
	{
		std::string customCode = (*it).getCustom_code();

		std::string inputFile;
		std::string outputFile;

		CodiFileManager::getInputContestFileName( customCode, inputFile );
		CodiFileManager::getOutputContestFileName( customCode, outputFile, codiMachine, codiVotingType, customniscode );

		logger->Debug(inputFile + " --> " + outputFile);

		std::string inputFileDom = Path::Combine(inputDirDom, inputFile);
		std::string inputFileFlash = Path::Combine(inputDirFlash, inputFile);

		std::string outputFileDom = Path::Combine(outputDirDom, outputFile);
		std::string outputFileFlash = Path::Combine(outputDirFlash, outputFile);

		if ( !File::copyFile( inputFileDom, outputFileDom ) || !File::copyFile( inputFileFlash, outputFileFlash ) )
		{
			deleteFiles();
			logger->Debug("ERROR load codi files - (" + inputFileDom + ").");
			throw CodiException(
					_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorInputCodiFiles"),
	                N_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorInputCodiFiles"),
	                logger);
		}
	}

	std::map < std::string, CodiFile * > & codiFiles (stationTally->getCodiFiles());
	std::map < std::string, CodiFile * >::iterator itcf;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [16];
	int sizeBuffer = sizeof (buffer) / sizeof(char);

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime (buffer, sizeBuffer,"%d/%m/%Y",timeinfo);
	currentDate = buffer;

	strftime (buffer, sizeBuffer,"%H:%M:%S",timeinfo);
	currentTime = buffer;

	bool persistenceCodi = SAESConfigurationManager::Current()->getCodiFileConfiguration().getPersistenceCodi();
	bool persistenceX7SCodi = SAESConfigurationManager::Current()->getCodiFileConfiguration().getPersistenceX7SCodi();

	for (itcf = codiFiles.begin(); itcf != codiFiles.end(); itcf++)
	{
		CodiFile * codi = itcf->second;
		std::string codiFile = codi->getFile();

		persistence(codi);

		if (persistenceX7SCodi)
		{
			X7SCodiFileWrapper x7sCodiFiles;
			x7sCodiFiles.init(electoralConfiguration, directories);

			std::list<std::string> codiFiles;
			std::list<std::string> pvFiles;

			std::list<std::string>::iterator itcodi;
			std::list<std::string>::iterator itpv;

			std::string pvreport = directories->getGeneratedPVReportFileFullPath(BasePathType::CONFIGURATION_DOM);
			pvreport = Path::GetFileName(pvreport);

		    bool allLanguages = SAESCommonConfigurationManager::Current()->isPVInAllLanguages();

			electoralConfiguration->getFileNamesByLanguages(codiFile, codiFiles, false, 1, true);
			electoralConfiguration->getFileNamesByLanguages(pvreport, pvFiles, allLanguages);

			for (itcodi = codiFiles.begin(), itpv = pvFiles.begin();
					itcodi != codiFiles.end() && itpv != pvFiles.end();
					itcodi++, itpv++)
			{
				std::string x7s = (*itcodi) + ".X7S";
				x7sCodiFiles.persistX7SCodiFile(codiFile, x7s, *itpv); ///< x7s codi files wrapper
			}
		}

	    std::string fileDom = Path::Combine(outputDirDom, codiFile);
	    std::string fileFlash = Path::Combine(outputDirFlash, codiFile);

	    if (persistenceCodi)
		{
	    	File::copyFile(fileDom, fileFlash);
		}
	    else
	    {
	    	File::DeleteFile(fileDom);
	    	File::DeleteFile(fileFlash);
	    }
	}
}

bool CodiFileWrapper::validate()
{
	logger->Debug("Validate codi files");

	bool validate = true;

	std::list <Contest> & contest = electoralConfiguration->getContestList();
	std::list <Contest>::iterator it;

	std::string outputDirDom = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_DOM);
	std::string outputDirFlash = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_FLASH);

	for (it = contest.begin(); it != contest.end() && validate; it++)
	{
		std::string customCode = (*it).getCustom_code();
		std::string outputFile;

		CodiFileManager::getOutputContestFileName(customCode, outputFile, codiMachine, codiVotingType, customniscode);

		if (SAESConfigurationManager::Current()->getCodiFileConfiguration().getPersistenceCodi())
		{
			std::string outputFileDom = Path::Combine(outputDirDom, outputFile);
			std::string outputFileFlash = Path::Combine(outputDirFlash, outputFile);

			if (!File::compareFiles( outputFileDom, outputFileFlash ))
			{
				validate = false;
				break;
			}
		}

		if (SAESConfigurationManager::Current()->getCodiFileConfiguration().getPersistenceX7SCodi())
		{
			std::list<std::string> codiFiles;
			std::list<std::string>::iterator itcodi;

			electoralConfiguration->getFileNamesByLanguages(outputFile, codiFiles, false, 1, true);

			for (itcodi = codiFiles.begin();
					itcodi != codiFiles.end() && validate;
					itcodi++)
			{
				std::string codiFileDom = Path::Combine(outputDirDom, (*itcodi) + ".X7S");
				std::string codiFileFlash = Path::Combine(outputDirFlash, (*itcodi) + ".X7S");

				std::string pvFileDom = Path::Combine(outputDirDom, (*itcodi) + ".X7S.PDF");
				std::string pvFileFlash = Path::Combine(outputDirFlash, (*itcodi) + ".X7S.PDF");

				if (!File::compareFiles( codiFileDom, codiFileFlash ))
				{
					validate = false;
					break;
				}
				if (!File::compareFiles( pvFileDom, pvFileFlash ))
				{
					validate = false;
					break;
				}
			}
		}
	}

	return validate;
}

void CodiFileWrapper::deleteFiles()
{
	std::string outputDirDom = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_DOM);
	std::string outputDirFlash = directories->getCodiFolderFullPath(BasePathType::CONFIGURATION_FLASH);

	Directory::Delete(outputDirDom, true);
	Directory::Delete(outputDirFlash, true);
}

void CodiFileWrapper::persistence(CodiFile * codi)
	throw (CodiException)
{
	currentFile = codi->getFile();

	logger->Debug("Load codi file " + currentFile);

	std::string dirDom = directories->getCodiFolderFullPath();
	std::string fileDom = Path::Combine(dirDom, currentFile);

	SafeBuffer bufferFile;
	File::openFileToBuffer(fileDom, bufferFile);

	std::vector <SafeBuffer> regG;
	std::vector <SafeBuffer> regS;
	std::vector <SafeBuffer> regL;
	std::vector <SafeBuffer> regC;

	std::vector <SafeBuffer>::iterator itrg;
	std::vector <SafeBuffer>::iterator itrs;
	std::vector <SafeBuffer>::iterator itrl;
	std::vector <SafeBuffer>::iterator itrc;

	CodiBuffer::getRegisters(bufferFile, regG, regS, regL, regC);

    bufferFile.Clear();

    std::vector<CodiRegister_S> & regs_S (codi->getRegsS());
    std::vector<CodiRegister_L> & regs_L (codi->getRegsL());
    std::vector<CodiRegister_C> regs_C;

	std::vector<CodiRegister_S>::iterator its;
	std::vector<CodiRegister_L>::iterator itl;
	std::vector<CodiRegister_C>::iterator itc;

    for (itrg = regG.begin();
    	 itrg != regG.end();
    	 itrg++)
	{
		//process register g
		SafeBuffer & bufferG ((*itrg));
		fillRegisterG(bufferG);
		bufferFile.AddData(bufferG);
	}

	for (itrs = regS.begin(), its = regs_S.begin();
		 itrs != regS.end() && its != regs_S.end();
		 itrs++, its++)
	{
		//process register s
		SafeBuffer & b ((*itrs));
		fillRegisterS(b, (*its));
		bufferFile.AddData(b);
   	}

	for (itrl = regL.begin(), itl = regs_L.begin();
		 itrl != regL.end() && itl != regs_L.end();
		 itrl++, itl++)
	{
		//process register l
		SafeBuffer & b ((*itrl));
		fillRegisterL(b, (*itl));
		bufferFile.AddData(b);

		std::vector<CodiRegister_C> principal ( (*itl).getPrincipal() );
		std::vector<CodiRegister_C> standIn ( (*itl).getStandIn() );

    	regs_C.insert(regs_C.end(), principal.begin(), principal.end());
    	regs_C.insert(regs_C.end(), standIn.begin(), standIn.end());
	}

    for (itrc = regC.begin(), itc = regs_C.begin();
    	 itrc != regC.end() && itc != regs_C.end();
    	 itrc++, itc++)
	{
		//process register c
    	SafeBuffer & b ((*itrc));
		fillRegisterC (b, (*itc));
		bufferFile.AddData(b);
	}

	//process register t
	SafeBuffer bufferT;
	fillRegisterT(bufferT);

	currentSize = bufferFile.GetSize() + bufferT.GetSize();

	//process register h
	SafeBuffer bufferH;
	fillRegisterH(bufferH);

	bufferFile.AddData(bufferH);
	bufferFile.AddData(bufferT);

	regs_C.clear();

	File::saveBufferToFile(bufferFile, fileDom);
}

void CodiFileWrapper::fillRegisterG(Smartmatic::System::SafeBuffer & buffer)
	throw (CodiException)
{
    CodiBuffer::fixRegister(buffer, MAX_REGISTER_G);
}

void CodiFileWrapper::fillRegisterS(Smartmatic::System::SafeBuffer & buffer, CodiRegister_S & regS)
	throw (CodiException)
{
   	CodiBuffer::fixRegister(buffer, MAX_REGISTER_S);

	if (registerS.getUpdateNISCode())
	{
		CodiBuffer::insertValue(buffer, 3, CodiInfo::getOutputNisCode(regS.getCustomCode(), customniscode)); //Type de bureau de totalisation
	}

	if (registerS.getSetLanguage())
	{
		CodiBuffer::insertValue(buffer, 9, CodiInfo::getLanguage(regS.getCustomCode())); //language
	}

	if (registerS.getSetVotingType())
	{
		CodiBuffer::insertValue(buffer, 6, codiVotingType); //Type de bureau de totalisation
	}

	if (registerS.getSetNISCode())
	{
	   	CodiBuffer::insertValue(buffer, 7, CodiInfo::getOutputNisCode(regS.getCustomCode(), customniscode)); //Code INS du bureau de totalisation
	}

   	CodiBuffer::insertValue(buffer, 8, regS.getNumValidVotes()); //Nombre de bulletins valables
   	CodiBuffer::insertValue(buffer, 10, regS.getNumRegisteredVotes()); //Nombre de bulletins enregistrés
   	CodiBuffer::insertValue(buffer, 11, regS.getNumBlankVotes()); //Nombre de bulletins nuls et blancs
   	CodiBuffer::insertValue(buffer, 13, regS.getChecksum()); //Check-sum
}

void CodiFileWrapper::fillRegisterL(Smartmatic::System::SafeBuffer & buffer, CodiRegister_L & regL)
	throw (CodiException)
{
	unsigned long tallyR = regL.getTallyPosition();
	unsigned long tallyB = CodiBuffer::getLongValue(buffer, 5);

	if (tallyR == tallyB)
	{
		CodiBuffer::fixRegister(buffer, MAX_REGISTER_L);

		if (registerL.getUpdateNISCode())
		{
			CodiBuffer::insertValue(buffer, 3, CodiInfo::getOutputNisCode(regL.getCustomCode(), customniscode)); //Type de bureau de totalisation
		}

		if (registerL.getSetLanguage())
		{
			CodiBuffer::insertValue(buffer, 10, CodiInfo::getLanguage(regL.getCustomCode())); //language
		}

		if (registerL.getSetVotingType())
		{
			CodiBuffer::insertValue(buffer, 14, codiVotingType); //Type de bureau de totalisation
		}

		if (registerL.getSetNISCode())
		{
			CodiBuffer::insertValue(buffer, 15, CodiInfo::getOutputNisCode(regL.getCustomCode(), customniscode)); //Code INS du bureau de totalisation
		}

		CodiBuffer::insertValue(buffer, 16, regL.get_category_1_count()); //Nombre de bulletins sous-catégorie 1
		CodiBuffer::insertValue(buffer, 17, regL.get_category_2_count()); //Nombre de bulletins sous-catégorie 2
		CodiBuffer::insertValue(buffer, 18, regL.get_category_3_count()); //Nombre de bulletins sous-catégorie 3
		CodiBuffer::insertValue(buffer, 19, regL.get_category_4_count()); //Nombre de bulletins sous-catégorie 4
		CodiBuffer::insertValue(buffer, 20, regL.getElectoralNumber()); //Electoral number
		CodiBuffer::insertValue(buffer, 31, regL.getChecksum()); //Check-sum
	}
	else
	{
		std::stringstream ss;
		ss << "ERROR - Tally register L (";
		ss << tallyR << ") not equal to buffer file (";
		ss << tallyB << ").";
		logger->Debug(ss.str());

		throw CodiException(
				_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorTallyRegisterL"),
                N_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorTallyRegisterL"),
                logger);
	}
}

void CodiFileWrapper::fillRegisterC(Smartmatic::System::SafeBuffer & buffer, CodiRegister_C & regC)
	throw (CodiException)
{
	unsigned long tallyR = regC.getTallyPosition();
	unsigned long tallyB = CodiBuffer::getLongValue(buffer, 7);

	if (tallyR == tallyB)
	{
		CodiBuffer::fixRegister(buffer, MAX_REGISTER_C);

		if (registerC.getUpdateNISCode())
		{
			CodiBuffer::insertValue(buffer, 3, CodiInfo::getOutputNisCode(regC.getCustomCode(), customniscode)); //Type de bureau de totalisation
		}

		if (registerC.getSetLanguage())
		{
			CodiBuffer::insertValue(buffer, 17, CodiInfo::getLanguage(regC.getCustomCode())); //language
		}

		if (registerC.getSetVotingType())
		{
			CodiBuffer::insertValue(buffer, 19, codiVotingType); //Type de bureau de totalisation
		}

		if (registerC.getSetNISCode())
		{
			CodiBuffer::insertValue(buffer, 20, CodiInfo::getOutputNisCode(regC.getCustomCode(), customniscode)); //Code INS du bureau de totalisation
		}

		CodiBuffer::insertValue(buffer, 21, regC.getVoteCount()); //Nombre de voix de nominatives

		if (registerC.getFillLastFields().present() && registerC.getFillLastFields().get())
		{
			Eligible_option eligibleOption =  electoralConfiguration->getEligibleOptionFromBallotOptionCode ( regC.getContestCode(), regC.getBallotOptionCode() );
			std::string strEligibleOption = ElectionStringResourcesManager::Current()->getResource(eligibleOption.getBallot_name_key());
			std::string lastName, firstName, initialFirstName;

			std::vector <std::string> parts;
			StringUtils::split (strEligibleOption, separator, parts);

			if (parts.size() >= 1)
			{
				lastName = parts[0];
			}
			if (parts.size() >= 2)
			{
				firstName = parts[1];
			}
			if (parts.size() >= 3)
			{
				initialFirstName = parts[2];
			}
			else
			{
				initialFirstName = StringUtils::trim(firstName).substr(0, 1);
			}

			CodiBuffer::insertValue(buffer, 33, lastName); //Nom pour la ligne 1 du système de vote électronique Smartmatic
			CodiBuffer::insertValue(buffer, 34, firstName); //Prénom pour la ligne 2 du système de vote électronique Smartmatic
			CodiBuffer::insertValue(buffer, 35, initialFirstName); //Initiale du prénom pour le système de vote électronique Smartmatic
		}
	}
	else
	{
		std::stringstream ss;
		ss << "ERROR - Tally register C (";
		ss << tallyR << ") not equal to buffer file (";
		ss << tallyB << ").";
		logger->Debug(ss.str());

		throw CodiException(
				_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorTallyRegisterC"),
                N_("Smartmatic.SAES.Voting.Codi.CodiFileWrapper.ErrorTallyRegisterC"),
                logger);
	}
}

void CodiFileWrapper::fillRegisterH(Smartmatic::System::SafeBuffer & buffer)
	throw (CodiException)
{
	CodiBuffer::createRegister(buffer, CodiBuffer::REGISTER_H);
    CodiBuffer::fixRegister(buffer, MAX_REGISTER_H);
    CodiBuffer::insertValue(buffer, 2, currentFile); //Nom du fichier hors répertoire
    CodiBuffer::insertValue(buffer, 3, currentDate); //Date de création du fichier
    CodiBuffer::insertValue(buffer, 4, currentTime); //Heure de création du fichier
    CodiBuffer::insertValue(buffer, 5, currentSize); //Taille du fichier en octets
    CodiBuffer::insertValue(buffer, 6, currentRegion); //Nom du bureau créant le fichier
    CodiBuffer::addEndRegister(buffer);

    unsigned long totalSize = 0;
    unsigned long size = buffer.GetSize() + currentSize;

    // recalculate size
    while (totalSize != size)
    {
    	totalSize = buffer.GetSize() + currentSize;
    	CodiBuffer::insertValue(buffer, 5, totalSize);
    	size = buffer.GetSize() + currentSize;
    }
}

void CodiFileWrapper::fillRegisterT(Smartmatic::System::SafeBuffer & buffer)
	throw (CodiException)
{
	CodiBuffer::createRegister(buffer, CodiBuffer::REGISTER_T);
	CodiBuffer::fixRegister(buffer, MAX_REGISTER_T);
    CodiBuffer::insertValue(buffer, 2, "D"); //Situation dépouillement selon le volume
    CodiBuffer::insertValue(buffer, 3, "1"); //Situation dépouillement selon le type
    CodiBuffer::insertValue(buffer, 4, "1"); //Nombre total de bureaux
    CodiBuffer::insertValue(buffer, 5, "1"); //Nombre de bureaux traités
    CodiBuffer::insertValue(buffer, 6, currentDate); //Date de génération du fichier
    CodiBuffer::insertValue(buffer, 7, currentTime); //Heure de génération du fichier
}

std::string CodiFileWrapper::getCodiMachine()
{
	return codiMachine;
}
std::string CodiFileWrapper::getCustomniscode()
{
	return customniscode;
}

std::string CodiFileWrapper::getCodiVotingType()
{
	return codiVotingType;
}
