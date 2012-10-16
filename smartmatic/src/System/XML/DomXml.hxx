/**
 * @file DomXml.hxx
 * @brief Header class DomXml
 */

#ifndef __DOM__XML__H__
#define __DOM__XML__H__

#include <iostream>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <System/Exception/XmlException.hxx>
#include <System/SafeBuffer.h>
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
    namespace System
    {
        namespace XML
        {
            /**
             * @class DomXml
             * @brief class for parser dom to xml file 
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 03-04-2011
             */
            class DomXml
            {
            public:
                /**
                 * @brief class constructor
                 * @throw XmlException
                 */
                DomXml() throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class destroy
                 */
                ~DomXml();
                /**
                 * @brief class for parser xml file to dom
                 * @param file file xml
                 * @return dom document
                 * @throw XmlException
                 */
                xercesc::DOMDocument * fileToDom(std::string & file)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class for parser dom to xml file
                 * @param doc dom document
                 * @param file file xml
                 * @throw XmlException
                 */
                void domToFile(xercesc::DOMDocument * doc, std::string & file)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class for parser dom to string
                 * @param doc dom document
                 * @param str string
                 * @throw XmlException
                 */
                void domToString(xercesc::DOMDocument * doc, std::string & str)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class for parser string to dom
                 * @param str string
                 * @return dom document
                 * @throw XmlException
                 */
                xercesc::DOMDocument * stringToDom(std::string & str)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class for parser dom to SafeBuffer
                 * @param doc dom document
                 * @param buffer buffer
                 * @throw XmlException
                 */
                void domToBuffer(xercesc::DOMDocument * doc, Smartmatic::System::SafeBuffer & buffer)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief class for parser buffer to dom
                 * @param buffer buffer
                 * @return dom document
                 * @throw XmlException
                 */
                xercesc::DOMDocument * bufferToDom(Smartmatic::System::SafeBuffer & buffer)
                        throw (Smartmatic::System::Exception::XmlException);
                /**
                 * @brief method for get node
                 * @param node dom node root
                 * @param name node name
                 * @return dom node
                 */
                xercesc::DOMNode * getNode(xercesc::DOMNode * node, std::string name);

            private:
                xercesc::XercesDOMParser *fileParser; ///<file parser
				static Smartmatic::Log::ISMTTLog* logger; ///<logger
            };
        }
    }
}

#endif /*__DOM__XML__H__*/
