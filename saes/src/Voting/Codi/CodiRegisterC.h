/*
 * CodiRegisterC.h
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#ifndef CODIREGISTERC_H_
#define CODIREGISTERC_H_

#include "SelectableCodiRegister.h"

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class CodiRegister_C : public SelectableCodiRegister
{
public:

	CodiRegister_C (
			  const std::string & contestCode
			, const std::string & customCode
			, const std::string & contestClassCode
			, Election::Ballot_option& ballotOption
			, Smartmatic::SAES::Voting::Vote::Register* stRegister);

	virtual ~CodiRegister_C();

	unsigned long getVoteCount ();
};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIREGISTERC_H_ */
