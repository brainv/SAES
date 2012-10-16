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

#include "a-u9520-card-reader.h"
#include "ifdhandler.h"
#include <iomanip>
#include <sstream>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

using std::ios;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::Log;

ISMTTLog* AU9520Reader::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.HW.Devices.AU9520Reader",GETTEXT_PACKAGE);

/*****************************************************************************
 *
 *					get_ccid_usb_interface
 *
 ****************************************************************************/
const struct libusb_interface * get_ccid_usb_interface(
	struct libusb_config_descriptor *desc, int *num)
{
	const struct libusb_interface *usb_interface = NULL;
	int i;
#ifdef O2MICRO_OZ776_PATCH
	int readerID;
#endif

	/* if multiple interfaces use the first one with CCID class type */
	for (i = *num; i < desc->bNumInterfaces; i++)
	{
		/* CCID Class? */
		if (desc->interface[i].altsetting->bInterfaceClass == 0xb
#ifdef ALLOW_PROPRIETARY_CLASS
			|| desc->interface[i].altsetting->bInterfaceClass == 0xff
#endif
			)
		{
			usb_interface = &desc->interface[i];
			/* store the interface number for further reference */
			*num = i;
			break;
		}
	}

#ifdef O2MICRO_OZ776_PATCH
	readerID = (dev->descriptor.idVendor << 16) + dev->descriptor.idProduct;
	if (usb_interface != NULL
		&& ((OZ776 == readerID) || (OZ776_7772 == readerID)
		|| (REINER_SCT == readerID) || (BLUDRIVEII_CCID == readerID))
		&& (0 == usb_interface->altsetting->extra_length)) /* this is the bug */
	{
		int j;
		for (j=0; j<usb_interface->altsetting->bNumEndpoints; j++)
		{
			/* find the extra[] array */
			if (54 == usb_interface->altsetting->endpoint[j].extra_length)
			{
				/* get the extra[] from the endpoint */
				usb_interface->altsetting->extra_length = 54;
				usb_interface->altsetting->extra =
					usb_interface->altsetting->endpoint[j].extra;
				/* avoid double free on close */
				usb_interface->altsetting->endpoint[j].extra = NULL;
				usb_interface->altsetting->endpoint[j].extra_length = 0;
				break;
			}
		}
	}
#endif

	return usb_interface;
} /* get_ccid_usb_interface */



AU9520Reader* AU9520Reader::current_instance = NULL;

AU9520Reader::AU9520Reader()
{
	handle = NULL;
	initialized = false;
	cardIsPresent = false;
}

AU9520Reader *AU9520Reader::Current()
{
	if (!current_instance)
	{
		current_instance = new AU9520Reader();
		
	}

	return current_instance;
}

std::vector<unsigned char> AU9520Reader::sendAPDU(std::vector<unsigned char> APDU)
{
		std::vector<unsigned char> sendAPDU;
	    sendAPDU.push_back(0x6F);
    	//data lenght
		sendAPDU.push_back(APDU.size() & 0x000000ff);
		sendAPDU.push_back((APDU.size()& 0x0000ff00) >> 8);
		sendAPDU.push_back(0x00);
		sendAPDU.push_back(0x00);
    	//slot
		sendAPDU.push_back(0x00);
    	//sequence
		sendAPDU.push_back(0x04);
    	//RFU
		sendAPDU.push_back(0x00);
		sendAPDU.push_back(0x00);
		sendAPDU.push_back(0x00);
		//ABDATA
		sendAPDU.insert(sendAPDU.end(),APDU.begin(),APDU.end());
		//// SEND APDU
        length = 10;
		actual_length = 0;
		rv = libusb_bulk_transfer(handle,
		bulk_out, &sendAPDU[0],sendAPDU.size(),
		&actual_length, 3000);
		//// ANSWER		
		length = 296;
		actual_length = 0;
		rv = libusb_bulk_transfer(handle,
		bulk_in, buffer, length,
		&actual_length,3000);

		std::vector<unsigned char> result;
		for(int i=10;i<actual_length;i++)
		{
			result.push_back(buffer[i]);
		}
		if(result.size()==0)
		{
			//// ANSWER	SPECIAL CASE 	
			length = 100;
			actual_length = 0;
			rv = libusb_bulk_transfer(handle,
			bulk_in, buffer, length,
			&actual_length,100);

			for(int i=10;i<actual_length;i++)
			{
				result.push_back(buffer[i]);
			}
		}
		//usleep(50000);
		return result;
}

