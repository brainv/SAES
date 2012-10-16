/**
 * @file Encryption.cxx
 * @brief Body class Encryption
 */

#include <System/XML/DomXml.hxx>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include <System/Compression/compression-class.h>
#include <sstream>
#include <glibmm.h>
#include <iomanip>
#include <openssl/evp.h>
#include <System/IO/File.h>
#include <System/Encoding/Base64Encoder.h>
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include "Encryption.hxx"
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/Security/Crypto.hxx>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/Security/Cryptography/CertificateValidator.h>
#include <System/Security/Cryptography/RsaUtil.h>
#include <System/Security/Cryptography/CertUtil.h>

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

using namespace Smartmatic::System::Encoding;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::XML;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Common::Security;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Compression;

ISMTTLog* Encryption::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Security.Encryption",GETTEXT_PACKAGE);

Encryption * Encryption::instance = NULL;
std::string Encryption::initKeyBase64 = "42WbFD4qfw0pjmcMTdFLGoP3kTZUv4TymESkD2OsA/0=";

Encryption::Encryption()
{
    OpenSSL_add_all_algorithms();

	machineTime = 0;
	keySize = Crypto::KEY_AES_256;
	m_SecretKey = NULL;
	m_UPKey = NULL;

	Base64Encoder::ConvertFromBase64(Encryption::initKeyBase64, initKey);

	SecurityCryptoMode mode = SecurityCryptoMode::CONFIGURATION_CBC;

	if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSecurityCryptoMode() != NULL)
	{
		mode = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getSecurityCryptoMode().get();
	}

	switch(mode)
	{
		case SecurityCryptoMode::CONFIGURATION_ECB:
			modeType = Crypto::MODE_AES_ECB;
			break;
		default:
			modeType = Crypto::MODE_AES_CBC;
			break;
	}
}

Encryption::~Encryption()
{
	if (m_SecretKey)
	{
		delete m_SecretKey;
		m_SecretKey = NULL;
	}
	if (m_UPKey)
	{
		delete m_UPKey;
		m_UPKey = NULL;
	}
}

void Encryption::initCrypto (SecretKey& sk, UseKeyType ukt) throw (CryptoException)
{
	switch (ukt)
	{
		case UP_KEY:
			this->m_UPKey = new SecretKey(sk);
			break;

		default:
			this->m_SecretKey = new SecretKey(sk);
			break;
	}
}

void Encryption::initSigned(Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories, std::string & signedKey) throw (SignedException, CryptoException)
{
    this->directories = directories;
    this->signedSecretKey = signedKey;
}

void Encryption::signedXml(std::string & xml, ResourceFileType rft)
        throw (CryptoException, SignedException)
{
    xercesc::DOMDocument * doc = NULL;
    Smartmatic::System::XML::DomXml dom;
    doc = dom.stringToDom(xml);
    signedDOM(doc, rft);
    dom.domToString(doc, xml);
}

void Encryption::signedDOM(xercesc::DOMDocument * doc,
        Encryption::ResourceFileType rft) throw (CryptoException, SignedException)
{
    Signed objSigned;
    configSigned(objSigned, NULL, rft);
    objSigned.signDOMWithCertificate(doc, signedData(rft));
}

void Encryption::signedFile(std::string & file,
        Encryption::ResourceFileType rft) throw (CryptoException, SignedException,
        XmlException)
{
    xercesc::DOMDocument * doc = NULL;
    Smartmatic::System::XML::DomXml dom;
    doc = dom.fileToDom(file);
    signedDOM(doc, rft);
    dom.domToFile(doc, file);
}

void Encryption::cryptoDOMToBuffer(xercesc::DOMDocument * doc, Smartmatic::System::SafeBuffer & dataOut,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    std::string dataIn;
    Smartmatic::System::XML::DomXml dom;
    dom.domToString(doc, dataIn);

    cryptoStringToBuffer(dataIn, dataOut, rft, ukt, pad);
}

