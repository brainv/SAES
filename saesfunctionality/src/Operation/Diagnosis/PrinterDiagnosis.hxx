/*
 * PrinterDiagnosis.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef PRINTERDIAGNOSIS_HXX_
#define PRINTERDIAGNOSIS_HXX_

#include "IDiagnosis.hxx"
#include <Printing/PrintDocumentClient.h>
#include <Printing/TestPrinting.hxx>
#include <glibmm.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace Operation
		{
			namespace Diagnosis
			{
				class PrinterDiagnosis : public IDiagnosis,
					Smartmatic::SAES::Printing::PrintDocumentClient
				{
				public:
					PrinterDiagnosis(std::string data, bool checkPrinter);
					virtual ~PrinterDiagnosis();

					virtual void test();

				protected:
					bool checkStatusPrinter();
					void onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res);
					virtual void updateMessage();

				private:
					bool checkPrinter;
					std::string errorMessage;
					Smartmatic::SAES::Printing::TestPrinting * testPrinter;
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* PRINTERDIAGNOSIS_HXX_ */
