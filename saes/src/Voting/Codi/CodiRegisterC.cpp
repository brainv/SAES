/*
 * CodiRegisterC.cpp
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#include "CodiRegisterC.h"

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

CodiRegister_C::CodiRegister_C (
		  const std::string & contestCode
		, const std::string & customCode
		, const std::string & contestClassCode
		, Election::Ballot_option& ballotOption
		, Smartmatic::SAES::Voting::Vote::Register* stRegister)
: SelectableCodiRegister (contestCode, customCode, contestClassCode, ballotOption, stRegister)
{
}

CodiRegister_C::~CodiRegister_C()
{
	// TODO Auto-generated destructor stub
}

unsigned long CodiRegister_C::getVoteCount()
{
	return (unsigned long) this->st_register->getTotal().get ();
}

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
