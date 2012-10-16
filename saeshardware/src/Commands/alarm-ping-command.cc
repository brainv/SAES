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

#include "alarm-ping-command.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <sstream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace std;
using namespace Smartmatic::SAES::HW::Commands;
using namespace Smartmatic::Log;

ISMTTLog* AlarmPingCommand::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.HW.Commands.AlarmPingCommand",GETTEXT_PACKAGE);

AlarmPingCommand::AlarmPingCommand():CommandBaseAlarm()
{

	hasResponse = true;
}

void AlarmPingCommand::getOrderOfCommand()
{
	addSection(sections::Sender);
	addSection (sections::CommandByte);
	addSection (sections::Data);
	addSection (sections::Trailer);
	
}

void AlarmPingCommand::Initialize()
{
	CommandByte.push_back(0x00);
	Data.push_back(0x00);
	Data.push_back(0x00);
}

bool AlarmPingCommand::ProccessResponse(vector<unsigned char> response)
{
	if(response.size()>=5 && response[0] ==0x55 && response[1] ==0x00 && response[2] ==0x00
	   && response[3] ==0x00 && response[4] ==0xAA)
	{
		return true;
	}

	if(response.size() > 2)
	{
		std::stringstream ss;
		ss << "Byte[0]: " << response[0]<< " Byte[1]: "<< response[1];
		logger->Debug(ss.str());
	}


	return false;
}

void AlarmPingCommand::GetSpecificResponseFromRaw()
{

	
}

