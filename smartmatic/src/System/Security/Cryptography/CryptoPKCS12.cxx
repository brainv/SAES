/**
 * @file CryptoPKCS12.cxx
 * @brief Body class for CryptoPKCS12 file
 */

#include "CryptoPKCS12.hxx"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
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

ISMTTLog* CryptoPKCS12::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CryptoPKCS12",GETTEXT_PACKAGE);

CryptoPKCS12::CryptoPKCS12():
p12(NULL),
pkey(NULL),
cert(NULL),
ca(NULL)
{

}

CryptoPKCS12::CryptoPKCS12(std::string & file, std::string & secretKey)
        throw (CryptoException)
{
//    OpenSSL_add_all_algorithms();

    this->pkey = NULL;
    this->cert = NULL;
    this->p12 = NULL;
    this->ca = NULL;
    Load(file,secretKey);

}


void CryptoPKCS12::Load(std::string & file, std::string & secretKey)
throw (Smartmatic::System::Exception::CryptoException)
{
	FILE *fp;

      if (!(fp = fopen(file.c_str(), "rb")))
      {
          throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorOpenPKCS12File"),
                  N_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorOpenPKCS12File"), logger);
      }

      p12 = d2i_PKCS12_fp(fp, NULL);
      fclose(fp);

      if (!p12)
      {
          throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorReadingPKCS12File"),
                  N_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorReadingPKCS12File"), logger);
      }

      if (!PKCS12_parse(p12, secretKey.c_str(), &pkey, &cert, &ca))
      {
          throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorParsingPKCS12File"),
                  N_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorParsingPKCS12File"), logger);
      }
}
CryptoPKCS12::~CryptoPKCS12()
{
    if (pkey)
    {
        EVP_PKEY_free(pkey);
        pkey = NULL;
    }
    if (cert)
    {
        X509_free(cert);
        cert = NULL;
    }
    if (p12)
    {
        PKCS12_free(p12);
        p12 = NULL;
    }
}

EVP_PKEY * CryptoPKCS12::getPrimaryKey() throw (CryptoException)
{
    if (pkey)
    {
        return pkey;
    }

    throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorPrimaryKeyNull"),
            N_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorPrimaryKeyNull"), logger);
}

X509 * CryptoPKCS12::getCertified() throw (CryptoException)
{
    if (cert)
    {
        return cert;
    }

    throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorCertifiedNull"), N_("Smartmatic.System.Security.Cryptography.CryptoPKCS12.ErrorCertifiedNull"), logger);
}

STACK_OF(X509) * /**<Certificates authorities*/
		CryptoPKCS12::getCertificatesAuthorities()
{
	return ca;
}
