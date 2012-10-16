/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#include "poll-worker-register-functionality.h"
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <time.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;


ISMTTLog* PollWorkerRegisterFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality",GETTEXT_PACKAGE);

PollWorkerRegisterFunctionality* PollWorkerRegisterFunctionality::current_instance = NULL;

PollWorkerRegisterFunctionality::PollWorkerRegisterFunctionality()
:GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	pollWorkerMemberRegisterWidget = NULL;
}


PollWorkerRegisterFunctionality* PollWorkerRegisterFunctionality::Current()
{
	if (!current_instance)
		current_instance = new PollWorkerRegisterFunctionality();

	return current_instance;
};

void PollWorkerRegisterFunctionality::deleteElement()
{
	if (pollWorkerMemberRegisterWidget)
	{
		delete pollWorkerMemberRegisterWidget;
		pollWorkerMemberRegisterWidget = NULL;
	}
}

void PollWorkerRegisterFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality.SavingPollWorkers"));
	enableExitButton();

	if (pollWorkerMemberRegisterWidget)
	{
		pollWorkerMemberRegisterWidget->Load();
	}
};

Gtk::Widget* PollWorkerRegisterFunctionality::GetFrame()
{
	pollWorkerMemberRegisterWidget = new PollWorkerMemberRegisterWidget();
	pollWorkerMemberRegisterWidget->getSignalEnabled().connect(sigc::mem_fun(*this, &PollWorkerRegisterFunctionality::enableExitButton));
	pollWorkerMemberRegisterWidget->getSignalDisabled().connect(sigc::mem_fun(*this, &PollWorkerRegisterFunctionality::disableExitButton));

	return pollWorkerMemberRegisterWidget;
}

string PollWorkerRegisterFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality.PollWorkerFunctionality");
};

Smartmatic::Functionality::MenuOptionDescriptor PollWorkerRegisterFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MPollWorkerRegisterFunctionality,false);
};	

void PollWorkerRegisterFunctionality::Dispose()
{
	if(pollWorkerMemberRegisterWidget && pollWorkerMemberRegisterWidget->checkNewStatus())
	{
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality.ElectionStatusChanged"));
		RefreshInfo();
	}

	if (pollWorkerMemberRegisterWidget)
	{
		pollWorkerMemberRegisterWidget->Dispose();
	}
}

Smartmatic::Log::ISMTTLog* PollWorkerRegisterFunctionality::getLogger()
{
	return logger;
}

Glib::ustring PollWorkerRegisterFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality.LogStartFunctionality");
}

Glib::ustring PollWorkerRegisterFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PollWorkerRegisterFunctionality.LogCloseFunctionality");
}

