/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
* saesguibase
* Copyright (C)  2011 <>
*
* saesguibase is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* saesguibase is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "alarm-box-diagnosis-widget.h"
#include "Configuration/label-configuration.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/FactoryMethodWidget.hxx>
#include <Devices/alarm-device.h>

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

using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;	
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation;

ISMTTLog* AlarmBoxDiagnosisWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget",GETTEXT_PACKAGE);

AlarmBoxDiagnosisWidget::AlarmBoxDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
:BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::AlarmBox, hasOk,hasCancel,hasMessage,showButtons)
{
	status = false;
	progressWidget = FactoryMethodWidget::createProgressWidget();

	LabelConfiguration diagConf = SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	progressWidget->setTextConfig(diagConf);
	progressWidget->setImage("ui/alarmButton.jpg");

	setDiagnosticFrame(*progressWidget);
	this->show_all_children();
}

AlarmBoxDiagnosisWidget::~AlarmBoxDiagnosisWidget()
{
	deleteElement();
}

void AlarmBoxDiagnosisWidget::deleteElement()
{
	remove();

	if(progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
}

void AlarmBoxDiagnosisWidget::Initialize()
{
	timerCounter = 0;
	buttonPress = false;

	progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget.InitializingDiagnostic"));

	connAlarm.disconnect();
	connAlarm = AlarmDevice::Current()->signal_button_press_detected().connect(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::BoxButtonPressed));

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::SendTest), 1000);
}

void AlarmBoxDiagnosisWidget::BoxButtonPressed()
{
	AlarmDevice::Current()->TurnOffRedLed();
	usleep(200000);
	AlarmDevice::Current()->TurnOffGreenLed();
	usleep(200000);
	AlarmDevice::Current()->TurnOffBuzzer();
	buttonPress = true;
}


bool AlarmBoxDiagnosisWidget::Refresh(int time_num)
{
	timerCounter++;

	if(timerCounter == 5 && !buttonPress)
	{
		timerCounter = 0;

		BoxButtonPressed();

		status = false;
		message = _("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget.DiagnosticFailed");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::showResult), 100);

		return false;
	}
	else if(buttonPress)
	{
		timerCounter = 0;
		status = true;
		message = _("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget.DiagnosticSuccessful");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::showResult), 100);

		return false;
	}

	return true;
}


void AlarmBoxDiagnosisWidget::SendTest()
{
	progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget.PressButtonMessage"));
    if(!Glib::thread_supported()) Glib::thread_init();
    Glib::Thread::create(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::test), false);
}

void AlarmBoxDiagnosisWidget::test()
{
	logger->Debug("AlarmBoxDiagnosisWidget Send Test");

	ping = AlarmDevice::Current()->sendPing();

	if(ping)
	{
		buttonPress = false;
		AlarmDevice::Current()->TurnOnRedLed(1);
		usleep(200000);
		AlarmDevice::Current()->TurnOnGreenLed(1);
		usleep(200000);
		AlarmDevice::Current()->TurnOnBuzzer(1);

		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::Refresh), 0);
		connRefresh.disconnect();
		connRefresh = Glib::signal_timeout().connect(my_slot,1000);
	}
	else
	{
		status = false;
		message = _("Smartmatic.SAES.GUI.Widgets.AlarmBoxDiagnosisWidget.AlarmBoxNotReach");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &AlarmBoxDiagnosisWidget::showResult), 100);
	}
}

void AlarmBoxDiagnosisWidget::showResult()
{
	progressWidget->setText(message);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::AlarmBox, status ? OperationStatus::Ok : OperationStatus::Error);
	signalContinue_detected.emit();
}

void AlarmBoxDiagnosisWidget::Dispose()
{
	connRefresh.disconnect();
	connAlarm.disconnect();

	BoxButtonPressed();

	buttonPress = false;
}

