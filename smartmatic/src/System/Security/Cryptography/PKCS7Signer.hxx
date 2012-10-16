/**
 * @file PKCS7Signer.hxx
 * @brief Header class PKCS7Signer
 * @date 02/03/2012
 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
 */

#ifndef PKCS7SIGNER_HXX_
#define PKCS7SIGNER_HXX_

#include <System/Exception/SignedException.hxx>
#include <System/Exception/CryptoException.hxx>
#include <System/SafeBuffer.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

namespace Smartmatic
{
	namespace
	{
		class ISMTTLog;
	}
    namespace System
    {
        namespace Security
        {
            namespace Cryptography
            {
            	class CryptoPKCS12;

				/**
				 * @class PKCS7Signer
				 * @brief Class PKCS7Signer
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 02/03/2012
				 */
				class PKCS7Signer
				{
				public:

					/**
					 * @enum SignedType
					 * @brief PKCS#7 signed type
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 03/03/2012
					 */
					enum SignedType
					{
						 PKCS7_PEM ///< signed CMS
						,PKCS7_SMIME ///< signed S/MIME
						,PKCS7_ASN1
					};

					/**
				     * @brief Class constructor
				     * @param cryptoPKCS12 crypto pkcs12
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 02/03/2012
				     */
					PKCS7Signer(CryptoPKCS12 * cryptoPKCS12);
					/**
				     * @brief Class constructor
				     * @param primaryKey primary key
				     * @param cert cert
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 02/03/2012
				     */
					PKCS7Signer(EVP_PKEY * primaryKey, X509 * cert);
					/**
				     * @brief Class destroy
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 02/03/2012
				     */
					virtual ~PKCS7Signer();

                    /**
                     * @brief method signed buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param type signed type
                     * @throw SignedException
                     * @throw CryptoException
                     */
                    void signedBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		SignedType type)
                    	throw (Smartmatic::System::Exception::SignedException,
                    			Smartmatic::System::Exception::CryptoException);

                    /**
                     * @brief method validate signed buffer
                     * @param bufferIn buffer in
                     * @param bufferSigned buffer signed
                     * @param type signed type
                     * @throw SignedException
                     * @throw CryptoException
                     */
                    void validateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferSigned,
                    		SignedType type)
                    	throw (Smartmatic::System::Exception::SignedException,
                    			Smartmatic::System::Exception::CryptoException);

				private:

                    CryptoPKCS12 * cryptoPKCS12; ///< cert pkcs12
                    EVP_PKEY * primaryKey; ///< primary key
                    X509 * cert; ///< cert
                    static Smartmatic::Log::ISMTTLog* logger;/**<logger*/
				};
            }
        }
    }
}

#endif /* PKCS7SIGNER_HXX_ */
