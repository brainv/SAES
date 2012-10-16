/**
 * @file	VMStatusWrapper.hxx
 *
 * @brief	virtual memory status wrapper class.
 */

#ifndef __V_M_STATUS_WRAPPER_H__
#define __V_M_STATUS_WRAPPER_H__

#include <iostream>
#include <list>
#include <Voting/Status/voting-machine-status-schema.hxx>



namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
         namespace Status
         {
            /**
             * @brief	Voting machine status wrapper. 
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            class VotingMachineStatusWrapper
            {
            public:

               /**
                * @brief	Constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	vmStatus	The virtual memory status.
                */

               VotingMachineStatusWrapper(VotingMachineStatus & vmStatus);

			   /**
			    * @brief	Gets the voting machine status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The voting machine status.
			    */

			   VotingMachineStatus & getVotingMachineStatus();

    		   /**
    		    * @brief	Gets the devices status.
    		    *
    		    * @author	Eduardo.campione
    		    * @date	28/04/2011
    		    *
    		    * @return	The devices status.
    		    */

    		   DevicesStatus & getDevicesStatus();	

			   /**
			    * @brief	Sets a device status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param	sequence	The sequence.
			    */

			   void setDeviceStatus(::xsd::cxx::tree::sequence< DeviceStatus > sequence);

			   /**
			    * @brief	Gets the virtual memory flags.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The virtual memory flags.
			    */

			   std::string	& getVMFlags();

			   /**
			    * @brief	Gets a device status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param	Type	The type.
			    *
			    * @return	The device status.
			    */

			   DeviceStatus & getDeviceStatus( std::string Type );

			   /**
			    * @brief	Gets a virtual memory date time.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param [in,out]	status	The status.
			    *
			    * @return	The virtual memory date time.
			    */

			   std::string	& getVMDateTime(DeviceStatus & status);		

			   /**
			    * @brief	Gets a virtual memory status.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param [in,out]	status	The status.
			    *
			    * @return	The virtual memory status.
			    */

			   std::string	& getVMStatus(DeviceStatus & status);	

			   /**
			    * @brief	Gets a diagnose description.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @param [in,out]	status	The status.
			    *
			    * @return	The diagnose description.
			    */

			   std::string	& getDiagnoseDescription(DeviceStatus & status);

			   /**
			    * @brief	Gets the factory diagnose completed.
			    *
			    * @author	Eduardo.campione
			    * @date	28/04/2011
			    *
			    * @return	The factory diagnose completed.
			    */

			   bool & getFactoryDiagnoseCompleted();

     		   /**
     		    * @brief	Gets the transmission attempts.
     		    *
     		    * @author	Eduardo.campione
     		    * @date	28/04/2011
     		    *
     		    * @return	The transmission attempts.
     		    */

     		   long long unsigned int &	getTransmissionAttempts();

               /**
                * @brief	Default constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                */

               virtual ~ VotingMachineStatusWrapper();

			private:
				 VotingMachineStatus status;	///< The status
            };
         }
     }
   }
}

#endif /*__V_M_STATUS_WRAPPER_H__*/
