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
/**
 * @file image-selection-window.h
 * @brief widget that displays images, and one can be selected
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _IMAGE_SELECTION_WIDGET_H_

/**
 * @brief	Gets the image selection widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _IMAGE_SELECTION_WIDGET_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ImageSelectionWidget: public Gtk::HBox 
			{
			public:

				/**
				 * @brief	constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	imagesPath	path of images.
				 * @param	imagesCode	path of images.
				 */

				ImageSelectionWidget(std::vector<std::string> imagesPath, std::vector<std::string> imagesCode);

				/**
				 * @brief	destructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~ImageSelectionWidget();

				/**
				 * @brief	signal definition.
				 */

				typedef sigc::signal<void, std::string> type_clicked;

				/**
				 * @brief	signal connect method.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_clicked clicked();
					
			protected:
				/**
				 * @brief signals declaration
				 */
				type_clicked m_clicked; ///< The clicked

				/**
				 * @brief	event box click connect method.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 * @param	imagePath	 	Full pathname of the image file.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool on_image_clicked(GdkEventButton* event, std::string imagePath);

			private:
				/**
				 * child widgets
				 */
				std::vector<Gtk::EventBox*> events; ///< The events
				std::vector<Gtk::Image*> images;	///< The images
			};
		}
	}
}

#endif // _IMAGE_SELECTION_WIDGET_H_
