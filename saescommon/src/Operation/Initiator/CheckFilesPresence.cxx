/**
 * @file CheckFilesPresence.cxx
 * @brief body class for check condition files presence
 */

#include "CheckFilesPresence.hxx"
#include <System/IO/Directory.h>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::SAES::Operation::Initiator;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;

ISMTTLog* CheckFilesPresence::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.CheckingFilePresence",GETTEXT_PACKAGE);

CheckFilesPresence::CheckFilesPresence(Runtime::Environment::SaesDirectories *directories,
		Smartmatic::SAES::Common::Configuration::BasePathType type)
 : ICheckCondition ( TestStatus::FilesPresence,
		 N_("Smartmatic.SAES.Operation.Initiator.CheckFilesPresence.CheckingFilePresence"),
		"ui/check-file-presence.gif",
		"ui/check-file-presence-failed.gif")
{
    this->directories = directories;
    this->type = type;
}

CheckFilesPresence::~CheckFilesPresence()
{

}

TestStatus::Tests CheckFilesPresence::check()
{
    bool success = false;

    std::string electionFile = directories->getElectionFileFullPath(type);
    std::string votingDeviceFile = directories->getVotingDeviceFileFullPath(type);
    std::string secretKeyFile = directories->getSecretKeyFileFullPath (type);
    std::string machineKeysFile = directories->getMachineKeysFileFullPath (type);

    if (!Directory::FileExists(electionFile))
    {
		logger->Debug("ERROR - load file " + electionFile);
    }
    else if (!Directory::FileExists(votingDeviceFile))
    {
		logger->Debug("ERROR - load file " + votingDeviceFile);
    }
    else if (!Directory::FileExists(secretKeyFile))
    {
		logger->Debug("ERROR - load file " + secretKeyFile);
    }
    else if (!Directory::FileExists(machineKeysFile))
    {
		logger->Debug("ERROR - load file " + machineKeysFile);
    }
    else
    {
    	success = true;
    }

    std::string line = "CheckingFilePresence result = ";
	logger->Debug(line.append(success ? "Success" : "Failed"));
	
	if(!success)
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.CheckingFilePresenceFailed"));
	
    return (success ? TestStatus::Passed : TestStatus::Failed);
}
