/**
 * @file CMSSigner.cxx
 * @brief Body class CMSSigner
 * @date 05/03/2012
 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
 */

#include "CMSSigner.hxx"
#include "CryptoPKCS12.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef USE_CMS_SIGNER
#include <openssl/pem.h>
#include <openssl/cms.h>
#include <openssl/ssl.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::System;

ISMTTLog* CMSSigner::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CMSSigner",GETTEXT_PACKAGE);

CMSSigner::CMSSigner()
{

}

CMSSigner::~CMSSigner()
{

}

void CMSSigner::signedBuffer(SafeBuffer & bufferIn,
		SafeBuffer & bufferOut,
		CryptoPKCS12 * cryptoPKCS12,
		SignedType type)
	throw (SignedException)
{
#ifdef USE_CMS_SIGNER

	CMS_ContentInfo * cms = NULL;
	BIO * messageBio = NULL;
	BIO * signedMessage = NULL;

	char * bioDataPtr = NULL;
    long   bioDataLen = 0;

	messageBio = BIO_new_mem_buf((void *)bufferIn.GetData(), bufferIn.GetSize());

	if (messageBio == NULL)
	{
		logger->Debug("ERROR - load data in.");

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				logger);
	}

    (void)SSL_library_init();
	OpenSSL_add_all_algorithms();

	cms = CMS_sign(cryptoPKCS12->getCertified(),
    		cryptoPKCS12->getPrimaryKey(),
    		cryptoPKCS12->getCertificatesAuthorities(),
    		messageBio,
    		CMS_BINARY);

	if (cms == NULL)
	{
		logger->Debug("ERROR - signature data in.");

		BIO_free(messageBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				logger);
	}

	signedMessage = BIO_new (BIO_s_mem());

	if (signedMessage == NULL)
	{
		logger->Debug("ERROR - load memory signature.");

		CMS_ContentInfo_free(cms);
		BIO_free(messageBio);

		throw SignedException(
				_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
				logger);
	}

	switch (type)
	{
		case CMS_PEM:
			if (PEM_write_bio_CMS (signedMessage, cms) <= 0)
			{
				logger->Debug("ERROR - create signature CMS.");

				CMS_ContentInfo_free(cms);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						logger);
		    }
			break;

		case CMS_SMIME:
			if (SMIME_write_CMS(signedMessage, cms, messageBio, CMS_BINARY) <= 0)
			{
				logger->Debug("ERROR - create signature S/MIME.");

				CMS_ContentInfo_free(cms);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						logger);
		    }
			break;

		case CMS_ASN1:
			if (i2d_CMS_bio(signedMessage, cms) <= 0)
			{
				logger->Debug("ERROR - create signature.");

				CMS_ContentInfo_free(cms);
				BIO_free(messageBio);
				BIO_free(signedMessage);

				throw SignedException(
						_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
						logger);
		    }
			break;

		default:
			break;
	}

	bioDataLen = BIO_get_mem_data (signedMessage, &bioDataPtr);
	bufferOut.AddData((unsigned char *)bioDataPtr, bioDataLen);

	CMS_ContentInfo_free(cms);
	BIO_free(messageBio);
	BIO_free(signedMessage);

#else

	logger->Debug("ERROR - CMS Signer not support in openssl < 1.0.0");

	throw SignedException(
			_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
			N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorSignedData"),
			logger);

#endif
}

void CMSSigner::validateBuffer(SafeBuffer & bufferIn,
		SafeBuffer & bufferSigned,
		CryptoPKCS12 * cryptoPKCS12,
		SignedType type)
	throw (SignedException)
{
	logger->Debug("ERROR - Validate data not support.");

	throw SignedException(
			_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorValidateData"),
			N_("Smartmatic.System.Security.Cryptography.CMSSigner.ErrorValidateData"),
			logger);
}
