/**
 * @file VoteRecoveryException.hxx
 * @brief Class custom for exceptions in vote recovery
 */

#ifndef __VOTE_RECOVERY_EXCEPTION_H__
#define __VOTE_RECOVERY_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class VoteRecoveryException
          * @brief Header class VoteRecoveryException
          * @author Marcel Mancini <marcel.mancini@smartmatic.com>
          * @date 14-02-2011
          */
         class VoteRecoveryException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
			 * @param logger logger
             */
            VoteRecoveryException( std::string message, std::string code, 
                            		Smartmatic::Log::ISMTTLog* logger) 
									: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /*__VOTE_RECOVERY_EXCEPTION_H__*/
