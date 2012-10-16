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

#include "Environment/Configurations/resource-path-provider.h"
#include "s-a-e-s-g-u-i-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
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

using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace std;
using namespace Smartmatic::System;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Log;

typedef Smartmatic::GUI::Widgets::MenuWidgetConfiguration SMMTMenuWidgetConfiguration;
typedef Smartmatic::SAES::Configuration::MenuWidgetConfiguration XMLMenuWidgetConfiguration;
typedef Smartmatic::GUI::Widgets::MenuOption SMMTMenuOption;
typedef Smartmatic::SAES::Configuration::MenuOption XMLMenuOption;

typedef Smartmatic::SAES::Functionality::MenuType::SaesMenuOptionType SMMTMenuOptionType;

SAESGUIConfigurationManager * SAESGUIConfigurationManager::singleton_instance = NULL;

#define LOGGER_PROJECT "Smartmatic.Configuration.SAESGUIConfigurationManager" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* SAESGUIConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* SAESGUIConfigurationManager::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

SAESGUIConfigurationManager::SAESGUIConfigurationManager()
{
    configuration = NULL;
	Initialize();

	votingWidgetLabelChildLabelConfiguration = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWidgetLabelChildLabelConfiguration());
	votingWidgetTopChildLabelConfiguration = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWidgetTopChildLabelConfiguration());
	votingWidgetBottomChildLabelConfiguration = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWidgetBottomChildLabelConfiguration());
	votingWidgetNumberChildLabelConfiguration = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWidgetNumberChildLabelConfiguration());
	votingWidgetPartySelectionLabelChildLabelConfiguration =ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWidgetPartySelectionLabelChildLabelConfiguration());
	partyNullLabelConfiguration = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getPartyNullLabelConfiguration());
	votingWindowEndMessagelabelConfig = ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getVotingWindowEndMessageLabelConfiguration());
	//votingExperienceLabelConfiguration;
	ballotOptionSelectionConfiguration = (*configuration)->getVotingExperience().getBallotOptionSelection();
	ballotOptionWidgetConfiguration =(*configuration)->getVotingExperience().getBallotOptionSelection().getBallotOptionWidget();
	votingWindowConfiguration =(*configuration)->getVotingExperience().getVotingWindow();//-----------------------------------------------------------------------------***********
	partySelectionConfiguration = (*configuration)->getVotingExperience().getPartySelection();
	partyWidgetConfiguration = partySelectionConfiguration.getPartyWidget();
	referendumConfiguration = (*configuration)->getVotingExperience().getReferendumSelection();
}

SAESGUIConfigurationManager::~SAESGUIConfigurationManager()
{
	if(configuration != NULL)
	{
		delete(configuration);
	}
}

auto_ptr<SaesGUIConfiguration>* SAESGUIConfigurationManager::getConfiguration()
{
	return configuration;
}

void SAESGUIConfigurationManager::Initialize()
{
	try
	{
		string semiFile (ConfigurationPersistenceManager::Current().GetLibraryConfigFile("SAESGUI"));
		if(!semiFile.empty())
		{
			istringstream ss( semiFile );
			configuration = new  auto_ptr<SaesGUIConfiguration>(parseSaesGUIConfiguration(ss,ConfigurationTypes::Flags::dont_validate ));
		}
		else
		{
			LoadDefault();
			Initialize();
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESGUI Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESGUI Error", "Error");
		exit (0);
	}
}

ReportPrintingWidgetConfiguration SAESGUIConfigurationManager::GetPrintingWidgetConfiguration ()
{
	return (*configuration)->getReportPrintingWidget();
}

bool SAESGUIConfigurationManager::GetForceToLoadFrame ()
{
	return (*configuration)->getForceToLoadFrame();
}

bool SAESGUIConfigurationManager::GetSendBarcodeConfigurationOnReconnectWidget()
{
	return (*configuration)->getSendBarcodeConfigurationOnReconnectWidget();
}

bool SAESGUIConfigurationManager::GetLaunchThreadBeid()
{
	return (*configuration)->getBeidCardUseThread();
}

bool SAESGUIConfigurationManager::GetBeidCardShowRemoveMessage()
{
	return (*configuration)->getBeidCardShowRemoveMessage();
}

bool SAESGUIConfigurationManager::GetPMInstallationWidgetShowPrintPasswordButton()
{
	return (*configuration)->getPMInstallationWidgetShowPrintPasswordButton();
}

bool SAESGUIConfigurationManager::GetBeidShowIdCard()
{
	return (*configuration)->getBeidShowIdCard();
}

CustomAtributtesWindowConfiguration SAESGUIConfigurationManager::GetCustomAtributtesWindowConfiguration()
{
	return (*configuration)->getVotingExperience().getCustomAtributtesWindow();
}

Smartmatic::SAES::Configuration::VotingExperienceLabelConfiguration SAESGUIConfigurationManager::GetVotingExperienceLabelConfiguration()
{
	return (*configuration)->getVotingExperience().getVotingExperienceLabel();
}

Smartmatic::SAES::Configuration::VMInstallationWidgetConfiguration SAESGUIConfigurationManager::GetVMInstallationConfiguration()
{
	return (*configuration)->getVMInstallationConfiguration();
}

Smartmatic::SAES::Configuration::ShowBeidEntryTypeConfiguration SAESGUIConfigurationManager::GetShowBeidEntry()
{
	return (*configuration)->getShowBeidEntry();
}

ConfirmationWindowConfiguration SAESGUIConfigurationManager::GetConfirmationWindowConfiguration()
{
	return (*configuration)->getVotingExperience().getConfirmationWindow();
}

BallotOptionWidgetConfiguration SAESGUIConfigurationManager::GetBallotOptionWidgetConfiguration()
{
	return ballotOptionWidgetConfiguration;
}

BallotOptionSelectionConfiguration& SAESGUIConfigurationManager::GetBallotOptionSelectionConfiguration()
{
	return ballotOptionSelectionConfiguration;
}

ReferendumConfiguration& SAESGUIConfigurationManager::GetReferendumConfiguration()
{
	return referendumConfiguration;
}

PartyWidgetConfiguration& SAESGUIConfigurationManager::GetPartyWidgetConfiguration()
{
	return partyWidgetConfiguration;
}

VotingWindowConfiguration& SAESGUIConfigurationManager::GetVotingWindowConfiguration()
{
	return votingWindowConfiguration;
}

int SAESGUIConfigurationManager::getHeightOfButtons()
{
	return(*configuration)->getTouchScreenCalibrationConfiguration ().getHeightOfButtons();
}

int SAESGUIConfigurationManager::getWidthOfButtons()
{
	return(*configuration)->getTouchScreenCalibrationConfiguration ().getWidthOfButtons();
}

BrightnessDiagnosisConfiguration& SAESGUIConfigurationManager::getBrightnessDiagnosisConfiguration()
{
	return(*configuration)->getBrightnessDiagnosisConfiguration();
}

int SAESGUIConfigurationManager::getTimeDelayButtons()
{
	return(*configuration)->getBrightnessDiagnosisConfiguration().getTimeDelayButtons();
}

int SAESGUIConfigurationManager::getTimeOutCard()
{
	return(*configuration)->getVotingExperience().getTimeOutCard();
}

int SAESGUIConfigurationManager::getTimeToShowFinalMessage()
{
	return(*configuration)->getVotingExperience().getTimeToShowFinalMessage();
}

bool SAESGUIConfigurationManager::getMarkCardAsUsed()
{
	return(*configuration)->getVotingExperience().getMarkCardAsUsed();
}

int SAESGUIConfigurationManager::getCheckSumFailTimerMessage()
{
	return(*configuration)->getVotingExperience().getCheckSumFailTimerMessage();
}


CheckSumFailOption::Value SAESGUIConfigurationManager::getCheckSumFailOption()
{
	return(*configuration)->getVotingExperience().getCheckSumFailOption();
}

bool SAESGUIConfigurationManager::GetSortAlphabetically()
{
	return (*configuration)->getVotingExperience().getSortOptionsAlphabetical();
}

bool SAESGUIConfigurationManager::GetSortLanguagesAlphabetical()
{
	return (*configuration)->getVotingExperience().getSortLanguagesAlphabetical();
}

bool SAESGUIConfigurationManager::getDetectCardExtraction()
{
	return (*configuration)->getVotingExperience().getDetectCardExtraction();
}

unsigned int SAESGUIConfigurationManager::getNumberOfExtractionsBeforeStop()
{
	return (*configuration)->getVotingExperience().getNumberOfExtractionsBeforeStop();
}

bool SAESGUIConfigurationManager::getAssistedActivationBySelection()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getAssistedActivationBySelection();
}

PrintPreviewFunctionalityConfiguration SAESGUIConfigurationManager::getPrintPreviewFunctionalityConfiguration()
{
	return (*configuration)->getPrintPreviewFunctionalityConfiguration();
}

PartySelectionConfiguration& SAESGUIConfigurationManager::GetPartySelectionConfiguration()
{
	return partySelectionConfiguration;
}

unsigned int SAESGUIConfigurationManager::getMinimumDemoCounterToAllowActivation()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getMinimumDemoCounterToAllowActivation();
}

unsigned int SAESGUIConfigurationManager::getMinimumDemoCounterToAllowRecovery()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration().getMinimumDemoCounterToAllowActivation();
}

bool SAESGUIConfigurationManager::getShowRecoveryConfirmationButtons()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration().getShowConfirmationButtons();
}

bool SAESGUIConfigurationManager::getRecoveryCleanOnCorrectActivation()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration().getCleanOnCorrectActivation();
}

bool SAESGUIConfigurationManager::getActivatedAfterInsertingCard()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getActivatedAfterInsertingCard();
}

bool SAESGUIConfigurationManager::getRecoveryCleanOnIncorrectActivation()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration().getCleanOnIncorrectActivation();
}

bool SAESGUIConfigurationManager::getShowConfirmationButtons()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getShowConfirmationButtons();
}

StatisticFunctionalityConfiguration& SAESGUIConfigurationManager::GetStatisticFunctionalityConfiguration()
{
	return (*configuration)->getStatisticFunctionalityConfiguration();
}

OpenElectionFunctionalityConfiguration& SAESGUIConfigurationManager::GetOpenElectionFunctionalityConfiguration()
{
	return (*configuration)->getOpenElectionFunctionalityConfiguration();
}

CloseElectionFunctionalityConfiguration& SAESGUIConfigurationManager::GetCloseElectionFunctionalityConfiguration()
{
	return (*configuration)->getCloseElectionFunctionalityConfiguration();
}

ActivationConsolidationFunctionalityConfiguration SAESGUIConfigurationManager::GetActivationConsolidationFunctionalityConfiguration()
{
	return (*configuration)->getActivationConsolidationFunctionalityConfiguration();
}

PollWorkerRegisterFunctionalityConfiguration SAESGUIConfigurationManager::GetPollWorkerRegisterFunctionalityConfiguration()
{
	return (*configuration)->getPollWorkerRegisterFunctionalityConfiguration();
}

IDConfig SAESGUIConfigurationManager::getPollWorkerIDConfiguration(Smartmatic::SAES::Voting::PBReports::WorkerMemberType type)
{
	IDConfig idConfig;
	IDProperties generic(true);
	generic.setType(ElementType::CONFIGURATION_ALPHA);
	generic.setMax(80);
	idConfig.setName(generic);
	idConfig.setLastName(generic);

	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationSequence sepPollWorker = SAESGUIConfigurationManager::Current()->GetPollWorkerRegisterFunctionalityConfiguration().getPollWorkerRegisterConfiguration();
	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationIterator itp;

	for (itp = sepPollWorker.begin();
			itp != sepPollWorker.end();
			itp++)
	{
		if (type == (*itp).getWorkerMemberType())
		{
			idConfig = (*itp).getIDConfig();
			break;
		}
	}

	return idConfig;
}

VoteConsolidationFunctionalityConfiguration SAESGUIConfigurationManager::GetVoteConsolidationFunctionalityConfiguration()
{
	return (*configuration)->getVoteConsolidationFunctionalityConfiguration();
}

VotingExperienceValidationScreensFunctionalityConfiguration SAESGUIConfigurationManager::GetVotingExperienceValidationScreensFunctionalityConfiguration()
{
	return (*configuration)->getVotingExperienceValidationScreensFunctionalityConfiguration();
}

IncidentReportFunctionalityConfiguration SAESGUIConfigurationManager::GetIncidentReportFunctionalityConfiguration()
{
	return (*configuration)->getIncidentReportFunctionalityConfiguration();
}

LogReportFunctionalityConfiguration SAESGUIConfigurationManager::GetLogReportFunctionalityConfiguration()
{
	return (*configuration)->getLogReportFunctionalityConfiguration();
}

unsigned int SAESGUIConfigurationManager::GetMinimunNotesToRegisterConfiguration()
{
	return (*configuration)->getCloseNotetFunctionalityConfiguration().getMinimunNotesToRegister();
}

//Themes Methods

ThemesConfiguration& SAESGUIConfigurationManager::GetThemesConfiguration()
{
	return (*configuration)->getThemesConfiguration();
}

OfficialThemeConfiguration& SAESGUIConfigurationManager::GetOfficialThemeConfiguration()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration();
}

DemoThemeConfiguration& SAESGUIConfigurationManager::GetDemoThemeConfiguration()
{
	return (*configuration)->getThemesConfiguration().getDemoThemeConfiguration();
}

RecoveryThemeConfiguration& SAESGUIConfigurationManager::GetRecoveryThemeConfiguration()
{
	return (*configuration)->getThemesConfiguration().getRecoveryThemeConfiguration();
}

std::string SAESGUIConfigurationManager::GetVotingWindowButtonName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingWindowButton();
}

std::string SAESGUIConfigurationManager::GetVotingExperiencePartyEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingExperiencePartyEventbox();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceWindowName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingExperienceWindow();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceBallotOptionEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingExperienceBallotOptionEventbox();
}

std::string SAESGUIConfigurationManager::GetCardActivatorFunctionalityMessageName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCardActivatorFunctionalityMessage();
}

std::string SAESGUIConfigurationManager::GetCardActivatorMessageEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCardActivatorMessageEventbox();
}

std::string SAESGUIConfigurationManager::GetCardActivatorFunctionalityEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCardActivatorFunctionalityEventbox();
}

std::string SAESGUIConfigurationManager::GetCardActivatorValuesEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCardActivatorValuesEventbox();
}

std::string SAESGUIConfigurationManager::GetCardActivatorFunctionalityCenterFrameName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCardActivatorFunctionalityCenterFrame();
}

std::string SAESGUIConfigurationManager::GetEventboxStepBarcodeName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxStepBarcode();
}

std::string SAESGUIConfigurationManager::GetEventboxStepBarcodeTitleName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxStepBarcodeTitle();
}

std::string SAESGUIConfigurationManager::GetEventboxStepCardTitleName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxStepCardTitle();
}

std::string SAESGUIConfigurationManager::GetVoteDemoFunctionalityMessageName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVoteDemoFunctionalityMessage();
}

std::string SAESGUIConfigurationManager::GetStandInLabelLabelName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getStandInLabelLabel();
}

std::string SAESGUIConfigurationManager::GetStandInLabelEventName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getStandInLabelEvent();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceSelectBallotOptionWidgetName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingExperienceSelectBallotOptionWidget();
}

std::string SAESGUIConfigurationManager::GetChangeLanguageMessageWigdetEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getChangeLanguageMessageWigdetEventbox();
}

std::string SAESGUIConfigurationManager::GetCustomAttributeComboSelectionsWidgetTitleName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCustomAttributeComboSelectionsWidgetTitle();
}

std::string SAESGUIConfigurationManager::GetCustomAttributeCounterWidgetTitleName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getCustomAttributeCounterWidgetTitle();
}

std::string SAESGUIConfigurationManager::GetEventboxChooseWidgetFrameName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxChooseWidgetFrame();
}

std::string SAESGUIConfigurationManager::GetVotingExperiencePartyWidgetName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getVotingExperiencePartyWidget();
}		

std::string SAESGUIConfigurationManager::GetPartyWidgetEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getPartyWidgetEventbox();
}

std::string SAESGUIConfigurationManager::GetEventboxImageStepInstallationWizardName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxImageStepInstallationWizard();
}

std::string SAESGUIConfigurationManager::GetEventboxStepInstallationWizardName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getEventboxStepInstallationWizard();
}

std::string SAESGUIConfigurationManager::GetParentKeypadEventboxName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getParentKeypadEventbox();
}

std::string SAESGUIConfigurationManager::GetInfoFrameName()
{
	return (*configuration)->getThemesConfiguration().getOfficialThemeConfiguration().getInfoFrame();
}

std::string SAESGUIConfigurationManager::GetVotingWindowButtonDemoName()
{
	return (*configuration)->getThemesConfiguration().getDemoThemeConfiguration().getVotingWindowButtonDemo();
}

