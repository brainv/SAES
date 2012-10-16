/*
 * LogTransformation.hxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#ifndef LOGTRANSFORMATION_HXX_
#define LOGTRANSFORMATION_HXX_

#include <map>
#include <Configuration/SaesCommonConfiguration-schema.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ICryptoLayoutTransformer;
	}

	namespace SAES
	{
		namespace Log
		{
			/**
			 * @class LogTransformation
			 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
			 * @date 25-07-2011
			 */
			class LogCryptoPool
			{
				private:
					/**
					 * @brief Class constructor
					 */
					LogCryptoPool();

					std::map < std::string, Smartmatic::Log::ICryptoLayoutTransformer * > cryptoMap;
					static LogCryptoPool * instance;

				public:
					/**
					 * @brief Class destroy
					 */
					~LogCryptoPool();

					void putLogCrypto( Smartmatic::Log::ICryptoLayoutTransformer * iCrypto );
					Smartmatic::Log::ICryptoLayoutTransformer * getLogCrypto( Smartmatic::SAES::Common::Configuration::CryptoType type );
					std::map < std::string, Smartmatic::Log::ICryptoLayoutTransformer * > & getCryptoMap();

					static LogCryptoPool * getInstance();
			};
		}
	}
}

#endif /* LOGTRANSFORMATION_HXX_ */
