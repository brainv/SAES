/**
 * @file BarcodePrinting.cxx
 * @brief Body class barcode printing
 * @date 24/10/2011
 * @author Yadickson Soto
 */

#include "BarcodePrinting.hxx"
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
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::System;
using namespace Smartmatic::SAES::Configuration;

BarcodePrinting::BarcodePrinting(std::string data)
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

BarcodePrinting::BarcodePrinting(Glib::RefPtr<Gdk::Pixbuf> pixBuff)
: BasePrintDocument(false)
{
	this->pixBuff = pixBuff;
}

BarcodePrinting::~BarcodePrinting()
{

}

void BarcodePrinting::PrintDoc()
{
	DocumentTextOptions titleOption(Biggest, Centered, Bold);

	this->NewTextBlock(titleOption);
	this->DrawString(_("Smartmatic.SAES.Printing.BarcodeTitle"), true);
	this->DrawString("", true);

	std::string s1 = _("Smartmatic.SAES.Printing.BarcodeInstructionLine1");
	std::string s2 = _("Smartmatic.SAES.Printing.BarcodeInstructionLine2");
	std::string s3 = _("Smartmatic.SAES.Printing.BarcodeInstructionLine3");

	DocumentTextOptions instOption(Biggest, LeftJustified, Bold);
	this->NewTextBlock(instOption);

	if(s1 != "")
		this->DrawString(s1, true);

	if(s2 != "")
		this->DrawString(s2, true);

	if(s3 != "")
		this->DrawString(s3, true);

	this->DrawString("", true);
	this->DrawString("", true);

	this->DrawImage(pixBuff,Center);

	this->NewTextBlock(titleOption);
	this->DrawString("", true);
	this->DrawString("", true);
	this->DrawString("", true);
}

void BarcodePrinting::BeginPrint()
{

}

void BarcodePrinting::EndPrint()
{

}
