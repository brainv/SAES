/**
 * @file HelpPrinting.cxx
 * @brief Body class help printing
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#include "HelpPrinting.hxx"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <System/IO/File.h>
#include <fstream>

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

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Log;
using namespace Smartmatic::Environment;
using namespace Smartmatic::System::IO;

ISMTTLog* HelpPrinting::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.HelpPrinting",GETTEXT_PACKAGE);

HelpPrinting::HelpPrinting(std::string file)
{
	this->file = file;
}

HelpPrinting::~HelpPrinting()
{

}

void HelpPrinting::Print()
{
	spooler.SetFileName(file);
	LPSpooler::JobStateEnumType printjob_status = spooler.Print();

	std::string msg = spooler.GetSpoolerErrorMessage (printjob_status);

    if ( printjob_status != LPSpooler::LPSPOOLER_JOB_COMPLETED )
    {
    	logger->Debug("Error detected " + msg);
        signalErrorDetected.emit ();
    }
    else
    {
    	logger->Debug("Print finish " + msg);
    	signalPrintFinished.emit();
    }
}
