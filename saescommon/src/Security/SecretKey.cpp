/**
 * @file SecretKey.cpp
 * @brief Body class secret key
 * @date 05/04/2011
 * @author Marcel Cordovi
 */

#include <iostream>
#include <glib.h>
#include <errno.h>

#include "SecretKey.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include "smartmatic/System/Security/Cryptography/PBEKeyDerivatorHMAC.h"
#include "smartmatic/System/Security/Crypto.hxx"
#include "Security/Encryption.hxx"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/IO/File.h>
#include <System/Encoding/Base64Encoder.h>

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

#define HMAC_KEY_LEN 32

using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Common::Security;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;
using namespace std;

ISMTTLog* SecretKey::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Common.Security.SecretKey",GETTEXT_PACKAGE);

// ================= Utility ==========================

void SecretKey::mClearKey (unsigned char* keyBuf, size_t& keyBufLen)
{
	if (keyBuf != NULL && keyBufLen != 0)
		memset (keyBuf, 0, keyBufLen);

	if(keyBuf)
		g_free ((gpointer) keyBuf);

	keyBuf = NULL;
	keyBufLen = 0;
}

void SecretKey::mAssignKey (
		  const unsigned char* keySrc
		, const size_t srcLen
		, unsigned char*& keyDest
		, size_t& destLen)
{
	if (keyDest != NULL && destLen > 0)
		mClearKey (keyDest, destLen);

	if (keySrc != NULL && srcLen != 0)
	{
		keyDest = static_cast<unsigned char*> (
				g_malloc (srcLen * sizeof (unsigned char)));

		memcpy (keyDest, keySrc, srcLen);
		destLen = srcLen;
	}
}


// ================= Operator Overloading ======================

SecretKey& SecretKey::operator=(const SecretKey& sk)
{
	if (this != &sk)
	{
		// clear current state

		mClearKey (mp_DecryptionKey, m_DecryptionKeyLen);
		mClearKey (mp_SecretKey, m_SecretKeyLen);
		mClearKey (mp_PassphraseEncrypted, m_PassphraseEncryptedLen);


		// copy new assigned values

		this->m_FilePath.assign (sk.m_FilePath);
		this->m_IsFileEncrypted = sk.m_IsFileEncrypted;
		this->m_Passphrase = sk.m_Passphrase;

		mAssignKey (
				  sk.mp_DecryptionKey
				, sk.m_DecryptionKeyLen
				, this->mp_DecryptionKey
				, this->m_DecryptionKeyLen);

		mAssignKey (
				  sk.mp_SecretKey
				, sk.m_SecretKeyLen
				, this->mp_SecretKey
				, this->m_SecretKeyLen);

		mAssignKey (
				  sk.mp_PassphraseEncrypted
				, sk.m_PassphraseEncryptedLen
				, this->mp_PassphraseEncrypted
				, this->m_PassphraseEncryptedLen);
	}

	return *this;
}


// ================= Access =======================================

Glib::ustring SecretKey::getKeyBase64 () const
{
	Glib::ustring base64_rep;

	SafeBuffer dbuf (mp_SecretKey, m_SecretKeyLen);
	base64_rep.assign (dbuf.GetBase64Data());

	return base64_rep;
}

void SecretKey::getKey (unsigned char*& key, int& keyLen)
{
	mAssignKey (
			  mp_SecretKey
			, m_SecretKeyLen
			, key
			, (size_t&)keyLen);
}

const unsigned char* SecretKey::getKey (int& keyLen) const
{
	keyLen = m_SecretKeyLen;
	return mp_SecretKey;
}

const unsigned char* SecretKey::getPassphrase (size_t& bufferLen) const
{
	bufferLen = m_PassphraseEncryptedLen;
	return mp_PassphraseEncrypted;
}


// ================= Life Cycle ==================================

SecretKey::SecretKey()
{
	mp_DecryptionKey = NULL;
	m_DecryptionKeyLen = 0;

	mp_SecretKey = NULL;
	m_SecretKeyLen = 0;

	mp_PassphraseEncrypted = NULL;
	m_PassphraseEncryptedLen = 0;
}

