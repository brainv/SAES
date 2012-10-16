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

#include "basic-diagnostic-widget.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <Operation/MachineOperationManager.hxx>
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

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

using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Gtk;

BasicDiagnosticWidget::BasicDiagnosticWidget(std::string Title, OperationStatus::Diagnostic diagnostic, bool showOk, bool showCancel, bool showMessage,bool showButtons):hboxButton(Gtk::BUTTONBOX_CENTER,10)
{
	if(Title.compare("")!=0)
	{
		Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
		fontTitle.set_size(12*Pango::SCALE);
		labelTitle.modify_font(fontTitle);	
		labelTitle.set_label (Title);
		labelTitle.set_size_request (-1,50);	
		vboxPrincipal.add(labelTitle);
	}
	
	okButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.BasicDiagnosticWidget.Ok"));
	okButton.WidgetsPosition (5,0,0);
	okButton.signal_clicked().connect( sigc::mem_fun(this, &BasicDiagnosticWidget::on_buttonOk_clicked));
	okButton.set_size_request (100,50);	
	okButton.SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	if(showOk)
	{	
		okButton.set_sensitive(true);		
	}
	else
	{
		okButton.set_sensitive(false);		
	}

	cancelButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.BasicDiagnosticWidget.Cancel"));
	cancelButton.WidgetsPosition (5,0,0);
	cancelButton.signal_clicked().connect( sigc::mem_fun(this, &BasicDiagnosticWidget::on_buttonCancel_clicked));
	cancelButton.set_size_request (100,50);
	cancelButton.SetSound(Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDiagnosisSound());
	if(showCancel)
	{
		cancelButton.set_sensitive(true);
	}
	else
	{
		cancelButton.set_sensitive(false);		
	}


	hboxButton.add(cancelButton);
	hboxButton.add(okButton);
	vboxPrincipal.add(frameDiagnostic);
	if(showMessage)
	{
		vboxPrincipal.add(labelMessage);	
	}
	if(showButtons)
	{
		vboxPrincipal.add(hboxButton);
	}

	frameDiagnostic.set_shadow_type(Gtk::SHADOW_NONE);
	this->set_shadow_type(Gtk::SHADOW_NONE);
	this->add(vboxPrincipal);
	this->show_all_children ();
	this->set_visible (true);
}

void BasicDiagnosticWidget::setOkButtonSensitive(bool sensitive)
{
	okButton.set_sensitive(sensitive);	
}

void BasicDiagnosticWidget::setCancelButtonSensitive(bool sensitive)
{
	cancelButton.set_sensitive (sensitive);
}

void BasicDiagnosticWidget::setOkButtonLabel(std::string label)
{
	okButton.SetLabel(label);
}

void BasicDiagnosticWidget::setCancelButtonLabel(std::string label)
{
	cancelButton.SetLabel(label);
}

void BasicDiagnosticWidget::setDiagnosticFrame(Gtk::Widget& widget)
{
	frameDiagnostic.remove();
	frameDiagnostic.add(widget);
}

void BasicDiagnosticWidget::on_buttonOk_clicked()
{
	setCancelButtonSensitive(false);
	setOkButtonSensitive (false);
	signalOk_detected.emit();
}

void BasicDiagnosticWidget::on_buttonCancel_clicked()
{
	setCancelButtonSensitive(false);
	setOkButtonSensitive (false);
	signalCancel_detected.emit();
}



