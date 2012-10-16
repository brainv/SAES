/**
 * @file	barcode-device.h
 * @brief	Header the barcode device class.
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

#ifndef _BARCODE_DEVICE_H_
#define _BARCODE_DEVICE_H_

#include "Commands/barcode-enter-serial-program-command.h"
#include "Connections/serial-port-connection.h"
#include <glibmm/thread.h>
#include <glibmm/timer.h>
#include <System/SafeBuffer.h>
#include "Log/ISMTTLog.h"
#include "Commands/BarcodeCommandWrapper.h"
#include "Configuration/s-a-e-s-hardware-conf-manager.h"
#include <glibmm/dispatcher.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				/**
				 * @brief	Manage the connections with the barcode. 
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class BarcodeDevice
				{
				public:

					typedef sigc::signal<void,bool> signal_commands_sent;	///< The signal commands sent
					typedef sigc::signal<void> connection_signal;	///< The signal connection
					typedef sigc::signal<void,Smartmatic::System::SafeBuffer *> signal_detected_data;  ///< The signal detected

					/**
					 * @brief	Handles signal connected
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 *
					 * @return	signal
					 */
					connection_signal signalConnected();

					/**
					 * @brief	Handles signal disconnected
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 *
					 * @return	signal
					 */
					connection_signal signalDisconnected();

					/**
					 * @brief	Handles signal detected
					 *
					 * @author	Yadickson Soto
					 * @date	09/02/2012
					 *
					 * @return	signal
					 */
					signal_detected_data signalDetected();
					/**
					 * @brief method getter signal start send command
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalStartSendCommand();
					/**
					 * @brief method getter signal start send command
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalEndSendCommand();

				private:

					/**
					 * @brief	Emit commands sent signal
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 *
					 * @param	true if commands sent were ok
					 */
					void EmitSignal(bool signal);

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					BarcodeDevice();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					~BarcodeDevice();

					/**
					 * @brief	Receive and processed the data.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void RecievedData(std::vector<unsigned char> & data);

					/**
					 * @brief	Send command pointed by commandsIterator
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 */
					void SendCommand();

					/**
					 * @brief	Send next command pointed by commandsIterator
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 */
					void SendNextCommand();

					/**
					 * @brief	Handles command timeout signal
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 */
					bool CommandTimeout(int timer);

					/**
					 * @brief	Retry command pointed by commandsIterator
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 */
					void RetryCommand();

					/**
					 * @brief	Get if device is present
					 *
					 * @author	Juan.Delgado
					 * @date	24/08/2011
					 *
					 * @return	true if device is present
					 */
					bool presentDevice();

					/**
					 * @brief	Handles connection and disconnection of barcode
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					static void signalHandler(int sig);

					/**
					 * @brief	Send configuration commands thread
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					void SendConfigurationCommandsThread();

					/**
					 * @brief	Emits connected signal
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					static void EmitSignalConnected();

					long countReceivedData; ///< count received data for debug
					Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial;  ///< The serial connection
					static BarcodeDevice *current_instance; ///< The current instance of the barcode device.
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
					static bool stopSendingCommands; ///< True if stop sending commands
					static bool gettingDeviceModel; ///< True if getting device model
					std::string deviceName; ///< The device name

					unsigned int commandRetries; ///< Number of commands retries
					unsigned int totalCommands; ///< Number of total commands to sent
					bool sendingConfigurationCommands; ///< True if sending configuration commands
					bool ping;  ///< Ping the device to test connectivity
					bool closeConnection; ///< True if close connection at end of commans send
					bool sendSignal;

					Glib::Mutex openConnectionMutex;	///< the mutex
					Glib::Mutex mutex;	///< the mutex
					sigc::connection commandTimeout;
					signal_commands_sent m_signal_commands_sent; ///< The signal commands sent
					connection_signal m_signalDisconnected;	///< The signal connected
					connection_signal m_signalConnected;	///< The signal disconnected
					signal_detected_data signal_detected;
					sigc::signal<void> signalStartSendCommand; ///< signal command sent
					sigc::signal<void> signalEndSendCommand; ///< signal command sent

					Smartmatic::SAES::HW::Configuration::BarcodeCommands::CommandSequence commandsSeq;
					Smartmatic::SAES::HW::Configuration::BarcodeCommands::CommandIterator commandsIter;

				public:

					/**
					 * @brief	Get device model on thread
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					void GetDeviceModelOnThread();

					/**
					 * @brief	Get device model
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					static void GetDeviceModel();

					/**
					 * @brief	handles signal commands sent
					 *
					 * @author	Juan Delgado
					 * @date	03/08/2011
					 *
					 * @return	connection
					 */
					signal_commands_sent signalCommandsSent();


					/**
					 * @brief	Opens this object.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void Open();

					/**
					 * @brief	Closes this object.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					void Close();

					/**
					 * @brief	Resyncs this object.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Resync();

					/**
					 * @brief	Sends the ping.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool sendPing();

					/**
					 * @brief	Send configuration commands
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	command block name to send
					 * @param	emitsignal, true if emit signal after commands send
					 * @param	closeConnection, true if close connection when all commands sent
					 */
					void SendConfigurationCommands(std::string commandBlockName, bool emitSignal, bool closeConnection);

					/**
					 * @brief	Turn On Scan Sound
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	true if turn sound on
					 *
					 * @return	false if error happen
					 */
					bool TurnOnScanSound(bool turnOn = true);

					/**
					 * @brief	Set read mode.
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	mode The barcode read mode
					 *
					 * @return	false if error happen
					 */
					bool SetReadMode(Smartmatic::SAES::HW::Commands::BarcodeCommandWrapper::BarcodeCommandWrapper_ReadMode mode);

					/**
					 * @brief	Set delay of reading.
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	msTime Time of delay in miliseconds
					 *
					 * @return	false if error happen
					 */
					bool SetDelayOfReading(int time_ms);

					/**
					 * @brief	enable event
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 */
					void enabledEvent();

					/**
					 * @brief	Gets the current barcode device.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static BarcodeDevice *Current();

					//sigc::signal<void,Smartmatic::System::SafeBuffer *> signal_detected;  ///< The signal detected

				};
			}
		}
	}
};



#endif // _BARCODE_DEVICE_H_
