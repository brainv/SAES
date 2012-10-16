/**
 * @file ButtonsWidget.cxx
 * @brief Body class buttons widget
 * @date 12/03/2012
 * @author Yadickson Soto
 */

#include "ButtonsWidget.hxx"
#include <Configuration/s-m-t-t-g-u-i-conf-manager.h>
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* ButtonsWidget::logger = SMTTLogManager::GetLogger("Smartmatic.GUI.Widgets.ButtonsWidget",GETTEXT_PACKAGE);

ButtonsWidget::ButtonsWidget(bool expand)
: Gtk::EventBox()
{
	eventbox = NULL;
	mainHbox = NULL;
	clearButton = NULL;
	acceptButton = NULL;
	backButton = NULL;
	nullButton = NULL;
	this->expand = expand;

	initialize();
}

ButtonsWidget::ButtonsWidget(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
:Glib::ObjectBase("ButtonsWidget"),
Gtk::EventBox(cobject)
{
	eventbox = NULL;
	mainHbox = NULL;
	clearButton = NULL;
	acceptButton = NULL;
	backButton = NULL;
	nullButton = NULL;
	expand = false;

	initialize();
}

ButtonsWidget::~ButtonsWidget()
{
	dispose();
}

void ButtonsWidget::initialize()
{
	dispose();

	eventbox = new Gtk::EventBox();
	mainHbox = new Gtk::HBox();
	acceptButton = new SmartmaticButton();
	clearButton = new SmartmaticButton();
	backButton = new SmartmaticButton();
	nullButton = new SmartmaticButton();

	clearButton->set_no_show_all();
	acceptButton->set_no_show_all();
	backButton->set_no_show_all();
	nullButton->set_no_show_all();

	switch(SMTTGUIConfigurationManager::Current()->getButtonsQuestionConfiguration())
	{
		case ButtonsQuestionConfiguration::CONFIGURATION_ACCEPT_CANCEL:
			mainHbox->pack_start(*acceptButton, true, expand);
			mainHbox->pack_start(*clearButton, true, expand);
			break;
		case ButtonsQuestionConfiguration::CONFIGURATION_CANCEL_ACCEPT:
			mainHbox->pack_start(*clearButton, true, expand);
			mainHbox->pack_start(*acceptButton, true, expand);
			break;
	}

	mainHbox->pack_start(*backButton, true, expand);
	mainHbox->pack_start(*nullButton, true, expand);

	eventbox->add(*mainHbox);
	this->add(*eventbox);
	this->show_all_children();
}

void ButtonsWidget::dispose()
{
	this->remove();

	if (eventbox)
	{
		delete eventbox;
		eventbox = NULL;
	}
	if (mainHbox)
	{
		delete mainHbox;
		mainHbox = NULL;
	}
	if (backButton)
	{
		delete backButton;
		backButton = NULL;
	}
	if (clearButton)
	{
		delete clearButton;
		clearButton = NULL;
	}
	if (acceptButton)
	{
		delete acceptButton;
		acceptButton = NULL;
	}
	if (nullButton)
	{
		delete nullButton;
		nullButton = NULL;
	}
}

Glib::SignalProxy0< void > ButtonsWidget::getSignalClearButtonClicked()
{
	return clearButton->signal_clicked();
}

Glib::SignalProxy0< void > ButtonsWidget::getSignalAcceptButtonClicked()
{
	return acceptButton->signal_clicked();
}

Glib::SignalProxy0< void > ButtonsWidget::getSignalBackButtonClicked()
{
	return backButton->signal_clicked();
}

Glib::SignalProxy0< void > ButtonsWidget::getSignalNullButtonClicked()
{
	return nullButton->signal_clicked();
}

void ButtonsWidget::setSpacing(int spacing)
{
	mainHbox->set_spacing(spacing);
}

void ButtonsWidget::modifyFontSize(int size)
{
	clearButton->ModifyFontSize(size);
	acceptButton->ModifyFontSize(size);
	backButton->ModifyFontSize(size);
}

void ButtonsWidget::showButton(bool showClear, bool showAccept, bool showBack, bool showNull)
{
	clearButton->set_visible(showClear);
	acceptButton->set_visible(showAccept);
	backButton->set_visible(showBack);
	nullButton->set_visible(showNull);
}

void ButtonsWidget::setTextClearButton(std::string text)
{
	clearButton->SetLabel(text);
}

void ButtonsWidget::setTextAcceptButton(std::string text)
{
	acceptButton->SetLabel(text);
}

void ButtonsWidget::setTextBackButton(std::string text)
{
	backButton->SetLabel(text);
}

void ButtonsWidget::setTextNullButton(std::string text)
{
	nullButton->SetLabel(text);
}

void ButtonsWidget::setSizeClearButton(int width, int height)
{
	clearButton->set_size_request(width, height);
}

void ButtonsWidget::setSizeAcceptButton(int width, int height)
{
	acceptButton->set_size_request(width, height);
}

void ButtonsWidget::setSizeBackButton(int width, int height)
{
	backButton->set_size_request(width, height);
}

void ButtonsWidget::setSizeNullButton(int width, int height)
{
	nullButton->set_size_request(width, height);
}

void ButtonsWidget::changeButtom()
{
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);

	acceptButton->SetButtonType(SmartmaticButton::Ok);
	acceptButton->WidgetsPosition(5,6,0);
}
