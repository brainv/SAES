/*
 * voting-experience-validation-functionality.cpp
 *
 *  Created on: Apr 6, 2011
 *      Author: Gerardo Hernandez
 */

#include "voting-experience-validation-functionality.h"
#include "Operation/MachineOperationManager.hxx"
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Log/SMTTLogManager.h>
#include <Resources/election-string-resources-manager.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Voting/set-language-functionality.h>
#include <Voting/VotingDevice/card-data-wrapper.h>
#include <Voting/Election/election-schema.hxx>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Operation/Voting/VotingOperation.hxx>
#include <Gui/Widgets/AbstractFactoryWidget.hxx>
#include <Gui/Widgets/Voting/FactoryVotingWidget.hxx>
#include <System/Runtime/ProcessLauncher.h>
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Graphics/Image/CheckImageFile.hxx>
#include <System/ZenityWrapper.hxx>

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

using namespace std;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::System::Runtime;
using namespace Smartmatic::Graphics::Image;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Runtime::Environment;

ISMTTLog* VotingExperienceValidationFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality",GETTEXT_PACKAGE);

VotingExperienceValidationFunctionality* VotingExperienceValidationFunctionality::current_instance = NULL;
VotingExperienceValidationFunctionality* VotingExperienceValidationFunctionality::Current()
{
	if (!current_instance)
		current_instance = new VotingExperienceValidationFunctionality();

	return current_instance;
}

VotingExperienceValidationFunctionality::VotingExperienceValidationFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	electoralConfiguration = NULL;
	votingExperienceValidationWidget = NULL;
	printScreenManager = NULL;
	votingExperienceController = NULL;
	screenVotingWidget = NULL;

	PartySelImage = "%1_%2-PartySel-%3";
	OptionSelImage = "%1_%2-OptionSel-%3-%4";
	CustomAttrSelImage = "%1_%2-AttrSel-%3";
	CustomAttrConfImage = "%1_%2-AttrConf-%3-%4";
	LanguageSelImage = "%1_%2-LangSel";
	LanguageSelImageConfirmation = "%1_%2-LangSelConf-%3";
	SuperNullImage = "%1_%2-SuperNull";
	SuperNullImageConfirmation = "%1_%2-SuperNullConf";
	PrintImage = "%1_%2-Print";
	CardRemotionIndImage = "%1_%2-CardRemotionInd";
	CardRemovedImage = "%1_%2-CardRemoved";
	FoldVoteImage = "%1_%2-FoldVote";
	NullImageConfirmation = "%1_%2-NullConf";
	WelcomeScreen = "%1_%2-Welcome";

	currentDirectories = MachineOperationManager::getInstance()->getSaesInstallDirectories();
	showDialog = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getShowDialog();
	checkImageFiles = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCheckImageFile();

	badCount = 0;
	badTotalCount = 0;
}

VotingExperienceValidationFunctionality::~VotingExperienceValidationFunctionality()
{
	deleteElement();
}

void VotingExperienceValidationFunctionality::deleteElement()
{
	if(votingExperienceValidationWidget)
	{
		delete(votingExperienceValidationWidget);
		votingExperienceValidationWidget = NULL;
	}
	if(printScreenManager)
	{
		delete(printScreenManager);
		printScreenManager = NULL;
	}
	if(electoralConfiguration)
	{
		delete(electoralConfiguration);
		electoralConfiguration = NULL;
	}
	if (votingExperienceController)
	{
		delete votingExperienceController;
		votingExperienceController = NULL;
	}
	if (screenVotingWidget)
	{
		delete screenVotingWidget;
		screenVotingWidget = NULL;
	}
}

void VotingExperienceValidationFunctionality::Dispose()
{

}

Gtk::Widget* VotingExperienceValidationFunctionality::GetFrame()
{
	bool autorun = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getAutorun();

	if(autorun)
	{
		baseWindow->popStepWidget();
		int startTime = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeForStart();
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this,&VotingExperienceValidationFunctionality::Generate),startTime);
	}
	else
	{
		votingExperienceValidationWidget = FactoryVotingWidget::createVotingExperineceValidationWidget();
		votingExperienceValidationWidget->getSignalAll().connect(sigc::mem_fun(*this,&VotingExperienceValidationFunctionality::generateAll));
		votingExperienceValidationWidget->getSignalBallot().connect(sigc::mem_fun(*this,&VotingExperienceValidationFunctionality::generatePartyAdnBallot));
	}

	return votingExperienceValidationWidget;
}

