/**
 * @file ReportPrintingController.cpp
 * @brief Body class report printing controller
 * @date 19/04/2011
 * @author Rafael Ferrero
 */

#include <System/IO/Path.h>
#include "Runtime/Environment/saes-directories.h"
#include "Environment/Configurations/base-language-controller.h"
#include "ReportPrintingController.h"
#include <iostream>
#include <System/IO/File.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Voting/Election/ElectionInstalationLanguages.h>
#include <Log/SMTTLogManager.h>
#include <Configuration/saes-language-controller.h>

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

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace std;
using namespace Smartmatic::SAES::Voting::Election;

ISMTTLog* ReportPrintingController::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.ReportPrintingController",GETTEXT_PACKAGE);

//====================== Life cycle ===============================

ReportPrintingController::ReportPrintingController()
{
	allLanguages = (*(SAESCommonConfigurationManager::Current()->getConfiguration()))->getConfigurationPrinter().getGeneratePVReportInAllLanguages();
}

void ReportPrintingController::loadReports()
{
	m_ReportList.clear();

	ConfigurationReportPrinting::ReportFilesConstIterator it;
	SaesDirectories dirs;

	ConfigurationReportPrinting report_conf =
		(*SAESConfigurationManager::Current()->
			getConfiguration())->getReportPrinting ();

	ConfigurationReportPrinting::ReportFilesSequence file_queue =
		report_conf.getReportFiles ();

	for (it = file_queue.begin(); it != file_queue.end(); it++)
	{
		ConfigurationReportFile file = *it;
		file.setReportTitle(_((*it).getReportTitle().c_str()));
		file.setFileDescription(_((*it).getFileDescription().c_str()));
		m_ReportList.push_back(file);
	}
}

int ReportPrintingController::getTotalDocumentsToPrint()
{
	totalDocumentsToPrint = 0;

	std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile>::const_iterator it;
    std::list <std::string> languages;
    std::list <std::string>::iterator itl;

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

	if (allLanguages && languagesFullName.size() > 0)
    {
        languages = languagesFullName;
    }
    else if (allLanguages && languagesFullName.size() == 0)
    {
        languages = ElectionInstalationLanguages::getInstance()->getStringLanguages();
    }

	if (languages.size() == 0)
	{
		languages.push_back("");
	}

	for (it = m_ReportList.begin(); it != m_ReportList.end(); it++)
	{
		int count = 0;
		std::string report_path = Path::Combine(directories.getDocsFolderFullPath(), it->getFileName());

		bool found = false;

        for (itl = languages.begin();
             itl != languages.end();
             itl++)
        {
            std::string lang = (*itl);
            std::string file = Path::GetFullFileNameWithOutExtension(report_path) + lang + Path::GetFileExtension(report_path);
            if (!File::canOpenFile(file))continue;

            count++;
            found = true;
        }

        if (!found && File::canOpenFile(report_path))
        {
        	count++;
        }

        totalDocumentsToPrint += (count * (*it).getNumCopies());
	}

	return totalDocumentsToPrint;
}

ReportPrintingController::~ReportPrintingController()
{
	if (m_SpoolerStateConn.connected())
		m_SpoolerStateConn.disconnect();
}


//====================== Signal handling ===========================

void ReportPrintingController::OnSpoolerStateChanged (LPSpooler& spooler)
{
}


//=========================== Public operations ==============================//

void ReportPrintingController::PrintReports ()
{
	LPSpooler::JobStateEnumType printjob_status;

	PrinterStatusNotifier::PhysichalStateEnumType printer_state;
	PrinterStatusNotifier notifier;

	Glib::ustring file_name;
	Glib::ustring file_desc;
	Glib::ustring error_msg;


	m_FailedReports.clear ();
	m_NumPrinted = 0;

	std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile>::const_iterator it;
    std::list <std::string> languages;
    std::list <std::string>::iterator itl;

    Smartmatic::SAES::Runtime::Environment::SaesDirectories directories;

	for (it = m_ReportList.begin(); it != m_ReportList.end(); it++)
	{
		std::string report_path = Path::Combine(directories.getDocsFolderFullPath(), it->getFileName());

		bool found = false;
		languages.clear();

		if (allLanguages && languagesFullName.size() > 0)
        {
            languages = languagesFullName;
        }
        else if (allLanguages && languagesFullName.size() == 0)
	    {
	        languages = ElectionInstalationLanguages::getInstance()->getStringLanguages();
	    }

        for (itl = languages.begin();
             itl != languages.end();
             itl++)
        {
            std::string lang = (*itl);
            std::string file = Path::GetFullFileNameWithOutExtension(report_path) + lang + Path::GetFileExtension(report_path);
            if (!File::canOpenFile(file))continue;

            found = true;
            break;
        }

        if (!found)
        {
            languages.push_back(""); // load default file
        }

        for (itl = languages.begin();
	         itl != languages.end();
	         itl++)
	    {
	        std::string lang = (*itl);
	        std::string file = Path::GetFullFileNameWithOutExtension(report_path) + lang + Path::GetFileExtension(report_path);

	        if (!File::canOpenFile(file))continue;

	        logger->Debug("Print report file " + file);

	        m_Spooler.SetFileName (file);
            m_NumOfCopies = it->getNumCopies();

            for (int i = 0; i < m_NumOfCopies; i++)
            {
                // Check wether the printer is available

                printer_state = notifier.getPrinterState ();

                notifier.getStatusMessage ();

                if ( ( printer_state & notifier.getErrorCondition () ) != 0 )
                {
                    m_ErrorMsg =  notifier.getStatusMessage (printer_state);
                    m_SignalErrorDetected.emit ();
                    return;
                }

                // Submit the report for printing

                m_ReportName.assign (_(it->getFileName ().c_str()));
                m_ReportDescription.assign (_(it->getFileDescription ().c_str()));
                m_NumPrinted++;

                m_SignalPrintFile.emit ();

                printjob_status = m_Spooler.Print ();

                // Manage the report printing operation result

                m_Spooler.GetSpoolerErrorMessage (printjob_status);

                if ( printjob_status != LPSpooler::LPSPOOLER_JOB_COMPLETED )
                {
                    m_ErrorMsg = m_Spooler.GetSpoolerErrorMessage ();
                    m_FailedReports.push_back(*it);
                    m_SignalErrorDetected.emit ();
                    break;
                }
            }
		}
	}

	m_SignalPrintFinished.emit ();
}

void ReportPrintingController::setLanguages(std::list <std::string> languagesFullName)
{
    this->languagesFullName = languagesFullName;
}

Glib::ustring ReportPrintingController::GetReportName ()
{
	return _(m_ReportName.c_str());
}

Glib::ustring ReportPrintingController::GetReportDescription ()
{
	return _(m_ReportDescription.c_str());
}

Glib::ustring ReportPrintingController::GetErrorMessage ()
{
	return m_ErrorMsg;
}

int ReportPrintingController::GetNumOfCopies ()
{
	return m_NumOfCopies;
}

int ReportPrintingController::GetNumOfCppiesPrinted ()
{
	return m_NumPrinted;
}

const std::vector<ConfigurationReportFile> ReportPrintingController::GetFailedReports ()
{
	return m_FailedReports;
}

const std::vector<ConfigurationReportFile>& ReportPrintingController::GetReportList ()
{
	return m_ReportList;
}
