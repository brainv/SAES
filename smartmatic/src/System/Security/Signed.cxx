/**
 * @file Signed.cxx
 * @brief Body class for Signed file
 */

#include "Signed.hxx"
#include "System/Security/Cryptography/CryptoPKCS12.hxx"
#include "System/Security/Cryptography/PKCS7Signer.hxx"
#include "System/Security/Cryptography/CMSSigner.hxx"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xsec/framework/XSECException.hpp>
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGReference.hpp>
#include <openssl/x509.h>

#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyHMAC.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyRSA.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyDSA.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyEC.hpp>
#include <xsec/enc/XSECCryptoException.hpp>
#include <xsec/xenc/XENCCipher.hpp>
#include <xsec/enc/XSECCryptoKeyRSA.hpp>
#include <xsec/dsig/DSIGKeyInfoX509.hpp>
#include <openssl/safestack.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/XML/DomXml.hxx>
#include <glibmm.h>
#include <glib.h>

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

#define DSIGNS_PREFIX "" ///< prefix signed node

using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

ISMTTLog* Signed::logger = SMTTLogManager::GetLogger("Smartmatic.System.Security.Signed",GETTEXT_PACKAGE);

Signed::Signed()
: SecurityBase(), hashAlgorithm(HASH_SHA1)
{
    this->privateKey = NULL;
    this->validator = NULL;
}

Signed::~Signed()
{
    if (cryptoP12 != NULL)
    {
        delete cryptoP12;
        cryptoP12 = NULL;
    }
    if(privateKey)
    {
        g_free(privateKey);
        privateKey = NULL;
    }
    if(certifiedX509)
    {
        X509_free(certifiedX509);
        certifiedX509 = NULL;
    }
    if (certPrivateKey)
    {
    	EVP_PKEY_free(certPrivateKey);
    	certPrivateKey = NULL;
    }
}

void Signed::SetHashAlgorithm(DigestAlgType hashType)
{
  hashAlgorithm = Traslate(hashType);
}

void Signed::SetPrivateKey(const unsigned char* seckey, int keyLen)
{
  if(privateKey)
  {
     g_free(privateKey);
     privateKey = NULL;
  }
  privateKey = static_cast<unsigned char*>(g_malloc(keyLen));
  keySize = static_cast<unsigned int>(keyLen);
  memcpy(privateKey,seckey,keyLen);
}

hashMethod Signed::Traslate(Smartmatic::System::Security::Cryptography::DigestAlgType digestype )
{
  hashMethod retVal = HASH_SHA1;

  switch(digestype)
  {
  case DGSTUTIL_MD5:
    retVal = HASH_MD5;
    break;
  case DGSTUTIL_SHA1:
    retVal = HASH_SHA1;
    break;
  case DGSTUTIL_SHA224:
    retVal = HASH_SHA224;
    break;
  case DGSTUTIL_SHA256:
    retVal = HASH_SHA256;
    break;
  case DGSTUTIL_SHA384:
    retVal = HASH_SHA384;
    break;
  case DGSTUTIL_SHA512:
    retVal = HASH_SHA512;
    break;
  default:
    retVal = HASH_SHA1;
    break;
  }

  return retVal;
}

void Signed::LoadCertificateValidator(CertificateValidator * validator)
    throw (SignedException)
{
    this->validator = validator;
}

void Signed::signedHMACDOM(xercesc::DOMDocument * doc, Signed::SignedType signedType) throw (SignedException)
{
    if (signedType == Signed::DONT_SIGNED)
    {
        return;
    }

    if (privateKey == NULL)
    {
        logger->Debug("Error - SignedHMACDOM - private key NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"),logger);
    }

    if (doc == NULL)
    {
        logger->Debug("Error - SignedHMACDOM - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"),logger);
    }

    XSECProvider prov;
    xercesc::DOMElement *rootElem = NULL;
    xercesc::DOMElement *sigNode = NULL;
    DSIGSignature *sig = NULL;
    OpenSSLCryptoKeyHMAC * key = NULL;

    try
    {
        rootElem = doc->getDocumentElement();

        sig = prov.newSignature();
        sig->setDSIGNSPrefix(MAKE_UNICODE_STRING(DSIGNS_PREFIX));

        sigNode = sig->createBlankSignature(doc, CANON_C14N_NOC,
                SIGNATURE_HMAC, hashAlgorithm);

        key = new OpenSSLCryptoKeyHMAC();
        key->setKey(privateKey,keySize);

        rootElem->appendChild(doc->createTextNode(MAKE_UNICODE_STRING("\n")));
        rootElem->appendChild(sigNode);
        rootElem->appendChild(doc->createTextNode(MAKE_UNICODE_STRING("\n")));

        sig->setSigningKey(key);
        sig->sign();

    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        std::stringstream ss;
        ss << "FATAL - " << msg;
		logger->Debug(ss.str());
        XMLString::release(&msg);
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"), N_("Smartmatic.System.Security.Signed.ErrorSignedHMAC"),logger);
    }
}