void Encryption::cryptoDOMToFile(xercesc::DOMDocument * doc, std::string & file,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    std::string dataIn;
    Smartmatic::System::XML::DomXml dom;
    dom.domToString(doc, dataIn);

    cryptoStringToFile(dataIn, file, rft, ukt, pad);
}

void Encryption::cryptoStringToFile(std::string & data, std::string & file,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn((unsigned char *)data.c_str(), data.length());
    cryptoBufferToFile(dataIn, file, rft, ukt, pad);
}

void Encryption::cryptoStringToFile(std::string & data, std::string & file,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn((unsigned char *)data.c_str(), data.length());
    cryptoBufferToFile(dataIn, file, ukt, pad);
}

void Encryption::cryptoBufferToFile(Smartmatic::System::SafeBuffer & dataIn, std::string & file,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    if (cryptoData(rft))
    {
        cryptoBufferToFile(dataIn, file, ukt);
    }
    else if (dataIn.GetSize() > 0)
    {
        std::ofstream myfile(file.c_str(), std::ios::out | std::ios::trunc);

        if (myfile.is_open())
        {
            std::string data;
            data.assign((char *)dataIn.GetData(), dataIn.GetSize());
            data.resize(dataIn.GetSize());
            myfile << data;
            myfile.close();
        }
    }
}

void Encryption::cryptoBufferToFile(Smartmatic::System::SafeBuffer & dataIn, std::string & file,
        Encryption::UseKeyType ukt,
        bool pad) throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.cryptoBufferToFile(dataIn, file, key.GetData(), iv.GetData());
}

void Encryption::cryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
	Smartmatic::System::SafeBuffer & dataOut,
	Smartmatic::System::SafeBuffer key, bool pad)
		throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.cryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
}

void Encryption::decryptoFileToString(std::string & file, std::string & data,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
        throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataOut;
    decryptoFileToBuffer(file, dataOut, rft, ukt, pad);

    if (dataOut.GetSize() > 0)
    {
    	data.assign((const char *)dataOut.GetData(), dataOut.GetSize());
    	data.resize(dataOut.GetSize());
    }
}

void Encryption::decryptoFileToString(std::string & file, std::string & data,
        Encryption::UseKeyType ukt,
        bool pad)
        throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataOut;
    decryptoFileToBuffer(file, dataOut, ukt, pad);

    if (dataOut.GetSize() > 0)
    {
    	data.assign((const char *)dataOut.GetData(), dataOut.GetSize());
    	data.resize(dataOut.GetSize());
    }
}

void Encryption::decryptoFileToBuffer(std::string & file,
		Smartmatic::System::SafeBuffer & dataOut,
		Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
        throw (CryptoException)
{
    if (cryptoData(rft))
    {
        decryptoFileToBuffer(file, dataOut, ukt, pad);
    }
    else
    {
        std::ifstream ifile(file.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
        int size;
        const char * d = NULL;

        if (ifile.is_open())
        {
            size = ifile.tellg();
            d = new char [size];
            ifile.seekg (0, std::ios::beg);
            ifile.read ((char *)d, size);
            ifile.close();

            dataOut.AddData((unsigned char *)d, size);
            delete[] d;
        }
    }
}

void Encryption::decryptoFileToBuffer(std::string & file,
		Smartmatic::System::SafeBuffer & dataOut,
		Encryption::UseKeyType ukt,
        bool pad)
        throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.decryptoFileToBuffer(file, dataOut, key.GetData(), iv.GetData());
}

void Encryption::decryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
	Smartmatic::System::SafeBuffer & dataOut,
	Smartmatic::System::SafeBuffer key, bool pad)
		throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.decryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
}

void Encryption::validateSignedString(std::string & data,
        Encryption::ResourceFileType rft)
        throw (CryptoException, SignedException)
{
    xercesc::DOMDocument * doc = NULL;
    DomXml dom;
    doc = dom.stringToDom(data);
    validateSignedDOM(doc, rft);
}

