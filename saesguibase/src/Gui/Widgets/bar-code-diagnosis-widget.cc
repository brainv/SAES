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

#include "bar-code-diagnosis-widget.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Printing/PrinterStatusNotifier.h"
#include "Devices/barcode-device.h"
#include "Configuration/label-configuration.h"
#include "Printing/LPSpooler.h"
#include "Printing/DocumentOptions.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Graphics/Encoding2D/QREncoding.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <stdio.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Operation;

Smartmatic::Log::ISMTTLog* BarCodeDiagnosisWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget",GETTEXT_PACKAGE);

BarCodeDiagnosisWidget::BarCodeDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
: BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::Barcode, hasOk,hasCancel,hasMessage,showButtons)
{
	framePrincipal= NULL;
	labelResult = NULL;
	imageBarcodeReader = NULL;
	buttonReconfigure=NULL;
	button_back_reconfigure=NULL;
	automaticPrint = false;
	hideRetryButton = false;
	barcodePrinting = new BarcodePrinting(SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode());

	commandsInBarcode = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getBarcodeInParams();
	commandsOutBarcode = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getBarcodeOutParams();
	commandsReconfigure = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getBarcodeCommandsName();
}

BarCodeDiagnosisWidget::~BarCodeDiagnosisWidget()
{
	remove();

	if(framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(imageBarcodeReader != NULL)
	{
		delete(imageBarcodeReader);
		imageBarcodeReader = NULL;
	}
	if(labelResult != NULL)
	{
		delete(labelResult);
		labelResult = NULL;
	}
	if(buttonReconfigure != NULL)
	{
		delete(buttonReconfigure);
		buttonReconfigure = NULL;
	}
	if(button_back_reconfigure != NULL)
	{
		delete(button_back_reconfigure);
		button_back_reconfigure = NULL;
	}
	if (barcodePrinting)
	{
		delete barcodePrinting;
		barcodePrinting = NULL;
	}
}

void BarCodeDiagnosisWidget::Initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barcode-diagnostic.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - BarCodeDiagnosisWidget Initialize");
	}
	framePrincipal = NULL;
	labelResult = NULL;
	imageBarcodeReader = NULL;
	buttonReconfigure= NULL;
	button_back_reconfigure=new Smartmatic::GUI::Widgets::SmartmaticButton();
	alignment1=NULL;

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("labelResult", labelResult);
	builder->get_widget("imageBarcodeReader", imageBarcodeReader);
	builder->get_widget_derived("buttonReconfigure",buttonReconfigure);
	//builder->get_widget_derived("button_back_reconfigure",button_back_reconfigure);
	builder->get_widget("alignment1",alignment1);

	buttonReconfigure->signal_clicked().connect(sigc::mem_fun(this, &BarCodeDiagnosisWidget::on_buttonReconfigure_clicked));
	buttonReconfigure->set_visible (false);
	buttonReconfigure->set_size_request(300,70);
	buttonReconfigure->SetLabel("");

	button_back_reconfigure->signal_clicked().connect(sigc::mem_fun(this, &BarCodeDiagnosisWidget::on_button_back_reconfigure_clicked));
	button_back_reconfigure->set_visible (false);
	button_back_reconfigure->set_size_request(300,70);
	button_back_reconfigure->SetLabel("");

	//imageBarcodeReader->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barCodeReader.jpg"));
	Glib::ustring toEncode (SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode());
	gint buffersize = toEncode.bytes();
	gchar* raw(NULL);
	raw = static_cast<gchar*>( g_malloc (buffersize));
	toEncode.copy(raw,buffersize);

	Smartmatic::SAES::Configuration::QRCodeConfig config =
			Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getQRCodeBarcodeConfig();

	int pixelSize = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();

	QRecLevel correctionLevel = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());
	Glib::RefPtr<Gdk::Bitmap> bitmap(Smartmatic::Graphics::Encoding2D::QREncoding::GenerateSymbol((guchar*)raw,buffersize,pixelSize,margin,correctionLevel,version));

	g_free(raw);

	Glib::RefPtr<Gdk::Drawable> drwptr = bitmap;
	gint width(0);
	gint height(0);
	bitmap->get_size(width,height);
	pixBuffBarcode =  Gdk::Pixbuf::create(drwptr,0,0,width,height);
	imageBarcodeReader->set(pixBuffBarcode);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.Empty"));


	LabelConfiguration diagConf =  SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(labelResult, diagConf);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.InitializingDiagnostic"));

	setDiagnosticFrame(*framePrincipal);
	success = false;

	if(!BarcodeDevice::Current()->sendPing())
	{
		BarcodeDevice::Current()->Resync();
	}

	timeoutCounter = 0;
	TimeOutFinal = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getTimeOut();
	automaticPrint = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getPrintAutomaticBarcode();

	sendCommandIn();

	buttonReconfigure->set_no_show_all(true);
	button_back_reconfigure->set_no_show_all(true);

	if(!automaticPrint)
	{
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &BarCodeDiagnosisWidget::SendTest), 2000);
	}
}

