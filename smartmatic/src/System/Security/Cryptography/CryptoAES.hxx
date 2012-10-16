/**
 * @file CryptoAES.hxx
 * @brief Header class for CryptoAES file
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

#ifndef __CRYPTOAES__H__
#define __CRYPTOAES__H__

#include <iostream>
#include <openssl/evp.h>
#include "System/Exception/CryptoException.hxx"
#include "System/SafeBuffer.h"
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
                 * @class CryptoAES
                 * @brief Header class Symetric Crypto
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05-04-2011
                 */
                class CryptoAES
                {
                public:
                    /**
                     * @brief Class constructor
                     * @param cipherMode cipher mode crypto
                     * @throw CryptoException
                     */
                    CryptoAES(const EVP_CIPHER * cipherMode);
                    /**
                     * @brief Class destroy
                     */
                    ~CryptoAES();

                    /**
                     * @brief method crypto data
                     * @param dataIn data to crypto
                     * @param dataOut data out of crypto
                     * @param key key crypto
                     * @param iv iv crypto
                     * @param enc 0=decrypto, 1=crypto
                     * @param pad padding true=padding
                     * @throw CryptoException
                     */
                    void encryptoDecrypto(Smartmatic::System::SafeBuffer & dataIn,
                    	Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key,
                        const unsigned char * iv,
                        int enc, bool pad)
                        throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method encrypto data
                     * @param dataIn data to crypto
                     * @param dataOut data out of crypto
                     * @param key key crypto
                     * @param iv iv crypto
                     * @param pad padding true=padding
                     * @throw CryptoException
                     */
                    void encryptoData(Smartmatic::System::SafeBuffer & dataIn,
                    	Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key,
                        const unsigned char * iv,
                        bool pad)
                        throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method decrypto data
                     * @param dataIn data to crypto
                     * @param dataOut data out of crypto
                     * @param key key crypto
                     * @param iv iv crypto
                     * @param pad padding true=padding
                     * @throw CryptoException
                     */
                    void decryptoData(Smartmatic::System::SafeBuffer & dataIn,
                    	Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key,
                        const unsigned char * iv,
                        bool pad)
                        throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method getter cipher
                     * @return cipher
                     */
                    const EVP_CIPHER * getCipher();

                private:
                    const EVP_CIPHER * cipherMode; ///<cipher mode
					static Smartmatic::Log::ISMTTLog* logger;///<logger
                };
            }
        }
    }
}

#endif /*__CRYPTOAES__H__*/
