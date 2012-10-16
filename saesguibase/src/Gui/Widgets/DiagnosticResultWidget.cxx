/*
 * DiagnosticResultWidget.cxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#include "DiagnosticResultWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::Log;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::System::Runtime;

ISMTTLog* DiagnosticResultWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.DiagnosticResultWidget",GETTEXT_PACKAGE);

DiagnosticResultWidget::DiagnosticResultWidget(std::vector <IDiagnosis *> & diagnosis)
: StepWidget(), diagnosis(diagnosis)
{
	this->mainFrame = NULL;
	this->mainVbox = NULL;
	this->centerVbox = NULL;
	this->buttonbox = NULL;
	this->actionButton = NULL;
	this->infoLabel = NULL;
	this->mandatoryFail = false;
	this->centerFrame = NULL;
	this->centerVbox = NULL;
	this->centerHbox = NULL;

	this->initialize();
	setWidget(mainFrame);
}

DiagnosticResultWidget::~DiagnosticResultWidget()
{
	dispose();
}

void DiagnosticResultWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/DiagnosticResultWidget.glade");
	iconFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/PM_pass.gif");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ContingencyWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("main-vbox", mainVbox);
	builder->get_widget("center-frame", centerFrame);
	builder->get_widget("center-vbox", centerVbox);
	builder->get_widget("center-hbox", centerHbox);
	builder->get_widget("vbuttonbox", buttonbox);
	builder->get_widget("info-label", infoLabel);
	builder->get_widget_derived("action-button", actionButton);

	std::vector <IDiagnosis *>::iterator it;

	for (it = diagnosis.begin();
		 it != diagnosis.end();
		 it++)
	{
		DeviceResultWidget * widget = new DeviceResultWidget(*it);
		deviceList.push_back(widget);
		centerVbox->add(*widget);
	}

	LabelConfiguration diagConf = SAESGUIConfigurationManager::Current()->getResultErrorLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(infoLabel, diagConf);

	infoLabel->set_visible(false);
	infoLabel->set_no_show_all(true);
}

void DiagnosticResultWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (mainVbox)
	{
		delete mainVbox;
		mainVbox = NULL;
	}
	if (centerFrame)
	{
		delete centerFrame;
		centerFrame = NULL;
	}
	if (centerHbox)
	{
		delete centerHbox;
		centerHbox = NULL;
	}
	if (centerVbox)
	{
		delete centerVbox;
		centerVbox = NULL;
	}
	if (actionButton)
	{
		delete actionButton;
		actionButton = NULL;
	}
	if (buttonbox)
	{
		delete buttonbox;
		buttonbox = NULL;
	}
	if (infoLabel)
	{
		delete infoLabel;
		infoLabel = NULL;
	}

	std::list < DeviceResultWidget * >::iterator it;

	for (it = deviceList.begin();
		 it != deviceList.end();
		 it++)
	{
		DeviceResultWidget * widget = (*it);
		delete widget;
	}
}

void DiagnosticResultWidget::start()
{
	std::list < DeviceResultWidget * >::iterator it;
	bool fail = false;
	mandatoryFail = false;

	for (it = deviceList.begin();
		 it != deviceList.end();
		 it++)
	{
		DeviceResultWidget * widget = (*it);
		IDiagnosis * interface = widget->getDiagnosis();

		widget->update();

		if (interface->getStatus() == OperationStatus::Error)
		{
			fail = true;

			if (interface->getMandatory())
			{
				mandatoryFail = true;
			}
		}
	}

	bool useOkButtonFailed = SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getUseOkButtonOnSomeNonMandatoryDiagnosticFailed();
	bool useShutDownButtonMandatoryFailed = SAESGUIConfigurationManager::Current()->GetAutomaticWindowConfiguration().getUseShutDownButtonOnSomeMandatoryDiagnosticFailed();

	if(fail && !mandatoryFail && useOkButtonFailed == true)
	{
		actionButton->set_label(_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.DiagnosticWithErrorFailedButtonText"));
		actionButton->signal_clicked().connect(sigc::mem_fun(*this, &DiagnosticResultWidget::end));
	}
	else if (mandatoryFail)
	{
		actionButton->set_label(_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.ButtonShutDown"));
		actionButton->signal_clicked().connect(sigc::mem_fun(*this, &DiagnosticResultWidget::shutDown));

		if (useShutDownButtonMandatoryFailed)
		{
			infoLabel->set_visible(true);
			infoLabel->set_text(_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.HardwareDiagnosticFailedText"));
		}
		else
		{
			actionButton->set_visible(false);
			buttonbox->remove(*actionButton);
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &DiagnosticResultWidget::fail), 5000);
		}
	}
	else
	{
		actionButton->set_visible(false);
		buttonbox->remove(*actionButton);
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &DiagnosticResultWidget::end), 5000);
	}
}

void DiagnosticResultWidget::shutDown()
{
	std::string commandShut = "powerdown &";
	(void)ProcessLauncher::RunProcessThroughSystem(commandShut.c_str());
}

void DiagnosticResultWidget::fail()
{
	centerFrame->remove();

	Gtk::Image * imagePen = manage(new Gtk::Image());
	imagePen->set(Gdk::PixbufAnimation::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/AutoDiagnosticFailed.img")));

	infoLabel->set_visible(true);
	infoLabel->set_text(_("Smartmatic.SAES.GUI.Windows.AutomaticDiagnosticWindow.HardwareDiagnosticFailedText"));

	actionButton->set_visible(true);
	buttonbox->add(*actionButton);
	centerFrame->add(*imagePen);
	centerFrame->show_all_children();
}

void DiagnosticResultWidget::end()
{
	signalEnd.emit();
}
