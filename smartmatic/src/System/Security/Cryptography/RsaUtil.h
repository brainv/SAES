/*
 * RsaUtil.h
 *
 *  Created on: May 24, 2011
 *      Author: mcordovi
 */

#ifndef RSAUTIL_H_
#define RSAUTIL_H_

#include <glibmm.h>
#include <openssl/ossl_typ.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include "System/SafeBuffer.h"
#include "System/Exception/RSAException.h"
#include "System/Security/Cryptography/MsgDigestUtil.h"
#include "System/Security/Cryptography/SignatureAlgorithm.h"



#define DEFAULT_MOD 1024
#define DEFAULT_EXP 0X10001

namespace Smartmatic
{

namespace Log
{
class ISMTTLog;
}

namespace System
{

namespace Security
{

namespace Cryptography
{


class RsaUtil : public SignatureAlgorithm
{
public:


	/**
	 * @brief Message padding type for use in rsa encyption/decryption
	 *        computations
	 */
	typedef enum RsaPaddingEnum
	{
		RSAPAD_PKCS1, // default
		RSAPAD_OAEP,
		RSAPAD_SSL,
		RSAPAD_RAW

	} RsaPaddingEnumType;






	RsaUtil ();

	/**
	 * @brief Constructor. The key pair must be obtained and set after
	 *        instantiation.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param  certPath: the absolute path to a certificate to load the keys
	 *         from.
	 * @param  certFormat: the certificate's format
	 * @param  pad: padding to use on further rsa computations
	 *
	 */
	RsaUtil(
		  const Glib::ustring& certPath
		, const CertUtil::CertFileFormat certFormat
		, const RsaPaddingEnumType pad)
	throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Constructor. Initializes this instance with an automatically
	 *        generated key pair using the provided public exponent end modulus.
	 *        The prime factors (p,q) are generated randomly and the private
	 *        exponent (d) is calculated to fit all the previous values.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param  n: public modulus (values of n < 1024 should be considered insecure)
	 * @param  e: public exponent (usually 3, 17 or 65537)
	 * @param  pad: padding to use on further rsa computations
	 *
	 */
	RsaUtil(
	      const RsaPaddingEnumType pad
		, const int n = DEFAULT_MOD
		, const unsigned long e = DEFAULT_EXP)
	throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Copy Constructor
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 */
	RsaUtil(const RsaUtil& other);

	/**
	 * @brief Destructor
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 */
	virtual ~RsaUtil();




	/**
	 * @brief Assignment operator overload
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 */
	RsaUtil& operator=(const RsaUtil& other);

	/**
	 * @brief Equality operator overload
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 */
	bool operator ==(const RsaUtil& other);




	/**
	 * @brief Public key encryption.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param plaintext: buffer containing the message to be encrypted
	 *
	 * @return a buffer containing the ciphertext obtained from the encryption
	 *         of the plaintext using this instance's public key and padding
	 *         type.
	 *
	 */
	Smartmatic::System::SafeBuffer PublicEncrypt (
			const Smartmatic::System::SafeBuffer& plaintext)
		throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Public key encryption. (Overload for raw buffering)
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param plaintext: buffer containing the message to be encrypted
	 *
	 * @return a buffer containing the ciphertext obtained from the encryption
	 *         of the plaintext using this instance's public key and padding
	 *         type.
	 *
	 */
	Smartmatic::System::SafeBuffer PublicEncrypt (
			const unsigned char* plaintext, int bufferLen)
		throw (const Smartmatic::System::Exception::RSAException&);



	/**
	 * @brief Private key decryption.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param ciphertext: buffer containing the encrypted message
	 *
	 * @return a buffer containing the message recovered from the ciphertext.
	 *         This instance's private key and padding are used for decryption
	 *         computations. Padding must be set to the padding type used to
	 *         encrypt the original message.
	 *
	 */
	Smartmatic::System::SafeBuffer PrivateDecrypt (
			const Smartmatic::System::SafeBuffer& ciphertext)
		throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Private key decryption. (Overload for raw buffering)
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param ciphertext: buffer containing the encrypted message
	 *
	 * @return a buffer containing the message recovered from the ciphertext.
	 *         This instance's private key and padding are used for decryption
	 *         computations. Padding must be set to the padding type used to
	 *         encrypt the original message.
	 *
	 */
	Smartmatic::System::SafeBuffer PrivateDecrypt (
			const unsigned char* ciphertext, int bufferLen)
		throw (const Smartmatic::System::Exception::RSAException&);



