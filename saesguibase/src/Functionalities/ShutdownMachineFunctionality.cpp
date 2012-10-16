/**
 * @file ShutdownMachineFunctionality.cpp
 * @brief Body class shutdown machine functionality
 * @date 10/06/2011
 * @author Gerardo Hernandez
 */

#include "ShutdownMachineFunctionality.h"
#include <Log/SMTTLogManager.h>
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

using namespace Gtk;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::System::Runtime;

ShutdownMachineFunctionality* ShutdownMachineFunctionality::current_instance = NULL;

Smartmatic::Log::ISMTTLog* ShutdownMachineFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ShutdownFunctionality",GETTEXT_PACKAGE);

ShutdownMachineFunctionality* ShutdownMachineFunctionality::Current()
{
	if (!current_instance)
		current_instance = new ShutdownMachineFunctionality();

	return current_instance;
};

ShutdownMachineFunctionality::ShutdownMachineFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	externalFrame = NULL;
	titleLabel = NULL;
}

Gtk::Widget* ShutdownMachineFunctionality::GetFrame()
{
	externalFrame = new Gtk::Frame();
	externalFrame->set_shadow_type(Gtk::SHADOW_NONE);

	titleLabel = new Label(_("Smartmatic.SAES.GUI.Functionality.ShutdownMachineFunctionality.ShutdownMachineMessage"));
	Pango::FontDescription fontTitle = titleLabel->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	titleLabel->modify_font(fontTitle);

	externalFrame->add(*titleLabel);
	externalFrame->show_all_children();
	externalFrame->show();

	this->EnableBackgroundProcess();

	return externalFrame;
};


void ShutdownMachineFunctionality::Dispose()
{

}

void ShutdownMachineFunctionality::Initialize()
{
	enableExitButton();
}

std::string ShutdownMachineFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ShutdownMachineFunctionality.ShutdownMachine");
}

Smartmatic::Functionality::MenuOptionDescriptor ShutdownMachineFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MShutdownMachine,false);
}

void ShutdownMachineFunctionality::ExcuteBackgroundProcess()
{
	std::string commandShut = "powerdown &";
	(void)ProcessLauncher::RunProcessThroughSystem(commandShut.c_str());
}

Smartmatic::Log::ISMTTLog* ShutdownMachineFunctionality::getLogger()
{
	return logger;
}

Glib::ustring ShutdownMachineFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ShutdownMachineFunctionality.ShutdownStartFunctionality");
}

Glib::ustring ShutdownMachineFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ShutdownMachineFunctionality.ShutdownCloseFunctionality");
}

void ShutdownMachineFunctionality::deleteElement()
{
	if (externalFrame)
	{
		delete externalFrame;
		externalFrame = NULL;
	}
	if (titleLabel)
	{
		delete titleLabel;
		titleLabel = NULL;
	}
}