void Encryption::validateSignedDOM(xercesc::DOMDocument * doc,
        Encryption::ResourceFileType rft)
        throw (CryptoException, SignedException)
{
    if (validateSigned(rft))
    {
        Signed objSigned;
        Smartmatic::System::Security::Cryptography::CertificateValidator validator;
        configSigned(objSigned, &validator, rft);

        if (!objSigned.validateXmlDigitalSignature(doc))
        {
            logger->Debug("Error validate signed");
            throw SignedException(_("Smartmatic.SAES.Security.Encryption.ErrorSignedValidate"), N_("Smartmatic.SAES.Security.Encryption.ErrorSignedValidate"), logger);
        }
    }
}

void Encryption::validateSignedFile(std::string & file,
        Encryption::ResourceFileType rft) throw (CryptoException, SignedException,
        XmlException)
{
    xercesc::DOMDocument * doc = NULL;
    Smartmatic::System::XML::DomXml dom;
    doc = dom.fileToDom(file);
    validateSignedDOM(doc, rft);
}

std::string Encryption::openXmlFile(std::string & file,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool isCompressed,
        bool pad)
        throw (Smartmatic::System::Exception::CryptoException,
                Smartmatic::System::Exception::SignedException,
                Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);

	std::stringstream ss;
	ss << "Open xml file " << file;
	logger->Debug(ss.str());

    Smartmatic::System::SafeBuffer buffer;
    decryptoFileToBuffer(file, buffer, rft, ukt, pad);

    std::string data;

    if (isCompressed)
    {
        std::stringstream ssc;
        ssc << "Decompress xml data of file " << file;
        logger->Debug(ssc.str());

        Smartmatic::System::SafeBuffer inflate;
        CompressionClass::Inflate(buffer, inflate);

        if (inflate.GetSize() > 0)
        {
        	data.assign((char *)inflate.GetData(), inflate.GetSize());
        	data.resize(inflate.GetSize());
        }
        else
        {
        	logger->Debug("File " + file + " not compress.");
        }

    }
    else if (buffer.GetSize() > 0)
    {
        data.assign((char *)buffer.GetData(), buffer.GetSize());
        data.resize(buffer.GetSize());
    }
    else
    {
    	logger->Debug("Error open xml file " + file);
    	return data;
    }

    validateSignedString(data, rft);

    logger->Debug("Success open xml file " + file + " with " + getUseKeyString(ukt));
    return data;
}

void Encryption::saveXmlFile(std::string & data, std::string & file,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool compress,
        bool pad)
        throw (Smartmatic::System::Exception::CryptoException,
                Smartmatic::System::Exception::SignedException,
                Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);

    logger->Debug("Save xml file " + file);

    xercesc::DOMDocument * doc = NULL;
    Smartmatic::System::XML::DomXml dom;
    doc = dom.stringToDom (data);
    signedDOM(doc, rft);

    std::string dataStr;
    dom.domToString(doc, dataStr);

    Smartmatic::System::SafeBuffer dataBuffer(dataStr);

    if (compress)
    {
        std::stringstream ssc;
        ssc << "Compress xml data of file " << file;
        logger->Debug(ssc.str());

        Smartmatic::System::SafeBuffer deflate;
        CompressionClass::Deflate(dataBuffer, deflate);

        if (deflate.GetSize() > 0)
        {
        	dataBuffer.Clear();
        	dataBuffer.AddData(deflate);
        }
        else
        {
        	logger->Debug("Error deflate data");
        	return;
        }

    }
    else if (dataBuffer.GetSize() == 0)
    {
    	logger->Debug("Error save xml file " + file);
    	return;
    }

    Smartmatic::System::SafeBuffer buffer;
    cryptoBufferToBuffer(dataBuffer, buffer, rft, ukt, pad);

    File::saveBufferToFile(buffer, file);

    logger->Debug("Success save xml file " + file + " with " + getUseKeyString(ukt));
}

Encryption * Encryption::getInstance()
{
    if (instance == NULL)
    {
        instance = new Encryption();
    }
    return instance;
}

