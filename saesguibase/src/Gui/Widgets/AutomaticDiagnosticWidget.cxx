/*
 * AutomaticDiagnosticWidget.cxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#include "AutomaticDiagnosticWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Configuration/s-a-e-s-functionality-conf-manager.h>
#include <Operation/Diagnosis/AlarmBoxDiagnosis.hxx>
#include <Operation/Diagnosis/BarCodeDiagnosis.hxx>
#include <Operation/Diagnosis/CalibrationDiagnosis.hxx>
#include <Operation/Diagnosis/FlashDiagnosis.hxx>
#include <Operation/Diagnosis/PrinterDiagnosis.hxx>
#include <Operation/Diagnosis/SmartCardReaderDiagnosis.hxx>
#include <Graphics/Encoding2D/QREncoding.h>
#include <System/SafeBuffer.h>
#include <Configuration/label-configuration.h>
#include "AbstractFactoryWidget.hxx"

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
using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::System;
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* AutomaticDiagnosticWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AutomaticDiagnosticWidget",GETTEXT_PACKAGE);

AutomaticDiagnosticWidget::AutomaticDiagnosticWidget(ProgressWidget * progress)
: Smartmatic::GUI::Widgets::StepWidget(), progress(progress)
{
	this->current = 0;
	this->resultWidget = NULL;
	this->diagnosisBlockedWidget = NULL;

	this->initialize();
	this->setWidget(progress);
}

AutomaticDiagnosticWidget::~AutomaticDiagnosticWidget()
{
	dispose();
}

void AutomaticDiagnosticWidget::start()
{
	if (SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getBlockDiagnostic())
	{
		block();
	}
	else
	{
		unblock();
	}
}

void AutomaticDiagnosticWidget::block()
{
	diagnosisBlockedWidget = AbstractFactoryWidget::createDiagnosisBlockedWidget();
	diagnosisBlockedWidget->getSignalClicked().connect(sigc::mem_fun(*this, &AutomaticDiagnosticWidget::unblock));
	this->setWidget(diagnosisBlockedWidget);
}

void AutomaticDiagnosticWidget::unblock()
{
	this->setWidget(progress);
	if(!Glib::thread_supported()) Glib::thread_init();
    Glib::Thread::create(sigc::mem_fun(*this, &AutomaticDiagnosticWidget::diagnostic), false);
}

void AutomaticDiagnosticWidget::initialize()
{
	LabelConfiguration diagConf = SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	progress->setTextConfig(diagConf);

	LabelConfiguration diagFooterConf = SAESGUIConfigurationManager::Current()->getDiagnosisFooterLabelConfiguration();
	progress->setFooterConfig(diagFooterConf);

	if (SAESGUIConfigurationManager::Current()->getShowFooterInAutoDiagnosis())
	{
		progress->showFooter();
	}
	else
	{
		progress->hideFooter();
	}

	progress->setImage(ProgressWidget::NONE);
	progress->setText(" ");
	progress->setFooter(" ");

	std::vector <DiagnosticType> configList = SAESGUIConfigurationManager::Current()->getAutoDiagnosisList();
	std::vector <DiagnosticType>::iterator it;

	for (it = configList.begin();
		 it != configList.end();
		 it++)
	{
		IDiagnosis * interface = NULL;

		switch((*it).getDevice())
		{
			case DiagnosticDevice::CONFIGURATION_ALARMBOX:
				interface = new AlarmBoxDiagnosis();
				interface->setTime(SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getAlarmDiagnosisWaitTime());
				break;

			case DiagnosticDevice::CONFIGURATION_BARCODE:
				interface = new BarCodeDiagnosis(SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getBarcodeCommandsName());
				interface->setTime(SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getBarcodeDiagnosisWaitTime());
				getPixbufBarcode();
				break;

			case DiagnosticDevice::CONFIGURATION_PRINTER:
				interface = new PrinterDiagnosis(SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode(),
						!SAESGUIConfigurationManager::Current()->getDoNotCheckBeforePrintDiagnostic());
				interface->setTime(SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getPrinterDiagnosisWaitTime());
				break;

			case DiagnosticDevice::CONFIGURATION_SMARTCARD:
				interface = new SmartCardReaderDiagnosis();
				interface->setTime(SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getSmartcardDiagnosisWaitTime());
				break;

			case DiagnosticDevice::CONFIGURATION_FLASH:
				interface = new FlashDiagnosis(false);
				interface->setTime(SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getFlashDiagnosisWaitTime());
				break;

			case DiagnosticDevice::CONFIGURATION_TOUCHSCREENCALIBRATION:
				interface = new CalibrationDiagnosis(SAESGUIConfigurationManager::Current()->getTouchScreenCalibrationNumberOfPoints());
				interface->setTime(1000);
				break;

			case DiagnosticDevice::CONFIGURATION_SCREENCONTRAST:
				interface = NULL;
				break;
		}

		if (interface)
		{
			interface->setMandatory((*it).getMandatory());
			diagnosisList.push_back(interface);
			diagnosisConnectionList.push_back(interface->getSignalEnd().connect(sigc::mem_fun(*this, &AutomaticDiagnosticWidget::checkEndDiagnosis)));
		}
	}

	resultWidget = new DiagnosticResultWidget(diagnosisList);
	resultWidget->getSignalEnd().connect(sigc::mem_fun(*this, &AutomaticDiagnosticWidget::end));
}

void AutomaticDiagnosticWidget::dispose()
{
	this->remove();

	std::vector <IDiagnosis *>::iterator it;

	for (it = diagnosisList.begin();
		 it != diagnosisList.end();
		 it++)
	{
		IDiagnosis * obj = (*it);
		if (obj) delete obj;
	}

	diagnosisConnectionList.clear();
	diagnosisList.clear();

	if (progress)
	{
		delete progress;
		progress = NULL;
	}
	if (diagnosisBlockedWidget)
	{
		delete diagnosisBlockedWidget;
		diagnosisBlockedWidget = NULL;
	}
	if (resultWidget)
	{
		delete resultWidget;
		resultWidget = NULL;
	}
}

void AutomaticDiagnosticWidget::end()
{
	Glib::Mutex::Lock lock(mutex);
	dispose();
	signalEnd.emit();
}

void AutomaticDiagnosticWidget::diagnostic()
{
	Glib::Mutex::Lock lock(mutex);

	if (diagnosisList.size() == 0 || diagnosisList.size() == current)
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::showResult), 100);
		return;
	}

	diagnosisList[current]->updateMessage();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::showMessage), 0);
	sleep(1);
	diagnosisList[current]->setStatus(OperationStatus::Run);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::showMessage), 0);
	sleep(1);
	diagnosisList[current]->test();
}

void AutomaticDiagnosticWidget::checkEndDiagnosis()
{
	diagnosisConnectionList[current].disconnect();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::showMessage), 0);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::nextPage), diagnosisList[current]->getTime());
}

void AutomaticDiagnosticWidget::nextPage()
{
	current++;
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &AutomaticDiagnosticWidget::unblock), 0);
}

void AutomaticDiagnosticWidget::showMessage()
{
	switch(diagnosisList[current]->getType())
	{
		case OperationStatus::AlarmBox:
			progress->setImage("ui/alarmButton.jpg");
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::Barcode:
			progress->setImage(pixbuffBarcode);
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::Printer:
			progress->setImage("ui/printer-test-logo-mp.bmp");
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::SmartCard:
			progress->setImage(ProgressWidget::SMARTCARD);
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::Flash:
			progress->setImage("ui/Flash.png");
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::TouchScreenCalibration:
			progress->setImage("ui/calibration.jpg");
			progress->setText(diagnosisList[current]->getMessage());
			progress->setFooter(diagnosisList[current]->getMessageFooter());
			break;

		case OperationStatus::ScreenContrast:
			break;

		default:
			break;
	}
}

void AutomaticDiagnosticWidget::getPixbufBarcode()
{
	std::string data = SAESGUIConfigurationManager::Current()->getBarcodeDiagnosisConfiguration().getStringToEncode();
	SafeBuffer buffer (data);
	QRCodeConfig config = SAESConfigurationManager::Current()->getQRCodeBarcodeConfig();

	int pixelSize = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();

	QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());
	Glib::RefPtr<Gdk::Bitmap> bitmap(QREncoding::GenerateSymbol((guchar*)buffer.GetData(),buffer.GetSize(),pixelSize,margin,correctionLevel,version));

	Glib::RefPtr<Gdk::Drawable> drwptr = bitmap;
	gint width(0);
	gint height(0);
	bitmap->get_size(width,height);

	pixbuffBarcode = Gdk::Pixbuf::create(drwptr,0,0,width,height);
}

void AutomaticDiagnosticWidget::showResult()
{
	this->remove();
	this->add(*resultWidget);
	this->show_all_children();
	resultWidget->start();
}

std::string AutomaticDiagnosticWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.Title");
}
