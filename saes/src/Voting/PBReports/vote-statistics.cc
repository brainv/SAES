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
#include "Voting/PBReports/vote-statistics.h"
#include "Configuration/s-a-e-s-conf-manager.h"
#include <sstream>
#include <Log/SMTTLogManager.h>
#include "Log/ISMTTLog.h"
#include <System/IO/File.h>
#include <System/IO/Directory.h>

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
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Common::Configuration;

#define LOGGER_PROJECT "Smartmatic.SAES.Voting.PBReports.VoteStatistics" ///< logger project name

#ifdef GETTEXT_PACKAGE
ISMTTLog* VoteStatisticsWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,GETTEXT_PACKAGE);
#else
ISMTTLog* VoteStatisticsWrapper::logger = SMTTLogManager::GetLogger(LOGGER_PROJECT,"");
#endif

VoteCounterByCA::VoteCounterByCA(std::string caCode, std::string caValue, unsigned int initialCounter)
{
	this->caCode = caCode;
	this->caValue = caValue;
	this->counter = initialCounter;
}

VoteCounterByCA::~VoteCounterByCA()
{
}

void VoteCounterByCA::incrementCounter()
{
	counter++;
}

std::string VoteCounterByCA::getCACode()
{
	return caCode;
}

std::string VoteCounterByCA::getCAValue()
{
	return caValue;
}

unsigned int VoteCounterByCA::getCounter()
{
	return counter;
}

void VoteCounterByCA::clearCounter()
{
    counter = 0;
}

VoteStatisticsWrapper::VoteStatisticsWrapper()
{
	statistics = NULL;
	deltaVotes = 0;
}

VoteStatisticsWrapper::~VoteStatisticsWrapper()
{
    Dispose();
}

unsigned int VoteStatisticsWrapper::getVoteCounterByCACodeAndValue(std::string caCode, std::string caValue)
{
	unsigned int counter = 0;
	for(unsigned int j=0;j < voteCountersByCA.size();j++)
	{
		if(caCode.compare(voteCountersByCA[j].getCACode())==0
		   && caValue.compare(voteCountersByCA[j].getCAValue())==0)
		{
			counter = voteCountersByCA[j].getCounter();
			break;
		}
	}
	return counter;
}

VoteStatistics VoteStatisticsWrapper::convertToGeneratedClass()
{
	VoteStatistics statistics;
	statistics.setTotalVotes(getTotalVotes());
	statistics.setTotalSecurityVotes(getSecurityCopyVotes());
	statistics.setTotalOfficialVotes (getOfficialVotes());
	statistics.setTotalDemoVotes (getDemoVotes());
	statistics.setTotalSuperNullVotes (getSuperNullVotes());
	statistics.setTotalDuplicatedVotes(getDuplicatedVotes());
	statistics.setTotalSimulatedVotes(getSimulatedVotes());

	VotesByCA votesCA;
	VotesByCA::VoteByCASequence voteCAseq;

	for(unsigned int j=0;j < voteCountersByCA.size();j++)
	{
		VoteByCA voteCA;
		voteCA.setVotesCounter (voteCountersByCA[j].getCounter ());
		voteCA.setCACode (voteCountersByCA[j].getCACode ());
		voteCA.setCAValue (voteCountersByCA[j].getCAValue ());
		voteCAseq.push_back(voteCA);
	}

	votesCA.setVoteByCA (voteCAseq);
	statistics.setVotesByCA (votesCA);

	return statistics;
}

bool VoteStatisticsWrapper::IsVoteProcessed(Smartmatic::SAES::Voting::Vote::Vote & vote)
{
	for(unsigned int j=0;j < voteGUUIDsRegistered.size();j++)
	{
		if(voteGUUIDsRegistered[j].compare(vote.getCode())==0)
		{
			return true;
		}
	}
	return false;
}

bool VoteStatisticsWrapper::IsVoteProcessed(std::string voteGUUID)
{
	for(unsigned int j=0;j < voteGUUIDsRegistered.size();j++)
	{
		if(voteGUUIDsRegistered[j].compare(voteGUUID)==0)
		{
			return true;
		}
	}
	return false;
}

