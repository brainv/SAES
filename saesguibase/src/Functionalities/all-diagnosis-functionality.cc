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

#include <Voting/Status/voting-machine-status-schema.hxx>
#include "Functionalities/all-diagnosis-functionality.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Printing/PrinterStatusNotifier.h>
#include <Operation/MachineOperationManager.hxx>
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

using namespace Smartmatic::Functionality;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;

using namespace std;

ISMTTLog* AllDiagnosisFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality",GETTEXT_PACKAGE);

AllDiagnosisFunctionality* AllDiagnosisFunctionality::current_instance = NULL;

AllDiagnosisFunctionality* AllDiagnosisFunctionality::Current()
{
	if (!current_instance)
		current_instance = new AllDiagnosisFunctionality();

	return current_instance;
};

AllDiagnosisFunctionality::AllDiagnosisFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	alarmWidget = NULL;
	bcreaderWidget = NULL;
	screaderWidget = NULL;
	printerWidget = NULL;
	calibrationWidget = NULL;
	flashWidget = NULL;
	brightnessWidget = NULL;
	framePrincipal = NULL;
	frameResultPrincipal = NULL;
	aligmentResultPrincipal = NULL;
	vbox1 = NULL;
	installationPrintDocument = NULL;
	boxPrincipal = NULL;
	boxContainer = NULL;
	box1 = NULL;
	box2 = NULL;
	labelDevice = NULL;
	imageStatus = NULL;

	startPrint = false;
}

AllDiagnosisFunctionality::~AllDiagnosisFunctionality()
{
	deleteElement();
}

void AllDiagnosisFunctionality::deleteElement()
{
	if (alarmWidget != NULL)
	{
		delete(alarmWidget);
		alarmWidget = NULL;
	}
	if (bcreaderWidget != NULL)
	{
		delete(bcreaderWidget);
		bcreaderWidget = NULL;
	}
	if (screaderWidget != NULL)
	{
		delete(screaderWidget);
		screaderWidget = NULL;
	}
	if (printerWidget != NULL)
	{
		delete(printerWidget);
		printerWidget = NULL;
	}
	if(calibrationWidget != NULL)
	{
		delete(calibrationWidget);
		calibrationWidget = NULL;
	}
	if(flashWidget != NULL)
	{
		delete(flashWidget);
		flashWidget = NULL;
	}
	if(brightnessWidget != NULL)
	{
		delete(brightnessWidget);
		brightnessWidget = NULL;
	}
	if (framePrincipal != NULL)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}

	deleteResultElement();
}

void AllDiagnosisFunctionality::deleteResultElement()
{
	if (frameResultPrincipal != NULL)
	{
		delete(frameResultPrincipal);
		frameResultPrincipal = NULL;
	}
	if (aligmentResultPrincipal != NULL)
	{
		delete(aligmentResultPrincipal);
		aligmentResultPrincipal = NULL;
	}
	if (vbox1 != NULL)
	{
		delete(vbox1 );
		vbox1 = NULL;
	}
	if (boxPrincipal)
	{
		delete boxPrincipal;
		boxPrincipal = NULL;
	}
	if (boxContainer)
	{
		delete boxContainer;
		boxContainer = NULL;
	}
	if (box1)
	{
		delete box1;
		box1 = NULL;
	}
	if (box2)
	{
		delete box2;
		box2 = NULL;
	}
	if (labelDevice)
	{
		delete labelDevice;
		labelDevice = NULL;
	}
	if (imageStatus)
	{
		delete imageStatus;
		imageStatus = NULL;
	}
	if(installationPrintDocument != NULL)
	{
		delete (installationPrintDocument);
		installationPrintDocument = NULL;
	}
}

