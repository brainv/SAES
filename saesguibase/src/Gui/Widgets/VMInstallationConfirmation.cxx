/*
 * VMInstallationConfirmation.cxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#include "VMInstallationConfirmation.hxx"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Log;

ISMTTLog* VMInstallationConfirmation::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.VMInstallationConfirmation",GETTEXT_PACKAGE);

VMInstallationConfirmation::VMInstallationConfirmation()
: Gtk::Frame()
{
	this->mainFrame = NULL;
	this->infoFrame = NULL;
	this->buttonBack = NULL;
	this->buttonOk = NULL;

	this->initialize();
	this->set_shadow_type(Gtk::SHADOW_NONE);
	this->add(*mainFrame);
	this->show_all_children();
}

VMInstallationConfirmation::~VMInstallationConfirmation()
{
	dispose();
}

void VMInstallationConfirmation::initialize()
{
	Glib::RefPtr<Gtk::Builder> builder;

	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/vm_installation_confirmation.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - VMInstallationConfirmation initialize");
	}

	int buttonWidth = SAESGUIConfigurationManager::Current()->GetVMInstallationConfiguration().getButtonsWidth();
	int buttonHeight = SAESGUIConfigurationManager::Current()->GetVMInstallationConfiguration().getButtonsHeight();
	std::string sound = SAESGUIConfigurationManager::Current()->getVMInstalationSound();

	builder->get_widget("main-frame",mainFrame);
	builder->get_widget("info-frame",infoFrame);
	builder->get_widget_derived("buttonBack",buttonBack);
	builder->get_widget_derived("buttonOk",buttonOk);

	buttonBack->set_label(_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.ButtonBack"));
	buttonBack->SetSound (sound);
	buttonBack->set_size_request (buttonWidth, buttonHeight);
	buttonBack->ModifyFontSize(18);

	buttonOk->set_label(_("Smartmatic.SAES.GUI.Windows.VMInstallationWindow.ButtonOk"));
	buttonOk->SetSound (sound);
	buttonOk->set_size_request (buttonWidth, buttonHeight);
	buttonOk->ModifyFontSize(18);

	buttonBack->set_no_show_all(true);
	buttonOk->set_no_show_all(true);
}

void VMInstallationConfirmation::dispose()
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
	if (buttonBack)
	{
		delete buttonBack;
		buttonBack = NULL;
	}
	if (buttonOk)
	{
		delete buttonOk;
		buttonOk = NULL;
	}
}

Glib::SignalProxy0< void > VMInstallationConfirmation::getSignalButtonBackClicked()
{
	return buttonBack->signal_clicked();
}

Glib::SignalProxy0< void > VMInstallationConfirmation::getSignalButtonOkClicked()
{
	return buttonOk->signal_clicked();
}

void VMInstallationConfirmation::hideButtonBack()
{
	buttonBack->set_visible(false);
}

void VMInstallationConfirmation::showButtonBack()
{
	buttonBack->set_visible(true);
}

void VMInstallationConfirmation::hideButtonOk()
{
	buttonOk->set_visible(false);
}

void VMInstallationConfirmation::showButtonOk()
{
	buttonOk->set_visible(true);
}

void VMInstallationConfirmation::setInfoWidget(Gtk::Widget * info)
{
	infoFrame->remove();
	infoFrame->add(*info);
	infoFrame->show_all_children();
}
