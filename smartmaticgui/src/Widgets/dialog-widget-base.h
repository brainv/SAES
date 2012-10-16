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

#ifndef _DIALOG_WIDGET_BASE_H_

/**
 * @brief	Gets the dialog widget base h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _DIALOG_WIDGET_BASE_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class DialogWidgetBase: public Gtk::VBox
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				DialogWidgetBase();		

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~DialogWidgetBase();

				/**
				 * @brief	Sets a base widgets base name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	baseName	Name of the base.
				 */

				static void SetBaseWidgetsBaseName(std::string baseName);

				/**
				 * @brief	Sets a frame header name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	frameHeaderName	Name of the frame header.
				 */

				void SetFrameHeaderName(std::string frameHeaderName);

				/**
				 * @brief	Sets a frame client area name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	frameClientAreaName	Name of the frame client area.
				 */

				void SetFrameClientAreaName(std::string frameClientAreaName);

				/**
				 * @brief	Sets a frame footer name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	frameFooterName	Name of the frame footer.
				 */

				void SetFrameFooterName(std::string frameFooterName);

				/**
				 * @brief	Sets a border frame header name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	borderFrameHeaderName	Name of the border frame header.
				 */

				void SetBorderFrameHeaderName(std::string borderFrameHeaderName);

				/**
				 * @brief	Sets a borderframe client area name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	borderframeClientAreaName	Name of the borderframe client area.
				 */

				void SetBorderframeClientAreaName(std::string borderframeClientAreaName);

				/**
				 * @brief	Sets a borderframe footer name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	borderframeFooterName	Name of the borderframe footer.
				 */

				void SetBorderframeFooterName(std::string borderframeFooterName);

			protected:
				Gtk::Frame frameHeader; ///< The frame header
				Gtk::Frame frameClientArea; ///< The frame client area
				Gtk::Frame frameFooter; ///< The frame footer
				Gtk::Frame borderFrameHeader;   ///< The border frame header
				Gtk::Frame borderframeClientArea;   ///< The borderframe client area
				Gtk::Frame borderframeFooter;   ///< The borderframe footer
				Gtk::EventBox frameHeaderEventBox;  ///< The frame header event box
				Gtk::EventBox frameClientAreaEventBox;  ///< The frame client area event box
				Gtk::EventBox frameFooterEventBox;  ///< The frame footer event box
					
			private:

				static std::string widgetBaseName;  ///< Name of the widget base

				/**
				 * @brief	Sets a widget name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	widget	The widget.
				 * @param	baseName	  	Name of the base.
				 * @param	name		  	The name.
				 */

				void SetWidgetName(Gtk::Widget & widget, std::string baseName, std::string name); 

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void Initialize();				
			};
		}
	}
}

#endif // _DIALOG_WIDGET_BASE_H_
