/**
 * @file	barcode-device.cc
 * @brief	Body barcode device class.
 */

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

#include "barcode-device.h"
#include <System/IO/Directory.h>
#include <System/IO/File.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <Log/SMTTLogManager.h>
#include <glibmm/main.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>

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

using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::HW::Connections;
using namespace std; 
using namespace Smartmatic::SAES::HW::Commands;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System;

ISMTTLog* BarcodeDevice::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.HW.Devices.BarcodeDevice",GETTEXT_PACKAGE);
BarcodeDevice* BarcodeDevice::current_instance = NULL;

bool BarcodeDevice::stopSendingCommands = false;
bool BarcodeDevice::gettingDeviceModel = false;

BarcodeDevice::BarcodeDevice()
{
	this->closeConnection = false;
	this->sendSignal = false;
	this->deviceName = "";
	BarcodeDevice::gettingDeviceModel = false;
	BarcodeDevice::stopSendingCommands = false;
	sendingConfigurationCommands = false;
	totalCommands = 0;
	commandRetries = 0;
	this->connectionSerial = NULL;
	this->countReceivedData = 0;

	vector<string> listOfPossibleDevices = SAESHardwareConfigurationManager::Current()->getListOfBarcodePorts();
	string chosenDevice = "/dev/ttyUSB0";
	bool found = false;
	for(unsigned int i = 0;i< listOfPossibleDevices.size();i++)
	{
		logger->Debug("Devices to look for are: " + listOfPossibleDevices[i]);
		string mediaPath= "/dev";
		DIR* d = opendir(mediaPath.c_str());
		struct dirent* dirp;
		if (d)
		{
			while ( (dirp = readdir(d)) != NULL )
			{
				string dirNameMedia(dirp->d_name);
				if(dirNameMedia.find(".")==string::npos)
				{
					if(dirNameMedia.compare(listOfPossibleDevices[i])==0)
					{
						chosenDevice = "/dev/" + dirNameMedia;
						logger->Debug("device found");
						logger->Debug("serial port will try to open: " + chosenDevice);
						found = true;
						break;
					}
				}
			}
		}
		closedir(d);
		if(found)
		{
			break;
		}
	}

	//int pollingTime = SAESHardwareConfigurationManager::Current()->getBarcodeDeviceConfiguration().getSerialPollingTime();

	connectionSerial = new SerialPortConnection(57600,Parity::PARITY_8N1,8,chosenDevice,false, /*pollingTime,*/ false);
	connectionSerial->signal_detected.connect(sigc::mem_fun(*this, &BarcodeDevice::RecievedData));
	BarcodeCommandWrapper::Current()->SetSerialPortConnection(connectionSerial);

	ping = false;//connectionSerial->Open();
}

BarcodeDevice::~BarcodeDevice()
{
	if (connectionSerial)
	{
		delete(connectionSerial);
	}
}

void BarcodeDevice::Open()
{
	Glib::Mutex::Lock lock(openConnectionMutex);
	logger->Debug("Fase # 2 : Open barcode device");
	ping = connectionSerial->Open();
	countReceivedData = 0;
}

bool BarcodeDevice::Resync()
{
	if (ping)
	{
		Close();
	}

	Open();

	if(!ping)
	{
		Close();
	}

	return ping;
}

void BarcodeDevice::Close()
{
	logger->Debug("Fase # 2 : Close barcode device");
	countReceivedData = 0;
	commandTimeout.disconnect();
	connectionSerial->Close();
	ping = false;
}

BarcodeDevice *BarcodeDevice::Current()
{
	if (!current_instance)
		current_instance = new BarcodeDevice();

	return current_instance;
}

bool BarcodeDevice::TurnOnScanSound(bool turnOn)
{
	return BarcodeCommandWrapper::Current()->SetVoiceOfDecode(turnOn);
}

bool BarcodeDevice::SetReadMode(BarcodeCommandWrapper::BarcodeCommandWrapper_ReadMode mode)
{
	return BarcodeCommandWrapper::Current()->SetReadMode(mode);
}

bool BarcodeDevice::SetDelayOfReading(int time_ms)
{
	std::vector<unsigned char> data;

	float div;

	for(float i = 10000; i >=1; i/=10)
	{
		div = time_ms / i;
		div+=48;

		data.push_back((unsigned char)div);

		time_ms = time_ms % (int)i;
	}

	return BarcodeCommandWrapper::Current()->SetDelayOfReading(data, true);
}

bool BarcodeDevice::sendPing()
{
	return ping;
}

