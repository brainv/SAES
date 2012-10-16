/*
 *  CardReaderUnresponsiveException.hxx
 *
 *  Created on: 01/08/2012
 *  Author: Daniel Ampuero
 *  Email: daniel.ampuero@smartmatic.com
 */

#ifndef CARDREADERUNRESPONSIVEEXCEPTION_H_
#define CARDREADERUNRESPONSIVEEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{
namespace System
{
namespace Exception
{

class CardReaderUnresponsiveException : public BaseException
{
public:

	CardReaderUnresponsiveException (std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger)
			: BaseException( message, code, logger) {};

};

} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* CARDREADERUNRESPONSIVEEXCEPTION_H_ */
