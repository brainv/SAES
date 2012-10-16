/**
 * @file VMWindow.cxx
 * @brief Body class vm window
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#include "VMWindow.hxx"
#include <Operation/Alarm/AlarmBoxMonitor.hxx>
#include <Devices/alarm-device.h>
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/AlarmMessage.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation::Alarm;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* VMWindow::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.VMWindow",GETTEXT_PACKAGE);

VMWindow::VMWindow()
: RunMachineWindow()
{
	initialize();
	nextStep();
	show();
}

VMWindow::~VMWindow()
{
	connAlarmButtom.disconnect();
	connAlarmConnected.disconnect();
}

void VMWindow::initialize()
{
	wizardStep.push_back(INSTALL_MACHINE);
	wizardStep.push_back(AUTOMATIC_DIAGNOSTIC);
	wizardStep.push_back(INITIATOR);
	wizardStep.push_back(PROCESS);
	wizardStep.push_back(END);
}

bool VMWindow::start()
{
	logger->Debug("Start check alarm button");

	connAlarmButtom.disconnect();
	connAlarmButtom = AlarmDevice::Current()->signal_button_press_detected().connect(sigc::mem_fun(*this, &VMWindow::clearAlarm));

	bool enable = SAESGUIConfigurationManager::Current()->getAlarmBoxMonitorConfiguration().getEnable();

	if (enable)
	{
		connAlarmConnected.disconnect();
		connAlarmDisconnected.disconnect();

		//connAlarmConnected = AlarmBoxMonitor::getInstance()->signalConnect.connect(sigc::mem_fun(*this, &VMWindow::alarmBoxConnected));
		connAlarmDisconnected = AlarmBoxMonitor::getInstance()->signalDisconnect.connect(sigc::mem_fun(*this, &VMWindow::alarmBoxDisconnected));

		unsigned int monitoringTime = SAESGUIConfigurationManager::Current()->getAlarmBoxMonitorConfiguration().getMonitoringTime();
		unsigned int searchTime = SAESGUIConfigurationManager::Current()->getAlarmBoxMonitorConfiguration().getSearchTime();

		AlarmBoxMonitor::getInstance()->start(monitoringTime, searchTime);
	}

	return true;
}

void VMWindow::pause()
{
	connAlarmButtom.disconnect();
	connAlarmDisconnected.disconnect();
}

void VMWindow::stop()
{
	logger->Debug("Stop check alarm button");
	MachineOperationManager::getInstance()->getAlarmController()->setMessage(" ");
	connAlarmButtom.disconnect();
	connAlarmConnected.disconnect();
	AlarmBoxMonitor::getInstance()->stop();
}

void VMWindow::clearAlarm()
{
	logger->Debug("Clear alarm");

	if(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getAlarmController()->isAlarmPending())
	{
		MachineOperationManager::getInstance()->getAlarmController()->clearAlarms();
		AlarmDevice::Current()->ShutDownAlarm();
	}
	else
	{
		MachineOperationManager::getInstance()->getAlarmController()->setMessage(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.BackButtonPressed"));
	}

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &VMWindow::updateMessage), 100);
}

void VMWindow::alarmBoxConnected()
{
	logger->Debug("alarmBoxConnected");
	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_ALARMBOXCONNECTED);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &VMWindow::updateMessage), 100);
}

void VMWindow::alarmBoxDisconnected()
{
	logger->Debug("alarmBoxDisconnected");
	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &VMWindow::updateMessage), 100);
}

void VMWindow::alarmBoxNotFound()
{
	logger->Debug("alarmBoxNotFound");
	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &VMWindow::updateMessage), 1000);
}

void VMWindow::updateMessage()
{
	authenticationWidget->clearPassword();
}
