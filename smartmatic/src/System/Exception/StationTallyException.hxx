/**
 * @file StationTallyException.hxx
 * @brief Class custom for exceptions in station tally
 */

#ifndef __STATION_TALLY_EXCEPTION_H__
#define __STATION_TALLY_EXCEPTION_H__

#include "BaseException.hxx"

namespace Smartmatic
{
   namespace System
   {
      namespace Exception
      {
         /**
          * @class StationTallyException
          * @brief Header class StationTallyException
          * @author Yadickson Soto <yadickson.soto@smartmatic.com>
          * @date 14-02-2011
          */
         class StationTallyException : public BaseException
         {
         public:
            /**
             * @brief Class constructor
             * @param message exception message
             * @param code exception code
			 * @param logger logger
             */
            StationTallyException( std::string message, std::string code, 
                            		Smartmatic::Log::ISMTTLog* logger) 
									: BaseException( message, code, logger){}
         };
      }
   }
}

#endif /*__STATION_TALLY_EXCEPTION_H__*/
