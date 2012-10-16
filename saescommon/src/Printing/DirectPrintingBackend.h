/**
 * @file	DirectPrintingBackend.h
 *
 * @brief	Declares the direct printing backend class.
 */

#ifndef DIRECTPRINTINGBACKEND_H_
#define DIRECTPRINTINGBACKEND_H_
#include <gtkmm.h>
#include <queue>
#include <iostream>
#include <fstream>
#include <System/SafeBuffer.h>
#include "Printing/IPrintingBackend.h"
#include "Printing/LPSpooler.h"
#include "Printing/DocumentOptions.h"
#include "Printing/PrintDocumentResult.h"

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
namespace SAES
{

namespace Printing
{
/**
 * @class	DirectPrintingBackend
 *
 * @brief	Direct printing backend. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class DirectPrintingBackend : IPrintingBackend
{
public:

	/*ASCII control codes*/
	typedef enum {
		NUL     = 0,
		SOH     = 1,
		STX     = 2,
		ETX     = 3,
		EOT     = 4,
		ENQ     = 5,
		ACK     = 6,
		BEL     = 7,
		BS      = 8,
		TAB     = 9,
		LF      = 10,
		VT      = 11,
		FF      = 12,
		CR      = 13,
		SO      = 14,
		SI      = 15,
		DLE     = 16,
		DC1     = 17,
		DC2     = 18,
		DC3     = 19,
		DC4     = 20,
		NAK     = 21,
		SYN     = 22,
		ETB     = 23,
		CAN     = 24,
		EM      = 25,
		SUB     = 26,
		ESC     = 27,
		FS      = 28,
		GS      = 29,
		RS      = 30,
		US      = 31
	} ApsControlCodeEnumType;

	typedef enum
	{
		DBCKND_IMAGE,
		DBCKND_CMD

	} QRPrintingModeEnumType;

	/**
	 * @fn	DirectPrintingBackend::DirectPrintingBackend();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	DirectPrintingBackend();

	/**
	 * @fn	virtual DirectPrintingBackend::~DirectPrintingBackend();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~DirectPrintingBackend();

	/**
	 * @fn	void DirectPrintingBackend::Init();
	 *
	 * @brief	Initialises this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void Init();

	/**
	 * @fn	void DirectPrintingBackend::End();
	 *
	 * @brief	Ends this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void End();
	//TODO: Add parameters to the methods
	//void Indent(gint levelsToIndent =1);
	//void UnIndent(gint levelsToUnIndent =1);
	//void Rotate();

	/**
	 * @fn	void DirectPrintingBackend::DrawString(std::list<Glib::ustring>& textContent,
	 * 		std::list< DocumentTextOptions>& textContentOptionList);
	 *
	 * @brief	Draw string.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	textContent			 	The text content.
	 * @param [in,out]	textContentOptionList	List of text content options.
	 */

	void DrawString(std::list<Glib::ustring>& textContent, std::list<
			DocumentTextOptions>& textContentOptionList);

	/**
	 * @fn	void DirectPrintingBackend::DrawImage(Glib::RefPtr<Gdk::Pixbuf> image);
	 *
	 * @brief	Draw image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	image	The image.
	 */

	void DrawImage(Glib::RefPtr<Gdk::Pixbuf> image);

	void DrawQRCode (QRCodeContent& qr);

	//void NewLine();


	// Access

	/**
	 * @fn	PrintDocumentResult DirectPrintingBackend::getPrintResult ()
	 *
	 * @brief	Gets the print result.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The print result.
	 */

	PrintDocumentResult getPrintResult ();


private:

	/**
	 * @fn	void DirectPrintingBackend::ChangeFile();
	 *
	 * @brief	Change file.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void ChangeFile();

	std::string currentFilename;	///< Filename of the current file
	std::ofstream* currentOutFileStr;   ///< The current out file string
	DocumentTextOptions currentOptions; ///< Options for controlling the current
	std::queue<std::string> filequeue;  ///< The filequeue

	/*std::map<int, char> iso_8859_1_2_aps_french;*/

	std::map<int, unsigned char> utf8_to_aps;   ///< The utf 8 to aps

	PrintDocumentResult mOverallResult; ///< The overall result

	bool deleteFiles;   ///< true to delete the files
	bool binaryOutput;

	/**
	 * @fn	void DirectPrintingBackend::DrawCell(DocumentTextOptions& options, std::string& text,
	 * 		int columns);
	 *
	 * @brief	Draw cell.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	options	Options for controlling the operation.
	 * @param [in,out]	text   	The text.
	 * @param	columns		   	The columns.
	 */

	void DrawCell(DocumentTextOptions& options, std::string& text,
			int columns);

	/**
	 * @fn	void DirectPrintingBackend::UpdateParameters(DocumentTextOptions& newParams,
	 * 		bool includeJustification);
	 *
	 * @brief	Updates the parameters.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	newParams   	Options for controlling the new.
	 * @param	includeJustification	true to include, false to exclude the justification.
	 */

	void UpdateParameters(DocumentTextOptions& newParams,
			bool includeJustification);

	/**
	 * @fn	int DirectPrintingBackend::getCharactersPerline(DocumentFontSize fontSize);
	 *
	 * @brief	Gets the characters perline.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	fontSize	Size of the font.
	 *
	 * @return	The characters perline.
	 */

	int getCharactersPerline(DocumentFontSize fontSize);

	/**
	 * @fn	void DirectPrintingBackend::ChangeFontSize(DocumentFontSize newFont);
	 *
	 * @brief	Change font size.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	newFont	The new font.
	 */

	void ChangeFontSize(DocumentFontSize newFont);

