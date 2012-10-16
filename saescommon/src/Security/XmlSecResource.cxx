/**
 * @file XmlSecResource.cxx
 * @brief Body class XmlSecResource
 */

#include "XmlSecResource.hxx"

#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/IO/File.h>
#include <System/XML/DomXml.hxx>
#include <xercesc/util/PlatformUtils.hpp>
#include <xsec/framework/XSECException.hpp>
#include <Security/Encryption.hxx>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include <xsec/utils/unixutils/XSECURIResolverGenericUnix.hpp>
#include <xsec/enc/XSECCryptoException.hpp>

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

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::XML;

ISMTTLog* XmlSecResource::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Security.XmlSecResource",GETTEXT_PACKAGE);
XmlSecResource * XmlSecResource::instance = NULL;

XmlSecResource::XmlSecResource()
{		

}

XmlSecResource::~XmlSecResource()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

bool XmlSecResource::validate(SaesDirectories * directories,
		Smartmatic::SAES::Common::Configuration::BasePathType type)
    throw (CryptoException,
            XmlException,
            FileSystemException)
{
    bool validate = false;

    if (SAESCommonConfigurationManager::Current()->isVerifyExternElements())
    {
        std::string file = directories->getSignatureResourceFileFullPath(type);

        if (File::canOpenFile(file))
        {
            std::string file = directories->getSignatureResourceFileFullPath(type);
            std::list <std::string> pathList;
            std::list <std::string>::iterator it;

            pathList.push_back(directories->getLocalSaesDataFolderFullPath(type));
            pathList.push_back(directories->getLocalElectoralImagesFullFolderPath(type));
            pathList.push_back(directories->getSaesDataFolderFullPath(type));
            pathList.push_back(directories->getElectoralImagesFullFolderPath(type));

            for (it = pathList.begin();
                 it != pathList.end();
                 it++)
            {
            	logger->Debug("Validate resources in path : " + *it);
                validate = validateResourceList((*it), file);
                if (validate) break;
            }

            logger->Debug("Validate electoral resources " + std::string(validate ? "success":"fail"));
        }
        else
        {
            logger->Debug("File " + file + " not found.");
        }
    }
    else
    {
        validate = true;
    }

    if(!validate)
    {
        logger->Debug("FATAL - Error validate electoral resources.");
    }

    return validate;
}

bool XmlSecResource::validateResourceList(std::string path, std::string signature)
    throw (CryptoException,
            XmlException,
            FileSystemException)
{
    bool validate = false;

    std::string basePath = "file:///";
    basePath += path;
    basePath += "/";

    std::string data;

    Smartmatic::SAES::Security::Encryption::getInstance()->decryptoFileToString(
            signature,
            data,
            Smartmatic::SAES::Security::Encryption::EXTERNAL_FILE);

    DomXml domXml;
    xercesc::DOMDocument * dom = domXml.stringToDom(data);

    XSECURIResolverGenericUnix theResolver;
    XSECProvider prov;
    DSIGSignature * sig = NULL;

    try
    {
        sig = prov.newSignatureFromDOM(dom);

        xercesc::DOMNode * resourceEmpty = dom->getDocumentElement();
        resourceEmpty = domXml.getNode(resourceEmpty, "Signature");
        resourceEmpty = domXml.getNode(resourceEmpty, "SignedInfo");
        resourceEmpty = domXml.getNode(resourceEmpty, "Reference");

        if (resourceEmpty != NULL)
        {
            XMLCh * param = XMLString::transcode("URI");
            xercesc::DOMElement * element = (xercesc::DOMElement *)resourceEmpty;
            std::string path = XMLString::transcode(element->getAttribute(param));
            XSEC_RELEASE_XMLCH(param);

            if (path.empty())
            {
                logger->Debug("Resources empty");
                validate = true;
            }
        }

        if (!validate)
        {
            XMLCh * baseURIXMLCh = XMLString::transcode(basePath.c_str());
            theResolver.setBaseURI(baseURIXMLCh);

            OpenSSLCryptoX509 * key = NULL;
            std::string cert;

            xercesc::DOMNode * elementX509Certificate = dom->getDocumentElement();

            elementX509Certificate = domXml.getNode(elementX509Certificate, "Signature");
            elementX509Certificate = domXml.getNode(elementX509Certificate, "KeyInfo");
            elementX509Certificate = domXml.getNode(elementX509Certificate, "X509Data");
            elementX509Certificate = domXml.getNode(elementX509Certificate, "X509Certificate");

            if (elementX509Certificate != NULL)
            {
                elementX509Certificate = elementX509Certificate->getFirstChild();
            }

            if (elementX509Certificate != NULL && elementX509Certificate->getNodeType() == xercesc::DOMNode::TEXT_NODE)
            {
                char * msg = XMLString::transcode(elementX509Certificate->getTextContent());
                cert = msg;
                key = new OpenSSLCryptoX509();
                key->loadX509Base64Bin(cert.c_str(), cert.length());

                sig->setURIResolver(&theResolver);
                sig->load();
                sig->setSigningKey( key->clonePublicKey() );
                validate = sig->verify();
            }

            XSEC_RELEASE_XMLCH(baseURIXMLCh);
        }
    }
    catch (XSECException &ex)
    {
        char * msg = XMLString::transcode(ex.getMsg());
        logger->Debug("FATAL - " + std::string(msg));
        XMLString::release(&msg);
    }
    catch (XSECCryptoException &ex)
    {
        std::stringstream ss;
        ss << "FATAL - " << ex.getMsg();
        logger->Debug(ss.str());
    }
    catch(std::exception & ex)
    {
        std::stringstream ss;
        ss << "FATAL - " << ex.what();
        logger->Debug(ss.str());
    }
    catch(...)
    {
        logger->Debug("FATAL - error " + std::string(__func__));
    }

    return validate;
}

XmlSecResource * XmlSecResource::getInstance()
{
    if (instance == NULL)
    {
        instance = new XmlSecResource();
    }
    return instance;
}
