/**
 * @file LPSpooler.cpp
 * @brief Body class lp spooler
 * @date 06/03/2011
 * @author Freddy Gomez, Marcel Cordoví
 */

#include <iostream>
#include <locale>
#include <string.h>
#include <glibmm/timer.h>

#include "PrinterStatusNotifier.h"
#include "LPSpooler.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"

#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

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

#define QRY_STATUS_FREQ 350000
#define MAX_TIME_ELAPSED 30000000

using namespace std;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Common::Configuration;
//using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;

//========= LIFECYCLE ===========//
ISMTTLog* LPSpooler::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.LPSpooler",GETTEXT_PACKAGE);

LPSpooler::LPSpooler()
{
	mJobId = 0;
	mSpoolerId = 0;
	mIppState = IPP_JOB_PENDING;

	mSpoolerId = 0;
}

LPSpooler::LPSpooler(std::string fileName)
{
	locale loc;
	const collate<char>& coll = use_facet<collate<char> > (loc);

	mJobId = 0;
	mIppState = IPP_JOB_PENDING;

	SetFileName(fileName);

	mSpoolerId = coll.hash(fileName.data(), fileName.data() + fileName.length());
}

LPSpooler::LPSpooler(const LPSpooler& copy)
{
	this->mJobId = copy.mJobId;
	this->mSpoolerId = copy.mSpoolerId;
	this->mIppState = copy.mIppState;
	this->mDestName.assign(copy.mDestName);
	this->mFileName.assign(copy.mFileName);
}

LPSpooler& LPSpooler::operator=(const LPSpooler& other)
{
	if (this != &other)
	{
		this->mJobId = other.mJobId;
		this->mSpoolerId = other.mSpoolerId;
		this->mIppState = other.mIppState;
		this->mDestName.assign(other.mDestName);
		this->mFileName.assign(other.mFileName);
	}

	return *this;
}

LPSpooler::~LPSpooler()
{
}


//========= PUBLIC INTERFACE ===========//

void LPSpooler::AddOption (const string& optionName, const string& optionValue)
{
	mJobOptions[optionName] = optionValue;
}

void LPSpooler::RemoveOption (const string& optionName, const string& optionValue)
{
	mJobOptions.erase (optionName);
}

void LPSpooler::ClearOptions ()
{
	mJobOptions.clear ();
}

LPSpooler::JobStateEnumType LPSpooler::PrintChain(std::queue<std::string> filequeue, bool async)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	//const char* dest_name;
	char** list_of_files;
	int i, num_options = 0, num_files = 0;
	std::string job_title ("File Chain");
	cups_option_t* options = NULL;

	ipp_status_t op_status;
	JobStateEnumType result_state;

	// Get destination printer

	//dest_name = mDestName.compare("") == 0 ? NULL : mDestName.c_str();

	cups_dest_t *dests;
	int ndests = cupsGetDests(&dests);
	cups_dest_t *dest = cupsGetDest(NULL, NULL, ndests, dests);

	if (dest == NULL)
	{
		cupsFreeDests(ndests, dests);
		return LPSPOOLER_NO_PRINTER_FOUND;
	}

	// Set print job options

	for (std::map<string, string>::iterator it = mJobOptions.begin()
			; it != mJobOptions.end()
			; it++)
	{
		num_options = cupsAddOption(it->first.c_str(), it->second.c_str(), num_options, &options);
	}

	// Generate list of files and print

	list_of_files = (char**) g_malloc (filequeue.size()*sizeof (char*));

	for (num_files = 0; ! filequeue.empty() ; num_files++)
	{
		string file_name = filequeue.front();
		list_of_files[num_files] = (char *)g_malloc (file_name.length()*sizeof(char));
		list_of_files[num_files] = strcpy (list_of_files[num_files], file_name.data());
	}

	mJobId = cupsPrintFiles(dest->name
			, num_files
			, (const char**)list_of_files
			, job_title.c_str()
			, num_options
			, options);


	// Cleanup and retrieve print operation results

	cupsFreeOptions(num_options, options);
	cupsFreeDests(ndests, dests);

	for (i=0; i<num_files; i++)
		g_free ((void *)list_of_files[i]);

	g_free (list_of_files);


	if ( cupsLastError() != IPP_OK || mJobId == 0 )
		return LPSPOOLER_SERVER_ERROR;

	result_state = mMonitorJobState ();  // wait for the device


	// Cancel any pending jobs on error condition

	if ( result_state != LPSPOOLER_JOB_COMPLETED)
	{
		op_status = cupsCancelJob2 (
				  CUPS_HTTP_DEFAULT
				, dest->name
				, CUPS_JOBID_ALL       // No jobs should remain in the printer queue
				, 1);                  // Purge all jobs from job history

		if ( op_status != IPP_OK )
			return LPSPOOLER_SERVER_ERROR;
	}

	cupsFreeOptions(num_options, options);
	cupsFreeDests(ndests, dests);

	return result_state;
}

