/**
 * @file VotingForDisabledFunctionality.cxx
 * @brief Body class voting for disabled functionality
 * @date 18/05/2012
 * @author Yadickson Soto
 */

#include "VotingForDisabledFunctionality.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Devices/barcode-device.h>

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

using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::Log;

ISMTTLog* VotingForDisabledFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.VotingForDisabledFunctionality",GETTEXT_PACKAGE);

VotingForDisabledFunctionality* VotingForDisabledFunctionality::instance = NULL;

VotingForDisabledFunctionality::VotingForDisabledFunctionality()
{
	votingForDisabledWidget = NULL;
}

VotingForDisabledFunctionality::~VotingForDisabledFunctionality()
{
	deleteElement();
}

VotingForDisabledFunctionality * VotingForDisabledFunctionality::getInstance()
{
	if (!instance)
	{
		instance = new VotingForDisabledFunctionality();
	}

	return instance;
}

std::string VotingForDisabledFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingForDisabledFunctionality.VotingForDisabledFunctionalityTitle");
}

Smartmatic::Log::ISMTTLog* VotingForDisabledFunctionality::getLogger()
{
	return logger;
}

Glib::ustring VotingForDisabledFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingForDisabledFunctionality.LogStartFunctionality");
}

Glib::ustring VotingForDisabledFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VotingForDisabledFunctionality.LogCloseFunctionality");
}

Smartmatic::Functionality::MenuOptionDescriptor VotingForDisabledFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::VOTING_FOR_DISABLED,false);
}

Gtk::Widget * VotingForDisabledFunctionality::GetFrame()
{
	votingForDisabledWidget = new VotingForDisabledWidget();
	votingForDisabledWidget->getSignalEnabled().connect(sigc::mem_fun(*this, &VotingForDisabledFunctionality::enableExitButton));
	votingForDisabledWidget->getSignalDisabled().connect(sigc::mem_fun(*this, &VotingForDisabledFunctionality::disableExitButton));

	return votingForDisabledWidget;
}

void VotingForDisabledFunctionality::Dispose()
{

}

void VotingForDisabledFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VotingForDisabledFunctionality.FinalMessage"));
	enableExitButton();
}

void VotingForDisabledFunctionality::deleteElement()
{
	if (votingForDisabledWidget)
	{
		delete votingForDisabledWidget;
		votingForDisabledWidget = NULL;
	}
}

void VotingForDisabledFunctionality::block()
{
	logger->Debug("Block functionality");
}

void VotingForDisabledFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void VotingForDisabledFunctionality::resume()
{
	logger->Debug("Resume functionality");
}
