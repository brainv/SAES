/**
 * @file CMSSigner.hxx
 * @brief Header class CMSSigner
 * @date 05/03/2012
 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
 */

#ifndef CMSSIGNER_HXX_
#define CMSSIGNER_HXX_

#include <System/Exception/SignedException.hxx>
#include <System/SafeBuffer.h>

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
				 * @class CMSSigner
				 * @brief Class CMSSigner
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 05/03/2012
				 */
				class CMSSigner
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
						 CMS_PEM ///< signed CMS
						,CMS_SMIME ///< signed S/MIME
						,CMS_ASN1
					};
					/**
				     * @brief Class constructor
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 05/03/2012
				     */
            		CMSSigner();
					/**
				     * @brief Class destroy
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 05/03/2012
				     */
					virtual ~CMSSigner();
                    /**
                     * @brief method signed buffer
                     * @param bufferIn buffer in
                     * @param bufferOut buffer out result
                     * @param cryptoPKCS12 crypto PKCS12 certified
                     * @param type signed type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 05/03/2012
                     * @throw SignedException
                     */
                    void signedBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferOut,
                    		CryptoPKCS12 * cryptoPKCS12,
                    		SignedType type)
                    	throw (Smartmatic::System::Exception::SignedException);
                    /**
                     * @brief method validate signed buffer
                     * @param bufferIn buffer in
                     * @param bufferSigned buffer signed
                     * @param cryptoPKCS12 crypto PKCS12 certified
                     * @param type signed type
				     * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				     * @date 05/03/2012
                     * @throw SignedException
                     */
                    void validateBuffer(Smartmatic::System::SafeBuffer & bufferIn,
                    		Smartmatic::System::SafeBuffer & bufferSigned,
                    		CryptoPKCS12 * cryptoPKCS12,
                    		SignedType type)
                    	throw (Smartmatic::System::Exception::SignedException);

				private:

                    static Smartmatic::Log::ISMTTLog* logger;/**<logger*/
				};
            }
        }
    }
}

#endif /* CMSSIGNER_HXX_ */
