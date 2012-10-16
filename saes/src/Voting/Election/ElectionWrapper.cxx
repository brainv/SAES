/**
 * @file ElectionWrapper.cxx
 * @brief Body class ElectionWrapper
 */

#include "ElectionWrapper.hxx"
#include <stdio.h>
#include <ctype.h>
#include <map>
#include <set>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <glibmm.h>
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Security/Encryption.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/IO/File.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;

#define LOGGER_PROJECT "Smartmatic.SAES.Voting.Election.ElectionWrapper" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* ElectionWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* ElectionWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

ElectionWrapper::ElectionWrapper( Election & election )
{
    this->election = election;
}

ElectionWrapper::~ElectionWrapper()
{
}

Election & ElectionWrapper::getElection ()
{
    return election;
}

Ballots & ElectionWrapper::getBallots ()
{
    return election.getBallots();
}

Ballot & ElectionWrapper::getBallot ( std::string codeBallot ) throw (ElectionException)
{
    Ballots & ballots( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       if ( codeBallot == (*b).getCode() )
       {
          return *b;
       }
    }

    Glib::ustring msg = Glib::ustring::compose("Ballot with code %1 not found.",codeBallot );
	logger->Debug(msg);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotWithCodeNotFound"),
    		logger);
}

Ballot_cards & ElectionWrapper::getBallotCards ( std::string codeBallot ) throw (ElectionException)
{
    return getBallot(codeBallot).getBallot_cards();
}

Ballot_cards & ElectionWrapper::getBallotCards ( Ballot & ballot )
{
    return ballot.getBallot_cards();
}

Ballot_card ElectionWrapper::getBallotCard ( std::string codeBallotCard, Ballot & ballot ) throw (ElectionException)
{
    Ballot_cards & ballotCards ( getBallotCards( ballot ) );

    for (Ballot_cards::Ballot_cardIterator
         b (ballotCards.getBallot_card ().begin ());
         b != ballotCards.getBallot_card ().end ();
         ++b)
    {
       if ( codeBallotCard == (*b).getCode() )
       {
          return *b;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Ballot card with code %1 not found.", codeBallotCard);
	logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotCardWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotCardWithCodeNotFound"),
    		logger);
}

Contests & ElectionWrapper::getContests ( Ballot_card & ballotCard )
{
    return ballotCard.getContests();
}

Contest & ElectionWrapper::getContest ( std::string codeContest, Ballot_card & ballotCard ) throw (ElectionException)
{
    Contests & contests ( getContests( ballotCard ) );

    for (Contests::ContestIterator
         c (contests.getContest ().begin ());
         c != contests.getContest ().end ();
         ++c)
    {
       if ( codeContest == (*c).getCode() )
       {
          return *c;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Contest by ballotCard with code %1 not found.", codeContest);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestWithCodeNotFound"),
    		logger);
}

Eligibles_options & ElectionWrapper::getEligiblesOptions ( Contest & contest )
{
    return contest.getEligibles_options();
}

Eligible_option & ElectionWrapper::getEligibleOption ( std::string codeEligibleOption, Contest & contest ) throw (ElectionException)
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       if ( codeEligibleOption == (*e).getCode() )
       {
          return *e;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Eligible option with code %1 not found",codeEligibleOption );
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.EligibleOptionWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.EligibleOptionWithCodeNotFound"),
    		logger);
}

Ballot_options & ElectionWrapper::getBallotOptions ( Eligible_option & eligibleOption )
{
    return eligibleOption.getBallot_options();
}

Ballot_option & ElectionWrapper::getBallotOption ( std::string codeBallotOption, Eligible_option & eligibleOption ) throw (ElectionException)
{
    Ballot_options & ballotOptions ( getBallotOptions( eligibleOption ) );

    for (Ballot_options::Ballot_optionIterator
         b (ballotOptions.getBallot_option ().begin ());
         b != ballotOptions.getBallot_option ().end ();
         ++b)
    {
       if ( codeBallotOption == (*b).getCode() )
       {
          return *b;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Ballot option with code %1 not found", codeBallotOption);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotOptionWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotOptionWithCodeNotFound"),
    		logger);
}

Ballot_option & ElectionWrapper::getBallotOptionByEligibleOption ( Eligible_option & eligibleOption ) throw (ElectionException)
{
    Ballot_options & ballotOptions ( getBallotOptions( eligibleOption ) );

    for (Ballot_options::Ballot_optionIterator
         b (ballotOptions.getBallot_option ().begin ());
         b != ballotOptions.getBallot_option ().end ();
         ++b)
    {
        return *b;
    }

    Glib::ustring text = Glib::ustring::compose("Ballot option for eligible option %1 not found.", eligibleOption.getCode());
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotOptionWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.BallotOptionWithCodeNotFound"),
    		logger);
}

