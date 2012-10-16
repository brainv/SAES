/*
 * SelectableCodiRegister.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#include "SelectableCodiRegister.h"

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::SAES::Voting::Vote;

// LIFE CYCLE

SelectableCodiRegister::SelectableCodiRegister(
		  const std::string & contestCode
		, const std::string & customCode
		, const std::string & contestClassCode
		, Election::Ballot_option& ballotOption
		, Register* stRegister)
: CodiRegisterBase (contestCode, customCode, contestClassCode)
{
	this->st_register = stRegister;
	this->ballot_op_code = ballotOption.getCode ();
	this->ballotOptionCustomCode = ballotOption.getCustom_code();
	this->tally_position = ballotOption.getTally_position();
}

SelectableCodiRegister::SelectableCodiRegister(const SelectableCodiRegister & sr)
: CodiRegisterBase (sr.contest_code, sr.customCode, sr.contest_code)
, st_register   ( sr.st_register )
{
	this->tally_position = sr.tally_position;
	this->ballot_op_code = sr.ballot_op_code;
	this->ballotOptionCustomCode = sr.ballotOptionCustomCode;
}

SelectableCodiRegister::~SelectableCodiRegister()
{
}


// ACCESS


std::string SelectableCodiRegister::getBallotOptionCode() const
{
	return ballot_op_code;
}

std::string SelectableCodiRegister::getBallotOptionCustomCode() const
{
	return ballotOptionCustomCode;
}

// OPERATOR OVERLOADING

SelectableCodiRegister& SelectableCodiRegister::operator=(const SelectableCodiRegister& sr)
{
	if (this != &sr)
	{
	    this->tally_position = sr.tally_position;
		this->ballot_op_code = sr.ballot_op_code;
		this->ballotOptionCustomCode = sr.ballotOptionCustomCode;
		this->st_register = sr.st_register;
		this->contest_class_code = sr.contest_class_code;
		this->contest_code = sr.contest_code;
		this->customCode = sr.customCode;
	}

	return *this;
}

bool SelectableCodiRegister::operator >(const SelectableCodiRegister & reg) const
{
	return this->tally_position > reg.tally_position;
}

bool SelectableCodiRegister::operator <(const SelectableCodiRegister & reg) const
{
	return this->tally_position < reg.tally_position;
}

bool SelectableCodiRegister::operator ==(const SelectableCodiRegister & reg) const
{
	return this->tally_position == reg.tally_position;
}

bool SelectableCodiRegister::operator >=(const SelectableCodiRegister & reg) const
{
	return (*this > reg) || (*this == reg);
}

bool SelectableCodiRegister::operator <=(const SelectableCodiRegister & reg) const
{
	return (*this < reg) || (*this == reg);
}

int SelectableCodiRegister::getTallyPosition() const
{
    return tally_position;
}








