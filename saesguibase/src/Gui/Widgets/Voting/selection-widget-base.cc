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

#include "selection-widget-base.h"
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

using namespace Gtk;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;

SelectionWidgetBase::SelectionWidgetBase()
{
	static int desiredWidth = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowWith();
	static int desiredHeight = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowHeight();
	
	int formheight ((*Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getHeight());
	int formwidth ((*Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getConfiguration())->getBasicWindowConfiguration().getWidth());

	int horizontalPadding = (formwidth - desiredWidth) / 2;
	int verticalPadding = (formheight - desiredHeight) / 2;

	mainContainer.set_border_width(0);

	clientAreaAlignment = manage(new Gtk::Alignment());
	clientAreaAlignment->set_padding(verticalPadding, verticalPadding, horizontalPadding, horizontalPadding);
	clientAreaAlignment->set(0.0,0.0,1);
	clientAreaAlignment->show();
	clientAreaAlignment->add(mainContainer);

	setTitle(false);
	setShowBorder(true);
	setWidget(clientAreaAlignment);
}

SelectionWidgetBase::~SelectionWidgetBase()
{
	
}