void AllDiagnosisFunctionality::Initialize()
{
	index = 0;
	vector<Smartmatic::SAES::Configuration::DiagnosticType> listDiagnosis = SAESGUIConfigurationManager::Current()->getAllDiagnosisList();
	listOfDiagnosis.clear();
	for(unsigned int i= 0;i < listDiagnosis.size();i++)
	{
		if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_ALARMBOX)
		{
			listOfDiagnosis.push_back (alarmWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_BARCODE)
		{
			listOfDiagnosis.push_back (bcreaderWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION)
		{
			listOfDiagnosis.push_back (calibrationWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SCREENCONTRAST)
		{
			listOfDiagnosis.push_back (brightnessWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_PRINTER)
		{
			listOfDiagnosis.push_back (printerWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SMARTCARD)
		{
			listOfDiagnosis.push_back (screaderWidget);
		}
		else if(listDiagnosis[i].getDevice() == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_FLASH)
		{
			listOfDiagnosis.push_back (flashWidget);
		}
	}

	connAlarmDiag = alarmWidget->signalContinue_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_AlarmDiagFinished));
	connBCDiag = bcreaderWidget->signalContinue_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_BCDiagFinished));
	connSCDiag = screaderWidget->signalContinue_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_SCDiagFinished));
	connPrinterDiag = printerWidget->signalContinue_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_PrinterDiagFinished));
	connPrinterDiagOnOk = printerWidget->signalOk_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_PrinterDiagFinishedOnOk));
	connPrinterDiagOnCancel = printerWidget->signalCancel_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_PrinterDiagFinishedOnCancel));
	connCalibDiag = calibrationWidget->signalOk_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_CalibrationDiagFinished));
	connBrightnessDiag = brightnessWidget->signalOk_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_BrightnessDiagFinished));
	connFlashDiag = flashWidget->signalContinue_detected.connect( sigc::mem_fun(this, &AllDiagnosisFunctionality::on_FlashDiagFinished));

	listOfDiagnosis[index]->Initialize();

	framePrincipal->set_shadow_type(Gtk::SHADOW_NONE);
	framePrincipal->remove();
	framePrincipal->set_visible (true);
	framePrincipal->add((*listOfDiagnosis[index]));
};

Smartmatic::SAES::Voting::OperationStatus::Diagnostic AllDiagnosisFunctionality::GetTraslatedDevice(Smartmatic::SAES::Configuration::DiagnosticDevice devtype)
{
	Smartmatic::SAES::Voting::OperationStatus::Diagnostic device = Smartmatic::SAES::Voting::OperationStatus::DateTime;

	if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_ALARMBOX)
	{
		device =Smartmatic::SAES::Voting::OperationStatus::AlarmBox;
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_BARCODE)
	{
		device =Smartmatic::SAES::Voting::OperationStatus::Barcode;
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION)
	{
		device=Smartmatic::SAES::Voting::OperationStatus::TouchScreenCalibration;
	}
	else if(devtype== Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SCREENCONTRAST)
	{
		device =Smartmatic::SAES::Voting::OperationStatus::ScreenContrast;
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_PRINTER)
	{
		device =  Smartmatic::SAES::Voting::OperationStatus::Printer;
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SMARTCARD)
	{
		device = Smartmatic::SAES::Voting::OperationStatus::SmartCard;
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_FLASH)
	{
		device = Smartmatic::SAES::Voting::OperationStatus::Flash;
	}
	return device;
}
std::string AllDiagnosisFunctionality::GetTraslatedName (Smartmatic::SAES::Configuration::DiagnosticDevice devtype)
{
	std::string name;
	if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_ALARMBOX)
	{
		name =_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.AlarmBoxDevice");
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_BARCODE)
	{
		name =_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.BarcodeReader");
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION)
	{
		name =_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.TouchScreenCalibration");
	}
	else if(devtype== Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SCREENCONTRAST)
	{
		name = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.ScreenContrastCalibration");
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_PRINTER)
	{
		name =  _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.PrinterDevice");
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_SMARTCARD)
	{
		name = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.SmartcardReader");
	}
	else if(devtype == Smartmatic::SAES::Configuration::DiagnosticDevice::CONFIGURATION_FLASH)
	{
		name = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.FlashDevice");
	}
	return name;
}

