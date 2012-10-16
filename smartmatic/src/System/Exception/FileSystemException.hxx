/**
 * @file FileSystemException.hxx
 * @brief Class custom for exceptions in data file system
 */

#ifndef __FILE_SYSTEM_EXCEPTION_H__
#define __FILE_SYSTEM_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class FileSystemException
          * @brief Header class FileSystemException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 23-04-2011
          */
         class FileSystemException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
             * @param logger logger
             */
             FileSystemException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}	
         };
      }
   }
}

#endif /* __FILE_SYSTEM_EXCEPTION_H__ */