std::string VotingExperienceValidationFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality.Title");
}

Smartmatic::Functionality::MenuOptionDescriptor VotingExperienceValidationFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MVotingExperienceValidationFunctionality,false);
}

void VotingExperienceValidationFunctionality::Initialize()
{
	electoralConfiguration = new ElectoralConfiguration();
	printScreenManager = new Smartmatic::Graphics::Capture::PrintScreenManager();

	machineOperationManager = MachineOperationManager::getInstance();
	VotingWidgetManager = VotingWidgetManager::getInstance();

	imageFileSequence = 1;

	screenVotingWidget = FactoryVotingWidget::createScreenVotingWidget();

	MachineOperationManager::getInstance()->StopDetection();
}

void VotingExperienceValidationFunctionality::generateAll()
{
	showDialog = true;
	baseWindow->popStepWidget();
	Generate();
}

void VotingExperienceValidationFunctionality::generatePartyAdnBallot()
{
	showDialog = false;
	baseWindow->popStepWidget();
	Generate();
}

void VotingExperienceValidationFunctionality::Generate()
{
	std::string directorySaes = currentDirectories->getBaseInstallationPath();
	std::string directoryBackup = currentDirectories->getBaseInstallationPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_BACKUP);
	
	logger->Debug("Find dir " + directorySaes);
	logger->Debug("Find dir " + directoryBackup);
	
	if (!directorySaes.empty() && !Smartmatic::System::IO::Directory::DirectoryExists(directorySaes) && Smartmatic::System::IO::Directory::DirectoryExists(directoryBackup))
	{
		DirectoryManager dirM (*currentDirectories);
		dirM.copyDir(directoryBackup, directorySaes);
	}
	
	std::string votingCentersFilePath = currentDirectories->getVotingCentersInstalationFileFullPath();

	bool success = VotingCentersWrapper::getInstance()->LoadFile(votingCentersFilePath);

	logger->Debug("Voting Centers File path is: " + votingCentersFilePath);

	if(success)
	{
		std::list< VotingCenter > & list (VotingCentersWrapper::getInstance()->getVotingCenters());
		std::list< VotingCenter >::iterator itVc;

		{
			std::stringstream ss;
			ss << "Number of voting centers: " << list.size();
			logger->Debug(ss.str());
		}

		votingCenters.clear();

		for (itVc = list.begin(); itVc != list.end(); itVc++)
		{
			votingCenters.push_back((*itVc));
		}

		currentCenter = 0;
		screenVotingWidget->setCurrentCenter(currentCenter);
		screenVotingWidget->setTotalCenter(votingCenters.size());

		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextVotingCenter), 10);
	}
	else
	{
		baseWindow->pushStepWidget(votingExperienceValidationWidget);
		logger->Debug("Could not open file: " + votingCentersFilePath);
	}
}

void VotingExperienceValidationFunctionality::nextVotingCenter()
{
	if (votingCenters.size() > 0)
	{
		currentCenter++;

		VotingCenter center = votingCenters.front();
		votingCenters.erase(votingCenters.begin(),votingCenters.begin()+1);

		logger->Debug("Process voting center " + center.getCode());

		//std::string toCompose = _("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality.TitleProgress");
		//std::string title = Glib::ustring::compose(toCompose, center.getCode(), center.getFolder_name());
		//screenVotingWidget->setCenterName(title);

		screenVotingWidget->setCenterName(" ");
		screenVotingWidget->setCurrentCenter(currentCenter);
		baseWindow->popPushStepWidget(screenVotingWidget);

		std::string folderName = center.getFolder_name();
		std::string programUnit = (center.getProgram_unit() != NULL ? center.getProgram_unit().get() : "");

		currentDirectories->setWorkingPath(folderName);
		currentDirectories->setProgramUnitName(programUnit);

		logger->Debug("Generate Center: " + folderName);

		folderPath = Path::Combine(currentDirectories->getVotingExperienceValidationFolderFullPath(), folderName);

		if(!Glib::thread_supported())
			Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &VotingExperienceValidationFunctionality::generateCenter), false);
	}
	else
	{
		if (SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getShowFinalMessage())
		{

			if (badTotalCount > 0)
			{
				screenVotingWidget->setImageError();
			}
			else
			{
				screenVotingWidget->setImageOk();
			}
			
			screenVotingWidget->setCenterName(" ");
			screenVotingWidget->setCurrentCenter(-1);

			baseWindow->popPushStepWidget(screenVotingWidget);
		}
		
		if(!Glib::thread_supported())
			Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &VotingExperienceValidationFunctionality::showEndResult), false);
	}
}

