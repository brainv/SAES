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

#include "custom-attributes-counter-widget.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Voting/PBReports/activated-card-statistics-schema.hxx>
#include "Resources/election-string-resources-manager.h"

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
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Resources;

CustomAttributesCounterWidget::CustomAttributesCounterWidget(std::string labelTitleKey,std::string imagePath,
                                                             Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration conf,
                                                             Smartmatic::SAES::Configuration::ColorConfiguration colorTitleConf,
                                                             Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConf)
{
	widgetToDelete = NULL;
	this->conf = conf;
	labelTitle.set_label(labelTitleKey);
	/*
	labelTitle.set_alignment(0.0, 0.5);//TODO configuration
	labelTitle.set_padding(5, 0);
	*/
	fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_size(10*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	//labelTitle.modify_font(fontTitle);
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(&labelTitle, labelTitleConf);
	//labelTitle.set_size_request(300, 50);
	set_size_request(400, -1);
	imageTitle.set(imagePath);
	//imageTitle.set_size_request(80, 50);
	if(imagePath.compare("")!=0)
	{
		hboxHeader.pack_start (imageTitle,Gtk::PACK_SHRINK);
	}
	eventBoxTitle.add(labelTitle);
	eventBoxTitle.set_name(SAESGUIConfigurationManager::Current()->GetCustomAttributeCounterWidgetTitleName());
	selectedColor.set_rgb(colorTitleConf.getRed(), colorTitleConf.getGreen(), colorTitleConf.getBlue());
	eventBoxTitle.modify_bg(Gtk::STATE_NORMAL, selectedColor);
	
	
	
	
	hboxHeader.pack_start (eventBoxTitle,Gtk::PACK_EXPAND_WIDGET);
	vboxPrincipal.pack_start(hboxHeader,Gtk::PACK_SHRINK);
	//viewCounter.add(vboxPrincipal);
	scrolledCounter.set_policy (POLICY_AUTOMATIC, POLICY_AUTOMATIC);
	scrolledCounter.add(vboxPrincipal);
	add(scrolledCounter);
	scrolledCounter.show_all_children ();
	scrolledCounter.set_visible (true);

	vboxPrincipal.pack_start(hboxTotalActivated,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start(separator0,Gtk::PACK_SHRINK);
	if(!conf.getHideOfficial())
	{
		vboxPrincipal.pack_start(hboxTotalOfficialActivated,Gtk::PACK_SHRINK); 
		vboxPrincipal.pack_start(separator1,Gtk::PACK_SHRINK);
	}
	if(!conf.getHideDemo())
	{
		vboxPrincipal.pack_start(hboxTotalDemoActivated,Gtk::PACK_SHRINK); 
		vboxPrincipal.pack_start(separator2,Gtk::PACK_SHRINK);
	}
	if(!conf.getHideRecovery())
	{
		vboxPrincipal.pack_start(hboxTotalRecoveryActivated,Gtk::PACK_SHRINK);
		vboxPrincipal.pack_start(separator3,Gtk::PACK_SHRINK);
	}
	
	if(!conf.getHideAudio())
	{
		vboxPrincipal.pack_start(hboxTotalAudioActivated,Gtk::PACK_SHRINK); 
		vboxPrincipal.pack_start(separator4,Gtk::PACK_SHRINK);
		if(!conf.getHideOfficial())
		{
			vboxPrincipal.pack_start(hboxTotalAudioOfficialActivated,Gtk::PACK_SHRINK);
			vboxPrincipal.pack_start(separator5,Gtk::PACK_SHRINK);
		}
		if(!conf.getHideDemo())
		{
			vboxPrincipal.pack_start(hboxTotalAudioDemoActivated,Gtk::PACK_SHRINK);  
			vboxPrincipal.pack_start(separator6,Gtk::PACK_SHRINK);
		}
		if(!conf.getHideRecovery())
		{
			vboxPrincipal.pack_start(hboxTotalAudioRecoveryActivated,Gtk::PACK_SHRINK);
			vboxPrincipal.pack_start(separator7,Gtk::PACK_SHRINK);
		}
	}
	if(!conf.getHideNonAudio())
	{
		vboxPrincipal.pack_start(hboxTotalNonAudioActivated,Gtk::PACK_SHRINK);
		vboxPrincipal.pack_start(separator8,Gtk::PACK_SHRINK);
		if(!conf.getHideOfficial())
		{
			vboxPrincipal.pack_start(hboxTotalNonAudioOfficialActivated,Gtk::PACK_SHRINK); 
			vboxPrincipal.pack_start(separator9,Gtk::PACK_SHRINK);
		}
		if(!conf.getHideDemo())
		{
			vboxPrincipal.pack_start(hboxTotalNonAudioDemoActivated,Gtk::PACK_SHRINK); 
			vboxPrincipal.pack_start(separator10,Gtk::PACK_SHRINK);
		}
		if(!conf.getHideRecovery())
		{
			vboxPrincipal.pack_start(hboxTotalNonAudioRecoveryActivated,Gtk::PACK_SHRINK); 
			vboxPrincipal.pack_start(separator11,Gtk::PACK_SHRINK);
		}
	}
	  
	
	vboxPrincipal.set_spacing(10);

	labelTotalActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalActivated"));
	labelTotalNonAudioActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalNonAudioActivated"));
	labelTotalAudioActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalAudioActivated"));
	labelTotalOfficialActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalOfficialActivated"));
	labelTotalDemoActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalDemoActivated"));
	labelTotalRecoveryActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalRecoveryActivated"));
	labelTotalAudioOfficialActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalAudioOfficialActivated"));
	labelTotalAudioDemoActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalAudioDemoActivated"));
	labelTotalAudioRecoveryActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalAudioRecoveryActivated"));
	labelTotalNonAudioOfficialActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalNonAudioOfficialActivated"));
	labelTotalNonAudioDemoActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalNonAudioDemoActivated"));
	labelTotalNonAudioRecoveryActivated.set_label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.TotalNonAudioRecoveryActivated"));

	labelTotalActivated.modify_font(fontTitle);	
	labelTotalNonAudioActivated.modify_font(fontTitle);	
	labelTotalAudioActivated.modify_font(fontTitle);	
	labelTotalOfficialActivated.modify_font(fontTitle);	
	labelTotalDemoActivated.modify_font(fontTitle);	
	labelTotalRecoveryActivated.modify_font(fontTitle);	
	labelTotalAudioOfficialActivated.modify_font(fontTitle);	
	labelTotalAudioDemoActivated.modify_font(fontTitle);	
	labelTotalAudioRecoveryActivated.modify_font(fontTitle);	
	labelTotalNonAudioOfficialActivated.modify_font(fontTitle);	
	labelTotalNonAudioDemoActivated.modify_font(fontTitle);	
	labelTotalNonAudioRecoveryActivated.modify_font(fontTitle);	
	
	hboxTotalActivated.pack_start(labelTotalActivated,Gtk::PACK_SHRINK); 
	hboxTotalActivated.pack_start(labelTotalActivatedCounter,Gtk::PACK_SHRINK);   
	hboxTotalActivated.set_spacing(3);
	
	hboxTotalNonAudioActivated.pack_start(labelTotalNonAudioActivated,Gtk::PACK_SHRINK);  
	hboxTotalNonAudioActivated.pack_start(labelTotalNonAudioActivatedCounter,Gtk::PACK_SHRINK);  
	hboxTotalNonAudioActivated.set_spacing(3);
				
	hboxTotalAudioActivated.pack_start(labelTotalAudioActivated,Gtk::PACK_SHRINK);  
	hboxTotalAudioActivated.pack_start(labelTotalAudioActivatedCounter,Gtk::PACK_SHRINK);  
	hboxTotalAudioActivated.set_spacing(3);
				
	hboxTotalOfficialActivated.pack_start(labelTotalOfficialActivated,Gtk::PACK_SHRINK);  
	hboxTotalOfficialActivated.pack_start(labelTotalOfficialActivatedCounter,Gtk::PACK_SHRINK);  
	hboxTotalOfficialActivated.set_spacing(3);
				
	hboxTotalDemoActivated.pack_start(labelTotalDemoActivated,Gtk::PACK_SHRINK);  
	hboxTotalDemoActivated.pack_start(labelTotalDemoActivatedCounter,Gtk::PACK_SHRINK);
	hboxTotalDemoActivated.set_spacing(3);
				
	hboxTotalRecoveryActivated.pack_start(labelTotalRecoveryActivated,Gtk::PACK_SHRINK);
	hboxTotalRecoveryActivated.pack_start(labelTotalRecoveryActivatedCounter,Gtk::PACK_SHRINK);
	hboxTotalRecoveryActivated.set_spacing(3);
				
	hboxTotalAudioOfficialActivated.pack_start(labelTotalAudioOfficialActivated,Gtk::PACK_SHRINK); 
	hboxTotalAudioOfficialActivated.pack_start(labelTotalAudioOfficialActivatedCounter,Gtk::PACK_SHRINK);
	hboxTotalAudioOfficialActivated.set_spacing(3);
				
	hboxTotalAudioDemoActivated.pack_start(labelTotalAudioDemoActivated,Gtk::PACK_SHRINK);  
	hboxTotalAudioDemoActivated.pack_start(labelTotalAudioDemoActivatedCounter,Gtk::PACK_SHRINK);  
	hboxTotalAudioDemoActivated.set_spacing(3);
				
	hboxTotalAudioRecoveryActivated.pack_start(labelTotalAudioRecoveryActivated,Gtk::PACK_SHRINK);  
	hboxTotalAudioRecoveryActivated.pack_start(labelTotalAudioRecoveryActivatedCounter,Gtk::PACK_SHRINK); 
	hboxTotalAudioRecoveryActivated.set_spacing(3);
				
	hboxTotalNonAudioOfficialActivated.pack_start(labelTotalNonAudioOfficialActivated,Gtk::PACK_SHRINK); 
	hboxTotalNonAudioOfficialActivated.pack_start(labelTotalNonAudioOfficialActivatedCounter,Gtk::PACK_SHRINK);
	hboxTotalNonAudioOfficialActivated.set_spacing(3);
				
	hboxTotalNonAudioDemoActivated.pack_start(labelTotalNonAudioDemoActivated,Gtk::PACK_SHRINK);  
	hboxTotalNonAudioDemoActivated.pack_start(labelTotalNonAudioDemoActivatedCounter,Gtk::PACK_SHRINK); 
	hboxTotalNonAudioDemoActivated.set_spacing(3);
				
	hboxTotalNonAudioRecoveryActivated.pack_start(labelTotalNonAudioRecoveryActivated,Gtk::PACK_SHRINK);
	hboxTotalNonAudioRecoveryActivated.pack_start(labelTotalNonAudioRecoveryActivatedCounter,Gtk::PACK_SHRINK);
	hboxTotalNonAudioRecoveryActivated.set_spacing(3);

	
	vboxPrincipal.show_all_children ();
	vboxPrincipal.set_visible (true);

	setCounters();
	show_all_children ();
	set_visible(true);
	set_shadow_type(SHADOW_NONE);
}


void CustomAttributesCounterWidget::setCounters()
{
	//Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	//fontTitle.set_size(10*Pango::SCALE);
	//fontTitle.set_weight(Pango::WEIGHT_BOLD);
	
	
	std::stringstream  messageTotalActivated;
	std::stringstream  messageTotalNonAudioActivated;
	std::stringstream  messageTotalAudioActivated;
	std::stringstream  messageTotalOfficialActivated;
	std::stringstream  messageTotalDemoActivated;
	std::stringstream  messageTotalRecoveryActivated;
	std::stringstream  messageTotalAudioOfficialActivated;
	std::stringstream  messageTotalAudioDemoActivated;
	std::stringstream  messageTotalAudioRecoveryActivated;
	std::stringstream  messageTotalNonAudioOfficialActivated;
	std::stringstream  messageTotalNonAudioDemoActivated;
	std::stringstream  messageTotalNonAudioRecoveryActivated;

	messageTotalActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalActivated();
	messageTotalNonAudioActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioActivated();
	messageTotalAudioActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioActivated();
	messageTotalOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalOfficialActivated();
	messageTotalDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated();
	messageTotalRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalRecoveryActivated();
	messageTotalAudioOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioOfficialActivated();
	messageTotalAudioDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioDemoActivated();
	messageTotalAudioRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioRecoveryActivated();
	messageTotalNonAudioOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioOfficialActivated();
	messageTotalNonAudioDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioDemoActivated();
	messageTotalNonAudioRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioRecoveryActivated();

	labelTotalActivatedCounter.set_label(messageTotalActivated.str());
	labelTotalNonAudioActivatedCounter.set_label(messageTotalNonAudioActivated.str());
	labelTotalAudioActivatedCounter.set_label(messageTotalAudioActivated.str());
	labelTotalOfficialActivatedCounter.set_label(messageTotalOfficialActivated.str());
	labelTotalDemoActivatedCounter.set_label(messageTotalDemoActivated.str());
	labelTotalRecoveryActivatedCounter.set_label(messageTotalRecoveryActivated.str());
	labelTotalAudioOfficialActivatedCounter.set_label(messageTotalAudioOfficialActivated.str());
	labelTotalAudioDemoActivatedCounter.set_label(messageTotalAudioDemoActivated.str());
	labelTotalAudioRecoveryActivatedCounter.set_label(messageTotalAudioRecoveryActivated.str());
	labelTotalNonAudioOfficialActivatedCounter.set_label(messageTotalNonAudioOfficialActivated.str());
	labelTotalNonAudioDemoActivatedCounter.set_label(messageTotalNonAudioDemoActivated.str());
	labelTotalNonAudioRecoveryActivatedCounter.set_label(messageTotalNonAudioRecoveryActivated.str());

	Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * actStatWrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics();
	Smartmatic::SAES::Voting::PBReports::ActivatedCardStatistics * stats = actStatWrapper->getCardStatistics();
	 Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* vd =  Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice();
	if(!conf.getHideCA())
	{
		if(!conf.getHideNonAudio())
		{
			if(!conf.getHideOfficial())
			{
				Gtk::Label* labelOfficNATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.OfficialNonAudioTitle")));
				Gtk::HBox* hboxOfficialNATitle = manage(new Gtk::HBox());
				hboxOfficialNATitle->pack_start(*labelOfficNATitle,Gtk::PACK_SHRINK);
				vboxPrincipal.pack_start(*hboxOfficialNATitle,Gtk::PACK_SHRINK);
				//labelOfficNATitle->set_padding(10, 10);
				labelOfficNATitle->modify_font(fontTitle);	
				titles.push_back(labelOfficNATitle);
				for(unsigned int j=0;j<stats->getActivatedOfficialNonAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }
					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
					
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator0 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator0,Gtk::PACK_SHRINK);
			}

			if(!conf.getHideDemo())
			{
				Gtk::Label* labelDemoNATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.DemoNonAudioTitle")));
				Gtk::HBox* hboxDemoNATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxDemoNATitle,Gtk::PACK_SHRINK);
				hboxDemoNATitle->pack_start(*labelDemoNATitle,Gtk::PACK_SHRINK);
				labelDemoNATitle->set_padding(0, 10);
				labelDemoNATitle->modify_font(fontTitle);	
				titles.push_back(labelDemoNATitle);
				

				for(unsigned int j=0;j< stats->getActivatedDemoNonAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					 Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }
					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}	
				}
				//Gtk::HSeparator* hseparator1 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator1,Gtk::PACK_SHRINK);
			}
		}
		if(!conf.getHideAudio())
		{
			if(!conf.getHideOfficial())
			{
				Gtk::Label* labelOfficATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.OfficialAudioTitle")));
				Gtk::HBox* hboxOfficATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxOfficATitle,Gtk::PACK_SHRINK);
				hboxOfficATitle->pack_start(*labelOfficATitle,Gtk::PACK_SHRINK);
				labelOfficATitle->set_padding(0, 10);
				labelOfficATitle->modify_font(fontTitle);	
				titles.push_back(labelOfficATitle);
				for(unsigned int j=0;j<stats->getActivatedOfficialAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					 Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }

					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
		
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedOfficialAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator2 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator2,Gtk::PACK_SHRINK);
			}

			if(!conf.getHideDemo())
			{
				Gtk::Label* labelDemoATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.DemoAudioTitle")));
				Gtk::HBox* hboxDemoATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxDemoATitle,Gtk::PACK_SHRINK);
				hboxDemoATitle->pack_start(*labelDemoATitle,Gtk::PACK_SHRINK);
				labelDemoATitle->set_padding(0, 10);
				labelDemoATitle->modify_font(fontTitle);
				titles.push_back(labelDemoATitle);
				for(unsigned int j=0;j<stats->getActivatedDemoAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;


					Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }

					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
					
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedDemoAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator3 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator3,Gtk::PACK_SHRINK);
			}
		}
	}
	
}

