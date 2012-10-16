/**
 * @file	XmlSecResource.hxx
 * @brief	xml security resources.
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#ifndef __XML_SEC_RESOURCE__H__
#define __XML_SEC_RESOURCE__H__

#include <Runtime/Environment/saes-directories.h>
#include <System/Exception/XmlException.hxx>
#include <System/Exception/SignedException.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/Exception/FileSystemException.hxx>

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }
}

namespace Smartmatic
{
    namespace SAES
    {
        namespace Security
        {
            /**
             * @class XmlSecResource
             * @brief Header class XmlSecResource
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 04-06-2011
             */
            class XmlSecResource
            {
            private:

                /**
                 * @brief	Class constructor.
                 *
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 04-06-2011
                 */

                XmlSecResource();

            public:

                /**
                 * @brief	Class destroy.
                 *
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 04-06-2011
                 */

                ~XmlSecResource();

                /**
                 * @brief	method to validate xml resources.
                 *
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 04-06-2011
                 *
                 * @param directories saesdirectories
                 * @return true is validate resources
                 */

                bool validate(Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories,
                		Smartmatic::SAES::Common::Configuration::BasePathType type)
                    throw (Smartmatic::System::Exception::CryptoException,
                            Smartmatic::System::Exception::XmlException,
                            Smartmatic::System::Exception::FileSystemException);

                /**
                 * @brief   Method getter instance class.
                 *
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 04-06-2011
                 *
                 * @return  instance class.
                 */

                static XmlSecResource * getInstance();

            private:

                /**
                 * @brief   method to open and validate resource list.
                 *
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 04-06-2011
                 *
                 * @param path path base resources
                 * @param signature signature file
                 * @return true is validate resources
                 */

                bool validateResourceList(std::string path, std::string signature)
                    throw (Smartmatic::System::Exception::CryptoException,
                            Smartmatic::System::Exception::XmlException,
                            Smartmatic::System::Exception::FileSystemException);

                static XmlSecResource * instance; ///< The instance
                static Smartmatic::Log::ISMTTLog* logger; ///< The logger
            };
        }
    }
}

#endif /*__XML_SEC_RESOURCE__H__*/