Pad_position_group & ElectionWrapper::getPadPositionGroup ( Ballot_option & ballotOption )
{
    return ballotOption.getPad_position_group().get();
}

bool ElectionWrapper::IsLanguagesPresent ()
{
    return getElection().getLanguages().present ();
}

Languages & ElectionWrapper::getLanguages ()
{
    return getElection().getLanguages().get ();
}

Contest_classes & ElectionWrapper::getContestClasses ()
{
    return getElection ().getContest_classes ();
}

Contest_class & ElectionWrapper::getContestClass ( std::string codeContestClass ) throw (ElectionException)
{
    Contest_classes & contestClasses ( getContestClasses () );

    for (Contest_classes::Contest_classIterator
         c (contestClasses.getContest_class ().begin ());
         c != contestClasses.getContest_class ().end ();
         ++c)
    {
       if ( codeContestClass == (*c).getCode() )
       {
          return *c;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Contest class with code %1 not found.", codeContestClass);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestClassWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestClassWithCodeNotFound"),
    		logger);
}

Contest_class & ElectionWrapper::getContestClassByCustomCode ( std::string customCoodeContestClass ) throw (ElectionException)
{
    Contest_classes & contestClasses ( getContestClasses () );

    for (Contest_classes::Contest_classIterator
         c (contestClasses.getContest_class ().begin ());
         c != contestClasses.getContest_class ().end ();
         ++c)
    {
       if ( (*c).getCustom_code() != NULL && customCoodeContestClass == (*c).getCustom_code().get() )
       {
          return *c;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Contest class with custom code %1 not found.", customCoodeContestClass);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestCustomCodeWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestCustomCodeWithCodeNotFound"),
    		logger);
}

Contest_groups & ElectionWrapper::getContestGroups ()
{
    return getElection ().getContest_groups ();
}

Contest_group & ElectionWrapper::getContestGroup ( std::string codeContestGroup ) throw (ElectionException)
{
    Contest_groups & contestGroups ( getContestGroups() );

    for (Contest_groups::Contest_groupIterator
         c (contestGroups.getContest_group ().begin ());
         c != contestGroups.getContest_group ().end ();
         ++c)
    {
       if ( codeContestGroup == (*c).getCode() )
       {
          return *c;
       }
    }

    Glib::ustring text = Glib::ustring::compose("Contest group with code %1 not found.", codeContestGroup);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestGroupWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestGroupWithCodeNotFound"),
    		logger);
}

void ElectionWrapper::getContestGroupByList ( std::list < std::string > & codeContestGroups,
		std::list < Contest_group > & list ) throw (ElectionException)
{
    std::list < std::string >::iterator it;
    list.clear();

    for (it = codeContestGroups.begin ();
         it != codeContestGroups.end ();
         ++it)
    {
        list.push_back( getContestGroup ( *it ) );
    }
}

Contest & ElectionWrapper::getContest ( std::string codeContest ) throw (ElectionException)
{
    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot & ballot (*b);
       Ballot_cards & ballotCards ( getBallotCards( ballot ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Ballot_card & ballotCard (*bc);
          Contests & contests ( getContests( ballotCard ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
              if ( codeContest == (*c).getCode())
              {
                  return *c;
              }
          }
       }
    }

    Glib::ustring text = Glib::ustring::compose("Contest with code %1 not found.", codeContest);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.ContestWithCodeNotFound"),
    		logger);
}

void ElectionWrapper::getContestByList ( std::list < std::string > & codeContests, std::list < Contest > & list )
    throw (ElectionException)
{
    std::list < std::string >::iterator itlist;
    list.clear();

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
           Contests & contests ( getContests( *bc ) );

           for (itlist = codeContests.begin ();
                itlist != codeContests.end ();
                ++itlist)
           {
              for (Contests::ContestIterator
                c (contests.getContest ().begin ());
                c != contests.getContest ().end ();
                ++c)
              {
                  if ( (*itlist) == (*c).getCode())
                  {
                      list.push_back( (*c) );
                      break;
                  }
              }
          }
       }
    }
}

void ElectionWrapper::getContestByContestClass ( std::list < std::string > & codeContests, std::list < Contest > & list )
    throw (ElectionException)
{
    std::list < std::string >::iterator itlist;
    std::list <std::string> orderContestCode;
    std::list <std::string> endContestCode;

    getContestCodeOrderByContestClass(orderContestCode);

    for (itlist = orderContestCode.begin();
         itlist != orderContestCode.end();
         itlist++)
    {
        std::list < std::string >::iterator it;

        for (it = codeContests.begin();
             it != codeContests.end();
             it++)
        {
            if ((*it) == (*itlist))
            {
                endContestCode.push_back((*it));
                codeContests.remove((*it));
                break;
            }
        }
    }

    getContestByList(endContestCode, list);
}

