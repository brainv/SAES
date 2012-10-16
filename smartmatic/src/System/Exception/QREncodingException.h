/**
 * @file	QREncodingException.h
 *
 * @brief	Header file to the qr encoding exception class.
 */

#ifndef _QRENCODINGEXCEPTION_H_
#define _QRENCODINGEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
		/**
		 * @class QREncodingException
		 * @brief	Header class GuIdException.
		 *
		 * @author	Rafael.gasperi
		 * @date	28/04/2011
		 */

		class QREncodingException: public BaseException 
		{
		public:

             /**
              * @brief	Class constructor.
              *
              * @author	Rafael.gasperi
              * @date	28/04/2011
              *
              * @param	message		  	exception message.
              * @param	code		  	exception code.
              * @param [logger	logger
              */

             QREncodingException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}
		protected:
				
		private:
				
		};
      }
   }
}


#endif // _QRENCODINGEXCEPTION_H_
