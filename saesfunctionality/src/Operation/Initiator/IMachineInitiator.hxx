/**
 * @file	IMachineInitiator.hxx
 *
 * @brief	Declares the IMachineInitiator interface.
 */

#ifndef _IMACHINE_INITIATOR_H_
#define _IMACHINE_INITIATOR_H_

#include <list>
#include <glibmm/thread.h>
#include <Operation/Initiator/ICheckCondition.hxx>
#include <Voting/ElectoralConfiguration.hxx>

namespace Smartmatic
{
    namespace SAES 
    {
        namespace Operation
        {
            namespace Initiator
            {
                /**
                 * @brief	Machine initiator.
                 * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date	02-03-2011 
                 */

                class IMachineInitiator
                {
                public:

                    enum RunModeType
                    {
                    	 FIRST_TIME
                    	,NORMAL_MODE
                    	,RECOVERY_MODE
                    	,REPLACE_MACHINE_MODE
                    	,CONTINGENCY_MODE
                    };

                    IMachineInitiator();

                    virtual ~IMachineInitiator();

                sigc::signal<void,InitializationStatus&, bool> signal_detected; ///< emit signal

                /**
                 * @brief	Initialises this object.
                 * @param [in,out]	conditions			  	[in,out] If non-null, the conditions.
                 * @param [in,out]	electoralConfiguration	If non-null, the electoral configuration.
                 */

                void init( std::list < ICheckCondition * > & conditions,
                           Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration );

                /**
                 * @brief	Gets the initialization status.
                 * @return	The status.
                 */

                InitializationStatus getStatus();

                virtual int getSuccessMessageTime() = 0;

                /**
                 * @brief	Starts this object.
                 */

                virtual void start() = 0;

                /**
                 * @brief	Dispose of this object, cleaning up any resources it uses.
                 */

                virtual void dispose() = 0;

                /**
                 * @brief Method virtual, check data from media
                 * @author Yadickson Soto yadickson.soto@smartmatic.com
                 * @date 25/05/2011
                 * @return true is check success
                 */
                virtual bool checkData() = 0;

                virtual void setMode(RunModeType mode);

                protected:

                RunModeType mode;
                Glib::Thread * m_thread;	///< thread  for run check machine initiator
                std::list < ICheckCondition * > conditions; ///< list conditions
                InitializationStatus status;	///< initialization status
                Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;	///< The electoral configuration instance
                };
            }
        }
    }
}

#endif // _IMACHINE_INITIATOR_H_
