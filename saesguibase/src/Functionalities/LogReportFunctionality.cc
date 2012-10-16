/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogReportFunctionality.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Log/LogReader.h>
#include <System/Exception/LogReaderException.h>
#include <System/IO/File.h>
#include <Runtime/Environment/saes-directories.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace std;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;

LogReportFunctionality* LogReportFunctionality::current_instance = NULL;

ISMTTLog* LogReportFunctionality::logger = 
SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.ReportLogFunctionality",
                          GETTEXT_PACKAGE);

LogReportFunctionality* LogReportFunctionality::Current()
{
	if (!current_instance)
		current_instance = new LogReportFunctionality();

	return current_instance;
}

LogReportFunctionality::LogReportFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	logReaderAudit = NULL;
	logReaderError = NULL;
	reportLogWidget = NULL;
	logReportFrame = NULL;
}

LogReportFunctionality::~LogReportFunctionality()
{
	deleteElement();
}

void LogReportFunctionality::deleteElement()
{
	if (logReaderAudit)
	{
		delete logReaderAudit;
		logReaderAudit = NULL;
	}
	if (logReaderError)
	{
		delete logReaderError;
		logReaderError = NULL;
	}
	if (reportLogWidget)
	{
		delete reportLogWidget;
		reportLogWidget = NULL;
	}
	if (logReportFrame)
	{
		delete logReportFrame;
		logReportFrame = NULL;
	}
}

void LogReportFunctionality::Initialize()
{
	enableExitButton();
}

Gtk::Widget* LogReportFunctionality::GetFrame()
{
	logReportFrame = new Gtk::Frame();
	logReportFrame->set_visible (true);
	logReportFrame->show();

    SaesDirectories directories;

    std::string auditPath = directories.getLogAuditFileFullPath();
    std::string errorPath = directories.getLogErrorFileFullPath();

    this->pageSize = SAESGUIConfigurationManager::Current()->GetLogReportFunctionalityConfiguration().getPageSize();

    LogConfigurationReader & logConf ((*SAESCommonConfigurationManager::Current()->getConfiguration())->getLogConfigurationReader());

    logReaderAudit = new LogReader(auditPath, pageSize, logConf.getLogAuditReader());
    logReaderError = new LogReader(errorPath, pageSize, logConf.getLogErrorReader());
    reportLogWidget = new ReportLogWidget(logReaderAudit, logReaderError);

    reportLogWidget->on_print_begin().connect(sigc::mem_fun(*this, &LogReportFunctionality::on_disable_exit));
    reportLogWidget->on_print_end().connect(sigc::mem_fun(*this, &LogReportFunctionality::on_enable_exit));
    logReportFrame->add(*reportLogWidget);
    logReportFrame->set_visible (true);

    return logReportFrame;
}

void LogReportFunctionality::on_disable_exit()
{
    setExitButtonSensitive(false);
    setHelpButtonSensitive(false);
}

void LogReportFunctionality::on_enable_exit()
{
	setExitButtonSensitive(true);
	setHelpButtonSensitive(true);
}

void LogReportFunctionality::on_close_clicked()
{
	ExitFunctionality();
}

string LogReportFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.ReportLogFunctionality.ReportLogTitle");
}

Smartmatic::Functionality::MenuOptionDescriptor LogReportFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MLogReportFunctionality,false);
}

void LogReportFunctionality::Dispose()
{
}

Smartmatic::Log::ISMTTLog* LogReportFunctionality::getLogger()
{
	return logger;
}
Glib::ustring LogReportFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.LogReportFunctionality.LogStartFunctionality");
}

Glib::ustring LogReportFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.LogReportFunctionality.LogCloseFunctionality");
}

