/**
 * @file	IAuthenticator.hxx
 *
 * @brief	Declares the IAuthenticator interface.
 */

#ifndef _IAUTHENTICATOR_H_
#define _IAUTHENTICATOR_H_

#include <iostream>
#include <Voting/ElectoralConfiguration.hxx>

namespace Smartmatic
{
    namespace SAES 
    {
        namespace Operation
        {
            namespace Authenticator
            {
                /**
                 * @brief	Abstract class for authenticator.
                 * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date	02-03-2011
                 */

                class IAuthenticator
                {
                public:

                    /**
                     * @enum AuthenticationResultType
                     * @brief enum for authentication result
                     */
                    enum AuthenticationResultType
                    {
                         VOTING_PROCESS /**<type voting process*/
                        ,ELECTORAL_PROCESS /**<type electoral process*/
                        ,AUDIO_VOTING_PROCESS /**<type audio voting process*/
                        ,MENU /**<type menu*/
                        ,WIZARD_MENU /**<type wizard menu*/
                        ,CLEAR_ALARM /**<type clear alarm*/
                        ,ERROR /**<type error*/
                        ,NO_MATCH /**<type no match*/
                    };

                    /**
                     * @enum MachineType
                     * @brief enum for machine type
                     */
                    enum MachineType
                    {
                         VOTING_MACHINE /**<type voting machine*/
                        ,PRESIDENT_MACHINE /**<type president machine*/
						,DIAGNOSTICS_ONLY/**<type diagnostics machine*/
                    };

                    /**
                     * @brief	Class constructor.
                     * @param	machineType	machine type.
                     */

                    IAuthenticator ( MachineType machineType);

                    virtual ~IAuthenticator();

                    /**
                     * @brief	obtains the machine type.
                     * @return	machine type.
                     */

                    MachineType getMachineType();

                    /**
                     * @brief	initializes the authenticator.
                     * @param [in,out]	electoralConfiguration	electoral configuration.
                     */

                    void init( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration );

                    /**
                     * @brief	abstract for authenticator validation.
                     * @param	password	The password to validate.
                     * @return	response of validation.
                     */

                    virtual AuthenticationResultType validate( std::string password ) = 0;

                    /**
                     * @brief	abstract for role validation.
                     * @param	password	The password.
                     * @return	true if it succeeds, false if it fails.
                     */
                    virtual bool ValidateRole(std::string password) = 0;

                    /**
                     * @brief	Method abstract for disposing the autehnticator machine.
                     */

                    virtual void dispose() = 0;

                private:
                    MachineType machineType; ///< Type of the machine

                protected:
                    Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;  ///< The electoral configuration instance
                };
            }
        }
    }
}

#endif // _IAUTHENTICADOR_H_
