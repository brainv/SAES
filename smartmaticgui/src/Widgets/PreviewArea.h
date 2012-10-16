/*
 * PreviewArea.h
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include <iostream>
#include <gtkmm.h>
#include <cairomm/cairomm.h>

#ifndef PREVIEWAREA_H_

/**
 * @brief	Gets the previewarea h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define PREVIEWAREA_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class PreviewArea : public Gtk::DrawingArea
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					PreviewArea();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual ~PreviewArea();

					/**
					 * @brief	Loads.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param		The.
					 * @param		true to.
					 */

					void load( Glib::ustring, bool );

				protected:
					Glib::RefPtr<Gdk::Pixbuf> ImagePixbuf;  ///< The image pixbuf

					/**
					 * @brief	Raises the expose event.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]		If non-null, the.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool on_expose_event(GdkEventExpose*);

					/**
					 * @brief	Pixbuf load.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param		The.
					 * @param		The.
					 * @param		The.
					 */

					void PixbufLoad( Glib::ustring,int,int );
			};
		}
	}
}

#endif /* PREVIEWAREA_H_ */
