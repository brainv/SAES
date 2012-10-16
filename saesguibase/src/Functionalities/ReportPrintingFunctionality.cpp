/*
 * ReportPrintingFunctionality.cpp
 *
 *  Created on: Apr 20, 2011
 *      Author: root
 */

#include <Log/SMTTLogManager.h>
#include "ReportPrintingFunctionality.h"
#include <Gui/Widgets/AbstractFactoryWidget.hxx>

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
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;



//======================= Static member initialization =======================//

ISMTTLog* ReportPrintingFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ReportPrintingFunctionality", GETTEXT_PACKAGE);
ReportPrintingFunctionality* ReportPrintingFunctionality::current_instance = NULL;


//=============================== Life cycle =================================//

ReportPrintingFunctionality::ReportPrintingFunctionality()
:GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	m_ReportPrintingWidget = NULL;
}

ReportPrintingFunctionality::~ReportPrintingFunctionality()
{

}

ReportPrintingFunctionality* ReportPrintingFunctionality::Current ()
{
	if ( ! current_instance )
		current_instance = new ReportPrintingFunctionality ();

	return current_instance;
}


//======== GraphicDisplayFunctionality abstract method implementation ========//

Gtk::Widget* ReportPrintingFunctionality::GetFrame()
{
	m_ReportPrintingWidget = AbstractFactoryWidget::createReportPrintingWidget();

	m_ReportPrintingWidget->signal_begin_print().connect(sigc::mem_fun(*this, &ReportPrintingFunctionality::BeginPrint));

	m_ReportPrintingWidget->signal_finished().connect(sigc::mem_fun(*this, &ReportPrintingFunctionality::EndPrint));

	return this->m_ReportPrintingWidget;
}

void ReportPrintingFunctionality::BeginPrint()
{
	disableExitButton();
}

void ReportPrintingFunctionality::EndPrint(bool succes)
{
	enableExitButton();
}

void ReportPrintingFunctionality::Dispose()
{

}

void ReportPrintingFunctionality::Initialize()
{
	enableExitButton();
}

std::string ReportPrintingFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ReportPrintingFunctionality.ReportPrintingFunctionality");
}

MenuOptionDescriptor ReportPrintingFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MReportPrintingFunctionality, false);
}


Smartmatic::Log::ISMTTLog* ReportPrintingFunctionality::getLogger()
{
	return logger;
}

Glib::ustring ReportPrintingFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ReportPrintingFunctionality.LogStartFunctionality");
}

Glib::ustring ReportPrintingFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ReportPrintingFunctionality.LogCloseFunctionality");
}

void ReportPrintingFunctionality::deleteElement()
{
	if (m_ReportPrintingWidget)
	{
		delete m_ReportPrintingWidget;
		m_ReportPrintingWidget = NULL;
	}
}
