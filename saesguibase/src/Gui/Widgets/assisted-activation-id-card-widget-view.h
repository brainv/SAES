/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	close-election-status-widget.h
 *
 * @brief	Declares the close election status widget class.
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

#ifndef _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEW_
#define _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEW_
#include <gtkmm.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	AssistedActivationIDCardWidgetView
				 *
				 * @brief	Show the info for a assisted activation specific individual. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */
				class AssistedActivationIDCardWidgetView: public Gtk::Frame
				{
				public:

							/**
						 * @fn	AssistedActivationIDCardWidgetView::AssistedActivationIDCardWidgetView (std::string title, std::string firstNameValue, std::string surNameValue);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	firstNameValue the subject first name
						 * @param	surNameValue the subject last name
						 */
					AssistedActivationIDCardWidgetView(std::string title, std::string firstNameValue, std::string surNameValue/*,std::string genderValue,
                                                                       std::string nationalityValue, std::string natNumberValue*/);

						/**
						 * @fn	AssistedActivationIDCardWidgetView::AssistedActivationIDCardWidgetView ();
						 *
						 * @brief	Finalizer.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 */
					~AssistedActivationIDCardWidgetView();

					 /**
					 * @fn	void AssistedActivationIDCardWidgetView::init();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					void init();

						/**
					 * @fn	void AssistedActivationIDCardWidgetView::dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					void dispose();


				private:

					Gtk::EventBox event;	///< The principal event box
					Gtk::VBox vboxEvents;   ///< The vbox events
					Gtk::HBox hboxRowFirstName;   ///< The hbox row  First Name
					Gtk::HBox hboxRowSurName;   ///< The hbox row  SurName
					Gtk::HBox hboxRowGender;   ///< The hbox row  Gender
					Gtk::HBox hboxRowNationality;   ///< The hbox row  Nationality
					Gtk::HBox hboxRowNatNumber;   ///< The hbox row  Nat Number
					
					Gtk::Label labelTitle; /// < the title label
					Gtk::EventBox eventTitle;	///< The event box for title
					Gtk::Label firstNameLabel; ///< The first name label
					Gtk::Label surNameLabel;   ///< The sur name label
					Gtk::Label genderLabel;	///< The gender label
					Gtk::Label nationalityLabel;   ///< The nationality label
					Gtk::Label natNumberLabel; ///< The nat number label

					Gtk::Label firstNameValueLabel; ///< The first name value label
					Gtk::Label surNameValueLabel;   ///< The sur name value label
					Gtk::Label genderValueLabel;	///< The gender value label
					Gtk::Label nationalityValueLabel;   ///< The nationality value label
					Gtk::Label natNumberValueLabel; ///< The nat number value label

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _ASSISTED_ACTIVATION_ID_CARD_WIDGET_VIEW_
