/**
 * @file PVFormWrapper.cxx
 * @brief Body pvform wrapper class.
 */

#include "PVFormWrapper.hxx"
#include <fstream>
#include <glibmm.h>
#include <Security/Encryption.hxx>
#include <Runtime/Environment/saes-directories.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Voting/Vote/TransmissionPackageWrapper.hxx>
#include <Voting/Vote/VoteWrapper.hxx>
#include "Resources/election-string-resources-manager.h"
#include "Voting/PBReports/activated-card-statistics-schema.hxx"
#include <Configuration/saes-language-controller.h>
#include <System/IO/Path.h>
#include <Voting/PBReports/pvform-schema.hxx>
#include <Voting/set-language-functionality.h>
#include <Voting/Codi/CodiFileWrapper.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>

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

using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* PVFormWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.PVFormWrapper",GETTEXT_PACKAGE);

PVFormWrapper * PVFormWrapper::instance = NULL;

PVFormWrapper * PVFormWrapper::getInstance()
{
    if (instance == NULL)
        instance = new PVFormWrapper();

    return instance;
}

PVFormWrapper::PVFormWrapper()
{
	transformer = NULL;
}

PVFormWrapper::~PVFormWrapper()
{
    dispose();
}

void PVFormWrapper::dispose()
{
    this->fileFullPath = "";
}

void PVFormWrapper::init(ElectoralConfiguration * electoralConfiguration,
        OperationStatus * operationStatus,
        PollworkersWrapper * pollWorkersWrapper,
        StatisticManager * statisticManager,
        AssistedActivationWrapper * assistedActivationWrapper,
        ActivatedCardStatisticsWrapper * activatedCardStatisticsWrapper,
        VoteStatisticsWrapper * voteStatisticsWrapper,
        IncidentReportWrapper * incidentReportWrapper,
        ClosingNotesWrapper * closingNotesWrapper,
        IDCardInfoWrapper * idCardInfoWrapper,
        VotingDisabledWrapper * votingDisabledWrapper,
        PoliceNoteWrapper * policeNoteWrapper)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    this->electoralConfiguration = electoralConfiguration;
    this->operationStatus = operationStatus;
    this->pollWorkersWrapper = pollWorkersWrapper;
    this->statisticManager = statisticManager;
    this->assistedActivationWrapper = assistedActivationWrapper;
    this->activatedCardStatisticsWrapper = activatedCardStatisticsWrapper;
    this->voteStatisticsWrapper = voteStatisticsWrapper;
    this->incidentReportWrapper = incidentReportWrapper;
    this->closingNotesWrapper = closingNotesWrapper;
    this->idCardInfoWrapper = idCardInfoWrapper;
    this->votingDisabledWrapper = votingDisabledWrapper;
    this->policeNoteWrapper = policeNoteWrapper;
    dispose();
}

bool PVFormWrapper::persistencePVForm(Smartmatic::System::XSLFO::XSLFOTransformer * transformer)
    throw (CryptoException,
           SignedException,
           XmlException)
{
	bool validate = false;
	this->transformer = transformer;

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    std::string pvformFileDom = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvformFileFlash = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::string pvreportFileDom = directories.getGeneratedPVReportFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvreportFileFlash = directories.getGeneratedPVReportFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::string pvtemplateFile = directories.getGlobalPVTemplateFileFullPath();

    validate = persistence(pvformFileDom, pvformFileFlash,
				pvreportFileDom, pvreportFileFlash,
				pvtemplateFile);

    std::string pvreportTestFileDom = directories.getGeneratedPVReportTestFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvreportTestFileFlash = directories.getGeneratedPVReportTestFullPath(BasePathType::CONFIGURATION_FLASH);

    std::string pvtemplateTestFile = directories.getTestPVTemplateFileFullPath();

    validate = persistence(pvformFileDom, pvformFileFlash,
				pvreportTestFileDom,
				pvreportTestFileFlash,
				pvtemplateTestFile) || validate;

    return validate;
}

