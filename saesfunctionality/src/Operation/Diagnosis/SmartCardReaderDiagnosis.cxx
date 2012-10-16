/**
 * @file SmartCardReaderDiagnosis.cxx
 * @brief Body class smartcard reader diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "SmartCardReaderDiagnosis.hxx"
#include <Operation/Card/CardController.hxx>
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
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;

ISMTTLog* SmartCardReaderDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.SmartCardReaderDiagnosis",GETTEXT_PACKAGE);

SmartCardReaderDiagnosis::SmartCardReaderDiagnosis()
: IDiagnosis(OperationStatus::SmartCard)
{
	updateMessage();
}

SmartCardReaderDiagnosis::~SmartCardReaderDiagnosis()
{

}

void SmartCardReaderDiagnosis::test()
{
	bool validate = CardController::getInstance()->initialize();

	setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());
	CardController::getInstance()->dispose();

	signalEnd.emit();
}

void SmartCardReaderDiagnosis::updateMessage()
{
	setMessageFooter(N_("Smartmatic.SAES.Operation.Diagnosis.SmartCardReaderDiagnosis.Info"));

	switch(getStatus())
	{
		case OperationStatus::NotDiagnosed:
		case OperationStatus::Run:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.SmartCardReaderDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.SmartCardReaderDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.SmartCardReaderDiagnosis.DiagnosticFailed"));
			break;
	}
}
