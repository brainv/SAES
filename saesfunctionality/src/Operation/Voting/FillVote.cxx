/**
 * @file FillVote.cxx
 * @brief Body class fill vote
 */

#include "FillVote.hxx"
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* FillVote::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Voting.FillVote",GETTEXT_PACKAGE);

FillVote::FillVote ( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration )
{
    this->electoralConfiguration = electoralConfiguration;
}

FillVote::~FillVote ()
{
}

void FillVote::fillBlankVote ( Smartmatic::SAES::Voting::Vote::Vote & vote,
    int & contestCount,
    int & ballotOptionCount,
    Smartmatic::SAES::Operation::Voting::VotingMemento * memento )
    throw (Smartmatic::System::Exception::ElectionException)
{
    contestCount = 0;
    ballotOptionCount = 0;

    std::string logicalVoterGroupCode = "";
    logicalVoterGroupCode = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();

    Smartmatic::SAES::Voting::Vote::Vote::SSequence& sseq (vote.getSelections());
    vote.setLogicalVoterGroup( logicalVoterGroupCode );
    Smartmatic::SAES::Voting::Vote::Selection selection;

    Smartmatic::SAES::Functionality::Configuration::BlankVoteListContestCodeType type;

    std::list < std::string > c;
    std::list < std::string >::iterator itc;

    electoralConfiguration->getElection()->getContestCodeOrderByContestClass(c);

    contestCount = c.size();

    for (itc = c.begin();
            itc != c.end();
            itc++)
   {
       selection.setContest ( (*itc) );
       sseq.push_back( selection );
   }
}

void FillVote::fillNormalVote ( Smartmatic::SAES::Voting::Vote::Vote & vote,
    int & contestCount,
    int & ballotOptionCount,
    std::vector < VotingMemento * > & caretaker )
    throw (Smartmatic::System::Exception::ElectionException)
{
    contestCount = 0;
    ballotOptionCount = 0;

    VotingMemento * memento = caretaker.back();

    int sizeLVG = memento->getState()->getLogicalVoterGroups().size();
    int sizeCG = memento->getState()->getContestGroups().size();

    if ( sizeLVG != 1 || sizeCG != 1 )
    {
        std::stringstream ss;
		ss<< __func__ << " " <<  __LINE__ << " - FATAL - Config election error - sizeLVG=" << sizeLVG << " sizeCG=" << sizeCG;
		logger->Debug(ss.str());
        throw ElectionException (_("Smartmatic.SAES.Operation.Voting.VotingExperienceController.ErrorLogicalVoterGroupAndCustomAttributeDefinition"),
                                   "Smartmatic.SAES.Operation.Voting.VotingExperienceController.ErrorLogicalVoterGroupAndCustomAttributeDefinition",
                                 logger);
    }

    std::string logicalVoterGroupCode = "";
    std::string lvgContestGroupCode = "";
    std::string contestGroupCode = "";

    logicalVoterGroupCode = (*(memento->getState()->getLogicalVoterGroups().begin())).getCode();
    lvgContestGroupCode = (*(memento->getState()->getLogicalVoterGroups().begin())).getContest_group_code();
    contestGroupCode = *(memento->getState()->getContestGroups().begin());

    if (lvgContestGroupCode != contestGroupCode)
    {
        std::stringstream ss;
		ss << __func__ << " " <<  __LINE__ << " - FATAL - Config election error - lvgContestGroupCode=" << lvgContestGroupCode << " contestGroupCode=" << contestGroupCode;
		logger->Debug(ss.str());
       
        throw Smartmatic::System::Exception::ElectionException (_("Smartmatic.SAES.Operation.Voting.FillVote.ErrorLogicalVoterGroupAndCustomAttributeDefinition"),
                                                                "Smartmatic.SAES.Operation.Voting.FillVote.ErrorLogicalVoterGroupAndCustomAttributeDefinition",
                                                                logger);
    }

    Smartmatic::SAES::Voting::Vote::Vote::SSequence& sseq (vote.getSelections());
    vote.setLogicalVoterGroup( logicalVoterGroupCode );

    std::list < std::string > corder;
    std::list < std::string >::iterator itorder;

    electoralConfiguration->getElection()->getContestCodeOrderByContestClass(corder);

    for (itorder = corder.begin();
         itorder != corder.end();
         itorder++)
    {
        int size = caretaker.size();

        for (int i = 0;i < size;i++)
        {
            VotingMemento * m = caretaker[i];

            std::list < std::string > c = m->getState()->getContests();
            std::list < std::string >::iterator itc;

            for (itc = c.begin();
                 itc != c.end();
                 itc++)
            {
                if (*itc != *itorder) continue;

                contestCount++;

                std::list < std::string > p = m->getState()->getPartys( *itc );
                std::list < std::string >::iterator itp;

                Smartmatic::SAES::Voting::Vote::Selection::BSequence bseq;
                Smartmatic::SAES::Voting::Vote::Selection selection;
                selection.setContest ( *itc );

                for ( itp = p.begin();
                      itp != p.end();
                      itp++)
                {
                    if ((*itp) == "")continue;
                    std::list < std::string > b = m->getState()->getBallotOptions ( *itc, *itp );
                    std::list < std::string >::iterator itb;

                    for ( itb = b.begin();
                          itb != b.end();
                          itb++)
                    {
                        if ((*itb) == "")continue;
                        ballotOptionCount++;
                        bseq.push_back( *itb );
                    }
                }

                selection.setBallotOptions( bseq );
                sseq.push_back( selection );

                m->getState()->getContests().remove(*itc);
                break;
            }
        }
    }
}

void FillVote::fillVote( Smartmatic::SAES::Voting::Vote::Vote & vote,
    int contestCount,
    int ballotOptionCount )
{
    std::string contestCode = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getContestCode();
    std::string ballotOptionCode = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getBallotOptionCode();

    int maxContest = electoralConfiguration->getMaxContestByVote() + 1;
    int maxBallotOptions = electoralConfiguration->getMaxBallotOptionsByVote();
    int ballotOptionDummyByContest = (maxBallotOptions - ballotOptionCount) / (maxContest - contestCount) + 1;

    Smartmatic::SAES::Voting::Vote::Vote::SSequence& sseq (vote.getSelections());

    for ( int i = contestCount; i < maxContest; i++ )
    {
        Smartmatic::SAES::Voting::Vote::Selection::BSequence bseq;
        Smartmatic::SAES::Voting::Vote::Selection selection;
        selection.setContest ( contestCode );

        for ( int j = 0;
              j < ballotOptionDummyByContest && ballotOptionCount < maxBallotOptions;
              j++, ballotOptionCount++ )
        {
            bseq.push_back( ballotOptionCode );
        }

        selection.setBallotOptions( bseq );
        sseq.push_back( selection );
    }
}

