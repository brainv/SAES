/**
 * @file CheckDirectoryStructure.cxx
 * @brief body class for check directory structure
 */

#include "CheckDirectoryStructure.hxx"
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

ISMTTLog* CheckDirectoryStructure::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.CheckDirectoryStructure",GETTEXT_PACKAGE);

CheckDirectoryStructure::CheckDirectoryStructure(Runtime::Environment::SaesDirectories *directories,
		Smartmatic::SAES::Common::Configuration::BasePathType type)
 : ICheckCondition ( TestStatus::DirectoryStructure,
		 N_("Smartmatic.SAES.Operation.Initiator.CheckDirectoryStructure.CheckingDirStructure"),
	     "ui/check-directory-structure.gif",
	     "ui/check-directory-structure-failed.gif")
{
    this->directories = directories;
    this->type = type;
}

CheckDirectoryStructure::~CheckDirectoryStructure()
{

}

TestStatus::Tests CheckDirectoryStructure::check()
{
    bool success = false;

    std::string electoralSAES = directories->getElectoralSAESFullFolderPath(type);
    std::string electoralResource = directories->getElectoralResourceFullFolderPath(type);

    if (!Directory::DirectoryExists(electoralSAES))
    {
    	logger->Debug("ERROR - load " + electoralSAES);
    }
    else if (!Directory::DirectoryExists(electoralResource))
    {
    	logger->Debug("ERROR - load " + electoralResource);
    }
    else
    {
    	success = true;
    }

	std::string line = "CheckDirectoryStructure result = ";
	logger->Debug(line.append(success ? "Success" : "Failed"));
	
	if(!success)
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.CheckDirectoryStructureFailed"));
	
    return (success ? TestStatus::Passed : TestStatus::Failed);
}
