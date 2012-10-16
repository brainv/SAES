/**
 * @file SignatureAlgorithmKeyException.h
 * @brief Header file to the signature algorithm key exception class.
 * @date 10/11/2011
 * @author fgomez
 */

#ifndef SIGNATUREALGORITHMKEYEXCEPTION_H_
#define SIGNATUREALGORITHMKEYEXCEPTION_H_

#include "System/Exception/BaseException.hxx"

namespace Smartmatic {
namespace System {
namespace Exception {

/**
 * @class SignatureAlgorithmKeyException
 * @brief	Exception for signature algorithm errors
 * @date 10/11/2011
 * @author fgomez
 */
class SignatureAlgorithmKeyException: public BaseException {
public:
	/**
	 * @brief	Constructor.
	 *
	 * @date 10/11/2011
	 * @author fgomez
	 *
	 * @param	message		  	exception message.
	 * @param	code		  	exception code.
	 * @param 	logger	logger
	 */
	SignatureAlgorithmKeyException(std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger );

};

} /* namespace Exception */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* SIGNATUREALGORITHMKEYEXCEPTION_H_ */
