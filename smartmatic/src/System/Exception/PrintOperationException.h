/**
 * @file	PrintOperationException.h
 *
 * @brief	Header file to the print operation exception class.
 */



#ifndef PRINTOPERATIONEXCEPTION_H_
#define PRINTOPERATIONEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
namespace System
{
namespace Exception
{
/**
 * @class PrintOperationException
 * @brief	Exception for signalling print operation errors. 
 *
 * @author	Rafael.gasperi
 * @date	28/04/2011
 */

class PrintOperationException: public BaseException
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

	PrintOperationException(std::string message, std::string code,
			Smartmatic::Log::ISMTTLog* logger) :
		BaseException(message, code, logger)
	{
	}
};
}
}
}

#endif /* PRINTOPERATIONEXCEPTION_H_ */
