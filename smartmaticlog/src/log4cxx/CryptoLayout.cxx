/**
 * @file CryptoLayout.cxx
 * @brief Body class CryptoLayout
 * @date 15/07/2011
 * @author Yadickson Soto yadickson.soto@smartmatic.com
 */

#include "CryptoLayout.hxx"
#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/helpers/loglog.h>
#include <log4cxx/helpers/thread.h>
#include <log4cxx/helpers/synchronized.h>
#include <iostream>

using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace log4cxx::spi;
using namespace log4cxx::pattern;

std::map <std::string, Smartmatic::Log::ICryptoLayoutTransformer * > CryptoLayout::iCryptoMap;

IMPLEMENT_LOG4CXX_OBJECT(CryptoLayout)
CryptoLayout::CryptoLayout()
	: PatternLayout()
{
	this->cryptoType = "GLOBAL";
}

CryptoLayout::~CryptoLayout()
{

}

bool CryptoLayout::ignoresThrowable()
{
	return true;
}

void CryptoLayout::setOption(const log4cxx::LogString& option, const log4cxx::LogString& value)
{
	if (StringHelper::equalsIgnoreCase(option, LOG4CXX_STR("CRYPTOTYPE"), LOG4CXX_STR("cryptotype")))
	{
		cryptoType = value;
	}
	else
	{
		PatternLayout::setOption(option, value);
	}
}

void CryptoLayout::format(log4cxx::LogString& output,
			              const spi::LoggingEventPtr& event,
			              log4cxx::helpers::Pool& pool) const
{
	PatternLayout::format (output, event, pool);
	CryptoLayout::format (output, cryptoType);
}


void CryptoLayout::format(log4cxx::LogString& output, log4cxx::LogString cryptoType)
{
	Smartmatic::Log::ICryptoLayoutTransformer * interface = NULL;

	if ( iCryptoMap.find(cryptoType) != iCryptoMap.end() )
	{
		interface = iCryptoMap[cryptoType];
	}

	if (interface != NULL)
	{
		synchronized sync(interface->getMutex());
		output = interface->encode(output);
	}
}

void CryptoLayout::setCryptoMap(std::map < std::string, Smartmatic::Log::ICryptoLayoutTransformer * > iCryptoMap )
{
	CryptoLayout::iCryptoMap = iCryptoMap;
}

void CryptoLayout::putCryptoInterface(Smartmatic::Log::ICryptoLayoutTransformer * iCrypto)
{
	if (iCrypto)
	{
		CryptoLayout::iCryptoMap[iCrypto->getCode()] = iCrypto;
	}
}
