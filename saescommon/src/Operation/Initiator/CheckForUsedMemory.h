/*
 * CheckForUsedMemory.h
 *
 *  Created on: 23/05/2011
 *      Author: yadicksons
 */

#ifndef CHECKFORUSEDMEMORY_H_
#define CHECKFORUSEDMEMORY_H_

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
                class CheckForUsedMemoryCondition: public ICheckCondition
                {
                public:

                    CheckForUsedMemoryCondition(
                            Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories,
                            Smartmatic::SAES::Common::Configuration::BasePathType type =
                                    Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);

                    TestStatus::Tests check();

                    virtual ~CheckForUsedMemoryCondition();

                private:
                    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
                    Smartmatic::SAES::Common::Configuration::BasePathType type;
                    static Smartmatic::Log::ISMTTLog* logger; ///< The logger
                };
            }
        }
    }
}

#endif /* CHECKFORUSEDMEMORY_H_ */
