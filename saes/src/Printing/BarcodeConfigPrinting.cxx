/**
 * @file BarcodeConfigPrinting.cxx
 * @brief Body class barcode config printing
 * @date 07/03/2012
 * @author Yadickson Soto
 */

#include "BarcodeConfigPrinting.hxx"
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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System::IO;

ISMTTLog* BarcodeConfigPrinting::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.BarcodeConfigPrinting",GETTEXT_PACKAGE);

BarcodeConfigPrinting::BarcodeConfigPrinting()
: BasePrintDocument(false)
{

}

BarcodeConfigPrinting::~BarcodeConfigPrinting()
{

}

void BarcodeConfigPrinting::PrintDoc()
{
	std::string pdf;

	switch(getBackendType())
	{
		case PrinterBackendType::CONFIGURATION_GTKPRINTING:
			pdf = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barcode-reader-configuration-gtk.pdf");
			break;

		case PrinterBackendType::CONFIGURATION_DIRECTPRINTING:
			pdf = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barcode-reader-configuration-direct.pdf");
			break;
	}

	LPSpooler barcodeSpooler(pdf);
	barcodeSpooler.Print();
}

void BarcodeConfigPrinting::BeginPrint()
{

}

void BarcodeConfigPrinting::EndPrint()
{

}
