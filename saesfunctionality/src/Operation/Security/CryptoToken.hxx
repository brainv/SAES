/*
 * CryptoToken.hxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#ifndef CRYPTOTOKEN_HXX_
#define CRYPTOTOKEN_HXX_

#include <Security/CryptoData.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Operation
		{
			namespace Security
			{
				class CryptoToken : public Smartmatic::SAES::Security::CryptoData
				{
				public:
					CryptoToken();
					virtual ~CryptoToken();
				};
			}
		}
	}
}

#endif /* CRYPTOTOKEN_HXX_ */
