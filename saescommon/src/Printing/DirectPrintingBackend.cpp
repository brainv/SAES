/**
 * @file DirectPrintingBackend.cpp
 * @brief Body class direct printing backend
 * @date 06/03/2011
 * @author Freddy Gomez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "DirectPrintingBackend.h"
#include "Runtime/Environment/saes-directories.h"
#include "Printing/LPSpooler.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Graphics/Encoding2D/QREncoding.h>
#include <Graphics/Image/Compose.hxx>

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
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Configuration;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::System;
using namespace Smartmatic::Log;
using namespace Smartmatic::Graphics::Encoding2D;

ISMTTLog* DirectPrintingBackend::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.DirectPrintingBackend",GETTEXT_PACKAGE);

#define FRENCH_CODEPAGE 1;

DirectPrintingBackend::DirectPrintingBackend() :
	  currentFilename ("")
	, currentOutFileStr (NULL)
	, currentOptions ()
	, mOverallResult (false, "", PrintDocumentResult::PRINTING_NONE)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());

	// Initialize french codepage mapping

	/*iso_8859_1_2_aps_french [0xe0] = 0x40;
	iso_8859_1_2_aps_french [0xb0] = 0x5b;
	iso_8859_1_2_aps_french [0xe7] = 0x5c;
	iso_8859_1_2_aps_french [0xa7] = 0x5d;
	iso_8859_1_2_aps_french [0xe9] = 0x7b;
	iso_8859_1_2_aps_french [0xf9] = 0x7c;
	iso_8859_1_2_aps_french [0xe8] = 0x7d;
	iso_8859_1_2_aps_french [0xeb] = 0x89;

	iso_8859_1_2_aps_french [0xfc] = 0x81;
	iso_8859_1_2_aps_french [0xe2] = 0x83;
	iso_8859_1_2_aps_french [0xe4] = 0x84;
	iso_8859_1_2_aps_french [0xea] = 0x88;
	iso_8859_1_2_aps_french [0xef] = 0x8b;
	iso_8859_1_2_aps_french [0xee] = 0x8c;
	iso_8859_1_2_aps_french [0xc4] = 0x8e;
	iso_8859_1_2_aps_french [0xc9] = 0x90;
	iso_8859_1_2_aps_french [0xf4] = 0x93;
	iso_8859_1_2_aps_french [0xf6] = 0x94;
	iso_8859_1_2_aps_french [0xf2] = 0x95;
	iso_8859_1_2_aps_french [0xfb] = 0x96;
	iso_8859_1_2_aps_french [0xed] = 0xa1;
	iso_8859_1_2_aps_french [0xf3] = 0xa2;
	iso_8859_1_2_aps_french [0xfa] = 0xa3;*/


	utf8_to_aps[0xC2A0] = 0x20;
	utf8_to_aps[0xC380] = 0xB7;
	utf8_to_aps[0xC381] = 0xB5;
	utf8_to_aps[0xC382] = 0xB6;
	utf8_to_aps[0xC383] = 0xC7;
	utf8_to_aps[0xC384] = 0x8E;
	utf8_to_aps[0xC385] = 0x8F;
	utf8_to_aps[0xC386] = 0x92;
	utf8_to_aps[0xC387] = 0x87;
	utf8_to_aps[0xC388] = 0xD4;
	utf8_to_aps[0xC389] = 0x90;
	utf8_to_aps[0xC38A] = 0x90;
	utf8_to_aps[0xC38B] = 0xD3;
	utf8_to_aps[0xC38C] = 0x8D;
	utf8_to_aps[0xC38D] = 0xD6;
	utf8_to_aps[0xC38E] = 0x8B;
	utf8_to_aps[0xC38F] = 0xD8;

	utf8_to_aps[0xC390] = 0xD1;
	utf8_to_aps[0xC391] = 0xA5;
	utf8_to_aps[0xC392] = 0xE3;
	utf8_to_aps[0xC393] = 0xE0;
	utf8_to_aps[0xC394] = 0xE2;
	utf8_to_aps[0xC395] = 0xE5;
	utf8_to_aps[0xC396] = 0x99;
	utf8_to_aps[0xC397] = 0x2A;
	utf8_to_aps[0xC398] = 0x9D;
	utf8_to_aps[0xC399] = 0xEB;
	utf8_to_aps[0xC39A] = 0xE9;
	utf8_to_aps[0xC39B] = 0xEA;
	utf8_to_aps[0xC39C] = 0x9A;
	utf8_to_aps[0xC39D] = 0xED;
	utf8_to_aps[0xC39E] = 0xE8;
	utf8_to_aps[0xC39F] = 0xE1;

	utf8_to_aps[0xC3A0] = 0x85;
	utf8_to_aps[0xC3A1] = 0xA0;
	utf8_to_aps[0xC3A2] = 0x83;
	utf8_to_aps[0xC3A3] = 0xC6;
	utf8_to_aps[0xC3A4] = 0x84;
	utf8_to_aps[0xC3A5] = 0x86;
	utf8_to_aps[0xC3A6] = 0x91;
	utf8_to_aps[0xC3A7] = 0x87;
	utf8_to_aps[0xC3A8] = 0x8A;
	utf8_to_aps[0xC3A9] = 0x82;
	utf8_to_aps[0xC3AA] = 0x88;
	utf8_to_aps[0xC3AB] = 0x89;
	utf8_to_aps[0xC3AC] = 0x8D;
	utf8_to_aps[0xC3AD] = 0xA1;
	utf8_to_aps[0xC3AE] = 0xA1;
	utf8_to_aps[0xC3AF] = 0x8B;

	utf8_to_aps[0xC3B0] = 0xE4;
	utf8_to_aps[0xC3B1] = 0xA4;
	utf8_to_aps[0xC3B2] = 0x95;
	utf8_to_aps[0xC3B3] = 0xA2;
	utf8_to_aps[0xC3B4] = 0x93;
	utf8_to_aps[0xC3B5] = 0xE4;
	utf8_to_aps[0xC3B6] = 0x94;
	utf8_to_aps[0xC3B7] = 0xF6;
	utf8_to_aps[0xC3B8] = 0x9B;
	utf8_to_aps[0xC3B9] = 0x97;
	utf8_to_aps[0xC3BA] = 0xA3;
	utf8_to_aps[0xC3BB] = 0x96;
	utf8_to_aps[0xC3BC] = 0x81;
	utf8_to_aps[0xC3BD] = 0xEC;
	utf8_to_aps[0xC3BE] = 0xE7;
	utf8_to_aps[0xC3BF] = 0x98;

	deleteFiles = ((* Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter()).getDirectPrintDeleteFiles();

	CommandPrintingModeType cmd_print_mode = ((* Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter()).getCommandPrintingMode();

	switch (cmd_print_mode)
	{
	case CommandPrintingModeType::CONFIGURATION_BINARY_CMD:
	binaryOutput = true;
	break;
	case CommandPrintingModeType::CONFIGURATION_EMBEDDED_TEXT_CMD:
	binaryOutput = false;
	break;
	default:
		binaryOutput = false;
		break;
	}
}

DirectPrintingBackend::~DirectPrintingBackend()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	utf8_to_aps.clear();

	if(currentOutFileStr != NULL)
	  {
		delete(currentOutFileStr);
		currentOutFileStr = NULL;
	  }
}

