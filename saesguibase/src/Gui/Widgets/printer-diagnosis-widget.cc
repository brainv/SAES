/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "printer-diagnosis-widget.h"
#include "Configuration/label-configuration.h"
#include "Printing/PrintDocumentResult.h"
#include "Printing/PrinterStatusNotifier.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Graphics/Encoding2D/QREncoding.h>

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
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting;	
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Diagnosis;

PrinterDiagnosisWidget::PrinterDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
: BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::Printer, hasOk,hasCancel,hasMessage, showButtons)
{
	framePrincipal = NULL;
	imagePrint = NULL;
	labelAllInfo = NULL;

	std::string encode = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode();
	bool checkPrinter = !SAESGUIConfigurationManager::Current()->getDoNotCheckBeforePrintDiagnostic();

	diagnosis = new PrinterDiagnosis(encode, checkPrinter);
	diagnosis->getSignalEnd().connect(sigc::mem_fun(*this, &PrinterDiagnosisWidget::checkEndDiagnosis));
}

PrinterDiagnosisWidget::~PrinterDiagnosisWidget()
{
	remove();

	if(framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(imagePrint != NULL)
	{
		delete(imagePrint);
		imagePrint = NULL;
	}
	if(labelAllInfo != NULL)
	{
		delete(labelAllInfo);
		imagePrint = NULL;
	}
	if (diagnosis)
	{
		delete diagnosis;
		diagnosis = NULL;
	}
}

void PrinterDiagnosisWidget::Initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-diagnostic.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	framePrincipal = NULL;
	labelAllInfo = NULL;
	imagePrint = NULL;

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("labelAllInfo", labelAllInfo);
	builder->get_widget("imagePrint", imagePrint);

	LaunchConfiguration& launchConfig(SAESFunctionalityConfigurationManager::Current()->getLaunchConfiguration());
	AppType  apptoLaunch= launchConfig.getAppType();

	//imagePrint->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-test-logo.bmp"));
	if(apptoLaunch == AppType::CONFIGURATION_VOTINGONLY)
	{
		imagePrint->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-test-logo-mv.bmp"));
	}
	else
	{
		imagePrint->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-test-logo-mp.bmp"));
	}

	LabelConfiguration diagConf =  SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(labelAllInfo, diagConf);

	diagnosis->setStatus(OperationStatus::NotDiagnosed);
	labelAllInfo->set_label(diagnosis->getMessage());

	setDiagnosticFrame(*framePrincipal);
	connCancel = this->signalCancel_detected.connect( sigc::mem_fun(this, &PrinterDiagnosisWidget::on_signalCancel));
	connOk = this->signalOk_detected.connect( sigc::mem_fun(this, &PrinterDiagnosisWidget::on_signalOk));
	setCancelButtonLabel(_("Smartmatic.SAES.GUI.Widgets.PrinterDiagnosisWidget.Error"));
	setOkButtonSensitive(false);
	setCancelButtonSensitive(false);

	int buttonWidth = SAESGUIConfigurationManager::Current()->getPrinterDiagnosisConfiguration().getButtonsWidth();
	int buttonHeight = SAESGUIConfigurationManager::Current()->getPrinterDiagnosisConfiguration().getButtonsHeight();
	int buttonFontSize = SAESGUIConfigurationManager::Current()->getPrinterDiagnosisConfiguration().getButtonsFontSize();

	okButton.set_size_request (buttonWidth, buttonHeight);
	okButton.ModifyFontSize(buttonFontSize);

	cancelButton.set_size_request (buttonWidth, buttonHeight);
	cancelButton.ModifyFontSize(buttonFontSize);

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PrinterDiagnosisWidget::SendTest), 1000);
};

void PrinterDiagnosisWidget::on_signalCancel()
{
	labelAllInfo->set_label(_("Smartmatic.SAES.GUI.Widgets.PrinterDiagnosisWidget.DiagnosticFailed"));
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Printer, OperationStatus::Error);
}

void PrinterDiagnosisWidget::on_signalOk()
{
	labelAllInfo->set_label(_("Smartmatic.SAES.GUI.Widgets.PrinterDiagnosisWidget.DiagnosticSuccessful"));
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Printer, OperationStatus::Ok);
}

void PrinterDiagnosisWidget::SendTest()
{
	diagnosis->setStatus(OperationStatus::Run);
	labelAllInfo->set_label(diagnosis->getMessage());
	diagnosis->test();
}

void PrinterDiagnosisWidget::checkEndDiagnosis ()
{
	m_PrintSuccess = diagnosis->getStatus() == OperationStatus::Ok;

	if(m_PrintSuccess)
	{
		setOkButtonSensitive(true);
		setCancelButtonSensitive(true);
		labelAllInfo->set_label(_("Smartmatic.SAES.GUI.Widgets.PrinterDiagnosisWidget.PressButtonAccordingResult"));
	}
	else
	{
		labelAllInfo->set_label(diagnosis->getMessage());
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PrinterDiagnosisWidget::EmitContinueSignal), 4000);
	}
}

void PrinterDiagnosisWidget::EmitContinueSignal()
{
	signalContinue_detected.emit();
}

bool PrinterDiagnosisWidget::Refresh(int time_num)
{
	if(!m_PrintSuccess)
	{
		labelAllInfo->set_label(diagnosis->getMessage());
		signalContinue_detected.emit();
	}
	else
	{
		setOkButtonSensitive(true);
		setCancelButtonSensitive(true);
		labelAllInfo->set_label(_("Smartmatic.SAES.GUI.Widgets.PrinterDiagnosisWidget.PressButtonAccordingResult"));
	}
	return false;
}


void PrinterDiagnosisWidget::Dispose()
{
	connOk.disconnect();
}
