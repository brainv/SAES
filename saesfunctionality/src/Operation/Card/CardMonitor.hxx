/**
 * @file CardMonitor.hxx
 * @brief Header class card monitor
 * @date 06/03/2012
 * @author Yadickson Soto
 */

#ifndef CARDMONITOR_HXX_
#define CARDMONITOR_HXX_

#include <glibmm.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Operation
		{
			namespace Card
			{
				/**
				 * @class CardMonitor
				 * @brief Class card monitor
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 06/03/2012
				 */
				class CardMonitor
				{
				private:
	                /**
	                 * @brief Class constructor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					CardMonitor();
	                /**
	                 * @brief Method run card monitor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					void run();

					static CardMonitor * instance; ///< instance
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
					bool flagRun; ///< flag is runnnig monitor
					bool flagThreadRun; ///< flag in running thread

				public:

					Glib::Dispatcher signalCardInsert;   ///< The signal card insert
					Glib::Dispatcher signalCardRemove;   ///< The signal card remove
          Glib::Dispatcher signalCardReaderUnresponsive;   ///< The signal card reader unresponsive

					/**
	                 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					virtual ~CardMonitor();
	                /**
	                 * @brief Method start card monitor
	                 * @param valueTime value time
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					void start(unsigned int valueTime = 1000);
	                /**
	                 * @brief Method stop card monitor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					void stop();
	                /**
	                 * @brief Method getter is running card monitor
	                 * @return true is running
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 08/03/2012
	                 */
					bool isRunning();
	                /**
	                 * @brief Method getter is card present
	                 * @return true is card present
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 08/03/2012
	                 */
					bool isCardPresent();
	                /**
	                 * @brief Method getter instance
	                 * @return instance
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 06/03/2012
	                 */
					static CardMonitor * getInstance();

				private:

					unsigned int valueTime; ///< value time
					bool present; ///< flag card present
				};
			}
		}
	}
}

#endif /* CARDMONITOR_HXX_ */
