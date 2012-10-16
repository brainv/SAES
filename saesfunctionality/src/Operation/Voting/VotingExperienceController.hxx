/**
 * @file	VotingExperienceController.hxx
 *
 * @brief	voting experience controller class.
 */

#ifndef __VOTING_EXPERIENCE_CONTROLLER_H__
#define __VOTING_EXPERIENCE_CONTROLLER_H__

#include <iostream>
#include <list>
#include <vector>
#include <Voting/ElectoralConfiguration.hxx>
#include <Voting/VotingDevice/card-data-schema.hxx>
#include <Voting/Vote/vote-schema.hxx>
#include <Log/ISMTTLog.h>
#include "VotingState.hxx"

namespace Smartmatic
{
   namespace SAES
   {
      namespace Operation
      {
         namespace Voting
         {
            /**
             * @brief	forward class declaration VotingOriginator.
             */

            class VotingOriginator;

            /**
             * @brief	forward class declaration VotingMemento.
             */

            class VotingMemento;

            /**
             * @brief	forward class declaration FillVote.
             */

            class FillVote;

            /**
             * @brief	Header class VotingExperienceController.
             *
             * @author	Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date	15-02-2011
             */
            class VotingExperienceController
            {
            public:

               /**
                * @brief	enumerate for voting experience.
                */

               typedef enum
               {
                    VOTING_CONTROLLER_CONTEST /**<action contest*/
                   ,VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION /**<action custom attribute definition*/
                   ,VOTING_CONTROLLER_CLOSE /**<action close*/
               } VotingExperienceType; /**<define type actions*/

               /**
                * @brief	Class constructor.
                * @param [in,out]	electoralConfiguration	electoral configuration.
                */

               VotingExperienceController( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration );

               /**
                * @brief	Finaliser.
                */

               virtual ~VotingExperienceController();

               /**
                * @brief	Initialises this object.
                * @param [in,out]	cardData	Information describing the card.
                * @return	true if it succeeds, false if it fails.
                */

