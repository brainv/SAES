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

#ifndef _BANNER_WIDGET_H_

/**
 * @brief	Gets the banner widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _BANNER_WIDGET_H_

#include <gtkmm.h>
#include <iostream>
#include "Widgets/smartmatic-button.h"
#include "Widgets/exit-button-listener.h"
#include "Widgets/help-button-listener.h"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
#include "Widgets/HelpExitButtons.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{

			class BannerWidget : public Gtk::HBox
			{
			public:		

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	exitListener	If non-null, the exit listener.
				 * @param	exitButton				true to exit button.
				 */

				BannerWidget(ExitButtonListener *exitListener, bool exitButton,
							 HelpButtonListener* helpListener, bool helpButton);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~BannerWidget();

				/**
				 * @brief	Exit button set sensitive.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	sensitive	true to sensitive.
				 */

				void exitButtonSetSensitive(bool sensitive);

				/**
				 * @brief	Exit button set visible.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	visible	true to show, false to hide.
				 */

				void exitButtonSetVisible(bool visible);

			    /**
			     * @brief	Exit button set name.
			     *
			     * @author	Luiggi.mendez
			     * @date	27/04/2011
			     *
			     * @param	name	The name.
			     */

			    void exitButtonSetName(std::string name);

			    /**
				 * @brief	Help button set sensitive.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	sensitive	true to sensitive.
				 */

				void helpButtonSetSensitive(bool sensitive);

				/**
				 * @brief	Help button set visible.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	visible	true to show, false to hide.
				 */

				void helpButtonSetVisible(bool visible);

				/**
				 * @brief	Help button set name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	name	The name.
				 */

				void helpButtonSetName(std::string name);
	
			protected:


			private:
				//Widgets of the Glade file
				Gtk::Image *image_banner;   ///< The image banner

				HelpExitButtons* helpExitButtons;


				/**
				 * @brief	Executes the button time elapsed action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	timer_number	The timer number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool On_Button_Time_Elapsed(int timer_number);

				/**
				 * @brief	Executes the timer timeout action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	timer_number	The timer number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool OnTimerTimeout(int timer_number);

				int formwidth;
			};
		}
	}
}




#endif // _BANNER_WIDGET_H_
