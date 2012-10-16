/*
 * BarcodeCommandWrapper.cpp
 *
 *  Created on: Aug 3, 2011
 *      Author: Juan.Delgado
 */

#include "BarcodeCommandWrapper.h"

using namespace Smartmatic::SAES::HW::Commands;

BarcodeCommandWrapper* BarcodeCommandWrapper::current_instance = NULL;

BarcodeCommandWrapper* BarcodeCommandWrapper::Current()
{
	if(current_instance == NULL)
	{
		current_instance = new BarcodeCommandWrapper();
	}

	return current_instance;
}

void BarcodeCommandWrapper::SetSerialPortConnection(Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial)
{
	this->connectionSerial = connectionSerial;
}

BarcodeCommandWrapper::BarcodeCommandWrapper()
{

}

bool BarcodeCommandWrapper::SetVoiceOfDecode(bool turnOn)
{
	/**
	 * Voice of Decode:
	 * disable:	NLS0203000
	 * enable:	NLS0203010
	 */

	std::vector<unsigned char> data;

	data.push_back(0x4E);
	data.push_back(0x4C);
	data.push_back(0x53);
	data.push_back(0x30);
	data.push_back(0x32);
	data.push_back(0x30);
	data.push_back(0x33);
	data.push_back(0x30);

	if(turnOn)
	{
		data.push_back(0x31);
	}
	else
	{
		data.push_back(0x30);
	}

	data.push_back(0x30);

	return connectionSerial->Send(data);
}

bool BarcodeCommandWrapper::SetReadMode(BarcodeCommandWrapper_ReadMode mode)
{
	/**
	 * Reading mode:
	 * Trigger:					NLS0302000
	 * Auto Scan:				NLS0302010
	 * Continue Scan:			NLS0302020
	 * Once continue auto scan:	NLS0302030
	 */

	std::vector<unsigned char> data;

	data.push_back(0x4E);
	data.push_back(0x4C);
	data.push_back(0x53);
	data.push_back(0x30);
	data.push_back(0x33);
	data.push_back(0x30);
	data.push_back(0x32);
	data.push_back(0x30);

	switch(mode)
	{
	case BARCODE_TRIGGER:
		data.push_back(0x30);
		break;
	case BARCODE_AUTO_SCAN:
		data.push_back(0x31);
		break;
	case BARCODE_CONTINUE_SCAN:
		data.push_back(0x32);
		break;
	case BARCODE_ONCE_CONTINUE_AUTO_SCAN:
		data.push_back(0x33);
		break;
	}

	data.push_back(0x30);

	return connectionSerial->Send(data);
}

bool BarcodeCommandWrapper::SetDelayOfReading(std::vector<unsigned char> time_ms, bool duplicateReading)
{
	/**
	 * Delay Selection:
	 * Set Delay Of Reading:			NLS0313000=3000
	 * Set No Duplicate Reading time:	NLS0313010=1000
	 */

	std::vector<unsigned char> data;

	data.push_back(0x4E);
	data.push_back(0x4C);
	data.push_back(0x53);
	data.push_back(0x30);
	data.push_back(0x33);
	data.push_back(0x31);
	data.push_back(0x33);
	data.push_back(0x30);

	if(duplicateReading)
	{
		data.push_back(0x31);
	}
	else
	{
		data.push_back(0x30);
	}

	data.push_back(0x30);
	data.push_back(0x3D);

	data.insert(data.end(), time_ms.begin(), time_ms.end());

	return connectionSerial->Send(data);
}

bool BarcodeCommandWrapper::SetIncompletelyDelay(bool incomplete)
{
	/**
	 * Delay Selection:
	 * incompletely delay:	NLS0313020
	 * completely delay:	NLS0313030
	 */

	std::vector<unsigned char> data;

	data.push_back(0x4E);
	data.push_back(0x4C);
	data.push_back(0x53);
	data.push_back(0x30);
	data.push_back(0x33);
	data.push_back(0x31);
	data.push_back(0x33);
	data.push_back(0x30);

	if(incomplete)
	{
		data.push_back(0x32);
	}
	else
	{
		data.push_back(0x33);
	}

	data.push_back(0x30);

	return connectionSerial->Send(data);
}

void BarcodeCommandWrapper::FormatBarcodeQueryCommand(std::vector<unsigned char> &data)
{
	/*EXAMPLE
	 * std::vector<unsigned char> data;

	data.push_back(0x42);
	data.push_back(0x30);
	data.push_back(0x30);
	data.push_back(0x30);

	FormatBarcodeQueryCommand(data);*/

	std::vector<unsigned char> temp;
	temp = data;

	//prefix1 + lens + command + LRC

	data.clear();

	data.push_back(0x7E);
	data.push_back(0x00);

	int totalLenght = temp.size();

	unsigned char lenght0 = totalLenght & 0x000000ff;
	unsigned char lenght1 = (totalLenght & 0x0000ff00) >>8;

	data.push_back(lenght1);
	data.push_back(lenght0);

	data.insert(data.end(), temp.begin(), temp.end());

	unsigned char lrc = 0xFF;

	for(unsigned int i = 2; i < data.size(); i++)
	{
		lrc = lrc ^ data[i];
	}

	data.push_back(lrc);
}

bool BarcodeCommandWrapper::SendConfigurationCommand(std::string command)
{
	std::vector<unsigned char> data;

	for(unsigned int i = 0; i < command.size(); i++)
	{
		data.push_back(command[i]);
	}

	return connectionSerial->Send(data);
}

Glib::ustring BarcodeCommandWrapper::GetDeviceModel(std::vector<unsigned char> & data)
{
	std::stringstream ss;

	for(unsigned int i = 0; i < data.size(); i++)
	{
		ss << data[i + 4];
	}

	Glib::ustring deviceID = "";
	std::string fullData = ss.str();
	size_t found;

	found = fullData.find("Device ID:");

	if(found != std::string::npos)
	{
		found += 10;
		deviceID = fullData.substr(found);

		while(deviceID[0] == ' ')
		{
			deviceID.erase(0, 1);
		}

		found = deviceID.find_first_of(' ');

		if(found != std::string::npos)
		{
			deviceID.erase(found);
		}
	}

	deviceID = deviceID.lowercase();

	return deviceID;
}


bool BarcodeCommandWrapper::AskDeviceModel()
{
	std::vector<unsigned char> data;

	/*
	 * ESN 		0x48+0x30+0x32+0x30
	 * S/N 		0x48+0x30+0x33+0x30
	 * Date		0x48+0x30+0x34+0x30
	 */

	data.push_back(0x33);
	data.push_back(0x47);

	FormatBarcodeQueryCommand(data);

	return connectionSerial->Send(data);
}

