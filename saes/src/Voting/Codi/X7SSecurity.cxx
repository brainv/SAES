/**
 * @file X7SSecurity.cxx
 * @brief Body class x7s security
 * @date 19/03/2012
 * @author Yadickson Soto
 */

#include "X7SSecurity.hxx"
#include <Security/Encryption.hxx>
#include <System/Encoding/Base64Encoder.h>
#include <System/Security/Signed.hxx>
#include <System/Security/Crypto.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <System/IO/Path.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

using namespace Smartmatic::SAES::Voting::Codi;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Runtime::Environment;

ISMTTLog* X7SSecurity::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.Codi.X7SSecurity",GETTEXT_PACKAGE);

X7SSecurity::X7SSecurity()
{
	this->electoralConfiguration = NULL;
	this->directories = NULL;
}

X7SSecurity::~X7SSecurity()
{

}

void X7SSecurity::init(ElectoralConfiguration * electoralConfiguration,
		SaesDirectories * directories)
{
	this->electoralConfiguration = electoralConfiguration;
	this->directories = directories;
}

void X7SSecurity::signedBuffer(SafeBuffer & bufferIn, SafeBuffer & bufferOut)
	throw (CryptoException,
			SignedException)
{
    X7SSigned signedType = SAESConfigurationManager::Current()->getCodiFileConfiguration().getX7SSigned();

	if (signedType != X7SSigned::CONFIGURATION_NONE)
    {
		SafeBuffer sign;
		Signed objSigned;

		X7SSecurityType certType = SAESConfigurationManager::Current()->getCodiFileConfiguration().getX7SSignedCertified();

		switch (certType)
		{
			case X7SSecurityType::CONFIGURATION_MACHINE_KEYS_FILE:
			{
				logger->Debug("Signed X7S codi file with machine keys");

				std::string signedSecretKey;
				std::string certifiedFile;

				signedSecretKey = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getKeys().getProtection_key();
				certifiedFile = directories->getMachineKeysFileFullPath();
				objSigned.loadPKCS12(signedSecretKey, certifiedFile);
			}
				break;

			case X7SSecurityType::CONFIGURATION_PEM_FILES:
			{
				logger->Debug("Signed X7S codi file with pem files");

				std::string signedSecretKey;
				std::string primaryKeyFile;
				std::string certifiedFile;

				primaryKeyFile = directories->getX7SSignedKeyCertifiedFileFullPath();
				certifiedFile = directories->getX7SSignedCertifiedFileFullPath();

				signedSecretKey = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getKeys().getBackup_zip_file_password();
				objSigned.loadCertifiedPKey(primaryKeyFile, signedSecretKey, Cryptography::CertUtil::CertFormat_PEM);
				objSigned.loadCertifiedX509(certifiedFile, Cryptography::CertUtil::CertFormat_PEM);
			}
				break;
		}

		switch(signedType)
		{
			case X7SSigned::CONFIGURATION_PKCS7_SIGNER:
				logger->Debug("Signed X7S codi file with pkcs7");

				objSigned.pkcs7SignerBuffer(bufferIn, sign);
				break;
			case X7SSigned::CONFIGURATION_CMS_SIGNER:
				logger->Debug("Signed X7S codi file with cms");

				objSigned.cmsSignerBuffer(bufferIn, sign);
				break;
			case X7SSigned::CONFIGURATION_NONE:
				break;
		}

		bufferOut.Clear();
		bufferOut.AddData(sign);
    }
	else
	{
		bufferOut.Clear();
		bufferOut.AddData(bufferIn);
	}
}

void X7SSecurity::cryptoBuffer(SafeBuffer & bufferIn, SafeBuffer & bufferOut)
	throw (CryptoException)
{
    X7SCrypto cryptoType = SAESConfigurationManager::Current()->getCodiFileConfiguration().getX7SCrypto();

	if (cryptoType != X7SCrypto::CONFIGURATION_NONE)
    {
		SafeBuffer crypto;
		Crypto objCrypto;

		X7SSecurityType certType = SAESConfigurationManager::Current()->getCodiFileConfiguration().getX7SCryptoCertified();
		objCrypto.init(Encryption::getInstance()->getKeySize(), Encryption::getInstance()->getModeType(), false);

		switch (certType)
		{
			case X7SSecurityType::CONFIGURATION_MACHINE_KEYS_FILE:
			{
				logger->Debug("Crypto X7S codi file with machine keys");

				std::string cryptoSecretKey;
				std::string certifiedFile;

				cryptoSecretKey = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getKeys().getProtection_key();
				certifiedFile = directories->getMachineKeysFileFullPath();
				objCrypto.loadPKCS12(cryptoSecretKey, certifiedFile);
			}
				break;
			case X7SSecurityType::CONFIGURATION_PEM_FILES:
			{
				logger->Debug("Crypto X7S codi file with pem files");

				std::string certifiedFile;

				certifiedFile = directories->getX7SCryptoCertifiedFileFullPath();
				objCrypto.loadCertifiedX509(certifiedFile, Cryptography::CertUtil::CertFormat_PEM);
			}
				break;
		}

		objCrypto.loadPKCS7();

		switch(cryptoType)
		{
			case X7SCrypto::CONFIGURATION_PKCS7_CRYPTO:
				logger->Debug("Crypto X7S codi file with pkcs7");
				objCrypto.pkcs7CryptoBuffer(bufferIn, crypto);
				break;
			case X7SCrypto::CONFIGURATION_CMS_CRYPTO:
				logger->Debug("Crypto X7S codi file with cms");
				objCrypto.cmsCryptoBuffer(bufferIn, crypto);
				break;
			case X7SCrypto::CONFIGURATION_SYMMETRIC_KEY:
			{
				logger->Debug("Crypto X7S codi file with symmetric key");
				SafeBuffer key;
				std::string password = electoralConfiguration->getVotingDevice()->getFirstVotingDevice().getKeys().getBackup_zip_file_password();
				Base64Encoder::ConvertFromBase64(password, key);
				Encryption::getInstance()->cryptoBufferToBuffer(bufferIn, crypto, key);
			}
				break;
			case X7SCrypto::CONFIGURATION_NONE:
				break;
		}

		bufferOut.Clear();
		bufferOut.AddData(crypto);
    }
	else
	{
		bufferOut.Clear();
		bufferOut.AddData(bufferIn);
	}
}

void X7SSecurity::decryptoBuffer(SafeBuffer & bufferIn, SafeBuffer & bufferOut)
	throw (CryptoException)
{

}

void X7SSecurity::validateSignedBuffer(SafeBuffer & bufferIn)
	throw (SignedException)
{

}
