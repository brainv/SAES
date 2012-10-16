/**
 * @file CryptoData.cxx
 * @brief Body class crypto data
 * @date 25/08/2011
 * @author Yadickson Soto
 */

#include "CryptoData.hxx"
#include <System/Security/Crypto.hxx>
#include <Security/Encryption.hxx>
#include <System/Exception/CryptoException.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* CryptoData::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Security.CryptoData",GETTEXT_PACKAGE);

CryptoData::CryptoData()
{

}

CryptoData::CryptoData(SafeBuffer & pin, SafeBuffer & key, SafeBuffer & iv)
{
	setPin(pin);
	setKey(key);
	setIV(iv);
}

CryptoData::~CryptoData()
{

}

bool CryptoData::crypto(SafeBuffer & dataIn, SafeBuffer & dataOut)
{
    Crypto objCrypto;
    objCrypto.init(Encryption::getInstance()->getKeySize(), Encryption::getInstance()->getModeType(), true);

    try
    {
    	dataOut.Clear();
    	objCrypto.cryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
    	return true;
    }
    catch(CryptoException & ex)
    {
    	logger->Debug("ERROR - crypto data");
    }

    return false;
}

bool CryptoData::decrypto(SafeBuffer & dataIn, SafeBuffer & dataOut)
{
    Crypto objCrypto;
    objCrypto.init(Encryption::getInstance()->getKeySize(), Encryption::getInstance()->getModeType(), true);

    try
    {
    	dataOut.Clear();
    	objCrypto.decryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
    	return true;
    }
    catch(CryptoException & ex)
    {
    	logger->Debug("ERROR - decrypto data");
    }

    return false;
}

void CryptoData::setPin(SafeBuffer & pin)
{
	this->pin.Clear();
	this->pin.AddData(pin);
}

void CryptoData::setKey(SafeBuffer & key)
{
	this->key.Clear();
	this->key.AddData(key);
}

void CryptoData::setIV(SafeBuffer & iv)
{
	this->iv.Clear();
	this->iv.AddData(iv);
}

const SafeBuffer & CryptoData::getPin()
{
	return pin;
}

const SafeBuffer & CryptoData::getKey()
{
	return key;
}

const SafeBuffer & CryptoData::getIV()
{
	return iv;
}
