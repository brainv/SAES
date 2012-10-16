/**
 * @file IAuthenticator.cxx
 * @brief body for interface authenticator manager
 */

#include "IAuthenticator.hxx"

using namespace Smartmatic::SAES::Operation::Authenticator;

IAuthenticator::IAuthenticator ( IAuthenticator::MachineType machineType )
{
    this->machineType = machineType;
    this->electoralConfiguration = electoralConfiguration;
}

IAuthenticator::~IAuthenticator()
{

}

void IAuthenticator::init( Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration )
{
    this->electoralConfiguration = electoralConfiguration;
}

IAuthenticator::MachineType IAuthenticator::getMachineType()
{
    return machineType;
}