void BarCodeDiagnosisWidget::PrintBarcode()
{
	bool skipPrinterError = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getSkipPrinterError();

	if(CheckPrinter())
	{
		m_type_printing_signal.emit(true);
		connReceived.disconnect();
		barcodePrinting->setClient (this);
		barcodePrinting->Print();
	}
	else if (skipPrinterError)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.CheckConfigurationPrinterPleaseScanThePrintedBarcode"));
		Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &BarCodeDiagnosisWidget::SendTest), 2000);
	}
}

void BarCodeDiagnosisWidget::onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res)
{
	connReceived.disconnect();
	connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::RecievedData));

	m_type_printing_signal.emit(false);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.PleaseScanThePrintedBarcodeOrTheScreenBarcode"));

	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &BarCodeDiagnosisWidget::SendTest), 2000);
}

BarCodeDiagnosisWidget::type_printing_signal BarCodeDiagnosisWidget::signal_printing()
{
	return m_type_printing_signal;
}

void BarCodeDiagnosisWidget::RecievedData(Smartmatic::System::SafeBuffer * recieved)
{
	if(recieved != NULL && recieved->GetData() != NULL)
	{
		string recievedData;
		recievedData.assign((const char*)recieved->GetData(), recieved->GetSize());
		recievedData.resize(recieved->GetSize());
		delete recieved;

		if(recievedData == (SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode().substr(0, recievedData.size())))
		{
			success = true;
		}
		connReceived.disconnect();

		connRefreshTimeout.disconnect();

		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
				   &BarCodeDiagnosisWidget::Refresh), 0);
		connRefresh = Glib::signal_timeout().connect(my_slot,1000);
	}
}

void BarCodeDiagnosisWidget::HideRetryButton()
{
	hideRetryButton = true;
}

void BarCodeDiagnosisWidget::CommandsSent(bool commandsOk)
{
	connCommandSend.disconnect();
	m_type_printing_signal.emit(false);

	if(commandsOk)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::Initialize), 100);
	}
	else
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.CouldNotReachBarcodeReaderDiagnosticFailed"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Barcode, OperationStatus::Error);
	}
}

void BarCodeDiagnosisWidget::SendTest()
{
	if(BarcodeDevice::Current()->sendPing())
	{
		connReceived.disconnect();
		connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::RecievedData));

		if(!automaticPrint)
		{
			labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.PleaseScanTheBarcodeShowedOnScreen"));
		}

		sigc::slot<bool> my_slot4 = sigc::bind(sigc::mem_fun(*this,
		   &BarCodeDiagnosisWidget::RefreshTimeout), 0);
		connRefreshTimeout = Glib::signal_timeout().connect(my_slot4,1000);
	}
	else
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.CouldNotReachBarcodeReaderDiagnosticFailed"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Barcode, OperationStatus::Error);
		sendCommandOut();
	}
}

bool BarCodeDiagnosisWidget::RefreshTimeout(int timer_num)
{
	timeoutCounter++;
	if(timeoutCounter == TimeOutFinal && !success)
	{
		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
				   &BarCodeDiagnosisWidget::Refresh), 0);
		connRefresh = Glib::signal_timeout().connect(my_slot,1000);
		return false;
	}
	return true;
}

