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
#include <sstream>
#include <iostream>
#include <fstream>
#include "Voting/PBReports/id-card-info-wrapper.h"
#include <Log/SMTTLogManager.h>
#include <Security/Encryption.hxx>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include "Log/ISMTTLog.h"

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

using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::Exception;

ISMTTLog* IDCardInfoWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper",GETTEXT_PACKAGE);

IDCardInfoWrapper::IDCardInfoWrapper()
{
	this->saesDirectories = NULL;
	this->idCardMembers = NULL;
}

IDCardInfoWrapper::~IDCardInfoWrapper()
{
	if (idCardMembers)
	{
		delete idCardMembers;
		idCardMembers = NULL;
	}
}

bool IDCardInfoWrapper::init(SaesDirectories * saesDirectories)
	throw (CryptoException,
			SignedException,
			XmlException)
{
	this->saesDirectories = saesDirectories;

	if (idCardMembers)
	{
		delete idCardMembers;
		idCardMembers = NULL;
	}

	return loadMembersFile();
}

void IDCardInfoWrapper::generateIdCardInfoWrapper(Smartmatic::SAES::EID::CitizenInfo &citizenInfo,
		IDCardInfo & info)
{
	info.setFirstName (citizenInfo.getFirstName ());
	info.setSurname (citizenInfo.getSurname ());

	if(citizenInfo.getGender () != "") 				info.setGender (citizenInfo.getGender ());
	if(citizenInfo.getDateOfBirth () != "") 		info.setDateOfBirth (citizenInfo.getDateOfBirth ());
	if(citizenInfo.getLocationOfBirth () != "") 	info.setLocationOfBirth (citizenInfo.getLocationOfBirth ());
	if(citizenInfo.getNationality () != "") 		info.setNationality (citizenInfo.getNationality ());
	if(citizenInfo.getNationalNumber () != "") 		info.setNationalNumber (citizenInfo.getNationalNumber ());
	if(citizenInfo.getSpecialOrganization () != "") info.setSpecialOrganization (citizenInfo.getSpecialOrganization ());
	if(citizenInfo.getMemberOfFamily () != "") 		info.setMemberOfFamily (citizenInfo.getMemberOfFamily ());
	if(citizenInfo.getAddressVersion () != "") 		info.setAddressVersion (citizenInfo.getAddressVersion ());
	if(citizenInfo.getStreet () != "") 				info.setStreet (citizenInfo.getStreet ());
	if(citizenInfo.getZipCode () != "") 			info.setZipCode (citizenInfo.getZipCode ());
	if(citizenInfo.getMunicipality () != "") 		info.setMunicipality (citizenInfo.getMunicipality ());
	if(citizenInfo.getCountry () != "") 			info.setCountry (citizenInfo.getCountry ());
	if(citizenInfo.getSpecialStatus () != "") 		info.setSpecialStatus (citizenInfo.getSpecialStatus ());
}

void IDCardInfoWrapper::generateCitizenInfo(IDCardInfo & idCardInfo, Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
{
	citizenInfo.setFirstName(idCardInfo.getFirstName());
	citizenInfo.setSurname(idCardInfo.getSurname());

	if(idCardInfo.getGender ().present())				citizenInfo.setGender(idCardInfo.getGender().get());
	if(idCardInfo.getDateOfBirth ().present()) 		citizenInfo.setDateOfBirth (idCardInfo.getDateOfBirth ().get());
	if(idCardInfo.getLocationOfBirth ().present()) 	citizenInfo.setLocationOfBirth (idCardInfo.getLocationOfBirth ().get());
	if(idCardInfo.getNationality ().present()) 		citizenInfo.setNationality (idCardInfo.getNationality ().get());
	if(idCardInfo.getNationalNumber ().present()) 	citizenInfo.setNationalNumber (idCardInfo.getNationalNumber ().get());
	if(idCardInfo.getSpecialOrganization ().present())citizenInfo.setSpecialOrganization (idCardInfo.getSpecialOrganization ().get());
	if(idCardInfo.getMemberOfFamily ().present()) 	citizenInfo.setMemberOfFamily (idCardInfo.getMemberOfFamily ().get());
	if(idCardInfo.getAddressVersion ().present()) 	citizenInfo.setAddressVersion (idCardInfo.getAddressVersion ().get());
	if(idCardInfo.getStreet ().present()) 			citizenInfo.setStreet (idCardInfo.getStreet ().get());
	if(idCardInfo.getZipCode ().present()) 			citizenInfo.setZipCode (idCardInfo.getZipCode ().get());
	if(idCardInfo.getMunicipality ().present()) 		citizenInfo.setMunicipality (idCardInfo.getMunicipality ().get());
	if(idCardInfo.getCountry ().present()) 			citizenInfo.setCountry (idCardInfo.getCountry ().get());
	if(idCardInfo.getSpecialStatus ().present()) 		citizenInfo.setSpecialStatus (idCardInfo.getSpecialStatus ().get());
}

std::string IDCardInfoWrapper::serializeIdCardInfoWrapper(Smartmatic::SAES::EID::CitizenInfo &citizenInfo)
{
    std::string data;

    try
	{
	    std::ostringstream os;
        IDCardInfo idCardInfo;
        generateIdCardInfoWrapper(citizenInfo, idCardInfo);
        serializeIDCardInfo(os,idCardInfo);
        data = os.str();
	}
	catch (...)
	{
	    logger->Debug("FATAL - error serialize IDCardInfo");
    }

	return data;
}

void IDCardInfoWrapper::addPMInstallIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardInfo info;
	generateIdCardInfoWrapper(citizenInfo, info);
	info.setType(IDCardInfoType::IDCARDINFO_INSTALLPM);
	persistenceInfo(info);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.AddPMInstallMemberInfo"));
}

