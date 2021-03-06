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

#include "alarm-box-diagnosis-functionality.h"
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

using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace std;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* AlarmBoxDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.AlarmBoxDiagnosisFunctionality",GETTEXT_PACKAGE);

AlarmBoxDiagnosisFunctionality::AlarmBoxDiagnosisFunctionality():GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	alarmWidget = NULL;
}

AlarmBoxDiagnosisFunctionality* AlarmBoxDiagnosisFunctionality::current_instance = NULL;

AlarmBoxDiagnosisFunctionality* AlarmBoxDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new AlarmBoxDiagnosisFunctionality();

	return current_instance;
};

AlarmBoxDiagnosisFunctionality::~AlarmBoxDiagnosisFunctionality()
{
	deleteElement();
}

void AlarmBoxDiagnosisFunctionality::deleteElement()
{
	if(alarmWidget)
	{
		delete(alarmWidget);
		alarmWidget = NULL;
	}
}

void AlarmBoxDiagnosisFunctionality::Initialize()
{
	alarmWidget->Initialize();
	connFinishDiagnosis.disconnect();
	connFinishDiagnosis = alarmWidget->signalContinue_detected.connect(sigc::mem_fun(*this, &AlarmBoxDiagnosisFunctionality::enableExitButton));
};


Gtk::Widget* AlarmBoxDiagnosisFunctionality::GetFrame()
{
	alarmWidget = new Smartmatic::SAES::GUI::Widgets::AlarmBoxDiagnosisWidget("",false, false, false,false);
	return alarmWidget;
};

string AlarmBoxDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AlarmBoxDiagnosisFunctionality.AlarmBoxDiagnosis");
};

MenuOptionDescriptor AlarmBoxDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MAlarmBoxDiagnosisFunctionality,false);
};

void AlarmBoxDiagnosisFunctionality::Dispose()
{
	alarmWidget->Dispose();
	connFinishDiagnosis.disconnect();
};

Smartmatic::Log::ISMTTLog* AlarmBoxDiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring AlarmBoxDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AlarmBoxDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring AlarmBoxDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AlarmBoxDiagnosisFunctionality.LogCloseFunctionality");
}


