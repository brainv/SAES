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

#include "p168-a-bright-command.h"

using namespace std;
using namespace Smartmatic::SAES::HW::Commands;

P168ABrightCommand::P168ABrightCommand(unsigned char brightness):CommandBaseP168A()
{   
	bright = brightness;
}

void P168ABrightCommand::Initialize()
{
	CommandByte.push_back(0x04);
	Data.push_back(bright);
}

bool P168ABrightCommand::ProccessResponse(vector<unsigned char> response)
{
	if(response.size()>3 && response[0] == 0x1B && response[1] == 0x04 && response[2]== 0x01)
	{
		return true;
	}
	return false;
}

void P168ABrightCommand::GetSpecificResponseFromRaw()
{
	
}