void ElectionWrapper::getPartysByContestCode( std::string contestCode, std::list < Party > & list )
	throw (Smartmatic::System::Exception::ElectionException)
{
	Contest & contest ( getContest (contestCode) );
	getPartys(contest, list);
}

void ElectionWrapper::getPartys ( Contest & contest, std::list < Party > & list )
{
    list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       if ( (*e).getParent_code() != "")
    	   continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if ((*b).getCategory() == Category::ELECTION_LIST
        	  || (*b).getCategory() == Category::ELECTION_PRINCIPAL)
          {
             list.push_back( (*b).getParty() );
          }

          break;
       }

    }
}

void ElectionWrapper::getBallotOptionPartyByContest ( Contest & contest, std::list < Ballot_option > & list, Category category )
{
	list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if ( (*e).getParent_code() != "")
    	   continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if(category == (*b).getCategory())
          {
        	  list.push_back ( *b );
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

bool ElectionWrapper::getIfCanPartyAbbByContest ( Contest & contest, std::string partyAbb, Party & partyReturn, Category category)
{
	Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

	for (Eligibles_options::Eligible_optionIterator e (eligiblesOptions.getEligible_option ().begin ());
			e != eligiblesOptions.getEligible_option ().end (); ++e)
	{

		if ( (*e).getParent_code() != "" )
			continue;

		Ballot_options & ballotOptions ( getBallotOptions( *e ) );

		for (Ballot_options::Ballot_optionIterator b (ballotOptions.getBallot_option ().begin ());
				b != ballotOptions.getBallot_option ().end (); ++b)
		{
			if(category == (*b).getCategory() &&
                ((*b).getParty()).getAbbreviation() != NULL &&
                ((*b).getParty()).getAbbreviation().get().compare(partyAbb) == 0 )
			{
				partyReturn = (*b).getParty();
				return true;
			}
		}
	}

	return false;
}

Party & ElectionWrapper::getPartyAbbByContest ( Contest & contest, std::string partyAbb, Category category)
   throw (ElectionException)
{
	 Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if ( (*e).getParent_code() != "" )
           continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if(category == (*b).getCategory() &&
             ((*b).getParty()).getAbbreviation() != NULL &&
             ((*b).getParty()).getAbbreviation().get().compare(partyAbb) == 0 )
          {
             return (*b).getParty();
          }
       }
    }

    Glib::ustring text = Glib::ustring::compose("Party with abbreviation %1 not found.",partyAbb );
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.PartyWithAbbNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.PartyWithAbbNotFound"),
    		logger);
}

Party & ElectionWrapper::getPartyByContest ( Contest & contest, std::string partyCode, Category category )
    throw (ElectionException)
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if ( (*e).getParent_code() != "")
           continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if(category == (*b).getCategory() &&
             ((*b).getParty()).getCode() == partyCode )
          {
             return (*b).getParty();
          }
       }
    }

    Glib::ustring text = Glib::ustring::compose("Party with code %1 not found.", partyCode);
    logger->Debug(text);
    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.PartyWithCodeNotFound"),
    		N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.PartyWithCodeNotFound"),
    		logger);
}

void ElectionWrapper::getMapBallotOptionsByContest ( Contest & contest, std::map < std::string, Ballot_option > & ballotOptionMap, Category category )
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       if ((*e).getParent_code() == "" && category != Category::ELECTION_LIST) continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if(category == (*b).getCategory())
          {
        	  ballotOptionMap[(*b).getCode()] = *b;
          }
       }
    }
}

void ElectionWrapper::getBallotOptionsByContest ( Contest & contest, std::list < Ballot_option > & ballotOptionList, Category category , bool sort )
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       if ((*e).getParent_code() == "" && category != Category::ELECTION_LIST) continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if(category == (*b).getCategory())
          {
             ballotOptionList.push_back ( *b );
          }
       }
    }

    if (sort)
    {
    	sortBallotOptionsListByTallyPosition ( ballotOptionList );
    }
}

void ElectionWrapper::getMapBallotOptionsListByContest ( Contest & contest, std::map < std::string , Ballot_option > & ballotOptionMap )
{
    std::list <std::string>::iterator it;

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if((*e).getParent_code() != "") continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if ( (*b).getCategory() == Category::ELECTION_LIST ||
               (*b).getCategory() == Category::ELECTION_PRINCIPAL)
          {
        	  ballotOptionMap[(*b).getCode()] = *b;
          }
       }
    }
}

