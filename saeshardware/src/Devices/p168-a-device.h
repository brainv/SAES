/**
 * @file	p168-a-device.h
 *
 * @brief	Declares the 168 a device class.
 */

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

#ifndef _P168_A_DEVICE_H_
#define _P168_A_DEVICE_H_
#include "Connections/serial-port-connection.h"
#include <glibmm/thread.h>
#include <glibmm/timer.h>



namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				/**
				 * @brief	Manage the configuration of the P168A device.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class P168ADevice
				{
				protected:
				private:
						
					Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial;  ///< The serial connection
					static P168ADevice *current_instance;   ///< The current instance of the P168 device.

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					P168ADevice();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					~P168ADevice()
					{
						delete(connectionSerial);
					};
						
				public:

					/**
					 * @brief	Sets the brightness.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	bright	The bright.
					 */

					void setBrightness(unsigned char bright);

					/**
					 * @brief	Sends a ping.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool sendPing();

					/**
					 * @brief	Gets the current P168 device.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static P168ADevice *Current();
					

				};
			}
		}
	}
}

#endif // _P168_A_DEVICE_H_