void DirectPrintingBackend::Init()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	SaesDirectories directories;
	currentFilename = directories.getTemporalFileFullPath() + ".txt";

	//currentOutFile = Gio::File::create_for_path(currentFilename)->create_file();
	currentOutFileStr= new ofstream(currentFilename.c_str(),ios_base::out );

	unsigned char charCode = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getCharsetDirectPrint();

	AddNewCharSetCommand(charCode);

}

void DirectPrintingBackend::ChangeFile()
{
  std::stringstream ss;
  ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
  logger->Debug(ss.str());
	
  bool fileIsEmpty = currentOutFileStr == NULL ||  currentOutFileStr->tellp() == 0;

  if(currentOutFileStr != NULL) //flush the file content, if any
    {
      currentOutFileStr->flush();
      currentOutFileStr->close();
      delete(currentOutFileStr);
      currentOutFileStr = NULL;
    }

  if(fileIsEmpty == false)//the file has content add to the queue
    {
      filequeue.push(currentFilename);
    }
  else //just remove the file from the system
    {
      remove(currentFilename.c_str());
    }

  SaesDirectories directories;
  currentFilename = directories.getTemporalFileFullPath() + ".txt";
  //currentOutFile = Gio::File::create_for_path(currentFilename)->create_file();
  currentOutFileStr= new ofstream(currentFilename.c_str(),ios_base::out );

}

