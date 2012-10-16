/**
 * @file	serial-port-connection.h
 *
 * @brief	Declares the serial port connection class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * commandstructure
 * Copyright (C)  2010 <>
 * 
 * commandstructure is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * commandstructure is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef _SERIAL_PORT_CONNECTION_H_
#define _SERIAL_PORT_CONNECTION_H_

#include "i-connection.h"
#include <string.h>  /* String function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/time.h> /* POSIX SELECT function definitions */
#include <sys/types.h>/* POSIX SELECT function definitions */
#include <sys/select.h> /* POSIX SELECT function definitions */
#include <glibmm/thread.h>
#include <glibmm/timer.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace HW
		{
			namespace Connections
			{
				namespace Parity
				{
					enum ParityEnum
					{
						PARITY_8N1,	
						PARITY_7E1
					};
				}

				/**
				 * @brief	Interface to define the method launched on a received affirmative peeking on input data. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				class IPeekListener
				{
					public:

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 */

						virtual ~IPeekListener() {}

						/**
						 * @brief	Peek event.
						 *
						 * @author	Fsilva
						 * @date	27/04/2011
						 *
						 * @param	data	The data.
						 */

						virtual void  peekEvent(std::vector<unsigned char> & data) = 0;
				};

				/**
				 * @brief	Manage the connection to a serial port resources.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class SerialPortConnection: public IConnection, public IPeekListener
				{

				private:

					sigc::connection connPeek;  ///< The connection peek

					//bool keepPeeking;
					int baud;   ///< The baud rate for the port
					int fd; ///< The fd
					int dataBits;   ///< The data bits
					Parity::ParityEnum parity;  ///< The parity of the connection
					std::string dev;	///< The development
					bool keepPeeking;   ///< true to keep peeking
					bool enableCTSRTS;  ///< true to enable, false to disable the ctsrts
					std::vector<unsigned char> readBuffer;  ///< Buffer for read data
					fd_set readfs;    ///< File descriptor set

					Glib::Mutex mutexNewThread;
					Glib::Mutex mutexFileDescriptor;
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					SerialPortConnection(bool connectSignal = true);
					~SerialPortConnection();
					/**
					 * @brief	Constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	baudI	 	The baud i.
					 * @param	parityI  	The parity i.
					 * @param	dataBitsI	The data bits i.
					 * @param	devI	 	The development i.
					 * @param	enableCTS	true to enable, false to disable the cts.
					 */

					SerialPortConnection(int baudI,Parity::ParityEnum parityI,int dataBitsI,std::string devI, bool enableCTS, bool connectSignal = true);
					//std::vector<unsigned char> response;

					/**
					 * @brief	Peek event.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void  peekEvent(std::vector<unsigned char> & data);

					/**
					 * @brief	Flushs the read buffer.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void FlushReadBuffer();

					/**
					 * @brief	Send the data given.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 *
					 * @return	.
					 */

					int Send(std::vector<unsigned char> data);

					/**
					 * @brief	Initializes the serial port.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	.
					 */

					bool Initialize();

					/**
					 * @brief	Opens the serial port.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Open();

					/**
					 * @brief	Starts a peeking data.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	.
					 */

					int StartPeeking();

					/**
					 * @brief	Waits for input.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	.
					 */

					void waitForInput();

					sigc::signal<void,std::vector<unsigned char> & > signal_detected; ///< The signal detected

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Read the data in the serial port.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	.
					 */

					std::vector<unsigned char> Read();

					/**
					 * @brief	Close the port
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	.
					 */

					int Close();

					 bool presentDevice();

				protected:

					 bool connectSignal;
					 static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif // _SERIAL_PORT_CONNECTION_H_
