/**
 * @file RsaUtil.cpp
 * @brief Body class rsa util
 * @date 24/05/2011
 * @author Marcel Cordovi
 */

#include <string.h>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <Log/SMTTLogManager.h>
#include "CryptoPKCS12.hxx"
#include "RsaUtil.h"

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

#define KEYGEN_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.ErrorGeneratingKey") ///< text for log
#define KCHECK_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.ErrorCheckingKeyIntegrity") ///< text for log
#define BUFINV_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.InvalidBuffer") ///< text for log
#define CIPHER_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.ErrorDuringCpherOperation") ///< text for log
#define PADING_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.InvalidPadding") ///< text for log
#define IOCERT_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.ErrorLoadingKeyFromDisk") ///< text for log
#define P12CER_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.ErrorConvertingP12Format") ///< text for log
#define PEMKEY_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.BadKeyTypeFormat") ///< text for log
#define RSAKEY_ERR_MSG N_("Smartmatic.System.Security.Cryptography.RsaUtil.LoadedKeyIsInvalid") ///< text for log

using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;
using namespace std;


ISMTTLog* RsaUtil::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Common.Security.SecretKey", GETTEXT_PACKAGE);


//============================================================================//
//============================= Life Cycle ===================================//
//============================================================================//


RsaUtil::RsaUtil()
{
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	m_Padding = RSAPAD_PKCS1;
	//m_Rsa = NULL;
}

RsaUtil::RsaUtil(
		  const Glib::ustring& certPath
		, const CertUtil::CertFileFormat certFormat
		, const RsaPaddingEnumType pad)
throw (const Smartmatic::System::Exception::RSAException&)
{
	/*ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	//m_Rsa = NULL;
	m_Padding = pad;

	switch (certFormat)
	{
	case CertUtil::CertFormat_ASN1RSA:
		SetPublicKey_X509_Der2 (certPath);
		break;
	case CertUtil::CertFormat_PEM:
		SetPublicKey_X509_Pem2 (certPath);
		break;
	case CertUtil::CertFormat_PKCS12:
		SetPublicKey_X509_PKCS122 (certPath, ""); //TODO request passphrase
		break;
	case CertUtil::CertFormat_TEXT:
		//TODO implement reading for this format
	case CertUtil::CertFormat_PEMRSA:
		//TODO implement reading for this format
		break;
	case CertUtil::CertFormat_DER:
			//TODO implement reading for this format
	break;
	}*/
}

RsaUtil::RsaUtil(
		  const RsaPaddingEnumType pad
		, const int n
		, const unsigned long e)
throw (const Smartmatic::System::Exception::RSAException&)
{
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	m_Padding = pad;

	//m_Rsa = RSA_generate_key (n, e, NULL, NULL); // TODO optionally implement callback function

	//if ( m_Rsa == NULL )
	//{
		//throw RSAException (_(KEYGEN_ERR_MSG), N_(KEYGEN_ERR_MSG), logger);
	//}
}

RsaUtil::RsaUtil(const RsaUtil& other)
{
	this->m_Padding = other.m_Padding;
	//this->m_Rsa = NULL;

	//if (other.m_Padding != NULL)
	//{
	//	m_Rsa = static_cast<RSA*> (g_malloc (sizeof (RSA)));
	//	memcpy ((void*)this->m_Rsa, (void*)other.m_Rsa, sizeof (RSA));
	//}
	//else
	//{
	 //   m_Rsa = NULL;
	//}
}

RsaUtil::~RsaUtil()
{
	//if (m_Rsa != NULL)
	//	RSA_free (m_Rsa);
}

SignatureAlgorithm::SignatureAlgorithmType RsaUtil::GetType() const
{
	return SignatureAlgorithm::RSA_SIGNATURE;
}

//============================================================================//
//======================= Operator overloading ===============================//
//============================================================================//


RsaUtil& RsaUtil::operator =(const RsaUtil& other)
{
	if (this != &other)
	{
		this->m_Padding = other.m_Padding;

		//if (m_Rsa != NULL)
		//	RSA_free (m_Rsa);

		//if (other.m_Padding != NULL)
		//{
		//	m_Rsa = static_cast<RSA*> (g_malloc (sizeof (RSA)));
		//	memcpy ((void*)this->m_Rsa, (void*)other.m_Rsa, sizeof (RSA));
		//}
		//else
		//	m_Rsa = NULL;
	}

	return *this;
}

