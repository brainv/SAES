/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	flash-diagnosis-widget.h
 *
 * @brief	Declares the flash diagnosis widget class.
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

#ifndef _FLASH_DIAGNOSIS_WIDGET_H_
#define _FLASH_DIAGNOSIS_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <Operation/Diagnosis/FlashDiagnosis.hxx>
#include <Gui/Widgets/ProgressWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	FlashDiagnosisWidget
				 *
				 * @brief	Flash diagnosis widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class FlashDiagnosisWidget: public BasicDiagnosticWidget
				{
				public:

					/**
					 * @fn	FlashDiagnosisWidget::FlashDiagnosisWidget(std::string Title,bool isAuto, bool hasOk,
					 * 		bool hasCancel, bool hasMessage, bool showButtons):BasicDiagnosticWidget(Title, isAuto,
					 * 		Smartmatic::SAES::Voting::OperationStatus::Flash, hasOk,hasCancel,hasMessage,showButtons)
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	Title	   	The title.
					 * @param	hasOk	   	true if the has operation was a success, false if it failed.
					 * @param	hasCancel  	true if has cancel.
					 * @param	hasMessage 	true if has message.
					 * @param	showButtons	true to show, false to hide the buttons.
					 */

					FlashDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons);

					/**
					 * @fn	FlashDiagnosisWidget::~FlashDiagnosisWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~FlashDiagnosisWidget();

					/**
					 * @fn	void FlashDiagnosisWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void FlashDiagnosisWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();
				protected:

				private:

					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget;
					Smartmatic::SAES::Operation::Diagnosis::FlashDiagnosis * diagnosis;

					/**
					 * @fn	bool FlashDiagnosisWidget::SendTest(int timer_num);
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

					void test();

					void showResult();
				};
			}
		}
	}
}


#endif // _FLASH_DIAGNOSIS_WIDGET_H_