void  BarcodeDevice::RecievedData(std::vector<unsigned char> & data)
{
	Glib::Mutex::Lock lock(BarcodeDevice::mutex);

	if(gettingDeviceModel)
	{
		deviceName = BarcodeCommandWrapper::Current()->GetDeviceModel(data);
		if(!deviceName.empty())
		{
			stringstream ss;
			ss << "Device Model is: ";
			ss <<  deviceName;
			logger->Debug(ss.str());
			gettingDeviceModel = false;
			Close();
		}
		else
		{
			logger->Debug("Error getting device model");
			deviceName = "";
		}
		return;
	}

	if(data.size() == 1)
	{
		commandTimeout.disconnect();

		if(data[0] == 0x06)
		{
			logger->Debug("Good Command Response");
			if(sendingConfigurationCommands)
				SendNextCommand();
		}
		else if(data[0] == 0x15)
		{
			logger->Debug("Bad Command Response");
			if(sendingConfigurationCommands)
				RetryCommand();
		}
		else
		{
			logger->Debug("Unknow Command Response");
			if(sendingConfigurationCommands)
				RetryCommand();
		}
		return;
	}
	else if(sendingConfigurationCommands)
	{
		logger->Debug("Sending configuration commands. Size response > 1.");

		stringstream ss;
		ss << "Response Get:";
		for(unsigned int i = 0; i < data.size(); i++)
		{
			ss <<" ";
			ss << (int)data[i];
		}

		logger->Debug(ss.str());

		if(data[0] == 0x06)
		{
			logger->Debug("Interpreting as Good Command Response");
			SendNextCommand();
		}
		return;
	}

	{
		std::stringstream ss;
		ss << "Fase # 2 : Get signal serial data - size : " << data.size() << " - count data : " << ++countReceivedData;
		logger->Debug(ss.str());
	}

	Smartmatic::System::SafeBuffer *safeBuffer = new Smartmatic::System::SafeBuffer(&data[0],data.size());

	{
		std::stringstream ss;
		ss << "Fase # 2 : Emit signal barcode data - size : " << safeBuffer->GetSize();
		logger->Debug(ss.str());
	}

	signal_detected.emit(safeBuffer);
	logger->Debug("Fase # 2 : End signal barcode data");
}

bool BarcodeDevice::presentDevice()
{
	return connectionSerial->presentDevice();
}

void BarcodeDevice::enabledEvent()
{
    (void) signal(SIGUSR1, BarcodeDevice::signalHandler);  // señal probada # 10
    std::string data = "SIGUSR1";
    SafeBuffer buffer(data);
    std::string sigFile = SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getSyncFileSignalUSER1();
    File::saveBufferToFile(buffer,sigFile);
}

void BarcodeDevice::signalHandler(int sig)
{
	BarcodeDevice::Current()->Close();

	if (!BarcodeDevice::Current()->presentDevice())
	{
		stopSendingCommands = true;
		BarcodeDevice::logger->Audit(N_("Smartmatic.SAES.HW.Devices.BarcodeDevice.BarcodeDisconnected"));
		BarcodeDevice::logger->Debug("Barcode disconnected");
		Current()->m_signalDisconnected.emit();
	}
	else
	{
		stopSendingCommands = false;
		Current()->GetDeviceModelOnThread();
		BarcodeDevice::logger->Audit(N_("Smartmatic.SAES.HW.Devices.BarcodeDevice.BarcodeConnected"));
		BarcodeDevice::logger->Debug("Barcode connected");
	}
}

void BarcodeDevice::GetDeviceModelOnThread()
{
	BarcodeDevice::gettingDeviceModel = false;
	BarcodeDevice::stopSendingCommands = false;
	sendingConfigurationCommands = false;
	Glib::Thread::create(sigc::ptr_fun(&BarcodeDevice::GetDeviceModel), false);
}

void BarcodeDevice::GetDeviceModel()
{
	BarcodeDevice::logger->Debug("Getting device model");
	if(!gettingDeviceModel)
	{
		gettingDeviceModel = true;

		if(BarcodeDevice::Current()->sendPing() == false)
			BarcodeDevice::Current()->Resync();

		BarcodeCommandWrapper::Current()->AskDeviceModel();

		sleep(2);	//Wait for response

		if(gettingDeviceModel)
		{
			BarcodeCommandWrapper::Current()->AskDeviceModel();
			sleep(2);	//Wait for response
		}

		if(gettingDeviceModel)
		{
			gettingDeviceModel = false;
			BarcodeDevice::Current()->Close();
			usleep(650000);//Allow port to close
		}
	}

	Glib::signal_timeout().connect_once(sigc::ptr_fun(&BarcodeDevice::EmitSignalConnected), 100);
}

