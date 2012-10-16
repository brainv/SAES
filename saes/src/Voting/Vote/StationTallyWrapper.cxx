/**
 * @file StationTallyWrapper.cxx
 * @brief Body class StationTally
 */

#include "StationTallyWrapper.hxx"
#include <Voting/Codi/CodiFormatUtillity.h>
#include <Voting/Codi/CodiFileManager.hxx>
#include <Voting/ElectoralConfiguration.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>
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

using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* StationTallyWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Vote.StationTallyWrapper",GETTEXT_PACKAGE);

StationTallyWrapper::StationTallyWrapper(ElectoralConfiguration * electoralConfiguration, bool enableCodi)
{
	this->electoralConfiguration = electoralConfiguration;
	this->enableCodi = enableCodi;
}

void StationTallyWrapper::init()
{
	clear();

	std::list<Election::Contest> & contests = electoralConfiguration->getContestList();
	std::list<Election::Contest>::iterator it;

	for (it = contests.begin();
		 it != contests.end();
		 it++)
	{
		std::string contest_code = it->getCode();
		std::string customCode = it->getCustom_code();
		std::string contest_class_code = it->getContest_class_code ();
		std::string index;

		CodiFileManager::getOutputContestFileName(customCode, index, codiMachine, codiVotingType, customniscode);

		StationTally * st = new StationTally();
		st->setContest(contest_code);
		st->setNumber((*it).getCustom_code());
		st->setEmptyVotes(0);
		st->setProcessedVotes(0);

		if (enableCodi)
		{
			CodiRegister_S*  s_register = new CodiRegister_S (
					contest_code, customCode, contest_class_code, *st);

			if ( codi_files.find (index) ==  codi_files.end () )
				codi_files [index] = new CodiFile (index);

			codi_files [index]->insert_S_reg(*s_register);

			st->setSelectedVotes(0);
			st->setCodiChecksum(0);    // checksum del registro S
		}

		st->setType(Type::STATION_TALLY_AUTOMATED);
		stationTallyMap[contest_code] = st;

		std::list<Election::Ballot_option> & list (electoralConfiguration->getEligibleOptionsListByContestCode(contest_code));
		std::list<Election::Ballot_option> & principal (electoralConfiguration->getEligibleOptionsPrincipalByContestCode(contest_code));
		std::list<Election::Ballot_option> & standIn (electoralConfiguration->getEligibleOptionsStandInByContestCode(contest_code));

		registerMap & listMap (listRegisterMap[contest_code]);
		registerMap & principalMap (principalRegisterMap[contest_code]);
		registerMap & standInMap (standInRegisterMap[contest_code]);

		initRegisterMap(contest_code, listMap, list);
		initRegisterMap(contest_code, principalMap, principal);
		initRegisterMap(contest_code, standInMap, standIn);

		if (enableCodi)
			m_UpdateCodiFiles (index, contest_class_code, contest_code, customCode, list);
	}
}

StationTallyWrapper::~StationTallyWrapper()
{
	clear();
}

void StationTallyWrapper::m_UpdateCodiFiles (
		  std::string index
		, std::string contestClassCode
		, std::string contestCode
		, std::string customCode
		, std::list<Election::Ballot_option> & listOptions)
{
	CodiFile* codi_file = codi_files [index];

	for ( std::list<Election::Ballot_option>::iterator it = listOptions.begin ()
			; it != listOptions.end ()
			; it++)
	{
		CodiRegister_L* reg_L = new CodiRegister_L (
				  contestCode
				, customCode
				, contestClassCode
				, (*it)
				, allRegisterMap [contestCode] [it->getCode ()]);

		std::list<Election::Ballot_option> children_ballots;

		electoralConfiguration->getElection ()->getBallotOptionsByParentList ( contestCode, it->getCode (), children_ballots );

		for ( std::list<Election::Ballot_option>::iterator c_it = children_ballots.begin ()
				; c_it != children_ballots.end ()
				; c_it++)
		{
			CodiRegister_C* reg_C = new CodiRegister_C (
					  contestCode
					, customCode
					, contestClassCode
					, (*c_it)
					, allRegisterMap [contestCode] [c_it->getCode ()] );

			if ( c_it->getCategory() == Election::Category::ELECTION_PRINCIPAL )
			{
				reg_L->InsertPrincipal(*reg_C);
			}
			else if ( c_it->getCategory() == Election::Category::ELECTION_STAND_IN )
			{
				reg_L->InsertStandIn(*reg_C);
			}
			else
			{
				logger->Debug ("ERROR - list as children ballot option");
			}
		}

		codi_file->insert_L_reg (*reg_L);
	}
}

void StationTallyWrapper::initRegisterMap (
		  std::string contestCode
		, registerMap & map
		, std::list<Election::Ballot_option> & list)
{
	std::list<Election::Ballot_option>::iterator it;

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		Register * r = new Register();
		std::string ballotCode = (*it).getCode();

		r->setBallotOption(ballotCode);
		r->setTotal(0);

		if (enableCodi)
		{
			r->setCountList(0);    // Category 1
			r->setCountListP(0);   // Category 2
			r->setCountListPS(0);  // Category 3
			r->setCountListS(0);   // Category 4
			r->setCheckSum(0);     // checksum solo para registro L
		}

		map[ballotCode] = r;
		(allRegisterMap[contestCode])[ballotCode] = r;
	}
}

void StationTallyWrapper::cleanRegisterMap(registerMap & map)
{
	registerMap::iterator it;

    for (it = map.begin();
    	 it != map.end();
    	 it++)
    {
    	Register * r = (*it).second;
    	delete r;
    }

	map.clear();
}

