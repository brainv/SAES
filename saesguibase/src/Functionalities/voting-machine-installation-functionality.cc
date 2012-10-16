/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#include "voting-machine-installation-functionality.h"
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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* VotingMachineInstallationFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality",GETTEXT_PACKAGE);

VotingMachineInstallationFunctionality* VotingMachineInstallationFunctionality::current_instance = NULL; 
VotingMachineInstallationFunctionality* VotingMachineInstallationFunctionality::Current()
{
	if (!current_instance)
		current_instance = new VotingMachineInstallationFunctionality();

	return current_instance;
}


VotingMachineInstallationFunctionality::VotingMachineInstallationFunctionality()
{
	wizardWidget = NULL;
}

VotingMachineInstallationFunctionality::~VotingMachineInstallationFunctionality()
{
}

void VotingMachineInstallationFunctionality::deleteElement()
{
	if (wizardWidget)
	{
		delete(wizardWidget);
		wizardWidget = NULL;
	}
}

Widget* VotingMachineInstallationFunctionality::GetFrame()
{
	wizardWidget = new Smartmatic::SAES::GUI::Widgets::VotingMachineInstallationWizardWidget();
	return wizardWidget;
}

void VotingMachineInstallationFunctionality::HideOnFinish()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.VotingMachineInstalled"));

	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.VotingMachineInstallationSuccessfull"));
	Dispose();
	ExitFunctionality();
}

void VotingMachineInstallationFunctionality::Dispose()
{
	wizardWidget->Dispose();
}

void VotingMachineInstallationFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.NoVotingMachineInstalled"));
	enableExitButton();
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.StartingVotingMachineInstallation"));
	wizardWidget->Initialize();
	connHide = wizardWidget->signalHide_detected.connect(sigc::mem_fun(*this,&VotingMachineInstallationFunctionality::HideOnFinish));
}

string VotingMachineInstallationFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallation");
}

MenuOptionDescriptor VotingMachineInstallationFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MVotingMachineInstallationFunctionality,false);
}

Smartmatic::Log::ISMTTLog* VotingMachineInstallationFunctionality::getLogger()
{
	return logger;
}

Glib::ustring VotingMachineInstallationFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.LogStartFunctionality");
}

Glib::ustring VotingMachineInstallationFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.LogCloseFunctionality");
}			

void VotingMachineInstallationFunctionality::block()
{
	Dispose();
}

void VotingMachineInstallationFunctionality::partial()
{

}

void VotingMachineInstallationFunctionality::resume()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VotingMachineInstallationFunctionality.NoVotingMachineInstalled"));
	ExitFunctionality();
}