void BarcodeDevice::EmitSignalConnected()
{
	logger->Debug("EmitSignalConnected");
	BarcodeDevice::Current()->m_signalConnected.emit();
}

BarcodeDevice::connection_signal BarcodeDevice::signalConnected()
{
	return m_signalConnected;
}

BarcodeDevice::connection_signal BarcodeDevice::signalDisconnected()
{
	return m_signalDisconnected;
}

void BarcodeDevice::SendConfigurationCommandsThread()
{
	if(sendingConfigurationCommands || stopSendingCommands)
	{
		logger->Debug("Skip send command");
		//Avoid send configuration commands two times in a row
		return;
	}

	sendingConfigurationCommands = true;

	commandsIter = commandsSeq.begin();
	commandRetries = commandsIter->getRetries();

	SendCommand();
}

void BarcodeDevice::SendConfigurationCommands(std::string commandBlockName, bool emitSignal, bool closeConnection)
{
	this->closeConnection = closeConnection;
	this->sendSignal = emitSignal;

	if(!sendingConfigurationCommands && !stopSendingCommands)
	{
		signalStartSendCommand.emit();
		logger->Audit(N_("Smartmatic.SAES.HW.Devices.BarcodeDevice.SendConfigurationCommands"));
		logger->Debug("Send command to device : " + deviceName);

		commandsSeq = SAESHardwareConfigurationManager::Current()->getBarcodeConfigurationCommands(commandBlockName, deviceName);

		if(!commandsSeq.empty())
		{
			Glib::Thread::create(sigc::mem_fun(*this,&BarcodeDevice::SendConfigurationCommandsThread), false);
		}
		else
		{
			Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), true), 100);
		}
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), false), 100);
	}
}

void BarcodeDevice::EmitSignal(bool signal)
{
	signalEndSendCommand.emit();
	sendingConfigurationCommands = false;

	if(sendSignal)
	{
		m_signal_commands_sent.emit(signal);
	}

	if(closeConnection)
	{
		Close();
	}
}

void BarcodeDevice::SendNextCommand()
{
	if(stopSendingCommands)
	{
		sendingConfigurationCommands = false;
		Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), false), 100);
		return;
	}

	commandsIter++;

	if(commandsIter !=  commandsSeq.end())
	{
		commandRetries = commandsIter->getRetries();
		SendCommand();
	}
	else
	{
		sendingConfigurationCommands = false;
		Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), true), 100);
	}
}

void BarcodeDevice::SendCommand()
{
	commandTimeout.disconnect();

	if(stopSendingCommands)
	{
		sendingConfigurationCommands = false;
		Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), false), 100);
		return;
	}

	if(commandsIter != commandsSeq.end())
	{
		logger->Debug("Sending Command: " + commandsIter->getCommand());

		if(BarcodeCommandWrapper::Current()->SendConfigurationCommand(commandsIter->getCommand()))
		{
			sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &BarcodeDevice::CommandTimeout), 0);
			commandTimeout = Glib::signal_timeout().connect(my_slot, commandsIter->getDelayResponse());
		}
		else
		{
			logger->Debug("Error Sending Command: " + commandsIter->getCommand());

			if(commandsIter->getMandatorySent())
			{
				sendingConfigurationCommands = false;
				Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), false), 100);
			}
			else
			{
				RetryCommand();
			}
		}
	}
}

bool BarcodeDevice::CommandTimeout(int timer)
{
	commandTimeout.disconnect();
	logger->Debug("Command Timeout");

	RetryCommand();
	return false;
}

void BarcodeDevice::RetryCommand()
{
	commandRetries--;

	if(commandRetries > 0)
	{
		SendCommand();
	}
	else
	{
		if(commandsIter->getMandatorySent())
		{
			sendingConfigurationCommands = false;
			Glib::signal_timeout().connect_once(sigc::bind<bool>(sigc::mem_fun(*this, &BarcodeDevice::EmitSignal), false), 100);
		}
		else
		{
			SendNextCommand();
		}
	}
}

BarcodeDevice::signal_commands_sent BarcodeDevice::signalCommandsSent()
{
	return m_signal_commands_sent;
}

BarcodeDevice::signal_detected_data BarcodeDevice::signalDetected()
{
	return signal_detected;
}

sigc::signal<void> BarcodeDevice::getSignalStartSendCommand()
{
	return signalStartSendCommand;
}

sigc::signal<void> BarcodeDevice::getSignalEndSendCommand()
{
	return signalEndSendCommand;
}
