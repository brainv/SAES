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
#include "Voting/PBReports/activated-card-statistics-wrapper.h"
#include <Runtime/Environment/saes-directories.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <Security/Encryption.hxx>
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
#include <Runtime/Environment/DirectoryManager.hxx>
#include <Runtime/Environment/MemoryPathController.h>

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
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace std;
using namespace Smartmatic::SAES::Runtime::Environment;

#define __ERROR_SERIALIZE_DATA_ N_("Smartmatic.SAES.Voting.PBReports.ActivatedCardStatisticsWrapper.ErrorParseFile")

ISMTTLog* ActivatedCardStatisticsWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.ActivatedCardStatisticsWrapper", GETTEXT_PACKAGE);

ActivatedCardStatisticsWrapper::ActivatedCardStatisticsWrapper()
{
	cardStatistics = NULL;
	oneMemory = false;
}

ActivatedCardStatisticsWrapper::~ActivatedCardStatisticsWrapper()
{
}

void ActivatedCardStatisticsWrapper::Persist()
    throw (CryptoException,
           SignedException,
           XmlException)
{
	this->oneMemory = oneMemory;
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializeActivatedCardStatistics(os,*cardStatistics, map, "UTF-8");

    std::string data = os.str();
    std::string fileDom = directories.getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

    if(!MemoryPathController::getInstance()->getDomMemoryBasePath().empty() &&
    		!MemoryPathController::getInstance()->getFlashMemoryBasePath().empty())
    {
	    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
	    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

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
    else
    {
    	string tempFile = fileDom;
    	tempFile.replace(tempFile.end()-4, tempFile.end(), "XYZ.xml");
    	Smartmatic::SAES::Security::Encryption::getInstance()->saveXmlFile(data, tempFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
    }
}

bool ActivatedCardStatisticsWrapper::Load(std::string xmlFile, Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

	if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
		if(cardStatistics) delete cardStatistics;
	    cardStatistics = new ActivatedCardStatistics();
		cardStatistics->setTotalActivated(0);
		cardStatistics->setTotalNonAudioActivated(0);
		cardStatistics->setTotalAudioActivated(0);
		cardStatistics->setTotalOfficialActivated(0);
		cardStatistics->setTotalDemoActivated(0);
		cardStatistics->setTotalRecoveryActivated(0);
		cardStatistics->setTotalAudioOfficialActivated(0);
		cardStatistics->setTotalAudioDemoActivated(0);
		cardStatistics->setTotalAudioRecoveryActivated(0);
		cardStatistics->setTotalNonAudioOfficialActivated(0);
		cardStatistics->setTotalNonAudioDemoActivated(0);
		cardStatistics->setTotalNonAudioRecoveryActivated(0);
		ActivatedOfficialNonAudioByCA officialNonAudio;
		ActivatedOfficialNonAudioByCA::CardByCASequence officialNonAudioSeq;
		
		ActivatedDemoNonAudioByCA demoNonAudio;
		ActivatedDemoNonAudioByCA::CardByCASequence demoNonAudioSeq;
		
		ActivatedOfficialAudioByCA officialAudio;
		ActivatedOfficialAudioByCA::CardByCASequence officialAudioSeq;
		
		ActivatedDemoAudioByCA demoAudio;
		ActivatedDemoAudioByCA::CardByCASequence demoAudioSeq;

		try
		{
			votingDeviceWrapper = elecConf->getVotingDevice();
			vd = votingDeviceWrapper->getFirstVotingDevice();
			Smartmatic::SAES::Voting::VotingDevice::Logical_voter_groups lvgs = votingDeviceWrapper->getLogicalVoterGroups(vd);

			if (lvgs.getCustom_attribute_definitions() != NULL)
			{
	            Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definitions caDefs = lvgs.getCustom_attribute_definitions().get();

	            for(unsigned int i = 0;i < caDefs.getCustom_attribute_definition().size();i++)
                {
                        for(unsigned int j = 0;j < caDefs.getCustom_attribute_definition()[i].getValue().size() ;j++)
                        {
                            ActivatedCardByCA cardByCa;
                            cardByCa.setCounter (0);
                            cardByCa.setCACode (caDefs.getCustom_attribute_definition()[i].getCode());
                            cardByCa.setCAValue (caDefs.getCustom_attribute_definition()[i].getValue()[j]);
                            officialNonAudioSeq.push_back(cardByCa);
                            demoNonAudioSeq.push_back(cardByCa);
                            officialAudioSeq.push_back(cardByCa);
                            demoAudioSeq.push_back(cardByCa);
                        }
                }
            }
		}
		catch(Smartmatic::System::Exception::VotingDeviceException & ex)
		{
		    std::stringstream ss;
			ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << ex.getMessage();
			logger->Debug(ss.str());
		}

		officialNonAudio.setCardByCA (officialNonAudioSeq);
		demoNonAudio.setCardByCA (demoNonAudioSeq);
		officialAudio.setCardByCA (officialAudioSeq);
		demoAudio.setCardByCA (demoAudioSeq);
			
		cardStatistics->setActivatedOfficialNonAudioByCA(officialNonAudio);
	    cardStatistics->setActivatedDemoNonAudioByCA(demoNonAudio);
		cardStatistics->setActivatedOfficialAudioByCA(officialAudio);
		cardStatistics->setActivatedDemoAudioByCA(demoAudio);
    }
	else
	{
	    try
	    {
	    	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
	        std::istringstream istr (data);
	        if(cardStatistics) delete cardStatistics;
	        cardStatistics = new ActivatedCardStatistics(*(parseActivatedCardStatistics(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
	        loadFile = true;
	    }
	    catch (const ::xsd::cxx::tree::exception< char >& e)
	    {
		    std::stringstream ss;
			ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << e;
			logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_(__ERROR_SERIALIZE_DATA_), N_(__ERROR_SERIALIZE_DATA_), logger);
	    }
	    catch(...)
	    {
		    std::stringstream ss;
			ss << "FATAL " << __LINE__ << " " << __FILE__;
			logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_(__ERROR_SERIALIZE_DATA_), N_(__ERROR_SERIALIZE_DATA_), logger);
	    }
	}
	return loadFile;
}

bool ActivatedCardStatisticsWrapper::RestoreFile(Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
{
	bool restoreSuccesfull = false;

	Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

	std::string file = directories.getActivatedCardStatisticsFileFullPath();
	file.replace(file.end()-4, file.end(), "XYZ.xml");

	try
	{
		if(Smartmatic::System::IO::File::canOpenFile(file))
		{
			Load(file,elecConf);
			Persist();
			restoreSuccesfull = true;
			Smartmatic::System::IO::File::DeleteFile(file);

			file = directories.getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);
			file.replace(file.end()-4, file.end(), "XYZ.xml");
			Smartmatic::System::IO::File::DeleteFile(file);
		}
		else
		{
			file = directories.getActivatedCardStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);
			file.replace(file.end()-4, file.end(), "XYZ.xml");

			if(Smartmatic::System::IO::File::canOpenFile(file))
			{
				Load(file,elecConf);
				Persist();
				restoreSuccesfull = true;
				Smartmatic::System::IO::File::DeleteFile(file);
			}
		}
	}
	catch(...)
	{
		logger->Debug("Error in RestoreFile");
	}

	return restoreSuccesfull;
}

bool ActivatedCardStatisticsWrapper::init (Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return Load(directories.getActivatedCardStatisticsFileFullPath(), elecConf);
}

void ActivatedCardStatisticsWrapper::RefreshStats(Smartmatic::SAES::Voting::VotingDevice::Card_data & card)
throw (Smartmatic::System::Exception::CryptoException,
                             Smartmatic::System::Exception::SignedException,
                             Smartmatic::System::Exception::XmlException)
{
	IncrementTotalActivated ();
	if(card.getCard_type() == Card_type::CARD_DATA_OFFICIAL_VOTE_CARD)
	{
		IncrementTotalOfficialActivated();
		if(card.getIsAudio())
		{
			IncrementTotalAudioActivated ();
			IncrementTotalAudioOfficialActivated ();
			for(unsigned int i=0;i<card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute().size(); i++)
			{
				for(unsigned int j=0;j<cardStatistics->getActivatedOfficialAudioByCA().getCardByCA().size(); j++)
				{
					if(card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getCode().compare(cardStatistics->getActivatedOfficialAudioByCA().getCardByCA()[j].getCACode())==0
					   && card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getValue().compare(cardStatistics->getActivatedOfficialAudioByCA().getCardByCA()[j].getCAValue())==0)
					{
						unsigned int caCounter = cardStatistics->getActivatedOfficialAudioByCA().getCardByCA()[j].getCounter();
						caCounter++;
						cardStatistics->getActivatedOfficialAudioByCA().getCardByCA()[j].setCounter(caCounter);
					}
				}
			}
		}
		else
		{
			IncrementTotalNonAudioActivated ();
			IncrementTotalNonAudioOfficialActivated ();
			for(unsigned int i=0;i<card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute().size(); i++)
			{
				for(unsigned int j=0;j<cardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA().size(); j++)
				{
					if(card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getCode().compare(cardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCACode())==0
					   && card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getValue().compare(cardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCAValue())==0)
					{
						unsigned int caCounter = cardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA()[j].getCounter();
						caCounter++;
						cardStatistics->getActivatedOfficialNonAudioByCA().getCardByCA()[j].setCounter(caCounter);
					}
				}
			}
		}
	}
	else if(card.getCard_type() == Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD)
	{
		IncrementTotalDemoActivated();
		if(card.getIsAudio())
		{
			IncrementTotalAudioActivated ();
			IncrementTotalAudioDemoActivated ();
			for(unsigned int i=0;i<card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute().size(); i++)
			{
				for(unsigned int j=0;j<cardStatistics->getActivatedDemoAudioByCA().getCardByCA().size(); j++)
				{
					if(card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getCode().compare(cardStatistics->getActivatedDemoAudioByCA().getCardByCA()[j].getCACode())==0
					   && card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getValue().compare(cardStatistics->getActivatedDemoAudioByCA().getCardByCA()[j].getCAValue())==0)
					{
						unsigned int caCounter = cardStatistics->getActivatedDemoAudioByCA().getCardByCA()[j].getCounter();
						caCounter++;
						cardStatistics->getActivatedDemoAudioByCA().getCardByCA()[j].setCounter(caCounter);
					}
				}
			}
		}
		else
		{
			IncrementTotalNonAudioActivated ();
			IncrementTotalNonAudioDemoActivated ();
			for(unsigned int i=0;i<card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute().size(); i++)
			{
				for(unsigned int j=0;j<cardStatistics->getActivatedDemoNonAudioByCA().getCardByCA().size(); j++)
				{
					if(card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getCode().compare(cardStatistics->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCACode())==0
					   && card.getLogical_voter_group ().getCustom_attributes().get().getCustom_attribute()[i].getValue().compare(cardStatistics->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCAValue())==0)
					{
						unsigned int caCounter = cardStatistics->getActivatedDemoNonAudioByCA().getCardByCA()[j].getCounter();
						caCounter++;
						cardStatistics->getActivatedDemoNonAudioByCA().getCardByCA()[j].setCounter(caCounter);
					}
				}
			}
			
		}
	}
	else if(card.getCard_type() == Card_type::CARD_DATA_RECOVERY_VOTE_CARD)
	{
		IncrementTotalRecoveryActivated();
		if(card.getIsAudio())
		{
			IncrementTotalAudioActivated ();
			IncrementTotalAudioRecoveryActivated ();
		}
		else
		{
			IncrementTotalNonAudioActivated ();
			IncrementTotalNonAudioRecoveryActivated ();
		}
	}
	Persist();
}

ActivatedCardStatistics* ActivatedCardStatisticsWrapper::getCardStatistics()
{
	return cardStatistics;
}

void ActivatedCardStatisticsWrapper::IncrementTotalActivated()
{
	cardStatistics->setTotalActivated (cardStatistics->getTotalActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalNonAudioActivated()
{
	cardStatistics->setTotalNonAudioActivated (cardStatistics->getTotalNonAudioActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalAudioActivated()
{
	cardStatistics->setTotalAudioActivated (cardStatistics->getTotalAudioActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalOfficialActivated()
{
	cardStatistics->setTotalOfficialActivated (cardStatistics->getTotalOfficialActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalDemoActivated()
{
	cardStatistics->setTotalDemoActivated (cardStatistics->getTotalDemoActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalRecoveryActivated()
{
	cardStatistics->setTotalRecoveryActivated (cardStatistics->getTotalRecoveryActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalAudioOfficialActivated()
{
	cardStatistics->setTotalAudioOfficialActivated (cardStatistics->getTotalAudioOfficialActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalAudioDemoActivated()
{
	cardStatistics->setTotalAudioDemoActivated (cardStatistics->getTotalAudioDemoActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalAudioRecoveryActivated()
{
	cardStatistics->setTotalAudioRecoveryActivated (cardStatistics->getTotalAudioRecoveryActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalNonAudioOfficialActivated()
{
	cardStatistics->setTotalNonAudioOfficialActivated (cardStatistics->getTotalNonAudioOfficialActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalNonAudioDemoActivated()
{
	cardStatistics->setTotalNonAudioDemoActivated (cardStatistics->getTotalNonAudioDemoActivated()+1);
}

void ActivatedCardStatisticsWrapper::IncrementTotalNonAudioRecoveryActivated()
{
	cardStatistics->setTotalNonAudioRecoveryActivated (cardStatistics->getTotalNonAudioRecoveryActivated()+1);
}

unsigned int ActivatedCardStatisticsWrapper::getTotalActivated()
{
	return cardStatistics->getTotalActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalNonAudioActivated()
{
	return cardStatistics->getTotalNonAudioActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalAudioActivated()
{
	return cardStatistics->getTotalAudioActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalOfficialActivated()
{
	return cardStatistics->getTotalOfficialActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalDemoActivated()
{
	return cardStatistics->getTotalDemoActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalRecoveryActivated()
{
	return cardStatistics->getTotalRecoveryActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalAudioOfficialActivated()
{
	return cardStatistics->getTotalAudioOfficialActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalAudioDemoActivated()
{
	return cardStatistics->getTotalAudioDemoActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalAudioRecoveryActivated()
{
	return cardStatistics->getTotalAudioRecoveryActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalNonAudioOfficialActivated()
{
	return cardStatistics->getTotalNonAudioOfficialActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalNonAudioDemoActivated()
{
	return cardStatistics->getTotalNonAudioDemoActivated();
}

unsigned int ActivatedCardStatisticsWrapper::getTotalNonAudioRecoveryActivated()
{
	return cardStatistics->getTotalNonAudioRecoveryActivated();
}

void ActivatedCardStatisticsWrapper::Dispose ()
{
    if (cardStatistics != NULL)
    {
        delete cardStatistics;
        cardStatistics = NULL;
    }
}