std::string Encryption::cryptoStringToB64(std::string & data,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
	Smartmatic::System::SafeBuffer dataOut;
    cryptoStringToBuffer(data, dataOut, rft, ukt, pad);
    return dataOut.GetBase64Data();
}

std::string Encryption::cryptoStringToB64(std::string & data,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn((unsigned char *)data.c_str(), data.length());
    Smartmatic::System::SafeBuffer dataOut;

    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.cryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());

    return dataOut.GetBase64Data();
}

std::string Encryption::decryptoB64ToString(std::string & data,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn;
    Base64Encoder::ConvertFromBase64(data, dataIn);
    return decryptoBufferToString(dataIn, rft, ukt, pad);
}

std::string Encryption::decryptoB64ToString(std::string & data,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn;
    decryptoB64ToBuffer (data, dataIn, ukt, pad);
    std::string dataReturn;

    if (dataIn.GetSize() > 0)
    {
    	dataReturn.assign((const char *)dataIn.GetData(), dataIn.GetSize());
    	dataReturn.resize(dataIn.GetSize());
    }

    return dataReturn;
}

void Encryption::decryptoB64ToBuffer(std::string & data,
		Smartmatic::System::SafeBuffer & dataOut,
        UseKeyType ukt,
        bool pad)
        throw (Smartmatic::System::Exception::CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn;
    Base64Encoder::ConvertFromBase64(data, dataIn);

    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.decryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
}

void Encryption::cryptoBufferToBuffer(
        Smartmatic::System::SafeBuffer & data,
        Smartmatic::System::SafeBuffer & dataOut,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    if (cryptoData(rft))
    {
        cryptoBufferToBuffer(data, dataOut, ukt, pad);
    }
    else
    {
        dataOut.AddData(data);
    }
}

void Encryption::cryptoBufferToBuffer(
        Smartmatic::System::SafeBuffer & data,
        Smartmatic::System::SafeBuffer & dataOut,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.cryptoBufferToBuffer(data, dataOut, key.GetData(), iv.GetData());
}

void Encryption::cryptoStringToBuffer(std::string & data,
		Smartmatic::System::SafeBuffer & dataOut,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Smartmatic::System::SafeBuffer dataIn((unsigned char *)data.c_str(), data.length());
    cryptoBufferToBuffer(dataIn, dataOut, rft, ukt, pad);
}

std::string Encryption::decryptoBufferToString(Smartmatic::System::SafeBuffer & dataIn,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    std::string dataReturn;
    Smartmatic::System::SafeBuffer dataOut;
    decryptoBufferToBuffer(dataIn, dataOut, rft, ukt, pad);

    if (dataOut.GetSize() > 0)
    {
    	dataReturn.assign((const char *)dataOut.GetData(), dataOut.GetSize());
    	dataReturn.resize(dataOut.GetSize());
    }

    return dataReturn;
}

void Encryption::decryptoBufferToBuffer(
        Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut,
        Encryption::ResourceFileType rft,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    if (cryptoData(rft))
    {
        decryptoBufferToBuffer(dataIn, dataOut, ukt, pad);
    }
    else
    {
        dataOut.AddData(dataIn);
    }
}

void Encryption::decryptoBufferToBuffer(
        Smartmatic::System::SafeBuffer & dataIn,
        Smartmatic::System::SafeBuffer & dataOut,
        Encryption::UseKeyType ukt,
        bool pad)
    throw (CryptoException)
{
    Crypto objCrypto;
    objCrypto.init(keySize, modeType, pad);

    Smartmatic::System::SafeBuffer key;
    getUseKey(key, ukt);
    Smartmatic::System::SafeBuffer iv;
    getUseIV(key, iv, getIVLength());
    objCrypto.decryptoBufferToBuffer(dataIn, dataOut, key.GetData(), iv.GetData());
}

Smartmatic::System::SafeBuffer Encryption::getVerificationKey() const
{
    Glib::ustring strKey = m_SecretKey->getKeyBase64();
    strKey += "_";
    strKey += openingCode.ToBase64String();
    return MsgDigestUtil::Digest(strKey, MsgDigestUtil::DGSTUTIL_SHA256);
}

