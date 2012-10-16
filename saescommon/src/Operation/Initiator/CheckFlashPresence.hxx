/**
 * @file CheckFlashPresence.hxx
 * @brief header class for check condition files presence
 */

#ifndef _CHECK_FLASH_PRESENCE_H_
#define _CHECK_FLASH_PRESENCE_H_

#include "ICheckCondition.hxx"
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
                 * @class CheckFlashPresence
                 * @brief Class for check condition files presence
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 * @see ICheckCondition
                 */
                class CheckFlashPresence: public ICheckCondition
                {
                public:
                    /**
                     * @brief Class constructor
                     * @param infinity flag infinity check
                     */
                    CheckFlashPresence(bool infinity = true);

                    /**
                     * @brief Class destroy
                     */
                    virtual ~CheckFlashPresence();

                    /**
                     * @brief Method for getter status test
                     * @return status of test
                     */
                    virtual TestStatus::Tests check ();

                private:
                        bool infinity; /**< flag infinity check*/
						static Smartmatic::Log::ISMTTLog* logger; /**< logger*/
                };
            }
        }
    }
}

#endif // _CHECK_FILES_PRESENCE_H_
