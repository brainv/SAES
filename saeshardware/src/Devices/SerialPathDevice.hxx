/*
 * SerialPathDevice.hxx
 *
 *  Created on: 17/08/2011
 *      Author: soto
 */

#ifndef SERIALPATHDEVICE_HXX_
#define SERIALPATHDEVICE_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				class SerialPathDevice
				{
				public:

					enum SerialDeviceType
					{
						 ABLE_DEVICE
						,SAB_DEVICE
						,NONE
					};

					SerialPathDevice(std::string line, std::string separator);
					~SerialPathDevice();

					std::string getName();
					std::string getPath();
					SerialDeviceType getType();

				private:

					std::string name;
					std::string path;
					SerialDeviceType type;
				};
			}
		}
	}
}

#endif /* SERIALPATHDEVICE_HXX_ */
