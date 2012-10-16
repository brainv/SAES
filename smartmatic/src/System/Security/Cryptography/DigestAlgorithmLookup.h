/*
 * DigestAlgorithmDefinition.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef DIGESTALGORITHMDEFINITION_H_
#define DIGESTALGORITHMDEFINITION_H_

#include <openssl/evp.h>

namespace Smartmatic
{
namespace System
{
namespace Security
{
namespace Cryptography
{
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
                DGSTUTIL_SHA512
        };

        /**
         * @brief	Digest algorithm lookup class. 
         *
         * @author	freddyg
         * @date	28/04/2011
         */

        class DigestAlgorithmLookup
        {

        public:

          /**
           * @brief	Default constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          DigestAlgorithmLookup(){}

          /**
           * @brief	Looks up a given key to find its associated digest.
           *
           * @author	freddyg
           * @date	28/04/2011
           *
           * @param	alg	The algorithm.
           *
           * @return	null if it fails, else.
           */

          static const EVP_MD * LookupDigest(DigestAlgType alg);
        };
}
}
}
}
#endif /* DIGESTALGORITHMDEFINITION_H_ */
