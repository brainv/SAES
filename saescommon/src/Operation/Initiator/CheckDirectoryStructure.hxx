/**
 * @file CheckDirectoryStructure.hxx
 * @brief header class for check directory structure
 */
 
#ifndef _CHECK_DIRECTORY_STRUCTURE_H_
#define _CHECK_DIRECTORY_STRUCTURE_H_

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
                 * @class CheckDirectoryStructure
                 * @brief Class for check directory structure
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 */
                class CheckDirectoryStructure: public ICheckCondition
                {
                public:
                /**
                 * @brief Class constructor
                 * @param directories directories configuration
                 */
                CheckDirectoryStructure(Smartmatic::SAES::Runtime::Environment::SaesDirectories *directories,
                		Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                virtual ~CheckDirectoryStructure();

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

#endif // _CHECK_DIRECTORY_STRUCTURE_H_
