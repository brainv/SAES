/**
 * @file ConfigurationException.hxx
 * @brief Class custom for exceptions in election
 */

#ifndef __CONFIGURATION_EXCEPTION_H__
#define __CONFIGURATION_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class ConfigurationException
          * @brief Header class ConfigurationException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 14-02-2011
          */
         class ConfigurationException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
			 * @param logger logger
             */
            ConfigurationException( std::string message, std::string code, 
                            Smartmatic::Log::ISMTTLog* logger ) 
							: BaseException( message, code, logger){}
      }
   }
}

#endif /*__CONFIGURATION_EXCEPTION_H__*/
