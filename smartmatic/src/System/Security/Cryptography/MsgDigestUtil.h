/*
 * MsgDigestUtil.h
 *
 *  Created on: Apr 1, 2011
 *      Author: marcel
 */

#ifndef MSGDIGESTUTIL_H_
#define MSGDIGESTUTIL_H_


#include <iostream>
#include <glibmm.h>

#include "System/Security/Cryptography/DigestAlgorithmLookup.h"
#include "System/Exception/MessageDigestException.h"
#include "System/SafeBuffer.h"




namespace Smartmatic
{
namespace System
{
namespace Security
{
namespace Cryptography
{
/**
 * @brief	Message digest utility class. 
 *
 * @author	marcel
 * @date	29/04/2011
 */

class MsgDigestUtil
{
public:

	/**
	 * @enum	DigestAlgType
	 *
	 * @brief	Values that represent DigestAlgType. 
	 */

	enum DigestAlgType
	{
		DGSTUTIL_MD5,
		DGSTUTIL_SHA1,
		DGSTUTIL_SHA224,
		DGSTUTIL_SHA256,
		DGSTUTIL_SHA384,
		DGSTUTIL_SHA512,
	};



	/** Destructor
	 */
	virtual ~MsgDigestUtil();


	// Public interface


	/**
	 * @brief   Claculates hash value over the content of the given file with
	 *          the specified algorithm.
	 * @param   The message to digest in binary format
	 * @returns Wraper of the buffer containing the hash value calculated over
	 *          the value of the content of the file specified.
	 */
	static SafeBuffer FileDigest(const Glib::ustring& file, DigestAlgType alg)
	    throw (Smartmatic::System::Exception::MessageDigestException);

	/**
	 * @brief   Claculates hash value of a given message with the specified
	 *          algorithm
	 * @param   the message to digest
	 * @returns wraper of the buffer containing the hash value calculated over
	 *          the value of the 'message' parameter.
	 */
	static SafeBuffer Digest(const Glib::ustring& message, DigestAlgType alg);

	/**
	 * @brief   Claculates hash value of a given binary message with the specified
	 *          algorithm
	 * @param   The message to digest in binary format
	 * @returns Wraper of the buffer containing the hash value calculated over
	 *          the value of the 'data' parameter.
	 */
	static SafeBuffer Digest(const unsigned char* data, int dataLen, DigestAlgType alg);

protected:


	/** Default Constructor
	 */
	MsgDigestUtil();


private:

	/**
	 * @brief	Map algorithm name.
	 *
	 * @author	marcel
	 * @date	28/04/2011
	 *
	 * @param	alg	The algorithm.
	 *
	 * @return	null if it fails, else.
	 */

	static const char* mMapAlgName (DigestAlgType alg);

	/**	
	 * @brief	Perform hashing.
	 *
	 * @author	marcel
	 * @date	28/04/2011
	 *
	 * @param	algName			  	Name of the algorithm.
	 * @param	data			  	The data.
	 * @param	dataLen			  	Length of the data.
	 * @param [in,out]	outBuffer 	If non-null, buffer for out data.
	 * @param [in,out]	outBufSize	Size of the out buffer.
	 *
	 * @return	null if it fails, else.
	 */

	static unsigned char* mPerformHashing (
			  const char* algName
			, const unsigned char* data, int dataLen
			, unsigned char* outBuffer, int& outBufSize);

	static Smartmatic::Log::ISMTTLog* logger;/**logger*/

};


}
}
}
}


#endif /* MSGDIGESTUTIL_H_ */
