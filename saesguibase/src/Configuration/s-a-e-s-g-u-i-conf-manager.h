/**
 * @file	s-a-e-s-g-u-i-conf-manager.h
 *
 * @brief	Declares a e s g u i conf manager class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _S_A_E_S_G_U_I_CONFIGURATION_MANAGER_H_
#define _S_A_E_S_G_U_I_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Configuration/ConfigurationBase-schema.hxx>
#include "Configuration/configuration-persistence-manager.h"
#include "Widgets/menu-widget-configuration.h"
#include "Widgets/menu-option.h"
#include "Functionalities/saes-menu-option-descriptor.h"
#include "Functionalities/saes-menu-option-type.h"
#include "Configuration/label-configuration.h"
#include <Widgets/WizardWidgetConfiguration.h>
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
			namespace Configuration
			{
				/**
				 * @brief	Manage the language button.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class LanguageButtonInfo
				{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	languageCode	The language code.
						 * @param	imageFile   	The image file.
						 */

						LanguageButtonInfo(std::string languageCode, std::string imageFile)
						{
							code = languageCode;
							path = imageFile;
						}

						/**
						 * @brief	Gets the language code.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The language code.
						 */

						std::string getLanguageCode()
						{
							return code;
						}

						/**
						 * @brief	Gets the image file.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The image file.
						 */

						std::string getImageFile()
						{
							return path;
						}
					private:
						std::string code;   ///< The code
						std::string path;   ///< Full pathname of the file
				};

				/**
				 * @brief	Manager that handles the configuration of all the actions realtes to the SAES GUI. 
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class SAESGUIConfigurationManager
				{
				public:
						enum MachineType
						{
							pollBookMachine,
							votingMachine
						};

						/**
						 * @brief	Gets the current configuration manager.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else.
						 */

						static SAESGUIConfigurationManager *Current();

						/**
						 * @brief	Gets the income passphrase.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The income passphrase.
						 */

						Smartmatic::SAES::Configuration::IncomePassphraseEnum getIncomePassphrase();


						/**
						 * @brief	Gets the wizard widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The wizard widget configuration.
						 */
						std::vector<Smartmatic::GUI::Widgets::WizardWidgetConfiguration> GetFunctionalityWizardConfiguration();

						/**
						 * @brief	Gets the ask for identifier.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getAskForId();

						/**
						 * @brief	Gets sort alphabetically.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if sort alphabetically, false if not.
						 */

						bool GetSortAlphabetically();

						/**
						 * @brief	Gets sort languages alphabetically.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if sort languages alphabetically, false if not.
						 */
						bool GetSortLanguagesAlphabetical();

						/**
						 * @brief	Gets change hour functionality configuration.
						 *
						 * @author	Juan Delgado
						 * @date	29/08/2011
						 *
						 * @return	Change hour functionality configuration
						 */
						Smartmatic::SAES::Configuration::ChangeHourFunctionalityConfiguration GetChangeHourFunctionalitConfiguration();

						/**
						 * @brief	Gets the vote demo functionality configuration
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	the vote demo functionality configuration
						 */
						Smartmatic::SAES::Configuration::VoteDemoFunctionalityConfiguration getVoteDemoFunctionalityConfiguration();


						/**
						 * @brief	Leave the duration fields blank in the close election process.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if the duration fields will be left blank in the close election process.
						 */						 
						bool getDurationLeaveFieldsBlank();						 
						//Smartmatic::SAES::Configuration::CardReaderType::Value getCardReaderType();

						/**
						 * @brief	Gets the printer diagnosis configuration
						 *
						 * @author	Juan Delgado
						 * @date	29/08/2011
						 *
						 * @return	The printer diagnosis configuration
						 */

						Smartmatic::SAES::Configuration::PrinterDiagnosisConfiguration getPrinterDiagnosisConfiguration();

						/**
						 * @brief	Gets the do not check before print diagnostic.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getDoNotCheckBeforePrintDiagnostic();

						/**
						 * @brief	Gets the graphical print for president.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getGraphicalPrintForPresident();

						/**
						 * @brief	Gets the assisted activation by selection.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getAssistedActivationBySelection();

						/**
						 * @brief	Gets the Print Preview Functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	print preview funcionality configuration
						 */
						Smartmatic::SAES::Configuration::PrintPreviewFunctionalityConfiguration getPrintPreviewFunctionalityConfiguration();

						/**
						 * @brief	Gets the recovery clean on correct activation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it clean.
						 */
						bool getRecoveryCleanOnCorrectActivation();

						/**
						 * @brief	Gets the recovery clean on correct activation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it clean.
						 */
						bool getActivatedAfterInsertingCard();

						/**
						 * @brief	Gets the recovery clean on incorrect activation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it clean.
						 */
						bool getRecoveryCleanOnIncorrectActivation();

						/**
						 * @brief	Gets the barcode diagnosis configuration
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The barcode diagnosis configuration
						 */
						Smartmatic::SAES::Configuration::BarcodeDiagnosisConfiguration getBarcodeDiagnosisConfiguration();

						/**
						 * @brief	Gets the PM widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The pm widget configuration
						 */

						Smartmatic::SAES::Configuration::PMWidgetConfiguration & getPMInstallationWidgetConfig();

						/**
						 * @brief	Gets the custom attributes for the presentation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom attributes presentation.
						 */

						std::string getCustomAttributesPresentation();

						/**
						 * @brief	Gets the boolean for show audio check button.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The boolean
						 */
						bool getShowAudioCheckButton();

						/**
						 * @brief	Gets the card activator widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else the card activator widget configuration.
						 */

						Smartmatic::SAES::Configuration::CardActivatorFunctionalityConfiguration* GetCardActivatorWidgetConfiguration();

						/**
						 * @brief	Obatin the functionality to go to authentication exit.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The menu option type to perform this action.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getFunctionalityGoToAuthenticationOnExit(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor);

						/**
						 * @brief	Query if a challenge is enable.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The menu option type to validate the challenge.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getChallengeIsEnable(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor);

						/**
						 * @brief	Gets a challenge for the password source.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	The challenge password source.
						 */

						Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum getChallengePasswordSource(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor);

						/**
						 * @brief	Get a list of disable state
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	The list of disable state
						 */

						Smartmatic::SAES::Configuration::ElectionBlockStatusList::ElectionStatusSequence getDisableStateList(Smartmatic::Functionality::MenuOptionDescriptor menuType);

						/**
						 * @brief	Get the help configuration for the functionality
						 *
						 * @author	Gerardo Hernandez
						 * @date	02/06/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	The help configuration for the functionality
						 */
						Smartmatic::SAES::Configuration::HelpConfiguration getHelpConfiguration(Smartmatic::Functionality::MenuOptionDescriptor menuType);

						/**
						 * @brief	Get if challenge is role
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	true if challenge is role
						 */

						bool getIfChallengeIsRole(Smartmatic::Functionality::MenuOptionDescriptor menuType);

						/**
						 * @brief	Gets if show exit message
						 *
						 * @author	Juan.Delgado
						 * @date	15/08/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	true if show exit message
						 */

						bool GetShowExitMessage(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor);

						/**
						 * @brief	Gets the block memory behavior
						 *
						 * @author	Juan.Delgado
						 * @date	15/08/2011
						 *
						 * @param	type	The menu option type to perform the action.
						 *
						 * @return	The memory block
						 */
						Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior GetBlockMemoryBehavior(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor);


						/**
						 * @brief	Gets the run functionality descriptor.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The run functionality descriptor.
						 */

						Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor getRunFunctionalityDescriptor();

						/**
						 * @brief	Gets the previous view.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getViewPrevious();

						/**
						 * @brief	Gets the height of buttons.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The height of buttons.
						 */

						int getHeightOfButtons();

						/**
						 * @brief	Gets the width of buttons.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The width of buttons.
						 */

						int getWidthOfButtons();

						/**
						 * @brief	Gets the time out.
						 *
						 * @author	IOnay
						 * @date	08/05/2011
						 *
						 * @return	The time to show final message.
						 */

						int getTimeToShowFinalMessage();
						/**
						 * @brief	Gets the brightness diagnosis configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The brightness diagnosis configuration.
						 */

						Smartmatic::SAES::Configuration::BrightnessDiagnosisConfiguration& getBrightnessDiagnosisConfiguration();

						/**
						 * @brief	Gets the time delay buttons.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The time delay buttons.
						 */

						int getTimeDelayButtons();


						/**
						 * @brief	Gets the time delay buttons.
						 *
						 * @author	Gerardo Hernandez
						 * @date	28/04/2011
						 *
						 * @return the boolean value to indicate to the functionalities reload frame.
						 */
						bool GetForceToLoadFrame ();

						/**
						 * @brief	Gets send barcode configuration on reconnect widget.
						 *
						 * @author	Juan delgado
						 * @date	24/08/2011
						 *
						 * @return True if send configuration
						 */
						bool GetSendBarcodeConfigurationOnReconnectWidget();

						/**
						 * @brief	Gets the time out card.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The time out card.
						 */

						int getTimeOutCard();

						/**
						 * @brief	Gets mark card as used.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getMarkCardAsUsed();

						/**
						 * @brief	Gets the show confirmation buttons for activation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getShowConfirmationButtons();

						/**
						 * @brief	Gets the show confirmation buttons for recovery.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */
						bool getShowRecoveryConfirmationButtons();
						/**
						 * @brief	Gets the check sum fail timer message.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The check sum fail timer message.
						 */

						int getCheckSumFailTimerMessage();

						/**
						 * @brief	Gets the screen reader diagnosis timeout.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The screen reader diagnosis timeout.
						 */

						unsigned int getSCReaderDiagnosisTimeout();

						/**
						 * @brief	Gets the pm instalation sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The pm instalation sound.
						 */

						std::string getPMInstalationSound();

						/**
						 * @brief	Gets the virtual memory instalation sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The virtual memory instalation sound.
						 */

						std::string getVMInstalationSound();

						/**
						 * @brief	Gets the authentication valid password sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The authentication valid password sound.
						 */

						std::string getAuthenticationValidPasswordSound();

						/**
						 * @brief	Gets the authentication invalid password sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The authentication invalid password sound.
						 */

						std::string getAuthenticationInvalidPasswordSound();

						/**
						 * @brief	Gets the voting experience sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience sound.
						 */

						std::string getVotingExperienceSound();						

						/**
						 * @brief	Gets the ballot option select sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The ballot option select sound.
						 */

						std::string getBallotOptionSelectSound();

						/**
						 * @brief	Gets the party select sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party select sound.
						 */

						std::string getPartySelectSound();

						/**
						 * @brief	Gets the diagnosis sound.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The diagnosis sound.
						 */

						std::string getDiagnosisSound();


						/**
						 * @brief	Gets the open election poll worker label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The open election poll worker label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetOpenElectionPollWorkerLabelConfiguration();

						/**
						 * @brief	Gets the statistic functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The statistic functionality configuration.
						 */

						Smartmatic::SAES::Configuration::StatisticFunctionalityConfiguration& GetStatisticFunctionalityConfiguration();

						/**
						 * @brief	Gets the open election functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The open election functionality configuration.
						 */

						Smartmatic::SAES::Configuration::OpenElectionFunctionalityConfiguration& GetOpenElectionFunctionalityConfiguration();

						/**
						 * @brief	Gets the close election functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The close election functionality configuration.
						 */

						Smartmatic::SAES::Configuration::CloseElectionFunctionalityConfiguration& GetCloseElectionFunctionalityConfiguration();

						/**
						 * @brief	Gets the activaction consolidation functionality configuration.
						 *
						 * @author	Juan Delgado
						 * @date	06/09/2011
						 *
						 * @return	The activation consolidation functionality configuration.
						 */
						Smartmatic::SAES::Configuration::ActivationConsolidationFunctionalityConfiguration GetActivationConsolidationFunctionalityConfiguration();

						/**
						 * @brief	Gets the incident report functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The incident report functionality configuration.
						 */

						Smartmatic::SAES::Configuration::IncidentReportFunctionalityConfiguration GetIncidentReportFunctionalityConfiguration();

						/**
						 * @brief	Gets the log report functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The log report functionality configuration.
						 */

						Smartmatic::SAES::Configuration::LogReportFunctionalityConfiguration GetLogReportFunctionalityConfiguration();

						/**
						 * @brief	Gets the minimun notes to register configuration
						 *
						 * @author	Juan.Delgado
						 * @date	06/08/2011
						 *
						 * @return	The minimun ammount of notes
						 */
						unsigned int GetMinimunNotesToRegisterConfiguration();


						/**
						 * @brief	Gets the poll worker register functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The poll worker register functionality configuration.
						 */

						Smartmatic::SAES::Configuration::PollWorkerRegisterFunctionalityConfiguration GetPollWorkerRegisterFunctionalityConfiguration();

						/**
						 * @brief Method getter PollWorker register configuration by type
						 * @param type type
						 * @return config
						 * @author Yadickson Soto
						 * @date 03-05-2012
						 */
						Smartmatic::SAES::Configuration::IDConfig getPollWorkerIDConfiguration(Smartmatic::SAES::Voting::PBReports::WorkerMemberType type);

						/**
						 * @brief	Gets the vote consolidation functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The vote consolidation functionality configuration.
						 */

						Smartmatic::SAES::Configuration::VoteConsolidationFunctionalityConfiguration GetVoteConsolidationFunctionalityConfiguration();

						/**
						 * @brief	Gets the voting experience validation screens functionality configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience validation screens functionality configuration.
						 */

						Smartmatic::SAES::Configuration::VotingExperienceValidationScreensFunctionalityConfiguration GetVotingExperienceValidationScreensFunctionalityConfiguration();

						/**
						 * @brief	Gets the themes configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The themes configuration.
						 */

						Smartmatic::SAES::Configuration::ThemesConfiguration& GetThemesConfiguration();

						/**
						 * @brief	Gets the official theme configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The official theme configuration.
						 */

						Smartmatic::SAES::Configuration::OfficialThemeConfiguration& GetOfficialThemeConfiguration();

						/**
						 * @brief	Gets the demo theme configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The demo theme configuration.
						 */

						Smartmatic::SAES::Configuration::DemoThemeConfiguration& GetDemoThemeConfiguration();

						/**
						 * @brief	Gets the recovery theme configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The recovery theme configuration.
						 */

						Smartmatic::SAES::Configuration::RecoveryThemeConfiguration& GetRecoveryThemeConfiguration();

						/**
						 * @brief	Gets the voting window button name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting window button name.
						 */

						std::string GetVotingWindowButtonName();

						/**
						 * @brief	Gets the voting experience party eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience party eventbox name.
						 */

						std::string GetVotingExperiencePartyEventboxName();

						/**
						 * @brief	Gets the voting experience window name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience window name.
						 */

						std::string GetVotingExperienceWindowName();

						/**
						 * @brief	Gets the voting experience ballot option eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience ballot option eventbox name.
						 */

						std::string GetVotingExperienceBallotOptionEventboxName();

						/**
						 * @brief	Gets the card activator functionality message name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The card activator functionality message name.
						 */

						std::string GetCardActivatorFunctionalityMessageName();

						/**
						 * @brief	Gets the card activator message eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The card activator message eventbox name.
						 */

						std::string GetCardActivatorMessageEventboxName();

						/**
						 * @brief	Gets the card activator functionality eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The card activator functionality eventbox name.
						 */

						std::string GetCardActivatorFunctionalityEventboxName();

						/**
						 * @brief	Gets the card activator values eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The card activator values eventbox name.
						 */

						std::string GetCardActivatorValuesEventboxName();

						/**
						 * @brief	Gets the card activator functionality center frame name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The card activator functionality center frame name.
						 */

						std::string GetCardActivatorFunctionalityCenterFrameName();

						/**
						 * @brief	Gets the eventbox step barcode name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox step barcode name.
						 */

						std::string GetEventboxStepBarcodeName();

						/**
						 * @brief	Gets the eventbox step barcode title name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox step barcode title name.
						 */

						std::string GetEventboxStepBarcodeTitleName();

						/**
						 * @brief	Gets the eventbox step card title name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox step card title name.
						 */

						std::string GetEventboxStepCardTitleName();

						/**
						 * @brief	Gets the vote demo functionality message name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The vote demo functionality message name.
						 */

						std::string GetVoteDemoFunctionalityMessageName();

						/**
						 * @brief	Gets the stand in label name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The stand in label name.
						 */

						std::string GetStandInLabelLabelName();

						/**
						 * @brief	Gets the stand in label event name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The stand in label event name.
						 */

						std::string GetStandInLabelEventName();

						/**
						 * @brief	Gets the voting experience select ballot option widget name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience select ballot option widget name.
						 */

						std::string GetVotingExperienceSelectBallotOptionWidgetName();

						/**
						 * @brief	Gets the change language message wigdet eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The change language message wigdet eventbox name.
						 */

						std::string GetChangeLanguageMessageWigdetEventboxName();

						/**
						 * @brief	Gets the custom attribute combo selections widget title name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom attribute combo selections widget title name.
						 */

						std::string GetCustomAttributeComboSelectionsWidgetTitleName();

						/**
						 * @brief	Gets the custom attribute counter widget title name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom attribute counter widget title name.
						 */

						std::string GetCustomAttributeCounterWidgetTitleName();

						/**
						 * @brief	Gets the eventbox choose widget frame name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox choose widget frame name.
						 */

						std::string GetEventboxChooseWidgetFrameName();

						/**
						 * @brief	Gets the voting experience party widget name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience party widget name.
						 */

						std::string GetVotingExperiencePartyWidgetName();

						/**
						 * @brief	Gets the party widget eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party widget eventbox name.
						 */

						std::string GetPartyWidgetEventboxName();

						/**
						 * @brief	Gets the eventbox image step installation wizard name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox image step installation wizard name.
						 */

						std::string GetEventboxImageStepInstallationWizardName();

						/**
						 * @brief	Gets the eventbox step installation wizard name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The eventbox step installation wizard name.
						 */

						std::string GetEventboxStepInstallationWizardName();

						/**
						 * @brief	Gets the parent keypad eventbox name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The parent keypad eventbox name.
						 */

						std::string GetParentKeypadEventboxName();

						/**
						 * @brief	Gets the information frame name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The information frame name.
						 */

						std::string GetInfoFrameName();

						/**
						 * @brief	Gets the voting window button demo name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting window button demo name.
						 */

						std::string GetVotingWindowButtonDemoName();

						/**
						 * @brief	Gets the voting experience party eventbox demo name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience party eventbox demo name.
						 */

						std::string GetVotingExperiencePartyEventboxDemoName();

						/**
						 * @brief	Gets the voting experience window demo name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience window demo name.
						 */

						std::string GetVotingExperienceWindowDemoName();

						/**
						 * @brief	Gets the voting experience ballot option eventbox demo name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience ballot option eventbox demo name.
						 */

						std::string GetVotingExperienceBallotOptionEventboxDemoName();

						/**
						 * @brief	Gets the check sum fail option.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The check sum fail option.
						 */

						Smartmatic::SAES::Configuration::CheckSumFailOption::Value getCheckSumFailOption();

						/**
						 * @brief	Gets the voting window button recovery name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting window button recovery name.
						 */

						std::string GetVotingWindowButtonRecoveryName();

						/**
						 * @brief	Gets the voting experience party eventbox recovery name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience party eventbox recovery name.
						 */

						std::string GetVotingExperiencePartyEventboxRecoveryName();

						/**
						 * @brief	Gets the voting experience window recovery name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience window recovery name.
						 */

						std::string GetVotingExperienceWindowRecoveryName();

						/**
						 * @brief	Gets the voting experience ballot option eventbox recovery name.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience ballot option eventbox recovery name.
						 */

						std::string GetVotingExperienceBallotOptionEventboxRecoveryName();			

						/**
						 * @brief	Gets the minimum demo counter to allow activation.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The minimum demo counter to allow activation.
						 */

						unsigned int getMinimumDemoCounterToAllowActivation();

						/**
						 * @brief	Gets the minimum demo counter to allow recovery.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The minimum demo counter to allow recovery.
						 */

						unsigned int getMinimumDemoCounterToAllowRecovery();

						/**
						 * @brief	Gets the touch screen calibration number of points.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The touch screen calibration number of points.
						 */

						int getTouchScreenCalibrationNumberOfPoints();

						/**
						 * @brief	Gets all diagnosis printer wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis printer wait time.
						 */

						int getAllDiagnosisPrinterWaitTime();

						/**
						 * @brief	Gets all diagnosis barcode wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis barcode wait time.
						 */

						int getAllDiagnosisBarcodeWaitTime();

						/**
						 * @brief	Gets all diagnosis smartcard wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis smartcard wait time.
						 */

						int getAllDiagnosisSmartcardWaitTime();

						/**
						 * @brief	Gets all diagnosis calibration wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis calibration wait time.
						 */

						int getAllDiagnosisCalibrationWaitTime();

						/**
						 * @brief	Gets all diagnosis contrast wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis contrast wait time.
						 */

						int getAllDiagnosisContrastWaitTime();

						/**
						 * @brief	Gets all diagnosis alarm wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis alarm wait time.
						 */

						int getAllDiagnosisAlarmWaitTime();

						/**
						 * @brief	Gets all diagnosis flash wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis flash wait time.
						 */

						int getAllDiagnosisFlashWaitTime();

						/**
						 * @brief	Gets all diagnosis printer wait time on ok.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis printer wait time on ok.
						 */

						int getAllDiagnosisPrinterWaitTimeOnOk();

						/**
						 * @brief	Gets all diagnosis printer wait time on cancel.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis printer wait time on cancel.
						 */

						int getAllDiagnosisPrinterWaitTimeOnCancel();

						/**
						 * @brief	Gets all diagnosis calibration wait time on ok.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis calibration wait time on ok.
						 */

						int getAllDiagnosisCalibrationWaitTimeOnOk();

						/**
						 * @brief	Gets all diagnosis contrast wait time on ok.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis contrast wait time on ok.
						 */

						int getAllDiagnosisContrastWaitTimeOnOk();

						/**
						 * @brief	Gets the automatic diagnosis printer wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis printer wait time.
						 */

						int getAutoDiagnosisPrinterWaitTime();

						/**
						 * @brief	Gets the automatic diagnosis barcode wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis barcode wait time.
						 */

						int getAutoDiagnosisBarcodeWaitTime();

						/**
						 * @brief	Gets the automatic diagnosis smartcard wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis smartcard wait time.
						 */

						int getAutoDiagnosisSmartcardWaitTime();

						/**
						 * @brief	Gets the automatic diagnosis alarm wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis alarm wait time.
						 */

						int getAutoDiagnosisAlarmWaitTime();

						/**
						 * @brief	Gets the automatic diagnosis flash wait time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis flash wait time.
						 */

						int getAutoDiagnosisFlashWaitTime();

						/**
						 * @brief	Gets waiting card widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	waiting card widget configuratio
						 */
						Smartmatic::SAES::Configuration::WaitingForCardWindowConfiguration getWaitingForCardWindowConfiguration();

						/**
						 * @brief	Gets the enable gtk printing.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getEnableGtkPrinting();

						/**
						 * @brief	Gets the language list.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The language list.
						 */

						std::vector<LanguageButtonInfo> getLanguageList();

						/**
						 * @brief	Gets all diagnosis list.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	all diagnosis list.
						 */

						std::vector<Smartmatic::SAES::Configuration::DiagnosticType> getAllDiagnosisList();
						//std::vector<std::string> getAutoDiagnosisList();

						/**
						 * @brief	Gets the automatic diagnosis list.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The automatic diagnosis list.
						 */

						std::vector<Smartmatic::SAES::Configuration::DiagnosticType> getAutoDiagnosisList();

						/**
						 * @brief	Gets the printing widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The printing widget configuration.
						 */

						Smartmatic::SAES::Configuration::ReportPrintingWidgetConfiguration GetPrintingWidgetConfiguration ();

						/**
						 * @brief	Gets the confirmation window configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The confirmation window configuration.
						 */

						Smartmatic::SAES::Configuration::ConfirmationWindowConfiguration GetConfirmationWindowConfiguration();

						/**
						 * @brief	Gets the custom atributtes window configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom atributtes window configuration.
						 */

						Smartmatic::SAES::Configuration::CustomAtributtesWindowConfiguration GetCustomAtributtesWindowConfiguration();

						/**
						 * @brief	Gets the voting experience label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting experience label configuration.
						 */

						Smartmatic::SAES::Configuration::VotingExperienceLabelConfiguration GetVotingExperienceLabelConfiguration();

						/**
						 * @brief	Gets the ballot option selection configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The ballot option selection configuration.
						 */

						Smartmatic::SAES::Configuration::BallotOptionSelectionConfiguration& GetBallotOptionSelectionConfiguration();

						/**
						 * @brief	Gets the referendum selection configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The referendum selection configuration.
						 */

						Smartmatic::SAES::Configuration::ReferendumConfiguration& GetReferendumConfiguration();



						/**
						 * @brief	Gets the ballot option widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The ballot option widget configuration.
						 */

						Smartmatic::SAES::Configuration::BallotOptionWidgetConfiguration GetBallotOptionWidgetConfiguration();

						/**
						 * @brief	Gets the detect card extraction.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool getDetectCardExtraction();

						/**
						 * @brief	Gets the number of extractions before stop.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The number of extractions before stop.
						 */

						unsigned int getNumberOfExtractionsBeforeStop();

						/**
						 * @brief	Gets the voting window configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting window configuration.
						 */

						Smartmatic::SAES::Configuration::VotingWindowConfiguration& GetVotingWindowConfiguration();

						/**
						 * @brief	Gets the party widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party widget configuration.
						 */

						Smartmatic::SAES::Configuration::PartyWidgetConfiguration& GetPartyWidgetConfiguration();

						/**
						 * @brief	Gets the party selection configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party selection configuration.
						 */

						Smartmatic::SAES::Configuration::PartySelectionConfiguration& GetPartySelectionConfiguration();

						/**
						 * @brief	Gets a machine widget configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The type.
						 *
						 * @return	null if it fails, else the machine widget configuration.
						 */

						Smartmatic::GUI::Widgets::MenuWidgetConfiguration* GetMachineWidgetConfiguration(MachineType type);

						/**
						 * @brief	Gets a menu option configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	type	The machine type.
						 *
						 * @return	The menu option configuration.
						 */

						std::vector<Smartmatic::GUI::Widgets::MenuOption> GetMenuOptionConfiguration();

						/**
						 * @brief	Gets a menu option configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	option The xml menu option.
						 *
						 * @return	The menu option configuration.
						 */
						Smartmatic::GUI::Widgets::MenuOption GetSMMTMenuOptionFromXMLMenuOption(Smartmatic::SAES::Configuration::MenuOption option);

						/**
						 * @brief	Gets the configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else the configuration.
						 */

						std::auto_ptr<Smartmatic::SAES::Configuration::SaesGUIConfiguration> *getConfiguration();

						/**
						 * @brief	Loads the default configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						void LoadDefault();

						/**
						 * @brief	Gets the block memory behavior menu
						 *
						 * @author	Juan.Delgado
						 *
						 * @return 	The memory block behavior
						 */

						Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior GetBlockMemoryBehaviorMenu();

						/*Label configurations*/

						/**
						 * @brief	Gets the custom atributtes window header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom atributtes window header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCustomAtributtesWindowHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the custom atributtes window bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom atributtes window bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCustomAtributtesWindowBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the custom atributtes window center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The custom atributtes window center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCustomAtributtesWindowCenterLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the confirmation window bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The confirmation window bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetConfirmationWindowBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the confirmation window header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The confirmation window header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetConfirmationWindowHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the party selection window bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party selection window bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetPartySelectionWindowBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the party selection window header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party selection window header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetPartySelectionWindowHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the ballot option selection window bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The ballot option selection window bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetBallotOptionSelectionWindowBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the ballot option selection window header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The ballot option selection window header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetBallotOptionSelectionWindowHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the selection language header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The selection language header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSelectionLanguageHeaderLabelConfiguration(); //LISTO

						/**
						 * @brief	Gets the selection language bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The selection language bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSelectionLanguageBottomLabelConfiguration(); //LISTO

						/**
						 * @brief	Gets the selection language confirmation header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The selection language confirmation header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSelectionLanguageConfirmationHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the selection language confirmation bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The selection language confirmation bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSelectionLanguageConfirmationBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the selection language confirmation center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The selection language confirmation center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSelectionLanguageConfirmationCenterLabelConfiguration(); //LISTO

						/**
						 * @brief	Gets the Title label configuration for card activator statistics.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	the Title label configuration for card activator statistics.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCardActivatorStatisticsTitleLabelConfiguration(); 					 

						/**
						 * @brief	Gets the Title label configuration for card recovery statistics.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	the Title label configuration for card recovery statistics.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCardRecoveryStatisticsTitleLabelConfiguration(); 					 

						/*Label configurations*/

						/**
						 * @brief	Gets the preview vote upper label in waiting card widget .
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The preview vote upper label in waiting card widget.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetPreviewVoteLabelConfiguration();//LISTO
						
						Smartmatic::SAES::Configuration::ButtonConfiguration getPreviewVoteButtonConfiguration();

						/**
						 * @brief	Gets the Title label configuration for vote consolidation statistics.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	the Title label configuration for vote consolidation statistics.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetVoteConsolidationStatisticsTitleLabelConfiguration(); 					 

						/**
						 * @brief	Gets the super white header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the super white center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteCenterLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the super white bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the super white confirmation header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white confirmation header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteConfirmationHeaderLabelConfiguration();

						/**
						 * @brief	Gets the super white confirmation bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white confirmation bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteConfirmationBottomLabelConfiguration();

						/**
						 * @brief	Gets the super white confirmation center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The super white confirmation center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetSuperWhiteConfirmationCenterLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the contest white selection header label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The contest white selection header label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetContestWhiteSelectionHeaderLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the contest white selection bottom label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The contest white selection bottom label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetContestWhiteSelectionBottomLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the contest white selection center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The contest white selection center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetContestWhiteSelectionCenterLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the welcome contest center label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The welcome contest center label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetWelcomeContestCenterLabelConfiguration();//LISTO

						/**
						 * @brief	Gets the diagnosis label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The diagnosis label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetDiagnosisLabelConfiguration();
						/**
						 * @brief Method getter diagnostic footer config
						 * @return diagnostic footer config
						 * @date 08/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getDiagnosisFooterLabelConfiguration();
						/**
						 * @brief Method getter diagnostic result error config
						 * @return diagnostic result error config
						 * @date 08/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getResultErrorLabelConfiguration();
						/**
						 * @brief Method getter is show footer in auto diagnosis
						 * @return true is show footer in auto diagnosis
						 * @date 08/05/2012
						 * @author Yadickson Soto
						 */
						bool getShowFooterInAutoDiagnosis();

						/**
						 * @brief	Gets the diagnosis label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The diagnosis label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration  GetFillAssistedInforConfiguration();

						Smartmatic::GUI::Configuration::LabelConfiguration GetNameLabelConfiguration();

						/**
						 * @brief	Gets the exit message label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The exit message label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration  GetExitMessageLabelConfiguration();

						/**
						 * @brief	Gets the loading ballots label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The loading ballots label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetLoadingBallotsLabelConfiguration();

						/**
						 * @brief	Gets the check sum label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The check sum label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCheckSumLabelConfiguration();

						/**
						 * @brief	Gets the title statistics label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Title Statistics label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration GetTitleStatisticsLabelConfiguration();

						/**
						 * @brief	Gets the stats statistics label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Stats Statistics label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration GetStatsStatisticsLabelConfiguration();

						/**
						 * @brief	Gets the Interrupt voting experience message label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Interrupt voting experience message label configuration.
						 */						 
						Smartmatic::GUI::Configuration::LabelConfiguration GetInterrupVotingExperienceMessageLabelConfiguration();

						/**
						 * @brief	Gets the Interrupt voting experience cancel label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Interrupt voting experience cancel label configuration.
						 */						 
						Smartmatic::GUI::Configuration::LabelConfiguration GetInterrupVotingExperienceCancelLabelConfiguration();

						/**
						 * @brief	Gets the report list title label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The report list title label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetReportListTitleLabelConfiguration();

						/**
						 * @brief	Gets the progress label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The progress label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetProgressLabelConfiguration();

						/**
						 * @brief	Gets the composite message label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The composite message label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetCompositeMsgLabelConfiguration();

						/**
						 * @brief	Gets the file item label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The file item label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetFileItemLabelConfiguration();

						/**
						 * @brief	Method getter the authentication password label configuration.
						 * @author	Yadickson Soto
						 * @date	24/04/2012
						 * @return	The authentication password label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getAuthenticationPasswordLabelConfiguration();
						/**
						 * @brief	Method getter the authentication alarm label configuration.
						 * @author	Yadickson Soto
						 * @date	24/04/2012
						 * @return	The authentication alarm label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getAuthenticationAlarmLabelConfiguration();
						/**
						 * @brief	Method getter the authentication info label configuration.
						 * @author	Yadickson Soto
						 * @date	24/04/2012
						 * @return	The authentication info label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getAuthenticationInfoLabelConfiguration();
						/**
						 * @brief	Method getter the authentication voting info label configuration.
						 * @author	Yadickson Soto
						 * @date	24/04/2012
						 * @return	The authentication voting info label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getAuthenticationVotingInfoLabelConfiguration();

						/**
						 * @brief	Gets the voting widget label child label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting widget label child label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWidgetLabelChildLabelConfiguration(); //Listo

						/**
						 * @brief	Gets the voting widget top child label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting widget top child label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWidgetTopChildLabelConfiguration(); //listo

						/**
						 * @brief	Gets the voting widget bottom child label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting widget bottom child label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWidgetBottomChildLabelConfiguration(); //listo

						/**
						 * @brief	Gets the voting widget number child label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting widget number child label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWidgetNumberChildLabelConfiguration(); //Listo

						/**
						 * @brief	Gets the voting widget party selection label child label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting widget party selection label child label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWidgetPartySelectionLabelChildLabelConfiguration();

						/**
						 * @brief	Gets the voting window end messagelabel configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The voting window end messagelabel configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetVotingWindowEndMessagelabelConfig();
						/**
						 * @brief	Method getter beid card widget configuration
						 * @author	Yadickson Soto
						 * @date	23/04/2012
						 * @return	beid card widget configuration
						 */
						Smartmatic::SAES::Configuration::BEIDCardWidgetConfiguration & getBEIDCardWidgetConfiguration();
						/**
						 * @brief	Method getter id card process widget configuration
						 * @author	Yadickson Soto
						 * @date	04/05/2012
						 * @return	id card process widget configuration
						 */
						Smartmatic::SAES::Configuration::IDCardProcessConfiguration & getIDCardProcessConfiguration();
						/**
						 * @brief	Method getter beid card widget title configuration
						 * @author	Yadickson Soto
						 * @date	23/04/2012
						 * @return	beid card widget configuration
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getBEIDCardWidgetTitleErrorConfiguration();
						/**
						 * @brief	Method getter beid card widget title configuration
						 * @author	Yadickson Soto
						 * @date	23/04/2012
						 * @return	beid card widget configuration
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getBEIDCardWidgetTextErrorConfiguration();
						/**
						 * @brief	Method getter beid card widget timeout error configuration
						 * @return  timeout error
						 * @author	Yadickson Soto
						 * @date	24/04/2012
						 * @return	beid card widget configuration
						 */
						unsigned int getBEIDCardWidgetTimeoutError();

						/**
						 * @brief	Gets the virtual memory loging message label.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The virtual memory loging message label.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetVMLogingMessageLabel();

						/**
						 * @brief	Gets the party null label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The party null label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration& GetPartyNullLabelConfiguration();

						/*Form common control*/

						/**
						 * @brief	Gets the empty window title form configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The empty window title form configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetEmptyWindowTitleFormConfiguration();

						/**
						 * @brief	Gets the form titles labels configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The form titles labels configuration.
						 */

						::Smartmatic::SAES::Configuration::FormsTitleLabelConfigurations& GetFormTitlesLabelsConfiguration();

						/**
						 * @brief	Gets the unable functionality label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The unable functionality label configuration.
						 */

						Smartmatic::GUI::Configuration::LabelConfiguration GetUnableFunctionalityLabelConfiguration();
						/**
						 * @brief	Gets the scan message label configuration.
						 *
						 * @author	Yadickson Soto
						 * @date	27/03/2012
						 *
						 * @return	The scan message label configuration.
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration GetScanMessageLabelConfiguration();

						/**
						 * @brief	Gets the unable message close time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The unable message close time.
						 */

						int GetUnableMessageCloseTime();

						/**
						 * @brief	Gets the exit functinoality message close time.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The exit functionality message close time.
						 */

						int GetExitFunctionalityMessageCloseTime();

						/**
						 * @brief	Gets the form messages labels configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The form messages labels configuration.
						 */

						::Smartmatic::SAES::Configuration::FormsMessagesLabelConfigurations& GetFormMessagesLabelsConfiguration();

						/**
						 * @brief	Gets the common controls form configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The common controls form configuration.
						 */

						::Smartmatic::SAES::Configuration::FormsCommonControlsConfigurations& GetCommonControlsFormConfiguration();

						 /**
						 * @brief	Gets the Activated card statistics for the Card Activator Functionality
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Activated card statistics for the Card Activator Functionality
						 */
						::Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration getCardActivationStatisticsConfiguration();

						/**
						 * @brief	Gets the Recovery card statistics for the Card Recovery Functionality
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Recovery card statistics for the Card Recovery Functionality
						 */
						::Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration getCardRecoveryStatisticsConfiguration();


						/**
						 * @brief	Gets the Color Configuration for the Card Activator statistics title
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Color Configuration for the Card Activator statistics title
						 */
						Smartmatic::SAES::Configuration::ColorConfiguration getCardActivatorStatisticsTitleColor();
						/**
						 * @brief	Gets the Color Configuration for the Card Recovery statistics title
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Color Configuration for the Card Recovery statistics title
						 */
						Smartmatic::SAES::Configuration::ColorConfiguration getCardRecoveryStatisticsTitleColor();
						/**
						 * @brief	Gets the Color Configuration for the Vote Consolidation statistics title
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Color Configuration for the Vote Consolidation statistics title
						 */
						Smartmatic::SAES::Configuration::ColorConfiguration getVoteConsolidationStatisticsTitleColor();
						/**
						 * @brief	Gets the Color Configuration for the Assisted Activation preview title
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Color Configuration for the the Assisted Activation preview title
						 */
						Smartmatic::SAES::Configuration::ColorConfiguration getAssistedActivationPreviewTitleColor();						 
						/**
						 * @brief	Gets the Color Configuration for the Assisted Activation preview content
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	The Color Configuration for the Assisted Activation preview content
						 */
						Smartmatic::SAES::Configuration::ColorConfiguration getAssistedActivationPreviewContentColor();						 
						
						Smartmatic::SAES::Configuration::VMInstallationWidgetConfiguration GetVMInstallationConfiguration();

						Smartmatic::SAES::Configuration::ShowBeidEntryTypeConfiguration GetShowBeidEntry();

						bool GetBeidShowIdCard();

						bool GetLaunchThreadBeid();

						bool GetBeidCardShowRemoveMessage();

						bool GetPMInstallationWidgetShowPrintPasswordButton();

						bool getCloseVotationRequestForId();

						int getCloseVotationMinimumOfficialsActivationForConfirmation();

						bool getCloseVotationShowConfirmationMessageWhenClosing();

						bool getInitializationWindowRequestForId();

						Smartmatic::SAES::Configuration::ContingencyCardWidgetConfiguration getContingencyCardWidgetConfiguration ();

						Smartmatic::SAES::Configuration::MemoryStateWidgetConfiguration & getMemoryStateWidgetConfiguration();

						Smartmatic::GUI::Configuration::LabelConfiguration getMemoryStateWidgetTextConfiguration();

						Smartmatic::SAES::Configuration::HelpWidgetConfiguration & getHelpWidgetConfiguration();

						Smartmatic::SAES::Configuration::NecessaryDevicesConfiguration::DeviceConfigurationSequence getDeviceConfiguration (Smartmatic::Functionality::MenuOptionDescriptor menuType);

						/**
						 * @brief	Gets the Automatic Diagnostic Configuration
						 *
						 * @author	Freddy Gomez
						 * @date	21/05/2011
						 *
						 * @return	The reference to the Automatic Diagnostic Configuration
						 */
						Smartmatic::SAES::Configuration::AutomaticWindowConfiguration& GetAutomaticWindowConfiguration();

						Smartmatic::GUI::Configuration::LabelConfiguration GetReferendumHeaderLabelConfiguration();
						Smartmatic::GUI::Configuration::LabelConfiguration GetReferendumBottomLabelConfiguration();
						Smartmatic::GUI::Configuration::LabelConfiguration GetReferendumQuestionLabelConfiguration();
						Smartmatic::GUI::Configuration::LabelConfiguration GetReferendumBallotsLabelConfiguration();

						/**
						 * @brief	Converts an xmlLabelConfiguration to a label configuration.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	xmlLabelConfiguration	The xml label configuration.
						 *
						 * @return	.
						 */

						static Smartmatic::GUI::Configuration::LabelConfiguration ConvertToLabelConfiguration(Smartmatic::SAES::Configuration::XMLLabelConfiguration xmlLabelConfiguration);

						/**
						 * @brief Method getter polling card configuration
						 * @return polling card configuration
						 * @date 16/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::PollingCardConfiguration & getPollingCardConfiguration();
						/**
						 * @brief Method getter alarm box monitor configuration
						 * @return alarm box monitor configuration
						 * @date 16/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::AlarmBoxMonitorConfiguration & getAlarmBoxMonitorConfiguration();

						Smartmatic::SAES::Configuration::StartConfiguration & getStartConfiguration();

						bool getContingencyCardEnabled ();

						void addSkipAutoDiagnosis(Smartmatic::SAES::Configuration::DiagnosticType type);

						/**
						 * @brief method getter pivot config for principal
						 * @param principalCount principal count candidates
						 * @return pivot config
						 * @date 14/03/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::PivotConfig getPivotConfig(unsigned int principalCount);
						/**
						 * @brief method getter title config for contingency card generation widget
						 * @return label configuration
						 * @date 20/03/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration  GetContingencyTitleLabelConfiguration();
						/**
						 * @brief method getter text config for contingency card generation widget
						 * @return label configuration
						 * @date 20/03/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration  GetContingencyTextLabelConfiguration();
						/**
						 * @brief method check pollworker register
						 * @return true is all pollworker register
						 * @date 20/03/2012
						 * @author Yadickson Soto
						 */
						bool checkPollworkerRegister();
						/**
						 * @brief method getter voting for disabled functionality configuration
						 * @return voting for disabled functionality configuration
						 * @date 18/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::VotingForDisabledFunctionalityConfiguration & getVotingForDisabledFunctionalityConfiguration();
						/**
						 * @brief method getter police note functionality configuration
						 * @return police note functionality configuration
						 * @date 25/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::PoliceNoteRegisterFunctionalityConfiguration & getPoliceNoteRegisterFunctionalityConfiguration();
						/**
						 * @brief method getter data utils validator functionality configuration
						 * @return data utils validator functionality configuration
						 * @date 18/07/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::DataUtilsValidatorFunctionalityConfiguration & getDataUtilsValidatorFunctionalityConfiguration();
						/**
						 * @brief method getter close note register functionality configuration
						 * @return close note register functionality configuration
						 * @date 24/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::CloseNoteRegisterFunctionalityConfiguration & getCloseNoteRegisterFunctionalityConfiguration();
						/**
						 * @brief method getter question title config
						 * @return label configuration
						 * @date 18/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getVotingForDisabledQuestionTitleConfiguration();
						/**
						 * @brief method getter info title config
						 * @return label configuration
						 * @date 22/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getVotingForDisabledInfoTitleConfiguration();
						/**
						 * @brief method getter info id config
						 * @return label configuration
						 * @date 22/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getVotingForDisabledInfoIDConfiguration();
						/**
						 * @brief method getter info text config
						 * @return label configuration
						 * @date 22/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getVotingForDisabledInfoTextConfiguration();
						/**
						 * @brief method getter info error config
						 * @return label configuration
						 * @date 22/05/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getVotingForDisabledInfoErrorConfiguration();
						/**
						 * @brief method getter block diagnosis config
						 * @return label configuration
						 * @date 12/06/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getBlockDiagnosticTitle();
						/**
						 * @brief method getter voting experience configuration
						 * @return voting experience configuration
						 * @date 14/06/2012
						 * @author Yadickson Soto
						 */
						Smartmatic::SAES::Configuration::VotingExperienceConfiguration & getVotingExperienceConfiguration();
						/**
						 * @brief	Method getter label configuration title remove contingency card
						 * @author	Fsilva
						 * @date	02/08/2012
						 * @return	label configuration
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getRemoveCardTitle();
						/**
						 * @brief	Method getter label configuration title remove contingency card
						 * @author	Fsilva
						 * @date	02/08/2012
						 * @return	label configuration
						 */
						Smartmatic::GUI::Configuration::LabelConfiguration getRemoveCardText();

				protected:

						/**
						 * @brief	Default constructor.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						SAESGUIConfigurationManager();

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						~SAESGUIConfigurationManager();

						/**
						 * @brief	Initializes this object.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						void Initialize();

						std::auto_ptr<Smartmatic::SAES::Configuration::SaesGUIConfiguration> *configuration;	///< The configuration instance.

						/**
						 * @brief	Gets an inner options with the given xml.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param	xmlMenuOption	The xml menu option.
						 *
						 * @return	The inner options.
						 */

						std::vector<Smartmatic::GUI::Widgets::MenuOption> GetInnerOptions(Smartmatic::SAES::Configuration::MenuOption xmlMenuOption);

						/**
						 * @brief	Convert menu option type.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param		The menu option type to convert.
						 *
						 * @return	.
						 */

						static Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor  ConvertMenuOptionType (Smartmatic::SAES::Configuration::MenuOptionType);

						/**
						 * @brief	Convert saes menu option descriptor.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @param		The saes menu option descriptor type to convert.
						 *
						 * @return	menu option type.
						 */
						static Smartmatic::SAES::Configuration::MenuOptionType ConvertSaesMenuOptionDescriptorType (Smartmatic::SAES::Functionality::MenuType::SaesMenuOptionType);

						Smartmatic::GUI::Configuration::LabelConfiguration  votingWidgetLabelChildLabelConfiguration;   ///< The voting widget label child label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration  votingWidgetTopChildLabelConfiguration; ///< The voting widget top child label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration  votingWidgetBottomChildLabelConfiguration;  ///< The voting widget bottom child label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration  votingWidgetNumberChildLabelConfiguration;  ///< The voting widget number child label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration  votingWidgetPartySelectionLabelChildLabelConfiguration; ///< The voting widget party selection label child label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration partyNullLabelConfiguration; ///< The party null label configuration
						Smartmatic::GUI::Configuration::LabelConfiguration votingWindowEndMessagelabelConfig;   ///< The voting window end messagelabel configuration

						Smartmatic::SAES::Configuration::VotingExperienceLabelConfiguration votingExperienceLabelConfiguration; ///< The voting experience label configuration
						Smartmatic::SAES::Configuration::BallotOptionSelectionConfiguration ballotOptionSelectionConfiguration; ///< The ballot option selection configuration
						Smartmatic::SAES::Configuration::BallotOptionWidgetConfiguration ballotOptionWidgetConfiguration;   ///< The ballot option widget configuration
						Smartmatic::SAES::Configuration::VotingWindowConfiguration votingWindowConfiguration;   ///< The voting window configuration
						Smartmatic::SAES::Configuration::PartyWidgetConfiguration partyWidgetConfiguration; ///< The party widget configuration
						Smartmatic::SAES::Configuration::PartySelectionConfiguration partySelectionConfiguration;   ///< The party selection configuration
						Smartmatic::SAES::Configuration::ReferendumConfiguration referendumConfiguration; ///< The referendum configuration

						/*Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration
						Smartmatic::GUI::Configuration::LabelConfiguration*/

				private:

						/**
						 * @brief	Creates the common controls configurations.
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 *
						 * @return	null if it fails, else.
						 */

						::Smartmatic::SAES::Configuration::FormsCommonControlsConfigurations* CreateCommonControlsConfigurations();

						::Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration * CreateFunctionalityWizardConfig();

						std::vector<Smartmatic::SAES::Configuration::DiagnosticType> skipDiagnosis;
						static Smartmatic::Log::ISMTTLog* logger;	///< The logger
                        static SAESGUIConfigurationManager * singleton_instance;	///< The singleton instance of the configuration manager.

				};
				
			}
		}
	}
}

#endif // _S_A_E_S_G_U_I_CONFIGURATION_MANAGER_H_