void AllDiagnosisFunctionality::convertToReadable(string& deviceName)
{
	if(deviceName.compare("AlarmBox") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.AlarmBoxDevice");
	}
	else if(deviceName.compare("Barcode") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.BarcodeReader");
	}
	else if(deviceName.compare("TouchScreenCalibration") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.TouchScreenCalibration");
	}
	else if(deviceName.compare("ScreenContrast") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.ScreenContrastCalibration");
	}
	else if(deviceName.compare("Printer") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.PrinterDevice");
	}
	else if(deviceName.compare("SmartCard") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.SmartcardReader");
	}
	else if(deviceName.compare("Flash") == 0)
	{
		deviceName = _("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.FlashDevice");
	}
}

void AllDiagnosisFunctionality::showResults()
{
	deleteResultElement();

	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/all-diagnostics-result.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	builder->get_widget("framePrincipal", frameResultPrincipal);
	builder->get_widget("alignmentPrincipal", aligmentResultPrincipal);
	builder->get_widget("vbox1", vbox1 );

	vector<Smartmatic::SAES::Configuration::DiagnosticType> listDiagnosis = SAESGUIConfigurationManager::Current()->getAllDiagnosisList();

	for(unsigned int i = 0;i < listDiagnosis.size();i++)
	{
		Smartmatic::SAES::Configuration::DiagnosticType diag = listDiagnosis[i];

		Glib::ustring devName = GetTraslatedName(diag.getDevice());
		Smartmatic::SAES::Voting::OperationStatus::Diagnostic diagDev = GetTraslatedDevice(diag.getDevice());
		Smartmatic::SAES::Voting::OperationStatus::DiagStatus sta = MachineOperationManager::getInstance()->getOperationStatus()->getDiagnosisStatus(diagDev);

			boxPrincipal = new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,10);
			boxContainer = new Gtk::HBox();
			box1 = new Gtk::Frame();
			box2 = new Gtk::Frame();
			box1->set_shadow_type (Gtk::SHADOW_IN);
			box1->set_border_width (3);
			box2->set_shadow_type (Gtk::SHADOW_IN);
			box2->set_border_width (3);
			boxPrincipal->set_homogeneous (false);
			labelDevice = new Gtk::Label();
			imageStatus = new Gtk::Image();
			labelDevice->set_size_request(300,-1);
			labelDevice->set_label(devName);
			if(sta == Smartmatic::SAES::Voting::OperationStatus::NotDiagnosed)
			{
				imageStatus->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/Interrogation_30.png"));
			}
			else if(sta == Smartmatic::SAES::Voting::OperationStatus::Ok)
			{
				imageStatus->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/Ok_30.png"));
			}
			else if(sta == Smartmatic::SAES::Voting::OperationStatus::Error)
			{
				imageStatus->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/Error_30.png"));
			}
			box1->add(*labelDevice);
			box2->add(*imageStatus);
			boxContainer->add(*box1);
			boxContainer->add(*box2);
			boxPrincipal->add(*boxContainer);
			vbox1->add(*boxPrincipal);
	}
	vbox1->set_visible(true);
	vbox1->show_all_children ();
	framePrincipal->add(*frameResultPrincipal);

	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.AllDiagnosticFinished"));

	try
	{

		PrinterStatusNotifier printerStatusNotifier;
		PrinterStatusNotifier::PhysichalStateEnumType printerState = printerStatusNotifier.getPrinterState();
		if(!startPrint && (printerState & PrinterStatusNotifier::PSTATE_READY))
		{
			startPrint = true;

			if (installationPrintDocument) delete installationPrintDocument;

			installationPrintDocument = new Smartmatic::SAES::Printing::InstallationPrintDocument (MachineOperationManager::getInstance()->getElectoralConfiguration(),false,true);
			installationPrintDocument->setClient(this);
			installationPrintDocument->Print();
		}
		else
		{
			logger->Debug("Error printing result diagnostic");
			enableExitButton();
		}
	}
	catch(exception & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.ErrorPrintingReport"));
		enableExitButton();
	}
	catch(...)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__;
        logger->Debug(ss.str());
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.ErrorPrintingReport"));
		enableExitButton();
	}
}

