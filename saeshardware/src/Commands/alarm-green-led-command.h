/**
 * @file	alarm-green-led-command.h
 *
 * @brief	Declares the alarm green led command class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C)  2010 <>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ALARM_GREEN_LED_COMMAND_H_
#define _ALARM_GREEN_LED_COMMAND_H_

#include "command-base-alarm.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Manages the commands that control the green led of the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AlarmGreenLedCommand: public CommandBaseAlarm
				{
	
				public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	period	The period.
				 * @param	repeat	The repeat.
				 */

				AlarmGreenLedCommand(unsigned char period, unsigned char repeat);

				/**
				 * @brief	Gets the specific response from raw.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void GetSpecificResponseFromRaw();
	
				protected:

				private:
				std::vector<unsigned char> result;  ///< The result

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
				};
			}
		}
	}
}

#endif // ALARM_GREEN_LED_COMMAND_H_