bool RsaUtil::operator ==(const RsaUtil& other)
{
	return this->m_Padding == other.m_Padding;
}


//============================================================================//
//=============================== Access =====================================//
//============================================================================//


RsaUtil::RsaPaddingEnumType RsaUtil::GetPaddingType() const
{
	return this->m_Padding;
}

void RsaUtil::SetPaddingType(RsaPaddingEnumType pad)
{
	this->m_Padding = pad;
}

/*void RsaUtil::SetPrivateKey_PEM2 (
		  const Glib::ustring& pemFilePath
		, const Glib::ustring& passPhrase)
throw (const Smartmatic::System::Exception::RSAException&)
{
	BIO* bp = mLoadKeyFile (pemFilePath);

	if (m_Rsa != NULL)
	{
	    RSA_free (m_Rsa);
	}

	m_Rsa = PEM_read_bio_RSAPrivateKey (bp, NULL, 0, NULL);

	if ( ! IsValidPrivateKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	BIO_free (bp);
}*/

/*void RsaUtil::SetPublicKey_PEM2 (
		  const Glib::ustring& pemFilePath
		, const Glib::ustring& passPhrase)
throw (const Smartmatic::System::Exception::RSAException&)
{
	BIO* bp = mLoadKeyFile (pemFilePath);

	if (m_Rsa != NULL)
		RSA_free (m_Rsa);

	m_Rsa = PEM_read_bio_RSAPublicKey (bp, NULL, 0, NULL);

	if ( ! IsValidPublicKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	BIO_free (bp);
}*/

/*void RsaUtil::SetPrivateKey_PKCS122 (
		  const Glib::ustring& certPath
		, const Glib::ustring& passPhrase )
throw (const Smartmatic::System::Exception::RSAException&)
{
	EVP_PKEY *pkey;
	std::string pass = passPhrase.raw ();
	std::string path = certPath.raw ();

	if (m_Rsa != NULL)
	{
	    RSA_free (m_Rsa);
	}

	try
	{
		CryptoPKCS12 p12 (path, pass);
		pkey = p12.getPrimaryKey ();

		m_Rsa = EVP_PKEY_get1_RSA (pkey);

		if ( ! IsValidPrivateKey () )
		{
			throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
		}
	}
	catch (CryptoException e)
	{
		throw RSAException (e.what (), e.what (), logger);
	}
}*/

/*void RsaUtil::SetPublicKey_X509_PKCS122 (
		  const Glib::ustring& certPath
		, const Glib::ustring& passPhrase)
throw (const Smartmatic::System::Exception::RSAException&)
{
	std::string pass = passPhrase.raw ();
	std::string path = certPath.raw ();

	try
	{
		CryptoPKCS12 p12 (path, pass);
		mSetKeyFromX509 (p12.getCertified ());
	}
	catch (CryptoException e)
	{
		throw RSAException (e.what (), e.what (), logger);
	}
}*/

/*void RsaUtil::SetPublicKey_X509_Pem2 (const Glib::ustring& certPath)
throw (const Smartmatic::System::Exception::RSAException&)
{
	BIO *bp;
	X509* x;

	bp = mLoadKeyFile (certPath);
	x = PEM_read_bio_X509_AUX (bp, NULL, NULL, NULL);

	if (x == NULL)
	{
		throw RSAException (_(IOCERT_ERR_MSG), N_(IOCERT_ERR_MSG), logger);
	}

	mSetKeyFromX509 (x);

	X509_free (x);
	BIO_free (bp);
}*/

/*void RsaUtil::SetPublicKey_X509_Der2 (const Glib::ustring& certPath)
throw (const Smartmatic::System::Exception::RSAException&)
{
	BIO* bp;
	X509* x;

	bp = mLoadKeyFile (certPath);
	x = d2i_X509_bio (bp, NULL);

	if (x == NULL)
	{
		throw RSAException (_(IOCERT_ERR_MSG), N_(IOCERT_ERR_MSG), logger);
	}

	mSetKeyFromX509 (x);

	X509_free (x);
	BIO_free (bp);
}*/


//============================================================================//
//============================== Interface ===================================//
//============================================================================//


