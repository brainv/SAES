/**
 * @file CryptoAES.cxx
 * @brief Body class for CryptoAES file
 */

#include "CryptoAES.hxx"
#include <string.h>
#include <glibmm.h>
#include <Log/SMTTLogManager.h>
#include <openssl/rand.h>

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
using namespace Smartmatic::System;
using namespace Smartmatic::Log;

ISMTTLog* CryptoAES::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.CryptoAES",GETTEXT_PACKAGE);

CryptoAES::CryptoAES(const EVP_CIPHER * cipherMode)
{
    this->cipherMode = cipherMode;
}

CryptoAES::~CryptoAES()
{

}

void CryptoAES::encryptoDecrypto(SafeBuffer & dataIn,
		SafeBuffer & buffer,
        const unsigned char * key, const unsigned char * iv, int enc, bool pad) throw (CryptoException)
{
    if (key == NULL || cipherMode == NULL)
    {
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    int sizeOut = 0;
    BIO *benc = NULL;
    EVP_CIPHER_CTX *ctx = NULL;

    benc = BIO_new(BIO_f_cipher());

    if (benc == NULL)
    {
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    BIO_get_cipher_ctx(benc, &ctx);

    if (!EVP_CipherInit_ex(ctx, this->cipherMode, NULL, NULL, NULL, enc))
    {
        BIO_free(benc);
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    if(!EVP_CIPHER_CTX_set_padding(ctx, !pad ? 0:1))
    {
        BIO_free(benc);
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    if (!EVP_CipherInit_ex(ctx, NULL, NULL, key, iv, enc))
    {
        BIO_free(benc);
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    unsigned char * dataOut = (unsigned char*) g_malloc(dataIn.GetSize() + 256);

    if (!EVP_CipherUpdate(ctx, dataOut, &sizeOut, dataIn.GetData(), dataIn.GetSize()))
    {
        g_free(dataOut);
        BIO_free(benc);
        throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    int finalSize = 0;
    if(!EVP_CipherFinal_ex(ctx, dataOut + sizeOut, &finalSize))
    {
    	g_free(dataOut);
        BIO_free(benc);
    	throw CryptoException(_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), N_("Smartmatic.System.Security.Cryptography.CryptoAES.ErrorEncryptoData"), logger);
    }

    sizeOut += finalSize;

    buffer.AddData(dataOut, sizeOut);

    g_free(dataOut);
    BIO_free(benc);
}

void CryptoAES::encryptoData(SafeBuffer & dataIn,
		SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv, bool pad) throw (CryptoException)
{
    encryptoDecrypto(dataIn, dataOut, key, iv, 1, pad);
}

void CryptoAES::decryptoData(SafeBuffer & dataIn,
		SafeBuffer & dataOut,
        const unsigned char * key, const unsigned char * iv, bool pad)
        throw (CryptoException)
{
    encryptoDecrypto(dataIn, dataOut, key, iv, 0, pad);
}

const EVP_CIPHER * CryptoAES::getCipher()
{
    return this->cipherMode;
}