const Smartmatic::SAES::Common::Security::SecretKey& Encryption::getSecretKey ()
{
	return (*m_SecretKey);
}

const Smartmatic::System::SafeBuffer & Encryption::getInitKey() const
{
    return initKey;
}

void Encryption::setOpeningCode(Smartmatic::System::GuidClass & openingCode)
{
	logger->Debug("set opening code " + openingCode.ToString());
    this->openingCode = openingCode;
}

const Smartmatic::System::GuidClass & Encryption::getOpeningCode()
{
	return this->openingCode;
}

Signed::SignedType Encryption::signedData(Encryption::ResourceFileType rft)
{
    Smartmatic::System::Security::Signed::SignedType signedType;
    Smartmatic::SAES::Common::Configuration::SignedType type;

    switch (rft)
    {
        case INSTALL_FILE:
            type = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getMachineSecuritySchema().getInstallationFiles().getSignedData();
            break;
        case EXTERNAL_FILE:
            type = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getMachineSecuritySchema().getExternalFiles().getSignedData();
            break;
        case INTERNAL_FILE:
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getSignedData();
            break;
        case RESOURCE_FILE:
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getSignedData();
            break;
        case EXCHANGE_FILE:
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getSignedData();
            break;
        case UTIL_FILE:
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getSignedData();
            break;
        case PRINTED_VOTE:
        	type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getSignedData();
        	 break;
    }

    switch(type)
    {
        case SignedType::CONFIGURATION_SIMPLE:
            signedType = Signed::SIMPLE_SIGNED;
            break;
        case SignedType::CONFIGURATION_FULL:
            signedType = Signed::FULL_SIGNED;
            break;
        default:
            signedType = Signed::DONT_SIGNED;
            break;
    }

    return signedType;
}

void Encryption::SignDataWithPersonalCertificate(Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & dataOut)
{
//	RsaUtil rsa;
//	std::string certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedFilePath();
//	std::string path = Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile);
//	rsa.SetPrivateKey_PKCS12(path,signedSecretKey);
//	rsa.SignData(dataIn,dataOut);

	Glib::ustring certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedFilePath();
	Glib::ustring path = Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile);
	SignatureAlgorithm* signer = SignatureAlgorithm::CreateForSign(path,signedSecretKey);
	try
	{
		signer->SignData(dataIn,dataOut, MsgDigestUtil::DGSTUTIL_MD5);
		delete signer;
	}
	catch(...)
	{
		delete signer;
		throw;
	}

}

bool Encryption::VerifySignatureWithPersonalCertificate(Smartmatic::System::SafeBuffer & dataIn, Smartmatic::System::SafeBuffer & signature)
{
	//RsaUtil rsa;
	//std::string certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedFilePath();
	//std::string path = Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile);
	//rsa.SetPublicKey_FromCert(path,signedSecretKey, CertUtil::CertFormat_PKCS12);

	//return rsa.VerifySignature(dataIn,signature);

	bool retVal = false;
	Glib::ustring certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedFilePath();
	Glib::ustring path = Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile);
	SignatureAlgorithm* signer = SignatureAlgorithm::CreateForVerify(path,signedSecretKey,CertUtil::CertFormat_PKCS12);
	try
	{
		retVal = signer->VerifySignature(dataIn,signature, MsgDigestUtil::DGSTUTIL_MD5);
		delete signer;
	}
	catch(...)
	{
		delete signer;
		throw;
	}
	return retVal;
}

bool Encryption::validateSigned(Encryption::ResourceFileType rft)
{
    bool validate = false;

    switch (rft)
    {
        case INSTALL_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getValidateSigned();
            break;
        case EXTERNAL_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getValidateSigned();
            break;
        case INTERNAL_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getValidateSigned();
            break;
        case RESOURCE_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getValidateSigned();
            break;
        case EXCHANGE_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getValidateSigned();
            break;
        case UTIL_FILE:
            validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getValidateSigned();
            break;
        case PRINTED_VOTE:
        	validate = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getValidateSigned();
        	break;
    }

    return validate;
}

