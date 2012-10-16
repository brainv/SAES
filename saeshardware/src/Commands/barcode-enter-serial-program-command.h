/**
 * @file	barcode-enter-serial-program-command.h
 *
 * @brief	Declares the barcode enter serial program command class.
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

#ifndef _BARCODE_ENTER_SERIAL_PROGRAM_COMMAND_H_
#define _BARCODE_ENTER_SERIAL_PROGRAM_COMMAND_H_
#include "Commands/command-base-barcode.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Commands
			{
				/**
				 * @brief	Manages the commands that control the barcode enter serial program of the alarm.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class BarcodeEnterSerialProgramCommand: public CommandBaseBarcode
				{
	
				public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				BarcodeEnterSerialProgramCommand();

				/**
				 * @brief	Gets the specific response from raw.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void GetSpecificResponseFromRaw();
	
				protected:

				private:
				std::vector<unsigned char> result;  ///< The result of the command executed.

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Initialize();	

				/**
				 * @brief	Proccess response.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	response	The response.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool ProccessResponse(std::vector<unsigned char> response);
				};
			}
		}
	}
}



#endif // _BARCODE_ENTER_SERIAL_PROGRAM_COMMAND_H_
