/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	report-printing-close-widget.h
 *
 * @brief	Declares the report printing close widget class.
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

#ifndef _REPORT_PRINTING_CLOSE_WIDGET_H_
#define _REPORT_PRINTING_CLOSE_WIDGET_H_
#include <gtkmm.h>
#include "Gui/Widgets/report-printing-close-widget.h"
#include <Widgets/wizard-widget-base.h>
#include <Printing/ReportPrintingController.h>
#include "Gui/Widgets/ReportPrintingWidget.h"

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
				 * @class	ReportPrintingCloseWidget
				 *
				 * @brief	Report printing close widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ReportPrintingCloseWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					/**
					 * @fn	ReportPrintingCloseWidget::ReportPrintingCloseWidget();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					ReportPrintingCloseWidget();

					/**
					 * @fn	ReportPrintingCloseWidget::~ReportPrintingCloseWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~ReportPrintingCloseWidget();

					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

					/**
					 * @fn	Glib::ustring ReportPrintingCloseWidget::GetWidgetName()
					 *
					 * @brief	Gets the widget name.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The widget name.
					 */

					Glib::ustring GetWidgetName() { return "ReportPrintingCloseWidget"; }
					
				protected:

				private:
					void EmitSignal();

					/**
					 * @fn	void ReportPrintingCloseWidget::Finish(bool printOk);
					 *
					 * @brief	Finishs.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	printOk	true if the print operation was a success, false if it failed.
					 */

					void Finish(bool printOk);

					/**
					 * @fn	void ReportPrintingCloseWidget::BeginPrint();
					 *
					 * @brief	Begin Print.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void BeginPrint();
						
					ReportPrintingWidget* reportPrintWidget;	///< The report print widget
						
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

				};
			}
		}
	}
}



#endif // _REPORT_PRINTING_CLOSE_WIDGET_H_
