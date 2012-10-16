/**
 * @file CryptoException.hxx
 * @brief Class custom for exceptions in crypto security
 */

#ifndef __CRYPTO_EXCEPTION_H__
#define __CRYPTO_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class CryptoException
          * @brief Header class CryptoException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 31-03-2011
          */
         class CryptoException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code, default empty
             * @param logger logger
             */
             CryptoException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /* __CRYPTO_EXCEPTION_H__ */
