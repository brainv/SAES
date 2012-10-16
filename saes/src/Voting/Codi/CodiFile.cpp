/**
 * @file CodiFile.cpp
 * @brief Body codi file persistence
 * @date 16/02/2012
 * @author Yadickson Soto
 */

#include <algorithm>
#include <Log/SMTTLogManager.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include "CodiFormatUtillity.h"
#include "CodiFile.h"

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
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::Log;

ISMTTLog* CodiFile::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.CodiFile", GETTEXT_PACKAGE);

CodiFile::CodiFile(const std::string & file)
{
	this->file = file;
}

CodiFile::~CodiFile()
{

}

void CodiFile::insert_S_reg(const CodiRegister_S& regS)
{
	regs_S.push_back (regS);
}

void CodiFile::insert_L_reg(const CodiRegister_L& regL)
{
	regs_L.push_back (regL);
}

void CodiFile::insert_C_reg(const CodiRegister_C& regC)
{
	regs_C.push_back (regC);

}

void CodiFile::CalculateChecksums()
{
	std::vector<CodiRegister_S>::iterator S_it;
	std::vector<CodiRegister_L>::iterator L_it;

	unsigned long total_registered_votes = 0;
	unsigned long total_valid_votes = 0;
	unsigned long total_blank_votes = 0;

	for ( S_it = regs_S.begin (); S_it != regs_S.end (); S_it++ )
	{
		total_registered_votes += S_it->getNumRegisteredVotes();
		total_blank_votes += S_it->getNumBlankVotes();
		total_valid_votes += S_it->getNumValidVotes();
	}

	sort (regs_L.begin (), regs_L.end ());

	for ( S_it = regs_S.begin (); S_it != regs_S.end (); S_it++ )
	{
		std::vector<unsigned long> chsm_input;

		chsm_input.push_back ( total_valid_votes );
		chsm_input.push_back ( total_registered_votes );
		chsm_input.push_back ( total_blank_votes );

		for (std::vector<CodiRegister_L>::iterator L_it = regs_L.begin ()
				; L_it != regs_L.end ()
				; L_it++)
		{
			chsm_input.push_back (L_it->get_category_1_count());
			chsm_input.push_back (L_it->get_category_2_count());
			chsm_input.push_back (L_it->get_category_4_count());
			chsm_input.push_back (L_it->get_category_3_count());

			L_it->CalculateChecksum ();
		}

		for (std::vector<CodiRegister_L>::iterator L_it = regs_L.begin ()
				; L_it != regs_L.end ()
				; L_it++)
		{
			std::vector<unsigned long> principal_votes = L_it->getPrincipalCheckVector();

			chsm_input.insert (
					  chsm_input.end ()
					, principal_votes.begin ()
					, principal_votes.end ());
		}

		for (std::vector<CodiRegister_L>::iterator L_it = regs_L.begin ()
				; L_it != regs_L.end ()
				; L_it++)
		{
			std::vector<unsigned long> standin_votes = L_it->getStandInCheckVector();

			chsm_input.insert (
					  chsm_input.end ()
					, standin_votes.begin ()
					, standin_votes.end ());
		}

		S_it->setChecksum (CodiFormatUtility::CodiCheckSum (chsm_input));
	}
}

std::string CodiFile::getFile() const
{
	return file;
}

std::vector<CodiRegister_S> & CodiFile::getRegsS()
{
	return regs_S;
}

std::vector<CodiRegister_L> & CodiFile::getRegsL()
{
	return regs_L;
}

std::vector<CodiRegister_C> & CodiFile::getRegsC()
{
	return regs_C;
}
