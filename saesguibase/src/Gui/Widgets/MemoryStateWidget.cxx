/**
 * @file MemoryStateWidget.cxx
 * @brief Body class memory state widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#include "MemoryStateWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <System/Runtime/ProcessLauncher.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Environment/Configurations/base-language-controller.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::System::Runtime;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* MemoryStateWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.MemoryStateWidget",GETTEXT_PACKAGE);

MemoryStateWidget::MemoryStateWidget(ProgressWidget * progress)
: StepWidget(), progress(progress)
{
	mainEventBox = NULL;
	memoryVBox = NULL;
	progressEventBox = NULL;
	shutdownHBox = NULL;
	shutdownButton = NULL;

	initialize();
	setWidget(mainEventBox);

	conn = MachineOperationManager::getInstance()->signalMemoryEvent.connect(sigc::mem_fun(*this, &MemoryStateWidget::processMemoryState));
}

MemoryStateWidget::~MemoryStateWidget()
{
	dispose();
}

void MemoryStateWidget::initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/MemoryStateWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - MemoryStateWidget Initialize");
	}

	builder->get_widget("memory-eventbox", mainEventBox);
	builder->get_widget("memory-vbox", memoryVBox);
	builder->get_widget("progress-eventbox", progressEventBox);
	builder->get_widget("shutdown-hbox", shutdownHBox);
	builder->get_widget_derived("shutdown-button", shutdownButton);

	shutdownHBox->set_no_show_all();
	shutdownButton->set_no_show_all();

	progressEventBox->add(*progress);
	progressEventBox->show_all_children();

	int fontSize = SAESGUIConfigurationManager::Current ()->getMemoryStateWidgetConfiguration().getButtonConf().getFontSize();
	int widthB = SAESGUIConfigurationManager::Current ()->getMemoryStateWidgetConfiguration().getButtonConf().getButtonWidth();
	int heightB = SAESGUIConfigurationManager::Current ()->getMemoryStateWidgetConfiguration().getButtonConf().getButtonHeight();

	LabelConfiguration textConf = SAESGUIConfigurationManager::Current()->getMemoryStateWidgetTextConfiguration();
	progress->setTextConfig(textConf);

	shutdownHBox->hide();
	shutdownButton->ModifyFontSize (fontSize);
	shutdownButton->set_size_request (widthB, heightB);
}

void MemoryStateWidget::dispose()
{
	conn.disconnect();

	this->remove();

	if (mainEventBox)
	{
		delete mainEventBox;
		mainEventBox = NULL;
	}
	if (memoryVBox)
	{
		delete memoryVBox;
		memoryVBox = NULL;
	}
	if (progressEventBox)
	{
		delete progressEventBox;
		progressEventBox = NULL;
	}
	if (shutdownHBox)
	{
		delete shutdownHBox;
		shutdownHBox = NULL;
	}
	if (shutdownButton)
	{
		delete shutdownButton;
		shutdownButton = NULL;
	}
	if (progress)
	{
		delete progress;
		progress = NULL;
	}
}

void MemoryStateWidget::refresh()
{

}

std::string MemoryStateWidget::getTitleText()
{
	std::string tr = _(StepWidget::getTitleText().c_str());
	return ((StepWidget::getTitleText() != tr && BaseLanguageController::setLanguage) ? tr : " ");
}

void MemoryStateWidget::processMemoryState(MachineOperationManager::MemoryEvent memoryEvent, MachineOperationManager::MemoryBehavior memoryBehavior)
{
	this->memoryEvent = memoryEvent;
	this->memoryBehavior = memoryBehavior;
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MemoryStateWidget::getMemoryState), 0);
   	usleep(250000);
}

void MemoryStateWidget::getMemoryState()
{
	Glib::Mutex::Lock lock(mutex);

	logger->Debug("Signal Block");
	signalBlock.emit();

	{
		std::stringstream ss;
		ss << "Get Signal ";

		switch(memoryEvent)
		{
			case MachineOperationManager::ONE_MEMORY:
				ss << "ONE_MEMORY";
				break;
			case MachineOperationManager::TWO_MEMORY:
				ss << "TWO_MEMORY";
				break;
			case MachineOperationManager::CHECK_MEMORY_OK:
				ss << "CHECK_MEMORY_OK";
				break;
			case MachineOperationManager::CHECK_MEMORY_ERROR:
				ss << "CHECK_MEMORY_ERROR";
				break;
			case MachineOperationManager::ERROR_MEMORY:
				ss << "ERROR_MEMORY";
				break;
		}

		logger->Debug(ss.str());
	}

	{
		std::stringstream ss;
		ss << "Memory Behavior ";

		switch(memoryBehavior)
		{
			case MachineOperationManager::MemoryBehavior_Allow:
				ss << "Allow";
				break;
			case MachineOperationManager::MemoryBehavior_Suspend:
				ss << "Suspend";
				break;
			case MachineOperationManager::MemoryBehavior_Block:
				ss << "Block";
				break;
		}

		logger->Debug(ss.str());
	}

	switch(memoryEvent)
	{
	case MachineOperationManager::ONE_MEMORY:
		switch(memoryBehavior)
		{
		case MachineOperationManager::MemoryBehavior_Allow:

			setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.AllowWindowTitle"));
			labelKey = N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.AllowWindowInstruction");
			image = "ui/one-memory-extracted-allow.gif";

			logger->Debug("Signal One Memory Allow");
			signalOneMemory.emit();
			configureWidget(true, false);
			break;

		case MachineOperationManager::MemoryBehavior_Suspend:

			setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.SuspendWindowTitle"));
			labelKey = N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.SuspendWindowInstruction");
			image = "ui/one-memory-extracted.gif";

			logger->Debug("Signal One Memory Suspend");
			signalOneMemory.emit();
			configureWidget(false, false);
			break;

		case MachineOperationManager::MemoryBehavior_Block:
			MachineOperationManager::getInstance()->StopDetection();

			setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.ErrorCheckData"));
			labelKey = " ";
			image = "ui/invalid-memory-inserted.gif";

			configureWidget(true, true);
			break;
		}
		break;

	case MachineOperationManager::TWO_MEMORY:

		setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.VerifyDataWindowTitle"));
		labelKey = N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.VerifyDataWindowInstruction");
		image = "ui/check-flash-structure.gif";

		logger->Debug("Signal Verify Memory");
		signalVerify.emit();
		configureWidget(false, false);
		break;

	case MachineOperationManager::CHECK_MEMORY_OK:

		logger->Debug("Signal Two Memory");
		signalTwoMemory.emit();
		signalEnd.emit();
		break;

	case MachineOperationManager::CHECK_MEMORY_ERROR:

		setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.ErrorCheckData"));
		labelKey = " ";
		image = "ui/check-flash-structure-failed.gif";

		configureWidget(true, true);
		break;


	case MachineOperationManager::ERROR_MEMORY:

		setTitleText(N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.PendriveExtracted"));
		labelKey = " ";
		image = "ui/invalid-memory-inserted.gif";

		configureWidget(true, true);
		break;
	}
}

void MemoryStateWidget::configureWidget(bool showHideButton, bool buttonClose)
{
	int button_enabling_delay = SAESGUIConfigurationManager::Current ()->getMemoryStateWidgetConfiguration().getButtonDelay ();

	progress->setImage(image);

	std::string lblTex = _(labelKey.c_str());

	if( lblTex != labelKey && BaseLanguageController::setLanguage)
	{
		progress->setText(lblTex);
	}
	else
	{
		progress->setText(" ");
	}

	if(showHideButton)
	{
		connectButton.disconnect();
		shutdownButton->set_sensitive(false);

		if(buttonClose)
		{
			std::string textButton = N_("Smartmatic.SAES.GUI.Windows.ErrorWindow.ButtonShutDown");
			std::string text = _(textButton.c_str());

			if (textButton != text && BaseLanguageController::setLanguage)
			{
				shutdownButton->set_label(text);
			}
			else
			{
				shutdownButton->set_label(" ");
				shutdownButton->WidgetsPosition(0,5,0);
				shutdownButton->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/button-shut-down.png"));
			}

			connectButton = shutdownButton->signal_clicked().connect( sigc::mem_fun(this, &MemoryStateWidget::shutDown));
		}
		else
		{
			shutdownButton->set_label(_("Smartmatic.SAES.GUI.Windows.ErrorWindow.AllowWindowButton"));
			connectButton = shutdownButton->signal_clicked().connect( sigc::mem_fun(this, &MemoryStateWidget::hideWidget));
		}

		Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MemoryStateWidget::enabledButton), button_enabling_delay);

		shutdownHBox->show();
	}
	else
	{
		shutdownHBox->hide();
	}

	logger->Debug("Signal View Memory State");
	signalStartWidget.emit();
}

void MemoryStateWidget::enabledButton()
{
	shutdownButton->set_sensitive(true);
}

void MemoryStateWidget::hideWidget()
{
	signalAllow.emit();
}

void MemoryStateWidget::shutDown()
{
	std::string commandShut = "powerdown &";
	(void)ProcessLauncher::RunProcessThroughSystem(commandShut.c_str());
}

sigc::signal<void> MemoryStateWidget::getSignalStartWidget()
{
	return signalStartWidget;
}

sigc::signal<void> MemoryStateWidget::getSignalAllow()
{
	return signalAllow;
}

sigc::signal<void> MemoryStateWidget::getSignalBlock()
{
	return signalBlock;
}

sigc::signal<void> MemoryStateWidget::getSignalOneMemory()
{
	return signalOneMemory;
}

sigc::signal<void> MemoryStateWidget::getSignalTwoMemory()
{
	return signalTwoMemory;
}

sigc::signal<void> MemoryStateWidget::getSignalVerify()
{
	return signalVerify;
}
