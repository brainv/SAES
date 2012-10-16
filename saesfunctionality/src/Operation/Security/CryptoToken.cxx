/*
 * CryptoToken.cxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#include "CryptoToken.hxx"
#include <Security/Encryption.hxx>

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System;

CryptoToken::CryptoToken()
{
	const SafeBuffer & initKey (Encryption::getInstance()->getInitKey());

	SafeBuffer pin;
	SafeBuffer key;
	SafeBuffer iv;

	Encryption::getInstance()->getComposeKey(initKey, pin, PASSWORD_PIN_LEN);
	Encryption::getInstance()->getComposeKey(initKey, key, Encryption::getInstance()->getKeyLength());
	Encryption::getInstance()->getComposeKey(initKey, iv, Encryption::getInstance()->getIVLength());

	setPin(pin);
	setKey(key);
	setIV(iv);
}

CryptoToken::~CryptoToken()
{

}
