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
#include "Functionalities/barcode-diagnosis-functionality.h"
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

ISMTTLog* BarcodeDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.BarcodeDiagnosisFunctionality",GETTEXT_PACKAGE);

BarcodeDiagnosisFunctionality* BarcodeDiagnosisFunctionality::current_instance = NULL;


BarcodeDiagnosisFunctionality* BarcodeDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new BarcodeDiagnosisFunctionality();

	return current_instance;
};

BarcodeDiagnosisFunctionality::BarcodeDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	readerWidget = NULL;
}

BarcodeDiagnosisFunctionality::~BarcodeDiagnosisFunctionality()
{
	deleteElement();
}

void BarcodeDiagnosisFunctionality::Initialize()
{
	readerWidget->Initialize();
	readerWidget->signal_printing().connect(sigc::mem_fun(this, &BarcodeDiagnosisFunctionality::on_printing_signal));
	connBCDiag.disconnect();
	connBCDiag = readerWidget->signalContinue_detected.connect( sigc::mem_fun(this, &BarcodeDiagnosisFunctionality::on_BCDiagFinished));
};

void BarcodeDiagnosisFunctionality::on_printing_signal(bool isPrinting)
{
	setExitButtonSensitive(!isPrinting);
}

void BarcodeDiagnosisFunctionality::on_BCDiagFinished()
{
	enableExitButton();
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.BarcodeDiagnosisFunctionality.BarcodeDiagnosisExecuted"));
}

Gtk::Widget* BarcodeDiagnosisFunctionality::GetFrame()
{
	readerWidget = new Smartmatic::SAES::GUI::Widgets::BarCodeDiagnosisWidget("",false, false, false,false);
	return readerWidget;
};

string BarcodeDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BarcodeDiagnosisFunctionality.WindowTitle");
};

MenuOptionDescriptor BarcodeDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MBarcodeDiagnosisFunctionality,false);
};

void BarcodeDiagnosisFunctionality::Dispose()
{
	connBCDiag.disconnect();
	readerWidget->Dispose();
}

Smartmatic::Log::ISMTTLog* BarcodeDiagnosisFunctionality::getLogger()

{
	return logger;
}
Glib::ustring BarcodeDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BarcodeDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring BarcodeDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.BarcodeDiagnosisFunctionality.LogCloseFunctionality");
}

void BarcodeDiagnosisFunctionality::deleteElement()
{
	if(readerWidget)
	{
		delete readerWidget;
		readerWidget = NULL;
	}
}
