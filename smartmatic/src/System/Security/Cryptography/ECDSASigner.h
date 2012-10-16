/*
 * ECDSASigner.h
 *
 *  Created on: Nov 10, 2011
 *      Author: fgomez
 */

#ifndef ECDSASIGNER_H_
#define ECDSASIGNER_H_

#include "System/Security/Cryptography/SignatureAlgorithm.h"

namespace Smartmatic {
namespace System {
namespace Security {
namespace Cryptography {

class ECDSASigner : public SignatureAlgorithm {
public:
	ECDSASigner();
	virtual ~ECDSASigner();

	/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Nov 10, 2011
		 *
		 * @param plainData: pointer to data
		 * @param dataLen: data lenght
		 * @param outSafeBuffer: output buffer
		 * @param hash: hash algorithm to use.
		 *
		 *
		 */
		virtual void SignData (
				const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) ;


		/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Nov 10, 2011
		 *
		 * @param inSafeBuffer: reference to data
		 * @param outSafeBuffer: output buffer
		 * @param hash: hash algorithm to use.
		 *
		 *
		 */

		virtual void SignData ( Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& outSafeBuffer ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) ;

		/**
		 * @brief Signature calculation.
		 *
		 * @author fgomez
		 * @date   Nov 10, 2011
		 *
		 * @param plainData: pointer to data
		 * @param dataLen: data lenght
		 * @param signature: to verify
		 * @param hash: hash algorithm to use.
		 * @return: true if validation succeed. Otherwise, false.
		 *
		 */
		virtual bool VerifySignature (
				const unsigned char* plainData, int dataLen,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1) ;

		/**
		 * @brief Signature verification.
		 *
		 * @author fgomez
		 * @date   Nov 10, 2011
		 *
		 * @param inSafeBuffer: reference to data
		 * @param signature: to verify
		 * @param hash: hash algorithm to use.
		 * @return: true if validation succeed. Otherwise, false.
		 *
		 */
		virtual bool VerifySignature (
				Smartmatic::System::SafeBuffer& inSafeBuffer,Smartmatic::System::SafeBuffer& signature ,MsgDigestUtil::DigestAlgType hashKind= MsgDigestUtil::DGSTUTIL_SHA1);


		virtual bool IsValidPublicKey () const;

		/**
		 * @brief Checks this instance's key for integrity.
		 *
		 * @author fgomez
		 * @date   Nov 10, 2011
		 *
		 * @return false if the key pair or public key hold by this instance is
		 *         invalid or has not been set yet (has a NULL value).
		 *
		 */
		virtual bool IsValidPrivateKey () const;

		virtual SignatureAlgorithmType GetType() const;

private:
		static Smartmatic::Log::ISMTTLog* logger;/**logger*/
};

} /* namespace Cryptography */
} /* namespace Security */
} /* namespace System */
} /* namespace Smartmatic */
#endif /* ECDSASIGNER_H_ */
