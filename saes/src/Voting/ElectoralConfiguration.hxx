/**
 * @file ElectoralConfiguration.hxx
 * @brief Header class electoral configuration
 */

#ifndef __ELECTORAL_CONFIGURATION_H__
#define __ELECTORAL_CONFIGURATION_H__

#include <Voting/Election/ElectionWrapper.hxx>
#include <Voting/VotingDevice/VotingDeviceWrapper.hxx>
#include <Voting/Vote/VoteRecovery.h>
#include <Security/Encryption.hxx>
#include "ElectoralFactory.hxx"
#include <Runtime/Environment/saes-directories.h>
#include <Log/ISMTTLog.h>
#include <iostream>
#include <map>
#include <System/Exception/FileSystemException.hxx>
#include <System/Exception/VoteRecoveryException.hxx>

namespace Smartmatic
{
   namespace SAES
   {
      namespace Voting
      {
         /**
          * @class ElectoralConfiguration
          * @brief	Electoral configuration. 
          *
          * @author	Eduardo.campione
          * @date	28/04/2011
          */

         class ElectoralConfiguration
         {
         public:               

            /**
             * @brief	Class constructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            ElectoralConfiguration();

            /**
             * @brief	Class destructor.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            ~ElectoralConfiguration();

            /**
             * @brief	Initialises this object.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param	directories	The directories.
             * @param type type of load default
             */

            void init(Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories,
            		Smartmatic::SAES::Common::Configuration::BasePathType type = Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM)
                throw (Smartmatic::System::Exception::ElectionException,
                        Smartmatic::System::Exception::VotingDeviceException,
                        Smartmatic::System::Exception::CryptoException,
                        Smartmatic::System::Exception::SignedException,
                        Smartmatic::System::Exception::FileSystemException);

            /**
             * @brief	method dispose.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            void dispose();

            /**
             * @brief	Gets the election.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @return	null if it fails, else the election.
             */

            Smartmatic::SAES::Voting::Election::ElectionWrapper *
                getElection ()
                throw (Smartmatic::System::Exception::ElectionException);

            /**
             * @brief	Gets the voting device.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @return	null if it fails, else the voting device.
             */

            Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * 
                getVotingDevice ()
                throw (Smartmatic::System::Exception::VotingDeviceException);

			/**
             * @brief	Gets the vote recovery.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @return	null if it fails, else the vote recovery.
             */				  

			Smartmatic::SAES::Voting::Vote::VoteRecovery * getVoteRecovery()
				  throw (Smartmatic::System::Exception::VoteRecoveryException);

            /**
             * @brief   method for create data map and calculate max
             *
             * @author  Yadickson Soto
             * @date    13/03/2012
             *
             */
            void loadAllData()
				throw (Smartmatic::System::Exception::ElectionException,
						Smartmatic::System::Exception::VotingDeviceException);

            /**
             * @brief	method getter max ballot options of electoral configuration.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @return	max ballot options.
             */

            unsigned int getMaxBallotOptionsByVote ();

            /**
             * @brief	method getter max contest of electoral configuration.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @return	max contest.
             */

            unsigned int getMaxContestByVote ();

            /**
             * @brief   method getter max contest of electoral configuration.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    17/06/2011
             *
             * @return  max contest by blank vote
             */

            unsigned int getMaxContestByBlankVote ();

            /**
             * @brief   method getter max custom attribute of electoral configuration.
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @return  custom attribute vote
             */
            unsigned int getMaxCustomAttributeByVote ();

            /**
             * @brief	Gets a maximum ballot option by contest code.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             *
             * @param	contestCode	The contest code.
             *
             * @return	The maximum ballot option by contest code.
             */

            unsigned int getMaxBallotOptionByContestCode ( std::string contestCode );

            /**
             * @brief   method getter map of max ballot option by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @return  map of max ballot option by contest code
             */
            std::map < std::string, int > & getMaxBallotOptionByContestCode();

            /**
             * @brief   method getter party code by max ballot option by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return  party code
             */
            std::string getPartyByMaxBallotOptionContestCode ( std::string contestCode );

            /**
             * @brief   method getter count list of ballot option by contest code and party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param partyCode party code
             * @return  count list
             */
            unsigned int getCountListBallotOptionByContestParty ( std::string contestCode, std::string partyCode );

            /**
             * @brief   method getter count principal of ballot option by contest code and party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param partyCode party code
             * @return  count principal
             */
            unsigned int getCountPrincipalBallotOptionByContestParty ( std::string contestCode, std::string partyCode );