std::string SAESGUIConfigurationManager::GetVotingExperiencePartyEventboxDemoName()
{
	return (*configuration)->getThemesConfiguration().getDemoThemeConfiguration().getVotingExperiencePartyEventboxDemo();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceWindowDemoName()
{
	return (*configuration)->getThemesConfiguration().getDemoThemeConfiguration().getVotingExperienceWindowDemo();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceBallotOptionEventboxDemoName()
{
	return (*configuration)->getThemesConfiguration().getDemoThemeConfiguration().getVotingExperienceBallotOptionEventboxDemo();
}
		
std::string SAESGUIConfigurationManager::GetVotingWindowButtonRecoveryName()
{
	return (*configuration)->getThemesConfiguration().getRecoveryThemeConfiguration().getVotingWindowButtonRecovery();
}

std::string SAESGUIConfigurationManager::GetVotingExperiencePartyEventboxRecoveryName()
{
	return (*configuration)->getThemesConfiguration().getRecoveryThemeConfiguration().getVotingExperiencePartyEventboxRecovery();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceWindowRecoveryName()
{
	return (*configuration)->getThemesConfiguration().getRecoveryThemeConfiguration().getVotingExperienceWindowRecovery();
}

std::string SAESGUIConfigurationManager::GetVotingExperienceBallotOptionEventboxRecoveryName()
{
	return (*configuration)->getThemesConfiguration().getRecoveryThemeConfiguration().getVotingExperienceBallotOptionEventboxRecovery();
}	

//End Theme Methods

SMMTMenuWidgetConfiguration* SAESGUIConfigurationManager::GetMachineWidgetConfiguration(MachineType type)
{

	XMLMenuWidgetConfiguration xmlMachineConfiguration;
    xmlMachineConfiguration =  (*configuration)->getVotingMachine ();
	
	SMMTMenuWidgetConfiguration *votingMachine = new SMMTMenuWidgetConfiguration(
			xmlMachineConfiguration.getFirstLevelWidth(), xmlMachineConfiguration.getFirstLevelHeight(),
			xmlMachineConfiguration.getFirstLevelSpacing(), xmlMachineConfiguration.getFirstLevelBorderWidth(),
			xmlMachineConfiguration.getFirstLevelFrameWidth(), xmlMachineConfiguration.getFirstLevelFrameHeight(),
			xmlMachineConfiguration.getSecondLevelWidth(), xmlMachineConfiguration.getSecondLevelHeight(),
			xmlMachineConfiguration.getSecondLevelSpacing(), xmlMachineConfiguration.getSecondLevelBorderWidth(),
			xmlMachineConfiguration.getSecondLevelFramePadding(), xmlMachineConfiguration.getHasShortcut());

	return votingMachine;
}

vector<SMMTMenuOption> SAESGUIConfigurationManager::GetMenuOptionConfiguration()
{
	vector<SMMTMenuOption> menuOptions;
	XMLMenuWidgetConfiguration xmlMachineConfiguration;
	XMLMenuOption xmlMenuOption;

	xmlMachineConfiguration =  (*configuration)->getVotingMachine ();

	return GetInnerOptions(xmlMachineConfiguration.getRootOption());

}

vector<SMMTMenuOption> SAESGUIConfigurationManager::GetInnerOptions(XMLMenuOption xmlMenuOption)
{
	vector<SMMTMenuOption> optionsReturn;

	MenuOptions childrenOptions = xmlMenuOption.getMenuOptions();

	 for (MenuOptions::OptionIterator i (childrenOptions.getOption().begin());	i != childrenOptions.getOption().end ();++i)
	{

		const XMLMenuOption & xmlOption (*i);

		SMMTMenuOption option = *new SMMTMenuOption();
		
		option.nameKey = _(xmlOption.getUntraslatedKey().c_str()); //FG: this translate the name of the button
		option.imageKey = xmlOption.getImageKey();
		option.code = xmlOption.getCode();
		option.mappingKey = xmlOption.getMappingKey();
		option.mappingKeyName = xmlOption.getMappingKeyName ();
		option.optionDescriptor = ConvertMenuOptionType(xmlOption.getOptionType ());
		option.v_MenuOption = GetInnerOptions(xmlOption);
		optionsReturn.push_back (option);

    }
	return optionsReturn;
}

MenuOptionType SAESGUIConfigurationManager::ConvertSaesMenuOptionDescriptorType (Smartmatic::SAES::Functionality::MenuType::SaesMenuOptionType menuType)
{
	MenuOptionType menuOptionType = MenuOptionType::CONFIGURATION_XMLMENU;

	switch(menuType)
	{
		case MenuType::Menu:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMENU;
			break;
		case MenuType::MOpenElectionFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMOPENELECTIONFUNCTIONALITY;
			break;
		case MenuType::MCloseElectionFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCLOSEELECTIONFUNCTIONALITY;
			break;
		case MenuType::MDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MSCReaderDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMSCREADERDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MPrinterDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMPRINTERDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MAlarmBoxDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMALARMBOXDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MCalibrationDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCALIBRATIONDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MBrightnessDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMBRIGHTNESSDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MBarcodeDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMBARCODEDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MAllDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMALLDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MFlashDiagnosisFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMFLASHDIAGNOSISFUNCTIONALITY;
			break;
		case MenuType::MChangeHourFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCHANGEHOURFUNCTIONALITY;
			break;
		case MenuType::MCardGeneratorFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCARDGENERATORFUNCTIONALITY;
			break;
		case MenuType::MAssistedCardGeneratorFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMASSISTEDCARDGENERATORFUNCTIONALITY;
			break;
		case MenuType::MRecoveryCardGeneratorFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMRECOVERYCARDGENERATORFUNCTIONALITY;
			break;
		case MenuType::MVotingMachineInstallationFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMVOTINGMACHINEINSTALLATIONFUNCTIONALITY;
			break;
		case MenuType::MVoteProcessDemoFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMVOTEPROCESSDEMOFUNCTIONALITY;
			break;
		case MenuType::MPrintPreviewFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMPRINTPREVIEWFUNCTIONALITY;
			break;
		case MenuType::MChangeLanguageFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCHANGELANGUAGEFUNCTIONALITY;
			break;
		case MenuType::MIncidentReportFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMINCIDENTREPORTFUNCTIONALITY;
			break;
		case MenuType::MStatisticsReportFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMSTATISTICSREPORTFUNCTIONALITY;
			break;
		case MenuType::MVotingExperienceValidationFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMVOTINGEXPERIENCEVALIDATIONFUNCTIONALITY;
			break;
		case MenuType::MPollWorkerRegisterFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMPOLLWORKERREGISTERFUNCTIONALITY;
			break;
		case MenuType::MCloseVotationFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMCLOSEVOTATIONFUNCTIONALITY;
			break;
		case MenuType::MVoteConsolidationFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMVOTECONSOLIDATIONFUNCTIONALITY;
			break;
		case MenuType::MRegisterPresidentNotesFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMREGISTERPRESIDENTNOTESFUNCTIONALITY;
			break;
		case MenuType::MReportPrintingFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMMREPORTPRINTINGFUNCTIONALITY;
			break;
		case MenuType::MLogReportFunctionality:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMLOGREPORTFUNCTIONALITY;
			break;
		case MenuType::MShutdownMachine:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMSHUTDOWMMACHINEFUNCTIONALITY;
			break;
		case MenuType::MFillAssistedActivationInfo:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMFILLASSISTEDACTIVATIONINFOFUNCTIONALITY;
			break;
		case MenuType::MActivationConsolidation:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMACTIVATIONCONSOLIDATIONFUNCTIONALITY;
			break;
		case MenuType::VOTING_FOR_DISABLED:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMVOTINGFORDISABLEDFUNCTIONALITY;
			break;
		case MenuType::POLICE_NOTES:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMPOLICENOTESFUNCTIONALITY;
			break;
		case MenuType::DATA_UTILS_VALIDATOR:
			menuOptionType = MenuOptionType::CONFIGURATION_XMLMDATAUTILSVALIDATORFUNCTIONALITY;
			break;
	}

	return menuOptionType;
}

SaesMenuOptionDescriptor  SAESGUIConfigurationManager::ConvertMenuOptionType (MenuOptionType xmlMenuOptionType)
{
	SaesMenuOptionDescriptor *descriptor = NULL;
	
		
	switch(xmlMenuOptionType)
	{
		case MenuOptionType::CONFIGURATION_XMLMENU:
			descriptor = new SaesMenuOptionDescriptor(MenuType::Menu,true);
			break;
		case MenuOptionType::CONFIGURATION_XMLMOPENELECTIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MOpenElectionFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCLOSEELECTIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MCloseElectionFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMSCREADERDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MSCReaderDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMPRINTERDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MPrinterDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMALARMBOXDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MAlarmBoxDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCALIBRATIONDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MCalibrationDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMBRIGHTNESSDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MBrightnessDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMBARCODEDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MBarcodeDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMALLDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MAllDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMFLASHDIAGNOSISFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MFlashDiagnosisFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCHANGEHOURFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MChangeHourFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCARDGENERATORFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MCardGeneratorFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMASSISTEDCARDGENERATORFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MAssistedCardGeneratorFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMRECOVERYCARDGENERATORFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MRecoveryCardGeneratorFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMVOTINGMACHINEINSTALLATIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MVotingMachineInstallationFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCHANGELANGUAGEFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MChangeLanguageFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMVOTEPROCESSDEMOFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MVoteProcessDemoFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMPRINTPREVIEWFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MPrintPreviewFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMINCIDENTREPORTFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MIncidentReportFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMSTATISTICSREPORTFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MStatisticsReportFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMPOLLWORKERREGISTERFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MPollWorkerRegisterFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMVOTINGEXPERIENCEVALIDATIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MVotingExperienceValidationFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMCLOSEVOTATIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MCloseVotationFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMREGISTERPRESIDENTNOTESFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MRegisterPresidentNotesFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMVOTECONSOLIDATIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MVoteConsolidationFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMMREPORTPRINTINGFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MReportPrintingFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMLOGREPORTFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MLogReportFunctionality,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMSHUTDOWMMACHINEFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MShutdownMachine,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMFILLASSISTEDACTIVATIONINFOFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MFillAssistedActivationInfo,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMACTIVATIONCONSOLIDATIONFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::MActivationConsolidation,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMVOTINGFORDISABLEDFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::VOTING_FOR_DISABLED,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMPOLICENOTESFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::POLICE_NOTES,false);
			break;
		case MenuOptionType::CONFIGURATION_XMLMDATAUTILSVALIDATORFUNCTIONALITY:
			descriptor = new SaesMenuOptionDescriptor(MenuType::DATA_UTILS_VALIDATOR,false);
			break;
	}
	SaesMenuOptionDescriptor finalDescriptor = *descriptor;
	delete(descriptor);
	return finalDescriptor;
}

Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration * SAESGUIConfigurationManager::CreateFunctionalityWizardConfig()
{
	Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration* retVal = new Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration();

	Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration::WizardStatesConfigurationSequence wizardSteps;

	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration noInstalled;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration noPollworkerRegistered;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration noDemoVote;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration noInitiated;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration initiated;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration votingClosed;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration electionClosed;

	Smartmatic::SAES::Configuration::WizardStateHelpConfiguration helpConfig;
	Smartmatic::SAES::Configuration::WizardStateTimeLineConfiguration timelineConfig;
	Smartmatic::SAES::Configuration::WizardStateToolboxConfiguration toolboxConfig;

	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence notInstalledOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::ToolbarMenuOptionsSequence toolBars;

	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence notPollworkerRegisteredOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence noDemoVoteOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence notInitiatedOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence initiatedOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence votingClosedOptions;
	Smartmatic::SAES::Configuration::FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence electionClosedOptions;



	MenuOptions emptyOptions;

	XMLMenuOption showMenu;
	showMenu.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.MenuToolbar"));
	showMenu.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.MenuToolbar"));
	showMenu.setImageKey ("ui/MenuInToolbar.gif");
	showMenu.setCode (11);
	showMenu.setMappingKey (3);
	showMenu.setMappingKeyName ("Menu");
	showMenu.setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);
	showMenu.setMenuOptions (emptyOptions);


	//option openElection

	XMLMenuOption openElection;
	openElection.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.OpenElection"));
	openElection.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.OpenElection"));
	openElection.setImageKey ("");
	openElection.setCode (11);
	openElection.setMappingKey (3);
	openElection.setMappingKeyName ("HOLA");
	openElection.setOptionType (MenuOptionType::CONFIGURATION_XMLMOPENELECTIONFUNCTIONALITY);
	openElection.setMenuOptions (emptyOptions);


	//option closeElection
	XMLMenuOption closeElection;
	closeElection.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseElection"));
	closeElection.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseElection"));
	closeElection.setImageKey ("");
	closeElection.setCode (12);
	closeElection.setMappingKey (4);
	closeElection.setMappingKeyName ("@");
	closeElection.setOptionType (MenuOptionType::CONFIGURATION_XMLMCLOSEELECTIONFUNCTIONALITY);
	closeElection.setMenuOptions (emptyOptions);


	//option voting machine installation

	XMLMenuOption vmInstallation;
	vmInstallation.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingMachineInstallation"));
	vmInstallation.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingMachineInstallation"));
	vmInstallation.setImageKey ("ui/InstallMachineToolbar.gif");
	vmInstallation.setCode (13);
	vmInstallation.setMappingKey (5);
	vmInstallation.setMappingKeyName ("F");
	vmInstallation.setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTINGMACHINEINSTALLATIONFUNCTIONALITY);
	vmInstallation.setMenuOptions (emptyOptions);

	//option card activator
	XMLMenuOption electorActivation;
	electorActivation.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CardActivatorFuncionality"));
	electorActivation.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CardActivatorFuncionality"));
	electorActivation.setImageKey ("");
	electorActivation.setCode (142);
	electorActivation.setMappingKey (4);
	electorActivation.setMappingKeyName ("U");
	electorActivation.setOptionType (MenuOptionType::CONFIGURATION_XMLMCARDGENERATORFUNCTIONALITY);
	electorActivation.setMenuOptions (emptyOptions);

	XMLMenuOption assistedActivations;
	assistedActivations.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AssistedCardActivatorFuncionality"));
	assistedActivations.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AssistedCardActivatorFuncionality"));
	assistedActivations.setImageKey ("ui/AssistedActivationToolbar.gif");
	assistedActivations.setCode (143);
	assistedActivations.setMappingKey (9);
	assistedActivations.setMappingKeyName ("J");
	assistedActivations.setOptionType (MenuOptionType::CONFIGURATION_XMLMASSISTEDCARDGENERATORFUNCTIONALITY);
	assistedActivations.setMenuOptions (emptyOptions);

	XMLMenuOption votingForDisabledTool;
	votingForDisabledTool.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingForDisabledFunctionality"));
	votingForDisabledTool.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingForDisabledFunctionality"));
	votingForDisabledTool.setImageKey ("ui/VotingForDisabledToolbar.gif");
	votingForDisabledTool.setCode (160);
	votingForDisabledTool.setMappingKey (9);
	votingForDisabledTool.setMappingKeyName ("Y");
	votingForDisabledTool.setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTINGFORDISABLEDFUNCTIONALITY);
	votingForDisabledTool.setMenuOptions (emptyOptions);

	XMLMenuOption policeNotesTool;
	policeNotesTool.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PoliceNotesFunctionality"));
	policeNotesTool.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PoliceNotesFunctionality"));
	policeNotesTool.setImageKey ("ui/PoliceNotesToolbar.gif");
	policeNotesTool.setCode (180);
	policeNotesTool.setMappingKey (9);
	policeNotesTool.setMappingKeyName ("P");
	policeNotesTool.setOptionType (MenuOptionType::CONFIGURATION_XMLMPOLICENOTESFUNCTIONALITY);
	policeNotesTool.setMenuOptions (emptyOptions);

	//option voting process demo
	XMLMenuOption voteProcessDemo;
	voteProcessDemo.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteProcessDemo"));
	voteProcessDemo.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteProcessDemo"));
	voteProcessDemo.setImageKey ("ui/VotingExperienceDemoToolbar.gif");
	voteProcessDemo.setCode (141);
	voteProcessDemo.setMappingKey (3);
	voteProcessDemo.setMappingKeyName ("H");
	voteProcessDemo.setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTEPROCESSDEMOFUNCTIONALITY);
	voteProcessDemo.setMenuOptions (emptyOptions);

	// Vote Print Preview
	XMLMenuOption printPreview;
	printPreview.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotePrintPreview"));
	printPreview.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotePrintPreview"));
	printPreview.setImageKey ("ui/VotePrintPreviewToolbar.jpg");
	printPreview.setCode (143);
	printPreview.setMappingKey (5);
	printPreview.setMappingKeyName ("I");
	printPreview.setOptionType (MenuOptionType::CONFIGURATION_XMLMPRINTPREVIEWFUNCTIONALITY);
	printPreview.setMenuOptions (emptyOptions);


	// Incident Report
	XMLMenuOption incidentReport;
	incidentReport.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.IncidentReport"));
	incidentReport.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.IncidentReport"));
	incidentReport.setImageKey ("ui/TechIncidentReportToolbar.gif");
	incidentReport.setCode (25);
	incidentReport.setMappingKey (6);
	incidentReport.setMappingKeyName ("W");
	incidentReport.setOptionType (MenuOptionType::CONFIGURATION_XMLMINCIDENTREPORTFUNCTIONALITY);
	incidentReport.setMenuOptions (emptyOptions);

	// Statistics Report
	XMLMenuOption statisticsReport;
	statisticsReport.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.StatisticsReport"));
	statisticsReport.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.StatisticsReport"));
	statisticsReport.setImageKey ("ui/StatisticsToolbar.gif");
	statisticsReport.setCode (26);
	statisticsReport.setMappingKey (7);
	statisticsReport.setMappingKeyName ("X");
	statisticsReport.setOptionType (MenuOptionType::CONFIGURATION_XMLMSTATISTICSREPORTFUNCTIONALITY);
	statisticsReport.setMenuOptions (emptyOptions);


	XMLMenuOption logReport;
	logReport.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.LogReport"));
	logReport.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.LogReport"));
	logReport.setImageKey ("ui/ViewLogToolbar.gif");
	logReport.setCode (285);
	logReport.setMappingKey (99);
	logReport.setMappingKeyName ("<");
	logReport.setOptionType (MenuOptionType::CONFIGURATION_XMLMLOGREPORTFUNCTIONALITY);
	logReport.setMenuOptions (emptyOptions);

	// Poll Worker Register
	XMLMenuOption pollWorkerRegister;
	pollWorkerRegister.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PollWorkerRegister"));
	pollWorkerRegister.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PollWorkerRegister"));
	pollWorkerRegister.setImageKey ("ui/RegPollworkerToolbar.gif");
	pollWorkerRegister.setCode (281);
	pollWorkerRegister.setMappingKey (9);
	pollWorkerRegister.setMappingKeyName ("Z");
	pollWorkerRegister.setOptionType (MenuOptionType::CONFIGURATION_XMLMPOLLWORKERREGISTERFUNCTIONALITY);
	pollWorkerRegister.setMenuOptions (emptyOptions);

	XMLMenuOption closeVotation;
	closeVotation.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseVotation"));
	closeVotation.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseVotation"));
	closeVotation.setImageKey ("");
	closeVotation.setCode (282);
	closeVotation.setMappingKey (3);
	closeVotation.setMappingKeyName ("+");
	closeVotation.setOptionType (MenuOptionType::CONFIGURATION_XMLMCLOSEVOTATIONFUNCTIONALITY);
	closeVotation.setMenuOptions (emptyOptions);

	XMLMenuOption voteConsolidation;
	voteConsolidation.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteConsolidation"));
	voteConsolidation.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteConsolidation"));
	voteConsolidation.setImageKey ("");
	voteConsolidation.setCode (283);
	voteConsolidation.setMappingKey (4);
	voteConsolidation.setMappingKeyName ("-");
	voteConsolidation.setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTECONSOLIDATIONFUNCTIONALITY);
	voteConsolidation.setMenuOptions (emptyOptions);

	XMLMenuOption registerPresidentNotes;
	registerPresidentNotes.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RegisterPresidentNotes"));
	registerPresidentNotes.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RegisterPresidentNotes"));
	registerPresidentNotes.setImageKey ("ui/ExpertNotesToolbar.gif");
	registerPresidentNotes.setCode (284);
	registerPresidentNotes.setMappingKey (5);
	registerPresidentNotes.setMappingKeyName ("*");
	registerPresidentNotes.setOptionType (MenuOptionType::CONFIGURATION_XMLMREGISTERPRESIDENTNOTESFUNCTIONALITY);
	registerPresidentNotes.setMenuOptions (emptyOptions);


	//recovery card Generator
	XMLMenuOption recoveryCardGenerator;
	recoveryCardGenerator.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RecoveryCardActivatorFuncionality"));
	recoveryCardGenerator.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RecoveryCardActivatorFuncionality"));
	recoveryCardGenerator.setImageKey ("ui/SecurityCopyToolbar.gif");
	recoveryCardGenerator.setCode (121);
	recoveryCardGenerator.setMappingKey (4);
	recoveryCardGenerator.setMappingKeyName ("z");
	recoveryCardGenerator.setOptionType (MenuOptionType::CONFIGURATION_XMLMRECOVERYCARDGENERATORFUNCTIONALITY);
	recoveryCardGenerator.setMenuOptions (emptyOptions);

	XMLMenuOption reportPrinting;
	reportPrinting.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportPrinting"));
	reportPrinting.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportPrinting"));
	reportPrinting.setImageKey ("ui/RePrintPVToolbar.gif");
	reportPrinting.setCode (219);
	reportPrinting.setMappingKey (3);
	reportPrinting.setMappingKeyName ("S");
	reportPrinting.setOptionType (MenuOptionType::CONFIGURATION_XMLMMREPORTPRINTINGFUNCTIONALITY);
	reportPrinting.setMenuOptions (emptyOptions);

	//Set the tool bar, the same for all states for now
	//set toolbar options
	toolBars.push_back(showMenu);
	toolBars.push_back(vmInstallation);
	toolBars.push_back(pollWorkerRegister);
	toolBars.push_back(assistedActivations);
	toolBars.push_back(votingForDisabledTool);
	toolBars.push_back(policeNotesTool);
	toolBars.push_back(voteProcessDemo);
	toolBars.push_back(printPreview);
	toolBars.push_back(incidentReport);
	toolBars.push_back(statisticsReport);
	toolBars.push_back(logReport);
	toolBars.push_back(registerPresidentNotes);
	toolBars.push_back(recoveryCardGenerator);
	toolBars.push_back(reportPrinting);

	XMLLabelConfiguration ButtonsLabelConfiguration;
	ButtonsLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	ButtonsLabelConfiguration.setLabel_VerticalPadding(0);
	ButtonsLabelConfiguration.setLabel_HorizontalPadding(0);
	ButtonsLabelConfiguration.setLabel_Family("Verdana");
	ButtonsLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	ButtonsLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	ButtonsLabelConfiguration.setLabel_Size(16);

	XMLLabelConfiguration TitleHelpLabelConfiguration;
	TitleHelpLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	TitleHelpLabelConfiguration.setLabel_VerticalPadding(0);
	TitleHelpLabelConfiguration.setLabel_HorizontalPadding(0);
	TitleHelpLabelConfiguration.setLabel_Family("Verdana");
	TitleHelpLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	TitleHelpLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	TitleHelpLabelConfiguration.setLabel_Size(20);

	XMLLabelConfiguration HelpLabelConfiguration;
	HelpLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	HelpLabelConfiguration.setLabel_VerticalPadding(0);
	HelpLabelConfiguration.setLabel_HorizontalPadding(0);
	HelpLabelConfiguration.setLabel_Family("Verdana");
	HelpLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	HelpLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	HelpLabelConfiguration.setLabel_Size(14);



	/********** Configure Not installed********/
	//Set help for no installed
	helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NotInstalledStateTitleKey"));
	helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NotInstalledStateContentKey"));
	helpConfig.setRelativeImagePath("ui/NotInstalledHelpImage.gif");

	//set time line config
	timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NotInstalledStateNameKey"));
	timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NotInstalledStateDescKey"));
	timelineConfig.setRelativeImagePath("ui/NotInstalledTimeline.png");

	toolboxConfig.setToolboxElementHeight(70);
	toolboxConfig.setToolboxElementWidth(70);

	//set help configuration
	HelpConfiguration helpNoInstalled;
	helpNoInstalled.setImageHelp("ui/wizard-not-installed-help.gif");
	helpNoInstalled.setPdfHelp("ui/wizard-not-installed-help.pdf");
	helpNoInstalled.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.helpNoInstalled"));
	helpNoInstalled.setUseHelp(true);
	//helpNoInstalle.


	//set principal options
	notInstalledOptions.push_back(vmInstallation);


	//Assign options
	noInstalled.setPrincipalMenuOptions(notInstalledOptions);
	noInstalled.setToolbarMenuOptions(toolBars);
	//set properties
	noInstalled.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINSTALLED);
	noInstalled.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NotInstalledStateNameKey"));
	noInstalled.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NotInstalledStateDeskKey"));
	helpConfig.setHelp(helpNoInstalled);
	noInstalled.setStateHelp(helpConfig);
	noInstalled.setTimeLineConfiguration(timelineConfig);
	noInstalled.setToolboxConfiguration(toolboxConfig);
	noInstalled.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
	noInstalled.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
	noInstalled.setHelpLabelConfiguration(HelpLabelConfiguration);


	/********** Configure Not Pollworker********/
	//Set help for not pollworker
	helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NotPollworkerRegisteredStateTitleKey"));
	helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NotPollworkerRegisteredStateContentKey"));
	helpConfig.setRelativeImagePath("ui/NotPollworkerRegisteredHelpImage.gif");

	//set time line config
	timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NotPollworkerRegisteredStateNameKey"));
	timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NotPollworkerRegisteredStateDescKey"));
	timelineConfig.setRelativeImagePath("ui/NotPollworkerRegisteredTimeline.png");

	//set principal options
	notPollworkerRegisteredOptions.push_back(pollWorkerRegister);

	HelpConfiguration helpNoPollworkerRegistered;
	helpNoPollworkerRegistered.setImageHelp("ui/wizard-not-pollworker-registered-help.gif");
	helpNoPollworkerRegistered.setPdfHelp("ui/wizard-not-pollworker-registered-help.pdf");
	helpNoPollworkerRegistered.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.NoPollworkerRegistered"));
	helpNoPollworkerRegistered.setUseHelp(true);

	//Assign options
	noPollworkerRegistered.setPrincipalMenuOptions(notPollworkerRegisteredOptions);
	noPollworkerRegistered.setToolbarMenuOptions(toolBars);
	//set properties
	noPollworkerRegistered.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTPOLLWORKERREGISTERED);
	noPollworkerRegistered.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoPollworkerRegisteredStateNameKey"));
	noPollworkerRegistered.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoPollworkerRegisteredDeskKey"));
	helpConfig.setHelp(helpNoPollworkerRegistered);
	noPollworkerRegistered.setStateHelp(helpConfig);
	noPollworkerRegistered.setTimeLineConfiguration(timelineConfig);
	noPollworkerRegistered.setToolboxConfiguration(toolboxConfig);
	noPollworkerRegistered.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
	noPollworkerRegistered.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
	noPollworkerRegistered.setHelpLabelConfiguration(HelpLabelConfiguration);


	/********** Configure No demo vote********/
	//Set help for no demo
		helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NoDemoVoteStateTitleKey"));
		helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NoDemoVoteStateContentKey"));
		helpConfig.setRelativeImagePath("ui/NotDemonstrationVote.gif");

		//set time line config
		timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NoDemoVoteStateNameKey"));
		timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NoDemoVoteStateDescKey"));
		timelineConfig.setRelativeImagePath("ui/NoDemoVoteTimeline.png");

		//set principal options
		noDemoVoteOptions.push_back(voteProcessDemo);

		HelpConfiguration helpNoDemoVote;
		helpNoDemoVote.setImageHelp("ui/wizard-not-demonstration-vote-help.gif");
		helpNoDemoVote.setPdfHelp("ui/wizard-not-demonstration-vote-help.pdf");
		helpNoDemoVote.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.NoDemoVote"));
		helpNoDemoVote.setUseHelp(true);

		//Assign options
		noDemoVote.setPrincipalMenuOptions(noDemoVoteOptions);
		noDemoVote.setToolbarMenuOptions(toolBars);
		//set properties
		noDemoVote.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE);
		noDemoVote.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoDemoVoteStateNameKey"));
		noDemoVote.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoDemoVoteDeskKey"));
		helpConfig.setHelp(helpNoDemoVote);
		noDemoVote.setStateHelp(helpConfig);
		noDemoVote.setTimeLineConfiguration(timelineConfig);
		noDemoVote.setToolboxConfiguration(toolboxConfig);
		noDemoVote.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
		noDemoVote.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
		noDemoVote.setHelpLabelConfiguration(HelpLabelConfiguration);

		/********** Configure No initiated********/
		//Set help for no demo
		helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NoInitiatedStateTitleKey"));
		helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.NoInitiatedStateContentKey"));
		helpConfig.setRelativeImagePath("ui/NotInitiatedHelpImage.gif");

		//set time line config
		timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NoInitiatedStateNameKey"));
		timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.NoInitiatedStateDescKey"));
		timelineConfig.setRelativeImagePath("ui/NoInitiatedTimeline.png");

		//set principal options
		notInitiatedOptions.push_back(openElection);

		HelpConfiguration helpNoInitiated;
		helpNoInitiated.setImageHelp("ui/wizard-not-initiated-help.gif");
		helpNoInitiated.setPdfHelp("ui/wizard-not-initiated-help.pdf");
		helpNoInitiated.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.NoInitiated"));
		helpNoInitiated.setUseHelp(true);

		//Assign options
		noInitiated.setPrincipalMenuOptions(notInitiatedOptions);
		noInitiated.setToolbarMenuOptions(toolBars);
		//set properties
		noInitiated.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED);
		noInitiated.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoInitiatedStateNameKey"));
		noInitiated.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.NoInitiatedDeskKey"));
		helpConfig.setHelp(helpNoInitiated);
		noInitiated.setStateHelp(helpConfig);
		noInitiated.setTimeLineConfiguration(timelineConfig);
		noInitiated.setToolboxConfiguration(toolboxConfig);
		noInitiated.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
		noInitiated.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
		noInitiated.setHelpLabelConfiguration(HelpLabelConfiguration);

		/********** Configure initiated********/
		//Set help for no demo
		helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.InitiatedStateTitleKey"));
		helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.InitiatedStateContentKey"));
		helpConfig.setRelativeImagePath("ui/InitiatedHelpImage.gif");

		//set time line config
		timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.InitiatedStateNameKey"));
		timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.InitiatedStateDescKey"));
		timelineConfig.setRelativeImagePath("ui/InitiatedTimeline.png");

		//set principal options
		initiatedOptions.push_back(electorActivation);
		initiatedOptions.push_back(closeVotation);

		HelpConfiguration helpInitiated;
		helpInitiated.setImageHelp("ui/wizard-initiated-help.gif");
		helpInitiated.setPdfHelp("ui/wizard-initiated-help.pdf");
		helpInitiated.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.Initiated"));
		helpInitiated.setUseHelp(true);

		//Assign options
		initiated.setPrincipalMenuOptions(initiatedOptions);
		initiated.setToolbarMenuOptions(toolBars);
		//set properties
		initiated.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED);
		initiated.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.InitiatedStateNameKey"));
		initiated.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.InitiatedDeskKey"));
		helpConfig.setHelp(helpInitiated);
		initiated.setStateHelp(helpConfig);
		initiated.setTimeLineConfiguration(timelineConfig);
		initiated.setToolboxConfiguration(toolboxConfig);
		initiated.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
		initiated.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
		initiated.setHelpLabelConfiguration(HelpLabelConfiguration);

		/********** Configure VotingClosed********/
		//Set help for no demo
		helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.VotingClosedStateTitleKey"));
		helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.VotingClosedStateContentKey"));
		helpConfig.setRelativeImagePath("ui/VotingClosedHelpImage.gif");

		//set time line config
		timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.VotingClosedStateNameKey"));
		timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.VotingClosedStateDescKey"));
		timelineConfig.setRelativeImagePath("ui/VotingClosedTimeline.png");

		//set principal options
		votingClosedOptions.push_back(voteConsolidation);
		votingClosedOptions.push_back(closeElection);

		HelpConfiguration helpVotingClosed;
		helpVotingClosed.setImageHelp("ui/wizard-voting-closed-help.gif");
		helpVotingClosed.setPdfHelp("ui/wizard-voting-closed-help.pdf");
		helpVotingClosed.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.VotingClosed"));
		helpVotingClosed.setUseHelp(true);

		//Assign options
		votingClosed.setPrincipalMenuOptions(votingClosedOptions);
		votingClosed.setToolbarMenuOptions(toolBars);
		//set properties
		votingClosed.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED);
		votingClosed.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.VotingClosedStateNameKey"));
		votingClosed.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.VotingClosedDeskKey"));
		helpConfig.setHelp(helpVotingClosed);
		votingClosed.setStateHelp(helpConfig);
		votingClosed.setTimeLineConfiguration(timelineConfig);
		votingClosed.setToolboxConfiguration(toolboxConfig);
		votingClosed.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
		votingClosed.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
		votingClosed.setHelpLabelConfiguration(HelpLabelConfiguration);


		/********** Configure Election Closed********/
		//Set help for no demo
		helpConfig.setTitleKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.ElectionClosedStateTitleKey"));
		helpConfig.setContentKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Help.ElectionClosedStateContentKey"));
		helpConfig.setRelativeImagePath("ui/ElectionClosedHelpImage.gif");

		//set time line config
		timelineConfig.setNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.ElectionClosedStateNameKey"));
		timelineConfig.setDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.Timeline.ElectionClosedStateDescKey"));
		timelineConfig.setRelativeImagePath("ui/ElectionClosedTimeline.png");

		//set principal options
		electionClosedOptions.push_back(reportPrinting);

		HelpConfiguration helpElectionClosed;
		helpElectionClosed.setImageHelp("ui/wizard-election-closed-help.gif");
		helpElectionClosed.setPdfHelp("ui/wizard-election-closed-help.pdf");
		helpElectionClosed.setTitleKey(N_("Smartmatic.SAES.GUI.FunctionalityWizard.HelpConfiguration.ElectionClosed"));
		helpElectionClosed.setUseHelp(true);

		//Assign options
		electionClosed.setPrincipalMenuOptions(electionClosedOptions);
		electionClosed.setToolbarMenuOptions(toolBars);
		//set properties
		electionClosed.setProcessStatus(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED);
		electionClosed.setStateNameKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.ElectionClosedStateNameKey"));
		electionClosed.setStateDescriptionKey(N_("Smartmatic.SAES.Configuration.FunctionalityWizardStateConfiguration.ElectionClosedDeskKey"));
		helpConfig.setHelp(helpElectionClosed);
		electionClosed.setStateHelp(helpConfig);
		electionClosed.setTimeLineConfiguration(timelineConfig);
		electionClosed.setToolboxConfiguration(toolboxConfig);
		electionClosed.setButtonsLabelConfiguration(ButtonsLabelConfiguration);
		electionClosed.setTitleHelpLabelConfiguration(TitleHelpLabelConfiguration);
		electionClosed.setHelpLabelConfiguration(HelpLabelConfiguration);



	//register the states
	wizardSteps.push_back(noInstalled);
	wizardSteps.push_back(noPollworkerRegistered);
	wizardSteps.push_back(noDemoVote);
	wizardSteps.push_back(noInitiated);
	wizardSteps.push_back(initiated);
	wizardSteps.push_back(votingClosed);
	wizardSteps.push_back(electionClosed);

	retVal->setWizardStatesConfiguration(wizardSteps);

	return retVal;
}

SMMTMenuOption SAESGUIConfigurationManager::GetSMMTMenuOptionFromXMLMenuOption(XMLMenuOption xmlOption)
{
	SMMTMenuOption optReturn;

	optReturn.nameKey = xmlOption.getUntraslatedKey().c_str();
	optReturn.imageKey = xmlOption.getImageKey();
	optReturn.code = xmlOption.getCode();
	optReturn.mappingKey = xmlOption.getMappingKey();
	optReturn.mappingKeyName = xmlOption.getMappingKeyName ();
	optReturn.optionDescriptor = ConvertMenuOptionType(xmlOption.getOptionType ());
	optReturn.v_MenuOption = GetInnerOptions(xmlOption);

	return optReturn;
}

std::vector<Smartmatic::GUI::Widgets::WizardWidgetConfiguration> SAESGUIConfigurationManager::GetFunctionalityWizardConfiguration()
{
	std::vector<Smartmatic::GUI::Widgets::WizardWidgetConfiguration> wizardWidgetConfigurationVector;

	FunctionalityWizardFlowConfiguration wizardFlow =  (*configuration)->getFunctionalityWizardConfiguration();

	FunctionalityWizardFlowConfiguration::WizardStatesConfigurationSequence wizardStatesConfigurationSeq = wizardFlow.getWizardStatesConfiguration();
	FunctionalityWizardFlowConfiguration::WizardStatesConfigurationIterator iterWizardStatesConfiguration;

	for(iterWizardStatesConfiguration = wizardStatesConfigurationSeq.begin();
			iterWizardStatesConfiguration != wizardStatesConfigurationSeq.end();
			iterWizardStatesConfiguration++)
	{
		Smartmatic::GUI::Widgets::WizardWidgetConfiguration wizardWidgetConfiguration;

		FunctionalityWizardStateConfiguration functionalityWizardStateConfiguration = *iterWizardStatesConfiguration;

		FunctionalityWizardStateConfiguration::PrincipalMenuOptionsSequence principalSeq =
				functionalityWizardStateConfiguration.getPrincipalMenuOptions();

		FunctionalityWizardStateConfiguration::PrincipalMenuOptionsIterator principalIter;

		vector<SMMTMenuOption> principalVector;

		for(principalIter = principalSeq.begin(); principalIter != principalSeq.end(); principalIter++)
		{
			SMMTMenuOption opt = GetSMMTMenuOptionFromXMLMenuOption(*principalIter);
			principalVector.push_back(opt);
		}

		wizardWidgetConfiguration.setPrincipalOptions(principalVector);

		vector<SMMTMenuOption> toolVector;

		FunctionalityWizardStateConfiguration::ToolbarMenuOptionsSequence toolSeq =
				functionalityWizardStateConfiguration.getToolbarMenuOptions();

		FunctionalityWizardStateConfiguration::ToolbarMenuOptionsIterator toolIter;

		for(toolIter = toolSeq.begin(); toolIter != toolSeq.end(); toolIter++)
		{
			SMMTMenuOption opt = GetSMMTMenuOptionFromXMLMenuOption(*toolIter);
			toolVector.push_back(opt);
		}

		wizardWidgetConfiguration.setToolbox(toolVector);

		wizardWidgetConfiguration.setStateName(functionalityWizardStateConfiguration.getStateNameKey());

		wizardWidgetConfiguration.setStateDescription(functionalityWizardStateConfiguration.getStateDescriptionKey());

		wizardWidgetConfiguration.setStateHelpTitleKey(functionalityWizardStateConfiguration.getStateHelp().getTitleKey());
		wizardWidgetConfiguration.setStateHelpContentKey(functionalityWizardStateConfiguration.getStateHelp().getContentKey());
		wizardWidgetConfiguration.setStateHelpRelativeImagePath(functionalityWizardStateConfiguration.getStateHelp().getRelativeImagePath());
		wizardWidgetConfiguration.setTimelineNameKey(functionalityWizardStateConfiguration.getTimeLineConfiguration().getNameKey());
		wizardWidgetConfiguration.setTimelineDescriptionKey(functionalityWizardStateConfiguration.getTimeLineConfiguration().getDescriptionKey());
		wizardWidgetConfiguration.settimelineRelativeImagePath(functionalityWizardStateConfiguration.getTimeLineConfiguration().getRelativeImagePath());
		wizardWidgetConfiguration.setToolboxElementWidth(functionalityWizardStateConfiguration.getToolboxConfiguration().getToolboxElementWidth());
		wizardWidgetConfiguration.setToolboxElementHeight(functionalityWizardStateConfiguration.getToolboxConfiguration().getToolboxElementHeight());

		wizardWidgetConfiguration.setImageHelp(functionalityWizardStateConfiguration.getStateHelp().getHelp().getImageHelp());
		wizardWidgetConfiguration.setPdfHelp(functionalityWizardStateConfiguration.getStateHelp().getHelp().getPdfHelp());
		wizardWidgetConfiguration.setTitleKey(functionalityWizardStateConfiguration.getStateHelp().getHelp().getTitleKey());
		wizardWidgetConfiguration.setUseHelp(functionalityWizardStateConfiguration.getStateHelp().getHelp().getUseHelp());

		wizardWidgetConfiguration.setStateEnum(functionalityWizardStateConfiguration.getProcessStatus());
		wizardWidgetConfiguration.setEnumIntState((int) functionalityWizardStateConfiguration.getProcessStatus());

		wizardWidgetConfiguration.setHelpLabelConfiguration(ConvertToLabelConfiguration(functionalityWizardStateConfiguration.getHelpLabelConfiguration()));
		wizardWidgetConfiguration.setTitleHelpLabelConfiguration(ConvertToLabelConfiguration(functionalityWizardStateConfiguration.getTitleHelpLabelConfiguration()));
		wizardWidgetConfiguration.setButtonsLabelConfiguration(ConvertToLabelConfiguration(functionalityWizardStateConfiguration.getButtonsLabelConfiguration()));

		wizardWidgetConfigurationVector.push_back(wizardWidgetConfiguration);
	}
	return wizardWidgetConfigurationVector;
}