reader::typeOfCard AU9520Reader::getTypeOfCard()
{
		/*
		bool power = powerOnNormal();
		bool switchTo = switchToMode(reader::Asynchronous);		
	    power = power && powerOnNormal();
		if(switchTo && power)
		{
		}
		if(selectFile(16128))
		{
			return reader::Smart;
		}
		if(selectApplet ())
		{
			return reader::Java;
		}
		*/
		if(handle != 0 && initialized)
		{
			bool powerOn = powerOnI2C();
			bool switchTo = switchToMode(reader::I2C);
			powerOn = powerOnI2C();
			if(switchTo && powerOn)
			{
			}
				std::vector<unsigned char> result = readCommandI2C(0x00,0x09,0x02);
				if(result.size()>0)
				{
					return reader::Memory;
				}
		}
		
		return reader::UnknownCardType;
		
}

bool AU9520Reader::powerOnNormal()
{
		std::vector<unsigned char> powerOn;
	    powerOn.push_back(0x62);
    	//data lenght
		powerOn.push_back(0x00);
		powerOn.push_back(0x00);
		powerOn.push_back(0x00);
		powerOn.push_back(0x00);
    	//slot
		powerOn.push_back(0x00);
    	//sequence
		powerOn.push_back(0x01);
    	//RFU
		powerOn.push_back(0x00);
		powerOn.push_back(0x00);
		powerOn.push_back(0x00);
		//// POWER ON THE CARD	
        int  length = 10;
		int        actual_length = 0;
		(void)libusb_bulk_transfer(handle,
		bulk_out, &powerOn[0],powerOn.size(),
		&actual_length, 3000);
		////ANSWER		
		length = 100;
		actual_length = 0;
		(void)libusb_bulk_transfer(handle,
		bulk_in, buffer, length,
		&actual_length,3000);

		bool success = false;
		for(int i=0;i<actual_length;i++)
		{
			if(i==7 || i==8)
			{
				if(buffer[i]==0)
				{
					success = true;
				}
			}
		}
		//usleep(500000);	
		return success;
}


bool AU9520Reader::getPasswordRequired()
{
	return false;
}

int AU9520Reader::getCapacity()
{
	//setTypeOfMode();
	int size = findOutSize();
	return size;
}

bool AU9520Reader::getConnected()
{
	return Initialize();
}

bool AU9520Reader::Read(int address, int count, std::vector<unsigned char> & buffer, reader::typeOfCard card)
{
	bool validate = false;

	buffer.clear();

	if (initialized && cardIsPresent)
	{
	try
	{
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = address & 0x000000ff;    
		upperByte = (address & 0x0000ff00) >> 8;
		
		for(int j=0;j<count/64;j++)
		{
			std::vector<unsigned char> tempResult;
			if(card==reader::Memory)
			{
				tempResult= readCommandI2C(upperByte,lowerByte, 0x40);
			}
			else if(card==reader::Smart)
			{
				tempResult= readFromFile(upperByte,lowerByte, 0x40);
			}
			buffer.insert(buffer.end(),tempResult.begin(),tempResult.end());
			if(lowerByte<0xC0)
			{
				lowerByte+=0x40;
			}
			else
			{
				upperByte+=0x01;
				lowerByte=(0x40)-(0xFF-lowerByte);
				//lowerByte=0x00;
			}
		}
		int rest= count%64;
		unsigned char restByte;
		restByte = rest & 0x000000ff;    
		{
			std::vector<unsigned char> restResult;
			if(card==reader::Memory)
			{
				restResult= readCommandI2C(upperByte,lowerByte,restByte);
			}
			else if(card==reader::Smart)
			{
				restResult= readFromFile(upperByte,lowerByte,restByte);
			}
			buffer.insert(buffer.end(),restResult.begin(),restResult.end());

		}
		validate = true;
	}
	catch(std::exception & ex)
	{
		logger->Debug("FATAL - Error read AU9520");
	}
	}
	return validate;
}