bool Encryption::cryptoData(Encryption::ResourceFileType rft)
{
    bool crypto = false;

    switch (rft)
    {
        case INSTALL_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getEncryptedData();
            break;
        case EXTERNAL_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getEncryptedData();
            break;
        case INTERNAL_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getEncryptedData();
            break;
        case RESOURCE_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getEncryptedData();
            break;
        case EXCHANGE_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getEncryptedData();
            break;
        case UTIL_FILE:
            crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getEncryptedData();
            break;
        case PRINTED_VOTE:
        	crypto = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getEncryptedData();
        	break;
    }

    return crypto;
}

void Encryption::getUseKey(Smartmatic::System::SafeBuffer & retVal, Encryption::UseKeyType ukt) const
{
    const unsigned char * key = NULL;
    int size = 0;
    Smartmatic::System::SafeBuffer verKey;

    switch(ukt)
    {
		case UP_KEY:
			if (m_UPKey)
			{
				key = m_UPKey->getKey(size);
				retVal.AddData(key, size);
			}
			else
			{
	            key = m_SecretKey->getKey(size);
	            retVal.AddData(key, size);
			}
			break;
        case SECRET_KEY:
            key = m_SecretKey->getKey(size);
            retVal.AddData(key, size);
            break;

        case VERIFICATION_KEY:
        	verKey = getVerificationKey();
            retVal.AddData(verKey);
            break;

        case INIT_KEY:
            retVal.AddData(initKey);
            break;
        default:
            break;
    }
}

std::string Encryption::getUseKeyString(UseKeyType ukt)
{
	std::string value;

    switch(ukt)
    {
		case UP_KEY:

			if (m_UPKey)
			{
				value = "UP_KEY";
			}
			else
			{
	            value = "SECRET_KEY";
			}
			break;

        case SECRET_KEY:
            value = "SECRET_KEY";
            break;

        case VERIFICATION_KEY:
            value = "VERIFICATION_KEY";
            break;

        case INIT_KEY:
            value = "INIT_KEY";
            break;

        default:
            value = "WITHOUT_KEY";
            break;
    }

    return value;
}

void Encryption::getComposeKey(const Smartmatic::System::SafeBuffer & key, Smartmatic::System::SafeBuffer & result, unsigned int length)
{
	if (key.GetData() != NULL)
	{
		unsigned int size = key.GetSize();
		unsigned char * info = new unsigned char[size];
		const unsigned char * array = key.GetData();

		for (unsigned int i = 0; i < size; i++)
		{
			bool high = (array[i] % 2) == 0;
			info[i] = (unsigned char)(high ? (array[i] & 0xF0) : (array[i] & 0x0F));
		}

		Smartmatic::System::SafeBuffer hash = MsgDigestUtil::Digest(info, size, MsgDigestUtil::DGSTUTIL_SHA1);

		delete []info;

		if (hash.GetSize() < length)
		{
			unsigned int pasted = 0;
			while (pasted < length)
			{
				int lengthToCopy = (hash.GetSize() < (length - pasted) ? hash.GetSize() : (length - pasted));
				result.AddData(hash.GetData(), lengthToCopy);
				pasted += lengthToCopy;
			}
		}
		else
		{
			result.AddData(hash.GetData(), length);
		}
	}
}

void Encryption::getUseIV(Smartmatic::System::SafeBuffer & key, Smartmatic::System::SafeBuffer & result, unsigned int length)
{
	if (length == 0)
	{
		length = getIVLength();
	}

	getComposeKey(key, result, length);
}