void SAESGUIConfigurationManager::LoadDefault()
{
	DeviceConfiguration barcodeDevice(DeviceConfiguration::CONFIGURATION_BARCODE);
	DeviceConfiguration smartcardDevice(DeviceConfiguration::CONFIGURATION_SMARTCARD);
	DeviceConfiguration printerDevice(DeviceConfiguration::CONFIGURATION_PRINTER);
	
	Smartmatic::SAES::Configuration::EventSoundsConfiguration *eventSounds = new Smartmatic::SAES::Configuration::EventSoundsConfiguration();
	SaesGUIConfiguration *configSAESGUI = new SaesGUIConfiguration();
	XMLMenuOption reportProcess;
	XMLMenuOption votingMachine;
	XMLMenuOption mainteinanceMenu;
	XMLMenuOption validationMenu;
	XMLMenuOption *openElection = new XMLMenuOption ();
	XMLMenuOption *closeElection = new XMLMenuOption ();
	XMLMenuOption *registerPresidentNotes = new XMLMenuOption ();
	XMLMenuOption *logReport = new XMLMenuOption ();
	XMLMenuOption *diagnosis = new XMLMenuOption ();
	XMLMenuOption *cardActivators = new XMLMenuOption ();
	XMLMenuOption *alarmBoxDiagnosis = new XMLMenuOption ();
	XMLMenuOption *smartcardReaderDiagnosis = new XMLMenuOption ();
	XMLMenuOption *calibrationDiagnosis = new XMLMenuOption ();
	XMLMenuOption *brightnessDiagnosis = new XMLMenuOption ();
	XMLMenuOption *barcodeDiagnosis = new XMLMenuOption ();
	XMLMenuOption *allDiagnosis = new XMLMenuOption ();
	XMLMenuOption *flashDiagnosis = new XMLMenuOption ();
	XMLMenuOption *printerDiagnosis = new XMLMenuOption ();
	XMLMenuOption *changeHour = new XMLMenuOption ();
	XMLMenuOption *cardGenerator = new XMLMenuOption ();
	XMLMenuOption *assistedCardGenerator = new XMLMenuOption ();
	XMLMenuOption *recoveryCardGenerator = new XMLMenuOption ();
	XMLMenuOption *changeLanguage = new XMLMenuOption ();
	XMLMenuOption *vmInstallation = new XMLMenuOption ();
	XMLMenuOption *voteProcessDemo = new XMLMenuOption ();
	XMLMenuOption *printPreview = new XMLMenuOption ();
	XMLMenuOption *incidentReport = new XMLMenuOption ();
	XMLMenuOption *statisticsReport = new XMLMenuOption ();
	XMLMenuOption *pollWorkerRegister = new XMLMenuOption ();	
	XMLMenuOption *votingExperienceValidation = new XMLMenuOption ();
	XMLMenuOption *closeVotation= new XMLMenuOption ();
	XMLMenuOption *voteConsolidation= new XMLMenuOption ();
	XMLMenuOption *reportPrinting = new XMLMenuOption ();
	XMLMenuOption *shutDownMenuOption = new XMLMenuOption ();
	XMLMenuOption *fillAssistedActivationInfo = new XMLMenuOption();
	XMLMenuOption *activationConsolidation = new XMLMenuOption();

	Smartmatic::SAES::Configuration::MenuOptions *optionsProcessReport = new  MenuOptions ();
	Smartmatic::SAES::Configuration::MenuOptions *optionsVotingMachine = new  MenuOptions ();
	Smartmatic::SAES::Configuration::MenuOptions *optionsMaintenance = new  MenuOptions ();
	Smartmatic::SAES::Configuration::MenuOptions *optionsValidations = new  MenuOptions ();
	Smartmatic::SAES::Configuration::MenuOptions *optionsDiagnosis = new  MenuOptions ();
	Smartmatic::SAES::Configuration::MenuOptions *optionsCardActivators = new  MenuOptions ();
	MenuOptions::OptionSequence *seqOptionsReportingProcess = new MenuOptions::OptionSequence();
	MenuOptions::OptionSequence *seqOptionsVotingMachine = new MenuOptions::OptionSequence();
	MenuOptions::OptionSequence *seqOptionsMaintenance = new MenuOptions::OptionSequence();
	MenuOptions::OptionSequence *seqOptionsValidations = new MenuOptions::OptionSequence();
	MenuOptions::OptionSequence *seqOptionsDiagnosis = new MenuOptions::OptionSequence();
	MenuOptions::OptionSequence *seqOptionsCardActivators = new MenuOptions::OptionSequence();
	Smartmatic::SAES::Configuration::MenuOptions *optionsRoot = new  MenuOptions ();
	MenuOptions::OptionSequence *seqRoot = new MenuOptions::OptionSequence();
	XMLMenuOption *rootPresidentMachineOption = new XMLMenuOption ();
	XMLMenuOption *rootVotingMachineOption = new XMLMenuOption ();
	XMLMenuWidgetConfiguration *pollBookMachineConfiguration = new XMLMenuWidgetConfiguration(); 
	XMLMenuWidgetConfiguration *votingMachineConfiguration = new XMLMenuWidgetConfiguration ();
	VotingExperienceConfiguration *votingExperienceConfiguration = new VotingExperienceConfiguration();
	VotingWindowConfiguration *votingWindowConfiguration = new VotingWindowConfiguration();
	CustomAtributtesWindowConfiguration *customAtributtesWindowConfiguration = new CustomAtributtesWindowConfiguration();
	ConfirmationWindowConfiguration *confirmationWindowConfiguration = new ConfirmationWindowConfiguration();
	VotingExperienceLabelConfiguration *votingExperienceLabelConfiguration = new VotingExperienceLabelConfiguration();
	InstallationWizardConfiguration *installWizardConfig = new InstallationWizardConfiguration();
	PMWidgetConfiguration *pmWidgetConfig = new PMWidgetConfiguration();
	FontConfiguration *votingWindowFont = new FontConfiguration();
	PartySelectionConfiguration* partySelection = new PartySelectionConfiguration();
	PartyWidgetConfiguration* partyWidget = new PartyWidgetConfiguration();
	DisplayType* displayTypeImage = new DisplayType("IMAGE");
	BallotOptionSelectionConfiguration* ballotOptionSelection = new BallotOptionSelectionConfiguration();
	BallotOptionWidgetConfiguration* ballotOptionWidget = new BallotOptionWidgetConfiguration();
	FontConfiguration *ballotOptionFont = new FontConfiguration();
	DisplayType* displayTypeText = new DisplayType("TEXT");
	ColorConfiguration* selectedColor = new ColorConfiguration();
	ColorConfiguration* unSelectedColor = new ColorConfiguration();
	GeneralDiagnosisConfiguration* generalDiag = new GeneralDiagnosisConfiguration();
	SmartCardReaderDiagnosisConfiguration* screaderDiagnosisConf = new SmartCardReaderDiagnosisConfiguration();

	PrinterDiagnosisConfiguration* printerDiagnosisConf = new PrinterDiagnosisConfiguration();
	BarcodeDiagnosisConfiguration* barcodeDiagnosisConf = new BarcodeDiagnosisConfiguration();
	BrightnessDiagnosisConfiguration* brightnessDiagnosisConf = new BrightnessDiagnosisConfiguration();
	TouchScreenCalibrationConfiguration *touchDiagConfig = new TouchScreenCalibrationConfiguration();
	AllDiagnosisConfiguration* allDiagnosisConf = new AllDiagnosisConfiguration();
	AuthenticationWindowConfiguration authWindowConf;
	DurationWidgetConfiguration *durationConf = new DurationWidgetConfiguration();
	XMLLabelConfiguration* diagnosisLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* fillAssistedLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* fillAssistedNameLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* exitMessageLabelConfiguration = new XMLLabelConfiguration();
	AutomaticWindowConfiguration::DiagnosticToApplySequence *seqDiagnosticToApply = new AllDiagnosisConfiguration::DiagnosticToApplySequence();
//	AutomaticWindowConfiguration::DiagnosticWithoutCalibrationSequence *seqDiagnosticWithoutCalibration = new AutomaticWindowConfiguration::DiagnosticWithoutCalibrationSequence();
	AutomaticWindowConfiguration::DiagnosticToApplySequence *seqAutoDiagnosticToApply = new AutomaticWindowConfiguration::DiagnosticToApplySequence();
	AutomaticWindowConfiguration* autoDiagnosisConf = new AutomaticWindowConfiguration();
	CardActivatorFunctionalityConfiguration* activationCardConf = new CardActivatorFunctionalityConfiguration();
	CardRecoveryFunctionalityConfiguration* recoveryCardConf = new CardRecoveryFunctionalityConfiguration();
	VoteDemoFunctionalityConfiguration *voteDemoConf = new VoteDemoFunctionalityConfiguration();
	CardAssistedActivationFunctionalityConfiguration* assistedCardConf = new CardAssistedActivationFunctionalityConfiguration();
	ColorConfiguration* selectedColorCardActiv = new ColorConfiguration();
	ColorConfiguration* unSelectedColorCardActiv = new ColorConfiguration();
	ReferendumConfiguration* referendumConfiguration = new ReferendumConfiguration();
	
	LanguageSelectionWindowConfiguration* languageSelectionConf = new LanguageSelectionWindowConfiguration();
	ContingencyCardWidgetConfiguration* contingencyCardWidget = new ContingencyCardWidgetConfiguration ();
	WaitingForCardWindowConfiguration* waitingCardWindow = new WaitingForCardWindowConfiguration();
	LanguageButton* buttonInfoEn = new LanguageButton();
	LanguageButton* buttonInfoNl = new LanguageButton();
	LanguageSelectionWindowConfiguration::LanguageButtonSequence *seqLanguageButtonSequence = new LanguageSelectionWindowConfiguration::LanguageButtonSequence();
	FunctionalitiesConfiguration *funcConfiguration = new FunctionalitiesConfiguration();
	FunctionalitiesConfiguration::FunctionalityConfigurationSequence *funcConfigSequence = new FunctionalitiesConfiguration::FunctionalityConfigurationSequence();
	RunFunctionalityConfiguration *runFuncConfig = new RunFunctionalityConfiguration();
	StatisticFunctionalityConfiguration *statsConfiguration = new StatisticFunctionalityConfiguration();
	OpenElectionFunctionalityConfiguration* openElectionConfig = new OpenElectionFunctionalityConfiguration();
	CloseElectionFunctionalityConfiguration* closeElectionconfig = new CloseElectionFunctionalityConfiguration();
	IncidentReportFunctionalityConfiguration* incidentReportConfig = new IncidentReportFunctionalityConfiguration();
	PollWorkerRegisterFunctionalityConfiguration* pollWorkerFunconfig = new PollWorkerRegisterFunctionalityConfiguration();
	LogReportFunctionalityConfiguration logReportFunconfig;
	CloseNotetFunctionalityConfiguration closeNoteFunConfig;
	VoteConsolidationFunctionalityConfiguration* voteConsolidationFuncConfig = new VoteConsolidationFunctionalityConfiguration();
	PrintPreviewFunctionalityConfiguration * printPreviewFuncConfig = new PrintPreviewFunctionalityConfiguration();
	XMLLabelConfiguration resultErrorLabelConfiguration;
	VotingExperienceValidationScreensFunctionalityConfiguration* votingExperienceValidationScreensConf = new VotingExperienceValidationScreensFunctionalityConfiguration();

	MemoryStateWidgetConfiguration memoryStateWidgetConfiguration;

	Smartmatic::SAES::Configuration::ButtonConfiguration memoryStateButtonConf;
	memoryStateButtonConf.setButtonWidth(1000);
	memoryStateButtonConf.setButtonHeight(65);
	memoryStateButtonConf.setFontSize(16);

	XMLLabelConfiguration memoryStateTitleFontConf;
	memoryStateTitleFontConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	memoryStateTitleFontConf.setLabel_VerticalPadding(1);
	memoryStateTitleFontConf.setLabel_HorizontalPadding(1);
	memoryStateTitleFontConf.setLabel_Family("Arial");
	memoryStateTitleFontConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	memoryStateTitleFontConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	memoryStateTitleFontConf.setLabel_Size(20);

	memoryStateWidgetConfiguration.setButtonDelay (4000);
	memoryStateWidgetConfiguration.setButtonConf(memoryStateButtonConf);
	memoryStateWidgetConfiguration.setTextFontConf(memoryStateTitleFontConf);

	HelpWidgetConfiguration helpWidgetConfiguration;
	Smartmatic::SAES::Configuration::ButtonConfiguration helpButtonConf;
	helpButtonConf.setButtonWidth(200);
	helpButtonConf.setButtonHeight(60);
	helpButtonConf.setFontSize(18);

	helpWidgetConfiguration.setPrintButtonConf(helpButtonConf);

	configSAESGUI->setMemoryStateWidgetConfiguration(memoryStateWidgetConfiguration);
	configSAESGUI->setHelpWidgetConfiguration(helpWidgetConfiguration);

	Smartmatic::SAES::Configuration::ButtonConfiguration contingencyCardWidgetRetryButtonConf;
	contingencyCardWidgetRetryButtonConf.setButtonWidth(250);
	contingencyCardWidgetRetryButtonConf.setButtonHeight(60);
	contingencyCardWidgetRetryButtonConf.setFontSize(16);

	Smartmatic::SAES::Configuration::ButtonConfiguration contingencyCardWidgetShutdownButtonConf;
	contingencyCardWidgetShutdownButtonConf.setButtonWidth(250);
	contingencyCardWidgetShutdownButtonConf.setButtonHeight(60);
	contingencyCardWidgetShutdownButtonConf.setFontSize(16);

	XMLLabelConfiguration contingencyCardWidgetTitleFontConf;
	contingencyCardWidgetTitleFontConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	contingencyCardWidgetTitleFontConf.setLabel_VerticalPadding(1);
	contingencyCardWidgetTitleFontConf.setLabel_HorizontalPadding(1);
	contingencyCardWidgetTitleFontConf.setLabel_Family("Arial");
	contingencyCardWidgetTitleFontConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	contingencyCardWidgetTitleFontConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	contingencyCardWidgetTitleFontConf.setLabel_Size(20);

	XMLLabelConfiguration contingencyCardWidgetTextFontConf;
	contingencyCardWidgetTextFontConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	contingencyCardWidgetTextFontConf.setLabel_VerticalPadding(1);
	contingencyCardWidgetTextFontConf.setLabel_HorizontalPadding(1);
	contingencyCardWidgetTextFontConf.setLabel_Family("Arial");
	contingencyCardWidgetTextFontConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	contingencyCardWidgetTextFontConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	contingencyCardWidgetTextFontConf.setLabel_Size(12);

	ButtonBoxConfiguration* buttonBoxConfig = new ButtonBoxConfiguration(170, 50, 20);
	ButtonBoxConfiguration* buttonBoxIncidentConfig = new ButtonBoxConfiguration(150, 60, 30);
	ButtonBoxConfiguration* buttonBoxPollConfig = new ButtonBoxConfiguration(150, 40, 15);
	XMLLabelConfiguration pollWorkerDialogLabelConfiguration;
	ThemesConfiguration *themesConfiguration = new ThemesConfiguration();
	OfficialThemeConfiguration *officialThemeConfiguration = new OfficialThemeConfiguration();
	DemoThemeConfiguration *demoThemeConfiguration = new DemoThemeConfiguration();
	RecoveryThemeConfiguration *recoveryThemeConfiguration = new RecoveryThemeConfiguration();

	XMLLabelConfiguration PartyLabelConfiguration;
	XMLLabelConfiguration PartyNumberLabelConfiguration;
	XMLLabelConfiguration PartyNullLabelConfiguration;
	XMLLabelConfiguration BallotListLabelConfiguration;
	XMLLabelConfiguration BallotListNumberLabelConfiguration;
	XMLLabelConfiguration BallotNumberLabelConfiguration;
	XMLLabelConfiguration BallotTopLabelConfiguration;
	XMLLabelConfiguration BallotBottomLabelConfiguration;		
	XMLLabelConfiguration* selectionLanguageHeaderLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* selectionLanguageBottomLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* selectionLanguageConfirmationHeaderLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* selectionLanguageConfirmationBottomLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* selectionLanguageConfirmationCenterLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteHeaderLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteBottomLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteCenterLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteConfirmationHeaderLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteConfirmationBottomLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* superWhiteConfirmationCenterLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* contestWhiteSelectionHeaderLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* contestWhiteSelectionBottomLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* contestWhiteSelectionCenterLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* welcomeContestCenterLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* votingWidgetLabelChildLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* votingWidgetTopChildLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* votingWidgetBottomChildLabelConfiguration = new XMLLabelConfiguration();		
	XMLLabelConfiguration* votingWidgetNumberChildLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* votingWidgetPartySelectionLabelChildLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration*  votingWindowEndMessageLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* loadingBallotsLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* checkSumLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* interrupVotingExperienceMessageLabelConfiguration = new XMLLabelConfiguration();
	XMLLabelConfiguration* interrupVotingExperienceCancelLabelConfiguration = new XMLLabelConfiguration();

	Smartmatic::SAES::Configuration::FunctionalityWizardFlowConfiguration * functionalityWizardConfig = CreateFunctionalityWizardConfig();


	ElectionBlockStatusList* listElectionNotInitiated = new ElectionBlockStatusList();
	ElectionBlockStatusList* listElectionInitiated = new ElectionBlockStatusList();
	ElectionBlockStatusList* listElectionClosed = new ElectionBlockStatusList();
	ElectionBlockStatusList* listElectionResults = new ElectionBlockStatusList();

	HelpConfiguration helpStandardFunctionality;
	helpStandardFunctionality.setImageHelp("ui/standard-help-image-help.gif");
	helpStandardFunctionality.setPdfHelp("ui/standard-help-pdf-help.pdf");
	helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.Generic"));
	helpStandardFunctionality.setUseHelp(false);

	ElectionBlockStatusList::ElectionStatusSequence seq1;
	seq1.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED);
	seq1.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED);
	seq1.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED);
	listElectionNotInitiated->setElectionStatus(seq1);

	ElectionBlockStatusList::ElectionStatusSequence seq2;
	seq2.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED);
	seq2.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED);
	seq2.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED);
	listElectionInitiated->setElectionStatus(seq2);

	ElectionBlockStatusList::ElectionStatusSequence seq3;
	seq3.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED);
	seq3.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED);
	seq3.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED);
	listElectionClosed->setElectionStatus(seq3);

	ElectionBlockStatusList::ElectionStatusSequence seq4;
	seq4.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED);
	seq4.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_INITIATED);
	seq4.push_back(Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_CLOSED);
	listElectionResults->setElectionStatus(seq4);


	/************* ReportPrintingWidget Label Configuration *****************************/

	ReportPrintingWidgetConfiguration* reportPrintingWidgetConfiguration = new ReportPrintingWidgetConfiguration ();
	
	XMLLabelConfiguration* compositeDescriptionLabelConfiguration = new XMLLabelConfiguration ();
	XMLLabelConfiguration* reportListTitleLabelConfiguration = new XMLLabelConfiguration ();
	XMLLabelConfiguration* progressMessageLabelConfiguration = new XMLLabelConfiguration ();
	XMLLabelConfiguration* reportListItemLabelConfiguration = new XMLLabelConfiguration ();

	compositeDescriptionLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	compositeDescriptionLabelConfiguration->setLabel_VerticalPadding(0);
	compositeDescriptionLabelConfiguration->setLabel_HorizontalPadding(0);
	compositeDescriptionLabelConfiguration->setLabel_Family("Verdana");
	compositeDescriptionLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	compositeDescriptionLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
	compositeDescriptionLabelConfiguration->setLabel_Size(15);

	reportListTitleLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	reportListTitleLabelConfiguration->setLabel_VerticalPadding(0);
	reportListTitleLabelConfiguration->setLabel_HorizontalPadding(0);
	reportListTitleLabelConfiguration->setLabel_Family("Verdana");
	reportListTitleLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	reportListTitleLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
	reportListTitleLabelConfiguration->setLabel_Size(15);

	progressMessageLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	progressMessageLabelConfiguration->setLabel_VerticalPadding(0);
	progressMessageLabelConfiguration->setLabel_HorizontalPadding(0);
	progressMessageLabelConfiguration->setLabel_Family("Verdana");
	progressMessageLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	progressMessageLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	progressMessageLabelConfiguration->setLabel_Size(15);

	reportListItemLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
	reportListItemLabelConfiguration->setLabel_VerticalPadding(0);
	reportListItemLabelConfiguration->setLabel_HorizontalPadding(0);
	reportListItemLabelConfiguration->setLabel_Family("Verdana");
	reportListItemLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	reportListItemLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	reportListItemLabelConfiguration->setLabel_Size(15);

	reportPrintingWidgetConfiguration->setCompositeDescriptionLabelConfiguration (*compositeDescriptionLabelConfiguration);
	reportPrintingWidgetConfiguration->setReportListTitleLabelConfiguration (*reportListTitleLabelConfiguration);
	reportPrintingWidgetConfiguration->setProgressMessageLabelConfiguration (*progressMessageLabelConfiguration);
	reportPrintingWidgetConfiguration->setReportListItemLabelConfiguration (*reportListItemLabelConfiguration);

	configSAESGUI->setReportPrintingWidget(*reportPrintingWidgetConfiguration);
	configSAESGUI->setForceToLoadFrame(true);
	configSAESGUI->setSendBarcodeConfigurationOnReconnectWidget(true);
	configSAESGUI->setBeidCardUseThread(false);
	configSAESGUI->setBeidCardShowRemoveMessage(true);
	configSAESGUI->setBeidShowIdCard(false);
	configSAESGUI->setPMInstallationWidgetShowPrintPasswordButton(true);
	configSAESGUI->setShowBeidEntry(ShowBeidEntryTypeConfiguration::CONFIGURATION_NOSHOW);

	/************* Start Voting Installation Window Configuration *****************************/

    VMInstallationWidgetConfiguration vMInstallationWidgetConfiguration(
    		VMInstallationWidgetTypeConfiguration::CONFIGURATION_KEYWORDANDTOKENXML,
    		270, 100);

	configSAESGUI->setVMInstallationConfiguration(vMInstallationWidgetConfiguration);

	/************* End Voting Installation Window Configuration *****************************/

	exitMessageLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	exitMessageLabelConfiguration->setLabel_VerticalPadding(1);
	exitMessageLabelConfiguration->setLabel_HorizontalPadding(1);
	exitMessageLabelConfiguration->setLabel_Family("Verdana");
	exitMessageLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	exitMessageLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	exitMessageLabelConfiguration->setLabel_Size(20);
	configSAESGUI->setExitMessageLabelConfiguration(*exitMessageLabelConfiguration);

	configSAESGUI->setBlockMemoryBehaviorMenu(MemoryBlock::CONFIGURATION_SUSPEND);

	/************* End ReportPrintingWidget Label Configuration *****************************/

	/************* Start Close Voting Configuration *****************************/

	CloseVotationFunctionalityConfiguration* closeVotationConfig = new CloseVotationFunctionalityConfiguration ();
	closeVotationConfig->setRequestForID(true);
	closeVotationConfig->setMinimumOfficialsActivationForConfirmation(1);
	closeVotationConfig->setShowConfirmationMessageWhenClosing(true);
	configSAESGUI->setCloseVotationFunctionalityConfiguration(*closeVotationConfig);

	/************* End Close Voting Configuration *****************************/

	/************* Start initialization window Configuration *****************************/

	InitializationWindowConfiguration* initializationWindowConfiguration = new InitializationWindowConfiguration();
	initializationWindowConfiguration->setRequestForIDOnPresidentMachineInitialization(true);
	initializationWindowConfiguration->setContingencyCardEnabled (false);
	exitMessageLabelConfiguration->setLabel_Size(16);
	initializationWindowConfiguration->setRemoveContingencyCardTitle(*exitMessageLabelConfiguration);
	exitMessageLabelConfiguration->setLabel_Size(12);
	initializationWindowConfiguration->setRemoveContingencyCardText(*exitMessageLabelConfiguration);

	configSAESGUI->setInitializationWindowConfiguration(*initializationWindowConfiguration);

	/************* End initialization window Configuration *****************************/

	FormsCommonControlsConfigurations* formCommonControl = CreateCommonControlsConfigurations();


	PollingCardConfiguration pollingCardConfiguration;
	pollingCardConfiguration.setPMInstallationWindow(1000);
	pollingCardConfiguration.setVMInstallationWindow(1000);
	pollingCardConfiguration.setVotingExperienceWindow(1000);
	pollingCardConfiguration.setEndVotingExperienceWindow(1000);
	pollingCardConfiguration.setAssistedCardGeneratorFunctionality(2000);
	pollingCardConfiguration.setCardGeneratorFunctionality(1000);
	pollingCardConfiguration.setRecoveryCardGeneratorFunctionality(2000);
	pollingCardConfiguration.setVoteProcessDemoFunctionality(2000);
	pollingCardConfiguration.setBEIDCardWidget(1000);
	pollingCardConfiguration.setActivationStatsWidget(1000);
	pollingCardConfiguration.setWaitingCardWidget(1000);
	pollingCardConfiguration.setSmartCardReaderDiagnosisWidget(1000);
	pollingCardConfiguration.setVotingMachineInstallationWidgetInsert(1500);
	pollingCardConfiguration.setVotingMachineInstallationWidgetExtract(1500);

	AlarmBoxMonitorConfiguration alarmBoxMonitorConfiguration;
	alarmBoxMonitorConfiguration.setEnable(false);
	alarmBoxMonitorConfiguration.setMonitoringTime(5000);
	alarmBoxMonitorConfiguration.setSearchTime(2000);

	BEIDCardWidgetConfiguration beidCardWidgetConfiguration;

	XMLLabelConfiguration beidCardWidgetTitleFontConf;
	beidCardWidgetTitleFontConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	beidCardWidgetTitleFontConf.setLabel_VerticalPadding(1);
	beidCardWidgetTitleFontConf.setLabel_HorizontalPadding(1);
	beidCardWidgetTitleFontConf.setLabel_Family("Arial");
	beidCardWidgetTitleFontConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	beidCardWidgetTitleFontConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	beidCardWidgetTitleFontConf.setLabel_Size(20);

	XMLLabelConfiguration beidCardWidgetTextFontConf;
	beidCardWidgetTextFontConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
	beidCardWidgetTextFontConf.setLabel_VerticalPadding(1);
	beidCardWidgetTextFontConf.setLabel_HorizontalPadding(1);
	beidCardWidgetTextFontConf.setLabel_Family("Arial");
	beidCardWidgetTextFontConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
	beidCardWidgetTextFontConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
	beidCardWidgetTextFontConf.setLabel_Size(16);


	beidCardWidgetConfiguration.setTitleErrorFontConf(beidCardWidgetTitleFontConf);
	beidCardWidgetConfiguration.setTextErrorFontConf(beidCardWidgetTextFontConf);
	beidCardWidgetConfiguration.setTimeoutError(4000);

	IDConfig idCardConfig;

	IDProperties idPropertiesGeneric(true);
	idPropertiesGeneric.setType(ElementType::CONFIGURATION_ALPHA);
	idPropertiesGeneric.setMax(80);

	idCardConfig.setName(idPropertiesGeneric);
	idCardConfig.setLastName(idPropertiesGeneric);

	IDCardProcessConfiguration idCardProcessConfiguration;
	idCardProcessConfiguration.setPMInstall(idCardConfig);
	idCardProcessConfiguration.setVMInstall(idCardConfig);
	idCardProcessConfiguration.setOpenElection(idCardConfig);
	idCardProcessConfiguration.setCloseVotation(idCardConfig);
	idCardProcessConfiguration.setCloseElection(idCardConfig);
	idCardProcessConfiguration.setCloseNoteRegister(idCardConfig);
	idCardProcessConfiguration.setIncidentReport(idCardConfig);
	idCardProcessConfiguration.setAssistedActivation(idCardConfig);
	idCardProcessConfiguration.setDisabledVoter(idCardConfig);
	idCardProcessConfiguration.setDisabledVoterHelper(idCardConfig);
	idCardProcessConfiguration.setPoliceNote(idCardConfig);

	try
	{
		stringstream ss;
		
		Smartmatic::ConfigurationTypes::String defaultString("defaultConfiguration");					
				//voting Machine Menu
				
				votingMachine.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingProcess"));
				votingMachine.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingProcess"));
				votingMachine.setImageKey ("votingmachine.jpg");
				votingMachine.setCode (0);
				votingMachine.setMappingKey (1);
				votingMachine.setMappingKeyName ("A");
				votingMachine.setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);

				mainteinanceMenu.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Maintenance"));
				mainteinanceMenu.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Maintenance"));
				mainteinanceMenu.setImageKey ("Maintenance.png");
				mainteinanceMenu.setCode (1);
				mainteinanceMenu.setMappingKey (2);
				mainteinanceMenu.setMappingKeyName ("B");
				mainteinanceMenu.setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);

				validationMenu.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.validationMenu"));
				validationMenu.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.validationMenu"));
				validationMenu.setImageKey ("Maintenance.png");
				validationMenu.setCode (2);
				validationMenu.setMappingKey (3);
				validationMenu.setMappingKeyName ("C");
				validationMenu.setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);

				reportProcess.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportingProcess"));
				reportProcess.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportingProcess"));
				reportProcess.setImageKey ("ReportingProcess.jpg");
				reportProcess.setCode (3);
				reportProcess.setMappingKey (4);
				reportProcess.setMappingKeyName ("D");
				reportProcess.setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);

						//option openElection
						
						openElection->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.OpenElection"));
						openElection->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.OpenElection"));
						openElection->setImageKey ("");
						openElection->setCode (11);
						openElection->setMappingKey (3);
						openElection->setMappingKeyName ("HOLA");
						openElection->setOptionType (MenuOptionType::CONFIGURATION_XMLMOPENELECTIONFUNCTIONALITY);
						openElection->setMenuOptions (* new MenuOptions ());


						//option closeElection
						
						closeElection->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseElection"));
						closeElection->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseElection"));
						closeElection->setImageKey ("");
						closeElection->setCode (12);
						closeElection->setMappingKey (4);
						closeElection->setMappingKeyName ("@");
						closeElection->setOptionType (MenuOptionType::CONFIGURATION_XMLMCLOSEELECTIONFUNCTIONALITY);
						closeElection->setMenuOptions (* new MenuOptions ());


						//option voting machine installation
						
						vmInstallation->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingMachineInstallation"));
						vmInstallation->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingMachineInstallation"));
						vmInstallation->setImageKey ("");
						vmInstallation->setCode (13);
						vmInstallation->setMappingKey (5);
						vmInstallation->setMappingKeyName ("F");
						vmInstallation->setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTINGMACHINEINSTALLATIONFUNCTIONALITY);
						vmInstallation->setMenuOptions (* new MenuOptions ());

						//option card activator
		
						cardActivators->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ActivationAndDemoProcess"));
						cardActivators->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ActivationAndDemoProcess"));
						cardActivators->setImageKey ("");
						cardActivators->setCode (14);
						cardActivators->setMappingKey (6);
						cardActivators->setMappingKeyName ("G");
						cardActivators->setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);
		
						//option voting process demo
						
						voteProcessDemo->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteProcessDemo"));
						voteProcessDemo->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteProcessDemo"));
						voteProcessDemo->setImageKey ("");
						voteProcessDemo->setCode (141);
						voteProcessDemo->setMappingKey (3);
						voteProcessDemo->setMappingKeyName ("H");
						voteProcessDemo->setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTEPROCESSDEMOFUNCTIONALITY);
						voteProcessDemo->setMenuOptions (* new MenuOptions ());
		
						// Vote Print Preview 
		
						printPreview->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotePrintPreview"));
						printPreview->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotePrintPreview"));
						printPreview->setImageKey ("");
						printPreview->setCode (143);
						printPreview->setMappingKey (5);
						printPreview->setMappingKeyName ("I");
						printPreview->setOptionType (MenuOptionType::CONFIGURATION_XMLMPRINTPREVIEWFUNCTIONALITY);
						printPreview->setMenuOptions (* new MenuOptions ());
		
						//option diagnosis
						
						diagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Diagnosis"));
						diagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Diagnosis"));
						diagnosis->setImageKey ("");
						diagnosis->setCode (21);
						diagnosis->setMappingKey (3);
						diagnosis->setMappingKeyName ("J");
						diagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);
						//diagnosis->setMenuOptions (* new MenuOptions ());

		
						//option alarmBoxDiagnosis
						
						alarmBoxDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AlarmBoxDiagnosis"));
						alarmBoxDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AlarmBoxDiagnosis"));
						alarmBoxDiagnosis->setImageKey ("");
						alarmBoxDiagnosis->setCode (211);
						alarmBoxDiagnosis->setMappingKey (3);
						alarmBoxDiagnosis->setMappingKeyName ("K");
						alarmBoxDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMALARMBOXDIAGNOSISFUNCTIONALITY);
						alarmBoxDiagnosis->setMenuOptions (* new MenuOptions ());

						//option smartcardReaderDiagnosis
						
						smartcardReaderDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.SmartcardReaderDiagnosis"));
						smartcardReaderDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.SmartcardReaderDiagnosis"));
						smartcardReaderDiagnosis->setImageKey ("");
						smartcardReaderDiagnosis->setCode (212);
						smartcardReaderDiagnosis->setMappingKey (4);
						smartcardReaderDiagnosis->setMappingKeyName ("L");
						smartcardReaderDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMSCREADERDIAGNOSISFUNCTIONALITY);
						smartcardReaderDiagnosis->setMenuOptions (* new MenuOptions ());

						//option printerDiagnosis
						
						printerDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PrinterDiagnosis"));
						printerDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PrinterDiagnosis"));
						printerDiagnosis->setImageKey ("");
						printerDiagnosis->setCode (213);
						printerDiagnosis->setMappingKey (5);
						printerDiagnosis->setMappingKeyName ("M");
						printerDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMPRINTERDIAGNOSISFUNCTIONALITY);
						printerDiagnosis->setMenuOptions (* new MenuOptions ());

						//option calibrationDiagnosis
							
						calibrationDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CalibrationDiagnosis"));
						calibrationDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CalibrationDiagnosis"));
						calibrationDiagnosis->setImageKey ("");
						calibrationDiagnosis->setCode (214);
						calibrationDiagnosis->setMappingKey (6);
						calibrationDiagnosis->setMappingKeyName ("N");
						calibrationDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMCALIBRATIONDIAGNOSISFUNCTIONALITY);
						calibrationDiagnosis->setMenuOptions (* new MenuOptions ());

						//option brightnessDiagnosis
							
						brightnessDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.BrightnessDiagnosis"));
						brightnessDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.BrightnessDiagnosis"));
						brightnessDiagnosis->setImageKey ("");
						brightnessDiagnosis->setCode (215);
						brightnessDiagnosis->setMappingKey (7);
						brightnessDiagnosis->setMappingKeyName ("O");
						brightnessDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMBRIGHTNESSDIAGNOSISFUNCTIONALITY);
						brightnessDiagnosis->setMenuOptions (* new MenuOptions ());

						//option barcodeDiagnosis
							
						barcodeDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.BarcodeDiagnosis"));
						barcodeDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.BarcodeDiagnosis"));
						barcodeDiagnosis->setImageKey ("");
						barcodeDiagnosis->setCode (216);
						barcodeDiagnosis->setMappingKey (8);
						barcodeDiagnosis->setMappingKeyName ("P");
						barcodeDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMBARCODEDIAGNOSISFUNCTIONALITY);
						barcodeDiagnosis->setMenuOptions (* new MenuOptions ());

						//option allDiagnosis
							
						allDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AllDiagnosis"));
						allDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AllDiagnosis"));
						allDiagnosis->setImageKey ("");
						allDiagnosis->setCode (217);
						allDiagnosis->setMappingKey (9);
						allDiagnosis->setMappingKeyName ("Q");
						allDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMALLDIAGNOSISFUNCTIONALITY);
						allDiagnosis->setMenuOptions (* new MenuOptions ());

						//option flashDiagnosis
							
						flashDiagnosis->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.FlashDiagnosis"));
						flashDiagnosis->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.FlashDiagnosis"));
						flashDiagnosis->setImageKey ("");
						flashDiagnosis->setCode (218);
						flashDiagnosis->setMappingKey (3);
						flashDiagnosis->setMappingKeyName ("R");
						flashDiagnosis->setOptionType (MenuOptionType::CONFIGURATION_XMLMFLASHDIAGNOSISFUNCTIONALITY);
						flashDiagnosis->setMenuOptions (* new MenuOptions ());


						//option report printing

						reportPrinting->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportPrinting"));
						reportPrinting->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ReportPrinting"));
						reportPrinting->setImageKey ("");
						reportPrinting->setCode (219);
						reportPrinting->setMappingKey (3);
						reportPrinting->setMappingKeyName ("S");
						reportPrinting->setOptionType (MenuOptionType::CONFIGURATION_XMLMMREPORTPRINTINGFUNCTIONALITY);
						reportPrinting->setMenuOptions (* new MenuOptions ());

						//option shutdown menu

						shutDownMenuOption->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Shutdowm"));
						shutDownMenuOption->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.Shutdowm"));
						shutDownMenuOption->setImageKey ("");
						shutDownMenuOption->setCode (888);
						shutDownMenuOption->setMappingKey (3);
						shutDownMenuOption->setMappingKeyName ("V");
						shutDownMenuOption->setOptionType (MenuOptionType::CONFIGURATION_XMLMSHUTDOWMMACHINEFUNCTIONALITY);
						shutDownMenuOption->setMenuOptions (* new MenuOptions ());

						//option changeHour
							
						changeHour->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.SetDateHour"));
						changeHour->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.SetDateHour"));
						changeHour->setImageKey ("");
						changeHour->setCode (22);
						changeHour->setMappingKey (4);
						changeHour->setMappingKeyName ("T");
						changeHour->setOptionType (MenuOptionType::CONFIGURATION_XMLMCHANGEHOURFUNCTIONALITY);
						changeHour->setMenuOptions (* new MenuOptions ());


						//card Generator

						cardGenerator->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CardActivatorFuncionality"));
						cardGenerator->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CardActivatorFuncionality"));
						cardGenerator->setImageKey ("");
						cardGenerator->setCode (142);
						cardGenerator->setMappingKey (4);
						cardGenerator->setMappingKeyName ("U");
						cardGenerator->setOptionType (MenuOptionType::CONFIGURATION_XMLMCARDGENERATORFUNCTIONALITY);
						cardGenerator->setMenuOptions (* new MenuOptions ());

						assistedCardGenerator->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AssistedCardActivatorFuncionality"));
						assistedCardGenerator->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.AssistedCardActivatorFuncionality"));
						assistedCardGenerator->setImageKey ("");
						assistedCardGenerator->setCode (143);
						assistedCardGenerator->setMappingKey (9);
						assistedCardGenerator->setMappingKeyName ("J");
						assistedCardGenerator->setOptionType (MenuOptionType::CONFIGURATION_XMLMASSISTEDCARDGENERATORFUNCTIONALITY);
						assistedCardGenerator->setMenuOptions (* new MenuOptions ());

						//Fill Assisted Activation Info

						fillAssistedActivationInfo->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.FillAssistedActivationInfo"));
						fillAssistedActivationInfo->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.FillAssistedActivationInfo"));
						fillAssistedActivationInfo->setImageKey ("");
						fillAssistedActivationInfo->setCode (144);
						fillAssistedActivationInfo->setMappingKey (3);
						fillAssistedActivationInfo->setMappingKeyName ("V");
						fillAssistedActivationInfo->setOptionType (MenuOptionType::CONFIGURATION_XMLMFILLASSISTEDACTIVATIONINFOFUNCTIONALITY);
						fillAssistedActivationInfo->setMenuOptions (* new MenuOptions ());

						//Fill Assisted Activation Info

						XMLMenuOption votingForDisabled;
						votingForDisabled.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingForDisabledFunctionality"));
						votingForDisabled.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingForDisabledFunctionality"));
						votingForDisabled.setImageKey ("");
						votingForDisabled.setCode (200);
						votingForDisabled.setMappingKey (10);
						votingForDisabled.setMappingKeyName ("Y");
						votingForDisabled.setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTINGFORDISABLEDFUNCTIONALITY);
						votingForDisabled.setMenuOptions (* new MenuOptions ());

						XMLMenuOption policeNotes;
						policeNotes.setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PoliceNotesFunctionality"));
						policeNotes.setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PoliceNotesFunctionality"));
						policeNotes.setImageKey ("");
						policeNotes.setCode (200);
						policeNotes.setMappingKey (10);
						policeNotes.setMappingKeyName ("P");
						policeNotes.setOptionType (MenuOptionType::CONFIGURATION_XMLMPOLICENOTESFUNCTIONALITY);
						policeNotes.setMenuOptions (* new MenuOptions ());

						//Activation Consolidation Functionality
						activationConsolidation->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ActivationConsolidationFunctionality"));
						activationConsolidation->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ActivationConsolidationFunctionality"));
						activationConsolidation->setImageKey ("");
						activationConsolidation->setCode (145);
						activationConsolidation->setMappingKey (2);
						activationConsolidation->setMappingKeyName ("W");
						activationConsolidation->setOptionType (MenuOptionType::CONFIGURATION_XMLMACTIVATIONCONSOLIDATIONFUNCTIONALITY);
						activationConsolidation->setMenuOptions (* new MenuOptions ());

						//Change language

						changeLanguage->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ChangeLanguageFuncionality"));
						changeLanguage->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.ChangeLanguageFuncionality"));
						changeLanguage->setImageKey ("");
						changeLanguage->setCode (24);
						changeLanguage->setMappingKey (5);
						changeLanguage->setMappingKeyName ("V");
						changeLanguage->setOptionType (MenuOptionType::CONFIGURATION_XMLMCHANGELANGUAGEFUNCTIONALITY);
						changeLanguage->setMenuOptions (* new MenuOptions ());

						// Incident Report
						incidentReport->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.IncidentReport"));
						incidentReport->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.IncidentReport"));
						incidentReport->setImageKey ("");
						incidentReport->setCode (25);
						incidentReport->setMappingKey (6);
						incidentReport->setMappingKeyName ("W");
						incidentReport->setOptionType (MenuOptionType::CONFIGURATION_XMLMINCIDENTREPORTFUNCTIONALITY);
						incidentReport->setMenuOptions (* new MenuOptions ());

						// Statistics Report
						statisticsReport->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.StatisticsReport"));
						statisticsReport->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.StatisticsReport"));
						statisticsReport->setImageKey ("");
						statisticsReport->setCode (26);
						statisticsReport->setMappingKey (7);
						statisticsReport->setMappingKeyName ("X");
						statisticsReport->setOptionType (MenuOptionType::CONFIGURATION_XMLMSTATISTICSREPORTFUNCTIONALITY);
						statisticsReport->setMenuOptions (* new MenuOptions ());

						votingExperienceValidation->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingExperienceValidationFunctionality"));
						votingExperienceValidation->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VotingExperienceValidationFunctionality"));
						votingExperienceValidation->setImageKey ("");
						votingExperienceValidation->setCode (27);
						votingExperienceValidation->setMappingKey (8);
						votingExperienceValidation->setMappingKeyName ("Y");
						votingExperienceValidation->setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTINGEXPERIENCEVALIDATIONFUNCTIONALITY);
						votingExperienceValidation->setMenuOptions (* new MenuOptions ());

						logReport->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.LogReport"));
						logReport->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.LogReport"));
						logReport->setImageKey ("");
						logReport->setCode (285);
						logReport->setMappingKey (99);
						logReport->setMappingKeyName ("<");
						logReport->setOptionType (MenuOptionType::CONFIGURATION_XMLMLOGREPORTFUNCTIONALITY);
						logReport->setMenuOptions (* new MenuOptions ());

						// Poll Worker Register
						pollWorkerRegister->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PollWorkerRegister"));
						pollWorkerRegister->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.PollWorkerRegister"));
						pollWorkerRegister->setImageKey ("");
						pollWorkerRegister->setCode (281);
						pollWorkerRegister->setMappingKey (9);
						pollWorkerRegister->setMappingKeyName ("Z");
						pollWorkerRegister->setOptionType (MenuOptionType::CONFIGURATION_XMLMPOLLWORKERREGISTERFUNCTIONALITY);
						pollWorkerRegister->setMenuOptions (* new MenuOptions ());

						closeVotation->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseVotation"));
						closeVotation->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.CloseVotation"));
						closeVotation->setImageKey ("");
						closeVotation->setCode (282);
						closeVotation->setMappingKey (3);
						closeVotation->setMappingKeyName ("+");
						closeVotation->setOptionType (MenuOptionType::CONFIGURATION_XMLMCLOSEVOTATIONFUNCTIONALITY);
						closeVotation->setMenuOptions (* new MenuOptions ());

						voteConsolidation->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteConsolidation"));
						voteConsolidation->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.VoteConsolidation"));
						voteConsolidation->setImageKey ("");
						voteConsolidation->setCode (283);
						voteConsolidation->setMappingKey (4);
						voteConsolidation->setMappingKeyName ("-");
						voteConsolidation->setOptionType (MenuOptionType::CONFIGURATION_XMLMVOTECONSOLIDATIONFUNCTIONALITY);
						voteConsolidation->setMenuOptions (* new MenuOptions ());

						registerPresidentNotes->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RegisterPresidentNotes"));
						registerPresidentNotes->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RegisterPresidentNotes"));
						registerPresidentNotes->setImageKey ("");
						registerPresidentNotes->setCode (284);
						registerPresidentNotes->setMappingKey (5);
						registerPresidentNotes->setMappingKeyName ("*");
						registerPresidentNotes->setOptionType (MenuOptionType::CONFIGURATION_XMLMREGISTERPRESIDENTNOTESFUNCTIONALITY);
						registerPresidentNotes->setMenuOptions (* new MenuOptions ());


						//recovery card Generator

						recoveryCardGenerator->setNameKey (N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RecoveryCardActivatorFuncionality"));
						recoveryCardGenerator->setUntraslatedKey(N_("Smartmatic.SAES.GUI.Configuration.SAESGUIConfigurationManager.RecoveryCardActivatorFuncionality"));
						recoveryCardGenerator->setImageKey ("");
						recoveryCardGenerator->setCode (121);
						recoveryCardGenerator->setMappingKey (4);
						recoveryCardGenerator->setMappingKeyName ("z");
						recoveryCardGenerator->setOptionType (MenuOptionType::CONFIGURATION_XMLMRECOVERYCARDGENERATORFUNCTIONALITY);
						recoveryCardGenerator->setMenuOptions (* new MenuOptions ());


						seqOptionsDiagnosis->push_back(*alarmBoxDiagnosis);			
						seqOptionsDiagnosis->push_back(*allDiagnosis);
						seqOptionsDiagnosis->push_back(*barcodeDiagnosis);
						seqOptionsDiagnosis->push_back(*smartcardReaderDiagnosis);
						seqOptionsDiagnosis->push_back(*printerDiagnosis);	
						seqOptionsDiagnosis->push_back(*calibrationDiagnosis);
						seqOptionsDiagnosis->push_back(*brightnessDiagnosis);												
						seqOptionsDiagnosis->push_back(*flashDiagnosis);
						optionsDiagnosis->setOption (*seqOptionsDiagnosis);
						diagnosis->setMenuOptions (*optionsDiagnosis);

						seqOptionsMaintenance->push_back(*diagnosis);
						seqOptionsMaintenance->push_back(*changeHour);
						seqOptionsMaintenance->push_back(*changeLanguage);
						seqOptionsMaintenance->push_back(*votingExperienceValidation);
		
						//seqOptionsValidations->push_back(*votingExperienceValidation);
		
						optionsMaintenance->setOption (*seqOptionsMaintenance);
						optionsValidations->setOption(*seqOptionsValidations);

						mainteinanceMenu.setMenuOptions (*optionsMaintenance);
						validationMenu.setMenuOptions(*optionsValidations);
						//MenuOptions VotingMachineOption
					
						seqOptionsVotingMachine->push_back(*reportPrinting);
						seqOptionsVotingMachine->push_back(*shutDownMenuOption);
						seqOptionsVotingMachine->push_back(*openElection);
						seqOptionsVotingMachine->push_back(*closeElection);
						seqOptionsVotingMachine->push_back(*registerPresidentNotes);
						seqOptionsVotingMachine->push_back(*pollWorkerRegister);
						seqOptionsVotingMachine->push_back(*closeVotation);
						seqOptionsVotingMachine->push_back(*voteConsolidation);

						seqOptionsReportingProcess->push_back(*incidentReport);
						seqOptionsReportingProcess->push_back(*fillAssistedActivationInfo);
						seqOptionsReportingProcess->push_back(votingForDisabled);
						seqOptionsReportingProcess->push_back(policeNotes);
						seqOptionsReportingProcess->push_back(*logReport);
						seqOptionsReportingProcess->push_back(*pollWorkerRegister);
						seqOptionsReportingProcess->push_back(*statisticsReport);

						seqOptionsDiagnosis->push_back(*alarmBoxDiagnosis);
				
						seqOptionsCardActivators->push_back(*cardGenerator);
						seqOptionsCardActivators->push_back(*assistedCardGenerator);
						seqOptionsCardActivators->push_back(*recoveryCardGenerator);
						seqOptionsCardActivators->push_back(*activationConsolidation);

						seqOptionsCardActivators->push_back(*voteProcessDemo);
						seqOptionsCardActivators->push_back(*printPreview);
						optionsCardActivators->setOption (*seqOptionsCardActivators);
						cardActivators->setMenuOptions (*optionsCardActivators);
						//seqOptionsVotingMachine->push_back(*vmInstallation);

						seqOptionsVotingMachine->push_back(*vmInstallation);
						seqOptionsVotingMachine->push_back(*cardActivators);

		
					optionsVotingMachine->setOption (*seqOptionsVotingMachine);
					optionsProcessReport->setOption (*seqOptionsReportingProcess);

				votingMachine.setMenuOptions (*optionsVotingMachine);
				reportProcess.setMenuOptions (*optionsProcessReport);

				
			//Menu Options  Root
								
					seqRoot->push_back(votingMachine);
					seqRoot->push_back(reportProcess);
					seqRoot->push_back(mainteinanceMenu);
					//seqRoot->push_back(*validationMenu);
					optionsRoot->setOption (*seqRoot);

		// rootPollBookMachine

			rootPresidentMachineOption->setNameKey (N_("Smartmatic.SAES.GUI.HelpConfiguration.RootPresidentMachineOption"));
			rootPresidentMachineOption->setUntraslatedKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.RootPresidentMachineOption"));
			rootPresidentMachineOption->setImageKey ("rootPollBookMachine");
			rootPresidentMachineOption->setCode (-1);
			rootPresidentMachineOption->setMappingKey (-1);
			rootPresidentMachineOption->setMappingKeyName ("rootPollBookMachine");
			rootPresidentMachineOption->setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);
			rootPresidentMachineOption->setMenuOptions (*optionsRoot);

		// rootVotingMachine

			rootVotingMachineOption->setNameKey (N_("Smartmatic.SAES.GUI.HelpConfiguration.RootVotingMachineOption"));
			rootVotingMachineOption->setUntraslatedKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.RootVotingMachineOption"));
			rootVotingMachineOption->setImageKey ("rootVotingMachine");
			rootVotingMachineOption->setCode (-1);
			rootVotingMachineOption->setMappingKey (-1);
			rootVotingMachineOption->setMappingKeyName ("rootVotingMachine");
			rootVotingMachineOption->setOptionType (MenuOptionType::CONFIGURATION_XMLMENU);
			rootVotingMachineOption->setMenuOptions (*optionsRoot);
		
		//presidentMachineConfiguration
		
			
			pollBookMachineConfiguration->setFirstLevelWidth (190);
			pollBookMachineConfiguration->setFirstLevelHeight (109);
			pollBookMachineConfiguration->setFirstLevelSpacing (5);
			pollBookMachineConfiguration->setFirstLevelBorderWidth (5);
			pollBookMachineConfiguration->setFirstLevelFrameWidth (200);
			pollBookMachineConfiguration->setFirstLevelFrameHeight (-1);
			pollBookMachineConfiguration->setSecondLevelWidth (520);
			pollBookMachineConfiguration->setSecondLevelHeight (50);
			pollBookMachineConfiguration->setSecondLevelSpacing (5);
			pollBookMachineConfiguration->setSecondLevelBorderWidth (5);
			pollBookMachineConfiguration->setSecondLevelFramePadding (10);
			pollBookMachineConfiguration->setHasShortcut(true);
			pollBookMachineConfiguration->setRootOption (*rootPresidentMachineOption);

		//votingMachineConfiguration
		
			
			votingMachineConfiguration->setFirstLevelWidth (190);
			votingMachineConfiguration->setFirstLevelHeight (109);
			votingMachineConfiguration->setFirstLevelSpacing (5);
			votingMachineConfiguration->setFirstLevelBorderWidth (5);
			votingMachineConfiguration->setFirstLevelFrameWidth (210);
			votingMachineConfiguration->setFirstLevelFrameHeight (-1);
			votingMachineConfiguration->setSecondLevelWidth (720);
			votingMachineConfiguration->setSecondLevelHeight (40);
			votingMachineConfiguration->setSecondLevelSpacing (5);
			votingMachineConfiguration->setSecondLevelBorderWidth (5);
			votingMachineConfiguration->setSecondLevelFramePadding (10);
			votingMachineConfiguration->setHasShortcut(true);
			votingMachineConfiguration->setRootOption (*rootVotingMachineOption);

		configSAESGUI->setVotingMachine (*votingMachineConfiguration);

		configSAESGUI->setFunctionalityWizardConfiguration(*functionalityWizardConfig);
			//
			//Voting Experience Configuration
			//

			XMLLabelConfiguration* customAtributtesWindowBottomLabelConfiguration = new XMLLabelConfiguration();
			customAtributtesWindowBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			customAtributtesWindowBottomLabelConfiguration->setLabel_VerticalPadding(1);
			customAtributtesWindowBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			customAtributtesWindowBottomLabelConfiguration->setLabel_Family("Verdana");
			customAtributtesWindowBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			customAtributtesWindowBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			customAtributtesWindowBottomLabelConfiguration->setLabel_Size(20);

			XMLLabelConfiguration* customAtributtesWindowHeaderLabelConfiguration = new XMLLabelConfiguration();
			customAtributtesWindowHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			customAtributtesWindowHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			customAtributtesWindowHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			customAtributtesWindowHeaderLabelConfiguration->setLabel_Family("Verdana");
			customAtributtesWindowHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			customAtributtesWindowHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			customAtributtesWindowHeaderLabelConfiguration->setLabel_Size(20);

			XMLLabelConfiguration* customAtributtesWindowCenterLabelConfiguration = new XMLLabelConfiguration();
			customAtributtesWindowCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			customAtributtesWindowCenterLabelConfiguration->setLabel_VerticalPadding(1);
			customAtributtesWindowCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			customAtributtesWindowCenterLabelConfiguration->setLabel_Family("Verdana");
			customAtributtesWindowCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			customAtributtesWindowCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			customAtributtesWindowCenterLabelConfiguration->setLabel_Size(20);
		
			customAtributtesWindowConfiguration->setHeaderLabelConfiguration(*customAtributtesWindowHeaderLabelConfiguration);
			customAtributtesWindowConfiguration->setBottomLabelConfiguration(*customAtributtesWindowHeaderLabelConfiguration);
			customAtributtesWindowConfiguration->setCenterLabelConfiguration(*customAtributtesWindowCenterLabelConfiguration);
			customAtributtesWindowConfiguration->setForceQuestionHeader(false);
			customAtributtesWindowConfiguration->setForceQuestionFooter(false);
			customAtributtesWindowConfiguration->setForceQuestionHeaderConfirmation(false);
			customAtributtesWindowConfiguration->setForceQuestionFooterConfirmation(false);
			customAtributtesWindowConfiguration->setShowWelcomeMessageQuestionCloseButton(false);
			customAtributtesWindowConfiguration->setWelcomeMessageQuestionTimer(3000);
			customAtributtesWindowConfiguration->setShowQuestionConfirmation(false);
			customAtributtesWindowConfiguration->setShowWelcomeQuestion(false);
			customAtributtesWindowConfiguration->setQuestionWindowWith(650);
			customAtributtesWindowConfiguration->setQuestionWindowHeight(600);

			XMLLabelConfiguration* confirmationWindowBottomLabelConfiguration = new XMLLabelConfiguration();
			confirmationWindowBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			confirmationWindowBottomLabelConfiguration->setLabel_VerticalPadding(1);
			confirmationWindowBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			confirmationWindowBottomLabelConfiguration->setLabel_Family("Verdana");
			confirmationWindowBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			confirmationWindowBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			confirmationWindowBottomLabelConfiguration->setLabel_Size(20);

			XMLLabelConfiguration* confirmationWindowHeaderLabelConfiguration = new XMLLabelConfiguration();
			confirmationWindowHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			confirmationWindowHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			confirmationWindowHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			confirmationWindowHeaderLabelConfiguration->setLabel_Family("Verdana");
			confirmationWindowHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			confirmationWindowHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			confirmationWindowHeaderLabelConfiguration->setLabel_Size(20);
		
			confirmationWindowConfiguration->setHeaderLabelConfiguration(*confirmationWindowHeaderLabelConfiguration);
			confirmationWindowConfiguration->setBottomLabelConfiguration(*confirmationWindowBottomLabelConfiguration);
			confirmationWindowConfiguration->setNullButtonsVertical(true);

			//voting experience label configuration

			//<1>
			selectionLanguageHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			selectionLanguageHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			selectionLanguageHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			selectionLanguageHeaderLabelConfiguration->setLabel_Family("Verdana");
			selectionLanguageHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			selectionLanguageHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			selectionLanguageHeaderLabelConfiguration->setLabel_Size(20);

			//<2>
			selectionLanguageBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			selectionLanguageBottomLabelConfiguration->setLabel_VerticalPadding(1);
			selectionLanguageBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			selectionLanguageBottomLabelConfiguration->setLabel_Family("Verdana");
			selectionLanguageBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			selectionLanguageBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			selectionLanguageBottomLabelConfiguration->setLabel_Size(20);

			//<3>
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_Family("Verdana");
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationHeaderLabelConfiguration->setLabel_Size(20);

			//<4>
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_VerticalPadding(1);
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_Family("Verdana");
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationBottomLabelConfiguration->setLabel_Size(20);

			//<5>
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_VerticalPadding(1);
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_Family("Verdana");
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			selectionLanguageConfirmationCenterLabelConfiguration->setLabel_Size(15);

			//<6>
			superWhiteHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteHeaderLabelConfiguration->setLabel_Family("Verdana");
			superWhiteHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteHeaderLabelConfiguration->setLabel_Size(20);

			//<7>
			superWhiteBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteBottomLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteBottomLabelConfiguration->setLabel_Family("Verdana");
			superWhiteBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteBottomLabelConfiguration->setLabel_Size(20);

			//<8>
			superWhiteCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteCenterLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteCenterLabelConfiguration->setLabel_Family("Verdana");
			superWhiteCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteCenterLabelConfiguration->setLabel_Size(20);

			//<9>
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_Family("Verdana");
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteConfirmationHeaderLabelConfiguration->setLabel_Size(20);

			//<10>
			superWhiteConfirmationBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteConfirmationBottomLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteConfirmationBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteConfirmationBottomLabelConfiguration->setLabel_Family("Verdana");
			superWhiteConfirmationBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteConfirmationBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteConfirmationBottomLabelConfiguration->setLabel_Size(20);

			//<11>
			superWhiteConfirmationCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			superWhiteConfirmationCenterLabelConfiguration->setLabel_VerticalPadding(1);
			superWhiteConfirmationCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			superWhiteConfirmationCenterLabelConfiguration->setLabel_Family("Verdana");
			superWhiteConfirmationCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			superWhiteConfirmationCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			superWhiteConfirmationCenterLabelConfiguration->setLabel_Size(20);

			//<12>
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_VerticalPadding(1);
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_Family("Verdana");
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			contestWhiteSelectionHeaderLabelConfiguration->setLabel_Size(20);

			//<13>
			contestWhiteSelectionBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			contestWhiteSelectionBottomLabelConfiguration->setLabel_VerticalPadding(1);
			contestWhiteSelectionBottomLabelConfiguration->setLabel_HorizontalPadding(1);
			contestWhiteSelectionBottomLabelConfiguration->setLabel_Family("Verdana");
			contestWhiteSelectionBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			contestWhiteSelectionBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			contestWhiteSelectionBottomLabelConfiguration->setLabel_Size(20);

			//<14>
			contestWhiteSelectionCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			contestWhiteSelectionCenterLabelConfiguration->setLabel_VerticalPadding(1);
			contestWhiteSelectionCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			contestWhiteSelectionCenterLabelConfiguration->setLabel_Family("Verdana");
			contestWhiteSelectionCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			contestWhiteSelectionCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			contestWhiteSelectionCenterLabelConfiguration->setLabel_Size(20);

			//<15>
			welcomeContestCenterLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			welcomeContestCenterLabelConfiguration->setLabel_VerticalPadding(1);
			welcomeContestCenterLabelConfiguration->setLabel_HorizontalPadding(1);
			welcomeContestCenterLabelConfiguration->setLabel_Family("Verdana");
			welcomeContestCenterLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			welcomeContestCenterLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			welcomeContestCenterLabelConfiguration->setLabel_Size(23);

			//<16>
			votingWidgetLabelChildLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
			votingWidgetLabelChildLabelConfiguration->setLabel_VerticalPadding(0);
			votingWidgetLabelChildLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWidgetLabelChildLabelConfiguration->setLabel_Family("Verdana");
			votingWidgetLabelChildLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWidgetLabelChildLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWidgetLabelChildLabelConfiguration->setLabel_Size(20);

			//<17>
			votingWidgetTopChildLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
			votingWidgetTopChildLabelConfiguration->setLabel_VerticalPadding(0);
			votingWidgetTopChildLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWidgetTopChildLabelConfiguration->setLabel_Family("Verdana");
			votingWidgetTopChildLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWidgetTopChildLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWidgetTopChildLabelConfiguration->setLabel_Size(10);

			//<18>
			votingWidgetBottomChildLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			votingWidgetBottomChildLabelConfiguration->setLabel_VerticalPadding(0);
			votingWidgetBottomChildLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWidgetBottomChildLabelConfiguration->setLabel_Family("Verdana");
			votingWidgetBottomChildLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWidgetBottomChildLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWidgetBottomChildLabelConfiguration->setLabel_Size(10);

			//<19>
			votingWidgetNumberChildLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			votingWidgetNumberChildLabelConfiguration->setLabel_VerticalPadding(0);
			votingWidgetNumberChildLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWidgetNumberChildLabelConfiguration->setLabel_Family("Verdana");
			votingWidgetNumberChildLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWidgetNumberChildLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWidgetNumberChildLabelConfiguration->setLabel_Size(15);

			//<20>
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_VerticalPadding(0);
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_Family("Verdana");
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWidgetPartySelectionLabelChildLabelConfiguration->setLabel_Size(15);

			votingWindowEndMessageLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			votingWindowEndMessageLabelConfiguration->setLabel_VerticalPadding(0);
			votingWindowEndMessageLabelConfiguration->setLabel_HorizontalPadding(0);
			votingWindowEndMessageLabelConfiguration->setLabel_Family("Verdana");
			votingWindowEndMessageLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			votingWindowEndMessageLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			votingWindowEndMessageLabelConfiguration->setLabel_Size(20);

			//<18>
			PartyNullLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			PartyNullLabelConfiguration.setLabel_VerticalPadding(0);
			PartyNullLabelConfiguration.setLabel_HorizontalPadding(0);
			PartyNullLabelConfiguration.setLabel_Family("Verdana");
			PartyNullLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			PartyNullLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			PartyNullLabelConfiguration.setLabel_Size(15);

			loadingBallotsLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			loadingBallotsLabelConfiguration->setLabel_VerticalPadding(0);
			loadingBallotsLabelConfiguration->setLabel_HorizontalPadding(0);
			loadingBallotsLabelConfiguration->setLabel_Family("Verdana");
			loadingBallotsLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			loadingBallotsLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			loadingBallotsLabelConfiguration->setLabel_Size(20);
			
			checkSumLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			checkSumLabelConfiguration->setLabel_VerticalPadding(0);
			checkSumLabelConfiguration->setLabel_HorizontalPadding(0);
			checkSumLabelConfiguration->setLabel_Family("Verdana");
			checkSumLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			checkSumLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			checkSumLabelConfiguration->setLabel_Size(20);


			interrupVotingExperienceMessageLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			interrupVotingExperienceMessageLabelConfiguration->setLabel_VerticalPadding(0);
			interrupVotingExperienceMessageLabelConfiguration->setLabel_HorizontalPadding(0);
			interrupVotingExperienceMessageLabelConfiguration->setLabel_Family("Verdana");
			interrupVotingExperienceMessageLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			interrupVotingExperienceMessageLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			interrupVotingExperienceMessageLabelConfiguration->setLabel_Size(20);

			interrupVotingExperienceCancelLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			interrupVotingExperienceCancelLabelConfiguration->setLabel_VerticalPadding(0);
			interrupVotingExperienceCancelLabelConfiguration->setLabel_HorizontalPadding(0);
			interrupVotingExperienceCancelLabelConfiguration->setLabel_Family("Verdana");
			interrupVotingExperienceCancelLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			interrupVotingExperienceCancelLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			interrupVotingExperienceCancelLabelConfiguration->setLabel_Size(20);

			votingExperienceLabelConfiguration->setPartyNullLabelConfiguration(PartyNullLabelConfiguration);
			votingExperienceLabelConfiguration->setSelectionLanguageHeaderLabelConfiguration(*selectionLanguageHeaderLabelConfiguration);
			votingExperienceLabelConfiguration->setSelectionLanguageBottomLabelConfiguration(*selectionLanguageBottomLabelConfiguration);
			votingExperienceLabelConfiguration->setSelectionLanguageConfirmationHeaderLabelConfiguration(*selectionLanguageConfirmationHeaderLabelConfiguration);
			votingExperienceLabelConfiguration->setSelectionLanguageConfirmationBottomLabelConfiguration(*selectionLanguageConfirmationBottomLabelConfiguration);
			votingExperienceLabelConfiguration->setSelectionLanguageConfirmationCenterLabelConfiguration(*selectionLanguageConfirmationCenterLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteHeaderLabelConfiguration(*superWhiteHeaderLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteBottomLabelConfiguration(*superWhiteBottomLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteCenterLabelConfiguration(*superWhiteCenterLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteConfirmationHeaderLabelConfiguration(*superWhiteConfirmationHeaderLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteConfirmationBottomLabelConfiguration(*superWhiteConfirmationBottomLabelConfiguration);
			votingExperienceLabelConfiguration->setSuperWhiteConfirmationCenterLabelConfiguration(*superWhiteConfirmationCenterLabelConfiguration);
			votingExperienceLabelConfiguration->setContestWhiteSelectionHeaderLabelConfiguration(*contestWhiteSelectionHeaderLabelConfiguration);
			votingExperienceLabelConfiguration->setContestWhiteSelectionBottomLabelConfiguration(*contestWhiteSelectionBottomLabelConfiguration);
			votingExperienceLabelConfiguration->setContestWhiteSelectionCenterLabelConfiguration(*contestWhiteSelectionCenterLabelConfiguration);
			votingExperienceLabelConfiguration->setWelcomeContestCenterLabelConfiguration(*welcomeContestCenterLabelConfiguration);	
			votingExperienceLabelConfiguration->setVotingWidgetLabelChildLabelConfiguration(*votingWidgetLabelChildLabelConfiguration);
			votingExperienceLabelConfiguration->setVotingWidgetTopChildLabelConfiguration(*votingWidgetTopChildLabelConfiguration);
			votingExperienceLabelConfiguration->setVotingWidgetBottomChildLabelConfiguration(*votingWidgetBottomChildLabelConfiguration);
			votingExperienceLabelConfiguration->setVotingWidgetNumberChildLabelConfiguration(*votingWidgetNumberChildLabelConfiguration);
			votingExperienceLabelConfiguration->setVotingWindowEndMessageLabelConfiguration(*votingWindowEndMessageLabelConfiguration);
			votingExperienceLabelConfiguration->setLoadingBallotsLabelConfiguration(*loadingBallotsLabelConfiguration);
			votingExperienceLabelConfiguration->setCheckSumLabelConfiguration(*checkSumLabelConfiguration);
			votingExperienceLabelConfiguration->setInterrupVotingExperienceMessageLabelConfiguration(*interrupVotingExperienceMessageLabelConfiguration);
			votingExperienceLabelConfiguration->setInterrupVotingExperienceCancelLabelConfiguration(*interrupVotingExperienceCancelLabelConfiguration);

			votingExperienceLabelConfiguration->setVotingWidgetPartySelectionLabelChildLabelConfiguration(*votingWidgetPartySelectionLabelChildLabelConfiguration);	
	
					//Voting Window Font
					votingWindowFont->setSize(16000);
					votingWindowFont->setFontName("Arial");

				//Voting Window Configuration
				votingWindowConfiguration->setWelcomeMessageContestTimer(3000);
				votingWindowConfiguration->setBottomFrameMargin(0);
				votingWindowConfiguration->setBottomFont(*votingWindowFont);
				votingWindowConfiguration->setBottomFrameHeight(40);
				votingWindowConfiguration->setShowLanguageConfirmation(true);
				votingWindowConfiguration->setShowBallotOptionFooter(false);
				votingWindowConfiguration->setShowBlankVoteQuestion(false);
				votingWindowConfiguration->setShowBlankVoteConfirmation(false);
				votingWindowConfiguration->setShowNullQuestionInBack(false);
				votingWindowConfiguration->setShowLanguageSelectionInBack(false);
				votingWindowConfiguration->setShowBallotOptionsInContestBack(false);
				votingWindowConfiguration->setShowWelcomeContest(false);
				votingWindowConfiguration->setEraseBallotOptionsInPartyChanged(true);
				votingWindowConfiguration->setQuestionHeaderSameInConfirmation(true);
				votingWindowConfiguration->setConnectTimer(50);
				votingWindowConfiguration->setConnectTimerLoading(1000);
				votingWindowConfiguration->setConnectTimerLanguage(5);
				votingWindowConfiguration->setNumberOfBallotsToDisplayLoadingBallotMessage(50);
				votingWindowConfiguration->setLoadingBallotMessage("Never");
				

					//Party Widget
					partyWidget->setNumberWidth(40);
					partyWidget->setUseAbbreviation(false);
					partyWidget->setPadding(3);
					partyWidget->setShowFrame(true);
					partyWidget->setDisplay(*displayTypeImage);
					partyWidget->setUseFillByRows(false);
				
				//Party Selection Widget

				Smartmatic::SAES::Configuration::ViewButtonConfiguration partyButtonConf(ViewButtonConfiguration::CONFIGURATION_EXPAND_BUTTONS);

				Smartmatic::SAES::Configuration::ExpandButtonConfiguration partyExpandButtonConfig;
				partyExpandButtonConfig.setSpacing(0);
				partyExpandButtonConfig.setFontSize(16);

				Smartmatic::SAES::Configuration::PartySeparateButtonConfiguration partySeparateButtonConfig;
				partySeparateButtonConfig.setNullButtonWidth(300);
				partySeparateButtonConfig.setBackButtonWidth(600);
				partySeparateButtonConfig.setFontSize(16);

				partySelection->setEnableClick(true);
				partySelection->setPartyButton(partyButtonConf);
				partySelection->setExpandButton(partyExpandButtonConfig);
				partySelection->setSeparateButton(partySeparateButtonConfig);

				partySelection->setUseMaxPartyNumerFromAllContest(false);
				partySelection->setShowNullParty(true);
				partySelection->setShowNullButton(false);

				partySelection->setFrameBottomHeight(50);
				partySelection->setColumns(4);
				partySelection->setSizeToColumns(4);
				partySelection->setImageRelation(1);
				partySelection->setPartiesMargin(5);
				partySelection->setPartySelectionAlignment(0.5);
				partySelection->setPartyWidget(*partyWidget);

				eventSounds->setPMInstalationSound("AzertySound");
				eventSounds->setVMInstalationSound("AzertySound");
				eventSounds->setAuthenticationValidPasswordSound("ValidPasswordSound");
				eventSounds->setAuthenticationInvalidPasswordSound("InvalidPasswordSound");		
				eventSounds->setVotingExperienceSound("VotePrintSound");
				eventSounds->setBallotOptionSelectSound("BallotVoteSound");
				eventSounds->setPartySelectSound("PartyVoteSound");
				eventSounds->setDiagnosisSound("DiagnosticSound");

				configSAESGUI->setEventSoundsConfiguration(*eventSounds);

				XMLLabelConfiguration* partySelectionWindowHeaderLabelConfiguration = new XMLLabelConfiguration();
				partySelectionWindowHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
				partySelectionWindowHeaderLabelConfiguration->setLabel_VerticalPadding(1);
				partySelectionWindowHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
				partySelectionWindowHeaderLabelConfiguration->setLabel_Family("Verdana");
				partySelectionWindowHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				partySelectionWindowHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				partySelectionWindowHeaderLabelConfiguration->setLabel_Size(20);

				XMLLabelConfiguration* partySelectionWindowBottomLabelConfiguration = new XMLLabelConfiguration();
				partySelectionWindowBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
				partySelectionWindowBottomLabelConfiguration->setLabel_VerticalPadding(1);
				partySelectionWindowBottomLabelConfiguration->setLabel_HorizontalPadding(1);
				partySelectionWindowBottomLabelConfiguration->setLabel_Family("Verdana");
				partySelectionWindowBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				partySelectionWindowBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				partySelectionWindowBottomLabelConfiguration->setLabel_Size(20);

				partySelection->setHeaderLabelConfiguration(*partySelectionWindowHeaderLabelConfiguration);
				partySelection->setBottomLabelConfiguration(*partySelectionWindowBottomLabelConfiguration);

				//Ballot Option Font
				ballotOptionFont->setSize(10);
				ballotOptionFont->setFontName("Arial");

				//Color Configuration
				selectedColor->setRed(40000);
				selectedColor->setGreen(40000);
				selectedColor->setBlue(40000);

				//Color Configuration
				unSelectedColor->setRed(65535);
				unSelectedColor->setGreen(65535);
				unSelectedColor->setBlue(65535);
		
				//Ballot Option Widget Configuration
				ballotOptionWidget->setNumberWidth(35);
				ballotOptionWidget->setDisplay(*displayTypeText);
				ballotOptionWidget->setPadding(0);
				ballotOptionWidget->setSelectedColor(*selectedColor);
				ballotOptionWidget->setUnSelectedColor(*unSelectedColor);
				ballotOptionWidget->setShowFrame(true);
				ballotOptionWidget->setBallotFont(*ballotOptionFont);
				ballotOptionWidget->setSeparatorCharacter("#");
				ballotOptionWidget->setNameIsBeforeSeparator(true);

				//Ballot Option Selection Widget

				Smartmatic::SAES::Configuration::ViewButtonConfiguration ballotOptionButtonConf(ViewButtonConfiguration::CONFIGURATION_SEPARATE_BUTTONS);
				Smartmatic::SAES::Configuration::ViewTableConfiguration ballotOptionTableConf(ViewTableConfiguration::CONFIGURATION_COLUMN_FIXED);

				Smartmatic::SAES::Configuration::ExpandButtonConfiguration ballotOptionExpandButtonConfig;
				ballotOptionExpandButtonConfig.setSpacing(0);
				ballotOptionExpandButtonConfig.setFontSize(16);

				Smartmatic::SAES::Configuration::BallotOptionSeparateButtonConfiguration ballotOptionSeparateButtonConfig;
				ballotOptionSeparateButtonConfig.setClearButtonWidth(300);
				ballotOptionSeparateButtonConfig.setAcceptButtonWidth(300);
				ballotOptionSeparateButtonConfig.setBackButtonWidth(600);
				ballotOptionSeparateButtonConfig.setFontSize(16);

				ballotOptionSelection->setEnableClick(true);
				ballotOptionSelection->setShowConfirmation(false);
				ballotOptionSelection->setBallotOptionTable(ballotOptionTableConf);
				ballotOptionSelection->setBallotOptionButton(ballotOptionButtonConf);
				ballotOptionSelection->setUseMaxBallotNumberFromContest(false);
				ballotOptionSelection->setHideStandInLabelIfEmpty(true);

				ballotOptionSelection->setExpandButton(ballotOptionExpandButtonConfig);
				ballotOptionSelection->setSeparateButton(ballotOptionSeparateButtonConfig);

				ballotOptionSelection->setFrameBottomHeight(80);
				ballotOptionSelection->setFrameHeaderHeight(50);
				ballotOptionSelection->setMaxColumns(4);
				ballotOptionSelection->setMaxRows(23);
				ballotOptionSelection->setFixBorder(10);
				ballotOptionSelection->setResizeBallotBox(false);
				ballotOptionSelection->setBallotsMargin(1);
				ballotOptionSelection->setOptionListLinked(false);
				ballotOptionSelection->setSelectListImpliesSelectStandIn(false);
				ballotOptionSelection->setSelectStandInImpliesSelectList(false);
				ballotOptionSelection->setAllowBackWithBallotSelected(false);
				ballotOptionSelection->setCandidatesButtonsSpacing(40);
				ballotOptionSelection->setUseCustomBallotRelation(true);
				ballotOptionSelection->setBallotRelation(6);
				ballotOptionSelection->setShowImageInList(true);
				ballotOptionSelection->setImageInListPadgging(10);
				ballotOptionSelection->setListSelectedColor(*selectedColor);
				ballotOptionSelection->setListUnSelectedColor(*unSelectedColor);
				ballotOptionSelection->setStandInColor(*unSelectedColor);
				ballotOptionSelection->setBallotOptionWidget(*ballotOptionWidget);

				//pivot principal configuration
				ballotOptionSelection->setFillPrincipal(FillPrincipalConfiguration::CONFIGURATION_FILL_COLUMN_FIXED);

				Smartmatic::SAES::Configuration::FillColumnDynamicConfiguration fillColumnDynamic;
				Smartmatic::SAES::Configuration::FillColumnDynamicConfiguration::PivotConfigSequence pivotPrincipalSeq;

				Smartmatic::SAES::Configuration::PivotConfig pivotConfig1(1, 1, true);
				Smartmatic::SAES::Configuration::PivotConfig pivotConfig2(20, 2, true);
				Smartmatic::SAES::Configuration::PivotConfig pivotConfig3(39, 3, true);
				Smartmatic::SAES::Configuration::PivotConfig pivotConfig4(70, 4, false);

				pivotPrincipalSeq.push_back(pivotConfig1);
				pivotPrincipalSeq.push_back(pivotConfig2);
				pivotPrincipalSeq.push_back(pivotConfig3);
				pivotPrincipalSeq.push_back(pivotConfig4);

				fillColumnDynamic.setPivotConfig(pivotPrincipalSeq);
				ballotOptionSelection->setFillColumnDynamic(fillColumnDynamic);

				//referendum selection
				referendumConfiguration->setEnableClick(true);
				referendumConfiguration->setFrameBottomHeight(50);
				referendumConfiguration->setQuestionWidth(400);
				referendumConfiguration->setQuestionHeight(200);
				referendumConfiguration->setButtonsVertical(false);
				referendumConfiguration->setBallotBoxTopPadding(10);
				referendumConfiguration->setBallotBoxLeftPadding(0);
				referendumConfiguration->setBallotBoxSpacing(50);
				referendumConfiguration->setBallotWidth(200);
				referendumConfiguration->setBallotHeight(100);
				referendumConfiguration->setShowBackButton(true);
				referendumConfiguration->setShowNullOption(false);

				XMLLabelConfiguration referendumHeaderLabelConfiguration;
				referendumHeaderLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
				referendumHeaderLabelConfiguration.setLabel_VerticalPadding(1);
				referendumHeaderLabelConfiguration.setLabel_HorizontalPadding(1);
				referendumHeaderLabelConfiguration.setLabel_Family("Verdana");
				referendumHeaderLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				referendumHeaderLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				referendumHeaderLabelConfiguration.setLabel_Size(20);

				XMLLabelConfiguration referendumBottomLabelConfiguration;
				referendumBottomLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				referendumBottomLabelConfiguration.setLabel_VerticalPadding(1);
				referendumBottomLabelConfiguration.setLabel_HorizontalPadding(1);
				referendumBottomLabelConfiguration.setLabel_Family("Verdana");
				referendumBottomLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				referendumBottomLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				referendumBottomLabelConfiguration.setLabel_Size(20);

				XMLLabelConfiguration referendumQuestionLabelConfiguration;
				referendumQuestionLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				referendumQuestionLabelConfiguration.setLabel_VerticalPadding(1);
				referendumQuestionLabelConfiguration.setLabel_HorizontalPadding(1);
				referendumQuestionLabelConfiguration.setLabel_Family("Verdana");
				referendumQuestionLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				referendumQuestionLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				referendumQuestionLabelConfiguration.setLabel_Size(30);

				XMLLabelConfiguration referendumBallotLabelConfiguration;
				referendumBallotLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				referendumBallotLabelConfiguration.setLabel_VerticalPadding(1);
				referendumBallotLabelConfiguration.setLabel_HorizontalPadding(1);
				referendumBallotLabelConfiguration.setLabel_Family("Verdana");
				referendumBallotLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				referendumBallotLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				referendumBallotLabelConfiguration.setLabel_Size(14);

				referendumConfiguration->setHeaderLabelConfiguration(referendumHeaderLabelConfiguration);
				referendumConfiguration->setBottomLabelConfiguration(referendumBottomLabelConfiguration);
				referendumConfiguration->setQuestionLabelConfiguration(referendumQuestionLabelConfiguration);
				referendumConfiguration->setBallotsLabelConfiguration(referendumBallotLabelConfiguration);

				
				XMLLabelConfiguration* ballotOptionSelectionWindowHeaderLabelConfiguration = new XMLLabelConfiguration();
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_VerticalPadding(1);
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_HorizontalPadding(1);
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_Family("Verdana");
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				ballotOptionSelectionWindowHeaderLabelConfiguration->setLabel_Size(20);

				XMLLabelConfiguration* ballotOptionSelectionWindowBottomLabelConfiguration = new XMLLabelConfiguration();
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_VerticalPadding(1);
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_HorizontalPadding(1);
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_Family("Verdana");
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				ballotOptionSelectionWindowBottomLabelConfiguration->setLabel_Size(20);

				ballotOptionSelection->setHeaderLabelConfiguration(*ballotOptionSelectionWindowHeaderLabelConfiguration);
				ballotOptionSelection->setBottomLabelConfiguration(*ballotOptionSelectionWindowBottomLabelConfiguration);
		
			//Define start the aplication

			votingExperienceConfiguration->setSortOptionsAlphabetical(true);
			votingExperienceConfiguration->setSortLanguagesAlphabetical(true);
			votingExperienceConfiguration->setDetectCardExtraction(true);
			votingExperienceConfiguration->setNumberOfExtractionsBeforeStop(3);
			votingExperienceConfiguration->setVotingWindow(*votingWindowConfiguration);
			votingExperienceConfiguration->setPartySelection(*partySelection);
			votingExperienceConfiguration->setBallotOptionSelection(*ballotOptionSelection);
			votingExperienceConfiguration->setReferendumSelection(*referendumConfiguration);
			votingExperienceConfiguration->setCustomAtributtesWindow(*customAtributtesWindowConfiguration);
			votingExperienceConfiguration->setConfirmationWindow(*confirmationWindowConfiguration);
			votingExperienceConfiguration->setVotingExperienceLabel(*votingExperienceLabelConfiguration);
			votingExperienceConfiguration->setTimeOutCard(60);
			votingExperienceConfiguration->setTimeToShowFinalMessage(3);
			votingExperienceConfiguration->setMarkCardAsUsed(true);
			votingExperienceConfiguration->setCheckSumFailTimerMessage(3);
			votingExperienceConfiguration->setCheckSumFailOption(CheckSumFailOption::CONFIGURATION_CLEANSELECTIONS);
			votingExperienceConfiguration->setRemoveCardFirst(false);

			//
			//Change hour funcionality configuration
			//

			ChangeHourFunctionalityConfiguration changeHourFunctionality;
			changeHourFunctionality.setButtonArrowWidth(80);
			changeHourFunctionality.setButtonArrowHeight(80);
			changeHourFunctionality.setButtonValidateWidth(150);
			changeHourFunctionality.setButtonValidateHeight(90);
			changeHourFunctionality.setEntryWidth(90);
			changeHourFunctionality.setEntryHeight(65);
			changeHourFunctionality.setFontEntrySize(23);
				XMLLabelConfiguration timeLabelConfiguration;
				timeLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
				timeLabelConfiguration.setLabel_VerticalPadding(1);
				timeLabelConfiguration.setLabel_HorizontalPadding(1);
				timeLabelConfiguration.setLabel_Family("Verdana");
				timeLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				timeLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				timeLabelConfiguration.setLabel_Size(18);
			changeHourFunctionality.setTimeLabelConfiguration(timeLabelConfiguration);
				XMLLabelConfiguration titlesLabelConfiguration;
				titlesLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				titlesLabelConfiguration.setLabel_VerticalPadding(1);
				titlesLabelConfiguration.setLabel_HorizontalPadding(1);
				titlesLabelConfiguration.setLabel_Family("Verdana");
				titlesLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				titlesLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
				titlesLabelConfiguration.setLabel_Size(20);
			changeHourFunctionality.setTitlesLabelConfiguration(titlesLabelConfiguration);
				XMLLabelConfiguration principalTitleLabelConfiguration;
				principalTitleLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				principalTitleLabelConfiguration.setLabel_VerticalPadding(1);
				principalTitleLabelConfiguration.setLabel_HorizontalPadding(1);
				principalTitleLabelConfiguration.setLabel_Family("Verdana");
				principalTitleLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				principalTitleLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
				principalTitleLabelConfiguration.setLabel_Size(22);
			changeHourFunctionality.setPrincipalTitleLabelConfiguration(principalTitleLabelConfiguration);
			changeHourFunctionality.setTableVerticalSpacing(30);
			configSAESGUI->setChangeHourFunctionalityConfiguration(changeHourFunctionality);


			touchDiagConfig->setNumberOfCalibrationPoints(5);
		
			touchDiagConfig->setHeightOfButtons(40);
			touchDiagConfig->setWidthOfButtons(40);
			
			brightnessDiagnosisConf->setTimeDelayButtons(1000);

			screaderDiagnosisConf->setTimeoutToFail(5);

			printerDiagnosisConf->setPrintGraphicalForPresident(true);
			printerDiagnosisConf->setDoNotCheckBeforePrintDiagnostic(false);
			printerDiagnosisConf->setButtonsWidth(150);
			printerDiagnosisConf->setButtonsHeight(100);
			printerDiagnosisConf->setButtonsFontSize(18);

			barcodeDiagnosisConf->setTimeOut(20);
			barcodeDiagnosisConf->setStringToEncode("BARCODEREADER barcodereader BARCODEREADER barcodereader");
			barcodeDiagnosisConf->setPrintAutomaticBarcode(true);
			barcodeDiagnosisConf->setBarcodeCommandsName("baseconfiguration");
			barcodeDiagnosisConf->setBarcodeInParams("LightsON");
			barcodeDiagnosisConf->setBarcodeOutParams("");
			barcodeDiagnosisConf->setSkipPrinterError(true);

			DiagnosticType printer(DiagnosticDevice::CONFIGURATION_PRINTER,true);
			DiagnosticType barcode(DiagnosticDevice::CONFIGURATION_BARCODE,false);
			DiagnosticType touchScreen(DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION,false);
			DiagnosticType alarmbox(DiagnosticDevice::CONFIGURATION_ALARMBOX,false);
			DiagnosticType screenContrast(DiagnosticDevice::CONFIGURATION_SCREENCONTRAST,false);
			DiagnosticType smartcard(DiagnosticDevice::CONFIGURATION_SMARTCARD,true);
			DiagnosticType flash(DiagnosticDevice::CONFIGURATION_FLASH,true);

				seqDiagnosticToApply->push_back (printer);
				seqDiagnosticToApply->push_back (barcode);
				seqDiagnosticToApply->push_back (touchScreen);
				seqDiagnosticToApply->push_back (screenContrast);
				seqDiagnosticToApply->push_back (smartcard);
				seqDiagnosticToApply->push_back (flash);

				/*seqDiagnosticWithoutCalibration->push_back ("Printer");
				seqDiagnosticWithoutCalibration->push_back ("Barcode");
				seqDiagnosticWithoutCalibration->push_back ("SmartCard");
				seqDiagnosticWithoutCalibration->push_back ("Flash");
				seqDiagnosticWithoutCalibration->push_back ("AlarmBox");*/
		
			allDiagnosisConf->setDiagnosticToApply(*seqDiagnosticToApply);
			
			allDiagnosisConf->setAlarmDiagnosisWaitTime(3);
			allDiagnosisConf->setBarcodeDiagnosisWaitTime(3);
			allDiagnosisConf->setContrastDiagnosisWaitTime(3);
			allDiagnosisConf->setCalibrationDiagnosisWaitTime(3);
			allDiagnosisConf->setFlashDiagnosisWaitTime(3);
			allDiagnosisConf->setPrinterDiagnosisWaitTime(3);
			allDiagnosisConf->setSmartcardDiagnosisWaitTime(3);
			allDiagnosisConf->setPrinterDiagnosisWaitTimeOnOk(3);
			allDiagnosisConf->setPrinterDiagnosisWaitTimeOnCancel(3);
			allDiagnosisConf->setCalibrationDiagnosisWaitTimeOnOk(0);
			allDiagnosisConf->setContrastDiagnosisWaitTimeOnOk(0);


				seqAutoDiagnosticToApply->push_back (printer);
				seqAutoDiagnosticToApply->push_back (smartcard);
				seqAutoDiagnosticToApply->push_back (flash);

			
			XMLLabelConfiguration diagnosisFooterLabelConfiguration;

			diagnosisLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			diagnosisLabelConfiguration->setLabel_VerticalPadding(1);
			diagnosisLabelConfiguration->setLabel_HorizontalPadding(1);
			diagnosisLabelConfiguration->setLabel_Family("Verdana");
			diagnosisLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			diagnosisLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			diagnosisLabelConfiguration->setLabel_Size(20);

			diagnosisFooterLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			diagnosisFooterLabelConfiguration.setLabel_VerticalPadding(1);
			diagnosisFooterLabelConfiguration.setLabel_HorizontalPadding(1);
			diagnosisFooterLabelConfiguration.setLabel_Family("Verdana");
			diagnosisFooterLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			diagnosisFooterLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			diagnosisFooterLabelConfiguration.setLabel_Size(12);

			resultErrorLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			resultErrorLabelConfiguration.setLabel_VerticalPadding(1);
			resultErrorLabelConfiguration.setLabel_HorizontalPadding(1);
			resultErrorLabelConfiguration.setLabel_Family("Verdana");
			resultErrorLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			resultErrorLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			resultErrorLabelConfiguration.setLabel_Size(12);

			//allDiagnosisConf->setDiagnosisLabelConfiguration(*diagnosisLabelConfiguration);
			XMLLabelConfiguration diagnosticReviewConfiguration;
			diagnosticReviewConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			diagnosticReviewConfiguration.setLabel_VerticalPadding(1);
			diagnosticReviewConfiguration.setLabel_HorizontalPadding(1);
			diagnosticReviewConfiguration.setLabel_Family("Verdana");
			diagnosticReviewConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			diagnosticReviewConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			diagnosticReviewConfiguration.setLabel_Size(20);

			XMLLabelConfiguration blockDiagnosticTitleConfiguration;
			blockDiagnosticTitleConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			blockDiagnosticTitleConfiguration.setLabel_VerticalPadding(1);
			blockDiagnosticTitleConfiguration.setLabel_HorizontalPadding(1);
			blockDiagnosticTitleConfiguration.setLabel_Family("Verdana");
			blockDiagnosticTitleConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			blockDiagnosticTitleConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			blockDiagnosticTitleConfiguration.setLabel_Size(14);

			Smartmatic::SAES::Configuration::ButtonConfiguration blockDiagnosticButtonConf;
			blockDiagnosticButtonConf.setButtonWidth(220);
			blockDiagnosticButtonConf.setButtonHeight(60);
			blockDiagnosticButtonConf.setFontSize(12);

			autoDiagnosisConf->setDiagnosticToApply(*seqAutoDiagnosticToApply);
			autoDiagnosisConf->setBlockDiagnostic(true);
			autoDiagnosisConf->setBlockDiagnosticTitle(blockDiagnosticTitleConfiguration);
			autoDiagnosisConf->setBlockDiagnosticButton(blockDiagnosticButtonConf);

			autoDiagnosisConf->setUseOkButtonOnSomeNonMandatoryDiagnosticFailed(true);
			autoDiagnosisConf->setUseShutDownButtonOnSomeMandatoryDiagnosticFailed(true);
			autoDiagnosisConf->setAlarmDiagnosisWaitTime(1000);
			autoDiagnosisConf->setBarcodeDiagnosisWaitTime(1000);
			autoDiagnosisConf->setFlashDiagnosisWaitTime(1000);
			autoDiagnosisConf->setPrinterDiagnosisWaitTime(4000);
			autoDiagnosisConf->setSmartcardDiagnosisWaitTime(1000);
			autoDiagnosisConf->setDiagnosticReviewWidth(500);
			autoDiagnosisConf->setDiagnosticReviewHeight(100);
			autoDiagnosisConf->setDiagnosticReviewLabelConfiguration(diagnosticReviewConfiguration);
			autoDiagnosisConf->setShowFooterInAutoDiagnosis(true);

		
			recoveryCardConf->setShowConfirmationButtons(false);
			recoveryCardConf->setCleanOnCorrectActivation(true);
			recoveryCardConf->setCleanOnIncorrectActivation(false);
			recoveryCardConf->setMinimumDemoCounterToAllowActivation(1);
				ActivatedCardStatisticsConfiguration recoveryCardStatisticsConf;
						recoveryCardStatisticsConf.setHideOfficial(false);
						recoveryCardStatisticsConf.setHideDemo(true);
						recoveryCardStatisticsConf.setHideRecovery(false);
						recoveryCardStatisticsConf.setHideAudio(true);
						recoveryCardStatisticsConf.setHideNonAudio(false);
						recoveryCardStatisticsConf.setHideCA(false);

			XMLLabelConfiguration recoveryCardStatisticsTitleLabelConf;
				recoveryCardStatisticsTitleLabelConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				recoveryCardStatisticsTitleLabelConf.setLabel_VerticalPadding(1);
				recoveryCardStatisticsTitleLabelConf.setLabel_HorizontalPadding(1);
				recoveryCardStatisticsTitleLabelConf.setLabel_Family("Verdana");
				recoveryCardStatisticsTitleLabelConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				recoveryCardStatisticsTitleLabelConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				recoveryCardStatisticsTitleLabelConf.setLabel_Size(20);


			//Color Configuration
			ColorConfiguration recoveryCardStatisticsTitleColor;
			recoveryCardStatisticsTitleColor.setRed(65535);
			recoveryCardStatisticsTitleColor.setGreen(65535);
			recoveryCardStatisticsTitleColor.setBlue(65535);
		
			recoveryCardConf->setStatisticsTitleLabelConfiguration(recoveryCardStatisticsTitleLabelConf);
			recoveryCardConf->setCardStatisticsConfiguration(recoveryCardStatisticsConf);
			recoveryCardConf->setStatisticsTitleColor(recoveryCardStatisticsTitleColor);

			XMLLabelConfiguration labelsDemoConfiguration;
			labelsDemoConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			labelsDemoConfiguration.setLabel_VerticalPadding(1);
			labelsDemoConfiguration.setLabel_HorizontalPadding(1);
			labelsDemoConfiguration.setLabel_Family("Arial");
			labelsDemoConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			labelsDemoConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			labelsDemoConfiguration.setLabel_Size(11);

			voteDemoConf->setPersistVote(true);
			voteDemoConf->setShowBarcodeInPreview(false);
			voteDemoConf->setBarcodeInParams("LightsON");
			voteDemoConf->setBarcodeOutParams("LightsOFF");
			voteDemoConf->setTitleFontConfiguration(labelsDemoConfiguration);
			labelsDemoConfiguration.setLabel_Size(12);
			voteDemoConf->setLabelSelectedConfiguration(labelsDemoConfiguration);
			labelsDemoConfiguration.setLabel_Size(12);
			voteDemoConf->setLabelUnselectedConfiguration(labelsDemoConfiguration);


			//Color Configuration
			ColorConfiguration assistedCardPreviewTitleColor;
			assistedCardPreviewTitleColor.setRed(65535);
			assistedCardPreviewTitleColor.setGreen(65535);
			assistedCardPreviewTitleColor.setBlue(65535);

			ColorConfiguration assistedCardPreviewContentColor;
			assistedCardPreviewContentColor.setRed(40000);
			assistedCardPreviewContentColor.setGreen(40000);
			assistedCardPreviewContentColor.setBlue(65535);
		
			assistedCardConf->setMinimumDemoCounterToAllowActivation(1);
			assistedCardConf->setPreviewTitlesColor(assistedCardPreviewTitleColor);
			assistedCardConf->setPreviewContentsColor(assistedCardPreviewContentColor);
			

			fillAssistedLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			fillAssistedLabelConfiguration->setLabel_VerticalPadding(1);
			fillAssistedLabelConfiguration->setLabel_HorizontalPadding(1);
			fillAssistedLabelConfiguration->setLabel_Family("Verdana");
			fillAssistedLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			fillAssistedLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			fillAssistedLabelConfiguration->setLabel_Size(17);
			assistedCardConf->setInstrunctionLabelConfiguration(*fillAssistedLabelConfiguration);

			fillAssistedNameLabelConfiguration->setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
			fillAssistedNameLabelConfiguration->setLabel_VerticalPadding(1);
			fillAssistedNameLabelConfiguration->setLabel_HorizontalPadding(1);
			fillAssistedNameLabelConfiguration->setLabel_Family("Verdana");
			fillAssistedNameLabelConfiguration->setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			fillAssistedNameLabelConfiguration->setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			fillAssistedNameLabelConfiguration->setLabel_Size(14);
			assistedCardConf->setNameLabelConfiguration(*fillAssistedNameLabelConfiguration);

			activationCardConf->setShowAudioCheck(false);
			activationCardConf->setCustomAttributesPresentation("EventBoxes");
			activationCardConf->setShowConfirmationButtons(false);
			activationCardConf->setMinimumDemoCounterToAllowActivation(1);
			activationCardConf->setAssistedActivationBySelection(false);
			activationCardConf->setActivatedAfterInsertingCard(true);

			CountConfiguration cardActivationTotalCount;
			CountConfiguration::CountTypeSequence countTypeSequence;
			countTypeSequence.push_back(CountTypeConfig::CONFIGURATION_TOTAL);
			cardActivationTotalCount.setCountType(countTypeSequence);

			activationCardConf->setCardActivationTotalCountConfiguration(cardActivationTotalCount);

						//Color Configuration
						selectedColorCardActiv->setRed(35500);
						selectedColorCardActiv->setGreen(35500);
						selectedColorCardActiv->setBlue(60000);

						//Color Configuration
						unSelectedColorCardActiv->setRed(65535);
						unSelectedColorCardActiv->setGreen(65535);
						unSelectedColorCardActiv->setBlue(65535);



						//Color Configuration
						ColorConfiguration activatedCardStatisticsTitleColor;
						activatedCardStatisticsTitleColor.setRed(65535);
						activatedCardStatisticsTitleColor.setGreen(65535);
						activatedCardStatisticsTitleColor.setBlue(65535);
						//Statistics Conf
						ActivatedCardStatisticsConfiguration cardStatisticsConf;
						cardStatisticsConf.setHideOfficial(false);
						cardStatisticsConf.setHideDemo(true);
						cardStatisticsConf.setHideRecovery(true);
						cardStatisticsConf.setHideAudio(true);
						cardStatisticsConf.setHideNonAudio(true);
						cardStatisticsConf.setHideCA(false);

		XMLLabelConfiguration activatedCardStatisticsTitleLabelConf;
				activatedCardStatisticsTitleLabelConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				activatedCardStatisticsTitleLabelConf.setLabel_VerticalPadding(1);
				activatedCardStatisticsTitleLabelConf.setLabel_HorizontalPadding(1);
				activatedCardStatisticsTitleLabelConf.setLabel_Family("Verdana");
				activatedCardStatisticsTitleLabelConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				activatedCardStatisticsTitleLabelConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				activatedCardStatisticsTitleLabelConf.setLabel_Size(20);

			activationCardConf->setStatisticsTitleLabelConfiguration(activatedCardStatisticsTitleLabelConf);
			activationCardConf->setCardStatisticsConfiguration(cardStatisticsConf);
			activationCardConf->setSelectedColor(*selectedColorCardActiv);
			activationCardConf->setUnSelectedColor(*unSelectedColorCardActiv);
			activationCardConf->setStatisticsTitleLabelConfiguration(activatedCardStatisticsTitleLabelConf);
			activationCardConf->setStatisticsTitleColor(activatedCardStatisticsTitleColor);
		buttonInfoEn->setLanguageCode("en");
			buttonInfoEn->setLanguageImageFile("en.jpg");
			buttonInfoNl->setLanguageCode("nl");
			buttonInfoNl->setLanguageImageFile("nl.jpg");
			seqLanguageButtonSequence->push_back(*buttonInfoEn);
			seqLanguageButtonSequence->push_back(*buttonInfoNl);
			languageSelectionConf->setLanguageButton(*seqLanguageButtonSequence);

			contingencyCardWidget->setRetryButtonConf (contingencyCardWidgetRetryButtonConf);
			contingencyCardWidget->setShutdownButtonConf (contingencyCardWidgetShutdownButtonConf);
			contingencyCardWidget->setTitleFontConf (contingencyCardWidgetTitleFontConf);
			contingencyCardWidget->setTextFontConf (contingencyCardWidgetTextFontConf);

			waitingCardWindow->setShowSimulateButton(true);
			waitingCardWindow->setShowBackButton(true);
			waitingCardWindow->setViewPrevious(false);
			waitingCardWindow->setAllowVotePreview(true);
			waitingCardWindow->setUsePrintPreview(true);
			waitingCardWindow->setUseVerticalTableInPreview(true);
			waitingCardWindow->setTimeoutPreviewVote(90);
			waitingCardWindow->setTimeoutPreviewVoteClose(3);
			waitingCardWindow->setBarcodeCommandsName("baseconfiguration");
			waitingCardWindow->setPreviewLanguageConfig(PreviewLanguageConfig::CONFIGURATION_LANGUAGE_VOTE);
			waitingCardWindow->setBlockOnCardInsertionError (false);
			waitingCardWindow->setIsNeopBlockingCondition (true);

		XMLLabelConfiguration waitingCardPreviewVoteTitleLabelConf;
				waitingCardPreviewVoteTitleLabelConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				waitingCardPreviewVoteTitleLabelConf.setLabel_VerticalPadding(1);
				waitingCardPreviewVoteTitleLabelConf.setLabel_HorizontalPadding(1);
				waitingCardPreviewVoteTitleLabelConf.setLabel_Family("Verdana");
				waitingCardPreviewVoteTitleLabelConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				waitingCardPreviewVoteTitleLabelConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				waitingCardPreviewVoteTitleLabelConf.setLabel_Size(20);

		waitingCardWindow->setPreviewVoteLabelConfiguration(waitingCardPreviewVoteTitleLabelConf);

		Smartmatic::SAES::Configuration::ButtonConfiguration waitingCardPreviewVoteButtonConf;
		waitingCardPreviewVoteButtonConf.setButtonWidth(100);
		waitingCardPreviewVoteButtonConf.setButtonHeight(120);
		waitingCardPreviewVoteButtonConf.setFontSize(20);

		waitingCardWindow->setPreviewVoteButtonConfiguration(waitingCardPreviewVoteButtonConf);

		FunctionalityConfiguration confOpenElection;
		confOpenElection.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMOPENELECTIONFUNCTIONALITY);
		confOpenElection.setFunctionalityExitToAuthentication(false);
		confOpenElection.setElectionBlockStatus(*listElectionNotInitiated);
		confOpenElection.setChallengeIsEnable(false);
		confOpenElection.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confOpenElection.setShowExitMessage(true);
		confOpenElection.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
			helpStandardFunctionality.setImageHelp("ui/open-election-help.gif");
			helpStandardFunctionality.setPdfHelp("ui/open-election-help.pdf");
			helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.OpenElection"));
			helpStandardFunctionality.setUseHelp(false);
		confOpenElection.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confCloseElection;
		confCloseElection.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCLOSEELECTIONFUNCTIONALITY);
		confCloseElection.setElectionBlockStatus(*listElectionClosed);
		confCloseElection.setFunctionalityExitToAuthentication(false);
		confCloseElection.setChallengeIsEnable(false);
		confCloseElection.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confCloseElection.setShowExitMessage(true);
		confCloseElection.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
			helpStandardFunctionality.setImageHelp("ui/close-election-help.gif");
			helpStandardFunctionality.setPdfHelp("ui/close-election-help.pdf");
			helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.CloseElection"));
			helpStandardFunctionality.setUseHelp(false);
		confCloseElection.setHelp(helpStandardFunctionality);
		
		FunctionalityConfiguration confDiagnosis;
		confDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMDIAGNOSISFUNCTIONALITY);
		confDiagnosis.setFunctionalityExitToAuthentication(false);
		confDiagnosis.setChallengeIsEnable(false);
		confDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confDiagnosis.setShowExitMessage(false);
		confDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
			helpStandardFunctionality.setImageHelp("ui/diagnosis-help.gif");
			helpStandardFunctionality.setPdfHelp("ui/diagnosis-help.pdf");
			helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.Diagnosis"));
			helpStandardFunctionality.setUseHelp(false);
		confDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confSCReaderDiagnosis;
		confSCReaderDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMSCREADERDIAGNOSISFUNCTIONALITY);
		confSCReaderDiagnosis.setFunctionalityExitToAuthentication(false);
		confSCReaderDiagnosis.setChallengeIsEnable(false);
		confSCReaderDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confSCReaderDiagnosis.setShowExitMessage(false);
		confSCReaderDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
			helpStandardFunctionality.setImageHelp("ui/sc-reader-diagnosis-help.gif");
			helpStandardFunctionality.setPdfHelp("ui/sc-reader-diagnosis-help.pdf");
			helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.ReaderDiagnosis"));
			helpStandardFunctionality.setUseHelp(false);
		confSCReaderDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confPrinterDiagnosis;
		confPrinterDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMPRINTERDIAGNOSISFUNCTIONALITY);
		confPrinterDiagnosis.setFunctionalityExitToAuthentication(false);
		confPrinterDiagnosis.setChallengeIsEnable(false);
		confPrinterDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confPrinterDiagnosis.setShowExitMessage(false);
		confPrinterDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
					helpStandardFunctionality.setImageHelp("ui/printer-diagnosis-help.gif");
					helpStandardFunctionality.setPdfHelp("ui/printer-diagnosis-help.pdf");
					helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.PrinterDiagnosis"));
					helpStandardFunctionality.setUseHelp(false);
		confPrinterDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confAlarmBDiagnosis;
		confAlarmBDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMALARMBOXDIAGNOSISFUNCTIONALITY);
		confAlarmBDiagnosis.setFunctionalityExitToAuthentication(false);
		confAlarmBDiagnosis.setChallengeIsEnable(false);
		confAlarmBDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confAlarmBDiagnosis.setShowExitMessage(false);
		confAlarmBDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/alarm-box-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/alarm-box-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.AlarmBoxDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confAlarmBDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confCalibDiagnosis;
		confCalibDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCALIBRATIONDIAGNOSISFUNCTIONALITY);
		confCalibDiagnosis.setFunctionalityExitToAuthentication(false);
		confCalibDiagnosis.setChallengeIsEnable(false);
		confCalibDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confCalibDiagnosis.setShowExitMessage(false);
		confCalibDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/calibration-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/calibration-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.CalibrationDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confCalibDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confBrightnessDiagnosis;
		confBrightnessDiagnosis.setFunctionalityDescriptor( MenuOptionType::CONFIGURATION_XMLMBRIGHTNESSDIAGNOSISFUNCTIONALITY);
		confBrightnessDiagnosis.setFunctionalityExitToAuthentication(false);
		confBrightnessDiagnosis.setChallengeIsEnable(false);
		confBrightnessDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confBrightnessDiagnosis.setShowExitMessage(false);
		confBrightnessDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/brightness-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/brightness-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.BirghtnessDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confBrightnessDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confBarcodeDiagnosis;
		confBarcodeDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMBARCODEDIAGNOSISFUNCTIONALITY);
		confBarcodeDiagnosis.setFunctionalityExitToAuthentication(false);
		confBarcodeDiagnosis.setChallengeIsEnable(false);
		confBarcodeDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confBarcodeDiagnosis.setShowExitMessage(false);
		confBarcodeDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/barcode-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/barcode-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.BarcodeDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confBarcodeDiagnosis.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesBarcodeDiagnosis;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndBarcodeDiagnosis;
		ndBarcodeDiagnosis.push_back(barcodeDevice);
		necessaryDevicesBarcodeDiagnosis.setDeviceConfiguration(ndBarcodeDiagnosis);
		confBarcodeDiagnosis.setNecessaryDevicesConfiguration(necessaryDevicesBarcodeDiagnosis);

		FunctionalityConfiguration confAllDiagnosis;
		confAllDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMALLDIAGNOSISFUNCTIONALITY);
		confAllDiagnosis.setFunctionalityExitToAuthentication(false);
		confAllDiagnosis.setChallengeIsEnable(false);
		confAllDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confAllDiagnosis.setShowExitMessage(false);
		confAllDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/all-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/all-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.AllDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confAllDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confFlashDiagnosis;
		confFlashDiagnosis.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMFLASHDIAGNOSISFUNCTIONALITY);
		confFlashDiagnosis.setFunctionalityExitToAuthentication(false);
		confFlashDiagnosis.setChallengeIsEnable(false);
		confFlashDiagnosis.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confFlashDiagnosis.setShowExitMessage(false);
		confFlashDiagnosis.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/flash-diagnosis-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/flash-diagnosis-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.FlashDiagnosis"));
				helpStandardFunctionality.setUseHelp(false);
		confFlashDiagnosis.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confChangeHour;
		confChangeHour.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCHANGEHOURFUNCTIONALITY);
		confChangeHour.setFunctionalityExitToAuthentication(false);
		confChangeHour.setChallengeIsEnable(false);
		confChangeHour.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confChangeHour.setShowExitMessage(true);
		confChangeHour.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/change-hour-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/change-hour-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.ChangeHour"));
				helpStandardFunctionality.setUseHelp(false);
		confChangeHour.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confCardGenerator;
		confCardGenerator.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCARDGENERATORFUNCTIONALITY);
		confCardGenerator.setElectionBlockStatus(*listElectionInitiated);
		confCardGenerator.setFunctionalityExitToAuthentication(false);
		confCardGenerator.setChallengeIsEnable(false);
		confCardGenerator.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confCardGenerator.setShowExitMessage(false);
		confCardGenerator.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_ALLOW);
				helpStandardFunctionality.setImageHelp("ui/card-generator-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/card-generator-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.CardGenerator"));
				helpStandardFunctionality.setUseHelp(true);
		confCardGenerator.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesCardGenerator;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndCardGenerator;
		ndCardGenerator.push_back(smartcardDevice);
		necessaryDevicesCardGenerator.setDeviceConfiguration(ndCardGenerator);
		confCardGenerator.setNecessaryDevicesConfiguration(necessaryDevicesCardGenerator);

		FunctionalityConfiguration confAssistedCardGenerator;
		confAssistedCardGenerator.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMASSISTEDCARDGENERATORFUNCTIONALITY);
		confAssistedCardGenerator.setElectionBlockStatus(*listElectionInitiated);
		confAssistedCardGenerator.setFunctionalityExitToAuthentication(false);
		confAssistedCardGenerator.setChallengeIsEnable(false);
		confAssistedCardGenerator.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confAssistedCardGenerator.setShowExitMessage(false);
		confAssistedCardGenerator.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/assisted-card-generator-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/assisted-card-generator-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.AssistedCardGenerator"));
				helpStandardFunctionality.setUseHelp(true);
		confAssistedCardGenerator.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesAssistedCardGenerator;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndAssistedCardGenerator;
		ndAssistedCardGenerator.push_back(smartcardDevice);
		necessaryDevicesAssistedCardGenerator.setDeviceConfiguration(ndAssistedCardGenerator);
		confAssistedCardGenerator.setNecessaryDevicesConfiguration(necessaryDevicesAssistedCardGenerator);

		FunctionalityConfiguration confRecoveryCardGenerator;
		confRecoveryCardGenerator.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMRECOVERYCARDGENERATORFUNCTIONALITY);
		confRecoveryCardGenerator.setElectionBlockStatus(*listElectionClosed);
		confRecoveryCardGenerator.setFunctionalityExitToAuthentication(false);
		confRecoveryCardGenerator.setChallengeIsEnable(false);
		confRecoveryCardGenerator.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confRecoveryCardGenerator.setShowExitMessage(false);
		confRecoveryCardGenerator.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/recovery-card-generator-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/recovery-card-generator-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.RecoveryCardGenerator"));
				helpStandardFunctionality.setUseHelp(false);
		confRecoveryCardGenerator.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesRecoveryCardGenerator;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndRecoveryCardGenerator;
		ndRecoveryCardGenerator.push_back(smartcardDevice);
		necessaryDevicesRecoveryCardGenerator.setDeviceConfiguration(ndRecoveryCardGenerator);
		confRecoveryCardGenerator.setNecessaryDevicesConfiguration(necessaryDevicesRecoveryCardGenerator);

		FunctionalityConfiguration confVotingMachineInstallation;
		confVotingMachineInstallation.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTINGMACHINEINSTALLATIONFUNCTIONALITY);
		confVotingMachineInstallation.setFunctionalityExitToAuthentication(false);
		confVotingMachineInstallation.setChallengeIsEnable(false);
		confVotingMachineInstallation.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confVotingMachineInstallation.setShowExitMessage(true);
		confVotingMachineInstallation.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/voting-machine-installation-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/voting-machine-installation-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.VotingMachineInstallation"));
				helpStandardFunctionality.setUseHelp(false);
		confVotingMachineInstallation.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesVotingMachineInstallation;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndVotingMachineInstallation;
		ndVotingMachineInstallation.push_back(smartcardDevice);
		necessaryDevicesVotingMachineInstallation.setDeviceConfiguration(ndVotingMachineInstallation);
		confVotingMachineInstallation.setNecessaryDevicesConfiguration(necessaryDevicesVotingMachineInstallation);

		FunctionalityConfiguration confChangeLanguage;
		confChangeLanguage.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCHANGELANGUAGEFUNCTIONALITY);
		confChangeLanguage.setFunctionalityExitToAuthentication(false);
		confChangeLanguage.setChallengeIsEnable(false);
		confChangeLanguage.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confChangeLanguage.setShowExitMessage(true);
		confChangeLanguage.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/change-language-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/change-language-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.ChangeLanguage"));
				helpStandardFunctionality.setUseHelp(false);
		confChangeLanguage.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confVoteProcessDemo;
		confVoteProcessDemo.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTEPROCESSDEMOFUNCTIONALITY);
		confVoteProcessDemo.setFunctionalityExitToAuthentication(false);
		confVoteProcessDemo.setChallengeIsEnable(false);
		confVoteProcessDemo.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confVoteProcessDemo.setShowExitMessage(true);
		confVoteProcessDemo.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/vote-process-demo-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/vote-process-demo-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.VoteProcessDemo"));
				helpStandardFunctionality.setUseHelp(false);
		confVoteProcessDemo.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesVoteProcessDemo;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndVoteProcessDemo;
		ndVoteProcessDemo.push_back(smartcardDevice);
		ndVoteProcessDemo.push_back(barcodeDevice);
		necessaryDevicesVoteProcessDemo.setDeviceConfiguration(ndVoteProcessDemo);
		confVoteProcessDemo.setNecessaryDevicesConfiguration(necessaryDevicesVoteProcessDemo);

		FunctionalityConfiguration confPrintPreview;
		confPrintPreview.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMPRINTPREVIEWFUNCTIONALITY);
		confPrintPreview.setFunctionalityExitToAuthentication(false);
		confPrintPreview.setChallengeIsEnable(false);
		confPrintPreview.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confPrintPreview.setShowExitMessage(false);
		confPrintPreview.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/print-preview-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/print-preview-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.PrintPreview"));
				helpStandardFunctionality.setUseHelp(false);
		confPrintPreview.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesPrintPreview;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndPrintPreview;
		ndPrintPreview.push_back(barcodeDevice);
		necessaryDevicesPrintPreview.setDeviceConfiguration(ndPrintPreview);
		confPrintPreview.setNecessaryDevicesConfiguration(necessaryDevicesPrintPreview);

		FunctionalityConfiguration confIncidentReport;
		confIncidentReport.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMINCIDENTREPORTFUNCTIONALITY);
		confIncidentReport.setFunctionalityExitToAuthentication(false);
		confIncidentReport.setChallengeIsEnable(false);
		confIncidentReport.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confIncidentReport.setShowExitMessage(true);
		confIncidentReport.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/incident-report-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/incident-report-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.IncidentReport"));
				helpStandardFunctionality.setUseHelp(false);
		confIncidentReport.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confStatisticsReport;
		confStatisticsReport.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMSTATISTICSREPORTFUNCTIONALITY);
		confStatisticsReport.setFunctionalityExitToAuthentication(false);
		confStatisticsReport.setChallengeIsEnable(false);
		confStatisticsReport.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confStatisticsReport.setShowExitMessage(true);
		confStatisticsReport.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/statistics-report-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/statistics-report-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.StatisticsReport"));
				helpStandardFunctionality.setUseHelp(false);
		confStatisticsReport.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confPollworkersRegister;
		confPollworkersRegister.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMPOLLWORKERREGISTERFUNCTIONALITY);
		confPollworkersRegister.setFunctionalityExitToAuthentication(false);
		confPollworkersRegister.setChallengeIsEnable(false);
		confPollworkersRegister.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confPollworkersRegister.setShowExitMessage(true);
		confPollworkersRegister.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/pollworker-register-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/pollworker-register-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.PollworkerRegister"));
				helpStandardFunctionality.setUseHelp(false);
		confPollworkersRegister.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confVotingExperienceValidation;
		confVotingExperienceValidation.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTINGEXPERIENCEVALIDATIONFUNCTIONALITY);
		confVotingExperienceValidation.setFunctionalityExitToAuthentication(false);
		confVotingExperienceValidation.setChallengeIsEnable(false);
		confVotingExperienceValidation.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confVotingExperienceValidation.setShowExitMessage(false);
		confVotingExperienceValidation.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/voting-experience-validation-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/voting-experience-validation-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.VotingExperienceValidation"));
				helpStandardFunctionality.setUseHelp(false);
		confVotingExperienceValidation.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confCloseVotation;
		confCloseVotation.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMCLOSEVOTATIONFUNCTIONALITY);
		confCloseVotation.setElectionBlockStatus(*listElectionInitiated);
		confCloseVotation.setFunctionalityExitToAuthentication(false);
		confCloseVotation.setChallengeIsEnable(false);
		confCloseVotation.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confCloseVotation.setShowExitMessage(true);
		confCloseVotation.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/close-votation-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/close-votation-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.CloseVotation"));
				helpStandardFunctionality.setUseHelp(false);
		confCloseVotation.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confVoteConsolidation;
		confVoteConsolidation.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTECONSOLIDATIONFUNCTIONALITY);
		confVoteConsolidation.setFunctionalityExitToAuthentication(false);
		confVoteConsolidation.setChallengeIsEnable(false);
		confVoteConsolidation.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confVoteConsolidation.setShowExitMessage(true);
		confVoteConsolidation.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
		confVoteConsolidation.setElectionBlockStatus(*listElectionClosed);
				helpStandardFunctionality.setImageHelp("ui/vote-consolidation-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/vote-consolidation-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.VoteConsolidation"));
				helpStandardFunctionality.setUseHelp(false);
		confVoteConsolidation.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesVoteConsolidation;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndVoteConsolidation;
		ndVoteConsolidation.push_back(barcodeDevice);
		necessaryDevicesVoteConsolidation.setDeviceConfiguration(ndVoteConsolidation);
		confVoteConsolidation.setNecessaryDevicesConfiguration(necessaryDevicesVoteConsolidation);

		FunctionalityConfiguration confFillAssistedActivationInfo;
		confFillAssistedActivationInfo.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMFILLASSISTEDACTIVATIONINFOFUNCTIONALITY);
		confFillAssistedActivationInfo.setFunctionalityExitToAuthentication(false);
		confFillAssistedActivationInfo.setChallengeIsEnable(false);
		confFillAssistedActivationInfo.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confFillAssistedActivationInfo.setShowExitMessage(false);
		confFillAssistedActivationInfo.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/fill-assisted-info-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/fill-assisted-info-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.FillAssistedInfo"));
				helpStandardFunctionality.setUseHelp(false);
		confFillAssistedActivationInfo.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesFillAssistedActivationInfo;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndFillAssistedActivationInfo;
		ndFillAssistedActivationInfo.push_back(smartcardDevice);
		necessaryDevicesFillAssistedActivationInfo.setDeviceConfiguration(ndFillAssistedActivationInfo);
		confFillAssistedActivationInfo.setNecessaryDevicesConfiguration(necessaryDevicesFillAssistedActivationInfo);


		FunctionalityConfiguration confVotingForDisabledInfo;
		confVotingForDisabledInfo.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTINGFORDISABLEDFUNCTIONALITY);
		confVotingForDisabledInfo.setFunctionalityExitToAuthentication(false);
		confVotingForDisabledInfo.setChallengeIsEnable(false);
		confVotingForDisabledInfo.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confVotingForDisabledInfo.setShowExitMessage(false);
		confVotingForDisabledInfo.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/voting-for-disabled-info-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/voting-for-disabled-info-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.VotingForDisabledInfo"));
				helpStandardFunctionality.setUseHelp(false);
				confVotingForDisabledInfo.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesVotingForDisabledInfo;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndVotingForDisabledInfo;
		necessaryDevicesVotingForDisabledInfo.setDeviceConfiguration(ndVotingForDisabledInfo);
		confVotingForDisabledInfo.setNecessaryDevicesConfiguration(necessaryDevicesVotingForDisabledInfo);

		FunctionalityConfiguration confPoliceFunctionality;
		confPoliceFunctionality.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMPOLICENOTESFUNCTIONALITY);
		confPoliceFunctionality.setFunctionalityExitToAuthentication(false);
		confPoliceFunctionality.setChallengeIsEnable(false);
		confPoliceFunctionality.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confPoliceFunctionality.setShowExitMessage(false);
		confPoliceFunctionality.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/police-info-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/police-info-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.PoliceFunctionalityInfo"));
				helpStandardFunctionality.setUseHelp(false);
		confPoliceFunctionality.setHelp(helpStandardFunctionality);
		confPoliceFunctionality.setNecessaryDevicesConfiguration(necessaryDevicesVotingForDisabledInfo);


		FunctionalityConfiguration confRegisterPresidentNote;
		confRegisterPresidentNote.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMREGISTERPRESIDENTNOTESFUNCTIONALITY);
		confRegisterPresidentNote.setFunctionalityExitToAuthentication(false);
		confRegisterPresidentNote.setChallengeIsEnable(false);
		confRegisterPresidentNote.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confRegisterPresidentNote.setShowExitMessage(true);
		confRegisterPresidentNote.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
		confRegisterPresidentNote.setElectionBlockStatus(*listElectionClosed);
				helpStandardFunctionality.setImageHelp("ui/register-president-notes-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/register-president-notes-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.RegisterPresidentNotes"));
				helpStandardFunctionality.setUseHelp(false);
		confRegisterPresidentNote.setHelp(helpStandardFunctionality);

		FunctionalityConfiguration confActivationConsolidation;

		NecessaryDevicesConfiguration necessaryDevicesActivationConsolidation;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndActivationConsolidation;
		ndActivationConsolidation.push_back(smartcardDevice);
		necessaryDevicesActivationConsolidation.setDeviceConfiguration(ndActivationConsolidation);
		confActivationConsolidation.setNecessaryDevicesConfiguration(necessaryDevicesActivationConsolidation);

		confActivationConsolidation.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMACTIVATIONCONSOLIDATIONFUNCTIONALITY);
		confActivationConsolidation.setFunctionalityExitToAuthentication(false);
		confActivationConsolidation.setChallengeIsEnable(false);
		confActivationConsolidation.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confActivationConsolidation.setShowExitMessage(true);
		confActivationConsolidation.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_ALLOW);
		confActivationConsolidation.setElectionBlockStatus(*listElectionInitiated);
				helpStandardFunctionality.setImageHelp("ui/activation-consolidation-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/activation-consolidation-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.ActivationConsolidation"));
				helpStandardFunctionality.setUseHelp(false);
		confActivationConsolidation.setHelp(helpStandardFunctionality);


		FunctionalityConfiguration confReportPrinting;
		confReportPrinting.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMMREPORTPRINTINGFUNCTIONALITY);
		confReportPrinting.setFunctionalityExitToAuthentication(false);
		confReportPrinting.setElectionBlockStatus(*listElectionResults);
		confReportPrinting.setChallengeIsEnable(false);
		confReportPrinting.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confReportPrinting.setShowExitMessage(false);
		confReportPrinting.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/report-printing-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/report-printing-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.ReportPrinting"));
				helpStandardFunctionality.setUseHelp(false);
		confReportPrinting.setHelp(helpStandardFunctionality);

		NecessaryDevicesConfiguration necessaryDevicesReportPrinting;
		NecessaryDevicesConfiguration::DeviceConfigurationSequence ndReportPrinting;
		ndReportPrinting.push_back(printerDevice);
		necessaryDevicesReportPrinting.setDeviceConfiguration(ndReportPrinting);
		confReportPrinting.setNecessaryDevicesConfiguration(necessaryDevicesReportPrinting);

		FunctionalityConfiguration confLogReport;
		confLogReport.setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMLOGREPORTFUNCTIONALITY);
		confLogReport.setFunctionalityExitToAuthentication(false);
		confLogReport.setChallengeIsEnable(false);
		confLogReport.setChallengePasswordSource(ChallengePasswordSourceEnum::CONFIGURATION_ROLE);
		confLogReport.setShowExitMessage(false);
		confLogReport.setBlockMemoryBehavior(MemoryBlock::CONFIGURATION_SUSPEND);
				helpStandardFunctionality.setImageHelp("ui/log-report-help.gif");
				helpStandardFunctionality.setPdfHelp("ui/log-report-help.pdf");
				helpStandardFunctionality.setTitleKey(N_("Smartmatic.SAES.GUI.HelpConfiguration.LogReport"));
				helpStandardFunctionality.setUseHelp(false);
		confLogReport.setHelp(helpStandardFunctionality);

		funcConfigSequence->push_back(confOpenElection);
		funcConfigSequence->push_back(confCloseElection);
		funcConfigSequence->push_back(confDiagnosis);
		funcConfigSequence->push_back(confSCReaderDiagnosis);
		funcConfigSequence->push_back(confPrinterDiagnosis);
		funcConfigSequence->push_back(confAlarmBDiagnosis);
		funcConfigSequence->push_back(confCalibDiagnosis);
		funcConfigSequence->push_back(confBrightnessDiagnosis);
		funcConfigSequence->push_back(confBarcodeDiagnosis);
		funcConfigSequence->push_back(confAllDiagnosis);
		funcConfigSequence->push_back(confFlashDiagnosis);
		funcConfigSequence->push_back(confChangeHour);
		funcConfigSequence->push_back(confCardGenerator);
		funcConfigSequence->push_back(confAssistedCardGenerator);
		funcConfigSequence->push_back(confRecoveryCardGenerator);
		funcConfigSequence->push_back(confVotingMachineInstallation);
		funcConfigSequence->push_back(confChangeLanguage);
		funcConfigSequence->push_back(confVoteProcessDemo);
		funcConfigSequence->push_back(confPrintPreview);
		funcConfigSequence->push_back(confIncidentReport);
		funcConfigSequence->push_back(confStatisticsReport);
		funcConfigSequence->push_back(confPollworkersRegister);
		funcConfigSequence->push_back(confVotingExperienceValidation);
		funcConfigSequence->push_back(confCloseVotation);
		funcConfigSequence->push_back(confVoteConsolidation);
		funcConfigSequence->push_back(confFillAssistedActivationInfo);
		funcConfigSequence->push_back(confVotingForDisabledInfo);
		funcConfigSequence->push_back(confPoliceFunctionality);
		funcConfigSequence->push_back(confRegisterPresidentNote);
		funcConfigSequence->push_back(confActivationConsolidation);
		funcConfigSequence->push_back(confLogReport);
		funcConfigSequence->push_back(confReportPrinting);
		funcConfiguration->setFunctionalityConfiguration(*funcConfigSequence);
		
		
		runFuncConfig->setFunctionalityDescriptor(MenuOptionType::CONFIGURATION_XMLMVOTINGEXPERIENCEVALIDATIONFUNCTIONALITY);
		
		generalDiag->setDiagnosisLabelConfiguration (*diagnosisLabelConfiguration);
		generalDiag->setDiagnosisFooterLabelConfiguration (diagnosisFooterLabelConfiguration);
		generalDiag->setResultErrorLabelConfiguration(resultErrorLabelConfiguration);

		installWizardConfig->setAskForId(true);
		installWizardConfig->setIncomePassphrase(IncomePassphraseEnum::CONFIGURATION_TOKEN);

		EntryDividedWidgetConfiguration entryPassword;
		EntryDividedWidgetConfiguration entryContingency;

		pmWidgetConfig->setShowImages(true);
		pmWidgetConfig->setLoginCaseSensitiveConfiguration(true);

		entryPassword.setNumberOfDivision(4);
		entryPassword.setMaxCharacters(4);
		entryPassword.setEntryWidth(55);
		entryPassword.setVisibility(false);

		entryContingency.setNumberOfDivision(4);
		entryContingency.setMaxCharacters(4);
		entryContingency.setEntryWidth(45);
		entryContingency.setVisibility(false);

		pmWidgetConfig->setPasswordWidgetConfiguration(entryPassword);
		pmWidgetConfig->setContingencyWidgetConfiguration(entryContingency);

		XMLLabelConfiguration authenticationPasswordLabelConfiguration;
		authenticationPasswordLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		authenticationPasswordLabelConfiguration.setLabel_VerticalPadding(0);
		authenticationPasswordLabelConfiguration.setLabel_HorizontalPadding(1);
		authenticationPasswordLabelConfiguration.setLabel_Family("Verdana");
		authenticationPasswordLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		authenticationPasswordLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		authenticationPasswordLabelConfiguration.setLabel_Size(50);

		XMLLabelConfiguration authenticationAlarmLabelConfiguration;
		authenticationAlarmLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		authenticationAlarmLabelConfiguration.setLabel_VerticalPadding(0);
		authenticationAlarmLabelConfiguration.setLabel_HorizontalPadding(1);
		authenticationAlarmLabelConfiguration.setLabel_Family("Verdana");
		authenticationAlarmLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		authenticationAlarmLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		authenticationAlarmLabelConfiguration.setLabel_Size(14);

		XMLLabelConfiguration authenticationInfoLabelConfiguration;
		authenticationInfoLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		authenticationInfoLabelConfiguration.setLabel_VerticalPadding(0);
		authenticationInfoLabelConfiguration.setLabel_HorizontalPadding(1);
		authenticationInfoLabelConfiguration.setLabel_Family("Verdana");
		authenticationInfoLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		authenticationInfoLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		authenticationInfoLabelConfiguration.setLabel_Size(20);

		XMLLabelConfiguration authenticationVotingInfoLabelConfiguration;
		authenticationVotingInfoLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		authenticationVotingInfoLabelConfiguration.setLabel_VerticalPadding(0);
		authenticationVotingInfoLabelConfiguration.setLabel_HorizontalPadding(1);
		authenticationVotingInfoLabelConfiguration.setLabel_Family("Verdana");
		authenticationVotingInfoLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		authenticationVotingInfoLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		authenticationVotingInfoLabelConfiguration.setLabel_Size(14);

		authWindowConf.setPasswordLabelConfiguration(authenticationPasswordLabelConfiguration);
		authWindowConf.setAlarmLabelConfiguration(authenticationAlarmLabelConfiguration);
		authWindowConf.setInfoLabelConfiguration(authenticationInfoLabelConfiguration);
		authWindowConf.setVotingInfoLabelConfiguration(authenticationVotingInfoLabelConfiguration);

		configSAESGUI->setFunctionalitiesConfiguration(*funcConfiguration);
		configSAESGUI->setRunFunctionalityConfiguration(*runFuncConfig);
		configSAESGUI->setInstallationWizardConfiguration(*installWizardConfig);
		configSAESGUI->setPMWidgetConfiguration(*pmWidgetConfig);
		configSAESGUI->setTouchScreenCalibrationConfiguration(*touchDiagConfig);
		configSAESGUI->setVotingExperience(*votingExperienceConfiguration);
		configSAESGUI->setGeneralDiagnosisConfiguration(*generalDiag);
		configSAESGUI->setPrinterDiagnosisConfiguration(*printerDiagnosisConf);
		configSAESGUI->setSmartCardReaderDiagnosisConfiguration(*screaderDiagnosisConf);
		configSAESGUI->setBarcodeDiagnosisConfiguration(*barcodeDiagnosisConf);
		configSAESGUI->setBrightnessDiagnosisConfiguration(*brightnessDiagnosisConf);
		configSAESGUI->setAllDiagnosisConfiguration(*allDiagnosisConf);
		configSAESGUI->setAutomaticWindowConfiguration(*autoDiagnosisConf);
		configSAESGUI->setLanguageSelectionWindowConfiguration(*languageSelectionConf);
		configSAESGUI->setCardActivatorFunctionalityConfiguration(*activationCardConf);
		configSAESGUI->setCardRecoveryFunctionalityConfiguration(*recoveryCardConf);
		configSAESGUI->setVoteDemoFunctionalityConfiguration(*voteDemoConf);
		configSAESGUI->setCardAssistedActivationFunctionalityConfiguration(*assistedCardConf);
		configSAESGUI->setWaitingForCardWindowConfiguration(*waitingCardWindow);
		configSAESGUI->setContingencyCardWidgetConfiguration(*contingencyCardWidget);
		configSAESGUI->setFormsCommonControls(*formCommonControl);
		configSAESGUI->setAuthenticationWindowConfiguration(authWindowConf);

		statsConfiguration->setRowsSpacing(30);
		statsConfiguration->setColumnsSpacing(30);
		statsConfiguration->setButtonConfiguration(*buttonBoxConfig);

			XMLLabelConfiguration titleLabelStatsConfiguration;
			titleLabelStatsConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			titleLabelStatsConfiguration.setLabel_VerticalPadding(1);
			titleLabelStatsConfiguration.setLabel_HorizontalPadding(1);
			titleLabelStatsConfiguration.setLabel_Family("Verdana");
			titleLabelStatsConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			titleLabelStatsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			titleLabelStatsConfiguration.setLabel_Size(16);
		statsConfiguration->setTitleLabelConfiguration(titleLabelStatsConfiguration);

			XMLLabelConfiguration statsLabelStatsConfiguration;
			statsLabelStatsConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			statsLabelStatsConfiguration.setLabel_VerticalPadding(1);
			statsLabelStatsConfiguration.setLabel_HorizontalPadding(1);
			statsLabelStatsConfiguration.setLabel_Family("Verdana");
			statsLabelStatsConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			statsLabelStatsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			statsLabelStatsConfiguration.setLabel_Size(12);
		statsConfiguration->setStatisticsLabelConfiguration(statsLabelStatsConfiguration);
		configSAESGUI->setStatisticFunctionalityConfiguration(*statsConfiguration);

		//open election functionality
			pollWorkerDialogLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_RIGHT);
			pollWorkerDialogLabelConfiguration.setLabel_VerticalPadding(1);
			pollWorkerDialogLabelConfiguration.setLabel_HorizontalPadding(1);
			pollWorkerDialogLabelConfiguration.setLabel_Family("Verdana");
			pollWorkerDialogLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			pollWorkerDialogLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			pollWorkerDialogLabelConfiguration.setLabel_Size(16);
		openElectionConfig->setDialogLabelConfiguration(pollWorkerDialogLabelConfiguration);
		openElectionConfig->setShowTitle(false);
		openElectionConfig->setButtonConfiguration(*buttonBoxConfig);

		OpenElectionFunctionalityConfiguration::OpenElectionStepsSequence openSeq;
		openSeq.push_back(OpenElectionSteps(OpenElectionSteps::CONFIGURATION_REGISTERNOTE));
		openSeq.push_back(OpenElectionSteps(OpenElectionSteps::CONFIGURATION_REQUESTIDCARD));
		openSeq.push_back(OpenElectionSteps(OpenElectionSteps::CONFIGURATION_OPENELECTION));

		openElectionConfig->setOpenElectionSteps(openSeq);

		configSAESGUI->setOpenElectionFunctionalityConfiguration(*openElectionConfig);
		
		//close election functionality

		CloseElectionFunctionalityConfiguration::ClosingElectionStepsSequence closeSeq;

		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_CLOSECONFIRMATION);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_REQUESTIDCARD);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_REGISTERCLOSENOTE);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_STATISTICS);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_VOTEDURATION);
		//closeSeq.push_back(CloseElectionSteps::CONFIGURATION_GENERATETRANSMISSIONPACKAGE);
		//closeSeq.push_back(CloseElectionSteps::CONFIGURATION_GENERATECODIFILES);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_GENERATEPVREPORT);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_GENERATEALLRESULT);
		//closeSeq.push_back(CloseElectionSteps::CONFIGURATION_SIGNTRANSMISSIONPACKAGE);
		//closeSeq.push_back(CloseElectionSteps::CONFIGURATION_SIGNELECTIONRESOURCE);
        closeSeq.push_back(CloseElectionSteps::CONFIGURATION_CLOSEELECTION);
		closeSeq.push_back(CloseElectionSteps::CONFIGURATION_PRINTPV);		
		closeElectionconfig->setClosingElectionSteps(closeSeq);
		closeElectionconfig->setButtonConfiguration(*buttonBoxConfig);
		closeElectionconfig->setShowSignQuestion(false);
		closeElectionconfig->setShowSignConfirmation(false);
		closeElectionconfig->setContinueCloseOnSignFail(true);
		closeElectionconfig->setShowConfirmation(true);

		durationConf->setLeaveFieldsBlank(true);

		configSAESGUI->setDurationWidgetConfiguration(*durationConf);
		configSAESGUI->setCloseElectionFunctionalityConfiguration(*closeElectionconfig);


		//Activation consolidation functionality

		ScanConsolidationConfiguration scanConfiguration;

		ColorConfiguration scanBoxColorValid;
		scanBoxColorValid.setRed(0);
		scanBoxColorValid.setGreen(65535);
		scanBoxColorValid.setBlue(0);

		ColorConfiguration scanBoxColorBad;
		scanBoxColorBad.setRed(65535);
		scanBoxColorBad.setGreen(0);
		scanBoxColorBad.setBlue(0);

		ColorConfiguration scanBoxColorDuplicate;
		scanBoxColorDuplicate.setRed(65535);
		scanBoxColorDuplicate.setGreen(0);
		scanBoxColorDuplicate.setBlue(0);

		ColorConfiguration scanFontColorValid;
		scanFontColorValid.setRed(65535);
		scanFontColorValid.setGreen(65535);
		scanFontColorValid.setBlue(65535);

		ColorConfiguration scanFontColorBad;
		scanFontColorBad.setRed(0);
		scanFontColorBad.setGreen(0);
		scanFontColorBad.setBlue(0);

		ColorConfiguration scanFontColorDuplicate;
		scanFontColorDuplicate.setRed(0);
		scanFontColorDuplicate.setGreen(0);
		scanFontColorDuplicate.setBlue(0);

		XMLLabelConfiguration scanLabelConfiguration;
		scanLabelConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		scanLabelConfiguration.setLabel_VerticalPadding(1);
		scanLabelConfiguration.setLabel_HorizontalPadding(1);
		scanLabelConfiguration.setLabel_Family("Verdana");
		scanLabelConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		scanLabelConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		scanLabelConfiguration.setLabel_Size(16);

		ScanPopUpMessageConfiguration scanPopUpMessageConfiguration;
		PositionConfiguration positionConfiguration(PositionConfiguration::CONFIGURATION_BOTTOM_RIGHT);

		scanPopUpMessageConfiguration.setVisible(true);
		scanPopUpMessageConfiguration.setTimeOut(3000);
		scanPopUpMessageConfiguration.setOpacity(90);
		scanPopUpMessageConfiguration.setWidth(200);
		scanPopUpMessageConfiguration.setHeight(100);
		scanPopUpMessageConfiguration.setX(0);
		scanPopUpMessageConfiguration.setY(0);
		scanPopUpMessageConfiguration.setPosition(positionConfiguration);

		scanConfiguration.setScanPopUpMessageConfiguration(scanPopUpMessageConfiguration);
		scanConfiguration.setEnabledChangeColor(true);
		scanConfiguration.setBoxColorValid(scanBoxColorValid);
		scanConfiguration.setBoxColorDuplicate(scanBoxColorDuplicate);
		scanConfiguration.setBoxColorBad(scanBoxColorBad);
		scanConfiguration.setFontColorValid(scanFontColorValid);
		scanConfiguration.setFontColorDuplicate(scanFontColorDuplicate);
		scanConfiguration.setFontColorBad(scanFontColorBad);
		scanConfiguration.setTextConfiguration(scanLabelConfiguration);

		ActivationConsolidationFunctionalityConfiguration activationConsolidation;
		activationConsolidation.setTitleHeight(60);
		activationConsolidation.setStatsConsolidationHeight(150);
		activationConsolidation.setStatsActivationHeight(110);
		activationConsolidation.setActivateCardsWithoutBarcode(true);
		activationConsolidation.setConsolidateVoteWithOneMemory(false);
			ColorConfiguration acColor1(100, 30000, 30000);
		activationConsolidation.setSelectedBoxColor(acColor1);
			ColorConfiguration acColor2(65000, 65000, 65000);
		activationConsolidation.setUnselectedBoxColor(acColor2);
			ColorConfiguration acColor3(65000, 65000, 65000);
		activationConsolidation.setSelectedFontColor(acColor3);
			ColorConfiguration acColor4(10, 10, 10);
		activationConsolidation.setUnselectedFontColor(acColor4);
		activationConsolidation.setBarcodeInParams("LightsON");
		activationConsolidation.setBarcodeOutParams("LightsOFF");
		activationConsolidation.setShowTotalVotes(false);
		activationConsolidation.setShowOfficialVotes(true);
		activationConsolidation.setShowDuplicatesVotes(true);
		activationConsolidation.setShowScanMessage(true);
		activationConsolidation.setShowBarcodeMessage(true);
		activationConsolidation.setScanConsolidationConfiguration(scanConfiguration);
		activationConsolidation.setShowActivateCards(true);
		activationConsolidation.setTimerSleepWriteCard(10000);

		XMLLabelConfiguration labelsConfiguration;
			labelsConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			labelsConfiguration.setLabel_VerticalPadding(1);
			labelsConfiguration.setLabel_HorizontalPadding(1);
			labelsConfiguration.setLabel_Family("Verdana");
			labelsConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
			labelsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
			labelsConfiguration.setLabel_Size(13);
		activationConsolidation.setTitleFontConfiguration(labelsConfiguration);

			labelsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
			labelsConfiguration.setLabel_Size(13);
		activationConsolidation.setStatsConsolidationFontConfiguration(labelsConfiguration);
		activationConsolidation.setStatsActivationFontConfiguration(labelsConfiguration);

			labelsConfiguration.setLabel_Size(15);
		activationConsolidation.setInstructionFontConfiguration(labelsConfiguration);

			labelsConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
			labelsConfiguration.setLabel_Size(14);
		activationConsolidation.setDevicesLabelConfiguration(labelsConfiguration);

			labelsConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
			labelsConfiguration.setLabel_Size(15);
			labelsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
		activationConsolidation.setLabelSelectedConfiguration(labelsConfiguration);

			labelsConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		activationConsolidation.setLabelUnselectedConfiguration(labelsConfiguration);

		CountConfiguration cardActivationTotal;
		CountConfiguration::CountTypeSequence countTypeCardSeq;
		countTypeCardSeq.push_back(CountTypeConfig::CONFIGURATION_TOTAL);
		cardActivationTotal.setCountType(countTypeCardSeq);

		CountConfiguration cosolidationTotal;
		CountConfiguration::CountTypeSequence countTypeConsolidationSeq;
		countTypeConsolidationSeq.push_back(CountTypeConfig::CONFIGURATION_TOTAL);
		cosolidationTotal.setCountType(countTypeConsolidationSeq);

		CountConfiguration cosolidationOfficial;
		CountConfiguration::CountTypeSequence countTypeConsolidationOfficialSeq;
		countTypeConsolidationOfficialSeq.push_back(CountTypeConfig::CONFIGURATION_OFFICIAL);
		countTypeConsolidationOfficialSeq.push_back(CountTypeConfig::CONFIGURATION_RECOVERY);
		cosolidationOfficial.setCountType(countTypeConsolidationOfficialSeq);

		activationConsolidation.setCardActivationTotalCountConfiguration(cardActivationTotal);
		activationConsolidation.setConsolidationTotalCountConfiguration(cosolidationTotal);
		activationConsolidation.setConsolidationOfficialCountConfiguration(cosolidationOfficial);

		configSAESGUI->setActivationConsolidationFunctionalityConfiguration(activationConsolidation);

		//incident report functionality

		IncidentReportFunctionalityConfiguration::IncidentReportConfigurationSequence incidentSeq;

		IncidentReportTreeViewConfiguration incident1;
			TreeColumnConfiguration tree1(false, 250, 250, 0.5);
			incident1.setIncidentColumnConfiguration(tree1);
			incident1.setIncidentReportColumn(IncidentReportColumn::CONFIGURATION_DESCRIPTION);
			incidentSeq.push_back(incident1);

		IncidentReportTreeViewConfiguration incident2;
			TreeColumnConfiguration tree2(false, 180, 180, 0.5);
			incident2.setIncidentColumnConfiguration(tree2);
			incident2.setIncidentReportColumn(IncidentReportColumn::CONFIGURATION_NOTIFICATIONDATE);
			incidentSeq.push_back(incident2);

		IncidentReportTreeViewConfiguration incident3;
			TreeColumnConfiguration tree3(false, 200, 200, 0.5);
			incident3.setIncidentColumnConfiguration(tree3);
			incident3.setIncidentReportColumn(IncidentReportColumn::CONFIGURATION_NAMESOFTECHNICIANS);
			incidentSeq.push_back(incident3);
		
		IncidentReportTreeViewConfiguration incident4;
			TreeColumnConfiguration tree4(false, 180, 180, 0.5);
			incident4.setIncidentColumnConfiguration(tree4);
			incident4.setIncidentReportColumn(IncidentReportColumn::CONFIGURATION_COMPLETE);
			incidentSeq.push_back(incident4);

		IncidentReportFunctionalityConfiguration::CompleteReportParametersSequence reportCompleteSeq;
			reportCompleteSeq.push_back(IncidentReportColumn::CONFIGURATION_DESCRIPTION);
			reportCompleteSeq.push_back(IncidentReportColumn::CONFIGURATION_NOTIFICATIONDATE);
			reportCompleteSeq.push_back(IncidentReportColumn::CONFIGURATION_NAMESOFTECHNICIANS);
			reportCompleteSeq.push_back(IncidentReportColumn::CONFIGURATION_ACTIVITYOFTECHNICIANS);
			reportCompleteSeq.push_back(IncidentReportColumn::CONFIGURATION_PERSONALARRIVALDATE);
	
		incidentReportConfig->setCompleteReportParameters(reportCompleteSeq);
		incidentReportConfig->setIncidentReportConfiguration(incidentSeq);
		incidentReportConfig->setButtonConfiguration(*buttonBoxIncidentConfig);
		incidentReportConfig->setShowID(false);
		incidentReportConfig->setShowDeleteConfirmation(true);
		configSAESGUI->setIncidentReportFunctionalityConfiguration(*incidentReportConfig);

		//LogReport functionality
		logReportFunconfig.setPrinterMessageTimeout(4000);
		logReportFunconfig.setPageSize(10);
		configSAESGUI->setLogReportFunctionalityConfiguration(logReportFunconfig);
		
		//Close Note Register
		closeNoteFunConfig.setMinimunNotesToRegister(3);
		configSAESGUI->setCloseNotetFunctionalityConfiguration(closeNoteFunConfig);

		//poll worker functionality
		pollWorkerFunconfig->setButtonConfiguration(*buttonBoxPollConfig);
		pollWorkerFunconfig->setShowDeleteConfirmation(true);

		PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationSequence pollWorkerSeq;

		IDConfig idConfigPresident;
		idConfigPresident.setName(idPropertiesGeneric);
		idConfigPresident.setLastName(idPropertiesGeneric);

		IDProperties idPropertiesAccounPresident(true);
		idPropertiesAccounPresident.setType(ElementType::CONFIGURATION_CUSTOM);
		idPropertiesAccounPresident.setMax(80);
		idPropertiesAccounPresident.setMask("0123456789-");
		idConfigPresident.setAccount(idPropertiesAccounPresident);

		PollWorkerRegisterConfiguration pollWorkerPresident;
		pollWorkerPresident.setRegisterMax(1);
		pollWorkerPresident.setRegisterRequired(1);
		pollWorkerPresident.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_PRESIDENT);
		pollWorkerPresident.setIDConfig(idConfigPresident);

		IDConfig idConfigSecretary;
		idConfigSecretary.setName(idPropertiesGeneric);
		idConfigSecretary.setLastName(idPropertiesGeneric);

		PollWorkerRegisterConfiguration pollWorkerSecretary;
		pollWorkerSecretary.setRegisterMax(1);
		pollWorkerSecretary.setRegisterRequired(1);
		pollWorkerSecretary.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_SECRETARY);
		pollWorkerSecretary.setIDConfig(idConfigSecretary);

		IDConfig idConfigDeputySecretary;
		idConfigDeputySecretary.setName(idPropertiesGeneric);
		idConfigDeputySecretary.setLastName(idPropertiesGeneric);

		PollWorkerRegisterConfiguration pollWorkerDeputySecretary;
		pollWorkerDeputySecretary.setRegisterMax(1);
		pollWorkerDeputySecretary.setRegisterRequired(0);
		pollWorkerDeputySecretary.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY);
		pollWorkerDeputySecretary.setIDConfig(idConfigDeputySecretary);

		IDConfig idConfigAssistent;
		idConfigAssistent.setName(idPropertiesGeneric);
		idConfigAssistent.setLastName(idPropertiesGeneric);

		PollWorkerRegisterConfiguration pollWorkerAssistent;
		pollWorkerAssistent.setRegisterMax(5);
		pollWorkerAssistent.setRegisterRequired(0);
		pollWorkerAssistent.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_ASSISTENT);
		pollWorkerAssistent.setIDConfig(idConfigAssistent);

		IDConfig idConfigWitness;
		idConfigWitness.setName(idPropertiesGeneric);
		idConfigWitness.setLastName(idPropertiesGeneric);

		PollWorkerRegisterConfiguration pollWorkerWitness;
		pollWorkerWitness.setRegisterMax(5);
		pollWorkerWitness.setRegisterRequired(0);
		pollWorkerWitness.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_WITNESS);
		pollWorkerWitness.setIDConfig(idConfigWitness);

		IDConfig idConfigSubstitutePresident;
		idConfigSubstitutePresident.setName(idPropertiesGeneric);
		idConfigSubstitutePresident.setLastName(idPropertiesGeneric);

		PollWorkerRegisterConfiguration pollWorkerSubstitutePresident;
		pollWorkerSubstitutePresident.setRegisterMax(1);
		pollWorkerSubstitutePresident.setRegisterRequired(0);
		pollWorkerSubstitutePresident.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT);
		pollWorkerSubstitutePresident.setIDConfig(idConfigSubstitutePresident);

		IDConfig idConfigPolice;
		idConfigPolice.setName(idPropertiesGeneric);
		idConfigPolice.setLastName(idPropertiesGeneric);

		IDProperties idPropertiesConfigPolice(true);
		idPropertiesConfigPolice.setType(ElementType::CONFIGURATION_CUSTOM);
		idPropertiesConfigPolice.setMax(5);
		idPropertiesConfigPolice.setMask("0123456789:");
		idPropertiesConfigPolice.setRegex("^(20|21|22|23|[01][0-9]):[0-5][0-9]$");
		idConfigPolice.setAllDay(idPropertiesConfigPolice);

		PollWorkerRegisterConfiguration pollWorkerPolice;
		pollWorkerPolice.setRegisterMax(2);
		pollWorkerPolice.setRegisterRequired(0);
		pollWorkerPolice.setWorkerMemberType(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::POLLWORKERS_POLICE);
		pollWorkerPolice.setIDConfig(idConfigPolice);


		pollWorkerSeq.push_back(pollWorkerPresident);
		pollWorkerSeq.push_back(pollWorkerSecretary);
		pollWorkerSeq.push_back(pollWorkerDeputySecretary);
		pollWorkerSeq.push_back(pollWorkerAssistent);
		pollWorkerSeq.push_back(pollWorkerWitness);
		pollWorkerSeq.push_back(pollWorkerSubstitutePresident);
		pollWorkerSeq.push_back(pollWorkerPolice);

		RegisterWidgetConfiguration pollWorkerRegisterWidgetConfiguration;
		pollWorkerRegisterWidgetConfiguration.setVerticalFilling(false);
		pollWorkerRegisterWidgetConfiguration.setMaxColumn(3);
		pollWorkerRegisterWidgetConfiguration.setMaxRow(2);
		pollWorkerRegisterWidgetConfiguration.setHeigthBox(160);
		pollWorkerRegisterWidgetConfiguration.setWidthBox(315);
		pollWorkerRegisterWidgetConfiguration.setSpacingBox(10);
		pollWorkerRegisterWidgetConfiguration.setShowHeader(true);
		pollWorkerRegisterWidgetConfiguration.setShowCenter(true);
		pollWorkerRegisterWidgetConfiguration.setShowBottom(true);

		pollWorkerFunconfig->setRegisterWidgetConfiguration(pollWorkerRegisterWidgetConfiguration);
		pollWorkerFunconfig->setPollWorkerRegisterConfiguration(pollWorkerSeq);
		configSAESGUI->setPollWorkerRegisterFunctionalityConfiguration(*pollWorkerFunconfig);

		//vote consolidation functionality
		voteConsolidationFuncConfig->setUsePrintPreview(true);
		voteConsolidationFuncConfig->setUseVerticalTableInPreview(true);
		voteConsolidationFuncConfig->setCounterWidth(300);
		voteConsolidationFuncConfig->setCounterPadding(8);
		voteConsolidationFuncConfig->setShowVotingMachineCustomAttribute(true);
		voteConsolidationFuncConfig->setShowBarcodeInPreview(false);
		voteConsolidationFuncConfig->setConsolidateDemoVotes(true);
		voteConsolidationFuncConfig->setConsolidateSimulatedVotes(false);
		voteConsolidationFuncConfig->setAuditModeResources(false);
		voteConsolidationFuncConfig->setBarcodeInParams("LightsON");
		voteConsolidationFuncConfig->setBarcodeOutParams("LightsOFF");

		CountConfiguration consolidationTotalVC;
		CountConfiguration::CountTypeSequence consolidationSeqVC;
		consolidationSeqVC.push_back(CountTypeConfig::CONFIGURATION_TOTAL);
		consolidationTotalVC.setCountType(consolidationSeqVC);

		CountConfiguration cosolidationOfficialVC;
		CountConfiguration::CountTypeSequence countTypeConsolidationOfficialVCSeq;
		countTypeConsolidationOfficialVCSeq.push_back(CountTypeConfig::CONFIGURATION_OFFICIAL);
		countTypeConsolidationOfficialVCSeq.push_back(CountTypeConfig::CONFIGURATION_RECOVERY);
		cosolidationOfficialVC.setCountType(countTypeConsolidationOfficialVCSeq);

		voteConsolidationFuncConfig->setConsolidationTotalCountConfiguration(consolidationTotalVC);
		voteConsolidationFuncConfig->setConsolidationOfficialCountConfiguration(cosolidationOfficialVC);

		//Color Configuration
		ColorConfiguration statistiscVoteTitleColor;
		statistiscVoteTitleColor.setRed(65535);
		statistiscVoteTitleColor.setGreen(65535);
		statistiscVoteTitleColor.setBlue(65535);

		XMLLabelConfiguration voteStatisticsTitleLabelConf;
				voteStatisticsTitleLabelConf.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
				voteStatisticsTitleLabelConf.setLabel_VerticalPadding(1);
				voteStatisticsTitleLabelConf.setLabel_HorizontalPadding(1);
				voteStatisticsTitleLabelConf.setLabel_Family("Verdana");
				voteStatisticsTitleLabelConf.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
				voteStatisticsTitleLabelConf.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
				voteStatisticsTitleLabelConf.setLabel_Size(20);

		voteConsolidationFuncConfig->setStatisticsTitleColor(statistiscVoteTitleColor);
		voteConsolidationFuncConfig->setStatisticsTitleLabelConfiguration(voteStatisticsTitleLabelConf);
		configSAESGUI->setVoteConsolidationFunctionalityConfiguration(*voteConsolidationFuncConfig);

		printPreviewFuncConfig->setUsePrintPreview(true);
		printPreviewFuncConfig->setUseVerticalTableInPreview(true);
		printPreviewFuncConfig->setShowBarcodeInPreview(false);
		printPreviewFuncConfig->setBarcodeInParams("LightsON");
		printPreviewFuncConfig->setBarcodeOutParams("LightsOFF");

		configSAESGUI->setPrintPreviewFunctionalityConfiguration(*printPreviewFuncConfig);


		ButtonConfiguration screensButtonConf;
		screensButtonConf.setButtonWidth(350);
		screensButtonConf.setButtonHeight(100);
		screensButtonConf.setFontSize(16);


		//voting experience validation screens conf
		votingExperienceValidationScreensConf->setScreenOnlyFirstBallot(false);
		votingExperienceValidationScreensConf->setAutorun(true);
		votingExperienceValidationScreensConf->setTimeForStart(500);
		votingExperienceValidationScreensConf->setAutoclose(true);
		votingExperienceValidationScreensConf->setTimeForClose(5000);
		votingExperienceValidationScreensConf->setTimeToShow(500);
		votingExperienceValidationScreensConf->setTimeToHide(0);
		votingExperienceValidationScreensConf->setTimeAfterCapture(500);
		votingExperienceValidationScreensConf->setCaptureWholeScreen(true);
		votingExperienceValidationScreensConf->setPartySelImageFormatName("%1_%2-%4_%3_0000.png");
		votingExperienceValidationScreensConf->setOptionSelImageFormatName("%1_%2-%5_%3_%4.png");
		votingExperienceValidationScreensConf->setCustomAttrSelImageFormatName("%1_%2-%4_0_CA.png");
		votingExperienceValidationScreensConf->setCustomAttrConfImageFormatName("%ZZ1_%2-CAC-%3-%4.png");
		votingExperienceValidationScreensConf->setLanguageSelImageFormatName("ZZ_%1_%2-LS.png");
		votingExperienceValidationScreensConf->setLanguageSelImageFormatNameConfirmation("ZZ_%1_%2-LSC-%3.png");
		votingExperienceValidationScreensConf->setSuperNullImageFormatName("ZZ_%1_%2-SN.png");
		votingExperienceValidationScreensConf->setSuperNullImageFormatNameConfirmation("ZZ_%1_%2-SNC.png");
		votingExperienceValidationScreensConf->setPrintImageFormatName("ZZ_%1_%2-P.png");
		votingExperienceValidationScreensConf->setCardRemotionIndImageFormatName("ZZ_%1_%2-CRI.png");
		votingExperienceValidationScreensConf->setCardRemovedImageFormatName("ZZ_%1_%2-CR.png");
		votingExperienceValidationScreensConf->setFoldVoteImageFormatName("ZZ_%1_%2-FV.png");
		votingExperienceValidationScreensConf->setNullImageConfirmationFormatName("ZZ_%1_%2-NC.png");
		votingExperienceValidationScreensConf->setWelcomeScreenFormatName("ZZ_%1_%2-We.png");
		votingExperienceValidationScreensConf->setShowDialog(true);
		votingExperienceValidationScreensConf->setScreensButtonConf(screensButtonConf);
 		votingExperienceValidationScreensConf->setCheckImageFile(true);
 		votingExperienceValidationScreensConf->setShowFinalMessage(true);

		configSAESGUI->setVotingExperienceValidationScreensFunctionalityConfiguration(*votingExperienceValidationScreensConf);

		/// voting for disabled

		ButtonConfiguration addButtonConf;
		addButtonConf.setButtonWidth(320);
		addButtonConf.setButtonHeight(50);
		addButtonConf.setFontSize(12);

		ButtonConfiguration questionButtonConf;
		questionButtonConf.setButtonWidth(350);
		questionButtonConf.setButtonHeight(100);
		questionButtonConf.setFontSize(16);

		ButtonConfiguration addCancelButtonConf;
		addCancelButtonConf.setButtonWidth(220);
		addCancelButtonConf.setButtonHeight(50);
		addCancelButtonConf.setFontSize(12);

		XMLLabelConfiguration questionTitleConfiguration;
		questionTitleConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		questionTitleConfiguration.setLabel_VerticalPadding(1);
		questionTitleConfiguration.setLabel_HorizontalPadding(1);
		questionTitleConfiguration.setLabel_Family("Verdana");
		questionTitleConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		questionTitleConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
		questionTitleConfiguration.setLabel_Size(14);

		XMLLabelConfiguration infoTitleConfiguration;
		infoTitleConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		infoTitleConfiguration.setLabel_VerticalPadding(1);
		infoTitleConfiguration.setLabel_HorizontalPadding(1);
		infoTitleConfiguration.setLabel_Family("Verdana");
		infoTitleConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		infoTitleConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
		infoTitleConfiguration.setLabel_Size(14);

		XMLLabelConfiguration infoIDConfiguration;
		infoIDConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_LEFT);
		infoIDConfiguration.setLabel_VerticalPadding(1);
		infoIDConfiguration.setLabel_HorizontalPadding(1);
		infoIDConfiguration.setLabel_Family("Verdana");
		infoIDConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		infoIDConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		infoIDConfiguration.setLabel_Size(12);

		XMLLabelConfiguration infoTextConfiguration;
		infoTextConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		infoTextConfiguration.setLabel_VerticalPadding(1);
		infoTextConfiguration.setLabel_HorizontalPadding(1);
		infoTextConfiguration.setLabel_Family("Verdana");
		infoTextConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		infoTextConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		infoTextConfiguration.setLabel_Size(12);

		XMLLabelConfiguration infoErrorConfiguration;
		infoErrorConfiguration.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
		infoErrorConfiguration.setLabel_VerticalPadding(1);
		infoErrorConfiguration.setLabel_HorizontalPadding(1);
		infoErrorConfiguration.setLabel_Family("Verdana");
		infoErrorConfiguration.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
		infoErrorConfiguration.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
		infoErrorConfiguration.setLabel_Size(16);

		RegisterWidgetConfiguration votingForDisabledRegisterWidgetConfiguration;
		votingForDisabledRegisterWidgetConfiguration.setVerticalFilling(false);
		votingForDisabledRegisterWidgetConfiguration.setMaxColumn(3);
		votingForDisabledRegisterWidgetConfiguration.setMaxRow(2);
		votingForDisabledRegisterWidgetConfiguration.setHeigthBox(160);
		votingForDisabledRegisterWidgetConfiguration.setWidthBox(315);
		votingForDisabledRegisterWidgetConfiguration.setSpacingBox(10);
		votingForDisabledRegisterWidgetConfiguration.setShowHeader(true);
		votingForDisabledRegisterWidgetConfiguration.setShowCenter(true);
		votingForDisabledRegisterWidgetConfiguration.setShowBottom(false);

		VotingForDisabledFunctionalityConfiguration votingForDisabledFunctionality;
		votingForDisabledFunctionality.setAddButtonConf(addButtonConf);
		votingForDisabledFunctionality.setQuestionButtonConf(questionButtonConf);
		votingForDisabledFunctionality.setQuestionTitleConfiguration(questionTitleConfiguration);
		votingForDisabledFunctionality.setInfoTitleConfiguration(infoTitleConfiguration);
		votingForDisabledFunctionality.setInfoIDConfiguration(infoIDConfiguration);
		votingForDisabledFunctionality.setInfoTextConfiguration(infoTextConfiguration);
		votingForDisabledFunctionality.setInfoErrorConfiguration(infoErrorConfiguration);
		votingForDisabledFunctionality.setTimeOutInfoError(3000);
		votingForDisabledFunctionality.setAddCancelButtonConf(addCancelButtonConf);
		votingForDisabledFunctionality.setRegisterWidgetConfiguration(votingForDisabledRegisterWidgetConfiguration);
		votingForDisabledFunctionality.setCommentConfig(IDProperties(false));

		configSAESGUI->setVotingForDisabledFunctionalityConfiguration(votingForDisabledFunctionality);

		PoliceNoteRegisterFunctionalityConfiguration policeNoteRegisterFunctionalityConfiguration;
		policeNoteRegisterFunctionalityConfiguration.setAddButtonConf(addButtonConf);
		policeNoteRegisterFunctionalityConfiguration.setAddCancelButtonConf(addCancelButtonConf);
		policeNoteRegisterFunctionalityConfiguration.setRegisterWidgetConfiguration(votingForDisabledRegisterWidgetConfiguration);

		configSAESGUI->setPoliceNoteRegisterFunctionalityConfiguration(policeNoteRegisterFunctionalityConfiguration);

		DataUtilsValidatorFunctionalityConfiguration dataUtilsValidatorFunctionalityConfiguration;
		dataUtilsValidatorFunctionalityConfiguration.setKeyFile("votingDevices");
		dataUtilsValidatorFunctionalityConfiguration.setColumns(2);
		dataUtilsValidatorFunctionalityConfiguration.setWidth(350);
		dataUtilsValidatorFunctionalityConfiguration.setHeight(40);
		dataUtilsValidatorFunctionalityConfiguration.setSeparator("|");
		dataUtilsValidatorFunctionalityConfiguration.setPositionCode(0);
		dataUtilsValidatorFunctionalityConfiguration.setPositionPassword(4);

		configSAESGUI->setDataUtilsValidatorFunctionalityConfiguration(dataUtilsValidatorFunctionalityConfiguration);

		RegisterWidgetConfiguration closeNoteRegisterWidgetConfiguration;
		closeNoteRegisterWidgetConfiguration.setVerticalFilling(false);
		closeNoteRegisterWidgetConfiguration.setMaxColumn(3);
		closeNoteRegisterWidgetConfiguration.setMaxRow(2);
		closeNoteRegisterWidgetConfiguration.setHeigthBox(160);
		closeNoteRegisterWidgetConfiguration.setWidthBox(315);
		closeNoteRegisterWidgetConfiguration.setSpacingBox(10);
		closeNoteRegisterWidgetConfiguration.setShowHeader(true);
		closeNoteRegisterWidgetConfiguration.setShowCenter(true);
		closeNoteRegisterWidgetConfiguration.setShowBottom(true);

		ButtonConfiguration addCloseNoteButtonConf;
		addCloseNoteButtonConf.setButtonWidth(220);
		addCloseNoteButtonConf.setButtonHeight(50);
		addCloseNoteButtonConf.setFontSize(12);

		CloseNoteRegisterFunctionalityConfiguration closeNoteRegisterFunctionality;
		closeNoteRegisterFunctionality.setAddButtonConf(addCloseNoteButtonConf);
		closeNoteRegisterFunctionality.setAddCancelButtonConf(addCancelButtonConf);
		closeNoteRegisterFunctionality.setNextButtonConf(addCloseNoteButtonConf);
		closeNoteRegisterFunctionality.setRegisterWidgetConfiguration(closeNoteRegisterWidgetConfiguration);

		configSAESGUI->setCloseNoteRegisterFunctionalityConfiguration(closeNoteRegisterFunctionality);

		//themes configuration
		officialThemeConfiguration->setVotingWindowButton("VotingWindowButton");
		officialThemeConfiguration->setVotingExperiencePartyEventbox("votingexperiencepartyeventbox");
		officialThemeConfiguration->setVotingExperienceWindow("votingexperiencewindow");
		officialThemeConfiguration->setVotingExperienceBallotOptionEventbox("votingexperienceballotoptioneventbox");
		officialThemeConfiguration->setCardActivatorFunctionalityMessage("CardActivatorFunctionalityMessage");
		officialThemeConfiguration->setCardActivatorMessageEventbox("CardActivatorMessageEventBox");
		officialThemeConfiguration->setCardActivatorFunctionalityEventbox("cardActivatorFunctionalityEventBox");
		officialThemeConfiguration->setCardActivatorValuesEventbox("cardActivatorValuesEventBox");
		officialThemeConfiguration->setCardActivatorFunctionalityCenterFrame("CardActivatorFunctionalityCenterFrame");
		officialThemeConfiguration->setEventboxStepBarcode("eventboxStepBarcode");
		officialThemeConfiguration->setEventboxStepBarcodeTitle("eventboxStepBarcodeTitle");
		officialThemeConfiguration->setEventboxStepCardTitle("eventboxStepCardTitle");
		officialThemeConfiguration->setVoteDemoFunctionalityMessage("VoteDemoFunctionalityMessage");
		officialThemeConfiguration->setStandInLabelLabel("stand_in_label_label");
		officialThemeConfiguration->setStandInLabelEvent("stand_in_label_event");
		officialThemeConfiguration->setVotingExperienceSelectBallotOptionWidget("voting_experience_select_ballot_option_widget");
		officialThemeConfiguration->setChangeLanguageMessageWigdetEventbox("change_language_message_wigdet_event_box");
		officialThemeConfiguration->setCustomAttributeComboSelectionsWidgetTitle("CustomAttributeComboSelectionsWidgetTitle");
		officialThemeConfiguration->setCustomAttributeCounterWidgetTitle("CustomAttributeCounterWidgetTitle");
		officialThemeConfiguration->setEventboxChooseWidgetFrame("event_box_choose_widget_frame");
		officialThemeConfiguration->setVotingExperiencePartyWidget("voting_experience_party_widget");
		officialThemeConfiguration->setPartyWidgetEventbox("party_widget_event_box");
		officialThemeConfiguration->setEventboxImageStepInstallationWizard("EventBoxImageStepInstallationWizard");
		officialThemeConfiguration->setEventboxStepInstallationWizard("EventBoxStepInstallationWizard");
		officialThemeConfiguration->setParentKeypadEventbox("parentkeypadeventbox");
		officialThemeConfiguration->setInfoFrame("infoFrame");

		demoThemeConfiguration->setVotingWindowButtonDemo("VotingWindowButtonDemo");
		demoThemeConfiguration->setVotingExperiencePartyEventboxDemo("votingexperiencepartyeventboxDemo");
		demoThemeConfiguration->setVotingExperienceWindowDemo("votingexperiencewindowDemo");
		demoThemeConfiguration->setVotingExperienceBallotOptionEventboxDemo("votingexperienceballotoptioneventboxDemo");

		recoveryThemeConfiguration->setVotingWindowButtonRecovery("VotingWindowButtonRecovery");
		recoveryThemeConfiguration->setVotingExperiencePartyEventboxRecovery("votingexperiencepartyeventboxRecovery");
		recoveryThemeConfiguration->setVotingExperienceWindowRecovery("votingexperiencewindowRecovery");
		recoveryThemeConfiguration->setVotingExperienceBallotOptionEventboxRecovery("votingexperienceballotoptioneventboxRecovery");

		themesConfiguration->setOfficialThemeConfiguration(*officialThemeConfiguration);
		themesConfiguration->setDemoThemeConfiguration(*demoThemeConfiguration);
		themesConfiguration->setRecoveryThemeConfiguration(*recoveryThemeConfiguration);
		
		configSAESGUI->setThemesConfiguration(*themesConfiguration);
		configSAESGUI->setPollingCardConfiguration(pollingCardConfiguration);
		configSAESGUI->setAlarmBoxMonitorConfiguration(alarmBoxMonitorConfiguration);
		configSAESGUI->setIDCardProcessConfiguration(idCardProcessConfiguration);
		configSAESGUI->setBEIDCardWidgetConfiguration(beidCardWidgetConfiguration);

		StartConfiguration startConfig;
		startConfig.setLoadSelectionLanguage(false);
		startConfig.setPersistLanguage(false);
		startConfig.setInfoMachine(InfoMachineConfiguration::CONFIGURATION_PM);

		configSAESGUI->setStartConfiguration(startConfig);

		Smartmatic::ConfigurationTypes::NamespaceInfomap map;
