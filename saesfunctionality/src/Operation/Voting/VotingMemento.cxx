/**
 * @file VotingMemento.cxx
 * @brief Body class memento design pattern memento
 */

#include "VotingOriginator.hxx"

using namespace Smartmatic::SAES::Operation::Voting;

VotingMemento::VotingMemento ( VotingState * state, int position )
{
    this->state = state;
    this->position = position;
}

VotingMemento::~VotingMemento ()
{
    if (state == NULL)
    {
        delete state;
    }
}

VotingState * VotingMemento::getState()
{
    return state;
}

int VotingMemento::getPosition()
{
    return this->position;
}
