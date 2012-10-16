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

#include "Gui/Widgets/assisted-activation-id-card-widget-viewer.h"
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
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* AssistedActivationIDCardWidgetViewer::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer",GETTEXT_PACKAGE);

AssistedActivationIDCardWidgetViewer::AssistedActivationIDCardWidgetViewer(Smartmatic::SAES::Voting::PBReports::Activation activation)
{
	pollworkerViewWidget= NULL;
	voterViewWidget= NULL;
	propossedPersonViewWidget= NULL;
	impugnatedPersonViewWidget= NULL;
	dessignatedPersonViewWidget= NULL;

	eventTypeOfActivation.add(labelTypeOfActivation);
	Gdk::Color selectedColorTypeOfActivation;
	ColorConfiguration colorConfTitle = SAESGUIConfigurationManager::Current()->getAssistedActivationPreviewTitleColor();
	selectedColorTypeOfActivation.set_rgb(colorConfTitle.getRed(), colorConfTitle.getGreen(), colorConfTitle.getBlue());
	eventTypeOfActivation.modify_bg(Gtk::STATE_NORMAL, selectedColorTypeOfActivation);
	eventTypeOfActivation.show_all_children ();
	eventTypeOfActivation.set_size_request(-1, 30);

	Pango::FontDescription fontTitle = labelTypeOfActivation.get_style()->get_font();
	fontTitle.set_size(11*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelTypeOfActivation.modify_font(fontTitle);	
	switch(activation.getActivationMode())
	{
		case ActivationMode::ASSISTED_ACTIVATION_PROXY:
			labelTypeOfActivation.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ProxyActivation"));
			break;
		case ActivationMode:: ASSISTED_ACTIVATION_PRESENTIAL:
			labelTypeOfActivation.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.PresentialActivation"));
			break;
	}
	
	IDCardInfo pollworker = activation.getPollworker();
	IDCardInfo voter = activation.getVoter();
	IDCardInfo propossedPerson = activation.getPropossedPerson();

	pollworkerViewWidget = new AssistedActivationIDCardWidgetView(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Pollworker"), pollworker.getFirstName(), pollworker.getSurname()/*,pollworker.getGender().get(),
                                                                       pollworker.getNationality().get(), pollworker.getNationalNumber().get()*/);
	voterViewWidget= new AssistedActivationIDCardWidgetView(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Voter"), voter.getFirstName(), voter.getSurname()/*,voter.getGender().get(),
                                                                       voter.getNationality().get(), voter.getNationalNumber().get()*/);
	propossedPersonViewWidget= new AssistedActivationIDCardWidgetView(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.PropossedPerson"), propossedPerson.getFirstName(), propossedPerson.getSurname()/*,propossedPerson.getGender().get(),
                                                                       propossedPerson.getNationality().get(), propossedPerson.getNationalNumber().get()*/);

	pack_start (eventTypeOfActivation,Gtk::PACK_SHRINK);
	
	pack_start (*pollworkerViewWidget,Gtk::PACK_SHRINK);
	pack_start (*voterViewWidget,Gtk::PACK_SHRINK);
	pack_start (*propossedPersonViewWidget,Gtk::PACK_SHRINK);

	if(activation.getWasImpugned())
	{
		labelImpugnation.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ActivationImpugnated"));
		labelImpugnation.modify_font(fontTitle);	
		eventImpugnation.add(labelImpugnation);
		Gdk::Color selectedColorImpugnation;
		selectedColorImpugnation.set_rgb(colorConfTitle.getRed(), colorConfTitle.getGreen(), colorConfTitle.getBlue());
		eventImpugnation.modify_bg(Gtk::STATE_NORMAL, selectedColorImpugnation);
		eventImpugnation.show_all_children ();
		eventImpugnation.set_size_request(-1, 30);
		
		IDCardInfo impugnator = activation.getImpugnator().get();
		IDCardInfo designatedPerson = activation.getDesignatedPerson().get();
		std::string reason = activation.getImpugnationReason().get();
		impugnatedPersonViewWidget= new AssistedActivationIDCardWidgetView(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.Impugnator"), impugnator.getFirstName(), impugnator.getSurname()/*,impugnator.getGender().get(),
                                                                       impugnator.getNationality().get(), impugnator.getNationalNumber().get()*/);
		dessignatedPersonViewWidget= new AssistedActivationIDCardWidgetView(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.DesignatedPerson"), designatedPerson.getFirstName(), designatedPerson.getSurname()/*,designatedPerson.getGender().get(),
                                                                       designatedPerson.getNationality().get(), designatedPerson.getNationalNumber().get()*/);
		frameReason.add(vboxReason);
		frameReason.show_all_children ();
		frameReason.set_visible(true);
		vboxReason.pack_start (eventReasonTitle,Gtk::PACK_SHRINK);
		vboxReason.pack_start (scrollReasonContent,Gtk::PACK_SHRINK);
		vboxReason.show_all_children ();
		vboxReason.set_visible(true);
		labelReasonTitle.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationIDCardWidgetViewer.ReasonTitle"));
		eventReasonTitle.add(labelReasonTitle);
		Gdk::Color selectedColorReasonTitle;
		scrollReasonContent.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		scrollReasonContent.add(labelReasonContent);
		scrollReasonContent.show_all_children ();
		scrollReasonContent.set_visible(true);
		labelReasonContent.set_label(reason);
		selectedColorReasonTitle.set_rgb(colorConfTitle.getRed(), colorConfTitle.getGreen(), colorConfTitle.getBlue());
		eventReasonTitle.modify_bg(Gtk::STATE_NORMAL, selectedColorReasonTitle);
		eventReasonTitle.show_all_children ();
		eventReasonTitle.set_visible(true);

		labelReasonContent.set_size_request (290,-1);
		labelReasonContent.set_line_wrap();
		labelReasonContent.set_justify(Gtk::JUSTIFY_FILL);
		scrollReasonContent.set_size_request (300,80);
		frameReason.set_size_request (300,60);

		pack_start (eventImpugnation,Gtk::PACK_SHRINK);

		pack_start (*impugnatedPersonViewWidget,Gtk::PACK_SHRINK);
		pack_start (*dessignatedPersonViewWidget,Gtk::PACK_SHRINK);
		pack_start(frameReason,Gtk::PACK_EXPAND_WIDGET);
		
		//pack_start (vboxButtonImpugnation,Gtk::PACK_EXPAND_WIDGET);
	}

	show_all_children ();
	set_visible (true);
	set_spacing(2);
}

AssistedActivationIDCardWidgetViewer::~AssistedActivationIDCardWidgetViewer()
{
	if(pollworkerViewWidget)
	{
		delete(pollworkerViewWidget);
		pollworkerViewWidget= NULL;
	}
	if(voterViewWidget)
	{
		delete(voterViewWidget);
		voterViewWidget= NULL;
	}
	if(propossedPersonViewWidget)
	{
		delete(propossedPersonViewWidget);
		propossedPersonViewWidget= NULL;
	}
	if(impugnatedPersonViewWidget)
	{
		delete(impugnatedPersonViewWidget);
		impugnatedPersonViewWidget= NULL;
	}
	if(dessignatedPersonViewWidget)
	{
		delete(dessignatedPersonViewWidget);
		dessignatedPersonViewWidget= NULL;
	}
	
}

void AssistedActivationIDCardWidgetViewer::init()
{
	
}

void AssistedActivationIDCardWidgetViewer::dispose()
{

}