void ElectionWrapper::getBallotOptionsListByContest ( Contest & contest, std::list < Ballot_option > & ballotOptionList, bool sort )
{
    std::list <std::string>::iterator it;

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if((*e).getParent_code() != "") continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if ( (*b).getCategory() == Category::ELECTION_LIST ||
               (*b).getCategory() == Category::ELECTION_PRINCIPAL)
          {
             ballotOptionList.push_back ( *b );
          }
       }
    }

    if (sort)
    {
    	sortBallotOptionsListByTallyPosition ( ballotOptionList );
    }
}

void ElectionWrapper::getBallotOptionsListByContest ( Contest & contest, std::list <std::string> & codes, std::list < Ballot_option > & list )
{
	list.clear();
	std::list <std::string>::iterator it;

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if((*e).getParent_code() != "") continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
           for(it = codes.begin();
               it != codes.end();
               it++)
           {
              if ( (*b).getCode() == (*it) &&
                   ((*b).getCategory() == Category::ELECTION_LIST ||
                   (*b).getCategory() == Category::ELECTION_PRINCIPAL))
              {
            	 list.push_back ( *b );
                 codes.remove(*it);
                 break;
              }
           }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

void ElectionWrapper::getBallotOptionsByContest ( Contest & contest, std::list <std::string> & codes, std::list < Ballot_option > & list, Category category )
{
    list.clear();
    std::list <std::string>::iterator it;

    Eligibles_options & eligiblesOptions ( getEligiblesOptions( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       if ((*e).getParent_code() == "" && category != Category::ELECTION_LIST) continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          for(it = codes.begin();
              it != codes.end();
              it++)
          {
             if (category == (*b).getCategory() &&
                 (*it) == (*b).getCode())
             {
            	 list.push_back ( *b );
                 codes.remove(*it);
                 break;
             }
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

void ElectionWrapper::getContestByContestGroup ( std::string codeContestGroup, std::list < Contest > & list ) throw (ElectionException)
{
	list.clear();
    Contest_group & contestGroup ( getContestGroup ( codeContestGroup ) );

    for (Contest_group::Contest_codeIterator
         c (contestGroup.getContest_code ().begin ());
         c != contestGroup.getContest_code ().end ();
         ++c)
    {
    	list.push_back( getContest ( *c ) );
    }
}

void ElectionWrapper::getAllContest (std::list < Contest > & contestList)
{
    contestList.clear();

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Contests & contests ( getContests( *bc ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
              contestList.push_back ( *c );
          }
       }
    }
}

void ElectionWrapper::getAllContestCode (std::list < std::string > & contestList)
{
    contestList.clear();

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Ballot_card & ballotCard (*bc);
          Contests & contests ( getContests( ballotCard ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
              contestList.push_back ( (*c).getCode() );
          }
       }
    }
}

int ElectionWrapper::getMaxPartysAllContests()
{
    int max = 0;

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Contests & contests ( getContests( *bc ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
        	 std::list < Party > partyList;
        	 getPartys (*c, partyList);
             int size = partyList.size();
             if (size > max)
             {
                 max = size;
             }
          }
       }
    }

    return max;
}

int ElectionWrapper::getMaxBallotOptionsByContest(Contest & contest,
		Party & party)
{
    std::list < Party > partys;
    std::list < Party >::iterator e;

    getPartys (contest, partys);

    int maxCount = 0;

    for ( e = partys.begin ();
          e != partys.end ();
          ++e)
    {
        Party partyTmp = *(e);

        int eligibleOptionList;
        int eligibleOptionPrincipal;
        int eligibleOptionStandIn;

        getCountBallotOptionsByContestParty(contest, partyTmp, eligibleOptionList, eligibleOptionPrincipal, eligibleOptionStandIn);

        int numberBallotOptions = eligibleOptionList + eligibleOptionPrincipal + eligibleOptionStandIn;

        if(numberBallotOptions > maxCount)
        {
        	maxCount = numberBallotOptions;
            party = partyTmp;
        }
    }

    return maxCount;
}

void ElectionWrapper::getBallotOptionsByContestPartyAbb ( Contest & contest,std::string partyAbb, std::list < Ballot_option > & list, Category category,bool getList)throw (Smartmatic::System::Exception::ElectionException)
{
	list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          Party & partyBallotOption ( (*b).getParty() );

          if (!getList && (*e).getParent_code() == "")
             continue;

          if (category == (*b).getCategory() &&
                  partyBallotOption.getAbbreviation () != NULL &&
              partyBallotOption.getAbbreviation ().get().compare(partyAbb) == 0 )
          {
             list.push_back( *b );
             break;
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

void ElectionWrapper::getBallotOptionsByContestParty ( Contest & contest, Party & party, std::list < Ballot_option > & list, Category category )
    throw (ElectionException)
{
	list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if((*e).getParent_code() == "" && category != Category::ELECTION_LIST) continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          Party & partyBallotOption ( (*b).getParty() );

          if (category == (*b).getCategory() &&
              party.getCode() == partyBallotOption.getCode() )
          {
        	  list.push_back( *b );
             break;
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

void ElectionWrapper::getBallotOptionsListByContestParty ( Contest & contest, Party & party, std::list < Ballot_option > & list )
    throw (ElectionException)
{
    list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {

       if((*e).getParent_code() != "") continue;

       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if ((*b).getCategory() == Category::ELECTION_LIST ||
              (*b).getCategory() == Category::ELECTION_PRINCIPAL)
          {
        	  if ((*b).getParty().getCode() == party.getCode())
        	  {
        		  list.push_back( *b );
        	  }
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

void ElectionWrapper::getAllBallotOptionsListCodeByContestParty ( Contest & contest, Party & party, std::list < std::string > & list )
    throw (ElectionException)
{
    list.clear();
    std::list < Ballot_option > ballotList;
    std::list < Ballot_option >::iterator it;

    getBallotOptionsListByContestParty(contest, party, ballotList);

    for (it = ballotList.begin();
    		it != ballotList.end();
    		it++)
    {
    	list.push_back((*it).getCode());
    }

    getBallotOptionsByContestParty(contest, party, ballotList, Category::ELECTION_PRINCIPAL);

    for (it = ballotList.begin();
    		it != ballotList.end();
    		it++)
    {
    	list.push_back((*it).getCode());
    }

    getBallotOptionsByContestParty(contest, party, ballotList, Category::ELECTION_STAND_IN);

    for (it = ballotList.begin();
    		it != ballotList.end();
    		it++)
    {
    	list.push_back((*it).getCode());
    }
}

void ElectionWrapper::getCountBallotOptionsByContestParty ( Contest & contest,
    Party & party,
    int & countList,
    int & countPrincipal,
    int & countStandIn)
        throw (ElectionException)
{
	countList = countPrincipal = countStandIn = 0;

    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          Party & partyBallotOption ( (*b).getParty() );

          if ( party.getCode() != partyBallotOption.getCode() ) continue;

          if ( Category::ELECTION_LIST == (*b).getCategory() ||
               ((*e).getParent_code() == "" &&
               Category::ELECTION_PRINCIPAL == (*b).getCategory()) )
          {
             countList++;
          }
          else if (Category::ELECTION_PRINCIPAL == (*b).getCategory() )
          {
             countPrincipal++;
          }
          else if (Category::ELECTION_STAND_IN == (*b).getCategory() )
          {
             countStandIn++;
          }
       }
    }
}

void ElectionWrapper::fillAllEligibleOptionsByContestParty ( Contest & contest,
    Party & party,
    std::list < Eligible_option > & eligibleOptionList,
    std::list < Eligible_option > & eligibleOptionPrincipal,
    std::list < Eligible_option > & eligibleOptionStandIn)
        throw (ElectionException)
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          Party & partyBallotOption ( (*b).getParty() );

          if ( party.getCode() != partyBallotOption.getCode() ) continue;

          if ( Category::ELECTION_LIST == (*b).getCategory() ||
               ((*e).getParent_code() == "" &&
               Category::ELECTION_PRINCIPAL == (*b).getCategory()) )
          {
             eligibleOptionList.push_back( *e );
          }
          else if (Category::ELECTION_PRINCIPAL == (*b).getCategory() )
          {
             eligibleOptionPrincipal.push_back( *e );
          }
          else if (Category::ELECTION_STAND_IN == (*b).getCategory() )
          {
             eligibleOptionStandIn.push_back( *e );
          }
       }
    }

    sortEligibleOptionsListByTallyPosition ( eligibleOptionList );
    sortEligibleOptionsListByTallyPosition ( eligibleOptionPrincipal );
    sortEligibleOptionsListByTallyPosition ( eligibleOptionStandIn );
}


void ElectionWrapper::fillAllEligibleOptionsByContest ( Contest & contest,
   std::list < Eligible_option > & eligibleOptionList)
   throw (ElectionException)
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          eligibleOptionList.push_back( *e );
       }
    }

    sortEligibleOptionsListByTallyPosition ( eligibleOptionList );
}

void ElectionWrapper::getBallotOptionsByContestParty ( Contest & contest,
    Party & party,
    std::list< std::string > & codes,
    std::list < Ballot_option > & list) throw (ElectionException)
{
	list.clear();

    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          Party & partyBallotOption ( (*b).getParty() );

          if ( party.getCode() == partyBallotOption.getCode() )
          {
             std::list < std::string >::iterator it;

             for (it = codes.begin();
                  it != codes.end();
                  it++)
             {
                 if ( (*it) != (*b).getCode() ) continue;

                 list.push_back( *b );
                 codes.remove( (*it) );
                 break;
             }
             break;
          }
       }
    }

    sortBallotOptionsListByTallyPosition ( list );
}

