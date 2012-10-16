/**
 * @file	alarm-device.h
 *
 * @brief	Declares the alarm device class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * commandstructure
 * Copyright (C)  2010 <>
 * 
 * commandstructure is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * commandstructure is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ALARM_DEVICE_H_
#define _ALARM_DEVICE_H_

#include "Commands/command-base-alarm.h"
#include "Commands/alarm-buzzer-command.h"
#include "Commands/alarm-green-led-command.h"
#include "Commands/alarm-red-led-command.h"
#include "Commands/alarm-ping-command.h"
#include "Connections/serial-port-connection.h"
#include <glibmm/thread.h>
#include <glibmm/timer.h>
#include "Log/ISMTTLog.h"
#include <glibmm.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				/**
				 * @brief	Represent the information about the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AlarmStep
				{			
					
					protected:
					public:

					enum AlarmSubModule
					{
						AB_Red,
						AB_Green,
						AB_Buzzer
							
					};

					/**
					 * @brief	Gets the period.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The period.
					 */

					unsigned int getPeriod()
					{
						return period;
					};

					/**
					 * @brief	Gets the is off.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool getIsOff()
					{
						return isOff;
					};

					/**
					 * @brief	Gets the device.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	The device.
					 */

					AlarmSubModule getDevice()
					{
						return device;
					}

					/**
					 * @brief	Sets a period.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	per	The per.
					 */

					void setPeriod(unsigned int per)
					{
						period = per;
					};

					/**
					 * @brief	Sets the is off.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	off	true to off.
					 */

					void setIsOff(bool off)
					{
						isOff = off;
					};

					/**
					 * @brief	Sets a device.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	module	The module.
					 */

					void setDevice(AlarmSubModule module)
					{
						device = module;
					}

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					AlarmStep()
					{

					}

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					~AlarmStep()
					{
						
					};

					private:
						
						unsigned int period;	///< The period
						bool isOff; ///< true to disable, false to enable the Off variable
						AlarmSubModule device;  ///< The alarm device.
				};

				/**
				 * @brief	Manage all the elements for configuring, activating and deactivating an alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AlarmDevice: public Smartmatic::SAES::HW::Connections::IPeekListener
				{

				protected:
					
				private:

					Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial;  ///< The connection serial
					static AlarmDevice *current_instance;   ///< The current instance of the alarm
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					AlarmDevice();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					virtual ~AlarmDevice();

					/**
					 * @brief	Peek event.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void  peekEvent(std::vector<unsigned char> & data);

				public:

					/**
					 * @brief	Sound an alarm.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param [in,out]	listOfSteps	The list of steps.
					 */

					void SoundAlarm(std::vector<AlarmStep>& listOfSteps);

					/**
					 * @brief	Shut down the alarm.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void ShutDownAlarm();		

					/**
					 * @brief	Gets the current alarm.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static AlarmDevice *Current();

					/**
					 * @typedef	sigc::signal<void> type_signal_detected
					 *
					 * @brief	definition of signal detected signal.
					 *
					 */

					typedef sigc::signal<void> type_signal_detected;

					/**
					 * @fn	type_signal_detected AlarmDevice::signal_detected();
					 *
					 * @brief	method to connect to receive the signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	signal.
					 */

					type_signal_detected signal_button_press_detected();

					/**
					 * @brief	Turn on the red led.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	period	The period.
					 */

					void TurnOnRedLed(unsigned char period);

					/**
					 * @brief	Turn on the green led.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	period	The period.
					 */

					void TurnOnGreenLed(unsigned char period);

					/**
					 * @brief	Turn off the red led.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void TurnOffRedLed();

					/**
					 * @brief	Turn off the green led.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void TurnOffGreenLed();

					/**
					 * @brief	Turn off the buzzer.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void TurnOffBuzzer();

					/**
					 * @brief	Turn on the buzzer.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	period	The period.
					 */

					void TurnOnBuzzer(unsigned char period);

					/**
					 * @brief	Sends a ping.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool sendPing();

					/**
					 * @brief	Wait for the button to respond.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void WaitForButton();

					/**
					 * @brief Method open port
					 * @return true is open success
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					bool open();
					/**
					 * @brief Method resync port
					 * @return true is resync success
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					bool resync();
					/**
					 * @brief Method open port
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					void close();
					/**
					 * @brief Method test
					 * @return true is test success
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					bool test();

				private:
					Glib::Mutex mutex; ///< mutex
					type_signal_detected m_signal_detected; ///< The signal detected
				};
			}
		}
	}
}

#endif // _ALARM_DEVICE_H_