bool BarCodeDiagnosisWidget::Refresh(int time_num)
{
	if(success)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.DiagnosticSuccessful"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Barcode, OperationStatus::Ok);
		buttonReconfigure->set_visible(false);
	}
	else
	{

		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.DiagnosticFailed"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::Barcode, OperationStatus::Error);
		if(!hideRetryButton)
			buttonReconfigure->set_visible(true);
		buttonReconfigure->set_label (_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.ReconfigureDevice"));

	}

	sendCommandOut();
	return false;
}

void BarCodeDiagnosisWidget::PrintPDF()
{
	m_type_printing_signal.emit(true);

	if(CheckPrinter())
	{
		connReceived.disconnect();
		barcodeConfigPrinting.Print();

		connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::RecievedData));

		m_type_printing_signal.emit(false);

		labelResult->set_text(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.TestAgainBarcodeReader"));
		button_back_reconfigure->set_label (_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.TestAgainBarcodeReaderButton"));
		alignment1->remove();
		alignment1->add(*button_back_reconfigure);
		button_back_reconfigure->set_visible (true);
	}
	else
	{
		m_type_printing_signal.emit(false);
	}
}

void  BarCodeDiagnosisWidget::on_buttonReconfigure_clicked()
{
	buttonReconfigure->set_sensitive(false);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::PrintPDF), 100);
}

void  BarCodeDiagnosisWidget::ReconfigureBarcode()
{
	labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.ReconfigureBarcode"));

	m_type_printing_signal.emit(true);

	if(!BarcodeDevice::Current()->sendPing())
	{
		BarcodeDevice::Current()->Resync();
	}

	connCommandSend.disconnect();
	connCommandSend = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::CommandsSent));

	BarcodeDevice::Current()->SendConfigurationCommands(commandsReconfigure,true,false);
}

void  BarCodeDiagnosisWidget::on_button_back_reconfigure_clicked()
{
	button_back_reconfigure->hide();
	connReceived.disconnect();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::ReconfigureBarcode), 100);
}

bool BarCodeDiagnosisWidget::CheckPrinter()
{
	bool validate = false;

	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	if ( ( printerState & printNotifier.getErrorCondition () ) != 0 )
	{
		std::string errorMessage = printNotifier.getStatusMessage (printerState);
		labelResult->set_label(errorMessage);
	}
	else
	{
		validate = true;
	}

	return validate;
}

void BarCodeDiagnosisWidget::Dispose()
{
	BarcodeDevice::Current()->Close();
	connReceived.disconnect();
	connRefresh.disconnect();
	connRefreshTimeout.disconnect();
	connCommandSend.disconnect();
}

void BarCodeDiagnosisWidget::printBarcode()
{
	if(automaticPrint)
	{
		logger->Debug("print barcode");
		labelResult->set_label(_("Smartmatic.SAES.GUI.Widgets.BarCodeDiagnosisWidget.WaitForBarcodeToBePrinted"));
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::PrintBarcode), 500);
	}
}

void BarCodeDiagnosisWidget::sendCommandIn()
{
	if (BarcodeDevice::Current()->sendPing() && commandsInBarcode.empty())
	{
		logger->Debug("Send command in");
		connCommandIn.disconnect();
		connCommandIn = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::endSendCommandIn));
		BarcodeDevice::Current()->SendConfigurationCommands(commandsInBarcode,true,false);
	}
	else
	{
		printBarcode();
	}
}

void BarCodeDiagnosisWidget::sendCommandOut()
{
	if (BarcodeDevice::Current()->sendPing() && !commandsOutBarcode.empty())
	{
		logger->Debug("Send command out");
		connCommandOut.disconnect();
		connCommandOut = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &BarCodeDiagnosisWidget::endSendCommandOut));
		BarcodeDevice::Current()->SendConfigurationCommands(commandsOutBarcode,true,true);
	}
	else
	{
		end();
	}
}

void BarCodeDiagnosisWidget::endSendCommandIn(bool commandsOk)
{
	connCommandIn.disconnect();
	printBarcode();
}

void BarCodeDiagnosisWidget::endSendCommandOut(bool commandsOk)
{
	connCommandOut.disconnect();
	end();
}

void BarCodeDiagnosisWidget::end()
{
	logger->Debug("End diagnosis");
	Dispose();
	signalContinue_detected.emit();
}
