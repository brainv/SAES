/*
 * ReportPrintingController.h
 *
 *  Created on: Apr 19, 2011
 *      Author: root
 */

#ifndef REPORTPRINTINGCONTROLLER_H_
#define REPORTPRINTINGCONTROLLER_H_

#include <Configuration/s-a-e-s-conf-manager.h>
#include <Printing/LPSpooler.h>
#include <Printing/PrinterStatusNotifier.h>
#include <Configuration/SaesConfiguration-schema.hxx>
#include <glibmm.h>
#include <vector>
#include "Log/ISMTTLog.h"
#include <list>

namespace Smartmatic
{
namespace SAES
{
namespace Printing
{
/**
 * @brief	Report printing controller. 
 *
 * @author	Eduardo.campione
 * @date	28/04/2011
 */

class ReportPrintingController
{

public:

	/**
	 * @brief	Default constructor.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 */

	ReportPrintingController();

	/**
	 * @brief	Finaliser.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 */

	virtual ~ReportPrintingController();


	// SIGNAL DECLARATION

	/**
	 * @brief	Raises the report changed event.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	.
	 */

	Glib::Dispatcher& signalReportChanged () {return m_SignalPrintFile;}

	/**
	 * @brief	Raises the report print finished event.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	.
	 */

	Glib::Dispatcher& signalReportPrintFinished () {return m_SignalPrintFinished;}

	/**
	 * @brief	Raises the report print error deteced event.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	.
	 */

	Glib::Dispatcher& signalReportPrintErrorDeteced () {return m_SignalErrorDetected;}

	/**
	 * @brief	Raises the report printing started event.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	.
	 */

	Glib::Dispatcher& signalReportPrintingStarted () {return m_SignalPrintBegin;}

	// PUBLIC INTERFACE

	/**
	 * @brief method load report
	 * @date 05/04/2012
	 * @author Yadickson Soto
	 */
	void loadReports();

	/**
	 * @brief	Submit print jobs for each report specified in SAESConfiguration.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 */

	void PrintReports ();

	/**
	 * @brief	Gets the report name.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The report name.
	 */

	Glib::ustring GetReportName ();

	/**
	 * @brief	Gets the report description.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The report description.
	 */

	Glib::ustring GetReportDescription ();

	/**
	 * @brief	Gets the error message.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The error message.
	 */

	Glib::ustring GetErrorMessage ();

	/**
	 * @brief	Gets the number of copies.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The number of copies.
	 */

	int GetNumOfCopies ();

	/**
	 * @brief	Gets the number of copies printed.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The number of copies printed.
	 */

	int GetNumOfCppiesPrinted ();

	/**
	 * @brief	Gets the failed reports.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The failed reports.
	 */

	const std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile> GetFailedReports ();

	/**
	 * @brief	Gets the report list.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @return	The report list.
	 */

	const std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile>& GetReportList ();

	void setLanguages(std::list <std::string> languagesFullName);

	int getTotalDocumentsToPrint();

protected:


private:

	Smartmatic::SAES::Printing::LPSpooler m_Spooler;	///< The spooler
	Smartmatic::SAES::Printing::PrinterStatusNotifier m_StatusNotifier; ///< The printer status notifier

	std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile> m_ReportList;  ///< List of configuration reports
	std::vector< ::Smartmatic::SAES::Configuration::ConfigurationReportFile> m_FailedReports;   ///< The failed configuration reports

	Glib::Dispatcher m_SignalPrintBegin;	///< The signal print begin
	Glib::Dispatcher m_SignalPrintFinished; ///< The signal print finished
	Glib::Dispatcher m_SignalErrorDetected; ///< The signal error detected
	Glib::Dispatcher m_SignalPrintFile; ///< The signal print file

	// Signal arguments
	Glib::ustring m_ReportName; ///< Name of the report
	Glib::ustring m_ReportDescription;  ///< Report description
	Glib::ustring m_ErrorMsg;   ///< Message describing the error
	int m_NumOfCopies;  ///< Number of copies
	int m_NumPrinted;   ///< Number of printeds
	static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

	sigc::connection m_SpoolerStateConn;	///< The spooler state connection

	/**
	 * @brief	Executes the spooler state changed action.
	 *
	 * @author	Eduardo.campione
	 * @date	28/04/2011
	 *
	 * @param [in,out]	spooler	The spooler.
	 */

	void OnSpoolerStateChanged (LPSpooler& spooler);

	std::list <std::string> languagesFullName;

	int totalDocumentsToPrint;
	bool allLanguages;
};

}
}
}

#endif /* REPORTPRINTINGCONTROLLER_H_ */
