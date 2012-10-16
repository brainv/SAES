/**
 * @file	athena-card-reader.h
 *
 * @brief	Declares the athena card reader class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk-foobar
 * Copyright (C)  2011 <>
 * 
 * gtk-foobar is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-foobar is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//#include "config.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <PCSC/pcsclite.h>
#include <PCSC/winscard.h>
#include <PCSC/reader.h>
#include <iostream>
#include "Configuration/s-a-e-s-hardware-conf-manager.h"

#ifndef _ATHENA_CARD_READER_H_
#define _ATHENA_CARD_READER_H_


namespace Smartmatic
{
	namespace SAES
	{
		namespace HW
		{
			namespace Devices
			{
				/**
				 * @brief	Manage the reader that handles the Athena card.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AthenaCardReader
				{
	
				public:

				/**
				 * @brief	Tests this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void Test();

				/**
				 * @brief	Gets the password required.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getPasswordRequired();

				/**
				 * @brief	Reads the data in the card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address	The address to read.
				 * @param	count  	Number of bytes to read.
				 *
				 * @return	.
				 */

				std::vector<unsigned char> Read(int address, int count);

				/**
				 * @brief	Writes the given buffer.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address	The address to write.
				 * @param	buffer 	The buffer to write.
				 * @param	offset 	The offset in the buffe to write.
				 * @param	count  	Number of bytes to write.
				 */

				void Write(int address, std::vector<unsigned char> buffer, int offset, int count);

				/**
				 * @brief	Writes a command.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	rawData	   	Information describing the raw.
				 * @param	addressHigh	The address high.
				 * @param	addressLow 	The address low.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool writeCommand(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow);

				/**
				 * @brief	Reads a command.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	addressHigh 	The address high.
				 * @param	addressLow  	The address low.
				 * @param	lenghtToRead	The lenght to read.
				 *
				 * @return	The command.
				 */

				std::vector<unsigned char> readCommand(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead);

				/**
				 * @brief	Initializes this object.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool Initialize();

				/**
				 * @brief	Gets the card readers currently present.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getCardReadersPresent();

				/**
				 * @brief	Gets if the card is present.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getCardPresent();

				/**
				 * @brief	Disconnects and releases the context.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void DisconnectAndReleaseContext();

				/**
				 * @brief	Gets if a connection has been done.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getConnected();

				/**
				 * @brief	Sets the extended mode.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool setExtendedMode();

				/**
				 * @brief	Gets the current card reader.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static AthenaCardReader *Current();
						
				protected:
	



				private:
						
					SCARDCONTEXT hContext;  ///< The card context
					SCARDHANDLE hCard;  ///< The handle to the card
					long rv;	///< The rv
					LPSTR mszReaders;   ///< The messages readers.
					LPSTR mszGroups;	///< The messages groups
					DWORD dwGroups; ///< The groups where the card is.
					DWORD dwPref;   ///< The preferences
					DWORD dwReaders;	///< The readers

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Fsilva
					 * @date	27/04/2011
					 */

					AthenaCardReader();	

					static AthenaCardReader *current_instance;  ///< The current instance of the reader.
			
	
				};
			}
		}
	}
}

#endif // _ATHENA_CARD_READER_H_
