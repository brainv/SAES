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

#include "assisted-activation-id-card-widget-view.h"
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "Environment/Configurations/resource-path-provider.h"
#include <Log/ISMTTLog.h>
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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* AssistedActivationIDCardWidgetView::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetView",GETTEXT_PACKAGE);

AssistedActivationIDCardWidgetView::AssistedActivationIDCardWidgetView(std::string title, std::string firstNameValue, std::string surNameValue/*,std::string genderValue,
                                                                       std::string nationalityValue, std::string natNumberValue*/)
{
	set_size_request (-1,60);
	set_shadow_type(Gtk::SHADOW_IN);
	//set_border_width (5);
	add(event);	
	event.add(vboxEvents);
	event.show_all_children ();
	event.set_visible(true);
	eventTitle.add(labelTitle);
	eventTitle.set_name("");
	eventTitle.show_all_children ();
	
	Gdk::Color selectedColorTitle;
	Gdk::Color selectedColorPrincipal;
	ColorConfiguration colorConfTitle = SAESGUIConfigurationManager::Current()->getAssistedActivationPreviewTitleColor();
	ColorConfiguration colorConfContent = SAESGUIConfigurationManager::Current()->getAssistedActivationPreviewContentColor();
	selectedColorTitle.set_rgb(colorConfTitle.getRed(), colorConfTitle.getGreen(), colorConfTitle.getBlue());
	selectedColorPrincipal.set_rgb(colorConfContent.getRed(), colorConfContent.getGreen(), colorConfContent.getBlue());
	eventTitle.modify_bg(Gtk::STATE_NORMAL, selectedColorTitle);
	event.modify_bg(Gtk::STATE_NORMAL, selectedColorPrincipal);
	
	vboxEvents.pack_start (eventTitle,Gtk::PACK_EXPAND_WIDGET);

	std::string firstName = _("Smartmatic.SAES.GUI.Widgets.IDCardWidget.FirstName");
	std::string surName = _("Smartmatic.SAES.GUI.Widgets.IDCardWidget.SurName");

	hboxRowFirstName.pack_start (firstNameLabel,Gtk::PACK_EXPAND_WIDGET); 
	hboxRowSurName.pack_start (surNameLabel,Gtk::PACK_EXPAND_WIDGET);   

	hboxRowFirstName.pack_start (firstNameValueLabel,Gtk::PACK_EXPAND_WIDGET); 
	hboxRowSurName.pack_start (surNameValueLabel,Gtk::PACK_EXPAND_WIDGET);   
	
	hboxRowFirstName.show_all_children (); 
	hboxRowSurName.show_all_children ();  

	vboxEvents.pack_start (hboxRowFirstName,Gtk::PACK_SHRINK);
	vboxEvents.pack_start (hboxRowSurName,Gtk::PACK_SHRINK);

	labelTitle.set_label(title);
	firstNameLabel.set_label(firstName);
	firstNameLabel.set_alignment(0.0, 0.5);//TODO configuration
	firstNameLabel.set_padding(10, 0);
	firstNameLabel.set_size_request(150, -1);
	
	surNameLabel.set_alignment(0.0, 0.5);//TODO configuration
	surNameLabel.set_padding(10, 0);
	surNameLabel.set_size_request(150, -1);
	surNameLabel.set_label(surName); 

	firstNameValueLabel.set_label(firstNameValue); 
	firstNameValueLabel.set_alignment(0.0, 0.5);//TODO configuration
	firstNameValueLabel.set_padding(10, 0);
	firstNameValueLabel.set_size_request(150, -1);
	
	surNameValueLabel.set_label(surNameValue);  
	surNameValueLabel.set_alignment(0.0, 0.5);//TODO configuration
	surNameValueLabel.set_padding(10, 0);
	surNameValueLabel.set_size_request(150, -1);

}

AssistedActivationIDCardWidgetView::~AssistedActivationIDCardWidgetView()
{

}

void AssistedActivationIDCardWidgetView::init()
{
	
}

void AssistedActivationIDCardWidgetView::dispose()
{

}
