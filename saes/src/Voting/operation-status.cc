/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Voting/operation-status.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <System/guid-class.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include <Runtime/Environment/DirectoryManager.hxx>

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

using namespace std;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;

OperationStatus*  OperationStatus::singleton_instance = NULL;
ISMTTLog* OperationStatus::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.OperationStatus",GETTEXT_PACKAGE);

OperationStatus* OperationStatus::Current ()
{ 
	if ( ! singleton_instance )
		singleton_instance = new OperationStatus ();

	return singleton_instance;
}

OperationStatus::OperationStatus()
{
	persistanceOnStatusChange = false;
	electionStatus = NULL;
	cardListStatus = NULL;
	vmStatus = NULL;
}

void OperationStatus::init ()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);
	InitializeElectionStatus();
	InitializeVMStatus();
	InitializeCardDataListStatus();
}

bool OperationStatus::InitializeCardDataListStatus()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
    bool loadFile = false;

    Runtime::Environment::SaesDirectories directories;
	std::string file = directories.getCardListStatusFileFullPath();

	if (cardListStatus)
	{
		delete cardListStatus;
		cardListStatus = NULL;
	}

    if (!Smartmatic::System::IO::File::canOpenFile(file))
    {
        LoadDefaultCardListStatus();
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            cardListStatus = new CardGeneratedListWrapper(*(parseCardDataListGenerated(istr, CardDataGeneratedTypes::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
        	std::stringstream ss;
            ss << "FATAL - " << __func__ << e;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
        }
        catch(...)
        {
        	std::stringstream ss;
            ss << "FATAL - " << __func__;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
        }
    }
    return loadFile;
}

bool OperationStatus::InitializeElectionStatus()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
    bool loadFile = false;

    Runtime::Environment::SaesDirectories directories;
    std::string fileDom = directories.getElectionStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getElectionStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (electionStatus)
    {
    	delete electionStatus;
    	electionStatus = NULL;
    }

    if (!Smartmatic::System::IO::File::canOpenFile(fileDom) && !Smartmatic::System::IO::File::canOpenFile(fileFlash))
    {
        LoadDefaultElectionStatus();
    }
    else
    {
    	ElectionStatusWrapper * statusDOM = loadElectionStatusFile(fileDom);
    	ElectionStatusWrapper * statusFlash = loadElectionStatusFile(fileFlash);

    	if (statusDOM == NULL && statusFlash == NULL)
    	{
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    	}

    	if (statusDOM != NULL && statusFlash == NULL)
    	{
    		electionStatus = statusDOM;
    	}
    	else if (statusDOM == NULL && statusFlash != NULL)
    	{
    		electionStatus = statusFlash;
    	}
    	else if (statusDOM != NULL && statusFlash != NULL)
    	{
    		if (statusDOM->getSynchronizeVotes() == true)
    		{
    			logger->Debug("Synchronize votes in DOM");
    			electionStatus = statusDOM;
        		delete statusFlash;
    		}
    		else if (statusFlash->getSynchronizeVotes() == true)
    		{
    			logger->Debug("Synchronize votes in Flash");
    			electionStatus = statusFlash;
        		delete statusDOM;
    		}
    		else if (statusDOM->getEletionState() >= statusFlash->getEletionState())
    		{
    			electionStatus = statusDOM;
        		delete statusFlash;
    		}
    		else
    		{
    			electionStatus = statusFlash;
        		delete statusDOM;
    		}
    	}
    }

    return loadFile;
}

ElectionStatusWrapper * OperationStatus::loadElectionStatusFile(std::string file)
{
	ElectionStatusWrapper * status = NULL;

	if (File::canOpenFile(file))
	{
		try
		{
			std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
			std::istringstream istr (data);
			status = new ElectionStatusWrapper(*(parseElectionStatus(istr, ElectionStatusTypes::Flags::dont_validate)));

			if (status->getElectionStatus().getSynchronizeVotes() == NULL)
			{
				status->getElectionStatus().setSynchronizeVotes(false);
			}
		}
		catch (const ::xsd::cxx::tree::exception< char >& e)
		{
			std::stringstream ss;
			ss << "FATAL - " << __func__ << e;
			logger->Debug(ss.str());
		}
		catch(...)
		{
			std::stringstream ss;
			ss << "FATAL - " << __func__;
			logger->Debug(ss.str());
		}
	}

    return status;
}


