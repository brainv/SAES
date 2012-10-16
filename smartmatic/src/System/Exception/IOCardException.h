/*
 * IOCardException.h
 *
 *  Created on: Feb 9, 2012
 *      Author: root
 */

#ifndef IOCARDEXCEPTION_H_
#define IOCARDEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
namespace System
{
namespace Exception
{

class IOCardException : public BaseException
{
public:

	IOCardException (std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger)
			: BaseException( message, code, logger) {};

};

} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* IOCARDEXCEPTION_H_ */
