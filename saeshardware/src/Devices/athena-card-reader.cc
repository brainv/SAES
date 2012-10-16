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

#include "athena-card-reader.h"
#include <sstream>

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

using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Configuration;
using namespace std; 

bool AthenaCardReader::getPasswordRequired()
{
	return false;
}

AthenaCardReader::AthenaCardReader()
{
	mszReaders = NULL;
	Initialize();
	if((*SAESHardwareConfigurationManager::Current()->getConfiguration())->getSmartcardConfiguration().getExtended())
	{
		setExtendedMode();
	}
}

AthenaCardReader* AthenaCardReader::current_instance = NULL;

AthenaCardReader *AthenaCardReader::Current()
{
	if (!current_instance)
		current_instance = new AthenaCardReader();

	return current_instance;
}

bool AthenaCardReader::getConnected()
{
	rv = SCardConnect(hContext, mszReaders,
	SCARD_SHARE_SHARED, SCARD_PROTOCOL_RAW,
	&hCard, &dwPref);
	if (rv==SCARD_S_SUCCESS)
	{
		printf(_("Smartmatic.SAES.HW.Devices.IMT5123CardReader.Connected"));
		return true;
	}
	else
	{
		printf(_("Smartmatic.SAES.HW.Devices.IMT5123CardReader.NotConnected"));
		return false;
	}
}

std::vector<unsigned char> AthenaCardReader::Read(int address, int count)
{
    std::vector<unsigned char> finalResult;

	try
	{
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = address & 0x000000ff;    
		upperByte = (address & 0x0000ff00) >> 8;

		for(int j=0;j<count/64;j++)
		{
			std::vector<unsigned char> tempResult= readCommand(upperByte,lowerByte, 0x40);
			finalResult.insert(finalResult.end(),tempResult.begin(),tempResult.end());
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
			std::vector<unsigned char> restResult= readCommand(upperByte,lowerByte,restByte);
			finalResult.insert(finalResult.end(),restResult.begin(),restResult.end());

		}
	}
	catch(std::exception & ex)
	{
		printf(_("Smartmatic.SAES.HW.Devices.IMT5123CardReader.ExceptionEaten"));
	}

    return finalResult;
}

void AthenaCardReader::Write(int address, std::vector<unsigned char> buffer, int offset, int count)
{
	try
	{
		unsigned char lowerByte;
		unsigned char upperByte;
		lowerByte = address & 0x000000ff;    
		upperByte = (address & 0x0000ff00) >> 8;
		std::vector<unsigned char>::iterator it;
		it=buffer.begin();
        int size = buffer.size();
		for(int j=0;j<size/64;j++)
		{
			std::vector<unsigned char> temp;
			temp.assign(it,it+64);
			writeCommand(temp,upperByte,lowerByte);
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
			writeCommand(restResult,upperByte,lowerByte);
		}
	}
	catch(std::exception & ex)
	{
		printf(_("Smartmatic.SAES.HW.Devices.IMT5123CardReader.ExceptionEaten"));
	}
		
}

bool AthenaCardReader::getCardReadersPresent()
{
	return true;
}

bool AthenaCardReader::getCardPresent()
{
	SCARD_READERSTATE rgReaderStates[1];
	rgReaderStates[0].szReader = mszReaders;
	rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;
	rv = SCardGetStatusChange(hContext, 1000, rgReaderStates, 1);

	if(rgReaderStates[0].dwEventState & 0x10)
	{
		return false;
	}
	else if(rgReaderStates[0].dwEventState & 0x20)
	{
		return true;
	}
	return false;
}



