/**
 * @file	SignByCardIDException.h
 *
 * @brief	Header file to the sign by card identifier exception class.
 */



#ifndef SIGNBYCARDIDEXCEPTION_H_
#define SIGNBYCARDIDEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{

namespace System
{

namespace Exception
{
/**
 * @class SignByCardIDException
 * @brief	Exception for signalling sign by card identifier errors. 
 *
 * @author	Rafael.gasperi
 * @date	28/04/2011
 */

class SignByCardIDException : public BaseException
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

	SignByCardIDException( std::string message, std::string code, 
                        Smartmatic::Log::ISMTTLog* logger) 
						: BaseException( message, code, logger){}

	/**
	 * @brief	Constructor.
	 *
	 * @author	Rafael.gasperi
	 * @date	28/04/2011
	 *
	 * @param	message		  	exception message.
	 * @param	code		  	exception code, default empty.
	 * @param logger	logger
	 * @param enumError enum error
	 */

	SignByCardIDException( std::string message, std::string code,
	                        Smartmatic::Log::ISMTTLog* logger, int enumError)
							: BaseException( message, code, logger)
	{
		this->enumError = enumError;
	}

	/**
	 * @brief	Method getter enum error
	 * @return enum error
	 */
	int getEnumError () { return enumError; };

private:
	int enumError; ///< enum error
};

}

}

}

#endif /* SIGNBYCARDIDEXCEPTION_H_ */