void DirectPrintingBackend::End()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	//Glib::Mutex::Lock lock(mFileNotificatinoMutex);
	LPSpooler* tmp_spool;
	bool fileIsEmpty = currentOutFileStr == NULL ||  currentOutFileStr->tellp() == 0;
	int endPadding = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getEndPaddingDirectPrint();
	CutType cutType = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getCutType();

	bool needToAddMoreDataToFile = false;

	if(endPadding >0)
		needToAddMoreDataToFile = true;

	if(cutType != CutType::CONFIGURATION_NOCUT)
	{
		needToAddMoreDataToFile = true;
	}

	//file not empty and no data to add, just add it to the queue
	if(needToAddMoreDataToFile == false && fileIsEmpty == false)
	{

		//currentOutFile->flush();
		//currentOutFile->close();
		currentOutFileStr->flush();
		currentOutFileStr->close();
		delete(currentOutFileStr);
		currentOutFileStr = NULL;
		filequeue.push(currentFilename);
	}

	//file is empty and no data to add, erase the file
	if(needToAddMoreDataToFile == false && fileIsEmpty == true)
	{
		currentOutFileStr->flush();
		currentOutFileStr->close();
		delete(currentOutFileStr);
		currentOutFileStr = NULL;
		remove(currentFilename.c_str());
	}

	//there is data to add
	if(needToAddMoreDataToFile == true)
	{
		if(currentOutFileStr == NULL)//file does not exist, create one
		{
			SaesDirectories directories;
			currentFilename = directories.getTemporalFileFullPath() + ".txt";
			//currentOutFile = Gio::File::create_for_path (currentFilename)->create_file();
			currentOutFileStr= new ofstream(currentFilename.c_str(),ios_base::out );
		}
	}


	for(int i=0; i<endPadding;i++)
	{
		this->AddFeedPaperCommand(40);
	}

	if(cutType == CutType::CONFIGURATION_CUT)
	{
		this->AddNewFullCutCommand();
	}
	else if(cutType == CutType::CONFIGURATION_PARTIALCUT)
	{
		this->AddNewPartialCutCommand();
	}

	if(needToAddMoreDataToFile == true || fileIsEmpty == false)
	{
		currentOutFileStr->flush();
		currentOutFileStr->close();
		delete(currentOutFileStr);
		currentOutFileStr = NULL;
		filequeue.push(currentFilename);
	}

	//Print the list of files
	while (!filequeue.empty())
	{
		LPSpooler::JobStateEnumType printop_res;

		std::string file = filequeue.front();
		
		std::stringstream ss;
		ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__<<" - Printing File "<<file;
		logger->Debug(ss.str());

		tmp_spool = new LPSpooler(file);
		tmp_spool->AddOption("rmtop", "True");


		printop_res = tmp_spool->Print();

		if ( printop_res != LPSpooler::LPSPOOLER_JOB_COMPLETED )
		{
			logger->Debug("Error " + tmp_spool->GetSpoolerErrorMessage (printop_res));
			mOverallResult.setResult (
					  false
					, tmp_spool->GetSpoolerErrorMessage (printop_res)
					, SpoolerResToPrintingRes (printop_res));

			delete(tmp_spool);
			break;
		}
		else
		{
			mOverallResult.setResult (
					  true
					, tmp_spool->GetSpoolerErrorMessage (printop_res)
					, SpoolerResToPrintingRes (printop_res));
		}


		delete(tmp_spool);


		if(deleteFiles)
		{
			if(remove(file.c_str()) != 0)
			{
				std::stringstream ss;
				ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__<<" Error deleting file";
				logger->Debug(ss.str());
			}
		}

		filequeue.pop();
	}
}

void DirectPrintingBackend::JobNotifListenerThreadBody()
{
	/*
	while (!mJobPool.empty())
		mAllFilesPrintedCondition.wait(mFileNotificatinoMutex);
*/
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());

	Glib::Thread::Exit();
}

void DirectPrintingBackend::onPrintJobStateChanged(LPSpooler& sender)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	//TODO:: Implement for the asynchronous case
}

