/**
 * @file AlarmMessage.cxx
 * @brief Body class alarm message text
 * @date 12/04/2012
 * @author Yadickson Soto
 */

#include "AlarmMessage.hxx"
#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
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

using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Alarm;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* AlarmMessage::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Operation.AlarmMessage",GETTEXT_PACKAGE);

AlarmMessage::AlarmMessage()
{

}

AlarmMessage::~AlarmMessage()
{

}

void AlarmMessage::alarm(AlarmEnum alarmType, std::string optionalText)
{
	MachineOperationManager::getInstance()->getAlarmController()->addAlarm(alarmType);
	std::string alarmMessage;

	if (optionalText.empty())
	{
		switch(alarmType)
		{
			case AlarmEnum::CONFIGURATION_PRINTERNOTREADYFORVOTE:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.PrinterError");
				break;

			case AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorInfoVotingCardData");
				break;

			case AlarmEnum::CONFIGURATION_INVALIDCONTENT:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.AlarmActivated");
				break;

			case AlarmEnum::CONFIGURATION_CARDEXTRACTIONCOUNTER:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.SmartCardExtracted");
				break;

			case AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote");
				break;

			case AlarmEnum::CONFIGURATION_PRINTERNEOPAFTERVOTE:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterNearEndOfPaperAfterVote");
				break;

			case AlarmEnum::CONFIGURATION_CARDNOTREMOVEDAFTERVOTING:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.CardNotExtracted");
				break;

			case AlarmEnum::CONFIGURATION_UNABLETOREAD:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.AlarmActivated");
				break;

			case AlarmEnum::CONFIGURATION_CARDUSED:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.AlarmCardUsed");
				break;

			case AlarmEnum::CONFIGURATION_CARDVALIDITYPERIODEXPIRED:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.CardValidityPeriodExpired");
				break;

			case AlarmEnum::CONFIGURATION_UNABLETOWRITE:
				alarmMessage = N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.ErrorWriteCard");
				break;

			case AlarmEnum::CONFIGURATION_TIMEOUT:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutEndVotingExperience");
				break;

			case AlarmEnum::CONFIGURATION_CRYPTOERROR:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.CryptoError");
				break;

			case AlarmEnum::CONFIGURATION_UNEXPECTED:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.UnexpectedAlarm");
				break;

			case AlarmEnum::CONFIGURATION_PRINTERNEOPBEFOREVOTE:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterNearEndOfPaperBeforeVote");
				break;

			case AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.AlarmBoxDisconnected");
				break;

			case AlarmEnum::CONFIGURATION_ALARMBOXCONNECTED:
				alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.AlarmBoxConnected");
				break;

      case AlarmEnum::CONFIGURATION_CARDREADERUNRESPONSIVE:
        alarmMessage = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.CardReaderUnresponsive");
				break;
		}
	}
	else
	{
		alarmMessage = optionalText;
	}

	logger->Audit(alarmMessage);
	MachineOperationManager::getInstance()->getAlarmController()->setMessage(alarmMessage);
}