bool OperationStatus::InitializeVMStatus()
    throw (Smartmatic::System::Exception::CryptoException,
            Smartmatic::System::Exception::SignedException,
            Smartmatic::System::Exception::XmlException)
{
    bool loadFile = false;

    Runtime::Environment::SaesDirectories directories;
    std::string file = directories.getVotingMachineStatusFileFullPath();
	
    if (!Smartmatic::System::IO::File::canOpenFile(file))
    {
        //LoadDefaultVMStatus();
    }
    else
    {
        ::xsd::cxx::tree::sequence< DeviceStatus > sequence = vmStatus->getDevicesStatus ().getDeviceStatus ();
        if(vmStatus!= NULL)
        {
            delete(vmStatus);
            vmStatus = NULL;
        }

        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            vmStatus = new VotingMachineStatusWrapper(*(parseVotingMachineStatus(istr, ElectionStatusTypes::Flags::dont_validate)));
            vmStatus->setDeviceStatus (sequence);
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
        	std::stringstream ss;
            ss << "FATAL - " << __func__ << e;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
        }
        catch(...)
        {
        	std::stringstream ss;
            ss << "FATAL - " << __func__;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
        }

    }
    return loadFile;
}

void OperationStatus::LoadDefault()
{
	//LoadDefaultCardListStatus();
	LoadDefaultElectionStatus();
	LoadDefaultVMStatus();
}

void OperationStatus::LoadDefaultCardListStatus()
{
	baseCardList = new CardDataList();
	
    Smartmatic::SAES::Voting::ElectionStatusTypes::NamespaceInfomap map;
    map[""].name = NAMESPACE_VOTING_STATUS;
    map[""].schema = "";

    std::ostringstream os;
    serializeCardDataListGenerated(os,*baseCardList, map, "UTF-8");
	cardListStatus = new CardGeneratedListWrapper(*baseCardList);
}

void OperationStatus::LoadDefaultElectionStatus()
{
	base = new ElectionStatus();
    std::ostringstream os;
	
	try
	{	
		Glib::TimeVal time;
		time.assign_current_time();

		std::string now = time.as_iso8601();

		base->setState(ProcessStatus::ELECTION_STATUS_NOTINSTALLED);

		std::string openCode = GuidClass::NewGuid().ToString();
		
		base->setOpeningCode (openCode);
		base->setVotersRegisteredInBook(0);
		base->setOperationModeCode("0");
		base->setElectionConfigurationReportPrinted (false);
		base->setOpenElectionDate(now);
		base->setCloseVotingDate(now);
		base->setCloseElectionDate(now);
		base->setSynchronizeVotes(false);

		electionStatus = new ElectionStatusWrapper(*base);
    }
    catch (const std::exception & e)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__ << e.what();
        logger->Debug(ss.str());
	  throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);

    }
    catch (...)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }
}

