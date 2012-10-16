/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk_functionalities
 * Copyright (C)  2010 <>
 * 
 * gtk_functionalities is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk_functionalities is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GRAPHIC_DISPLAY_FUNCTIONALITY_H_

/**
 * @brief	Gets the graphic display functionality h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define _GRAPHIC_DISPLAY_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>

#include "Functionalities/saes-functionality.h"
#include "Gui/Windows/empty-window.h"
#include "Functionalities/saes-menu-option-descriptor.h"
#include "Functionalities/saes-menu-option-type.h"
#include "Windows/pop-up-message-window.h"
#include "Configuration/label-configuration.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Functionalities/FunctionalityChallengeConfiguration.h"
#include "Functionalities/Providers/PresidentPassPhraseAuthenticationProvider.h"
#include "Functionalities/Providers/RoleAuthenticationProvider.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Devices/barcode-device.h>
#include <Operation/Card/CardController.hxx>
#include <Printing/PrinterStatusNotifier.h>
#include <Widgets/StepWidget.hxx>
#include <Widgets/RefreshListener.hxx>
#include <Widgets/StateListener.hxx>
#include <Gui/Widgets/HelpWidget.hxx>
#include <Gui/Widgets/InfoStepWidget.hxx>

#define N_(String) (String)

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{

			    /**
				 * @brief	Graphic display functionality. 
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				template <class TMenuOptionDescriptor>
				class GraphicDisplayFunctionality : public Smartmatic::SAES::Functionality::SAESFunctionality<TMenuOptionDescriptor>,
					public Smartmatic::GUI::Widgets::RefreshListener,
					public Smartmatic::GUI::Widgets::StateListener
				{


				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
					 */

					GraphicDisplayFunctionality();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @tparam	TMenuOptionDescriptor	Type of the menu option descriptor.
					 */

					~GraphicDisplayFunctionality();

					/**
					 * @brief	Begins an execute.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void BeginExecute();

					/**
					 * @brief	Execute a Background process functionality.
					 *
					 * @author	Gerardo.Hernandez
					 * @date	10/06/2011
					 */
					virtual void ExcuteBackgroundProcess();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Rafael.gasperi
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					virtual TMenuOptionDescriptor GetMenuOptionType() = 0;

					/**
					 * @brief	Executes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @exception	e	Thrown when .
					 */

					void Execute();

					/**
					 * @brief	Pre load.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void PreLoad();
	
					//Pure Virtual Function

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					virtual  Gtk::Widget* GetFrame() = 0;

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					virtual void Dispose() = 0;

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					virtual void Initialize() = 0;

					/**
					 * @brief	Gets the helpconfiguration.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The helpconfiguration.
					 */

					virtual std::vector<Smartmatic::GUI::Windows::HelpItem> GetHelpconfiguration();

					/**
					 * @brief	Displays a unable message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void DisplayUnableMessage();

					/**
					 * @brief	Force show help.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ForceShowHelp();

					/**
					 * @brief	Gets if password is role
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					bool GetIsRolePassword();

					/**
					 * @brief	Return if this functionality can be executed
					 *
  					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if can execute functionality
					 */

					virtual bool CanExecute();

					/**
					 * @brief	Enables this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool Enable();

					/**
					 * @brief	Force exit.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ForceExit();

					/**
					 * @brief	Gets the challenge is enable.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool ChallengeIsEnable();

					/**
					 * @brief	Gets the challenge configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The challenge configuration.
					 */

					virtual Smartmatic::Functionality::FunctionalityChallengeConfiguration getChallengeConfiguration();
					/**
					 * @brief	Gets the challenge title message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The challenge title message.
					 */

					virtual std::string getChallengeTitleMessage();

					/**
					 * @brief	Gets the ivalid challenge message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The ivalid challenge message.
					 */

					virtual std::string getIvalidChallengeMessage();

					/**
					 * @brief	Gets the valid challenge message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The valid challenge message.
					 */

					virtual std::string getValidChallengeMessage();

					/**
					 * @brief	Gets the description message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The description message.
					 */

					virtual std::string getDescriptionMessage();

                    /**
                     * @brief   Sets an exit button sensitive.
                     *
                     * @author  Luiggi.mendez
                     * @date    28/04/2011
                     *
                     * @param   sensitive   true to sensitive.
                     */

                    void setExitButtonSensitive(bool sensitive);

                    /**
					 * @brief   Sets a help button sensitive.
					 *
					 * @author  Luiggi.mendez
					 * @date    28/04/2011
					 *
					 * @param   sensitive   true to sensitive.
					 */
                    void setHelpButtonSensitive(bool sensitive);

					/**
					 * @brief Method enable exit button
					 * @date 09/04/2012
					 * @author Yadickson Soto
					 */
					void enableExitButton();

					/**
					 * @brief Method disable exit button
					 * @date 09/04/2012
					 * @author Yadickson Soto
					 */
					void disableExitButton();

					/**
					 * @brief Method enable help button
					 * @date 09/04/2012
					 * @author Yadickson Soto
					 */
					void enableHelpButton();

					/**
					 * @brief Method disable help button
					 * @date 09/04/2012
					 * @author Yadickson Soto
					 */
					void disableHelpButton();

				protected:

					sigc::connection startHelpPrintConn;	///< The start print connection
					sigc::connection stopHelpPrintConn;	///< The stop print connection

					Smartmatic::SAES::GUI::Windows::EmptyWindow *baseWindow;	///< The base window
					Smartmatic::GUI::Widgets::StepWidget stepWidget; ///< step widget
					Smartmatic::SAES::GUI::Widgets::InfoStepWidget initWidget; ///< init widget
					Smartmatic::SAES::GUI::Widgets::HelpWidget helpWidget; ///< help widget
					Smartmatic::SAES::GUI::Widgets::InfoStepWidget exitWidget; ///< exit widget
					/**
					 * @brief	Gets the challenge password source.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The challenge password source.
					 */

					virtual Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum getChallengePasswordSource();

					/**
					 * @brief	Gets the challenge is enable.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool getChallengeIsEnable();

					/**
					 * @brief	Locks the machine.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool LockMachine();

					/**
					 * @brief	Show final message.
					 *
					 * @author	Juan.Delgado
					 * @date	28/04/2011
					 *
					 * @return	true if show final message
					 */

					bool ShowFinalMessage();

					/**
					 * @brief	Executes the exit button clicked action.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					virtual void OnExitButtonClicked();
					virtual void BeforeExit();

					void ExitFunctionality();

					/**
					 * @brief	Executes the help button clicked action.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void OnHelpButtonClicked();

					/**
					 * @brief	Executes the help button clicked action.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void OnHelpButtonClickedConnect();

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					virtual Smartmatic::Log::ISMTTLog* getLogger() = 0;

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The start log message.
					 */

					virtual Glib::ustring getStartLogMessage() = 0;

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finish log message.
					 */

					virtual Glib::ustring getFinishLogMessage() = 0;

					/**
					 * @brief	Enable background process functionality.
					 *
					 * @author	Gerardo.Hernandez
					 * @date	10/06/2011
					 */
					void EnableBackgroundProcess();

					/**
					 * @brief virtual method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement() = 0;

					/**
					 * @brief	Set memory block behavior
					 *
					 * @author	Juan.Delgado
					 * @date	16/08/2011
					 */
					void SetMemoryBlock();

					/**
					 * @brief	Set menu memory block behavior
					 *
					 * @author	Juan.Delgado
					 * @date	10/06/2011
					 */
					void SetMenuMemoryBlock();

					void RefreshInfo();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief method block functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void block();
					/**
					 * @brief method partial functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void partial();
					/**
					 * @brief method resume functionality
					 * @date 19/04/2012
					 * @author Yadickson Soto
					 */
					virtual void resume();

				private:
					Gtk::Widget *frame; ///< The frame

					bool forceToLoad;
					bool enableBackgroundProcess; ///<enable background process
					
					sigc::connection connector; ///< The connector
					sigc::slot<bool> slot_button;   ///< The slot button

					sigc::connection exit_connector;	///< The exit connector
					sigc::slot<bool> exit_slot_button;  ///< The exit slot button

					Smartmatic::SAES::Configuration::HelpConfiguration helpConfiguration; ///<the help configuration

					/**
					 * @brief	Executes the dispose operation.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ExecuteDispose();

					bool checkMemoryPath();

					bool checkOperationStatus(Smartmatic::SAES::Voting::OperationStatus * operationStatus);

					bool checkNecessaryDevices();

					bool checkBarcode();

					bool checkSmartcard();

					bool checkPrinter();

					/**
					 * @brief	Exits this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Exit(); //Call OnExitButtonClicked if want to exit functionality

					sigc::connection connExitWindow; ///< The connector
					sigc::connection connShowExitMessage; ///< the connector show exit message
				};
			}
		}
	}
}

#include "graphic-display-functionality.hpp"

#endif // _GRAPHIC_DISPLAY_FUNCTIONALITY_H_
