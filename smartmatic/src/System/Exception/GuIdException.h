/**
 * @file	GuIdException.h
 *
 * @brief	Header file to the the guId identifier exception class.
 */

#ifndef _GUIDEXCEPTION_H_
#define _GUIDEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class GuIdException
          * @brief Header class GuIdException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          */
		class GuIdException: public BaseException 
		{
		public:
			 /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
             * @param logger logger
             */
             GuIdException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}	
		protected:
				
		private:
				
		};
      }
   }
}


#endif // _GUIDEXCEPTION_H_
