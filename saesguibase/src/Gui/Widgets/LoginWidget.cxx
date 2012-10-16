/**
 * @file LoginWidget.cxx
 * @brief Body class Login widget
 * @date 17/10/2011
 * @author Yadickson Soto
 */

#include "LoginWidget.hxx"
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

ISMTTLog* LoginWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.LoginWidget",GETTEXT_PACKAGE);

LoginWidget::LoginWidget(bool onlyIcons, EntryDividedWidgetConfiguration & config)
: Gtk::Frame()
{
	this->mainFrame = NULL;
	this->tableLogin = NULL;
	this->labelTitle = NULL;
	this->labelLogin = NULL;
	this->labelPassword = NULL;
	this->imageLogin = NULL;
	this->imagePassword = NULL;
	this->login = NULL;
	this->password = NULL;
	this->buttonOk = NULL;

	this->onlyIcons = onlyIcons;
	this->entryDivisions = config.getNumberOfDivision();
	this->entryMaxChar = config.getMaxCharacters();
	this->entryWidth = config.getEntryWidth();
	this->entryVisibility = config.getVisibility();

	this->set_shadow_type(Gtk::SHADOW_NONE);

	this->initialize();

	this->add(*mainFrame);
	this->show_all_children();
}

LoginWidget::~LoginWidget()
{
	dispose();
}

void LoginWidget::initialize()
{
	dispose();

	Glib::RefPtr<Gtk::Builder> builder;

	std::string gladeFile;
	std::string iconLoginFile;
	std::string iconPasswordFile;

	gladeFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/LoginWidget.glade");
	iconLoginFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/PM_login.gif");
	iconPasswordFile = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/PM_pass.gif");

	try
	{
		builder = Gtk::Builder::create_from_file(gladeFile);
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - LoginWidget Initialize");
	}

	builder->get_widget("main-frame", mainFrame);
	builder->get_widget("table-login", tableLogin);
	builder->get_widget_derived("entry-login", login);
	builder->get_widget("label-title", labelTitle);
	builder->get_widget("label-login", labelLogin);
	builder->get_widget("label-password", labelPassword);
	builder->get_widget("image-login", imageLogin);
	builder->get_widget("image-password", imagePassword);
	builder->get_widget_derived("button-ok", buttonOk);

	password = new SmartmaticEntryDivided(entryDivisions, entryMaxChar, entryWidth, entryVisibility);
	tableLogin->attach(*password, 1, 2, 1, 2, Gtk::SHRINK, Gtk::SHRINK);

	labelTitle->set_text(!onlyIcons ? _("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.InsertYourLoginAndPassword") : " ");
	labelLogin->set_text(!onlyIcons ? _("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.Login") : " ");
	labelPassword->set_text(!onlyIcons ? _("Smartmatic.SAES.GUI.Widgets.PMInstallationWidget.Password") : " ");

	imageLogin->set(Gdk::PixbufAnimation::create_from_file(iconLoginFile));
	imagePassword->set(Gdk::PixbufAnimation::create_from_file(iconPasswordFile));

	buttonOk->SetButtonType(SmartmaticButton::Ok);
	buttonOk->WidgetsPosition(0,5,0);
}

void LoginWidget::dispose()
{
	this->remove();

	if (mainFrame)
	{
		delete mainFrame;
		mainFrame = NULL;
	}
	if (tableLogin)
	{
		delete tableLogin;
		tableLogin = NULL;
	}
	if (labelTitle)
	{
		delete labelTitle;
		labelTitle = NULL;
	}
	if (labelLogin)
	{
		delete labelLogin;
		labelLogin = NULL;
	}
	if (labelPassword)
	{
		delete labelPassword;
		labelPassword = NULL;
	}
	if (imageLogin)
	{
		delete imageLogin;
		imageLogin = NULL;
	}
	if (imagePassword)
	{
		delete imagePassword;
		imagePassword = NULL;
	}
	if (login)
	{
		delete login;
		login = NULL;
	}
	if (password)
	{
		delete password;
		password = NULL;
	}
	if (buttonOk)
	{
		delete buttonOk,
		buttonOk = NULL;
	}
}

Glib::SignalProxy0< void > LoginWidget::getSignalButtonOkClicked()
{
	return buttonOk->signal_clicked();
}

void LoginWidget::enabledLogin(bool enabled)
{
	login->set_editable(enabled);
	login->set_sensitive(enabled);
}

void LoginWidget::getLoginText(std::string & text)
{
	text = login->get_text();
}

void LoginWidget::setLoginText(std::string & text)
{
	login->set_text(text);
}

void LoginWidget::getPasswordText(std::string & text)
{
	text = password->GetText();
}

void LoginWidget::clearLogin()
{
	login->set_text("");
}

void LoginWidget::clearPassword()
{
	password->Clean();
}