void DirectPrintingBackend::UtfToPrinterCharSet (const Glib::ustring& utf8_string, std::string& decodeResult)
{
	unsigned int siz = utf8_string.bytes();
	unsigned char data[siz];


	utf8_string.copy((char*)data,siz,0);

	for(unsigned int i=0; i< siz; i++)
	{
	    if(data[i] == 0xC3 || data[i] == 0xC2)
	      {
	          i++; //goto next char
	          if(i <siz)
	          {
	              int code =  (data[i-1] << 8) |  data[i];
	              decodeResult.push_back(utf8_to_aps[code]);
	          }
	      }
	    else
	      {
	        decodeResult.push_back(data[i]);
	      }
	}
}

//TODO: Add parameters to the methods


void DirectPrintingBackend::DrawString(
		  std::list<Glib::ustring>& textContent
		, std::list<DocumentTextOptions>& textContentOptionList)
{


	std::vector<DocumentTextOptions> textOptionList(textContentOptionList.begin(),textContentOptionList.end());
	std::vector<Glib::ustring> text;
	
	std::_List_iterator<Glib::ustring> iterator = textContent.begin();
	while(iterator != textContent.end())
	{
		text.push_back(*iterator++);
	}

	if(textOptionList.size() > 1)
	{
		//columns number
		int columns = textOptionList.size();
		int rows = text.size()/columns;

		int reminder = text.size()%columns;
		for(int r=0; r<rows; r++)
		{
			for(int c=0; c<columns;c++)
			{
			    std::string decodedInner;
				 UtfToPrinterCharSet (text[(r*columns)+c], decodedInner);

				
				DrawCell(
						  textOptionList[c]
				        , decodedInner
						, columns);
			}

			AddLineFeedCommand();
		}

		//Draw incomplete row
		for(int e=0; e<reminder;e++)
		{

		    std::string decodedInner;
			UtfToPrinterCharSet (text[(rows*columns)+e], decodedInner);

		
			DrawCell(
					  textOptionList[e]
			        , decodedInner
					, columns);

		}
		//New line for the uncomplete row
		if(reminder >0)
		  AddLineFeedCommand();
	}
	else
	{
	    std::string decoded;
		//Update parameters
		UpdateParameters(textOptionList.front(),true);
		//Send text one by one

		std::_List_const_iterator<Glib::ustring> iterator = textContent.begin();
		while(iterator != textContent.end())
		{
			UtfToPrinterCharSet (*iterator++, decoded);

			//currentOutFile->write(decoded.c_str(),decoded.size() );
			currentOutFileStr->write(decoded.c_str(),decoded.size() );

		}

		AddLineFeedCommand();
	}
}

void DirectPrintingBackend::DrawCell(DocumentTextOptions& options, std::string& text, int columns)
{
	//int allowedIndent = 0;
	int counter = 0;
	std::string finalText;
	// update the options of the text
	UpdateParameters(options,false);
	//sub string to the
	int maxChars = getCharactersPerline(options.getFontSize())/columns;

	/*Glib::ustring cell;
	cell.assign(text);*/


	int identationLevel = options.getIndentationLevel();
	//add indentation

	string identationChar = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getCharIndentationDirectPrint();


	while(counter++ < identationLevel)
	{

		finalText.append(identationChar);
	}


	finalText.append(text);
	
	//trunc the string
	if(finalText.size() > static_cast<unsigned int>(maxChars))
		finalText = finalText.substr(0,maxChars);


	
	int padding = maxChars - finalText.size();
	
	string paddingChar = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getCharPaddingDirectPrint();
	counter = 0;
	while(counter++<padding)
	{

		finalText.append(paddingChar);
	}

	
	//currentOutFile->write(finalText);
	currentOutFileStr->write(finalText.c_str(),finalText.size() );
}

void DirectPrintingBackend::UpdateParameters(DocumentTextOptions& newParams, bool includeJustification)
{

	if(currentOptions.getFontSize() != newParams.getFontSize())
	{
		ChangeFontSize(newParams.getFontSize());
		currentOptions.setFontSize(newParams.getFontSize());
	}

	if(currentOptions.getJustification() != newParams.getJustification() && includeJustification)
	{
		ChangeJustification(newParams.getJustification());
		currentOptions.setJustification(newParams.getJustification());
	}
	if(currentOptions.getFontStyle() != newParams.getFontStyle())
	{
		ChangeFontStyle(newParams.getFontStyle());
		currentOptions.setFontStyle(newParams.getFontStyle());
	}
	if(currentOptions.getIndentationLevel() != newParams.getIndentationLevel())
	{
		currentOptions.setIndentationLevel(newParams.getIndentationLevel());
	}
	if(currentOptions.getLineSpacing() != newParams.getLineSpacing())
	{
		//TODO: parse this command
		//ChangeLineSpacing(newParams.getLineSpacing());
		currentOptions.setLineSpacing(newParams.getLineSpacing());
	}
}