void VotingExperienceValidationFunctionality::showEndResult()
{
	sleep(2);
	std::string directoryImages = currentDirectories->getVotingExperienceValidationFolderFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_BACKUP);
	logger->Debug("Find dir " + directoryImages);
	
	if (!directoryImages.empty() && !Smartmatic::System::IO::Directory::DirectoryExists(directoryImages))
	{
		DirectoryManager dirM (*currentDirectories);
		dirM.copyDir(currentDirectories->getVotingExperienceValidationFolderFullPath(), directoryImages);
	}
	else
	{
		directoryImages = currentDirectories->getVotingExperienceValidationFolderFullPath();
	}
	
	std::string command = "chmod 777 -R ";
	command += directoryImages;
	(void)ProcessLauncher::RunProcessThroughSystem (command.c_str());

	logger->Debug("Execute command " + command);

	bool autoclose = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getAutoclose();

	if(autoclose)
	{
		int closeTime = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeForClose();
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::ExitFunctionality), closeTime);
		sleep (closeTime/1000 + 1);
	}
	else
	{
		baseWindow->setTitleLabelConfiguration(SAESGUIConfigurationManager::Current()->GetEmptyWindowTitleFormConfiguration());
		baseWindow->pushStepWidget(votingExperienceValidationWidget);
	}
}

void VotingExperienceValidationFunctionality::nextStepWidget()
{
	if (stepWidgets.size() > 0)
	{
		forceDelete = true;

		StepWidget * widget = stepWidgets.front().widget;
		std::string fileName = stepWidgets.front().fileName;
		std::string language = stepWidgets.front().language;
		std::string country = stepWidgets.front().country;

		configurePrintScreenManager(fileName);
		SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(language, country);

		stepWidgets.erase(stepWidgets.begin(),stepWidgets.begin()+1);
		baseWindow->popPushStepWidget(widget);

		unsigned int timeToShow = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeToShow();
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::captureImage), timeToShow);
	}
	else if (votingWidgets.size() > 0)
	{
		forceDelete = false;

		VotingFrameBase * widget = votingWidgets.front().widget;
		std::string fileName = votingWidgets.front().fileName;
		std::string language = votingWidgets.front().language;
		std::string country = votingWidgets.front().country;

		configurePrintScreenManager(fileName);
		SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(language, country);

		votingWidgets.erase(votingWidgets.begin(),votingWidgets.begin()+1);

		baseWindow->setTitleLabelConfiguration(widget->getTitleLabelConfig());
		baseWindow->setBottomLabelConfiguration(widget->getBottomLabelConfig());
		baseWindow->popPushStepWidget(widget);

		unsigned int timeToShow = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeToShow();
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::captureImage), timeToShow);
	}
	else
	{
		generateXml.persist(folderPath);
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextVotingCenter), 100);
	}
}

void VotingExperienceValidationFunctionality::captureImage()
{
	bool captureWholeScreen = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCaptureWholeScreen();

	if(captureWholeScreen)
	{
		capturePrintScreen("root");
	}
	else
	{
		std::vector<std::string> windows = printScreenManager->GetWindows("election-simulation");
		capturePrintScreen(windows[0]);
	}

	bool validate = true;
	
	if (checkImageFiles)
	{
		std::string imageFile = Smartmatic::System::IO::Path::Combine(currentImageFolder, currentImageName);
		logger->Debug("Check image file " + imageFile);
		validate = CheckImageFile::check(imageFile);

		if (!validate)
		{
			badCount++;
			badTotalCount++;
			std::stringstream ss;
			ss << imageFile << ".bad" << badCount;
			File::renameFile(imageFile, ss.str());
		}
		logger->Debug("Check image file " + std::string(validate ? "Success":"Fail"));
	}
	
	if (validate || badCount > 2)
	{
		badCount = 0;
		unsigned int timeAfterCapture = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeAfterCapture();
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::saveImage), timeAfterCapture);
	}
	else
	{
		unsigned int timeAfterCapture = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeAfterCapture();
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::captureImage), timeAfterCapture);
	}
}

