/**
 * @file StatisticManager.cxx
 * @brief Body class StatisticManager
 */
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

#include "StatisticManager.hxx"
#include <sstream>
#include <iostream>
#include <fstream>
#include <Runtime/Environment/saes-directories.h>
#include <Security/Encryption.hxx>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <System/IO/File.h>
#include <System/IO/Directory.h>
#include <System/Utils/StringUtils.hxx>

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
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Log;

ISMTTLog* StatisticManager::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.StatisticManager", GETTEXT_PACKAGE);

#define ASSISTED_ACTIVATION "AXX"
#define IMPUGNED_ACTIVATION "IXX"
#define PROXY_ACTIVATION "PXX"

StatisticManager::StatisticManager()
{

}

StatisticManager::~StatisticManager()
{
    dispose();
}

bool StatisticManager::load()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    std::string xmlFile = directories.getStatisticsFileFullPath();

    if (Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);

            Statistics * statistics = new Statistics (*(parseStatistics(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            Statistics::StatisticIterator it;

            for (it = statistics->getStatistic().begin();
                 it != statistics->getStatistic().end();
                 it++)
            {
            	StatisticWrapper * statistic = new StatisticWrapper(*it);
            	addStatistic(statistic);
            }

            loadFile = true;
            delete statistics;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__ << " " << e;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"),
                    N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"), logger);
        }
        catch(...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"),
                    N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}

void StatisticManager::persistence()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    logger->Debug("Start persistence statistic file");

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    Statistics statistics;
    Statistics::StatisticSequence seq;
    std::ostringstream os;

    std::map <std::string, StatisticWrapper*>::iterator it;

    for (it = statisticMap.begin();
         it != statisticMap.end();
         it++)
    {
        StatisticWrapper * item = (*it).second;
        seq.push_back(*item);
    }

    statistics.setStatistic(seq);

    try
    {
		Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
		map[""].name = NAMESPACE_PBREPORTS;
		map[""].schema = "";

		serializeStatistics(os,statistics, map, "UTF-8");
    }
    catch(...)
    {
    	throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"),
    	      N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.ErrorParseFile"), logger);
    }

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getStatisticsFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getStatisticsFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

    logger->Audit(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.PersistenceStatistic"));
    logger->Debug("End persistence statistic file");
}

bool StatisticManager::init (OperationStatus * operationStatus,
        AssistedActivationWrapper * assistedActivationWrapper,
        ActivatedCardStatisticsWrapper * activatedCardStatistics,
        VoteStatisticsWrapper * voteStatisticsWrapper)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    this->operationStatus = operationStatus;
    this->assistedActivationWrapper = assistedActivationWrapper;
    this->activatedCardStatistics = activatedCardStatistics;
    this->voteStatisticsWrapper = voteStatisticsWrapper;

    dispose();
    bool loadFile = load();
    getConfigStatistics();
    //getAppStatistics();
    setRequired();
    refreshAll();

    return loadFile;
}

void StatisticManager::setRequired()
{
    std::map <std::string, std::list <std::string> >::iterator it;
    std::list <std::string>::iterator itl;

    for (it = calculatedMap.begin();
         it != calculatedMap.end();
         it++)
    {
        for (itl = ((*it).second).begin();
             itl != ((*it).second).end();
             itl++)
        {
            if (statisticMap.find(*itl) != statisticMap.end())
            {
                StatisticWrapper * req = statisticMap[(*itl)];
                req->setRequired(true);
            }
        }
    }
}

void StatisticManager::refreshAll()
{
    refreshCalculated();
    //refreshAppStatistic();
    refreshConfigStatistic();
}

void StatisticManager::refreshCalculated()
{
    std::map <std::string, std::list <std::string> >::iterator it;
    std::list <std::string>::iterator itl;

    for (it = calculatedMap.begin();
         it != calculatedMap.end();
         it++)
    {
        StatisticWrapper * statistic = statisticMap[(*it).first];

       	int value = 0;

        for (itl = ((*it).second).begin();
             itl != ((*it).second).end();
             itl++)
        {
            if (statisticMap.find(*itl) != statisticMap.end())
            {
                StatisticWrapper * add = statisticMap[(*itl)];
                value += StringUtils::stringToInt(add->getValue());
            }
        }

        statistic->setValue(StringUtils::intToString(value));
    }
}

void StatisticManager::refreshAppStatistic()
{
    std::string code;
    StatisticWrapper * statistic = NULL;
    AssistedActivations::ActivationsType::ActivationSequence seq = (assistedActivationWrapper->getActivations().getActivation());

    code = ASSISTED_ACTIVATION;

    if (statisticMap.find(code) != statisticMap.end())
    {
        statistic = statisticMap[code];
        statistic->setValue(StringUtils::intToString(seq.size()));
    }

    int totalImpugned = 0;
    int totalProxy = 0;

    AssistedActivations::ActivationsType::ActivationIterator it;

    for (it = seq.begin();
         it != seq.end();
         it++)
    {
        if ((*it).getWasImpugned())
        {
            totalImpugned++;
        }

        if ((*it).getActivationMode() == ActivationMode::ASSISTED_ACTIVATION_PROXY)
        {
            totalProxy++;
        }
    }

    code = IMPUGNED_ACTIVATION;

    if (statisticMap.find(code) != statisticMap.end())
    {
        statistic = statisticMap[code];
        statistic->setValue(StringUtils::intToString(totalImpugned));
    }

    code = PROXY_ACTIVATION;

    if (statisticMap.find(code) != statisticMap.end())
    {
        statistic = statisticMap[code];
        statistic->setValue(StringUtils::intToString(totalProxy));
    }
}

void StatisticManager::refreshConfigStatistic()
{
    StatisticConfiguration::StatisticGroupsSequence & seq (
    (*(SAESConfigurationManager::Current()->getConfiguration()))->getStatisticConfiguration().getStatisticGroups());
    StatisticConfiguration::StatisticGroupsIterator its;

    for (its = seq.begin();
         its != seq.end();
         its++)
    {

        StatisticGroup * group = groupMap[(*its).getNameKey()];

        StatisticGroups::StatisticEditTypeSequence editSeq = (*its).getStatisticEditType();
        StatisticGroups::StatisticEditTypeIterator ite;

        bool edit = false;

        for (ite = editSeq.begin();
             ite != editSeq.end();
             ite++)
        {
            if ((*ite) == StatisticEditType::CONFIGURATION_ALL)
            {
                edit = true;
                break;
            }
            else if ((*ite) == StatisticEditType::CONFIGURATION_NONE)
            {
                edit = false;
                break;
            }

            switch (operationStatus->getElectionStatusWrapper()->getElectionStatus().getState())
            {
                case Status::ProcessStatus::ELECTION_STATUS_NOTINSTALLED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_NOTINSTALLED;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_NOTPOLLWORKERREGISTERED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_NOTPOLLWORKERREGISTERED;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_NOTDEMOSTRATIONVOTE:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_NOTDEMOSTRATIONVOTE;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_NOTINITIATED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_NOTINITIATED;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_INITIATED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_INITIATED;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_CLOSED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_CLOSED;
                    break;
                case Status::ProcessStatus::ELECTION_STATUS_RESULTSTRANSMITTED:
                    edit = edit || (*ite) == StatisticEditType::CONFIGURATION_RESULTSTRANSMITTED;
                    break;
            }
        }

        StatisticGroups::StatisticItemSequence & itemSeq ((*its).getStatisticItem());
        StatisticGroups::StatisticItemIterator iti;

        for (iti = itemSeq.begin();
             iti != itemSeq.end();
             iti++)
        {
            std::string code = (*iti).getCode();
            StatisticWrapper * statistic = statisticMap[code];
            statistic->setEdit(edit);
            group->setState(edit);
        }
    }
}

std::list<StatisticGroup*> StatisticManager::getStatisticGroup()
{
    return this->groupList;
}

std::list<StatisticWrapper*> StatisticManager::getAllStatistics()
{
    std::list<StatisticWrapper*> list;
    std::map<std::string, StatisticWrapper*>::iterator it;

    for (it = statisticMap.begin();
         it != statisticMap.end();
         it++)
    {
        list.push_back((*it).second);
    }

    return list;
}

void StatisticManager::addStatistic(StatisticWrapper* statistic)
{
    std::string code = statistic->getCode();

    if (statisticMap.find(code) != statisticMap.end())
    {
        statisticMap[code]->setValue(statistic->getValue());
    }
    else
    {
        statisticMap[code] = statistic;
    }
}

StatisticWrapper* StatisticManager::getStatisticByCode(std::string code)
{
    return statisticMap[code];
}

void StatisticManager::getConfigStatistics()
{
    logger->Debug("Start getter config statistics");

    StatisticConfiguration::StatisticGroupsSequence & seq (
    (*(SAESConfigurationManager::Current()->getConfiguration()))->getStatisticConfiguration().getStatisticGroups());
    StatisticConfiguration::StatisticGroupsIterator it;

    for (it = seq.begin();
         it != seq.end();
         it++)
    {
        StatisticGroup * group = new StatisticGroup();
        group->setNameKey(N_((*it).getNameKey().c_str()));
        group->setEditInfoKey(N_((*it).getEditInfoKey().c_str()));
        group->setBlockerInfoKey(N_((*it).getBlockerInfoKey().c_str()));
        group->setVerticalFilling((*it).getVerticalFilling());
        group->setPivot((*it).getPivot());

        StatisticGroups::StatisticItemSequence itemSeq = (*it).getStatisticItem();
        StatisticGroups::StatisticItemIterator iti;

        for (iti = itemSeq.begin();
             iti != itemSeq.end();
             iti++)
        {
            std::string code = (*iti).getCode();
            StatisticWrapper * statistic = NULL;

            if (statisticMap.find(code) == statisticMap.end())
            {
                statistic = new StatisticWrapper();
                statistic->setCode(code);
                statisticMap[code] = statistic;
            }
            else
            {
                statistic = statisticMap[code];
            }

            StatisticItem::AddStatisticCodeSequence addSeq = (*iti).getAddStatisticCode();
            StatisticItem::AddStatisticCodeIterator ita;
            bool calculated = false;

            for (ita = addSeq.begin();
                 ita != addSeq.end();
                 ita++)
            {
                calculated = true;
                calculatedMap[code].push_back((*ita));
            }

            std::string description = (*iti).getDescriptionKey();
            std::string name = (*iti).getNameKey();

            statistic->setDescriptionKey(description);
            statistic->setNameKey(name);
            statistic->setCalculated(calculated);
            statistic->setType((*iti).getType());
            statistic->setMax(((*iti).getMax().present() ? (*iti).getMax().get() : 250));
            statistic->setMask(((*iti).getMask().present() ? (*iti).getMask().get() : ""));
            statistic->setRegex(((*iti).getRegex().present() ? (*iti).getRegex().get() : ""));
            statistic->setMandatory(((*iti).getMandatory().present() ? (*iti).getMandatory().get() : false));
            statistic->setSize(((*iti).getWidth().present() ? (*iti).getWidth().get() : -1), ((*iti).getHeight().present() ? (*iti).getHeight().get() : -1));
            group->addStatistic(statistic);
        }

        groupList.push_back(group);
        groupMap[group->getNameKey()] = group;
    }

    logger->Debug("End getter config statistics");
}

void StatisticManager::getAppStatistics()
{
    logger->Debug("Start getter app statistics");

    StatisticGroup * group = NULL;

    group = new StatisticGroup();
    group->setNameKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.AssistedActivation"));
    group->setEditInfoKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.EditInfoAssistedActivation"));
    group->setBlockerInfoKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.BlockerInfoAssistedActivation"));
    group->setVerticalFilling(false);
    group->setPivot(2);

    StatisticWrapper * statistic = NULL;

    statistic = new StatisticWrapper();
    statistic->setCode(ASSISTED_ACTIVATION);
    statistic->setNameKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.TotalAssistedActivation"));
    addStatistic(statistic);
    group->addStatistic(statistic);

    statistic = new StatisticWrapper();
    statistic->setCode(IMPUGNED_ACTIVATION);
    statistic->setNameKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.TotalImpugnedActivation"));
    addStatistic(statistic);
    group->addStatistic(statistic);

    statistic = new StatisticWrapper();
    statistic->setCode(PROXY_ACTIVATION);
    statistic->setNameKey(N_("Smartmatic.SAES.Voting.PBReports.StatisticManager.TotalProxyActivation"));
    addStatistic(statistic);
    group->addStatistic(statistic);

    groupList.push_back(group);

    logger->Debug("End getter app statistics");
}

void StatisticManager::dispose ()
{
    std::map <std::string, StatisticWrapper *>::iterator it;

    for (it = statisticMap.begin();
         it != statisticMap.end();
         it++)
    {
        StatisticWrapper * statistic = (*it).second;
        if (statistic) delete statistic;
    }

    std::list <StatisticGroup *>::iterator itg;

    for (itg = groupList.begin();
         itg != groupList.end();
         itg++)
    {
        StatisticGroup * statisticGroup = (*itg);
        if (statisticGroup) delete statisticGroup;
    }

    groupList.clear();
    groupMap.clear();
    statisticMap.clear();
    calculatedMap.clear();
}

Statistics StatisticManager::getStatistics()
{
    Statistics statistics;
    Statistics::StatisticSequence seq;

    std::map<std::string, StatisticWrapper*>::iterator it;

    for (it = statisticMap.begin();
         it != statisticMap.end();
         it++)
    {
        StatisticWrapper st (*((*it).second));
        st.setNameKey(st.getName());
        st.setDescriptionKey(st.getDescription());
        seq.push_back(st);
    }

    statistics.setStatistic(seq);
    return statistics;
}
