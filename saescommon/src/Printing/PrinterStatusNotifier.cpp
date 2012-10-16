/**
 * @file PrinterStatusNotifier.cpp
 * @brief Body class printer status notifier
 * @date 19/03/2011
 * @author Marcel Cordovi
 */

#include <iostream>
#include <cups/cups.h>

#include "PrinterStatusNotifier.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <System/Runtime/ProcessLauncher.h>

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

using namespace std;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::Runtime;

ISMTTLog* PrinterStatusNotifier::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.PrinterStatusNotifier",GETTEXT_PACKAGE);


bool PrinterStatusNotifier::CheckCurrentState = true;

PrinterStatusNotifier::PrinterStatusNotifier() :
	mPhState(PSTATE_UNKNOWN)
, mStatusMessage("")
{
	Smartmatic::SAES::Common::Configuration::PrinterBackendType printerBackendType =
			((* Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter()).getPrinterBackendType();

	if( printerBackendType ==  Smartmatic::SAES::Common::Configuration::PrinterBackendType::CONFIGURATION_DIRECTPRINTING)
		externalStatusTrigger = true;
	else
		externalStatusTrigger = false;
}


PrinterStatusNotifier::~PrinterStatusNotifier()
{
	// TODO Auto-generated destructor stub
}

PrinterStatusNotifier::PhysichalStateEnumType PrinterStatusNotifier::getPrinterState(bool useCachedValue )
{
	bool skipPrint = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getSkipPrint();


	if(!skipPrint && PrinterStatusNotifier::CheckCurrentState)
	{
		mRefreshStatusMessage (useCachedValue );
	}
	else
	{
		mPhState = PSTATE_READY;
		mStatusMessage = "printer ok";
	}

	return mPhState;
}

void PrinterStatusNotifier::CheckPrinterState (bool check)
{
	Smartmatic::SAES::Common::Configuration::PrinterBackendType printerBackendType =
			((* Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter()).getPrinterBackendType();

	// Allow to be set only when GtkPrint backend is being used

	if( printerBackendType == Smartmatic::SAES::Common::Configuration::PrinterBackendType::CONFIGURATION_DIRECTPRINTING)
		PrinterStatusNotifier::CheckCurrentState = true;
	else
		PrinterStatusNotifier::CheckCurrentState = check;
}

const Glib::ustring& PrinterStatusNotifier::getStatusMessage (bool useCachedValue)
{
//	mRefreshStatusMessage (useCachedValue);
	return mStatusMessage;
}

void PrinterStatusNotifier::setExternalStatusTrigger (bool arg)
{
	externalStatusTrigger = arg;
}

int PrinterStatusNotifier::getErrorCondition () const
{
	int printer_failure_cond =
			( PSTATE_OUT_OF_PAPER | PSTATE_PROCESSING | PSTATE_PAPER_JAM
			| PSTATE_COVER_OPEN   | PSTATE_OFFLINE    | PSTATE_REJECTING_JOBS
			| PSTATE_OUT_OF_TONER | PSTATE_CANCELING  | PSTATE_CARTRIDGE_NOT_PRESENT
			| PSTATE_UNKNOWN );

	return printer_failure_cond;
}

void PrinterStatusNotifier::mRefreshStatusMessage (bool skipBlankPage)
{
	int i;
	bool paper_present = false;
	bool paper_jam = false;
	bool processing = false;
	bool online = false;
	bool rejecting = false;
	bool cover_open = false;
	bool none = false;
	bool neop = false;
	bool supply_low = false;
	bool out_of_toner = false;
	bool cartridge_not_present = false;
	bool printer_canceling = false;
	bool other = false;

	int printer_failure_cond;

	if(externalStatusTrigger && skipBlankPage == false)
	{
		logger->Debug ("Running printblank");
		runPrintBlank();
	}

	mPhState = PSTATE_UNKNOWN;
	mStatusMessage.clear();

	// Get default destination printer
	cups_dest_t *dests = NULL;
	cups_dest_t *dest = NULL;

	int ndests = cupsGetDests(&dests);

	if ( dests )
		dest = cupsGetDest(NULL, NULL, ndests, dests);

	if (dest == NULL)
	{
//		mStatusMessage.assign((const char*) cupsLastErrorString());
		mStatusMessage.assign( _("Smartmatic.SAES.Printing.PrinterStatusNotifier.ServiceFailureOnNotificationOp") );
		logger->Debug("Error - impossible to get destination printer for status notification");

		if (dests)
			cupsFreeDests(ndests, dests);

		return;
	}

	for (i=0; i<dest->num_options; i++)
	{
		if ( strcmp (dest->options[i].name, "printer-state") == 0 )
		{
			online = strcmp (dest->options[i].value, "5") != 0;

			// The IPP specification's processing state value
			// processing = strcmp (dflt_dest->options[i].value, "4") == 0;
		}
		else if ( strcmp (dest->options[i].name, "printer-state-reasons") == 0 )
		{
			paper_present = ! strstr (dest->options[i].value, "media-empty");
			paper_jam     =   strstr (dest->options[i].value, "media-jam");
			processing    =   strstr (dest->options[i].value, "processing");
			cover_open    =   strstr (dest->options[i].value, "cover-open");
			none          =   strstr (dest->options[i].value, "none");
			neop          =   strstr (dest->options[i].value, "media-low");
			out_of_toner  =   strstr (dest->options[i].value, "toner-empty-error");
			supply_low    =   strstr (dest->options[i].value, "marker-supply-low-warning");
			other         =   strstr (dest->options[i].value, "other");

			printer_canceling = strstr (dest->options[i].value, "cancel-error");

			cartridge_not_present = cartridge_not_present || strstr (dest->options[i].value, "pen-failure-error");
			cartridge_not_present = cartridge_not_present || strstr (dest->options[i].value, "cartridge-not-present-error");

			logger->Debug("printer-state-reasons : " + std::string(dest->options[i].value));
		}
		else if ( strcmp (dest->options[i].name, "printer-is-accepting-jobs") == 0 )
			rejecting = ! (strstr (dest->options[i].value, "false") == 0);
	}

	if ( ! online )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_OFFLINE));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_OFFLINE);

		cupsFreeDests(ndests, dests);
		return;
	}

	if ( ! paper_present )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_OUT_OF_PAPER));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_OUT_OF_PAPER);
	}

	if (cover_open)
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_COVER_OPEN));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_COVER_OPEN);
	}

	if ( paper_jam )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_PAPER_JAM));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_PAPER_JAM);
	}

	if ( processing )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_PROCESSING) + "\n");
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_PROCESSING);
	}

	if (rejecting)
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_REJECTING_JOBS));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_REJECTING_JOBS);
	}

	if ( neop )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_NEAR_END_OF_PAPER));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_NEAR_END_OF_PAPER);
	}

	if ( supply_low )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_SUPPLYLOW_WARN));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_SUPPLYLOW_WARN);
	}

	if ( out_of_toner )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_OUT_OF_TONER));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_OUT_OF_TONER);
	}

	if ( printer_canceling )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_CANCELING));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_CANCELING);
	}

	if ( cartridge_not_present )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_CARTRIDGE_NOT_PRESENT));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_CARTRIDGE_NOT_PRESENT);
	}

	if ( other )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_UNKNOWN));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_UNKNOWN);
	}

	printer_failure_cond = mPhState & this->getErrorCondition ();

	if ( ! printer_failure_cond )
	{
		if ( ! mStatusMessage.empty() )
			mStatusMessage.append("\n");

		mStatusMessage.append(mapStatusMessage (PSTATE_READY));
		mPhState = (PhysichalStateEnumType) (mPhState | PSTATE_READY);
	}

	if ( none )
	{

	}

	logger->Debug("Printer Status Message : " + mStatusMessage);

	cupsFreeDests(ndests, dests);
}

