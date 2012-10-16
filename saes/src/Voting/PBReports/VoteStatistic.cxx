/*
 * VoteStatistic.cxx
 *
 *  Created on: 13/09/2011
 *      Author: soto
 */

#include "VoteStatistic.hxx"

using namespace Smartmatic::SAES::Voting::PBReports;

VoteStatistic::VoteStatistic()
{
	clearAll();
}

VoteStatistic::~VoteStatistic()
{

}

void VoteStatistic::clearAll()
{
	this->totalVotes = 0;
	this->officialVotes = 0;
	this->demoVotes = 0;
	this->securityCopyVotes = 0;
	this->superNullVotes = 0;
	this->simulateVotes = 0;
	this->duplicatedVotes = 0;
}

void VoteStatistic::clearAllNotDuplicate()
{
	this->totalVotes = 0;
	this->officialVotes = 0;
	this->demoVotes = 0;
	this->securityCopyVotes = 0;
	this->superNullVotes = 0;
	this->simulateVotes = 0;
}

unsigned int VoteStatistic::getTotalVotes()
{
	return totalVotes;
}

unsigned int VoteStatistic::getOfficialVotes()
{
	return officialVotes;
}

unsigned int VoteStatistic::getDemoVotes()
{
	return demoVotes;
}

unsigned int VoteStatistic::getSecurityCopyVotes()
{
	return securityCopyVotes;
}

unsigned int VoteStatistic::getSuperNullVotes()
{
	return superNullVotes;
}

unsigned int VoteStatistic::getDuplicatedVotes()
{
	return duplicatedVotes;
}

unsigned int VoteStatistic::getSimulateVotes()
{
	return simulateVotes;
}

void VoteStatistic::setTotalVotes(unsigned int totalVotes)
{
	this->totalVotes = totalVotes;
}

void VoteStatistic::setOfficialVotes(unsigned int officialVotes)
{
	this->officialVotes = officialVotes;
}

void VoteStatistic::setDemoVotes(unsigned int demoVotes)
{
	this->demoVotes = demoVotes;
}

void VoteStatistic::setSecurityCopyVotes(unsigned int securityCopyVotes)
{
	this->securityCopyVotes = securityCopyVotes;
}

void VoteStatistic::setSuperNullVotes(unsigned int superNullVotes)
{
	this->superNullVotes = superNullVotes;
}

void VoteStatistic::setDuplicatedVotes(unsigned int duplicatedVotes)
{
	this->duplicatedVotes = duplicatedVotes;
}

void VoteStatistic::setSimulateVotes(unsigned int simulateVotes)
{
	this->simulateVotes = simulateVotes;
}
