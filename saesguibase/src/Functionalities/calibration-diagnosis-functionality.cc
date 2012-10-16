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
#include "Voting/operation-status.h"
#include "Functionalities/calibration-diagnosis-functionality.h"
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
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;
using namespace std;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* CalibrationDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.CalibrationDiagnosisFunctionality",GETTEXT_PACKAGE);
CalibrationDiagnosisFunctionality* CalibrationDiagnosisFunctionality::current_instance = NULL;

CalibrationDiagnosisFunctionality* CalibrationDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new CalibrationDiagnosisFunctionality();

	return current_instance;
};

CalibrationDiagnosisFunctionality::CalibrationDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	calibrationWidget = NULL;
}

CalibrationDiagnosisFunctionality::~CalibrationDiagnosisFunctionality()
{
	deleteElement();
}

void CalibrationDiagnosisFunctionality::Initialize()
{
	calibrationWidget->Initialize();
	connOk = calibrationWidget->signalOk_detected.connect(sigc::mem_fun(*this,&CalibrationDiagnosisFunctionality::signalOkDetected));
};

void CalibrationDiagnosisFunctionality::signalOkDetected()
{
	ExitFunctionality();
}

Gtk::Widget* CalibrationDiagnosisFunctionality::GetFrame()
{
	calibrationWidget = new Smartmatic::SAES::GUI::Widgets::CalibrationDiagnosisWidget("",false,false,false,false,false);
	return calibrationWidget;
};

string CalibrationDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CalibrationDiagnosisFunctionality.CalibrationDiagnosis");
};

MenuOptionDescriptor CalibrationDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MCalibrationDiagnosisFunctionality,false);
};

void CalibrationDiagnosisFunctionality::Dispose()
{
	calibrationWidget->Dispose();
	connOk.disconnect();
};

Smartmatic::Log::ISMTTLog* CalibrationDiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring CalibrationDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CalibrationDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring CalibrationDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CalibrationDiagnosisFunctionality.LogCloseFunctionality");
}

void CalibrationDiagnosisFunctionality::deleteElement()
{
	if(calibrationWidget != NULL)
	{
		delete (calibrationWidget);
		calibrationWidget = NULL;
	}
}