SecretKey::SecretKey (const SecretKey& sk)
{
	this->m_FilePath.assign (sk.m_FilePath);
	this->m_IsFileEncrypted = sk.m_IsFileEncrypted;
	this->m_Passphrase = sk.m_Passphrase;

	mp_DecryptionKey = NULL;
	m_DecryptionKeyLen = 0;

	mp_SecretKey = NULL;
	m_SecretKeyLen = 0;

	mp_PassphraseEncrypted = NULL;
	m_PassphraseEncryptedLen = 0;

	mAssignKey (
			  sk.mp_DecryptionKey
			, sk.m_DecryptionKeyLen
			, this->mp_DecryptionKey
			, this->m_DecryptionKeyLen);

	mAssignKey (
			  sk.mp_SecretKey
			, sk.m_SecretKeyLen
			, this->mp_SecretKey
			, this->m_SecretKeyLen);

	mAssignKey (
			  sk.mp_PassphraseEncrypted
			, sk.m_PassphraseEncryptedLen
			, this->mp_PassphraseEncrypted
			, this->m_PassphraseEncryptedLen);
}

SecretKey::SecretKey(const Glib::ustring filePath, const Glib::ustring passPhrase)
    throw (SecretKeyException)
{
	processKey(filePath, passPhrase);
}

void SecretKey::processKey(const Glib::ustring filePath, const Glib::ustring passPhrase)
	throw (SecretKeyException)
{
	Glib::ustring passphrase (passPhrase);

	m_Passphrase = passPhrase;

	/* State initialization */
	logger->Debug("Open file: " + filePath);
    m_FilePath.assign (filePath);

	m_IsFileEncrypted = (*SAESCommonConfigurationManager::Current()->getConfiguration())->
            getMachineSecuritySchema().getSecretKeyEncrypted();

	mp_DecryptionKey = NULL;
	m_DecryptionKeyLen = 0;

	mp_SecretKey = NULL;
	m_SecretKeyLen = 0;

	mp_PassphraseEncrypted = NULL;
	m_PassphraseEncryptedLen = 0;


	/* Calculate file's decryption key  */

	if (m_IsFileEncrypted)
	{
		SafeBuffer salt;
		int iterations = 0;

		SaltSourceType salt_conf = (*SAESCommonConfigurationManager::Current()->getConfiguration())->
	            getMachineSecuritySchema().getSaltSource();

		if ( salt_conf.getCalcSalt() ) // check whether salt must be calculated
		{
			SafeBuffer dbg_salt ((unsigned char*)passphrase.data (), (int)passphrase.bytes());

			salt = MsgDigestUtil::Digest (
					  dbg_salt.GetData ()
					, dbg_salt.GetSize ()
					, MsgDigestUtil::DGSTUTIL_SHA256);

			/* Debug: Prints calculated salt  */
			logger->Debug("Salt = " + salt.GetBase64Data());

			iterations = (*SAESCommonConfigurationManager::Current()->getConfiguration())->
		            getMachineSecuritySchema().getIterations();
		}
		else // obtain salt from input
		{
			Glib::ustring salt_b64;

			mProcessInputPassphrase (
					  passphrase
					, salt_b64
					, salt_conf.getSepChar()
					, iterations);

			if (salt_b64.empty())    // salt wasn't provided
				salt_b64.assign (salt_conf.getDefaultSalt ());

			if (iterations == 0) // iterations wasn't provided
				iterations = (*SAESCommonConfigurationManager::Current()->getConfiguration())->
	            getMachineSecuritySchema().getIterations();

			Base64Encoder::ConvertFromBase64(salt_b64, salt);
		}

		mObtainSymetricKey (
				  passphrase
				, salt
				, (*SAESCommonConfigurationManager::Current()->getConfiguration())->
	                  getMachineSecuritySchema().getKeyDerivAlg()
				, (*SAESCommonConfigurationManager::Current()->getConfiguration())->
	                  getMachineSecuritySchema().getDigestAlg()
				, iterations);

		/* Debug: Prints PBE key */
		SafeBuffer pbe_key (mp_DecryptionKey, m_DecryptionKeyLen);
		logger->Debug("PBE Key = " + pbe_key.GetBase64Data());
	}


	// TODO: Encrypt passphrase
    //m_Passphrase.assign (passphrase);

    mEncryptPassphrase (passphrase);


	/* Extract key from file */

	mUnwrap ();

	Smartmatic::System::SafeBuffer key (mp_SecretKey, m_SecretKeyLen);
	Smartmatic::System::SafeBuffer iv;
	Smartmatic::SAES::Security::Encryption::getInstance()->getUseIV(key, iv);

	/* Debug: Prints unencrypted file content */
	logger->Debug("----------------------------------------------------------------");
	logger->Debug("Key = " + getKeyBase64 ());
	logger->Debug("IV = " + iv.GetBase64Data());
	logger->Debug("----------------------------------------------------------------");
}

