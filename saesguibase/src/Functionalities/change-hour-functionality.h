/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * changehourfunctionality
 * Copyright (C)  2010 <>
 * 
 * changehourfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * changehourfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CHANGE_HOUR_FUNCTIONALITY_EASIER_H_
#define _CHANGE_HOUR_FUNCTIONALITY_EASIER_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Log/ISMTTLog.h>
#include <Widgets/smartmatic-entry.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
      
				class ChangeHourFunctionality : public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{	
	
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

				/**
				 * @brief	Check string and add zero.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @param	input	The input.
				 *
				 * @return	.
				 */

				std::string checkStringAndAddZero(std::string input);

				/**
				 * @brief	Gets the update.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @return	.
				 */

				int updateDate();
				/**
				 * @brief method delete all element
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				virtual void deleteElement();

				private:	

				Smartmatic::SAES::Configuration::ChangeHourFunctionalityConfiguration config;

				static ChangeHourFunctionality *current_instance;   ///< The current instance

				/**
				 * @brief	Sets a timer.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @param [in,out]	tv	The tv.
				 * @param	sec		  	The security.
				 *
				 * @return	.
				 */

				int SetTimer(struct timeval &tv, time_t sec);

				/**
				 * @brief	Check timer.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @param [in,out]	tv	The tv.
				 * @param	sec		  	The security.
				 *
				 * @return	.
				 */

				int CheckTimer(struct timeval &tv, time_t sec);
				bool firstTime; ///< true to first time
				bool isComingFrom;  ///< true if is coming from
				bool killThread;	///< true to kill thread
				sigc::connection conn;  ///< The connection

				/**
				 * @brief	Label hour title. 
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				struct timeval tv;
				Gtk::Window window; ///< The window
				Gtk::AspectFrame* frameDateHour;	///< The frame date hour
				Gtk::VBox*  vboxDateHour;   ///< The vbox date hour
				Gtk::Table* table2;	///<The table 2
				Gtk::Label* labelCurrentDate;   ///< Date of the label current
				Gtk::Label* labelCurrentDateValue;  ///< The label current date value
				Gtk::Label* labelDateTitle; ///< The label date title
				Gtk::Label* labelHourTitle; ///< The label hour title
				Gtk::Label* labelDay;   ///< The label day
				Gtk::Label* labelMonth; ///< The label month
				Gtk::Label* labelYear;  ///< The label year
				Gtk::Label* labelHour;  ///< The label hour
				Gtk::Label* labelMins;  ///< The label mins
				Gtk::Label* labelSecs;  ///< The label in seconds
				Gtk::Image* imageDate;  ///< Date of the image
				Gtk::Image* imageHour;  ///< The image hour
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonApplyNewDateHour; ///< The button apply new date hour
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonDayUp;	///< The button day up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonDayDown;  ///< The button day down
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonMonthUp;  ///< The button month up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonMonthDown;	///< The button month down
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonYearUp;   ///< The button year up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonYearDown; ///< The button year down
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonHourUp;   ///< The button hour up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonHourDown; ///< The button hour down
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonMinsUp;   ///< The button mins up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonMinsDown; ///< The button mins down
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonSecondsUp;	///< The button seconds up
				Smartmatic::GUI::Widgets::SmartmaticButton* buttonSecondsDown;  ///< The button seconds down
				Smartmatic::GUI::Widgets::SmartmaticEntry* entryDay;   ///< The entry day
				Smartmatic::GUI::Widgets::SmartmaticEntry* entryMonth; ///< The entry month
				Smartmatic::GUI::Widgets::SmartmaticEntry* entryYear;  ///< The entry year
				Smartmatic::GUI::Widgets::SmartmaticEntry* entryHour;  ///< The entry hour
				Smartmatic::GUI::Widgets::SmartmaticEntry* entryMin;   ///< The entry minimum
				Smartmatic::GUI::Widgets::SmartmaticEntry* entrySec;   ///< The entry security
	
				bool isFrameEntry;  ///< true if is frame entry
				bool hourSet;   ///< true to hour set

				/**
				 * @brief	Executes the timeout action.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @param	timer_number	The timer number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool on_timeout(int timer_number);
				std::string s_day;  ///< The day
	
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
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				ChangeHourFunctionality();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				~ChangeHourFunctionality();

				/**
				 * @brief	Gets the current.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static ChangeHourFunctionality* Current();

				/**
				 * @brief	Handles button apply clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonApply_clicked();

				/**
				 * @brief	Handles button day up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonDayUp_clicked();

				/**
				 * @brief	Handles button day down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonDayDown_clicked();

				/**
				 * @brief	Handles button month up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonMonthUp_clicked();

				/**
				 * @brief	Handles button month down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonMonthDown_clicked();

				/**
				 * @brief	Handles button year up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonYearUp_clicked();

				/**
				 * @brief	Handles button year down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonYearDown_clicked();

				/**
				 * @brief	Handles button hour up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonHourUp_clicked();

				/**
				 * @brief	Handles button hour down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonHourDown_clicked();

				/**
				 * @brief	Handles button mins up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonMinsUp_clicked();

				/**
				 * @brief	Handles button mins down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonMinsDown_clicked();

				/**
				 * @brief	Handles button seconds up clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonSecondsUp_clicked();

				/**
				 * @brief	Handles button seconds down clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 */

				void on_buttonSecondsDown_clicked();

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
				 * @brief	Gets the window title.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @return	The window title.
				 */

				std::string GetWindowTitle();

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
				 * @brief	Gets the frame.
				 *
				 * @author	Luiggi.mendez
				 * @date	28/04/2011
				 *
				 * @return	null if it fails, else the frame.
				 */

				Gtk::Widget* GetFrame();

				static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}

#endif // _CHANGE_HOUR_FUNCTIONALITY_H_
