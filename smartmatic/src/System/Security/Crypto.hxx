/**
 * @file Crypto.hxx
 * @brief Header class for Crypto file
 */

#ifndef __CRYPTO__H__
#define __CRYPTO__H__

#include <iostream>
#include "System/Exception/CryptoException.hxx"
#include "System/SafeBuffer.h"
#include "SecurityBase.hxx"

namespace Smartmatic
{
    namespace Log
    {
		class ISMTTLog;
    }

    namespace System
    {
        namespace Security
        {
            namespace Cryptography
            {
                /**
                 * @brief forward declaration
                 */
                class CryptoAES;
                /**
                 * @brief forward declaration
                 */
                class CryptoPKCS7;
            }
            /**
             * @class Crypto
             * @brief Class utils for crypto data
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 31-03-2011
             */
            class Crypto : public SecurityBase
            {
            public:
                /**
                 * @brief enum KeySize
                 */
                typedef enum
                {
                     KEY_AES_128 ///<key aes 128
                    ,KEY_AES_192 ///<key aes 192
                    ,KEY_AES_256 ///<key aes 256
                }KeySize;

                /**
                 * @brief enum Mode
                 */
                typedef enum
                {
                     MODE_AES_CBC /**<Cipher Block Chaining*/
                    ,MODE_AES_CFB1 /**<Cipher FeedBack*/
                    ,MODE_AES_CFB8 /**<Cipher FeedBack*/
                    ,MODE_AES_CFB128 /**<Cipher FeedBack*/
                    ,MODE_AES_ECB /**<Electronic CodeBook*/
                    ,MODE_AES_OFB /**<Output FeedBack*/
                }Mode;

                /**
                 * @brief enum KeyMode
                 */
                typedef enum
                {
                     KEY_MODE_SHA1 /**<encrypt key mode sha1*/
                    ,KEY_MODE_MD5 /**<encrypt key mode md5*/
                }KeyMode;

                /**
                 * @brief Class constructor
                 */
                Crypto();
                /**
                 * @brief Class destroy
                 */
                ~Crypto();
                /**
                 * @brief method for init class
                 * @param keySize key size
                 * @param mode encrypt mode
                 * @param pad true padding
                 * @throw CryptoException
                 */
                void init(KeySize keySize, Mode mode, bool pad)
                        throw (Smartmatic::System::Exception::CryptoException);
				/**
				 * @brief method load pkcs7
				 * @throw CryptoException
				 */
				void loadPKCS7()
						throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method crypto buffer to file
                 * @param dataIn data to crypto
                 * @param file file out
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void cryptoBufferToFile(Smartmatic::System::SafeBuffer & dataIn,
                        std::string & file,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method crypto file to buffer
                 * @param fileIn file in
                 * @param dataOut data out crypto
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void cryptoFileToBuffer(std::string & fileIn, Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method crypto file to file
                 * @param fileIn file in
                 * @param fileOut file out
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void cryptoFileToFile(std::string & fileIn, std::string & fileOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method crypto buffer
                 * @param dataIn data to crypto
                 * @param dataOut data out crypto
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void cryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method decrypto file to buffer
                 * @param file file in
                 * @param dataOut data out decrypto
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void decryptoFileToBuffer(std::string & file,
                        Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method decrypto buffer to file
                 * @param dataIn data in to decrypto
                 * @param file file out
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void decryptoBufferToFile(Smartmatic::System::SafeBuffer &dataIn,
                        std::string & file,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method decrypto file to file
                 * @param fileIn file in
                 * @param fileOut file out
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void decryptoFileToFile(std::string & fileIn, std::string & fileOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);
                /**
                 * @brief method decrypto buffer to buffer
                 * @param dataIn data in to decrypto
                 * @param dataOut data out
                 * @param key private key
                 * @param iv initialization vector
                 * @throw CryptoException
                 */
                void decryptoBufferToBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut,
                        const unsigned char * key, const unsigned char * iv = NULL)
                        throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method crypto buffer with pkcs7
                 * @param dataIn data in to crypto
                 * @param dataOut data out
                 * @throw CryptoException
                 */
                void pkcs7CryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut)
                	throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method decrypto buffer with pkcs7
                 * @param dataIn data in to decrypto
                 * @param dataOut data out
                 * @throw CryptoException
                 */
                void pkcs7DecryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut)
                	throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method crypto buffer with cms
                 * @param dataIn data in to crypto
                 * @param dataOut data out
                 * @throw CryptoException
                 */
                void cmsCryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut)
                	throw (Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method decrypto buffer with cms
                 * @param dataIn data in to decrypto
                 * @param dataOut data out
                 * @throw CryptoException
                 */
                void cmsDecryptoBuffer(Smartmatic::System::SafeBuffer & dataIn,
                        Smartmatic::System::SafeBuffer & dataOut)
                	throw (Smartmatic::System::Exception::CryptoException);

            private:

                Smartmatic::System::Security::Cryptography::CryptoPKCS7 * cryptoP7; ///<object crypto with pkcs7
                Smartmatic::System::Security::Cryptography::CryptoAES * cryptoAES; ///<object crypto aes
                Mode mode; ///<encrypt mode
                bool pad; ///< flag enabled pad
                KeySize keySize; ///< key size
				static Smartmatic::Log::ISMTTLog* logger;///<logger

                /**
                 * @brief method setter config crypto aes key 128
                 */
                void configCryptoAESKey128();
                /**
                 * @brief method setter config crypto aes key 192
                 */
                void configCryptoAESKey192();
                /**
                 * @brief method setter config crypto aes key 256
                 */
                void configCryptoAESKey256();
            };
        }
    }
}

#endif /*__CRYPTO__H__*/
