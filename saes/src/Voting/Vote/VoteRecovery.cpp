/*
 * VoteRecovery.cpp
 *
 *  Created on: Jun 6, 2011
 *      Author: mcordovi
 */

#include <iterator>
#include <glib.h>
#include <System/SafeBuffer.h>
#include <System/Encoding/Base64Encoder.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <glibmm.h>
#include "VoteEncoder.h"
#include "VoteRecovery.h"
#include <Log/SMTTLogManager.h>
#include <Voting/ElectoralConfiguration.hxx>

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

using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::Log;

#define NULL_VOTE "0"
#define INDEX_OF(s,x) std::distance (( s ).begin (), std::find (( s ).begin (), ( s ).end (), ( x )))

ISMTTLog* VoteRecovery::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Vote.VoteRecovery", GETTEXT_PACKAGE);

//============================================================================//
//============================= Life Cycle ===================================//
//============================================================================//

VoteRecovery::VoteRecovery(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration)
{
	this->electoralConfiguration = electoralConfiguration;
}

VoteRecovery::~VoteRecovery()
{

}

//============================================================================//
//============================= Interface ====================================//
//============================================================================//

std::map<std::string, std::string> VoteRecovery::LogicalToRecovery (const Vote& vote)
{
	std::map<std::string, std::string> codes;

	switch ( SAESConfigurationManager::Current()->getEncodingMode () )
	{
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_BITWISE:
		codes = BitmaskEncode ( vote );
		break;
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_OPTIMIZED:
		codes = CombEncode ( vote );
		break;
	default:
		break;
	}

	return codes;
}

void  VoteRecovery::RecoveryToLogical (
		std::map<std::string, std::string>& recoverySelections, Smartmatic::SAES::Voting::Vote::Vote& outVote)
{
	switch ( SAESConfigurationManager::Current()->getEncodingMode () )
	{
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_BITWISE:
		BitmaskDecode ( recoverySelections, outVote );
		break;
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_OPTIMIZED:
		CombDecode ( recoverySelections, outVote );
		break;
	default:
		break;
	}
}

bool VoteRecovery::IsCodeValid(std::string conetstCode,
		std::string recoveryCode)
{
	switch ( SAESConfigurationManager::Current()->getEncodingMode () )
	{
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_BITWISE:
		return IsBitmaskCodeValid ( conetstCode, recoveryCode );
		break;
	case Smartmatic::SAES::Configuration::VoteEncodeModeType::CONFIGURATION_OPTIMIZED:
		return IsCombCodeValid ( conetstCode, recoveryCode );
		break;
	default:
		break;
	}

	return false;
}

bool VoteRecovery::IsCodeValid(
		std::map<std::string, std::string> & recoverySelections)
{
	for (std::map<std::string, std::string>::const_iterator it = recoverySelections.begin()
			; it != recoverySelections.end()
			; it++)
	{
		if (it->second == NULL_VOTE)
			continue;

		if (!IsCodeValid(it->first, it->second))
			return false;
	}

	return true;
}



//============================================================================//
//============================== Validation ==================================//
//============================================================================//

bool VoteRecovery::IsBitmaskCodeValid (std::string conetstCode,
		std::string recoveryCode)
{
	if (recoveryCode == NULL_VOTE)
		return true;

	if (!Smartmatic::System::Encoding::Base64Encoder::TestBase64String(recoveryCode))
	{
		logger->Debug("Error test base 64 code " + recoveryCode);
		return false;
	}

	int rec_size = 0;

    bool validate = false;
	Smartmatic::System::SafeBuffer buffer;
	Base64Encoder::ConvertFromBase64(recoveryCode, buffer);

	if (buffer.GetSize() > 0)
	{
	    validate = true;
        rec_size = (int) (buffer.GetSize()) - 1;

        int pair_index = buffer.GetData()[0] & 0xff;
        std::string contest_code;
        std::string party_code;

        IndexToPair(pair_index, contest_code, party_code);

        if (conetstCode != contest_code)
        {
        	logger->Debug("Error index to pair " + conetstCode + " " + contest_code + " " + party_code);
            validate = false;
        }
        else
        {
            int selections_size = electoralConfiguration->getCountBallotOptionByContestParty(contest_code, party_code);
                    //Nominations_x_Party_x_Contest[contest_code][party_code].size();
            int selections_csts_size = electoralConfiguration->getCountBallotOptionByContestParty(conetstCode, party_code);
                    //Nominations_x_Party_x_Contest[conetstCode][party_code].size();

            int rec_capacity = selections_size / 8;
            rec_capacity += (selections_size % 8) == 0 ? 0 : 1;

            if (rec_capacity != rec_size || selections_size != selections_csts_size)
            {
            	std::stringstream ss;
            	ss << "Error " << rec_capacity << " " << rec_size << " - " << selections_size << " " << selections_csts_size;
            	logger->Debug(ss.str());
                validate = false;
            }
        }
	}

	return validate;
}

bool VoteRecovery::IsCombCodeValid (std::string conetstCode,
		std::string recoveryCode)
{
	if (recoveryCode == "0")
		return true;

	if (!Smartmatic::System::Encoding::Base64Encoder::TestBase64String(recoveryCode))
		return false;

	return true;
}


