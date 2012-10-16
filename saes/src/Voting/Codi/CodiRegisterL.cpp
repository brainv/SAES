/**
 * @file CodiRegisterL.cpp
 * @brief Body class codi register L
 * @date 16/02/2012
 * @author Marcel Cordoví
 */

#include <algorithm>
#include <Log/SMTTLogManager.h>
#include "CodiFormatUtillity.h"
#include "CodiRegisterL.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::Log;


ISMTTLog* CodiRegister_L::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.CodiRegister_L", GETTEXT_PACKAGE);

CodiRegister_L::CodiRegister_L (
		  const std::string & contestCode
		, const std::string & customCode
		, const std::string & contestClassCode
		, Election::Ballot_option& ballotOption
		, Smartmatic::SAES::Voting::Vote::Register* stRegister)
: SelectableCodiRegister (contestCode, customCode, contestClassCode, ballotOption, stRegister)
{
}

CodiRegister_L::~CodiRegister_L ()
{
	// TODO Auto-generated destructor stub
}


// UTILITY

void CodiRegister_L::PrintVector (const std::vector<unsigned long> seq)
{
	std::stringstream ss;

	for (std::vector<unsigned long>::const_iterator it = seq.begin ()
			; it != seq.end ()
			; it++)
	{
		ss << (*it) << ", ";
	}

	logger->Debug (ss.str ());
}

// ACCESS

unsigned long CodiRegister_L::getChecksum()
{
	return (unsigned long) (this->st_register->getCheckSum() != NULL ? this->st_register->getCheckSum().get() : 0);
}

void CodiRegister_L::InsertPrincipal(
		CodiRegister_C principalReg)
{
    asoc_principal.push_back(principalReg);
}

void CodiRegister_L::InsertStandIn(
		CodiRegister_C standInReg)
{
    asoc_standin.push_back(standInReg);
}

std::vector<CodiRegister_C> & CodiRegister_L::getPrincipal()
{
    return asoc_principal;
}

std::vector<CodiRegister_C> & CodiRegister_L::getStandIn()
{
    return asoc_standin;
}

int CodiRegister_L::get_category_1_count()
{
	return (this->st_register->getCountList() != NULL ? this->st_register->getCountList().get () : 0);
}

int CodiRegister_L::get_category_2_count()
{
	return (this->st_register->getCountListP() != NULL ? this->st_register->getCountListP().get () : 0);
}

int CodiRegister_L::get_category_3_count ()
{
	return (this->st_register->getCountListPS() != NULL ? this->st_register->getCountListPS().get () : 0);
}

int CodiRegister_L::get_category_4_count()
{
	return (this->st_register->getCountListS() != NULL ? this->st_register->getCountListS().get () : 0);
}


// INTERFACE

std::vector<unsigned long> CodiRegister_L::getPrincipalCheckVector ()
{
	std::vector<unsigned long> chsm;

	sort (asoc_principal.begin (), asoc_principal.end ());

	for ( std::vector<CodiRegister_C>::iterator it = asoc_principal.begin ()
			; it != asoc_principal.end ()
			; it++)
	{
		chsm.push_back(it->getVoteCount());
	}

	return chsm;
}

std::vector<unsigned long> CodiRegister_L::getStandInCheckVector ()
{
	std::vector<unsigned long> chsm;

	sort (asoc_standin.begin (), asoc_standin.end ());

	for ( std::vector<CodiRegister_C>::iterator it = asoc_standin.begin ()
			; it != asoc_standin.end ()
			; it++)
	{
		chsm.push_back(it->getVoteCount());
	}

	return chsm;
}

void CodiRegister_L::setChecksum(unsigned long  chkm)
{
	this->st_register->getCheckSum().set (chkm);
}

void CodiRegister_L::CalculateChecksum()
{
	std::vector<unsigned long> chsm_input;

	chsm_input.push_back(get_category_1_count());
	chsm_input.push_back(get_category_2_count());
	chsm_input.push_back(get_category_4_count());
	chsm_input.push_back(get_category_3_count());

	sort (asoc_principal.begin (), asoc_principal.end ());

	for (std::vector<CodiRegister_C>::iterator it = asoc_principal.begin ()
			; it != asoc_principal.end ()
			;it++)
	{
		chsm_input.push_back(it->getVoteCount());
	}

	sort (asoc_standin.begin (), asoc_standin.end ());

	for (std::vector<CodiRegister_C>::iterator it = asoc_standin.begin ()
			; it != asoc_standin.end ()
			;it++)
	{
		chsm_input.push_back(it->getVoteCount());
	}

	setChecksum  (CodiFormatUtility::CodiCheckSum (chsm_input));
}

int CodiRegister_L::getElectoralNumber()
{
	return (get_category_1_count() + get_category_2_count() + get_category_3_count() + get_category_4_count());
}