bool RsaUtil::IsValidPublicKey () const
{
	bool is_public = false;

	// TODO if the class allow m_Rsa to have NULL value on a given time the semantic of this method is broken
	// This should never happen since all errors on loading m_Rsa are handled but m_Rsa can still be NULL right after default constructor instantiation
	EVP_PKEY * pkey = SignatureAlgorithm::GetPublicKey();

	if(pkey != NULL)
	{
		RSA * rsakey = EVP_PKEY_get1_RSA (pkey);

		if (rsakey != NULL)
		{
			is_public =
					rsakey->d == NULL
					&& rsakey->p == NULL
					&& rsakey->q == NULL
					&& rsakey->dmp1 == NULL
					&& rsakey->dmq1 == NULL
					&& rsakey->iqmp == NULL;
			RSA_free(rsakey);
		}

	}
	return is_public;
}

bool RsaUtil::IsValidPrivateKey () const
throw (const Smartmatic::System::Exception::RSAException&)
{
	int integrity;

	EVP_PKEY * pkey = SignatureAlgorithm::GetPrivateKey();

	if(pkey != NULL)
	{
		RSA * rsakey = EVP_PKEY_get1_RSA (pkey);
		if (rsakey != NULL)
		{
			if ( IsValidPublicKey () )
			{
				RSA_free(rsakey);
				return false;
			}
			else if ( (integrity = RSA_check_key (rsakey)) < 0 )
			{
				RSA_free(rsakey);
				throw RSAException (_(KCHECK_ERR_MSG), N_(KCHECK_ERR_MSG), logger);
			}
			RSA_free(rsakey);
			return (integrity == 1);
		}
	}


	return false;

}



SafeBuffer RsaUtil::PublicEncrypt(const SafeBuffer& plaintext)
throw (const Smartmatic::System::Exception::RSAException&)
{
	return PublicEncrypt (plaintext.GetData(), plaintext.GetSize ());
}

SafeBuffer RsaUtil::PublicEncrypt(
		  const unsigned char *plaintext
		, int plaintTextLen)
