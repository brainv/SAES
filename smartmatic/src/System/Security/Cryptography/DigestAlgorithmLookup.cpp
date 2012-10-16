/*
 * DigestAlgorithmLookup.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#include "System/Security/Cryptography/DigestAlgorithmLookup.h"

using namespace Smartmatic ::System::Security::Cryptography;

const EVP_MD * DigestAlgorithmLookup::LookupDigest(DigestAlgType alg)
{
  const EVP_MD * retVal =NULL;
  switch (alg)
          {
          case DGSTUTIL_MD5:
            retVal = EVP_md5();
            break;
          case DGSTUTIL_SHA1:
            retVal = EVP_sha1();
            break;
          case DGSTUTIL_SHA224:
            retVal = EVP_sha224();
            break;
          case DGSTUTIL_SHA256:
            retVal = EVP_sha256();
            break;
          case DGSTUTIL_SHA384:
            retVal = EVP_sha384();
            break;
          case DGSTUTIL_SHA512:
            retVal = EVP_sha512();
            break;
          default:
            retVal = EVP_sha1();
            break;
          }
  return retVal;
}