void DirectPrintingBackend::DrawImage(Glib::RefPtr<Gdk::Pixbuf> image)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	if( currentFilename.size() >0 &&  currentOutFileStr->tellp()/*currentOutFile->query_info()->get_size() >0*/)
	{
		//push the file on the queue
		ChangeFile();
	}
	//create a file with the image and push it to the queque
	SaesDirectories directories;
	std::string imageFileName = directories.getTemporalFileFullPath()+".png" ;
	image->save(imageFileName ,"png");
	filequeue.push(imageFileName);
}

void DirectPrintingBackend::DrawQRCode (QRCodeContent& qr)
{
	if ( binaryOutput )
		DrawQRCodeBin (qr);
	else
		DrawQRCodeText (qr);
}

void DirectPrintingBackend::DrawQRCodeImage (QRCodeContent qr)
{
	Glib::RefPtr<Gdk::Pixbuf> code_image;
	Glib::RefPtr<Gdk::Bitmap> code_bitmap;
	Glib::RefPtr<Gdk::Drawable> drawable;

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

	if ( qr.getImage() )
		code_image = Smartmatic::Graphics::Image::PixbufComposer::compose(qr.getImage(), code_image, qr.getPosInBackground ());

	DrawImage (code_image);
}

void DirectPrintingBackend::DrawQRCodeText (QRCodeContent qr)
{
	std::stringstream ss;
	int correction_level = 0;

	switch ( qr.getCorrectionLevel() )
	{
	case QR_ECLEVEL_L:
		correction_level = 0;
		break;
	case QR_ECLEVEL_M:
		correction_level = 1;
		break;
	case QR_ECLEVEL_Q:
		correction_level = 2;
		break;
	case QR_ECLEVEL_H:
		correction_level = 3;
		break;
	default:
		break;
	}

	if (SAESCommonConfigurationManager::Current()->getDirectQrUseOptimization())
		ss << SAESCommonConfigurationManager::Current()->getDirectQrCommandHeader ();

	ss << "<ESC><.><"
	   << qr.getPixelSize() << "><"                       /* module size */
	   << qr.getVersion () << "><"                        /* qr version */
	   << correction_level << "><"                        /* correction level */
	   << 2 << "><"                                       /* 8 bit mode */
	   << 0 << "><"                                       /* case sensitvity */
	   << 1 << "><"                                       /* bin mode */
	   << qr.getData ().GetBase64Data ().c_str ()         /* data argument */
	   << ">";

	if (SAESCommonConfigurationManager::Current()->getDirectQrUseOptimization())
		ss << SAESCommonConfigurationManager::Current()->getDirectQrCommandFooter ();

	logger->Debug (ss.str ());

	currentOutFileStr->write( ss.str ().c_str (), ss.str ().size () );
}

void DirectPrintingBackend::DrawQRCodeBin ( QRCodeContent qr )
{
	const char* cmd_data = qr.getData().GetBase64Data().c_str();
	int cmd_length = strlen (cmd_data) + 9; // plus arguments and the trailing zero
	char cmdbuff [cmd_length];

	char ver0 = '0'
	   , ver1 = '0'
	   , correction_level
	   , mode = '2'
	   , bin_mode = '1';


	memset (cmdbuff, 0, cmd_length);

	switch ( qr.getCorrectionLevel() )
	{
	case QR_ECLEVEL_L:
		correction_level = '0';
		break;
	case QR_ECLEVEL_M:
		correction_level = '1';
		break;
	case QR_ECLEVEL_Q:
		correction_level = '2';
		break;
	case QR_ECLEVEL_H:
		correction_level = '3';
		break;
	default:
		correction_level = '0';
		break;
	}

	snprintf ( cmdbuff, cmd_length, "%c%c%c%c%c%c%c%s%c"
			, ESC
			, '.'
			, ver0
			, ver1
			, correction_level
			, mode
			, bin_mode
			, cmd_data
			, ESC);

	currentOutFileStr->write( cmdbuff, cmd_length );
}



