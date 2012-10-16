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

#include "language-selection-window.h"
#include "Environment/Configurations/base-language-controller.h"
#include "Voting/Election/election-language-schema.hxx"
#include <Operation/MachineOperationManager.hxx>
#include "System/IO/File.h"
#include <gtkmm.h>

using namespace std;
using namespace Gtk;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Operation;

LanguageSelectionWindow::LanguageSelectionWindow()
: EmptyWindow(NULL, "",false,false,false)
{	
	this->changeLanguageWidget = manage(new Smartmatic::SAES::GUI::Widgets::ChangeLanguageWidget());
	this->changeLanguageWidget->init(MachineOperationManager::getInstance()->getSaesDirectories());
}

LanguageSelectionWindow::~LanguageSelectionWindow()
{
	
}

bool LanguageSelectionWindow::loadDefaultLanguage()
{
	return changeLanguageWidget->loadDefaultLanguage();
}

void LanguageSelectionWindow::setSaveFile(bool saveFile)
{
	changeLanguageWidget->SetSaveFile(saveFile);
}

void LanguageSelectionWindow::initialize()
{
	this->changeLanguageWidget->LanguageChanged().connect(sigc::mem_fun(this, &LanguageSelectionWindow::OncloseWindow));

    list<Smartmatic::SAES::Voting::Election::Language> listLang = ElectionInstalationLanguages::getInstance()->getLanguages();

	changeLanguageWidget->initialize(listLang, false);
	
	getClientAreaFrame().set_shadow_type(SHADOW_NONE);
	setWidget(changeLanguageWidget);

	show_all_children ();
}

void LanguageSelectionWindow::OncloseWindow()
{
	exit_slot = sigc::bind(sigc::mem_fun(*this, &LanguageSelectionWindow::on_exit_language_selection_window), 0);
	exit_connector = Glib::signal_timeout().connect(exit_slot, 20);		
};

bool LanguageSelectionWindow::on_exit_language_selection_window(int timer_number)
{		
	QuitDialog();
	return false;
};