bool PVFormWrapper::persistence(std::string & pvformFileDom,
		std::string & pvformFileFlash,
		std::string & pvreportFileDom,
		std::string & pvreportFileFlash,
		std::string & pvtemplateFile)
throw (CryptoException,
       SignedException,
       XmlException)
{
	bool validate = true;

    std::string actualLanguage;
    std::string actualCountry;
    std::string currentLanguage;

    currentLanguage = Smartmatic::SAES::Configuration::SAESLanguageController::getActualLanguage();
    SetLanguageFunctionality::getCurrentLanguageCountry(actualLanguage, actualCountry);

    std::list <std::string> languages = getLanguages();
    std::list <std::string>::iterator it;

    for (it = languages.begin();
         it != languages.end();
         it++)
    {
        std::string lang = (*it);

        logger->Debug("Generate pv-report in language " + lang);

        if (lang.empty())
        {
            Smartmatic::SAES::Configuration::SAESLanguageController::FullLocalizeApplication(currentLanguage);
            SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(actualLanguage, actualCountry);
        }
        else
        {
            Smartmatic::SAES::Configuration::SAESLanguageController::FullLocalizeApplication(lang);
            std::string aLand, aCountry;
            Smartmatic::SAES::Configuration::SAESLanguageController::GetActualLanguage(aLand, aCountry);
            SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(aLand, aCountry);
        }

        std::string pvformFileDomTemp = Path::GetFullFileNameWithOutExtension(pvformFileDom) + lang + Path::GetFileExtension(pvformFileDom);
        std::string pvformFileFlashTemp = Path::GetFullFileNameWithOutExtension(pvformFileFlash) + lang + Path::GetFileExtension(pvformFileFlash);

		logger->Debug("Persist pv report data " + pvformFileDomTemp);
		fileFullPath = pvformFileDomTemp;
		persistence();
		Smartmatic::System::IO::File::copyFile(pvformFileDomTemp, pvformFileFlashTemp);

        std::string pvreportFileDomTemp = Path::GetFullFileNameWithOutExtension(pvreportFileDom) + lang + Path::GetFileExtension(pvreportFileDom);
        std::string pvreportFileFlashTemp = Path::GetFullFileNameWithOutExtension(pvreportFileFlash) + lang + Path::GetFileExtension(pvreportFileFlash);

        std::string pvtemplateFileTemp = Path::GetFullFileNameWithOutExtension(pvtemplateFile) + lang + Path::GetFileExtension(pvtemplateFile);

        if (!File::canOpenFile(pvtemplateFileTemp))
        {
            pvtemplateFileTemp = pvtemplateFile;
        }

        logger->Debug("input pv report file " + pvformFileDomTemp);
        logger->Debug("template pv report file " + pvtemplateFileTemp);
        logger->Debug("Genarate pv report file " + pvreportFileDomTemp);

        if (!File::canOpenFile(pvtemplateFileTemp))
        {
            logger->Debug("Error pv template file " + pvtemplateFileTemp + " not found");
            validate = false;
        }
        else if (!transformer || !transformer->transformFile(pvreportFileDomTemp, pvformFileDomTemp, pvtemplateFileTemp))
        {
            logger->Debug("Error transform file " + pvformFileDomTemp + " to " + pvreportFileDomTemp);
            validate = false;
        }

       	Smartmatic::System::IO::File::copyFile(pvreportFileDomTemp, pvreportFileFlashTemp);
    }

    SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(actualLanguage, actualCountry);

    return validate;
}

