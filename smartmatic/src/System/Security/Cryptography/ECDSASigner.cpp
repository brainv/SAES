/*
 * ECDSASigner.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: fgomez
 */

#include "ECDSASigner.h"
#include <openssl/bn.h>
#include <Log/SMTTLogManager.h>
#include "System/Exception/ECDSException.h"
#include <glibmm.h>

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

using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Security::Cryptography;


Smartmatic::Log::ISMTTLog* ECDSASigner::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.ECDSASigner",GETTEXT_PACKAGE);;/**logger*/

ECDSASigner::ECDSASigner() {
	// TODO Auto-generated constructor stub

}

ECDSASigner::~ECDSASigner() {
	// TODO Auto-generated destructor stub
}

SignatureAlgorithm::SignatureAlgorithmType ECDSASigner::GetType() const
{
	return SignatureAlgorithm::ECDSA_SIGNATURE;
}

void ECDSASigner::SignData (
		const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind)
{

	SafeBuffer hash = MsgDigestUtil::Digest(plainData,dataLen,hashKind);

	EVP_PKEY * pkey = GetPrivateKey();
	EC_KEY * key = pkey->pkey.ec;

	ECDSA_SIG * dsa_sig;
	dsa_sig = ECDSA_do_sign(hash.GetData(), hash.GetSize(), key);

	unsigned char rawSigBufR[256];
	unsigned char rawSigBufS[256];
	unsigned int rawLenR, rawLenS;

	if (dsa_sig == NULL) {

		throw ECDSException(_("Smartmatic.System.Security.Cryptography.ECDSASigner.CannotComputeSignature"),
				N_("Smartmatic.System.Security.Cryptography.ECDSASigner.CannotComputeSignature"), logger);

	}

	const BIGNUM *bnpkey = EC_KEY_get0_private_key(key);
	unsigned int keySize = BN_num_bytes(bnpkey);

	rawLenR = BN_bn2bin(dsa_sig->r, rawSigBufR);
	rawLenS = BN_bn2bin(dsa_sig->s, rawSigBufS);

	for (int i = 0; i < (int)(keySize - rawLenR); i++, outSafeBuffer.push_back(0x00));
	//copy r
	outSafeBuffer.AddData(rawSigBufR, rawLenR);

	for (int i = 0; i < (int)(keySize - rawLenS); i++, outSafeBuffer.push_back(0x00));
	//copy s
	outSafeBuffer.AddData(rawSigBufS, rawLenS);

	ECDSA_SIG_free(dsa_sig);
}


void ECDSASigner::SignData ( Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind)
{
	SignData(inSafeBuffer.GetData(), inSafeBuffer.GetSize(),outSafeBuffer, hashKind );
}

bool ECDSASigner::VerifySignature (
		const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind)
{
	//compute hash
	SafeBuffer hash = MsgDigestUtil::Digest(plainData,dataLen,hashKind);
	EC_KEY    *key = GetPublicKey()->pkey.ec;

	ECDSA_SIG * dsa_sig = ECDSA_SIG_new();
	dsa_sig->r = BN_bin2bn(signature.GetData(), signature.GetSize() / 2, NULL);
	dsa_sig->s = BN_bin2bn(signature.GetData() + signature.GetSize() / 2, signature.GetSize() / 2, NULL);

	// Now we have a signature and a key - lets check
	int err = ECDSA_do_verify(hash.GetData(), hash.GetSize(), dsa_sig, key);

	ECDSA_SIG_free(dsa_sig);

	if (err < 0) {

		return false;
	}
	return true;
}

bool ECDSASigner::VerifySignature (
		Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind)
{
	return VerifySignature(inSafeBuffer.GetData(), inSafeBuffer.GetSize(),signature, hashKind );
}

bool ECDSASigner::IsValidPublicKey () const
{
	return true;
}

bool ECDSASigner::IsValidPrivateKey () const
{
	return true;
}

