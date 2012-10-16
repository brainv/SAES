/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 *
 * @file	brightness-diagnosis-widget.h
 *
 * @brief	Declares the brightness diagnosis widget class.
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

#ifndef _BRIGHTNESS_DIAGNOSIS_WIDGET_H_
#define _BRIGHTNESS_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <gtkmm.h>
#include <iostream>
#include "Voting/operation-status.h"

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
				 * @class	BrightnessDiagnosisWidget
				 *
				 * @brief	Brightness diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class BrightnessDiagnosisWidget: public BasicDiagnosticWidget
				{
				public:

					/**
					 * @fn	BrightnessDiagnosisWidget::BrightnessDiagnosisWidget(std::string Title,bool isAuto,
					 * 		bool hasOk, bool hasCancel, bool hasMessage,
					 * 		bool showButtons):BasicDiagnosticWidget(Title,isAuto,
					 * 		Smartmatic::SAES::Voting::OperationStatus::ScreenContrast, hasOk,hasCancel,hasMessage,
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

					BrightnessDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons);

					/**
					 * @fn	BrightnessDiagnosisWidget::~BrightnessDiagnosisWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~BrightnessDiagnosisWidget();

					/**
					 * @fn	void BrightnessDiagnosisWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void BrightnessDiagnosisWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();

					void deleteElement();

				protected:

				private:

					int brightSelected; ///< The bright selected

						//Frame inicial de calibracion de brillo
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::VBox* bottomBox;   ///< The bottom box
					Gtk::Label *label1; ///< The first label
					Gtk::Label *label2; ///< The second label
					Gtk::Label *label3; ///< The third label
					Gtk::Label *label4; ///< The fourth label
					Gtk::Label *mensaje;	///< The mensaje
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonOk;   ///< The button ok
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonCalibrate;	///< The button calibrate
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonMas;  ///< The button mas
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonMenos;	///< The button menos
					
					
					Glib::RefPtr<Gtk::Builder> builder; ///< The builder

					//Frame de calibracion de brillo
					sigc::connection connPlus;  ///< The connection plus
					sigc::connection connMinus; ///< The connection minus
					sigc::connection connMinusOff;  ///< The connection minus off
					sigc::connection connPlusOff;   ///< The connection plus off
					sigc::connection connAdjustment;	///< The connection adjustment
					sigc::connection connOk;	///< The connection ok
					sigc::connection connCalibrate; ///< The connection calibrate
					Gtk::Frame* frameBrillo;	///< The frame brillo
					Smartmatic::GUI::Widgets::SmartmaticButton* buttonClose;	///< The button close
					Gtk::Label *labelMas;   ///< The label mas
					Gtk::Label *labelMenos; ///< The label menos
					Gtk::HScale *hscale;	///< The hscale
					Gtk::Adjustment *adjustment;	///< The adjustment

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_buttonMinus_clicked();
					 *
					 * @brief	Handles button minus clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonMinus_clicked();

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_buttonPlus_clicked();
					 *
					 * @brief	Handles button plus clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonPlus_clicked();

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_buttonOk_clicked();
					 *
					 * @brief	Handles button ok clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void  on_buttonOk_clicked();

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_buttonCalibrate_clicked();
					 *
					 * @brief	Handles button calibrate clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void  on_buttonCalibrate_clicked();

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_buttonClose_clicked();
					 *
					 * @brief	Handles button close clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void  on_buttonClose_clicked();

					/**
					 * @fn	void BrightnessDiagnosisWidget::getBacktoInitialFrame();
					 *
					 * @brief	Gets the backto initial frame.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void getBacktoInitialFrame();

					/**
					 * @fn	void BrightnessDiagnosisWidget::GetFrameCalibrarBrillo();
					 *
					 * @brief	Gets the frame calibrar brillo.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void GetFrameCalibrarBrillo();

					/**
					 * @fn	void BrightnessDiagnosisWidget::on_adjustment_value_changed();
					 *
					 * @brief	Handles adjustment value changed signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_adjustment_value_changed();

					/**
					 * @fn	bool BrightnessDiagnosisWidget::WaitButtonMinusOff(int time_num);
					 *
					 * @brief	Wait button minus off.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool WaitButtonMinusOff(int time_num);

					/**
					 * @fn	bool BrightnessDiagnosisWidget::WaitButtonPlusOff(int time_num);
					 *
					 * @brief	Wait button plus off.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool WaitButtonPlusOff(int time_num);

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};

			}
		}
	}
}

#endif // _BRIGHTNESS_DIAGNOSIS_WIDGET_H_
