/**
 * @file	LogReaderException.h
 *
 * @brief	Header file to the log reader exception class.
 */

#ifndef _LOGREADEREXCEPTION_H_
#define _LOGREADEREXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
	namespace System
	{
		namespace Exception
		{
			/**
			 * @class	LogReaderException
			 *
			 * @brief	Exception for signalling log reader errors. 
			 *
			 * @author	Rafael.gasperi
			 * @date	28/04/2011
			 */

			class LogReaderException : public BaseException
			{
			public:

					/**
					 * @brief	Constructor.
					 *
					 * @author	Rafael.gasperi
					 * @date	28/04/2011
					 *
					 * @param	message		  	exception message.
					 * @param	code		  	exception code.
					 * @param logger logger
					 */

					LogReaderException ( std::string message, std::string code, 
						                Smartmatic::Log::ISMTTLog* logger) 
										: BaseException( message, code, logger){}

			protected:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Rafael.gasperi
					 * @date	28/04/2011
					 */

					LogReaderException();

			private:

			};
		}
	}
}



#endif // _LOGREADEREXCEPTION_H_
