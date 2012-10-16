/**
 * @file	ElectionWrapper.hxx
 *
 * @brief	election wrapper class.
 */

#ifndef __ELECTION_WRAPPER_H__
#define __ELECTION_WRAPPER_H__

#include <iostream>
#include <list>
#include <vector>
#include <Voting/Election/election-schema.hxx>
#include <System/Exception/ElectionException.hxx>
#include <Runtime/Environment/saes-directories.h>

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
         namespace Election
         {
            /**
             * @class ElectionWrapper
             * @brief	Election wrapper. 
             *
             * @author	Yadickson Soto
             * @date	28/04/2011
             */

            class ElectionWrapper
            {
            public:

               /**
                * @brief	Constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	election	The election.
                */

               ElectionWrapper(Election & election);

               /**
                * @brief	Finaliser.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                */

               virtual ~ElectionWrapper();

               /**
                * @brief	Gets the election.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	The election.
                */

               Election & getElection ();

               /**
                * @brief	Gets the ballots.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	The ballots.
                */

               Ballots & getBallots ();

               /**
                * @brief	Gets a ballot.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeBallot	The code ballot.
                *
                * @return	The ballot.
                */

               Ballot & getBallot ( std::string codeBallot )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a ballot cards.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeBallot	The code ballot.
                *
                * @return	The ballot cards.
                */

               Ballot_cards & getBallotCards ( std::string codeBallot )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a ballot cards.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballot	The ballot.
                *
                * @return	The ballot cards.
                */

               Ballot_cards & getBallotCards ( Ballot & ballot );

               /**
                * @brief	Gets a ballot card.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeBallotCard	The code ballot card.
                * @param [in,out]	ballot	The ballot.
                *
                * @return	The ballot card.
                */

               Ballot_card getBallotCard ( std::string codeBallotCard, Ballot & ballot )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets the contests.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballotCard	The ballot card.
                *
                * @return	The contests.
                */

               Contests & getContests ( Ballot_card & ballotCard );

               /**
                * @brief	Gets a contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeContest		  	The code contest.
                * @param [in,out]	ballotCard	The ballot card.
                *
                * @return	The contest.
                */

               Contest & getContest ( std::string codeContest, Ballot_card & ballotCard )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to obtain the eligibles options.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	root contest of eligibles options.
                *
                * @return	a reference of the eligibles options.
                */

               Eligibles_options & getEligiblesOptions ( Contest & contest ) ;

               /**
                * @brief	Gets an eligible option.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeEligibleOption	The code eligible option.
                * @param [in,out]	contest   	The contest.
                *
                * @return	The eligible option.
                */

               Eligible_option & getEligibleOption ( std::string codeEligibleOption, Contest & contest )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to obtain the ballot options.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	eligibleOption	root eligible option of ballot options.
                *
                * @return	a reference of the ballot options.
                */

               Ballot_options & getBallotOptions ( Eligible_option & eligibleOption );

               /**
                * @brief	Gets a ballot option by eligible option.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	eligibleOption	The eligible option.
                *
                * @return	The ballot option by eligible option.
                */

               Ballot_option & getBallotOptionByEligibleOption ( Eligible_option & eligibleOption )
                   throw (Smartmatic::System::Exception::ElectionException);
         
               /**
                * @brief	Constructor.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param		Details of the exception.
                */
               Ballot_option & getBallotOption ( std::string codeBallotOption, Eligible_option & eligibleOption )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to obtain the pad position group.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballotOption	root ballot option of pad position group.
                *
                * @return	a reference of the pad position group.
                */

               Pad_position_group & getPadPositionGroup ( Ballot_option & ballotOption );

               /**
                * @brief	method to obtain the languages.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	a reference of the languages.
                */

               Languages & getLanguages ();

               bool IsLanguagesPresent ();

               /**
                * @brief	method to obtain the contest classes.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	a reference of the contest classes.
                */

               Contest_classes & getContestClasses ();

               /**
                * @brief	Gets a contest class.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeContestClass	The code contest class.
                *
                * @return	The contest class.
                */

               Contest_class & getContestClass ( std::string codeContestClass )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a contest class by custom code.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	customCoodeContestClass	The custom coode contest class.
                *
                * @return	The contest class by custom code.
                */

               Contest_class & getContestClassByCustomCode ( std::string customCoodeContestClass )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	method to obtain the contest groups.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	a reference of the contest groups.
                */

               Contest_groups & getContestGroups ();
               
               Contest_group & getContestGroup ( std::string codeContestGroup )

                   /**
                    * @brief	Constructor.
                    *
                    * @author	Eduardo.campione
                    * @date	28/04/2011
                    *
                    * @param		Details of the exception.
                    */

                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a contest group by list.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param	codeContestGroups	Groups the code contest belongs to.
                * @param	list result the contest group by list.
                */

               void getContestGroupByList ( std::list < std::string > & codeContestGroups, std::list < Contest_group > & list)
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	codeContest	The code contest.
                *
                * @return	The contest.
                */

               Contest & getContest ( std::string codeContest )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a contest by list.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param	codeContests	The code contests.
                * @param	list result the contest by list.
                */

               void getContestByList ( std::list < std::string > & codeContests, std::list < Contest > & list )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief    Gets a contest by contest class.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param    codeContests    The code contests.
                * @param	list result the contest by contest class.
                */

               void getContestByContestClass ( std::list < std::string > & codeContests, std::list < Contest > & list )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets the partys.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param 	contest	The contest.
                * @param	list result the party list
                */

               void getPartys ( Contest & contest, std::list < Party > & list );

               /**
                * @brief	Gets the partys by contest code.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param 	contest	The contest.
                * @param	list result the party list
                */
               void getPartysByContestCode( std::string contestCode, std::list < Party > & list )
				   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a ballot option party by contest.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param [in,out]	contest	The contest.
                * @param	list result the ballot options party by contest
                * @param	category	   	The category.
                *
                */
               void getBallotOptionPartyByContest ( Contest & contest,
            		   std::list < Ballot_option > & list,
            		   Category category = Category::ELECTION_PRINCIPAL );

               /**
                * @brief	Gets a party by contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param	partyCode	   	The party code.
                * @param	category	   	The category.
                *
                * @return	The party by contest.
                */

               Party & getPartyByContest ( Contest & contest, std::string partyCode, Category category = Category::ELECTION_PRINCIPAL )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a party abb by contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param	partyAbb	   	The party abb.
                * @param	category	   	The category.
                *
                * @return	The party abb by contest.
                */

               Party & getPartyAbbByContest ( Contest & contest, std::string partyAbb, Category category = Category::ELECTION_PRINCIPAL )
                   throw (Smartmatic::System::Exception::ElectionException);


               /**
                * @brief	Gets if can obtain a party abb by contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param	partyAbb	   	The party abb.
                * @param	category	   	The category.
                *
                * @return	true if can get party abb by contest.
                */

               bool getIfCanPartyAbbByContest ( Contest & contest, std::string partyAbb, Party & returnParty, Category category = Category::ELECTION_PRINCIPAL);

               /**
                * @brief	Gets a ballot options by contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param	category	   	The category.
                *
                * @return	The ballot options by contest.
                */

               void getBallotOptionsByContest ( Contest & contest, std::list < Ballot_option > & ballotOptionList, Category category = Category::ELECTION_PRINCIPAL, bool sort = true );

               /**
                * @brief	Gets map ballot options by contest.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param	contest	The contest.
                * @param	ballotOptionMap result map of ballot option
                * @param	category	   	The category.
                *
                * @return	The ballot options by contest.
                */
               void getMapBallotOptionsByContest ( Contest & contest,
            		   std::map < std::string , Ballot_option > & ballotOptionMap,
            		   Category category = Category::ELECTION_PRINCIPAL );

               /**
                * @brief    Gets a ballot options list by contest.
                *
                * @author   Yadickson Soto
                * @date		22/02/2012
                *
                * @param [in,out]   contest The contest.
                * @param ballotOptionList  result ballot option list
                * @param sort flag sort ballot option list
                */

               void getBallotOptionsListByContest ( Contest & contest, std::list < Ballot_option > & ballotOptionList, bool sort = true );

               /**
                * @brief	Gets map ballot options list by contest.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param	contest	The contest.
                * @param	ballotOptionMap result map of ballot option list
                * @param	category	   	The category.
                *
                * @return	The ballot options by contest.
                */
               void getMapBallotOptionsListByContest ( Contest & contest,
            		   std::map < std::string , Ballot_option > & ballotOptionMap );

               /**
                * @brief    Gets a ballot options list by contest codes.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param [in,out]   contest The contest.
                * @param    codes list codes
                * @param 	list result ballot option list
                */

               void getBallotOptionsListByContest ( Contest & contest, std::list <std::string> & codes, std::list < Ballot_option > & list );

               /**
                * @brief    Gets a ballot options by contest.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param [in,out]   contest The contest.
                * @param    codes list codes
                * @param 	list result ballot option list
                * @param    category        The category.
                */

               void getBallotOptionsByContest ( Contest & contest, std::list <std::string> & codes, std::list < Ballot_option > & list, Category category = Category::ELECTION_PRINCIPAL );

               /**
                * @brief	Gets a contest by contest group.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param	codeContestGroup	Group the code contest belongs to.
                * @param 	list result ballot option by contest group.
                */

               void getContestByContestGroup ( std::string codeContestGroup, std::list < Contest > & list )
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets all contest.
                * @param	contestList all contest.
                *
                * @author	Yadickson Soto
                * @date	22/02/2012
                *
                */

               void getAllContest (std::list < Contest > & contestList);

               /**
                * @brief	Gets all contest code.
                * @param	contestList all contest code.
                *
                * @author	Yadickson Soto
                * @date	22/02/2012
                */

               void getAllContestCode (std::list < std::string > & contestList);

               /**
                * @brief	Gets the maximum partys all contests.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	The maximum partys all contests.
                */

               int getMaxPartysAllContests();

               /**
                * @brief	Gets a maximum ballot options by contest.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                *
                * @return	The maximum ballot options by contest.
                */

               int getMaxBallotOptionsByContest(Contest & contest, Party & party);

               /**
                * @brief	Gets a ballot options by contest party.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param [in,out]	party  	The party.
                * @param	category	   	The category.
                * @param	getList		   	true to get list.
                *
                * @return	The ballot options by contest party.
                */

               void getBallotOptionsByContestParty ( Contest & contest,
                   Party & party,
                   std::list < Ballot_option > & list,
                   Category category)
                   throw (Smartmatic::System::Exception::ElectionException);

               void getBallotOptionsListByContestParty ( Contest & contest,
                   Party & party,
                   std::list < Ballot_option > & list)
                   throw (Smartmatic::System::Exception::ElectionException);

               void getAllBallotOptionsListCodeByContestParty ( Contest & contest, Party & party, std::list < std::string > & list )
               	   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a ballot options by contest party abb.
                *
                * @author	Yadickson Soto
                * @date		22/02/2012
                *
                * @param [in,out]	contest	The contest.
                * @param	partyAbb	   	The party abb.
                * @param	category	   	The category.
                * @param	list	result of ballot options
                * @param	getList		   	true to get list.
                *
                * @return	The ballot options by contest party abb.
                */

               void getBallotOptionsByContestPartyAbb ( Contest & contest,
                   std::string partyAbb,
                   std::list < Ballot_option > & list,
                   Category category,
                   bool getList = true)
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Fill all eligible options by contest party.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest					   	The contest.
                * @param [in,out]	party					   	The party.
                * @param [in,out]	eligibleOptionPrincipalList	List of eligible option principals.
                * @param [in,out]	eligibleOptionStandInList  	List of eligible option stand ins.
                * @param	getPrincipalList				   	true to get principal list.
                * @param	getStandInList					   	true to get stand in list.
                */

               void fillAllEligibleOptionsByContestParty ( Contest & contest,
                   Party & party,
                   std::list < Eligible_option > & eligibleOptionList,
                   std::list < Eligible_option > & eligibleOptionPrincipal,
                   std::list < Eligible_option > & eligibleOptionStandIn)
                   throw (Smartmatic::System::Exception::ElectionException);

               void getCountBallotOptionsByContestParty ( Contest & contest,
                   Party & party,
                   int & countList,
                   int & countPrincipal,
                   int & countStandIn)
				   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief    Fill all eligible options by contest.
                *
                * @author   Yadickson Soto yadickson.soto@smartmatic.com
                * @date 13/06/2011
                *
                * @param [in,out]   contest                     The contest.
                * @param [in,out]   eligibleOptionList          List of eligible option ins.
                */

               void fillAllEligibleOptionsByContest ( Contest & contest,
                   std::list < Eligible_option > & eligibleOptionList)
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets a ballot options by contest party.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest	The contest.
                * @param [in,out]	party  	The party.
                * @param	codes		   	The codes.
                *
                * @return	The ballot options by contest party.
                */

               void getBallotOptionsByContestParty ( Contest & contest,
                   Party & party,
                   std::list< std::string > & codes,
                   std::list < Ballot_option > & list)
                   throw (Smartmatic::System::Exception::ElectionException);

               /**
                * @brief	Gets an eligible option by ballot option.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest			The contest.
                * @param [in,out]	ballotOption	The ballot option.
                *
                * @return	The eligible option by ballot option.
                */

               Eligible_option & getEligibleOptionByBallotOption ( Contest & contest, Ballot_option & ballotOption )
                   throw (Smartmatic::System::Exception::ElectionException);


               std::string getEligibleOptionCodeByBallotOptionCode (
               		  const std::string & contestCode
               		, const std::string & parentBallotCode );


               /**
                * @brief	Gets if can obtain an eligible option by ballot option.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contest			The contest.
                * @param [in,out]	ballotOption	The ballot option.
                *
                * @return	true if can get an eligible option
                */

               bool getIfCanEligibleOptionByBallotOption ( Contest & contest, Ballot_option & ballotOption, Eligible_option & returnEligibleOption );

               /**
                * @brief	Gets all contest code by contest group.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	contestGroupCodes	The contest group codes.
                *
                * @return	all contest code by contest group.
                */

               void getAllContestCodeByContestGroup ( std::list < std::string > & contestGroupCodes,
            		   std::list < std::string > & list);

               /**
                * @brief	Sort ballot options list by tally position.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballotOptionList	List of ballot options.
                */

               void sortBallotOptionsListByTallyPosition ( std::list < Ballot_option > & ballotOptionList );

               /**
                * @brief	Sort eligible options list by tally position.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	eligibleOptionList	List of eligible options.
                */

               void sortEligibleOptionsListByTallyPosition ( std::list < Eligible_option > & eligibleOptionList );

               /**
                * @brief	Sort ballot options vector by tally position.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballotOptionVector	The ballot option vector.
                */

               void sortBallotOptionsVectorByTallyPosition ( std::vector < Ballot_option > & ballotOptionVector );

               /**
                * @brief	Sort ballot options party vector by tally position.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param [in,out]	ballotOptionVector	The ballot option vector.
                */

               void sortBallotOptionsPartyVectorByTallyPosition ( std::vector < Ballot_option > & ballotOptionVector );

               /**
                * @brief	Gets all contest vector.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @return	all contest vector.
                */

               void getAllContestVector (std::vector < Contest > & vector);

               /**
                * @brief	Gets all party vector.
                *
                * @author	Eduardo.campione
                * @date	28/04/2011
                *
                * @param	category	The category.
                *
                * @return	all party vector.
                */

               void getAllPartyVector (std::vector < Ballot_option > & vector, Category category = Category::ELECTION_PRINCIPAL);

               void getContestsByContestClassCode(std::string code, std::list <std::string> & list);

               void getContestCodeOrderByContestClass(std::list <std::string> & list);

               void getContestOrderByContestClassByContestGroup ( std::string codeContestGroup, std::list < Contest > & list );

               void getBallotOptionsByParentList (const std::string & contestCode, const std::string & parentBallotCode, std::list<Ballot_option> & children);

               void FillIndexes ();

               void persistence(Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories);

            private:
               Election election;///< The election
				static Smartmatic::Log::ISMTTLog* logger;///< The logger

            };
         }
      }
   }
}

#endif /*__ELECTION_WRAPPER_H__*/
