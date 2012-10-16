/*
 * VoteEncdoer.h
 *
 *  Created on: Jun 17, 2011
 *      Author: root
 */

#ifndef VOTEENCDOER_H_
#define VOTEENCDOER_H_


#include <gmp.h>
#include <vector>
#include <System/SafeBuffer.h>

namespace Smartmatic
{

namespace SAES
{

namespace Voting
{

namespace Vote
{

class VoteEncoder
{
public:

	VoteEncoder();

	virtual ~VoteEncoder();


	/**
	 * @brief Recovers a combination of selections from a vote code and returns
	 *        a sequence containing the number (i.e. tally position) of each
	 *        option selected.
	 *
	 * @param voteCode a code previously calculated with this class.
	 *
	 * @returns a sequence containing a number (i.e. tally position) for each
	 *          option selected.
	 */
	std::vector<int> Decode (const Smartmatic::System::SafeBuffer& voteCode);

	/**
	 * @brief Encodes a combination of selections.
	 *
	 * @param selectedOptions a sequence containing a number (i.e. tally position) for each
	 *                        option selected.
	 *
	 * @returns a buffer containing the code for the combination of selections.
	 */
	Smartmatic::System::SafeBuffer Encode (std::vector<int> selectedOptions);


private:

	// Coding


	void getCombinationCode (mpz_t N, std::vector<int> indexes_string);
	std::vector<int> recoverCombination (int k, mpz_t combIdx);

};

}

}

}

}

#endif /* VOTEENCDOER_H_ */
