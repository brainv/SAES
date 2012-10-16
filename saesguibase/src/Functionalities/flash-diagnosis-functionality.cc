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
#include "Functionalities/flash-diagnosis-functionality.h"
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

using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace std;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* FlashDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.FlashDiagnosisFunctionality",GETTEXT_PACKAGE);

FlashDiagnosisFunctionality* FlashDiagnosisFunctionality::current_instance = NULL;

FlashDiagnosisFunctionality* FlashDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new FlashDiagnosisFunctionality();

	return current_instance;
};

FlashDiagnosisFunctionality::FlashDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	flashWidget = NULL;
}

FlashDiagnosisFunctionality::~FlashDiagnosisFunctionality()
{
	deleteElement();
}

void FlashDiagnosisFunctionality::Initialize()
{
	flashWidget->Initialize();
	connFlashDiag = flashWidget->signalContinue_detected.connect( sigc::mem_fun(this, &FlashDiagnosisFunctionality::on_FlashDiagFinished));
};

void FlashDiagnosisFunctionality::on_FlashDiagFinished()
{
	enableExitButton();
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.FlashDiagnosisFunctionality.FlashDiagnosisExecuted"));
};

Gtk::Widget* FlashDiagnosisFunctionality::GetFrame()
{
	flashWidget = new Smartmatic::SAES::GUI::Widgets::FlashDiagnosisWidget("",false,false,false,false);
	return flashWidget;
};

string FlashDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FlashDiagnosisFunctionality.FlashDiagnosis");
};

MenuOptionDescriptor FlashDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MFlashDiagnosisFunctionality,false);
};

void FlashDiagnosisFunctionality::Dispose()
{
	connFlashDiag.disconnect();
	flashWidget->Dispose();
};

Smartmatic::Log::ISMTTLog* FlashDiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring FlashDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FlashDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring FlashDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.FlashDiagnosisFunctionality.LogCloseFunctionality");
}

void FlashDiagnosisFunctionality::deleteElement()
{
	if(flashWidget)
	{
		delete (flashWidget);
		flashWidget = NULL;
	}
}