bool AU9520Reader::Write(int address, std::vector<unsigned char> & buffer, int offset, int count,reader::typeOfCard card)
{
	bool validate = false;

	if (initialized && cardIsPresent)
	{
	try
	{
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = address & 0x000000ff;    
		upperByte = (address & 0x0000ff00) >> 8;
		std::vector<unsigned char>::iterator it;
		it=buffer.begin();

		for(unsigned int j=0;j<buffer.size()/64;j++)
		{
			std::vector<unsigned char> temp;
			temp.assign(it,it+64);
			if(card== reader::Memory)
			{
				writeCommandI2C(temp,upperByte,lowerByte);
			}
			else if(card== reader::Smart)
			{
				writeToFile(temp,upperByte,lowerByte);
			}
			it+=64;
			if(lowerByte<0xC0)
			{
				lowerByte+=0x40;
			}
			else
			{
				upperByte+=0x01;
				lowerByte=(0x40)-(0xFF-lowerByte);
		//			lowerByte=0x00;
			}

		}
		int rest= buffer.size()%64;
		if(rest!=0)
		{
			std::vector<unsigned char> restResult;
			restResult.assign(it,it+rest);
			if(card== reader::Memory)
			{
				writeCommandI2C(restResult,upperByte,lowerByte);
			}
			else if(card== reader::Smart)
			{
				writeToFile(restResult,upperByte,lowerByte);
			}
		}

		validate = true;
	}
	catch(std::exception & ex)
	{
		logger->Debug("FATAL - Error write AU9520");
	}
	}

	return validate;
}

bool AU9520Reader::setCardPresent(bool cardPresent)
{
	cardIsPresent = cardPresent;
	return cardPresent;
}

bool AU9520Reader::getCardReadersPresent()
{
	return Initialize();
}

bool AU9520Reader::askIfInterrupt()
{
	//// INTERRUPT
	length = 100;
	
	actual_length = 0;
	if(handle!=0 && initialized)
	{
		rv = libusb_bulk_transfer(handle,
		interrupt, buffer, length,
		&actual_length,100);

		std::vector<unsigned char> result;
		for(int i=0;i<actual_length;i++)
		{
			if(i==1)
			{
				if(buffer[i]== 12 || buffer[i]== 2)
				{
					cardIsPresent = false;
				}
				else if(buffer[i]== 13 || buffer[i]== 3)
				{
					cardIsPresent = true;
				}
			}
		}
		return true;
	}
	return false;
}

bool AU9520Reader::getCardPresent()
{
	if (initialized)
	{
		askIfInterrupt ();
	}
	else
	{
		cardIsPresent = false;
	}

	return cardIsPresent;
}

int AU9520Reader::getTrials()
{
	return 0;
}

