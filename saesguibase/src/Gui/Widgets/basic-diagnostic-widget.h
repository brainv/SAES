/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	basic-diagnostic-widget.h
 *
 * @brief	Declares the basic diagnostic widget class.
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

#ifndef _BASIC_DIAGNOSTIC_WIDGET_H_
#define _BASIC_DIAGNOSTIC_WIDGET_H_


#include <gtkmm.h>
#include <iostream>
#include <Widgets/smartmatic-button.h>
#include <Voting/operation-status.h>


namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	BasicDiagnosticWidget
				 *
				 * @brief	Basic diagnostic widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class BasicDiagnosticWidget: public Gtk::Frame
				{
					
					public:
						
						sigc::signal<void> signalOk_detected;   ///< The signal ok detected
						sigc::signal<void> signalCancel_detected;   ///< The signal cancel detected
						sigc::signal<void> signalError_detected;	///< The signal error detected
						sigc::signal<void> signalContinue_detected; ///< The signal continue detected
						sigc::connection connError; ///< The connection error
						sigc::connection connContinue;  ///< The connection continue
						sigc::connection connOk;	///< The connection ok
						sigc::connection connCancel;	///< The connection cancel

						/**
						 * @fn	void BasicDiagnosticWidget::setOkButtonSensitive(bool sensitive);
						 *
						 * @brief	Sets an ok button sensitive.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	sensitive	true to sensitive.
						 */

						void setOkButtonSensitive(bool sensitive);

						/**
						 * @fn	void BasicDiagnosticWidget::setCancelButtonSensitive(bool sensitive);
						 *
						 * @brief	Sets a cancel button sensitive.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	sensitive	true to sensitive.
						 */

						void setCancelButtonSensitive(bool sensitive);

						/**
						 * @fn	void BasicDiagnosticWidget::setOkButtonLabel(std::string label);
						 *
						 * @brief	Sets an ok button label.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	label	The label.
						 */

						void setOkButtonLabel(std::string label);

						/**
						 * @fn	void BasicDiagnosticWidget::setCancelButtonLabel(std::string label);
						 *
						 * @brief	Sets a cancel button label.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	label	The label.
						 */

						void setCancelButtonLabel(std::string label);

						/**
						 * @fn	virtual void BasicDiagnosticWidget::Initialize() = 0;
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						virtual void Initialize() = 0;
					protected:

						/**
						 * @fn	void BasicDiagnosticWidget::setDiagnosticFrame(Gtk::Widget& widget);
						 *
						 * @brief	Sets a diagnostic frame.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param [in,out]	widget	The widget.
						 */

						void setDiagnosticFrame(Gtk::Widget& widget);

						/**
						 * @fn	BasicDiagnosticWidget::BasicDiagnosticWidget(std::string Title,bool isAutomatic,
						 * 		Smartmatic::SAES::Voting::OperationStatus::Diagnostic diagnostic, bool showOk,
						 * 		bool showCancel, bool showMessage,bool showButtons);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	Title	   	The title.
						 * @param	diagnostic 	The diagnostic.
						 * @param	showOk	   	true to show, false to hide the ok.
						 * @param	showCancel 	true to show, false to hide the cancel.
						 * @param	showMessage	true to show, false to hide the message.
						 * @param	showButtons	true to show, false to hide the buttons.
						 */

						BasicDiagnosticWidget(std::string Title, Smartmatic::SAES::Voting::OperationStatus::Diagnostic diagnostic, bool showOk, bool showCancel, bool showMessage,bool showButtons);

						/**
						 * @fn	virtual void BasicDiagnosticWidget::Dispose() = 0;
						 *
						 * @brief	Dispose of this object, cleaning up any resources it uses.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						virtual void Dispose() = 0;	


						/**
						 * @fn	void BasicDiagnosticWidget::on_buttonOk_clicked();
						 *
						 * @brief	Handles button ok clicked signals.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void on_buttonOk_clicked();

						/**
						 * @fn	void BasicDiagnosticWidget::on_buttonCancel_clicked();
						 *
						 * @brief	Handles button cancel clicked signals.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void on_buttonCancel_clicked();

						/**
						 * @fn	void BasicDiagnosticWidget::on_buttonRealBack_clicked();
						 *
						 * @brief	Handles button real back clicked signals.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void on_buttonRealBack_clicked();
						Gtk::VBox vboxPrincipal;	///< The vbox principal
						Gtk::Frame frameDiagnostic; ///< The frame diagnostic
						Gtk::HButtonBox hboxButton; ///< The hbox button
						Smartmatic::GUI::Widgets::SmartmaticButton okButton;	///< The ok button
						Smartmatic::GUI::Widgets::SmartmaticButton cancelButton;	///< The cancel button
						Gtk::Label labelTitle;  ///< The label title
						Gtk::Label labelMessage;	///< Message describing the label
						

				};
			}
		}
	}
}

#endif // _BASIC_DIAGNOSTIC_WIDGET_H_
