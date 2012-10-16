/*
 * ReportPrintingWidget.cpp
 *
 *  Created on: Apr 18, 2011
 *      Author: root
 */


#include <iostream>
#include <vector>
#include <glibmm.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Configuration/SaesConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "ReportPrintingWidget.h"
#include <Operation/MachineOperationManager.hxx>

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

using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Printing;
using namespace std;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;

//======================= Life Cycle =============================

ReportPrintingWidget::ReportPrintingWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	outsideHbox = NULL;
	eventbox_ReportListTitle = NULL;
	m_PrintButton = NULL;
	m_ReportListTitle = NULL;
	mainEventBox = NULL;

	m_SignalPrintFileConn = m_ReportPrinterController.signalReportChanged ()
			.connect (sigc::mem_fun (*this, &ReportPrintingWidget::OnBeginReportPrinting));

	m_SignalPrintFinishedConn = m_ReportPrinterController.signalReportPrintFinished ()
			.connect (sigc::mem_fun (*this, &ReportPrintingWidget::OnAllReportPrintingFinished));

	m_SignalErrorDetectedConn = m_ReportPrinterController.signalReportPrintErrorDeteced ()
			.connect (sigc::mem_fun (*this, &ReportPrintingWidget::OnReportPrintErrorDetected));

	LoadGUI ();
	m_CurrentState = RPWDGT_INIT;
	DisplayState (RPWDGT_INIT);
}

ReportPrintingWidget::~ReportPrintingWidget()
{
	remove();

	m_SignalPrintFileConn.disconnect ();
	m_SignalPrintFinishedConn.disconnect ();
	m_SignalErrorDetectedConn.disconnect ();

	if(outsideHbox)
	{
		delete outsideHbox;
		outsideHbox = NULL;
	}
	if(m_ReportListTitle)
	{
		delete m_ReportListTitle;
		m_ReportListTitle = NULL;
	}

	if(eventbox_ReportListTitle)
	{
		delete eventbox_ReportListTitle;
		eventbox_ReportListTitle = NULL;
	}

	if (m_PrintButton)
	{
		delete m_PrintButton;
		m_PrintButton = NULL;
	}

	if (progress)
	{
		delete progress;
		progress = NULL;
	}

	if (mainEventBox)
	{
		delete mainEventBox;
		mainEventBox = NULL;
	}
}


//======================= Visual elements management =========================//