void CustomAttributesCounterWidget::RefreshCounter()
{
	//Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	//fontTitle.set_size(10*Pango::SCALE);
	//fontTitle.set_weight(Pango::WEIGHT_BOLD);
	
	std::stringstream  messageTotalActivated;
	std::stringstream  messageTotalNonAudioActivated;
	std::stringstream  messageTotalAudioActivated;
	std::stringstream  messageTotalOfficialActivated;
	std::stringstream  messageTotalDemoActivated;
	std::stringstream  messageTotalRecoveryActivated;
	std::stringstream  messageTotalAudioOfficialActivated;
	std::stringstream  messageTotalAudioDemoActivated;
	std::stringstream  messageTotalAudioRecoveryActivated;
	std::stringstream  messageTotalNonAudioOfficialActivated;
	std::stringstream  messageTotalNonAudioDemoActivated;
	std::stringstream  messageTotalNonAudioRecoveryActivated;

	messageTotalActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalActivated();
	messageTotalNonAudioActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioActivated();
	messageTotalAudioActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioActivated();
	messageTotalOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalOfficialActivated();
	messageTotalDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated();
	messageTotalRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalRecoveryActivated();
	messageTotalAudioOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioOfficialActivated();
	messageTotalAudioDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioDemoActivated();
	messageTotalAudioRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalAudioRecoveryActivated();
	messageTotalNonAudioOfficialActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioOfficialActivated();
	messageTotalNonAudioDemoActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioDemoActivated();
	messageTotalNonAudioRecoveryActivated << Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalNonAudioRecoveryActivated();

	labelTotalActivatedCounter.set_label(messageTotalActivated.str());
	labelTotalNonAudioActivatedCounter.set_label(messageTotalNonAudioActivated.str());
	labelTotalAudioActivatedCounter.set_label(messageTotalAudioActivated.str());
	labelTotalOfficialActivatedCounter.set_label(messageTotalOfficialActivated.str());
	labelTotalDemoActivatedCounter.set_label(messageTotalDemoActivated.str());
	labelTotalRecoveryActivatedCounter.set_label(messageTotalRecoveryActivated.str());
	labelTotalAudioOfficialActivatedCounter.set_label(messageTotalAudioOfficialActivated.str());
	labelTotalAudioDemoActivatedCounter.set_label(messageTotalAudioDemoActivated.str());
	labelTotalAudioRecoveryActivatedCounter.set_label(messageTotalAudioRecoveryActivated.str());
	labelTotalNonAudioOfficialActivatedCounter.set_label(messageTotalNonAudioOfficialActivated.str());
	labelTotalNonAudioDemoActivatedCounter.set_label(messageTotalNonAudioDemoActivated.str());
	labelTotalNonAudioRecoveryActivatedCounter.set_label(messageTotalNonAudioRecoveryActivated.str());

	for(unsigned int l=0;l<listOfCounters.size();l++)
	{
		listOfCounters[l]->Dispose();
		vboxPrincipal.remove(*listOfCounters[l]);
		delete(listOfCounters[l]);
	}

	for(unsigned int k=0;k<titles.size();k++)
	{
		vboxPrincipal.remove(*titles[k]);
		delete(titles[k]);
	}

	titles.clear();
	listOfCounters.clear();

		Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper * actStatWrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics();
	Smartmatic::SAES::Voting::PBReports::ActivatedCardStatistics * stats = actStatWrapper->getCardStatistics();
	 Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper* vd =  Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice();
	if(!conf.getHideCA())
	{
		if(!conf.getHideNonAudio())
		{
			if(!conf.getHideOfficial())
			{
				Gtk::Label* labelOfficNATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.OfficialNonAudioTitle")));
				//labelOfficNATitle->set_padding(0, 10);
				labelOfficNATitle->modify_font(fontTitle);
				titles.push_back(labelOfficNATitle);

				Gtk::HBox* hboxOfficNATitle = manage(new Gtk::HBox());
				hboxOfficNATitle->pack_start(*labelOfficNATitle,Gtk::PACK_SHRINK);
				if(widgetToDelete)
				{
					delete widgetToDelete;
				}
				widgetToDelete = hboxOfficNATitle;

				vboxPrincipal.pack_start(*hboxOfficNATitle,Gtk::PACK_SHRINK);

				for(unsigned int j=0;j<stats->getActivatedOfficialNonAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }

					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
					
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						//vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator0 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator0,Gtk::PACK_SHRINK);
			}
			if(!conf.getHideDemo())
			{

				Gtk::Label* labelDemoNATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.DemoNonAudioTitle")));
				labelDemoNATitle->set_padding(0, 10);
				Gtk::HBox* hboxDemoNATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxDemoNATitle,Gtk::PACK_SHRINK);
				hboxDemoNATitle->pack_start(*labelDemoNATitle,Gtk::PACK_SHRINK);
				labelDemoNATitle->modify_font(fontTitle);
				titles.push_back(labelDemoNATitle);
				for(unsigned int j=0;j< stats->getActivatedDemoNonAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					 Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }
					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator1 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator1,Gtk::PACK_SHRINK);
			}
		}
		
		if(!conf.getHideAudio())
		{
			if(!conf.getHideOfficial())
			{
				Gtk::Label* labelOfficATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.OfficialAudioTitle")));
				labelOfficATitle->set_padding(0, 10);
				Gtk::HBox* hboxOfficATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxOfficATitle,Gtk::PACK_SHRINK);
				hboxOfficATitle->pack_start(*labelOfficATitle,Gtk::PACK_SHRINK);
				labelOfficATitle->modify_font(fontTitle);
				titles.push_back(labelOfficATitle);
				for(unsigned int j=0;j<stats->getActivatedOfficialAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;

					 Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }
					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
		
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedOfficialAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedOfficialAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator2 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator2,Gtk::PACK_SHRINK);
			}
		
			if(!conf.getHideDemo())
			{
				Gtk::Label* labelDemoATitle = manage(new Gtk::Label(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.DemoAudioTitle")));
				labelDemoATitle->modify_font(fontTitle);
				labelDemoATitle->set_padding(0, 10);
				Gtk::HBox* hboxDemoATitle = manage(new Gtk::HBox());
				vboxPrincipal.pack_start(*hboxDemoATitle,Gtk::PACK_SHRINK);
				hboxDemoATitle->pack_start(*labelDemoATitle,Gtk::PACK_SHRINK);
				titles.push_back(labelDemoATitle);
				for(unsigned int j=0;j<stats->getActivatedDemoAudioByCA().getCardByCA().size(); j++)
				{
					unsigned int counter = stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCounter();
					std::stringstream  counterStream;
					counterStream << counter;


					Glib::ustring caCode = "No CA Found";
					 Glib::ustring caName ="No CA Found";
					 Glib::ustring caDesc ="No CA Found";

					 Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition caDefs;
					 bool caOk = vd->GetCustomAttributeDefinition(stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCACode(),caDefs );

					 if(caOk)
					 {
						 caCode = ElectionStringResourcesManager::Current()->getResource(caDefs.getCode());
						 caName = ElectionStringResourcesManager::Current()->getResource(caDefs.getName_key());
						 caDesc = ElectionStringResourcesManager::Current()->getResource(caDefs.getDescription_key());
					 }
					if(caDefs.getMachine_type () == "PM")
					{
						 Glib::ustring labelTilteText = Glib::ustring::compose(_("Smartmatic.SAES.GUI.Widgets.CustomAttributesCounterWidget.CustomAttributeLabelText"), caCode, caName, caDesc );

						 Glib::ustring labelValueText = ElectionStringResourcesManager::Current()->getResource(stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCAValue());
						ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (labelTilteText, labelValueText,counterStream.str());
					
						//ActivatorCardCounterWidget *cardCounterWidget = new ActivatorCardCounterWidget (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getCardStatistics()->getActivatedDemoAudioByCA().getCardByCA()[j].getCACode(),
						//stats->getActivatedDemoAudioByCA().getCardByCA()[j].getCAValue(),counterStream.str());
						vboxPrincipal.pack_start(*cardCounterWidget,Gtk::PACK_SHRINK);
						addCounter(cardCounterWidget);
					}
				}
				//Gtk::HSeparator* hseparator3 = manage(new Gtk::HSeparator());
				//vboxPrincipal.pack_start(*hseparator3,Gtk::PACK_SHRINK);
			}

		}
	}
}

