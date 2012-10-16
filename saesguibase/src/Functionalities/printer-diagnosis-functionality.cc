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

#include "printer-diagnosis-functionality.h"
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

using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* PrinterDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.PrinterDiagnosisFunctionality",GETTEXT_PACKAGE);

PrinterDiagnosisFunctionality* PrinterDiagnosisFunctionality::current_instance = NULL;

PrinterDiagnosisFunctionality* PrinterDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new PrinterDiagnosisFunctionality();

	return current_instance;
};

PrinterDiagnosisFunctionality::PrinterDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	printerWidget = NULL;
}

PrinterDiagnosisFunctionality::~PrinterDiagnosisFunctionality()
{
	deleteElement();
}

void PrinterDiagnosisFunctionality::Initialize()
{
	printerWidget->Initialize();
	connPrinterDiag = printerWidget->signalContinue_detected.connect( sigc::mem_fun(this, &PrinterDiagnosisFunctionality::on_PrinterDiagFinished));
	connPrinterDiagOnOk = printerWidget->signalOk_detected.connect( sigc::mem_fun(this, &PrinterDiagnosisFunctionality::on_PrinterDiagFinished));
	connPrinterDiagOnCancel = printerWidget->signalCancel_detected.connect( sigc::mem_fun(this, &PrinterDiagnosisFunctionality::on_PrinterDiagFinished));
};

void PrinterDiagnosisFunctionality::on_PrinterDiagFinished()
{
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrinterDiagnosisFunctionality.PrinterDiagnosisExecuted"));
	enableExitButton();
}

Gtk::Widget* PrinterDiagnosisFunctionality::GetFrame()
{
	printerWidget = new Smartmatic::SAES::GUI::Widgets::PrinterDiagnosisWidget("",false, false, false,true);
	return printerWidget;
};

std::string PrinterDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrinterDiagnosisFunctionality.PrinterDiagnosis");
};

MenuOptionDescriptor PrinterDiagnosisFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MPrinterDiagnosisFunctionality,false);
};

void PrinterDiagnosisFunctionality::Dispose()
{
	printerWidget->Dispose();
};

Smartmatic::Log::ISMTTLog* PrinterDiagnosisFunctionality::getLogger()
{
	return logger;
}

Glib::ustring PrinterDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrinterDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring PrinterDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrinterDiagnosisFunctionality.LogCloseFunctionality");
}

void PrinterDiagnosisFunctionality::deleteElement()
{
	if (printerWidget)
	{
		delete printerWidget;
		printerWidget = NULL;
	}
}
