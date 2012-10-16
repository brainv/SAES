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

#include "select-language-widget.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <queue>

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
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;

void SelectLanguageWidget::Initialize()
{

	framePrincipal = NULL;
	vector<LanguageButtonInfo> listOfLanguages = SAESGUIConfigurationManager::Current()->getLanguageList();
	//int cantIdiomas = listOfLanguages.size();





	//buttonOk->signal_clicked().connect(sigc::mem_fun(this, &SelectLanguageWidget::on_buttonOk_clicked));
	//buttonCalibrate->signal_clicked().connect(sigc::mem_fun(this, &SelectLanguageWidget::on_buttonCalibrate_clicked));

};



void SelectLanguageWidget::Dispose()
{

};

