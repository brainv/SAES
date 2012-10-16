/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	voting-machine-installation-wizard-widget.h
 *
 * @brief	Declares the voting machine installation wizard widget class.
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

#ifndef _VOTING_MACHINE_INSTALLATION_WIZARD_WIDGET_H_
#define _VOTING_MACHINE_INSTALLATION_WIZARD_WIDGET_H_

#include <gtkmm.h>
#include <iostream>
#include <list>
#include "Widgets/smartmatic-button.h"
#include <Gui/Widgets/IDCardWidgetVMInstall.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	VotingMachineInstallationWizardWidget
				 *
				 * @brief	Voting machine installation wizard widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class VotingMachineInstallationWizardWidget: public Gtk::Frame
				{
					
					typedef enum
					{
						WIZ_ASK_FOR_ID_INFO,
						WIZ_REQUEST_IDENTITY_CARD,
						WIZ_WRITE_IDENTITY_CARD,
						WIZ_EXTRACT_IDENTITY_CARD,
						WIZ_UMOUNT_DEVICE,
						WIZ_EXTRACT_MEDIA,
						WIZ_INSTALL_MEDIA,
                        WIZ_VERIFY_MEDIA,
						WIZ_FINALIZE,
						WIZ_END

					} WizardStepType;

					public:
						static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

						/**
						 * @fn	VotingMachineInstallationWizardWidget::VotingMachineInstallationWizardWidget();
						 *
						 * @brief	Default constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						VotingMachineInstallationWizardWidget();

						/**
						 * @fn	void VotingMachineInstallationWizardWidget::Initialize();
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void Initialize();

						/**
						 * @fn	void VotingMachineInstallationWizardWidget::Dispose();
						 *
						 * @brief	Dispose of this object, cleaning up any resources it uses.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void Dispose();
						sigc::signal<void> signalHide_detected; ///< The signal hide detected
						
					protected:
						bool on_buttonNext_clicked_signal();
						bool RefreshLabel();


					private:

						std::string directory;  ///< Pathname of the directory
						std::string device; ///< The device
						int counterStep;	///< The counter step
						unsigned int counterImage;  ///< The counter image
						int counterUnmount; ///< The counter unmount
						bool nothingMounted;	///< true to nothing mounted
						unsigned int filesBeforeUnmount;	///< The files before unmount

						// Timer signal connections

						sigc::connection mconn_InsertCard;  ///< The mconn insert card
						sigc::connection mconn_WritingCard; ///< The mconn writing card
						sigc::connection mconn_ExtractCard; ///< The mconn extract card
						sigc::connection connExtract;   ///< The connection extract
						sigc::connection connDetect;	///< The connection detect
						sigc::connection connIdCardFinished;	///< The connection identifier card finished
                        sigc::connection connVerifyData;    ///< The connection verify data
                        sigc::connection connNextButton;    ///< The connection next button
                        sigc::connection connRefreshLabel;    ///< The connection next button


						// Gui elements

						Gdk::Color imageStepColor;  ///< The image step color
						Gdk::Color hboxStepColor;   ///< The hbox step color
						Gtk::VBox vboxPrincipal;	///< The vbox principal
						Gtk::HBox hboxStep; ///< The hbox step
						Gtk::EventBox eventBoxStep; ///< The event box step
						Gtk::HButtonBox hboxButton; ///< The hbox button
						Gtk::Label labelStep;   ///< The label step
						Gtk::Label labelMessage;	///< Message describing the label
						Gtk::Image imageMessage;	///< Message describing the image
						Gtk::Image imageStep;   ///< The image step
						Gtk::EventBox eventBoxImageStep;	///< The event box image step
						//Gtk::Alignment framePrincipal;		
						Smartmatic::GUI::Widgets::SmartmaticButton nextButton;  ///< The next button
						Smartmatic::SAES::GUI::Widgets::IDCardWidgetVMInstall idCardWidget;  ///< The identifier card widget

						// Process step tracking

						std::list<WizardStepType> m_StepSequence;   ///< The step sequence
						std::list<WizardStepType>::const_iterator m_ProcessTracker; ///< The process tracker
						std::vector<std::string> imagePath; ///< Full pathname of the image file
						//list<std::string>::iterator it;

						/**
						 * @brief	Calls on_next_button_clicked after a delay timer.
						 *
						 * @author	Juan Delgado
						 * @date	2/09/2011
						 *
						 * @param 	timer delay for next step
						 */

						void NextStep(int timer);

						/**
						 * @brief	Disconnect al connections.
						 *
						 * @author	Juan Delgado
						 * @date	2/09/2011
						 */

						void DisconnectConnections();


						/**
						 * @fn	bool VotingMachineInstallationWizardWidget::DetectCard ();
						 *
						 * @brief	Gets the detect card.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool DetectCard ();

						/**
						 * @fn	bool VotingMachineInstallationWizardWidget::WriteCard ();
						 *
						 * @brief	Writes the card.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool WriteCard ();

						/**
						 * @fn	bool VotingMachineInstallationWizardWidget::WaitForCardExtraction ();
						 *
						 * @brief	Gets the wait for card extraction.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool WaitForCardExtraction ();

						/**
						 * @fn	bool VotingMachineInstallationWizardWidget::Detect(int time_num);
						 *
						 * @brief	Detects.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool Detect();

						/**
						 * @fn	bool VotingMachineInstallationWizardWidget::Extract(int time_num);
						 *
						 * @brief	Extracts the given time_num.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool Extract();


						/**
						 * @fn	void VotingMachineInstallationWizardWidget::IdCardFinished();
						 *
						 * @brief	Identifier card finished.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void IdCardFinished();

						// Installation process flow

						/**
						 * @fn	void VotingMachineInstallationWizardWidget::mForwardProcess ();
						 *
						 * @brief	Forward process.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void mForwardProcess ();

						// GUI signal handling

						/**
						 * @fn	void VotingMachineInstallationWizardWidget::on_buttonNext_clicked();
						 *
						 * @brief	Handles button next clicked signals.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void on_buttonNext_clicked();

						/**
						 * @brief	Check data in memory path
						 *
						 * @author	Juan Delgado
						 * @date	2/09/2011
						 */
						void checkData();

						/**
						 * @brief	Procces the check data button
						 *
						 * @author	Juan Delgado
						 * @date	2/09/2011
						 */
						void processCheckDataOk();
						void processCheckDataError();
				};
			}
		}
	}
}

#endif // _VOTING_MACHINE_INSTALLATION_WIZARD_WIDGET_H_