LPSpooler::JobStateEnumType LPSpooler::Print ()
//throw (PrintOperationException)
{

	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	int num_options = 0, num_jobs = 0;

	cups_job_t* jobs;
	cups_option_t* options = NULL;
	ipp_status_t op_status;

	std::string job_title;
	size_t split_pos = 0;

	LPSpooler::JobStateEnumType result_state;

	// Get destination printer

	cups_dest_t *dests;
	int ndests = cupsGetDests(&dests);
	cups_dest_t *dest = cupsGetDest(NULL, NULL, ndests, dests);

	if (dest == NULL)
	{
		cupsFreeDests(ndests, dests);
		return LPSPOOLER_NO_PRINTER_FOUND;
	}


	// Cancel any previous jobs

	num_jobs = cupsGetJobs(&jobs, dest->name, 1, CUPS_WHICHJOBS_ALL);

	if ( num_jobs != 0 )
	{
		op_status = cupsCancelJob2 (
				  CUPS_HTTP_DEFAULT
				, dest->name
				, CUPS_JOBID_ALL       // No jobs should remain in the printer queue
				, 1);                  // Purge all jobs from job history
	}

	cupsFreeJobs(num_jobs, jobs);


	// Set print job options

	for (map<string, string>::iterator it = mJobOptions.begin()
			; it != mJobOptions.end ()
			; it++)
	{
		num_options = cupsAddOption(it->first.c_str(), it->second.c_str(), num_options, &options);
	}


	// Generate job title and print

	if ((split_pos = mFileName.find_last_of("/")) != std::string::npos)
		job_title = mFileName.substr(split_pos + 1, mFileName.length());
	else
		job_title.assign(mFileName);

	mJobId = cupsPrintFile(dest->name
			, mFileName.c_str()
			, job_title.c_str()
			, num_options
			, options);


	// Retrieve print operation results

	if ( cupsLastError() != IPP_OK || mJobId == 0 )
	{
		cupsFreeOptions(num_options, options);
		cupsFreeDests(ndests, dests);
		return LPSPOOLER_SERVER_ERROR;
	}

	result_state = mMonitorJobState (); // wait for the device


	// Cancel any remaining jobs on error condition

	if ( SAESCommonConfigurationManager::Current ()->getStatusMonitorCancel ()
			&& SAESCommonConfigurationManager::Current ()->getPrinterBackendType() ==
		            PrinterBackendType::CONFIGURATION_GTKPRINTING)

	if ( result_state != LPSPOOLER_JOB_COMPLETED
			&& SAESCommonConfigurationManager::Current ()->getStatusMonitorCancel ()
			&& SAESCommonConfigurationManager::Current ()->getPrinterBackendType ()
			== PrinterBackendType::CONFIGURATION_GTKPRINTING)
	{
		op_status = cupsCancelJob2 (
				  CUPS_HTTP_DEFAULT
				, dest->name
				, CUPS_JOBID_ALL       // No jobs should remain in the printer queue
				, 1);                  // Purge all jobs from job history

		if ( op_status != IPP_OK )
		{
			cupsFreeOptions(num_options, options);
			cupsFreeDests(ndests, dests);
			return LPSPOOLER_SERVER_ERROR;
		}
	}

	cupsFreeOptions(num_options, options);
	cupsFreeDests(ndests, dests);

	return result_state;
}

