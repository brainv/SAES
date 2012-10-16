/**
 * @file IStateWrapper.cxx
 * @brief Body interface IStateWrapper
 */

#include "IStateWrapper.hxx"

using namespace Smartmatic::SAES::Voting;

IStateWrapper::IStateWrapper()
{

}

IStateWrapper::~IStateWrapper()
{

}

void IStateWrapper::setState( bool state )
{
    this->state = state;
}