void CustomAttributesCounterWidget::RefreshStats(Smartmatic::SAES::Voting::VotingDevice::Card_data & card)
throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException)
{
	 Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->RefreshStats(card);
	 RefreshCounter();
}

void CustomAttributesCounterWidget::addCounter(ActivatorCardCounterWidget* counter)
{
	listOfCounters.push_back (counter);
	vboxPrincipal.pack_start(*counter,Gtk::PACK_SHRINK);
	vboxPrincipal.show_all_children ();
	vboxPrincipal.set_visible (true);
}

CustomAttributesCounterWidget::~CustomAttributesCounterWidget()
{

}

void CustomAttributesCounterWidget::ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight)
{
	for(unsigned int l=0;l<listOfCounters.size();l++)
	{
		listOfCounters[l]->ResizeOptionsWidgets(WidgetOptionsWidth,WidgetOptionsHeight);
	}
}

std::vector<ActivatorCardCounterWidget*> CustomAttributesCounterWidget::getListOfCounters()
{
	return listOfCounters;
}

void CustomAttributesCounterWidget::Dispose()
{
	
	for(unsigned int l=0;l<listOfCounters.size();l++)
	{
		listOfCounters[l]->Dispose();
		vboxPrincipal.remove(*listOfCounters[l]);
		delete(listOfCounters[l]);
	}

	for(unsigned int k=0;k<titles.size();k++)
	{
		vboxPrincipal.remove(*titles[k]);
		delete(titles[k]);
	}

	titles.clear();
	listOfCounters.clear();
}