void PVFormWrapper::persistence()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    ElectionStringResourcesManager * resource = ElectionStringResourcesManager::Current();
    Election::ElectionWrapper * election = electoralConfiguration->getElection();
    VotingDevice::VotingDeviceWrapper * votingDevice = electoralConfiguration->getVotingDevice();
    VotingDevice::Voting_booth votingBooth = votingDevice->getFirstVotingDevice().getVoting_booths().getVoting_booth()[0];

    Glib::TimeVal time;
    PVForm pv;
    PVInfoElection infoElection;
    PVVotes votes;

    time.assign_current_time();

    /*******************************************************************/

    infoElection.setElection_name(resource->getResource(election->getElection().getName_key()));
    infoElection.setElectoral_organization(resource->getResource(election->getElection().getElectoral_organization()));
    infoElection.setCreation_time(time.as_iso8601().c_str());
    infoElection.setVoting_device_code(votingDevice->getFirstVotingDevice().getCode());
    infoElection.setPolling_station_code(votingBooth.getPolling_station_code());
    infoElection.setPolling_station_number(votingBooth.getPolling_station_number());
    infoElection.setPolling_station_criteria(resource->getResource(votingBooth.getPolling_station_criteria()));
    infoElection.setPolling_place_code(votingBooth.getPolling_place_code());
    infoElection.setPolling_place_registered_electors(0);
    infoElection.setPolling_place_address(resource->getResource(votingBooth.getPolling_place_address()));
    infoElection.setPolling_place_name(resource->getResource(votingBooth.getPolling_place_name()));
    infoElection.setOpening_date(operationStatus->getElectionStatusWrapper()->getOpenElectionDate());
    infoElection.setClose_voting_date(operationStatus->getElectionStatusWrapper()->getCloseVotingDate());
    infoElection.setClose_election_date(operationStatus->getElectionStatusWrapper()->getCloseElectionDate());
    infoElection.setNumber_senators(0);
    infoElection.setNumber_members(0);
    infoElection.setDuration_election_date(durationElection);

	Smartmatic::SAES::Voting::Codi::CodiFileWrapper codiFiles;
	Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
	codiFiles.init(electoralConfiguration, &directories);
	codiFiles.update();
	infoElection.setNiscode(codiFiles.getCustomniscode());

    PVInfoElection::RegionLevelSequence regions;

    std::list <VotingDevice::Region_category> & regionList (electoralConfiguration->getRegionCategoryList());
    std::list <VotingDevice::Region_category>::iterator regionIt;

    for(regionIt = regionList.begin(); regionIt != regionList.end(); regionIt++)
    {
		VotingDevice::Region_category category = (*regionIt);
		RegionLevel regionLevel;
		regionLevel.setCategory_level(category.getCategory_level().present() ? category.getCategory_level().get() : "");
    	regionLevel.setCategory(resource->getResource(category.getName_key()));
    	regionLevel.setName(resource->getResource(category.getRegion().getName_key()));
    	regions.push_back(regionLevel);
    }

    infoElection.setRegionLevel(regions);
    pv.setInfoElection(infoElection);
    pv.setIDCardMembers(*(idCardInfoWrapper->getIdCardMembers()));

    /*******************************************************************/
    pv.setPollworkers(*(pollWorkersWrapper->getPollworkers()));
    pv.setPoliceNotes(policeNoteWrapper->getPoliceNotes());

    pv.setStatistics(statisticManager->getStatistics());

    //Vote Statistics

    VoteStatistics newVoteStatistics = voteStatisticsWrapper->convertToGeneratedClass();
    VotesByCA::VoteByCASequence& sequenceVotesByCA = newVoteStatistics.getVotesByCA().getVoteByCA();

    for(unsigned int i= 0; i < sequenceVotesByCA.size();i++)
    {
    	sequenceVotesByCA[i].setCAValue(resource->getResource(sequenceVotesByCA[i].getCAValue()));
    }

    pv.setVoteStatistics(newVoteStatistics);

   //Activated Card Statistics

    ActivatedCardStatistics *newActivatedCardStatistics = new ActivatedCardStatistics();
    newActivatedCardStatistics = activatedCardStatisticsWrapper->getCardStatistics();

	ActivatedOfficialAudioByCA::CardByCASequence& cardOfficialAudioSeq = newActivatedCardStatistics->getActivatedOfficialAudioByCA().getCardByCA();
	for(unsigned int i= 0; i < cardOfficialAudioSeq.size();i++)
	{
		cardOfficialAudioSeq[i].setCAValue(resource->getResource(cardOfficialAudioSeq[i].getCAValue()));
	}

    ActivatedOfficialNonAudioByCA::CardByCASequence& cardOfficialNonAudioSeq = newActivatedCardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA();
	for(unsigned int i= 0; i < cardOfficialNonAudioSeq.size();i++)
	{
		cardOfficialNonAudioSeq[i].setCAValue(resource->getResource(cardOfficialNonAudioSeq[i].getCAValue()));
	}

    ActivatedDemoAudioByCA::CardByCASequence& cardDemoAudioSeq = newActivatedCardStatistics->getActivatedDemoAudioByCA().getCardByCA();
	for(unsigned int i= 0; i < cardDemoAudioSeq.size();i++)
	{
		cardDemoAudioSeq[i].setCAValue(resource->getResource(cardDemoAudioSeq[i].getCAValue()));
	}

    ActivatedDemoNonAudioByCA::CardByCASequence& cardDemoNonAudioSeq = newActivatedCardStatistics->getActivatedDemoNonAudioByCA().getCardByCA();
	for(unsigned int i= 0; i < cardDemoNonAudioSeq.size();i++)
	{
		cardDemoNonAudioSeq[i].setCAValue(resource->getResource(cardDemoNonAudioSeq[i].getCAValue()));
	}

    pv.setActivatedCardStatistics(*newActivatedCardStatistics);

    pv.setVotingDisabledInformation(votingDisabledWrapper->getVotingDisabledInformation());

    pv.setAssistedActivations(assistedActivationWrapper->getActivations());

    pv.setIncidentReports(*(incidentReportWrapper->getIncidentReports()));

    pv.setCloseElectionNotes(*(closingNotesWrapper->getCloseElectionNotes()));

    /*******************************************************************/

    std::string fileTransmissionPackages = directories.getTransmissionPackagesFileFullPath();
    Smartmatic::System::SafeBuffer bufferFile;
    Smartmatic::System::IO::File::getHashFile(fileTransmissionPackages, bufferFile);
    std::string hash = bufferFile.GetBase64Data();
    pv.setHashOfTheResults(hash);

    /*******************************************************************/

    std::list <Vote::Vote> demoVotes = Vote::TransmissionPackageWrapper::getInstance()->getAllVoteDemo();
    std::list <Vote::Vote>::iterator itv;
    PVVotes::VoteSequence voteSeq;

    for (itv = demoVotes.begin();
         itv != demoVotes.end();
         itv++)
    {
        PVVote vote = Vote::VoteWrapper::voteToPVVote(electoralConfiguration, *itv);
        voteSeq.push_back(vote);
    }

    votes.setVote(voteSeq);
    votes.setTotal_votes(demoVotes.size());
    pv.setReferenceVotes(votes);

    /*******************************************************************/

    std::ostringstream os;

    try
    {
        Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
        map[""].name = NAMESPACE_PBREPORTS;
        map[""].schema = "";

        serializePVForm(os, pv, map);
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
		ss<< "FATAL - " << __func__ << e.what();
		logger->Debug(ss.str());
        
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.PVFormWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.PBReports.PVFormWrapper.ErrorSerializaData"),
                                                          logger);
    }
    catch (...)
    {
        std::stringstream ss;
		ss<< "FATAL - " << __func__ << __LINE__;
		logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.PVFormWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.PBReports.PVFormWrapper.ErrorSerializaData"),
                                                          logger);
    }

    std::string data = os.str();
    std::string file;

    if (fileFullPath.empty())
    {
        file = directories.getPVFormFileFullPath();
    }
    else
    {
        file = fileFullPath;
    }

    Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, file,
            Smartmatic::SAES::Security::Encryption::UTIL_FILE);
}

