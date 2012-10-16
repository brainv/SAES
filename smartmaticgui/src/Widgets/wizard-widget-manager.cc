/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "wizard-widget-manager.h"
#include <iostream>

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

WizardWidgetManager::WizardWidgetManager(vector<WizardWidgetBase*> widgetsVector)
{
	set_shadow_type(Gtk::SHADOW_NONE);
	this->widgetsVector = widgetsVector;
	iter = this->widgetsVector.begin();
}

WizardWidgetManager::~WizardWidgetManager()
{
	widgetConnect.disconnect();
}

void WizardWidgetManager::InitializeWidget()
{

	
}

void WizardWidgetManager::ShowWidget()
{
	if(*iter)
	{
		widgetConnect = (*iter)->on_done_signal_emit().connect(sigc::mem_fun(this,&WizardWidgetManager::NextWidget));
		(*iter)->initialize();
		remove();
		add(*(*iter));
		show_all_children();
	}
}

void WizardWidgetManager::NextWidget()
{
	widgetConnect.disconnect();
	(*iter)->dispose();
	m_transition_signal.emit();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &WizardWidgetManager::NextWidgetInternal), 100);
}

void WizardWidgetManager::NextWidgetInternal()
{
	if(!(*iter)->StopWizard())
	{
		iter++;
		if(iter != this->widgetsVector.end())
			ShowWidget();
		else
			m_finish_signal.emit();
	}
	else
		m_finish_signal.emit();
}
												 

WizardWidgetManager::type_void_signal WizardWidgetManager::on_finish_signal_emit()
{
	return m_finish_signal;
}

WizardWidgetManager::type_void_signal WizardWidgetManager::on_transition_signal_emit()
{
	return m_transition_signal;
}

void WizardWidgetManager::Start()
{
	this->iter = this->widgetsVector.begin();
	ShowWidget();
}

WizardWidgetBase * WizardWidgetManager::getCurrentWidget()
{
	return (*iter);
}
