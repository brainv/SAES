/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
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

#ifndef _INFO_WIDGET_H_

/**
 * @brief	Gets the information widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _INFO_WIDGET_H_

#include <iostream>
#include <string.h>
#include <map>
#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{

			class InfoWidget: public Gtk::Frame
			{
				
			public:		

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	info	The information.
					 */

					InfoWidget (std::vector< std::vector<std::string> > & info);

					/**
					 * @brief	Set string vectors.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	info	The information.
					 */

					void SetVector (std::vector< std::vector<std::string> > & info);

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~InfoWidget();
	
			protected:


			private:
				Gtk::VBox *vbox;	///< The vbox
				Gtk::HBox *hbox;	///< The hbox
				Gtk::Label *information;	///< The information
				Gtk::EventBox *eventBox;	///< The event box
				Gtk::EventBox *informationeventBox; ///< The informationevent box
				std::vector<Gtk::Label*> vectorLabel; ///< The vector label
			};
		}
	}
}





#endif // _INFO_WIDGET_H_
