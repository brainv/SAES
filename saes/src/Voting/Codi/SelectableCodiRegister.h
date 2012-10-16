/*
 * SelectableCodiRegister.h
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#ifndef SELECTABLECODIREGISTER_H_
#define SELECTABLECODIREGISTER_H_

#include <Voting/Election/election-schema.hxx>
#include <Voting/Vote/station-tally-schema.hxx>
#include "CodiRegisterBase.h"

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class SelectableCodiRegister : public CodiRegisterBase
{
public:

	SelectableCodiRegister (const SelectableCodiRegister& sr);

	SelectableCodiRegister (
			  const std::string & contestCode
			, const std::string & customCode
			, const std::string & contestClassCode
			, Election::Ballot_option& ballotOption
			, Smartmatic::SAES::Voting::Vote::Register* stRegister);

	virtual ~SelectableCodiRegister();

	std::string getBallotOptionCode() const;

	/**
	 * @brief method getter ballot option custom code
	 * @return ballot option custom code
	 * @author Yadickson Soto
	 * @date 24/02/2012
	 */
	std::string getBallotOptionCustomCode() const;
    int getTallyPosition() const;

    bool operator>(const SelectableCodiRegister & reg) const;
    bool operator<(const SelectableCodiRegister & reg) const;
    bool operator>=(const SelectableCodiRegister & reg) const;
    bool operator<=(const SelectableCodiRegister & reg) const;
    bool operator==(const SelectableCodiRegister & reg) const;

    SelectableCodiRegister& operator=(const SelectableCodiRegister& sr);

protected:

    std::string ballot_op_code;
    std::string ballotOptionCustomCode; ///< ballot option custom code
    int tally_position;
    Smartmatic::SAES::Voting::Vote::Register* st_register;

private:

};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* SELECTABLECODIREGISTER_H_ */
