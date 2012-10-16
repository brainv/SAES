/**
 * @file VotingState.cxx
 * @brief Body class state design pattern memento
 */

#include "VotingState.hxx"

using namespace Smartmatic::SAES::Operation::Voting;

VotingState::VotingState( std::string code, std::string value, VotingState::TypeResponse response )
{
    this->code = code;
    this->value = value;
    this->response = response;
}

std::string VotingState::getCode()
{
    return code;
}

std::string VotingState::getValue()
{
    return value;
}

VotingState::TypeResponse VotingState::getResponse()
{
    return response;
}

void VotingState::addBallotOption ( std::string contestCode, std::string partyCode, std::string ballotOptionCode )
{
    ( mapContest[ contestCode ] )[ partyCode ].remove( ballotOptionCode );
    ( mapContest[ contestCode ] )[ partyCode ].push_back ( ballotOptionCode );
}

void VotingState::removeContest ( std::string contestCode )
{
    mapContest.erase ( contestCode );
}

void VotingState::removeAllContest ()
{
	mapContest.clear();
}

void VotingState::removePartyByContest ( std::string contestCode, std::string partyCode )
{
    ( mapContest[ contestCode ] ).erase ( partyCode );
}

void VotingState::removeBallotOption ( std::string contestCode, std::string partyCode, std::string ballotOptionCode )
{
    ( mapContest[ contestCode ] )[ partyCode ].remove ( ballotOptionCode );
}

void VotingState::addContestByContestGroup ( std::string contestGroupCode, std::string contestCode )
{
    ( mapContestGroup[ contestGroupCode ] ).remove ( contestCode );
    ( mapContestGroup[ contestGroupCode ] ).push_back ( contestCode );
}

void VotingState::removeContestByContestGroup ( std::string contestGroupCode, std::string contestCode )
{
    ( mapContestGroup[ contestGroupCode ] ).remove ( contestCode );
}

void VotingState::removeContestGroup ( std::string contestGroupCode )
{
    mapContestGroup.erase( mapContestGroup.find ( contestGroupCode ) );
}

void VotingState::setLogicalVoterGroups ( VotingState::ListLogicalVoterGroup logicalVoterGroups )
{
    this->logicalVoterGroups = logicalVoterGroups;
}

void VotingState::setCustomAttributeDefinitions ( ListCustomAttributeDefinition customAttributeDefinitions )
{
    this->customAttributeDefinitions = customAttributeDefinitions;
}

std::list < std::string > VotingState::getContests ()
{
    std::list < std::string > list;

    if (mapContest.empty()) return list;

    MapContest::iterator it;
    MapContest temp = mapContest;

    for ( it = temp.begin();
          it != temp.end();
          it++ )
    {
        list.push_back( (*it).first );
    }

    return list;
}

std::list < std::string > VotingState::getPartys ( std::string contestCode )
{
    std::list < std::string > list;
    if (mapContest.empty() || mapContest.find(contestCode) == mapContest.end()) return list;

    MapList::iterator it;
    MapList temp = mapContest[ contestCode ];

    for ( it = temp.begin();
          it != temp.end();
          it++ )
    {
        list.push_back( (*it).first );
    }

    return list;
}

std::list < std::string > VotingState::getBallotOptions ( std::string contestCode, std::string partyCode )
{
    (( mapContest[ contestCode ] )[ partyCode ]).sort();
    return ( mapContest[ contestCode ] )[ partyCode ];
}

std::list < std::string > VotingState::getContestGroups ()
{
    std::list < std::string > list;
    if (mapContestGroup.empty()) return list;

    MapList::iterator it;
    MapList temp = mapContestGroup;

    for ( it = temp.begin();
          it != temp.end();
          it++ )
    {
        list.push_back( (*it).first );
    }

    return list;
}

std::list < std::string > & VotingState::getContestsByContestGroup ( std::string contestGroupCode )
{
    return mapContestGroup[ contestGroupCode ];
}

std::list < std::string > VotingState::getAllContestsByContestGroup ()
{
    std::list < std::string > list;
    std::list < std::string >::iterator it;
    std::list < std::string > listContestGroup = getContestGroups ();

    for (it = listContestGroup.begin();
         it != listContestGroup.end();
         it++)
    {
        std::list < std::string > listC = getContestsByContestGroup(*it);
        std::list < std::string >::iterator itC;

        for (itC = listC.begin();
             itC != listC.end();
             itC++)
        {
            list.remove((*itC));
            list.push_back((*itC));
        }
    }

    return list;
}

VotingState::ListLogicalVoterGroup & VotingState::getLogicalVoterGroups ()
{
    return logicalVoterGroups;
}

VotingState::ListCustomAttributeDefinition & VotingState::getCustomAttributeDefinitions ()
{
    return customAttributeDefinitions;
}

void VotingState::setContestByContestClass( std::list <std::string> contest )
{
    this->contestByContestClass = contest;
}

std::list <std::string> & VotingState::getContestByContestClass()
{
    return contestByContestClass;
}
