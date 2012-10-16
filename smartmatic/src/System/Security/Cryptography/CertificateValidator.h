/**
 * @file CertificateValidator.h
 * @brief Header class certificate validator
 * @date 07/04/2011
 * @author Freddy Gomez
 */

#ifndef CERTIFICATEVALIDATOR_H_
#define CERTIFICATEVALIDATOR_H_

#include <glibmm.h>
#include <openssl/x509.h>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include <Log/ISMTTLog.h>
#include "System/Security/Cryptography/CertUtil.h"

namespace Smartmatic
{
  namespace System

  {
    namespace Security
    {
      namespace Cryptography
      {
        /**
         * @enum	CertificatePurpose
         *
         * @brief	Values that represent CertificatePurpose. 
         */

        enum CertificatePurpose
        {
          DefaultPurpose = 0,
          SSLClientCertificate =1,
          SSLServerCertificate =2,
          NSSSLServerCertificate = 3,
          SMIMESignCertificate = 4,
          SMIMEEncryptCertificate = 5,
          CRLSIGNCertificate = 6,
          AnyPurposeCertificate = 7
        };

        /**
         * @enum	CertificateValidationFlags
         *
         * @brief	Values that represent CertificateValidationFlags. 
         */

        enum CertificateValidationFlags
        {
          VERIFY_NO_FLAGS = 0,
          VERIFY_DO_NOT_VALIDATE = 1, //this does nothing
          VERIFY_IGNORE_CRITICAL = 2,
          VERIFY_CB_ISSUER_CHECK = 4,
          VERIFY_CRL_CHECK = 8,
          VERIFY_CRL_CHECK_ALL = 16,
          VERIFY_POLICY_CHECK = 32,
          VERIFY_EXPLICIT_POLICY = 64,
          VERIFY_INHIBIT_ANY = 128,
          VERIFY_INHIBIT_MAP = 256,
          VERIFY_X509_STRICT = 512,
          VERIFY_EXTENDED_CRL_SUPPORT = 1024,
          VERIFY_USE_DELTAS = 2048,
          VERIFY_NOTIFY_POLICY = 4096,
          VERIFY_CHECK_SS_SIGNATURE = 8192,
          VERIFY_SET_CHECK_TIME = 16384,
          VERIFY_ALLOW_PROXY_CERTS = 32768
        };

        /**
         * @enum	TrustResultEnum
         *
         * @brief	Values that represent TrustResultEnum. 
         */