#ifdef NAMESPACE_SAES_GUI_CONFIGURATION
        map[""].name = NAMESPACE_SAES_GUI_CONFIGURATION;
#endif
        map[""].schema = "";

		serializeSaesGUIConfiguration(ss,*configSAESGUI, map, "UTF-8");		
		ConfigurationPersistenceManager::Current().SetLibraryConfigFile("SAESGUI",ss.str());		
		
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{		
		std::cerr << "FATAL " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << e << std::endl;
		std::stringstream ss;
		ss << e;
		ZenityWrapper::showError("Config SAESGUI Error \n\n" + ss.str(), "Error");
		exit (0);
	}
	catch (...)
	{
		ZenityWrapper::showError("Config SAESGUI Error", "Error");
		exit (0);
	}

	delete(fillAssistedNameLabelConfiguration);
	delete(referendumConfiguration);
	delete(listElectionNotInitiated);
	delete(listElectionInitiated);
	delete(listElectionClosed);
	delete(listElectionResults);
	delete(formCommonControl);
	delete(votingWindowEndMessageLabelConfiguration);
	delete(funcConfiguration);
	delete(funcConfigSequence);
	delete(runFuncConfig);

	//delete(formTitles);
	//delete(emptyWindowTitle);
	delete(configSAESGUI);
	delete(durationConf);
	delete(installWizardConfig);
	delete(generalDiag);
	delete(cardActivators);
	delete(optionsCardActivators);
	delete(touchDiagConfig);
	delete(optionsMaintenance);
	delete(optionsValidations);
	delete(seqOptionsMaintenance);
	delete(seqOptionsValidations);
	delete(seqOptionsDiagnosis);
	delete(seqOptionsCardActivators);
	delete(languageSelectionConf);
	delete(seqLanguageButtonSequence);
	delete(buttonInfoEn);
	delete(buttonInfoNl);
	delete(openElection);
	delete(closeElection);
	delete(registerPresidentNotes);
	delete(logReport);
	delete(diagnosis);
	delete(voteProcessDemo);
	delete(alarmBoxDiagnosis);
	delete(changeHour);
	delete(cardGenerator);
	delete(assistedCardGenerator);
	delete(fillAssistedActivationInfo);
	delete(activationConsolidation);
	delete(recoveryCardGenerator);
	delete(smartcardReaderDiagnosis);
	delete(printerDiagnosis);
	delete(screaderDiagnosisConf);
	delete(printPreview);
	delete(incidentReport);
	delete(calibrationDiagnosis);
	delete(brightnessDiagnosis);
	delete(barcodeDiagnosis);
	delete(allDiagnosis);
	delete(flashDiagnosis);
	delete(optionsVotingMachine);
	delete(seqOptionsVotingMachine);
	delete(optionsRoot);
	delete(seqRoot);
	delete(rootPresidentMachineOption);
	delete(rootVotingMachineOption);
	delete(pollBookMachineConfiguration);
	delete(votingMachineConfiguration);	
	delete(votingExperienceConfiguration);
	delete(votingWindowConfiguration);
	delete(votingWindowFont);
	delete(partySelection);
	delete(partyWidget);
	delete(displayTypeImage);
	delete(ballotOptionSelection);
	delete(ballotOptionWidget);
	delete(displayTypeText);
	delete(ballotOptionFont);
	delete(selectedColor);
	delete(unSelectedColor);
	delete(recoveryCardConf);
	delete(assistedCardConf);
	delete(voteDemoConf);
	delete(activationCardConf);
	delete(selectedColorCardActiv);
	delete(unSelectedColorCardActiv);
	delete(printerDiagnosisConf);
	delete(barcodeDiagnosisConf);
	delete(brightnessDiagnosisConf);
	delete(allDiagnosisConf);
	delete(autoDiagnosisConf);
	delete(seqDiagnosticToApply);
	//delete(seqDiagnosticWithoutCalibration);	
	delete(seqAutoDiagnosticToApply);
	delete(waitingCardWindow);
	delete(diagnosisLabelConfiguration);
	delete(fillAssistedLabelConfiguration);
	delete(exitMessageLabelConfiguration);
	delete(vmInstallation);
	delete(selectionLanguageHeaderLabelConfiguration);
	delete(selectionLanguageBottomLabelConfiguration);
	delete(selectionLanguageConfirmationHeaderLabelConfiguration);
	delete(selectionLanguageConfirmationBottomLabelConfiguration);
	delete(selectionLanguageConfirmationCenterLabelConfiguration);
	delete(superWhiteHeaderLabelConfiguration);
	delete(superWhiteBottomLabelConfiguration);
	delete(superWhiteCenterLabelConfiguration);
	delete(superWhiteConfirmationHeaderLabelConfiguration);
	delete(superWhiteConfirmationBottomLabelConfiguration);
	delete(superWhiteConfirmationCenterLabelConfiguration);
	delete(contestWhiteSelectionHeaderLabelConfiguration);
	delete(contestWhiteSelectionBottomLabelConfiguration);
	delete(contestWhiteSelectionCenterLabelConfiguration);
	delete(welcomeContestCenterLabelConfiguration);
	delete(votingWidgetLabelChildLabelConfiguration);
	delete(votingWidgetTopChildLabelConfiguration);
	delete(votingWidgetBottomChildLabelConfiguration);	
	delete(votingWidgetNumberChildLabelConfiguration);
	delete(votingWidgetPartySelectionLabelChildLabelConfiguration);
	delete(statsConfiguration);
	delete(openElectionConfig);
	delete(closeElectionconfig);
	delete(incidentReportConfig);
	delete(pollWorkerFunconfig);
	delete(printPreviewFuncConfig);
	delete(voteConsolidationFuncConfig);
	delete(votingExperienceValidationScreensConf);
	delete(buttonBoxConfig);
	delete(buttonBoxIncidentConfig);
	delete(buttonBoxPollConfig);
	delete(pollWorkerRegister);
	delete(voteConsolidation);
	delete(closeVotation);
	delete(statisticsReport);
	delete(eventSounds);
	delete(loadingBallotsLabelConfiguration);
	delete(checkSumLabelConfiguration);
	delete(interrupVotingExperienceMessageLabelConfiguration);
	delete(interrupVotingExperienceCancelLabelConfiguration);
	delete(themesConfiguration);
	delete(officialThemeConfiguration);
	delete(demoThemeConfiguration);
	delete(recoveryThemeConfiguration);
	delete(closeVotationConfig);
	delete(initializationWindowConfiguration);

	if(functionalityWizardConfig)
		delete functionalityWizardConfig;
}

