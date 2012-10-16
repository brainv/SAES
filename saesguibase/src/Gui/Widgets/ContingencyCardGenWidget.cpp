/*
 * ContingencyCardGenWidget.cpp
 *
 *  Created on: Oct 17, 2011
 *      Author: marcel
 */

#include <Environment/Configurations/resource-path-provider.h>
#include <System/guid-class.h>
#include <Operation/Card/CardController.hxx>
#include <Log/SMTTLogManager.h>
#include <Voting/VotingCenters/VotingCentersWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Printing/PrinterStatusNotifier.h"
#include <Security/Encryption.hxx>
#include <iostream>
#include "ContingencyCardGenWidget.h"
#include <System/Runtime/ProcessLauncher.h>

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

#define SUCCESS_HANDLING_INTERVAL 300
#define TIMER_INTERVAL 3000

#define PASS_PIN_LEN 8

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::VotingCenters;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Runtime;

ISMTTLog* ContingencyCardGenWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.ContingencyCardGenWidget",GETTEXT_PACKAGE);


//=============================================================================
//=============================== Life Cycle ==================================
//=============================================================================


ContingencyCardGenWidget::ContingencyCardGenWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::StepWidget(), progress(progress)
{
	report = NULL;
	mainFrame = NULL;
	mainVBox = NULL;
	centerFrame = NULL;
	hboxButton = NULL;
	retryButton = NULL;
	quitButton = NULL;

	// initialize GUI elements

	initialize ();

	// set up workflow sequence

	steps.push_back (CONTCARD_WAITING_INSERTION);
	steps.push_back (CONTCARD_WRITING);
	steps.push_back (CONTCARD_ERROR_HANDLING);
	steps.push_back (CONTCARD_WAITING_REMOVAL);
	steps.push_back (CONTCARD_PRINTING_REPORT);
	steps.push_back (CONTCARD_ERROR_HANDLING);
	steps.push_back (CONTCARD_SHOWING_RESULTS);


	current_step = steps.begin ();
	result_step = steps.end ();
	result_step--;

	// set initial error state

	current_error = CONTCARD_SUCCESS;

	// set card data structure

	m_CardData.setOpeningCode(MachineOperationManager::getInstance()->
			getOperationStatus()->getElectionStatusWrapper()->getOpeningCode());

	logger->Debug (MachineOperationManager::getInstance()->
			getOperationStatus()->getElectionStatusWrapper()->getOpeningCode());

	std::string passphrase = Encryption::getInstance()->getSecretKey().getPlainPassphrase();

	m_CardData.setPassphrase(passphrase);

	VotingCenter votingCenter;
	VotingCentersWrapper::getInstance()->getInstallationVotingCenter(votingCenter);

	m_CardData.setPollingPlace(votingCenter.getCode ());

	// initilialize card controller

	CardController::getInstance ()->initialize ();

	// launch workflow

	ManageState ();
}

ContingencyCardGenWidget::~ContingencyCardGenWidget()
{
	this->remove();

	mconn_wait_card_insertion.disconnect ();
	mconn_wait_card_writing.disconnect();
	mconn_wait_printing.disconnect();
	mconn_wait_card_removal.disconnect ();

	if (report)
	{
		delete report;
		report = NULL;
	}
	if (progress)
	{
		delete progress;
		progress = NULL;
	}
	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (centerFrame)
	{
		delete centerFrame;
		centerFrame = NULL;
	}
	if (hboxButton)
	{
		delete hboxButton;
		hboxButton = NULL;
	}
	if (retryButton)
	{
		delete retryButton;
		retryButton = NULL;
	}
	if (quitButton)
	{
		delete quitButton;
		quitButton = NULL;
	}
}


//=============================================================================
//================================== GUI ======================================
//=============================================================================

