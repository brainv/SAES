/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*
 * main.cxx
 * Copyright (C) Daniel Ampuero 2012 <daniel.ampuero@smartmatic.com>
 * 
 * barcode-vote is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * barcode-vote is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#include <iostream>
#include <sstream>
#include <set>

#include <gtkmm.h>
#include <config.h>

#include <PCSC/winscard.h>

#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Runtime/Environment/MemoryPathController.h>
#include "Log/ISMTTLog.h"
#include <System/Runtime/ProcessLauncher.h>

#include "SCard.hxx"
#include "PSCIManager.hxx"
#include "Parameters.hxx"

#define LOG_CONF_FILENAME LOGDATADIR"/log4-configuration.xml"

using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::Runtime;

Smartmatic::Log::ISMTTLog* logger;

std::pair<int, std::string> statusCodes[12] = {
	std::make_pair(SCARD_STATE_UNAWARE, "SCARD_STATE_UNAWARE"),
	std::make_pair(SCARD_STATE_IGNORE, "SCARD_STATE_IGNORE"),
	std::make_pair(SCARD_STATE_CHANGED, "SCARD_STATE_CHANGED"),
	std::make_pair(SCARD_STATE_UNKNOWN, "SCARD_STATE_UNKNOWN"),
	std::make_pair(SCARD_STATE_UNAVAILABLE, "SCARD_STATE_UNAVAILABLE"),
	std::make_pair(SCARD_STATE_EMPTY, "SCARD_STATE_EMPTY"),
	std::make_pair(SCARD_STATE_PRESENT, "SCARD_STATE_PRESENT"),
	std::make_pair(SCARD_STATE_ATRMATCH, "SCARD_STATE_ATRMATCH"),
	std::make_pair(SCARD_STATE_EXCLUSIVE, "SCARD_STATE_EXCLUSIVE"),
	std::make_pair(SCARD_STATE_INUSE, "SCARD_STATE_INUSE"),
	std::make_pair(SCARD_STATE_MUTE, "SCARD_STATE_MUTE"),
	std::make_pair(SCARD_STATE_UNPOWERED, "SCARD_STATE_UNPOWERED")};

std::set<int> ignoredErrors = {
	SCARD_E_TIMEOUT};

std::string decodeStatus(DWORD status)
{
	std::string result = "";
	for(int i=0; i<12 /*this sucks*/; ++i)
	{
		if(status & statusCodes[i].first)
		{
			if(!result.empty())
				result += " | ";
			result += statusCodes[i].second;
		}
	}
	return result;
}


int giveReanimator()
{
	int delayAfterOn = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getDelayAfterOn();
	int delayAfterSuspend = SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getDelayAfterSuspend();

	std::stringstream ss;
  ss << SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getScriptRunSmartCard() << " " << delayAfterSuspend;

	std::string command = ss.str();
	logger->Debug("Run script " + command);

	int returnValue = ProcessLauncher::RunProcessThroughSystem(command.c_str());
	sleep(delayAfterOn);
	return returnValue;
}


LPSCARD_READERSTATE waitForState(SCard::SCardManager * manager, ParameterSet * waitParameters, LPSCARD_READERSTATE readerStates, int sleepTime, DWORD desiredState, DWORD currentState = SCARD_STATE_UNAWARE, DWORD timeout=INFINITE, bool offerReanimator = false )
{
	if(currentState != SCARD_STATE_UNAWARE)
		waitParameters->setParameter("currentState", currentState);
	if(timeout != INFINITE)
		waitParameters->setParameter("dwTimeout", timeout);
	bool flag = true;
	DWORD last = INFINITE;
	do
	{
		if(!flag)
			sleep(sleepTime);
		try
		{
			manager->wait(waitParameters);
		}
		catch(PSCIManager::PSCIException & e)
		{
			if(ignoredErrors.count(e.getErrorCode())==0)
			{
				//std::cerr << e.getErrorCodeAsString() << " " << e.getErrorMessage() << " reanimator: " << offerReanimator	 << std::endl;
				logger->Error("Error waiting for " + std::string(desiredState==SCARD_STATE_PRESENT?"insertion":"removal") + " event: " + e.what());
				if(offerReanimator)
				{
					char answer;
					std::cout << "Error on card reader, reanimate? (Y/N)" << std::endl;
					std::cin >> answer;
					if(toupper(answer) == 'Y')
					{
						giveReanimator();
						logger->Debug("Reanimation aplied on PSCD");
						/*try{
							manager->establishContext();
						} catch(PSCIManager::PSCIException & e) {
							logger->Error(std::string("Error establishing new context: ") + e.what());
						}*/
					}	else
						logger->Debug("Reanimation not aplied on PSCD");
				}
			}
		}
		readerStates = boost::any_cast<LPSCARD_READERSTATE>(waitParameters->getParameter("rgReaderStates").value);
		const DWORD eventState = readerStates->dwEventState;
		if(eventState != last)
		{
			logger->Debug("Event state associated: " + decodeStatus(readerStates->dwEventState));
			last = eventState;
		}
	}while(!(flag = readerStates->dwEventState & desiredState));
	return readerStates;
}


