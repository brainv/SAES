/**
 * @file HelpWidget.cxx
 * @brief Body help widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#include "HelpWidget.hxx"
#include <Environment/Configurations/base-language-controller.h>
#include <Environment/Configurations/resource-path-provider.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Printing/PrinterStatusNotifier.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::GUI::Configuration;

ISMTTLog* HelpWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.HelpWidget",GETTEXT_PACKAGE);

HelpWidget::HelpWidget()
: StepWidget()
{
	initialize();
	setWidget(helpEventBox);
}

HelpWidget::HelpWidget(std::string titleKey, std::string image, std::string file)
: StepWidget()
{
	initialize();
	setInfo(titleKey, imageFile, file);
	setWidget(helpEventBox);
}

HelpWidget::~HelpWidget()
{
	dispose();
}

bool HelpWidget::isExit()
{
	return true;
}

void HelpWidget::initialize()
{
	this->helpEventBox = NULL;
	this->mainVBox = NULL;
	this->labelInfo = NULL;
	this->label1 = NULL;
	this->helpVBox = NULL;
	this->image = NULL;
	this->mainVBox = NULL;
	this->separator = NULL;
	this->printHBox = NULL;
	this->printButton = NULL;
	this->printing = NULL;

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/HelpWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - HelpWidget Initialize");
	}

	builder->get_widget("help-eventbox", helpEventBox);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("label-info", labelInfo);
	builder->get_widget("label1", label1);
	builder->get_widget("help-vbox", helpVBox);
	builder->get_widget("main-image", image);
	builder->get_widget("hseparator", separator);
	builder->get_widget("print-hbox", printHBox);
	builder->get_widget_derived("print-button", printButton);

	image->set_no_show_all();
	separator->set_no_show_all();
	printHBox->set_no_show_all();

	int fontSize = SAESGUIConfigurationManager::Current ()->getHelpWidgetConfiguration().getPrintButtonConf().getFontSize();
	int widthB = SAESGUIConfigurationManager::Current ()->getHelpWidgetConfiguration().getPrintButtonConf().getButtonWidth();
	int heightB = SAESGUIConfigurationManager::Current ()->getHelpWidgetConfiguration().getPrintButtonConf().getButtonHeight();

	printButton->ModifyFontSize(fontSize);
	printButton->set_size_request(widthB, heightB);

	printButton->signal_clicked().connect(sigc::mem_fun(*this, &HelpWidget::startPrintProcess));

	Pango::FontDescription fontTitle = labelInfo->get_style()->get_font();
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	fontTitle.set_size(14*Pango::SCALE);

	labelInfo->modify_font(fontTitle);
	label1->modify_font(fontTitle);

	this->show_all_children();
}

void HelpWidget::dispose()
{
	this->remove();

	if (helpEventBox)
	{
		delete helpEventBox;
		helpEventBox = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
	}
	if (labelInfo)
	{
		delete labelInfo;
		labelInfo = NULL;
	}
	if (helpVBox)
	{
		delete helpVBox;
		helpVBox = NULL;
	}
	if (image)
	{
		delete image;
		image = NULL;
	}
	if (separator)
	{
		delete separator;
		separator = NULL;
	}
	if (printHBox)
	{
		delete printHBox;
		printHBox = NULL;
	}
	if (printButton)
	{
		delete printButton;
		printButton = NULL;
	}
	if(printing)
	{
		delete printing;
		printing = NULL;
	}
}

void HelpWidget::setInfo(std::string titleKey, std::string image, std::string file)
{
	setTitleText(titleKey);
	this->imageFile = image;
	this->file = file;
	refresh();
}

void HelpWidget::refresh()
{
	std::string toFile = getCurrentLanguageFile(file);
	std::string toImageFile = getCurrentLanguageFile(imageFile);

	if(File::canOpenFile(toImageFile))
	{
		image->set(Gdk::Pixbuf::create_from_file(toImageFile));
		image->show();

		if(File::canOpenFile(toFile))
		{
			separator->show();
			printHBox->show();
			labelInfo->set_text("");
			printButton->SetLabel(_("Smartmatic.SAES.GUI.Windows.HelpWindow.PrintButton"));
		}
		else
		{
			separator->hide();
			printHBox->hide();
			labelInfo->set_text("");
			labelInfo->set_text(_("Smartmatic.SAES.GUI.Windows.HelpWindow.NoFileToPrintFound"));
		}
	}
	else
	{
		image->hide();
		labelInfo->set_text(_("Smartmatic.SAES.GUI.Windows.HelpWindow.NoImageHelpFound"));
	}
}

std::string HelpWidget::getCurrentLanguageFile(std::string file)
{
	std::string finalFile;
/*
	std::string extension = Path::GetFileExtension(file);

	std::string langFile = Path::GetFullFileNameWithOutExtension(file) +
			BaseLanguageController::getActualLanguage() + extension;

	std::string newLangFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, langFile);

	if(File::canOpenFile(newLangFile))
	{
		finalFile = newLangFile;
	}
	else
	{*/
		//std::string filePath = Path::GetFullFileNameWithOutExtension(file) + extension;
		finalFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, file);
		logger->Debug("File to load: " + finalFile);
	//}

	return finalFile;
}

void HelpWidget::printHelp()
{
	printing->Print();
}

void HelpWidget::startPrintProcess()
{
	if (printing)
	{
		delete printing;
		printing = NULL;
	}

	if (checkPrinter())
	{
		signalStartPrint.emit();

		printButton->set_sensitive(false);

		std::string toFile = getCurrentLanguageFile(file);
		printing = new HelpPrinting(toFile);
		printing->signalPrintFinished.connect (sigc::mem_fun (*this, &HelpWidget::printFinished));
		printing->signalErrorDetected.connect (sigc::mem_fun (*this, &HelpWidget::errorDetected));

		Glib::Thread::create((sigc::mem_fun(*this, &HelpWidget::printHelp)), false);
	}
	else
	{
		labelInfo->set_text(_("Smartmatic.SAES.GUI.Windows.HelpWindow.PrinterErrorState"));
		labelInfo->show();
	}
}

bool HelpWidget::checkPrinter()
{
	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	return ( printerState & printNotifier.getErrorCondition () ) == 0;
}

void HelpWidget::endPrinting()
{
	printButton->set_sensitive(true);

	if (endStatus)
	{
		labelInfo->set_text(_("Smartmatic.SAES.GUI.Windows.HelpWindow.PrintComplete"));
	}
	else
	{
		labelInfo->set_text(_("Smartmatic.SAES.GUI.Windows.HelpWindow.ErrorPrinting"));
	}

	signalEndPrint.emit();
}

void HelpWidget::printFinished ()
{
	endStatus = true;
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &HelpWidget::endPrinting), 100);
}

void HelpWidget::errorDetected ()
{
	endStatus = false;
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &HelpWidget::endPrinting), 100);
}

sigc::signal<void> HelpWidget::getSignalStartPrint()
{
	return signalStartPrint;
}

sigc::signal<void> HelpWidget::getSignalEndPrint()
{
	return signalEndPrint;
}
