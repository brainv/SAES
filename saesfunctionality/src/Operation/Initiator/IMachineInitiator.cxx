/**
 * @file IMachineInitiator.hxx
 * @brief body interface for machine operation manager
 */

#include "IMachineInitiator.hxx"

using namespace Smartmatic::SAES::Operation::Initiator;

IMachineInitiator::IMachineInitiator()
{

}

IMachineInitiator::~IMachineInitiator()
{

}

void IMachineInitiator::init( std::list < ICheckCondition * > & conditions, Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration )
{
    this->conditions = conditions;
    this->electoralConfiguration = electoralConfiguration;
    mode = FIRST_TIME;
}

InitializationStatus IMachineInitiator::getStatus()
{
    return status;
}

void IMachineInitiator::setMode(RunModeType mode)
{
	this->mode = mode;
}
