/**
 * @file SignedException.hxx
 * @brief Class custom for exceptions in signed security
 */

#ifndef __SIGNED_EXCEPTION_H__
#define __SIGNED_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class SignedException
          * @brief Header class SignedException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 31-03-2011
          */
         class SignedException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param	message		  	exception message.
	         * @param	code		  	exception code, default empty.
	         * @param [in,out]	logger	If non-null, the logger to be modified with exceptions.
             */
             SignedException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}	
         };
      }
   }
}

#endif /* __SIGNED_EXCEPTION_H__ */
