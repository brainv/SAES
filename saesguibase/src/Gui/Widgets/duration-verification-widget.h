/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	recovery-card-generator-widget.h
 *
 * @brief	Declares the recovery card generator widget class.
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

#ifndef _DURATION_VERIFICATION_WIDGET_H_
#define _DURATION_VERIFICATION_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>
#include <Widgets/smartmatic-entry-hours.h>
#include <Widgets/smartmatic-button.h>
#include <Widgets/smartmatic-combo-box.h>
#include <Operation/MachineOperationManager.hxx>
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
				 * @class	DurationVerificationWidget
				 *
				 * @brief	duration verification widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class DurationVerificationWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					/**
					 * @fn	DurationVerificationWidget::DurationVerificationWidget();
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 */

					DurationVerificationWidget();
					sigc::signal<void> signalOk_detected;  ///< The signal ok detected
					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

						/**
					 * @brief	return the widgets name.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The widget name.
					 */

					Glib::ustring GetWidgetName();
					
				protected:

				private:

					/**
					 * @fn	void DurationVerificationWidget::on_buttonOk_clicked();
					 *
					 * @brief	Handles button ok clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonOk_clicked();

				
					Gtk::VBox vboxPrincipal;	///< The vbox principal
					Gtk::Label labelOpenElection;   ///< The label Open Election
					//Gtk::Label labelCloseElection;	///< The label Close Election
					//Gtk::Label labelOpenElectionValue;   ///< The label Open Election value
					//Gtk::Label labelCloseElectionValue;	///< The label Close Election value
					Gtk::Label labelDuration;   ///< The label Duration
					Gtk::Label labelTitle;  ///< The label title
					Gtk::HBox hboxTitle;	///< The hbox title
					Gtk::HButtonBox hboxOpenElection; ///< The hbox Open Election
					Gtk::HBox hboxCloseElection;  ///< The hbox Close Election
					Gtk::HBox hboxDuration; ///< The hbox Duration
					Gtk::HButtonBox hbuttonbox; ///< The hbuttonbox
					Gtk::HButtonBox hbuttonboxprincipal;
					Smartmatic::GUI::Widgets::SmartmaticEntryHours hoursWidget; ///< The widget holding the hour
					Smartmatic::GUI::Widgets::SmartmaticButton okButton;	///< The ok button

					void CheckFields(bool disableButton);

					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}


#endif // _DURATION_VERIFICATION_WIDGET_H_
