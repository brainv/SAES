/*
 * LogCryptoGlobal.hxx
 *
 *  Created on: 27/07/2011
 *      Author: soto
 */

#ifndef LOGCRYPTOGLOBAL_HXX_
#define LOGCRYPTOGLOBAL_HXX_

#include <Log/ICryptoLayoutTransformer.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Log
		{
			class LogCryptoGlobal : public Smartmatic::Log::ICryptoLayoutTransformer
			{
				public:

					LogCryptoGlobal ();

					std::string encode(std::string & line);

					std::string decode(std::string & line);
			};
		}
	}
}

#endif /* LOGCRYPTOGLOBAL_HXX_ */
