/*
 * SerialPathManager.cxx
 *
 *  Created on: 17/08/2011
 *      Author: soto
 */

#include "SerialPathManager.hxx"
#include "SerialPathDevice.hxx"
#include <System/IO/File.h>
#include <fstream>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Utils;

SerialPathManager * SerialPathManager::instance = NULL;

SerialPathManager::SerialPathManager()
{
	updatePath();
}

SerialPathManager::~SerialPathManager()
{

}

void SerialPathManager::updatePath()
{
    OSConfigurationFiles & osConf (SAESCommonConfigurationManager::Current()->getOSConfigurationFiles());
    std::string filePath = osConf.getSerialLocationFileFullPath();
    std::string separator = osConf.getLineSerialLocationSeparator();

    p168ADevice = "";
    alarmDevice = "";

    if (File::canOpenFile(filePath))
    {
        std::string line;
        std::ifstream ifs(filePath.c_str());

        if(ifs.is_open())
        {
            while (ifs.good())
            {
            	getline(ifs, line);
            	SerialPathDevice device(line, separator);

            	switch (device.getType())
            	{
					case SerialPathDevice::ABLE_DEVICE:
						this->p168ADevice = device.getPath();
						break;
					case SerialPathDevice::SAB_DEVICE:
						this->alarmDevice = device.getPath();
						break;
					case SerialPathDevice::NONE:
						break;
            	}
            }

            ifs.close();
        }
    }
}

std::string SerialPathManager::getAlarmDevice()
{
	return alarmDevice;
}

std::string SerialPathManager::getP168ADevice()
{
	return p168ADevice;
}

SerialPathManager * SerialPathManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new SerialPathManager();
	}

	return instance;
}
