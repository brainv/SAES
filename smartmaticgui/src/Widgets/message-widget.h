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

#ifndef _MESSAGE_WIDGET_H_

/**
 * @brief	Gets the message widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _MESSAGE_WIDGET_H_

#include <gtkmm.h>
#include "Widgets/smartmatic-button.h"
#include "Configuration/label-configuration.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class MessageWidget: public Gtk::Frame 
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	widgetChild	If non-null, the widget child.
				 */

				MessageWidget(Gtk::Widget* widgetChild);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	widgetChild	If non-null, the widget child.
				 * @param	showButton		   	true to show, false to hide the button.
				 * @param	timerToClose	   	The timer to close.
				 * @param	buttonText		   	The button text.
				 */

				MessageWidget(Gtk::Widget* widgetChild, bool showButton, int timerToClose, std::string buttonText = "");

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~MessageWidget();

				/**
				 * @brief	signals definitions.
				 */

				typedef sigc::signal<void> type_close_clicked;

				/**
				 * @brief	signals connect methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_close_clicked close_clicked();

				/**
				 * @brief	Closes a button set name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	name	The name.
				 */

				void closeButtonSetName(std::string name);

			protected:
	            /**
        		 * @brief signals declaration
	             */
				type_close_clicked m_close_clicked; ///< The close clicked

				sigc::connection connector_close;   ///< The connector close

				/**
				 * @brief	Executes the timeout action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	timer	The timer.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool on_timeout(int timer);

				/**
				 * @brief	Handles close button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_closeButton_clicked();

			private:
				Gtk::VBox* vertBox; ///< The vertical box
				Gtk::Alignment* totalAlignment; ///< The total alignment
				Gtk::Alignment* buttonAlignment;	///< The button alignment
				Smartmatic::GUI::Widgets::SmartmaticButton* closeButton;	///< The close button
				
			};
		}
	}
}

#endif // _MESSAGE_WIDGET_H_
