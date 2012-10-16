/*
 * QRTestPrintDocument.cpp
 *
 *  Created on: Jul 15, 2011
 *      Author: root
 */

#include <config.h>
#include <Graphics/Encoding2D/QREncoding.h>
#include <Printing/DocumentOptions.h>
#include "QRTestPrintDocument.h"
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <Printing/PrinterStatusNotifier.h>
#include <Log/SMTTLogManager.h>
#include <config.h>

#define BACKGROUND_IMAGE_PATH DATADIR"/"PACKAGE_NAME"/ui/qrbkground.bmp"

using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Graphics::Encoding2D;
using namespace Smartmatic::Log;

//============================== Life Cycle ==================================//

ISMTTLog* QRTestPrintDocument::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.QRTestPrintDocument",PACKAGE_NAME);

QRTestPrintDocument::QRTestPrintDocument (std::string title)
: BasePrintDocument (false)
, m_Title (title)
{
	PrinterStatusNotifier notifier;
	notifier.getStatusMessage();
}

QRTestPrintDocument::~QRTestPrintDocument()
{
}

//=============================== Interface ==================================//

void QRTestPrintDocument::AddTestCase (
		  int test_id_suffix
		, std::string test_id
		, Smartmatic::SAES::Printing::QRCodeContent qr
		, bool image_based
		, bool use_background)
{
	TestPrintBlockType block;

	std::stringstream info_ss;
	info_ss << std::endl;
	info_ss << "data size = " << qr.getData().GetSize () << std::endl;
	info_ss << "code version = " << qr.getVersion () << std::endl;

	switch ( qr.getCorrectionLevel() )
	{
	case QR_ECLEVEL_L:
		info_ss << "correction level = " << "L" << std::endl;
		break;
	case QR_ECLEVEL_M:
		info_ss << "correction level = " << "M" << std::endl;
		break;
	case QR_ECLEVEL_Q:
		info_ss << "correction level = " << "Q" << std::endl;
		break;
	case QR_ECLEVEL_H:
		info_ss << "correction level = " << "H" << std::endl;
		break;
	default:
		info_ss << "correction level = " << "L" << std::endl;
	}

	if ( image_based )
		info_ss << "pixel size = " << qr.getPixelSize() << std::endl;
	else
		info_ss << "pixel size = - " << std::endl;

	if ( use_background )
		info_ss << "margin size = " << qr.getMargin() << std::endl;
	else
		info_ss << "margin size = - " << std::endl;

	block.test_id = test_id;
	block.text_info = info_ss.str ();
	block.qr_content = qr;
	block.image_based = image_based;
	block.use_background = use_background;

	m_Content.insert (std::pair<int,TestPrintBlockType>(test_id_suffix,block));
}


//========================== Base Class Implementation =======================//

void QRTestPrintDocument::DrawQrCodeImage (
		  Smartmatic::SAES::Printing::QRCodeContent qr
		, bool use_back_ground )
{
	Glib::RefPtr<Gdk::Pixbuf> code_image;
	Glib::RefPtr<Gdk::Bitmap> code_bitmap;
	Glib::RefPtr<Gdk::Drawable> drawable;

	Glib::RefPtr<Gdk::Pixbuf> bgn = Gdk::Pixbuf::create_from_file (BACKGROUND_IMAGE_PATH);

	gint width, height;
	width = height = 0;

	code_bitmap = QREncoding::GenerateSymbol(
			  (guchar*) qr.getData ().GetData ()
			, qr.getData().GetSize ()
			, qr.getPixelSize()
			, qr.getMargin()
			, qr.getCorrectionLevel()
			, qr.getVersion ());

	code_bitmap->get_size (width, height);
	drawable = code_bitmap;
	code_image = Gdk::Pixbuf::create (drawable, 0, 0, width, height);

	if ( use_back_ground )
		code_image = Smartmatic::Graphics::Image::PixbufComposer::compose(bgn, code_image, qr.getPosInBackground ());

	this->DrawImage (code_image, Smartmatic::SAES::Printing::Center);
}

void QRTestPrintDocument::PrintDoc()
{
	DocumentTextOptions title_options;

	title_options.setFontSize (Biggest);
	NewTextBlock (title_options);

	this->DrawString(m_Title, true);

	for ( std::multimap <int,  TestPrintBlockType>::const_iterator it = m_Content.begin ()
			; it != m_Content.end ()
			; it++)
	{

		this->DrawString("---------------------------------------", true);
		this->DrawString(it->second.test_id, true);
		this->DrawString("---------------------------------------", true);

		Smartmatic::SAES::Printing::QRCodeContent qr_content = it->second.qr_content;

		if ( ! it->second.image_based)
			this->DrawQRCode (qr_content);
		else
			this->DrawQrCodeImage ( qr_content, it->second.use_background );

		this->DrawString(it->second.text_info, true);
		this->DrawString("---------------------------------------", true);
		this->DrawString("\n", true);
	}
}

void QRTestPrintDocument::BeginPrint()
{

}

void QRTestPrintDocument::EndPrint()
{

}
