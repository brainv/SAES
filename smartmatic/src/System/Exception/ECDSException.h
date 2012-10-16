/**
 * @file ECDSException.h
 * @brief Class custom for exceptions in ecdse
 * @date 17/11/2011
 * @author freddy gomez
 */

#ifndef ECDSEXCEPTION_H_
#define ECDSEXCEPTION_H_

#include "BaseException.hxx"

namespace Smartmatic{
namespace System{
namespace Exception
{
/**
 * @class ECDSException
 * @brief Header class ECDSException
 * @date 17/11/2011
 * @author freddy gomez
 * @see BaseException
 */
class ECDSException: public BaseException {
public:
    /**
     * @brief Class constructor
     * @param message exception message
     * @param code exception code
     * @param logger logger
     */
	ECDSException(std::string message, std::string code,
            Smartmatic::Log::ISMTTLog* logger );

};
}
}
}
#endif /* ECDSEXCEPTION_H_ */