int Encryption::getCertificateValidatorFlags(Encryption::ResourceFileType rft)
{
    int flags = 0;
    SecurityFileConfiguration::ValidateCertifiedConfigSequence sequence;

    switch(rft)
    {
        case INSTALL_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getValidateCertifiedConfig();
            break;
        case EXTERNAL_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getValidateCertifiedConfig();
            break;
        case INTERNAL_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getValidateCertifiedConfig();
            break;
        case RESOURCE_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getValidateCertifiedConfig();
            break;
        case EXCHANGE_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getValidateCertifiedConfig();
            break;
        case UTIL_FILE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getValidateCertifiedConfig();
            break;
        case PRINTED_VOTE:
            sequence = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getValidateCertifiedConfig();
            break;
    }

    for (unsigned int i = 0;i < sequence.size();i++)
    {
        switch (sequence[i])
        {
            case ValidateCertifiedConfiguration::CONFIGURATION_NO_FLAGS:
                flags |= Cryptography::VERIFY_NO_FLAGS;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_DO_NOT_VALIDATE:
                flags |= Cryptography::VERIFY_DO_NOT_VALIDATE;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_IGNORE_CRITICAL:
                flags |= Cryptography::VERIFY_IGNORE_CRITICAL;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_CB_ISSUER_CHECK:
                flags |= Cryptography::VERIFY_CB_ISSUER_CHECK;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_CRL_CHECK:
                flags |= Cryptography::VERIFY_CRL_CHECK;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_CRL_CHECK_ALL:
                flags |= Cryptography::VERIFY_CRL_CHECK_ALL;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_POLICY_CHECK:
                flags |= Cryptography::VERIFY_POLICY_CHECK;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_EXPLICIT_POLICY:
                flags |= Cryptography::VERIFY_EXPLICIT_POLICY;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_INHIBIT_ANY:
                flags |= Cryptography::VERIFY_INHIBIT_ANY;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_INHIBIT_MAP:
                flags |= Cryptography::VERIFY_INHIBIT_MAP;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_X509_STRICT:
                flags |= Cryptography::VERIFY_X509_STRICT;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_EXTENDED_CRL_SUPPORT:
                flags |= Cryptography::VERIFY_EXTENDED_CRL_SUPPORT;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_USE_DELTAS:
                flags |= Cryptography::VERIFY_USE_DELTAS;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_NOTIFY_POLICY:
                flags |= Cryptography::VERIFY_NOTIFY_POLICY;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_CHECK_SS_SIGNATURE:
                flags |= Cryptography::VERIFY_CHECK_SS_SIGNATURE;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_SET_CHECK_TIME:
                flags |= Cryptography::VERIFY_SET_CHECK_TIME;
                break;
            case ValidateCertifiedConfiguration::CONFIGURATION_ALLOW_PROXY_CERTS:
                flags |= Cryptography::VERIFY_ALLOW_PROXY_CERTS;
                break;
        }
    }

    return flags;
}

