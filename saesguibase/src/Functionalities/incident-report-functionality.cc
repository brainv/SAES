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

#include "incident-report-functionality.h"
#include "Functionalities/time-functionality.h"
#include <Log/SMTTLogManager.h>
#include <time.h>

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
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;


ISMTTLog* IncidentReportFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality",GETTEXT_PACKAGE);

IncidentReportFunctionality* IncidentReportFunctionality::current_instance = NULL;

IncidentReportFunctionality* IncidentReportFunctionality::Current()
{
	if (!current_instance)
		current_instance = new IncidentReportFunctionality();

	return current_instance;
};

IncidentReportFunctionality::IncidentReportFunctionality()
 : GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	incidentReportWidget = NULL;
}

IncidentReportFunctionality::~IncidentReportFunctionality()
{
	deleteElement();
}

void IncidentReportFunctionality::deleteElement()
{
	if (incidentReportWidget)
	{
		delete incidentReportWidget;
		incidentReportWidget = NULL;
	}
}

void IncidentReportFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.SavingIncidentReports"));

	if (incidentReportWidget)
	{
		incidentReportWidget->LoadReports();
	}

	enableExitButton();
};


Gtk::Widget* IncidentReportFunctionality::GetFrame()
{
	incidentReportWidget = new IncidentReportWidget();
	return incidentReportWidget;
};

string IncidentReportFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.IncidentReport");
};

Smartmatic::Functionality::MenuOptionDescriptor IncidentReportFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MIncidentReportFunctionality,false);
};	

void IncidentReportFunctionality::Dispose()
{
	if (incidentReportWidget)
	{
		incidentReportWidget->dispose();
	}
};

Smartmatic::Log::ISMTTLog* IncidentReportFunctionality::getLogger()
{
	return logger;
}

Glib::ustring IncidentReportFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.LogStartFunctionality");
}

Glib::ustring IncidentReportFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.IncidentReportFunctionality.LogCloseFunctionality");
}