               bool init( Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData )
                   throw (Smartmatic::System::Exception::ElectionException,
                          Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Dispose of this object, cleaning up any resources it uses.
                */

               void dispose();

               /**
                * @brief	Gets the type of next action.
                * @return	The next type action.
                */

               VotingExperienceType getNextTypeAction();


               /**
                * @brief	Check if is new recovery type.
                *
                * @return true if new recovery type
                */
               bool isNewRecoveryType();

               /**
                * @brief	method to obtain the previous custom attribute definition.
                * @return	a reference to the previous custom attribute definition
                * 			@throw VotingDeviceException.
                */

               Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition &
                   getPreviousCustomAttributeDefinition ()
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	method to obtain the next custom attribute definition.
                * @return	a reference to the next custom attribute definition
                * 			@throw VotingDeviceException.
                */

               Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition &
                   getNextCustomAttributeDefinition ()
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	method to obtain the current custom attribute definition.
                * @return	a reference to the current custom attribute definition.
                */

               Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition &
                   getCurrentCustomAttributeDefinition ();

               /**
                * @brief	method to set the current custom attribute definition response.
                * @param	code 	code response.
                * @param	value	value response
                * 					@throw VotingDeviceException.
                */

               void setCustomAttributeDefinitionResponse ( std::string code, std::string value )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	method to set the blank vote response.
                */

               void sendBlankVoteResponse();

               /**
                * @brief	method to set the null eligible option response.
                * @param [in,out]	contest	current contest.
                */

               void setNullPartyResponse (Smartmatic::SAES::Voting::Election::Contest & contest);

               /**
                * @brief	method to get the vote.
                * @return	vote
                * 			@throw ElectionException.
                */

               Smartmatic::SAES::Voting::Vote::Vote * getVote ()
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to set the ballot option state.
                * @param	contestCode			contest.
                * @param	partyCode			party.
                * @param	ballotOptionCode	ballot option.
                * @param	state				enw state ballot option.
                */

               void setBallotOptionState(
                   std::string contestCode,
                   std::string partyCode,
                   std::string ballotOptionCode,
                   bool state = true);

               /**
                * @brief	method to get the current contest list.
                * @return	current contest list.
                */

               std::list < Smartmatic::SAES::Voting::Election::Contest >
                   getCurrentContestList ()
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets the ballot options selected by contest.
                * @param [in,out]	contest	The contest.
                * @return	The ballot options selected by contest.
                */

               std::list < Smartmatic::SAES::Voting::Election::Ballot_option >
                   getBallotOptionsSelectedByContest(
                   Smartmatic::SAES::Voting::Election::Contest & contest);

               /**
                * @brief	Gets the ballot options selected by contest party.
                * @param [in,out]	contest	The contest.
                * @param [in,out]	party  	The party.
                * @return	The ballot options selected by contest party.
                */

               std::list < Smartmatic::SAES::Voting::Election::Ballot_option >
                   getBallotOptionsSelectedByContestParty (
                   Smartmatic::SAES::Voting::Election::Contest & contest,
                   Smartmatic::SAES::Voting::Election::Party & party )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Clears the ballot options selected by contest.
                * @param [in,out]	contest	The contest.
                */

               void clearBallotOptionsSelectedByContest (
                   Smartmatic::SAES::Voting::Election::Contest & contest );

               /**
                * @brief	Reset the voting experience. used when a recovery vote is done bad.
                */

               void resetVotingExperience ();

               /**
                * @brief	Clears the ballot options selected by contest and party.
                * @param [in,out]	contest	The contest.
                * @param [in,out]	party  	The party.
                */

               void clearBallotOptionsSelectedByContestParty (
                   Smartmatic::SAES::Voting::Election::Contest & contest,
                   Smartmatic::SAES::Voting::Election::Party & party );

               /**
                * @brief	Gets the party selected from contest.
                * @param [in,out]	contest	The contest.
                * @return	The party selected from contest.
                */

               Smartmatic::SAES::Voting::Election::Party
                   getPartySelectedFromContest ( 
                   Smartmatic::SAES::Voting::Election::Contest & contest )
                   throw (Smartmatic::System::Exception::ElectionException);

			   /**
			    * @brief	Query if there is any party selected from contest.
			    * @param [in,out]	contest	The contest.
			    * @return	true if there is any party selected from contest, false if not.
			    */

			   bool isThereAnyPartySelectedFromContest ( 
                   Smartmatic::SAES::Voting::Election::Contest & contest );

               /**
                * @brief	moves the contest list forward.
                * @return	true if it succeeds, false if it fails.
                */

               bool moveContestListForward();

               /**
                * @brief    Queries if it can move back.
                * @param    contestCode current contest code.
                * @return   true if it can move, false if not.
                */

               bool canMoveBack(std::string contestCode);

               /**
                * @brief	Queries if it can move contest back.
                * @param    contestCode current contest code.
                * @return	true if it can move, false if not.
                */

               bool firstContest(std::string contestCode);

               /**
                * @brief    Queries if it can move back.
                * @return   true if it can move, false if not.
                */

               bool canMoveContestListBack();

               /**
                * @brief	moves the contest list back.
                * @return	true if it succeeds, false if it fails.
                */

               bool moveContestListBack();

               /**
                * @brief	method to get current vote code.
                * @return	current vote code.
                */

               //std::string getVoteCode();

               /**
                * @brief	method to get checksum of vote.
                * @return	the checksum of vote.
                */

               std::string getChecksumVote();

               /**
                * @brief	method to get the voting mode.
                * @return	voting mode.
                */

               Smartmatic::SAES::Voting::Vote::VoteMode getVotingMode();

				/**
				 * @brief	Sets a voting mode.
				 * @param	mode	The mode.
				 */

				void setVotingMode(Smartmatic::SAES::Voting::Vote::VoteMode mode);

               /**
                * @brief	method to get the activation code.
                * @return	activation card data code.
                */

               std::string getActivationCode();

               /**
                * @brief	method to get fixed contest
                * @return	fixed contests
                */

               std::list < std::string > getFixedContests()
			   { return allContestsFixed; }

            private:
			   static Smartmatic::Log::ISMTTLog* logger;	///< the logger
               bool isBlankVote;	///< true if is blank vote
               bool newRecoveryType; ///< new recovery type

               VotingOriginator * originator;   ///< object originator from design pattern memento
               VotingMemento * memento; ///< object state from design pattern memento
               FillVote * fillVote; ///< fill vote
               std::vector < VotingMemento * > caretaker;   ///< object caretaker from design pattern memento

               Smartmatic::SAES::Voting::Vote::VoteMode votingMode;   ///< flag for voting mode
               std::string checksumCode;	///< checksum code
               std::string activationCode;  ///< activation card data code
               std::string voteCode;	///< vote code
               std::string operationModeCode;   ///< operation mode code
               std::string votingBoothCode; ///< voting booth code
               std::string regionCode;  ///< region code
               std::string vdCode; ///< The Voting Device Code
               Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration;   ///< electoral configuration
               Smartmatic::SAES::Voting::Vote::Vote * vote;   ///< vote
               Smartmatic::SAES::Voting::Election::Contest currentContest;  ///< The current contest
               Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition currentCustomAttributeDefinition;	///< Current Custom attribute definition

               std::list < std::string > allContestsFixed;  ///< Contest fixed list
               std::list < std::string > allContests;   ///< Contest list
               Smartmatic::SAES::Voting::VotingDevice::Card_data  cardData;
               /**
                * @brief	validates elements from card data.
                * @param [in,out]	cardData	voting activation card data.
                * @return	true if it succeeds, false if it fails.
                */

               bool validateCardData( Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData );

               /**
                * @brief	validates the logical voter group from card data.
                * @param [in,out]	cardData	voting activation card data.
                * @return	true if it succeeds, false if it fails.
                */

               bool validateLogicalVoterGroupCardData ( Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData );

               /**
                * @brief	validates the custom attribute definitions from card data.
                * @param [in,out]	cardData	voting activation card data.
                * @return	true if it succeeds, false if it fails.
                */

               bool validateCustomAttributeDefinitionCardData ( Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData );

               /**
                * @brief	filters the elements from the card data response.
                * @param [in,out]	cardData	voting activation card data.
                *
                * @return	true if validate
                * 			@throw VotingDeviceException.
                */

               bool filterFromCardData( Smartmatic::SAES::Voting::VotingDevice::Card_data & cardData )
                   throw (Smartmatic::System::Exception::VotingDeviceException);

               /**
                * @brief	Filters empty custom attribute definition.
                */

               void filterEmptyCustomAttributeDefinition();

              /**
               * @brief	Searches for fixed contests.
               */
              
			   void findFixedContests()
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to filter the logical voter group.
                * @param	code 	code response.
                * @param	value	value response.
                * @return	list of logical voter group.
                */

               std::list<Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group> filterLogicalVoterGroup( std::string code, std::string value );

               /**
                * @brief	method to filter custom attribute definition by logical voter group.
                * @param [in,out]	logicalVoterGroups	list logical voter groups.
                * @param	code					  	code response.
                * @return	list of custom attribute definitions.
                */

               std::list < Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition > 
                   filterCustomAttributeDefinitionByLogicalVoterGroup ( 
                   std::list<Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group> & logicalVoterGroups,
                   std::string code );

               /**
                * @brief	searches for a custom attribute definition.
                * @param [in,out]	logicalVoterGroups	list of logical voter groups.
                * @param	code					  	code response.
                * @return	true if finds a custom attribute definition.
                */

               bool findCustomAttribute ( std::list<Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group> & logicalVoterGroups, std::string code );

              /**
               * @brief	Searches for new contests.
               */

			   void findNewContests()
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Searches for contests.
                * @param	fixeds	true to fixeds.
                */

               void findContests( bool fixeds = true )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	alternates first questions, first questions and last contests fixed.
                * @return	type action execute.
                */
               VotingExperienceType alternateFirstQuestions();

               /**
                * @brief	alternates questions, first contests fixed.
                * @return	type action execute.
                */
               VotingExperienceType alternateFirstContestsFixed();

               /**
                * @brief	all questions, first questions and last contests.
                * @return	type action execute.
                */
               VotingExperienceType allQuestionsFirstQuestions();

               /**
                * @brief	all questions, first contests fixed, all questions and last constest.
                * @return	type action execute.
                */
               VotingExperienceType allQuestionsFirstContestsFixed();

               /**
                * @brief    all questions and first contests by priority contest class
                * @return   type action execute.
                */
               VotingExperienceType priorityByContestClass();

               /**
                * @brief	Sets a response.
                * @param	code			The code response.
                * @param	value			The value response.
                * @param	userResponse	response of user or automatic.
                */
               void setResponse( std::string code, std::string value , VotingState::TypeResponse response );

            };
         }
      }
   }
}

#endif /*__VOTING_EXPERIENCE_CONTROLLER_H__*/
