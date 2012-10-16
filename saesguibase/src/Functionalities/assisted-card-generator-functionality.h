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

#ifndef _ASSISTED_CARD_GENERATOR_FUNCTIONALITY_H_
#define _ASSISTED_CARD_GENERATOR_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Functionalities/graphic-display-functionality.h>
#include "Gui/Windows/choose-option-window.h"
#include "Gui/Widgets/recovery-card-generator-widget.h"
#include "Gui/Widgets/custom-attributes-combo-selections-widget.h"
#include "Gui/Widgets/custom-attributes-counter-widget.h"
#include "Gui/Widgets/assisted-activation-add-widget.h"
#include "Gui/Widgets/assisted-activation-view-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include "Gui/Widgets/assisted-activation-manager-widget.h"
#include "Gui/Widgets/assisted-activation-id-card-widget-viewer.h"
#include <Widgets/smartmatic-button.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class AssistedCardGeneratorFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{

				public:

					/**
					 * @brief	Gets the dont allow help.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowHelp();

					/**
					 * @brief	Gets the help sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The help sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getHelpSeqKey();

					/**
					 * @brief	Gets the dont allow exit.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowExit();

					/**
					 * @brief	Gets the sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getSeqKey();

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static AssistedCardGeneratorFunctionality* Current();

				protected:

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The start log message.
					 */

					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finish log message.
					 */

					Glib::ustring getFinishLogMessage();

					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

				private:
					bool cardJustActivated;		///< true if card was just activated
					bool isAssistedActivation;  ///< true if is assisted activation
					bool wasPresent;	///< true to was present
					std::vector<unsigned char> dataBinarizedToWrite;	///< The data binarized to write
					sigc::connection conn;  ///< The connection
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Frame* frame1; ///< The first frame
					Gtk::Frame* frame2; ///< The second frame
					Gtk::Frame* frame4; ///< The fourth frame
					Gtk::EventBox* eventboxCardActivator;   ///< The eventbox card activator
					Gtk::EventBox* cardActivatorMessageEventBox;	///< The card activator message event box
					Gtk::EventBox* cardActivatorFunctionalityEventBox;  ///< The card activator functionality event box
					Gtk::EventBox* cardActivatorValuesEventBox; ///< The card activator values event box
					Gtk::HBox* hbox1;   ///< The first hbox
					Gtk::VBox* vbox2;   ///< The second vbox
					Gtk::Image* imageCard;  ///< The image card
					Gtk::Label* labelResult;	///< The label result
					Gtk::VBox* vboxBack;	///< The vbox back
					Gtk::Label* labelBack;  ///< The label back
					Gtk::Alignment* alignmentBack;  ///< The alignment back
					Gtk::HButtonBox* assistedAlignment; ///< The assisted alignment
					Gtk::VButtonBox* vbuttonbox1;   ///< The first vbuttonbox
					Gtk::HButtonBox buttonBox;  ///< The button box
					Smartmatic::GUI::Widgets::SmartmaticButton buttonOk;   ///< The button ok
					Smartmatic::GUI::Widgets::SmartmaticButton buttonCancel;   ///< The button cancel
					Gtk::CheckButton* checkbuttonIsAudio;   ///< The button to determine if is Audio
					Gtk::ScrolledWindow* scrolled;
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonBack; ///< The button back
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonActivate; ///< The button activate
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonStartWizard; ///< The button recovery activate
					Smartmatic::SAES::GUI::Widgets::AssistedActivationManagerWidget* assistedManager;
					Smartmatic::SAES::GUI::Widgets::AssistedActivationIDCardWidgetViewer* assistedPreviewInfo;
					Smartmatic::SAES::GUI::Widgets::ComboBoxChooseWidget *comboWidget;
					Smartmatic::SAES::GUI::Widgets::EventBoxChooseWidget *eventWidget;

					/**
					 * @brief	Handles button ok clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonOk_clicked();	

					/**
					 * @brief	Handles button recovery ok clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonStartWizard_clicked();

					/**
					 * @brief	Handles button cancel clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonCancel_clicked();	

					/**
					 * @brief	Handles button generate clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonGenerate_clicked();

					/**
					 * @brief	Handles button back clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_buttonBack_clicked();

					/**
					 * @brief	Handles assisted ok signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	activation	The activation.
					 */

					void on_AssistedOk(Smartmatic::SAES::Voting::PBReports::Activation activation);

					/**
					 * @brief	Handles assisted cancel signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					Smartmatic::SAES::GUI::Widgets::RecoveryCardInfo recoveryInfo;  ///< Information describing the recovery

					/**
					 * @brief	Go to selection window.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void GoToSelectionWindow();
					std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute*> attributes;  ///< The attributes
					Smartmatic::SAES::GUI::Widgets::CustomAttributesComboSelectionsWidget* comboSelections; ///< The combo selections
					static AssistedCardGeneratorFunctionality *current_instance;	///< The current instance

					/**
					 * @brief	Refresh counter.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	optionName 	Name of the option.
					 * @param	optionValue	The option value.
					 */

					void RefreshCounter(std::string optionName, std::string optionValue);

					/**
					 * @brief	Executes the option button action.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param [in,out]	info	If non-null, the information.
					 */

					void onOptionButton(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* info);

					/**
					 * @brief	Generates a recovery card.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The recovery card.
					 */

					Smartmatic::SAES::Voting::VotingDevice::Card_data GenerateRecoveryCard();
					std::string temporalValue;  ///< The temporal value

					/**
					 * @brief	Default constructor Initialize all variables in NULL.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					AssistedCardGeneratorFunctionality();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					~AssistedCardGeneratorFunctionality();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();	
					std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > listCAD;  ///< The list cad
					Smartmatic::SAES::Voting::PBReports::Activation activation; ///< The activation

					/**
					 * @brief	Gets a code by name.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	optionName	Name of the option.
					 *
					 * @return	The code by name.
					 */

					std::string getCodeByName(std::string optionName);

					/**
					 * @brief	Gets a name by code.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	optionCode	The option code.
					 *
					 * @return	The name by code.
					 */

					std::string getNameByCode(std::string optionCode);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					Gtk::Widget* GetFrame();

					/**
					 * @brief	Enables this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Enable();

					/**
					 * @brief	Refreshs.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int time_num);

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
					
					bool wizardIsReady;

					void cleanAttributes();

				};
			}
		}
	}
}

#endif // _ASSISTED_CARD_GENERATOR_FUNCTIONALITY_H_
