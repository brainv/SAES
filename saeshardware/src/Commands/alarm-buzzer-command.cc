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

#include "alarm-buzzer-command.h"
using namespace std;
using namespace Smartmatic::SAES::HW::Commands;

AlarmBuzzerCommand::AlarmBuzzerCommand(unsigned char periodB, unsigned char repeatB):CommandBaseAlarm()
{
	period = periodB;
	repeat = repeatB;
	hasResponse = true;
}

void AlarmBuzzerCommand::Initialize()
{
	CommandByte.push_back(0x05);
	Data.push_back(period);
	Data.push_back(repeat);
}

bool AlarmBuzzerCommand::ProccessResponse(vector<unsigned char> response)
{
	return true;

}

void AlarmBuzzerCommand::GetSpecificResponseFromRaw()
{
	return;
	/*
	if(rawResponse[1] ==0)
	{
		// bool everythingOk = true;
	}
	*/
	
}
