/**
 * @file SignatureAlgorithm.cpp
 * @brief Body class signature algorithm
 * @date 10/11/2011
 * @author Freddy Gomez
 */

#include <openssl/evp.h>
#include <openssl/ossl_typ.h>
#include <openssl/rsa.h>
#include <openssl/ecdsa.h>
#include "System/Security/Cryptography/SignatureAlgorithm.h"
#include "System/Security/Cryptography/RsaUtil.h"
#include "System/Security/Cryptography/ECDSASigner.h"
#include "System/Exception/SignatureAlgorithmKeyException.h"
#include <Log/SMTTLogManager.h>
#include <System/Security/Cryptography/CryptoPKCS12.hxx>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security::Cryptography;

Smartmatic::Log::ISMTTLog* SignatureAlgorithm::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.SignatureAlgorithm",GETTEXT_PACKAGE);;/**logger*/

SignatureAlgorithm::SignatureAlgorithm() {
	// TODO Auto-generated constructor stub
	private_key = NULL;
	public_key = NULL;
}

SignatureAlgorithm::~SignatureAlgorithm() {

	if(private_key != NULL)
	{
		EVP_PKEY_free(private_key);
		private_key = NULL;
	}

	if(public_key != NULL)
	{
		EVP_PKEY_free(public_key);
		public_key = NULL;
	}
}


	void SignatureAlgorithm::SetPrivateKey_PKCS12 (
			 std::string& p12FilePath
			,  std::string& passPhrase)
	{
		CryptoPKCS12 aux (p12FilePath, passPhrase);
		EVP_PKEY * tmp;
		tmp = aux.getPrimaryKey();

		if(tmp != NULL)
		{
			SetPrivateKey(tmp);
		}
	}


	void SignatureAlgorithm::SetPublicKey_FromCert (const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format)
	{
		EVP_PKEY* key = GetPubliKeyFromCert(certFilePath,passPhrase, format);
		SetPublicKey(key);
	}


	EVP_PKEY* SignatureAlgorithm::GetPubliKeyFromCert(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format)
	{
		X509 * cert =NULL;
		EVP_PKEY* key;
		CryptoPKCS12 aux;

		if(format != CertUtil::CertFormat_PKCS12)
		{
			cert = CertUtil::LoadCertificate(certFilePath, format);
		}
		else
		{
			std::string path = certFilePath;
			std::string pass = passPhrase;
			aux.Load(path, pass);
			cert = aux.getCertified();
		}

		if(cert == NULL)
		{
			throw SignatureAlgorithmKeyException(_("Smartmatic.System.Security.Cryptography.SignatureAlgorithm.ErrorLoadCertifiedX509"),
					N_("Smartmatic.System.Security.Cryptography.SignatureAlgorithm.ErrorLoadCertifiedX509"), logger);
		}


		key = X509_get_pubkey(cert);

		if(format != CertUtil::CertFormat_PKCS12)
		{
			X509_free(cert);
		}
		//otherwise the destructor of the p12 container get rid of it

		return key;
	}

	void SignatureAlgorithm::SetPrivateKey(EVP_PKEY* pkey)
	{
		if(private_key != NULL)
		{
			EVP_PKEY_free(private_key);
		}
		private_key = EVP_PKEY_new();
		private_key->type = pkey->type;
		if(pkey->type == EVP_PKEY_RSA || pkey->type == EVP_PKEY_RSA2)
		{
			struct rsa_st*   key = EVP_PKEY_get1_RSA (pkey);
			EVP_PKEY_set1_RSA(private_key,key);
			RSA_free(key);
		}
		else if (pkey->type == EVP_PKEY_EC)
		{
			EC_KEY *   key = EVP_PKEY_get1_EC_KEY (pkey);
			EVP_PKEY_set1_EC_KEY(private_key,key);
			EC_KEY_free(key);
		}
		EVP_PKEY_copy_parameters(private_key,pkey );
	}
	void SignatureAlgorithm::SetPublicKey(EVP_PKEY* pkey)
	{
		if(public_key != NULL)
		{
			EVP_PKEY_free(public_key);
		}
		public_key = pkey;
	}
	SignatureAlgorithm* SignatureAlgorithm::CreateForSign(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase)
	{

		std::string path = certFilePath;
		std::string pass = passPhrase;

		CryptoPKCS12 aux(path, pass);
		EVP_PKEY * tmp;
		tmp = aux.getPrimaryKey();

		if(tmp != NULL)
		{
			SignatureAlgorithm* retVal = CreateForKeyType(tmp);
			retVal->SetPrivateKey(tmp);
			return retVal;
		}

		return NULL;
	}

	SignatureAlgorithm* SignatureAlgorithm::CreateForSign(EVP_PKEY * tmp)
	{
		if(tmp != NULL)
		{
			SignatureAlgorithm* retVal = CreateForKeyType(tmp);
			retVal->SetPrivateKey(tmp);
			return retVal;
		}

		return NULL;
	}

	SignatureAlgorithm* SignatureAlgorithm::CreateForVerify(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format)
	{

		EVP_PKEY * tmp = GetPubliKeyFromCert(certFilePath,passPhrase, format);
		if(tmp != NULL)
		{
			SignatureAlgorithm* retVal = CreateForKeyType(tmp);
			retVal->SetPublicKey(tmp);
			return retVal;
		}
		return NULL;
	}


	SignatureAlgorithm* SignatureAlgorithm::CreateForKeyType(EVP_PKEY* pkey)
	{
		SignatureAlgorithm* retVal;
		switch (pkey->type)
				{
			case EVP_PKEY_RSA:
			case EVP_PKEY_RSA2:
				retVal =  new RsaUtil();
			break;
			case EVP_PKEY_DSA:
			case EVP_PKEY_DSA1:
			case EVP_PKEY_DSA2:
			case EVP_PKEY_DSA3:
			case EVP_PKEY_DSA4:
				retVal = NULL;
				break;
			case EVP_PKEY_EC:
				retVal =  new ECDSASigner();
				break;
			default:
				retVal = NULL;
				break;
				}
		return retVal;
	}


	EVP_PKEY* SignatureAlgorithm::GetPublicKey() const
	{
		return public_key;
	}
	EVP_PKEY* SignatureAlgorithm::GetPrivateKey() const
	{
		return private_key;
	}

