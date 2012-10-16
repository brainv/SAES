/**
 * @file ICheckCondition.hxx
 * @brief interface for check condition
 */

#ifndef _ICHECK_CONDITION_H_
#define _ICHECK_CONDITION_H_

#include "InitializationStatus.hxx"
#include <iostream>

namespace Smartmatic
{
    namespace SAES
    {
        namespace Operation
        {
            namespace Initiator
            {
                /**
                 * @class ICheckCondition
                 * @brief Abstract class for check condition
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 */
                class ICheckCondition
                {
                public:
                /**
                 * @brief Class constructor
                 * @param test identify of test
                 * @param message identify of message
                 */
                ICheckCondition ( TestStatus::Tests test, std::string msg, std::string imgFileName, std::string imgEFileName );

                virtual ~ICheckCondition();

                /**
                 * @brief Method for getter identify of test
                 * @return identify of test
                 */
                TestStatus::Tests whois ();
                /**
                 * @brief Method for getter status test
                 * @return identify of test
                 */
                std::string getMessage();
                /**
			     * @brief Method for getter status test
				 * @return identify of test
				 */
                std::string getImageFilename();
        
                std::string getImageErrorFilename();
                virtual TestStatus::Tests check () = 0;

                private:
                TestStatus::Tests test; /**<identify test*/
                std::string message; /**<message test*/
                std::string imageFilename;/**<image identify test*/
                std::string imageErrorFilename;/**<image identify test with errors*/
                };
            }
        }
    }
}

#endif // _ICHECK_CONDITION_H_