void OperationStatus::LoadDefaultVMStatus()
{
	baseVM = new VotingMachineStatus();
	devices = new DevicesStatus();
	deviceBallot = new DeviceStatus();
	devicePrinter = new DeviceStatus();
	deviceSmartcard = new DeviceStatus();
	deviceScreenCalibration = new DeviceStatus();
	deviceScreenContrast = new DeviceStatus();
	deviceAlarmBox = new DeviceStatus();
	deviceBarcode = new DeviceStatus();
	deviceFlash = new DeviceStatus();
	::xsd::cxx::tree::sequence< DeviceStatus >* sequence = new ::xsd::cxx::tree::sequence< DeviceStatus >();
	try
	{	

		baseVM->setVMFlags ("None");
		baseVM->setFactoryDiagnoseCompleted (false);
		baseVM->setTransmissionAttempts(0);
		
		deviceBallot->setVMType ("Ballot");
		deviceBallot->setVMDateTime ("2011/01/01T00:00:00");
		deviceBallot->setVMStatus ("NotDiagnosed");
		deviceBallot->setDiagnoseDescription ("Nothing");

		deviceBarcode->setVMType("Barcode");
		deviceBarcode->setVMDateTime ("2011/01/01T00:00:00");
		deviceBarcode->setVMStatus ("NotDiagnosed");
		deviceBarcode->setDiagnoseDescription ("Nothing");

		devicePrinter->setVMType ("Printer");
		devicePrinter->setVMDateTime ("2011/01/01T00:00:00");
		devicePrinter->setVMStatus ("NotDiagnosed");
		devicePrinter->setDiagnoseDescription ("Nothing");

		deviceSmartcard->setVMType ("SmartCard");
		deviceSmartcard->setVMDateTime ("2011/01/01T00:00:00");
		deviceSmartcard->setVMStatus ("NotDiagnosed");
		deviceSmartcard->setDiagnoseDescription ("Nothing");

		deviceScreenCalibration->setVMType ("TouchScreenCalibration");
		deviceScreenCalibration->setVMDateTime ("2011/01/01T00:00:00");
		deviceScreenCalibration->setVMStatus ("NotDiagnosed");
		deviceScreenCalibration->setDiagnoseDescription ("Nothing");

		deviceScreenContrast->setVMType ("ScreenContrast");
		deviceScreenContrast->setVMDateTime ("2011/01/01T00:00:00");
		deviceScreenContrast->setVMStatus ("NotDiagnosed");
		deviceScreenContrast->setDiagnoseDescription ("Nothing");
		
		deviceAlarmBox->setVMType ("AlarmBox");
		deviceAlarmBox->setVMDateTime ("2011/01/01T00:00:00");
		deviceAlarmBox->setVMStatus ("NotDiagnosed");
		deviceAlarmBox->setDiagnoseDescription ("Nothing");

		deviceFlash->setVMType ("Flash");
		deviceFlash->setVMDateTime ("2011/01/01T00:00:00");
		deviceFlash->setVMStatus ("NotDiagnosed");
		deviceFlash->setDiagnoseDescription ("Nothing");
		
		sequence->push_back(*deviceBallot);
		sequence->push_back(*deviceBarcode);
		sequence->push_back(*devicePrinter);
		sequence->push_back(*deviceSmartcard);
		sequence->push_back(*deviceScreenCalibration);
		sequence->push_back(*deviceScreenContrast);
		sequence->push_back(*deviceAlarmBox);
		sequence->push_back(*deviceFlash);
		devices->setDeviceStatus (*sequence);
		baseVM->setDevicesStatus (*devices);
    }
	catch (const std::exception & e)
	{
    	std::stringstream ss;
        ss << "FATAL - " << __func__ << e.what();
        logger->Debug(ss.str());
	}
	catch (...)
	{
    	std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Debug(ss.str());
	}

	vmStatus = new VotingMachineStatusWrapper(*baseVM);
}

void OperationStatus::changeDiagnosisStatus(Diagnostic diag, DiagStatus stat)
{
	DeviceStatus* device = NULL;
	device = getDeviceStatus(device,diag);
	if(device != NULL)
	{
		changeStatus(device,stat);
	}
}

OperationStatus::DiagStatus OperationStatus::getDiagnosisStatus(Diagnostic diag)
 {
		DeviceStatus* device = NULL;
		device = getDeviceStatus(device,diag);
		DiagStatus status = NotDiagnosed;

		if(device != NULL)
		{
			Smartmatic::SAES::Voting::Status::VMStatus::Value value = device->getVMStatus();

			device = NULL;
			switch (value)
			{
				case Smartmatic::SAES::Voting::Status::VMStatus::VOTING_MACHINE_STATUS_NOTDIAGNOSED:
					status = NotDiagnosed;
					break;
				case Smartmatic::SAES::Voting::Status::VMStatus::VOTING_MACHINE_STATUS_OK:
					status = Ok;
					break;
				case Smartmatic::SAES::Voting::Status::VMStatus::VOTING_MACHINE_STATUS_ERROR:
					status = Error;
					break;	
			}
		}
		return status;
}

std::vector<std::string> OperationStatus::getDeviceStatusList()
{
	std::vector<std::string> listOfDevices;
	xsd::cxx::tree::sequence<Smartmatic::SAES::Voting::Status::DeviceStatus> devStatus = vmStatus->getDevicesStatus().getDeviceStatus();
	for(unsigned int i= 0; i < devStatus.size();i++)
	{
		std::string statusDiagnostic;
		statusDiagnostic.append(devStatus[i].getVMType());
		statusDiagnostic.append("-");
		statusDiagnostic.append(devStatus[i].getVMStatus());
		listOfDevices.push_back(statusDiagnostic);
	}
	return listOfDevices;
}
std::vector<OperationStatus::Diagnostic> OperationStatus::getDeviceList()
{
	std::vector<Diagnostic> listOfDevices;
	xsd::cxx::tree::sequence<Smartmatic::SAES::Voting::Status::DeviceStatus> devStatus = vmStatus->getDevicesStatus().getDeviceStatus();
	for(unsigned int i= 0; i < devStatus.size();i++)
	{	
		switch(devStatus[i].getVMType())
		{
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_BALLOT:
				listOfDevices.push_back(Ballot);
				break;
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_BARCODE:
				listOfDevices.push_back(Barcode);
				break;
			case Smartmatic::SAES::Voting::Status::VMType:: VOTING_MACHINE_STATUS_PRINTER:
				listOfDevices.push_back(Printer);
				break;
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_SMARTCARD:
				listOfDevices.push_back(SmartCard);
				break;
			case Smartmatic::SAES::Voting::Status::VMType:: VOTING_MACHINE_STATUS_TOUCHSCREENCALIBRATION:
				listOfDevices.push_back(TouchScreenCalibration);
				break;
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_SCREENCONTRAST:
				listOfDevices.push_back(ScreenContrast);
				break;
			case Smartmatic::SAES::Voting::Status::VMType:: VOTING_MACHINE_STATUS_ALARMBOX:
				listOfDevices.push_back(AlarmBox);
				break;
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_FLASH:
				listOfDevices.push_back(Flash);
				break;
			case Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_ABLE:
				listOfDevices.push_back(Able);
				break;
			case Smartmatic::SAES::Voting::Status::VMType:: VOTING_MACHINE_STATUS_DATETIME:
				listOfDevices.push_back(DateTime);
				break;
		}
		
	}
	return listOfDevices;
}

