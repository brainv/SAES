/**
 * @file CodiFileManager.cxx
 * @brief Body codi file manager
 * @date 14/02/2012
 * @author Yadickson Soto
 */

#include "CodiFileManager.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include "CodiInfo.hxx"
#include <Configuration/s-a-e-s-conf-manager.h>
using namespace Smartmatic::SAES::Configuration;

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

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::Log;

ISMTTLog* CodiFileManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.CodiFileManager",GETTEXT_PACKAGE);

static const char * inputFile[] =
{
		 "DC" ///< (CK) Chambre
		,"DL" ///< (SE) Sénat
		,"DL" ///< (EU) Parlement européen
		,"DC" ///< (VL) Parlement flamand
		,"DC" ///< (WL) Parlement wallon
		,"DR" ///< (BR) Parlement de la Région de Bruxelles-Capitale
		,"DG" ///< (DE) Parlement de la Communauté germanophone
		,"DD" ///< (PR) Conseils provinciaux
		,"DM" ///< (CG) Conseils communaux
		,"DI" ///< (DI) Conseils de district (à Anvers)
		,"DM" ///< (CS) Conseils de CPAS
};///< input code files

CodiFileManager::CodiFileManager()
{

}

CodiFileManager::~CodiFileManager()
{

}

void CodiFileManager::getInputContestFileName(std::string customCode, std::string & file)
{
	std::string typeFile;
	std::string electionType = CodiInfo::getElectionType(customCode);
	std::string niscode = CodiInfo::getInputNisCode(customCode);

	getTypeFile(electionType, inputFile, typeFile);
	file = typeFile + niscode + "." + electionType;
}

void CodiFileManager::getOutputContestFileName(
		std::string customCode,
		std::string & file,
		std::string codiMachine,
		std::string codiVotingType,
		std::string customniscode)
{
	file.clear();

	try
	{
		std::string electionType = CodiInfo::getElectionType(customCode);
		std::string niscode = CodiInfo::getOutputNisCode(customCode, customniscode);
		std::string stringFile = SAESConfigurationManager::Current()->getCodiFileConfiguration().getFirstStringFileName();

		switch(SAESConfigurationManager::Current()->getCodiFileConfiguration().getRuleCodiFileName())
		{
			case RuleCodiFileNameConfiguration::CONFIGURATION_TOTALIZATION_TYPE:
				file = stringFile + codiVotingType + niscode + "." + electionType;
				break;

			case RuleCodiFileNameConfiguration::CONFIGURATION_CODE_MACHINE:
				file = stringFile + codiMachine + niscode + "." + electionType;
				break;
		}
	}
	catch (...)
	{
		logger->Debug("FATAL - Error in getOutputContestFileName");
	}
}

void CodiFileManager::getTypeFile(std::string electionType, const char * files[], std::string & typeFile)
{
	if (electionType == "CK") // (CK) Chambre
	{
		typeFile = files[CK];
	}
	else if (electionType == "SE") // (SE) Sénat
	{
		typeFile = files[SE];
	}
	else if (electionType == "EU") // (EU) Parlement européen
	{
		typeFile = files[EU];
	}
	else if (electionType == "VL") // (VL) Parlement flamand
	{
		typeFile = files[VL];
	}
	else if (electionType == "WL") // (WL) Parlement wallon
	{
		typeFile = files[WL];
	}
	else if (electionType == "BR") // (BR) Parlement de la Région de Bruxelles-Capitale
	{
		typeFile = files[BR];
	}
	else if (electionType == "DE") // (DE) Parlement de la Communauté germanophone
	{
		typeFile = files[DE];
	}
	else if (electionType == "PR") // (PR) Conseils provinciaux
	{
		typeFile = files[PR];
	}
	else if (electionType == "CG") // (CG) Conseils communaux
	{
		typeFile = files[CG];
	}
	else if (electionType == "DI") // (DI) Conseils de district (à Anvers)
	{
		typeFile = files[DI];
	}
	else if (electionType == "CS") // (CS) Conseils de CPAS
	{
		typeFile = files[CS];
	}
	else
	{
		logger->Debug("ERROR - Election type (" + electionType + ") not found.");
	}
}
