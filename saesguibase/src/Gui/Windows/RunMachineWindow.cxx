/**
 * @file RunMachineWindow.cxx
 * @brief Body class run machine window
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#include "RunMachineWindow.hxx"
#include <Gui/Widgets/AbstractFactoryWidget.hxx>
#include <Gui/Widgets/FactoryMethodWidget.hxx>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Runtime/Environment/saes-directories.h>
#include "Functionalities/saes-functionality-manager.h"
#include <Operation/Alarm/AlarmBoxMonitor.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/IO/File.h>

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

using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Functionality;

ISMTTLog* RunMachineWindow::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Windows.RunMachineWindow",GETTEXT_PACKAGE);

RunMachineWindow::RunMachineWindow()
: EmptyWindow(NULL," ",false,false,false)
{
	this->installWidget = NULL;
	this->diagnosticWidget = NULL;
	this->initiatorWidget = NULL;
	this->idCardWidget = NULL;
	this->contingencyCardWidget = NULL;
	this->reportInstallWidget = NULL;
	this->authenticationWidget = NULL;
	this->runMachineWidget = NULL;
	this->menuWidget = NULL;
	this->helpWidget = NULL;
	this->step = 0;
	this->authenticationPosition = 0;
}

RunMachineWindow::~RunMachineWindow()
{
	remove();

	dispose();

	if (authenticationWidget)
	{
		delete authenticationWidget;
		authenticationWidget = NULL;
	}
	if (runMachineWidget)
	{
		delete runMachineWidget;
		runMachineWidget = NULL;
	}
	if (helpWidget)
	{
		delete helpWidget;
		helpWidget = NULL;
	}
	if (menuWidget)
	{
		delete menuWidget;
		menuWidget = NULL;
	}
}

void RunMachineWindow::dispose()
{
	if (installWidget)
	{
		delete installWidget;
		installWidget = NULL;
	}
	if (diagnosticWidget)
	{
		delete diagnosticWidget;
		diagnosticWidget = NULL;
	}
	if (initiatorWidget)
	{
		delete initiatorWidget;
		initiatorWidget = NULL;
	}
	if (idCardWidget)
	{
		delete idCardWidget;
		idCardWidget = NULL;
	}
	if (contingencyCardWidget)
	{
		delete contingencyCardWidget;
		contingencyCardWidget = NULL;
	}
	if (reportInstallWidget)
	{
		delete reportInstallWidget;
		reportInstallWidget = NULL;
	}
}

bool RunMachineWindow::start()
{
	return true;
}

void RunMachineWindow::pause()
{

}

void RunMachineWindow::stop()
{

}

void RunMachineWindow::install()
{
	logger->Debug("Show install machine");

	if (!installWidget)
	{
		installWidget = AbstractFactoryWidget::createInstallMachineWidget();
		installWidget->getSignalEnd().connect(sigc::mem_fun(*this, &RunMachineWindow::nextStep));
	}

	popPushStepWidget(installWidget);
}

void RunMachineWindow::diagnostic()
{
	if (!SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getSkipAutoDiagnostic())
	{
		logger->Debug("Run auto diagnostic");

		if (!diagnosticWidget)
		{
			diagnosticWidget = AbstractFactoryWidget::createAutomaticDiagnosticWidget();
			diagnosticWidget->getSignalEnd().connect(sigc::mem_fun(*this, &RunMachineWindow::nextStep));
		}

		popPushStepWidget(diagnosticWidget);
		diagnosticWidget->start();
	}
	else
	{
		logger->Debug("Skip auto diagnostic");
		nextStep();
	}
}

void RunMachineWindow::initialization()
{
	logger->Debug("Run initialization");

	if (!initiatorWidget)
	{
		initiatorWidget = AbstractFactoryWidget::createInitiatorWidget();
		initiatorWidget->getSignalEnd().connect(sigc::mem_fun(*this, &RunMachineWindow::nextStep));
	}

	popPushStepWidget(initiatorWidget);
	initiatorWidget->start();
}

void RunMachineWindow::reportInstall()
{
	if (SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration().getPrintInstallationReportPM() &&
		!MachineOperationManager::getInstance()->isPrintingInstallReport())
	{
		logger->Debug("Run install report");

		if(!reportInstallWidget)
		{
			reportInstallWidget = AbstractFactoryWidget::createReportInstallWidget();
			reportInstallWidget->getSignalEnd().connect(sigc::mem_fun(*this, &RunMachineWindow::nextStep));
		}

		popPushStepWidget(reportInstallWidget);
		reportInstallWidget->start();
	}
	else
	{
		logger->Debug("Skip install report");
		nextStep();
	}
}

void RunMachineWindow::contingencyCard()
{
	if (SAESGUIConfigurationManager::Current()->getContingencyCardEnabled () &&
			!MachineOperationManager::getInstance()->getOperationStatus()->getElectionStatusWrapper()->getContingencyCardCreated())
	{
		logger->Debug("Run create contingency card");

		if (!contingencyCardWidget)
		{
			contingencyCardWidget = AbstractFactoryWidget::createContingencyCardGenWidget();
			connContingency = contingencyCardWidget->card_generated_signal ().connect(sigc::mem_fun(*this, &RunMachineWindow::endContingency));
		}

		popPushStepWidget(contingencyCardWidget);
	}
	else
	{
		logger->Debug("Skip create contingency card");
		nextStep();
	}
}

void RunMachineWindow::idCardInstall()
{
	SaesDirectories saes;

	if (SAESGUIConfigurationManager::Current()->getInitializationWindowRequestForId() &&
	   !MachineOperationManager::getInstance()->getIDCardInfoWrapper()->isInstallPM())
	{
		logger->Debug("Run initialization window request for id");

		if (!idCardWidget)
		{
			idCardWidget = new IDCardWidgetPMInstall();
			connIdCard = idCardWidget->on_done_signal_emit().connect(sigc::mem_fun(*this, &RunMachineWindow::endIdCardInstall));
		}

		popPushStepWidget(idCardWidget);
		idCardWidget->initialize();
	}
	else
	{
		logger->Debug("Skip initialization window request for id");
		nextStep();
	}
}

void RunMachineWindow::endIdCardInstall()
{
	idCardWidget->dispose();
	connIdCard.disconnect();
	nextStep();
}

void RunMachineWindow::endContingency(ContingencyCardGenWidget::ContingencyErrorEnumType type)
{
	if (type == ContingencyCardGenWidget::CONTCARD_SUCCESS)
	{
		MachineOperationManager::getInstance()->saveElectoralConfigurationContingencyCardCreated();
	}

	contingencyCardWidget->dispose();
	connContingency.disconnect();
	nextStep();
}

void RunMachineWindow::process()
{
	logger->Debug("execute process");

	if (!authenticationWidget)
	{
		authenticationWidget = AbstractFactoryWidget::createAuthenticationWidget();
		authenticationWidget->getSignalRunMenu().connect(sigc::mem_fun(*this, &RunMachineWindow::runMenu));
		authenticationWidget->getSignalRunMachine().connect(sigc::mem_fun(*this, &RunMachineWindow::runMachine));
	}

	if (!runMachineWidget)
	{
		menuWidget = new MenuWidget();
		helpWidget = new HelpWidget();

		startHelpPrintConn = helpWidget->getSignalStartPrint().connect(sigc::mem_fun(*this, &BasicWindow::disableExitButton));
		stopHelpPrintConn = helpWidget->getSignalEndPrint().connect(sigc::mem_fun(*this, &BasicWindow::enableExitButton));

		runMachineWidget = FactoryMethodWidget::createRunMachineWidget(menuWidget, helpWidget);
		runMachineWidget->getSignalBlock().connect(sigc::mem_fun(*this, &RunMachineWindow::blockMachine));
		runMachineWidget->getSignalRunMenu().connect(sigc::mem_fun(*this, &RunMachineWindow::runMenu));

		menuWidget->setExit(true);

		SaesFunctionalityManager * menu_manager = SaesFunctionalityManager::Current();
		menu_manager->LockMachine().connect(sigc::mem_fun(this, &RunMachineWindow::blockMachine));
	}

	load();
}

void RunMachineWindow::load()
{
	dispose();

	popPushStepWidget(authenticationWidget);
	authenticationPosition = getCountStepWidget();

	start();
	runMachine();
}

void RunMachineWindow::blockMachine()
{
	runMachineWidget->dispose();

	int currentPos = getCountStepWidget();

	while (currentPos > authenticationPosition)
	{
		popStepWidget();
		currentPos = getCountStepWidget();
	}

	start();
	refreshStepWidget();
}

void RunMachineWindow::runMenu()
{
	stop();

	menuWidget->reloadMenu = true;
	pushStepWidget(menuWidget);
}

void RunMachineWindow::runMachine()
{
	start();
	pause();

	pushStepWidget(runMachineWidget);
	runMachineWidget->start();
}

void RunMachineWindow::end()
{
	logger->Debug("End window");
	dispose();
	QuitDialog();
}

void RunMachineWindow::nextStep()
{
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &RunMachineWindow::executeNextStep), 5);
}

void RunMachineWindow::executeNextStep()
{
	if (step < wizardStep.size())
	{
		switch (wizardStep[step])
		{
			case INSTALL_MACHINE:
				install();
				break;

			case AUTOMATIC_DIAGNOSTIC:
				diagnostic();
				break;

			case INITIATOR:
				initialization();
				break;

			case REPORT_INSTALL:
				reportInstall();
				break;

			case CONTINGENCY_CARD:
				contingencyCard();
				break;

			case ID_CARD_INSTALL:
				idCardInstall();
				break;

			case PROCESS:
				process();
				break;

			case END:
				end();
				break;
		}

		step++;
	}
}
