/**
 * @file VMachineInitiator.hxx
 * @brief header class for voting machine initiator
 */

#ifndef _VMACHINE_INITIATOR_H_
#define _VMACHINE_INITIATOR_H_

#include "IMachineInitiator.hxx"
#include "Log/ISMTTLog.h"
#include <Runtime/Environment/saes-directories.h>

namespace Smartmatic
{
    namespace SAES 
    {
        namespace Operation
        {
            namespace Initiator
            {
                /**
                 * @class VMachineInitiator
                 * @brief class for voting machine initiator
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03-03-2011
                 */
                class VMachineInitiator: public IMachineInitiator
                {
                    
                public:

    		    	/**
    		    	 * @brief	Constructor.
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
    		    	 */

    		    	VMachineInitiator ();

    		    	/**
    		    	 * @brief	Finaliser.
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
    		    	 */

    		    	virtual ~VMachineInitiator ();

                    /**
                     * @brief Method for start machine initiator
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
                     */
                    virtual void start();
                    /**
                     * @brief Method for dispose machine initiator
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
                     */
                    virtual void dispose();
                    /**
                     * @brief Method for check data from media
                     * @author Yadickson Soto yadickson.soto@smartmatic.com
                     * @date 25/05/2011
                     * @return true is check success
                     */
                    virtual bool checkData();
					
                    virtual int getSuccessMessageTime();

                private:

                    /**
                     * @brief Method for run machine initiator
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
                     */
                    void run();
                    /**
                     * @brief Method for check configuration load
                     * @author  Yadickson Soto <yadickson.soto@smartmatic.com>
                     * @date    03-03-2011
                     * @return true if check success
                     */
                    bool CheckConfigurationLoad();

                    int stepTime;
                    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
					static Smartmatic::Log::ISMTTLog* logger; /***<logger*/
                };
            }
        }
    }
}

#endif // _VMACHINE_INITIATOR_H_