ChangeHourFunctionalityConfiguration SAESGUIConfigurationManager::GetChangeHourFunctionalitConfiguration()
{
	return (*configuration)->getChangeHourFunctionalityConfiguration();
}

ColorConfiguration SAESGUIConfigurationManager::getAssistedActivationPreviewTitleColor()
{
	return (*configuration)->getCardAssistedActivationFunctionalityConfiguration ().getPreviewTitlesColor();
}

ColorConfiguration SAESGUIConfigurationManager::getAssistedActivationPreviewContentColor()
{
	return (*configuration)->getCardAssistedActivationFunctionalityConfiguration ().getPreviewContentsColor();
}

ColorConfiguration SAESGUIConfigurationManager::getCardActivatorStatisticsTitleColor()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration ().getStatisticsTitleColor();
}
					
ColorConfiguration SAESGUIConfigurationManager::getCardRecoveryStatisticsTitleColor()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration ().getStatisticsTitleColor();
}

ColorConfiguration SAESGUIConfigurationManager::getVoteConsolidationStatisticsTitleColor()
{
	return (*configuration)->getVoteConsolidationFunctionalityConfiguration ().getStatisticsTitleColor();
}

bool SAESGUIConfigurationManager::getFunctionalityGoToAuthenticationOnExit(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	bool exitToAuth = false;
	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			exitToAuth = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityExitToAuthentication();
			break;
		}
	}
	return exitToAuth;
}

