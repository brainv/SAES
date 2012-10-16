/*
 * SignatureAlgorithm.h
 *
 *  Created on: Nov 10, 2011
 *      Author: fgomez
 */

#ifndef SIGNATUREALGORITHM_H_
#define SIGNATUREALGORITHM_H_


#include "System/SafeBuffer.h"
//#include "System/Exception/RSAException.h"
#include "System/Security/Cryptography/MsgDigestUtil.h"
#include "System/Security/Cryptography/CertUtil.h"

namespace Smartmatic {
namespace System {
namespace Security {
namespace Cryptography {


typedef enum CertFileFormatEnum
{
	RSACERT_TEXT,
	RSACERT_PEM,
	RSACERT_PKCS12,
	RSACERT_PEMRSA,
	RSACERT_ASN1RSA

} CertFileFormatEnumType;

class SignatureAlgorithm {
public:

	/**
	 * @brief Format of X509 certificate.
	 */



	typedef enum signature_algorithm_typ
	{
		RSA_SIGNATURE,
		ECDSA_SIGNATURE,
	}SignatureAlgorithmType;

	SignatureAlgorithm();
	virtual ~SignatureAlgorithm();


	static SignatureAlgorithm* CreateForSign(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase);
	static SignatureAlgorithm* CreateForVerify(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format);
	static SignatureAlgorithm* CreateForSign(EVP_PKEY * tmp);

	/**
	 * @brief Signature calculation.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param plainData: pointer to data
	 * @param dataLen: data lenght
	 * @param outSafeBuffer: output buffer
	 * @param hash: hash algorithm to use.
	 *
	 *
	 */
	virtual void SignData (
			const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) = 0;


	/**
	 * @brief Signature calculation.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param inSafeBuffer: reference to data
	 * @param outSafeBuffer: output buffer
	 * @param hash: hash algorithm to use.
	 *
	 *
	 */

	virtual void SignData ( Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) = 0;

	/**
	 * @brief Signature calculation.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param plainData: pointer to data
	 * @param dataLen: data lenght
	 * @param signature: to verify
	 * @param hash: hash algorithm to use.
	 * @return: true if validation succeed. Otherwise, false.
	 *
	 */
	virtual bool VerifySignature (
			const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) = 0 ;

	/**
	 * @brief Signature verification.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param inSafeBuffer: reference to data
	 * @param signature: to verify
	 * @param hash: hash algorithm to use.
	 * @return: true if validation succeed. Otherwise, false.
	 *
	 */
	virtual bool VerifySignature (
			Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) = 0;


	/**
	 * @brief Loads the private key contained in a PKCS#12 file.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param certPath: the absolute path to the PKCS#12 file.
	 *
	 */
	void SetPrivateKey_PKCS12 (
			 std::string& p12FilePath
			,  std::string& passPhrase);

	/**
	 * @brief Loads the key information from an X.509 certificate stored with
	 *        PEM format.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @param certPath: the absolute path to the certificate's file.
	 *
	 */
	virtual void SetPublicKey_FromCert (const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format);

	/**
	 * @brief Checks whether a public or private key is currently being used.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @return true if the key hold by this instance for use in cryptographic
	 *         computations is a public key.
	 *
	 */
	virtual bool IsValidPublicKey () const = 0;

	/**
	 * @brief Checks this instance's key for integrity.
	 *
	 * @author fgomez
	 * @date   Nov 10, 2011
	 *
	 * @return false if the key pair or public key hold by this instance is
	 *         invalid or has not been set yet (has a NULL value).
	 *
	 */
	virtual bool IsValidPrivateKey () const = 0;


	virtual SignatureAlgorithmType GetType() const = 0;

protected:

	EVP_PKEY * GetPublicKey() const;
	EVP_PKEY * GetPrivateKey() const;

private:

	static SignatureAlgorithm* CreateForKeyType(EVP_PKEY* pkey);

	static EVP_PKEY* GetPubliKeyFromCert(const Glib::ustring& certFilePath,const Glib::ustring& passPhrase, CertUtil::CertFileFormat format);

	void SetPrivateKey(EVP_PKEY* pkey);
	void SetPublicKey(EVP_PKEY* pkey);

static Smartmatic::Log::ISMTTLog* logger;/**logger*/
EVP_PKEY* private_key;
EVP_PKEY* public_key;

};

} /* namespace Cryptography */
} /* namespace Security */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* SIGNATUREALGORITHM_H_ */


