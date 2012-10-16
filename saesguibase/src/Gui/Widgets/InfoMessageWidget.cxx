/*
 * InfoMessageWidget.cxx
 *
 *  Created on: 17/10/2011
 *      Author: soto
 */

#include "InfoMessageWidget.hxx"
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

ISMTTLog* InfoMessageWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.InfoMessageWidget",GETTEXT_PACKAGE);

InfoMessageWidget::InfoMessageWidget()
: Gtk::Frame()
{
	this->mainFrame = NULL;
	this->infoFrame = NULL;
	this->mainVBox = NULL;
	this->buttonBack = NULL;
	this->buttonOk = NULL;
	this->buttonPrint = NULL;

	this->set_shadow_type(Gtk::SHADOW_NONE);
	this->initialize();

	this->add(*mainFrame);
	this->show_all_children();
}

InfoMessageWidget::~InfoMessageWidget()
{
	dispose();
}

void InfoMessageWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/InfoMessageWidget.glade");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - InfoMessageWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("info-frame", infoFrame);
	builder->get_widget("main-vbox", mainVBox);
	builder->get_widget("vbuttonbox-print", vbuttonboxPrint);
	builder->get_widget_derived("button-back", buttonBack);
	builder->get_widget_derived("button-ok", buttonOk);
	builder->get_widget_derived("button-print", buttonPrint);

	infoFrame->set_shadow_type(Gtk::SHADOW_NONE);
	buttonOk->SetButtonType(SmartmaticButton::Ok);
	buttonOk->WidgetsPosition(0,5,0);
	buttonBack->SetButtonType(SmartmaticButton::Cancel);
	buttonBack->WidgetsPosition(0,5,0);

	buttonBack->set_no_show_all(true);
	buttonOk->set_no_show_all(true);
	buttonPrint->set_no_show_all(true);
}

void InfoMessageWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (infoFrame)
	{
		delete infoFrame;
		infoFrame = NULL;
	}
	if (mainVBox)
	{
		delete mainVBox;
		mainVBox = NULL;
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
	if (buttonPrint)
	{
		delete buttonPrint,
		buttonPrint = NULL;
	}
}

Glib::SignalProxy0< void > InfoMessageWidget::getSignalButtonBackClicked()
{
	return buttonBack->signal_clicked();
}

Glib::SignalProxy0< void > InfoMessageWidget::getSignalButtonOkClicked()
{
	return buttonOk->signal_clicked();
}

Glib::SignalProxy0< void > InfoMessageWidget::getSignalButtonPrintClicked()
{
	return buttonPrint->signal_clicked();
}

void InfoMessageWidget::setInfoWidget(Gtk::Widget * info)
{
	infoFrame->remove();
	infoFrame->add(*info);
	infoFrame->show_all_children();
}

void InfoMessageWidget::enableButtonBack(bool enable)
{
	this->buttonBack->set_sensitive(enable);
}

void InfoMessageWidget::enableButtonOk(bool enable)
{
	this->buttonOk->set_sensitive(enable);
}

void InfoMessageWidget::enableButtonPrint(bool enable)
{
	this->buttonPrint->set_sensitive(enable);
}

void InfoMessageWidget::hideButtonBack()
{
	buttonBack->set_visible(false);
}

void InfoMessageWidget::showButtonBack()
{
	buttonBack->set_visible(true);
}

void InfoMessageWidget::hideButtonOk()
{
	buttonOk->set_visible(false);
}

void InfoMessageWidget::showButtonOk()
{
	buttonOk->set_visible(true);
}

void InfoMessageWidget::hideButtonPrint()
{
	buttonPrint->set_visible(false);
}

void InfoMessageWidget::showButtonPrint()
{
	buttonPrint->set_visible(true);
}

void InfoMessageWidget::hideText()
{
	buttonBack->set_label("");
	buttonOk->set_label("");
	buttonPrint->set_label("");

	buttonBack->SetButtonType(SmartmaticButton::Cancel);
	buttonOk->SetButtonType(SmartmaticButton::Ok);
	buttonPrint->SetButtonType(SmartmaticButton::Custom);

	buttonBack->WidgetsPosition(0,5,0);
	buttonOk->WidgetsPosition(0,5,0);
}

void InfoMessageWidget::showText()
{
	buttonBack->set_label(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.Back"));
	buttonOk->set_label(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.Ok"));
	buttonPrint->set_label(_("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.RetryPassword"));

	buttonBack->SetButtonType(SmartmaticButton::Cancel);
	buttonBack->WidgetsPosition(5,6,0);

	buttonOk->SetButtonType(SmartmaticButton::Ok);
	buttonOk->WidgetsPosition(5,6,0);

	buttonPrint->SetButtonType(SmartmaticButton::Custom);
}
