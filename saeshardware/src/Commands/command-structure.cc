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

#include <stdio.h>
#include "command-structure.h"

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

using namespace Smartmatic::SAES::HW::Commands;
using namespace Smartmatic::SAES::HW::Connections;
using namespace std;

std::vector<unsigned char> CommandStructure::analyzeResponse(IConnection* connectionProvider, vector<unsigned char> response)
{
	vector<unsigned char> tempBuffer;
	//retriesToRecive defines the number of retries to retrieve the answer before going back to the main loop of total retries
	for(int retries = 0; retries < retriesToRecive; retries++)
	{
		response.clear();
		for(int formingResponse = 0; formingResponse < 10; formingResponse++)
		{
			tempBuffer = connectionProvider->Read();

			if(!tempBuffer.empty())
			{
				response.insert(response.end(),tempBuffer.begin(),tempBuffer.end());
				tempBuffer.clear();
			}

			success = ProccessResponse(response);
			if(success)
				break;
			usleep(timeBetweenRetryuS);
		}
		
		if(success)
			break;
	}

	return response;
}

//This method finds out if the response is the correct one
bool CommandStructure::ProccessResponse(vector<unsigned char> response)
{
	return true;
}

int CommandStructure::runAsynchronousResponse(IConnection *connectionPtr)
{
	//retriesToSend defines the total number of retries
	for(int index = 0; index < retriesToSend; index++)
	{
		//if the data could not be sent then the loop continues to another retry
		if(!connectionPtr->Send(fullData))
			break;

		//if the command has a response then it has to be processed
		if(hasResponse)
		{
			response = analyzeResponse(connectionPtr ,response);
			if(success)
				break;
		}
		else
			success = true;
	}
	
	for (vector<IResponseListener*>::iterator itListener = responseListeners.begin();
	     itListener != responseListeners.end();itListener++)
	{
		IResponseListener* listener = *itListener;
		listener->responseEvent();
	}
	return 0;
}

void CommandStructure::responseEvent()
{

}

void CommandStructure::setCharsExpected(int expected)
{
	charsExpected = expected;
}

void CommandStructure::addRawData(unsigned char data)
{
	Data.push_back(data);
}

void CommandStructure::clearRawData()
{
	Data.clear();
}

CommandStructure::CommandStructure()
{
	retriesToSend = 3 ;
	retriesToRecive = 3;
	timeBetweenRetryuS = 50000;
	charsExpected = 0;
	hasResponse = false;
	hasEncryption = false;
	success = false;
}

bool CommandStructure::isSuccess()
{
	return success;
}

bool CommandStructure::HasResponse()
{
	return hasResponse;
}

vector<unsigned char> CommandStructure::getResponse()
{
	return response;
}

void CommandStructure::addListener(IResponseListener* responseListener)
{
	responseListeners.push_back(responseListener);
}

//clear all listeners
void CommandStructure::clearListeners()
{
	responseListeners.clear();
}

//erase the defined index
void CommandStructure::eraseListenerByIndex(int index)
{
	responseListeners.erase (responseListeners.begin()+index - 1);
}

//erase the first appearence of Listener
void CommandStructure::eraseSpecificListener(IResponseListener* responseListener) 
{
	vector<IResponseListener*>::iterator f = find(responseListeners.begin(), responseListeners.end(), responseListener);
	if( f != responseListeners.end() )
		responseListeners.erase(f);
}

//add a new section to the sorting list
void CommandStructure::addSection(sections::SectionsOfCommand section)
{
	OrderOfCommand.push_back(section);
}

//clear all sorting section list
void CommandStructure::clearSections()
{
	OrderOfCommand.clear();
}

//erase the defined index
void CommandStructure::eraseSectionByIndex(int index)
{
	OrderOfCommand.erase (OrderOfCommand.begin()+index - 1);
}

//erase the first appearence of the defined enum
void CommandStructure::eraseSpecificSection(sections::SectionsOfCommand section) 
{
	vector<sections::SectionsOfCommand>::iterator f = find(OrderOfCommand.begin(), OrderOfCommand.end(), section);
	if( f != OrderOfCommand.end() )
		OrderOfCommand.erase(f);
}

//send Data in an asynchronous way
bool CommandStructure::beginSendData(IConnection* connectionProvider)
{
//	pthread_t thread1;
//	int  iret1;
//	iret1 = pthread_create(&thread1, NULL, runThread, new thread_args(this,connectionProvider));
	///CAREFUL WITH THIS: IT IS ONLY HERE FOR TESTING PURPOSES
	//pthread_join(thread1, NULL);
	//--------------------------------------------------------
	return true;
}

