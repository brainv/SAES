/*
 * BarcodeCommandWrapper.h
 *
 *  Created on: Aug 3, 2011
 *      Author: Juan.Delgado
 */

#ifndef BARCODECOMMANDWRAPPER_H_
#define BARCODECOMMANDWRAPPER_H_

#include "Connections/serial-port-connection.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				class BarcodeCommandWrapper
				{
				public:
					static BarcodeCommandWrapper* Current();


					enum BarcodeCommandWrapper_ReadMode
					{
						BARCODE_TRIGGER,
						BARCODE_AUTO_SCAN,
						BARCODE_CONTINUE_SCAN,
						BARCODE_ONCE_CONTINUE_AUTO_SCAN
					};

					/**
					 * @brief	Sets the Serial Port Connection
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	connectionSerial The serial connection
					 */
					void SetSerialPortConnection(Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial);

					/**
					 * @brief	Set voice of decode.
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	true if turn sound on
					 *
					 * @return	false if error happen
					 */

					bool SetVoiceOfDecode(bool turnOn = true);

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
					bool SetReadMode(BarcodeCommandWrapper_ReadMode mode);

					/**
					 * @brief	Set delay of reading.
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	msTime Time of delay in miliseconds
					 * @param	duplicateReading true if delay is for duplicate reading
					 *
					 * @return	false if error happen
					 */
					bool SetDelayOfReading(std::vector<unsigned char> time_ms, bool duplicateReading = false);

					/**
					 * @brief	Set read mode.
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	incomplete true if sets imcomplete delay mode, otherwise sets complete delay mode
					 *
					 * @return	false if error happen
					 */
					bool SetIncompletelyDelay(bool incomplete = true);

					/**
					 * @brief	Send configuration command
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @return	false if error happen
					 */
					bool SendConfigurationCommand(std::string command);

					/**
					 * @brief	Ask device model
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @return	false if error happen
					 */
					bool AskDeviceModel();

					/**
					 * @brief	get device model from data
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	data to transform
					 *
					 * @return	device model, empty if fail
					 */
					Glib::ustring GetDeviceModel(std::vector<unsigned char> & data);

				private:
					/**
					 * @brief	Format Barcode Query Command
					 *
					 * @author	Juan.Delgado
					 * @date	03/08/2011
					 *
					 * @param	data	The data.
					 */
					void FormatBarcodeQueryCommand(std::vector<unsigned char> &data);

					static BarcodeCommandWrapper* current_instance;

					Smartmatic::SAES::HW::Connections::SerialPortConnection* connectionSerial;

					BarcodeCommandWrapper();
				};
			}
		}
	}
}

#endif /* BARCODECOMMANDWRAPPER_H_ */
