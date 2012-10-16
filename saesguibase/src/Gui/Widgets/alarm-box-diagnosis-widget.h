/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	alarm-box-diagnosis-widget.h
 *
 * @brief	Declares the alarm box diagnosis widget class.
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

#ifndef _ALARM_BOX_DIAGNOSIS_WIDGET_H_
#define _ALARM_BOX_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <Gui/Widgets/ProgressWidget.hxx>

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
				 * @class	AlarmBoxDiagnosisWidget
				 *
				 * @brief	Alarm box diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class AlarmBoxDiagnosisWidget: public BasicDiagnosticWidget
				{
					public:

						/**
						 * @fn	AlarmBoxDiagnosisWidget::AlarmBoxDiagnosisWidget(std::string Title,bool isAuto,
						 * 		bool hasOk, bool hasCancel, bool hasMessage,
						 * 		bool showButtons):BasicDiagnosticWidget(Title,isAuto,
						 * 		Smartmatic::SAES::Voting::OperationStatus::AlarmBox, hasOk,hasCancel,hasMessage,
						 * 		showButtons)
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	Title	   	The title.
						 * @param	isAuto	   	true if is automatic.
						 * @param	hasOk	   	true if the has operation was a success, false if it failed.
						 * @param	hasCancel  	true if has cancel.
						 * @param	hasMessage 	true if has message.
						 * @param	showButtons	true to show, false to hide the buttons.
						 */

						AlarmBoxDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons);

						/**
						 * @fn	AlarmBoxDiagnosisWidget::~AlarmBoxDiagnosisWidget()
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						~AlarmBoxDiagnosisWidget();

						/**
						 * @fn	void AlarmBoxDiagnosisWidget::Dispose();
						 *
						 * @brief	Dispose of this object, cleaning up any resources it uses.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void Dispose();

						/**
						 * @fn	void AlarmBoxDiagnosisWidget::Initialize();
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void Initialize();
					protected:

					private:

						/**
						 * @fn	void AlarmBoxDiagnosisWidget::BoxButtonPressed();
						 *
						 * @brief	Box button pressed.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void BoxButtonPressed();
						int timerCounter;   ///< The timer counter
						bool buttonPress;   ///< true to button press
						bool ping;  ///< true to ping
						bool status;
						std::string message;
						sigc::connection connRefresh;   ///< The connection refresh
						sigc::connection connAlarm; ///< The connection alarm

						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget;
						static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

						/**
						 * @fn	bool AlarmBoxDiagnosisWidget::SendTest(int timer_num);
						 *
						 * @brief	Sends a test.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	timer_num	The timer number.
						 *
						 * @return	true if the test passes, false if the test fails.
						 */

						void SendTest();

						/**
						 * @fn	bool AlarmBoxDiagnosisWidget::Refresh(int time_num);
						 *
						 * @brief	Refreshs.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 *
						 * @param	time_num	The time number.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool Refresh(int time_num);
					
						void deleteElement();

						void test();

						void showResult();
				};
			}
		}
	}
}

#endif // _ALARM_BOX_DIAGNOSIS_WIDGET_H_
