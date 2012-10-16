/*
 * LogCryptoBase64.hxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#ifndef LOGCRYPTOBASE64_HXX_
#define LOGCRYPTOBASE64_HXX_

#include <Log/ICryptoLayoutTransformer.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			class LogCryptoBase64 : public Smartmatic::Log::ICryptoLayoutTransformer
			{
				public:

					LogCryptoBase64 ();

					std::string encode(std::string & line);

					std::string decode(std::string & line);
			};
		}
	}
}

#endif /* LOGCRYPTOBASE64_HXX_ */
