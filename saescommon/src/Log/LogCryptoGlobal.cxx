/*
 * LogCryptoGlobal.cxx
 *
 *  Created on: 27/07/2011
 *      Author: soto
 */

#include "LogCryptoGlobal.hxx"
#include <Security/Encryption.hxx>
#include <Configuration/SaesCommonConfiguration-schema.hxx>

using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Common::Configuration;

LogCryptoGlobal::LogCryptoGlobal()
: Smartmatic::Log::ICryptoLayoutTransformer( CryptoType( CryptoType::CONFIGURATION_GLOBAL) )
{

}

std::string LogCryptoGlobal::encode(std::string & line)
{
	std::stringstream ss;

	try
	{
		ss << Encryption::getInstance()->cryptoStringToB64(line, Encryption::INIT_KEY);
		ss << std::endl;
	}
	catch (CryptoException & ex)
	{
		std::cerr << "FATAL - " << __func__ << " - " << ex.what() << std::endl;
	}

	return ss.str();
}

std::string LogCryptoGlobal::decode(std::string & line)
{
	std::stringstream ss;

	try
	{
		ss << Encryption::getInstance()->decryptoB64ToString(line, Encryption::INIT_KEY);
		ss << std::endl;
	}
	catch (CryptoException & ex)
	{
		std::cerr << "FATAL - " << __func__ << " - " << ex.what() << std::endl;
	}

	return ss.str();
}
