/**
 * @file	Path.h
 *
 * @brief	Header file to the path class.
 */

#ifndef _PATH_CLASS_H_
#define _PATH_CLASS_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>

namespace Smartmatic
{
	namespace System		
	{
		namespace IO
		{
			/**
			 * @class	Path. 
			 * @brief	Class utilities for Path manager. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class Path
			{

				public:

				/**
				 * @brief	Combines the given file.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path1	The first path.
				 * @param	path2	The second path.
				 *
				 * @return	.
				 */

				static std::string Combine(const std::string & path1, const std::string & path2);

				/**
				 * @brief	Gets a file name.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	The file name in the given path.
				 */

				static std::string GetFileName(const std::string& path);

				/**
				 * @brief	Gets a file name with out extension.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	The file name with out extension.
				 */

				static std::string GetFileNameWithOutExtension(const std::string path);

				/**
				 * @brief	Gets a full path file name with out extension.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	The full path file name with out extension.
				 */

				static std::string GetFullFileNameWithOutExtension(const std::string path);

				/**
				 * @brief	Gets a file extension.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	The file extension.
				 */

				static std::string GetFileExtension(const std::string path);

				/**
				 * @brief	Gets a directory.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	The directory.
				 */

				static std::string GetDirectory(const std::string& path);

				/**
				 * @brief	Gets the current directory.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @return	The current directory.
				 */

				static std::string GetCurrentDirectory();

				/**
				 * @brief	Gets combine name file.
				 * @param   file
				 * @param   combine
				 * @author	Yadickson Soto yadickson.soto@smartmatic.com
				 * @date	03/08/2011
				 *
				 * @return	new file name
				 */

				static std::string combineFileName( std::string file, std::string combine );

				/**
				 * @brief	Gets combine name file.
				 * @param   file
				 * @param   combine
				 * @param   result
				 * @author	Yadickson Soto yadickson.soto@smartmatic.com
				 * @date	03/08/2011
				 *
				 */

				static void combineFileName( std::string file, std::list < std::string > & combine, std::list < std::string > & result );

			};
		}
	}
}

#endif //  _PATH_CLASS_H_