bool  VoteStatisticsWrapper::ProcessVote(Smartmatic::SAES::Voting::Vote::Vote & vote)
{
    bool validate = false;

	try
	{
		if(!IsVoteProcessed(vote))
		{
		    std::string sblvgCode = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();
		    std::string voteLVG = vote.getLogicalVoterGroup();

			if(voteLVG != sblvgCode)
			{
			    Smartmatic::SAES::Voting::VotingDevice::Logical_voter_group & lvg (votingDeviceWrapper->getLogicalVoterGroup(vd,vote.getLogicalVoterGroup ()));
				bool incrementVote = false;

				for(unsigned int i=0;i < lvg.getCustom_attributes ().get().getCustom_attribute ().size();i++)
				{
						for(unsigned int j=0;j < voteCountersByCA.size();j++)
						{
							if(lvg.getCustom_attributes ().get().getCustom_attribute ()[i].getCode().compare(voteCountersByCA[j].getCACode())==0
							   && lvg.getCustom_attributes ().get().getCustom_attribute ()[i].getValue().compare(voteCountersByCA[j].getCAValue())==0)
							{
								voteCountersByCA[j].incrementCounter();
								incrementVote = true;
								break;
							}
						}
				}
				if(incrementVote)
				{
					incrementTotalVotes();
					voteGUUIDsRegistered.push_back (vote.getCode());
					switch(vote.getMode())
					{
						case Vote::VoteMode::VOTE_O:
							incrementOfficialVotes();
							break;
						case Vote::VoteMode::VOTE_D:
							incrementDemoVotes();
							break;
						case Vote::VoteMode::VOTE_R:
							incrementSecurityVotes();
							break;
						case Vote::VoteMode::VOTE_S:
							incrementSimulateVotes();
							break;
					}
				}
			}
			else
			{
				incrementSuperNullVotes();
				incrementTotalVotes();
				voteGUUIDsRegistered.push_back (vote.getCode());
				switch(vote.getMode())
				{
					case Vote::VoteMode::VOTE_O:
						incrementOfficialVotes();
						break;
					case Vote::VoteMode::VOTE_D:
						incrementDemoVotes();
						break;
					case Vote::VoteMode::VOTE_R:
						incrementSecurityVotes();
						break;
					case Vote::VoteMode::VOTE_S:
						incrementSimulateVotes();
						break;
				}
			}

			validate = true;
		}
		else
		{
			incrementTotalDuplicatedVotes();
		}
		
	}	
	catch(Smartmatic::System::Exception::VotingDeviceException & ex)
	{
        std::stringstream ss;
        ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << ex.getMessage();
        logger->Debug(ss.str());
        return false;
	}

	return validate;
}

std::vector<VoteCounterByCA> VoteStatisticsWrapper::getVoteCountersByCA()
{
	return voteCountersByCA;
}

bool VoteStatisticsWrapper::init (Smartmatic::SAES::Voting::ElectoralConfiguration * elecConf)
	throw (CryptoException,
		   SignedException,
		   XmlException,
		   VoteException)
{
    Dispose();

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
                        VoteCounterByCA voteCounter(caDefs.getCustom_attribute_definition()[i].getCode(), caDefs.getCustom_attribute_definition()[i].getValue()[j]);
                        voteCountersByCA.push_back(voteCounter);
                    }
            }
		}
		else
		{
		    logger->Debug("ERROR - Custom attribute definitions not found.");
		}
	}
	catch(Smartmatic::System::Exception::VotingDeviceException & ex)
	{
        std::stringstream ss;
        ss << "FATAL " << __LINE__ << " " << __FILE__ << ": " << ex.getMessage();
        logger->Debug(ss.str());
	}

	Glib::Mutex::Lock lock(mutex);
	int totalVotes = -1;

    if (statistics != NULL)
    {
    	totalVotes = statistics->getTotalVotes();

    	delete statistics;
    	statistics = NULL;
    }

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    VoteStatistic * statisticDom = Load(directories.getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM));
    VoteStatistic * statisticFlash = Load(directories.getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH));

    bool load = false;

    if (statisticDom != NULL && statisticFlash == NULL)
    {
    	logger->Debug("Load vote statistics in DOM.");
    	statistics = statisticDom;
    	deltaVotes = statistics->getTotalVotes();
    	load = true;
    }
    else if (statisticDom == NULL && statisticFlash != NULL)
    {
    	logger->Debug("Load vote statistics in Flash.");
    	statistics = statisticFlash;
    	deltaVotes = statistics->getTotalVotes();
    	load = true;
    }
    else if (statisticDom != NULL && statisticFlash != NULL)
    {
    	load = true;
    	deltaVotes = (unsigned int)abs((int)(statisticDom->getTotalVotes() - statisticFlash->getTotalVotes()));

    	if (statisticDom->getTotalVotes() > statisticFlash->getTotalVotes())
    	{
        	logger->Debug("Load vote statistics in DOM by total votes.");
    		statistics = statisticDom;
    		delete statisticFlash;
    	}
    	else if (statisticDom->getDuplicatedVotes() > statisticFlash->getDuplicatedVotes())
    	{
        	logger->Debug("Load vote statistics in DOM by duplicate votes.");
    		statistics = statisticDom;
    		delete statisticFlash;
    	}
    	else
    	{
        	logger->Debug("Load vote statistics in Flash by default.");
    		statistics = statisticFlash;
    		delete statisticDom;
    	}

    	if (totalVotes >= 0 && totalVotes != (int)statistics->getTotalVotes())
    	{
            throw Smartmatic::System::Exception::VoteException(_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorLoadStatisticVote"), N_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorLoadStatisticVote"), logger);
    	}
    }
    else
    {
    	logger->Debug("New vote statistics by default.");
    	statistics = new VoteStatistic();
    }

    return load;
}

unsigned int VoteStatisticsWrapper::getTotalVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getTotalVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getOfficialVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getOfficialVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getSimulatedVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getSimulateVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getDemoVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getDemoVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getSecurityCopyVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getSecurityCopyVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getSuperNullVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getSuperNullVotes() : 0);
}

