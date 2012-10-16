/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	calibration-diagnosis-widget.h
 *
 * @brief	Declares the calibration diagnosis widget class.
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

#ifndef _CALIBRATION_DIAGNOSIS_WIDGET_H_
#define _CALIBRATION_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <gtkmm.h>
#include <iostream>
#include "Widgets/smartmatic-button.h"
#include "Voting/operation-status.h"
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	CalibrationDiagnosisWidget
				 *
				 * @brief	Calibration diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class CalibrationDiagnosisWidget: public BasicDiagnosticWidget
				{
				public:

					/**
					 * @fn	CalibrationDiagnosisWidget::CalibrationDiagnosisWidget(std::string Title,bool isAuto,
					 * 		bool hasOk, bool hasCancel, bool hasMessage, bool showButtons,bool isOpeningMachine);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	Title				The title.
					 * @param	isAuto				true if is automatic.
					 * @param	hasOk				true if the has operation was a success, false if it failed.
					 * @param	hasCancel			true if has cancel.
					 * @param	hasMessage			true if has message.
					 * @param	showButtons			true to show, false to hide the buttons.
					 * @param	isOpeningMachine	true if is opening machine.
					 */

					CalibrationDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons,bool isOpeningMachine);

					/**
					 * @fn	CalibrationDiagnosisWidget::~CalibrationDiagnosisWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~CalibrationDiagnosisWidget();

					/**
					 * @fn	void CalibrationDiagnosisWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void CalibrationDiagnosisWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();
				protected:

				private:
						//
				//Frame inicial de calibracion
				Gtk::Frame* framePrincipal; ///< The frame principal
				Gtk::HBox* bottomBox;   ///< The bottom box
				Gtk::VBox* vbox1;   ///< The first vbox
				Gtk::VBox* vbox2;   ///< The second vbox
				Gtk::HButtonBox* hbuttonbox1;   ///< The first hbuttonbox
				Gtk::HButtonBox* hbuttonbox2;   ///< The second hbuttonbox
				Gtk::EventBox* side1;   ///< The first side
				Gtk::EventBox* side2;   ///< The second side
				Gtk::EventBox* middle;  ///< The middle
				Gtk::Label *labelCal;   ///< The label cal
				Gtk::Image *imageCalib; ///< The image calib
				Gtk::Label *labelResult;	///< The label result
				Smartmatic::GUI::Widgets::SmartmaticButton* button1;	///< The first button
				Smartmatic::GUI::Widgets::SmartmaticButton* button2;	///< The second button
				Smartmatic::GUI::Widgets::SmartmaticButton* button3;	///< The third button
				Smartmatic::GUI::Widgets::SmartmaticButton* button4;	///< The fourth button
				Smartmatic::GUI::Widgets::SmartmaticButton* button5;	///< The fifth button

				bool fail_Cal;  ///< true to fail cal
				int click_counter;  ///< The click counter

				Glib::RefPtr<Gtk::Builder> builder; ///< The builder

				//Frame de fallo de calibracion
				Gtk::Frame* frameFailure;   ///< The frame failure
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonCalibrate;	///< The button calibrate
				Gtk::Label *mensajeFracaso; ///< The mensaje fracaso

				//FRame de exito de calibracion
				Gtk::Frame* frameSuccess;   ///< The frame success
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonCalSuc;   ///< The button cal suc
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonOk;   ///< The button ok
				Gtk::Label *mensajeSuccess; ///< The mensaje success

				int timeout;	///< The timeout
				bool isOpeningMachine;  ///< true if is opening machine

				/**
				 * @fn	bool CalibrationDiagnosisWidget::on_zone_clicked(GdkEventButton* event);
				 *
				 * @brief	Executes the zone clicked action.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool  on_zone_clicked(GdkEventButton* event);
				sigc::connection connAuto;  ///< The connection automatic
				sigc::connection connRefreshTimeout;	///< The connection refresh timeout

				/**
				 * @fn	bool CalibrationDiagnosisWidget::RefreshTimeout(int time_num);
				 *
				 * @brief	Refresh timeout.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	time_num	The time number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool  RefreshTimeout(int time_num);

				/**
				 * @fn	bool CalibrationDiagnosisWidget::AutoDiag(int time_num);
				 *
				 * @brief	Automatic diagram.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	time_num	The time number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool  AutoDiag(int time_num);

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_button1_clicked();
				 *
				 * @brief	Handles button 1 clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_button1_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_button2_clicked();
				 *
				 * @brief	Handles button 2 clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_button2_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_button3_clicked();
				 *
				 * @brief	Handles button 3 clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_button3_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_button4_clicked();
				 *
				 * @brief	Handles button 4 clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_button4_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_button5_clicked();
				 *
				 * @brief	Handles button 5 clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_button5_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::on_buttonCalibrate_clicked();
				 *
				 * @brief	Handles button calibrate clicked signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void  on_buttonCalibrate_clicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::onbuttonokclicked();
				 *
				 * @brief	Onbuttonokclickeds this object.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void onbuttonokclicked();

				/**
				 * @fn	void CalibrationDiagnosisWidget::getBacktoInitialFrame();
				 *
				 * @brief	Gets the backto initial frame.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void getBacktoInitialFrame();

				/**
				 * @fn	void CalibrationDiagnosisWidget::GetFrameSuccess();
				 *
				 * @brief	Gets the frame success.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void GetFrameSuccess();

				/**
				 * @fn	void CalibrationDiagnosisWidget::GetFrameFracaso();
				 *
				 * @brief	Gets the frame fracaso.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void GetFrameFracaso();

				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};

			}
		}
	}
}

#endif // _CALIBRATION_DIAGNOSIS_WIDGET_H_
