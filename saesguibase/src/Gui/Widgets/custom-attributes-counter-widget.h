/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	custom-attributes-counter-widget.h
 *
 * @brief	Declares the custom attributes counter widget class.
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

#ifndef _CUSTOM_ATTRIBUTES_COUNTER_WIDGET_H_
#define _CUSTOM_ATTRIBUTES_COUNTER_WIDGET_H_

#include <gtkmm.h>
#include <iostream>
#include "activator-card-counter-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	CustomAttributesCounterWidget
				 *
				 * @brief	Custom attributes counter widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class CustomAttributesCounterWidget:public Gtk::Frame
				{
				public:

				/**
				 * @fn	CustomAttributesCounterWidget::CustomAttributesCounterWidget(std::string labelTitle,
				 * 		std::string imagePath);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	labelTitle	The label title.
				 * @param	imagePath 	Full pathname of the image file.
				 */

				CustomAttributesCounterWidget(std::string labelTitle,std::string imagePath, Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration conf,
				                              Smartmatic::SAES::Configuration::ColorConfiguration colorTitleConf,
                                                             Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConf);

				/**
				 * @fn	void CustomAttributesCounterWidget::addCounter(ActivatorCardCounterWidget* counter);
				 *
				 * @brief	Adds a counter. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	counter	If non-null, the counter.
				 */

				void addCounter(ActivatorCardCounterWidget* counter);		

				/**
				 * @fn	CustomAttributesCounterWidget::~CustomAttributesCounterWidget();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				~CustomAttributesCounterWidget();

				/**
				 * @fn	void CustomAttributesCounterWidget::Dispose();
				 *
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void Dispose();

				/**
				 * @fn	void CustomAttributesCounterWidget::ResizeOptionsWidgets(int WidgetOptionsWidth,
				 * 		int WidgetOptionsHeight);
				 *
				 * @brief	Resize options widgets.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	WidgetOptionsWidth 	Width of the widget options.
				 * @param	WidgetOptionsHeight	Height of the widget options.
				 */

				void ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight);



				
				/**
				 * @fn	std::vector<ActivatorCardCounterWidget*> CustomAttributesCounterWidget::getListOfCounters();
				 *
				 * @brief	Gets the list of counters.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	null if it fails, else the list of counters.
				 */

				std::vector<ActivatorCardCounterWidget*> getListOfCounters();	
				
				/**
				 * @fn	void CustomAttributesCounterWidget::RefreshStats(Smartmatic::SAES::Voting::VotingDevice::Card_data card);
				 *
				 * @brief	Refresh the statistics
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	Smartmatic::SAES::Voting::VotingDevice::Card_data The data of the card generated to refresh statistics
				 * @param	oneMemory true if one memory
				 */						 
				void RefreshStats(Smartmatic::SAES::Voting::VotingDevice::Card_data & card)throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException);

				/**
				 * @fn	void CustomAttributesCounterWidget::RefreshCounter();
				 *
				 * @brief	Refresh the propper Counters
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 */
				void RefreshCounter();

				protected:

				private:	

				Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration conf; // configuration of widget

				/**
				 * @fn	void CustomAttributesCounterWidget::setCounters();
				 *
				 * @brief	set the propper Counters
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 */	
				void setCounters();
						
				std::vector<ActivatorCardCounterWidget*> listOfCounters;	///< The list of counters
				std::vector<Gtk::Label*> titles; // list of titles of CA groups;

				Gtk::VBox vboxPrincipal;// principal vbox																				
						
				Gtk::EventBox eventBoxTitle;	///< The event box title
				Gdk::Color selectedColor;   ///< The selected color for title
				Gtk::Label labelTitle;  ///< The label title

				Gtk::HBox hboxTotalActivated;   ///< The hbox for total 			
				Gtk::Label labelTotalActivated;  ///< The label for total
				Gtk::Label labelTotalActivatedCounter;  ///< The label counter for total
							
				Gtk::Label labelTotalNonAudioActivated;  ///< The label for non audio
				Gtk::HBox hboxTotalNonAudioActivated;   ///< The hbox for non audio
				Gtk::Label labelTotalNonAudioActivatedCounter;  ///< The label counter for non audio
							
				Gtk::Label labelTotalAudioActivated;  ///< The label for audio
				Gtk::HBox hboxTotalAudioActivated;   ///< The hbox for audio
				Gtk::Label labelTotalAudioActivatedCounter;  ///< The label counter for audio
							
				Gtk::Label labelTotalOfficialActivated;  ///< The label for official
				Gtk::HBox hboxTotalOfficialActivated;   ///< The hbox for official
				Gtk::Label labelTotalOfficialActivatedCounter;  ///< The label counter for official
							
				Gtk::Label labelTotalDemoActivated;  ///< The label for demo
				Gtk::HBox hboxTotalDemoActivated;   ///< The hbox for demo
				Gtk::Label labelTotalDemoActivatedCounter;  ///< The label counter for demo 
							
				Gtk::Label labelTotalRecoveryActivated;  ///< The label for recovery
				Gtk::HBox hboxTotalRecoveryActivated;   ///< The hbox for recovery
				Gtk::Label labelTotalRecoveryActivatedCounter;  ///< The label counter for recovery
							
				Gtk::Label labelTotalAudioOfficialActivated;  ///< The label for audio official
				Gtk::HBox hboxTotalAudioOfficialActivated;   ///< The hbox  for audio official
				Gtk::Label labelTotalAudioOfficialActivatedCounter;  ///< The label counter  for audio official
							
				Gtk::Label labelTotalAudioDemoActivated;  ///< The label for audio demo
				Gtk::HBox hboxTotalAudioDemoActivated;   ///< The hbox  for audio demo
				Gtk::Label labelTotalAudioDemoActivatedCounter;  ///< The label counter  for audio demo
							
				Gtk::Label labelTotalAudioRecoveryActivated;  ///< The label for audio recovery
				Gtk::HBox hboxTotalAudioRecoveryActivated;   ///< The hbox  for audio recovery
				Gtk::Label labelTotalAudioRecoveryActivatedCounter;  ///< The label counter  for audio recovery
							
				Gtk::Label labelTotalNonAudioOfficialActivated;  ///< The label for non audio official
				Gtk::HBox hboxTotalNonAudioOfficialActivated;   ///< The hbox  for non audio official
				Gtk::Label labelTotalNonAudioOfficialActivatedCounter;  ///< The label counter  for non audio official
							
				Gtk::Label labelTotalNonAudioDemoActivated;  ///< The label for non audio demo
				Gtk::HBox hboxTotalNonAudioDemoActivated;   ///< The hbox  for non audio demo
				Gtk::Label labelTotalNonAudioDemoActivatedCounter;  ///< The label counter  for non audio demo
							
				Gtk::Label labelTotalNonAudioRecoveryActivated;  ///< The label for non audio recovery
				Gtk::HBox hboxTotalNonAudioRecoveryActivated;   ///< The hbox  for non audio recovery
				Gtk::Label labelTotalNonAudioRecoveryActivatedCounter;  ///< The label counter  for non audio recovery
							
				Gtk::Image imageTitle;  ///< The image title
				Gtk::HBox hboxHeader;   ///< The hbox header

				Gtk::HSeparator separator0;
				Gtk::HSeparator separator1;
				Gtk::HSeparator separator2;
				Gtk::HSeparator separator3;
				Gtk::HSeparator separator4;
				Gtk::HSeparator separator5;
				Gtk::HSeparator separator6;
				Gtk::HSeparator separator7;
				Gtk::HSeparator separator8;
				Gtk::HSeparator separator9;
				Gtk::HSeparator separator10;
				Gtk::HSeparator separator11;
				Gtk::ScrolledWindow  scrolledCounter;  ///< The scrolled magnify
				//Gtk::Viewport   viewCounter;   ///< The view magnify
				Gtk::Widget* widgetToDelete; // The widget to delete
				Pango::FontDescription fontTitle; // The font title description

				};
			}
		}
	}
}


#endif // _CUSTOM_ATTRIBUTES_COUNTER_WIDGET_H_
