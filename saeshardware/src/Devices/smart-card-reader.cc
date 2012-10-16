/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk-foobar
 * Copyright (C)  2011 <>
 * 
 * gtk-foobar is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-foobar is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Devices/smart-card-reader.h"
#include "Devices/a-u9520-card-reader.h"
#include "Devices/athena-card-reader.h"
#include "Configuration/s-a-e-s-hardware-conf-manager.h"

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

using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace std; 

SmartCardReader::SmartCardReader()
{

}

SmartCardReader* SmartCardReader::current_instance = NULL;

SmartCardReader *SmartCardReader::Current()
{
	if (!current_instance)
		current_instance = new SmartCardReader();

	return current_instance;
}


bool SmartCardReader::Read(int address, int count, std::vector<unsigned char> & buffer)
{
    std::vector<unsigned char> finalResult;
    bool validate = false;

	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			validate = AU9520Reader::Current()->Read(address,count, buffer, reader::Memory);
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			finalResult = AthenaCardReader::Current()->Read(address,count);
			validate = true;
			break;	
	}

    return validate;
}

bool SmartCardReader::Write(int address, std::vector<unsigned char> & buffer, int offset, int count)
{
	bool validate = false;

	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			validate = AU9520Reader::Current()->Write(address,buffer,offset,count,reader::Memory);
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			AthenaCardReader::Current()->Write(address,buffer,offset,count);
			validate = true;
			break;	
	}

	return validate;
}

bool SmartCardReader::init()
{
	bool validate = false;

	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			AU9520Reader::Current()->getTypeOfCard();
			validate = true;
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			validate = true;
			break;	
	}

	return validate;
}

bool SmartCardReader::getCardPresent()
{
	bool isPresent = false;
	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			isPresent = AU9520Reader::Current()->getCardPresent();
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			isPresent = AthenaCardReader::Current()->getCardPresent();
			break;	
	}
	return isPresent;
}

bool SmartCardReader::getConnected()
{
	bool isConnected = false;
	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			isConnected = true;
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			isConnected = AthenaCardReader::Current()->getConnected();
			break;	
	}
	return isConnected;
}

bool SmartCardReader::Initialize()
{
	bool initialized = false;
	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			initialized = AU9520Reader::Current()->Initialize();
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			initialized = AthenaCardReader::Current()->Initialize();
			break;	
	}
	return initialized;
}

void SmartCardReader::Dispose()
{
	switch(Smartmatic::SAES::HW::Configuration::SAESHardwareConfigurationManager::Current()->getSmartCardReaderType ())
	{
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_AU9520:
			AU9520Reader::Current()->SwitchToAsyncAndReleaseInterface();
			break;
		case Smartmatic::SAES::HW::Configuration::CardReaderType::CONFIGURATION_ATHENA:
			AthenaCardReader::Current()->DisconnectAndReleaseContext();
			break;	
	}
}

void SmartCardReader::Test()
{
		
}