SecretKey::~SecretKey()
{
	mClearKey (mp_DecryptionKey, m_DecryptionKeyLen);
	mClearKey (mp_SecretKey, m_SecretKeyLen);
	mClearKey (mp_PassphraseEncrypted, m_PassphraseEncryptedLen);
}


// ================= Key Processing ======================

void SecretKey::mProcessInputPassphrase (
		  Glib::ustring& passphrase
		, Glib::ustring& salt
		, Glib::ustring sep_pattern
		, int &iterations)
        throw (SecretKeyException)
{
	std::vector<Glib::ustring> tokens;
	size_t num_tokens;

	if ( sep_pattern == "|" ) // TODO: use regular expression for regex's reserved tokens detection and scapeping
		sep_pattern = "\\" + sep_pattern; // preppend scape character

	tokens = Glib::Regex::split_simple(sep_pattern, passphrase);
	num_tokens = tokens.size();

	if ( num_tokens == 0 || num_tokens > 3 )
	{
	    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorInvalidPassphraseFormat"), N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorInvalidPassphraseFormat"), logger);
	}

	passphrase.assign (tokens[0]);

	if (num_tokens >= 2)
		salt = tokens[1];
	else // no provided
		salt.assign ("");

	if (num_tokens == 3)
		iterations = atoi (tokens[2].c_str ());
	else // no provided
		iterations = 0;
}

void SecretKey::mObtainSymetricKey (
		  const Glib::ustring passPhrase
		, const SafeBuffer& salt
		, const Smartmatic::SAES::Common::Configuration::KeyDerivAlgType drv_alg
		, const Smartmatic::SAES::Common::Configuration::DigestAlgType   dgst_alg
		, const int iterations)
throw (SecretKeyException)
{
	PBEKeyDerivatorHMAC deriver;
	unsigned char output_buffer[HMAC_KEY_LEN];


	// TODO: HMAC is the only algorithm supported for the moment

	try
	{
		switch (drv_alg)
		{

		case KEYDERIV_HMAC:

			deriver.SetSalt(salt.GetData(), salt.GetSize ());

			deriver.GenerateKey(
					  passPhrase
					, output_buffer
					, (int) sizeof (output_buffer)
					, iterations);
			/* TODO: DGSTUTIL_SHA1 is the default use dgst_alg instead when available*/
			break;

		case KEYDERIV_DES:
		case KEYDERIV_3KEY3DES:
		case KEYDERIV_2KEY3DES:
		case KEYDERIV_RC4:
		    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorAlgorithmNotSupported"), N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorAlgorithmNotSupported"), logger );
			break;
		default:
		    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorAlgorithmNotSupported"), N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorAlgorithmNotSupported"), logger );
		}
	}
	catch (...) // TODO: catch HMAC exception
	{
	    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorDerivingDecryptionKey"), N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorDerivingDecryptionKey"), logger);
	}

	mAssignKey (
			  output_buffer
			, sizeof (output_buffer)
			, mp_DecryptionKey
			, m_DecryptionKeyLen);
}