bool AU9520Reader::Initialize()
{
	logger->Debug("Initialize AU9520");

	initialized = false;

	libusb_device **devs, *dev;
	int r, i;
	char class_ff = FALSE;
	ssize_t cnt;

	static bool firstInitialize = true;

	if(!firstInitialize && handle)
	{
		libusb_close(handle);
		libusb_exit(NULL);
		handle = NULL;
	}

	firstInitialize = false;

	r = libusb_init(NULL);

	if (r < 0)
	{
		logger->Debug("FATAL - libusb init failed for AU9520");
		return false;
	}

	cnt = libusb_get_device_list(NULL, &devs);

	if (cnt < 0)
	{
		logger->Debug("FATAL - libusb get device list failed for AU9520");
		libusb_exit(NULL);
		return false;
	}

	i = 0;
	while ((dev = devs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		struct libusb_config_descriptor *config_desc;
		const struct libusb_interface *usb_interface = NULL;
		int num = 0;

		r = libusb_open(dev, &handle);

		if (r < 0)
		{
			break;
		}

		r = libusb_get_device_descriptor(dev, &desc);

		if (r < 0)
		{
			break;
		}

		r = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, buffer, sizeof(buffer));
		r = libusb_get_string_descriptor_ascii(handle, desc.iProduct, buffer, sizeof(buffer));
		r = libusb_get_active_config_descriptor(dev, &config_desc);

		if (r < 0)
		{
			continue;
		}

		usb_interface = get_ccid_usb_interface(config_desc, &num);

		if (NULL == usb_interface)
		{
			libusb_close(handle);
			handle = NULL;
			continue;
		}
		if (!class_ff && (0xFF == usb_interface->altsetting->bInterfaceClass))
		{
			continue;
		}

		interface = usb_interface->altsetting->bInterfaceNumber;

		r = libusb_claim_interface(handle, interface);
		r = libusb_kernel_driver_active(handle, interface);

		if (r == 1)
		{
			r = libusb_detach_kernel_driver(handle, interface);
		}

		r = libusb_claim_interface(handle, interface);

		if (r < 0)
		{
			libusb_close(handle);
			handle = NULL;

			if (EBUSY == errno)
			{
				break;
			}
			continue;
		}

		bulk_out = 0;
		bulk_in = 0;
		interrupt = 0;

		for (i=0; i<usb_interface->altsetting->bNumEndpoints; i++)
		{
		/* interrupt end point (if available) */
			if (usb_interface->altsetting->endpoint[i].bmAttributes
				== LIBUSB_TRANSFER_TYPE_INTERRUPT)
			{
				interrupt =	usb_interface->altsetting->endpoint[i].bEndpointAddress;
			}

			if (usb_interface->altsetting->endpoint[i].bmAttributes
				!= LIBUSB_TRANSFER_TYPE_BULK)
				continue;

			int	bEndpointAddress = usb_interface->altsetting->endpoint[i].bEndpointAddress;
			if ((bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK)
				== LIBUSB_ENDPOINT_IN)
				bulk_in = bEndpointAddress;

			if ((bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK)
				== LIBUSB_ENDPOINT_OUT)
				bulk_out = bEndpointAddress;
		 }

		 initialized = true;
		 cardIsPresent = getCardPresent();

		 return true;
	}

	libusb_exit(NULL);
	logger->Debug("Fail initialize AU9520");

	return false;
}

std::vector<unsigned char> AU9520Reader::sendPCToReader(std::vector<unsigned char> command)
{
	std::vector<unsigned char> pcToReader;
	//PCrdrEscapeCommand
	pcToReader.push_back(0x6B);
    //data lenght
	pcToReader.push_back(command.size());
	pcToReader.push_back(0x00);
	pcToReader.push_back(0x00);
	pcToReader.push_back(0x00);
	//slot
	pcToReader.push_back(0x00);
    //sequence
	pcToReader.push_back(0xFF);
	//RFU
	pcToReader.push_back(0x00);
	pcToReader.push_back(0x00);
	pcToReader.push_back(0x00);
	//ABDATA
	pcToReader.insert(pcToReader.end(),command.begin(), command.end());
	//Send
	rv = libusb_bulk_transfer(handle,
		bulk_out, &pcToReader[0], pcToReader.size(),
		&actual_length, 3000);
	length = 100;
	//ANSWER
	actual_length = 0;
	rv = libusb_bulk_transfer(handle,
		bulk_in, buffer, length,
		&actual_length,3000);
	std::vector<unsigned char> result;
	for(int i=0;i<actual_length;i++)
	{
		result.push_back(buffer[i]);
	}
	//usleep(100000);
	return result;
	
}


