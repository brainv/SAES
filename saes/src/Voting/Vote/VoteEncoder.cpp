/*
 * VoteEncdoer.cpp
 *
 *  Created on: Jun 17, 2011
 *      Author: root
 */


#include "VoteEncoder.h"
#include <algorithm>
#include <glib.h>
#include <stack>


using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::System;



//============================================================================//
//============================= LifeCycle ====================================//
//============================================================================//


VoteEncoder::VoteEncoder()
{
	// TODO Auto-generated constructor stub

}

VoteEncoder::~VoteEncoder()
{
	// TODO Auto-generated destructor stub
}


//============================================================================//
//============================= Interface ====================================//
//============================================================================//


SafeBuffer VoteEncoder::Encode (
		std::vector<int> selectedOptions)
{
	SafeBuffer result;

	sort (selectedOptions.begin (), selectedOptions.end());
	reverse (selectedOptions.begin (), selectedOptions.end());

	mpz_t comb_code;
	mpz_init_set_ui (comb_code, 0);

	getCombinationCode (comb_code, selectedOptions);

	unsigned char* bignum_buf;
	size_t bignum_bytes;

	bignum_buf = (unsigned char*) mpz_export (
			  NULL            /* allocate */
			, &bignum_bytes
			, 1               /* order more signficant words first */
			, 1               /* words of 1 byte length */
			, 0               /* native endianness */
			, 0               /* produce full words */
			, comb_code
			);

	int k = selectedOptions.size ();
	unsigned char order = k & 0xff;

	result.AddData (&order, sizeof (order));
	result.AddData (bignum_buf, bignum_bytes);

	mpz_clear (comb_code);
	free (bignum_buf);

	return result;
}

std::vector<int> VoteEncoder::Decode (
		  const SafeBuffer& combCode)
{
	unsigned char* raw_buf = (unsigned char*) combCode.GetData ();
	size_t code_size = combCode.GetSize ();

	int order = raw_buf[0];

	mpz_t code;
	mpz_init_set_ui (code, 0);

	mpz_import (
			  code
			, code_size - 1
			, 1               /* order more signficant words first */
			, 1               /* words of 1 byte length */
			, 0               /* native endianness */
			, 0               /* produce full words */
			, (const void *) (raw_buf + 1)
			);

	std::vector<int> idx_seq = recoverCombination (order, code);

	mpz_clear (code);

	return idx_seq;
}


//============================================================================//
//============================= Auxiliar =====================================//
//============================================================================//

void VoteEncoder::getCombinationCode (mpz_t N, std::vector<int> indexes_string)
{
	unsigned long int k = (unsigned long int)indexes_string.size ();
	mpz_t n;
	mpz_t coef;

	mpz_init_set_ui (n, 0);
	mpz_init_set_ui (coef, 0);

	for (unsigned long int i = 0; i<k; i++)
	{
		mpz_set_ui (n, (unsigned long int)indexes_string [i]);
		mpz_bin_ui (coef, n, k-i);
		mpz_add (N, N, coef);
	}

	mpz_clear (n);
	mpz_clear (coef);
}

std::vector<int> VoteEncoder::recoverCombination (int k, mpz_t combIdx)
{
	std::vector<int> indexes_string;
	unsigned long int order = (unsigned long int)k;

	while ( (mpz_cmp_ui (combIdx, 0) > 0) && order > 0)
	{
		mpz_t idx;
		mpz_t coef;

		mpz_init_set_ui (idx, order - 1);
		mpz_init_set_ui (coef, 0);

		while ( mpz_cmp (coef, combIdx) <= 0 )
		{
			mpz_bin_ui (coef, idx, order);
			mpz_add_ui (idx, idx, 1);
		}

		mpz_sub_ui (idx, idx, 2);

		indexes_string.push_back((int) mpz_get_ui (idx));

		mpz_bin_ui (coef, idx, order);
		mpz_sub (combIdx, combIdx, coef);
		order--;

		mpz_clear (idx);
		mpz_clear (coef);
	}

	while (order > 0)
		indexes_string.push_back((int)(--order));

	return indexes_string;
}
