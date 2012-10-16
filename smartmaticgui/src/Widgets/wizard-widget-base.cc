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

#include "wizard-widget-base.h"
#include <iostream>

using namespace Smartmatic::GUI::Widgets;

WizardWidgetBase::WizardWidgetBase()
: StepWidget()
{

}

WizardWidgetBase::~WizardWidgetBase()
{

}

WizardWidgetBase::type_done_signal WizardWidgetBase::on_done_signal_emit()
{
	return m_done_signal;
}

WizardWidgetBase::type_done_signal WizardWidgetBase::on_stop_signal_emit()
{
	return m_stop_signal;
}

WizardWidgetBase::type_done_signal WizardWidgetBase::on_disable_close_signal_emit()
{
	return m_disable_close_signal;
}

bool WizardWidgetBase::StopWizard()
{
	return false;
}

bool WizardWidgetBase::isEnabledButtonExitWizard()
{
	return true;
}