bool AU9520Reader::switchToMode(reader::cardMode mode)
{
	std::vector<unsigned char> switchToI2C;
    //ABDATA
	switchToI2C.push_back(0x40);
	switchToI2C.push_back(0x50);
	//type of mode
	if(mode == reader::I2C)
	{
		switchToI2C.push_back(0x02);
	}
	else if(mode == reader::Asynchronous)
	{
		switchToI2C.push_back(0x01);
	}
	//5 zeros
	switchToI2C.push_back(0x00);
	switchToI2C.push_back(0x00);
	switchToI2C.push_back(0x00);
	switchToI2C.push_back(0x00);
	switchToI2C.push_back(0x00);
	//// LETS SWITCH 
	std::vector<unsigned char> result = sendPCToReader(switchToI2C);

	if(result.size() >= 10)
	{
		if(result[7] != 0 || result[8] != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool AU9520Reader::powerOnI2C()
{
	std::vector<unsigned char> powerOn;
	//ABDATA
	powerOn.push_back(0x40);
	powerOn.push_back(0x51);
	powerOn.push_back(0x00);
	//5 zeros
	powerOn.push_back(0x00);
	powerOn.push_back(0x00);
	powerOn.push_back(0x00);
	powerOn.push_back(0x00);
	powerOn.push_back(0x00);		
	////POWER ON THE CARD	
	std::vector<unsigned char> result = sendPCToReader(powerOn);	

	if(result.size() >= 10)
	{
		if(result[7] != 0 || result[8] != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool AU9520Reader::setI2CAddress(unsigned char addressHigh,unsigned char addressLow,int pageSize)
{
		std::vector<unsigned char> I2CAddW;
    	//ABDATA
		I2CAddW.push_back(0x40);
		I2CAddW.push_back(0x60);
		//Address of device
		I2CAddW.push_back(0x50 | addressHigh);
		I2CAddW.push_back(addressLow);
		//page size (8 for writin, 0 for reading)
		I2CAddW.push_back(pageSize);
		/////
		I2CAddW.push_back(0x00);
		I2CAddW.push_back(0x00);
		I2CAddW.push_back(0x00);
		//// LETS  I2C	ADD
		std::vector<unsigned char> result = sendPCToReader(I2CAddW);	
		//// ANSWER		

		if(result.size() >= 10)
		{
			if(result[7] != 0 || result[8] != 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return false;
}

bool AU9520Reader::writeCommandI2C(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow)
{
	bool validate;

	validate = setI2CAddress(addressHigh,addressLow,8);

	if (validate)
	{
		////WRITE COMMAND
        std::vector<unsigned char> writeCmd;
	    //ABDATA
		writeCmd.push_back(0x40);
		writeCmd.push_back(0x61);
		//
		writeCmd.push_back(rawData.size());
		writeCmd.push_back(0x00);
		//4 zeros
		writeCmd.push_back(0x00);
		writeCmd.push_back(0x00);
		writeCmd.push_back(0x00);
		writeCmd.push_back(0x00);
		//data
		writeCmd.insert(writeCmd.end(), rawData.begin(),rawData.end());
		//// LETS TRY TO WRITE
  		 std::vector<unsigned char> result = sendPCToReader(writeCmd);
		//// ANSWER
	}

	return validate;
}

std::vector<unsigned char> AU9520Reader::readCommandI2C(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead)
{
	std::vector<unsigned char> finalResult;

	if (setI2CAddress(addressHigh,addressLow,0))
	{
		std::vector<unsigned char> readCmd;
		//ABDATA
		readCmd.push_back(0x40);
		readCmd.push_back(0x62);
		//lenght low byte first and high byte second
		readCmd.push_back(lenghtToRead);
		readCmd.push_back(0x00);
		//Four zeros???
		readCmd.push_back(0x00);
		readCmd.push_back(0x00);
		readCmd.push_back(0x00);
		readCmd.push_back(0x00);	
		//// LETS TRY TO READ
		 std::vector<unsigned char> result = sendPCToReader(readCmd);
		////ANSWER

		for(unsigned int i=10;i<result.size();i++)
		{
			finalResult.push_back(buffer[i]);
		}
	}

	return finalResult;
}



void AU9520Reader::SwitchToAsyncAndReleaseInterface()
{
	logger->Debug("Dispose AU9520");

	if(handle != NULL && initialized)
	{
		initialized = false;

		powerOnNormal();
		switchToMode(reader::Asynchronous);
		powerOnNormal();

		libusb_detach_kernel_driver(handle, interface);
		libusb_release_interface(handle, interface);
		libusb_close(handle);
		libusb_exit(NULL);
		handle = NULL;
	}
}

bool AU9520Reader::setSize(int size)
{
	return false;
}

int AU9520Reader::findOutSize()
{
	int size = 0;
	return size;
}

/*
SmartcardConnStatusEnum AU9520Reader::CardStatus()
{
	return Removed;
}
*/

bool AU9520Reader::setTypeOfMode()
{
	return false;
}

bool  AU9520Reader::createMasterFile()
{
	std::vector<unsigned char> sendBuffer;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xE0);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x0A);
	sendBuffer.push_back(0x62);
	sendBuffer.push_back(0x08);
	sendBuffer.push_back(0x82);
	sendBuffer.push_back(0x02);
	sendBuffer.push_back(0x3F);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x83);
	sendBuffer.push_back(0x02);
	sendBuffer.push_back(0x3F);
	sendBuffer.push_back(0x00);
	std::vector<unsigned char> send = sendAPDU(sendBuffer);
	//// ANSWER	SPECIAL CASE 	
	length = 100;
	actual_length = 0;
	rv = libusb_bulk_transfer(handle,
	bulk_in, buffer, length,
	&actual_length,100);

	std::vector<unsigned char> result;
	for(int i=0;i<actual_length;i++)
	{
		if(i>=10)
		{
			result.push_back(buffer[i]);	
		}
	}	
	if(result.size()>1 && result[0]==144)
	{
		return true;
	}
	return false;
}

bool   AU9520Reader::createTransparentFile(int ID, int size)
{
	unsigned char lowerByte;
	unsigned char upperByte;
	lowerByte = ID & 0x000000ff;    
	upperByte = (ID & 0x0000ff00) >> 8;
	unsigned char lowerByteSize;
	unsigned char upperByteSize;
	lowerByteSize = size & 0x000000ff;    
	upperByteSize = (size & 0x0000ff00) >> 8;
	std::vector<unsigned char> sendBuffer;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xE0);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x1C);
	sendBuffer.push_back(0x62);
	sendBuffer.push_back(0x1A);
	sendBuffer.push_back(0x80);
	sendBuffer.push_back(0x02);
	sendBuffer.push_back(upperByteSize);
	sendBuffer.push_back(lowerByteSize);
	sendBuffer.push_back(0x82);
	sendBuffer.push_back(0x01);
	sendBuffer.push_back(0x01);
	sendBuffer.push_back(0x83);
	sendBuffer.push_back(0x02);
	sendBuffer.push_back(upperByte);
	sendBuffer.push_back(lowerByte);
	sendBuffer.push_back(0x88);
	sendBuffer.push_back(0x01);
	//SHORT FILE ID
	sendBuffer.push_back(0x00);
	//Default Life Cycle
	sendBuffer.push_back(0x8A);
	sendBuffer.push_back(0x01);
	sendBuffer.push_back(0x01);
	//Default security allow everything;
	//\x8C\x07\x00\x00\x00\x00\x00\x00\x00
	sendBuffer.push_back(0x8C);
	sendBuffer.push_back(0x07);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	std::vector<unsigned char> firstResult = sendAPDU (sendBuffer);
	std::vector<unsigned char> result;
	if(firstResult.size()==0)
	{
		//// ANSWER	SPECIAL CASE 	
		length = 100;
		actual_length = 0;
		rv = libusb_bulk_transfer(handle,
		bulk_in, buffer, length,
		&actual_length,100);

		for(int i=0;i<actual_length;i++)
		{
			if(i>=10)
			{
				result.push_back(buffer[i]);	
			}
		}
	}
	if(result.size()>1 && result[0]==144)
	{
		return true;
	}
	return false;
}

bool AU9520Reader::selectFile(int ID)
{
	 // Master File For example 00 A4 00 00 02 3F 00 
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = ID & 0x000000ff;    
		upperByte = (ID & 0x0000ff00) >> 8;
		std::vector<unsigned char> sendBuffer;
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0xA4);
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0x02);
		sendBuffer.push_back(upperByte);
		sendBuffer.push_back(lowerByte);
		std::vector<unsigned char> send = sendAPDU(sendBuffer);
		if(send.size()>1)
		{
			if(send[0]==97)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//// ANSWER	SPECIAL CASE 	
		length = 100;
		actual_length = 0;
		rv = libusb_bulk_transfer(handle,
		bulk_in, buffer, length,
		&actual_length,100);

		std::vector<unsigned char> result;
		for(int i=0;i<actual_length;i++)
		{
			if(i>=10)
			{
				result.push_back(buffer[i]);	
			}
		}	
		if(result.size()>1 && result[0]==97)
		{
			return true;
		}
		return false;
}



bool   AU9520Reader::deleteLastFile(int ID)
{
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = ID & 0x000000ff;    
		upperByte = (ID & 0x0000ff00) >> 8;
		std::vector<unsigned char> sendBuffer;
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0xE4);
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(0x00);
		sendBuffer.push_back(upperByte);
		sendBuffer.push_back(lowerByte);
		std::vector<unsigned char> send = sendAPDU(sendBuffer);
		if(send.size()>1 && send[0]==144)
		{
			return true;
		}
		return false;
}

bool  AU9520Reader::getResponse()
{
	std::vector<unsigned char> sendBuffer;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xC0);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0x31);
	std::vector<unsigned char> send = sendAPDU(sendBuffer);
	if(send.size()>1)
	{
		return true;
	}
	return false;
}

