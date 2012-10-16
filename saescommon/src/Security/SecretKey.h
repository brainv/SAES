/**
 * @file	SecretKey.h
 *
 * @brief	Declares the secret key class.
 */

#ifndef SECRETKEY_H_
#define SECRETKEY_H_

#include <glibmm.h>
#include <Configuration/SaesCommonConfiguration-schema.hxx>
#include <System/Exception/SecretKeyException.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

namespace SAES
{
namespace Common
{
namespace Security
{
/**
 * @class	SecretKey
 *
 * @brief	Secret key. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class SecretKey
{

public:

	typedef enum
	{
		KEYDERIV_HMAC,
		KEYDERIV_DES,
		KEYDERIV_3KEY3DES,
		KEYDERIV_2KEY3DES,
		KEYDERIV_RC4

	} KeyDerivAlgType;


	// Lifecycle

	/**
	 * @fn	SecretKey::SecretKey();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	SecretKey();

	/**
	 * @fn	SecretKey::SecretKey(const Glib::ustring filePath,
	 * 		const Glib::ustring passPhrase) throw (System::Exception::SecretKeyException);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	filePath  	Full pathname of the file.
	 * @param	passPhrase	The pass phrase.
	 */

	SecretKey(const Glib::ustring filePath, const Glib::ustring passPhrase)
        throw (System::Exception::SecretKeyException);

	/**
	 * @fn	SecretKey::SecretKey (const SecretKey& other);
	 *
	 * @brief	Copy constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	other	The other.
	 */

	SecretKey (const SecretKey& other);

	/**
	 * @fn	virtual SecretKey::~SecretKey();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~SecretKey();


	// Operator overloading

	/**
	 * @fn	SecretKey& SecretKey::operator=(const SecretKey& sk);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	sk	The sk.
	 *
	 * @return	A shallow copy of this object.
	 */

	SecretKey& operator=(const SecretKey& sk);


	// Public interface

	/**
	 * @fn	Glib::ustring SecretKey::getKeyBase64 () const;
	 *
	 * @brief	Accessor to the file stored secret key.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	the key contained in the file in a base64 encoding format.
	 */

	Glib::ustring getKeyBase64 () const;

	/**
	 * @brief Accessor to the file stored secret key
	 * @param key out parameter. Is allocated with a new buffer containing the key bytes
	 * @param keyLen out parameter. Will contain the key buffer length.
	 * @return keylen out parameter. Will contain the key buffer length.
	 */
	void getKey (unsigned char*& key, int& keyLen);

	/**
	 * @brief Accessor to the file stored secret key
	 * @param key out parameter. Is allocated with a new buffer containing the key bytes
	 * @returns pointer to the key content
	 */
	const unsigned char* getKey (int& keyLen) const;

	/**
	 * @brief Accesor to the user provided passphrase.
	 */
	const Glib::ustring getPlainPassphrase () const { return m_Passphrase; }

	/**
	 * @brief accesor to the encrypted passphrase
	 * @param Out. Mutable integer wich will contain the size of the buffer.
	 * @return a buffer with the encrypted passphrase
	 */
	const unsigned char* getPassphrase (size_t& bufferLen) const;


protected:


private:


	// properties

	Glib::ustring m_FilePath;   ///< Full pathname of the file
	Glib::ustring m_Passphrase; ///< The passphrase

	bool m_IsFileEncrypted; ///< true if is file encrypted

	unsigned char* mp_DecryptionKey;	///< The decryption key
	size_t m_DecryptionKeyLen;  ///< Length of the decryption key

	unsigned char* mp_SecretKey;	///< The secret key
	size_t m_SecretKeyLen;  ///< Length of the secret key

	unsigned char* mp_PassphraseEncrypted;  ///< The passphrase encrypted
	size_t m_PassphraseEncryptedLen;	///< Length of the passphrase encrypted


	// member methods