void Signed::signedRSADOM(xercesc::DOMDocument * doc, Signed::SignedType signedType) throw (SignedException)
{
    if (signedType == Signed::DONT_SIGNED)
    {
        return;
    }

    if (cryptoP12 == NULL)
    {
        logger->Debug("Error - SignedRSADOM - cryptoP12 NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedRSA"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedRSA"),logger);
    }

    if (doc == NULL)
    {
        logger->Debug("Error - SignedRSADOM - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedRSA"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedRSA"),logger);
    }

    XSECProvider prov;
    xercesc::DOMElement *rootElem = NULL;
    xercesc::DOMElement *sigNode = NULL;
    DSIGSignature *sig = NULL;
    OpenSSLCryptoKeyRSA * key = NULL;
    EVP_PKEY * pk = NULL;

    try
    {
        rootElem = doc->getDocumentElement();

        sig = prov.newSignature();
        sig->setDSIGNSPrefix(MAKE_UNICODE_STRING(DSIGNS_PREFIX));
        sig->setPrettyPrint(true);

        sigNode = sig->createBlankSignature(doc, CANON_C14N_NOC, SIGNATURE_RSA,
            hashAlgorithm);

        pk = cryptoP12->getPrimaryKey();
        key = new OpenSSLCryptoKeyRSA(pk);

        rootElem->appendChild(sigNode);
        rootElem->appendChild(doc->createTextNode(MAKE_UNICODE_STRING("\n")));

        if (signedType == Signed::FULL_SIGNED)
        {
            OpenSSLCryptoX509 * x509 = new OpenSSLCryptoX509(cryptoP12->getCertified());
            setKeyInfo(sig, x509);
        }

        sig->setSigningKey(key);
        sig->sign();

    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        std::stringstream ss;
        ss << "FATAL - " << msg;
		logger->Debug(ss.str());
        XMLString::release(&msg);
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedRSA"), N_("Smartmatic.System.Security.Signed.ErrorSignedRSA"),logger);
    }
}


void Signed::signDOMWithCertificate(xercesc::DOMDocument * doc, Signed::SignedType signedType)
throw (Smartmatic::System::Exception::SignedException)
{
	if (signedType == Signed::DONT_SIGNED)
	    {
	        return;
	    }

	    if (cryptoP12 == NULL)
	    {
	        logger->Debug("Error - Sign Dom - cryptoP12 NULL");
	        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedCert"),
	                        N_("Smartmatic.System.Security.Signed.ErrorSignedCert"),logger);
	    }

	    if (doc == NULL)
	    {
	        logger->Debug("Error - Sign Dom - doc NULL");
	        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedCert"),
	                        N_("Smartmatic.System.Security.Signed.ErrorSignedCert"),logger);
	    }

	    XSECProvider prov;
	    xercesc::DOMElement *rootElem = NULL;
	    xercesc::DOMElement *sigNode = NULL;
	    DSIGSignature *sig = NULL;
	    XSECCryptoKey * key = NULL;


	    try
	    {
	        rootElem = doc->getDocumentElement();

	        sig = prov.newSignature();
	        sig->setDSIGNSPrefix(MAKE_UNICODE_STRING(DSIGNS_PREFIX));
	        sig->setPrettyPrint(true);

	        //Get the signature algorithm from the key
	        signatureMethod sigMethod = getSignatureMethodFromPrimaryKey(cryptoP12);
	        sigNode = sig->createBlankSignature(doc, CANON_C14N_NOC, sigMethod , hashAlgorithm);

	        rootElem->appendChild(sigNode);
	        rootElem->appendChild(doc->createTextNode(MAKE_UNICODE_STRING("\n")));

	        switch(sigMethod)
	        {
	        	case SIGNATURE_DSA:
	        		key = new OpenSSLCryptoKeyDSA(cryptoP12->getPrimaryKey());
	        		break;
	        	case SIGNATURE_RSA:
	        		key = new OpenSSLCryptoKeyRSA(cryptoP12->getPrimaryKey());
	        	break;
	        	case SIGNATURE_ECDSA:
	        		key = new OpenSSLCryptoKeyEC(cryptoP12->getPrimaryKey());
	        		break;
	        	default:
	        		throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedCert"),
	        				N_("Smartmatic.System.Security.Signed.ErrorSignedCert"),logger);
	        		break;
	        }

	        if (signedType == Signed::FULL_SIGNED)
	        {
	            OpenSSLCryptoX509 * x509 = new OpenSSLCryptoX509(cryptoP12->getCertified());
	            setKeyInfo(sig, x509);
	        }

	        sig->setSigningKey(key);
	        sig->sign();
	    }
	    catch (XSECException &ex)
	    {
	        char * msg = XMLString::transcode(ex.getMsg());
	        std::stringstream ss;
	        ss << "FATAL - " << msg;
			logger->Debug(ss.str());
	        XMLString::release(&msg);
	        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedCert"), N_("Smartmatic.System.Security.Signed.ErrorSignedCert"),logger);
	    }

}

