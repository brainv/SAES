/*
 * CodiRegisterS.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#include "CodiRegisterS.h"

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::SAES::Voting::Vote;

CodiRegister_S::CodiRegister_S(
		  const std::string & contestCode
		, const std::string & customCode
		, const std::string & contestClassCode
		, StationTally & stationTally)
: CodiRegisterBase (contestCode, customCode, contestClassCode)
, station_tally ( stationTally )
{

}

CodiRegister_S::CodiRegister_S(const CodiRegister_S & ss)
: CodiRegisterBase (ss.contest_code, ss.customCode, ss.contest_class_code)
, station_tally ( ss.station_tally )
{

}

CodiRegister_S::~CodiRegister_S()
{
}

// OPERATOR OVERLOADING


CodiRegister_S & CodiRegister_S::operator =(const CodiRegister_S & ss)
{
	if (this != &ss)
	{
	    this->station_tally = ss.station_tally;
		this->contest_class_code = ss.contest_class_code;
		this->contest_code = ss.contest_code;
		setCustomCode(ss.customCode);
	}

	return *this;
}


// ACCESS


unsigned long CodiRegister_S::getChecksum()
{
	return (unsigned long) (this->station_tally.getCodiChecksum() != NULL ? this->station_tally.getCodiChecksum ().get() : 0);
}


void CodiRegister_S::InsertRegisterL(CodiRegister_L registerL)
{
	this->asoc_lists.push_back (registerL);
}

unsigned long CodiRegister_S::getNumBlankVotes() const
{
	return (unsigned long)((station_tally.getEmptyVotes().get ()));
}

unsigned long CodiRegister_S::getNumRegisteredVotes() const
{
	return (unsigned long )((station_tally.getProcessedVotes().get ()));
}

unsigned long CodiRegister_S::getNumValidVotes() const
{
	return (unsigned long )((station_tally.getSelectedVotes().get ()));
}

void CodiRegister_S::setChecksum(unsigned long chkm)
{
	this->station_tally.getCodiChecksum ().set (chkm);
}

std::vector<CodiRegister_L> CodiRegister_S::getAsocLists() const
{
	return asoc_lists;
}

void CodiRegister_S::setAsocLists(std::vector<CodiRegister_L> asocLists)
{
    asoc_lists = asocLists;
}