//============================================================================//
//============================== Encoding ====================================//
//============================================================================//

void VoteRecovery::BitmaskDecode (
		std::map<std::string, std::string> & recoverySelections,  Vote& outVote)
{
	Vote::SSequence vote_selections;

	std::list <std::string > & contestOrder = electoralConfiguration->getContestCodeList();
	std::list <std::string>::iterator itorder;

	for (itorder = contestOrder.begin();
	     itorder != contestOrder.end();
	     itorder++)
	{
        for (std::map<std::string, std::string>::const_iterator it = recoverySelections.begin()
                ; it != recoverySelections.end()
                ; it++)
        {

            if (it->first != *itorder) continue;

        	if (!IsCodeValid(it->first, it->second))
            {
        		logger->Debug("not valid selection");
            	continue;
            }

            Selection sln;
            Selection::BSequence selected_ops;
            std::string contestCode, partyCode;

            if (it->second != NULL_VOTE)
            {
                std::vector<std::string> elgbl_ops;

                Smartmatic::System::SafeBuffer buffer;
                Base64Encoder::ConvertFromBase64(it->second, buffer);

                if (buffer.GetSize() > 0)
                {
					unsigned int rec_size = buffer.GetSize();
					const unsigned char * rec_contest = buffer.GetData();

					IndexToPair(buffer.GetData()[0], contestCode, partyCode);
					rec_contest++;
					rec_size--;

					std::list <std::string> & list (electoralConfiguration->getAllCodeBallotOptionByContestParty(contestCode, partyCode));
							//Nominations_x_Party_x_Contest[contestCode][partyCode];
					elgbl_ops.insert(elgbl_ops.end(), list.begin(), list.end());

					for (unsigned int i = 0; i < rec_size; i++)
					{
						unsigned char chunk = rec_contest[i];

						for (int j = 0; j < 8; j++)
						{
							unsigned int eops_idx = i * 8 + j;

							if (eops_idx >= elgbl_ops.size())
								break;

							if (chunk & (1 << j))
								selected_ops.push_back(elgbl_ops[eops_idx]);
						}
					}
                }
            }
            else
            {
                contestCode = it->first;
            }

            sln.setContest(contestCode);
            sln.setBallotOptions(selected_ops);
            vote_selections.push_back(sln);
        }
	}

	outVote.setSelections(vote_selections);

}

std::map<std::string, std::string> VoteRecovery::BitmaskEncode (const Vote& vote)
{
	std::map<std::string, std::string> vrecovery_rep;

	for (Vote::SConstIterator vcontest_it = vote.getSelections().begin()
			; vcontest_it != vote.getSelections().end()
			; vcontest_it++)
	{
		std::string contest_code = vcontest_it->getContest();

		if (vcontest_it->getBallotOptions().empty())
		{
			vrecovery_rep[contest_code] = NULL_VOTE; // null vote is represented as the "0" string
		}
		else
		{
			std::string option_code = vcontest_it->getBallotOptions()[0]; // We can do this because just one party per contest is allowed
			std::string parent_code = electoralConfiguration->getPartyCodeByBallotOptionCode(option_code);
			std::list <std::string> & list (electoralConfiguration->getAllCodeBallotOptionByContestParty(contest_code, parent_code));
					//Nominations_x_Party_x_Contest[contest_code][parent_code];
			std::vector<std::string> options_by_party (list.begin(), list.end());

			int bitset_size = options_by_party.size() / 8 + 1;
			bitset_size += options_by_party.size() % 8 ? 1 : 0;

			unsigned char recovery_selections[bitset_size];
			memset(recovery_selections, 0, sizeof recovery_selections);

			// the contest-party index
			int pairToIndexValue = PairToIndex(contest_code, parent_code);

			recovery_selections[0] = pairToIndexValue;

			for (Selection::BConstIterator vboption_it =
					vcontest_it->getBallotOptions().begin(); vboption_it
					!= vcontest_it->getBallotOptions().end(); vboption_it++)
			{
				std::string sel_opt_code = *vboption_it;
				int index = INDEX_OF (options_by_party, sel_opt_code); // TODO check for not founded strings

				recovery_selections[index / 8 + 1] |= 1 << (index % 8);
			}

			SafeBuffer contest_buf(recovery_selections, bitset_size);
			vrecovery_rep[contest_code] = contest_buf.GetBase64Data();
		}
	}

	return vrecovery_rep;
}