bool AthenaCardReader::Initialize()
{
	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
	rv = SCardListReaders (hContext, NULL, NULL, &dwReaders);
	if(mszReaders == NULL)
	{
		mszReaders = (LPSTR)malloc ( dwReaders * sizeof (char) );
	}
	rv = SCardListReaders ( hContext, mszGroups, mszReaders, &dwReaders );
	if(rv==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AthenaCardReader::DisconnectAndReleaseContext()
{
    if (hCard)
	{
        rv = SCardDisconnect (hCard, SCARD_UNPOWER_CARD);
	}
    if (hContext)
	{
        rv = SCardReleaseContext (hContext);
	}
	if(mszReaders != NULL)
	{
		free(mszReaders);
		mszReaders = NULL;
	}
}


bool AthenaCardReader::setExtendedMode()
{
		std::vector<unsigned char> sendTramaToExtended;
		sendTramaToExtended.push_back(0xF0);
		sendTramaToExtended.push_back(0xA0);
		sendTramaToExtended.push_back(0x00);
		sendTramaToExtended.push_back(0x00);	
		DWORD controlLenght = 256;
		unsigned char controlBuffer[256];
		rv = SCardControl(hCard, 0x42000802, &sendTramaToExtended[0], sendTramaToExtended.size(),
		controlBuffer, sizeof(controlBuffer), &controlLenght);
		printf(_("Smartmatic.SAES.HW.Devices.IMT5123CardReader.ExtendedModeOn"));
		return true;
}

bool AthenaCardReader::writeCommand(std::vector<unsigned char> rawData, unsigned char addressHigh,unsigned char addressLow)
{
    DWORD lengthToWrite=256;
	unsigned char bRecvBuffer[256];
	std::vector<unsigned char> sendBufferWrite;
	sendBufferWrite.push_back(0x00);
	sendBufferWrite.push_back(0xD6);
	sendBufferWrite.push_back(addressHigh);
	sendBufferWrite.push_back(addressLow);	
	sendBufferWrite.insert (sendBufferWrite.begin()+4,rawData.begin(),rawData.end());

	int writeLenght= rawData.size();

	sendBufferWrite.insert(sendBufferWrite.begin()+4, writeLenght);

	rv = SCardTransmit(hCard, SCARD_PCI_RAW, &sendBufferWrite[0], sendBufferWrite.size(),
		(SCARD_IO_REQUEST*)SCARD_PCI_RAW, bRecvBuffer, &lengthToWrite);
	if(rv==SCARD_S_SUCCESS)
	{
		return true;
	}
	return false;
}

std::vector<unsigned char> AthenaCardReader::readCommand(unsigned char addressHigh,unsigned char addressLow,DWORD lenghtToRead)
{
	unsigned char bRecvBuffer[256];
	std::vector<unsigned char> sendBuffer;
	DWORD lenghtOfReceived= 256;
	sendBuffer.push_back(0x00);
	sendBuffer.push_back(0xB0);
	sendBuffer.push_back(addressHigh);
	sendBuffer.push_back(addressLow);	
	sendBuffer.push_back(lenghtToRead);
	rv = SCardTransmit(hCard, SCARD_PCI_RAW, &sendBuffer[0], sendBuffer.size(),
		(SCARD_IO_REQUEST*)SCARD_PCI_RAW, bRecvBuffer, &lenghtOfReceived);
	if(rv==SCARD_S_SUCCESS)
	{
	}
	std::vector<unsigned char> result;
	result.assign(bRecvBuffer,bRecvBuffer+(lenghtOfReceived-2));

	return result;
}



	
void AthenaCardReader::Test()
{
		bool initialized = false;
		initialized = Initialize();
		if(initialized)
		{
			DisconnectAndReleaseContext();
			Initialize();
			std::vector<unsigned char> rawDataToWrite;
			/*
			rawDataToWrite.push_back(0x49);
			rawDataToWrite.push_back(0x4a);
			rawDataToWrite.push_back(0x4b);
			rawDataToWrite.push_back(0x4c);
			rawDataToWrite.push_back(0x4d);
			rawDataToWrite.push_back(0x4e);
			rawDataToWrite.push_back(0x4f);
			rawDataToWrite.push_back(0x50);

			*/
			rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
						rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
						rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
						rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
						rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
									rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
									rawDataToWrite.push_back(0x31);
			rawDataToWrite.push_back(0x32);
			rawDataToWrite.push_back(0x33);
			rawDataToWrite.push_back(0x34);
			rawDataToWrite.push_back(0x35);
			rawDataToWrite.push_back(0x36);
			rawDataToWrite.push_back(0x37);
			rawDataToWrite.push_back(0x38);
				

			std::vector<unsigned char> sendTramaToExtended;
				sendTramaToExtended.push_back(0xF0);
				sendTramaToExtended.push_back(0xA0);
				sendTramaToExtended.push_back(0x00);
				sendTramaToExtended.push_back(0x00);	
				DWORD controlLenght = 256;
				unsigned char controlBuffer[256];
				rv = SCardControl(hCard, 0x42000802, &sendTramaToExtended[0], sendTramaToExtended.size(),
    			controlBuffer, sizeof(controlBuffer), &controlLenght);
				printf("extended mode on\n");


			writeCommand(rawDataToWrite,0x00,0x00);
			readCommand(0x00,0x00,0x50);
		}
}
