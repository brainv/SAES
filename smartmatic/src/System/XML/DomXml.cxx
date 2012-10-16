/**
 * @file DomXml.cxx
 * @brief Body class DomXml
 */

#include "DomXml.hxx"
#include "System/XML/Serialization/DomWriter.h"
#include <fstream>
#include <sstream>
#include <System/IO/File.h>
#include <Log/SMTTLogManager.h>
#include <xsec/framework/XSECProvider.hpp>

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

#define _ERROR_INITIALITATION_XML_ N_("Smartmatic.System.XML.DomXml.ErrorDuringInitialitationOfXmlPlatformUtils") ///< text for log
#define _ERROR_PARSER_FILE_TO_XML_ N_("Smartmatic.System.XML.DomXml.ErrorDuringParserFileToXml") ///< text for log
#define _ERROR_PARSER_XML_TO_FILE_ N_("Smartmatic.System.XML.DomXml.ErrorDuringParserXmlToFile") ///< text for log
#define _ERROR_PARSER_XML_TO_STRING_ N_("Smartmatic.System.XML.DomXml.ErrorDuringParserXmlToString") ///< text for log
#define _ERROR_PARSER_STRING_TO_DOM_ N_("Smartmatic.System.XML.DomXml.ErrorDuringParserStringToDom") ///< text for log

using namespace Smartmatic::System::XML;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::IO;

ISMTTLog* DomXml::logger = SMTTLogManager::GetLogger("Smartmatic.System.XML.DomXml",GETTEXT_PACKAGE);

DomXml::DomXml() throw (XmlException)
{
    this->fileParser = NULL;
    fileParser = new xercesc::XercesDOMParser;
}

DomXml::~DomXml()
{
    if (fileParser)
    {
        delete fileParser;
    }
}

xercesc::DOMDocument * DomXml::fileToDom(std::string & file)
        throw (XmlException)
{
	xercesc::DOMDocument * doc = NULL;

    if (!fileParser)
    {
        return doc;
    }

    fileParser->setValidationScheme(xercesc::XercesDOMParser::Val_Never);
    fileParser->setDoNamespaces(true);
    fileParser->setDoSchema(true);
    fileParser->setLoadExternalDTD(false);

    try
    {
        fileParser->parse(file.c_str());
        doc = fileParser->getDocument();
    }
    catch (xercesc::XMLException & ex)
    {
        throw XmlException(_(_ERROR_PARSER_FILE_TO_XML_),
                N_(_ERROR_PARSER_FILE_TO_XML_),logger);
    }

    return doc;
}

void DomXml::domToFile(xercesc::DOMDocument * doc, std::string & file)
        throw (XmlException)
{
    std::filebuf fb;
    fb.open(file.c_str(), std::ios::out);
    std::ostream os(&fb);

    try
    {
        Serialization::DomWriter domWriter(os);
        domWriter.Write(doc);
    }
    catch (std::exception & ex)
    {
        throw XmlException(_(_ERROR_PARSER_XML_TO_FILE_),
                N_(_ERROR_PARSER_XML_TO_FILE_), logger);
    }

    fb.close();
}

void DomXml::domToString(xercesc::DOMDocument * doc, std::string & str)
        throw (XmlException)
{
    try
    {
        std::ostringstream oss;
        Serialization::DomWriter domWriter(oss);
        domWriter.Write(doc);
        str = oss.str();
    }
    catch (std::exception & ex)
    {
        throw XmlException(_(_ERROR_PARSER_XML_TO_STRING_),
                N_(_ERROR_PARSER_XML_TO_STRING_), logger);
    }
}

xercesc::DOMDocument * DomXml::stringToDom(std::string & str)
        throw (XmlException)
{
    std::string fileName = "/tmp/f.xml";

    std::ofstream file (fileName.c_str(), std::ios::trunc);
    xercesc::DOMDocument * doc = NULL;

    if (file.is_open())
    {
        file << str;
        file.close();

        doc = fileToDom (fileName);
        File::DeleteFile(fileName);

        return doc;
    }

    throw XmlException(_(_ERROR_PARSER_STRING_TO_DOM_),
            N_(_ERROR_PARSER_STRING_TO_DOM_),logger);
}

void DomXml::domToBuffer(xercesc::DOMDocument * doc, Smartmatic::System::SafeBuffer & buffer)
	throw (XmlException)
{
	std::string str;
	domToString(doc, str);
	buffer.Clear();
	buffer.AddData((const unsigned char *) str.c_str(), str.length());
}

xercesc::DOMDocument * DomXml::bufferToDom(SafeBuffer & buffer)
	throw (Smartmatic::System::Exception::XmlException)
{
	std::string str;
	str.assign((const char *)buffer.GetData(), buffer.GetSize());
	str.resize(buffer.GetSize());
	return stringToDom(str);
}

xercesc::DOMNode * DomXml::getNode(xercesc::DOMNode * node, std::string name)
{
    xercesc::DOMNode * temp = node;

    if (temp != NULL && temp->getNodeType() == xercesc::DOMNode::ELEMENT_NODE &&
                strEquals (temp->getNodeName(), name.c_str()))
    {
        return temp;
    }

    if (temp != NULL)
    {
        temp = temp->getFirstChild();
    }

    while (temp != NULL &&
         !(temp->getNodeType() == xercesc::DOMNode::ELEMENT_NODE &&
           strEquals (temp->getNodeName(), name.c_str())))
    {
        temp = temp->getNextSibling();
    }

    return temp;
}
