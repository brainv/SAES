/*
 * DeviceResultWidget.cxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#include "DeviceResultWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/label-configuration.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* DeviceResultWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.DeviceResultWidget",GETTEXT_PACKAGE);

DeviceResultWidget::DeviceResultWidget(IDiagnosis * diagnosis)
: StepWidget()
{
	this->diagnosis = diagnosis;
	this->mainFrame = NULL;
	this->label = NULL;
	this->image = NULL;

	this->initialize();
	setWidget(mainFrame);
}

DeviceResultWidget::~DeviceResultWidget()
{
	dispose();
}

void DeviceResultWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/DeviceResultWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - DeviceResultWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("label", label);
	builder->get_widget("image", image);

	int labelWidth = SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getDiagnosticReviewWidth();
	int labelHeight = SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getDiagnosticReviewHeight();

	LabelConfiguration labelConf = SAESGUIConfigurationManager::ConvertToLabelConfiguration(
		SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getDiagnosticReviewLabelConfiguration());

	LabelConfiguration::SetLabelConfiguration(label, labelConf);
	label->set_size_request(labelWidth, labelHeight);

	update();
}

void DeviceResultWidget::dispose()
{
	this->remove();

	if (image)
	{
		delete image;
		image = NULL;
	}
	if (label)
	{
		delete label;
		label = NULL;
	}
}

IDiagnosis * DeviceResultWidget::getDiagnosis()
{
	return diagnosis;
}

void DeviceResultWidget::update()
{
	std::string iconFile;
	std::string text;

	switch(diagnosis->getStatus())
	{
		case OperationStatus::Ok:
			iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/Ok_30.png");
			break;
		case OperationStatus::Error:
			iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/Error_30.png");
			break;
		default:
			iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/Interrogation_30.png");
			break;
	}

	switch(diagnosis->getType())
	{
		case OperationStatus::AlarmBox:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.AlarmBoxDevice");
			break;

		case OperationStatus::Barcode:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.BarcodeReader");
			break;

		case OperationStatus::Printer:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.PrinterDevice");
			break;

		case OperationStatus::SmartCard:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.SmartcardReader");
			break;

		case OperationStatus::Flash:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.FlashDevice");
			break;

		case OperationStatus::TouchScreenCalibration:
			text =_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.TouchScreenCalibration");
			break;

		case OperationStatus::ScreenContrast:
			text = _("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.ScreenContrastCalibration");
			break;

		default:
			break;
	}

	image->set(iconFile);
	label->set_text(text);
}