            /**
             * @brief   method getter count stand in of ballot option by contest code and party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param partyCode party code
             * @return  count stand in
             */
            unsigned int getCountStandInBallotOptionByContestParty ( std::string contestCode, std::string partyCode );

            /**
             * @brief   method getter all count of ballot option by contest code and party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param partyCode party code
             * @return count
             */
            unsigned int getCountBallotOptionByContestParty ( std::string contestCode, std::string partyCode );

            /**
             * @brief   method getter all count of ballot option by contest code and party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param partyCode party code
             * @param countList in, out count list
             * @param countPrincipal in, out count principal
             * @param countStandIn in, out count stand in
             */
            void getCountBallotOptionByContestParty ( std::string contestCode, std::string partyCode, int & countList, int & countPrincipal, int & countStandIn );

            std::list < std::string > & getAllCodeBallotOptionByContestParty(std::string contestCode, std::string partyCode );

            std::map <std::string, std::map < std::string, std::list <std::string> > > & getAllCodeBallotOptionByContestParty();

            std::string getPartyCodeByBallotOptionCode(std::string ballotCode);

            /**
             * @brief   method view info debug context group
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contextGroup contest group code
             */
            void viewInfo(std::string contextGroup);

            /**
             * @brief   method not reload config files
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             */
            void notReload();

            /**
             * @brief   method getter ballot option by contest code and ballot code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param ballotOptionCode ballot option code
             * @return ballot option
             */
            Smartmatic::SAES::Voting::Election::Ballot_option getBallotOptionListFromBallotOptionCode(std::string contestCode, std::string ballotOptionCode);

            /**
             * @brief   method getter eligible option by contest code and ballot code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param ballotOptionCode ballot option code
             * @return eligible option
             */
            Smartmatic::SAES::Voting::Election::Eligible_option & getEligibleOptionFromBallotOptionCode(std::string contestCode, std::string ballotOptionCode);

            /**
             * @brief   method getter eligible option by contest code and eligible option code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @param eligibleOptionCode eligible option code
             * @return eligible option
             */
            Smartmatic::SAES::Voting::Election::Eligible_option & getEligibleOptionFromEligibleOptionCode(std::string contestCode, std::string eligibleOptionCode);

            /**
             * @brief   method getter ballot option list by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return ballot option list
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getEligibleOptionsListByContestCode (std::string contestCode);

            /**
             * @brief   method getter ballot option principal by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return ballot option principal
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getEligibleOptionsPrincipalByContestCode (std::string contestCode);

            /**
             * @brief   method getter ballot option stand in by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return ballot option stand in
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getEligibleOptionsStandInByContestCode (std::string contestCode);

            /**
             * @brief   method getter eligible option map list by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return eligible option map list
             */
            std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & getMapEligibleOptionsListByContestCode (std::string contestCode);

            /**
             * @brief   method getter eligible option map principal by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return eligible option map principal
             */
            std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & getMapEligibleOptionsPrincipalByContestCode (std::string contestCode);

            /**
             * @brief   method getter eligible option map stand in by contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param contestCode contest code
             * @return eligible option map stand in
             */
            std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > & getMapEligibleOptionsStandInByContestCode (std::string contestCode);

            /**
             * @brief   method getter language list full name
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param onlyDefaultTrue only default true parameter
             * @return language list full name
             */
            std::list <std::string> getLanguageListFullName(bool onlyDefaultTrue = true, bool onlyLanguage = false);

            /**
             * @brief   method getter language list
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @param onlyDefaultTrue only default true parameter
             * @return language list
             */
            std::list <Smartmatic::SAES::Voting::Election::Language> getLanguageList(bool onlyDefaultTrue = true);

            /**
             * @brief   method getter languages
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    10/02/2012
             *
             * @return languages
             */
            Smartmatic::SAES::Voting::Election::Languages & getLanguages ();

            /**
             * @brief   method getter contest by code
             * @param code contest code
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return contest by code
             */
            Smartmatic::SAES::Voting::Election::Contest & getContestByCode (std::string code);

            /**
             * @brief   method getter list parties by contest code
             * @param code contest code
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    22/02/2012
             *
             * @return list parties by contest code
             */
            std::list < Smartmatic::SAES::Voting::Election::Party > & getListPartyByContestCode (std::string code);

