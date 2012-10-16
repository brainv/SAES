/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ReportLogWidget.h"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "Printing/AuditLogPrintDocument.h"
#include "Printing/ErrorLogPrintDocument.h"
#include "Printing/PrinterStatusNotifier.h"
#include "Operation/MachineOperationManager.hxx"
#include <Log/SMTTLogManager.h>
#include <glibmm.h>

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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Operation;

ISMTTLog* ReportLogWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ReportLogWidget",GETTEXT_PACKAGE);

ReportLogWidget::ReportLogWidget(LogReader * logReaderAudit,
                                 LogReader * logReaderError)
{

	m_TopWidgetTableLayout = NULL;
	m_NotebookLogs = NULL;
	m_FrameAudit = NULL;
	m_FrameErrors = NULL;
	logPagingTreeViewAudit = NULL;
	logPagingTreeViewError = NULL;

	this->logReaderAudit = logReaderAudit;
	this->logReaderError = logReaderError;

	this->m_AuditLogPrintReport = new AuditLogPrintDocument (logReaderAudit, MachineOperationManager::getInstance()->getElectoralConfiguration());
	this->m_ErrorLogPrintReport = new ErrorLogPrintDocument (logReaderError, MachineOperationManager::getInstance()->getElectoralConfiguration());

	m_AuditLogPrintReport->setClient (this);
	m_ErrorLogPrintReport->setClient (this);

	LoadGUI();
}

ReportLogWidget::~ReportLogWidget()
{
	if(!m_TopWidgetTableLayout)
	{
		delete(m_TopWidgetTableLayout);
		m_TopWidgetTableLayout= NULL;
	}
	if(!m_NotebookLogs)
	{
		delete(m_NotebookLogs);
		m_NotebookLogs= NULL;
	}
	if(!m_FrameAudit)
	{
		delete(m_FrameAudit);
		m_FrameAudit= NULL;
	}
	if(!m_FrameErrors)
	{
		delete(m_FrameErrors);
		m_FrameErrors= NULL;
	}

	if (m_AuditLogPrintReport != NULL)
		delete m_AuditLogPrintReport;

	if (m_ErrorLogPrintReport != NULL)
		delete m_ErrorLogPrintReport;

	if (logPagingTreeViewAudit)
	{
		delete logPagingTreeViewAudit;
	}

	if (logPagingTreeViewError)
	{
		delete logPagingTreeViewError;
	}
	connPrintAudit.disconnect();
	connPrintError.disconnect();
}

bool ReportLogWidget::checkPrinter()
{
	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	return ( printerState & printNotifier.getErrorCondition () ) == 0;
}

void ReportLogWidget::on_buttonPrint_clicked()
{
	if (!checkPrinter())
	{
		showErrorMessage();
		return;
	}

	showLoadImage();

	m_signalPrint_begin.emit();
	logPagingTreeViewAudit->SetPrintButtonSensitive(false);
	logPagingTreeViewError->SetPrintButtonSensitive(false);

	int page = m_NotebookLogs->get_current_page ();

	if(page == 0)
	    printAuditLogger ();
	else
		printErrorLogger ();
}

void ReportLogWidget::printAuditLogger()
{
	m_AuditLogPrintReport->Print ();
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.PrintingAuditLog"));
}

void ReportLogWidget::printErrorLogger()
{
	m_ErrorLogPrintReport->Print ();
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.PrintingErrorLog"));
}

ReportLogWidget::signalPrint ReportLogWidget::on_print_begin()
{
	return m_signalPrint_begin;
}

ReportLogWidget::signalPrint ReportLogWidget::on_print_end()
{
	return m_signalPrint_end;
}

void ReportLogWidget::onDocumentPrinted (PrintDocumentResult res)
{
	PrintDocumentResult::PrintingResultEnumType resultType = PrintDocumentResult::PRINTING_NONE;
	Glib::ustring msg;

	res.getResult(statusPrint, msg, resultType);

	if ( !statusPrint )
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.LogPrinted"));
		messagePrint = _("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.PrintError");
	}
	else
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.LogPrinted"));
		messagePrint = _("Smartmatic.SAES.GUI.Widgets.ReportLogWidget.PrintOk");
	}

	showPrintMessage();
	int timeout = SAESGUIConfigurationManager::Current()->GetLogReportFunctionalityConfiguration().getPrinterMessageTimeout();
	Glib::signal_timeout ().connect_once ( sigc::mem_fun (*this, &ReportLogWidget::endPrint), timeout);
}

