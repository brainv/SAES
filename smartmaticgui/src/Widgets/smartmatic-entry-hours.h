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

#ifndef _SMARTMATIC_ENTRY_HOURS_H_

/**
 * @brief	Gets the smartmatic entry hours h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_ENTRY_HOURS_H_

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
			class SmartmaticEntryHours: public Gtk::HBox
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmartmaticEntryHours();


				/**
				 * @brief	Sets a sensitive.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	isSensitive	true if is sensitive.
				 */

				void SetSensitive(bool isSensitive = true);

				/**
				 * @brief	return the hours.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */					 
				int getHours();

				/**
				 * @brief	return the minutes.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */					 
   			    int getMins();

				/**
				 * @brief	return the seconds.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */					 
				int getSecs();

				/**
				 * @brief	Sets the labels.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	str_hour	The string hour.
				 * @param	str_min 	The string minimum.
				 * @param	str_sec 	The string security.
				 */

				void SetLabels(Glib::ustring str_hour,Glib::ustring str_min, Glib::ustring str_sec);

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	hours
				 * @param	mins
				 * @param	secs
				 */

				void Initialize(int hours, int mins, int secs);

				bool CheckFields();

				typedef sigc::signal<void, bool> fields_complete;

				fields_complete fields_complete_signal();

			protected:
				fields_complete m_fields_complete;   ///< The ballot clicked

				SmartmaticEntryNumber* entry_hour;  ///< The entry hour
				SmartmaticEntryNumber* entry_min;   ///< The entry minimum
				SmartmaticEntryNumber* entry_sec;   ///< The entry security


				Gtk::Label* label_hour; ///< The label hour
				Gtk::Label* label_min;  ///< The label minimum
				Gtk::Label* label_sec;  ///< The label security

				Glib::ustring str_hour; ///< The string hour
				Glib::ustring str_min;  ///< The string minimum
				Glib::ustring str_sec;  ///< The string security


				void TextInserted();


			};
		}
	}
}

#endif // _SMARTMATIC_ENTRY_HOURS_H_
