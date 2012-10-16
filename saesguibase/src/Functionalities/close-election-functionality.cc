/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "close-election-functionality.h"
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Gui/Widgets/AbstractFactoryWidget.hxx"

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
using namespace Gtk;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;

CloseElectionFunctionality* CloseElectionFunctionality::current_instance = NULL;

Smartmatic::Log::ISMTTLog* CloseElectionFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality",GETTEXT_PACKAGE);

CloseElectionFunctionality* CloseElectionFunctionality::Current()
{
	if (!current_instance)
		current_instance = new CloseElectionFunctionality();

	return current_instance;
};

CloseElectionFunctionality::CloseElectionFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	persistPackage = NULL;
	persistCodiFilesWidget = NULL;
	persistAllResultWidget = NULL;
	signPackage = NULL;
	closeStatus = NULL;
	printWidget = NULL;
	generatePVReport = NULL;
	noteRegisterWidget = NULL;
	statCounterWidget = NULL;
	durationWidget = NULL;
	signElection = NULL;
	closeConfirmation = NULL;
	questionAlign = NULL;
	manager = NULL;
	idCardWidget = NULL;
	closeFrame = NULL;
}

CloseElectionFunctionality::~CloseElectionFunctionality()
{
	deleteElement();
}

void CloseElectionFunctionality::deleteElement()
{
	if (persistPackage)
	{
		delete persistPackage;
		persistPackage = NULL;
	}
	if (persistCodiFilesWidget)
	{
		delete persistCodiFilesWidget;
		persistCodiFilesWidget = NULL;
	}
	if (persistAllResultWidget)
	{
		delete persistAllResultWidget;
		persistAllResultWidget = NULL;
	}
	if (signPackage)
	{
		delete signPackage;
		signPackage = NULL;
	}
	if (closeStatus)
	{
		delete closeStatus;
		closeStatus = NULL;
	}
	if (printWidget)
	{
		delete printWidget;
		printWidget = NULL;
	}
	if (generatePVReport)
	{
		delete generatePVReport;
		generatePVReport = NULL;
	}
	if (noteRegisterWidget)
	{
		delete noteRegisterWidget;
		noteRegisterWidget = NULL;
	}
	if (statCounterWidget)
	{
		delete statCounterWidget;
		statCounterWidget = NULL;
	}
	if (durationWidget)
	{
		delete durationWidget;
		durationWidget = NULL;
	}
	if (signElection)
	{
		delete signElection;
		signElection = NULL;
	}
	if (closeConfirmation)
	{
		delete closeConfirmation;
		closeConfirmation = NULL;
	}
	if (questionAlign)
	{
		delete questionAlign;
		questionAlign = NULL;
	}
	if (manager)
	{
		delete manager;
		manager = NULL;
	}
	if (idCardWidget)
	{
		delete idCardWidget;
		idCardWidget = NULL;
	}
	if (closeFrame)
	{
		delete closeFrame;
		closeFrame = NULL;
	}
}

void CloseElectionFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.VotationWasNotClose"));
	enableExitButton();

	if(manager)
	{
		manager->Start();
	}
};

bool CloseElectionFunctionality::checkIfCanCloseByDate()
{
	bool validate = false;

	try
	{
		Smartmatic::SAES::Voting::VotingDevice::Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
		std::string dateClose = vd.getOperation_modes().getOperation_mode()[0].getClosing_date_time ();
		Glib::TimeVal timeValClose;
		bool checkDates = timeValClose.assign_from_iso8601 (dateClose);
		Glib::TimeVal timeValNow;

		timeValNow.assign_current_time ();

		if(timeValNow > timeValClose || checkDates == false)
		{
			validate = true;
		}
	}
	catch(...)
	{
		//TODO handle exception
	}

	return validate;
}

void CloseElectionFunctionality::on_close_clicked()
{
	try
	{
		MachineOperationManager::getInstance()->closeElection();
	}
	catch(Smartmatic::System::Exception::CryptoException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorClosingElection"));
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorClosingElection"));
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorClosingElection"));
	}
	catch(...)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorClosingElection"));
	}
	
	ExitFunctionality();
}

