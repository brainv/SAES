/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Log/SMTTLogManager.h>
#include "register-president-notes-functionality.h"
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

RegisterPresidentNotesFunctionality* RegisterPresidentNotesFunctionality::current_instance = NULL;

Smartmatic::Log::ISMTTLog* RegisterPresidentNotesFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.RegisterPresidentNotesFunctionality",GETTEXT_PACKAGE);

RegisterPresidentNotesFunctionality* RegisterPresidentNotesFunctionality::Current()
{
	if (!current_instance)
		current_instance = new RegisterPresidentNotesFunctionality();

	return current_instance;
};

RegisterPresidentNotesFunctionality::RegisterPresidentNotesFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	closeNoteWidget = NULL;
}

void RegisterPresidentNotesFunctionality::deleteElement()
{
	if (closeNoteWidget)
	{
		delete closeNoteWidget;
		closeNoteWidget = NULL;
	}
}

void RegisterPresidentNotesFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.RegisterPresidentNotesFunctionality.SavingNotes"));
	enableExitButton();
}

void RegisterPresidentNotesFunctionality::on_close_clicked()
{
	ExitFunctionality();
}

Gtk::Widget* RegisterPresidentNotesFunctionality::GetFrame()
{
	closeNoteWidget = new CloseNoteWidget();
	closeNoteWidget->getSignalEnabled().connect(sigc::mem_fun(*this, &RegisterPresidentNotesFunctionality::enableExitButton));
	closeNoteWidget->getSignalDisabled().connect(sigc::mem_fun(*this, &RegisterPresidentNotesFunctionality::disableExitButton));

	return closeNoteWidget;
};

string RegisterPresidentNotesFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RegisterPresidentNotesFunctionality.RegisterPresidentNotes");
}

Smartmatic::Functionality::MenuOptionDescriptor RegisterPresidentNotesFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MRegisterPresidentNotesFunctionality,false);
}

void RegisterPresidentNotesFunctionality::Dispose()
{

}

Smartmatic::Log::ISMTTLog* RegisterPresidentNotesFunctionality::getLogger()
{
	return logger;
}

Glib::ustring RegisterPresidentNotesFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RegisterPresidentNotesFunctionality.LogStartFunctionality");
}

Glib::ustring RegisterPresidentNotesFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RegisterPresidentNotesFunctionality.LogCloseFunctionality");
}
