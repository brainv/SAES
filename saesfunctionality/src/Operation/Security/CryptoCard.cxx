/*
 * CryptoCard.cxx
 *
 *  Created on: 26/08/2011
 *      Author: soto
 */

#include "CryptoCard.hxx"
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Utils;

CryptoCard::CryptoCard()
{

}

CryptoCard::~CryptoCard()
{

}

void CryptoCard::getKeyPin()
{

}

void CryptoCard::getKeys()
{

}

void CryptoCard::setKeyPin(std::string & strPin)
{
	SafeBuffer pin;
	StringUtils::stringToBufferHex(strPin, pin);
	setPin(pin);
}
