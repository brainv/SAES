/**
 * @file FlashDiagnosis.cxx
 * @brief Body class flash diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "FlashDiagnosis.hxx"
#include <Runtime/Environment/MemoryPathController.h>
#include <Operation/MachineOperationManager.hxx>
#include <System/SafeBuffer.h>
#include <System/IO/Directory.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <stdlib.h>
#include <time.h>

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
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::Log;

ISMTTLog* FlashDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis",GETTEXT_PACKAGE);

FlashDiagnosis::FlashDiagnosis(bool checkBoth)
: IDiagnosis(OperationStatus::Flash)
{
	this->checkBoth = checkBoth;
	this->errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.DiagnosticFailed");

	updateMessage();
}

FlashDiagnosis::~FlashDiagnosis()
{

}

void FlashDiagnosis::test()
{
	bool validate = false;

	if (checkBoth)
	{
		std::string domPath = MemoryPathController::getInstance()->getDomMemoryBasePath();
		std::string flashPath = MemoryPathController::getInstance()->getFlashMemoryBasePath();

		validate = getDeviceStatus(domPath) && getDeviceStatus(flashPath);
	}
	else
	{
		std::string domPath = MemoryPathController::getInstance()->getStartupMemoryBasePath();
		validate = getDeviceStatus(domPath);
	}

	setStatus(validate ? OperationStatus::Ok : OperationStatus::Error);
	MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(getType(), getStatus());

	signalEnd.emit();
}

bool FlashDiagnosis::getDeviceStatus(std::string device)
{
	bool validate = false;

	if(Directory::DirectoryExists(device))
	{
		std::string pathComplete = Path::Combine(device, "test.bin");

		unsigned char data[4000];

		srand ( time(NULL) );

		for (unsigned int i = 0;i < sizeof (data);i++)
		{
			data[i] = rand() % 256;
		}

		srand ( 1 );

		SafeBuffer bufferWrite (data, sizeof (data));
		SafeBuffer bufferRead;

		if (!File::saveBufferToFile(bufferWrite, pathComplete))
		{
			logger->Debug("Error save file in " + device);
			errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.WriteDeviceError");
		}
		else if (!File::openFileToBuffer(pathComplete, bufferRead))
		{
			logger->Debug("Error open file in " + device);
			errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.ReadDeviceError");
		}
		else if (bufferWrite.GetBase64Data() != bufferRead.GetBase64Data())
		{
			logger->Debug("Error compare data file in " + device);
			errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.DataWriteDeviceError");
		}
		else if (!File::DeleteFile(pathComplete))
		{
			logger->Debug("Error delete file in " + device);
			errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.DeleteDeviceError");
		}
		else
		{
			validate = true;
		}
	}
	else
	{
		logger->Debug("Error - device " + device + " not found");
		errorMessage = N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.DeviceNotFound");
	}

	return validate;
}

void FlashDiagnosis::updateMessage()
{
	setMessageFooter(N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.Info"));

	switch(getStatus())
	{
		case OperationStatus::NotDiagnosed:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.InitializingDiagnostic"));
			break;
		case OperationStatus::Run:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.CheckingForMediaInserted"));
			break;
		case OperationStatus::Ok:
			setMessage(N_("Smartmatic.SAES.Operation.Diagnosis.FlashDiagnosis.DiagnosticSuccessful"));
			break;
		case OperationStatus::Error:
			setMessage(errorMessage);
			break;
	}
}