void DirectPrintingBackend::ChangeJustification(DocumentJustifitacion justification)
{
	unsigned char code(0);
	switch(justification)
	{
	case LeftJustified:
		code = 2;
		break;
	case Centered:
		code = 0;
		break;
	case RightJustified:
		code = 1;
		break;

	}
	AddNewJustificationCommand(code);
}
void DirectPrintingBackend::ChangeFontSize(DocumentFontSize newFont)
{

	unsigned char code(0);
	switch(newFont)
	{
	case TinyFont:
	case SmallFont:
		code = 2;
		break;
	case MediumFont:
		code = 0;
		break;
	case LargeFont:
	case Biggest:
		code = 1;
		break;

	}
	AddNewFontCommand(code);
}

void DirectPrintingBackend::ChangeFontStyle(DocumentFontStyle newFontStyle)
{
	bool underlined = ((Underlined & newFontStyle) != Normal);
	AddNewTextModeCommand(underlined);

}
int DirectPrintingBackend::getCharactersPerline(DocumentFontSize fontSize)
{
	int size(64);
	switch(fontSize)
	{
	case TinyFont:
	case SmallFont:
		size = 64;
		break;
	case MediumFont:
		size = 56;
		break;
	case LargeFont:
	case Biggest:
		size = 40;
		break;
	}

	return size;
}


