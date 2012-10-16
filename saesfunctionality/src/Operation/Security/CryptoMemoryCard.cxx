/*
 * CryptoMemoryCard.cxx
 *
 *  Created on: 25/08/2011
 *      Author: soto
 */

#include "CryptoMemoryCard.hxx"
#include <Security/Encryption.hxx>

using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Operation::Security;

CryptoMemoryCard::CryptoMemoryCard()
{

}

CryptoMemoryCard::~CryptoMemoryCard()
{

}

bool CryptoMemoryCard::decrypto(SafeBuffer & dataIn, SafeBuffer & dataOut)
{
	getKeys();
	return CryptoData::decrypto(dataIn, dataOut);
}

void CryptoMemoryCard::getKeys()
{
	const unsigned char * dataKey;
	int len;
	dataKey = Encryption::getInstance()->getSecretKey().getKey(len);

	SafeBuffer key((unsigned char *)dataKey, len);
	SafeBuffer iv;

	Encryption::getInstance()->getComposeKey(key, iv, Encryption::getInstance()->getIVLength());

	setKey(key);
	setIV(iv);
}