std::map<std::string, std::string> VoteRecovery::CombEncode (const Vote& vote)
{
	VoteEncoder encoder;
	std::map<std::string, std::string> vote_codes;

	for (Vote::SConstIterator vcontest_it = vote.getSelections().begin()
			; vcontest_it != vote.getSelections().end()
			; vcontest_it++)
	{
		std::string contest_id = vcontest_it->getContest();

		if (vcontest_it->getBallotOptions().empty())
		{
			vote_codes [contest_id] = NULL_VOTE;
		}
		else
		{
			SafeBuffer per_contest_encoding;
			SafeBuffer code;

			std::vector<int> contest_selection;

			std::string option_id = vcontest_it->getBallotOptions () [0];
			std::string parent_id = electoralConfiguration->getPartyCodeByBallotOptionCode(option_id);

			std::list <std::string> & options_by_party (electoralConfiguration->getAllCodeBallotOptionByContestParty(contest_id, parent_id));
					//Nominations_x_Party_x_Contest [contest_id] [parent_id];

//			std::vector<std::string> options_by_party (options_by_party_list.begin (), options_by_party_list.end ());

			unsigned char ops_idx = PairToIndex (contest_id, parent_id);

			for (Selection::BConstIterator vboption_it = vcontest_it->getBallotOptions().begin()
					; vboption_it != vcontest_it->getBallotOptions().end()
					; vboption_it++)
			{
				std::string sel_opt_code = *vboption_it;
				int index = INDEX_OF (options_by_party, sel_opt_code); // TODO check for not founded strings
				contest_selection.push_back (index);
			}

			code = encoder.Encode (contest_selection);

			per_contest_encoding.AddData(&ops_idx, sizeof (ops_idx));
			per_contest_encoding.AddData ( code );

			vote_codes [contest_id] = per_contest_encoding.GetBase64Data();
		}
	}

	return vote_codes;
}

void VoteRecovery::CombDecode (
		std::map<std::string, std::string>& selectionCodes,  Vote& outVote)
{

	Vote::SSequence vote_selections;

	VoteEncoder encoder;

	for (std::map<std::string, std::string>::const_iterator it = selectionCodes.begin()
			; it != selectionCodes.end()
			; it++)
	{
		SafeBuffer per_contest_encoding;

		//std::list<std::string> elgbl_ops_list;
		std::vector<int> decoded_options;
		std::string contestCode, partyCode;

		Selection sln;
		Selection::BSequence selected_ops;

		if ( it->second != NULL_VOTE )
		{
			gsize rec_size = 0;
			unsigned char* rec_contest = (unsigned char*) g_base64_decode(
					(const gchar*) it->second.data(), &rec_size);

			IndexToPair(rec_contest[0], contestCode, partyCode);
			per_contest_encoding.AddData(rec_contest + 1, rec_size - 1);
			g_free (rec_contest);

			std::list <std::string> & elgbl_ops_list (electoralConfiguration->getAllCodeBallotOptionByContestParty(contestCode, partyCode));
			//elgbl_ops_list = Nominations_x_Party_x_Contest [contestCode] [partyCode];
			std::vector<std::string> elgbl_ops (elgbl_ops_list.begin (), elgbl_ops_list.end ());

			decoded_options = encoder.Decode(per_contest_encoding);

			for (unsigned int i = 0; i < decoded_options.size (); i++)
				selected_ops.push_back(elgbl_ops[decoded_options [i]]);
		}
		else
		{
			contestCode = it->first;
		}

		sln.setContest(contestCode);
		sln.setBallotOptions(selected_ops);
		vote_selections.push_back(sln);
	}

	outVote.setSelections(vote_selections);


}



//============================================================================//
//============================= Auxiliars ====================================//
//============================================================================//

unsigned char VoteRecovery::PairToIndex(const std::string& contestCode,
		const std::string& partyCode)
{
	int idx = 0;

	std::map <std::string, std::map < std::string, std::list <std::string> > > & Nominations_x_Party_x_Contest(electoralConfiguration->getAllCodeBallotOptionByContestParty());

	for (std::map<std::string, std::map<std::string, std::list<std::string> > >::const_iterator c_it = Nominations_x_Party_x_Contest.begin(); c_it
			!= Nominations_x_Party_x_Contest.end(); c_it++)
	{
		if (c_it->first == contestCode)
		{
			std::map<std::string, std::list<std::string> >::const_iterator f_it;

			if ((f_it = c_it->second.find(partyCode)) == c_it->second.end())
				return 0; // TODO party code not found. This would be a BUG
			else
			{
				if ((idx += std::distance(c_it->second.begin(), f_it)) <= 0xff)
				{
					// TODO index too large for a byte to hold it. Throw exception
				}

				return idx & 0xff;
			}
		}
		else
			idx += c_it->second.size();
	}

	return 0; // if the contest was found this point should never be reached. A not found contest is a BUG in this class or from a corrupted vote.
}

void VoteRecovery::IndexToPair(int idx, std::string& contestCode,
		std::string& partyCode)
{
	std::map <std::string, std::map < std::string, std::list <std::string> > > & Nominations_x_Party_x_Contest(electoralConfiguration->getAllCodeBallotOptionByContestParty());
	std::map<std::string, std::map<std::string, std::list<std::string> > >::const_iterator c_it = Nominations_x_Party_x_Contest.begin();

	while (idx >= (int)c_it->second.size())
	{
		idx -= (int)c_it->second.size();
		c_it++;
	}

	if (c_it != Nominations_x_Party_x_Contest.end())
		contestCode = c_it->first;

	std::map<std::string, std::list<std::string> >::const_iterator p_it = c_it->second.begin();
	std::advance(p_it, idx);
	partyCode = p_it->first;
}
