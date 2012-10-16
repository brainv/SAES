/*
 * CryptoSmartCard.cxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#include "CryptoSmartCard.hxx"
#include <Security/Encryption.hxx>
#include <System/guid-class.h>
#include <System/Security/Cryptography/PBEKeyDerivatorHMAC.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::SAES::Common::Configuration;

CryptoSmartCard::CryptoSmartCard()
{

}

CryptoSmartCard::~CryptoSmartCard()
{

}

void CryptoSmartCard::getKeyPin()
{
    SafeBuffer key;
    SafeBuffer pin;

	DataPIN dataPinType = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getDataPIN();

	switch(dataPinType)
	{
		case DataPIN::CONFIGURATION_OPENING_CODE:
			key = Encryption::getInstance()->getOpeningCode().toSafeBuffer();
			break;

		case DataPIN::CONFIGURATION_VERIFICATION_KEY:
			key = Encryption::getInstance()->getVerificationKey();
			break;
	}

	Encryption::getInstance()->getComposeKey(key, pin, PASSWORD_PIN_LEN);
	setPin(pin);
}

void CryptoSmartCard::getKeys()
{
    PBEKeyDerivatorHMAC pbe;

    Glib::ustring passPhrase = GuidClass::NewGuid().ToString();
    Glib::ustring salt = GuidClass::NewGuid().ToString();

    unsigned char outkey[32];
    int keyLen = sizeof(outkey)/sizeof(char);
    int iterations = 2048;

    pbe.SetSalt(salt);
    pbe.GenerateKey(passPhrase, outkey, keyLen, iterations);

    SafeBuffer globalKey(outkey, keyLen);

    SafeBuffer key;
	SafeBuffer iv;

	Encryption::getInstance()->getComposeKey(globalKey, key, Encryption::getInstance()->getKeyLength());
	Encryption::getInstance()->getComposeKey(globalKey, iv, Encryption::getInstance()->getIVLength());

	setKey(key);
	setIV(iv);
}
