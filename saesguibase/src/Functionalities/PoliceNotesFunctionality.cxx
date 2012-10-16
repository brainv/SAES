/**
 * @file PoliceNotesFunctionality.cxx
 * @brief Body class police notes functionality
 * @date 25/05/2012
 * @author Yadickson Soto
 */

#include "PoliceNotesFunctionality.hxx"
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

ISMTTLog* PoliceNotesFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.PoliceNotesFunctionality",GETTEXT_PACKAGE);

PoliceNotesFunctionality* PoliceNotesFunctionality::instance = NULL;

PoliceNotesFunctionality::PoliceNotesFunctionality()
{
	policeNotesWidget = NULL;
}

PoliceNotesFunctionality::~PoliceNotesFunctionality()
{
	deleteElement();
}

PoliceNotesFunctionality * PoliceNotesFunctionality::getInstance()
{
	if (!instance)
	{
		instance = new PoliceNotesFunctionality();
	}

	return instance;
}

std::string PoliceNotesFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PoliceNotesFunctionality.VotingForDisabledFunctionalityTitle");
}

Smartmatic::Log::ISMTTLog* PoliceNotesFunctionality::getLogger()
{
	return logger;
}

Glib::ustring PoliceNotesFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PoliceNotesFunctionality.LogStartFunctionality");
}

Glib::ustring PoliceNotesFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PoliceNotesFunctionality.LogCloseFunctionality");
}

Smartmatic::Functionality::MenuOptionDescriptor PoliceNotesFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::POLICE_NOTES,false);
}

Gtk::Widget * PoliceNotesFunctionality::GetFrame()
{
	policeNotesWidget = new PoliceNoteWidget();
	policeNotesWidget->getSignalEnabled().connect(sigc::mem_fun(*this, &PoliceNotesFunctionality::enableExitButton));
	policeNotesWidget->getSignalDisabled().connect(sigc::mem_fun(*this, &PoliceNotesFunctionality::disableExitButton));

	return policeNotesWidget;
}

void PoliceNotesFunctionality::Dispose()
{

}

void PoliceNotesFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.PoliceNotesFunctionality.FinalMessage"));
	enableExitButton();
}

void PoliceNotesFunctionality::deleteElement()
{
	if (policeNotesWidget)
	{
		delete policeNotesWidget;
		policeNotesWidget = NULL;
	}
}

void PoliceNotesFunctionality::block()
{
	logger->Debug("Block functionality");
}

void PoliceNotesFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void PoliceNotesFunctionality::resume()
{
	logger->Debug("Resume functionality");
}
