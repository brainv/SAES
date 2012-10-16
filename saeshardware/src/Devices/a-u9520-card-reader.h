/**
 * @file	a-u9520-card-reader.h
 *
 * @brief	Declares a u 9520 card reader class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C)  2010 <>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _A_U9520_CARD_READER_H_
#define _A_U9520_CARD_READER_H_

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <PCSC/pcsclite.h>
#include <PCSC/winscard.h>
#include <PCSC/reader.h>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <errno.h>
#include <fstream>
#include <ios>

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
			namespace Devices
			{
				namespace reader
				{
					enum cardMode
					{
						I2C,
						Asynchronous
					};

					enum typeOfCard
					{
						Smart,
						Java,
						Memory,
						UnknownCardType
					};
				}

				/**
				 * @brief	Manage the reader that handles the AU9520 card.
				 *
				 * @author	Fsilva
				 * @date	28/04/2011
				 */

				class AU9520Reader
				{
	
				public:
	

				int pictureLenght;  ///< The picture lenght

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
				 * @brief	Gets the capacity.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	The capacity.
				 */

				int getCapacity();

				/**
				 * @brief	Reads the data on the given address.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address   	The address to read
				 * @param	count	  	Number of bytes.
				 * @param	typeOfCard	Type of the card.
				 *
				 * @return	.
				 */

				bool Read(int address, int count, std::vector<unsigned char> & buffer, reader::typeOfCard typeOfCard);

				/**
				 * @brief	Writes the buffer to the given address.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	address   	The address to write.
				 * @param	buffer	  	The buffer to write.
				 * @param	offset	  	The offset to write the data.
				 * @param	count	  	Number of bytes.
				 * @param	typeOfCard	Type of the card.
				 */

				bool Write(int address, std::vector<unsigned char> & buffer, int offset, int count,reader::typeOfCard typeOfCard);

				/**
				 * @brief	Gets the card readers present.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getCardReadersPresent();

				/**
				 * @brief	Gets the card present.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getCardPresent();

				/**
				 * @brief	Sets a card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	cardPresent	true to card present.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool setCardPresent(bool cardPresent);

				/**
				 * @brief	Gets the trials on the card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	The trials.
				 */

				int getTrials();

				/**
				 * @brief	Switch to asynchronous and release interface.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				void SwitchToAsyncAndReleaseInterface();
				//SmartcardConnStatusEnum CardStatus();

				/**
				 * @brief	Sets the type of mode.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool setTypeOfMode();

				/**
				 * @brief	Gets the connected card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getConnected();

				/**
				 * @brief	Query the size of the data.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	The size of the data.
				 */

				int findOutSize();

				/**
				 * @brief	Gets the type of card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	The type of card.
				 */

				reader::typeOfCard getTypeOfCard();

				/**
				 * @brief	Switch to mode.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	mode	The mode to change.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool switchToMode(reader::cardMode mode);

				/**
				 * @brief	Turn on the I2C.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool powerOnI2C();

				/**
				 * @brief	Turn the power ON in the SmartCard.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool powerOnNormal();

				/**
				 * @brief	Creates the master file.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool createMasterFile();

				/**
				 * @brief	Creates a transparent file.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	ID  	The identifier.
				 * @param	size	The size.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool createTransparentFile(int ID, int size);

				/**
				 * @brief	Select file by the given ID.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	ID	The identifier.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool selectFile(int ID);

				/**
				 * @brief	Deletes the last file described by ID.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	ID	The identifier.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool deleteLastFile(int ID);

				/**
				 * @brief	Gets the response.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getResponse();

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
				 * @brief	Gets the selected applet.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool selectApplet();

				/**
				 * @brief	Introduce the pin of the card.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool introducePIN();

				/**
				 * @brief	Sends the picture lenght.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	lenght	The lenght.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool sendPictureLenght(int lenght);

				/**
				 * @brief	Sends the picture.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	fileOpened	The file opened.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool sendPicture(std::string fileOpened);

				/**
				 * @brief	Gets the picture.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getPicture();

				/**
				 * @brief	Gets the current reader.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	null if it fails, else.
				 */

				static AU9520Reader *Current();
				protected:
	



				private:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				AU9520Reader();
						
				SCARDCONTEXT hContext;	
				SCARDHANDLE hCard;
				long rv;
				LPSTR mszReaders;
				LPSTR mszGroups;
				DWORD dwGroups;
				DWORD dwPref;
				DWORD dwReaders;

				bool cardIsPresent; ///< true if card is present

				/**
				 * @brief	Sends a APDU.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	APDU	The apdu.
				 *
				 * @return	.
				 */

				std::vector<unsigned char> sendAPDU(std::vector<unsigned char> APDU);

				/**
				 * @brief	Sends a command from the pc to the reader.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	command	The command.
				 *
				 * @return	.
				 */

				std::vector<unsigned char> sendPCToReader(std::vector<unsigned char> command);

				/**
				 * @brief	Gets the picture lenght.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool getPictureLenght();

				/**
				 * @brief	Sends a picture to the APDU.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	data  	The picture.
				 * @param	offset	The offset to begin to write.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool sendPictureAPDU(std::vector<unsigned char> data, int offset);

				/**
				 * @brief	Gets a picture from the APDU, from the given offset.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	offset	The offset.
				 *
				 * @return	The picture a pdu.
				 */

				std::vector<unsigned char> getPictureAPDU(int offset);

				/**
				 * @brief	Sets a size.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	size	The size.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool setSize(int size);

				/**
				 * @brief	Sets an I2C address.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	addressHigh	The address high.
				 * @param	addressLow 	The address low.
				 * @param	pageSize   	Size of the page.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool setI2CAddress(unsigned char addressHigh,unsigned char addressLow,int pageSize);

				/**
				 * @brief	Writes an I2C command.
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

				bool writeCommandI2C(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow);

				/**
				 * @brief	Reads an I2C command.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	addressHigh 	The address high.
				 * @param	addressLow  	The address low.
				 * @param	lenghtToRead	The lenght to read.
				 *
				 * @return	The command i 2 c.
				 */

				std::vector<unsigned char> readCommandI2C(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead);

				/**
				 * @brief	Writes to file the given data at the specific addresses.
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

				bool writeToFile(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow);

				/**
				 * @brief	Reads from file the data at the specific addresses.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @param	addressHigh 	The address high.
				 * @param	addressLow  	The address low.
				 * @param	lenghtToRead	The lenght to read.
				 *
				 * @return	from file.
				 */

				std::vector<unsigned char> readFromFile(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead);

				/**
				 * @brief	Gets if it is interrupt.
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool askIfInterrupt();
				bool initialized;   ///< true to initialized

				/**
				 * @brief	Buffer[ 300]. 
				 *
				 * @author	Fsilva
				 * @date	27/04/2011
				 */

				struct libusb_device_handle *handle;

				int interface;  ///< The interface
				int bulk_out;   ///< The bulk out
				int bulk_in;	///< The bulk in
				int interrupt;  ///< The interrupt
				int actual_length;  ///< The actual length of the data read.
				int length; ///< The total length
				unsigned char buffer[300];  ///< The buffer to read the data
				static AU9520Reader *current_instance;  ///< The current instance of the reader.
				static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}



#endif // _A_U9520_CARD_READER_H_