Glib::ustring LPSpooler::GetSpoolerErrorMessage (
		LPSpooler::JobStateEnumType jobState)
{

	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__<<" jobstate "<<jobState;
	logger->Debug(ss.str());
	
	switch (jobState)
	{
	case LPSpooler::LPSPOOLER_DEVICE_ERROR:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.SpoolerDeviceError");
	case LPSpooler::LPSPOOLER_SERVER_ERROR:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.SpoolerServerError");
	case LPSpooler::LPSPOOLER_NO_PRINTER_FOUND:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.SpoolerNoPrinterFound");
	case LPSpooler::LPSPOOLER_NO_JOBS:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.NoJobsSubmitted");
	case LPSpooler::LPSPOOLER_JOB_PENDING:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobPending");
	case LPSpooler::LPSPOOLER_JOB_HELD:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobHeld");
	case LPSpooler::LPSPOOLER_JOB_PROCESSING:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobProcesing");
	case LPSpooler::LPSPOOLER_JOB_STOPPED:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobStopped");
	case LPSpooler::LPSPOOLER_JOB_CANCELED:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobCanceled");
	case LPSpooler::LPSPOOLER_JOB_ABORTED:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobAborted");
	case LPSpooler::LPSPOOLER_JOB_COMPLETED:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.ReportPrintJobCompleted");
	default:
		return _("Smartmatic.SAES.Printing.ReportPrintingController.UnmanagedReportStatus");
	}

	return _("Smartmatic.SAES.Printing.ReportPrintingController.UnmanagedReportStatus");
}

void LPSpooler::CancelJobs ()
{
	int num_jobs = 0;

	cups_job_t* jobs;
	cups_dest_t* dest;
	//ipp_status_t op_status;

	// Get destination printer

	dest = cupsGetNamedDest(CUPS_HTTP_DEFAULT, NULL, NULL);

	if (dest == NULL)
		return;

	// Cancel all queued jobs

	num_jobs = cupsGetJobs(&jobs, dest->name, 1, CUPS_WHICHJOBS_ALL);

	if ( num_jobs != 0 )
	{
		(void)cupsCancelJob2 (
				  CUPS_HTTP_DEFAULT
				, dest->name
				, CUPS_JOBID_ALL       // No jobs should remain in the printer queue
				, 1);                  // Purge all jobs from job history
	}

	cupsFreeJobs(num_jobs, jobs);
}

//========= MEMBER FUNCTIONS ===========//


