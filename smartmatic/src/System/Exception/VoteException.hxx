/**
 * @file VoteException.hxx
 * @brief Class custom for exceptions in crypto security
 */

#ifndef __VOTE_EXCEPTION_H__
#define __VOTE_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class VoteException
          * @brief Header class VoteException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 08-05-2011
          */
         class VoteException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
             * @param logger logger
             */
             VoteException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /* __VOTE_EXCEPTION_H__ */
