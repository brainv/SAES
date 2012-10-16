/**
 * @file ICardController.cxx
 * @brief Body interface card controller
 * @date 15/08/2011
 * @author Yadickson Soto
 */

#include "Configuration/s-a-e-s-common-conf-manager.h"
#include "ICardController.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/ZenityWrapper.hxx>
#include <System/Runtime/ProcessLauncher.h>
#include <stdlib.h>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Card;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Runtime;

ISMTTLog* ICardController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Card.ICardController",GETTEXT_PACKAGE);

ICardController::ICardController()
{

}

ICardController::~ICardController()
{

}

void ICardController::doReaderPowerCycle()
{
	int delayAfterSuspend = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getDelayAfterSuspend();
	int delayAfterOn = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getDelayAfterOn();
    bool showMessage = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getShowMessagePowerCycle();

    if (showMessage)
    {
        int timeout = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getTimeOutMessagePowerCycle();

        ZenityWrapper::showInfo(_("Smartmatic.SAES.Card.ICardController.MessageReaderPowerCycle"),
        		_("Smartmatic.SAES.Card.ICardController.TitleReaderPowerCycle"), timeout);
    }

    std::stringstream ss;
    ss << SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getScriptRunSmartCard() << " " << delayAfterSuspend;

	std::string command = ss.str();
	logger->Debug("Run script " + command);

	(void)ProcessLauncher::RunProcessThroughSystem(command.c_str());
	sleep(delayAfterOn);
}
