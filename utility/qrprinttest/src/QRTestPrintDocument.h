/*
 * QRTestPrintDocument.h
 *
 *  Created on: Jul 15, 2011
 *      Author: root
 */

#ifndef QRTESTPRINTDOCUMENT_H_
#define QRTESTPRINTDOCUMENT_H_


#include <list>
#include <map>
#include <Printing/BasePrintDocument.h>
#include <Printing/DocumentOptions.h>
#include <Log/ISMTTLog.h>

class QRTestPrintDocument : public Smartmatic::SAES::Printing::BasePrintDocument
{
public:

	QRTestPrintDocument(std::string title);

	virtual ~QRTestPrintDocument();


	/* Base class implementation */

	void PrintDoc();
	void BeginPrint();
	void EndPrint();


	/* Interface */

	void AddTestCase (
			  int test_id_suffix
			, std::string test_id
			, Smartmatic::SAES::Printing::QRCodeContent qr
			, bool image_based
			, bool use_background);

	void SetTitle (std::string title) { m_Title = title; }

private:

	typedef struct
	{
		std::string test_id;
		Smartmatic::SAES::Printing::QRCodeContent qr_content;
		std::string text_info;
		bool image_based;
		bool use_background;

	} TestPrintBlockType;

	Glib::ustring m_Title;
	std::multimap<int,  TestPrintBlockType> m_Content;

	/* Auxiliar */

	void DrawQrCodeImage (
			  Smartmatic::SAES::Printing::QRCodeContent qr
			, bool use_back_ground );

	static Smartmatic::Log::ISMTTLog* logger; ///< The logger
};

#endif /* QRTESTPRINTDOCUMENT_H_ */
