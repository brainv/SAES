/**
 * @file CertUtil.h
 * @brief Header class utility certified manager
 * @date 10/11/2011
 * @author Freddy Gomez
 */

#ifndef CERTUTIL_H_
#define CERTUTIL_H_

#include <glibmm.h>
#include <Log/ISMTTLog.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

namespace Smartmatic {
namespace System {
namespace Security {
namespace Cryptography {

/**
 * @class CertUtil
 * @brief Class utility certified manager
 * @date 10/11/2011
 * @author Freddy Gomez
 */
class CertUtil
{
protected:
	/**
	 * @brief Class constructor
	 * @date 10/11/2011
	 * @author Freddy Gomez
	 */
	CertUtil();
public:

	/**
	 * @enum CertFileFormat
	 * @brief enum format certified
	 * @date 10/11/2011
	 * @author Freddy Gomez
	 */
	typedef enum
	{
		 CertFormat_DER		= 1		///< ANS1
		,CertFormat_TEXT	= 2		///< text
		,CertFormat_PEM 	= 3		///< pem
		,CertFormat_PKCS12 	= 5		///< pkcs12
		,CertFormat_PEMRSA 	= 9		///< PEM RSAPubicKey format
		,CertFormat_ASN1RSA	= 10	///< DER RSAPubicKey format
	}CertFileFormat;

	/**
	 * @brief Class destroy
	 * @date 10/11/2011
	 * @author Freddy Gomez
	 */
	virtual ~CertUtil();
	/**
	 * @brief Method load private key certified
	 * @param certPath path file
	 * @param certPass password
	 * @param format format certified
	 * @return private key
	 * @date 21/03/2012
	 * @author Yadickson Soto
	 */
	static EVP_PKEY * LoadCertificate(std::string certPath, std::string certPass, CertFileFormat format);
	/**
	 * @brief Method load certified
	 * @param certPath path file
	 * @param format format certified
	 * @return certified
	 * @date 10/11/2011
	 * @author Yadickson Soto
	 */
	static X509 * LoadCertificate(std::string certPath, CertFileFormat format);

private:
	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
};

} /* namespace Cryptography */
} /* namespace Security */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* CERTUTIL_H_ */