	/**
	 * @fn	void SecretKey::mUnwrap() throw (Smartmatic::System::Exception::SecretKeyException);
	 *
	 * @brief	Extract the secret key contained in the file decrypting it if necessary.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void mUnwrap() throw (Smartmatic::System::Exception::SecretKeyException);

	/**
	 * @fn	void SecretKey::mProcessInputPassphrase( Glib::ustring& passphrase , Glib::ustring& salt ,
	 * 		Glib::ustring sep_pattern ,
	 * 		int &iterations) throw (Smartmatic::System::Exception::SecretKeyException);
	 *
	 * @brief	Parse the string provided by the client to obtain the parameters needed by the
	 * 			cryptography algorithms involved in the extraction of the secret key.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	passphrase	The passphrase.
	 * @param [in,out]	salt	  	The salt.
	 * @param	sep_pattern		  	The separator pattern.
	 * @param [in,out]	iterations	The iterations.
	 */

	void mProcessInputPassphrase(
			  Glib::ustring& passphrase
			, Glib::ustring& salt
			, Glib::ustring sep_pattern
			, int &iterations)
	throw (Smartmatic::System::Exception::SecretKeyException);

	/**
	 * @fn	void SecretKey::mObtainSymetricKey( const Glib::ustring passPhrase ,
	 * 		const Smartmatic::System::Security::Cryptography::DigestBuffer& salt ,
	 * 		const Smartmatic::SAES::Common::Configuration::KeyDerivAlgType drv_alg ,
	 * 		const Smartmatic::SAES::Common::Configuration::DigestAlgType dgst_alg ,
	 * 		const int iterations) throw (Smartmatic::System::Exception::SecretKeyException);
	 *
	 * @brief	Derives PBE key from the passphrase provided by the user.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	passPhrase	The pass phrase.
	 * @param	salt	  	The salt.
	 * @param	drv_alg   	The driver algorithm.
	 * @param	dgst_alg  	The dgst algorithm.
	 * @param	iterations	The iterations.
	 */

	void mObtainSymetricKey(
			  const Glib::ustring passPhrase
			, const Smartmatic::System::SafeBuffer& salt
			, const Smartmatic::SAES::Common::Configuration::KeyDerivAlgType drv_alg
			, const Smartmatic::SAES::Common::Configuration::DigestAlgType dgst_alg
			, const int iterations)
	throw (Smartmatic::System::Exception::SecretKeyException);

	/**
	 * @fn	void SecretKey::mClearKey (unsigned char* keyBuf, size_t& keyBufLen);
	 *
	 * @brief	securely free a key buffer resources.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	keyBuf   	pointer to the buffer to be erased.
	 * @param [in,out]	keyBufLen	buffer's size.
	 */

	void mClearKey (unsigned char* keyBuf, size_t& keyBufLen);

	/**
	 * @fn	void SecretKey::mAssignKey ( const unsigned char* keySrc , const size_t srcLen ,
	 * 		unsigned char*& keyDest , size_t& destLen);
	 *
	 * @brief	securely fills a key buffer with a new key value.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	keySrc		   	source buffer pointer to copy from.
	 * @param	srcLen		   	source buffer's size.
	 * @param [in,out]	keyDest	destination buffer.
	 * @param [in,out]	destLen	destination buffer's size.
	 */

	void mAssignKey (
			  const unsigned char* keySrc
			, const size_t srcLen
			, unsigned char*& keyDest
			, size_t& destLen);

	/**
	 * @fn	void SecretKey::mEncryptPassphrase (Glib::ustring passphrase) throw (Smartmatic::System::Exception::SecretKeyException);
	 *
	 * @brief	store provided plain phassphrase encrypted with the default encryption key.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	passphrase	passphrase.
	 */

	void mEncryptPassphrase (Glib::ustring passphrase)
	throw (Smartmatic::System::Exception::SecretKeyException);

	/**
	 * @brief	Method process file key.
	 * @param	filePath file path
	 * @param	passPhrase	The pass phrase.
	 * @author	Yadickson Soto
	 * @date	13/02/2012
	 */
	void processKey(const Glib::ustring filePath, const Glib::ustring passPhrase)
		throw (Smartmatic::System::Exception::SecretKeyException);


	static Smartmatic::Log::ISMTTLog* logger; ///< The logger
};

}
}
}
}

#endif /* SECRETKEY_H_ */
