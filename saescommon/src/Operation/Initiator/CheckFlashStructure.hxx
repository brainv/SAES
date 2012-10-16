/**
 * @file CheckFlashStructure.hxx
 * @brief header class for check condition files presence
 */

#ifndef _CHECK_FLASH_STRUCTURE_H_
#define _CHECK_FLASH_STRUCTURE_H_

#include "ICheckCondition.hxx"
#include <Runtime/Environment/saes-directories.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
    namespace SAES 
    {
        namespace Operation
        {
            namespace Initiator
            {
                /**
                 * @class CheckFlashStructure
                 * @brief Class for check condition files presence
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 */
                class CheckFlashStructure: public ICheckCondition
                {
                public:
                    /**
                     * @brief Class constructor
                     * @param directories directories configuration
                     * @param type type base path
                     */
                    CheckFlashStructure(Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories,
                    		Smartmatic::SAES::Common::Configuration::BasePathType type =
                    		Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH);

                    /**
                     * @brief Class destroy
                     */
                    virtual ~CheckFlashStructure();

                    /**
                     * @brief Method for getter status test
                     * @return status of test
                     */
                    virtual TestStatus::Tests check ();

                private:
                        Smartmatic::SAES::Runtime::Environment::SaesDirectories directories; /**< directories configuration*/
                        Smartmatic::SAES::Common::Configuration::BasePathType type; ///< type base path
						static Smartmatic::Log::ISMTTLog* logger; /**< logger*/
                };
            }
        }
    }
}

#endif // _CHECK_FLASH_STRUCTURE_H_
