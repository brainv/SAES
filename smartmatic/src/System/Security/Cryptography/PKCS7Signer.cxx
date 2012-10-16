/**
 * @file PKCS7Signer.cxx
 * @brief Body class PKCS7Signer
 * @date 02/03/2012
 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
 */

#include "PKCS7Signer.hxx"
#include "CryptoPKCS12.hxx"
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
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

ISMTTLog* PKCS7Signer::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.PKCS7Signer",GETTEXT_PACKAGE);

PKCS7Signer::PKCS7Signer(CryptoPKCS12 * cryptoPKCS12)
{
	this->cryptoPKCS12 = cryptoPKCS12;
	this->primaryKey = NULL;
	this->cert = NULL;
}

PKCS7Signer::PKCS7Signer(EVP_PKEY * primaryKey, X509 * cert)
{
	this->cryptoPKCS12 = NULL;
	this->primaryKey = primaryKey;
	this->cert = cert;
}

PKCS7Signer::~PKCS7Signer()
{

}

void PKCS7Signer::signedBuffer(SafeBuffer & bufferIn,
		SafeBuffer & bufferOut,
		PKCS7Signer::SignedType type)
	throw (SignedException, CryptoException)
{
	PKCS7 * p7 = NULL;
	BIO * messageBio = NULL;
	BIO * signedMessage = NULL;

	char * bioDataPtr = NULL;
    long   bioDataLen = 0;

	messageBio = BIO_new_mem_buf((void *)bufferIn.GetData(), bufferIn.GetSize());

	if (messageBio == NULL)
	{
		logger->Debug("ERROR - load data in.");

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				logger);
	}

    (void)SSL_library_init();

    if (cryptoPKCS12)
    {
    	p7 = PKCS7_sign(cryptoPKCS12->getCertified(),
    		cryptoPKCS12->getPrimaryKey(),
    		cryptoPKCS12->getCertificatesAuthorities(),
    		messageBio,
    		PKCS7_BINARY);
    }
    else if (primaryKey && cert)
    {
    	p7 = PKCS7_sign(cert,
    		primaryKey,
    		NULL,
    		messageBio,
    		PKCS7_BINARY);
    }

	if (p7 == NULL)
	{
		logger->Debug("ERROR - signature data in.");

		BIO_free(messageBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				logger);
	}

	signedMessage = BIO_new (BIO_s_mem());

	if (signedMessage == NULL)
	{
		logger->Debug("ERROR - load memory signature.");

		PKCS7_free(p7);
		BIO_free(messageBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
				logger);
	}

	switch (type)
	{
		case PKCS7_PEM:
			if (PEM_write_bio_PKCS7 (signedMessage, p7) <= 0)
			{
				logger->Debug("ERROR - create signature CMS.");

				PKCS7_free(p7);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						logger);
		    }
			break;

		case PKCS7_SMIME:
			if (SMIME_write_PKCS7(signedMessage, p7, messageBio, PKCS7_BINARY) <= 0)
			{
				logger->Debug("ERROR - create signature S/MIME.");

				PKCS7_free(p7);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						logger);
		    }
			break;

		case PKCS7_ASN1:
			if (i2d_PKCS7_bio(signedMessage, p7) <= 0)
			{
				logger->Debug("ERROR - create signature.");

				PKCS7_free(p7);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorSignedData"),
						logger);
		    }
			break;

		default:
			break;
	}

	bioDataLen = BIO_get_mem_data (signedMessage, &bioDataPtr);
	bufferOut.AddData((unsigned char *)bioDataPtr, bioDataLen);

	PKCS7_free(p7);
	BIO_free(messageBio);
	BIO_free(signedMessage);
}

void PKCS7Signer::validateBuffer(SafeBuffer & bufferIn,
		Smartmatic::System::SafeBuffer & bufferSigned,
		PKCS7Signer::SignedType type)
	throw (SignedException, CryptoException)
{
	/*
	PKCS7 * p7 = NULL;
	X509_STORE * store = NULL;
	BIO * messageBio = NULL;
	BIO * signedBio = NULL;
	BIO * outBio = NULL;

	messageBio = BIO_new_mem_buf((void *)bufferIn.GetData(), bufferIn.GetSize());

	if (messageBio == NULL)
	{
		logger->Debug("ERROR - load data in.");

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

	signedBio = BIO_new_mem_buf((void *)bufferSigned.GetData(), bufferSigned.GetSize());

	if (signedBio == NULL)
	{
		logger->Debug("ERROR - load signed data.");

		BIO_free(messageBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

	outBio = BIO_new(BIO_s_mem());

	if (outBio == NULL)
	{
		logger->Debug("ERROR - new out bio.");

		BIO_free(messageBio);
		BIO_free(signedBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

	store = X509_STORE_new();

	if (store == NULL)
	{
		logger->Debug("ERROR - new store.");

		BIO_free(messageBio);
		BIO_free(signedBio);
		BIO_free(outBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

    (void)SSL_library_init();

    if (X509_STORE_add_cert(store, cryptoPKCS12->getCertified()) <= 0)
	{
		logger->Debug("ERROR - add certified.");

		BIO_free(messageBio);
		BIO_free(signedBio);
		BIO_free(outBio);
		X509_STORE_free(store);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

    switch(type)
	{
		case PKCS7_PEM:
			p7 = PEM_read_bio_PKCS7(signedBio, NULL, NULL, NULL);
			break;
		case PKCS7_SMIME:
			p7 = SMIME_read_PKCS7(signedBio, &messageBio);
			break;

		default:
			break;
	}

	if (p7 == NULL)
	{
		logger->Debug("ERROR - load p7.");

		BIO_free(messageBio);
		BIO_free(signedBio);
		BIO_free(outBio);
		X509_STORE_free(store);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
	}

    if (PKCS7_verify(p7, cryptoPKCS12->getCertificatesAuthorities(), store, messageBio, outBio, PKCS7_NOVERIFY) <= 0)
    {
		logger->Debug("ERROR - verify certified.");

		PKCS7_free(p7);
	    X509_STORE_free(store);
		BIO_free(messageBio);
		BIO_free(signedBio);
		BIO_free(outBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
				logger);
    }

	PKCS7_free(p7);
    X509_STORE_free(store);
	BIO_free(messageBio);
	BIO_free(signedBio);
	BIO_free(outBio);
	*/

	logger->Debug("ERROR - Validate data not support.");

	throw SignedException(
			_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
			N_("Smartmatic.System.Security.Cryptography.PKCS7Signer.ErrorValidateData"),
			logger);
}
