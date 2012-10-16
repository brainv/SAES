/*
 * CryptoCard.hxx
 *
 *  Created on: 26/08/2011
 *      Author: soto
 */

#ifndef CRYPTOCARD_HXX_
#define CRYPTOCARD_HXX_

#include <Security/CryptoData.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Security
			{
				class CryptoCard : public Smartmatic::SAES::Security::CryptoData
				{
				public:

					CryptoCard();
					virtual ~CryptoCard();

					virtual void setKeyPin(std::string & strPin);
					virtual void getKeyPin();
					virtual void getKeys();
				};
			}
		}
	}
}

#endif /* CRYPTOCARD_HXX_ */
