/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	bar-code-diagnosis-widget.h
 *
 * @brief	Declares the bar code diagnosis widget class.
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

#ifndef _BAR_CODE_DIAGNOSIS_WIDGET_H_
#define _BAR_CODE_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <gtkmm.h>
#include <iostream>
#include <queue>
#include <qrencode.h>
#include "Voting/operation-status.h"
#include <System/SafeBuffer.h>
#include <Printing/BarcodePrinting.hxx>
#include <Printing/PrintDocumentClient.h>
#include <Printing/BarcodeConfigPrinting.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	BarCodeDiagnosisWidget
				 *
				 * @brief	Bar code diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class BarCodeDiagnosisWidget: public BasicDiagnosticWidget, Smartmatic::SAES::Printing::PrintDocumentClient
				{
				public:

					/**
					 * @fn	BarCodeDiagnosisWidget::BarCodeDiagnosisWidget(std::string Title,bool isAuto, bool hasOk,
					 * 		bool hasCancel, bool hasMessage, bool showButtons):BasicDiagnosticWidget(Title,isAuto,
					 * 		Smartmatic::SAES::Voting::OperationStatus::Barcode, hasOk,hasCancel,hasMessage,
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

					BarCodeDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons);

					/**
					 * @fn	BarCodeDiagnosisWidget::~BarCodeDiagnosisWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~BarCodeDiagnosisWidget();

					/**
					 * @fn	void BarCodeDiagnosisWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void BarCodeDiagnosisWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();

					/**
					 * @typedef	sigc::signal<void, bool> type_printing_signal
					 *
					 * @brief	definition of ballot clicked signal.
					 *
					 * @param	bool true if is printing
					 */

					typedef sigc::signal<void, bool> type_printing_signal;

					type_printing_signal signal_printing();

					/**
					 * @brief	Hides retry button
					 */
					void HideRetryButton();

				protected:
					type_printing_signal m_type_printing_signal;

				private:
					Smartmatic::SAES::Printing::BarcodePrinting * barcodePrinting;

					bool automaticPrint;	///> The automatic print
					bool hideRetryButton;	///< True if hide retry button
					int timeoutCounter; ///< The timeout counter
					int TimeOutFinal;   ///< The time out final
					bool success;   ///< true if the operation was a success, false if it failed
					Smartmatic::SAES::Printing::BarcodeConfigPrinting barcodeConfigPrinting; ///< barcode config printing

					Glib::RefPtr<Gdk::Pixbuf> pixBuffBarcode;

					void PrintPDF();
					void onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res);

					void CommandsSent(bool commandsOk);

					/**
					 * @fn	void BarCodeDiagnosisWidget::SendTest();
					 *
					 * @brief	Sends a test.
					 *
					 * @author	Yadickson Soto
					 * @date	09/04/2012
					 *
					 */

					void SendTest();

					/**
					 * @brief	Reconfigure barcode.
					 *
					 * @author	Juan.Delgado
					 * @date	08/04/2011
					 */
					void  ReconfigureBarcode();

					/**
					 * @fn	void BarCodeDiagnosisWidget::PrintBarcode();
					 *
					 * @brief	Print a barcode.
					 *
					 * @author	Juan.Delgado
					 * @date	08/04/2011
					 */
					void PrintBarcode();

					/**
					 * @fn	bool BarCodeDiagnosisWidget::Refresh(int timer_num);
					 *
					 * @brief	Refreshs.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	timer_num	The timer number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Refresh(int timer_num);

					/**
					 * @fn	bool BarCodeDiagnosisWidget::RefreshTimeout(int timer_num);
					 *
					 * @brief	Refresh timeout.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	timer_num	The timer number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshTimeout(int timer_num);

					/**
					 * @fn	void BarCodeDiagnosisWidget::RecievedData(Smartmatic::System::SafeBuffer recieved);
					 *
					 * @brief	Recieved data.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	recieved	The recieved.
					 */

					void RecievedData(Smartmatic::System::SafeBuffer * recieved);

					/**
					 * @fn	void BarCodeDiagnosisWidget::BoxButtonPressed();
					 *
					 * @brief	Box button pressed.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void BoxButtonPressed();
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Image* imageBarcodeReader; ///< The image barcode reader
					Gtk::Label* labelResult;	///< The label result
					Gtk::Alignment* alignment1; ///< The first alignment
					

					sigc::connection connCommandIn;  ///< The connection commands send
					sigc::connection connCommandOut;  ///< The connection commands send
					sigc::connection connCommandSend;  ///< The connection commands send
					sigc::connection connRefresh;   ///< The connection refresh
					sigc::connection connRefreshTimeout;	///< The connection refresh timeout
					sigc::connection connReceived;  ///< The connection received
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonReconfigure;  ///< The button reconfigure
					Smartmatic::GUI::Widgets::SmartmaticButton* button_back_reconfigure;	///< The button back reconfigure

					std::string commandsInBarcode;///< The commands in barcode
					std::string commandsOutBarcode;///< The commands out barcode
					std::string commandsReconfigure;

					/**
					 * @fn	void BarCodeDiagnosisWidget::on_buttonReconfigure_clicked();
					 *
					 * @brief	Handles button reconfigure clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void  on_buttonReconfigure_clicked();

					/**
					 * @fn	void BarCodeDiagnosisWidget::on_button_back_reconfigure_clicked();
					 *
					 * @brief	Handles button back reconfigure clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void  on_button_back_reconfigure_clicked();

					/**
					 * @fn	bool BarCodeDiagnosisWidget::CheckPrinter();
					 *
					 * @brief	Gets the check printer.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool CheckPrinter();

					void printBarcode();

					void sendCommandIn();
					void sendCommandOut();

					void endSendCommandIn(bool commandsOk);
					void endSendCommandOut(bool commandsOk);
					void end();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}

#endif // _BAR_CODE_DIAGNOSIS_WIDGET_H_
