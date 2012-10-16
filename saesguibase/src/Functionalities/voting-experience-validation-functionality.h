/**
 * @file voting-experience-validation-functionality.h
 * @brief Header class voting experience validation functionality
 * @date 06/04/2011
 * @author Gerardo Hernandez, Juan Delgado, Yadickson Soto
 */

#ifndef VOTING_EXPERIENCE_VALIDATION_FUNCTIONALITY_H_
#define VOTING_EXPERIENCE_VALIDATION_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <map>
#include <Widgets/menu-option.h>
#include <Functionalities/graphic-display-functionality.h>
#include "Operation/Voting/VotingWidgetManager.hxx"
#include "Graphics/Capture/PrintScreenManager.h"
#include <Runtime/Environment/SaesInstallDirectories.hxx>
#include <Log/ISMTTLog.h>
#include <Gui/Widgets/Voting/VotingExperienceValidationWidget.hxx>
#include <Widgets/StepWidget.hxx>
#include <Voting/VotingCenters/voting-centers-schema.hxx>
#include <Operation/Voting/VotingExperienceController.hxx>
#include <Gui/Widgets/Voting/ScreenVotingWidget.hxx>
#include <Gui/Widgets/voting-frame-base.h>
#include <Operation/GenerateXMLImage.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{

				class VotingExperienceValidationFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{
					public:

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static VotingExperienceValidationFunctionality* Current();

					static void FormatName(std::string &fileName);

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

					private:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					std::string FormatTallyPosition(int position);

					VotingExperienceValidationFunctionality();

					static VotingExperienceValidationFunctionality *current_instance;   ///< The current instance

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					~VotingExperienceValidationFunctionality();

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
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

				private:

					/**
					 * @brief	Generates this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Generate();

					/**
					 * @brief	Loads the electoral configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					bool LoadElectoralConfiguration();

					/**
					 * @brief	Capture print screen.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	screenName	Name of the screen.
					 */

					void capturePrintScreen(std::string screenName);

					/**
					 * @brief	Configure print screen manager.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	imageName  	Name of the image.
					 */

					void configurePrintScreenManager(std::string imageName);
					/**
					 * @brief	Updated fixed contest
					 *
					 * @author	Juan.Delgado
					 * @date	18/07/2011
					 */
					void UpdateFixedContests();

					/**
					 * @brief	Clear variables
					 *
					 * @author	Juan.Delgado
					 * @date	18/07/2011
					 */
					void ClearVariables();

					/**
					 * @brief	Gets the contest class index from contest class code
					 *
					 * @author	Juan.Delgado
					 * @date	18/07/2011
					 *
					 * @param The contest class code
					 *
					 * @return Index of contest class
					 */
					int GetContestClassIndexFromContestCode(std::string contestClassCode);

				protected:

					void generateCenter();
					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();
					/**
					 * @brief method next voting center
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void nextVotingCenter();
					/**
					 * @brief method next step widget
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void nextStepWidget();
					/**
					 * @brief method capture image
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void captureImage();
					/**
					 * @brief method save image
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void saveImage();
					/**
					 * @brief method generate all
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void generateAll();
					/**
					 * @brief method generate party and ballot
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					void generatePartyAdnBallot();
					/**
					 * @brief	Generate welcome screen
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateWelcomeScreen();
					/**
					 * @brief	Generate languages
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateLanguages();
					/**
					 * @brief	Generate super null
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateSuperNull();
					/**
					 * @brief	Generate super confirmation
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateSuperNullConfirmation();
					/**
					 * @brief	Generate Null Vote Confirmation
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateNullVoteConfirmation();
					/**
					 * @brief	Generate custom attribute images
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateCustomAttributes();
					/**
					 * @brief	Generate print vote
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generatePrintVote();
					/**
					 * @brief	Generate remove card
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateRemoveCard();
					/**
					 * @brief	Generate card removed
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateCardRemoved();
					/**
					 * @brief	Generate print vote
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateEndPrintVote();
					/**
					 * @brief	Generates the maps.
					 * @author	Yadickson Soto
					 * @date	25/04/2012
					 */
					void generateMaps();
					/**
					 * @brief	Add step widget
					 * @param 	widget widget
					 * @param	fileName file name
					 * @author	Yadickson Soto
					 * @date	15/05/2012
					 */
					void addStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget, std::string fileName);
					/**
					 * @brief	Add voting widget
					 * @param 	widget widget
					 * @param	fileName file name
					 * @author	Yadickson Soto
					 * @date	15/05/2012
					 */
					void addVotingWidget(Smartmatic::SAES::GUI::Widgets::VotingFrameBase * widget, std::string fileName);
					/**
					 * @brief	show end result
					 * @author	Yadickson Soto
					 * @date	01/07/2012
					 */
					 void showEndResult();
					 
				private:

					std::string language;	///< The language
					std::string country;	///< The country
					std::string folderPath;	///< The folder path

					std::list<std::string> fixedContest;	///< The fixed contest

					std::string PartySelImage;
					std::string OptionSelImage;
					std::string CustomAttrSelImage;
					std::string CustomAttrConfImage;
					std::string LanguageSelImage;
					std::string LanguageSelImageConfirmation;
					std::string SuperNullImage;
					std::string SuperNullImageConfirmation;
					std::string PrintImage;
					std::string CardRemotionIndImage;
					std::string CardRemovedImage;
					std::string FoldVoteImage;
					std::string NullImageConfirmation;
					std::string WelcomeScreen;

					std::string currentImageFolder; ///< Pathname of the current image folder
					std::string currentImageName;   ///< The current image name
					std::vector<std::string> files; ///< The files
					int contestClassIndex;	///< The contest class index

					Smartmatic::SAES::Operation::MachineOperationManager * machineOperationManager; ///< Manager for machine operation
					Smartmatic::Graphics::Capture::PrintScreenManager* printScreenManager;  ///< Manager for print screen
					Operation::Voting::VotingWidgetManager* VotingWidgetManager;	///< Manager for voting widget
					Smartmatic::SAES::Runtime::Environment::SaesInstallDirectories * currentDirectories;   ///< The current directories
					Smartmatic::SAES::Voting::ElectoralConfiguration *electoralConfiguration;   ///< The electoral configuration
					unsigned long imageFileSequence;

					Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController; ///< voting experience controller
					Smartmatic::SAES::GUI::Widgets::Voting::VotingExperienceValidationWidget * votingExperienceValidationWidget; ///< voting experinece validation widget
					Smartmatic::SAES::GUI::Widgets::Voting::ScreenVotingWidget * screenVotingWidget; ///< screen voting widget

					/**
					 * @struct LanguageStepWidget
					 * @brief Struct language step widget
					 * @date 15/05/2012
					 * @author Yadickson Soto
					 */
					struct LanguageStepWidget
					{
						std::string fileName; ///< file name
						std::string language; ///< language
						std::string country; ///< country
						Smartmatic::GUI::Widgets::StepWidget * widget; ///< widget
					};

					/**
					 * @struct LanguageVotingFrameBase
					 * @brief Struct language voting frame base
					 * @date 15/05/2012
					 * @author Yadickson Soto
					 */
					struct LanguageVotingFrameBase
					{
						std::string fileName; ///< file name
						std::string language; ///< language
						std::string country; ///< country
						Smartmatic::SAES::GUI::Widgets::VotingFrameBase * widget; ///< widget
					};

					std::vector< Smartmatic::SAES::Voting::VotingCenters::VotingCenter > votingCenters; ///< all voting centers
					std::vector< LanguageStepWidget > stepWidgets; ///< all step widgets
					std::vector< LanguageVotingFrameBase > votingWidgets; ///< all voting widgets

					int currentCenter; ///< current center
					bool showDialog; ///< flag show dialog
					bool forceDelete; ///< flag force delete
					bool checkImageFiles;  ///< flag check image files
					unsigned int badCount; ///< count bad files
					unsigned int badTotalCount; ///< count total bad files
					Smartmatic::SAES::GUI::Operation::GenerateXMLImage generateXml; ///< generate xml file
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* VOTING_EXPERIENCE_VALIDATION_FUNCTIONALITY_H_ */
