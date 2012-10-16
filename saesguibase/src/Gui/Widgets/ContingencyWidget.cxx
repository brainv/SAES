/**
 * @file ContingencyWidget.cxx
 * @brief Body class contingency widget
 * @date 17/10/2011
 * @author Yadickson Soto
 */

#include "ContingencyWidget.hxx"
#include <Environment/Configurations/resource-path-provider.h>
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
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* ContingencyWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ContingencyWidget",GETTEXT_PACKAGE);

ContingencyWidget::ContingencyWidget(bool onlyIcons, EntryDividedWidgetConfiguration & config)
: StepWidget()
{
	this->mainFrame = NULL;
	this->tablePin = NULL;
	this->labelTitle = NULL;
	this->labelPin = NULL;
	this->imagePin = NULL;
	this->imageHelp = NULL;
	this->pin = NULL;
	this->buttonBack = NULL;
	this->buttonOk = NULL;

	this->onlyIcons = onlyIcons;
	this->entryDivisions = config.getNumberOfDivision();
	this->entryMaxChar = config.getMaxCharacters();
	this->entryWidth = config.getEntryWidth();
	this->entryVisibility = config.getVisibility();

	this->initialize();

	setWidget(mainFrame);
}

ContingencyWidget::~ContingencyWidget()
{
	dispose();
}

void ContingencyWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconPin;
	std::string iconHelp;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/ContingencyWidget.glade");
	iconPin = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/contingency-pin.gif");
	iconHelp = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/contingency-help.gif");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - ContingencyWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("table-pin", tablePin);
	builder->get_widget("label-title", labelTitle);
	builder->get_widget("label-pin", labelPin);
	builder->get_widget("image-pin", imagePin);
	builder->get_widget("image-help", imageHelp);
	builder->get_widget_derived("button-back", buttonBack);
	builder->get_widget_derived("button-ok", buttonOk);

	pin = new SmartmaticEntryDivided(entryDivisions, entryMaxChar, entryWidth, entryVisibility);

	tablePin->attach(*pin, 1, 2, 0, 1, Gtk::SHRINK, Gtk::SHRINK);

	labelTitle->set_text(!onlyIcons ? _("Smartmatic.SAES.GUI.Widgets.ContingencyWidget.Title") : " ");
	labelPin->set_text(!onlyIcons ? _("Smartmatic.SAES.GUI.Widgets.ContingencyWidget.Pin") : " ");
	imagePin->set(Gdk::PixbufAnimation::create_from_file(iconPin));
	imageHelp->set(Gdk::PixbufAnimation::create_from_file(iconHelp));

	buttonOk->SetButtonType(SmartmaticButton::Ok);
	buttonOk->WidgetsPosition(0,5,0);
	buttonBack->SetButtonType(SmartmaticButton::Cancel);
	buttonBack->WidgetsPosition(0,5,0);

	buttonBack->hide();
	buttonBack->set_no_show_all();
}

void ContingencyWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (tablePin)
	{
		delete tablePin;
		tablePin = NULL;
	}
	if (labelTitle)
	{
		delete labelTitle;
		labelTitle = NULL;
	}
	if (labelPin)
	{
		delete labelPin;
		labelPin = NULL;
	}
	if (imagePin)
	{
		delete imagePin;
		imagePin = NULL;
	}
	if (imageHelp)
	{
		delete imageHelp;
		imageHelp = NULL;
	}
	if (pin)
	{
		delete pin;
		pin = NULL;
	}
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if (buttonOk)
	{
		delete buttonOk,
		buttonOk = NULL;
	}
}

Glib::SignalProxy0< void > ContingencyWidget::getSignalButtonBackClicked()
{
	return buttonBack->signal_clicked();
}

Glib::SignalProxy0< void > ContingencyWidget::getSignalButtonOkClicked()
{
	return buttonOk->signal_clicked();
}

void ContingencyWidget::getText(std::string & text)
{
	text = pin->GetText();
}

void ContingencyWidget::clear()
{
	pin->Clean();
}
