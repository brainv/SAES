/**
 * @file Crypto.cxx
 * @brief Body class for Crypto file
 */

#include "Crypto.hxx"
#include "System/Security/Cryptography/CryptoAES.hxx"
#include "System/Security/Cryptography/CryptoPKCS12.hxx"
#include "System/Security/Cryptography/CryptoPKCS7.hxx"
#include <iostream>
#include <fstream>
#include "System/guid-class.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/IO/File.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///< macro for gettext
#else
#define _(String) (String) ///< macro without gettext
#endif

#define N_(String) (String) ///< macro not translate

using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

ISMTTLog* Crypto::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.Crypto",GETTEXT_PACKAGE);

Crypto::Crypto()
{
    this->cryptoAES = NULL;
    this->cryptoP12 = NULL;
    this->cryptoP7 = NULL;
}

Crypto::~Crypto()
{
    if (cryptoAES)
    {
        delete cryptoAES;
        cryptoAES = NULL;
    }
    if (cryptoP12)
    {
        delete cryptoP12;
        cryptoP12 = NULL;
    }
    if (cryptoP7)
    {
        delete cryptoP7;
        cryptoP7 = NULL;
    }
}

void Crypto::init(Crypto::KeySize keySize, Crypto::Mode mode, bool pad)
        throw (CryptoException)
{
    this->mode = mode;
    this->pad = pad;
    this->keySize = keySize;

    switch(keySize)
    {
        case KEY_AES_128:
            configCryptoAESKey128();
            break;
        case KEY_AES_192:
            configCryptoAESKey192();
            break;
        case KEY_AES_256:
            configCryptoAESKey256();
            break;
    }
}

void Crypto::loadPKCS7()
        throw (CryptoException)
{
    if (cryptoP7)
    {
        delete cryptoP7;
        cryptoP7 = NULL;
    }

    const EVP_CIPHER * cipher = NULL;

	switch(keySize)
	{
		case KEY_AES_128:
			cipher = EVP_aes_128_cbc();
			break;
		case KEY_AES_192:
			cipher = EVP_aes_192_cbc();
			break;
		case KEY_AES_256:
			cipher = EVP_aes_256_cbc();
			break;
	}

	if (cryptoP12)
    {
		cryptoP7 = new Cryptography::CryptoPKCS7(cryptoP12, cipher);
    }
    else if (certifiedX509)
    {
    	cryptoP7 = new Cryptography::CryptoPKCS7(certifiedX509, cipher);
    }
}

void Crypto::cryptoBufferToFile(SafeBuffer & dataIn, std::string & file,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    SafeBuffer encryptoData;
    cryptoBufferToBuffer(dataIn, encryptoData, key, iv);

    if (!Smartmatic::System::IO::File::saveBufferToFile(encryptoData, file))
    {
        logger->Debug("ERROR - write file " + file);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorWriteFile"), N_("Smartmatic.System.Security.Crypto.ErrorWriteFile"),logger);
    }
}

void Crypto::cryptoFileToBuffer(std::string & fileIn,
		Smartmatic::System::SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    Smartmatic::System::SafeBuffer bufferFile;
    Smartmatic::System::IO::File::openFileToBuffer(fileIn, bufferFile);

    Smartmatic::System::SafeBuffer buffer;

    if (bufferFile.GetData() != NULL)
    {
        cryptoBufferToBuffer(bufferFile, buffer, key, iv);
    }
    else
    {
        logger->Debug("ERROR - open file " + fileIn);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorOpenFile"), N_("Smartmatic.System.Security.Crypto.ErrorOpenFile"),logger);
    }
}

void Crypto::cryptoFileToFile(std::string & fileIn, std::string & fileOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    Smartmatic::System::SafeBuffer bufferFile;
    Smartmatic::System::IO::File::openFileToBuffer(fileIn, bufferFile);

    if (bufferFile.GetData() != NULL)
    {
        cryptoBufferToFile(bufferFile, fileOut, key, iv);
    }
    else
    {
        logger->Debug("ERROR - open file " + fileIn);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorOpenFile"), N_("Smartmatic.System.Security.Crypto.ErrorOpenFile"),logger);
    }
}

void Crypto::cryptoBufferToBuffer(SafeBuffer & dataIn,
		Smartmatic::System::SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    return cryptoAES->encryptoData(dataIn, dataOut, key, iv, pad);
}