            /**
             * @brief   method getter list contest by contest group code
             * @param code contest group code
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    22/02/2012
             *
             * @return list contest by contest group code
             */
            std::list < Smartmatic::SAES::Voting::Election::Contest > & getListContestByContestGroupCode (std::string code);

            /**
             * @brief   method getter list all contest
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return list all contest
             */
            std::list < Smartmatic::SAES::Voting::Election::Contest > & getContestList();

            std::list < std::string > & getContestCodeList();

            /**
             * @brief   method getter list all logical voter group
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return list all logical voter group
             */
            std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group > & getLogicalVoterGroupList();

            /**
             * @brief   method getter eligible option list by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return eligible option list by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & getEligibleOptionsListByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter eligible option principal by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return ballot eligible principal by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & getEligibleOptionsPrincipalByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter eligible option stand in by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return eligible option stand in by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Eligible_option > & getEligibleOptionsStandInByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter ballot option party by contest code
             * @param 	contestCode contest code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return ballot option party by contest
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getBallotOptionPartyByContest(std::string contestCode);

            /**
             * @brief   method getter ballot option list by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return ballot option list by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getBallotOptionsListByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter ballot option principal by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return ballot option principal by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getBallotOptionsPrincipalByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter ballot option stand in by contest party
             * @param 	contestCode contest code
             * @param	partyCode party code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    23/02/2012
             *
             * @return ballot option stand in by contest party
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot_option > & getBallotOptionsStandInByContestParty(std::string contestCode, std::string partyCode);

            /**
             * @brief   method getter contest group
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return contest group list
             */
            std::list < Smartmatic::SAES::Voting::Election::Contest_group > & getContestGroups();

            /**
             * @brief   method getter contest group by code
             * @param contestGroupCode contest group code
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return contest group
             */
            Smartmatic::SAES::Voting::Election::Contest_group & getContestGroup(std::string contestGroupCode);

            /**
             * @brief   method getter ballots
             *
             * @author  Yadickson Soto yadickson.soto@smartmatic.com
             * @date    13/03/2012
             *
             * @return ballots
             */
            std::list < Smartmatic::SAES::Voting::Election::Ballot > & getBallots();

            /**
             * @brief Method validate contest in voting device
             * @param contest contest
             * @return true is validate
             * @date 13/03/2012
             * @author Yadickson Soto
             */
            bool isContestValidate ( Smartmatic::SAES::Voting::Election::Contest & contest );
            /**
             * @brief Method getter max parties by all contest
             * @return max parties by all contest
             * @date 13/03/2012
             * @author Yadickson Soto
             */
            unsigned int getMaxPartiesByAllContest();
            /**
             * @brief method getter all region category
             * @return all region category
             * @date 04/04/2012
             * @author Yadickson Soto
             */
            std::list <Smartmatic::SAES::Voting::VotingDevice::Region_category> & getRegionCategoryList();
            /**
             * @brief Method getter file names by languages
             * @param file file name
             * @fileNames result file names
             * @param allLanguages all languages
             * @param delta delta compare language
             * @param onlyLanguage only language
             * @author    Yadickson Soto yadickson.soto@smartmatic.com
             * @date  10/05/2012
             */
            void getFileNamesByLanguages(std::string file, std::list <std::string> & fileNames, bool allLanguages, unsigned int delta = 0, bool onlyLanguage = false);

         private:
            /**
             * @brief   method for create eligible option map
             *
             * @author  Juan Delgado
             * @date    10/02/2012
             *
             */
            void createMap()
        		throw (Smartmatic::System::Exception::ElectionException,
        				Smartmatic::System::Exception::VotingDeviceException);

            /**
             * @brief	calculate max.
             *
             * @author	Eduardo.campione
             * @date	28/04/2011
             */

            void calculateMax ()
    		throw (Smartmatic::System::Exception::ElectionException,
    				Smartmatic::System::Exception::VotingDeviceException);


            void reduceElectionContests()
    		throw (Smartmatic::System::Exception::ElectionException,
    				Smartmatic::System::Exception::VotingDeviceException);

            void reduceElectionContestGroups()
    		throw (Smartmatic::System::Exception::ElectionException,
    				Smartmatic::System::Exception::VotingDeviceException);

            void verifyIntegrityData ()
    		throw (Smartmatic::System::Exception::ElectionException,
    				Smartmatic::System::Exception::VotingDeviceException);