        enum TrustResultEnum
        {
            TRUST_OK = 0,
            TRUST_CANNOT_READ_TARGET = 1,
            TRUST_INVALID_DATE = 2,
            TRUST_CANNOT_CREATE_STORE = 3,
            TRUST_CANNOT_READ_INTERMEDIATE_CA_CERTS = 4,
            TRUST_CANNOT_READ_TRUSTED_CERTS = 5,
            TRUST_ERR_UNABLE_TO_GET_CRL = 6,
            TRUST_UNABLE_TO_GET_ISSUER_CERT = 7,
            TRUST_UNABLE_TO_DECRYPT_CERT_SIGNATURE,
            TRUST_UNABLE_TO_DECRYPT_CRL_SIGNATURE,
            TRUST_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY,
            TRUST_CERT_SIGNATURE_FAILURE,
            TRUST_CRL_SIGNATURE_FAILURE,
            TRUST_CERT_NOT_YET_VALID,
            TRUST_CRL_NOT_YET_VALID,
            TRUST_CERT_HAS_EXPIRED,
            TRUST_ERR_CRL_HAS_EXPIRED,
            TRUST_ERROR_IN_CERT_NOT_BEFORE_FIELD,
            TRUST_ERROR_IN_CERT_NOT_AFTER_FIELD,
            TRUST_ERROR_IN_CRL_LAST_UPDATE_FIELD,
            TRUST_ERROR_IN_CRL_NEXT_UPDATE_FIELD,
            TRUST_OUT_OF_MEM,
            TRUST_DEPTH_ZERO_SELF_SIGNED_CERT,
            TRUST_SELF_SIGNED_CERT_IN_CHAIN,
            TRUST_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,
            TRUST_UNABLE_TO_VERIFY_LEAF_SIGNATURE,
            TRUST_CERT_CHAIN_TOO_LONG,
            TRUST_ERR_CERT_REVOKED,
            TRUST_ERR_INVALID_CA,
            TRUST_INVALID_NON_CA,
            TRUST_ERR_PATH_LENGTH_EXCEEDED,
            TRUST_ERR_PROXY_PATH_LENGTH_EXCEEDED,
            TRUST_ERR_PROXY_CERTIFICATES_NOT_ALLOWED,
            TRUST_ERR_INVALID_PURPOSE,
            TRUST_ERR_CERT_UNTRUSTED,
            TRUST_ERR_CERT_REJECTED,
            TRUST_ERR_APPLICATION_VERIFICATION,
            TRUST_ERR_SUBJECT_ISSUER_MISMATCH,
            TRUST_ERR_AKID_SKID_MISMATCH,
            TRUST_ERR_AKID_ISSUER_SERIAL_MISMATCH,
            TRUST_ERR_KEYUSAGE_NO_CERTSIGN,
            TRUST_ERR_UNABLE_TO_GET_CRL_ISSUER,
            TRUST_ERR_UNHANDLED_CRITICAL_EXTENSION,
            TRUST_ERR_KEYUSAGE_NO_CRL_SIGN,
            TRUST_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE,
            TRUST_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION,
            TRUST_ERR_INVALID_EXTENSION,
            TRUST_ERR_INVALID_POLICY_EXTENSION,
            TRUST_ERR_NO_EXPLICIT_POLICY,
            TRUST_ERR_DIFFERENT_CRL_SCOPE,
            TRUST_ERR_UNSUPPORTED_EXTENSION_FEATURE,
            TRUST_ERR_UNNESTED_RESOURCE,
            TRUST_ERR_PERMITTED_VIOLATION,
            TRUST_ERR_EXCLUDED_VIOLATION,
            TRUST_ERR_SUBTREE_MINMAX,
            TRUST_ERR_UNSUPPORTED_CONSTRAINT_TYPE,
            TRUST_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX,
            TRUST_ERR_UNSUPPORTED_NAME_SYNTAX,
            TRUST_ERR_CRL_PATH_VALIDATION_ERROR

        };

        /**
         * @brief	Cert validation result class. 
         *
         * @author	freddyg
         * @date	28/04/2011
         */

        class CertValidationResult
        {
        public:

          /**
           * @brief	Default constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          CertValidationResult();

          /**
           * @brief	Copy constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param [in,out]	x	The x coordinate.
           */

          CertValidationResult(CertValidationResult& x);

          /**
           * @brief	Constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	depthA 	The depth .
           * @param	detailA	The detail.
           */

          CertValidationResult(int depthA, TrustResultEnum detailA);

          /**
           * @brief	Finaliser.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          virtual ~CertValidationResult();

          /**
           * @brief	Gets the succes.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @return	true if it succeeds, false if it fails.
           */

          bool GetSucces();

          /**
           * @brief	Gets the detail.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @return	The detail.
           */

          TrustResultEnum GetDetail();

          /**
           * @brief	Sets a detail.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	val	The value.
           */

          void SetDetail(TrustResultEnum val);

          /**
           * @brief	Gets the depth.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @return	The depth.
           */

          int GetDepth();

          /**
           * @brief	Sets a depth.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	newDepth	new Depth.
           */

          void SetDepth(int newDepth);

        private:
         
          int depth;  ///< The depth
          TrustResultEnum detail;  ///< The detail
        };

        /**
         * @class CertificateValidator
         * @brief	Certificate validator. 
         *
         * @author	freddyg
         * @date	28/04/2011
         */

        class CertificateValidator
        {
        public:

          /**
           * @brief	Default constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          CertificateValidator();

          /**
           * @brief	Class destroy.
           *
           * @author	freddyg
           * @date	28/04/2011
           */
          virtual ~CertificateValidator();

