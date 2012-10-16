/*
 * SerialPathManager.hxx
 *
 *  Created on: 17/08/2011
 *      Author: soto
 */

#ifndef SERIALPATHMANAGER_HXX_
#define SERIALPATHMANAGER_HXX_

#include <iostream>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				class SerialPathManager
				{
				private:

					SerialPathManager();
					static SerialPathManager * instance;

					std::string alarmDevice;
					std::string p168ADevice;

				public:

					~SerialPathManager();

					void updatePath();
					std::string getAlarmDevice();
					std::string getP168ADevice();

					static SerialPathManager * getInstance();
				};
			}
		}
	}
}

#endif /* SERIALPATHMANAGER_HXX_ */
