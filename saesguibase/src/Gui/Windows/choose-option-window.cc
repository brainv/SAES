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

#include "choose-option-window.h"

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

using namespace Gtk;
using namespace std;
using namespace Smartmatic::SAES::GUI::Windows;

ChooseOptionWindow::ChooseOptionWindow(Smartmatic::GUI::Widgets::ChooseDialogInfo *info)
: EmptyWindow(NULL,N_("Smartmatic.SAES.GUI.Windows.ChooseOptionWindow.Title"),false,false,false)
{
	this->info = info;
	setKeywordNavigation(this);
	
	framePrincipal.set((float)0.5,(float)0.5,(float)0.8,(float)0.3);

	frameContainer = manage(new Frame());
	dialogWidget = new Smartmatic::GUI::Widgets::ChooseDialogWidget(info);
	frameContainer->add(*dialogWidget);
	frameContainer->set_border_width(10);
	frameContainer->set_shadow_type(SHADOW_OUT);
	framePrincipal.add(*frameContainer);
	framePrincipal.show_all_children ();
	framePrincipal.set_visible (true);
	setWidget(&framePrincipal);
	dialogWidget->signal_detected.connect(sigc::mem_fun(*this,&ChooseOptionWindow::onOptionButton));
};

ChooseOptionWindow::ChooseOptionWindow(Smartmatic::GUI::Widgets::ChooseDialogInfo *info, bool showCancel)
: EmptyWindow(NULL,N_("Smartmatic.SAES.GUI.Windows.ChooseOptionWindow.Title"),false,false,false)
{
	this->info = info;
	setKeywordNavigation(this);
	
	framePrincipal.set((float)0.5,(float)0.5,(float)0.8,(float)0.3);

	frameContainer = manage(new Frame());
	dialogWidget = new Smartmatic::GUI::Widgets::ChooseDialogWidget(info, showCancel);
	frameContainer->add(*dialogWidget);
	frameContainer->set_border_width(10);
	frameContainer->set_shadow_type(SHADOW_OUT);
	framePrincipal.add(*frameContainer);
	framePrincipal.show_all_children ();
	framePrincipal.set_visible (true);
	setWidget(&framePrincipal);
	dialogWidget->signal_detected.connect(sigc::mem_fun(*this,&ChooseOptionWindow::onOptionButton));
};

ChooseOptionWindow::~ChooseOptionWindow()
{
	remove();

	if(dialogWidget)
	{
		delete(dialogWidget);
		dialogWidget = NULL;
	}
}

void ChooseOptionWindow::onOptionButton(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* info)
{
	if(info!=NULL)
	{
		signal_detected.emit(info);
		infoSelected = info;
		QuitDialog();
	}
}

Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* ChooseOptionWindow::GetOptionSelected()
{
	return infoSelected;
}

void ChooseOptionWindow::SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value)
{
	
}