unsigned int VoteStatisticsWrapper::getDuplicatedVotes()
{
	Glib::Mutex::Lock lock(mutex);
	return (statistics != NULL ? statistics->getDuplicatedVotes() : 0);
}

void VoteStatisticsWrapper::incrementTotalVotes()
{
	if (statistics)
    {
		statistics->setTotalVotes(statistics->getTotalVotes() + 1);
    }
}

void VoteStatisticsWrapper::incrementSuperNullVotes()
{
	if (statistics)
    {
		statistics->setSuperNullVotes(statistics->getSuperNullVotes() + 1);
		std::stringstream ss;
	    ss << "Increment super null vote to " << statistics->getSuperNullVotes();
	    logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::incrementTotalDuplicatedVotes()
{
	if (statistics)
    {
		statistics->setDuplicatedVotes(statistics->getDuplicatedVotes() + 1);
		std::stringstream ss;
		ss << "Increment duplicate vote to " << statistics->getDuplicatedVotes();
		logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::incrementOfficialVotes()
{
	if (statistics)
    {
		statistics->setOfficialVotes(statistics->getOfficialVotes() + 1);
		std::stringstream ss;
		ss << "Increment official vote to " << statistics->getOfficialVotes();
		logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::incrementDemoVotes()
{
	if (statistics)
    {
		statistics->setDemoVotes(statistics->getDemoVotes() + 1);
		std::stringstream ss;
		ss << "Increment demo vote to " << statistics->getDemoVotes();
		logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::incrementSimulateVotes()
{
	if (statistics)
    {
		statistics->setSimulateVotes(statistics->getSimulateVotes() + 1);
		std::stringstream ss;
		ss << "Increment simulate vote to " << statistics->getSimulateVotes();
		logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::incrementSecurityVotes()
{
	if (statistics)
    {
		statistics->setSecurityCopyVotes(statistics->getSecurityCopyVotes() + 1);
		std::stringstream ss;
		ss << "Increment security copy vote to " << statistics->getSecurityCopyVotes();
		logger->Debug(ss.str());
    }
}

void VoteStatisticsWrapper::Dispose ()
{
    if (statistics)
    {
    	statistics->clearAll();
    }

    voteGUUIDsRegistered.clear();
    voteCountersByCA.clear();
}

void VoteStatisticsWrapper::clearCounter(bool cleanDuplicated)
{
	if (statistics)
	{
		if (cleanDuplicated)
		{
			statistics->clearAll();
		}
		else
		{
			statistics->clearAllNotDuplicate();
		}
	}

    voteGUUIDsRegistered.clear();

    for(unsigned int j=0;j < voteCountersByCA.size();j++)
    {
        voteCountersByCA[j].clearCounter();
    }

    logger->Debug("Clear counters");
}

void VoteStatisticsWrapper::persistence()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    logger->Debug("Start persistence vote statistics file");

    VoteStatistics statistic = convertToGeneratedClass();
    std::ostringstream os;

    try
    {
        Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;

#ifdef NAMESPACE_PBREPORTS
        map[""].name = NAMESPACE_PBREPORTS;
#endif
        map[""].schema = "";

        serializeVoteStatistics(os, statistic, map);
    }
    catch (const ::xsd::cxx::tree::exception< char >& e)
    {
        std::stringstream ss;
        ss<< "FATAL - " << __func__ << e.what();
        logger->Debug(ss.str());

        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorSerializaData"),
                                                          logger);
    }
    catch (...)
    {
        std::stringstream ss;
        ss<< "FATAL - " << __func__ << __LINE__;
        logger->Debug(ss.str());
        throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorSerializaData"),
                                                          N_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorSerializaData"),
                                                          logger);
    }

    std::string data = os.str();

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getVoteStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

    logger->Debug("Success persistence vote statistics file");
}

VoteStatistic * VoteStatisticsWrapper::Load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{

	VoteStatistic * statisticTemp = NULL;

    if (Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            VoteStatistics * statistic = new VoteStatistics(*(parseVoteStatistics(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));

            statisticTemp = new VoteStatistic();

            statisticTemp->setDemoVotes(statistic->getTotalDemoVotes());
            statisticTemp->setDuplicatedVotes(statistic->getTotalDuplicatedVotes());
            statisticTemp->setOfficialVotes(statistic->getTotalOfficialVotes());
            statisticTemp->setSecurityCopyVotes(statistic->getTotalSecurityVotes());
            statisticTemp->setSuperNullVotes(statistic->getTotalSuperNullVotes());
            statisticTemp->setTotalVotes(statistic->getTotalVotes());
            statisticTemp->setSimulateVotes(statistic->getTotalSimulatedVotes() != NULL ? statistic->getTotalSimulatedVotes().get() : 0);

            delete statistic;
            statistic = NULL;

        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__ << " " << e;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorParseFile"), logger);
        }
        catch (...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.VoteStatisticsWrapper.ErrorParseFile"), logger);
        }
    }

    return statisticTemp;
}

unsigned int VoteStatisticsWrapper::getDeltaVotes()
{
	return deltaVotes;
}
