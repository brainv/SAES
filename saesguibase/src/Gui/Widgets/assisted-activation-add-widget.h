/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	assisted-activation-add-widget.h
 *
 * @brief	Declares the assisted activation add widget class.
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

#ifndef _ASSISTED_ACTIVATION_ADD_WIDGET_H_
#define _ASSISTED_ACTIVATION_ADD_WIDGET_H_
#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>
#include <Widgets/smartmatic-combo-box.h>
#include <Operation/MachineOperationManager.hxx>
#include <Widgets/smartmatic-entry.h>
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
				 * @class	AssistedActivationAddWidget
				 *
				 * @brief	Assisted activation add widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class AssistedActivationAddWidget: public Gtk::HBox
				{
				public:

					/**
					 * @fn	AssistedActivationAddWidget::AssistedActivationAddWidget(bool waitForCardToRegister);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	waitForCardToRegister	true to wait for card to register.
					 */

					AssistedActivationAddWidget(bool waitForCardToRegister);

					/**
					 * @fn	AssistedActivationAddWidget::~AssistedActivationAddWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					~AssistedActivationAddWidget();
					sigc::signal<void,Smartmatic::SAES::Voting::PBReports::Activation> signalOk_detected;   ///< The signal ok detected
					sigc::signal<void> signalCancel_detected;   ///< The signal cancel detected

					/**
					 * @fn	void AssistedActivationAddWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void Initialize();

					/**
					 * @fn	void AssistedActivationAddWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void Dispose();
				protected:

				private:
					Glib::ustring presidentSelection;   ///< The president selection
					Glib::ustring witnessSelection; ///< The witness selection
					bool chooseByCombo; ///< true to choose by combo
					bool waitForCardToRegister; ///< true to wait for card to register

					/**
					 * @fn	bool AssistedActivationAddWidget::Refresh(int time_num);
					 *
					 * @brief	Refreshs.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int time_num);

					/**
					 * @fn	void AssistedActivationAddWidget::on_buttonOk_clicked();
					 *
					 * @brief	Handles button ok clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void on_buttonOk_clicked();

					/**
					 * @fn	void AssistedActivationAddWidget::on_buttonCancel_clicked();
					 *
					 * @brief	Handles button cancel clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void on_buttonCancel_clicked();

					/**
					 * @fn	void AssistedActivationAddWidget::onWitnessComboChanged(Glib::ustring selected);
					 *
					 * @brief	Executes the witness combo changed action.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	selected	The selected.
					 */

					void onWitnessComboChanged(Glib::ustring selected);

					/**
					 * @fn	void AssistedActivationAddWidget::onPresidentComboChanged(Glib::ustring selected);
					 *
					 * @brief	Executes the president combo changed action.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	selected	The selected.
					 */

					void onPresidentComboChanged(Glib::ustring selected);
					sigc::connection connOk;	///< The connection ok
					sigc::connection connCancel;	///< The connection cancel
					sigc::connection connRefresh;   ///< The connection refresh
					Gtk::VBox vboxPrincipal;	///< The vbox principal
					Smartmatic::GUI::Widgets::SmartmaticEntry entryWitness;	///< The entry witness
					Smartmatic::GUI::Widgets::SmartmaticEntry entryPresident;  ///< The entry president
					Smartmatic::GUI::Widgets::SmartmaticEntry entryVoter;  ///< The entry voter
					Smartmatic::GUI::Widgets::SmartmaticComboBox comboPresident;	///< The combo president
					Smartmatic::GUI::Widgets::SmartmaticComboBox comboWitness;  ///< The combo witness
					Gtk::Label labelWitness;	///< The label witness
					Gtk::Label labelPresident;  ///< The label president
					Gtk::Label labelVoter;  ///< The label voter
					Gtk::Label labelTitle;  ///< The label title
					Gtk::Label labelMessage;	///< Message describing the label
					Gtk::HBox hboxTitle;	///< The hbox title
					Gtk::HBox hboxWitness;  ///< The hbox witness
					Gtk::HBox hboxPresident;	///< The hbox president
					Gtk::HBox hboxVoter;	///< The hbox voter
					Gtk::HButtonBox hbuttonbox; ///< The hbuttonbox
					Smartmatic::GUI::Widgets::SmartmaticButton okButton;	///< The ok button
					Smartmatic::GUI::Widgets::SmartmaticButton cancelButton;	///< The cancel button

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}



#endif // _ASSISTED_ACTIVATION_ADD_WIDGET_H_