bool SAESGUIConfigurationManager::getChallengeIsEnable(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	bool exitToAuth = false;
	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			exitToAuth = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getChallengeIsEnable();
			break;
		}
	}
	return exitToAuth;
}

bool SAESGUIConfigurationManager::getIfChallengeIsRole(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	bool isRole = true;

	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			if((*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getChallengePasswordSource() == ChallengePasswordSourceEnum::CONFIGURATION_PRESIDENTPASSPHRASE)
				isRole = false;

			break;
		}
	}
	return isRole;
}

HelpConfiguration SAESGUIConfigurationManager::getHelpConfiguration(Smartmatic::Functionality::MenuOptionDescriptor menuType)
{
	HelpConfiguration config;
	config.setImageHelp("xx");
	config.setPdfHelp("yy");
	config.setTitleKey(" ");
	config.setUseHelp(false);

	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuType.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			if((*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getHelp())
			{
				config = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getHelp().get();
			}
			break;
		}
	}

	return config;
}

ElectionBlockStatusList::ElectionStatusSequence SAESGUIConfigurationManager::getDisableStateList(Smartmatic::Functionality::MenuOptionDescriptor menuType)
{
	ElectionBlockStatusList::ElectionStatusSequence seqStatus;
	seqStatus.clear();
	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuType.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			if((*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getElectionBlockStatus())
			{
				seqStatus = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getElectionBlockStatus().get().getElectionStatus();
			}
			break;
		}
	}
	return seqStatus;
}