//Report printed
void AllDiagnosisFunctionality::onDocumentPrinted ( Smartmatic::SAES::Printing:: PrintDocumentResult res)
{
	bool printResult = false;
	Glib::ustring msg;
	PrintDocumentResult::PrintingResultEnum resultType = PrintDocumentResult::PRINTING_NONE;
	res.getResult(printResult, msg, resultType);

	if(printResult)
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.DiagnosticReportPrintedLogKey"));
	}
	else
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.DiagnosticReportPrintFailedLogKey"));
	}

	startPrint = false;
	Glib::signal_timeout().connect_once (sigc::mem_fun(*this , &AllDiagnosisFunctionality::enableExitButton), 100);
}

bool AllDiagnosisFunctionality::RefreshCalib(int time_num)
{
	calibrationWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}

	return false;
}

bool AllDiagnosisFunctionality::RefreshAlarm(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisAlarmWaitTime());
	alarmWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}

	return false;
}

bool AllDiagnosisFunctionality::RefreshBC(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisBarcodeWaitTime());
	bcreaderWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}

	return false;
}
bool AllDiagnosisFunctionality::RefreshPrinter(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisPrinterWaitTime());
	SetPrinterWidget();
	return false;
}

bool AllDiagnosisFunctionality::RefreshPrinterOnOk(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisPrinterWaitTimeOnOk());
	SetPrinterWidget();
	return false;
}

bool AllDiagnosisFunctionality::RefreshPrinterOnCancel(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisPrinterWaitTimeOnCancel());
	SetPrinterWidget();
	return false;
}

void AllDiagnosisFunctionality::SetPrinterWidget()
{
	printerWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}
}

bool AllDiagnosisFunctionality::RefreshSC(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisSmartcardWaitTime());
	screaderWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}
	return false;
}


bool AllDiagnosisFunctionality::RefreshBrightness(int time_num)
{
	brightnessWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}
	return false;
}

bool AllDiagnosisFunctionality::RefreshFlash(int time_num)
{
	sleep(SAESGUIConfigurationManager::Current()->getAllDiagnosisFlashWaitTime());
	flashWidget->Dispose();
	framePrincipal->remove();
	if(index < listOfDiagnosis.size()-1)
	{
		index++;
		listOfDiagnosis[index]->Initialize();
		framePrincipal->add((*listOfDiagnosis[index]));
	}
	else
	{
		showResults();
	}
	return false;
}


void AllDiagnosisFunctionality::on_AlarmDiagFinished()
{
	sigc::slot<bool> my_slot1 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshAlarm), 0);
	connRefreshAlarm = Glib::signal_timeout().connect(my_slot1,1500);
}

void AllDiagnosisFunctionality::on_BCDiagFinished()
{

	sigc::slot<bool> my_slot2 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshBC), 0);
	connRefreshBC = Glib::signal_timeout().connect(my_slot2,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.BarCodeDiagnosisFinished"));
}

void AllDiagnosisFunctionality::on_SCDiagFinished()
{

	sigc::slot<bool> my_slot3 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshSC), 0);
	connRefreshSC = Glib::signal_timeout().connect(my_slot3,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.SmartcardReaderDiagnosisFinished"));
}

void AllDiagnosisFunctionality::on_PrinterDiagFinished()
{

	sigc::slot<bool> my_slot4 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshPrinter), 0);
	connRefreshPrinter = Glib::signal_timeout().connect(my_slot4,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.PrinterFinished"));
}

void AllDiagnosisFunctionality::on_PrinterDiagFinishedOnOk()
{

	sigc::slot<bool> my_slot5 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshPrinterOnOk), 0);
	connRefreshPrinterOnOk = Glib::signal_timeout().connect(my_slot5,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.PrinterFinishedOk"));
}

