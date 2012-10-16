/**
 * @file CryptoBase.hxx
 * @brief Header class crypto base
 * @date 20/03/2012
 * @author Yadickson Soto
 */

#ifndef CRYPTOBASE_HXX_
#define CRYPTOBASE_HXX_

#include <System/Exception/CryptoException.hxx>
#include <System/SafeBuffer.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

namespace Smartmatic
{
    namespace System
    {
        namespace Security
        {
            namespace Cryptography
            {
            	class CryptoPKCS12;

				/**
				 * @class CryptoBase
				 * @brief Class crypto base
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 20/03/2012
				 */
				class CryptoBase
				{
				public:
					/**
					 * @enum CryptoBaseType
					 * @brief crypto type
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 20/03/2012
					 */
					enum CryptoBaseType
					{
						 CRYPTO_PEM ///< crypto PEM
						,CRYPTO_SMIME ///< crypto S/MIME
						,CRYPTO_DER ///< crypto DER
					};
					/**
					 * @brief Class constructor
                     * @param cryptoPKCS12 crypto PKCS12 certified
                     * @param cipherMode cipher mode crypto
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
					 */
					CryptoBase(CryptoPKCS12 * cryptoPKCS12, const EVP_CIPHER * cipherMode);
					/**
					 * @brief Class constructor
                     * @param cert certified
                     * @param cipherMode cipher mode crypto
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
					 */
					CryptoBase(const X509 * cert, const EVP_CIPHER * cipherMode);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 20/03/2012
					 */
					virtual ~CryptoBase();
                    /**
                     * @brief method crypto buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param type crypto type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 20/03/2012
                     * @throw CryptoException
                     */
                    virtual void cryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		CryptoBaseType type)
                    	throw (Smartmatic::System::Exception::CryptoException) = 0;
                    /**
                     * @brief method decrypto buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param type crypto type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 20/03/2012
                     * @throw CryptoException
                     */
                    virtual void decryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		CryptoBaseType type)
                    	throw (Smartmatic::System::Exception::CryptoException) = 0;

				protected:

                    CryptoPKCS12 * cryptoPKCS12; ///< crypto pkcs12
                    const X509 * cert; ///< cert
                    const EVP_CIPHER * cipherMode; ///< chipher mode
				};
            }
        }
    }
}

#endif /* CRYPTOBASE_HXX_ */
