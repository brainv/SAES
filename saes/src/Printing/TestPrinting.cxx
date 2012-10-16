/**
 * @file TestPrinting.cxx
 * @brief Body class test printing
 * @date 24/10/2011
 * @author Yadickson Soto
 */

#include "TestPrinting.hxx"
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/s-a-e-s-conf-manager.h>
#include <Graphics/Encoding2D/QREncoding.h>
#include <System/SafeBuffer.h>

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Configuration;

TestPrinting::TestPrinting(std::string data)
: BasePrintDocument(false)
{
	SafeBuffer toEncode(data);
	QRCodeConfig config = SAESConfigurationManager::Current()->getQRCodeBarcodeConfig();

	int pixelSize = config.getSizeQRCode();
	int margin = config.getMarginQRCode();
	int version = config.getVersionQRCode();

	QRecLevel correctionLevel = SAESConfigurationManager::Current()->GetCorrectionModeQRCode(config.getCorrectionModeQRCode());
	Glib::RefPtr<Gdk::Bitmap> bitmap(QREncoding::GenerateSymbol((guchar*)toEncode.GetData(),toEncode.GetSize(),pixelSize,margin,correctionLevel,version));

	Glib::RefPtr<Gdk::Drawable> drwptr = bitmap;
	gint width(0);
	gint height(0);
	bitmap->get_size(width,height);

	this->pixBuff = Gdk::Pixbuf::create(drwptr,0,0,width,height);
}

TestPrinting::TestPrinting(Glib::RefPtr<Gdk::Pixbuf> pixBuff)
: BasePrintDocument(false)
{
	this->pixBuff = pixBuff;
}

TestPrinting::~TestPrinting()
{

}

void TestPrinting::PrintDoc()
{
	Glib::RefPtr<Gdk::Pixbuf> logo;

	DocumentTextOptions titleOption(Biggest, Centered, Bold);

	switch(getBackendType())
	{
		case PrinterBackendType::CONFIGURATION_GTKPRINTING:
			logo = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-test-logo-gtk.bmp"));
			break;

		case PrinterBackendType::CONFIGURATION_DIRECTPRINTING:
			logo = Gdk::Pixbuf::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/printer-test-logo-direct.bmp"));
			break;
	}

	this->NewTextBlock(titleOption);
	this->DrawString(_("Smartmatic.SAES.Printing.TestPrinting.Title"), true);
	this->DrawString("", true);
	this->DrawImage(logo, Center);
	this->NewTextBlock(titleOption);
	this->DrawString("", true);
	this->DrawImage(pixBuff, Center);
}

void TestPrinting::BeginPrint()
{

}

void TestPrinting::EndPrint()
{

}
