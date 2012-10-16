/**
 * @file ElectoralFactory.hxx
 * @brief Class wrapper for Election class
 */

#ifndef __ELECTORAL_FACTORY_WRAPPER_H__
#define __ELECTORAL_FACTORY_WRAPPER_H__

#include <iostream>
#include <Voting/Election/ElectionWrapper.hxx>
#include <Voting/VotingDevice/VotingDeviceWrapper.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
         /**
          * @brief	Electoral factory. 
          *
          * @author	Eduardo.campione
          * @date	28/04/2011
          */

         class ElectoralFactory
         {
         public:

            /**
             * @brief	Gets an election.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param [in,out]	xml	The xml.
             *
             * @return	null if it fails, else the election.
             */

            static Smartmatic::SAES::Voting::Election::ElectionWrapper *
                getElection (std::istream & xml)
                throw (Smartmatic::System::Exception::ElectionException);

            /**
             * @brief	Gets a voting device.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param [in,out]	xml	The xml.
             *
             * @return	null if it fails, else the voting device.
             */

            static Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * 
                getVotingDevice (std::istream & xml)
                throw (Smartmatic::System::Exception::VotingDeviceException);

		 private:
			static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
         };
      }
   }
}

#endif /*__ELECTORAL_FACTORY_WRAPPER_H__*/