void VotingExperienceValidationFunctionality::saveImage()
{
	StepWidget * widget = baseWindow->popStepWidget();

	if (forceDelete && widget)
	{
		delete widget;
		widget = NULL;
	}

    std::stringstream totalImagesText;
    totalImagesText << "Total images = " << imageFileSequence;
    logger->Debug(totalImagesText.str());

    unsigned int timeToHide = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getTimeToHide();
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextStepWidget), timeToHide);
}

void VotingExperienceValidationFunctionality::generateCenter()
{
	stepWidgets.clear();
	votingWidgets.clear();

	std::string currentDirectoryPath = currentDirectories->getBasePath();

	if(Smartmatic::System::IO::Directory::DirectoryExists(currentDirectoryPath))
	{
		logger->Debug("Loading Configuration of: " + currentDirectoryPath);

		if(LoadElectoralConfiguration())
		{

			generateXml.init();

			//Configure selectable languages

			machineOperationManager->setVotingExperienceController( votingExperienceController );

			Languages::LanguageSequence sequence = electoralConfiguration->getLanguages().getLanguage();
			Languages::LanguageIterator it;

			if(sequence.size() == 0)
			{
				logger->Debug("Could not load languages of the configuration");
			}

			//Clear previous language
			ElectionInstalationLanguages::getInstance()->clearLanguage();
			/**
			 * LANGUAGE ITERATION
			 */

			for (it = sequence.begin(); it != sequence.end(); ++it)
			{
				try
				{
					ClearVariables();

					ElectionInstalationLanguages::getInstance()->addInstallationLanguages((*it));

					Voting_device vd = machineOperationManager->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();

					list < Custom_attribute_definition > listCAD =
							machineOperationManager->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, VotingDevice::Machine_type::VOTING_DEVICES_PM);

					vector<Custom_attribute*> attributes;  ///< The attributes

					/**
					 * CUSTOM ATTRIBUTE MP ITERATION / SIMULATE
					 */
					for(list<VotingDevice::Custom_attribute_definition>::iterator l (listCAD.begin()); l != listCAD.end(); ++l)
					{
						/**
						 * ITERATION IN VALUES OF CURRENT CUSTOM ATTRIBUTE
						 * GET ALL FIXED CONTEST
						 */
						for ( VotingDevice::Custom_attribute_definition::ValueIterator c ((*l).getValue().begin()); c != (*l).getValue().end(); ++c)
						{
							VotingDevice::Custom_attribute* attribute = new VotingDevice::Custom_attribute();
							attribute->setCode(l->getCode());
							attribute->setValue(*c);
							attributes.push_back(attribute);

							VotingDevice::Card_data cardData;
							VotingDevice::CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), attributes, cardData, false, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD);

							if(votingExperienceController->init(cardData))
							{
								VotingOperation::refresh();
								UpdateFixedContests();
							}
							else
							{
								logger->Debug("Error writing info card for images in: " + currentDirectoryPath + " for " + it->getCode());
							}

							attributes.clear();
							delete attribute;
							votingExperienceController->dispose();
						}

						language = it->getLanguage();
						country = it->getCountry();

						logger->Debug("Generating images in language: " + language + "_" + country);

						if (showDialog)
						{
							generateWelcomeScreen();
							generateSuperNull();
							generateSuperNullConfirmation();
							generateNullVoteConfirmation();
							generateCustomAttributes();
							generatePrintVote();
							generateRemoveCard();
							generateCardRemoved();
							generateEndPrintVote();
						}

						generateMaps();
					}
				}
				catch(...)
				{
					logger->Debug("Error generating and showing the images in: " + currentDirectoryPath + " for " + it->getCode());
				}
			}

			if (showDialog)
			{
				generateLanguages();
			}

			Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextStepWidget), 250);
		}
		else
		{
			logger->Debug("Error loading the configuration");
			Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextVotingCenter), 250);
		}
	}
	else
	{
		logger->Debug("Directory no exist: " + currentDirectoryPath);
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &VotingExperienceValidationFunctionality::nextVotingCenter), 250);
	}
}

