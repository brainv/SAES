/*
 * logCryptoBase64.cxx
 *
 *  Created on: 25/07/2011
 *      Author: soto
 */

#include "LogCryptoBase64.hxx"
#include <System/Encoding/Base64Encoder.h>
#include <Configuration/SaesCommonConfiguration-schema.hxx>

using namespace Smartmatic::SAES::Log;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Common::Configuration;

LogCryptoBase64::LogCryptoBase64()
: Smartmatic::Log::ICryptoLayoutTransformer( CryptoType( CryptoType::CONFIGURATION_BASE64) )
{

}

std::string LogCryptoBase64::encode(std::string & line)
{
	std::stringstream ss;
	Glib::ustring data = line;
	ss << Base64Encoder::ConvertToBase64(data);
	ss << std::endl;
	return ss.str();
}

std::string LogCryptoBase64::decode(std::string & line)
{
	std::string ss;
	SafeBuffer buffer;
	Base64Encoder::ConvertFromBase64(line, buffer);

	if (buffer.GetSize() > 0)
	{
		ss.assign((const char *)buffer.GetData(), buffer.GetSize());
		ss.resize(buffer.GetSize());
	}

	return ss;
}
