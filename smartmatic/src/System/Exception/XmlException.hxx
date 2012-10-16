/**
 * @file XmlException.hxx
 * @brief Class custom for exceptions in xml security
 */

#ifndef __XML_EXCEPTION_H__
#define __XML_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class XmlException
          * @brief Header class XmlException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 03-04-2011
          */
         class XmlException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code, default empty
             * @param logger logger
             */
             XmlException ( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}	
         };
      }
   }
}

#endif /* __XML_EXCEPTION_H__ */
