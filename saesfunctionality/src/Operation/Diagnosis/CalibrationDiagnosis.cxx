/**
 * @file CalibrationDiagnosis.cxx
 * @brief Body class calibration diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "CalibrationDiagnosis.hxx"
#include <System/IO/File.h>
#include <Operation/MachineOperationManager.hxx>
#include <System/Runtime/ProcessLauncher.h>
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
using namespace Smartmatic::System::IO;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;
using namespace Smartmatic::System::Runtime;

ISMTTLog* CalibrationDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.CalibrationDiagnosis",GETTEXT_PACKAGE);

CalibrationDiagnosis::CalibrationDiagnosis(int numberPoints)
: IDiagnosis(OperationStatus::TouchScreenCalibration)
{
	this->numberPoints = numberPoints;
	updateMessage();
}

CalibrationDiagnosis::~CalibrationDiagnosis()
{

}

void CalibrationDiagnosis::test()
{
	bool validate = false;

	if (!File::canOpenFile("/live/image/osconf/penmount.dat"))
	{
		std::stringstream ss;
		ss << numberPoints;
		std::string fullCommand("gCal ");
		fullCommand.append(ss.str());
		int result = ProcessLauncher::RunProcessThroughSystem(fullCommand.c_str());
		validate = result == 0;
	}
	else
	{
		validate = true;
	}

	setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());

	signalEnd.emit();
}

void CalibrationDiagnosis::updateMessage()
{
	switch(getStatus())
	{
		case OperationStatus::NotDiagnosed:
		case OperationStatus::Run:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.CalibrationDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.CalibrationDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.CalibrationDiagnosis.DiagnosticFailed"));
			break;
	}
}
