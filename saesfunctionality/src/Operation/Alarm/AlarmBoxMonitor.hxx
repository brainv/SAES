/**
 * @file AlarmBoxMonitor.hxx
 * @brief Header class alarm box monitor
 * @date 16/05/2012
 * @author Yadickson Soto
 */

#ifndef ALARMBOXMONITOR_HXX_
#define ALARMBOXMONITOR_HXX_

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
			namespace Alarm
			{
				/**
				 * @class AlarmBoxMonitor
				 * @brief Class alarm box monitor
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 16/05/2012
				 */
				class AlarmBoxMonitor
				{
				private:
	                /**
	                 * @brief Class constructor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					AlarmBoxMonitor();
	                /**
	                 * @brief Method run alarm box monitor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					void run();
	                /**
	                 * @brief Method check alarm box
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 17/05/2012
	                 */
					void checkThread();

					static AlarmBoxMonitor * instance; ///< instance
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
					bool flagRun; ///< flag is runnnig monitor
					bool flagThreadRun; ///< flag in running thread

				public:

					Glib::Dispatcher signalConnect; ///< The signal connect
					Glib::Dispatcher signalDisconnect;   ///< The signal disconnect

					/**
	                 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					virtual ~AlarmBoxMonitor();
	                /**
	                 * @brief Method start alarm box monitor
	                 * @param monitoringTime monitor time connected
	                 * @param searchTime search disconnected
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					void start(unsigned int monitoringTime = 4000, unsigned int searchTime = 1000);
	                /**
	                 * @brief Method stop alarm box monitor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					void stop();
	                /**
	                 * @brief Method getter is running alarm box monitor
	                 * @return true is running
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					bool isRunning();
	                /**
	                 * @brief Method getter is running alarm box monitor
	                 * @return true is running
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					bool isConnect();
	                /**
	                 * @brief Method check alarm box
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 17/05/2012
	                 */
					void check();
	                /**
	                 * @brief Method getter instance
	                 * @return instance
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					static AlarmBoxMonitor * getInstance();

				private:

					unsigned int monitoringTime; ///<  monitor time connected
					unsigned int searchTime; ///< search disconnected
					bool flagConnect; ///< flag is connect
				};
			}
		}
	}
}

#endif /* ALARMBOXMONITOR_HXX_ */