	/**
	 * @fn	void DirectPrintingBackend::ChangeFontStyle(DocumentFontStyle newFontStyle);
	 *
	 * @brief	Change font style.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	newFontStyle	The new font style.
	 */

	void ChangeFontStyle(DocumentFontStyle newFontStyle);

	/**
	 * @fn	void DirectPrintingBackend::ChangeJustification(DocumentJustifitacion justification);
	 *
	 * @brief	Change justification.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	justification	The justification.
	 */

	void ChangeJustification(DocumentJustifitacion justification);

	/**
	 * @fn	void DirectPrintingBackend::UtfToPrinterCharSet (const Glib::ustring& utf8_string,
	 * 		std::string& decodeResult);
	 *
	 * @brief	Utf to printer character set.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	utf8_string				The utf 8 string.
	 * @param [in,out]	decodeResult	The decode result.
	 */

	void UtfToPrinterCharSet (const Glib::ustring& utf8_string, std::string& decodeResult);

	/**
	 * @fn	void DirectPrintingBackend::AddNewFontCommand(unsigned char code);
	 *
	 * @brief	Adds a new font command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewFontCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewCharSetCommand(unsigned char code);
	 *
	 * @brief	Adds a new character set command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewCharSetCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewLineSpacingCommand(unsigned char code);
	 *
	 * @brief	Adds a new line spacing command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewLineSpacingCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewLinePreSpacingCommand(unsigned char code);
	 *
	 * @brief	Adds a new line pre spacing command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewLinePreSpacingCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewCharSpacingCommand(unsigned char code);
	 *
	 * @brief	Adds a new character spacing command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewCharSpacingCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewJustificationCommand(unsigned char code);
	 *
	 * @brief	Adds a new justification command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewJustificationCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewColumnsPerLineCommand(unsigned char code);
	 *
	 * @brief	Adds a new columns per line command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	code	The code.
	 */

	void AddNewColumnsPerLineCommand(unsigned char code);

	/**
	 * @fn	void DirectPrintingBackend::AddNewTextModeCommand(unsigned char underlined);
	 *
	 * @brief	Adds a new text mode command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	underlined	The underlined.
	 */

	void AddNewTextModeCommand(unsigned char underlined);

	/**
	 * @fn	void DirectPrintingBackend::AddNewFullCutCommand();
	 *
	 * @brief	Adds new full cut command.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void AddNewFullCutCommand();

	/**
	 * @fn	void DirectPrintingBackend::AddNewPartialCutCommand();
	 *
	 * @brief	Adds new partial cut command.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void AddNewPartialCutCommand();

	/**
	 * @fn	void DirectPrintingBackend::AddNewPrinterSpeedCommand(unsigned short int val);
	 *
	 * @brief	Adds a new printer speed command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddNewPrinterSpeedCommand(unsigned short int val);

	/**
	 * @fn	void DirectPrintingBackend::AddNewDinamicDivisionCommand(unsigned char val);
	 *
	 * @brief	Adds a new dinamic division command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddNewDinamicDivisionCommand(unsigned char val);

	/**
	 * @fn	void DirectPrintingBackend::AddNewAcelerationSmoothingCommand(unsigned char val);
	 *
	 * @brief	Adds a new aceleration smoothing command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddNewAcelerationSmoothingCommand(unsigned char val);

	/**
	 * @fn	void DirectPrintingBackend::AddNewPrintIntensityCommand(unsigned char val);
	 *
	 * @brief	Adds a new print intensity command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddNewPrintIntensityCommand(unsigned char val);

	/**
	 * @fn	void DirectPrintingBackend::AddLineFeedCommand();
	 *
	 * @brief	Adds line feed command.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void AddLineFeedCommand();

	/**
	 * @fn	void DirectPrintingBackend::AddFeedPaperCommand(unsigned char val);
	 *
	 * @brief	Adds a feed paper command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddFeedPaperCommand(unsigned char val);

	/**
	 * @fn	void DirectPrintingBackend::AddCodePageCommand(unsigned char val);
	 *
	 * @brief	Adds a code page command. 
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void AddCodePageCommand(unsigned char val);



	void DrawQRCodeImage (QRCodeContent qr);

	void DrawQRCodeText (QRCodeContent qr);

	void DrawQRCodeBin (QRCodeContent qr);




	/**
	 * @fn	void DirectPrintingBackend::JobNotifListenerThreadBody();
	 *
	 * @brief	Job notif listener thread body.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void JobNotifListenerThreadBody();

	// Signal handlers

	/**
	 * @fn	void DirectPrintingBackend::onPrintJobStateChanged(LPSpooler& sender);
	 *
	 * @brief	Executes the print job state changed action.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	sender	The sender.
	 */

	void onPrintJobStateChanged(LPSpooler& sender);

	/**
	 * @fn	void DirectPrintingBackend::setDeleteFiles(bool arg);
	 *
	 * @brief	Sets a delete files.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	arg	true to argument.
	 */

	void setDeleteFiles(bool arg);

	/**
	 * @fn	PrintDocumentResult::PrintingResultEnumType DirectPrintingBackend::SpoolerResToPrintingRes ( LPSpooler::JobStateEnumType spoolerRes);
	 *
	 * @brief	Spooler resource to printing resource.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	spoolerRes	The spooler resource.
	 *
	 * @return	.
	 */

	PrintDocumentResult::PrintingResultEnumType SpoolerResToPrintingRes (
			LPSpooler::JobStateEnumType spoolerRes);

	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/

};

}
}
}
#endif /* DIRECTPRINTINGBACKEND_H_ */
