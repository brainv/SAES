/**
 * @file CheckForMemoryComplete.h
 * @brief Header class check for memory complete
 * @date 23/05/2011
 * @author Yadickson Soto
 */

#ifndef CHECKFORMEMORYCOMPLETE_H_
#define CHECKFORMEMORYCOMPLETE_H_

#include "ICheckCondition.hxx"
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

    namespace SAES
    {
        namespace Operation
        {
            namespace Initiator
            {

                class CheckForMemoryCompleteCondition: public ICheckCondition
                {
                public:

                    CheckForMemoryCompleteCondition(
                        Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories,
                        Smartmatic::SAES::Common::Configuration::BasePathType type =
                                Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    virtual ~CheckForMemoryCompleteCondition();

                    TestStatus::Tests check();

                private:
                    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
                    Smartmatic::SAES::Common::Configuration::BasePathType type;
                    static Smartmatic::Log::ISMTTLog* logger; ///< The logger
                };
            }
        }
    }
}
#endif /* CHECKFORMEMORYCOMPLETE_H_ */
