/**
 * @file SecurityBase.hxx
 * @brief Header class security base
 * @date 21/03/2012
 * @author Yadickson Soto
 */

#ifndef SECURITYBASE_HXX_
#define SECURITYBASE_HXX_

#include "System/Security/Cryptography/CertUtil.h"
#include "System/Security/Cryptography/CryptoPKCS12.hxx"
#include "System/Exception/CryptoException.hxx"
#include <openssl/evp.h>
#include <openssl/x509.h>

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
			 * @class SecurityBase
			 * @brief Class utils for crypto and signed
			 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
			 * @date 21/03/2012
			 */
			class SecurityBase
			{
			public:
				/**
				 * @brief Class constructor
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 21/03/2012
				 */
				SecurityBase();
				/**
				 * @brief Class destroy
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 21/03/2012
				 */
				virtual ~SecurityBase();
				/**
				 * @brief method load pkcs12 file
				 * @param secretKey secret key
				 * @param file file optinal, only for RSA
				 * @throw CryptoException
				 */
				void loadPKCS12(std::string & secretKey, std::string file = "")
						throw (Smartmatic::System::Exception::CryptoException);
				/**
				 * @brief method load file crt
				 * @param file file crt
				 * @param pass pass file
				 * @param format cert file format
				 * @date 21/03/2012
				 * @author Yadickson Soto
				 * @throw CryptoException
				 */
				void loadCertifiedPKey(std::string file, std::string pass,
						Smartmatic::System::Security::Cryptography::CertUtil::CertFileFormat format)
						throw (Smartmatic::System::Exception::CryptoException);
				/**
				 * @brief method load file crt
				 * @param file file crt
				 * @param format cert file format
				 * @throw CryptoException
				 */
				void loadCertifiedX509(std::string file,
						Smartmatic::System::Security::Cryptography::CertUtil::CertFileFormat format)
						throw (Smartmatic::System::Exception::CryptoException);

			protected:

				Smartmatic::System::Security::Cryptography::CryptoPKCS12 * cryptoP12; ///<object read crypto
				X509 * certifiedX509; ///<object certified x509
				EVP_PKEY * certPrivateKey; ///< cert private key

			private:

				static Smartmatic::Log::ISMTTLog* logger;///<logger
			};
        }
    }
}

#endif /* SECURITYBASE_HXX_ */
