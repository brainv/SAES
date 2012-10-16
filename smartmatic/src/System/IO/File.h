/**
 * @file File.h
 * @brief Class util for files
 */

#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <iostream>
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
   namespace System
   {
      namespace IO
      {
         /**
          * @class File
          * @brief Class for file utils
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 21-02-2011
          */
         class File
         {
         public:
            /**
             * @brief method to obtain is can open file
             * @param file file
             * @return true is can open file
             */
            static bool canOpenFile (std::string file);
            /**
            * @brief method to obtain the content of file
            * @param file file
            * @param content string of file
            * @return true is can read file
            */
            static bool readFile(std::string file, std::string & content);

            /**
             * @brief	Reads a last line.
             *
             * @author	Yadickson Soto
             * @date	28/04/2011
             *
             * @param	file		   	The file.
             * @param [in,out]	content	The content.
             *
             * @return	true if it succeeds, false if it fails.
             */

            static bool readLastLine(std::string file, std::string & content);

            /**
             * @brief	Searches for a line in the given file.
             *
             * @author	Yadickson Soto
             * @date	28/04/2011
             *
             * @param	file		   	The file.
             * @param [in,out]	content	The content.
             * @param	contentText	   	The content text.
             *
             * @return	true if it succeeds, false if it fails.
             */

            static bool findLine(std::string file, std::string & content, std::string contentText);

            /**
             * @brief	Deletes the file described by fullPath.
             *
             * @author	Yadickson Soto
             * @date	28/04/2011
             *
             * @param	fullPath	Full pathname of the full file.
             *
             * @return	true if it succeeds, false if it fails.
             */

            static bool DeleteFile(std::string fullPath);

            /**
             * @brief	Copies the file.
             *
             * @author	Yadickson Soto
             * @date	28/04/2011
             *
             * @param [in,out]	inputFile 	The input file.
             * @param [in,out]	outputFile	The output file.
             *
             * @return	true if it succeeds, false if it fails.
             */

            static bool copyFile(std::string & inputFile, std::string & outputFile);

            /**
             * @brief   compare files.
             *
             * @author  Yadickson Soto
             * @date    09/05/2011
             *
             * @param [in,out]  fileOne   The first file.
             * @param [in,out]  fileTwo   The second file.
             *
             * @return  true if it succeeds, false if it fails.
             */

            static bool compareFiles(std::string & fileOne, std::string & fileTwo);

            /**
             * @brief   Method getter hash file.
             *
             * @author  Yadickson Soto
             * @date    04/06/2011
             *
             * @param file   The file.
             * @param dataOut  data out buffer.
             *
             */

            static void getHashFile(std::string & file, Smartmatic::System::SafeBuffer & dataOut);

            /**
             * @brief   Method save buffer to file.
             *
             * @author  Yadickson Soto
             * @date    08/06/2011
             *
             * @param buffer   The buffer.
             * @param file   The file.
             *
             * @return true is success.
             */

            static bool saveBufferToFile(Smartmatic::System::SafeBuffer & buffer, std::string & file);

            /**
             * @brief   Method open file to buffer.
             *
             * @author  Yadickson Soto
             * @date    04/06/2011
             *
             * @param file   The file.
             * @param dataOut  data out buffer.
             *
             * @return true is success.
             */
            static bool openFileToBuffer(std::string & file, Smartmatic::System::SafeBuffer & dataOut);

            /**
             * @brief   Method rename file.
             *
             * @author  Yadickson Soto
             * @date    04/06/2011
             *
             * @param oldName   The old file name.
             * @param newName   The new file name.
             *
             * @return true is success.
             */
            static bool renameFile(std::string oldName, std::string newName);

            static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
         };
      }
   }
}

#endif /*__FILE_H__*/
