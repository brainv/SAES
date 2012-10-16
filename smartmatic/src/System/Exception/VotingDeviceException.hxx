/**
 * @file VotingDeviceException.hxx
 * @brief Class custom for exceptions in voting devices
 */

#ifndef __VOTING_DEVICE_EXCEPTION_H__
#define __VOTING_DEVICE_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class VotingDeviceException
          * @brief Header class VotingDeviceException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 14-02-2011
          */
         class VotingDeviceException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
			 * @param logger logger
             */
            VotingDeviceException( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /*__VOTING_DEVICE_EXCEPTION_H__*/
