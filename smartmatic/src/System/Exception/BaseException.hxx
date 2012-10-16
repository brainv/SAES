/**
 * @file BaseException.hxx
 * @brief Class base for exceptions
 * @date 24/02/2011
 * @author Yadickson Soto
 */

#ifndef __BASE_EXCEPTION_H__
#define __BASE_EXCEPTION_H__

#include <iostream>
#include <exception>

namespace Smartmatic
{
   namespace Log
   {
	   class ISMTTLog;
   }

   namespace System
   {
      namespace Exception
      {
         /**
          * @class BaseException
          * @brief Header class BaseException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 14-02-2011
          */
         class BaseException : public std::exception
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message for interface
             * @param code exception message for logger
             * @param logger logger
             */
            BaseException( std::string message, std::string code,
                          Smartmatic::Log::ISMTTLog* logger);
            /**
             * @brief Class destructor
             */
            virtual ~BaseException() throw ();
            /**
             * @brief method to obtain the exception message
             * @return the exception message
             */
            std::string getMessage() const;
            /**
             * @brief method to obtain the exception code
             * @return the exception code
             */
            std::string getCode() const;
            /**
             * @brief method to obtain the exception message
             * @return the exception message
             */
            virtual const char* what() const throw();

         private:
            std::string message; ///< exception message
            std::string code; ///< exception code
         };
      }
   }
}

#endif /*__BASE_EXCEPTION_H__*/
