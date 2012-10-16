/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) Freddy 2011 <fgomez@smartmatic.com>
 * 
 * votesim is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * votesim is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>
#include <iostream>
#include <glibmm/timeval.h>

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "SimVoetWindow.h"
#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xsec/utils/XSECPlatformUtils.hpp>
#include <Environment/Configurations/base-language-controller.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <System/Runtime/ProcessMonitor.h>
#include <Runtime/Environment/MemoryPathController.h>
#include "config.h"
#include <Configuration/smartmatic-language-controller.h>
#include <Configuration/smartmaticgui-language-controller.h>
#include <Configuration/saes-language-controller.h>
#include <Configuration/saes-common-language-controller.h>
#include <Configuration/saes-functionality-language-controller.h>
#include <Configuration/saes-hardware-language-controller.h>
//#include <Configuration/saes-gui-language-controller.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
//#include <Operation/functionality-initiator.h>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/Initiator/VMachineInitiator.hxx>
#include <Operation/Initiator/CheckFilesPresence.hxx>
#include <Operation/Initiator/CheckDirectoryStructure.hxx>
#include <Operation/Authenticator/VMachineAuthenticator.hxx>

#include <Operation/Initiator/VMachineInitiator.hxx>
#include <Operation/Initiator/CheckFilesPresence.hxx>
#include <Operation/Initiator/CheckDirectoryStructure.hxx>
#include <Operation/Authenticator/VMachineAuthenticator.hxx>
#include <System/IO/Path.h>
#include <Operation/MachineOperationManager.hxx>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/safestack.h>
#include <System/OptParser.hxx>

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/cryptotest/ui/cryptotest.ui" */
#define UI_FILE "src/cryptotest.ui"

using namespace Smartmatic::Environment;
using namespace Smartmatic::System::Runtime;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
//using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
//using namespace Smartmatic::SAES::GUI::Windows;
//using namespace Smartmatic::SAES::GUI::Operation;
//using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System;
//using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
//using namespace Smartmatic::SAES::HW::Devices;


XERCES_CPP_NAMESPACE_USE

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String)
#else
#define _(String) (String)
#endif

int main (int argc, char *argv[])
{
	OptParser optparser(argc, argv, PACKAGE_NAME, VERSION, LOGDATADIR);

	  if(!Glib::thread_supported()) Glib::thread_init();

	  Gtk::Main kit(argc, argv);

	  setlocale (LC_ALL, "");

	  BaseLanguageController::LocalizeApplication("en", "US");
	  // No eliminar, esto activa el uso de las senales del sistema operativo
	  Smartmatic::SAES::Runtime::Environment::MemoryPathController::getInstance()->updatePaths();


	  std::cout << "PATH : " << Smartmatic::SAES::Runtime::Environment::MemoryPathController::getInstance()->getDomMemoryBasePath() << std::endl;

	  	  std::ios_base::sync_with_stdio(true);

	  	Glib::TimeVal time;
	  		time.assign_current_time();
	  		int seed = time.as_double();
	  		srand(seed);

	  	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");


		try
		{
			xercesc::XMLPlatformUtils::Initialize();
			#ifndef XSEC_NO_XALAN
				XalanTransformer::initialize();
			#endif
			XSECPlatformUtils::Initialise();
		}
		catch (const xercesc::XMLException &ex)
		{
			return 0;
		}

		SmartmaticLanguageController smartLang;
		smartLang.InitializeLanguage();
		SmartmaticGUILanguageController smartguiLang;
		smartguiLang.InitializeLanguage();
		SAESLanguageController saesLang;
		saesLang.InitializeLanguage();
		//SAESGUILanguageController saesguiLang;
		//saesguiLang.InitializeLanguage();
		SAESCommonLanguageController saescommonLang;
		saescommonLang.InitializeLanguage();
		SAESFunctionalityLanguageController saesfuncLang;
		saesfuncLang.InitializeLanguage();
		SAESHardwareLanguageController saeshwLang;
		saeshwLang.InitializeLanguage();


	  CRYPTO_malloc_init();
	    ERR_load_crypto_strings();
	    OPENSSL_add_all_algorithms_noconf();
	    OPENSSL_config(NULL);

	    Smartmatic::SAES::Operation::MachineOperationManager * machineOperationManager = Smartmatic::SAES::Operation::MachineOperationManager::getInstance();



	  try {
	        XMLPlatformUtils::Initialize();
	        XSECPlatformUtils::Initialise();
	    }
	    catch (const XMLException &e) {

	        std::cout << "Error during initialization of Xerces" << std::endl;
	        std::cout << "Error Message = : "
	            << e.getMessage() << std::endl;
	    }

	    /**********************************************************************/
	    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
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
	    		dirCondition = new Smartmatic::SAES::Operation::Initiator::CheckDirectoryStructure (&directories);
	    		Smartmatic::SAES::Operation::Initiator::CheckFilesPresence * filesCondition = NULL;
	    		filesCondition = new Smartmatic::SAES::Operation::Initiator::CheckFilesPresence (&directories);

	    		/**
	    		* @brief Setter electoral configuration and saes directories for voting widget manager
	    		*/
	    		//Smartmatic::SAES::GUI::Operation::Voting::VotingWidgetManager * votingWidgetManager = NULL;
	    		//votingWidgetManager = Smartmatic::SAES::GUI::Operation::Voting::VotingWidgetManager::getInstance();
	    		//votingWidgetManager->SetElectoralConfiguration(electoralConfiguration);
	    		//votingWidgetManager->SetSaesDirectories(&directories);

	    		std::list < Smartmatic::SAES::Operation::Initiator::ICheckCondition * > conditions;
	    		conditions.push_back(dirCondition);
	    		conditions.push_back(filesCondition);
	    		//conditions.push_back(votingWidgetManager);

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

	    		/**
	    		* @brief Setter Operation status for voting machine
	    		*/
	    		machineOperationManager->setOperationStatus(Smartmatic::SAES::Voting::OperationStatus::Current());
	    		Smartmatic::SAES::Voting::OperationStatus::Current()->LoadDefault();

	    		/**********************************************************************/

	    SimVoteWindow form;

	  Gtk::Main::run(form);

	  /***********************************************/
	  delete authenticator;
	  		delete initiator;
	  		delete electoralConfiguration;
	  		delete votingExperienceController;
	  		delete machineOperationManager;
	  		//if (votingWidgetManager) delete votingWidgetManager;
	  /*************************************************/
}