void Crypto::decryptoFileToBuffer(std::string & file,
		Smartmatic::System::SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    Smartmatic::System::SafeBuffer bufferFile;
    Smartmatic::System::IO::File::openFileToBuffer(file, bufferFile);

    if (bufferFile.GetData() != NULL)
    {
        decryptoBufferToBuffer(bufferFile, dataOut, key, iv);
    }
    else
    {
        logger->Debug("ERROR - open file " + file);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorOpenFile"), N_("Smartmatic.System.Security.Crypto.ErrorOpenFile"),logger);
    }
}
void Crypto::decryptoBufferToFile(Smartmatic::System::SafeBuffer &dataIn,
        std::string & file,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    SafeBuffer encryptoData;
    decryptoBufferToBuffer(dataIn, encryptoData, key, iv);

    std::ofstream cryptoFile(file.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    if (cryptoFile.is_open())
    {
        cryptoFile.write((const char *)encryptoData.GetData(), encryptoData.GetSize());
        cryptoFile.close();
    }
    else
    {
        logger->Debug("ERROR - write file " + file);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorWriteFile"), N_("Smartmatic.System.Security.Crypto.ErrorWriteFile"),logger);
    }
}

void Crypto::decryptoFileToFile(std::string & fileIn, std::string & fileOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    SafeBuffer encryptoData;
    decryptoFileToBuffer(fileIn, encryptoData, key, iv);

    std::ofstream cryptoFile(fileOut.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    if (cryptoFile.is_open())
    {
        cryptoFile.write((const char *)encryptoData.GetData(), encryptoData.GetSize());
        cryptoFile.close();
    }
    else
    {
    	logger->Debug("ERROR - write file " + fileIn);
        throw CryptoException(_("Smartmatic.System.Security.Crypto.ErrorWriteFile"), N_("Smartmatic.System.Security.Crypto.ErrorWriteFile"),logger);
    }
}

void Crypto::decryptoBufferToBuffer(SafeBuffer & dataIn,
		Smartmatic::System::SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv)
        throw (CryptoException)
{
    cryptoAES->decryptoData(dataIn, dataOut, key, iv, pad);
}

void Crypto::pkcs7CryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut)
	throw (CryptoException)
{
	cryptoP7->cryptoBuffer(dataIn, dataOut, Cryptography::CryptoBase::CRYPTO_SMIME);
}

void Crypto::pkcs7DecryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut)
	throw (CryptoException)
{
	cryptoP7->decryptoBuffer(dataIn, dataOut, Cryptography::CryptoBase::CRYPTO_SMIME);
}

void Crypto::cmsCryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut)
	throw (CryptoException)
{

}

void Crypto::cmsDecryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut)
	throw (CryptoException)
{

}

void Crypto::configCryptoAESKey128()
{
    switch (mode)
    {
        case MODE_AES_CBC:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_cbc());
            break;
        case MODE_AES_CFB1:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_cfb1());
            break;
        case MODE_AES_CFB8:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_cfb8());
            break;
        case MODE_AES_CFB128:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_cfb128());
            break;
        case MODE_AES_ECB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_ecb());
            break;
        case MODE_AES_OFB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_128_ofb());
            break;
    }
}

void Crypto::configCryptoAESKey192()
{
    switch (mode)
    {
        case MODE_AES_CBC:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_cbc());
            break;
        case MODE_AES_CFB1:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_cfb1());
            break;
        case MODE_AES_CFB8:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_cfb8());
            break;
        case MODE_AES_CFB128:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_cfb128());
            break;
        case MODE_AES_ECB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_ecb());
            break;
        case MODE_AES_OFB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_192_ofb());
            break;
    }
}

void Crypto::configCryptoAESKey256()
{
    switch (mode)
    {
        case MODE_AES_CBC:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_cbc());
            break;
        case MODE_AES_CFB1:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_cfb1());
            break;
        case MODE_AES_CFB8:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_cfb8());
            break;
        case MODE_AES_CFB128:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_cfb128());
            break;
        case MODE_AES_ECB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_ecb());
            break;
        case MODE_AES_OFB:
            cryptoAES = new Cryptography::CryptoAES(EVP_aes_256_ofb());
            break;
    }
}
