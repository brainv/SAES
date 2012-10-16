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
#include "Voting/PBReports/incident-report-wrapper.h"
#include "System/guid-class.h"
#include <System/IO/Directory.h>
#include <System/IO/File.h>
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
using namespace Smartmatic::SAES::Security;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace std;

ISMTTLog* IncidentReportWrapper::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Voting.PBReports.IncidentReportWrapper",GETTEXT_PACKAGE);

IncidentReportWrapper::IncidentReportWrapper()
{
	incidentReports = NULL;
}

IncidentReportWrapper::~IncidentReportWrapper()
{
}

void IncidentReportWrapper::Persist()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

    Smartmatic::SAES::Voting::PBReports::NamespaceInfomap map;
    map[""].name = NAMESPACE_PBREPORTS;
    map[""].schema = "";

    std::ostringstream os;
    serializeIncidentReports(os,*incidentReports, map, "UTF-8");

    std::string data = os.str();

    std::string devicePathDom = directories.getDevicePath(BasePathType::CONFIGURATION_DOM);
    std::string devicePathFlash = directories.getDevicePath(BasePathType::CONFIGURATION_FLASH);

    std::string fileDom = directories.getIncidentReportFileFullPath(BasePathType::CONFIGURATION_DOM);
    std::string fileFlash = directories.getIncidentReportFileFullPath(BasePathType::CONFIGURATION_FLASH);

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

bool IncidentReportWrapper::Load(std::string xmlFile)
    throw (CryptoException,
           SignedException,
           XmlException)
{
    bool loadFile = false;

    if (!Smartmatic::System::IO::File::canOpenFile( xmlFile ))
    {
        incidentReports = new IncidentReports();
        Reports reports;
        incidentReports->setReports(reports);
    }
    else
    {
        try
        {
        	std::string data = Smartmatic::SAES::Security::Encryption::getInstance()->openXmlFile(xmlFile, Smartmatic::SAES::Security::Encryption::INTERNAL_FILE);
            std::istringstream istr (data);
            incidentReports = new IncidentReports(*(parseIncidentReports(istr,Smartmatic::SAES::Voting::PBReports::Flags::dont_validate)));
            loadFile = true;
        }
        catch (const ::xsd::cxx::tree::exception< char >& e)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__ << " " << e;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.IncidentReportWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.IncidentReportWrapper.ErrorParseFile"), logger);
        }
        catch (...)
        {
            std::stringstream ss;
            ss  << "FATAL - " << __func__;
            logger->Debug(ss.str());
            throw Smartmatic::System::Exception::XmlException(_("Smartmatic.SAES.Voting.PBReports.IncidentReportWrapper.ErrorParseFile"), N_("Smartmatic.SAES.Voting.PBReports.IncidentReportWrapper.ErrorParseFile"), logger);
        }
    }
    return loadFile;
}

bool IncidentReportWrapper::init ()
    throw (CryptoException,
           SignedException,
           XmlException)
{
    Dispose();
    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;
    return Load(directories.getIncidentReportFileFullPath());
}

void IncidentReportWrapper::AddReport(Report &report)
{
	GuidClass guidC = GuidClass::NewGuid();
	report.setCustom_code((std::string)guidC.ToString());
	incidentReports->getReports().getReport().push_back (report);
	return;
}

void IncidentReportWrapper::RemoveReport(std::string customCode)
{
	
	for (Reports::ReportIterator
         p (incidentReports->getReports ().getReport().begin ());
         p != incidentReports->getReports ().getReport().end ();
         ++p)
    {
       if ( customCode .compare((*p).getCustom_code())== 0 )
       {
          incidentReports->getReports ().getReport().erase(p);
		  break;
       }
    }

}

void IncidentReportWrapper::ModifyReport(Report report)
{
	
	for (Reports::ReportIterator
         p (incidentReports->getReports ().getReport().begin ());
         p != incidentReports->getReports ().getReport().end ();
         ++p)
    {
       if ( report.getCustom_code().compare((*p).getCustom_code()) == 0 )
       {
         (*p).setDescription (report.getDescription ());
         (*p).setNamesOfTechnicians (report.getNamesOfTechnicians ());
         (*p).setActivityOfTechnicians (report.getActivityOfTechnicians ());
		 (*p).setAdditionalObservations (report.getAdditionalObservations ());

		 (*p).setNotificationDate(report.getNotificationDate ());
		 (*p).setPersonalArrivalDate(report.getPersonalArrivalDate ());
		 (*p).setIncidentSolutionDate (report.getIncidentSolutionDate ());
		 (*p).setIsComplete(report.getIsComplete());
		  break;
       }
    }

}

Report IncidentReportWrapper::getReport(std::string customCode)
{
	for (Reports::ReportIterator
         p (incidentReports->getReports ().getReport().begin ());
         p != incidentReports->getReports ().getReport().end ();
         ++p)
    {
       if ( customCode.compare((*p).getCustom_code()) == 0 )
       {
          return *p;
       }
    }
	Report dummyReport;
	return dummyReport;
}

Reports IncidentReportWrapper::getReports()
{
	return incidentReports->getReports();
}

IncidentReports* IncidentReportWrapper::getIncidentReports()
{
    return incidentReports;
}

void IncidentReportWrapper::Dispose ()
{
    if (incidentReports != NULL)
    {
        delete incidentReports;
        incidentReports = NULL;
    }
}
