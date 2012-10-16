/**
 * @file VotingOriginator.cxx
 * @brief Body class originator design pattern memento
 */

#include "VotingOriginator.hxx"

using namespace Smartmatic::SAES::Operation::Voting;
int VotingOriginator::count = 0;

VotingMemento * VotingOriginator::createMemento()
{
    return new VotingMemento( state , count++ );
}

void VotingOriginator::setState( VotingState * state )
{
    this->state = state;
}

