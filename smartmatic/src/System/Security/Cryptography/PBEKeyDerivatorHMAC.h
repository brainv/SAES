/*
 * PBEKeyDerivatorHMAC.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef PBEKEYDERIVATORHMAC_H_
#define PBEKEYDERIVATORHMAC_H_

#include <glibmm.h>
#include "System/Security/Cryptography/DigestAlgorithmLookup.h"


namespace Smartmatic {
  namespace System
  {
    namespace Security
    {
      namespace Cryptography
      {
        /**
         * @brief	Pbe key derivator hmac class. 
         *
         * @author	freddyg
         * @date	28/04/2011
         */

        class PBEKeyDerivatorHMAC
        {
        public:

          /**
           * @brief	Default constructor.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          PBEKeyDerivatorHMAC();
          virtual

          /**
           * @brief	Finaliser.
           *
           * @author	freddyg
           * @date	28/04/2011
           */

          ~PBEKeyDerivatorHMAC();

        /**
         * @brief	Generates a key.
         *
         * @author	freddyg
         * @date	28/04/2011
         *
         * @param	passPhrase	  	The pass phrase.
         * @param [in,out]	outkey	If non-null, the outkey.
         * @param	keyLen		  	Length of the key.
         * @param	iterations	  	The iterations.
         * @param	mdAlg		  	The md algorithm.
         */

        void GenerateKey(const Glib::ustring& passPhrase, unsigned char * outkey, int keyLen,int iterations, DigestAlgType mdAlg = DGSTUTIL_SHA1 );

        /**
         * @brief	Sets a salt.
         *
         * @author	freddyg
         * @date	28/04/2011
         *
         * @param	salt   	The salt.
         * @param	saltLen	Length of the salt.
         */

        void SetSalt(const unsigned char * salt, int saltLen);

        /**
         * @brief	Sets a salt.
         *
         * @author	freddyg
         * @date	28/04/2011
         *
         * @param	salt	The salt.
         */

        void SetSalt(const Glib::ustring& salt);

      private:

       
        unsigned char* mSaltValue;  ///< The salt value

       
        int mSaltSize;  ///< Size of the salt

        };
      }
    }
  }
}
#endif /* PBEKEYDERIVATORHMAC_H_ */