std::vector<unsigned char> AU9520Reader::readFromFile(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead)
{
	std::vector<unsigned char> sendBuffer;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xB0);
	sendBuffer.push_back(addressHigh);
	sendBuffer.push_back(addressLow);	
	sendBuffer.push_back(lenghtToRead);
	std::vector<unsigned char> send = sendAPDU(sendBuffer);
	if(send.size()>=2)
	{
		send.pop_back();
		send.pop_back();
	}
	return send;
}

bool AU9520Reader::writeToFile(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow)
{
	std::vector<unsigned char> sendBuffer;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xD6);
	sendBuffer.push_back(addressHigh);
	sendBuffer.push_back(addressLow);	
	sendBuffer.insert (sendBuffer.begin()+4,rawData.begin(),rawData.end());
	int writeLenght= rawData.size();
	sendBuffer.insert(sendBuffer.begin()+4, writeLenght);
	std::vector<unsigned char> send = sendAPDU(sendBuffer);
	return true;
}


bool AU9520Reader::selectApplet()
{
	std::vector<unsigned char> APDU;
	//0x00 0xA4 0x04 0x00 0x0b 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x00 0x00
	APDU.push_back(0x00);
	APDU.push_back(0xA4);
	APDU.push_back(0x04);
	APDU.push_back(0x00);
	APDU.push_back(0x0B);
	APDU.push_back(0x01);
	APDU.push_back(0x02);
	APDU.push_back(0x03);
	APDU.push_back(0x04);
	APDU.push_back(0x05);
	APDU.push_back(0x06);
	APDU.push_back(0x07);
	APDU.push_back(0x08);
	APDU.push_back(0x09);
	APDU.push_back(0x00);
	APDU.push_back(0x00);
	std::vector<unsigned char> result = sendAPDU(APDU);
	if(result.size()>1 && result[0] == 144)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AU9520Reader::introducePIN()
{
	std::vector<unsigned char> APDU;
	//0x80 0x40 0x00 0x00 0x04 0x01 0x02 0x03 0x04
	APDU.push_back(0x80);
	APDU.push_back(0x40);
	APDU.push_back(0x00);
	APDU.push_back(0x00);
	APDU.push_back(0x04);
	APDU.push_back(0x01);
	APDU.push_back(0x02);
	APDU.push_back(0x03);
	APDU.push_back(0x04);
	std::vector<unsigned char> result = sendAPDU(APDU);
	if(result.size()>1 && result[0] == 144)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AU9520Reader::sendPictureLenght(int lenght)
{
	//0x80 0x50 0x00 0x00 0x02 <SIZE>
	std::vector<unsigned char> APDU;
	APDU.push_back(0x80);
	APDU.push_back(0x50);
	APDU.push_back(0x00);
	APDU.push_back(0x00);
	APDU.push_back(0x02);
	APDU.push_back((lenght& 0x0000ff00) >> 8);
	APDU.push_back(lenght & 0x000000ff);
	std::vector<unsigned char> result = sendAPDU(APDU);
	if(result.size()>1 && result[0] == 144)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AU9520Reader::getPictureLenght()
{
	//0x80 0x60 0x00 0x00 0x00
	std::vector<unsigned char> APDU;
	APDU.push_back(0x80);
	APDU.push_back(0x60);
	APDU.push_back(0x00);
	APDU.push_back(0x00);
	APDU.push_back(0x00);
	std::vector<unsigned char> result = sendAPDU(APDU);
	if(result.size()>2)
	{
		pictureLenght = (result[0] << 8 )+ result[1];
		return true;
	}
	return false;
}

bool AU9520Reader::sendPictureAPDU(std::vector<unsigned char> data, int offset)
{
	//0x80 0x20 <offset> <lenght> <data>
	std::vector<unsigned char> APDU;
	APDU.push_back(0x80);
	APDU.push_back(0x20);
	APDU.push_back((offset & 0x0000ff00) >> 8);
	APDU.push_back(offset & 0x000000ff);
	APDU.push_back(data.size());
	APDU.insert(APDU.end(),data.begin(),data.end());
	std::vector<unsigned char> result= sendAPDU(APDU);	
	if(result.size()>1 && result[0] == 144)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AU9520Reader::sendPicture(std::string fileOpened)
{
	std::ifstream::pos_type size;
	char* memblock;
	std::vector<unsigned char> message;

	std::ifstream file (fileOpened.c_str(), ios::in|ios::binary|ios::ate);
	
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		for(int i = 0; i <= (int)size ; i++)
		{
			message.push_back(memblock[i]);			
		}
		delete[] memblock;
	}
	sendPictureLenght(message.size());
	int offset = 0;
	std::vector<unsigned char>::iterator it;
	it=message.begin();
	for(unsigned int j=0;j<message.size()/255;j++)
	{
		std::vector<unsigned char> temp;
		temp.assign(it,it+255);
		sendPictureAPDU (temp,offset);
		it+=255;
		offset +=255;
	}
	int rest= message.size()%255;
	if(rest!=0)
	{
		std::vector<unsigned char> restResult;
		restResult.assign(it,it+rest);
		sendPictureAPDU (restResult,offset);
	}
	return true;
}

bool AU9520Reader::getPicture()
{
	std::vector<unsigned char> finalResult;
	bool lenght = getPictureLenght();
	if(lenght)
	{
		int offset = 0;
		for(int j=0;j<pictureLenght/256;j++)
		{
			std::vector<unsigned char> tempResult;
			tempResult = getPictureAPDU (offset);
		
			finalResult.insert(finalResult.end(),tempResult.begin(),tempResult.end()-2);
			offset += 256;
		}
		int rest= pictureLenght%256;
		if(rest>0)   
		{
			std::vector<unsigned char> restResult;
			restResult= getPictureAPDU (offset);
			finalResult.insert(finalResult.end(),restResult.begin(),restResult.end()-2);
		}
		std::fstream binary_file("resultPicture.bmp",ios::out|ios::binary|ios::app);
		binary_file.write((char *)(&finalResult[0]),finalResult.size());
		binary_file.close();
		return true;
	}
	return false;
}

std::vector<unsigned char> AU9520Reader::getPictureAPDU(int offset)
{
	//0x80 0x30 <offset> 0x00
	std::vector<unsigned char> APDU;
	APDU.push_back(0x80);
	APDU.push_back(0x30);
	APDU.push_back((offset & 0x0000ff00) >> 8);
	APDU.push_back(offset & 0x000000ff);
	APDU.push_back(0x00);
	std::vector<unsigned char> result;
	result = sendAPDU(APDU);
	return result;
}


void AU9520Reader::Test()
{
		bool initialized = false;
		initialized = Initialize();
		if(initialized)
		{
			std::vector<unsigned char> rawDataToWrite;
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
						rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x37);

			
			
			bool powerOn = powerOnI2C();
			bool switchTo = switchToMode(reader::I2C);
			powerOn = powerOnI2C();
			if(switchTo && powerOn)
			{
			}

			writeCommandI2C(rawDataToWrite,0x00,0x09);
			readCommandI2C(0x00,0x09,0x40);
		}
}
	
