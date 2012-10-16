/**
 * @file	VotingDeviceWrapper.hxx
 *
 * @brief	voting device wrapper class.
 */

#ifndef __VOTING_DEVICE_WRAPPER_H__
#define __VOTING_DEVICE_WRAPPER_H__

#include <iostream>
#include <list>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <System/Exception/VotingDeviceException.hxx>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

   namespace SAES
   {
      namespace Voting
      {
         namespace VotingDevice
         {
            /**
             * @brief	Voting device wrapper. 
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            class VotingDeviceWrapper
            {
            public:

               /**
                * @brief	Constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevices	The voting devices.
                */

               VotingDeviceWrapper(Voting_devices & votingDevices);

               /**
                * @brief	Finaliser.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                */

               virtual ~VotingDeviceWrapper();

               /**
                * @brief	Gets the voting devices.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	The voting devices.
                */

               Voting_devices & getVotingDevices ();

               /**
                * @brief	Gets the first voting device.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	The first voting device.
                */

               Voting_device & getFirstVotingDevice()
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a voting device.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeVotingDevice	The code voting device.
                *
                * @return	The voting device.
                */

               Voting_device & getVotingDevice( std::string codeVotingDevice )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets an operation modes.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                *
                * @return	The operation modes.
                */

               Operation_modes & getOperationModes ( Voting_device & votingDevice );

               Voting_booths & getVotingBooths ()
               throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a voting booths.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                *
                * @return	The voting booths.
                */

               Voting_booths & getVotingBooths ( Voting_device & votingDevice );

               Logical_voter_groups & getLogicalVoterGroups()
               throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a logical voter groups.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                *
                * @return	The logical voter groups.
                */

               Logical_voter_groups & getLogicalVoterGroups( Voting_device & votingDevice );

               /**
                * @brief	Gets a logical voter group.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                * @param	codeLVG					The code lvg.
                *
                * @return	The logical voter group.
                */

               Logical_voter_group & getLogicalVoterGroup( Voting_device & votingDevice, std::string codeLVG )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a logical voter group.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                * @param	codeLVG					The code lvg.
                *
                * @return	The logical voter group.
                */

               Logical_voter_group & getLogicalVoterGroup(std::string codeLVG )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a logical voter group.
                *
                * @author	Yadickson Soto yadickson.soto@smartmatic.com
                * @date	28/04/2011
                *
                * @param	contestGroupCode		The contest group code.
                *
                * @return	The logical voter group.
                */

               Logical_voter_group & getLogicalVoterGroupByContestGroupCode( std::string contestGroupCode )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a tally reports.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                *
                * @return	The tally reports.
                */

               Tally_reports & getTallyReports( Voting_device & votingDevice );

               std::list < Custom_attribute_definition > getCustomAttributeDefinitionList(
            		   Machine_type machineType = Machine_type::VOTING_DEVICES_VM )
                       throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Gets a custom attribute definition list.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	votingDevice	The voting device.
                * @param	machineType				Type of the machine.
                *
                * @return	The custom attribute definition list.
                */

               std::list < Custom_attribute_definition > getCustomAttributeDefinitionList( 
                   Voting_device & votingDevice,
                   Machine_type machineType = Machine_type::VOTING_DEVICES_VM );

               /**
                * @brief	Gets a custom attribute list.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	lvg	The lvg.
                *
                * @return	The custom attribute list.
                */

               std::list < Custom_attribute > getCustomAttributeList(
                   Logical_voter_group & lvg);

               /**
                * @brief	Gets a logical voter group list.
                *
                * @author	Yadickson Soto
                * @date		23/02/2012
                *
                * @param [in,out]	votingDevice	The voting device.
                * @param list result the logical voter group list.
                */

               void getLogicalVoterGroupList( Voting_device & votingDevice, std::list < Logical_voter_group > & list );

               /**
                * @brief	Test whether the Logical Voter Group is registered in the ocnfiguration
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in]	lvgCode	LVG Code.
                *
                * @return	true whether the LVG is present in the configuration.
                */
               bool IsLogicalVoterGroupPresent(std::string lvgCode);

               /**
                * @brief	Gets a logical voter group list from a LVG code.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in]	lvgCode	LVG Code.
                *
                * @return	The custom attribute list.
                */
               std::list < Custom_attribute > getCustomAttributeListFromLVGCode(std::string lvgCode)
						throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Return the custom attribute definition belongiing to the specified code
                *
                * @author	Freddy.Gomez
                * @date	12/05/2011
                *
                * @param [in]	caCode	Custom attribute Code.
                * @param [out]	customAttrDef	Custom attribute Definition.
                *
                * @return	true whether the Custom Attribute is found, otherwise false.
                */
               bool GetCustomAttributeDefinition(std::string caCode,Custom_attribute_definition& customAttrDef );

               bool IsLanguagesPresent ();
               void setLanguages (Smartmatic::SAES::Voting::Election::Languages & lang);
               Smartmatic::SAES::Voting::Election::Languages & getLanguages ();

               /**
                * @brief method getter all region category
                * @param list all region category
                * @date 04/04/2012
                * @author Yadickson Soto
                */
               void getRegionCategoryList(std::list <Smartmatic::SAES::Voting::VotingDevice::Region_category> & list)
               	   throw (Smartmatic::System::Exception::VotingDeviceException);


            private:
               Voting_devices votingDevices;	///< The voting devices
			   static Smartmatic::Log::ISMTTLog* logger;	///< The logger
            };
         }
      }
   }
}

#endif /*__VOTING_DEVICE_WRAPPER_H__*/