void SecretKey::mUnwrap () throw (SecretKeyException)
{
	Glib::RefPtr<Glib::IOChannel> input;
	Glib::IOStatus iostatus;
	Glib::ustring file_content;

	unsigned char* content_buffer;
	unsigned char* decrypted_buffer;
	int decryptkey_len = 0;
	int secretkey_len = 0;

	if (!File::canOpenFile(m_FilePath))
	{
        throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorOpenFileSecretKey"),
                                  N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorOpenFileSecretKey"), logger);
	}

	Crypto crypt;

	try
	{
		input = Glib::IOChannel::create_from_file(m_FilePath, "r");
		iostatus = input->set_encoding ();  // Set channel for binary reading

		if (iostatus != Glib::IO_STATUS_NORMAL)
		{
		    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorSettingChannel"),
			                         N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorSettingChannel"), logger);
		}

		iostatus = input->read_to_end(file_content);

		if (iostatus != Glib::IO_STATUS_NORMAL)
		{
		    throw SecretKeyException (_("Smartmatic.SAES.Common.Security.SecretKey.ErrorReadingSecretKey"),
			                         N_("Smartmatic.SAES.Common.Security.SecretKey.ErrorReadingSecretKey"), logger);
		}
	}
	catch ( Glib::IOChannelError& io_error)
	{
		// TODO translatable message
	    throw SecretKeyException (io_error.what(), io_error.what(), logger);
	}
	catch (Glib::ConvertError & conv_error)
	{
		// TODO translatable message
	    throw SecretKeyException (conv_error.what(), conv_error.what(), logger);
	}
	catch (Glib::FileError& ferr)
	{
		// TODO translatable message
	    throw SecretKeyException (ferr.what(), ferr.what(), logger);
	}

	if (m_IsFileEncrypted)
	{
		try
		{
			content_buffer = (unsigned char*)file_content.data ();
			secretkey_len = file_content.bytes();
			Smartmatic::System::SafeBuffer dataIn (content_buffer, secretkey_len);

			crypt.init (Smartmatic::SAES::Security::Encryption::getInstance()->getKeySize(),
					Smartmatic::SAES::Security::Encryption::getInstance()->getModeType(), true);

			Smartmatic::System::SafeBuffer key (mp_DecryptionKey, m_DecryptionKeyLen);
			Smartmatic::System::SafeBuffer iv;
			Smartmatic::SAES::Security::Encryption::getInstance()->getUseIV(key, iv);

			Smartmatic::System::SafeBuffer dataOut;

			crypt.decryptoBufferToBuffer (
			          dataIn
			        , dataOut
					, mp_DecryptionKey
					, iv.GetData());

			decrypted_buffer = (unsigned char *)dataOut.GetData();
			decryptkey_len = dataOut.GetSize();

			mAssignKey (
					  decrypted_buffer
					, decryptkey_len
					, mp_SecretKey
					, m_SecretKeyLen);
		}
		catch (CryptoException & ce)
		{
			// TODO translatable message
		    throw SecretKeyException (ce.what(), ce.what(), logger);
		}
	}
	else
	{
		// obtain secret key directly by decoding the file content

		gsize bytes_converted = 0;
		guchar* base64_buff = g_base64_decode ((const gchar*) file_content.data (), &bytes_converted);

		mAssignKey (
				  (unsigned char *)base64_buff
				, bytes_converted
				, mp_SecretKey
				, m_SecretKeyLen);

		if (base64_buff != NULL)
		{
			g_free (base64_buff);
		}
	}
}

void SecretKey::mEncryptPassphrase (Glib::ustring passphrase)
    throw (SecretKeyException)
{
    Smartmatic::System::SafeBuffer passEncrypted;
    Smartmatic::System::SafeBuffer initKey;
    Smartmatic::System::SafeBuffer data((unsigned char*)passphrase.data(), (int)passphrase.bytes ());

    initKey = Smartmatic::SAES::Security::Encryption::getInstance()->
			    getInitKey ();

	Crypto crypt;

	try
	{
		crypt.init (Smartmatic::SAES::Security::Encryption::getInstance()->getKeySize(),
				Smartmatic::SAES::Security::Encryption::getInstance()->getModeType(), true);

		Smartmatic::System::SafeBuffer iv;
		Smartmatic::SAES::Security::Encryption::getInstance()->getUseIV(initKey, iv);

		crypt.cryptoBufferToBuffer (
				  data
				, passEncrypted
				, initKey.GetData()
				, iv.GetData());
	}
	catch (CryptoException & ce)
	{
		// TODO translatable message
	    throw SecretKeyException (ce.what(), ce.what(), logger);
	}

	mAssignKey (
	        passEncrypted.GetData()
			, passEncrypted.GetSize()
			, mp_PassphraseEncrypted
			, m_PassphraseEncryptedLen);
}
