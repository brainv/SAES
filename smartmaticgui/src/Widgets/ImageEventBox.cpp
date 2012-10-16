/*
 * ImageEventBox.cpp
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include "ImageEventBox.h"

extern "C" {
#include <libintl.h>
}

using namespace Smartmatic::GUI::Widgets;

ImageEventBox::ImageEventBox() : Image()
{
	add(Image);
	show_all_children();
	loaded = false;
};

ImageEventBox::~ImageEventBox()
{
	clearImage();
};

void ImageEventBox::LoadImage(const Glib::ustring & filename, double * scalefactor, Gdk::InterpType interpType, int width, int height )
{
	try
	{
		//create base pixbuf
		pixbufOriginal = Gdk::Pixbuf::create_from_file(filename);
		loaded = true;

		if( width <= pixbufOriginal->get_width() || height <= pixbufOriginal->get_height() )
			ScaleImage(width, height, scalefactor, interpType);
		else
			ScaleImage(1.0, interpType), *scalefactor = 1.0;
	}
	catch(Gdk::PixbufError & error)
	{
		if( filename != "No file to load.")
		{
			std::cerr << "There has been an error allocating " << filename << std::endl;
			loaded = false;
			imagePixbuf = Gdk::Pixbuf::create_from_file( iconpath + (Glib::ustring) "unreadable.png" );
			Image.set(imagePixbuf);
		}
		else
		{
			clearImage();
		}
	}
	catch(Glib::FileError & error)
	{
		if( filename != "No file to load.")
		{
			std::cerr << "There has been an error loading the file" << filename << std::endl;
			loaded = false;
			imagePixbuf = Gdk::Pixbuf::create_from_file( iconpath + (Glib::ustring) "unreadable.png" );
			Image.set(imagePixbuf);
		}
		else
		{
			clearImage();
		}
	}
};

void ImageEventBox::LoadImage(	const Glib::ustring & filename, double scalefactor, Gdk::InterpType interpType)
{
	try
	{
		pixbufOriginal = Gdk::Pixbuf::create_from_file(filename);
		loaded = true;
		ScaleImage(scalefactor, interpType);
	}
	catch(Gdk::PixbufError & error)
	{
		if( filename != "No file to load.")
		{
			std::cerr << "There has been an error allocating " << filename << std::endl;
			loaded = false;
			imagePixbuf = Gdk::Pixbuf::create_from_file( iconpath + (Glib::ustring) "unreadable.png" );
			Image.set(imagePixbuf);
		}
		else
		{
			clearImage();
		}
	}
	catch(Glib::FileError & error)
	{
		if( filename != "No file to load.")
		{
			std::cerr << "There has been an error loading the file. \n\t"  << filename << std::endl;
			loaded = false;
			imagePixbuf = Gdk::Pixbuf::create_from_file( iconpath + (Glib::ustring) "unreadable.png" );
			Image.set(imagePixbuf);
		}
		else
		{
			clearImage();
		}
	}
};

void ImageEventBox::ScaleImage(int width, int height,double * scalefactor, Gdk::InterpType interpType)
{
	if(pixbufOriginal != 0 && loaded == true)
	{
		double ratioh = (double)height/(double)pixbufOriginal->get_height();
		double ratiow = (double)width/(double)pixbufOriginal->get_width();

		*scalefactor = ratioh;

		if( (*scalefactor) * (double)pixbufOriginal->get_width() > width )
			*scalefactor = ratiow;

		if( (*scalefactor) * (double)pixbufOriginal->get_height() > height )
			*scalefactor = ratioh;

		ScaleImage(*scalefactor,interpType);
	}
};

void ImageEventBox::ScaleImage2(int width,	int height,	double * scalefactor, Gdk::InterpType interpType)
{
	if(pixbufOriginal != 0 && loaded == true)
	{
		if( width <= pixbufOriginal->get_width() || height <= pixbufOriginal->get_height() )
	    {
    		double ratioh = (double)height/(double)pixbufOriginal->get_height();
    		double ratiow = (double)width/(double)pixbufOriginal->get_width();

    		*scalefactor = ratioh;

    		if( (*scalefactor) * (double)pixbufOriginal->get_width() > width )
    			*scalefactor = ratiow;

    		if( (*scalefactor) * (double)pixbufOriginal->get_height() > height )
    			*scalefactor = ratioh;

    		ScaleImage(*scalefactor,interpType);
   	    }
    	else
        	ScaleImage(1.0, interpType), *scalefactor = 1.0;
	}
};

void ImageEventBox::ScaleImage(double scalefactor,	Gdk::InterpType interpType)
{
	if(pixbufOriginal != 0 && loaded == true)
	{
		int new_width   = (int)(scalefactor * (double)pixbufOriginal->get_width());
		int new_height  = (int)(scalefactor * (double)pixbufOriginal->get_height());

		try
		{
			imagePixbuf =	pixbufOriginal->scale_simple(new_width, new_height, interpType);
			Image.set(imagePixbuf);
		}
		catch(Gdk::PixbufError & error)
		{
			std::cerr << "There has been a problem scaling the image." << std::endl;
		}
	}
};

void ImageEventBox::RotateImage(Gdk::PixbufRotation rotateby)
{
	if(pixbufOriginal != 0 && loaded == true)
	{
		try
		{
			imagePixbuf = imagePixbuf->rotate_simple(rotateby);
			pixbufOriginal = pixbufOriginal->rotate_simple(rotateby);

			Image.set(imagePixbuf);
			if		(angle == 0 && rotateby == Gdk::PIXBUF_ROTATE_COUNTERCLOCKWISE)
				angle = 270;
			else if	(angle == 270 && rotateby == Gdk::PIXBUF_ROTATE_CLOCKWISE)
				angle = 0;
			else
			{
				if( rotateby == Gdk::PIXBUF_ROTATE_CLOCKWISE )
					angle += 90;
				else if( rotateby == Gdk::PIXBUF_ROTATE_COUNTERCLOCKWISE )
					angle -= 90;
			}
		}
		catch(Gdk::PixbufError & error)
		{

		}
	}
};

int ImageEventBox::getImageHeight(void)
{
	return imagePixbuf->get_height();
};

int ImageEventBox::getImageWidth(void)
{
	return imagePixbuf->get_width();
};

int ImageEventBox::getImageAngle(void)
{
	return angle;
};

bool ImageEventBox::saveImage(Glib::ustring filename, Glib::ustring filetype)
{
	if ( filetype == "unsupported" )
			return false;

	try
	{
		pixbufOriginal->save(	filename, filetype );
		return true;
	}
	catch(Gdk::PixbufError & error)
	{
	}
	catch(Glib::FileError & error)
	{
	}

	return false;
}

bool ImageEventBox::isLoaded(void)
{
	return loaded;
}

void ImageEventBox::clearImage( void )
{
	loaded = false;
	Image.clear();
	pixbufOriginal.clear();
	imagePixbuf.clear();
};