bool ElectionWrapper::getIfCanEligibleOptionByBallotOption ( Contest & contest, Ballot_option & ballotOption, Eligible_option & returnEligibleOption )
{
	Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

	for (Eligibles_options::Eligible_optionIterator
		 e (eligiblesOptions.getEligible_option ().begin ());
		 e != eligiblesOptions.getEligible_option ().end ();
		 ++e)
	{
	   Ballot_options & ballotOptions ( getBallotOptions( *e ) );

	   for (Ballot_options::Ballot_optionIterator
			b (ballotOptions.getBallot_option ().begin ());
			b != ballotOptions.getBallot_option ().end ();
			++b)
	   {
		  if ( (*b).getCode() == ballotOption.getCode() )
		  {
			 returnEligibleOption = *e;
			 return true;
		  }
	   }
	}

	return false;
}

std::string ElectionWrapper::getEligibleOptionCodeByBallotOptionCode (
		  const std::string & contestCode
		, const std::string & parentBallotCode )
{
	std::string eoption_code = "";

	Contest& contest = getContest (contestCode);
	Eligibles_options & eligible_options ( getEligiblesOptions ( contest ) );

	Eligibles_options::Eligible_optionIterator eo_it;
	Eligibles_options::Eligible_optionSequence eo_seq =
			eligible_options.getEligible_option();

	for ( eo_it = eo_seq.begin (); eo_it != eo_seq.end (); eo_it++)
	{
		Ballot_options::Ballot_optionSequence & b_option_seq (
				getBallotOptions( *eo_it ).getBallot_option () );

		for (Ballot_options::Ballot_optionIterator b_it = b_option_seq.begin ()
				; b_it != b_option_seq.end ()
				; b_it++)
		{
			if ( b_it->getCode () == parentBallotCode )
			{
				eoption_code = eo_it->getCode ();
				break;
			}
		}

		if ( ! eoption_code.empty() )
			break;
	}

	return eoption_code;
}

