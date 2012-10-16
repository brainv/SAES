/*
 * VoteRecovery.h
 *
 *  Created on: Jun 6, 2011
 *      Author: mcordovi
 */

#ifndef VOTERECOVERY_H_
#define VOTERECOVERY_H_


#include <vector>
#include <map>
#include <list>
#include <Voting/Election/election-schema.hxx>
#include <Voting/Vote/vote-schema.hxx>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{

namespace SAES
{

namespace Voting
{
	class ElectoralConfiguration;

namespace Vote
{

class VoteRecovery
{
public:

	/**
	 * @brief Constructor
	 */
	VoteRecovery(Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration);
	/**
	 * @brief Destructor
	 */
	virtual ~VoteRecovery();


	/**
	 * @brief Computes a compact representation of the vote object.
	 *
	 * @author mcordovi
	 * @date   Jun 6, 2011
	 *
	 * @param vote: logical vote object.
	 *
	 * @returns a plain, compact representation of the logical vote.
	 */
	std::map<std::string, std::string> LogicalToRecovery (const Vote& vote);

	/**
	 * @brief Recovers a logical vote object out of the compact recovery
	 *        representation.
	 *
	 * @author mcordovi
	 * @date   Jun 6, 2011
	 *
	 * @param recoverySelections: List of base64 strings representing the
	 *                            selections per contest.
	 *
	 * @returns a plain, compact representation of the logical vote.
	 */
	void RecoveryToLogical (std::map<std::string, std::string> & recoverySelections, Smartmatic::SAES::Voting::Vote::Vote& outVote);

	bool IsCodeValid (std::string conetstCode, std::string recoveryCode);

	bool IsCodeValid (std::map<std::string, std::string> & recoverySelections);

private:

	Smartmatic::SAES::Voting::ElectoralConfiguration * electoralConfiguration; ///< electoral configuration

	// validation check

	bool IsBitmaskCodeValid (std::string conetstCode, std::string recoveryCode);
	bool IsCombCodeValid (std::string conetstCode, std::string recoveryCode);


	// encoding

	std::map<std::string, std::string> BitmaskEncode (const Vote& vote);
	std::map<std::string, std::string> CombEncode (const Vote& vote);

	void BitmaskDecode (std::map<std::string, std::string>& selectionCodes, Vote& outVote);
	void CombDecode (std::map<std::string, std::string>& selectionCodes, Vote& outVote);


	// auxiliars

	unsigned char PairToIndex (const std::string& contestCode, const std::string& partyCode);
	void IndexToPair (int idx, std::string& contestCode, std::string& partyCode);

	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
};

}

}

}

}

#endif /* VOTERECOVERY_H_ */