//send Data in a synchronous way
vector<unsigned char> CommandStructure::sendData(IConnection* connectionProvider)
{
	success = false;
	if(hasResponse)
	  {
	    connectionProvider->FlushReadBuffer();
	  }
	//retriesToSend defines the total number of retries
	for(int index = 0; index < retriesToSend; index++)
	{
		//if the data could not be sent then the loop continues to another retry
		if(!connectionProvider->Send(fullData))
			break;

		//if the command has a response then it has to be processed
		if(hasResponse)
		{
			response = analyzeResponse(connectionProvider ,response);
		}
		else
		    success = true;

		if(success)
			break;
	}
	return response;
}


// the most important method of the class. It allows to determine each section and to sort the order of the command.
vector<unsigned char> CommandStructure::GetData(IProviderSender *send,IProviderMAC *mac, IProviderLenght *lenght,
                                                     IProviderNoise *noise, IProviderEncryption *encryption, IProviderCheckSum *checksum,
                                                IProviderTrailer *trailer)
{
	Initialize();
	getOrderOfCommand();
	vector<unsigned char> fullCommand;
	vector<unsigned char> encryptedData;
	if(send!=NULL)
	{
		Sender = send->getSender();
	}
	if(noise!=NULL)
	{
		Noise = noise-> getNoise();
	}
	if(trailer!=NULL)
	{
		Trailer = trailer->getTrailer();
	}
	if(hasEncryption)
	{
		vector<unsigned char> commandData;
		if(!CommandByte.empty())
			commandData.insert(commandData.end(), CommandByte.begin(), CommandByte.end());

		if(!MultiByteIdentifier.empty())
			commandData.insert(commandData.end(), MultiByteIdentifier.begin(), MultiByteIdentifier.end());

		if(!Data.empty())
			commandData.insert(commandData.end(), Data.begin(), Data.end());

		encryptedData = encryption->getEncryptedData(commandData, Noise);
		MAC = mac-> getEncryptedMAC(encryptedData);
		Lenght = lenght-> getLenght(commandData.size());

	}
	else
	{
		if(mac!=NULL)
		{
			MAC= mac-> getNormalMAC();
		}
		int totalSize = Data.size();
		if(lenght!= NULL)
		{
			Lenght = lenght-> getLenght(totalSize);
		}
		if(checksum != NULL)
		{
			CheckSum = checksum->getCheckSum(Data);
		}
	}
	
	//The sections are sorted by the list of enums of type SectionsOfCommand in this loop. It also
	// manages the case where a section is empty
    int size = OrderOfCommand.size();
	for(int index =0; index<size; index++)
	{
		switch(OrderOfCommand[index])
		{
			case sections::Sender:
				if(!Sender.empty())
					fullCommand.insert(fullCommand.end(), Sender.begin(), Sender.end());
				break;
			case sections::MAC:
				if(!MAC.empty())
					fullCommand.insert(fullCommand.end(), MAC.begin(), MAC.end());
				break;
			case sections::Lenght:
				if(!Lenght.empty())
					fullCommand.insert(fullCommand.end(), Lenght.begin(), Lenght.end());
				break;
			case sections::Noise:
				if(!Noise.empty())
					fullCommand.insert(fullCommand.end(), Noise.begin(), Noise.end());
				break;
			case sections::MultiByte:
				if(!MultiByteIdentifier.empty())
					fullCommand.insert(fullCommand.end(), MultiByteIdentifier.begin(), MultiByteIdentifier.end());
				break;
			case sections::CommandByte:
				if(!CommandByte.empty())
					fullCommand.insert(fullCommand.end(), CommandByte.begin(), CommandByte.end());
				break;
			case sections::Data:
				if(!Data.empty())
					fullCommand.insert(fullCommand.end(), Data.begin(), Data.end());
				break;
			case sections::Checksum:
				if(!CheckSum.empty())
					fullCommand.insert(fullCommand.end(), CheckSum.begin(), CheckSum.end());
				break;
			case sections::Trailer:
				if(!Trailer.empty())
					fullCommand.insert(fullCommand.end(), Trailer.begin(), Trailer.end());
				break;
			case sections::EncryptedData:
				if(!encryptedData.empty())
					fullCommand.insert(fullCommand.end(), encryptedData.begin(), encryptedData.end());
				break;
			default:
				break;
		  }
	}
	fullData = fullCommand;
	return fullCommand;
}
