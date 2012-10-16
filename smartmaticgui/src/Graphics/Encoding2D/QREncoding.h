/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Freddy Gomez 2011 <fgomez@smartmatic.com>
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

#ifndef _QRENCODING_H_

/**
 * @brief	Gets the qrencoding h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _QRENCODING_H_

#include <gtkmm.h>
#include <qrencode.h>
#include "System/Exception/QREncodingException.h"
#include <Log/ISMTTLog.h>


namespace Smartmatic
{
	namespace Graphics
	{
		namespace Encoding2D
		{

			class QREncoding
			{
				public:

				/**
				 * @brief	Generate QRcode.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	toEncode	data to encode.
				 * @param	length				size of data.
				 * @param	pixelSize			Size of the pixel.
				 * @param	margin				of bitmap.
				 * @param	level				correction Level.
				 * @param	symbolVersion   	@throw QREncondingException.
				 *
				 * @return	The symbol.
				 */

				static Glib::RefPtr<Gdk::Bitmap> GenerateSymbol(guchar* toEncode,
					                                            guint length,gint pixelSize = 3,
					                                            gint margin = 3, 
					                                            QRecLevel level = QR_ECLEVEL_L,
					                                            gint symbolVersion = 0 )
				throw (Smartmatic::System::Exception::QREncodingException);

				protected:

				private:

				/**
				 * @brief	Convert to bitmap a QRCode symbol.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	symbol	QRcode
				 * 							@param margin.
				 * @param	margin		  	The margin.
				 * @param	pixelSize	  	of bitmap.
				 *
				 * @return	.
				 */

				static Glib::RefPtr<Gdk::Bitmap> ConvertToBitmap(QRcode* symbol, 
				                                                 guint margin,
				                                                 guint pixelSize );
				static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

			};
		}
	}
}
#endif // _QRENCODING_H_