void ElectionWrapper::getBallotOptionsByParentList (
		  const std::string & contestCode
		, const std::string & parentBallotCode,
		std::list<Ballot_option> & children)
{
	children.clear();
	std::string parent_eoption_code =
			getEligibleOptionCodeByBallotOptionCode (contestCode, parentBallotCode);

	Contest& contest = getContest (contestCode);
	Eligibles_options & eligible_options ( getEligiblesOptions ( contest ) );

	Eligibles_options::Eligible_optionIterator eo_it;
	Eligibles_options::Eligible_optionSequence eo_seq =
			eligible_options.getEligible_option();

	for ( eo_it = eo_seq.begin (); eo_it != eo_seq.end (); eo_it++)
	{
		if ( eo_it->getParent_code () ==  parent_eoption_code )
		{
			Ballot_options::Ballot_optionSequence & b_option_seq (
					getBallotOptions( *eo_it ).getBallot_option () );

			for (Ballot_options::Ballot_optionIterator b_it = b_option_seq.begin ()
					; b_it != b_option_seq.end ()
					; b_it++)
			{
				children.insert (
						children.end ()
						, eo_it->getBallot_options ().getBallot_option ().begin ()
						, eo_it->getBallot_options ().getBallot_option ().end () );
			}
		}
	}

	sortBallotOptionsListByTallyPosition ( children );
}

Eligible_option & ElectionWrapper::getEligibleOptionByBallotOption ( Contest & contest, Ballot_option & ballotOption ) throw (ElectionException)
{
    Eligibles_options & eligiblesOptions ( getEligiblesOptions ( contest ) );

    for (Eligibles_options::Eligible_optionIterator
         e (eligiblesOptions.getEligible_option ().begin ());
         e != eligiblesOptions.getEligible_option ().end ();
         ++e)
    {
       Ballot_options & ballotOptions ( getBallotOptions( *e ) );

       for (Ballot_options::Ballot_optionIterator
            b (ballotOptions.getBallot_option ().begin ());
            b != ballotOptions.getBallot_option ().end ();
            ++b)
       {
          if ( (*b).getCode() == ballotOption.getCode() )
          {
             return *e;
          }
       }
    }

    throw ElectionException( _("Smartmatic.SAES.Voting.Election.ElectionWrapper.EligibleOptionNotFound"),
                            N_("Smartmatic.SAES.Voting.Election.ElectionWrapper.EligibleOptionNotFound"), 
                            logger);
}

