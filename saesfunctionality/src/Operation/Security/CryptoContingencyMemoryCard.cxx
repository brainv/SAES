/*
 * CryptoContingencyMemoryCard.cxx
 *
 *  Created on: 16/10/2011
 *      Author: soto
 */

#include "CryptoContingencyMemoryCard.hxx"
#include <Security/Encryption.hxx>
#include <System/Security/Cryptography/PBEKeyDerivatorHMAC.h>

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System;

CryptoContingencyMemoryCard::CryptoContingencyMemoryCard()
{

}

CryptoContingencyMemoryCard::~CryptoContingencyMemoryCard()
{

}

void CryptoContingencyMemoryCard::getKeys()
{
	const SafeBuffer & pin (getPin());

	PBEKeyDerivatorHMAC pbe;

	SafeBuffer hash = MsgDigestUtil::Digest(pin.GetData(), pin.GetSize(), MsgDigestUtil::DGSTUTIL_SHA1);


	Glib::ustring passPhrase = pin.GetBase64Data();
	Glib::ustring salt = hash.GetBase64Data();

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