	/**
	 * @brief Private key encryption.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param plaintext: buffer containing the message to be encrypted
	 *
	 * @return a buffer containing the ciphertext obtained from the encryption
	 *         of the plaintext using this instance's private key and padding
	 *         type.
	 *
	 */
	Smartmatic::System::SafeBuffer PrivateEncrypt (
			const Smartmatic::System::SafeBuffer& plaintext)
		throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Private key encryption. (Overload for raw buffering)
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param plaintext: raw buffer containing the message to be encrypted
	 *
	 * @return a buffer containing the ciphertext obtained from the encryption
	 *         of the plaintext using this instance's private key and padding
	 *         type.
	 *
	 */
	Smartmatic::System::SafeBuffer PrivateEncrypt (
			const unsigned char* plaintext, int bufferLen)
		throw (const Smartmatic::System::Exception::RSAException&);



	/**
	 * @brief Public key decryption.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param ciphertext: safe buffer containing the encrypted message
	 *
	 * @return a buffer containing the message recovered from the ciphertext.
	 *         This instance's public key and padding are used for decryption
	 *         computations. Padding must be set to the padding type used to
	 *         encrypt the original message.
	 *
	 */
	Smartmatic::System::SafeBuffer PublicDecrypt (
			const Smartmatic::System::SafeBuffer& ciphertext)
		throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Public key decryption. (Overload for raw buffering)
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param ciphertext: raw buffer containing the encrypted message
	 *
	 * @return a buffer containing the message recovered from the ciphertext.
	 *         This instance's public key and padding are used for decryption
	 *         computations. Padding must be set to the padding type used to
	 *         encrypt the original message.
	 *
	 */
	Smartmatic::System::SafeBuffer PublicDecrypt (
			const unsigned char* ciphertext, int bufferLen)
		throw (const Smartmatic::System::Exception::RSAException&);

		/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Oct 27, 2011
		 *
		 * @param plainData: pointer to data
		 * @param dataLen: data lenght
		 * @param outSafeBuffer: output buffer
		 * @param hash: hash algorithm to use.
		 *
		 *
		 */

		void SignData (
				const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1)
			throw (const Smartmatic::System::Exception::RSAException&);

		/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Oct 27, 2011
		 *
		 * @param inSafeBuffer: reference to data
		 * @param outSafeBuffer: output buffer
		 * @param hash: hash algorithm to use.
		 *
		 *
		 */

		void SignData ( Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1)
					throw (const Smartmatic::System::Exception::RSAException&);

		/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Oct 27, 2011
		 *
		 * @param plainData: pointer to data
		 * @param dataLen: data lenght
		 * @param signature: to verify
		 * @param hash: hash algorithm to use.
		 * @return: true if validation succeed. Otherwise, false.
		 *
		 */
		bool VerifySignature (
						const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1)
					throw (const Smartmatic::System::Exception::RSAException&);

		/**
		 * @brief Signature verification.
		 *
		 * @author fgomez
		 * @date   Oct 27, 2011
		 *
		 * @param inSafeBuffer: reference to data
		 * @param signature: to verify
		 * @param hash: hash algorithm to use.
		 * @return: true if validation succeed. Otherwise, false.
		 *
		 */
		bool VerifySignature (
				Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1)
							throw (const Smartmatic::System::Exception::RSAException&);



	/**
	 * @brief Gets the current padding
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @return the current padding type to be used in cryptographic computations
	 */
	RsaPaddingEnumType GetPaddingType () const;

	/**
	 * @brief Sets the padding to be used for cryptographic computations
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 */
	void SetPaddingType (RsaPaddingEnumType pad);


	/**
	 * @brief Loads a private key contained in a PEM key-file.
	 *
	 * @author mcordovi
	 * @date   May 26, 2011
	 *
	 * @param certPath: the absolute path to the container file.
	 * @param passphrase: the passphrase used to encrypt the key at the time of
	 *                    key-file creation.
	 *
	 */
	/*void SetPrivateKey_PEM2 (
			  const Glib::ustring& pemFilePath
			, const Glib::ustring&  passPhrase)
		throw (const Smartmatic::System::Exception::RSAException&);*/

