/**
 * @file	VotingState.hxx
 *
 * @brief	voting state class.
 */

#ifndef __VOTING_STATE_H__
#define __VOTING_STATE_H__

#include <iostream>
#include <list>
#include <map>
#include <Voting/VotingDevice/voting-devices-schema.hxx>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Operation
      {
         namespace Voting
         {
            /**
             * @brief	Header class VotingState.
             * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date	07-03-2011
             */

            class VotingState
            {
            public:

                enum TypeResponse
                {
                    START
                   ,USER_RESPONSE
                   ,AUTOMATIC_RESPONSE
                };

               /**
                * @brief	Defines an alias representing list logical voter group for state.
                */

               typedef std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group > ListLogicalVoterGroup; /**< list logical voter group for state*/

               /**
                * @brief	Defines an alias representing the list custom attribute definition for state.
                */

               typedef std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > ListCustomAttributeDefinition;

               /**
                * @brief	Defines an alias representing list of maps for state.
                */

               typedef std::map < std::string, std::list < std::string > > MapList; 

               /**
                * @brief	Defines an alias representing the map contest for state.
                */

               typedef std::map < std::string, MapList > MapContest; 

            private:

               std::string code;	///< response code
               std::string value;   ///< response value
               TypeResponse response;   ///< response of user or automatic
               ListLogicalVoterGroup logicalVoterGroups;	///< list logical voter group for state
               ListCustomAttributeDefinition customAttributeDefinitions;	///< list custom attribute definition for state
               MapContest mapContest;   ///< map contest
               MapList mapContestGroup; ///< map contest group
               std::list <std::string> contestByContestClass; ///< contest by contest class
               std::list <std::string> contestResolved; ///< contest resolved

            public:

               /**
                * @brief	class constructor.
                * @param	code			The response code.
                * @param	value			The response value.
                * @param	userResponse	true to user response.
                */
               VotingState( std::string code, std::string value, TypeResponse response = START );

               /**
                * @brief	method to get the response code.
                * @return	response code.
                */

               std::string getCode();

               /**
                * @brief	method to get the response value.
                * @return	response value.
                */

               std::string getValue();

               /**
                * @brief	query if it is user response.
                * @return	true if is user response.
                */

               TypeResponse getResponse();

               /**
                * @brief	method to add ballot option.
                * @param	contestCode			contest code.
                * @param	partyCode			party code.
                * @param	ballotOptionCode	ballot option.
                */

               void addBallotOption ( std::string contestCode, std::string partyCode, std::string ballotOptionCode );

               /**
                * @brief	method to remove contest.
                * @param	contestCode	contest code.
                */

               void removeContest ( std::string contestCode );

               void removeAllContest ();

               /**
                * @brief	method to remove party by contest.
                * @param	contestCode	contest code.
                * @param	partyCode  	party code.
                */

               void removePartyByContest ( std::string contestCode, std::string partyCode );

               /**
                * @brief	method to remove ballot options.
                * @param	contestCode			contest code.
                * @param	partyCode			party code.
                * @param	ballotOptionCode	ballot option.
                */

               void removeBallotOption ( std::string contestCode, std::string partyCode, std::string ballotOptionCode );

               /**
                * @brief	add contest to contest group.
                * @param	contestGroupCode	contest group code.
                * @param	contestCode			contest code.
                */

               void addContestByContestGroup ( std::string contestGroupCode, std::string contestCode );

               /**
                * @brief	removes contest from contest group.
                * @param	contestGroupCode	contest group code.
                * @param	contestCode			contest code.
                */

               void removeContestByContestGroup ( std::string contestGroupCode, std::string contestCode );

               /**
                * @brief	removes contest group.
                * @param	contestGroupCode	contest group code.
                */

               void removeContestGroup ( std::string contestGroupCode);

               /**
                * @brief	sets the list of logical voter groups.
                * @param	logicalVoterGroups	list of logical voter groups.
                */

               void setLogicalVoterGroups ( ListLogicalVoterGroup logicalVoterGroups );

               /**
                * @brief	sets the list of custom attribute definitions.
                * @param	customAttributeDefinitions	list of custom attribute definitions.
                */

               void setCustomAttributeDefinitions ( ListCustomAttributeDefinition customAttributeDefinitions );

               /**
                * @brief    sets the list of contest by contest class
                * @param    contest  list of contest by contest class.
                */

               void setContestByContestClass( std::list <std::string> contest );

               /**
                * @brief	gets the list of contests.
                * @return	list of contests.
                */

               std::list < std::string > getContests ();

               /**
                * @brief	gets the list of partys.
                * @param	contestCode	contest code.
                * @return	list of partys.
                */

               std::list < std::string > getPartys ( std::string contestCode );

               /**
                * @brief	gets the list of ballot options.
                * @param	contestCode	contest code.
                * @param	partyCode  	party code.
                * @return	list of ballot options.
                */

               std::list < std::string > getBallotOptions ( std::string contestCode, std::string partyCode );

               /**
                * @brief	gets the list of contest groups.
                * @return	list of contest group.
                */

               std::list < std::string > getContestGroups ();

               /**
                * @brief	gets the list of contests by contest group.
                * @param	contestGroupCode	contest group code.
                * @return	list of contests by contest group.
                */

               std::list < std::string > & getContestsByContestGroup ( std::string contestGroupCode );

               /**
                * @brief    gets the list of contests by contest group.
                * @return   list of contests by contest group.
                */

               std::list < std::string > getAllContestsByContestGroup ();

               /**
                * @brief	gets the list of logical voter groups.
                * @return	list of logical voter groups.
                */

               ListLogicalVoterGroup & getLogicalVoterGroups ();

               /**
                * @brief	gets the list of custom attribute definitions.
                * @return	list of custom attribute definitions.
                */

               ListCustomAttributeDefinition & getCustomAttributeDefinitions ();

               /**
                * @brief    gets the list of contest by contest class
                * @return   list of contest by contest class.
                */

               std::list <std::string> & getContestByContestClass();
            };
         }
      }
   }
}

#endif /*__VOTING_STATE_H__*/
