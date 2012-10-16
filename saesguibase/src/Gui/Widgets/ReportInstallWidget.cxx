/*
 * ReportInstallWidget.cxx
 *
 *  Created on: 19/10/2011
 *      Author: soto
 */

#include "ReportInstallWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Printing/PrinterStatusNotifier.h>
#include <Printing/PrintDocumentResult.h>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Operation;

ISMTTLog* ReportInstallWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ReportInstallWidget",GETTEXT_PACKAGE);

ReportInstallWidget::ReportInstallWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::StepWidget(), progress(progress)
{
	this->status = false;
	this->installationPrintDocument = NULL;
	this->setWidget(progress);
}

ReportInstallWidget::~ReportInstallWidget()
{
	dispose();
}

void ReportInstallWidget::initialize()
{
	progress->setImage(ProgressWidget::PRINTING);
	progress->setTitle(" ");
	progress->setText(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.PrintingReport"));
}

void ReportInstallWidget::dispose()
{
	this->remove();

	if (installationPrintDocument)
	{
		delete installationPrintDocument;
		installationPrintDocument = NULL;
	}
	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void ReportInstallWidget::start(bool createBarcode)
{
	if (!installationPrintDocument)
	{
		installationPrintDocument = new InstallationPrintDocument(MachineOperationManager::getInstance()->getElectoralConfiguration(),true, createBarcode);
		installationPrintDocument->setIsPasswordRetry(!createBarcode);
		installationPrintDocument->setClient(this);
	}

	initialize();
	startPrinting ();
}

void ReportInstallWidget::startPrinting()
{
	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	if ( ( printerState & printNotifier.getErrorCondition () ) == 0 )
	{
		installationPrintDocument->Print();
	}
	else
	{
		message = printNotifier.getStatusMessage (printerState); //_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.PrinterIsWrong");
		status = false;
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &ReportInstallWidget::showMessagePrinting), 100);
	}
}

void ReportInstallWidget::end()
{
	signalEnd.emit();
}

void ReportInstallWidget::showMessagePrinting()
{
	if(status)
	{
		logger->Debug("Printing success");
		message = _("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.SuccessfulPosters");
		progress->setImage(ProgressWidget::PRINTING_OK);
		MachineOperationManager::getInstance()->saveElectoralConfigurationReportPrinted();
	}
	else
	{
		logger->Debug("Printing error");
		progress->setImage(ProgressWidget::PRINTING_ERROR);
	}

	progress->setText(message);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &ReportInstallWidget::end), 2000);
}

void ReportInstallWidget::onDocumentPrinted(Smartmatic::SAES::Printing::PrintDocumentResult res)
{
	Glib::ustring msg;
	PrintDocumentResult::PrintingResultEnum resultType = PrintDocumentResult::PRINTING_NONE;
	res.getResult(status, msg, resultType);

	message = msg;
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &ReportInstallWidget::showMessagePrinting), 100);
}

bool ReportInstallWidget::getStatus()
{
	return status;
}

std::string ReportInstallWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.InitializationWindow.Title");
}
