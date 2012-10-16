/**
 * @file	PrintDocumentResult.h
 *
 * @brief	Declares the print document result class.
 */

#ifndef PRINTDOCUMENTRESULT_H_
#define PRINTDOCUMENTRESULT_H_

#include <glibmm.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
		/**
		 * @class	PrintDocumentResult
		 *
		 * @brief	Print document result. 
		 *
		 * @author	Cesar.bonilla
		 * @date	4/28/2011
		 */

		class PrintDocumentResult
		{
			public:

				typedef enum PrintingResultEnum
				{
					// Cups job related error codes

					PRINTING_SERVER_ERROR,     /* Error has occurred while attempting status retrieval */
					PRINTING_NO_JOBS,          /* No print request has been made so far*/
					PRINTING_NO_PRINTER_FOUND, /* No printer was found */
					PRINTING_PENDING,          /* Job is waiting to be printed */
					PRINTING_HELD,             /* Job is waiting to be printed */
					PRINTING_PROCESSING,       /* Job is currently being printed */
					PRINTING_STOPPED,          /* Job has been stopped */
					PRINTING_CANCELED,         /* Job has been canceled */
					PRINTING_ABORTED,          /* Job has aborted due to error */
					PRINTING_COMPLETED,        /* Job has completed successfully */

					// Gtk print related error codes

					PRINTING_INTERNAL_ERROR,
					PRINTING_PREPARING,
					PRINTING_GENERATING_DATA,
					PRINTING_SENDING_DATA,
					PRINTING_NONE,

					// Device related error codes

					PRINTING_DEVICE_ERROR,     /* Hardware level error condition */

					// Document creation logic related errors

					PRINTING_UNEXPECTED_ERROR,
					PRINTING_PREPARING_ERROR,

					// Status receiving logic

					PRINTING_JOB_NOT_SENT,
					PRINTING_JOB_ABORTED_BY_SYSTEM

				} PrintingResultEnumType;

				/**
				 * @fn	PrintDocumentResult::PrintDocumentResult();
				 *
				 * @brief	Default constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				PrintDocumentResult();

				/**
				 * @fn	PrintDocumentResult::PrintDocumentResult(bool success, Glib::ustring printer_status,
				 * 		PrintingResultEnum printResult);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	success		  	true if the operation was a success, false if it failed.
				 * @param	printer_status	The printer status.
				 * @param	printResult   	The print result.
				 */

				PrintDocumentResult(bool success, Glib::ustring printer_status, PrintingResultEnum printResult);

				/**
				 * @fn	PrintDocumentResult::~PrintDocumentResult();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				~PrintDocumentResult();

				/**
				 * @fn	void PrintDocumentResult::setResult(bool wasOk, Glib::ustring printStatus,
				 * 		PrintingResultEnum printResult );
				 *
				 * @brief	Sets a result.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	wasOk	   	true if the was operation was a success, false if it failed.
				 * @param	printStatus	The print status.
				 * @param	printResult	The print result.
				 */

				void setResult(bool wasOk, Glib::ustring printStatus, PrintingResultEnum printResult );

				/**
				 * @fn	void PrintDocumentResult::getResult(bool& wasOk, Glib::ustring& printStatus,
				 * 		PrintingResultEnum& printResult );
				 *
				 * @brief	Gets a result.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param [in,out]	wasOk	   	The was ok.
				 * @param [in,out]	printStatus	The print status.
				 * @param [in,out]	printResult	The print result.
				 */

				void getResult(bool& wasOk, Glib::ustring& printStatus, PrintingResultEnum& printResult );

				/**
				 * @fn	PrintingResultEnum PrintDocumentResult::getResult(bool& wasOk,
				 * 		Glib::ustring& printStatus );
				 *
				 * @brief	Gets a result.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param [in,out]	wasOk	   	The was ok.
				 * @param [in,out]	printStatus	The print status.
				 *
				 * @return	The result.
				 */

				PrintingResultEnum getResult(bool& wasOk, Glib::ustring& printStatus );
				friend class BasePrintDocument; ///< The base print document

				bool getSuccess();
				Glib::ustring getPrinterStatusDetail();
				PrintingResultEnumType getPrintingResult();

			private:

				bool wasSuccess;	///< true if the was operation was a success, false if it failed
				Glib::ustring printerStatusDetail;  ///< The printer status detail
				PrintingResultEnumType printingResult;  ///< The printing results
			};
		}
	}
}

#endif /* PRINTDOCUMENTRESULT_H_ */
