/**
 * @file CheckFlashPresence.cxx
 * @brief body class for check condition flash presence
 */

#include "CheckFlashPresence.hxx"
#include <Log/SMTTLogManager.h>
#include <System/IO/Directory.h>
#include <Runtime/Environment/MemoryPathController.h>

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
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Runtime::Environment;

ISMTTLog* CheckFlashPresence::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Initiator.CheckFlashPresence",GETTEXT_PACKAGE);

CheckFlashPresence::CheckFlashPresence(bool infinity)
 : ICheckCondition ( TestStatus::FlashPresence,
		 N_("Smartmatic.SAES.Operation.Initiator.CheckFlashPresence.CheckingFlashPresence"),
		 "ui/check-flash-presence.gif",
		 "ui/check-flash-presence-failed.gif")
{
    this->infinity = infinity;
}

CheckFlashPresence::~CheckFlashPresence()
{

}

TestStatus::Tests CheckFlashPresence::check()
{
    bool success = false;

    do
    {
        std::string flashMedia = MemoryPathController::getInstance()->getFlashMemoryBasePath();
        success = Directory::DirectoryExists( flashMedia );
        sleep (1);
    }
    while (!success && infinity);

    std::string line = "CheckFlashPresence result = ";
	logger->Debug(line.append(success ? "Success" : "Failed"));
	
	if(!success)
		logger->Audit(N_("Smartmatic.SAES.Operation.Initiator.CheckFlashPresenceFailed"));
	
    return (success ? TestStatus::Passed : TestStatus::Failed);
}
