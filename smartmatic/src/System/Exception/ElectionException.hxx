/**
 * @file ElectionException.hxx
 * @brief Class custom for exceptions in election
 */

#ifndef __ELECTION_EXCEPTION_H__
#define __ELECTION_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class ElectionException
          * @brief Header class ElectionException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 14-02-2011
          */
         class ElectionException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
			 * @param logger logger
             */
            ElectionException( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger) 
							: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /*__ELECTION_EXCEPTION_H__*/