void AllDiagnosisFunctionality::on_PrinterDiagFinishedOnCancel()
{
	sigc::slot<bool> my_slot6 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshPrinterOnCancel), 0);
	connRefreshPrinterOnCancel = Glib::signal_timeout().connect(my_slot6,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.PrinterFinishedError"));
}

void AllDiagnosisFunctionality::on_CalibrationDiagFinished()
{

	sigc::slot<bool> my_slot7 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshCalib), 0);
	connRefreshCalib = Glib::signal_timeout().connect(my_slot7,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.CalibrationDiagnosisFinished"));
}

void AllDiagnosisFunctionality::on_FlashDiagFinished()
{

	sigc::slot<bool> my_slot8 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshFlash), 0);
	connRefreshFlash = Glib::signal_timeout().connect(my_slot8,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.FlashDiagnosisFinished"));
}

void AllDiagnosisFunctionality::on_BrightnessDiagFinished()
{
	sigc::slot<bool> my_slot9 = sigc::bind(sigc::mem_fun(*this,
			   &AllDiagnosisFunctionality::RefreshBrightness), 0);
	connRefreshBrightness = Glib::signal_timeout().connect(my_slot9,1500);
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.BrightnessDiagnosisFinished"));
}

Gtk::Widget* AllDiagnosisFunctionality::GetFrame()
{
	startPrint = false;

	framePrincipal = new Gtk::Frame();
	framePrincipal->set_shadow_type(Gtk::SHADOW_NONE);
	alarmWidget = new Smartmatic::SAES::GUI::Widgets::AlarmBoxDiagnosisWidget("",false, false, false,false);
	bcreaderWidget = new Smartmatic::SAES::GUI::Widgets::BarCodeDiagnosisWidget("",false, false, false,false);
	bcreaderWidget->HideRetryButton();
	calibrationWidget = new Smartmatic::SAES::GUI::Widgets::CalibrationDiagnosisWidget("",false, false, false,false,false);
	screaderWidget = new Smartmatic::SAES::GUI::Widgets::SmartCardReaderDiagnosisWidget("",false, false, false,false);
	printerWidget = new Smartmatic::SAES::GUI::Widgets::PrinterDiagnosisWidget("",false, false, false,true);
	brightnessWidget = new Smartmatic::SAES::GUI::Widgets::BrightnessDiagnosisWidget("",false, false, false,false);
	flashWidget = new Smartmatic::SAES::GUI::Widgets::FlashDiagnosisWidget("",false, false, false,false);
	return framePrincipal;
};

string AllDiagnosisFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.AllDiagnosis");
};

MenuOptionDescriptor AllDiagnosisFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MAllDiagnosisFunctionality,false);
};

void AllDiagnosisFunctionality::Dispose()
{
	startPrint = false;

	connRefreshAlarm.disconnect();
	connRefreshPrinter.disconnect();
	connRefreshPrinterOnOk.disconnect();
	connRefreshPrinterOnCancel.disconnect();
	connRefreshCalib.disconnect();
	connRefreshBC.disconnect();
	connRefreshSC.disconnect();
	connRefreshFlash.disconnect();
	connRefreshBrightness.disconnect();
	
	connAlarmDiag.disconnect();
	connBCDiag.disconnect();
	connSCDiag.disconnect();
	connCalibDiag.disconnect();
	connPrinterDiag.disconnect();
	connPrinterDiagOnOk.disconnect();
	connPrinterDiagOnCancel.disconnect();
	connBrightnessDiag.disconnect();
	connFlashDiag.disconnect();
};

Smartmatic::Log::ISMTTLog* AllDiagnosisFunctionality::getLogger()
{
	return logger;
}
Glib::ustring AllDiagnosisFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.LogStartFunctionality");
}

Glib::ustring AllDiagnosisFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.AllDiagnosisFunctionality.LogCloseFunctionality");
}
