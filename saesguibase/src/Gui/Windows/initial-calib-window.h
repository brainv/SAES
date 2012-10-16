/**
 * @file	initial-calib-window.h
 *
 * @brief	Declares the initial calibration Windows Form.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#ifndef _INITIAL_CALIB_WINDOW_H_
#define _INITIAL_CALIB_WINDOW_H_

#include "Functionalities/all-diagnosis-functionality.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @brief	Form for viewing the initial calibration. 
				 */

				class InitialCalibWindow: public EmptyWindow
				{
					private:

						/**
						 * @brief	Builds the automatic.
						 */

						void BuildAutomatic();

						/**
						 * @brief	Executes on load action.
						 */

						void OnLoad();

						/**
						 * @brief	Handles calibration diagnostic finished signals.
						 */

						void on_CalibDiagFinished();

					
						Smartmatic::SAES::GUI::Widgets::CalibrationDiagnosisWidget* calibrationWidget;  ///< calibration widget

					public:

						/**
						 * @brief	Finaliser.
						 */

						~InitialCalibWindow();

						/**
						 * @brief	Default constructor.
						 */

						InitialCalibWindow();

						/**
						 * @brief	Dispose this object, cleaning up any resources it uses.
						 */

						void Dispose(){}

						/**
						 * @brief	Initializes this object.
						 */

						void Initialize(){}
						


				};
			}
		}
	}
}


#endif // _INITIAL_CALIB_WINDOW_H_
