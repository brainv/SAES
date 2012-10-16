/*
 * InvalidCardContentException.hxx
 *
 *  Created on: Feb 9, 2012
 *      Author: root
 */

#ifndef INVALIDCARDCONTENTEXCEPTION_HXX_
#define INVALIDCARDCONTENTEXCEPTION_HXX_

#include "BaseException.hxx"

namespace Smartmatic
{
namespace System
{
namespace Exception
{

class InvalidCardContentException : public BaseException
{
public:

	InvalidCardContentException(std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger)
			: BaseException( message, code, logger) {};
};

} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* INVALIDCARDCONTENTEXCEPTION_HXX_ */