void ElectionWrapper::getAllContestCodeByContestGroup ( std::list < std::string > & contestGroupCodes, std::list < std::string > & list )
{
    std::set < std::string > listContest;
    std::list < std::string >::iterator it;

    getAllContestCode (list);

    for ( it = contestGroupCodes.begin();
          it != contestGroupCodes.end();
          it++ )
    {
        std::list < Contest > sequence;
        std::list < Contest >::iterator its;

        getContestByContestGroup(*it, sequence);

        for ( its = sequence.begin();
              its != sequence.end();
              its++ )
        {
            listContest.insert ((*its).getCode());
        }
    }

    std::list < std::string > tempList = list;
    std::list < std::string >::iterator itinner;

    for ( itinner = tempList.begin();
          itinner != tempList.end();
          itinner++ )
    {
        if ( listContest.find (*itinner) == listContest.end() )
        {
            list.remove(*itinner);
        }
    }
}

void ElectionWrapper::sortBallotOptionsListByTallyPosition ( std::list < Ballot_option > & ballotOptionList )
{
    std::multimap<int,Ballot_option> map;
    std::multimap<int,Ballot_option>::iterator itmap;

    std::list < Ballot_option >::iterator it;

    for ( it = ballotOptionList.begin();
          it != ballotOptionList.end();
          it++ )
    {
        map.insert (std::pair<int,Ballot_option>((*it).getTally_position(),*it));
    }

    ballotOptionList.clear();

    for ( itmap = map.begin();
          itmap != map.end();
          itmap++ )
    {
        ballotOptionList.push_back((*itmap).second);
    }
}

void ElectionWrapper::sortEligibleOptionsListByTallyPosition ( std::list < Eligible_option > & eligibleOptionList )
{
    std::multimap<int,Eligible_option> map;
    std::multimap<int,Eligible_option>::iterator itmap;

    std::list < Eligible_option >::iterator it;

    for ( it = eligibleOptionList.begin();
          it != eligibleOptionList.end();
          it++ )
    {
        try
        {
            Eligible_option & e (*it);
            Ballot_option & b ( getBallotOptionByEligibleOption( e ));
            map.insert (std::pair<int,Eligible_option>(b.getTally_position(),*it));
        }
        catch(...)
        {

        }
    }

    eligibleOptionList.clear();

    for ( itmap = map.begin();
          itmap != map.end();
          itmap++ )
    {
        eligibleOptionList.push_back((*itmap).second);
    }
}

void ElectionWrapper::sortBallotOptionsVectorByTallyPosition ( std::vector < Ballot_option > & ballotOptionVector )
{
    std::multimap<int,Ballot_option> map;
    std::multimap<int,Ballot_option>::iterator itmap;

    std::vector < Ballot_option >::iterator it;

    for ( it = ballotOptionVector.begin();
          it != ballotOptionVector.end();
          it++ )
    {
        map.insert (std::pair<int,Ballot_option>((*it).getTally_position(),*it));
    }

    ballotOptionVector.clear();

    for ( itmap = map.begin();
          itmap != map.end();
          itmap++ )
    {
        ballotOptionVector.push_back((*itmap).second);
    }
}

void ElectionWrapper::sortBallotOptionsPartyVectorByTallyPosition ( std::vector < Ballot_option > & ballotOptionVector )
{
    std::map<std::string,Ballot_option> map;
    std::map<std::string,Ballot_option>::iterator itmap;

    std::vector < Ballot_option >::iterator it;

    for ( it = ballotOptionVector.begin();
          it != ballotOptionVector.end();
          it++ )
    {
        map.insert (std::pair<std::string,Ballot_option>((*it).getParty().getCode(),*it));
    }

    ballotOptionVector.clear();

    for ( itmap = map.begin();
          itmap != map.end();
          itmap++ )
    {
        ballotOptionVector.push_back((*itmap).second);
    }
}

void ElectionWrapper::getAllContestVector (std::vector < Contest > & vector)
{
    vector.clear();

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Contests & contests ( getContests( *bc ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
              vector.push_back ( *c );
          }
       }
    }
}