void PVFormWrapper::setFileFullPath(std::string fileFullPath)
{
    this->fileFullPath = fileFullPath;
}

void PVFormWrapper::setDurationElection(std::string durationElection)
{
    this->durationElection = durationElection;
}

std::string PVFormWrapper::getDurationElection()
{
    return this->durationElection;
}

std::list <std::string> PVFormWrapper::getLanguages()
{
    std::list <std::string> languages;

    std::string currentLanguage = Smartmatic::SAES::Configuration::SAESLanguageController::getActualLanguage();

    bool allLanguages = SAESCommonConfigurationManager::Current()->isPVInAllLanguages();

    if (allLanguages)
    {
        languages = electoralConfiguration->getLanguageListFullName();
    }

    if (languages.size() == 0)
    {
        languages.push_back(currentLanguage); // generate default
    }

    return languages;
}

bool PVFormWrapper::validate()
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    std::string pvformFileDom = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvformFileFlash = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::list <std::string>::iterator itl;
    std::list <std::string> languages = getLanguages();

    bool validate = true;

    for (itl = languages.begin();
         itl != languages.end();
         itl++)
    {
        std::string lang = (*itl);

        std::string pvformFileDomTemp = Path::GetFullFileNameWithOutExtension(pvformFileDom) + lang + Path::GetFileExtension(pvformFileDom);
        std::string pvformFileFlashTemp = Path::GetFullFileNameWithOutExtension(pvformFileFlash) + lang + Path::GetFileExtension(pvformFileFlash);

        try
        {
            (void)Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(pvformFileDomTemp,
                        Smartmatic::SAES::Security::Encryption::UTIL_FILE);
        }
        catch (...)
        {
            logger->Debug("FATAL - error open " + pvformFileDomTemp);
            validate = false;
            continue;
        }

        if(!File::compareFiles(pvformFileDomTemp, pvformFileFlashTemp))
        {
        	logger->Debug("FATAL - error compare files " + pvformFileDomTemp + " " + pvformFileFlashTemp);
        	validate = false;
        }
    }

    return validate;
}

