/**
 * @file SignatureAlgorithmKeyException.cpp
 * @brief Body file to the signature algorithm key exception class.
 * @date 10/11/2011
 * @author fgomez
 */

#include "SignatureAlgorithmKeyException.h"

namespace Smartmatic {
namespace System {
namespace Exception {

SignatureAlgorithmKeyException::SignatureAlgorithmKeyException(std::string message, std::string code,
        Smartmatic::Log::ISMTTLog* logger ) : BaseException( message, code, logger)
{
	// TODO Auto-generated constructor stub

}


} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
