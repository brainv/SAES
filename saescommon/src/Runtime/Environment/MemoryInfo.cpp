/*
 * MemoryInfo.cpp
 *
 *  Created on: May 18, 2011
 *      Author: feddy
 */

#include "MemoryInfo.h"
#include <System/Utils/StringUtils.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>

using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Utils;

enum ElementLineDevice
{
     SERIAL
    ,DEVICE
    ,PATH
    ,STATUS
};

MemoryInfo::MemoryInfo()
{
	this->mount = false;
	this->remove = false;
	this->add = false;
}

MemoryInfo::MemoryInfo(std::string info)
{
	this->mount = false;
	this->remove = false;
	this->add = false;

	OSConfigurationFiles & osConf (SAESCommonConfigurationManager::Current()->getOSConfigurationFiles());
    std::list<std::string>::iterator it;
    int count = 0;
    std::list<std::string> list = StringUtils::split(info, osConf.getLineDeviceSeparator());

    if (list.size() > 2)
    {
        for (it = list.begin();
             it != list.end();
             it++, count++)
        {
            switch((ElementLineDevice)count)
            {
                case SERIAL:
                    serial = (*it);
                    break;

                case DEVICE:
                    device = (*it);
                    break;

                case PATH:
                    path = (*it);
                    break;

                case STATUS:
                    remove = (*it) == "remove";
                    add = (*it) == "add";
                    break;
            }
        }
    }
    else if (list.size() > 0)
    {
        for (it = list.begin();
             it != list.end();
             it++, count++)
        {
        	switch((ElementLineDevice)count)
            {
                case DEVICE - 1:
                    device = (*it);
                    break;

                case PATH - 1:
                    path = (*it);
					mount = true;
					break;

                default:
                    break;
            }
        }
    }
}

MemoryInfo::~MemoryInfo()
{

}

std::string MemoryInfo::getDevice()
{
	return device;
}

std::string MemoryInfo::getPath()
{
	return path;
}

std::string MemoryInfo::getSerial()
{
	return serial;
}

bool MemoryInfo::isMount()
{
    return mount;
}

bool MemoryInfo::isRemove()
{
	return remove;
}

bool MemoryInfo::isAdd()
{
	return add;
}

void MemoryInfo::setDevice(std::string devName)
{
	device = devName;
}

void MemoryInfo::setPath(std::string mountPath)
{
	path = mountPath;
}

void MemoryInfo::setSerial(std::string serialNumber)
{
	serial = serialNumber;
}

void MemoryInfo::setMount(bool mount)
{
    this->mount = mount;
}