signatureMethod Signed::getSignatureMethodFromPrimaryKey(Smartmatic::System::Security::Cryptography::CryptoPKCS12* p12Container)
{
	EVP_PKEY * pk = p12Container->getPrimaryKey();


	logger->Debug(Glib::ustring::compose("Primary Key type: %1", pk->type));

	signatureMethod retVal = SIGNATURE_NONE;
	switch (pk->type)
			{
		case EVP_PKEY_RSA:
		case EVP_PKEY_RSA2:
			retVal = SIGNATURE_RSA;
		break;
		case EVP_PKEY_DSA:
		case EVP_PKEY_DSA1:
		case EVP_PKEY_DSA2:
		case EVP_PKEY_DSA3:
		case EVP_PKEY_DSA4:
			retVal = SIGNATURE_DSA;
			break;
		case EVP_PKEY_EC:
			retVal = SIGNATURE_ECDSA;
			break;
		default:
			retVal = SIGNATURE_NONE;
			break;
			}


	return retVal;
}
void Signed::signDOMWithDSA(xercesc::DOMDocument * doc, Signed::SignedType signedType)
throw (Smartmatic::System::Exception::SignedException)
{
    if (signedType == Signed::DONT_SIGNED)
    {
        return;
    }

    if (cryptoP12 == NULL)
    {
        logger->Debug("Error - SignDOMWithDSA - cryptoP12 NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedDSA"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedDSA"),logger);
    }

    if (doc == NULL)
    {
        logger->Debug("Error - SignDOMWithDSA - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedDSA"),
                        N_("Smartmatic.System.Security.Signed.ErrorSignedDSA"),logger);
    }

      XSECProvider prov;
      xercesc::DOMElement *rootElem = NULL;
      xercesc::DOMElement *sigNode = NULL;
      DSIGSignature *sig = NULL;
      OpenSSLCryptoKeyDSA * key = NULL;
      EVP_PKEY * pk = NULL;

      try
      {
          rootElem = doc->getDocumentElement();

          sig = prov.newSignature();
          sig->setDSIGNSPrefix(MAKE_UNICODE_STRING(DSIGNS_PREFIX));

          sigNode = sig->createBlankSignature(doc, CANON_C14N_NOC, SIGNATURE_DSA,
              hashAlgorithm);

          pk = cryptoP12->getPrimaryKey();
          key = new OpenSSLCryptoKeyDSA(pk);
          rootElem->appendChild(sigNode);
          rootElem->appendChild(doc->createTextNode(MAKE_UNICODE_STRING("\n")));

          if (signedType == Signed::FULL_SIGNED)
          {
              OpenSSLCryptoX509 * x509 = new OpenSSLCryptoX509(cryptoP12->getCertified());
              setKeyInfo(sig, x509);
          }

          sig->setSigningKey(key);
          sig->sign();

      }
      catch (XSECException &ex)
      {
          char * msg = XMLString::transcode(ex.getMsg());
          std::stringstream ss;
          ss << "FATAL - " << msg;
		  logger->Debug(ss.str());
          XMLString::release(&msg);
          throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSignedDSA"), N_("Smartmatic.System.Security.Signed.ErrorSignedDSA"), logger);
      }
}

