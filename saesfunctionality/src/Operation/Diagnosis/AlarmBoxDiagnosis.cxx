/**
 * @file AlarmBoxDiagnosis.cxx
 * @brief Body class alarm box diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "AlarmBoxDiagnosis.hxx"
#include <Devices/alarm-device.h>
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

using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation::Diagnosis;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;

ISMTTLog* AlarmBoxDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.AlarmBoxDiagnosis",GETTEXT_PACKAGE);

AlarmBoxDiagnosis::AlarmBoxDiagnosis()
: IDiagnosis(OperationStatus::AlarmBox)
{
	updateMessage();
}

AlarmBoxDiagnosis::~AlarmBoxDiagnosis()
{

}

void AlarmBoxDiagnosis::test()
{
	bool validate = AlarmDevice::Current()->test();
	setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());

	signalEnd.emit();
}

void AlarmBoxDiagnosis::updateMessage()
{
	setMessageFooter(N_("Smartmatic.SAES.Operation.Diagnosis.AlarmBoxDiagnosis.Info"));

	switch(getStatus())
	{
		case OperationStatus::NotDiagnosed:
		case OperationStatus::Run:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.AlarmBoxDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.AlarmBoxDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.AlarmBoxDiagnosis.DiagnosticFailed"));
			break;
	}
}
