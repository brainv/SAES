/**
 * @file	alarm-ping-command.h
 *
 * @brief	Declares the alarm ping command class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saeshardware
 * Copyright (C)  2011 <>
 * 
 * saeshardware is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saeshardware is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ALARM_PING_COMMAND_H_
#define _ALARM_PING_COMMAND_H_

#include "command-base-alarm.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Manages the commands that control the ping of the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AlarmPingCommand: public CommandBaseAlarm
				{
	
				public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				AlarmPingCommand();

				/**
				 * @brief	Gets the specific response from raw.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void GetSpecificResponseFromRaw();
				
				protected:

				private:

				/**
				 * @brief	Gets the order of command.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void getOrderOfCommand();

				std::vector<unsigned char> result;  ///< The result of the command executed.

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Initialize();	

				/**
				 * @brief	Proccess response.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	response	The response.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool ProccessResponse(std::vector<unsigned char> response);

				unsigned char period;   ///< Indicate the waiting time between each run.
				unsigned char repeat;   ///< Indicate the amount of run. 
				static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}


#endif // _ALARM_PING_COMMAND_H_