DeviceStatus* OperationStatus::getDeviceStatus(DeviceStatus* device, Diagnostic diag)
{
	bool found = false;
	for(unsigned int i = 0; i<vmStatus->getDevicesStatus().getDeviceStatus().size() ;i++)
	{
		switch(diag)
		{
			case Ballot:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_BALLOT,i))
				{
					found = true;
				}
				break;
			case Printer:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_PRINTER,i))
				{
					found = true;
				}
				break;
			case AlarmBox:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_ALARMBOX,i))
				{
					found = true;
				}
				break;
			case SmartCard:				
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_SMARTCARD,i))
				{
					found = true;
				}				
				break;
			case TouchScreenCalibration:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_TOUCHSCREENCALIBRATION,i))
				{
					found = true;
				}
				break;
			case ScreenContrast:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_SCREENCONTRAST,i))
				{
					found = true;
				}
				break;
			case Able:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_ABLE,i))
				{
					found = true;
				}
				break;
			case DateTime:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_DATETIME,i))
				{
					found = true;
				}
				break;
			case Barcode:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_BARCODE,i))
				{
					found = true;
				}
				break;
			case Flash:
				if(lookStatus(Smartmatic::SAES::Voting::Status::VMType::VOTING_MACHINE_STATUS_FLASH,i))
				{
					found = true;
				}
				break;
		}
		if(found)
		{
			device = &(vmStatus->getDevicesStatus().getDeviceStatus()[i]);
			return device;
		}
	}
	return NULL;
}

bool OperationStatus::lookStatus(Smartmatic::SAES::Voting::Status::VMType::Value device, unsigned int index)
{
	if(index<vmStatus->getDevicesStatus().getDeviceStatus().size())
	{
		return vmStatus->getDevicesStatus().getDeviceStatus()[index].getVMType()== device;
	}
	return false;
}

void OperationStatus::changeStatus(DeviceStatus* device,DiagStatus stat)
{
	switch(stat)
	{
		case NotDiagnosed:
		case Run:
			device->setVMStatus(Smartmatic::SAES::Voting::Status::VMStatus::VOTING_MACHINE_STATUS_NOTDIAGNOSED);
			break;
		case Ok:
			device->setVMStatus(Smartmatic::SAES::Voting::Status::VMStatus:: VOTING_MACHINE_STATUS_OK);
			break;
		case Error:
			device->setVMStatus(Smartmatic::SAES::Voting::Status::VMStatus:: VOTING_MACHINE_STATUS_ERROR);
			break;
	}
	time_t date_temp;       // Stores seconds elapsed since 01-01-1970
	struct tm *date_format = NULL; // Saves in Date format
	char date_out[15];      // Output string
	time(&date_temp);
	date_format = localtime(&date_temp);
	strftime(date_out, 15, "%Y%m%d%H%M%S", date_format);
	std::string strtime(date_out);
	std::string strYear(strtime.substr(0,4));
	std::string strMonth(strtime.substr(4,2));
	std::string strDay(strtime.substr(6,2));
	std::string strHour(strtime.substr(8,2));
	std::string strMin(strtime.substr(10,2));
	std::string strSec(strtime.substr(12,2));
	device->setVMDateTime(strYear + "/" + strMonth + "/" + strDay + "T" + strHour + ":" + strMin + ":" + strSec);
	if(persistanceOnStatusChange)
	{
		persistVotingMachineStatus ();
	}
}

