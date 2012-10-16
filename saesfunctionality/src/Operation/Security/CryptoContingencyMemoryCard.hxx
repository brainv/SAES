/*
 * CryptoContingencyCard.hxx
 *
 *  Created on: 16/10/2011
 *      Author: soto
 */

#ifndef CRYPTOCONTINGENCYMEMORYCARD_HXX_
#define CRYPTOCONTINGENCYMEMORYCARD_HXX_

#include "CryptoMemoryCard.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Security
			{
				class CryptoContingencyMemoryCard: public CryptoMemoryCard
				{
				public:
					CryptoContingencyMemoryCard();
					virtual ~CryptoContingencyMemoryCard();
					virtual void getKeys();
				};
			}
		}
	}
}

#endif /* CRYPTOCONTINGENCYMEMORYCARD_HXX_ */