void ReportPrintingWidget::LoadGUI ()
{
	m_ReportPrinterController.loadReports();
    m_ReportPrinterController.setLanguages(MachineOperationManager::getInstance()->getElectoralConfiguration()->getLanguageListFullName());

	Glib::RefPtr<Gtk::Builder> widget_builder =
			Gtk::Builder::create_from_file (ResourcePathProvider::Current()->
					GetResourcePath(PACKAGE_NAME,"ui/ReportPrintingWidget.glade"));

	std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile>
	report_list = m_ReportPrinterController.GetReportList ();

	LabelConfiguration compositeMsgLabelConf = SAESGUIConfigurationManager::Current()->GetCompositeMsgLabelConfiguration ();
	LabelConfiguration progressLabelConf = SAESGUIConfigurationManager::Current()->GetProgressLabelConfiguration ();
	LabelConfiguration reportListTitleConf = SAESGUIConfigurationManager::Current()->GetReportListTitleLabelConfiguration ();
	LabelConfiguration reportLabelConf = SAESGUIConfigurationManager::Current()->GetFileItemLabelConfiguration ();

	// m_ReportListTitle

	widget_builder->get_widget ("m_ReportListTitle", m_ReportListTitle);
	m_ReportListTitle->set_text (_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.ReportListTitleLabelInitialMsg"));
	m_ReportListTitle->set_size_request(270, -1);
	LabelConfiguration::SetLabelConfiguration (m_ReportListTitle, reportListTitleConf);

	// m_PrintButton

	widget_builder->get_widget_derived ("m_PrintButton", m_PrintButton);
	m_PrintButton->set_label (_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.PrintButtonMsg"));
	m_PrintButton->signal_clicked().connect (mem_fun (*this, &ReportPrintingWidget::OnPrintButtonClicked));

	progress->setTitleConfig(compositeMsgLabelConf);
	progress->setTextConfig(progressLabelConf);

	progress->setTitle(_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.CompositeLabelInitialMsg"));
	progress->setText(_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.ProgressLabelInitialMsg"));

	// m_ReportListVBox

	widget_builder->get_widget ("m_ReportListVBox", m_ReportListVBox);

	if ( report_list.size () >= 0 )
	{
		std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile>::const_iterator it
		= report_list.begin ();

		for (it = report_list.begin(); it != report_list.end(); it++)
		{
			Gtk::Label* report_label = Gtk::manage (new Gtk::Label (it->getReportTitle()));

			LabelConfiguration::SetLabelConfiguration (report_label, reportLabelConf);

			report_label->set_visible (true);
			report_label->set_alignment(Gtk::ALIGN_LEFT);
			report_label->set_size_request(270, -1);
			report_label->set_line_wrap();

			m_ReportListVBox->pack_start (*report_label, false, true);
		}
	}

	widget_builder->get_widget ("hbox1", outsideHbox);
	widget_builder->get_widget ("main-eventbox", mainEventBox);

	widget_builder->get_widget ("eventbox_ReportListTitle", eventbox_ReportListTitle);
	eventbox_ReportListTitle->set_name("ReportListTitleEventBox");

	mainEventBox->add(*progress);

	setWidget(outsideHbox);
}

void ReportPrintingWidget::DisplayState (WidgetStateEnumType state)
{
	switch (state)
	{
	case RPWDGT_INIT:

		progress->setImage("ui/RPW_inactive.img");
		m_PrintButton->set_sensitive (true);
		break;

	case RPWDGT_PRINTING:

		progress->setImage("ui/RPW_printing.img");
		m_PrintButton->set_sensitive (false);
		break;

	case RPWDGT_PRINTERROR:

		progress->setImage("ui/RPW_error.img");
		progress->setTitle(m_ReportPrinterController.GetErrorMessage ());
		m_PrintButton->set_sensitive (true);
		break;

	case RPWDGT_FINISHED:

		progress->setImage("ui/RPW_ok.img");
		progress->setText(_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.ReportPrintingFinishedMessage"));
		m_PrintButton->set_sensitive (true);
		break;

	default:

		break;
	}

	m_CurrentState = state;
}

void ReportPrintingWidget::PrintReportsThreadBody ()
{
	m_ReportPrinterController.PrintReports ();
}


//======================= Signal Handling =============================

void ReportPrintingWidget::OnPrintButtonClicked ()
{
	m_SignalBeginPrint.emit();
	DisplayState (RPWDGT_PRINTING);
	Glib::Thread::create (sigc::mem_fun (*this, &ReportPrintingWidget::PrintReportsThreadBody), false);
}

void ReportPrintingWidget::OnAllReportPrintingFinished ()
{
	if (m_CurrentState != RPWDGT_PRINTERROR)
	{
		DisplayState (RPWDGT_FINISHED);
	}

	m_SignalFinished.emit (true);
}

void ReportPrintingWidget::OnReportPrintErrorDetected ()
{
	DisplayState (RPWDGT_PRINTERROR);
	m_SignalFinished.emit (false);
}

void ReportPrintingWidget::OnBeginReportPrinting ()
{
	Glib::ustring count_message;
	Glib::ustring file_msg;
	Glib::ustring compose_fmt (_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.ComposeLabelMsgFormat"));
	Glib::ustring msg_header =_("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.PrintingNewReportMesg");
	Glib::ustring report_name = m_ReportPrinterController.GetReportName ();
	Glib::ustring report_dsc = m_ReportPrinterController.GetReportDescription ();

	int num_copies = m_ReportPrinterController.getTotalDocumentsToPrint();
	int num_printed = m_ReportPrinterController.GetNumOfCppiesPrinted ();

	std::stringstream ss;

	file_msg = Glib::ustring::compose (compose_fmt, msg_header, report_name, report_dsc);

	ss << _("Smartmatic.SAES.GUI.Widgets.ReportPrintingWidget.ReportCountMessage")
	   << " " << num_printed << " / " << num_copies;
	count_message.assign ( ss.str() );

	progress->setTitle(file_msg);
	progress->setText(count_message);
}



