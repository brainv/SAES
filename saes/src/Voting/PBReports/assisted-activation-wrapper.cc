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
#include <glib.h>
#include "Voting/PBReports/assisted-activation-wrapper.h"
#include "System/guid-class.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
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

using namespace Smartmatic::System;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace std;

ISMTTLog* AssistedActivationWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.AssistedActivationWrapper",GETTEXT_PACKAGE);

AssistedActivationWrapper::AssistedActivationWrapper()
{
	assistedActivations = NULL;
}

AssistedActivationWrapper::~AssistedActivationWrapper()
{
}

void AssistedActivationWrapper::Persist()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializeAssistedActivations(os,*assistedActivations, map, "UTF-8");

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getAssistedActivationFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getAssistedActivationFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

bool AssistedActivationWrapper::Load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        assistedActivations = new AssistedActivations();
        Activations activations;
        assistedActivations->setActivations(activations);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            assistedActivations = new AssistedActivations(*(parseAssistedActivations(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::cerr << "FATAL - " << __func__ << e << std::endl;
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.AssistedActivationWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.AssistedActivationWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}


bool AssistedActivationWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return Load(directories.getAssistedActivationFileFullPath());
}

void AssistedActivationWrapper::AddActivation(Activation activation)
{
	GuidClass guidC = GuidClass::NewGuid();
	activation.setCustom_code((std::string)guidC.ToString());
	assistedActivations->getActivations().getActivation().push_back (activation);
	logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.AssistedActivationWrapper.AddAssistedActivation"));
}

void AssistedActivationWrapper::RemoveActivation(std::string customCode)
{
	
	for (Activations::ActivationIterator
         p (assistedActivations->getActivations ().getActivation().begin ());
         p != assistedActivations->getActivations ().getActivation().end ();
         ++p)
    {
       if ( customCode .compare((*p).getCustom_code())== 0 )
       {
          assistedActivations->getActivations ().getActivation().erase(p);
		  break;
       }
    }
	return;
}

void AssistedActivationWrapper::ModifyActivation(Activation activation)
{
	
	for (Activations::ActivationIterator
         p (assistedActivations->getActivations ().getActivation().begin ());
         p != assistedActivations->getActivations ().getActivation().end ();
         ++p)
    {
       if ( activation.getCustom_code().compare((*p).getCustom_code()) == 0 )
       {
         *p = activation;
         //(*p).setElector_names (activation.getElector_names ());
         //(*p).setWitness_names (activation.getWitness_names ());
		  break;
       }
    }
	return;

}

Activation AssistedActivationWrapper::getActivation(std::string customCode)
{
	for (Activations::ActivationIterator
         p (assistedActivations->getActivations ().getActivation().begin ());
         p != assistedActivations->getActivations ().getActivation().end ();
         ++p)
    {
       if ( customCode.compare((*p).getCustom_code()) == 0 )
       {
          return *p;
       }
    }
	Activation dummyActivation;
	return dummyActivation;
}

Activations AssistedActivationWrapper::getActivations()
{
	return assistedActivations->getActivations();
}


void AssistedActivationWrapper::Dispose ()
{
    if (assistedActivations != NULL)
    {
        delete assistedActivations;
        assistedActivations = NULL;
    }
}