NecessaryDevicesConfiguration::DeviceConfigurationSequence SAESGUIConfigurationManager::getDeviceConfiguration (Smartmatic::Functionality::MenuOptionDescriptor menuType)
{
	NecessaryDevicesConfiguration::DeviceConfigurationSequence seq;
	seq.clear();

	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuType.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			if((*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getNecessaryDevicesConfiguration() != NULL)
			{
				seq = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getNecessaryDevicesConfiguration().get().getDeviceConfiguration();
			}
			break;
		}
	}
	return seq;
}

Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum SAESGUIConfigurationManager::getChallengePasswordSource(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum exitToAuth = Smartmatic::SAES::Configuration::ChallengePasswordSourceEnum::CONFIGURATION_PRESIDENTPASSPHRASE;
	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			exitToAuth = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getChallengePasswordSource();
			break;
		}
	}
	return exitToAuth;
}

Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor SAESGUIConfigurationManager::getRunFunctionalityDescriptor()
{
	return ConvertMenuOptionType((*configuration)->getRunFunctionalityConfiguration().getFunctionalityDescriptor());
}
/*
CardReaderType::Value SAESGUIConfigurationManager::getCardReaderType()
{
	return (*configuration)->getSmartCardReaderDiagnosisConfiguration ().getCardReader();
}
*/
CardActivatorFunctionalityConfiguration* SAESGUIConfigurationManager::GetCardActivatorWidgetConfiguration()
{
	return &((*configuration)->getCardActivatorFunctionalityConfiguration());
}

