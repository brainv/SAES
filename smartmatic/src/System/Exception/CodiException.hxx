/**
 * @file CodiException.hxx
 * @brief Class custom for exceptions in codi files
 * @date 01/03/2012
 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
 */

#ifndef __CODI_EXCEPTION_H__
#define __CODI_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class CodiException
          * @brief Header class CodiException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 01/03/2012
          */
         class CodiException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
             * @param logger logger
             * @date 01/03/2012
             * @author Yadickson Soto <yadickson.soto@smartmatic.com>
             */
             CodiException ( std::string message, std::string code,
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /* __CODI_EXCEPTION_H__ */
