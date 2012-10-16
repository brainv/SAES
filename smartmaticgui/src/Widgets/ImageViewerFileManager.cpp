/*
 * ImageViewerFileManager.cpp
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include "ImageViewerFileManager.h"
#include "System/IO/Directory.h"

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::IO;

ImageViewerFileManager::ImageViewerFileManager()
{
	initialised = false;
};

ImageViewerFileManager::~ImageViewerFileManager()
{
	filenames.clear();
};

Glib::ustring ImageViewerFileManager::getFirstFile()
{
	currentIndex = 0;
	return filenames[0];
};

Glib::ustring ImageViewerFileManager::getNextFile()
{
	Glib::ustring file = "";

	if(currentIndex != (int)(filenames.size() -1))
		file = filenames[++currentIndex];
	else
	{
		file = filenames[0];
		currentIndex = 0;
	}

	return file;
};

Glib::ustring ImageViewerFileManager::getPreviousFile()
{
	Glib::ustring file = "";

	if(currentIndex == 0)
		file = filenames[filenames.size() -1];
	else
	{
		file = filenames[--currentIndex];
	}

	return file;
};

Glib::ustring ImageViewerFileManager::getCurrentFile()
{
	Glib::ustring file = "";

	if(currentIndex != (int)(filenames.size() -1))
		file = filenames[currentIndex];
	else
	{
		file = filenames[0];
		currentIndex = 0;
	}

	return file;
};

bool ImageViewerFileManager::haveMultipleFiles(void)
{
	bool result = false;

	if(filenames.size() > 1)
		result = true;

	return result;
};

bool ImageViewerFileManager::filterFilename(Glib::ustring filename)
{
	if( filename.find(".jpg") != Glib::ustring::npos ||
			filename.find(".JPG") != Glib::ustring::npos ||
			filename.find(".gif") != Glib::ustring::npos ||
			filename.find(".GIF") != Glib::ustring::npos ||
			filename.find(".png") != Glib::ustring::npos ||
			filename.find(".PNG") != Glib::ustring::npos ||
			filename.find(".bmp") != Glib::ustring::npos ||
			filename.find(".BMP") != Glib::ustring::npos ||
			filename.find(".xpm") != Glib::ustring::npos ||
			filename.find(".XPM") != Glib::ustring::npos ||
			filename.find(".pcx") != Glib::ustring::npos ||
			filename.find(".PCX") != Glib::ustring::npos ||
			filename.find(".pgm") != Glib::ustring::npos ||
			filename.find(".PGM") != Glib::ustring::npos ||
			filename.find(".ppm") != Glib::ustring::npos ||
			filename.find(".PPM") != Glib::ustring::npos ||
			filename.find(".tiff") != Glib::ustring::npos ||
			filename.find(".TIFF") != Glib::ustring::npos ||
			filename.find(".tif") != Glib::ustring::npos ||
			filename.find(".TIF") != Glib::ustring::npos ||
			filename.find(".tga") != Glib::ustring::npos ||
			filename.find(".TGA") != Glib::ustring::npos ||
			filename.find(".pbm") != Glib::ustring::npos ||
			filename.find(".PBM") != Glib::ustring::npos ||
			filename.find(".ppm") != Glib::ustring::npos ||
			filename.find(".PPM") != Glib::ustring::npos ||
			filename.find(".svg") != Glib::ustring::npos ||
			filename.find(".SVG") != Glib::ustring::npos )
			return true;

	return false;
};

bool ImageViewerFileManager::OpenFiles( Glib::ustring basePath )
{
	std::vector<std::string> files;
	Directory::GetFiles((std::string)basePath, files, false, false);

	return false;
};
