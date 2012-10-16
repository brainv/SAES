/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMARTMATIC_ENTRY_DATE_TIME_H_

/**
 * @brief	Gets the smartmatic entry date time h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_ENTRY_DATE_TIME_H_

#include <gtkmm.h>
#include "smartmatic-entry-number.h"
#include <locale.h>
#include <time.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticEntryDateTime: public Gtk::HBox
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	complete  	true to complete.
				 * @param	widthEntry	The width entry.
				 * @param	spacing   	The spacing.
				 */

				SmartmaticEntryDateTime(bool complete, int widthEntry, int spacing);

				/**
				 * @brief	Sets the labels.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	str_year	The string year.
				 * @param	str_mon 	The string mon.
				 * @param	str_day 	The string day.
				 * @param	str_hour	The string hour.
				 * @param	str_min 	The string minimum.
				 * @param	str_sec 	The string security.
				 */

				void SetLabels(Glib::ustring str_year, Glib::ustring str_mon,
				               Glib::ustring str_day, Glib::ustring str_hour,
				               Glib::ustring str_min, Glib::ustring str_sec);

				/**
				 * @brief	Sets a time.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	timeFormat	The time format.
				 */

				void SetTime(struct tm timeFormat);

				/**
				 * @brief	Protected. 
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				struct tm GetTime();

				/**
				 * @brief	Clears this object to its blank/initial state.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void Clear();

				/**
				 * @brief	Sets a sensitive.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	isSensitive	true if is sensitive.
				 */

				void SetSensitive(bool isSensitive = true);

			protected:

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	complete  	true to complete.
				 * @param	widthEntry	The width entry.
				 * @param	spacing   	The spacing.
				 */

				void Initialize(bool complete, int widthEntry, int spacing);

				/**
				 * @brief	Sets the labels.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetLabels();
				
				SmartmaticEntryNumber* entry_year;  ///< The entry year
				SmartmaticEntryNumber* entry_mon;   ///< The entry mon
				SmartmaticEntryNumber* entry_day;   ///< The entry day
				SmartmaticEntryNumber* entry_hour;  ///< The entry hour
				SmartmaticEntryNumber* entry_min;   ///< The entry minimum
				SmartmaticEntryNumber* entry_sec;   ///< The entry security

				Gtk::Label* label_year; ///< The label year
				Gtk::Label* label_mon;  ///< The label mon
				Gtk::Label* label_day;  ///< The label day
				Gtk::Label* label_hour; ///< The label hour
				Gtk::Label* label_min;  ///< The label minimum
				Gtk::Label* label_sec;  ///< The label security

				Glib::ustring str_year; ///< The string year
				Glib::ustring str_mon;  ///< The string mon
				Glib::ustring str_day;  ///< The string day
				Glib::ustring str_hour; ///< The string hour
				Glib::ustring str_min;  ///< The string minimum
				Glib::ustring str_sec;  ///< The string security
			};
		}
	}
}

#endif // _SMARTMATIC_ENTRY_DATE_TIME_H_