void Encryption::configSigned(Smartmatic::System::Security::Signed & objSigned,
        Smartmatic::System::Security::Cryptography::CertificateValidator * validator,
        Encryption::ResourceFileType rft)
{
    std::string certifiedFile;
    CertifiedType type;
    bool validated = false;

    switch(rft)
    {
        case INSTALL_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInstallationFiles().getValidateCertified();
            break;
        case EXTERNAL_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExternalFiles().getValidateCertified();
            break;
        case INTERNAL_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getInternalFiles().getValidateCertified();
            break;
        case RESOURCE_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getResourcesFiles().getValidateCertified();
            break;
        case EXCHANGE_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getExchangeFiles().getValidateCertified();
            break;
        case UTIL_FILE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getUtilFiles().getValidateCertified();
            break;
        case PRINTED_VOTE:
            certifiedFile = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedFilePath();
            type = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getCertifiedType();
            validated = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getPrintedVoteData().getValidateCertified();
            break;
    }

    switch(type)
    {
        case CertifiedType::CONFIGURATION_PCKS12:
        	if(Smartmatic::System::IO::File::canOpenFile(Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile)))
        	{
        		objSigned.loadPKCS12(signedSecretKey, Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile));
        	}
        	else
        	{
        		objSigned.loadPKCS12(signedSecretKey, Smartmatic::System::IO::Path::Combine(directories->getBasePath(
        				Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH), certifiedFile));
        	}
            break;
        case CertifiedType::CONFIGURATION_X509:
        	if(Smartmatic::System::IO::File::canOpenFile(Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile)))
        	{
                objSigned.loadCertifiedX509(Smartmatic::System::IO::Path::Combine(directories->getBasePath(), certifiedFile),
                		CertUtil::CertFormat_PEM);
        	}
        	else
        	{
                objSigned.loadCertifiedX509(Smartmatic::System::IO::Path::Combine(directories->getBasePath(
                		Smartmatic::SAES::Common::Configuration::BasePathType::CONFIGURATION_FLASH), certifiedFile),
                		CertUtil::CertFormat_PEM);
        	}
            break;
        case CertifiedType::CONFIGURATION_NONE:
            break;
    }

    if (validator != NULL && validated)
    {
        validator->SetOptions((Cryptography::CertificateValidationFlags)getCertificateValidatorFlags(rft));
        time_t timeCertified = getCertificateValidatorTime();

        if (timeCertified != 0)
        {
            validator->SetVerificationTime(timeCertified);
        }

        if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getImplementCACertificateFileName())
        {
            std::string file;

            if(File::canOpenFile(directories->getCACertificateFileFullPath()))
            {
                file = directories->getCACertificateFileFullPath();
            }
            else
            {
                file = directories->getCACertificateInstalationFileFullPath();
            }

            validator->SetCACertificate(file, CertUtil::CertFormat_PEM);
        }

        if (SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getImplementItermediateCACertificates())
        {
            std::string file;

            if(File::canOpenFile(directories->getItermediateCACertificatesFileFullPath()))
            {
                file = directories->getItermediateCACertificatesFileFullPath();
            }
            else
            {
                file = directories->getItermediateCACertificatesInstalationFileFullPath();
            }

            validator->SetItermediateCACertificates(file, CertUtil::CertFormat_PEM);
        }

        if(SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getImplementTrustedCertificates())
        {
            std::string file;

            if(File::canOpenFile(directories->getTrustedCertificatesFileFullPath()))
            {
                file = directories->getTrustedCertificatesFileFullPath();
            }
            else
            {
                file = directories->getTrustedCertificatesInstalationFileFullPath();
            }
            validator->SetTrustedCertificates(file, CertUtil::CertFormat_PEM);
        }

        objSigned.LoadCertificateValidator(validator);
    }
}

void Encryption::setMachineTime(double machineTime)
{
    this->machineTime = machineTime;
}

time_t Encryption::getCertificateValidatorTime()
{
    Glib::TimeVal time;
    Glib::ustring dateStr = "";
    double timeD = 0;

    TimeConfiguration type =
            SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getValidateCertifiedTime();

    switch(type)
    {
        case TimeConfiguration::CONFIGURATION_CONFIG_TIME:
            dateStr = SAESCommonConfigurationManager::Current()->getSecurityConfiguration().getCertifiedTime();
            time.assign_from_iso8601(dateStr);
            timeD = time.as_double();
            break;
        case TimeConfiguration::CONFIGURATION_MACHINE_TIME:
            timeD = machineTime;
            break;
        case TimeConfiguration::CONFIGURATION_NONE:
            timeD = 0;
            break;
    }

    return (time_t)timeD;
}

unsigned int Encryption::getKeyLength()
{
	unsigned int leng = 0;

	switch(keySize)
	{
		case Crypto::KEY_AES_256:
			leng = 32;
			break;

		case Crypto::KEY_AES_192:
			leng = 24;
			break;

		case Crypto::KEY_AES_128:
			leng = 16;
			break;
	}

	return leng;
}

unsigned int Encryption::getIVLength()
{
	return 16;  // AES::BLOCKSIZE
}

Smartmatic::System::Security::Crypto::KeySize Encryption::getKeySize()
{
	return this->keySize;
}

Smartmatic::System::Security::Crypto::Mode Encryption::getModeType()
{
	return this->modeType;
}

std::string Encryption::getSignedSecretKey()
{
	return signedSecretKey;
}
