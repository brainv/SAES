/*
 * CardCanNotWriteException.h
 *
 *  Created on: Feb 10, 2012
 *      Author: root
 */

#ifndef CARDCANNOTWRITEEXCEPTION_H_
#define CARDCANNOTWRITEEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
namespace System
{
namespace Exception
{

class CardCanNotWriteException : BaseException
{

public:

	CardCanNotWriteException (std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger)
			: BaseException( message, code, logger) {};
};

} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* CARDCANNOTWRITEEXCEPTION_H_ */
