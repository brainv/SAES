/**
 * @file	LoginCardException.h
 *
 * @brief	Header file to the login card exception class.
 */



#ifndef LOGINCARDEXCEPTION_H_
#define LOGINCARDEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{

namespace System
{

namespace Exception
{
/**
 * @class LoginCardException
 * @brief	Exception for signalling login card errors.
 *
 * @author	Rafael.gasperi
 * @date	28/04/2011
 */

class LoginCardException : BaseException
{
public:

	/**
	 * @brief	Constructor.
	 *
	 * @author	Rafael.gasperi
	 * @date	28/04/2011
	 *
	 * @param	message		  	exception message.
	 * @param	code		  	exception code
	 * @param 	logger	logger
	 */

	LoginCardException( std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger)
			: BaseException( message, code, logger){}
};

}
}
}

#endif /* LOGINCARDEXCEPTION_H_ */