void DirectPrintingBackend::AddNewFontCommand(unsigned char code)
{
	char cmdbuff[32];

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>%%<%d>", code);
	else
		sprintf (cmdbuff, "%c%%<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewCharSetCommand(unsigned char code)
{
	if(code < 0)
		code = 0;
	if(code >12)
		code = 12;

	char cmdbuff[32] ;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>R<%d>", code);
	else
		sprintf(cmdbuff,"%cR<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewLineSpacingCommand(unsigned char code)
{
	char cmdbuff[32] ;
	if(code >15)
		code = 15;
	else if(code <3)
		code = 3;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>3<%d>", code);
	else
		sprintf(cmdbuff,"%c3<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}

void DirectPrintingBackend::AddNewLinePreSpacingCommand(unsigned char code)
{
	char cmdbuff[32] ;
	if(code >15)
		code = 15;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>2<%d>", code);
	else
		sprintf(cmdbuff,"%c2<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());

}
void DirectPrintingBackend::AddNewCharSpacingCommand(unsigned char code)
{
	char cmdbuff[32] ;
	if(code <1)
		code = 1;
	else if(code > 16)
		code = 16;

	if (! binaryOutput )
		sprintf(cmdbuff,"<ESC>SP<%d>", code);
	else
		sprintf(cmdbuff,"%cSP<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());

}
void DirectPrintingBackend::AddNewJustificationCommand(unsigned char code)
{
	char cmdbuff[32];

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>C<%d>", code);
	else
		sprintf(cmdbuff,"%cC<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewColumnsPerLineCommand(unsigned char code)
{
	char cmdbuff[32];
	if(code > 3)
		code = 3;
	else if (code <1)
		code = 0;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>c<%d>", code);
	else
		sprintf(cmdbuff,"%cc<%d>", ESC, code);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewTextModeCommand(unsigned char underlined)
{
	char cmdbuff[32];
	if(underlined)
		underlined=0x80;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>!<%d>", underlined);
	else
		sprintf(cmdbuff,"%c!<%d>", ESC, underlined);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewFullCutCommand()
{
	std::string cmdstr;

	if ( ! binaryOutput )
		cmdstr = "<ESC>i";
	else
	{
		char cmdbuff [32];
		memset (cmdbuff, 0, 32);

		sprintf (cmdbuff, "%ci", ESC);
		cmdstr.assign (cmdbuff);
	}

	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewPartialCutCommand()
{
	std::string cmdstr = "<ESC>m";

	if ( ! binaryOutput )
		cmdstr = "<ESC>m";
	else
	{
		char cmdbuff [32];
		memset (cmdbuff, 0, 32);

		sprintf (cmdbuff, "%cm", ESC);
		cmdstr.assign (cmdbuff);
	}

	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewPrinterSpeedCommand(unsigned short int val)
{
	char cmdbuff[32];
	unsigned char val1  = (unsigned char) (val & 0xFF);
	unsigned char val2 = (unsigned char) ((val >> 8) & 0xFF);

	if ( ! binaryOutput )
		sprintf (cmdbuff,"<GS>s<%d><%d>",val1,val2);
	else
		sprintf (cmdbuff,"%cs<%d><%d>", GS,val1,val2);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewDinamicDivisionCommand(unsigned char val)
{

	char cmdbuff[32];
	if(val < 1)
		val = 1;
	else if(val >32)
		val = 32;

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<GS>/<%d>",val);
	else
		sprintf(cmdbuff,"%c/<%d>", GS,val);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());


}
void DirectPrintingBackend::AddNewAcelerationSmoothingCommand(unsigned char val)
{
	char cmdbuff[32];

	if (! binaryOutput )
		sprintf(cmdbuff,"<GS>a<%d>",val);
	else
		sprintf(cmdbuff,"%ca<%d>", GS,val);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
void DirectPrintingBackend::AddNewPrintIntensityCommand(unsigned char val)
{
	char cmdbuff[32];

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<GS>D<%d>",val);
	else
		sprintf(cmdbuff,"%cD<%d>", GS,val);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}

void DirectPrintingBackend::AddLineFeedCommand()
{
	std::string cmdstr;// ("<LF>");

	if (! binaryOutput )
		cmdstr = "<LF>";
	else
	{
		char cmdbuff [32];
		memset (cmdbuff, 0, 32);

		sprintf (cmdbuff, "%c", LF);
		cmdstr.assign (cmdbuff);
	}

	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}
/**
 * @brief Feed paper (n dot lines) forward Paper is fed for val (val<256) dot lines (val times 0.125 mm). 
 * The print position is at the beginning of the next line.
 */
void DirectPrintingBackend::AddFeedPaperCommand(unsigned char val)
{
	char cmdbuff[32];

	if ( ! binaryOutput )
		sprintf(cmdbuff,"<ESC>J<%d>",val);
	else
		sprintf(cmdbuff,"%cJ<%d>", ESC, val);

	std::string cmdstr (cmdbuff);
	//currentOutFile->write(cmdstr);
	currentOutFileStr->write(cmdstr.c_str(),cmdstr.size());
}

void DirectPrintingBackend::setDeleteFiles(bool arg)
{
	deleteFiles = arg;
}


PrintDocumentResult::PrintingResultEnumType DirectPrintingBackend::SpoolerResToPrintingRes (
		LPSpooler::JobStateEnumType spoolerRes)
{
	switch (spoolerRes)
	{
	case LPSpooler::LPSPOOLER_DEVICE_ERROR:
		return PrintDocumentResult::PRINTING_DEVICE_ERROR;
	case LPSpooler::LPSPOOLER_SERVER_ERROR:
		return PrintDocumentResult::PRINTING_SERVER_ERROR;
	case LPSpooler::LPSPOOLER_NO_PRINTER_FOUND:
		return PrintDocumentResult::PRINTING_NO_PRINTER_FOUND;
	case LPSpooler::LPSPOOLER_NO_JOBS:
		return PrintDocumentResult::PRINTING_NO_JOBS;
	case LPSpooler::LPSPOOLER_JOB_PENDING:
		return PrintDocumentResult::PRINTING_PENDING;
	case LPSpooler::LPSPOOLER_JOB_HELD:
		return PrintDocumentResult::PRINTING_HELD;
	case LPSpooler::LPSPOOLER_JOB_PROCESSING:
		return PrintDocumentResult::PRINTING_PROCESSING;
	case LPSpooler::LPSPOOLER_JOB_STOPPED:
		return PrintDocumentResult::PRINTING_STOPPED;
	case LPSpooler::LPSPOOLER_JOB_CANCELED:
		return PrintDocumentResult::PRINTING_CANCELED;
	case LPSpooler::LPSPOOLER_JOB_ABORTED:
		return PrintDocumentResult::PRINTING_ABORTED;
	case LPSpooler::LPSPOOLER_JOB_COMPLETED:
		return PrintDocumentResult::PRINTING_COMPLETED;
	default:
		return PrintDocumentResult::PRINTING_NO_JOBS;
	}
}

PrintDocumentResult DirectPrintingBackend::getPrintResult ()
{
	std::stringstream ss;
	ss << "Status : " << (mOverallResult.getSuccess() ? "success" : "error") << " - ";
	ss << "PrinterStatusDetail : " << mOverallResult.getPrinterStatusDetail() << " - ";
	ss << "PrintingResult : " << mOverallResult.getPrintingResult();

	logger->Debug(ss.str());
	return mOverallResult;
}
