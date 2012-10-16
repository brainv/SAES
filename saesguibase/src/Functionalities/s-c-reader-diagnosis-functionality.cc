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
#include "s-c-reader-diagnosis-functionality.h"
#include <Log/SMTTLogManager.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

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
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace std;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;

ISMTTLog* SCReaderDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.SCReaderDiagnosisFunctionality",GETTEXT_PACKAGE);

SCReaderDiagnosisFunctionality* SCReaderDiagnosisFunctionality::current_instance = NULL;

SCReaderDiagnosisFunctionality* SCReaderDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new SCReaderDiagnosisFunctionality();

	return current_instance;
};

SCReaderDiagnosisFunctionality::SCReaderDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	readerWidget = NULL;
}

SCReaderDiagnosisFunctionality::~SCReaderDiagnosisFunctionality()
{
	deleteElement();
}

void SCReaderDiagnosisFunctionality::Initialize()
{
	readerWidget->Initialize ();
	connSCDiag.disconnect();
	connSCDiag = readerWidget->signalContinue_detected.connect( sigc::mem_fun(this, &SCReaderDiagnosisFunctionality::on_SCDiagFinished));
};

void SCReaderDiagnosisFunctionality::on_SCDiagFinished()
{
	enableExitButton();
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.SCReaderDiagnosisFunctionality.SmartcardReaderDiagnosisExecuted"));
}

Gtk::Widget* SCReaderDiagnosisFunctionality::GetFrame()
{
	readerWidget = new Smartmatic::SAES::GUI::Widgets::SmartCardReaderDiagnosisWidget("",false, false, false,false);
	return readerWidget;
};

string SCReaderDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.SCReaderDiagnosisFunctionality.SmartcardReaderDiagnosis");
};

MenuOptionDescriptor SCReaderDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MSCReaderDiagnosisFunctionality,false);
};

void SCReaderDiagnosisFunctionality::Dispose()
{
	connSCDiag.disconnect();

	if (readerWidget)
	{
		readerWidget->Dispose();
	}
};

Smartmatic::Log::ISMTTLog* SCReaderDiagnosisFunctionality::getLogger()
{
	return logger;
}

Glib::ustring SCReaderDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.SCReaderDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring SCReaderDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.SCReaderDiagnosisFunctionality.LogCloseFunctionality");
}

void SCReaderDiagnosisFunctionality::deleteElement()
{
	if (readerWidget)
	{
		delete readerWidget;
		readerWidget = NULL;
	}
}