            std::map <std::string, std::map<std::string, Smartmatic::SAES::Voting::Election::Eligible_option> > eligibleOptionByBallotOptionCodeMap;  ///< instance of eligible option by ballot option code map
            std::map <std::string, std::map<std::string, Smartmatic::SAES::Voting::Election::Eligible_option> > eligibleOptionByEligibleOptionCodeMap;  ///< instance of eligible option by eligible option code map

            Smartmatic::SAES::Voting::Election::ElectionWrapper * election; ///< instance of class ElectionWrapper
            Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper * votingDevice; ///< instance of class VotingDeviceWrapper
			Smartmatic::SAES::Voting::Vote::VoteRecovery* voteRecovery;  ///< instance of vote recovery object

			unsigned int maxPartiesByAllContest; ///< max parties by all contest
			unsigned int maxContestByVote; ///<max contest of electoral configuration
			unsigned int maxContestByBlankVote; ///<max contest of electoral configuration for blank vote
			unsigned int maxBallotOptionByVote; ///<max ballot option of electoral configuration
			unsigned int maxCustomAttributeByVote; ///< max custom attribute by vote
            bool reload; ///< flag for not reload config files
            bool loadData; ///< flag load data

            std::map < std::string, int > maxBallotOptionByContest; ///<max ballot option by contest
            std::map < std::string, std::string > contestParty; ///< map contest party
            std::list < std::string > listContestCode; ///< list contest code
            std::list < Smartmatic::SAES::Voting::Election::Contest > listContest; ///< list contest
            std::list < Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group > listLVG; ///< list logical voter group
            std::list < Smartmatic::SAES::Voting::Election::Contest_group > contestGroupList; ///< list contest group
            std::list < Smartmatic::SAES::Voting::Election::Ballot >  ballotList; ///< list ballot
            std::list < Smartmatic::SAES::Voting::VotingDevice::Region_category > regionCategoryList; ///< region category list

            std::map < std::string, Smartmatic::SAES::Voting::Election::Contest_group > mapContestGroupByCode; ///< map contest group by code
            std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Contest > > mapListContestByContestGroup; ///< map list contest by contest group
            std::map < std::string, Smartmatic::SAES::Voting::Election::Contest > mapContestCode; ///< map contest code
            std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Party > > mapContestParty; ///< map contest party

            std::map <std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > mapBallotOptionsPartyByContest; ///< map ballot option party by contest

            std::map < std::string, std::map <std::string, unsigned int > > maxListBallotOptionByContestParty; ///<max list ballot option by contest party
            std::map < std::string, std::map <std::string, unsigned int > > maxPrincipalBallotOptionByContestParty; ///<max principal ballot option by contest party
            std::map < std::string, std::map <std::string, unsigned int > > maxStandInBallotOptionByContestParty; ///<max stand in ballot option by contest party

            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > > mapBallotOptionsListByContestParty; ///<map ballot option list by contest party
            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > > mapBallotOptionsPrincipalByContestParty; ///<map ballot option principal by contest party
            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > > mapBallotOptionsStandInByContestParty; ///<map ballot option stand in by contest party

            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Eligible_option > > > mapEligibleOptionsListByContestParty; ///<map eligible option list by contest party
            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Eligible_option > > > mapEligibleOptionsPrincipalByContestParty; ///<map eligible option principal by contest party
            std::map <std::string, std::map < std::string, std::list < Smartmatic::SAES::Voting::Election::Eligible_option > > > mapEligibleOptionsStandInByContestParty; ///<map eligible option stand in by contest party

            std::map <std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsListByContest; ///<max eligible option list by contest
            std::map <std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsPrincipalByContest; ///<max eligible option principal by contest
            std::map <std::string, std::list < Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsStandInByContest; ///<max eligible option stand in by contest

            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsList; ///<max eligible option list
            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsPrincipal; ///<max eligible option principal
            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsStandIn; ///<max eligible option stand in

            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsListByParty; ///<max eligible option list by party
            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsPrincipalByParty; ///<max eligible option principal by party
            std::map <std::string, std::map < std::string, Smartmatic::SAES::Voting::Election::Ballot_option > > mapEligibleOptionsStandInByParty; ///<max eligible option stand in by party

            std::map <std::string, std::map < std::string, std::list <std::string> > > allCodeBallot; ///< all code ballot
            std::map <std::string, std::string> partyCodeByBallotOptionCode; ///< parent code by ballot option code

            Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories; ///< directories
            static Smartmatic::Log::ISMTTLog* logger; ///<logger
         };
      }
   }
}

#endif /*__ELECTORAL_CONFIGURATION_H__*/
