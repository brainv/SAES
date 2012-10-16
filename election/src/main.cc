/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
 * 
 * BelgiumVM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Election is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <gtkmm.h>
#include <Gui/Windows/PMWindow.hxx>
#include <Gui/Windows/VMWindow.hxx>
#include <Gui/Windows/empty-window.h>
#include <Gui/Windows/menu-window.h>
#include <Gui/Windows/initial-calib-window.h>
#include <Operation/functionality-initiator.h>
#include <Widgets/choose-dialog-button-info.h>
#include <Widgets/choose-dialog-info.h>
#include <Gui/Windows/choose-option-window.h>
#include <Configuration/s-a-e-s-hardware-conf-manager.h>
#include <Configuration/smartmatic-language-controller.h>
#include <Configuration/smartmaticgui-language-controller.h>
#include <Configuration/saes-language-controller.h>
#include <Configuration/saes-common-language-controller.h>
#include <Configuration/saes-functionality-language-controller.h>
#include <Configuration/saes-hardware-language-controller.h>
#include <Configuration/saes-gui-language-controller.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/Initiator/VMachineInitiator.hxx>
#include <Operation/Initiator/CheckFilesPresence.hxx>
#include <Operation/Initiator/CheckDirectoryStructure.hxx>
#include <Operation/Authenticator/VMachineAuthenticator.hxx>
#include <Operation/Initiator/PMachineInitiator.hxx>
#include <Operation/Authenticator/PMachineAuthenticator.hxx>
#include <Gui/Windows/language-selection-window.h>
#include <System/IO/File.h>
#include <Operation/Voting/VotingWidgetManager.hxx>
#include <Voting/PBReports/vote-statistics.h>
#include <eid/EIDManager.hxx>
#include <Log/SMTTLogManager.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xsec/utils/XSECPlatformUtils.hpp>
#include <Graphics/Image/Compose.hxx>
#include <log4cxx/DynamicPathRollingFileAppender.hxx>
#include <log4cxx/CryptoLayout.hxx>
#include <Log/LogBasePath.hxx>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <Log/LogCryptoPool.hxx>
#include <Devices/barcode-device.h>
#include <Windows/basic-window.h>
#include <Runtime/Environment/MemoryPathController.h>
#include <Devices/barcode-device.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <System/OptParser.hxx>
#include <Operation/Alarm/AlarmBoxMonitor.hxx>

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

#ifndef XSEC_NO_XALAN
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
XALAN_USING_XALAN( XalanTransformer)
#endif

using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace Smartmatic::GUI::Widgets;   
using namespace Smartmatic::GUI::Windows; 
using namespace Smartmatic::SAES::GUI::Windows; 
using namespace Smartmatic::SAES::GUI::Operation; 
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Operation::Alarm;

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "Config.hxx"
#include "RunFunctionality.hxx"
#include "Diagnostics.hxx"

using namespace Smartmatic::SAES::Election;