// TODO: Legacy. remove.
const Glib::ustring PrinterStatusNotifier::getStatusMessage (PhysichalStateEnumType state)
{
	return this->mStatusMessage;
}

const Glib::ustring PrinterStatusNotifier::getCurrentStatusMessage ()
{
	return this->mStatusMessage;
}

const Glib::ustring PrinterStatusNotifier::mapStatusMessage (PhysichalStateEnumType state)
{
	Glib::ustring message;

	switch (state)
	{
	case PSTATE_UNKNOWN:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.UnknownState");
		break;
	case PSTATE_READY:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.PrinterReady");
		break;
	case PSTATE_OUT_OF_PAPER:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.OutOfPaper");
		break;
	case PSTATE_PROCESSING:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.Processing");
		break;
	case PSTATE_PAPER_JAM:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.PaperJam");
		break;
	case PSTATE_COVER_OPEN:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.CoverOpen");
		break;
	case PSTATE_OFFLINE:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.Offline");
		break;
	case PSTATE_REJECTING_JOBS:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.RejectingPrintJobs");
		break;
	case PSTATE_NEAR_END_OF_PAPER:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.NearEndOfPaper");
		break;
	case PSTATE_SUPPLYLOW_WARN:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.TonnerLowWarning");
		break;
	case PSTATE_OUT_OF_TONER:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.OutOfTonner");
		break;
	case PSTATE_CANCELING:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.Cancel");
		break;
	case PSTATE_CARTRIDGE_NOT_PRESENT:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.CartridgeNotPresent");
		break;
	default:
		message = _("Smartmatic.SAES.Printing.PrinterStatusNotifier.UnknownStateCode");
		break;
	}

	return message;
}

void PrinterStatusNotifier::runPrintBlank()
{
	std::string script = SAESCommonConfigurationManager::Current()->getOSConfigurationFiles().getScriptRunPrintBlank();
	(void)ProcessLauncher::RunProcessThroughSystem(script);
}
