/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C)  2010 <>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HELP_WINDOW_H_

/**
 * @brief	Gets the help window h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _HELP_WINDOW_H_

#include <string>
#include <gtkmm.h>
#include <iostream>
#include "Windows/help-item.h"

/**
 * @brief	Gets the user interface file.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define UI_FILE "src/ui/help_window.ui"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Windows
		{
			class HelpWindow : public Gtk::Window
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	title  	The title.
				 * @param	content	The content.
				 */

				HelpWindow(std::string title, std::vector<Smartmatic::GUI::Windows::HelpItem> content);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~HelpWindow();

	
			protected:
	
			private:

				/**
				 * @brief	Builds a help.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	content	The content.
				 */

				void BuildHelp(std::vector<Smartmatic::GUI::Windows::HelpItem> content);

				/**
				 * @brief	Sets the initial configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetInitialConfiguration();

				/**
				 * @brief	Key pressed.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool key_pressed(GdkEventKey *event);

	
				Gtk::Table* main_table; ///< The main table
				Gtk::Table* key_value_table;	///< The key value table
				Gtk::Label* label_instructions; ///< The label instructions
				Gtk::Label* label_navigation_text;  ///< The label navigation text
				Gtk::Label* label_navigation_type;  ///< Type of the label navigation
				Gtk::Image* simple_navigation_image;	///< The simple navigation image
			};

		}
	}
}
#endif // _HELP_WINDOW_H_
