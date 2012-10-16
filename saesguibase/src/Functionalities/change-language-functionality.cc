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

#include "change-language-functionality.h"
#include "Operation/MachineOperationManager.hxx"
#include <Log/SMTTLogManager.h>
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Voting/ElectoralConfiguration.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>

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
using namespace std;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* ChangeLanguageFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality",GETTEXT_PACKAGE);

ChangeLanguageFunctionality* ChangeLanguageFunctionality::current_instance = NULL;
ChangeLanguageFunctionality* ChangeLanguageFunctionality::Current()
{
	if (!current_instance)
		current_instance = new ChangeLanguageFunctionality();

	return current_instance;
};

ChangeLanguageFunctionality::ChangeLanguageFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	changeLanguageWidget = NULL;
}

void ChangeLanguageFunctionality::deleteElement()
{
	if (changeLanguageWidget)
	{
		delete changeLanguageWidget;
		changeLanguageWidget = NULL;
	}
}

void ChangeLanguageFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality.LanguageNotChanged"));
	enableExitButton();
}

Gtk::Widget* ChangeLanguageFunctionality::GetFrame()
{	
	changeLanguageWidget = new ChangeLanguageWidget();
	changeLanguageWidget->init(MachineOperationManager::getInstance()->getSaesDirectories());
	changeLanguageWidget->SetShowMessage(true);
	changeLanguageWidget->LanguageChanged().connect(sigc::mem_fun(this, &ChangeLanguageFunctionality::OnLanguageChange));

	Smartmatic::SAES::Voting::ElectoralConfiguration * elecConfig =
			Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration();

	list<Smartmatic::SAES::Voting::Election::Language> listLang;

	if(elecConfig != NULL)
	{
	    listLang = elecConfig->getLanguageList();
	}
	else
	{
		listLang = Smartmatic::SAES::Voting::Election::ElectionInstalationLanguages::getInstance()->getLanguages();
	}


	Smartmatic::SAES::Functionality::Configuration::AppType apptoLaunch=
			Smartmatic::SAES::Functionality::Configuration::SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getAppType();

	if(apptoLaunch == Smartmatic::SAES::Functionality::Configuration::AppType::CONFIGURATION_VOTINGONLY)
	{
		changeLanguageWidget->SetSaveFile(false);
	}

	changeLanguageWidget->initialize(listLang,true);//False to save the file in both memories
	changeLanguageWidget->set_visible(true);	
	
	this->changeLanguageWidget->SetSaveFile(true);
	return changeLanguageWidget;
}

string ChangeLanguageFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality.Title");
}

MenuOptionDescriptor ChangeLanguageFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MChangeLanguageFunctionality,false);
}

void ChangeLanguageFunctionality::Dispose()
{

}

void ChangeLanguageFunctionality::OnLanguageChange()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality.LanguageChanged"));
	RefreshInfo();
	ExitFunctionality();
}

ChangeLanguageFunctionality::~ChangeLanguageFunctionality()
{
	deleteElement();
};

Smartmatic::Log::ISMTTLog* ChangeLanguageFunctionality::getLogger()
{
	return logger;
}

Glib::ustring ChangeLanguageFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality.LogStartFunctionality");
}

Glib::ustring ChangeLanguageFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ChangeLanguageFunctionality.LogCloseFunctionality");
}
