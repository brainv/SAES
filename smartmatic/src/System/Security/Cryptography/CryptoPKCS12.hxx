/**
 * @file CryptoPKCS12.hxx
 * @brief Header class for CryptoPKCS12 file
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

#ifndef __CRYPTOPKCS12__H__
#define __CRYPTOPKCS12__H__

#include <iostream>
#include <openssl/pem.h>
#include <openssl/pkcs12.h>
#include <openssl/safestack.h>
#include "System/Exception/CryptoException.hxx"
#include "Log/ISMTTLog.h"

namespace Smartmatic
{
    namespace System
    {
        namespace Security
        {
            namespace Cryptography
            {
        		/**
                 * @class CryptoPKCS12
                 * @brief Header class Crypto
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 31-03-2011
                 */
                class CryptoPKCS12
                {
                public:
                  /**
                   * @brief Class constructor
                   */
                  CryptoPKCS12();
                    /**
                     * @brief Class constructor
                     * @param file file
                     * @param secretKey secret key
                     * @throw CryptoException
                     */
                    CryptoPKCS12(std::string & file, std::string & secretKey)
                        throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief Class destroy
                     */
                    ~CryptoPKCS12();
                    /**
                     * @param file file
                     * @param secretKey secret key
                     * @throw CryptoException
                     *
                     * */
                    void Load(std::string & file, std::string & secretKey)
                    throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method getter primary key
                     * @return primary key
                     * @throw CryptoException
                     */
                    EVP_PKEY * getPrimaryKey()
                        throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method getter certified
                     * @return certified
                     * @throw CryptoException
                     */
                    X509 * getCertified()
                        throw (Smartmatic::System::Exception::CryptoException);

                    /**
                     * @brief method getter of certificate authorities inside this container
                     * @return certified
                     * @throw CryptoException
                     */
                    STACK_OF(X509) * getCertificatesAuthorities();


                private:
                    PKCS12 * p12; /**<object pkcs#12*/
                    EVP_PKEY * pkey; /**<primary key*/
                    X509 * cert; /**<certified*/
                    STACK_OF(X509) *ca;/**<certificate authorities*/
                    static Smartmatic::Log::ISMTTLog* logger;/**<logger*/
                };
            }
        }
    }
}

#endif /*__CRYPTOPKCS12__H__*/
