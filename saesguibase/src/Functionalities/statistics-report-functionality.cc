/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "statistics-report-functionality.h"
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;


ISMTTLog* StatisticsReportFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.StatisticsReportFunctionality",GETTEXT_PACKAGE);

StatisticsReportFunctionality* StatisticsReportFunctionality::current_instance = NULL;

StatisticsReportFunctionality* StatisticsReportFunctionality::Current()
{
	if (!current_instance)
		current_instance = new StatisticsReportFunctionality();

	return current_instance;
};


StatisticsReportFunctionality::StatisticsReportFunctionality()
:GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	statisticCounterRegisterWidget = NULL;
}

StatisticsReportFunctionality::~StatisticsReportFunctionality()
{
	deleteElement();
}

void StatisticsReportFunctionality::deleteElement()
{
	if (statisticCounterRegisterWidget)
	{
		delete statisticCounterRegisterWidget;
		statisticCounterRegisterWidget = NULL;
	}
}

void StatisticsReportFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.StatisticsReportFunctionality.SavingStatistics"));
	enableExitButton();
}

Gtk::Widget* StatisticsReportFunctionality::GetFrame()
{
	statisticCounterRegisterWidget = new StatisticCounterRegisterWidget();
	return statisticCounterRegisterWidget;
}

string StatisticsReportFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.StatisticsReport");
}

Smartmatic::Functionality::MenuOptionDescriptor StatisticsReportFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MStatisticsReportFunctionality,false);
}

void StatisticsReportFunctionality::Dispose()
{
	if (statisticCounterRegisterWidget)
	{
		statisticCounterRegisterWidget->Persist();
	}
}

Smartmatic::Log::ISMTTLog* StatisticsReportFunctionality::getLogger()
{
	return logger;
}

Glib::ustring StatisticsReportFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.StatisticsReportFunctionality.LogStartFunctionality");
}

Glib::ustring StatisticsReportFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.StatisticsReportFunctionality.LogCloseFunctionality");
}
