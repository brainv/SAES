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

#include "menu-window.h"

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;

using namespace Smartmatic::SAES::GUI::Windows;

MenuWindow::MenuWindow()
:EmptyWindow(NULL,N_("Smartmatic.SAES.GUI.Windows.MenuWindow.Title"),true, false, false)
{
	menu = new MenuWidget();
	menu->setExit(false);
	pushStepWidget(menu);
}

MenuWindow::~MenuWindow()
{
	remove();

	if(menu)
	{
		delete menu;
		menu = NULL;
	}

	EmptyWindow::dispose();
}
