/*
 * CodiRegisterL.h
 *
 *  Created on: Feb 16, 2012
 *      Author: Marcel Cordoví
 */

#ifndef CODIREGISTERL_H_
#define CODIREGISTERL_H_

#include "SelectableCodiRegister.h"
#include "CodiRegisterC.h"
#include "Log/ISMTTLog.h"

namespace Smartmatic
{
namespace SAES
{
namespace Voting
{
namespace Codi
{

class CodiRegister_L : public  SelectableCodiRegister
{
public:

	CodiRegister_L (
			  const std::string & contestCode
			, const std::string & contestClassCode
			, const std::string & customCode
			, Election::Ballot_option& ballotOption
			, Smartmatic::SAES::Voting::Vote::Register* stRegister);

	virtual ~CodiRegister_L();

	unsigned long getChecksum ();

	void InsertPrincipal (CodiRegister_C principalReg);
	void InsertStandIn (CodiRegister_C standInReg);

	int get_category_1_count ();
	int get_category_2_count ();
	int get_category_3_count ();
	int get_category_4_count ();

	/**
	 * @brief method getter electoral number
	 * @return electoral number count
	 * @date 14/03/2012
	 * @author Yadickson Soto
	 */
	int getElectoralNumber();

	std::vector<unsigned long> getPrincipalCheckVector ();
	std::vector<unsigned long> getStandInCheckVector ();

	void CalculateChecksum ();

	std::vector<CodiRegister_C> & getPrincipal();
	std::vector<CodiRegister_C> & getStandIn();

private:

	std::vector<CodiRegister_C> asoc_principal;
    std::vector<CodiRegister_C> asoc_standin;

    static Smartmatic::Log::ISMTTLog* logger;

	void setChecksum (unsigned long chkm);

	void PrintVector (const std::vector<unsigned long> seq);

};

} /* namespace Vote */
} /* namespace Voting */
} /* namespace SAES */
} /* namespace Smartmatic */
#endif /* CODIREGISTERL_H_ */