void VotingExperienceValidationFunctionality::ClearVariables()
{
	fixedContest.clear();
}

void VotingExperienceValidationFunctionality::UpdateFixedContests()
{
	list<string> fixed = machineOperationManager->getVotingExperienceController()->getFixedContests();

	for(list<string>::iterator iter = fixed.begin(); iter != fixed.end(); iter++)
	{
		list<string>::iterator itFind = find(fixedContest.begin(), fixedContest.end(), *iter);
		if(itFind == fixedContest.end())
		{
			fixedContest.push_back(*iter);
		}
	}
}

bool VotingExperienceValidationFunctionality::LoadElectoralConfiguration()
{
	bool returnVal = TRUE;
	try
	{
		electoralConfiguration->init(currentDirectories);
		electoralConfiguration->loadAllData();
		ElectionStringResourcesManager::Current()->init(currentDirectories);
		machineOperationManager->setElectoralConfiguration( electoralConfiguration );
		VotingWidgetManager->SetElectoralConfiguration(electoralConfiguration);
		VotingWidgetManager->SetSaesDirectories(currentDirectories);
		VotingWidgetManager->init();

		if (votingExperienceController)
		{
			delete votingExperienceController;
			votingExperienceController = NULL;
		}

		votingExperienceController = new VotingExperienceController ( electoralConfiguration );
	}
	catch(...)
	{
		returnVal = FALSE;
	}

	return returnVal;
}

