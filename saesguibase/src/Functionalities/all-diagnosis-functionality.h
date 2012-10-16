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

#ifndef _ALL_DIAGNOSIS_FUNCTIONALITY_H_
#define _ALL_DIAGNOSIS_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Printing/InstallationPrintDocument.h>
#include <Printing/PrintDocumentClient.h>
#include "Gui/Widgets/alarm-box-diagnosis-widget.h"
#include "Gui/Widgets/smart-card-reader-diagnosis-widget.h"
#include "Gui/Widgets/printer-diagnosis-widget.h"
#include "Gui/Widgets/bar-code-diagnosis-widget.h"
#include "Gui/Widgets/calibration-diagnosis-widget.h"
#include "Gui/Widgets/brightness-diagnosis-widget.h"
#include "Gui/Widgets/flash-diagnosis-widget.h"
#include <Log/ISMTTLog.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Voting/operation-status.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class AllDiagnosisFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>, public Smartmatic::SAES::Printing::PrintDocumentClient
				{

				public:

					/**
					 * @brief	Gets the dont allow help.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowHelp();

					/**
					 * @brief	Gets the help sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The help sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getHelpSeqKey();

					/**
					 * @brief	Gets the dont allow exit.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool DontAllowExit();

					/**
					 * @brief	Gets the sequence key.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The sequence key.
					 */

					std::vector<Smartmatic::GUI::Widgets::KeysActionsCode> getSeqKey();

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static AllDiagnosisFunctionality* Current();

				protected:

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The start log message.
					 */

					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finish log message.
					 */

					Glib::ustring getFinishLogMessage();

				private:

					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Frame* frameResultPrincipal;   ///< The frame result principal
					Gtk::Alignment* aligmentResultPrincipal;	///< The aligment result principal
					Gtk::VBox* vbox1;   ///< The first vbox
					Gtk::HButtonBox* boxPrincipal;
					Gtk::HBox* boxContainer;
					Gtk::Frame* box1;
					Gtk::Frame* box2;
					Gtk::Label* labelDevice;
					Gtk::Image* imageStatus;

					Smartmatic::SAES::Printing::InstallationPrintDocument*  installationPrintDocument; ///< Diagnostic print document
					bool startPrint; ///< flag start printing

					/**
					 * @brief	Handles alarm diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_AlarmDiagFinished();

					/**
					 * @brief	Handles bc diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_BCDiagFinished();

					/**
					 * @brief	Handles screen diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_SCDiagFinished();

					/**
					 * @brief	Handles printer diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_PrinterDiagFinished();

					/**
					 * @brief	Handles printer diagram finished on ok signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_PrinterDiagFinishedOnOk();	

					/**
					 * @brief	Handles printer diagram finished on cancel signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_PrinterDiagFinishedOnCancel();

					/**
					 * @brief	Handles calibration diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_CalibrationDiagFinished();

					/**
					 * @brief	Handles flash diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_FlashDiagFinished();

					/**
					 * @brief	Handles brightness diagram finished signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_BrightnessDiagFinished();

					/**
					 * @brief	Shows the results.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void showResults();
						
					/**
					 * @brief	Handle the print documment result.
					 *
					 * @author	Freddy.Gomez
					 * @date	22/05/2011
					 *
					 */
					void onDocumentPrinted ( Smartmatic::SAES::Printing:: PrintDocumentResult res);

					static AllDiagnosisFunctionality *current_instance; ///< The current instance

					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

					void deleteResultElement();

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					AllDiagnosisFunctionality();
					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					~AllDiagnosisFunctionality();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();	

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					Gtk::Widget* GetFrame();

					unsigned int index; ///< Zero-based index of the 
					std::vector<Smartmatic::SAES::GUI::Widgets::BasicDiagnosticWidget*> listOfDiagnosis;	///< The list of diagnosis

					/**
					 * @brief	Refresh alarm.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshAlarm(int time_num);

					/**
					 * @brief	Refresh bc.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshBC(int time_num);

					/**
					 * @brief	Refresh printer.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshPrinter(int time_num);

					/**
					 * @brief	Refresh printer on ok.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshPrinterOnOk(int time_num);

					/**
					 * @brief	Refresh printer on cancel.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshPrinterOnCancel(int time_num);	

					/**
					 * @brief	Sets the printer widget.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void SetPrinterWidget();

					/**
					 * @brief	Refresh screen.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshSC(int time_num);

					/**
					 * @brief	Refresh calib.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshCalib(int time_num);

					/**
					 * @brief	Refresh brightness.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshBrightness(int time_num);

					/**
					 * @brief	Refresh flash.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	time_num	The time number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool RefreshFlash(int time_num);


					/**
					 * @brief	Converts a device to a readable text.
					 *
					 * @author	Luiggi.mendez
					 * @date	20/05/2011
					 *
					 * @param [in]	the device.
					 */

					std::string GetTraslatedName(Smartmatic::SAES::Configuration::DiagnosticDevice devtype);

					Smartmatic::SAES::Voting::OperationStatus::Diagnostic GetTraslatedDevice(Smartmatic::SAES::Configuration::DiagnosticDevice devtype);
					/**
					 * @brief	Converts a deviceName to a readable.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param [in,out]	deviceName	Name of the device.
					 */

					void convertToReadable(std::string& deviceName);

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();
					sigc::connection connAlarmDiag; ///< The connection alarm diagram
					sigc::connection connBCDiag;	///< The connection bc diagram
					sigc::connection connSCDiag;	///< The connection screen diagram
					sigc::connection connPrinterDiag;   ///< The connection printer diagram
					sigc::connection connPrinterDiagOnOk;   ///< The connection printer diagram on ok
					sigc::connection connPrinterDiagOnCancel;   ///< The connection printer diagram on cancel
					sigc::connection connCalibDiag; ///< The connection calib diagram
					sigc::connection connFlashDiag; ///< The connection flash diagram
					sigc::connection connBrightnessDiag;	///< The connection brightness diagram
					sigc::connection connRefreshAlarm;  ///< The connection refresh alarm
					sigc::connection connRefreshBC; ///< The connection refresh bc
					sigc::connection connRefreshSC; ///< The connection refresh screen
					sigc::connection connRefreshPrinter;	///< The connection refresh printer
					sigc::connection connRefreshPrinterOnOk;	///< The connection refresh printer on ok
					sigc::connection connRefreshPrinterOnCancel;	///< The connection refresh printer on cancel
					sigc::connection connRefreshCalib;  ///< The connection refresh calib
					sigc::connection connRefreshFlash;  ///< The connection refresh flash
					sigc::connection connRefreshBrightness; ///< The connection refresh brightness

					Smartmatic::SAES::GUI::Widgets::CalibrationDiagnosisWidget* calibrationWidget;  ///< The calibration widget
					Smartmatic::SAES::GUI::Widgets::BarCodeDiagnosisWidget* bcreaderWidget; ///< The bcreader widget
					Smartmatic::SAES::GUI::Widgets::PrinterDiagnosisWidget* printerWidget;  ///< The printer widget
					Smartmatic::SAES::GUI::Widgets::SmartCardReaderDiagnosisWidget* screaderWidget; ///< The screader widget
					Smartmatic::SAES::GUI::Widgets::AlarmBoxDiagnosisWidget* alarmWidget;   ///< The alarm widget
					Smartmatic::SAES::GUI::Widgets::FlashDiagnosisWidget* flashWidget;  ///< The flash widget
					Smartmatic::SAES::GUI::Widgets::BrightnessDiagnosisWidget* brightnessWidget;	///< The brightness widget

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}


#endif // _ALL_DIAGNOSIS_FUNCTIONALITY_H_