void ElectionWrapper::getAllPartyVector (std::vector < Ballot_option > & vector, Category category)
{
    vector.clear();

    std::list < Contest > contestList;
    std::list < Contest >::iterator it;

    getAllContest(contestList);

    for (it = contestList.begin();
         it != contestList.end();
         it++)
    {
        Eligibles_options & eligiblesOptions ( getEligiblesOptions( *it ) );

        for (Eligibles_options::Eligible_optionIterator
             e (eligiblesOptions.getEligible_option ().begin ());
             e != eligiblesOptions.getEligible_option ().end ();
             ++e)
        {

           if ( (*e).getParent_code() != "" )
               continue;

           Ballot_options & ballotOptions ( getBallotOptions( *e ) );

           for (Ballot_options::Ballot_optionIterator
                b (ballotOptions.getBallot_option ().begin ());
                b != ballotOptions.getBallot_option ().end ();
                ++b)
           {
              if(category == (*b).getCategory())
              {
                  vector.push_back ( *b );
              }
           }
        }
    }

    sortBallotOptionsPartyVectorByTallyPosition(vector);
}

void ElectionWrapper::getContestsByContestClassCode(std::string code, std::list <std::string> & list)
{
    list.clear();
    std::list < std::string >::iterator itlist;

    Ballots & ballots ( getBallots() );

    for (Ballots::BallotIterator
         b (ballots.getBallot ().begin ());
         b != ballots.getBallot ().end ();
         ++b)
    {
       Ballot_cards & ballotCards ( getBallotCards( *b ) );

       for (Ballot_cards::Ballot_cardIterator
            bc (ballotCards.getBallot_card ().begin ());
            bc != ballotCards.getBallot_card ().end ();
            ++bc)
       {
          Contests & contests ( getContests( *bc ) );

          for (Contests::ContestIterator
            c (contests.getContest ().begin ());
            c != contests.getContest ().end ();
            ++c)
          {
              if ((*c).getContest_class_code() == code)
              {
                  list.push_back( (*c).getCode() );
              }
          }
       }
    }
}

void ElectionWrapper::getContestCodeOrderByContestClass(std::list <std::string> & list)
{
    list.clear();

    Contest_classes & contestClasses ( getContestClasses () );

    for (Contest_classes::Contest_classIterator
         c (contestClasses.getContest_class ().begin ());
         c != contestClasses.getContest_class ().end ();
         ++c)
    {
        std::list <std::string> contest;
        std::list <std::string>::iterator it;

        getContestsByContestClassCode((*c).getCode(), contest);

        it = list.end();
        list.insert (it, contest.begin(), contest.end());
    }
}

void ElectionWrapper::getContestOrderByContestClassByContestGroup ( std::string codeContestGroup, std::list < Contest > & list )
{
    list.clear();

    try
    {
        std::list < Contest > contest;
        std::list <std::string> order;

        getContestByContestGroup(codeContestGroup, contest);
        getContestCodeOrderByContestClass(order);

        std::list < Contest >::iterator itc;
        std::list <std::string>::iterator ito;

        for (ito = order.begin();
             ito != order.end();
             ito++)
        {
            for (itc = contest.begin();
                 itc != contest.end();
                 itc++)
            {
                if ((*ito) == (*itc).getCode())
                {
                    list.push_back(*itc);
                    break;
                }
            }
        }
    }
    catch (ElectionException &ex)
    {
        logger->Debug ("FATAL - Error get contest order by contest class by contest group - codeContestGroup: " + codeContestGroup);
    }
}

void ElectionWrapper::persistence(Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories)
{
	logger->Debug("persistence electoral config");

    std::ostringstream str;
    std::string outString;

    ElectionTypes::NamespaceInfomap mapv;
    mapv[""].name = NAMESPACE_VOTING_ELECTION;
    mapv[""].schema = "";

    try
    {
    	serializeElection(str, election, mapv, "UTF-8", ElectionTypes::Flags::dont_validate);
    	outString = str.str();
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
    	std::stringstream ss;
    	ss << "FATAL - " << __func__ << e;
    	logger->Error(ss.str());
     }
     catch (...)
     {
         std::stringstream ss;
         ss << "FATAL - " << __func__;
         logger->Error(ss.str());
     }

     std::string domFile = directories.getElectionFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_DOM);
     std::string flashFile = directories.getElectionFileFullPath(Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH);

     try
     {
    	 Encryption::getInstance()->saveXmlFile(outString, domFile,
    			 Smartmatic::SAES::Security::Encryption::EXTERNAL_FILE,
    	         Smartmatic::SAES::Security::Encryption::UP_KEY,
    	         SAESCommonConfigurationManager::Current()->isCompressElection());

    	 File::copyFile(domFile, flashFile);
     }
     catch(...)
     {
         std::stringstream ss;
         ss << "FATAL - " << __func__;
         logger->Error(ss.str());
     }
}