void writeSomeStuffs(SCard::SCardManager * manager, ParameterSet * connectionParameters)
{
	ParameterSet * lockParameters = manager->getLockParameters();
	lockParameters->setParameter("hCard", connectionParameters->getParameter("hCard").value);
	try
	{
		manager->lock(lockParameters);
	}
	catch(PSCIManager::PSCIException & e)
	{
		logger->Error(std::string("Error locking SC reader for exclusive writing: ") + e.what());
	}

	const BYTE sendBuffer[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
	DWORD sendBufferSize = 5;
	ParameterSet * writeParameters = manager->getWriteParameters();

	writeParameters->setParameter("hCard", lockParameters->getParameter("hCard").value);
	writeParameters->setParameter("pbSendBuffer", (LPCBYTE)sendBuffer);
	writeParameters->setParameter("pbSendLength", (DWORD)sendBufferSize);

	try{
		manager->write(writeParameters);
	}
	catch(PSCIManager::PSCIException & e)
	{
		logger->Error(std::string("Error writing: ") + e.what());
	}
	
	std::stringstream ss;
	for(DWORD i=0; i<boost::any_cast<DWORD>(writeParameters->getParameter("pcbRecvLenght").value); ++i)
		ss << std::hex << (int)(boost::any_cast<LPBYTE>(writeParameters->getParameter("pbRecvBuffer").value)[i]);
	logger->Debug(std::string("Returned data after writing: ") + ss.str() );

	ParameterSet * unlockParameters = manager->getUnlockParameters();
	unlockParameters->setParameter("hCard", lockParameters->getParameter("hCard").value);
	try
	{
		manager->unlock(unlockParameters);
	}
	catch(PSCIManager::PSCIException & e)
	{
		logger->Error(std::string("Error unlocking SC reader for exclusive writing: ") + e.what());	
	}
}

void disconnect(SCard::SCardManager * manager, ParameterSet * connectionParameters)
{
	ParameterSet * disconnectionParameters = manager->getDisconnectParameters();
	disconnectionParameters->setParameter("hCard", connectionParameters->getParameter("hCard").value);
	try
	{
		manager->disconnect(disconnectionParameters);
	}
	catch(PSCIManager::PSCIException & e)
	{
		//std::cerr << e.what() << std::endl;
		logger->Error(std::string("Error disconnecting: ") + e.what());
	}
	delete disconnectionParameters;
}

		/*ParameterSet * connectionParameters = manager->getConnectParameters();
		connectionParameters->setParameter("szReader", (LPCTSTR)readerStates->szReader);
		bool connected = true;
		try 
		{
			manager->connect(connectionParameters);
		} 
		catch(PSCIManager::PSCIException & e)
		{
			//std::cerr << e.getErrorCode() << std::endl;
			logger->Error(std::string("Error connecting: ") + e.what());
			connected = false;
		}

		if(connected)
		{
			writeSomeStuffs(manager, connectionParameters);
			disconnect(manager, connectionParameters);
		}
		delete connectionParameters;	*/

int main(int argc, char *argv[])
{

	logger = SMTTLogManager::GetLogger("SmartCard", "Stress Test");
	SMTTLogManager::Configure(LOG_CONF_FILENAME);
	PrinterBackendType & backend (SAESCommonConfigurationManager::Current()->getPrinterBackendType());
	backend = PrinterBackendType::CONFIGURATION_DIRECTPRINTING;

	SCard::SCardManager * manager = new PSCIManager();
	ParameterSet * waitParameters = manager->getWaitParameters();
	LPSCARD_READERSTATE readerStates = NULL;
	std::cout << "Remove any inserted card to start test" << std::endl;
	readerStates = waitForState(manager, waitParameters, readerStates, 1, SCARD_STATE_EMPTY);
	while(true)
	{
		std::cout << "Insert card " << std::endl;
		readerStates = waitForState(manager, waitParameters, readerStates, 0, SCARD_STATE_PRESENT, SCARD_STATE_EMPTY, 500, true);

		std::cout << "Remove card " << std::endl;
		readerStates = waitForState(manager, waitParameters, readerStates, 0, SCARD_STATE_EMPTY, SCARD_STATE_PRESENT, 500, true);
			
	}
	delete manager;
	delete waitParameters;	
	return 0;
}