void ContingencyCardGenWidget::initialize ()
{
	int quit_button_width = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getShutdownButtonConf ()
			.getButtonWidth ();
	int quit_button_height = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getShutdownButtonConf ()
			.getButtonHeight ();
	int quit_button_font_size = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getShutdownButtonConf ()
			.getFontSize ();

	int retry_button_height = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getRetryButtonConf ()
			.getButtonHeight ();
	int retry_button_width = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getRetryButtonConf ()
			.getButtonWidth ();
	int retry_button_font_size = SAESGUIConfigurationManager::Current()->
			 getContingencyCardWidgetConfiguration ()
			.getRetryButtonConf ()
			.getFontSize ();

	Smartmatic::GUI::Configuration::LabelConfiguration titleConf =
			SAESGUIConfigurationManager::Current()->GetContingencyTitleLabelConfiguration();

	Smartmatic::GUI::Configuration::LabelConfiguration textConf =
			SAESGUIConfigurationManager::Current()->GetContingencyTextLabelConfiguration();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/ContingencyCardGenWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ContingencyCardGenWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("center-frame", centerFrame);
	builder->get_widget("hbox-button", hboxButton);
	builder->get_widget_derived("button1", quitButton);
	builder->get_widget_derived("button2", retryButton);

	progress->setTitleConfig(titleConf);
	progress->setTextConfig(textConf);

	centerFrame->add(*progress);

	hboxButton->set_visible(false);
	hboxButton->set_no_show_all(true);

	// RetryButton

	retryButton->SetImage (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/contingency-retry.png"));

	retryButton->SetButtonType (SmartmaticButton::Custom);
	retryButton->ModifyFontSize(retry_button_font_size);
	retryButton->WidgetsPosition (5, 6, 0);

	retryButton->set_size_request (retry_button_width, retry_button_height);
	retryButton->set_no_show_all (true);
	retryButton->set_visible (false);

	retryButton->signal_clicked (). connect (sigc::mem_fun (*this, &ContingencyCardGenWidget::OnRetryButtonClicked));


	// QuitButton

	quitButton->SetImage (ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/contingency-shut-down.png"));

	quitButton->SetButtonType (SmartmaticButton::Custom);
	quitButton->ModifyFontSize(quit_button_font_size);
	quitButton->WidgetsPosition (5, 6, 0);

	quitButton->set_size_request (quit_button_width, quit_button_height);
	quitButton->set_no_show_all (true);
	quitButton->set_visible (false);

	quitButton->signal_clicked (). connect (sigc::mem_fun (*this, &ContingencyCardGenWidget::OnQuitButtonClicked));

	setWidget(mainFrame);
}

void ContingencyCardGenWidget::SetResultScreen ()
{
	progress->hideImage();
	progress->hideText();

	retryButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.RetryButtonLabel"));
	quitButton->SetLabel (_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.QuitButtonLabel"));

	switch (current_error)
	{
	case CONTCARD_SUCCESS:
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ResultSuccess"));
		break;
	case CONTCARD_ERROR_READER:
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ErrorReader"));
		break;
	case CONTCARD_ERROR_WRITING:
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ErrorWritingCardData"));
		break;
	case CONTCARD_ERROR_PRINTING:
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ErrorPrinting"));
		break;
	default:
		logger->Debug ("WARNING: Unknown step");
		break;
	}
}

void ContingencyCardGenWidget::SetScreen ()
{
	hboxButton->set_visible(false);
	retryButton->set_visible (false);
	quitButton->set_visible (false);

	retryButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.RetryButtonLabel"));
	quitButton->SetLabel (_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.QuitButtonLabel"));

	switch (*current_step)
	{
	case CONTCARD_WAITING_INSERTION:

		progress->showText();
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.WaitForCardInsertion"));
		progress->setText(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.TextWaitForCardInsertion"));
		progress->setImage("ui/request_contingency_card.gif");

		break;

	case CONTCARD_WRITING:

		progress->showText();
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.WritingCardData"));
		progress->setText(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.TextWritingCardData"));
		progress->setImage("ui/writing-contingency-card.gif");

		break;

	case CONTCARD_PRINTING_REPORT:

		progress->showText();
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.PrintingContingencyReport"));
		progress->setText(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.TextPrintingContingencyReport"));
		progress->setImage("ui/printing-contingency-report.gif");

		break;

	case CONTCARD_WAITING_REMOVAL:

		progress->showText();
		progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.WaitingForCardRemoval"));
		progress->setText(_("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.TextWaitingForCardRemoval"));
		progress->setImage("ui/extract_contingency_card.gif");

		break;

	case CONTCARD_SHOWING_RESULTS:

		SetResultScreen ();
		break;

	case CONTCARD_ERROR_HANDLING:

		switch (current_error)
		{
		case CONTCARD_ERROR_READER:
		case CONTCARD_ERROR_WRITING:

			progress->hideText();
			progress->setTitle(m_ErrorMsg);
			hboxButton->set_visible(true);
			retryButton->set_visible (true);
			quitButton->set_visible (true);
			progress->setImage("ui/contingency-card_error.gif");

			break;

		case CONTCARD_ERROR_PRINTING:

			progress->hideText();
			progress->setTitle(m_ErrorMsg);
			hboxButton->set_visible(true);
			retryButton->set_visible (true);
			quitButton->set_visible (true);
			progress->setImage("ui/contingency-printer-error.img");

			break;

		case CONTCARD_FATAL_ERROR:

			progress->showText();
			progress->setTitle(m_ErrorMsg);
			progress->setText(" ");
			hboxButton->set_visible(true);
			retryButton->set_visible (false);  // deny retrial on fatal error conditions
			quitButton->set_visible (true);
			progress->setImage("ui/contingency-fatal-error.img");

			break;

		case CONTCARD_SUCCESS:
			break;

		default:
			break;
		}

		break;

	default:
		logger->Debug ("WARNING: Unknown step");
		break;
	}
}


//=============================================================================
//============================ Flow Logic =====================================
//=============================================================================

void ContingencyCardGenWidget::ManageState ()
{
	SetScreen ();

	switch (*current_step)
	{
	case CONTCARD_WAITING_INSERTION:

		mconn_wait_card_insertion = Glib::signal_timeout ().connect
				(sigc::mem_fun (*this, &ContingencyCardGenWidget::DetectCard),
						TIMER_INTERVAL);

		break;

	case CONTCARD_WRITING:

		WriteContingencyData ();

		Glib::signal_timeout ().connect_once(
			sigc::mem_fun (*this, &ContingencyCardGenWidget::Wait),
				TIMER_INTERVAL);

		break;

	case CONTCARD_PRINTING_REPORT:

//	    if(!Glib::thread_supported())
//	    	Glib::thread_init();
//
//	    Glib::Thread::create(sigc::mem_fun(*this, &ContingencyCardGenWidget::PrintContingencyReport), false);

	    PrintContingencyReport ();

	    break;

	case CONTCARD_WAITING_REMOVAL:

		mconn_wait_card_removal = Glib::signal_timeout ().connect
				(sigc::mem_fun (*this, &ContingencyCardGenWidget::DetectRemoval),
					TIMER_INTERVAL);

		break;

	case CONTCARD_SHOWING_RESULTS:

		Glib::signal_timeout ().connect_once (
			sigc::mem_fun (*this, &ContingencyCardGenWidget::WaitAndExit),
				TIMER_INTERVAL);

		break;

	case CONTCARD_ERROR_HANDLING:

		if ( current_error != CONTCARD_SUCCESS )
			return;
		else
		{
			Glib::signal_timeout ().connect_once (
				sigc::mem_fun (*this, &ContingencyCardGenWidget::Wait),
					SUCCESS_HANDLING_INTERVAL);
		}

		break;

	default:
		logger->Debug ("WARNING: Unknown step");
		return;
	}

	if (current_step != result_step)
		current_step++;
	else
		current_step = result_step; // Don't allow to go beyond the last step
}

void ContingencyCardGenWidget::WriteContingencyData ()
{
	bool success;
	unsigned char pin_data[PASS_PIN_LEN];
	int i;
	size_t pin_len = PASS_PIN_LEN;
	std::string pin_str_rep = "";

	m_Pin = "";

	logger->Debug ("Writing");
	std::stringstream pin_stream;
	std::stringstream pin_report_stream;

	SafeBuffer pin;
	SafeBuffer pin_salt =
			Smartmatic::System::GuidClass::NewGuid().toSafeBuffer ();

	Encryption::getInstance()->getComposeKey(pin_salt, pin, PASS_PIN_LEN);
	pin.GetData((unsigned char **)pin_data, pin_len);

	for (i=0; i< PASS_PIN_LEN; i++)
	{
		pin_report_stream << ( pin_data[i] <= 0x0f ? "0" : "" ) << std::hex
		   << (unsigned int)pin_data[i] << ( i%2 && i != 7 ? "-" : "" );

		pin_stream << ( pin_data[i] <= 0x0f ? "0" : "" ) << std::hex
			<< (unsigned int)pin_data[i];
	}

	m_Pin += pin_report_stream.str ();
	pin_str_rep += pin_stream.str ();

	try
	{
		logger->Debug("PIN: " + pin_str_rep);
		success = CardController::getInstance ()->writeContingencyCardData (m_CardData, pin_str_rep);
	}
	catch(...)
	{
		logger->Debug("ERROR write card data");
		success = false;
	}

	if ( ! success )
	{
		m_ErrorMsg = _("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ErrorWritingCardData");
		current_error = CONTCARD_ERROR_WRITING;
	}
	else
	{
		m_ErrorMsg = _("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ResultSuccess");
		current_error = CONTCARD_SUCCESS;
	}
}

void ContingencyCardGenWidget::PrintContingencyReport ()
{
	logger->Debug ("Printing");

	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printer_state = printNotifier.getPrinterState();

	if ( ( printer_state & printNotifier.getErrorCondition () ) != 0 )
	{
		current_error = CONTCARD_ERROR_PRINTING;
		m_ErrorMsg = printNotifier.getStatusMessage (printer_state);

    	Glib::signal_timeout ().connect_once (
    		sigc::mem_fun (*this, &ContingencyCardGenWidget::Wait),
    		    TIMER_INTERVAL);
	}
	else
	{
		m_ErrorMsg = _("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ResultSuccess");
		current_error = CONTCARD_SUCCESS;

		report = new ContingencyCardReport (m_Pin, MachineOperationManager::getInstance ()->getElectoralConfiguration ());
		report->setClient(this);
		report->Print ();
	}
}


//=============================================================================
//============================== Signal Handling ==============================
//=============================================================================


void ContingencyCardGenWidget::OnRetryButtonClicked ()
{
	current_step--;
	ManageState ();
}

void ContingencyCardGenWidget::OnQuitButtonClicked ()
{
	std::string commandShut = "powerdown &";
	(void)ProcessLauncher::RunProcessThroughSystem(commandShut.c_str());
}

bool ContingencyCardGenWidget::DetectCard ()
{
	bool card_detected = CardController::getInstance()->isCardPresent();

	if ( card_detected )
	{
		logger->Debug ("Card inserted");
		ManageState ();
	}

	return ! card_detected;
}

bool ContingencyCardGenWidget::DetectRemoval ()
{
	bool card_detected = CardController::getInstance()->isCardPresent();

	if ( ! card_detected )
	{
		logger->Debug ("Card removed");
		ManageState ();
	}

	return card_detected;
}

void ContingencyCardGenWidget::Wait ()
{
	logger->Debug ("Waiting");
	ManageState ();
}

void ContingencyCardGenWidget::WaitAndExit ()
{
	logger->Debug ("Waiting");
	dispose();
	on_card_generated.emit (current_error);
	signalEnd.emit();
}

void ContingencyCardGenWidget::dispose ()
{
	CardController::getInstance()->dispose ();
	mconn_wait_card_insertion.disconnect ();
	mconn_wait_card_writing.disconnect();
	mconn_wait_printing.disconnect();
	mconn_wait_card_removal.disconnect ();
}

void ContingencyCardGenWidget::onDocumentPrinted (PrintDocumentResult res)
{
	PrintDocumentResult::PrintingResultEnumType resultType = PrintDocumentResult::PRINTING_NONE;
	Glib::ustring msg;
	bool print_successfull;

	res.getResult(print_successfull, msg, resultType);

	if ( ! print_successfull)
	{
		m_ErrorMsg = msg;

		if (resultType == PrintDocumentResult::PRINTING_JOB_ABORTED_BY_SYSTEM)
			current_error = CONTCARD_FATAL_ERROR;
		else
			current_error = CONTCARD_ERROR_PRINTING;
	}
	else
	{
		m_ErrorMsg = _("Smartmatic.SAES.GUI.Widgets.ContingencyCardGenWidget.ResultSuccess");
		current_error = CONTCARD_SUCCESS;
	}

	Glib::signal_timeout().connect_once (
		sigc::mem_fun(*this , &ContingencyCardGenWidget::ManageState), 100);
}

std::string ContingencyCardGenWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.InitializationWindow.Title");
}
