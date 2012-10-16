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

#include "alarm-device.h"
#include <Log/SMTTLogManager.h>
#include "SerialPathManager.hxx"

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
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Connections;
using namespace Smartmatic::Log;

ISMTTLog* AlarmDevice::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.HW.Devices.AlarmDevice",GETTEXT_PACKAGE);
AlarmDevice* AlarmDevice::current_instance = NULL;

AlarmDevice::AlarmDevice()
{
	connectionSerial = new SerialPortConnection(57600,Parity::PARITY_8N1,8,SerialPathManager::getInstance()->getAlarmDevice(),true);
	connectionSerial->signal_detected.connect(sigc::mem_fun(*this, &AlarmDevice::peekEvent));
	connectionSerial->Open();
}

AlarmDevice::~AlarmDevice()
{
	if (connectionSerial)
	{
		delete connectionSerial;
		connectionSerial = NULL;
	}
}

AlarmDevice *AlarmDevice::Current()
{
	if (!current_instance)
		current_instance = new AlarmDevice();

	return current_instance;
}

bool AlarmDevice::sendPing()
{
	Glib::Mutex::Lock lock(mutex);
	AlarmPingCommand pingCommand;
	pingCommand.Execute(connectionSerial);
	return pingCommand.isSuccess();
}

void AlarmDevice::peekEvent(std::vector<unsigned char> & data)
{
	if(data.size()>4)
	{
		if(data[0] == 0x55 && data[1] == 0xA1 && data[2] == 0x00 && data[3] == 0x00 && data[4] == 0xAA)
		{
			logger->Debug("buttonPress");
			m_signal_detected.emit();
		}
	}
}

void AlarmDevice::ShutDownAlarm()
{
	Glib::Mutex::Lock lock(mutex);
	TurnOffRedLed();
	usleep(20000);
	TurnOffGreenLed();
	usleep(20000);
	TurnOffBuzzer();
	usleep(20000);
}

void AlarmDevice::SoundAlarm(std::vector<AlarmStep>& listOfSteps)
{
	Glib::Mutex::Lock lock(mutex);
	logger->Debug("SendingAlarm");

	for(unsigned int i=0;i < listOfSteps.size();i++)
	{
		switch(listOfSteps[i].getDevice())
		{
			case AlarmStep::AB_Green:
				if(listOfSteps[i].getIsOff())
				{
					logger->Debug("turning off green led");
					TurnOffGreenLed();
				}
				else
				{
					logger->Debug("turning on green led with period " + listOfSteps[i].getPeriod());
					TurnOnGreenLed (listOfSteps[i].getPeriod());
				}
				break;
			case AlarmStep::AB_Red:
				if(listOfSteps[i].getIsOff())
				{
					logger->Debug("turning off red led");
					TurnOffRedLed();
				}
				else
				{
					logger->Debug("turning on red led with period " + listOfSteps[i].getPeriod());
					TurnOnRedLed (listOfSteps[i].getPeriod());
				}
				break;
			case AlarmStep::AB_Buzzer:
				if(listOfSteps[i].getIsOff())
				{
					logger->Debug("turning off buzzer");
					TurnOffBuzzer();
				}
				else
				{
					logger->Debug("turning on buzzer with period " + listOfSteps[i].getPeriod());
					TurnOnBuzzer (listOfSteps[i].getPeriod());
				}
				break;
		}

		usleep(20000);
	}
}

void AlarmDevice::TurnOnRedLed(unsigned char period)
{
	AlarmRedLedCommand greenLed(period,0x01);
	greenLed.Execute(connectionSerial);
}

void AlarmDevice::TurnOnGreenLed(unsigned char period)
{
	AlarmGreenLedCommand redLed(period,0x01);
	redLed.Execute(connectionSerial);
}

void AlarmDevice::TurnOffRedLed()
{
	AlarmRedLedCommand redLed(0x00,0x00);
	redLed.Execute(connectionSerial);
}

void AlarmDevice::TurnOffGreenLed()
{
	AlarmGreenLedCommand greenLed(0x00,0x00);
	greenLed.Execute(connectionSerial);
}

void AlarmDevice::TurnOnBuzzer(unsigned char period)
{
	AlarmBuzzerCommand buzzer(period,0x01);
	buzzer.Execute(connectionSerial);
}

void AlarmDevice::TurnOffBuzzer()
{
	AlarmBuzzerCommand buzzer(0x00,0x00);
	buzzer.Execute(connectionSerial);
}

AlarmDevice::type_signal_detected AlarmDevice::signal_button_press_detected()
{
	return m_signal_detected;
}

bool AlarmDevice::open()
{
	return connectionSerial->Open();
}

bool AlarmDevice::resync()
{
	Glib::Mutex::Lock lock(mutex);

	bool ping;

	connectionSerial->Close();

	ping = connectionSerial->Open();

	if(!ping)
	{
		connectionSerial->Close();
	}

	return ping;
}

void AlarmDevice::close()
{
	connectionSerial->Close();
}

bool AlarmDevice::test()
{
	bool validate = sendPing();

	if (validate)
	{
		TurnOnRedLed(1);
		usleep(200000);
		TurnOnGreenLed(1);
		usleep(200000);
		TurnOnBuzzer(1);

		usleep(200000);
		TurnOffRedLed();
		usleep(200000);
		TurnOffGreenLed();
		usleep(200000);
		TurnOffBuzzer();
	}

	return validate;
}