throw (const Smartmatic::System::Exception::RSAException&)
{

	unsigned char* cphtext_buff;
	int cphtext_len;

	if ( ! IsValidPrivateKey () && ! IsValidPublicKey ())
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if (plaintext == NULL)
	{
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	RSA * rsakey = EVP_PKEY_get1_RSA (SignatureAlgorithm::GetPublicKey());
	// Check whether buffer is out of bounds for the current padding
	if ( ! mCheckPadding (plaintTextLen, rsakey) )
	{
		throw RSAException (_(PADING_ERR_MSG), N_(PADING_ERR_MSG), logger);
	}

	/*
	 * Pseudo random number generator must be seeded before encryption. If
	 * system supports /dev/urandom this is done transparently. Here we are
	 * checking if PRNG is seeded with enough entropy in order to proceed
	 * properly. If it is not, the PRNG must be explicitly seeded.
	 */
	if ( ! RAND_status () )
	{
		throw RSAException (_(CIPHER_ERR_MSG), N_(CIPHER_ERR_MSG), logger);
	}




	cphtext_buff = (unsigned char*) OPENSSL_malloc (RSA_size(rsakey));

	if (cphtext_buff == NULL)
	{
		RSA_free(rsakey);
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	cphtext_len = RSA_public_encrypt (
			  plaintTextLen
			, plaintext
			, cphtext_buff
			, rsakey
			, mGetNativePadding ());

	RSA_free(rsakey);

	if (cphtext_len < 0)
	{
		throw RSAException (_(CIPHER_ERR_MSG), N_(CIPHER_ERR_MSG), logger);
	}

	SafeBuffer cipher_text (cphtext_buff, cphtext_len);

	return cipher_text;
}



SafeBuffer RsaUtil::PrivateDecrypt(const SafeBuffer& ciphertext)
throw (const Smartmatic::System::Exception::RSAException&)
{
	return PrivateDecrypt (ciphertext.GetData(), ciphertext.GetSize ());
}

SafeBuffer RsaUtil::PrivateDecrypt(
		  const unsigned char *ciphertext
		, int cipherTextLen)
throw (const Smartmatic::System::Exception::RSAException&)
{
	unsigned char* plaintext_buff;
	int plaintext_len;

	if ( ! IsValidPrivateKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if (ciphertext == NULL)
	{
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}
	RSA * rsakey = EVP_PKEY_get1_RSA (SignatureAlgorithm::GetPrivateKey());

	plaintext_buff = (unsigned char*) OPENSSL_malloc (RSA_size(rsakey));

	if (plaintext_buff == NULL)
	{
		RSA_free(rsakey);
		throw RSAException(_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	plaintext_len = RSA_private_decrypt (
			  cipherTextLen
			, ciphertext
			, plaintext_buff
			, rsakey
			, mGetNativePadding ());
	RSA_free(rsakey);
	if (plaintext_len < 0)
	{
		throw RSAException (_(CIPHER_ERR_MSG), N_(CIPHER_ERR_MSG), logger);
	}

	SafeBuffer plain_text (plaintext_buff, plaintext_len);

	return plain_text;
}



SafeBuffer RsaUtil::PrivateEncrypt(const SafeBuffer& plaintext)
throw (const Smartmatic::System::Exception::RSAException&)
{
	return PrivateEncrypt (plaintext.GetData(), plaintext.GetSize ());
}

SafeBuffer RsaUtil::PrivateEncrypt(
		  const unsigned char *plaintext
		, int plaintTextLen)
throw (const Smartmatic::System::Exception::RSAException&)
{
	unsigned char* cphtext_buff;
	int cphtext_len, pad;

	if ( ! IsValidPrivateKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if (plaintext == NULL)
	{
		throw RSAException(_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	pad = mGetNativePadding ();

	if ( pad != RSA_PKCS1_PADDING && pad != RSA_NO_PADDING ) // openssl doesn't allow private encryption with other padding than these two
	{
		throw RSAException (_(PADING_ERR_MSG), N_(PADING_ERR_MSG), logger);
	}

	RSA * rsakey = EVP_PKEY_get1_RSA (SignatureAlgorithm::GetPrivateKey());

	cphtext_buff = (unsigned char*) OPENSSL_malloc (RSA_size(rsakey));

	if (cphtext_buff == NULL)
	{
		RSA_free(rsakey);
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	cphtext_len = RSA_private_encrypt (
			  plaintTextLen
			, plaintext
			, cphtext_buff
			, rsakey
			, mGetNativePadding ());
	RSA_free(rsakey);
	if (cphtext_len < 0)
	{
		throw RSAException (_(CIPHER_ERR_MSG), N_(CIPHER_ERR_MSG), logger);
	}

	SafeBuffer cipher_text (cphtext_buff, cphtext_len);

	return cipher_text;
}



SafeBuffer RsaUtil::PublicDecrypt(const SafeBuffer& ciphertext)
throw (const Smartmatic::System::Exception::RSAException&)
{
	return PublicDecrypt (ciphertext.GetData(), ciphertext.GetSize ());
}

SafeBuffer RsaUtil::PublicDecrypt(
		  const unsigned char *ciphertext
		, int cipherTextLen)
throw (const Smartmatic::System::Exception::RSAException&)
{
	unsigned char* plaintext_buff;
	int plaintext_len;

	if ( ! IsValidPrivateKey () && ! IsValidPublicKey ())
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if ( ciphertext == NULL )
	{
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	RSA * rsakey = EVP_PKEY_get1_RSA (SignatureAlgorithm::GetPublicKey());

	plaintext_buff = (unsigned char*) OPENSSL_malloc (RSA_size(rsakey) - 11);

	if (plaintext_buff == NULL)
	{
		RSA_free(rsakey);
		throw RSAException (_(BUFINV_ERR_MSG), N_(BUFINV_ERR_MSG), logger);
	}

	plaintext_len = RSA_public_decrypt (
			  cipherTextLen
			, ciphertext
			, plaintext_buff
			, rsakey
			, mGetNativePadding ());
	RSA_free(rsakey);
	if (plaintext_len < 0)
	{
		throw RSAException (_(CIPHER_ERR_MSG), N_(CIPHER_ERR_MSG), logger);
	}

	SafeBuffer plain_text (plaintext_buff, plaintext_len);

	return plain_text;
}


void RsaUtil::SignData (
		const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind)
throw (const Smartmatic::System::Exception::RSAException&)
{

	int pad = mGetNativePadding ();

	//check conditions
	if ( ! IsValidPrivateKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if ( pad != RSA_PKCS1_PADDING && pad != RSA_NO_PADDING ) // openssl doesn't allow private encryption with other padding than these two
	{
		throw RSAException (_(PADING_ERR_MSG), N_(PADING_ERR_MSG), logger);
	}

	//compute hash
	SafeBuffer hash = MsgDigestUtil::Digest(plainData,dataLen,hashKind);
	//encrypt hash
	Smartmatic::System::SafeBuffer res = PrivateEncrypt(hash.GetData(), hash.GetSize());
	outSafeBuffer.AddData(res);
	//return
}


void RsaUtil::SignData ( Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind)
throw (const Smartmatic::System::Exception::RSAException&)
{
	SignData(inSafeBuffer.GetData(), inSafeBuffer.GetSize(), outSafeBuffer, hashKind);
}


bool RsaUtil::VerifySignature (
		const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind)
throw (const Smartmatic::System::Exception::RSAException&)
{
	bool retVal = true;

	int pad = mGetNativePadding ();

	//check conditions
	if ( ! IsValidPublicKey() )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}

	if ( pad != RSA_PKCS1_PADDING && pad != RSA_NO_PADDING ) // openssl doesn't allow private encryption with other padding than these two
	{
		throw RSAException (_(PADING_ERR_MSG), N_(PADING_ERR_MSG), logger);
	}

	//compute hash
	SafeBuffer hash = MsgDigestUtil::Digest(plainData,dataLen,hashKind);

	//decrypt signature
	Smartmatic::System::SafeBuffer res = PublicDecrypt(signature);

	//compare hash
	if(memcmp(hash.GetData(), res.GetData(), hash.GetSize()) != 0)
	{
		retVal = 0;
	}

	return retVal;
}


bool RsaUtil::VerifySignature (
		Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind)
throw (const Smartmatic::System::Exception::RSAException&)
{
	return VerifySignature(inSafeBuffer.GetData(), inSafeBuffer.GetSize(),signature, hashKind );
}


//============================================================================//
//============================== Auxiliars ===================================//
//============================================================================//

/*void RsaUtil::mSetKeyFromX509 (X509* x)
throw (const Smartmatic::System::Exception::RSAException&)
{
	EVP_PKEY* pkey;

	pkey = X509_get_pubkey (x);

	if (m_Rsa != NULL)
		RSA_free (m_Rsa);

	m_Rsa = EVP_PKEY_get1_RSA (pkey);

	EVP_PKEY_free (pkey);

	if ( ! IsValidPublicKey () )
	{
		throw RSAException (_(RSAKEY_ERR_MSG), N_(RSAKEY_ERR_MSG), logger);
	}
}*/

/*BIO* RsaUtil::mLoadKeyFile (const Glib::ustring& certPath)
throw (const Smartmatic::System::Exception::RSAException&)
{
	BIO *cert;

	if ((cert = BIO_new(BIO_s_file())) == NULL)
	{
		throw RSAException (_(IOCERT_ERR_MSG), N_(IOCERT_ERR_MSG), logger);
	}

	if ( BIO_read_filename (cert, certPath.c_str ()) <= 0)
	{
		throw RSAException (_(IOCERT_ERR_MSG), N_(IOCERT_ERR_MSG), logger);
	}

	return cert;
}*/

bool RsaUtil::mCheckPadding (int buffLen,  RSA* rsakey)
{
	bool retVal = false;

	if(rsakey == NULL )
		return retVal;

	switch (m_Padding)
	{
	case RSAPAD_PKCS1:
		retVal = buffLen < (RSA_size (rsakey) - 11);
		break;
	case RSAPAD_OAEP:
		retVal = buffLen < (RSA_size (rsakey) - 41);
		break;
	case RSAPAD_SSL:
		retVal = buffLen < (RSA_size (rsakey) - 11);
		break;
	case RSAPAD_RAW:
		retVal = buffLen == RSA_size (rsakey);
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
}

int RsaUtil::mGetNativePadding ()
{
	switch (m_Padding)
	{
	case RSAPAD_PKCS1:
		return RSA_PKCS1_PADDING;
	case RSAPAD_OAEP:
		return RSA_PKCS1_OAEP_PADDING;
	case RSAPAD_SSL:
		return RSA_SSLV23_PADDING;
	case RSAPAD_RAW:
		return RSA_NO_PADDING;
	default:
	    return RSA_NO_PADDING;
	}
}