bool Signed::validateXmlDigitalSignature(xercesc::DOMDocument *doc, Signed::ValidateType validateType)
throw (Smartmatic::System::Exception::SignedException)
{
    if (doc == NULL)
    {
        logger->Debug("Error - ValidateXmlDigitalSignature - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
              N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }

    XSECProvider prov;
    DSIGSignature * sig = NULL;
    bool validate = false;

    try
    {
        sig = prov.newSignatureFromDOM(doc);
        OpenSSLCryptoX509 * x509 = getX509(doc, validateType);

        sig->load();
        sig->setSigningKey(x509->clonePublicKey());

        validate = sig->verify();
    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        std::stringstream ss;
        ss << "FATAL - " << msg;
		logger->Debug(ss.str());
        XMLString::release(&msg);
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
              N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }
    catch (XSECCryptoException &ex)
    {
        std::stringstream ss;
        ss << "FATAL - " << ex.getMsg();
		logger->Debug(ss.str());
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
              N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }
    catch (std::exception &ex)
    {
        std::stringstream ss;
        ss << "FATAL - " << ex.what();
        logger->Debug(ss.str());
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
              N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }
    catch (...)
    {
        logger->Debug("FATAL - error " + std::string(__func__));
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
              N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }

    return validate;
}

bool Signed::validateSignedHMACDOM(xercesc::DOMDocument *doc)
        throw (SignedException)
{
    if (privateKey == NULL)
    {
        logger->Debug("Error - ValidateSignedHMACDOM - private key NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
            N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }

    if (doc == NULL)
    {
        logger->Debug("Error - ValidateSignedHMACDOM - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
            N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }

    XSECProvider prov;
    DSIGSignature * sig = NULL;
    OpenSSLCryptoKeyHMAC * key = NULL;
    bool validate = false;

    try
    {
        sig = prov.newSignatureFromDOM(doc);
        key = new OpenSSLCryptoKeyHMAC();
        key->setKey(privateKey, keySize);

        sig->load();
        sig->setSigningKey(key);

        validate = sig->verify();
    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        std::stringstream ss;
        ss << "FATAL - " << msg;
		logger->Debug(ss.str());
        XMLString::release(&msg);
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidateSignedHMAC"),
                N_("Smartmatic.System.Security.Signed.ErrorValidateSignedHMAC"),logger);
    }

    return validate;
}

/*bool Signed::validateSignedRSADOM(xercesc::DOMDocument *doc, Signed::ValidateType validateType)
        throw (SignedException)
{
    if (doc == NULL)
    {
        logger->Debug("Error - ValidateSignedRSADOM - doc NULL");
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),
                N_("Smartmatic.System.Security.Signed.ErrorValidatingDigitalXmlSignature"),logger);
    }

    XSECProvider prov;
    DSIGSignature * sig = NULL;
    bool validate = false;

    try
    {
        sig = prov.newSignatureFromDOM(doc);
        OpenSSLCryptoX509 * x509 = getX509(doc, validateType);

        sig->load();
        sig->setSigningKey(x509->clonePublicKey());

        validate = sig->verify();
    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        std::stringstream ss;
        ss << "FATAL - " << msg;
		logger->Debug(ss.str());
        XMLString::release(&msg);
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidateSignedRSA"),
                N_("Smartmatic.System.Security.Signed.ErrorValidateSignedRSA"),logger);
    }
    catch (XSECCryptoException &ex)
    {
        std::stringstream ss;
        ss << "FATAL - " << ex.getMsg();
		logger->Debug(ss.str());
        throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidateSignedRSA"),
                N_("Smartmatic.System.Security.Signed.ErrorValidateSignedRSA"),logger);
    }

    return validate;
}*/

void Signed::setKeyInfo(DSIGSignature * sig, OpenSSLCryptoX509 * x509)
{
    DSIGReference* ref = NULL;
    ref = sig->createReference(MAKE_UNICODE_STRING(""));
    ref->appendEnvelopedSignatureTransform();

    safeBuffer sb;
    const char * b64CertStr = NULL;
    const XMLCh * b64Cert = NULL;

    DSIGKeyInfoX509* keyInfoX509 = NULL;
    sb = x509->getDEREncodingSB();
    keyInfoX509 = sig->appendX509Data();

    char buf[1024];
    X509_NAME_oneline(X509_get_subject_name(x509->getOpenSSLX509()), buf, 1024);

    std::string str = buf;
    bool change = true;

    if (change)
    {
        std::string::size_type pos;
        str.replace(str.find("/"), 1, "");

        for (pos = str.find("/"); pos != std::string::npos; pos = str.find("/", pos+1)) {
            str.replace(pos, 1, ",");
        }
    }

    keyInfoX509->setX509SubjectName(MAKE_UNICODE_STRING(str.c_str()));

    b64CertStr = sb.rawCharBuffer();
    b64Cert = XMLString::transcode(b64CertStr);
    keyInfoX509->appendX509Certificate(b64Cert);
}

OpenSSLCryptoX509 * Signed::getX509(xercesc::DOMDocument * doc, Signed::ValidateType validateType)
    throw (SignedException)
{
    OpenSSLCryptoX509 * x509 = NULL;

    std::string cert;
    xercesc::DOMNode * elementX509Certificate = doc->getDocumentElement();
    Smartmatic::System::XML::DomXml domXml;

    elementX509Certificate = domXml.getNode(elementX509Certificate, "Signature");
    elementX509Certificate = domXml.getNode(elementX509Certificate, "KeyInfo");
    elementX509Certificate = domXml.getNode(elementX509Certificate, "X509Data");
    elementX509Certificate = domXml.getNode(elementX509Certificate, "X509Certificate");

    if (elementX509Certificate != NULL)
    {
        elementX509Certificate = elementX509Certificate->getFirstChild();
    }

    if (elementX509Certificate == NULL || elementX509Certificate->getNodeType() != xercesc::DOMNode::TEXT_NODE)
    {
      //  throw SignedException(_("Smartmatic.System.Security.Signed.ErrorSigned"), N_("Smartmatic.System.Security.Signed.ErrorSigned"),logger);

        if (cryptoP12 != NULL && validateType == VALIDATE_PKCS12)
        {
            x509 = new OpenSSLCryptoX509(cryptoP12->getCertified());
        }
        else if (certifiedX509 != NULL && validateType == VALIDATE_X509)
        {
            x509 = new OpenSSLCryptoX509(certifiedX509);
        }
    }
    else
    {
		char * msg = XMLString::transcode(elementX509Certificate->getTextContent());
		cert = msg;
		x509 = new OpenSSLCryptoX509();
		x509->loadX509Base64Bin(cert.c_str(), cert.length());
		XMLString::release(&msg);
    }

    if (validator != NULL)
    {
        CertValidationResult result;
        result = validator->VerifyX509Certificate(x509, DefaultPurpose);
        std::stringstream message;
        message << "Validation = ";
        message << result.GetSucces();
        message << " result = ";
        message << result.GetDetail();
        logger->Debug(message.str());

        if (!result.GetSucces())
        {
            throw SignedException(_("Smartmatic.System.Security.Signed.ErrorValidatingSignature"), N_("Smartmatic.System.Security.Signed.ErrorValidatingSignature"),logger);
        }
    }

    return x509;
}

void Signed::pkcs7SignerBuffer(Smartmatic::System::SafeBuffer & bufferIn,
	Smartmatic::System::SafeBuffer & bufferOut)
	throw (Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::CryptoException)
{
	if (cryptoP12)
	{
		PKCS7Signer signer(cryptoP12);
		signer.signedBuffer(bufferIn, bufferOut, PKCS7Signer::PKCS7_ASN1);
	}
	else if (certPrivateKey && certifiedX509)
	{
		PKCS7Signer signer(certPrivateKey, certifiedX509);
		signer.signedBuffer(bufferIn, bufferOut, PKCS7Signer::PKCS7_ASN1);
	}
}

void Signed::pkcs7ValidateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
		Smartmatic::System::SafeBuffer & bufferSigned)
	throw (Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::CryptoException)
{
	//PKCS7Signer signer;
	//signer.validateBuffer(bufferIn, bufferSigned, cryptoP12, PKCS7Signer::PKCS7_PEM);
}

void Signed::cmsSignerBuffer(Smartmatic::System::SafeBuffer & bufferIn,
	Smartmatic::System::SafeBuffer & bufferOut)
	throw (Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::CryptoException)
{
	CMSSigner signer;
	signer.signedBuffer(bufferIn, bufferOut, cryptoP12, CMSSigner::CMS_ASN1);
}

void Signed::cmsValidateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
		Smartmatic::System::SafeBuffer & bufferSigned)
	throw (Smartmatic::System::Exception::SignedException,
			Smartmatic::System::Exception::CryptoException)
{
	//CMSSigner signer;
	//signer.validateBuffer(bufferIn, bufferSigned, cryptoP12, CMSSigner::CMS_PEM);
}
