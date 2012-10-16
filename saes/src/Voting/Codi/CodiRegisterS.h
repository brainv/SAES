/*
 * CodiRegisterS.h
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#ifndef CODIREGISTERS_H_
#define CODIREGISTERS_H_

#include <vector>
#include <string>
#include <Voting/Vote/station-tally-schema.hxx>
#include "CodiRegisterBase.h"
#include "CodiRegisterL.h"

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class CodiRegister_S : public CodiRegisterBase
{
public:

	// life cycle

	CodiRegister_S (
			  const std::string & contestCode
			, const std::string & contestClassCode
			, const std::string & customCode
			, Smartmatic::SAES::Voting::Vote::StationTally & stationTally);

	CodiRegister_S (const CodiRegister_S & ss);

	virtual ~CodiRegister_S();

	// operator overloading

	CodiRegister_S& operator=(const CodiRegister_S & ss);

    // access

    unsigned long getChecksum ();
    void setChecksum (unsigned long chkm);

    unsigned long getNumBlankVotes() const;
    unsigned long getNumRegisteredVotes() const;
    unsigned long getNumValidVotes() const;

    // interface

    void InsertRegisterL (CodiRegister_L registerL);

    std::vector<CodiRegister_L> getAsocLists() const;
    void setAsocLists(std::vector<CodiRegister_L> asocLists);


private:

    Smartmatic::SAES::Voting::Vote::StationTally & station_tally;
    std::vector<CodiRegister_L> asoc_lists;
};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIREGISTERS_H_ */