void PVFormWrapper::deleteFiles()
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    std::string pvformFileDom = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvformFileFlash = directories.getPVFormFileFullPath(BasePathType::CONFIGURATION_FLASH);
    std::string pvreportFileDom = directories.getGeneratedPVReportFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string pvreportFileFlash = directories.getGeneratedPVReportFileFullPath(BasePathType::CONFIGURATION_FLASH);

    std::list <std::string>::iterator itl;
    std::list <std::string> languages = getLanguages();

    for (itl = languages.begin();
         itl != languages.end();
         itl++)
    {
        std::string lang = (*itl);

        std::string pvformFileDomTemp = Path::GetFullFileNameWithOutExtension(pvformFileDom) + lang + Path::GetFileExtension(pvformFileDom);
        std::string pvformFileFlashTemp = Path::GetFullFileNameWithOutExtension(pvformFileFlash) + lang + Path::GetFileExtension(pvformFileFlash);

        std::string pvreportFileDomTemp = Path::GetFullFileNameWithOutExtension(pvreportFileDom) + lang + Path::GetFileExtension(pvreportFileDom);
        std::string pvreportFileFlashTemp = Path::GetFullFileNameWithOutExtension(pvreportFileFlash) + lang + Path::GetFileExtension(pvreportFileFlash);

        Smartmatic::System::IO::File::DeleteFile(pvformFileDomTemp);
        Smartmatic::System::IO::File::DeleteFile(pvformFileFlashTemp);
        Smartmatic::System::IO::File::DeleteFile(pvreportFileDomTemp);
        Smartmatic::System::IO::File::DeleteFile(pvreportFileFlashTemp);
    }
}

void PVFormWrapper::getPVFileNames(std::string file, std::list <std::string> & fileNames)
{
	fileNames.clear();

    std::list <std::string>::iterator itl;
    std::list <std::string> languages = getLanguages();

    for (itl = languages.begin();
         itl != languages.end();
         itl++)
    {
        std::string lang = (*itl);
        std::string tmpFile = Path::GetFileNameWithOutExtension(file) + lang + Path::GetFileExtension(file);
        fileNames.push_back(tmpFile);
    }
}
