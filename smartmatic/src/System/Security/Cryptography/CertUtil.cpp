/**
 * @file CertUtil.cpp
 * @brief Body class utility certified manager
 * @date 10/11/2011
 * @author Freddy Gomez
 */

#include "System/Security/Cryptography/CertUtil.h"
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/engine.h>
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

using namespace Smartmatic::Log;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::IO;

/**
 * @brief Open ssl prototypes
 */
typedef struct pw_cb_data
{
  const void *password; ///< password
  const char *prompt_info; ///< info
} PW_CB_DATA; ///< Open ssl prototypes

/**
 * @brief method pass callback
 * @param buf buffer data
 * @param bufsiz buffer size
 * @param verify flag
 * @param cb_tmp struct data
 * @return status
 */
int passw_callback(char *buf, int bufsiz, int verify, PW_CB_DATA *cb_tmp);

ISMTTLog* CertUtil::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CertUtil",GETTEXT_PACKAGE);

CertUtil::CertUtil()
{

}

CertUtil::~CertUtil()
{

}

EVP_PKEY * CertUtil::LoadCertificate(std::string certPath, std::string certPass, CertFileFormat format)
{
	BIO * key = NULL;
	EVP_PKEY * pkey = NULL;
	PW_CB_DATA cb_data;

	if (!File::canOpenFile(certPath))
	{
		logger->Debug("Error load certified file " + certPath);
		return pkey;
	}

	key = BIO_new(BIO_s_file());

	if (key == NULL)
	{
		logger->Debug("Error load memory key");
		return pkey;
	}

	if (BIO_read_filename(key, certPath.c_str()) <= 0)
	{
		logger->Debug("Error read key in certified file " + certPath);
		BIO_free(key);
		return pkey;
	}

	switch(format)
	{
		case CertUtil::CertFormat_DER:
			pkey = d2i_PrivateKey_bio(key, NULL);
			break;

		case CertUtil::CertFormat_PEM:
			cb_data.password = certPass.c_str();
			cb_data.prompt_info = certPath.c_str();
			pkey = PEM_read_bio_PrivateKey(key, NULL, (pem_password_cb *)passw_callback, &cb_data);
			break;

		default:
			logger->Debug("Error format not support");
			break;
	}

	if (!pkey)
	{
		logger->Debug("Error load private key");
	}

	BIO_free(key);

	//HOW TO --- EVP_PKEY_free(key);
	return pkey;
}

X509 * CertUtil::LoadCertificate(std::string certPath, CertUtil::CertFileFormat format)
{
	X509 * x = NULL;
	BIO * cert = NULL;

	if (!File::canOpenFile(certPath))
	{
		logger->Debug("Error load certified file " + certPath);
		return x;
	}

	cert = BIO_new(BIO_s_file());

	if (cert == NULL)
	{
		logger->Debug("Error load memory for cert");
		return x;
    }

	if (BIO_read_filename(cert, certPath.c_str()) <= 0)
	{
		logger->Debug("Error opening target cert");
		BIO_free(cert);
		return x;
	}

	switch(format)
	{
		case CertUtil::CertFormat_DER:
			x = d2i_X509_bio(cert, NULL);
			break;
		case CertUtil::CertFormat_PEM:
			x = PEM_read_bio_X509_AUX(cert,NULL, (pem_password_cb *)passw_callback, NULL);
			break;
		default:
		  logger->Debug("bad input format specified for target cert");
		  break;
	}

	if (!x)
	{
		logger->Debug("Unable to load cert");
	}

	BIO_free(cert);

	// HOW TO --- X509_free(x);
	return x;
}

/*Open SSL source*/
int passw_callback(char *buf, int bufsiz, int verify, PW_CB_DATA *cb_tmp)
{
	int res = 0;
	const char * password = NULL;
	PW_CB_DATA * cb_data = (PW_CB_DATA *)cb_tmp;

	if (cb_data)
	{
		if (cb_data->password)
		{
			password = (const char *)cb_data->password;
		}
	}

	if (password)
	{
		res = strlen(password);
		if (res > bufsiz)
		{
			res = bufsiz;
		}
		memcpy(buf, password, res);
	}

	return res;
}
