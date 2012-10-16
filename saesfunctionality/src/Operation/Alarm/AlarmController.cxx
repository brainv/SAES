/**
 * @file AlarmController.cxx
 * @brief Body class alarm box monitor
 * @date 16/05/2012
 * @author Yadickson Soto
 */

#include "AlarmController.hxx"
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

using namespace Smartmatic::SAES::Operation::Alarm;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::HW::Devices;

ISMTTLog* AlarmController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Card.AlarmController",GETTEXT_PACKAGE);
AlarmController * AlarmController::instance = NULL;

AlarmController::AlarmController()
{
	this->message = " ";
}

AlarmController::~AlarmController()
{

}

void AlarmController::addAlarm(AlarmEnum alarm)
{
	alarmList.push_back(alarm);

	std::vector<AlarmCommand> alarmCommands;
	std::vector<AlarmStep> alarmSteps;

	switch(alarm)
	{
		case AlarmEnum::CONFIGURATION_UNABLETOREAD:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogUnableToReadCard"));
			logger->Debug("Alarm sent was: LogUnableToReadCard");
			break;
		case AlarmEnum::CONFIGURATION_UNABLETOWRITE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogUnableToWriteCard"));
			logger->Debug("Alarm sent was: Unable to write card");
			break;
		case AlarmEnum::CONFIGURATION_CARDVALIDITYPERIODEXPIRED:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogUnableToWriteCard"));
			logger->Debug("Alarm sent was: Unable to write card");
			break;
		case  AlarmEnum::CONFIGURATION_CRYPTOERROR:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogCryptographicError"));
			logger->Debug("Alarm sent was: Cryptographic error");
			break;
		case AlarmEnum::CONFIGURATION_INVALIDCONTENT:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogInvalidCard"));
			logger->Debug("Alarm sent was: Invalid card");
			break;
		case AlarmEnum::CONFIGURATION_CARDUSED:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogCardUsed"));
			logger->Debug("Alarm sent was: Card used");
			break;
		case AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogInvalidVotingCardData"));
			logger->Debug("Alarm sent was: Invalid voting card data");
            break;
		case AlarmEnum::CONFIGURATION_PRINTERNOTREADYFORVOTE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogPrinterNotReadyForVoterActivation"));
			logger->Debug("Alarm sent was: Printer not ready for voter activation");
			break;
		case AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogPrinterFailure"));
			logger->Debug("Alarm sent was: Printer device failure");
			break;
		case AlarmEnum::CONFIGURATION_PRINTERNEOPAFTERVOTE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogPrinterNearEndOfPaperAfterVoting"));
			logger->Debug("Alarm sent was: Printer near end of paper after last vote printed");
			break;
		case AlarmEnum::CONFIGURATION_PRINTERNEOPBEFOREVOTE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogPrinterNearEndOfPaperBeforeVoting"));
			logger->Debug("Alarm sent was: Printer near end of paper before last vote printed");
			break;
		case AlarmEnum::CONFIGURATION_TIMEOUT:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogTimeOut"));
			logger->Debug("Alarm sent was: Time out");
			break;
		case AlarmEnum::CONFIGURATION_UNEXPECTED:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogUnexpected"));
			logger->Debug("Alarm sent was: Unexpected");
			break;
		case AlarmEnum::CONFIGURATION_CARDNOTREMOVEDAFTERVOTING:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogCardNotRemovedAfterVoting"));
			logger->Debug("Alarm sent was: CardNotRemovedAfterVoting");
			break;
		case AlarmEnum::CONFIGURATION_CARDEXTRACTIONCOUNTER:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogMaximunCardExtractionCounterAlarm"));
			logger->Debug("Alarm sent was: CardExtractionCounterAlarm");
			break;
		case AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.AlarmBoxDisconnected"));
			logger->Debug("Alarm sent was: AlarmBoxDisconnected");
			break;
		case AlarmEnum::CONFIGURATION_ALARMBOXCONNECTED:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.AlarmBoxConnected"));
			logger->Debug("Alarm sent was: AlarmBoxConnected");
			break;
    case AlarmEnum::CONFIGURATION_CARDREADERUNRESPONSIVE:
			logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.CardReaderUnresponsive"));
			logger->Debug("Alarm sent was: CardReaderUnresponsive");
			break;
	}

	SAESFunctionalityConfigurationManager::Current()->getCommandsOfAlarm(alarmCommands, alarm);
	getAlarmSteps(alarmCommands, alarmSteps);
	AlarmDevice::Current()->SoundAlarm(alarmSteps);
}

std::vector<AlarmEnum> & AlarmController::getAlarms()
{
	return alarmList;
}

void AlarmController::clearAlarms()
{
	logger->Audit(N_("Smartmatic.SAES.Operation.AlarmController.LogStackOfAlarmsCleared"));
	logger->Debug("Stack of Alarms Cleared");
	alarmList.clear();
}

bool AlarmController::isCriticalAlarmPending()
{
	bool criticalAlarmPending = false;
	std::vector<AlarmEnum>::iterator it;

	for(it = alarmList.begin();
			it != alarmList.end();
			it++)
	{
		if(SAESFunctionalityConfigurationManager::Current()->getCategoryOfAlarm(*it) == AlarmCategoryEnum::CONFIGURATION_CRITICALALARM)
		{
			criticalAlarmPending = true;
			break;
		}
	}

	return criticalAlarmPending;
}

bool AlarmController::isGoToAuthentication()
{
	bool goToAuthentication = false;
	std::vector<AlarmEnum>::iterator it;

	for(it = alarmList.begin();
			it != alarmList.end();
			it++)
	{
		if(SAESFunctionalityConfigurationManager::Current()->getBehaviorOfAlarm(*it) == AlarmBehaviorEnum::CONFIGURATION_GOAUTHENTICATION)
		{
			goToAuthentication = true;
			break;
		}
	}

	return goToAuthentication;
}

bool AlarmController::isAlarmPending()
{
	return alarmList.size() > 0;
}

void AlarmController::setMessage(std::string message)
{
	this->message = message;
}

std::string AlarmController::getMessage()
{
	return message;
}

void AlarmController::getAlarmSteps(std::vector<AlarmCommand>& alarmCommands, std::vector<AlarmStep>& steps)
{

	for(unsigned int i =0;i < alarmCommands.size();i++)
	{
		AlarmStep step;
		if(alarmCommands[i].getTypeOfCommand()== AlarmCommandEnum::CONFIGURATION_REDLED)
		{
			logger->Debug("Device is Red Led");
			step.setDevice(AlarmStep::AB_Red);
		}
		else if(alarmCommands[i].getTypeOfCommand() == AlarmCommandEnum::CONFIGURATION_GREENLED)
		{
			logger->Debug("Device is Green Led");
			step.setDevice(AlarmStep::AB_Green);
		}
		else if(alarmCommands[i].getTypeOfCommand() == AlarmCommandEnum::CONFIGURATION_BUZZER)
		{
			logger->Debug("Device is Buzzer");
			step.setDevice(AlarmStep::AB_Buzzer);
		}

		step.setPeriod(alarmCommands[i].getPeriod());
		step.setIsOff(alarmCommands[i].getIsOff());
		steps.push_back (step);
	}
}

AlarmController * AlarmController::getInstance()
{
	if (!instance)
	{
		instance = new AlarmController();
	}

	return instance;
}
