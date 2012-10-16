/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * trunk
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	ReportLogWidget.h
 *
 * @brief	Declares the report log widget class.
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

#ifndef _REPORTLOGWIDGET_H_
#define _REPORTLOGWIDGET_H_

#include <gtkmm.h>
#include <Log/LogReader.h>
#include <Gui/Widgets/LogPagingTreeViewWidget.h>
#include <Printing/PrintDocumentClient.h>
#include <Printing/PrintDocumentClient.h>
#include "Printing/PrintDocumentResult.h"
#include <Printing/AuditLogPrintDocument.h>
#include <Printing/ErrorLogPrintDocument.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	ReportLogWidget
				 *
				 * @brief	Report log widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ReportLogWidget : public Gtk::Frame
                , Smartmatic::SAES::Printing::PrintDocumentClient
				{
				public:

					enum LogType
					{
						LogType_Audit,
						LogType_Error,
					};

					sigc::signal<void,LogType> signalPrint_detected;
					/**
					 * @fn	ReportLogWidget::ReportLogWidget(Smartmatic::SAES::Log::LogReader * logReaderAudit,
					 * 		Smartmatic::SAES::Log::LogReader * logReaderError);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	logReaderAudit	If non-null, the log reader audit.
					 * @param [in,out]	logReaderError	If non-null, the log reader error.
					 */

					ReportLogWidget(Smartmatic::SAES::Log::LogReader * logReaderAudit,
					                Smartmatic::SAES::Log::LogReader * logReaderError);

					/**
					 * @fn	virtual ReportLogWidget::~ReportLogWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~ReportLogWidget();

					typedef sigc::signal<void> signalPrint;

					signalPrint on_print_begin();
					signalPrint on_print_end();

				protected:
					
					signalPrint m_signalPrint_begin;
					signalPrint m_signalPrint_end;

					void printAuditLogger();
					void printErrorLogger();

				private:

					/**
					 * @fn	void ReportLogWidget::LoadGUI();
					 *
					 * @brief	Loads the graphical user interface.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void LoadGUI();
					void on_buttonPrint_clicked();
					void onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res);
					Gtk::Table* m_TopWidgetTableLayout; ///< The top widget table layout
					Gtk::Frame* m_FrameAudit;   ///< The frame audit
					Gtk::Frame* m_FrameErrors;  ///< The frame errors
					Gtk::Notebook*	m_NotebookLogs; ///< The notebook logs
					LogPagingTreeViewWidget* logPagingTreeViewAudit;	///< The log paging tree view audit
					LogPagingTreeViewWidget* logPagingTreeViewError;	///< The log paging tree view error
					sigc::connection connPrintAudit; ///< connection print audit
					sigc::connection connPrintError;	///< connection print error
					Smartmatic::SAES::Log::LogReader *logReaderAudit;   ///< The log reader audit
					Smartmatic::SAES::Log::LogReader *logReaderError;   ///< The log reader error

					Smartmatic::SAES::Printing::AuditLogPrintDocument* m_AuditLogPrintReport;
					Smartmatic::SAES::Printing::ErrorLogPrintDocument* m_ErrorLogPrintReport;

					std::string messagePrint;
					bool statusPrint;

					void showInitialImage();
					void showLoadImage();
					void showPrintMessage();
					void showErrorMessage();
					void endPrint();
					bool checkPrinter();
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _REPORTLOGWIDGET_H_