void StationTallyWrapper::update (Vote & vote)
{
	bool count = false;

	switch(vote.getMode())
	{
	case VoteMode::VOTE_D:
		if(SAESConfigurationManager::Current()->getSaveDemoVotesInTransmissionPackage())
		{
			count = true;
		}
		break;
	case VoteMode::VOTE_O:
	case VoteMode::VOTE_R:
		count = true;
		break;
	case VoteMode::VOTE_S:
		break;
	}

	if (!count)
	{
		return;
	}

    Vote::SSequence sequenceS = vote.getSelections();
    Vote::SIterator its;

    for (its = sequenceS.begin();
    	 its != sequenceS.end();
    	 its++)
    {
    	Selection & selection (*its);
    	Selection::BSequence sequenceB = selection.getBallotOptions();
    	Selection::BIterator itb;

    	std::string contestCode = selection.getContest();

    	long countList = 0;
    	long countPrincipal = 0;
    	long countStandIn = 0;

    	for (itb = sequenceB.begin();
    		 itb != sequenceB.end();
    		 itb++)
    	{
    		std::string ballotCode = (*itb);
    		Register * r = (allRegisterMap[contestCode])[ballotCode];

    		r->setTotal(r->getTotal().get() + 1);  // increments L (list) total counter

    		if (enableCodi && countList == 0 && listRegisterMap[contestCode].find(ballotCode) != listRegisterMap[contestCode].end())
    		{
    			countList++;
    		}
    		else if (enableCodi && countPrincipal == 0 && principalRegisterMap[contestCode].find(ballotCode) != principalRegisterMap[contestCode].end())
    		{
    			countPrincipal++;
    		}
    		else if (enableCodi && countStandIn == 0 && standInRegisterMap[contestCode].find(ballotCode) != standInRegisterMap[contestCode].end())
    		{
    			countStandIn++;
    		}
    	}

    	if (enableCodi && sequenceB.size() > 0)
    	{
    		std::string ballotCode = *(sequenceB.begin());
    		Election::Ballot_option option = electoralConfiguration->getBallotOptionListFromBallotOptionCode(contestCode, ballotCode);

			Register * r = (allRegisterMap[contestCode])[option.getCode()];

			if (countPrincipal > 0 && countStandIn == 0)
			{
				r->setCountListP(r->getCountListP().get() + 1);
			}
			else if (countPrincipal == 0 && countStandIn > 0)
			{
				r->setCountListS(r->getCountListS().get() + 1);
			}
			else if (countPrincipal > 0 && countStandIn > 0)
			{
				r->setCountListPS(r->getCountListPS().get() + 1);
			}
			else if (countList > 0)
			{
				r->setCountList(r->getCountList().get() + 1);
			}
    	}

    	StationTally * st = stationTallyMap[contestCode];
    	st->setProcessedVotes(st->getProcessedVotes().get() + 1);

    	if (sequenceB.size() > 0L)
    	{
    		if (enableCodi) st->setSelectedVotes(st->getSelectedVotes().get() + 1);
    	}
    	else
    	{
    		st->setEmptyVotes(st->getEmptyVotes().get() + 1);
    	}
    }
}

void StationTallyWrapper::getStationTally(std::list <StationTally *> & list)
{
	std::map <std::string, StationTally *>::iterator it;

	if (enableCodi)
		CmputeCodiCheckSums ();

	for (it = stationTallyMap.begin();
		 it != stationTallyMap.end();
		 it++)
	{
		StationTally * st = (*it).second;
		std::string contestCode = st->getContest().get();

		StationTally::RSequence registers;
		registerMap::iterator itr;

		for (itr = allRegisterMap[contestCode].begin();
			 itr != allRegisterMap[contestCode].end();
			 itr++)
		{
			Register * r = (*itr).second;
			registers.push_back(*r);
		}

		st->setRegisters(registers);
		list.push_back(st);
	}
}

void StationTallyWrapper::CmputeCodiCheckSums ()
{
	for (std::map<std::string, CodiFile *>::iterator it = codi_files.begin ()
			; it != codi_files.end ()
			; it++)
	{
		it->second->CalculateChecksums ();
	}
}

void StationTallyWrapper::clear()
{
    std::map <std::string, StationTally *>::iterator it;

    for (it = stationTallyMap.begin();
    	 it != stationTallyMap.end();
    	 it++)
    {
    	std::string contestCode = (*it).first;
    	StationTally * st = (*it).second;
    	delete st;

		registerMap & listMap (listRegisterMap[contestCode]);
		registerMap & principalMap (principalRegisterMap[contestCode]);
		registerMap & standInMap (standInRegisterMap[contestCode]);

		cleanRegisterMap(listMap);
		cleanRegisterMap(principalMap);
		cleanRegisterMap(standInMap);
    }

    std::map <std::string, CodiFile *>::iterator itcf;

    for (itcf = codi_files.begin();
    	 itcf != codi_files.end();
    	 itcf++)
    {
    	std::string contestCode = (*itcf).first;
    	CodiFile * cf = (*itcf).second;
    	delete cf;
    }

    stationTallyMap.clear();
    allRegisterMap.clear();
	codi_files.clear();
}

std::map < std::string, CodiFile * > & StationTallyWrapper::getCodiFiles()
{
	return codi_files;
}

void StationTallyWrapper::setCodiMachine(std::string codiMachine)
{
	this->codiMachine = codiMachine;
}

void StationTallyWrapper::setCodiVotingType(std::string codiVotingType)
{
	this->codiVotingType = codiVotingType;
}

void StationTallyWrapper::setCustomniscode(std::string customniscode)
{
	this->customniscode = customniscode;
}
