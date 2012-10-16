/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * bullet
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * bullet is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bullet is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CIRCLE_WIDGET_H_

/**
 * @brief	Gets the circle widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CIRCLE_WIDGET_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class CircleWidget : public Gtk::DrawingArea
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				CircleWidget();

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	red1  	The first red.
				 * @param	green1	The first green.
				 * @param	blue1 	The first blue.
				 * @param	alpha1	The first alpha.
				 * @param	red2  	The second red.
				 * @param	green2	The second green.
				 * @param	blue2 	The second blue.
				 * @param	alpha2	The second alpha.
				 */

				CircleWidget(float red1, float green1, float blue1, float alpha1,
							 float red2, float green2, float blue2, float alpha2);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual ~CircleWidget();

				/**
				 * @brief	Sets a mark.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	setFirst	true to set first.
				 */

				void SetMark(bool setFirst = true);

			protected:
				//Override default signal handler:

				/**
				 * @brief	Raises the expose event.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				virtual bool on_expose_event(GdkEventExpose* event);

				float backRed1, backGreen1, backBlue1, backAlpha1;  ///< The first back alpha
				float backRed2, backGreen2, backBlue2, backAlpha2;  ///< The second back alpha
	
				bool setFirst;  ///< true to set first
			};
		}
	}
}

#endif // _CIRCLE_WIDGET_H_