void CloseElectionFunctionality::LoadWizardFrame()
{
	CloseElectionFunctionalityConfiguration::ClosingElectionStepsSequence  seq =
				SAESGUIConfigurationManager::Current()->GetCloseElectionFunctionalityConfiguration().getClosingElectionSteps();

	Smartmatic::SAES::Configuration::CloseElectionFunctionalityConfiguration::ClosingElectionStepsIterator iter;
	countGeneratePV = -1;
	countGenerateAllResult = -1;

	for(iter = seq.begin(); iter != seq.end(); iter++)
	{
		switch(*iter)
		{
			case CloseElectionSteps::CONFIGURATION_CLOSECONFIRMATION:
				closeConfirmation = new CloseElectionConfirmationWidget();
				closeConfirmation->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::on_cancelButton_clicked));
				closeConfirmation->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(closeConfirmation);
				break;
			case CloseElectionSteps::CONFIGURATION_REQUESTIDCARD:
				idCardWidget = new IDCardWidgetCloseElection();
				idCardWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				idCardWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(idCardWidget);
				break;
/*			case CloseElectionSteps::CONFIGURATION_GENERATETRANSMISSIONPACKAGE:
				persistPackage = AbstractFactoryWidget::createPersistTransmissionPackageWidget();
				persistPackage->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				persistPackage->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(persistPackage);
				break;*/
			case CloseElectionSteps::CONFIGURATION_SIGNTRANSMISSIONPACKAGE:
				signPackage = AbstractFactoryWidget::createSignTransmissionPackageWidget();
				signPackage->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				signPackage->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(signPackage);
				break;
			case CloseElectionSteps::CONFIGURATION_CLOSEELECTION:
				closeStatus = AbstractFactoryWidget::createCloseElectionStatusWidget();
				closeStatus->on_done_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ElectionWasClosed));
				closeStatus->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				closeStatus->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(closeStatus);
				break;
			case CloseElectionSteps::CONFIGURATION_PRINTPV:
				printWidget = new ReportPrintingCloseWidget();
				printWidget->on_done_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::enableExitButton));
				printWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(printWidget);
				break;
			case CloseElectionSteps::CONFIGURATION_GENERATEPVREPORT:
				generatePVReport = AbstractFactoryWidget::createGeneratePVReportWidget();
				generatePVReport->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				generatePVReport->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				countGeneratePV = wizardVector.size();
				wizardVector.push_back(generatePVReport);
				break;
			case CloseElectionSteps::CONFIGURATION_REGISTERCLOSENOTE:
				noteRegisterWidget = new CloseNoteWidget();
				noteRegisterWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				noteRegisterWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				noteRegisterWidget->showNextButton();
				wizardVector.push_back(noteRegisterWidget);
				break;
			case CloseElectionSteps::CONFIGURATION_STATISTICS:
				statCounterWidget = new StatisticCounterRegisterWidget();
				statCounterWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				statCounterWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				statCounterWidget->ShowNextButton();
				wizardVector.push_back(statCounterWidget);
				break;
			case CloseElectionSteps::CONFIGURATION_VOTEDURATION:
				durationWidget = new DurationVerificationWidget();
				durationWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				durationWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(durationWidget);
				break;
			case CloseElectionSteps::CONFIGURATION_SIGNELECTIONRESOURCE:
				signElection = new SignElectionResourceWidget();
				signElection->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::ErrorHappen));
				signElection->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(signElection);
				break;
/*			case CloseElectionSteps::CONFIGURATION_GENERATECODIFILES:
				persistCodiFilesWidget = AbstractFactoryWidget::createPersistCodiFilesWidget();
				persistCodiFilesWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::on_cancelButton_clicked));
				persistCodiFilesWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				wizardVector.push_back(persistCodiFilesWidget);
				break;*/
			case CloseElectionSteps::CONFIGURATION_GENERATEALLRESULT:
				persistAllResultWidget = AbstractFactoryWidget::createPersistAllResultWidget();
				persistAllResultWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::on_cancelButton_clicked));
				persistAllResultWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::disableExitButton));
				countGenerateAllResult = wizardVector.size();
				wizardVector.push_back(persistAllResultWidget);
				break;
		}
	}

	manager = new WizardWidgetManager(wizardVector);
	//manager->on_finish_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::Finish));
	manager->on_transition_signal_emit().connect(sigc::mem_fun(*this, &CloseElectionFunctionality::TransitionSignal));
	manager->set_shadow_type(SHADOW_NONE);

	closeFrame->remove();
	closeFrame->add(*manager);
	closeFrame->set_shadow_type(SHADOW_NONE);
	closeFrame->show_all_children();
	closeFrame->show();

	count = 1;
}

void CloseElectionFunctionality::ElectionWasClosed()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ElectionWasClosed"));
	RefreshInfo();
}

void CloseElectionFunctionality::on_cancelButton_clicked()
{
	ExitFunctionality();
}

bool CloseElectionFunctionality::CanExecute()
{
	bool validate = GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>::CanExecute();

	if (validate && !SAESGUIConfigurationManager::Current()->checkPollworkerRegister())
	{
		validate = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.RegisterPollWorker"));
	}

	return validate;
}

Gtk::Widget* CloseElectionFunctionality::GetFrame()
{
	closeFrame = new Frame();
	LoadWizardFrame();
	return closeFrame;
}

void CloseElectionFunctionality::TransitionSignal()
{
	bool enableHeldButton = (countGeneratePV == -1 || countGeneratePV != count) &&
			(countGenerateAllResult == -1 || countGenerateAllResult != count);

	bool enableButton = (++count) == (int)wizardVector.size() ||
		manager->getCurrentWidget()->isEnabledButtonExitWizard();

	setExitButtonSensitive(enableButton);
	setHelpButtonSensitive(enableButton && enableHeldButton);
}

void CloseElectionFunctionality::ErrorHappen()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ErrorClosingElection"));
	enableExitButton();
	RefreshInfo();
}

void CloseElectionFunctionality::Finish()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ElectionWasClosed"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &CloseElectionFunctionality::ExitFunctionality),50);
}

bool CloseElectionFunctionality::Enable()
{
	bool enableFunctionality = true;

	if(!checkIfCanCloseByDate())
	{
		enableFunctionality = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.UnableKeyMessageIsNotCloseDateYet"));
	}
	else
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.CanCloseBecauseDateCheckPassed"));
	}
	
	return enableFunctionality;
};

string CloseElectionFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.CloseElection");
};

Smartmatic::Functionality::MenuOptionDescriptor CloseElectionFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MCloseElectionFunctionality,false);
};	

void CloseElectionFunctionality::Dispose()
{
	if(idCardWidget)
	{
		idCardWidget->dispose();
	}

	wizardVector.clear();

	if(MachineOperationManager::getInstance()->getOperationStatus()->getElectionStatusWrapper()->getEletionState()
			!= Smartmatic::SAES::Voting::Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED)
		MachineOperationManager::getInstance()->deleteCloseFiles();
};

Smartmatic::Log::ISMTTLog* CloseElectionFunctionality::getLogger()
{
	return logger;
}

Glib::ustring CloseElectionFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.LogStartFunctionality");
}

Glib::ustring CloseElectionFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.LogCloseFunctionality");
}