LPSpooler::JobStateEnumType LPSpooler::mMonitorJobState()
{

	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	PrinterStatusNotifier notifier;
	bool state_changed = false, device_error_condition = false;
	long time_elapsed = 0;

	while (true)
	{
		// return unsuccessfully on device error condition

		PrinterStatusNotifier::PhysichalStateEnumType state = notifier.getPrinterState(true);
		int error_cond = notifier.getErrorCondition ();

		device_error_condition = error_cond & (int)state;
			//(notifier.getPrinterState() & notifier.getPrinterState()) != 0;

		if (device_error_condition)
		{
			if (PrinterStatusNotifier::PSTATE_OUT_OF_PAPER & state)
			{
				logger->Debug("Device error condition: PSTATE_OUT_OF_PAPER");
			}
			if (PrinterStatusNotifier::PSTATE_PROCESSING & state)
			{
				logger->Debug("Device error condition: PSTATE_OUT_OF_PAPER");
			}
			if (PrinterStatusNotifier::PSTATE_PAPER_JAM & state)
			{
				logger->Debug("Device error condition: PSTATE_PROCESSING");
			}
			if (PrinterStatusNotifier::PSTATE_COVER_OPEN & state)
			{
				logger->Debug("Device error condition: PSTATE_COVER_OPEN");
			}
			if (PrinterStatusNotifier::PSTATE_OFFLINE & state)
			{
				logger->Debug("Device error condition: PSTATE_OFFLINE");
			}
			if (PrinterStatusNotifier::PSTATE_REJECTING_JOBS & state)
			{
				logger->Debug("Device error condition: PSTATE_REJECTING_JOBS");
			}
			if (PrinterStatusNotifier::PSTATE_OUT_OF_TONER & state)
			{
				logger->Debug("Device error condition: PSTATE_OUT_OF_TONER");
			}
			if (PrinterStatusNotifier::PSTATE_CANCELING & state)
			{
				logger->Debug("Device error condition: PSTATE_CANCELING");
			}
			if (PrinterStatusNotifier::PSTATE_CARTRIDGE_NOT_PRESENT & state)
			{
				logger->Debug("Device error condition: PSTATE_CARTRIDGE_NOT_PRESENT");
			}
			if (PrinterStatusNotifier::PSTATE_UNKNOWN & state)
			{
				logger->Debug("Device error condition: PSTATE_UNKNOWN");
			}

			m_StatusMsg = notifier.getStatusMessage(true);
			return LPSPOOLER_DEVICE_ERROR;
		}

		state_changed = mQueryJobState();

		if (state_changed)
		{
			std::stringstream ss;
			ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__<<" state "<<mIppState;
			logger->Debug(ss.str());
			
			time_elapsed = 0; // reset unchanged state time counter

			switch (mIppState)
			{
			case IPP_JOB_PENDING:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_PENDING);
				mSignalJobState.emit(LPSPOOLER_JOB_PENDING, m_StatusMsg);

				break;

			case IPP_JOB_HELD:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_HELD);

				return LPSPOOLER_JOB_HELD;

			case IPP_JOB_PROCESSING:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_PROCESSING);
				mSignalJobState.emit(LPSPOOLER_JOB_PROCESSING, m_StatusMsg);

				break;

			case IPP_JOB_STOPPED:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_STOPPED);

				return LPSPOOLER_JOB_STOPPED;

			case IPP_JOB_CANCELED:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_CANCELED);

				return LPSPOOLER_JOB_CANCELED;

			case IPP_JOB_ABORTED:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_ABORTED);

				return LPSPOOLER_JOB_ABORTED;

			case IPP_JOB_COMPLETED:

				m_StatusMsg = GetSpoolerErrorMessage (LPSPOOLER_JOB_COMPLETED);

				return LPSPOOLER_JOB_COMPLETED;
			}

		}
		else
		{
			time_elapsed += QRY_STATUS_FREQ;
		}

		Glib::usleep(QRY_STATUS_FREQ);
	}

	return LPSPOOLER_JOB_STOPPED;
}


bool LPSpooler::mQueryJobState()
{
	cups_job_t* jobs;
	const char *dest_name;
	int i, num_jobs = 0;


	dest_name = mDestName.compare("") == 0 ? NULL : mDestName.c_str();

	num_jobs = cupsGetJobs(&jobs, dest_name, 1, CUPS_WHICHJOBS_ALL);

	// Find the job managed by this instance

	for (i = 0; i < num_jobs; i++)
		if (jobs[i].id == mJobId)
			break;

	if (i == num_jobs) // job not found
	{
		cupsFreeJobs(num_jobs, jobs);
		return false;
	}

	if (mIppState != jobs[i].state)
	{
		mIppState = jobs[i].state;
		cupsFreeJobs(num_jobs, jobs);
		return true;
	}

	cupsFreeJobs(num_jobs, jobs);

	return false;
}


