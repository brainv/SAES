/**
 * @file Signed.hxx
 * @brief Header class for Signed file
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

#ifndef __SIGNED__H__
#define __SIGNED__H__

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include "System/Exception/CryptoException.hxx"
#include "System/Exception/SignedException.hxx"
#include "System/Security/Cryptography/DigestAlgorithmLookup.h"
#include "System/Security/Cryptography/CertificateValidator.h"
#include <System/SafeBuffer.h>
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
            /**
             * @class Signed
             * @brief Class for signed manager
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             * @date 31-03-2011
             */
            class Signed : public SecurityBase
            {
            public:

                /**
                 * @enum SignedType
                 * @brief Enum signed type config
                 */
                typedef enum
                {
                     SIMPLE_SIGNED /**<Use signed simple*/
                    ,FULL_SIGNED /**<Use signed full*/
                    ,DONT_SIGNED /**<not used signed*/
                }SignedType;

                /**
                 * @enum ValidateType
                 * @brief Enum validate type config
                 */
                typedef enum
                {
                     VALIDATE_PKCS12 /**<validate pkcs12*/
                    ,VALIDATE_X509 /**<validate x509*/
                    ,VALIDATE_INTERNAL /**<validate internal*/
                }ValidateType;

                /**
                 * @brief Class constructor
                 */
                Signed();
                /**
                 * @brief Class destroy
                 */
                ~Signed();

                /**
                 * @brief method setter hash algorithm
                 * @param hashType hash type
                 */
                void SetHashAlgorithm(Smartmatic::System::Security::Cryptography::DigestAlgType hashType);
                /**
                 * @brief method setter private key
                 * @param seckey private key
                 * @param keyLen key length
                 */
                void SetPrivateKey(const unsigned char* seckey, int keyLen);
                /**
                 * @brief method to certificate validator
                 * @param validator cert validator
                 * @throw SignedException
                 */
                void LoadCertificateValidator(Smartmatic::System::Security::Cryptography::CertificateValidator * validator)
                    throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to signed DOMElement HMAC
                 * @param doc DOM document signed
                 * @param signedType signed type
                 * @throw SignedException
                 */
                void signedHMACDOM(xercesc::DOMDocument * doc, SignedType signedType)
                        throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to signed DOMElement RSA
                 * @param doc DOM document signed
                 * @param signedType signed type
                 * @throw SignedException
                 */
                void signedRSADOM(xercesc::DOMDocument * doc, SignedType signedType)
                        throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to Sign a xml dom with a certificate
                 * @param doc DOM document to sign
                 * @param signedType signature mode
                 * @throw SignedException
                 */
                void signDOMWithCertificate(xercesc::DOMDocument * doc, SignedType signedType)
						throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to Sign a xml dom with a certificate
                 * @param doc DOM document to sign
                 * @param signedType signature mode
                 * @throw SignedException
                 */
                void signDOMWithDSA(xercesc::DOMDocument * doc, SignedType signedType)
                                        throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to validate signed file HMAC
                 * @param doc DOM document
                 * @return true if valid dom
                 * @throw SignedException
                 */
                bool validateSignedHMACDOM(xercesc::DOMDocument *doc)
                        throw (Smartmatic::System::Exception::SignedException);
                /**
                 * @brief method to validate signed file RSA
                 * @param doc DOM document
                 * @param validateType validate type, (dafault pkcs12)
                 * @return true if valid dom
                 * @throw SignedException
                 */
                bool validateXmlDigitalSignature(xercesc::DOMDocument *doc,
                        ValidateType validateType = VALIDATE_PKCS12)
                        throw (Smartmatic::System::Exception::SignedException);

                /**
                 * @brief method pkcs7 signer buffer
                 * @param bufferIn buffer in
                 * @param bufferOut buffer out result
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03/03/2012
                 * @throw SignedException
                 */
                void pkcs7SignerBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                		Smartmatic::System::SafeBuffer & bufferOut)
                		throw (Smartmatic::System::Exception::SignedException,
                				Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method pkcs7 signer buffer
                 * @param bufferIn buffer in
                 * @param bufferSigned buffer signed
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 03/03/2012
                 * @throw SignedException
                 */
                void pkcs7ValidateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                		Smartmatic::System::SafeBuffer & bufferSigned)
                		throw (Smartmatic::System::Exception::SignedException,
                				Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method cms signer buffer
                 * @param bufferIn buffer in
                 * @param bufferOut buffer out result
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05/03/2012
                 * @throw SignedException
                 */
                void cmsSignerBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                		Smartmatic::System::SafeBuffer & bufferOut)
                		throw (Smartmatic::System::Exception::SignedException,
                				Smartmatic::System::Exception::CryptoException);

                /**
                 * @brief method cms signer buffer
                 * @param bufferIn buffer in
                 * @param bufferSigned buffer signed
                 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
                 * @date 05/03/2012
                 * @throw SignedException
                 */
                void cmsValidateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                		Smartmatic::System::SafeBuffer & bufferSigned)
                		throw (Smartmatic::System::Exception::SignedException,
                				Smartmatic::System::Exception::CryptoException);

            private:

                /**
                 * @brief method for translate DigestAlgType to HashMethod
                 * @param digestype digest type
                 * @return hash method
                 */
                hashMethod Traslate(Smartmatic::System::Security::Cryptography::DigestAlgType digestype );
                /**
                 * @brief method for getter signature method from p12
                 * @param p12Container object p12
                 * @return signature method
                 */
				signatureMethod getSignatureMethodFromPrimaryKey(Smartmatic::System::Security::Cryptography::CryptoPKCS12* p12Container);
                /**
                 * @brief method setter key info
                 * @param sig object digital signature
                 * @param x509 object open ssl crypto x509
                 */
                void setKeyInfo(DSIGSignature * sig, OpenSSLCryptoX509 * x509);
                /**
                 * @brief method getter x509
                 * @param doc object digital signature
                 * @param validateType validate type, (default pkcs12)
                 * @return open ssl crypto x509
                 * @see SignedException
                 */
                OpenSSLCryptoX509 * getX509(xercesc::DOMDocument * doc,
                        ValidateType validateType = VALIDATE_PKCS12)
                        throw (Smartmatic::System::Exception::SignedException);

                unsigned char* privateKey; ///< private key
                unsigned int keySize; ///< key size
                Smartmatic::System::Security::Cryptography::CertificateValidator * validator; ///<validator
                hashMethod hashAlgorithm; ///< hash method
				static Smartmatic::Log::ISMTTLog* logger;///<logger
            };
        }
    }
}

#endif /*__SIGNED__H__*/
