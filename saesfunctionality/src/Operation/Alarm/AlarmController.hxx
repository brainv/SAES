/**
 * @file AlarmController.hxx
 * @brief Header class alarm box monitor
 * @date 16/05/2012
 * @author Yadickson Soto
 */

#ifndef ALARMBOXCONTROLLER_HXX_
#define ALARMBOXCONTROLLER_HXX_

#include <glibmm.h>
#include "Configuration/s-a-e-s-functionality-conf-manager.h"
#include <Devices/alarm-device.h>

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
				 * @class AlarmController
				 * @brief Class alarm box monitor
				 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
				 * @date 16/05/2012
				 */
				class AlarmController
				{
				private:
	                /**
	                 * @brief Class constructor
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					AlarmController();

			        std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmEnum> alarmList;  ///< The alarm list
					std::string message; ///< message alarm
					static AlarmController * instance; ///< instance
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

				public:

					Glib::Dispatcher signalAlarmBoxDisconnect;   ///< The signal alarm box disconnect
					Glib::Dispatcher signalAlarmBoxConnect;   ///< The signal alarm box connect

					/**
	                 * @brief Class destroy
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
	                 */
					virtual ~AlarmController();
			        /**
			         * @brief Add current alarm
			         * @param alarm new current alarm
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
			        void addAlarm(Smartmatic::SAES::Functionality::Configuration::AlarmEnum alarm);
			        /**
			         * @brief	Method getter all alarms
			         * @return	all alarms
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
			        std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmEnum> & getAlarms();
			        /**
			         * @brief	Method clear all alarms
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
			        void clearAlarms();
			        /**
			         * @brief	Method getter is alarm pending
			         * @return	true is alarm pending
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
			        bool isAlarmPending();
			        /**
			         * @brief	Method getter is critical alarm pending
			         * @return	true is critical alarm pending
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
					bool isCriticalAlarmPending();
			        /**
			         * @brief	Method getter is alarm requires go to authentication
			         * @return	true is alarm requires go to authentication
					 * @author Yadickson Soto <yadickson.soto@smartmatic.com>
					 * @date 16/05/2012
			         */
					bool isGoToAuthentication();
					/**
					 * @brief	Method setter message alarm
					 * @param 	message message alarm
					 * @date	16/05/2012
					 * @author	Yadickson Soto
					 */
					void setMessage(std::string message);
					/**
					 * @brief	Method getter message alarm
					 * @return 	message alarm
					 * @date	16/05/2012
					 * @author	Yadickson Soto
					 */
					std::string getMessage();
					/**
					 * @brief	Method getter instance class
					 * @return 	instance class
					 * @date	16/05/2012
					 * @author	Yadickson Soto
					 */
					static AlarmController * getInstance();
					/**
					 * @brief Gets the alarm steps.
			         * @param alarmCommands	The alarm commands.
			         * @param steps		 	The steps.
					 * @date	16/05/2012
					 * @author	Yadickson Soto
					 */
			        void getAlarmSteps(std::vector<Smartmatic::SAES::Functionality::Configuration::AlarmCommand>& alarmCommands, std::vector<Smartmatic::SAES::HW::Devices::AlarmStep>& steps);
				};
			}
		}
	}
}

#endif /* ALARMBOXCONTROLLER_HXX_ */
