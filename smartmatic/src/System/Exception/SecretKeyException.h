/**
 * @file	SecretKeyException.h
 *
 * @brief	Header file to the secret key exception class.
 */



#ifndef SECRETKEYEXCEPTION_H_
#define SECRETKEYEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{

namespace System
{

namespace Exception
{
/**
 * @class SecretKeyException
 * @brief	Exception for signalling secret key errors. 
 *
 * @author	Rafael.gasperi
 * @date	28/04/2011
 */

class SecretKeyException : public BaseException
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
	 * @param 	logger	logger
	 */
	SecretKeyException( std::string message, std::string code, 
                        Smartmatic::Log::ISMTTLog* logger) 
						: BaseException( message, code, logger){}
};

}

}

}

#endif /* SECRETKEYEXCEPTION_H_ */
