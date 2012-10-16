/*
 * ImageEventBox.h
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include <string>
#include <iostream>
#include <gtkmm.h>



#ifndef IMAGEEVENTBOX_H_

/**
 * @brief	Gets the imageeventbox h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define IMAGEEVENTBOX_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ImageEventBox : public Gtk::EventBox
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					ImageEventBox();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual ~ImageEventBox();

					/**
					 * @brief	Loads an image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	filename		   	Filename of the file.
					 * @param [in,out]	scalefactor	If non-null, the scalefactor.
					 * @param	interpType		   	Type of the interp.
					 * @param	width			   	The width.
					 * @param	height			   	The height.
					 */

					void LoadImage(	const Glib::ustring & filename, double * scalefactor, Gdk::InterpType interpType, int width, int height);

					/**
					 * @brief	Loads an image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	filename   	Filename of the file.
					 * @param	scalefactor	The scalefactor.
					 * @param	interpType 	Type of the interp.
					 */

					void LoadImage(	const Glib::ustring & filename, double scalefactor, Gdk::InterpType interpType);

					/**
					 * @brief	Scale image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	width			   	The width.
					 * @param	height			   	The height.
					 * @param [in,out]	scalefactor	If non-null, the scalefactor.
					 * @param	interpType		   	Type of the interp.
					 */

					void ScaleImage(int width, int height,double * scalefactor, Gdk::InterpType interpType);

					/**
					 * @brief	Scale image 2.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	width			   	The width.
					 * @param	height			   	The height.
					 * @param [in,out]	scalefactor	If non-null, the scalefactor.
					 * @param	interpType		   	Type of the interp.
					 */

					void ScaleImage2(int width,	int height,	double * scalefactor, Gdk::InterpType interpType);

					/**
					 * @brief	Scale image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	scalefactor	The scalefactor.
					 * @param	interpType 	Type of the interp.
					 */

					void ScaleImage(double scalefactor,	Gdk::InterpType interpType);

					/**
					 * @brief	Rotate image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	rotateby	The rotateby.
					 */

					void RotateImage(Gdk::PixbufRotation rotateby);

					/**
					 * @brief	Gets the image height.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The image height.
					 */

					int getImageHeight(void);

					/**
					 * @brief	Gets the image width.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The image width.
					 */

					int getImageWidth(void);

					/**
					 * @brief	Gets the image angle.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The image angle.
					 */

					int getImageAngle(void);

					/**
					 * @brief	Saves an image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	filename	Filename of the file.
					 * @param	filetype	The filetype.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool saveImage(Glib::ustring filename, Glib::ustring filetype);

					/**
					 * @brief	Query if this object is loaded.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	true if loaded, false if not.
					 */

					bool isLoaded(void);
					Glib::ustring iconpath; ///< The iconpath

				protected:
					Gtk::Image Image;   ///< The image

					int angle;  ///< The angle
					bool loaded;	///< true if the data was loaded
					bool modified;  ///< true if the data is modified

					Glib::RefPtr<Gdk::Pixbuf> imagePixbuf;  ///< The image pixbuf
					Glib::RefPtr<Gdk::Pixbuf> pixbufOriginal;   ///< The pixbuf original

					/**
					 * @brief	Clears the image.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void clearImage( void );
			};
		}
	}
}

#endif /* IMAGEEVENTBOX_H_ */
