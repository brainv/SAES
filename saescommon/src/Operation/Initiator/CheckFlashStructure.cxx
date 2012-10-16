/**
 * @file CheckFlashStructure.cxx
 * @brief body class for check condition flash presence
 */

#include "CheckFlashStructure.hxx"
#include "Runtime/Environment/DirectoryManager.hxx"
#include <System/IO/File.h>
#include <System/IO/Path.h>
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
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Common::Configuration;

ISMTTLog* CheckFlashStructure::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.CheckFlashStructure",GETTEXT_PACKAGE);

CheckFlashStructure::CheckFlashStructure(Runtime::Environment::SaesDirectories & directories,
		Smartmatic::SAES::Common::Configuration::BasePathType type)
 : ICheckCondition ( TestStatus::FlashStructure,
		 N_("Smartmatic.SAES.Operation.Initiator.CheckingFlashStructure.CheckingFlashStructure"),
				 "ui/check-flash-structure.gif",
				 "ui/check-flash-structure-failed.gif")
{
    this->directories = directories;
    this->type = type;
}

CheckFlashStructure::~CheckFlashStructure()
{

}

TestStatus::Tests CheckFlashStructure::check()
{
    bool success = false;
    std::string basePath = directories.getDevicePath(type);

    std::string bootPath = Smartmatic::System::IO::Path::Combine(basePath,"/boot");
    logger->Debug("validating boot in: " + bootPath);
    std::string squashfs = Smartmatic::System::IO::Path::Combine(basePath,"/live/filesystem.squashfs");
    logger->Debug("validating squashfs in: " + squashfs);
    std::string votingCenters = directories.getVotingCentersInstalationFileFullPath(type);
    logger->Debug("validating votingCenters in: " + votingCenters);

    success =
            Directory::DirectoryExists(bootPath) &&
            File::canOpenFile(squashfs) &&
            File::canOpenFile(votingCenters);

    std::string line = "CheckFlashStructure result = ";
    line.append(success ? "Success" : "Failed");
    line.append(" in " + type);
	logger->Debug(line);


	if(!success)
	{
	    logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.CheckFlashStructureFailed"));
	}

    return (success ? TestStatus::Passed : TestStatus::Failed);
}
