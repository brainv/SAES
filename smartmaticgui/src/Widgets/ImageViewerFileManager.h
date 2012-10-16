/*
 * ImageViewerFileManager.h
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include <iostream>
#include <list>
#include <gtkmm.h>

/**
 * @brief	Gets the "c".
 *
 * @return	The "c".
 */

extern "C" {
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
}

#ifndef IMAGEVIEWERFILEMANAGER_H_

/**
 * @brief	Gets the imageviewerfilemanager h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define IMAGEVIEWERFILEMANAGER_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ImageViewerFileManager
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					ImageViewerFileManager();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual ~ImageViewerFileManager();

					/**
					 * @brief	Gets the first file.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The first file.
					 */

					Glib::ustring getFirstFile();

					/**
					 * @brief	Gets the next file.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The next file.
					 */

					Glib::ustring getNextFile();

					/**
					 * @brief	Gets the previous file.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The previous file.
					 */

					Glib::ustring getPreviousFile();

					/**
					 * @brief	Gets the current file.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The current file.
					 */

					Glib::ustring getCurrentFile();

					/**
					 * @brief	Gets the have multiple files.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool haveMultipleFiles(void);

					/**
					 * @brief	Filter filename.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	filename	Filename of the file.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool filterFilename(Glib::ustring filename);

					/**
					 * @brief	Opens the files.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	basePath	Full pathname of the base file.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool OpenFiles( Glib::ustring basePath );

				protected:

					/**
					 * @brief	Showfiles this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void showfiles();
					Glib::ustring result;   ///< The result

				private:
					bool initialised;   ///< true to initialised
					std::vector <Glib::ustring> filenames;  ///< The filenames
					std::vector<Glib::ustring>::iterator file_iterator; ///< The file iterator
					int currentIndex;   ///< The current index
			};
		}
	}
}

#endif /* IMAGEVIEWERFILEMANAGER_H_ */