          //Policy: indica cual poliza del archivo de configuracion usar. no parecen inyectarse al momento de hacer la validacion

          /**
           * @brief	Sets the options.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	flags	The flags.
           */

          void SetOptions(CertificateValidationFlags flags);

          /**
           * @brief	Clears the options described by flags.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	flags	The flags.
           */

          void ClearOptions(CertificateValidationFlags flags);

          /**
           * @brief	Sets a verification time.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	time	The time.
           */

          void SetVerificationTime(time_t time);

          /**
           * @brief	Clears the verification time.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          void ClearVerificationTime();

          //This would be the Root CA

          /**
           * @brief	Sets a ca certificate.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	format  	Describes the format to use.
           */

          void SetCACertificate(Glib::ustring certPath, CertUtil::CertFileFormat format);

          //These would be the certs in the chain, untrusted cert for openssl

          /**
           * @brief	Sets an itermediate ca certificates.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	format  	Describes the format to use.
           */

          void SetItermediateCACertificates(Glib::ustring certPath, CertUtil::CertFileFormat format);

          /**
           * @brief	Sets an itermediate ca certificates from pkcs 12.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	password	The password.
           */

          void SetItermediateCACertificatesFromPKCS12(Glib::ustring certPath, Glib::ustring password);


          //These would be the others trusted cert

          /**
           * @brief	Sets a trusted certificates.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	format  	Describes the format to use.
           */

          void SetTrustedCertificates(Glib::ustring certPath, CertUtil::CertFileFormat format);

          /**
           * @brief	Sets a trusted certificates from pkcs 12.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	password	The password.
           */

          void SetTrustedCertificatesFromPKCS12(Glib::ustring certPath, Glib::ustring password);

          /**
           * @brief	Verify x coordinate 509 certificate.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	format  	Describes the format to use.
           * @param	purpose 	The purpose.
           *
           * @return	.
           */

          CertValidationResult VerifyX509Certificate(Glib::ustring certPath, CertUtil::CertFileFormat format, CertificatePurpose purpose );

          /**
           * @brief	Verify pkcs 12 certificate.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	certPath	Full pathname of the cert file.
           * @param	password	The password.
           * @param	purpose 	The purpose.
           *
           * @return	.
           */

          CertValidationResult VerifyPKCS12Certificate(Glib::ustring certPath,Glib::ustring password,  CertificatePurpose purpose );

          /**
           * @brief	Verify x coordinate 509 certificate.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param [in,out]	cert	If non-null, the cert.
           * @param	purpose				The purpose.
           *
           * @return	.
           */

          CertValidationResult VerifyX509Certificate(OpenSSLCryptoX509 * cert, CertificatePurpose purpose );

          static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

        private:

          /**
           * @brief	Verify x coordinate 509 certificate.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param [in,out]	cert	If non-null, the cert.
           * @param	purpose				The purpose.
           *
           * @return	.
           */

          CertValidationResult VerifyX509Certificate(X509 * cert, CertificatePurpose purpose );

         
          Glib::ustring certAuthorityPath;  ///< Full pathname of the cert authority file

          CertUtil::CertFileFormat certAuthorityFormat;  ///< The cert authority format
          
          bool usingIntermediateCA; ///< true to using intermediate ca
		            
          CertUtil::CertFileFormat intermediateCAFormat; ///< The intermediate ca format
          
          Glib::ustring intermediateCAPath; ///< Full pathname of the intermediate ca file
          
          Glib::ustring intermediateCAFilePassword; ///< The intermediate ca file password         
          
          bool usingTrustedCert; ///< true to using trusted cert
         
          CertUtil::CertFileFormat trustedCertFormat; ///< The trusted cert format
         
          Glib::ustring trustedCertPath;  ///< Full pathname of the trusted cert file
         
          Glib::ustring trustedCertFilePassword;  ///< The trusted cert file password		  
         
          CertificateValidationFlags validationFlags;  ///< The validation flags
         
          time_t checkTime;  ///< Time of the check

        };

      }
    }
  }
}
#endif /* CERTIFICATEVALIDATOR_H_ */
