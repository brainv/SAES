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

#include "Graphics/Encoding2D/QREncoding.h"
#include <queue>
#include <errno.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

#define ERROR_INIT_QRCODE_ENOMEM N_("Smartmatic.Graphics.Encoding2D.QREncoding.InitQRCodeUnableToAllocateMemory") ///< text for log
#define ERROR_INIT_QRCODE_EINVAL N_("Smartmatic.Graphics.Encoding2D.QREncoding.InitQRCodeInvalidArguments") ///< text for log

using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* QREncoding::logger = SMTTLogManager::GetLogger("Smartmatic.Graphics.Encoding2D.QREncoding",GETTEXT_PACKAGE);

Glib::RefPtr<Gdk::Bitmap> QREncoding::GenerateSymbol(guchar* toEncode,
                                                     guint length,
                                                     gint pixelSize,
                                                     gint margin,
                                                     QRecLevel level,
                                                     gint symbolVersion )
													 throw (QREncodingException)
{
		QRcode* qrcod(NULL);
		QRinput * qrInput(NULL);

		qrInput = QRinput_new2(symbolVersion, level);
		if(qrInput == NULL)
		{
			if(errno == ENOMEM)
				 throw QREncodingException(_(ERROR_INIT_QRCODE_ENOMEM),
				                            N_(ERROR_INIT_QRCODE_ENOMEM), logger);
			else if(errno == EINVAL)
				throw QREncodingException(_(ERROR_INIT_QRCODE_EINVAL),
				                            N_(ERROR_INIT_QRCODE_EINVAL), logger);
		}

		
		if(QRinput_append(qrInput, QR_MODE_8, length,toEncode) != 0)
		{
			if(errno == ENOMEM)
				 throw QREncodingException(_(ERROR_INIT_QRCODE_ENOMEM),
				                            N_(ERROR_INIT_QRCODE_ENOMEM), logger);
			else if(errno == EINVAL)
				throw QREncodingException(_(ERROR_INIT_QRCODE_EINVAL),
				                            N_(ERROR_INIT_QRCODE_EINVAL), logger);
		}
	
		qrcod = QRcode_encodeInput(qrInput);
		if(qrcod == NULL)
		{
			if(errno == ENOMEM)
				 throw QREncodingException(_(ERROR_INIT_QRCODE_ENOMEM),
				                            N_(ERROR_INIT_QRCODE_ENOMEM), logger);
			else if(errno == EINVAL)
				throw QREncodingException(_(ERROR_INIT_QRCODE_EINVAL),
				                            N_(ERROR_INIT_QRCODE_EINVAL), logger);
		}
	
		QRinput_free(qrInput);
		

		Glib::RefPtr<Gdk::Bitmap> bitmap =	QREncoding::ConvertToBitmap(qrcod, margin,pixelSize );
	
		QRcode_free(qrcod);

	return bitmap;
}


Glib::RefPtr<Gdk::Bitmap> QREncoding::ConvertToBitmap(QRcode* symbol, 
                                                      guint margin,
                                                      guint pixelSize )
{
	guint realLineWidth = (symbol->width + (margin * 2)) * pixelSize;
	guint lineSizeInBytes = (realLineWidth + 7) / 8;
	
	guchar* workingLineStart(NULL);
	guchar* workingLineCursor(NULL);
	guchar* bigBuffer(NULL);
	guchar* symbolDataPtr(NULL);
	std::queue<guchar*> buffers;

	
	gint8 bitPosition(0); 


	//Add the top margin
	for( guint topMarginLine = 0; topMarginLine<pixelSize*margin;topMarginLine++)
	{
		workingLineStart = static_cast<guchar*>( g_malloc (lineSizeInBytes));
		memset(workingLineStart, 0xFF, lineSizeInBytes);  //blank pixel
		buffers.push(workingLineStart);
	}


	//Add the code lines
	symbolDataPtr = symbol->data;
	
	for(gint symbolLineCounter=0; symbolLineCounter<symbol->width; symbolLineCounter++) //iterate over the number of lines or rows
	{
		bitPosition = 0;  
		
		workingLineStart = static_cast<guchar*>( g_malloc (lineSizeInBytes));
		memset(workingLineStart, 0xFF, lineSizeInBytes);  //blank pixel
				
		workingLineCursor = workingLineStart;
		//skip the margin
		workingLineCursor += margin * pixelSize / 8;
		//adjust the bit position
		bitPosition =  (margin * pixelSize % 8);

		//iterate over the pixel in a row
		for(gint symbolLinePixel=0; symbolLinePixel<symbol->width; symbolLinePixel++) 
		{
			//Set pixel as many time as the size of the pixel
			for(guint samePixel=0; samePixel<pixelSize; samePixel++) {
				*workingLineCursor ^= (*symbolDataPtr & 1) << bitPosition;
				bitPosition++;
				if(bitPosition > 7) {
					workingLineCursor++;
					bitPosition = 0;
				}
			}
			symbolDataPtr++;
		}

		buffers.push(workingLineStart);
		
		for( guint sameLineCounter=1; sameLineCounter<pixelSize; sameLineCounter++) 
		{
			//COPY AND insert
			workingLineCursor = static_cast<guchar*>( g_malloc (lineSizeInBytes));
			memcpy(workingLineCursor,workingLineStart, lineSizeInBytes);
			buffers.push(workingLineCursor);
		}
	}
	
	//add the bottom margin
	for( guint bottomMarginLine = 0; bottomMarginLine<pixelSize*margin;bottomMarginLine++)
	{
		workingLineStart = static_cast<guchar*> (g_malloc (lineSizeInBytes));
		memset(workingLineStart, 0xFF, lineSizeInBytes); //blank pixel
		buffers.push(workingLineStart);
	}


	//create a big buffer and copy the pixels inside
	bigBuffer	= static_cast<guchar*> (g_malloc (lineSizeInBytes*buffers.size()));
	workingLineCursor = bigBuffer;
	//free the buffer
	while (!buffers.empty())
	{
		workingLineStart = buffers.front();
		memcpy(workingLineCursor,workingLineStart, lineSizeInBytes);
		workingLineCursor += lineSizeInBytes;
		g_free(workingLineStart);
	    buffers.pop();
	}

	Glib::RefPtr<Gdk::Bitmap> bitmap (Gdk::Bitmap::create( (char*)bigBuffer, realLineWidth,realLineWidth) );

	g_free(bigBuffer);
	
	return bitmap;	
}

