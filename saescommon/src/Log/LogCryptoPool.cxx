/*
 * LogTransformation.cxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#include "LogCryptoPool.hxx"
#include "LogCryptoBase64.hxx"
#include "LogCryptoGlobal.hxx"
#include <Log/ICryptoLayoutTransformer.hxx>

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::SAES::Common::Configuration;

LogCryptoPool * LogCryptoPool::instance = NULL;

LogCryptoPool::LogCryptoPool()
{
	putLogCrypto(new LogCryptoBase64());
	putLogCrypto(new LogCryptoGlobal());
}

LogCryptoPool::~LogCryptoPool()
{

}

void LogCryptoPool::putLogCrypto( ICryptoLayoutTransformer * iCrypto )
{
	if (iCrypto)
	{
		cryptoMap[iCrypto->getCode()] = iCrypto;
	}
}

ICryptoLayoutTransformer * LogCryptoPool::getLogCrypto( CryptoType type )
{
	ICryptoLayoutTransformer * interface = NULL;

	if (cryptoMap.find(type) != cryptoMap.end())
	{
		interface = cryptoMap[type];
	}

	return interface;
}

std::map < std::string, ICryptoLayoutTransformer * > & LogCryptoPool::getCryptoMap()
{
	return cryptoMap;
}

LogCryptoPool * LogCryptoPool::getInstance()
{
	if (instance == NULL)
	{
		instance = new LogCryptoPool();
	}

	return instance;
}
