/**
 * @file ECDSException.cpp
 * @brief Class custom for exceptions in ecdse
 * @date 17/11/2011
 * @author freddy gomez
 */

#include "ECDSException.h"

namespace Smartmatic {
namespace System {
namespace Exception {

ECDSException::ECDSException(std::string message, std::string code,
        Smartmatic::Log::ISMTTLog* logger ) : BaseException( message, code, logger)
{
	// TODO Auto-generated constructor stub

}

}
}

}