void VotingExperienceValidationFunctionality::generateWelcomeScreen()
{
	logger->Debug("Generate welcome screen");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getWelcomeScreenFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(WelcomeScreen, language, country, imageFileSequence);

	WaitingForCardWidget * stepWidget = FactoryVotingWidget::createWaitingForCardWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setWelcomeScreen(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateLanguages()
{
	Languages::LanguageSequence langElection = electoralConfiguration->getLanguages().getLanguage();
	Languages::LanguageIterator ite;

	Languages::LanguageSequence langInstall = electoralConfiguration->getLanguages().getLanguage();
	Languages::LanguageIterator iti;

	for (ite = langElection.begin();
			ite != langElection.end() && langInstall.size() > 1;
			ite++)
	{
		language = ite->getLanguage();
		country = ite->getCountry();

		logger->Debug("Generate selection languages for : " + language + "_" + country);

		std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getLanguageSelImageFormatName();
		std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
		std::string formatMap = Glib::ustring::compose(LanguageSelImage, language, country, imageFileSequence);

		LanguageSelectionWidget * stepWidget = FactoryVotingWidget::createVotingLanguageSelectionWidget();
		stepWidget->setName(VotingOperation::getWindowName());

		generateXml.setLanguageScreen(fileName, language, country);
		addStepWidget(stepWidget, fileName);

		if(SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowLanguageConfirmation())
		{
			int i = 0;

			for (iti = langInstall.begin();
					iti != langInstall.end();
					iti++, i++)
			{
				language = ite->getLanguage();
				country = ite->getCountry();

				LanguageSelectionWidget * stepWidget = FactoryVotingWidget::createVotingLanguageSelectionWidget();
				stepWidget->setName(VotingOperation::getWindowName());

				std::string currentCode = stepWidget->SimulateButtonNPressed(i);

				std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getLanguageSelImageFormatNameConfirmation();
				std::string fileName = Glib::ustring::compose(formatName, language, country, currentCode, imageFileSequence);
				std::string formatMap = Glib::ustring::compose(LanguageSelImageConfirmation, language, country, currentCode, imageFileSequence);

				generateXml.addToLanguageScreen(fileName, language, country);

				std::string language1;
				std::string country1;

				SetLanguageFunctionality::getCurrentLanguageCountry ( language1, country1 );

				Glib::ustring temp;
				temp = language1;
				language1 = temp.uppercase();

				temp = country1;
				country1 = temp.uppercase();

				language = language1;
				country = country1;

				addStepWidget(stepWidget, fileName);
			}
		}
	}
}

void VotingExperienceValidationFunctionality::generateSuperNull()
{
	if(SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBlankVoteQuestion())
	{
		logger->Debug("Generate super null");

		std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getSuperNullImageFormatName();
		std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
		std::string formatMap = Glib::ustring::compose(SuperNullImage, language, country, imageFileSequence);

		SuperNullSelectionWidget * stepWidget = FactoryVotingWidget::createSuperNullSelectionWidget();
		stepWidget->setName(VotingOperation::getWindowName());

		generateXml.setSuperNull(fileName, language, country);
		addStepWidget(stepWidget, fileName);
	}
}

void VotingExperienceValidationFunctionality::generateSuperNullConfirmation()
{
	if(SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBlankVoteQuestion() &&
			SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBlankVoteConfirmation())
	{
		logger->Debug("Generate super null confiramtion");

		std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getSuperNullImageFormatName();
		std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
		std::string formatMap = Glib::ustring::compose(SuperNullImage, language, country, imageFileSequence);

		SuperNullSelectionWidget * stepWidget = FactoryVotingWidget::createSuperNullSelectionWidget();
		stepWidget->setName(VotingOperation::getWindowName());
		stepWidget->SimulateNullClicked();

		generateXml.setSuperNullConfirmation(fileName, language, country);
		addStepWidget(stepWidget, fileName);
	}
}

void VotingExperienceValidationFunctionality::generateNullVoteConfirmation()
{
	logger->Debug("Generate null vote confirmation");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getNullImageConfirmationFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(NullImageConfirmation, language, country, imageFileSequence);

	ContestNullSelectionWidget * stepWidget = FactoryVotingWidget::createContestNullSelectionWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setNullVoteConfirmation(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateCustomAttributes()
{
	logger->Debug("Generate custom attributes");

	std::list < Custom_attribute_definition > customAttrList;
	std::list <Custom_attribute_definition>::iterator iter;
	Contest_classes::Contest_classSequence contestClassSeq;

	Voting_device votDev = machineOperationManager->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
	customAttrList = machineOperationManager->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(votDev);
	contestClassSeq = machineOperationManager->getElectoralConfiguration()->getElection()->getContestClasses().getContest_class();

	for(iter = customAttrList.begin(); iter != customAttrList.end(); iter++)
	{
		contestClassIndex = 0;

		for(unsigned int i = 0; i < contestClassSeq.size(); i++)
		{
			if(contestClassSeq[i].getCustom_code().get() == iter->getCode())
			{
				std::list < Smartmatic::SAES::Voting::Election::Contest > & allContestList =
						machineOperationManager->getElectoralConfiguration()->getContestList();

				for(std::list < Smartmatic::SAES::Voting::Election::Contest >::iterator iterContest = allContestList.begin();
						iterContest != allContestList.end(); iterContest++)
				{
					if(contestClassSeq[i].getCode() == iterContest->getContest_class_code())
					{
						contestClassIndex = i;
						break;
					}
				}
			}
		}

		//compare custom class code
		if(iter->getValue().size() > 1)
		{
			// give a format to the custom attribute name key
			std::string formattedNameKey = iter->getName_key();
			FormatName(formattedNameKey);

			std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCustomAttrSelImageFormatName();
			std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
			std::string formatMap = Glib::ustring::compose(CustomAttrSelImage, language, country, formattedNameKey, contestClassIndex, imageFileSequence);

			CustomAttributeWidget * stepWidget = FactoryVotingWidget::createCustomAttributeWidget(*iter);
			stepWidget->setName(VotingOperation::getWindowName());

			generateXml.addCustomAttributes(fileName, language, country);
			addStepWidget(stepWidget, fileName);

			if(SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getShowQuestionConfirmation())
			{
				for(unsigned int i = 0; i < iter->getValue().size(); i++)
				{
					std::string formattedValue = iter->getValue()[i];
					FormatName(formattedValue);

					std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCustomAttrConfImageFormatName();
					std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
					std::string formatMap = Glib::ustring::compose(CustomAttrConfImage, language, country, formattedNameKey, formattedValue, imageFileSequence);

					CustomAttributeWidget * stepWidget = FactoryVotingWidget::createCustomAttributeWidget(*iter);
					stepWidget->setName(VotingOperation::getWindowName());
					stepWidget->ForceSelectedOption(iter->getValue()[i]);

					generateXml.addToCustomAttributes(fileName, language, country);
					addStepWidget(stepWidget, fileName);
				}
			}
		}
	}
}

void VotingExperienceValidationFunctionality::generatePrintVote()
{
	logger->Debug("Generate print vote");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getPrintImageFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(PrintImage, language, country, imageFileSequence);

	PrintVoteWidget * stepWidget = FactoryVotingWidget::createPrintVoteWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setPrintVote(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateRemoveCard()
{
	logger->Debug("Generate remove card");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCardRemotionIndImageFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(CardRemotionIndImage, language, country, imageFileSequence);

	RemoveCardWidget * stepWidget = FactoryVotingWidget::createRemoveCardWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setRemoveCard(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateCardRemoved()
{
	logger->Debug("Generate card removed");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getCardRemovedImageFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(CardRemovedImage, language, country, imageFileSequence);

	CardRemovedWidget * stepWidget = FactoryVotingWidget::createCardRemovedWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setCardRemoved(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateEndPrintVote()
{
	logger->Debug("Generate end print vote");

	std::string formatName = SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getFoldVoteImageFormatName();
	std::string fileName = Glib::ustring::compose(formatName, language, country, imageFileSequence);
	std::string formatMap = Glib::ustring::compose(FoldVoteImage, language, country, imageFileSequence);

	EndPrintVoteWidget * stepWidget = FactoryVotingWidget::createEndPrintVoteWidget();
	stepWidget->setName(VotingOperation::getWindowName());

	generateXml.setEndPrintVote(fileName, language, country);
	addStepWidget(stepWidget, fileName);
}

void VotingExperienceValidationFunctionality::generateMaps()
{
	logger->Debug("Generate maps");

	int totalPartyWindows = 0;
	int totalBallotOptionWindows = 0;
	
	std::map<std::string, Smartmatic::SAES::GUI::Widgets::PartySelectionWidget *>::iterator iterPartySel;
	std::map<std::string, Smartmatic::SAES::GUI::Widgets::PartySelectionWidget *> mapPartySelectionWidget;

	std::map<std::string, std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > >::iterator itb1;
	std::map<std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * >::iterator itb2;

	std::map < std::string , std::map < std::string, Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget * > >	mapBallotOptionSelectionWidget;

	std::string fileName;
	
	//Loading Party Selections
	//Map indexed by the contest code
	mapPartySelectionWidget = VotingWidgetManager->getMapPartySelectionWidget();
	mapBallotOptionSelectionWidget = VotingWidgetManager->getMapBallotOptionSelectionWidget();

	for(iterPartySel = mapPartySelectionWidget.begin(); iterPartySel !=  mapPartySelectionWidget.end(); iterPartySel++)
	{
		contestClassIndex = GetContestClassIndexFromContestCode(iterPartySel->second->getContest().getContest_class_code());
		std::list<string>::iterator itFind = find(fixedContest.begin(), fixedContest.end(), iterPartySel->second->getContest().getCode());

		if(itFind == fixedContest.end())
		{
			iterPartySel->second->ShowBackButton();
		}
		else
		{
			iterPartySel->second->SetBackButton(false);
		}

		fileName = Glib::ustring::compose(SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getPartySelImageFormatName(),language, country,iterPartySel->first, contestClassIndex, imageFileSequence++);
		iterPartySel->second->setName(VotingOperation::getWindowName());
		addVotingWidget(iterPartySel->second, fileName);
		imageFileSequence++;
		totalPartyWindows++;

		string partyMap = Glib::ustring::compose(PartySelImage,language, country,iterPartySel->first, contestClassIndex);
		generateXml.addParty(fileName, language, country);
	}

	//Loading Ballot Options Selections

	mapBallotOptionSelectionWidget = VotingWidgetManager->getMapBallotOptionSelectionWidget();

	for(itb1 = mapBallotOptionSelectionWidget.begin(); itb1 != mapBallotOptionSelectionWidget.end(); itb1++ )
	{
		std::list < Party > & partyList = machineOperationManager->getElectoralConfiguration()->getListPartyByContestCode (itb1->first);

		for (itb2 = ((*itb1).second).begin(); itb2 != ((*itb1).second).end();  itb2++)
		{
			contestClassIndex = GetContestClassIndexFromContestCode(itb2->second->getContest().getContest_class_code());
			list<string>::iterator itFind = find(fixedContest.begin(), fixedContest.end(), itb2->second->getContest().getCode());

			if(itFind == fixedContest.end())
			{
				itb2->second->ShowBackButton();
			}
			else
			{
				itb2->second->SetBackButton(false);
			}

			fileName = Glib::ustring::compose(SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getOptionSelImageFormatName(),language, country,itb1->first, FormatTallyPosition(itb2->second->GetTallyPosition()),contestClassIndex,imageFileSequence++);

			{
				std::stringstream ss;
				ss << "Tally Position: "<< itb2->second->GetTallyPosition();
				logger->Debug(ss.str());
			}

			itb2->second->setName(VotingOperation::getWindowName());

			if(SAESGUIConfigurationManager::Current()->GetVotingExperienceValidationScreensFunctionalityConfiguration().getScreenOnlyFirstBallot())
			{
				if(itb2->first == partyList.begin()->getCode())
				{
					addVotingWidget(itb2->second, fileName);
					imageFileSequence++;
					totalBallotOptionWindows++;

					string ballotMap = Glib::ustring::compose(OptionSelImage,language, country,itb1->first, itb2->first,contestClassIndex);
					generateXml.addBallot(fileName, language, country);
				}
			}
			else
			{
				addVotingWidget(itb2->second, fileName);
				imageFileSequence++;
				totalBallotOptionWindows++;

				string ballotMap = Glib::ustring::compose(OptionSelImage,language, country,itb1->first, itb2->first,contestClassIndex);
				generateXml.addBallot(fileName, language, country);
			}
		}
	}
}

std::string VotingExperienceValidationFunctionality::FormatTallyPosition(int position)
{
	stringstream out;
	out<<position;

	string formattedPosition = out.str();

	if(formattedPosition.size() == 1)
		formattedPosition.insert(0, "000");
	else if(formattedPosition.size() == 2)
		formattedPosition.insert(0, "00");
	else if(formattedPosition.size() == 3)
		formattedPosition.insert(0, "0");

	return formattedPosition;
}

int VotingExperienceValidationFunctionality::GetContestClassIndexFromContestCode(std::string contestCode)
{
	Contest_classes::Contest_classSequence contestClassSeq = machineOperationManager->getElectoralConfiguration()->getElection()->getContestClasses().getContest_class();

	for(unsigned int i = 0; i < contestClassSeq.size(); i++)
	{
		if(contestClassSeq[i].getCode() == contestCode)
		{
			return i;
		}
	}

	return 0;
}

void VotingExperienceValidationFunctionality::FormatName(std::string &fileName)
{
	size_t found = fileName.find("|");
	fileName.erase(found);

	if(fileName.size() > 5)
	{
		fileName.erase(fileName.begin() + 5, fileName.end());
	}
}

void VotingExperienceValidationFunctionality::configurePrintScreenManager(std::string imageName)
{
	currentImageFolder = folderPath;
	currentImageName = imageName;
};

void VotingExperienceValidationFunctionality::capturePrintScreen(std::string screenName)
{
	if(Smartmatic::System::IO::Directory::DirectoryExists(currentImageFolder) == false)
		Smartmatic::System::IO::Directory::Mkdir(currentImageFolder);
	std::string currentImageFolderA = currentImageFolder;
	printScreenManager->Capture(screenName, Smartmatic::System::IO::Path::Combine(currentImageFolder, currentImageName));
}

Smartmatic::Log::ISMTTLog* VotingExperienceValidationFunctionality::getLogger()
{
	return logger;
}

Glib::ustring VotingExperienceValidationFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality.LogStartFunctionality");
}

Glib::ustring VotingExperienceValidationFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingExperienceValidationFunctionality.LogCloseFunctionality");
}

void VotingExperienceValidationFunctionality::addStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget, std::string fileName)
{
	LanguageStepWidget config;
	config.fileName = fileName;
	config.language = language;
	config.country = country;
	config.widget = widget;
	stepWidgets.push_back(config);

	logger->Debug("file name: " + fileName + " - " + language + "_" + country);
	imageFileSequence++;
}

void VotingExperienceValidationFunctionality::addVotingWidget(Smartmatic::SAES::GUI::Widgets::VotingFrameBase * widget, std::string fileName)
{
	LanguageVotingFrameBase config;
	config.fileName = fileName;
	config.language = language;
	config.country = country;
	config.widget = widget;
	votingWidgets.push_back(config);
}