void  OperationStatus::persistElectionStatus(bool loadOpeningCode, bool createBackup)
    throw (Smartmatic::System::Exception::CryptoException,
           Smartmatic::System::Exception::SignedException,
           Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);

    Runtime::Environment::SaesDirectories directories;
	std::ostringstream os;

    std::string fileDom = directories.getElectionStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getElectionStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    try
    {
    	if (loadOpeningCode)
    	{
			if (Smartmatic::System::IO::File::canOpenFile(fileDom))
			{
				std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(fileDom, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
				std::istringstream istr (data);
				ElectionStatusWrapper es(*(parseElectionStatus(istr, ElectionStatusTypes::Flags::dont_validate)));
				electionStatus->getElectionStatus().setOpeningCode(es.getElectionStatus().getOpeningCode());
			}
			else if (Smartmatic::System::IO::File::canOpenFile(fileFlash))
			{
				std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(fileFlash, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
				std::istringstream istr (data);
				ElectionStatusWrapper es(*(parseElectionStatus(istr, ElectionStatusTypes::Flags::dont_validate)));
				electionStatus->getElectionStatus().setOpeningCode(es.getElectionStatus().getOpeningCode());
			}
    	}

        Smartmatic::SAES::Voting::ElectionStatusTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_VOTING_STATUS;
        map[""].schema = "";

        serializeElectionStatus(os,electionStatus->getElectionStatus(), map, "UTF-8");
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__ << e;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }
    catch (...)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);

    	if (createBackup)
        {
    		File::copyFile(fileDom, fileFlash);
        }
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);

    	if (createBackup)
        {
    		File::copyFile(fileFlash, fileDom);
        }
    }
}

void OperationStatus::PersistOnStatusChange(bool persistOnChange)
{
	persistanceOnStatusChange = persistOnChange;
}

void  OperationStatus::persistVotingMachineStatus()
    throw (Smartmatic::System::Exception::CryptoException,
           Smartmatic::System::Exception::SignedException,
           Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);
    std::ostringstream os;

    try
	{
        Smartmatic::SAES::Voting::ElectionStatusTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_VOTING_STATUS;
        map[""].schema = "";

        serializeVotingMachineStatus(os,vmStatus->getVotingMachineStatus(), map, "UTF-8");
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__ << e;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }
    catch (...)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }

    std::string data = os.str();
    Runtime::Environment::SaesDirectories directories;

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getVotingMachineStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getVotingMachineStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileFlash, fileDom);
    }
}

void  OperationStatus::persistCardListStatus()
    throw (Smartmatic::System::Exception::CryptoException,
           Smartmatic::System::Exception::SignedException,
           Smartmatic::System::Exception::XmlException)
{
	Glib::Mutex::Lock lock(mutex);
    std::ostringstream os;

    try
	{
        Smartmatic::SAES::Voting::ElectionStatusTypes::NamespaceInfomap map;
        map[""].name = NAMESPACE_VOTING_STATUS;
        map[""].schema = "";

        serializeCardDataListGenerated(os,cardListStatus->getCardDataListStatus(), map, "UTF-8");
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__ << e;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }
    catch (...)
    {
    	std::stringstream ss;
        ss << "FATAL - " << __func__;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), N_("Smartmatic.SAES.Voting.OperationStatus.ErrorSerializaData"), logger);
    }

    std::string data = os.str();
    Runtime::Environment::SaesDirectories directories;

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getCardListStatusFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getCardListStatusFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileDom,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, fileFlash,
                Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
        File::copyFile(fileFlash, fileDom);
    }
}

ElectionStatusWrapper * OperationStatus::getElectionStatusWrapper()
{
	Glib::Mutex::Lock lock(mutex);
	return electionStatus;
}

CardGeneratedListWrapper * OperationStatus::getCardGeneratedListStatusWrapper()
{
	Glib::Mutex::Lock lock(mutex);
	return cardListStatus;
}

VotingMachineStatusWrapper * OperationStatus::getVotingMachineStatusWrapper()
{
	Glib::Mutex::Lock lock(mutex);
	return vmStatus;
}

void OperationStatus::dispose ()
{
	if (electionStatus != NULL)
	{
		delete electionStatus;
		electionStatus = NULL;
	}
	
	if (vmStatus != NULL)
	{
		delete vmStatus;
		vmStatus = NULL;
	}

	if (cardListStatus != NULL)
	{
		delete cardListStatus;
		cardListStatus = NULL;
	}
}

OperationStatus::~OperationStatus()
{
    dispose();
}
