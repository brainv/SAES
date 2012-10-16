/**
 * @file CheckFilesPresence.hxx
 * @brief header class for check condition files presence
 */

#ifndef _CHECK_FILES_PRESENCE_H_
#define _CHECK_FILES_PRESENCE_H_

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
                 * @class CheckFilesPresence
                 * @brief Class for check condition files presence
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 */
                class CheckFilesPresence: public ICheckCondition
                {
                public:
                    /**
                     * @brief Class constructor
                     * @param directories directories configuration
                     */
                    CheckFilesPresence(Smartmatic::SAES::Runtime::Environment::SaesDirectories *directories,
                    		Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    virtual ~CheckFilesPresence();

                    /**
                     * @brief Method for getter status test
                     * @return identifi of test
                     */
                    virtual TestStatus::Tests check ();

                private:
                        Smartmatic::SAES::Runtime::Environment::SaesDirectories *directories; /**<directories configuration*/
                        Smartmatic::SAES::Common::Configuration::BasePathType type;
						static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
                };
            }
        }
    }
}

#endif // _CHECK_FILES_PRESENCE_H_
