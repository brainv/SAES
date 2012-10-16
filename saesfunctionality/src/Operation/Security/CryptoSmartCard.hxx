/*
 * CryptoSmartCard.hxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#ifndef CRYPTOSMARTCARD_HXX_
#define CRYPTOSMARTCARD_HXX_

#include "CryptoCard.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Security
			{
				class CryptoSmartCard : public CryptoCard
				{
				public:
					CryptoSmartCard();
					virtual ~CryptoSmartCard();
					virtual void getKeyPin();
					virtual void getKeys();
				};
			}
		}
	}
}

#endif /* CRYPTOSMARTCARD_HXX_ */
