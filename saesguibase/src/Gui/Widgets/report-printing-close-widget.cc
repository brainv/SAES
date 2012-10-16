/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Gui/Widgets/report-printing-close-widget.h>
#include "AbstractFactoryWidget.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/XmlException.hxx>

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
using namespace Glib;
using namespace std;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;

Smartmatic::Log::ISMTTLog* ReportPrintingCloseWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ReportPrintingCloseWidget",GETTEXT_PACKAGE);

ReportPrintingCloseWidget::ReportPrintingCloseWidget()
{	
	reportPrintWidget = AbstractFactoryWidget::createReportPrintingWidget();
	reportPrintWidget->signal_finished().connect(sigc::mem_fun(*this, &ReportPrintingCloseWidget::Finish));
	reportPrintWidget->signal_begin_print().connect(sigc::mem_fun(*this, &ReportPrintingCloseWidget::BeginPrint));
	setWidget(reportPrintWidget);
}

ReportPrintingCloseWidget::~ReportPrintingCloseWidget()
{
	remove();

	if (reportPrintWidget)
	{
		delete reportPrintWidget;
		reportPrintWidget = NULL;
	}
}

void ReportPrintingCloseWidget::initialize()
{

}

void ReportPrintingCloseWidget::EmitSignal()
{
	m_done_signal.emit();
}

void ReportPrintingCloseWidget::BeginPrint()
{
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportPrintingCloseWidget.PrintReport"));
	m_disable_close_signal.emit();
}

void ReportPrintingCloseWidget::Finish(bool printOk)
{
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ReportPrintingCloseWidget.FinishPrintReport"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &ReportPrintingCloseWidget::EmitSignal), 3000);
}

void ReportPrintingCloseWidget::dispose()
{

}
