/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	printer-diagnosis-widget.h
 *
 * @brief	Declares the printer diagnosis widget class.
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

#ifndef _PRINTER_DIAGNOSIS_WIDGET_H_
#define _PRINTER_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <gtkmm.h>
#include <iostream>
#include <queue>
#include <Operation/Diagnosis/PrinterDiagnosis.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	PrinterDiagnosisWidget
				 *
				 * @brief	Printer diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class PrinterDiagnosisWidget : public BasicDiagnosticWidget
				{
				public:

					/**
					 * @fn	PrinterDiagnosisWidget::PrinterDiagnosisWidget(std::string Title,bool isAuto, bool hasOk,
					 * 		bool hasCancel, bool hasMessage, bool showButtons):BasicDiagnosticWidget(Title,isAuto,
					 * 		Smartmatic::SAES::Voting::OperationStatus::Printer, hasOk,hasCancel,hasMessage,
					 * 		showButtons)
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	Title	   	The title.
					 * @param	isAuto	   	true if is automatic.
					 * @param	hasOk	   	true if the has operation was a success, false if it failed.
					 * @param	hasCancel  	true if has cancel.
					 * @param	hasMessage 	true if has message.
					 * @param	showButtons	true to show, false to hide the buttons.
					 */

					PrinterDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons);

					/**
					 * @fn	PrinterDiagnosisWidget::~PrinterDiagnosisWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PrinterDiagnosisWidget();

					/**
					 * @fn	void PrinterDiagnosisWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void PrinterDiagnosisWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();
				protected:

				private:

					Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;	///< The directories
					std::string	tempFile;   ///< The temp file
					bool m_PrintSuccess;	///< true if the print operation was a success, false if it failed
					std::string errorPrinting;
					Smartmatic::SAES::Operation::Diagnosis::PrinterDiagnosis * diagnosis;

					void EmitContinueSignal();

					/**
					 * @fn	void PrinterDiagnosisWidget::on_signalOk();
					 *
					 * @brief	Handles signal ok signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_signalOk();

					/**
					 * @fn	void PrinterDiagnosisWidget::on_signalCancel();
					 *
					 * @brief	Handles signal cancel signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_signalCancel();
					std::string trace;  ///< The trace
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Image* imagePrint; ///< The image print
					Gtk::Label* labelAllInfo;   ///< Information describing the label all

					/**
					 * @fn	bool PrinterDiagnosisWidget::SendTest(int timer_num);
					 *
					 * @brief	Sends a test.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	timer_num	The timer number.
					 *
					 * @return	true if the test passes, false if the test fails.
					 */

					void SendTest();

					/**
					 * @fn	bool PrinterDiagnosisWidget::Refresh(int time_num);
					 *
					 * @brief	Refreshs.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int time_num);

					void checkEndDiagnosis();

				};
			}
		}
	}
}
			

#endif // _PRINTER_DIAGNOSIS_WIDGET_H_