void ReportLogWidget::LoadGUI ()
{
	Glib::RefPtr<Gtk::Builder> widget_builder =
		Gtk::Builder::create_from_file (ResourcePathProvider::Current()->
			GetResourcePath(PACKAGE_NAME,"ui/ReportLogWidget.glade"));

	widget_builder->get_widget ("m_TopWidgetTableLayout", m_TopWidgetTableLayout);
	widget_builder->get_widget ("m_NotebookLogs", m_NotebookLogs);
	widget_builder->get_widget ("m_FrameAudit", m_FrameAudit);
	widget_builder->get_widget ("m_FrameErrors", m_FrameErrors);
	
	
	if(this->logReaderAudit != NULL)
	{
		logPagingTreeViewAudit = new  LogPagingTreeViewWidget(this->logReaderAudit); 
		m_FrameAudit->add(*logPagingTreeViewAudit);
		m_FrameAudit->show_all_children();
	}

	if(this->logReaderError != NULL)
	{
		logPagingTreeViewError = new  LogPagingTreeViewWidget(this->logReaderError); 
		m_FrameErrors->add(*logPagingTreeViewError);
		m_FrameErrors->show_all_children();
	}

	Gtk::Label* auditTitleLabel = manage(new Gtk::Label());
	Gtk::Label* errorTitleLabel = manage(new Gtk::Label());
	auditTitleLabel->set_label(_("Smartmatic.SAES.Glade.ReportLogWidget.TagAudit"));
	errorTitleLabel->set_label(_("Smartmatic.SAES.Glade.ReportLogWidget.TagError"));
	m_NotebookLogs->set_tab_label(*m_FrameAudit, *auditTitleLabel);
	m_NotebookLogs->set_tab_label(*m_FrameErrors, *errorTitleLabel);


	if (logPagingTreeViewAudit)
	{
	    connPrintAudit = logPagingTreeViewAudit->signalPrint_detected.connect( sigc::mem_fun(this, &ReportLogWidget::on_buttonPrint_clicked));
	}

	if (logPagingTreeViewError)
	{
	    connPrintError = logPagingTreeViewError->signalPrint_detected.connect( sigc::mem_fun(this, &ReportLogWidget::on_buttonPrint_clicked));
	}

	this->add (*m_TopWidgetTableLayout);
	this->show_all_children (true);
	this->set_visible(true);

	showInitialImage();
}

void ReportLogWidget::showInitialImage()
{
	if(logPagingTreeViewAudit)
	{
		logPagingTreeViewAudit->SetPrintButtonSensitive(true);
		logPagingTreeViewAudit->showInitialImage();
	}

	if(logPagingTreeViewError)
	{
		logPagingTreeViewError->SetPrintButtonSensitive(true);
		logPagingTreeViewError->showInitialImage();
	}
}

void ReportLogWidget::showErrorMessage()
{
	if(logPagingTreeViewAudit)
		logPagingTreeViewAudit->showPrintErrorImage();

	if(logPagingTreeViewError)
		logPagingTreeViewError->showPrintErrorImage();
}

void ReportLogWidget::showLoadImage()
{
	if(logPagingTreeViewAudit)
		logPagingTreeViewAudit->showLoadImage();

	if(logPagingTreeViewError)
		logPagingTreeViewError->showLoadImage();
}

void ReportLogWidget::showPrintMessage()
{
	if(logPagingTreeViewAudit)
	{
		statusPrint ? logPagingTreeViewAudit->showPrintOkImage() : logPagingTreeViewAudit->showPrintErrorImage();
		logPagingTreeViewAudit->SetPrinterMessage (messagePrint);
	}

	if(logPagingTreeViewError)
	{
		statusPrint ? logPagingTreeViewError->showPrintOkImage() : logPagingTreeViewError->showPrintErrorImage();
		logPagingTreeViewError->SetPrinterMessage (messagePrint);
	}
}


void ReportLogWidget::endPrint()
{
	showInitialImage();
	m_signalPrint_end.emit ();
}
