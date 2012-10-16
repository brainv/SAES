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
#include "Functionalities/brightness-diagnosis-functionality.h"
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

ISMTTLog* BrightnessDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.BrightnessDiagnosisFunctionality",GETTEXT_PACKAGE);
BrightnessDiagnosisFunctionality* BrightnessDiagnosisFunctionality::current_instance = NULL;

BrightnessDiagnosisFunctionality* BrightnessDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new BrightnessDiagnosisFunctionality();

	return current_instance;
}

BrightnessDiagnosisFunctionality::BrightnessDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	brightnessWidget = NULL;
}

BrightnessDiagnosisFunctionality::~BrightnessDiagnosisFunctionality()
{
	deleteElement();
}

void BrightnessDiagnosisFunctionality::Initialize()
{
	brightnessWidget->Initialize ();
	connOk = brightnessWidget->signalOk_detected.connect(sigc::mem_fun(*this,&BrightnessDiagnosisFunctionality::signalOkDetected));
};

Gtk::Widget* BrightnessDiagnosisFunctionality::GetFrame()
{
	brightnessWidget = new Smartmatic::SAES::GUI::Widgets::BrightnessDiagnosisWidget("",false,false,false,false);
	return brightnessWidget;
};

void BrightnessDiagnosisFunctionality::signalOkDetected()
{
	ExitFunctionality();
}

string BrightnessDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BrightnessDiagnosisFunctionality.WindowTitle");
};

MenuOptionDescriptor BrightnessDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MBrightnessDiagnosisFunctionality,false);
};

void BrightnessDiagnosisFunctionality::Dispose()
{
	brightnessWidget->Dispose();
	connOk.disconnect();
};

Smartmatic::Log::ISMTTLog* BrightnessDiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring BrightnessDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BrightnessDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring BrightnessDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BrightnessDiagnosisFunctionality.LogCloseFunctionality");
}

void BrightnessDiagnosisFunctionality::deleteElement()
{
	if(brightnessWidget)
	{
		delete brightnessWidget;
		brightnessWidget = NULL;
	}
}
