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

#include "p168-a-device.h"
#include "Commands/p168-a-bright-command.h"
#include "SerialPathManager.hxx"

using namespace Smartmatic::SAES::HW::Connections;
using namespace std; 
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Commands;

P168ADevice::P168ADevice()
{
	connectionSerial = new SerialPortConnection(9600,Parity::PARITY_8N1,8,SerialPathManager::getInstance()->getP168ADevice(),true);
	connectionSerial->Open();
}

P168ADevice* P168ADevice::current_instance = NULL;

P168ADevice *P168ADevice::Current()
{
	if (!current_instance)
		current_instance = new P168ADevice();

	return current_instance;
}
void P168ADevice::setBrightness(unsigned char bright)
{
	P168ABrightCommand brightCommand(bright);
	brightCommand.Execute(connectionSerial);
}

bool P168ADevice::sendPing()
{
	return true;
}