	/**
	 * @brief Loads a public key contained in a PEM key-file.
	 *
	 * @author mcordovi
	 * @date   May 26, 2011
	 *
	 * @param certPath: the absolute path to the container file.
	 *
	 */
	/*void SetPublicKey_PEM2 (
			  const Glib::ustring& pemFilePath
			, const Glib::ustring&  passPhrase)
		throw (const Smartmatic::System::Exception::RSAException&);*/

	/**
	 * @brief Loads the private key contained in a PKCS#12 file.
	 *
	 * @author mcordovi
	 * @date   May 26, 2011
	 *
	 * @param certPath: the absolute path to the PKCS#12 file.
	 *
	 */
	/*void SetPrivateKey_PKCS122 (
			  const Glib::ustring& p12FilePath
			, const Glib::ustring& passPhrase)
		throw (const Smartmatic::System::Exception::RSAException&);*/

	/**
	 * @brief Loads the key information from an X.509 certificate stored with
	 *        PKCS#12 format.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @param certPath: the absolute path to the certificate's file.
	 *
	 */
	/*void SetPublicKey_X509_PKCS122 (
			  const Glib::ustring& p12FilePath
			, const Glib::ustring& passPhrase)
		throw (const Smartmatic::System::Exception::RSAException&);*/

	/**
	 * @brief Loads the key information from an X.509 certificate stored with
	 *        PEM format.
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 * @param certPath: the absolute path to the certificate's file.
	 *
	 */
	/*void SetPublicKey_X509_Pem2 (const Glib::ustring& certFilePath)
		throw (const Smartmatic::System::Exception::RSAException&);*/

	/**
	 * @brief Loads the key information from an X.509 certificate stored with
	 *        DER format.
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 * @param certPath: the absolute path to the certificate's file.
	 *
	 */
	/*void SetPublicKey_X509_Der2 (const Glib::ustring& certFilePath)
		throw (const Smartmatic::System::Exception::RSAException&);*/



	/**
	 * @brief Checks whether a public or private key is currently being used.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @return true if the key hold by this instance for use in cryptographic
	 *         computations is a public key.
	 *
	 */
	bool IsValidPublicKey () const;

	/**
	 * @brief Checks this instance's key for integrity.
	 *
	 * @author mcordovi
	 * @date   May 24, 2011
	 *
	 * @return false if the key pair or public key hold by this instance is
	 *         invalid or has not been set yet (has a NULL value).
	 *
	 */
	bool IsValidPrivateKey () const
		throw (const Smartmatic::System::Exception::RSAException&);


	virtual SignatureAlgorithmType GetType() const;

protected:


private:

	static Smartmatic::Log::ISMTTLog* logger; ///< logger

	RsaPaddingEnumType m_Padding; ///< padding type
	//RSA* m_Rsa; ///< RSA algorithm keys, parameters and other info


	/**
	 * @brief Fills the instance's RSA structure with the key info extracted
	 *        from a previously parsed X509 certificate. (implemented just to
	 *        factor out some common code repeated along the class)
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 */
	//void mSetKeyFromX509 (X509* x)
		//throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Loads a certificate from disk. (implemented just to
	 *        factor out some common code repeated along the class)
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 * @param absolute path to certificate file
	 *
	 * @return a BIO structure for further certificate content parsing
	 *
	 */
	//BIO* mLoadKeyFile (const Glib::ustring& certPath)
		//throw (const Smartmatic::System::Exception::RSAException&);

	/**
	 * @brief Checks for the buffer intended for encryption to be consistent
	 *        with this instance's padding type and RSA combination.
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 * @param pad padding type to get info from
	 * @param buffLen length of buffer intended for encryption
	 *
	 * @return false if buffer length is not consistent with the current padding
	 *         and RSA (see http://www.openssl.org/docs/crypto/RSA_public_encrypt.html#
	 *         or manual page (3) for RSA_public_encrypt).
	 *
	 */
	bool mCheckPadding (int buffLen, RSA* key);

	/**
	 * @brief Translate enum values.
	 *
	 * @author mcordovi
	 * @date   May 25, 2011
	 *
	 * @param pad [in] padding type to get info from
	 *
	 * @return integer value corresponding to the RSA paddign value of the
	 *         wrapped library.
	 *
	 */
	int mGetNativePadding ();

};

}

}

}

}

#endif /* RSAUTIL_H_ */
