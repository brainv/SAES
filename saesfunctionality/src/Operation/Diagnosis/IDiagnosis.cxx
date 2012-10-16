/**
 * @file IDiagnosis.cxx
 * @brief Body class diagnosis
 * @date 20/10/2011
 * @author Yadickson Soto
 */

#include "IDiagnosis.hxx"
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
using namespace Smartmatic::Log;

ISMTTLog* IDiagnosis::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis",GETTEXT_PACKAGE);

IDiagnosis::IDiagnosis(OperationStatus::Diagnostic type)
{
	this->valueTime = 1;
	this->type = type;
	this->mandatory = false;
	this->message = " ";
	this->messageFooter = " ";
	this->status = OperationStatus::NotDiagnosed;
}

IDiagnosis::~IDiagnosis()
{

}

OperationStatus::Diagnostic IDiagnosis::getType()
{
	return type;
}
void IDiagnosis::setMandatory(bool mandatory)
{
	this->mandatory = mandatory;
}

bool IDiagnosis::getMandatory()
{
	return mandatory;
}

void IDiagnosis::setMessage(std::string message)
{
	this->message = message;
}

std::string IDiagnosis::getMessage()
{
	return _(message.c_str());
}

void IDiagnosis::setTime(int valueTime)
{
	this->valueTime = valueTime;
}

int IDiagnosis::getTime()
{
	return valueTime;
}

void IDiagnosis::setStatus(OperationStatus::DiagStatus status)
{
	switch(type)
	{
		case OperationStatus::AlarmBox:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.AlarmBox.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.AlarmBox.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.AlarmBox.Error"));
					break;
				default:
					break;
			}

			break;

		case OperationStatus::Barcode:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Barcode.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Barcode.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Barcode.Error"));
					break;
				default:
					break;
			}

			break;

		case OperationStatus::Printer:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Printer.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Printer.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Printer.Error"));
					break;
				default:
					break;
			}

			break;

		case OperationStatus::SmartCard:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.SmartCard.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.SmartCard.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.SmartCard.Error"));
					break;
				default:
					break;
			}

			break;

		case OperationStatus::Flash:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Flash.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Flash.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.Flash.Error"));
					break;
				default:
					break;
			}

			break;

		case OperationStatus::TouchScreenCalibration:

			switch(status)
			{
				case OperationStatus::Run:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.TouchScreenCalibration.Run"));
					break;
				case OperationStatus::Ok:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.TouchScreenCalibration.Ok"));
					break;
				case OperationStatus::Error:
					logger->Audit(N_("Smartmatic.SAES.Operation.Diagnosis.IDiagnosis.TouchScreenCalibration.Error"));
					break;
				default:
					break;
			}

			break;

		default:
			break;
	}

	this->status = status;
	updateMessage();
}

OperationStatus::DiagStatus IDiagnosis::getStatus()
{
	return status;
}

sigc::signal<void> IDiagnosis::getSignalEnd()
{
	return signalEnd;
}

void IDiagnosis::setMessageFooter(std::string messageFooter)
{
	this->messageFooter = messageFooter;
}

std::string IDiagnosis::getMessageFooter()
{
	return _(messageFooter.c_str());
}
