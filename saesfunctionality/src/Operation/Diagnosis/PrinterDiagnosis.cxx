/**
 * @file PrinterDiagnosis.cxx
 * @brief Body class printer diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "PrinterDiagnosis.hxx"
#include <Printing/PrinterStatusNotifier.h>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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

using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;

ISMTTLog* PrinterDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.PrinterDiagnosis",GETTEXT_PACKAGE);

PrinterDiagnosis::PrinterDiagnosis(std::string data, bool checkPrinter)
: IDiagnosis(OperationStatus::Printer)
{
	this->checkPrinter = checkPrinter;

	testPrinter = NULL;
	testPrinter = new TestPrinting(data);
	testPrinter->setClient(this);

	updateMessage();
}

PrinterDiagnosis::~PrinterDiagnosis()
{
	if (testPrinter)
	{
		delete testPrinter;
		testPrinter = NULL;
	}
}

void PrinterDiagnosis::test()
{
	bool validate = false;

	if ( !checkPrinter || (checkPrinter && checkStatusPrinter()) )
	{
		testPrinter->Print();
	}
	else
	{
		setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());
		signalEnd.emit();
	}
}

void PrinterDiagnosis::onDocumentPrinted (Smartmatic::SAES::Printing::PrintDocumentResult res)
{
	PrintDocumentResult::PrintingResultEnum resultType = PrintDocumentResult::PRINTING_NONE;
	Glib::ustring msg;
	bool validate = false;
	res.getResult(validate, msg, resultType);

	errorMessage = msg;

	logger->Debug("onDocumentPrinted " + errorMessage);

	setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());
	signalEnd.emit();
}

void PrinterDiagnosis::updateMessage()
{
	setMessageFooter(N_("Smartmatic.SAES.Operation.Diagnosis.PrinterDiagnosis.Info"));

	switch(getStatus())
	{
		case OperationStatus::NotDiagnosed:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.PrinterDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Run:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.PrinterDiagnosis.SendingFileToPrint"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.PrinterDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			setMessage(errorMessage);
			break;
	}
}

bool PrinterDiagnosis::checkStatusPrinter()
{
	bool validate = false;

	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState = printNotifier.getPrinterState();

	if ( ( printerState & printNotifier.getErrorCondition () ) != 0 )
	{
		errorMessage = printNotifier.getStatusMessage (printerState);
		validate = false;
	}
	else
	{
		validate = true;
	}

	return validate;
}