int main (int argc, char *argv[])
{
	struct sigaction sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = SIG_IGN;

	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGUSR2, &sact, NULL);

	if(!Glib::thread_supported())
	{
		Glib::thread_init();
	}

	Gtk::Main kit(argc, argv);

	bindtextdomain(GETTEXT_PACKAGE, GNOMELOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain (GNOMELOCALEDIR);
	setlocale (LC_ALL, "");

	OptParser optparser(argc, argv, PACKAGE_NAME, VERSION, CONFDIR/*optional*/);
    Config::start();

	ISMTTLog* logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Election",GETTEXT_PACKAGE);

	logger->Debug(_("Program name: ") + std::string(PACKAGE_NAME) );
	logger->Debug(_("Version: ") + std::string(VERSION) );

	/**
	* @brief Method operation machine manager for voting machine
	* @author Yadickson Soto <yadickson.soto@smartmatic.com>
	*/
	Smartmatic::SAES::Operation::MachineOperationManager * machineOperationManager = NULL;
	machineOperationManager = Smartmatic::SAES::Operation::MachineOperationManager::getInstance();
	machineOperationManager->StartDetection();

	/**
	* @brief Method selected language default
	* @author Juan Delgado <juan.delgado@smatmatic.com>, Yadickson Soto <yadickson.soto@smartmatic.com>
	*/
	Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories = NULL;
	directories = machineOperationManager->getSaesDirectories();

	LaunchConfiguration& launchConfig(SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());
	AppType apptoLaunch= launchConfig.getAppType();

	if (apptoLaunch != AppType::CONFIGURATION_DIAGNOSTICSONLY)
	{
		bool loadLanguage = SAESGUIConfigurationManager::Current()->getStartConfiguration().getLoadSelectionLanguage();
		bool persistLanguage = SAESGUIConfigurationManager::Current()->getStartConfiguration().getPersistLanguage();

		LanguageSelectionWindow langWindow;
		langWindow.setSaveFile(persistLanguage);

		if(loadLanguage && !langWindow.loadDefaultLanguage())
		{
			langWindow.initialize();
			langWindow.ShowDialog();
		}
	}

	/**
	 * Ask barcode model
	 */
	if(Smartmatic::SAES::HW::Devices::BarcodeDevice::Current()->Resync())
	{
		Smartmatic::SAES::HW::Devices::BarcodeDevice::Current()->GetDeviceModelOnThread();
	}

	if(apptoLaunch == AppType::CONFIGURATION_VOTINGONLY)
	{
		logger->Debug(_("Running MV"));

		SAESGUIConfigurationManager::Current()->getStartConfiguration().setInfoMachine (InfoMachineConfiguration::CONFIGURATION_VM);

		/**
		* @brief Method setter electoral configuration for voting machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration = NULL;
		electoralConfiguration = machineOperationManager->getElectoralConfiguration();

		/**
		* @brief Method setter initiator for voting machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Initiator::VMachineInitiator * initiator = NULL;
		initiator = new Smartmatic::SAES::Operation::Initiator::VMachineInitiator();
		machineOperationManager->setMachineInitiator( initiator );

		Smartmatic::SAES::Operation::Initiator::CheckDirectoryStructure * dirCondition = NULL;
		dirCondition = new Smartmatic::SAES::Operation::Initiator::CheckDirectoryStructure (directories);
		Smartmatic::SAES::Operation::Initiator::CheckFilesPresence * filesCondition = NULL;
		filesCondition = new Smartmatic::SAES::Operation::Initiator::CheckFilesPresence (directories);

		/**
		* @brief Setter electoral configuration and saes directories for voting widget manager
		*/
		Smartmatic::SAES::GUI::Operation::Voting::VotingWidgetManager * votingWidgetManager = NULL;
		votingWidgetManager = Smartmatic::SAES::GUI::Operation::Voting::VotingWidgetManager::getInstance();
		votingWidgetManager->SetElectoralConfiguration(electoralConfiguration);
		votingWidgetManager->SetSaesDirectories(directories);

		std::list < Smartmatic::SAES::Operation::Initiator::ICheckCondition * > conditions;
		conditions.push_back(dirCondition);
		conditions.push_back(filesCondition);
		conditions.push_back(votingWidgetManager);

		initiator->init (conditions, electoralConfiguration);

		/**
		* @brief Method setter authenticator for voting machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Authenticator::VMachineAuthenticator * authenticator = NULL;
		authenticator = new Smartmatic::SAES::Operation::Authenticator::VMachineAuthenticator();
		authenticator->init( electoralConfiguration );
		machineOperationManager->setAuthenticator( authenticator );

		/**
		* @brief Method setter voting expirience controller for voting machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController = NULL;
		votingExperienceController = new Smartmatic::SAES::Operation::Voting::VotingExperienceController ( electoralConfiguration );
		machineOperationManager->setVotingExperienceController( votingExperienceController );

		Smartmatic::SAES::Voting::PBReports::StatisticManager * statisticManager = NULL;
		statisticManager = new Smartmatic::SAES::Voting::PBReports::StatisticManager ();
		machineOperationManager->setStatisticManager( statisticManager );

		/**
		* @brief Setter Operation status for voting machine
		*/
		machineOperationManager->setOperationStatus(Smartmatic::SAES::Voting::OperationStatus::Current());

		Smartmatic::SAES::Voting::OperationStatus::Current()->LoadDefault();

		/********************************************************************************************/

		bool showDiagnostic = false;

		if(!launchConfig.getSkipAutoDiagnostic())
		{
			if(launchConfig.getExecuteInitialCalibrationInAppTypeVotingOnly())
			{
				if (!Smartmatic::System::IO::File::canOpenFile("/live/image/osconf/penmount.dat"))
				{
					showDiagnostic = true;
					DiagnosticType type (DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION, false);
					SAESGUIConfigurationManager::Current()->addSkipAutoDiagnosis(type);
				}
			}
		}

		if(showDiagnostic)
		{
			InitialCalibWindow calibWindow;
			calibWindow.ShowDialog();
		}

		AlarmBoxMonitor::getInstance()->check();

		VMWindow * vmWindow = new VMWindow();
		vmWindow->ShowDialog();

		delete vmWindow;
		delete authenticator;
		delete initiator;
		delete electoralConfiguration;
		delete votingExperienceController;
		delete machineOperationManager;
		if (votingWidgetManager) delete votingWidgetManager;
	}

	else if(apptoLaunch == AppType::CONFIGURATION_POLLBOOKONLY)
	{
		logger->Debug(_("Running PM"));

		SAESGUIConfigurationManager::Current()->getStartConfiguration().setInfoMachine (InfoMachineConfiguration::CONFIGURATION_PM);

		Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration = NULL;
		electoralConfiguration = machineOperationManager->getElectoralConfiguration();

		Smartmatic::SAES::Common::Configuration::BasePathType type =
				Smartmatic::SAES::Voting::VotingCenters::VotingCentersWrapper::getInstance()->getMasterDevice();

		Smartmatic::SAES::Voting::PBReports::PollworkersWrapper * pollworkers = NULL;
		pollworkers = new Smartmatic::SAES::Voting::PBReports::PollworkersWrapper ();
		machineOperationManager->setPollworkers( pollworkers );

		Smartmatic::SAES::Voting::PBReports::StatisticManager * statisticManager = NULL;
		statisticManager = new Smartmatic::SAES::Voting::PBReports::StatisticManager ();
		machineOperationManager->setStatisticManager( statisticManager );

		Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper *activatedCardStatistics = NULL;
		activatedCardStatistics = new Smartmatic::SAES::Voting::PBReports::ActivatedCardStatisticsWrapper();
		machineOperationManager->setActivatedCardStatistics( activatedCardStatistics );

		Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper * incidentReport = NULL;
		incidentReport = new Smartmatic::SAES::Voting::PBReports::IncidentReportWrapper ();
		machineOperationManager->setIncidentReport( incidentReport );

		Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper * assistedActivation = NULL;
		assistedActivation = new Smartmatic::SAES::Voting::PBReports::AssistedActivationWrapper ();
		machineOperationManager->setAssistedActivation( assistedActivation );

		Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper * closingNotes = NULL;
		closingNotes = new Smartmatic::SAES::Voting::PBReports::ClosingNotesWrapper ();
		machineOperationManager->setClosingNotes( closingNotes );

		machineOperationManager->setOperationStatus(Smartmatic::SAES::Voting::OperationStatus::Current());

		Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper * voteStatistics = NULL;
		voteStatistics = new Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper();

		machineOperationManager->setVoteStatistics(voteStatistics);
		machineOperationManager->SetBlockMemoryBehavior(SAESGUIConfigurationManager::Current()->GetBlockMemoryBehaviorMenu());

		/**
		* @brief Method setter initiator for president machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Initiator::PMachineInitiator * initiator = NULL;
		initiator = new Smartmatic::SAES::Operation::Initiator::PMachineInitiator();
		machineOperationManager->setMachineInitiator( initiator );

		Smartmatic::SAES::Operation::Initiator::CheckDirectoryStructure * dirCondition = NULL;
		dirCondition = new Smartmatic::SAES::Operation::Initiator::CheckDirectoryStructure (directories, type);
		Smartmatic::SAES::Operation::Initiator::CheckFilesPresence * filesCondition = NULL;
		filesCondition = new Smartmatic::SAES::Operation::Initiator::CheckFilesPresence (directories, type);

		std::list < Smartmatic::SAES::Operation::Initiator::ICheckCondition * > conditions;
		conditions.push_back(dirCondition);
		conditions.push_back(filesCondition);

		initiator->init (conditions, electoralConfiguration);

		/**
		* @brief Method setter authenticator for president machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Authenticator::PMachineAuthenticator * authenticator = NULL;
		authenticator = new Smartmatic::SAES::Operation::Authenticator::PMachineAuthenticator();
		authenticator->init( electoralConfiguration );
		machineOperationManager->setAuthenticator( authenticator );

		/**
		* @brief Method setter voting expirience controller for president machine
		* @author Yadickson Soto <yadickson.soto@smartmatic.com>
		*/

		Smartmatic::SAES::Operation::Voting::VotingExperienceController * votingExperienceController = NULL;
		votingExperienceController = new Smartmatic::SAES::Operation::Voting::VotingExperienceController ( electoralConfiguration );
		machineOperationManager->setVotingExperienceController( votingExperienceController );

		/********************************************************************************************/
		Smartmatic::SAES::Voting::OperationStatus::Current()->LoadDefault();

		PMWindow * pmWindow = new PMWindow();
		pmWindow->ShowDialog();

		delete pmWindow;
		delete voteStatistics;
		delete authenticator;
		delete initiator;
		delete electoralConfiguration;
		delete votingExperienceController;
		delete machineOperationManager;
	}

	else if(apptoLaunch == AppType::CONFIGURATION_DIAGNOSTICSONLY)
	{
		logger->Debug(_("Running Diagnostic"));
		Diagnostics::start();
	}
	else if(apptoLaunch == AppType::CONFIGURATION_RUNFUNCTIONALITY)
	{
		logger->Debug(_("Running functionality"));
		RunFunctionality::start();
	}
	else
	{
		logger->Debug(_("App Mode not supported"));
	}

	Smartmatic::SAES::EID::EIDManager::release();

	return 0;
}
