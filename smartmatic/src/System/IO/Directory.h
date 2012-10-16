/**
 * @file	Directory.h
 *
 * @brief	Header file to the directory class.
 */

#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <vector>
#include <string>
#include <fstream>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace System		
	{
		namespace IO
		{
			/**
			 * @class	Directory.
			 * @brief	Class utils for directory manager.
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class Directory
			{
				public:

				/**
				 * @brief	Gets the files.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path			Full pathname of the file.
				 * @param [in,out]	list	The list of files.
				 * @param	recursive   	true to process recursively, false to process locally only.
				 * @param	relative		true to relative.
				 */

				static void GetFiles(const std::string & path, std::vector<std::string>& list, bool recursive, bool relative);

				/**
				 * @brief	Gets a sub directories.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path			Full pathname of the file.
				 * @param [in,out]	list	The list of sub directories.
				 * @param	recursive   	true to process recursively, false to process locally only.
				 * @param	relative		true to relative.
				 */

				static void GetSubDirectories(const std::string & path, std::vector<std::string>& list, bool recursive, bool relative);

				/**
				 * @brief	Deletes the Directory in the given pathname.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	 	Full pathname of the file.
				 * @param	recursive	true to process recursively, false to process locally only.
				 */

				static void Delete(const std::string & path, bool recursive);

                /**
                 * @brief	Make de Directory in the  the given pathname.
                 *
                 * @author	Rafael.gasperi
                 * @date	28/04/2011
                 *
                 * @param	path	Full pathname of the file.
                 */

                static void Mkdir(const std::string & path);

				/**
				 * @brief	Empty directory in the given pathname.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	 	Full pathname of the file.
				 * @param	recursive	true to process recursively, false to process locally only.
				 */

				static void EmptyDirectory(const std::string & path, bool recursive);

				/**
				 * @brief	Queries if a given directory exists.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				static bool DirectoryExists(const std::string & path);	

				/**
				 * @brief	Queries if a given file exists.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				static bool FileExists(const std::string & path);	

				/**
				 * @brief	Gets a sub directories.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path			Full pathname of the file.
				 * @param [in,out]	list	The list of sub directories.
				 * @param	recursive   	true to process recursively, false to process locally only.
				 */

				static void GetSubDirectories(const std::string & path, std::vector<std::string>& list, bool recursive);

				/**
				 * @brief	Gets the files.
				 *
				 * @author	Rafael.gasperi
				 * @date	28/04/2011
				 *
				 * @param	path			Full pathname of the file.
				 * @param [in,out]	list	The list of files.
				 * @param	recursive   	true to process recursively, false to process locally only.
				 */

				static void GetFiles(const std::string & path, std::vector<std::string>& list, bool recursive);

				/**
				 * @brief   compare directories.
				 *
				 * @author  Yadickson Soto
				 * @date    13/02/2012
				 *
				 * @param [in,out]  directoryOne   The first directory.
				 * @param [in,out]  directoryTwo   The second directory.
				 * @param full compare all files
				 * @return  true if it succeeds, false if it fails.
				 */

				static bool compareDirectories(std::string & directoryOne, std::string & directoryTwo, bool full = true);


				/**
				 * @brief   compare directory structure.
				 *
				 * @author  Yadickson Soto
				 * @date    13/02/2012
				 *
				 * @param [in,out]  directoryOne   The first directory.
				 * @param [in,out]  directoryTwo   The second directory.
				 * @return  true if it succeeds, false if it fails.
				 */

				static bool compareDirectoryStructure(std::string & directoryOne, std::string & directoryTwo);

			private:

				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
			};
		}
	}
}






#endif
