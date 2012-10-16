/**
 * @file CryptoPKCS7.cxx
 * @brief Body class crypto PCKS7
 * @date 19/03/2012
 * @author Yadickson Soto
 */

#include "CryptoPKCS7.hxx"
#include "CryptoPKCS12.hxx"
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

ISMTTLog* CryptoPKCS7::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CryptoPKCS7",GETTEXT_PACKAGE);

CryptoPKCS7::CryptoPKCS7(CryptoPKCS12 * cryptoPKCS12, const EVP_CIPHER * cipherMode)
: CryptoBase(cryptoPKCS12, cipherMode)
{

}

CryptoPKCS7::CryptoPKCS7(const X509 * cert, const EVP_CIPHER * cipherMode)
: CryptoBase(cert, cipherMode)
{

}

CryptoPKCS7::~CryptoPKCS7()
{

}

void CryptoPKCS7::cryptoBuffer(SafeBuffer & bufferIn, SafeBuffer & bufferOut, CryptoBase::CryptoBaseType type)
   	throw (CryptoException)
{
	PKCS7 * p7 = NULL;
	BIO * messageBio = NULL;
	BIO * cryptoMessage = NULL;
	STACK_OF(X509) * ca = NULL;
	const X509 * _cert = NULL;

	char * bioDataPtr = NULL;
    long   bioDataLen = 0;
	int flags = PKCS7_BINARY;

	messageBio = BIO_new_mem_buf((void *)bufferIn.GetData(), bufferIn.GetSize());

	if (messageBio == NULL)
	{
		logger->Debug("ERROR - load data in.");

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				logger);
	}

    (void)SSL_library_init();

	ca = sk_X509_new_null();

	if (cryptoPKCS12)
    {
		_cert = cryptoPKCS12->getCertified();
    }
    else if (cert)
    {
		_cert = cert;
    }

	sk_X509_push(ca, _cert);

    p7 = PKCS7_encrypt(ca,
    		messageBio,
    		cipherMode,
    		flags);

	if (p7 == NULL)
	{
		logger->Debug("ERROR - cryptography data in.");

		BIO_free(messageBio);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				logger);
	}

	cryptoMessage = BIO_new (BIO_s_mem());

	if (cryptoMessage == NULL)
	{
		logger->Debug("ERROR - load memory cryptography.");

		PKCS7_free(p7);
		BIO_free(messageBio);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				logger);
	}

	int resp = 0;

	switch(type)
	{
		case CryptoBase::CRYPTO_PEM:
			resp = PEM_write_bio_PKCS7(cryptoMessage,p7);
			break;
		case CryptoBase::CRYPTO_SMIME:
			resp = SMIME_write_PKCS7(cryptoMessage, p7, messageBio, flags);
			break;
		case CryptoBase::CRYPTO_DER:
			resp = i2d_PKCS7_bio(cryptoMessage,p7);
			break;
	}

	if (resp <= 0)
	{
		PKCS7_free(p7);
		BIO_free(messageBio);
		BIO_free(cryptoMessage);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorCryptoData"),
				logger);
	}

	bioDataLen = BIO_get_mem_data (cryptoMessage, &bioDataPtr);
	bufferOut.AddData((unsigned char *)bioDataPtr, bioDataLen);

	PKCS7_free(p7);
	BIO_free(messageBio);
	BIO_free(cryptoMessage);
}

void CryptoPKCS7::decryptoBuffer(SafeBuffer & bufferIn, SafeBuffer & bufferOut, CryptoBase::CryptoBaseType type)
   	throw (CryptoException)
{
	PKCS7 * p7 = NULL;
	BIO * messageBio = NULL;
	BIO * decryptoMessage = NULL;
	BIO * indata = NULL;

	char * bioDataPtr = NULL;
    long   bioDataLen = 0;
	int flags = PKCS7_BINARY;

	messageBio = BIO_new_mem_buf((void *)bufferIn.GetData(), bufferIn.GetSize());

	if (messageBio == NULL)
	{
		logger->Debug("ERROR - load data in.");

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				logger);
	}

    (void)SSL_library_init();

	switch(type)
	{
		case CryptoBase::CRYPTO_PEM:
			p7 = PEM_read_bio_PKCS7(messageBio, NULL, NULL, NULL);
			break;
		case CryptoBase::CRYPTO_SMIME:
			p7 = SMIME_read_PKCS7(messageBio, &indata);
			break;
		case CryptoBase::CRYPTO_DER:
			p7 = d2i_PKCS7_bio(messageBio, NULL);
			break;
	}

    if (p7 == NULL)
	{
		logger->Debug("ERROR - load p7.");

		BIO_free(messageBio);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				logger);
	}

	decryptoMessage = BIO_new (BIO_s_mem());

	if (decryptoMessage == NULL)
	{
		logger->Debug("ERROR - load memory cryptography.");

		PKCS7_free(p7);
		BIO_free(messageBio);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				logger);
	}

    if (PKCS7_decrypt(p7,
    		cryptoPKCS12->getPrimaryKey(),
    		cryptoPKCS12->getCertified(),
    		decryptoMessage,
    		flags) <= 0)
    {
		logger->Debug("ERROR - decrypt data in.");

		PKCS7_free(p7);
		BIO_free(messageBio);
		BIO_free(decryptoMessage);

		throw CryptoException(
				_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				N_("Smartmatic.System.Security.Cryptography.CryptoPKCS7.ErrorDecryptoData"),
				logger);
    }

	bioDataLen = BIO_get_mem_data (decryptoMessage, &bioDataPtr);
	bufferOut.AddData((unsigned char *)bioDataPtr, bioDataLen);

	PKCS7_free(p7);
	BIO_free(messageBio);
	BIO_free(decryptoMessage);
}
