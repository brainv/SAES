/**
 * @file BarCodeDiagnosis.cxx
 * @brief Body class barcode diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "BarCodeDiagnosis.hxx"
#include <Devices/barcode-device.h>
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

ISMTTLog* BarCodeDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis",GETTEXT_PACKAGE);

BarCodeDiagnosis::BarCodeDiagnosis(std::string command)
: IDiagnosis(OperationStatus::Barcode)
{
	this->flagEnd = false;
	this->command = command;
	this->runcommand = false;
	connSend = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &BarCodeDiagnosis::end));
	runcommand = !command.empty();
	updateMessage();
}

BarCodeDiagnosis::~BarCodeDiagnosis()
{
	flagEnd = true;
	connSend.disconnect();
	connDisconnect.disconnect();
}

void BarCodeDiagnosis::test()
{
	bool validate = BarcodeDevice::Current()->Resync();
	connDisconnect = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &BarCodeDiagnosis::disconnect));

	if (!flagEnd && validate && runcommand)
	{
		BarcodeDevice::Current()->SendConfigurationCommands(command, true, false);
	}
	else
	{
		end(validate);
	}
}

void BarCodeDiagnosis::disconnect()
{
	end(false);
}

void BarCodeDiagnosis::end(bool status)
{
	flagEnd = true;
	connSend.disconnect();
	connDisconnect.disconnect();
	setStatus(status ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());
	BarcodeDevice::Current()->Close();
	signalEnd.emit();
}

void BarCodeDiagnosis::updateMessage()
{
	setMessageFooter(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.Info"));

	switch(getStatus())
	{
		case OperationStatus::Run:
			if (runcommand)
			{
				setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.ReconfigureDevice"));
			}
			else
			{
				setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.InitializingDiagnostic"));
			}
			break;
		case OperationStatus::NotDiagnosed:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			if (runcommand)
			{
				setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.CouldNotReachBarcodeReaderDiagnosticFailed"));
			}
			else
			{
				setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.BarCodeDiagnosis.DiagnosticFailed"));
			}
			break;
	}
}
