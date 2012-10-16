/*
 * CryptoMemoryCard.hxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#ifndef CRYPTOMEMORYCARD_HXX_
#define CRYPTOMEMORYCARD_HXX_

#include "CryptoCard.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Security
			{
				class CryptoMemoryCard : public CryptoCard
				{
				public:
					CryptoMemoryCard();
					virtual ~CryptoMemoryCard();

					virtual bool decrypto(Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & dataOut);
					virtual void getKeys();
				};
			}
		}
	}
}

#endif /* CRYPTOMEMORYCARD_HXX_ */
