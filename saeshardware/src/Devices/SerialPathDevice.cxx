/*
 * SerialPathDevice.cxx
 *
 *  Created on: 17/08/2011
 *      Author: soto
 */


#include "SerialPathDevice.hxx"
#include <System/Utils/StringUtils.hxx>

using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::System::Utils;


SerialPathDevice::SerialPathDevice(std::string line, std::string separator)
{
	type = NONE;

	std::list<std::string> list = StringUtils::split(line, separator);

	if (list.size() == 2)
	{
		name = list.front();
		path = list.back();

		if (name == "ABLELocation")
		{
			type = ABLE_DEVICE;
		}
		else if (name == "SABLocation")
		{
			type = SAB_DEVICE;
		}
	}
}

SerialPathDevice::~SerialPathDevice()
{

}
std::string SerialPathDevice::getName()
{
	return name;
}

std::string SerialPathDevice::getPath()
{
	return path;
}

SerialPathDevice::SerialDeviceType SerialPathDevice::getType()
{
	return type;
}