int SAESGUIConfigurationManager::getTouchScreenCalibrationNumberOfPoints()
{
	return (*configuration)->getTouchScreenCalibrationConfiguration ().getNumberOfCalibrationPoints();
}

int SAESGUIConfigurationManager::getAllDiagnosisPrinterWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getPrinterDiagnosisWaitTime();
}

vector<LanguageButtonInfo> SAESGUIConfigurationManager::getLanguageList()
{
	std::vector<LanguageButtonInfo> listOfLanguages;
	xsd::cxx::tree::sequence<Smartmatic::SAES::Configuration::LanguageButton> languageList = (*configuration)->getLanguageSelectionWindowConfiguration ().getLanguageButton();
	for(unsigned int i= 0; i < languageList.size();i++)
	{
		LanguageButtonInfo buttonInfo(languageList[i].getLanguageCode(),languageList[i].getLanguageImageFile());
		listOfLanguages.push_back(buttonInfo);
	}
	return listOfLanguages;
}

unsigned int SAESGUIConfigurationManager::getSCReaderDiagnosisTimeout()
{
	return (*configuration)->getSmartCardReaderDiagnosisConfiguration().getTimeoutToFail();
}

int SAESGUIConfigurationManager::getAllDiagnosisBarcodeWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getBarcodeDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisSmartcardWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getSmartcardDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisCalibrationWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getCalibrationDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisContrastWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getContrastDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisAlarmWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getAlarmDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisFlashWaitTime()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getFlashDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAllDiagnosisPrinterWaitTimeOnOk()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getPrinterDiagnosisWaitTimeOnOk();
}

int SAESGUIConfigurationManager::getAllDiagnosisPrinterWaitTimeOnCancel()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getPrinterDiagnosisWaitTimeOnCancel();
}

int SAESGUIConfigurationManager::getAllDiagnosisCalibrationWaitTimeOnOk()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getCalibrationDiagnosisWaitTimeOnOk();
}

int SAESGUIConfigurationManager::getAllDiagnosisContrastWaitTimeOnOk()
{
	return (*configuration)->getAllDiagnosisConfiguration ().getContrastDiagnosisWaitTimeOnOk();
}

int SAESGUIConfigurationManager::getAutoDiagnosisPrinterWaitTime()
{
	return (*configuration)->getAutomaticWindowConfiguration().getPrinterDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAutoDiagnosisBarcodeWaitTime()
{
	return (*configuration)->getAutomaticWindowConfiguration().getBarcodeDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAutoDiagnosisSmartcardWaitTime()
{
	return (*configuration)->getAutomaticWindowConfiguration().getSmartcardDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAutoDiagnosisAlarmWaitTime()
{
	return (*configuration)->getAutomaticWindowConfiguration().getAlarmDiagnosisWaitTime();
}

int SAESGUIConfigurationManager::getAutoDiagnosisFlashWaitTime()
{
	return (*configuration)->getAutomaticWindowConfiguration().getFlashDiagnosisWaitTime();
}

std::string  SAESGUIConfigurationManager::getCustomAttributesPresentation()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getCustomAttributesPresentation();
}

bool SAESGUIConfigurationManager::getShowAudioCheckButton()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getShowAudioCheck();
}

PrinterDiagnosisConfiguration SAESGUIConfigurationManager::getPrinterDiagnosisConfiguration()
{
	return (*configuration)->getPrinterDiagnosisConfiguration();
}

bool SAESGUIConfigurationManager::getDoNotCheckBeforePrintDiagnostic()
{
	return (*configuration)->getPrinterDiagnosisConfiguration ().getDoNotCheckBeforePrintDiagnostic();
}

bool SAESGUIConfigurationManager::getGraphicalPrintForPresident()
{
	return (*configuration)->getPrinterDiagnosisConfiguration ().getPrintGraphicalForPresident();
}

bool SAESGUIConfigurationManager::getDurationLeaveFieldsBlank()
{
	return (*configuration)->getDurationWidgetConfiguration ().getLeaveFieldsBlank();
}

IncomePassphraseEnum SAESGUIConfigurationManager::getIncomePassphrase()
{
	return (*configuration)->getInstallationWizardConfiguration ().getIncomePassphrase();
}

PMWidgetConfiguration & SAESGUIConfigurationManager::getPMInstallationWidgetConfig()
{
	return (*configuration)->getPMWidgetConfiguration();
}

bool SAESGUIConfigurationManager::getAskForId()
{
	return (*configuration)->getInstallationWizardConfiguration ().getAskForId();
}

vector<DiagnosticType> SAESGUIConfigurationManager::getAllDiagnosisList()
{
	vector<DiagnosticType> diagnosisList;
	AllDiagnosisConfiguration::DiagnosticToApplySequence seq = (*configuration)->getAllDiagnosisConfiguration ().getDiagnosticToApply();
	for(unsigned int i = 0;i < seq.size();i++)
	{
		diagnosisList.push_back (seq[i]);
	}
	return diagnosisList;
}

/*vector<std::string> SAESGUIConfigurationManager::getAutoDiagnosisList()
{
	vector<std::string> diagnosisList;
	AllDiagnosisConfiguration::DiagnosticToApplySequence seq = (*configuration)->getAutomaticWindowConfiguration ().getDiagnosticToApply();
	for(unsigned int i = 0;i < seq.size();i++)
	{
		diagnosisList.push_back (seq[i]);
	}
	return diagnosisList;
}*/

Smartmatic::SAES::Configuration::AutomaticWindowConfiguration& SAESGUIConfigurationManager::GetAutomaticWindowConfiguration()
{
	return (*configuration)->getAutomaticWindowConfiguration ();
}

std::vector<Smartmatic::SAES::Configuration::DiagnosticType> SAESGUIConfigurationManager::getAutoDiagnosisList()
{
	std::vector<Smartmatic::SAES::Configuration::DiagnosticType> diagnosisList;
	std::vector<Smartmatic::SAES::Configuration::DiagnosticType>::iterator it;
	AllDiagnosisConfiguration::DiagnosticToApplySequence seq = (*configuration)->getAutomaticWindowConfiguration ().getDiagnosticToApply();

	for(unsigned int i = 0;i < seq.size();i++)
	{
		bool found = false;

		for (it = skipDiagnosis.begin();
			 it != skipDiagnosis.end();
			 it++)
		{
			if (seq[i].getDevice() == (*it).getDevice())
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			diagnosisList.push_back (seq[i]);
		}
	}

	return diagnosisList;
}

void SAESGUIConfigurationManager::addSkipAutoDiagnosis(Smartmatic::SAES::Configuration::DiagnosticType type)
{
	skipDiagnosis.push_back(type);
}

::Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration SAESGUIConfigurationManager::getCardActivationStatisticsConfiguration()
{
	return (*configuration)->getCardActivatorFunctionalityConfiguration().getCardStatisticsConfiguration();
}

::Smartmatic::SAES::Configuration::ActivatedCardStatisticsConfiguration SAESGUIConfigurationManager::getCardRecoveryStatisticsConfiguration()
{
	return (*configuration)->getCardRecoveryFunctionalityConfiguration().getCardStatisticsConfiguration();
}

WaitingForCardWindowConfiguration SAESGUIConfigurationManager::getWaitingForCardWindowConfiguration()
{
	return (*configuration)->getWaitingForCardWindowConfiguration();
}

VoteDemoFunctionalityConfiguration SAESGUIConfigurationManager::getVoteDemoFunctionalityConfiguration()
{
	return (*configuration)->getVoteDemoFunctionalityConfiguration();
}

BarcodeDiagnosisConfiguration SAESGUIConfigurationManager::getBarcodeDiagnosisConfiguration()
{
	return (*configuration)->getBarcodeDiagnosisConfiguration ();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCardActivatorStatisticsTitleLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getCardActivatorFunctionalityConfiguration ().getStatisticsTitleLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCardRecoveryStatisticsTitleLabelConfiguration()					 
{
	return ConvertToLabelConfiguration((*configuration)->getCardRecoveryFunctionalityConfiguration ().getStatisticsTitleLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetPreviewVoteLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getWaitingForCardWindowConfiguration ().getPreviewVoteLabelConfiguration());
}

Smartmatic::SAES::Configuration::ButtonConfiguration SAESGUIConfigurationManager::getPreviewVoteButtonConfiguration()
{
	return (*configuration)->getWaitingForCardWindowConfiguration ().getPreviewVoteButtonConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetVoteConsolidationStatisticsTitleLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVoteConsolidationFunctionalityConfiguration ().getStatisticsTitleLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCustomAtributtesWindowHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetCustomAtributtesWindowConfiguration().getHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCustomAtributtesWindowBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetCustomAtributtesWindowConfiguration().getBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCustomAtributtesWindowCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetCustomAtributtesWindowConfiguration().getCenterLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetConfirmationWindowBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetConfirmationWindowConfiguration().getHeaderLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetConfirmationWindowHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetConfirmationWindowConfiguration().getHeaderLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetDiagnosisLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getGeneralDiagnosisConfiguration().getDiagnosisLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::getDiagnosisFooterLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getGeneralDiagnosisConfiguration().getDiagnosisFooterLabelConfiguration());
}

bool SAESGUIConfigurationManager::getShowFooterInAutoDiagnosis()
{
	return (*configuration)->getAutomaticWindowConfiguration().getShowFooterInAutoDiagnosis();
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetContingencyTitleLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getContingencyCardWidgetConfiguration().getTitleFontConf());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetContingencyTextLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getContingencyCardWidgetConfiguration().getTextFontConf());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::getResultErrorLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getGeneralDiagnosisConfiguration().getResultErrorLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetFillAssistedInforConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getCardAssistedActivationFunctionalityConfiguration().getInstrunctionLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetNameLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getCardAssistedActivationFunctionalityConfiguration().getNameLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration  SAESGUIConfigurationManager::GetExitMessageLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getExitMessageLabelConfiguration());
}

Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior SAESGUIConfigurationManager::GetBlockMemoryBehaviorMenu()
{
	Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior behavior =
			Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Block;

	switch((*configuration)->getBlockMemoryBehaviorMenu())
	{
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_BLOCK:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Block;
		break;
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_ALLOW:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Allow;
		break;
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_SUSPEND:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Suspend;
		break;
	}

	return behavior;
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetPartySelectionWindowBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPartySelectionConfiguration().getBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetPartySelectionWindowHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPartySelectionConfiguration().getHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetBallotOptionSelectionWindowBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetBallotOptionSelectionConfiguration().getBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetBallotOptionSelectionWindowHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetBallotOptionSelectionConfiguration().getHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSelectionLanguageHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSelectionLanguageHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSelectionLanguageBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSelectionLanguageBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSelectionLanguageConfirmationHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSelectionLanguageConfirmationHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSelectionLanguageConfirmationBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSelectionLanguageConfirmationBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSelectionLanguageConfirmationCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSelectionLanguageConfirmationCenterLabelConfiguration());
};




Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetReportListTitleLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPrintingWidgetConfiguration ().getCompositeDescriptionLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetProgressLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPrintingWidgetConfiguration ().getReportListTitleLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCompositeMsgLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPrintingWidgetConfiguration ().getProgressMessageLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetFileItemLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetPrintingWidgetConfiguration ().getReportListItemLabelConfiguration());
};





Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteCenterLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteConfirmationHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteConfirmationHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteConfirmationBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteConfirmationBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetSuperWhiteConfirmationCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getSuperWhiteConfirmationCenterLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetContestWhiteSelectionHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getContestWhiteSelectionHeaderLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetContestWhiteSelectionBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getContestWhiteSelectionBottomLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetContestWhiteSelectionCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getContestWhiteSelectionCenterLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetWelcomeContestCenterLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getWelcomeContestCenterLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetLoadingBallotsLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getLoadingBallotsLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetCheckSumLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getCheckSumLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetTitleStatisticsLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetStatisticFunctionalityConfiguration().getTitleLabelConfiguration());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetStatsStatisticsLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetStatisticFunctionalityConfiguration().getStatisticsLabelConfiguration());
};


Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetInterrupVotingExperienceMessageLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getInterrupVotingExperienceMessageLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetInterrupVotingExperienceCancelLabelConfiguration()
{
	return ConvertToLabelConfiguration(GetVotingExperienceLabelConfiguration().getInterrupVotingExperienceCancelLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getAuthenticationPasswordLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getAuthenticationWindowConfiguration().getPasswordLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getAuthenticationAlarmLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getAuthenticationWindowConfiguration().getAlarmLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getAuthenticationInfoLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getAuthenticationWindowConfiguration().getInfoLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getAuthenticationVotingInfoLabelConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getAuthenticationWindowConfiguration().getVotingInfoLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWidgetLabelChildLabelConfiguration()
{

  return votingWidgetLabelChildLabelConfiguration;
}

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWidgetTopChildLabelConfiguration()
{
	return votingWidgetTopChildLabelConfiguration;
};

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWidgetBottomChildLabelConfiguration()
{
	return votingWidgetBottomChildLabelConfiguration;
};

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWidgetNumberChildLabelConfiguration()
{
	return votingWidgetNumberChildLabelConfiguration;
};

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetPartyNullLabelConfiguration()
{
	return partyNullLabelConfiguration;
}


Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWidgetPartySelectionLabelChildLabelConfiguration()
{
	return votingWidgetPartySelectionLabelChildLabelConfiguration;
};

Smartmatic::GUI::Configuration::LabelConfiguration& SAESGUIConfigurationManager::GetVotingWindowEndMessagelabelConfig()
{
        return votingWindowEndMessagelabelConfig;
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetVMLogingMessageLabel()
{
        return ConvertToLabelConfiguration(GetFormMessagesLabelsConfiguration().getVMLogingMessageLabel());
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetReferendumHeaderLabelConfiguration()
{
	return ConvertToLabelConfiguration(referendumConfiguration.getHeaderLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetReferendumBottomLabelConfiguration()
{
	return ConvertToLabelConfiguration(referendumConfiguration.getBottomLabelConfiguration());
}
Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetReferendumQuestionLabelConfiguration()
{
	return ConvertToLabelConfiguration(referendumConfiguration.getQuestionLabelConfiguration());
}
Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetReferendumBallotsLabelConfiguration()
{
	return ConvertToLabelConfiguration(referendumConfiguration.getBallotsLabelConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::ConvertToLabelConfiguration(XMLLabelConfiguration xmlLabelConfiguration)
{
	Smartmatic::GUI::Configuration::LabelConfiguration labelConfiguration;

	switch ( xmlLabelConfiguration.getLabel_Alignment() ) 
	{
		case Label_Alignment::CONFIGURATION_CENTER:
		{
			labelConfiguration.SetLabelAlignment(Smartmatic::GUI::Configuration::CenterAlignment);
		}   
        break;
		case Label_Alignment::CONFIGURATION_LEFT:
		{
			labelConfiguration.SetLabelAlignment(Smartmatic::GUI::Configuration::LeftAlignment);
		}   
        break;
		case Label_Alignment::CONFIGURATION_RIGHT:
		{
			labelConfiguration.SetLabelAlignment(Smartmatic::GUI::Configuration::RigthAlignment);
		}   
        break;
	}

	labelConfiguration.SetVerticalPadding(xmlLabelConfiguration.getLabel_VerticalPadding());
	labelConfiguration.SetHorizontalPadding(xmlLabelConfiguration.getLabel_HorizontalPadding());
	labelConfiguration.SetFontFamily(xmlLabelConfiguration.getLabel_Family());

	switch ( xmlLabelConfiguration.getLabel_Style()) 
	{
		case Label_Style::CONFIGURATION_NORMAL:
		{
			labelConfiguration.SetStyle(Smartmatic::GUI::Configuration::NormalStyle);
		}   
        break;
		case Label_Style::CONFIGURATION_OBLIQUE:
		{
			labelConfiguration.SetStyle(Smartmatic::GUI::Configuration::ObliqueStyle);
		}   
        break;
		case Label_Style::CONFIGURATION_ITALIC:
		{
			labelConfiguration.SetStyle(Smartmatic::GUI::Configuration::ItalicStyle);
		}   
        break;
	}

	switch (xmlLabelConfiguration.getLabel_Weight()) 
	{
		case Label_Weight::CONFIGURATION_LIGHT:
		{
			labelConfiguration.SetWeight(Smartmatic::GUI::Configuration::LightWeight);
		}   
        break;
		case Label_Weight::CONFIGURATION_NORMAL:
		{
			labelConfiguration.SetWeight(Smartmatic::GUI::Configuration::NormalWeight);
		}   
        break;
		case Label_Weight::CONFIGURATION_BOLD:
		{
			labelConfiguration.SetWeight(Smartmatic::GUI::Configuration::BoldWeight);
		}   
        break;
	}
	
	labelConfiguration.SetSize(xmlLabelConfiguration.getLabel_Size());

	return labelConfiguration;	
};

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetOpenElectionPollWorkerLabelConfiguration()
{
  return ConvertToLabelConfiguration(GetOpenElectionFunctionalityConfiguration().getDialogLabelConfiguration());
}


Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetEmptyWindowTitleFormConfiguration()
{
  return ConvertToLabelConfiguration(GetFormTitlesLabelsConfiguration().getEmptyWindowTitleLabel());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetUnableFunctionalityLabelConfiguration()
{
  return ConvertToLabelConfiguration(GetCommonControlsFormConfiguration().getUnableFunctionalityMessage());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::GetScanMessageLabelConfiguration()
{
  return ConvertToLabelConfiguration(GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getTextConfiguration());
}

int SAESGUIConfigurationManager::GetUnableMessageCloseTime()
{
  return GetCommonControlsFormConfiguration().getUnableMessageCloseTime();
}

int SAESGUIConfigurationManager::GetExitFunctionalityMessageCloseTime()
{
  return GetCommonControlsFormConfiguration().getExitFunctionalityMessageCloseTime();
}

Smartmatic::SAES::Configuration::FormsTitleLabelConfigurations& SAESGUIConfigurationManager::GetFormTitlesLabelsConfiguration()
{
  return GetCommonControlsFormConfiguration().getFormTitles();
}

::Smartmatic::SAES::Configuration::FormsMessagesLabelConfigurations& SAESGUIConfigurationManager::GetFormMessagesLabelsConfiguration()
{
  return GetCommonControlsFormConfiguration().getFormMesages();
}

::Smartmatic::SAES::Configuration::FormsCommonControlsConfigurations& SAESGUIConfigurationManager::GetCommonControlsFormConfiguration()
{
  return (*configuration)->getFormsCommonControls();
}

FormsCommonControlsConfigurations* SAESGUIConfigurationManager::CreateCommonControlsConfigurations()
{
  FormsCommonControlsConfigurations* formCommonCotrols = new FormsCommonControlsConfigurations();
  FormsTitleLabelConfigurations formTitles;
  FormsMessagesLabelConfigurations formMessages;

  ::Smartmatic::SAES::Configuration::XMLLabelConfiguration emptyWindowTitle;

  ::Smartmatic::SAES::Configuration::XMLLabelConfiguration VMInstallMessage;

  ::Smartmatic::SAES::Configuration::XMLLabelConfiguration UnableFunctionalityMessage;
  //emptyWindowTitle


  emptyWindowTitle.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
  emptyWindowTitle.setLabel_VerticalPadding(1);
  emptyWindowTitle.setLabel_HorizontalPadding(1);
  emptyWindowTitle.setLabel_Family("Verdana");
  emptyWindowTitle.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
  emptyWindowTitle.setLabel_Weight(Label_Weight::CONFIGURATION_BOLD);
  emptyWindowTitle.setLabel_Size(20);


  VMInstallMessage.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
  VMInstallMessage.setLabel_VerticalPadding(1);
  VMInstallMessage.setLabel_HorizontalPadding(1);
  VMInstallMessage.setLabel_Family("Verdana");
  VMInstallMessage.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
  VMInstallMessage.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
  VMInstallMessage.setLabel_Size(18);

  UnableFunctionalityMessage.setLabel_Alignment(Label_Alignment::CONFIGURATION_CENTER);
  UnableFunctionalityMessage.setLabel_VerticalPadding(1);
  UnableFunctionalityMessage.setLabel_HorizontalPadding(1);
  UnableFunctionalityMessage.setLabel_Family("Verdana");
  UnableFunctionalityMessage.setLabel_Style(Label_Style::CONFIGURATION_NORMAL);
  UnableFunctionalityMessage.setLabel_Weight(Label_Weight::CONFIGURATION_NORMAL);
  UnableFunctionalityMessage.setLabel_Size(30);


  formTitles.setEmptyWindowTitleLabel(emptyWindowTitle);
  formMessages.setVMLogingMessageLabel(VMInstallMessage);

  formCommonCotrols->setFormTitles(formTitles);
  formCommonCotrols->setFormMesages(formMessages);
  formCommonCotrols->setUnableFunctionalityMessage(UnableFunctionalityMessage);
  formCommonCotrols->setUnableMessageCloseTime(3000);
  formCommonCotrols->setExitFunctionalityMessageCloseTime(4000);

  return formCommonCotrols;
}

bool SAESGUIConfigurationManager::GetShowExitMessage(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			return (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getShowExitMessage();
		}
	}
	return false;
}

Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior SAESGUIConfigurationManager::GetBlockMemoryBehavior(Smartmatic::Functionality::MenuOptionDescriptor menuOptionDescriptor)
{
	Smartmatic::SAES::Configuration::MemoryBlock blockBehavior = Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_SUSPEND;

	for(unsigned int i = 0;i < (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration().size(); i++)
	{
		Glib::ustring str = menuOptionDescriptor.getMenuOption();
		MenuType::SaesMenuOptionType saesMenuOptionType = SaesMenuOptionDescriptor::getSaesMenuOptionType(str);

		if(ConvertSaesMenuOptionDescriptorType(saesMenuOptionType) == (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getFunctionalityDescriptor())
		{
			if((*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getBlockMemoryBehavior())
				blockBehavior = (*configuration)->getFunctionalitiesConfiguration().getFunctionalityConfiguration()[i].getBlockMemoryBehavior().get();
			break;
		}
	}

	Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior behavior =
			Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Block;

	switch(blockBehavior)
	{
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_BLOCK:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Block;
		break;
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_ALLOW:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Allow;
		break;
	case Smartmatic::SAES::Configuration::MemoryBlock::CONFIGURATION_SUSPEND:
		behavior = Smartmatic::SAES::Operation::MachineOperationManager::MemoryBehavior_Suspend;
		break;
	}

	return behavior;
}

SAESGUIConfigurationManager *SAESGUIConfigurationManager::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new SAESGUIConfigurationManager ();

	return singleton_instance;
}

std::string SAESGUIConfigurationManager::getPMInstalationSound()
{
	return(*configuration)->getEventSoundsConfiguration().getPMInstalationSound();
}

std::string SAESGUIConfigurationManager::getVMInstalationSound()
{
	return(*configuration)->getEventSoundsConfiguration().getVMInstalationSound();
}

std::string SAESGUIConfigurationManager::getAuthenticationValidPasswordSound()
{
	return(*configuration)->getEventSoundsConfiguration().getAuthenticationValidPasswordSound();
}

std::string SAESGUIConfigurationManager::getAuthenticationInvalidPasswordSound()
{
	return(*configuration)->getEventSoundsConfiguration().getAuthenticationInvalidPasswordSound();
}

std::string SAESGUIConfigurationManager::getVotingExperienceSound()
{
	return(*configuration)->getEventSoundsConfiguration().getVotingExperienceSound();
}

std::string SAESGUIConfigurationManager::getBallotOptionSelectSound()
{
	return(*configuration)->getEventSoundsConfiguration().getBallotOptionSelectSound();
}

std::string SAESGUIConfigurationManager::getPartySelectSound()
{
	return(*configuration)->getEventSoundsConfiguration().getPartySelectSound();
}

std::string SAESGUIConfigurationManager::getDiagnosisSound()
{
	return(*configuration)->getEventSoundsConfiguration().getDiagnosisSound();
}

ContingencyCardWidgetConfiguration SAESGUIConfigurationManager::getContingencyCardWidgetConfiguration ()
{
	return (*configuration)->getContingencyCardWidgetConfiguration ();
}

MemoryStateWidgetConfiguration & SAESGUIConfigurationManager::getMemoryStateWidgetConfiguration()
{
	return (*configuration)->getMemoryStateWidgetConfiguration();
}

HelpWidgetConfiguration & SAESGUIConfigurationManager::getHelpWidgetConfiguration()
{
	return (*configuration)->getHelpWidgetConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getMemoryStateWidgetTextConfiguration()
{
	return ConvertToLabelConfiguration(getMemoryStateWidgetConfiguration().getTextFontConf());
}

bool SAESGUIConfigurationManager::getCloseVotationRequestForId()
{
	return(*configuration)->getCloseVotationFunctionalityConfiguration().getRequestForID();
}

int SAESGUIConfigurationManager::getCloseVotationMinimumOfficialsActivationForConfirmation()
{
	return(*configuration)->getCloseVotationFunctionalityConfiguration().getMinimumOfficialsActivationForConfirmation();
}

bool SAESGUIConfigurationManager::getCloseVotationShowConfirmationMessageWhenClosing()
{
	return(*configuration)->getCloseVotationFunctionalityConfiguration().getShowConfirmationMessageWhenClosing();
}

bool SAESGUIConfigurationManager::getInitializationWindowRequestForId()
{
	return(*configuration)->getInitializationWindowConfiguration().getRequestForIDOnPresidentMachineInitialization();
}

PollingCardConfiguration & SAESGUIConfigurationManager::getPollingCardConfiguration()
{
	return(*configuration)->getPollingCardConfiguration();
}

AlarmBoxMonitorConfiguration & SAESGUIConfigurationManager::getAlarmBoxMonitorConfiguration()
{
	return(*configuration)->getAlarmBoxMonitorConfiguration();
}

StartConfiguration & SAESGUIConfigurationManager::getStartConfiguration()
{
	return(*configuration)->getStartConfiguration();
}

bool SAESGUIConfigurationManager::getContingencyCardEnabled ()
{
	return (*configuration)->getInitializationWindowConfiguration ().getContingencyCardEnabled ();
}

Smartmatic::SAES::Configuration::PivotConfig SAESGUIConfigurationManager::getPivotConfig(unsigned int principalCount)
{
	PivotConfig pivotConfig(1, ballotOptionSelectionConfiguration.getMaxColumns(), false);

	Smartmatic::SAES::Configuration::FillColumnDynamicConfiguration::PivotConfigSequence & seq (ballotOptionSelectionConfiguration.getFillColumnDynamic().getPivotConfig());
	Smartmatic::SAES::Configuration::FillColumnDynamicConfiguration::PivotConfigIterator it;

    std::map <unsigned int, PivotConfig> mapConfig;
    std::map <unsigned int, PivotConfig>::iterator mapIt;

    for (it = seq.begin();
         it != seq.end();
         it++)
    {
        mapConfig[(*it).getValue()] = (*it);
    }

	for (mapIt = mapConfig.begin();
		 mapIt != mapConfig.end();
		 mapIt++)
	{
		if ((*mapIt).first <= principalCount)
		{
			pivotConfig = (*mapIt).second;
		}
		else
		{
			break;
		}
	}

	return pivotConfig;
}

BEIDCardWidgetConfiguration & SAESGUIConfigurationManager::getBEIDCardWidgetConfiguration()
{
	return (*configuration)->getBEIDCardWidgetConfiguration();
}

IDCardProcessConfiguration & SAESGUIConfigurationManager::getIDCardProcessConfiguration()
{
	return (*configuration)->getIDCardProcessConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getBEIDCardWidgetTitleErrorConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getBEIDCardWidgetConfiguration().getTitleErrorFontConf());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getBEIDCardWidgetTextErrorConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getBEIDCardWidgetConfiguration().getTextErrorFontConf());
}

unsigned int SAESGUIConfigurationManager::getBEIDCardWidgetTimeoutError()
{
	return (*configuration)->getBEIDCardWidgetConfiguration().getTimeoutError();
}

bool SAESGUIConfigurationManager::checkPollworkerRegister()
{
	bool validate = true;

	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationSequence sepPollWorker = GetPollWorkerRegisterFunctionalityConfiguration().getPollWorkerRegisterConfiguration();
	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationIterator itp;

	for (itp = sepPollWorker.begin();
			itp != sepPollWorker.end();
			itp++)
	{
		unsigned int count = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getPollworkers()->getCount((*itp).getWorkerMemberType());
		unsigned int required = (*itp).getRegisterRequired();

		if (count < required)
		{
			validate = false;
			break;
		}
	}

	if( validate && Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->isNotPollworkerRegistered())
	{
		Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->registerPollworker();
	}

	return validate;
}

VotingForDisabledFunctionalityConfiguration & SAESGUIConfigurationManager::getVotingForDisabledFunctionalityConfiguration()
{
	return (*configuration)->getVotingForDisabledFunctionalityConfiguration();
}

PoliceNoteRegisterFunctionalityConfiguration & SAESGUIConfigurationManager::getPoliceNoteRegisterFunctionalityConfiguration()
{
	return (*configuration)->getPoliceNoteRegisterFunctionalityConfiguration();
}

DataUtilsValidatorFunctionalityConfiguration & SAESGUIConfigurationManager::getDataUtilsValidatorFunctionalityConfiguration()
{
	return (*configuration)->getDataUtilsValidatorFunctionalityConfiguration();
}

CloseNoteRegisterFunctionalityConfiguration & SAESGUIConfigurationManager::getCloseNoteRegisterFunctionalityConfiguration()
{
	return (*configuration)->getCloseNoteRegisterFunctionalityConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getVotingForDisabledQuestionTitleConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVotingForDisabledFunctionalityConfiguration().getQuestionTitleConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getVotingForDisabledInfoTitleConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVotingForDisabledFunctionalityConfiguration().getInfoTitleConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getVotingForDisabledInfoIDConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVotingForDisabledFunctionalityConfiguration().getInfoIDConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getVotingForDisabledInfoTextConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVotingForDisabledFunctionalityConfiguration().getInfoTextConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getVotingForDisabledInfoErrorConfiguration()
{
	return ConvertToLabelConfiguration((*configuration)->getVotingForDisabledFunctionalityConfiguration().getInfoErrorConfiguration());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getBlockDiagnosticTitle()
{
	return ConvertToLabelConfiguration((*configuration)->getAutomaticWindowConfiguration().getBlockDiagnosticTitle());
}

VotingExperienceConfiguration & SAESGUIConfigurationManager::getVotingExperienceConfiguration()
{
	return (*configuration)->getVotingExperience();
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getRemoveCardTitle()
{
	return ConvertToLabelConfiguration((*configuration)->getInitializationWindowConfiguration().getRemoveContingencyCardTitle());
}

Smartmatic::GUI::Configuration::LabelConfiguration SAESGUIConfigurationManager::getRemoveCardText()
{
	return ConvertToLabelConfiguration((*configuration)->getInitializationWindowConfiguration().getRemoveContingencyCardText());
}
