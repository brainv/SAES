/**
 * @file SecurityBase.cxx
 * @brief Body class security base
 * @date 21/03/2012
 * @author Yadickson Soto
 */

#include "SecurityBase.hxx"
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

using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::Log;

ISMTTLog* SecurityBase::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.SecurityBase",GETTEXT_PACKAGE);

SecurityBase::SecurityBase()
{
    this->cryptoP12 = NULL;
    this->certifiedX509 = NULL;
    this->certPrivateKey = NULL;
}

SecurityBase::~SecurityBase()
{

}


void SecurityBase::loadPKCS12(std::string & secretKey, std::string file)
        throw (CryptoException)
{
    if (cryptoP12)
    {
        delete(cryptoP12);
        cryptoP12 = NULL;
    }

    this->cryptoP12 = new Cryptography::CryptoPKCS12(file, secretKey);
}

void SecurityBase::loadCertifiedPKey(std::string file,
		std::string pass,
		CertUtil::CertFileFormat format)
        throw (CryptoException)
{
    if (certPrivateKey)
    {
    	EVP_PKEY_free(certPrivateKey);
    	certPrivateKey = NULL;
    }

    certPrivateKey = CertUtil::LoadCertificate(file, pass, format);

    if (certPrivateKey == NULL)
    {
        throw CryptoException(_("Smartmatic.System.Security.SecurityBase.ErrorLoadCertifiedPKey"),
                N_("Smartmatic.System.Security.SecurityBase.ErrorLoadCertifiedPKey"), logger);
    }
}

void SecurityBase::loadCertifiedX509(std::string file,
		CertUtil::CertFileFormat format)
        throw (CryptoException)
{
    if (certifiedX509)
    {
        X509_free(certifiedX509);
        certifiedX509 = NULL;
    }

    certifiedX509 = CertUtil::LoadCertificate(file, format);

    if (certifiedX509 == NULL)
    {
        throw CryptoException(_("Smartmatic.System.Security.SecurityBase.ErrorLoadCertifiedX509"),
                N_("Smartmatic.System.Security.SecurityBase.ErrorLoadCertifiedX509"), logger);
    }
}
