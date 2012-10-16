/**
 * @file	VMachineAuthenticator.hxx
 *
 * @brief	voting machine authenticator class.
 */

#ifndef _VMACHINE_AUTHENTICATOR_H_
#define _VMACHINE_AUTHENTICATOR_H_

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
                 * @brief	class for voting machine authenticator.
                 * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date	03-03-2011
                 */

                class VMachineAuthenticator: public IAuthenticator
                {        
                public:

                    /**
                     * @brief	Class constructor.
                     */

                    VMachineAuthenticator ();

                    virtual ~VMachineAuthenticator();

                    /**
                     * @brief	Method for authenticator validation.
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
                     * @brief	Method for disposing the autehnticator machine.
                     */

                    virtual void dispose();
					
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger
                };
            }
        }
    }
}

#endif // _VMACHINE_AUTHENTICATOR_H_
