/**
 * @file CryptoPKCS7.hxx
 * @brief HEader class crypto PKCS7
 * @date 19/03/2012
 * @author Yadickson Soto
 */

#ifndef CRYPTOPKCS7_HXX_
#define CRYPTOPKCS7_HXX_

#include "CryptoBase.hxx"

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
				 * @class CryptoPKCS7
				 * @brief Class crypto PKCS7
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 19/03/2012
				 * @see CryptoBase
				 */
				class CryptoPKCS7 : public CryptoBase
				{
				public:
					/**
					 * @brief Class constructor
                     * @param cryptoPKCS12 crypto PKCS12 certified
                     * @param cipherMode cipher mode crypto
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
					 */
					CryptoPKCS7(CryptoPKCS12 * cryptoPKCS12, const EVP_CIPHER * cipherMode);
					/**
					 * @brief Class constructor
                     * @param cert certified
                     * @param cipherMode cipher mode crypto
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
					 */
					CryptoPKCS7(const X509 * cert, const EVP_CIPHER * cipherMode);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
					 */
					virtual ~CryptoPKCS7();
                    /**
                     * @brief method crypto buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param type crypto type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
                     * @throw CryptoException
                     */
                    virtual void cryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		CryptoBase::CryptoBaseType type)
                    	throw (Smartmatic::System::Exception::CryptoException);
                    /**
                     * @brief method decrypto buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param type crypto type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 19/03/2012
                     * @throw CryptoException
                     */
                    virtual void decryptoBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		CryptoBase::CryptoBaseType type)
                    	throw (Smartmatic::System::Exception::CryptoException);

				private:

                    static Smartmatic::Log::ISMTTLog* logger;/**<logger*/
				};
            }
        }
    }
}

#endif /* CRYPTOPKCS7_HXX_ */
