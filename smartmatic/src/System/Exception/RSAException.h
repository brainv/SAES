/**
 * @file RSAException.h
 * @brief Class custom for exceptions in rsa
 * @date 24/05/2011
 * @author mcordovi
 */

#ifndef RSAEXCEPTION_H_
#define RSAEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic
{

namespace System
{

namespace Exception
{
/**
 * @class RSAException
 * @brief Header class RSAException
 * @date 17/11/2011
 * @author mcordovi
 * @see BaseException
 */
class RSAException: public Smartmatic::System::Exception::BaseException
{
public:
    /**
     * @brief Class constructor
     * @param message exception message
     * @param code exception code
     * @param logger logger
     */
	RSAException ( std::string message, std::string code,
                   Smartmatic::Log::ISMTTLog* logger)
					: BaseException( message, code, logger){}
};

}

}

}

#endif /* RSAEXCEPTION_H_ */
