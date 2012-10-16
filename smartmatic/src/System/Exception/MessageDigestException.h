/**
 * @file	MessageDigestException.h
 *
 * @brief	Header file to the message digest exception class.
 */


#ifndef MESSAGEDIGESTEXCEPTION_H_
#define MESSAGEDIGESTEXCEPTION_H_


#include "BaseException.hxx"


namespace Smartmatic
{

namespace System
{

namespace Exception
{
/**
 * @class MessageDigestException
 * @brief	Exception for signalling message digest errors. 
 *
 * @author	Rafael.gasperi
 * @date	28/04/2011
 */

class MessageDigestException : public BaseException
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

	MessageDigestException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}
protected:

	/**
	 * @brief	Default constructor.
	 *
	 * @author	Rafael.gasperi
	 * @date	28/04/2011
	 */

	MessageDigestException();

};

}

}

}

#endif /* MESSAGEDIGESTEXCEPTION_H_ */