void IDCardInfoWrapper::addVMInstallIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardInfo info;
	generateIdCardInfoWrapper(citizenInfo, info);
	info.setType(IDCardInfoType::IDCARDINFO_INSTALLVM);
	persistenceInfo(info);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.AddVMInstallMemberInfo"));
}

void IDCardInfoWrapper::addOpenElectionIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardInfo info;
	generateIdCardInfoWrapper(citizenInfo, info);
	info.setType(IDCardInfoType::IDCARDINFO_OPENELECTION);
	persistenceInfo(info);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.AddOpenElectionMemberInfo"));
}

void IDCardInfoWrapper::addCloseVotingIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardInfo info;
	generateIdCardInfoWrapper(citizenInfo, info);
	info.setType(IDCardInfoType::IDCARDINFO_CLOSEVOTING);
	persistenceInfo(info);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.AddCloseVotingMemberInfo"));
}

void IDCardInfoWrapper::addCloseElectionIdCardInfo(Smartmatic::SAES::EID::CitizenInfo & citizenInfo)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardInfo info;
	generateIdCardInfoWrapper(citizenInfo, info);
	info.setType(IDCardInfoType::IDCARDINFO_CLOSEELECTION);
	persistenceInfo(info);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.AddCloseElectionMemberInfo"));
}

bool IDCardInfoWrapper::loadMembersFile()
	throw (CryptoException,
			SignedException,
			XmlException)
{
    std::string fileDom = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_FLASH);
    std::string file;

    if (File::canOpenFile(fileDom))
    {
    	file = fileDom;
    }
    else if (File::canOpenFile(fileFlash))
    {
    	file = fileFlash;
    }
    else
    {
    	idCardMembers = new IDCardMembers();
    	return false;
    }

    try
    {
    	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(file,
    			Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
		std::istringstream istr (data);
		idCardMembers = new IDCardMembers(*(parseIDCardMembers(istr, Flags::dont_validate)));
    }
    catch(...)
    {
    	throw XmlException (_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.ErrorLoadFile"),
    						N_("Smartmatic.SAES.Voting.PBReports.IDCardInfoWrapper.ErrorLoadFile"),
    						logger);
    }

    return true;
}

void IDCardInfoWrapper::persistenceInfo(IDCardInfo & info)
    throw (CryptoException,
            SignedException,
            XmlException)
{
	IDCardMembers::IDCardInfoSequence seq = idCardMembers->getIDCardInfo();
	seq.push_back(info);
	idCardMembers->setIDCardInfo(seq);

	persistence();
}

void IDCardInfoWrapper::persistence()
    throw (CryptoException,
            SignedException,
            XmlException)
{
    std::string data;

    try
	{
	    std::ostringstream os;
        serializeIDCardMembers(os, *idCardMembers);
        data = os.str();
	}
	catch (...)
	{
	    logger->Debug("FATAL - error serialize IdCardMembers");
    }

    std::string devicePathDom = saesDirectories->getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = saesDirectories->getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = saesDirectories->getIDCardMembersFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if (Directory::DirectoryExists(devicePathDom))
    {
    	Encryption::getInstance()->saveXmlFile(data, fileDom, Encryption::INTERNAL_FILE);
        File::copyFile(fileDom, fileFlash);
    }
    else if (Directory::DirectoryExists(devicePathFlash))
    {
    	Encryption::getInstance()->saveXmlFile(data, fileFlash, Encryption::INTERNAL_FILE);
        File::copyFile(fileFlash, fileDom);
    }
}

bool IDCardInfoWrapper::isInstallPM()
{
	bool validate = false;

	IDCardMembers::IDCardInfoSequence seq = idCardMembers->getIDCardInfo();
	IDCardMembers::IDCardInfoIterator it;

	for (it = seq.begin();
		 it != seq.end();
		 it++)
	{
		IDCardInfo info = (*it);

		if (info.getType() && info.getType().get() == IDCardInfoType::IDCARDINFO_INSTALLPM)
		{
			validate = true;
			break;
		}
	}

	return validate;
}

IDCardMembers * IDCardInfoWrapper::getIdCardMembers()
{
	return idCardMembers;
}
