/**
 * @file	PMachineAuthenticator.hxx
 *
 * @brief	president machine authenticator class.
 */

#ifndef _PMACHINE_AUTHENTICATOR_H_
#define _PMACHINE_AUTHENTICATOR_H_

#include "IAuthenticator.hxx"
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Operation
        {
            namespace Authenticator
            {
                /**
                 * @brief	class for president machine authenticator.
                 * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date	03-03-2011
                 */

                class PMachineAuthenticator: public IAuthenticator
                {        
                public:

                    /**
                     * @brief	Class constructor.
                     */

                    PMachineAuthenticator ();

                    virtual ~PMachineAuthenticator();

                    /**
                     * @brief	Performs the validation.
                     * @param	password	password to validate.
                     * @return	response of validation.
                     */

                    virtual AuthenticationResultType validate( std::string password );

                    /**
                     * @brief	Validate role.
                     * @param	password	The password.
                     * @return	true if it succeeds, false if it fails.
                     */

                    bool ValidateRole(std::string password);

                    /**
                     * @brief	Dispose of this object, cleaning up any resources it uses.
                     */

                    virtual void dispose();
					static Smartmatic::Log::ISMTTLog* logger;   ///< logger
                };
            }
        }
    }
}

#endif // _PMACHINE_AUTHENTICATOR_H_
