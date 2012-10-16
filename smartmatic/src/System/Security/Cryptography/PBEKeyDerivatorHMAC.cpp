/**
 * @file PBEKeyDerivatorHMAC.cpp
 * @brief Body class PBE Key derivator hmac
 * @date  05/04/2011
 * @author Freddy Gomez
 */
#include <string.h>
#include "System/Security/Cryptography/PBEKeyDerivatorHMAC.h"
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/hmac.h>

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


using namespace Smartmatic::System::Security::Cryptography;

#ifdef USE_PKCS5_PBKDF2_HMAC

static  int PKCS5_PBKDF2_HMAC(const char *pass, int passlen, const unsigned char *salt,
		int saltlen, int iter, const EVP_MD *digest, int keylen,
		unsigned char *out);

#endif

PBEKeyDerivatorHMAC::PBEKeyDerivatorHMAC() :
	mSaltValue(NULL), mSaltSize(0)
{
	// TODO Auto-generated constructor stub

}

PBEKeyDerivatorHMAC::~PBEKeyDerivatorHMAC()
{
  // TODO Auto-generated destructor stub
  if(mSaltValue)
    g_free(mSaltValue);
}

void PBEKeyDerivatorHMAC::SetSalt(const unsigned char * salt, int saltLen)
{
	if (mSaltValue)
	  g_free(mSaltValue);

	mSaltValue = static_cast<unsigned char*> (g_malloc(saltLen));
	memcpy(mSaltValue, salt, saltLen);
	mSaltSize = saltLen;

}

void PBEKeyDerivatorHMAC::SetSalt(const Glib::ustring& salt)
{
	char buffer[salt.bytes()];

	unsigned char* ptr = (unsigned char*) buffer;

	salt.copy(buffer, salt.bytes(),0 );

	SetSalt(const_cast<const unsigned char*> (ptr), salt.size());
}

void PBEKeyDerivatorHMAC::GenerateKey(
		  const Glib::ustring& passPhrase
		, unsigned char * outKey
		, int keyLen
		, int iterations
		, DigestAlgType mdAlg)
{
        int passSize =passPhrase.bytes() ;
	const EVP_MD * digest = DigestAlgorithmLookup::LookupDigest(mdAlg);
	char buffer[passSize];
	passPhrase.copy(buffer, passSize,0 );

	if (PKCS5_PBKDF2_HMAC(buffer, passSize, mSaltValue, mSaltSize,
			iterations, digest, keyLen, outKey) == 0)
	{
		//TODO: Error throw and exception
	}
}

#ifdef USE_PKCS5_PBKDF2_HMAC

/* This is an implementation of PKCS#5 v2.0 password based encryption key
 * derivation function PBKDF2.
 * SHA1 version verified against test vectors posted by Peter Gutmann
 * <pgut001@cs.auckland.ac.nz> to the PKCS-TNG <pkcs-tng@rsa.com> mailing list.
 */
static int PKCS5_PBKDF2_HMAC(
		  const char *pass
		, int passlen
		, const unsigned char *salt
		, int saltlen
		, int iter
		, const EVP_MD *digest
		, int keylen
		, unsigned char *out)
{
	unsigned char digtmp[EVP_MAX_MD_SIZE], *p, itmp[4];
	int cplen, j, k, tkeylen, mdlen;
	unsigned long i = 1;
	HMAC_CTX hctx;

	mdlen = EVP_MD_size(digest);
	if (mdlen < 0)
		return 0;

	HMAC_CTX_init(&hctx);
	p = out;
	tkeylen = keylen;
	if (!pass)
		passlen = 0;
	else if (passlen == -1)
		passlen = strlen(pass);
	while (tkeylen)
	{
		if (tkeylen > mdlen)
			cplen = mdlen;
		else
			cplen = tkeylen;
		/* We are unlikely to ever use more than 256 blocks (5120 bits!)
		 * but just in case...
		 */
		itmp[0] = (unsigned char) ((i >> 24) & 0xff);
		itmp[1] = (unsigned char) ((i >> 16) & 0xff);
		itmp[2] = (unsigned char) ((i >> 8) & 0xff);
		itmp[3] = (unsigned char) (i & 0xff);
		HMAC_Init_ex(&hctx, pass, passlen, digest, NULL);
		HMAC_Update(&hctx, salt, saltlen);
		HMAC_Update(&hctx, itmp, 4);
		HMAC_Final(&hctx, digtmp, NULL);
		memcpy(p, digtmp, cplen);
		for (j = 1; j < iter; j++)
		{
			HMAC(digest, pass, passlen, digtmp, mdlen, digtmp, NULL);
			for (k = 0; k < cplen; k++)
				p[k] ^= digtmp[k];
		}
		tkeylen -= cplen;
		i++;
		p += cplen;
	}

	HMAC_CTX_cleanup(&hctx);

	/*#ifdef DEBUG_PKCS5V2
	 fprintf(stderr, "Password:\n");
	 h__dump (pass, passlen);
	 fprintf(stderr, "Salt:\n");
	 h__dump (salt, saltlen);
	 fprintf(stderr, "Iteration count %d\n", iter);
	 fprintf(stderr, "Key:\n");
	 h__dump (out, keylen);
	 #endif*/

	return 1;
}

#endif
