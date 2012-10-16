/**
 * @file MsgDigestUtil.cpp
 * @brief Body class msg digest util
 * @date 01/04/2011
 * @author Marcel Cordovi
 */

#include <iostream>
#include <gtkmm.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <glib.h>
#include <glibmm.h>
#include <Log/SMTTLogManager.h>
#include "MsgDigestUtil.h"

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

#define MD5     "md5"
#define SHA1    "sha1"
#define SHA224  "sha224"
#define SHA256  "sha256"
#define SHA384  "sha384"
#define SHA512  "sha512"
#define CRC32   "crc32"

#define BUFFER_SIZE 256

#define _ERROR_SETTING_CHANNEL_ N_("Smartmatic.System.Security.Cryptography.MsgDigestUtil.ErrorSettingChannel")
#define _ERROR_READING_SECRET_KEY_ N_("Smartmatic.System.Security.Cryptography.MsgDigestUtil.ErrorReadingSecretKey")
#define _ERROR_READING_FILE_HASHING_ N_("Smartmatic.System.Security.Cryptography.MsgDigestUtil.ErrorReadingFileHashing")
#define _ERROR_UNKHOWN_MESSAGE_DIGEST_ N_("Smartmatic.System.Security.Cryptography.MsgDigestUtil.ErrorUnknownMessageDigest")

using namespace Smartmatic::System;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security::Cryptography;
using namespace std;
using namespace Smartmatic::Log;

ISMTTLog* MsgDigestUtil::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Cryptography.MsgDigestUtil.",GETTEXT_PACKAGE);

const char* MsgDigestUtil::mMapAlgName (DigestAlgType alg)
{
	switch (alg)
	{
	case DGSTUTIL_MD5:
		return MD5;
		break;
	case DGSTUTIL_SHA1:
		return SHA1;
		break;
	case DGSTUTIL_SHA224:
		return SHA224;
		break;
	case DGSTUTIL_SHA256:
		return SHA256;
		break;
	case DGSTUTIL_SHA384:
		return SHA384;
		break;
	case DGSTUTIL_SHA512:
		return SHA512;
		break;
	default:
		return "";
	}

	return "";
}


SafeBuffer MsgDigestUtil::Digest(const unsigned char* data, int dataLen, DigestAlgType alg)
{
	unsigned char* md_buffer = NULL;
	int mdbuf_len = 0;

	md_buffer = mPerformHashing (mMapAlgName (alg), data, dataLen, md_buffer, mdbuf_len);

	SafeBuffer digest_result (md_buffer, mdbuf_len);
	g_free(md_buffer);

	return digest_result;
}

SafeBuffer MsgDigestUtil::Digest(const Glib::ustring& message, DigestAlgType alg)
{
	return Digest ((unsigned char*)message.data (), message.bytes (), alg);
}

SafeBuffer MsgDigestUtil::FileDigest(const Glib::ustring& filePath, DigestAlgType alg)
    throw (MessageDigestException)
{
	Glib::RefPtr<Glib::IOChannel> input;
	Glib::IOStatus iostatus;
	Glib::ustring file_content;

	try
	{
		input = Glib::IOChannel::create_from_file(filePath, "r");
		iostatus = input->set_encoding ();

		if (iostatus != Glib::IO_STATUS_NORMAL)
			throw MessageDigestException (_(_ERROR_SETTING_CHANNEL_), N_(_ERROR_SETTING_CHANNEL_), logger);

		iostatus = input->read_to_end(file_content);

		if (iostatus != Glib::IO_STATUS_NORMAL)
			throw MessageDigestException (_(_ERROR_READING_SECRET_KEY_), N_(_ERROR_READING_SECRET_KEY_), logger);
	}
	catch ( Glib::IOChannelError& io_error)
	{
		throw MessageDigestException (_(_ERROR_READING_FILE_HASHING_), N_(_ERROR_READING_FILE_HASHING_), logger);
	}
	catch (Glib::ConvertError & conv_error)
	{
		throw MessageDigestException (_(_ERROR_READING_SECRET_KEY_), N_(_ERROR_READING_SECRET_KEY_), logger);
	}
	catch (Glib::FileError& e)
	{
		throw MessageDigestException (_(_ERROR_READING_SECRET_KEY_), N_(_ERROR_READING_SECRET_KEY_), logger);
	}

	return Digest ((unsigned char*)file_content.data (), file_content.bytes (), alg);
}

unsigned char* MsgDigestUtil::mPerformHashing (
		  const char* algName
		, const unsigned char* data, int dataLen
		, unsigned char* outBuffer, int& outBufSize)
{
	EVP_MD_CTX mdctx;
	const EVP_MD *md;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;
	unsigned char* res_buf = NULL;

	OpenSSL_add_all_digests();
	md = EVP_get_digestbyname(algName);

	if (!md)
		throw MessageDigestException (_(_ERROR_UNKHOWN_MESSAGE_DIGEST_), N_(_ERROR_UNKHOWN_MESSAGE_DIGEST_), logger);

	EVP_MD_CTX_init (&mdctx);
	EVP_DigestInit_ex (&mdctx, md, NULL);
	EVP_DigestUpdate (&mdctx, data, dataLen);
	EVP_DigestFinal_ex (&mdctx, md_value, &md_len);
	EVP_MD_CTX_cleanup (&mdctx);

	outBufSize = md_len;

	res_buf = (unsigned char*)g_malloc (md_len * sizeof (char));
	memset (res_buf, 0, md_len);
	memcpy (res_buf, md_value, md_len);

	return res_buf;
}

