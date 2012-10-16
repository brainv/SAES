/*
 * Diagnostics.cxx
 *
 *  Created on: 23/08/2011
 *      Author: soto
 */

#include "Diagnostics.hxx"
#include <Voting/operation-status.h>
#include <Operation/functionality-initiator.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Functionalities/saes-functionality-manager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Windows/language-selection-window.h>
#include <Gui/Windows/menu-window.h>
#include <System/IO/File.h>
#include <System/Runtime/ProcessLauncher.h>

using namespace Smartmatic::SAES::Election;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Runtime;

void Diagnostics::start()
{
	LaunchConfiguration& launchConfig(SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());

	MachineOperationManager * machineOperationManager = MachineOperationManager::getInstance();
	machineOperationManager->setOperationStatus(OperationStatus::Current());
	machineOperationManager->getOperationStatus()->LoadDefaultVMStatus();
	machineOperationManager->getOperationStatus()->LoadDefaultElectionStatus();

	if(launchConfig.getExecutePMSetupInAppTypeDiagnostics())
	{
		if (!File::canOpenFile("/live/image/osconf/pmsetup"))
		{
			(void)ProcessLauncher::RunProcessThroughSystem(launchConfig.getPMSetupCommand().c_str());
			sleep(3);
		}
	}

	if(launchConfig.getExecuteInitialCalibrationInAppTypeVotingOnly())
	{
		int numberOfPoints = SAESGUIConfigurationManager::Current()->getTouchScreenCalibrationNumberOfPoints();
		std::string fullCommand = Glib::ustring::compose("gCal %1", numberOfPoints);

		(void)ProcessLauncher::RunProcessThroughSystem(fullCommand.c_str());
	}

	bool loadLanguage = SAESGUIConfigurationManager::Current()->getStartConfiguration().getLoadSelectionLanguage();
	bool persistLanguage = SAESGUIConfigurationManager::Current()->getStartConfiguration().getPersistLanguage();

	LanguageSelectionWindow langWindow;
	langWindow.setSaveFile(persistLanguage);

	if( !langWindow.loadDefaultLanguage() && loadLanguage )
	{
		langWindow.initialize();
		langWindow.ShowDialog();
	}

	FunctionalityInitiator::Register();

	MachineOperationManager::getInstance()->setElectoralConfiguration(NULL);

	MenuWindow menuWindow;
	menuWindow.ShowDialog();
}
