/*
 * RsaController.cpp
 *
 *  Created on: May 26, 2011
 *      Author: mcordovi
 */

#include <iostream>
#include "RsaController.h"

#define TRACE(x) std::cout << __FILE__ << " " << __func__ << " " << __LINE__ << ": " << ( x ) << std::endl; // TODO debug, remove this line

using namespace Smartmatic::System::Security::Cryptography;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::System;

RsaController::RsaController()
:
  m_entryPassphrase (NULL)
, m_entryKeyFilePath(NULL)
, m_comboboxKeyFileFormat (NULL)
, m_buttonLoadKeyFromFile (NULL)
, m_entryModulus (NULL)
, m_entryPublicExponent (NULL)
, m_comboboxPaddingType (NULL)
, m_buttonGenerateKey (NULL)
, m_radiobuttonLoadKey (NULL)
, m_radiobuttonGenKey (NULL)
, m_labelPrivateKeyValue (NULL)
, m_labelPublicKeyValue (NULL)
, m_entrySrcFilePath (NULL)
, m_buttonBrowse (NULL)
, m_buttonOpenSrcFile (NULL)
, m_textviewCipherContent (NULL)
, m_entryResultSavePath (NULL)
, m_buttonOpenPlainTextFile (NULL)
, m_textviewPlainContent (NULL)
, m_buttonEncrypt (NULL)
, m_buttonDecrypt (NULL)
, m_buttonSign (NULL)
, m_buttonVerify (NULL)
{
	m_RsaProcessor = new RsaUtil (RsaUtil::RSAPAD_PKCS1/*, 1024, 65537*/);
}

RsaController::~RsaController()
{
	if (m_RsaProcessor)
		delete m_RsaProcessor;

//	if (m_entryPassphrase)
//		delete m_entryPassphrase;
//
//	if (m_entryKeyFilePath)
//		delete m_entryKeyFilePath;
//
//	if (m_comboboxKeyFileFormat)
//		delete m_comboboxKeyFileFormat;
//
//	if (m_buttonLoadKeyFromFile)
//		delete m_buttonLoadKeyFromFile;
//
//	if (m_entryModulus)
//		delete m_entryModulus;
//
//	if (m_entryPublicExponent)
//		delete m_entryPublicExponent;
//
//	if (m_comboboxPaddingType)
//		delete m_comboboxPaddingType;
//
//	if (m_buttonGenerateKey)
//		delete m_buttonGenerateKey;
//
//	if (m_radiobuttonLoadKey)
//		delete m_radiobuttonLoadKey;
//
//	if (m_radiobuttonGenKey)
//		delete m_radiobuttonGenKey;
//
//	if (m_labelPrivateKeyValue)
//		delete m_labelPrivateKeyValue;
//
//	if (m_labelPublicKeyValue)
//		delete m_labelPublicKeyValue;
//
//	if (m_entrySrcFilePath)
//		delete m_entrySrcFilePath;
//
//	if (m_buttonBrowse)
//		delete m_buttonBrowse;
//
//	if (m_buttonOpenSrcFile)
//		delete m_buttonOpenSrcFile;
//
//	if (m_textviewSrcContent)
//		delete m_textviewSrcContent;
//
//	if (m_entryResultSavePath)
//		delete m_entryResultSavePath;
//
//	if (m_buttonSaveReslult)
//		delete m_buttonSaveReslult;
//
//	if (m_textviewResultContent)
//		delete m_textviewResultContent;
//
//	if (m_buttonEncrypt)
//		delete m_buttonEncrypt;
//
//	if (m_buttonDecrypt)
//		delete m_buttonDecrypt;
//
//	if (m_buttonSign)
//		delete m_buttonSign;
//
//	if (m_buttonVerify)
//		delete m_buttonVerify;
}


Gtk::Fixed *RsaController::GetWidget(Glib::RefPtr<Gtk::Builder> builder)
{
	builder->get_widget ("fixedRsa",this->m_fixedRsa);


	// Key Loading

	builder->get_widget ("entryPassphrase",this->m_entryPassphrase);
	m_entryPassphrase->get_buffer ()->set_text ("69HPfDkOuRpzKOs5KhJzmsr5dRtrr0H+Vl7Amz+7G7E=");

	builder->get_widget ("entryKeyFilePath",this->m_entryKeyFilePath);

	builder->get_widget ("buttonBrowseKeyFile",this->m_buttonBrowseKeyFile);
	m_buttonBrowseKeyFile->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonBrowseKeyFile_clicked));

	builder->get_widget ("comboboxKeyFileFormat",this->m_comboboxKeyFileFormat);
	m_refFormatTreeModel = Gtk::ListStore::create (m_FmtColumns);
	m_comboboxKeyFileFormat->set_model (m_refFormatTreeModel);

	Gtk::TreeModel::Row fmt_row = *(m_refFormatTreeModel->append());
	fmt_row[m_FmtColumns.m_col_id] = 1;
	fmt_row[m_FmtColumns.m_col_name] = "Keyfile PEM";

	fmt_row = *(m_refFormatTreeModel->append());
	fmt_row[m_FmtColumns.m_col_id] = 2;
	fmt_row[m_FmtColumns.m_col_name] = "PKCS#12";

	fmt_row = *(m_refFormatTreeModel->append());
	fmt_row[m_FmtColumns.m_col_id] = 3;
	fmt_row[m_FmtColumns.m_col_name] = "X.509 inside a p12";

	fmt_row = *(m_refFormatTreeModel->append());
	fmt_row[m_FmtColumns.m_col_id] = 4;
	fmt_row[m_FmtColumns.m_col_name] = "X.509 PEM";

	fmt_row = *(m_refFormatTreeModel->append());
	fmt_row[m_FmtColumns.m_col_id] = 5;
	fmt_row[m_FmtColumns.m_col_name] = "X.509 CER";

	m_comboboxKeyFileFormat->pack_start(m_FmtColumns.m_col_id);
	m_comboboxKeyFileFormat->pack_start(m_FmtColumns.m_col_name);
	m_comboboxKeyFileFormat->set_active(0);
	m_comboboxKeyFileFormat->set_sensitive (true);


	builder->get_widget ("buttonLoadKeyFromFile",this->m_buttonLoadKeyFromFile);
	m_buttonLoadKeyFromFile->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonLoadKeyFromFile_clicked));


	builder->get_widget ("entryModulus",this->m_entryModulus);
	m_entryModulus->get_buffer ()->set_text ("1024");

	builder->get_widget ("entryPublicExponent",this->m_entryPublicExponent);
	m_entryPublicExponent->get_buffer ()->set_text ("65537");


	builder->get_widget ("comboboxPaddingType",this->m_comboboxPaddingType);
	m_refPadTreeModel = Gtk::ListStore::create (m_PadColumns);
	m_comboboxPaddingType->set_model (m_refPadTreeModel);

	Gtk::TreeModel::Row pad_row = *(m_refPadTreeModel->append());
	pad_row[m_PadColumns.m_col_id] = 1;
	pad_row[m_PadColumns.m_col_name] = "PKCS1";

	pad_row = *(m_refPadTreeModel->append());
	pad_row[m_PadColumns.m_col_id] = 2;
	pad_row[m_PadColumns.m_col_name] = "OAEP";

	pad_row = *(m_refPadTreeModel->append());
	pad_row[m_PadColumns.m_col_id] = 3;
	pad_row[m_PadColumns.m_col_name] = "SSL";

	pad_row = *(m_refPadTreeModel->append());
	pad_row[m_PadColumns.m_col_id] = 4;
	pad_row[m_PadColumns.m_col_name] = "RAW";

	m_comboboxPaddingType->pack_start (m_PadColumns.m_col_id);
	m_comboboxPaddingType->pack_start (m_PadColumns.m_col_name);
	m_comboboxPaddingType->set_active (0);
	m_comboboxPaddingType->set_sensitive (true);


	builder->get_widget ("buttonGenerateKey",this->m_buttonGenerateKey);
	m_buttonGenerateKey->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonGenerateKey_clicked));


	builder->get_widget ("radiobuttonLoadKey",this->m_radiobuttonLoadKey);
	m_buttonGenerateKey->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_radiobuttonLoadKey_clicked));

	builder->get_widget ("radiobuttonGenKey",this->m_radiobuttonGenKey);
	//	m_radiobuttonGenKey->set_group (m_radiobuttonLoadKey->get_group ());
//	m_buttonGenerateKey->signal_clicked ().connect (sigc::mem_fun (*this
//			, &RsaController::on_radiobuttonGenerateKey_clicked));



	// Key Display

	builder->get_widget ("labelPrivateKeyValue",this->m_labelPrivateKeyValue);
	builder->get_widget ("labelPublicKeyValue",this->m_labelPublicKeyValue);

	m_labelPublicKeyValue->set_visible (false);
	m_labelPrivateKeyValue->set_visible (false);



	// Operation display

	builder->get_widget ("entrySrcFilePath",this->m_entrySrcFilePath);
	m_entrySrcFilePath->get_buffer ()->set_text ("/home/smartmatic/keys/data.txt.crypt");

	builder->get_widget ("buttonBrowse",this->m_buttonBrowse);
	m_buttonBrowse->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonBrowse_clicked));

	builder->get_widget ("buttonOpenSrcFile",this->m_buttonOpenSrcFile);
	m_buttonOpenSrcFile->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonOpenSrcFile_clicked));

	builder->get_widget ("textviewCipherContent",this->m_textviewCipherContent);
	m_textviewCipherContent->set_right_margin (300);
	m_textviewCipherContent->set_wrap_mode (Gtk::WRAP_CHAR);

	builder->get_widget ("entryResultSavePath",this->m_entryResultSavePath);

	builder->get_widget ("buttonBrowsePlainTextFile",this->m_buttonBrowsePlainTextFile);
	m_buttonBrowsePlainTextFile->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonBrowsePlainTextFile_clicked));

	builder->get_widget ("buttonOpenPlainTextFile",this->m_buttonOpenPlainTextFile);
	m_buttonOpenPlainTextFile->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonOpenPlainTextFile_clicked));


	builder->get_widget ("textviewPlainContent",this->m_textviewPlainContent);
	m_textviewPlainContent->set_right_margin (300);
	m_textviewPlainContent->set_wrap_mode (Gtk::WRAP_CHAR);
	m_textviewPlainContent->get_buffer ()->set_text ("plain text");


	// RSA Operation buttons

	builder->get_widget ("buttonEncrypt ",this->m_buttonEncrypt); // Anjuta glade editor won't let us to remove the space after the button name
	m_buttonEncrypt->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonEncrypt_clicked));

	builder->get_widget ("buttonDecrypt ",this->m_buttonDecrypt);
	m_buttonDecrypt->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonDecrypt_clicked));

	builder->get_widget ("buttonSign",this->m_buttonSign);
	m_buttonSign->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonSign_clicked));

	builder->get_widget ("buttonVerify",this->m_buttonVerify);
	m_buttonVerify->signal_clicked ().connect (sigc::mem_fun (*this
			, &RsaController::on_buttonVerify_clicked));


	// Finally

	m_fixedRsa->set_visible ();

	return m_fixedRsa;
}




void RsaController::SetWindow(Gtk::Window *parentWindow)
{
	this->window = parentWindow;
}



//============================================================================//
//============================== Event handling ==============================//
//============================================================================//


void RsaController::on_buttonEncrypt_clicked()
{
	Glib::ustring content;
	unsigned char *data;
	int data_len;

	content = m_textviewPlainContent->get_buffer ()->get_text (true);

	data = (unsigned char*)content.data ();
	data_len = content.bytes ();

	try
	{
		m_CipherText = m_RsaProcessor->PublicEncrypt (data, data_len);
		m_textviewCipherContent->get_buffer ()->set_text (m_CipherText.GetBase64Data ());
	}
	catch (const RSAException& ex)
	{
		mShowRsaDialog (ex.what (), Gtk::MESSAGE_ERROR);
	}
}

void RsaController::on_buttonDecrypt_clicked()
{
	Glib::ustring result;

	try{
		m_PlainText = m_RsaProcessor->PrivateDecrypt (m_CipherText);

		Glib::ustring recov_text;
		recov_text.assign ((const char *)m_PlainText.GetData (), m_PlainText.GetSize ());

		result.append ("====== Recovered plain text ======\n");
		result.append (recov_text);
		result.append ("\n=============================");

		m_textviewPlainContent->get_buffer ()->set_text (result);
	}
	catch (const RSAException& ex)
	{
		mShowRsaDialog (ex.what (), Gtk::MESSAGE_ERROR);
	}
}

void RsaController::on_buttonSign_clicked()
{
	Glib::ustring content;
	unsigned char *data;
	int data_len;

	content = m_textviewPlainContent->get_buffer ()->get_text (true);

	data = (unsigned char*)content.data ();
	data_len = content.bytes ();

	try
	{
		m_CipherText = m_RsaProcessor->PrivateEncrypt (data, data_len);
		m_textviewCipherContent->get_buffer ()->set_text (m_CipherText.GetBase64Data ());
	}
	catch (const RSAException& ex)
	{
		mShowRsaDialog (ex.what (), Gtk::MESSAGE_ERROR);
	}
}

void RsaController::on_buttonVerify_clicked()
{
	Glib::ustring result;

	try
	{
		m_PlainText = m_RsaProcessor->PublicDecrypt (m_CipherText);

		Glib::ustring recov_text;
		recov_text.assign ((const char *)m_PlainText.GetData (), m_PlainText.GetSize ());

		result.append ("====== Recovered plain text ======\n");
		result.append (recov_text);
		result.append ("\n=============================");

		m_textviewPlainContent->get_buffer ()->set_text (result);
	}
	catch (const RSAException& ex)
	{
		mShowRsaDialog (ex.what (), Gtk::MESSAGE_ERROR);
	}
}



void RsaController::on_buttonLoadKeyFromFile_clicked()
{
	Glib::ustring srcdata_path;
	int id = 0;

	Gtk::TreeModel::iterator iter = m_comboboxKeyFileFormat->get_active();

	if(iter)
		id = (*iter)[m_FmtColumns.m_col_id];

	try
	{
		srcdata_path = m_entryKeyFilePath->get_buffer ()->get_text ();

		std::string path = srcdata_path;
		std::string pass = m_entryPassphrase->get_buffer ()->get_text ();
		switch (id)
		{
		case 1:
			m_RsaProcessor->SetPublicKey_FromCert(srcdata_path,m_entryPassphrase->get_buffer ()->get_text (),CertUtil::CertFormat_PEMRSA);
			break;
		case 2:

			m_RsaProcessor->SetPrivateKey_PKCS12( path, pass); //OK
			break;
		case 3:
			m_RsaProcessor->SetPublicKey_FromCert(srcdata_path,m_entryPassphrase->get_buffer ()->get_text (),CertUtil::CertFormat_PKCS12);
			break;
		case 4:
			m_RsaProcessor->SetPublicKey_FromCert(srcdata_path, "no password", CertUtil::CertFormat_PEM);          // OK
			break;
		case 5:
			m_RsaProcessor->SetPublicKey_FromCert(srcdata_path, "no password", CertUtil::CertFormat_DER);          // OK// OK
			break;
		}

		if ( m_RsaProcessor->IsValidPublicKey () )
			mShowRsaDialog ("Loaded key is public", Gtk::MESSAGE_INFO);
		else if ( m_RsaProcessor->IsValidPrivateKey () )
			mShowRsaDialog ("Loaded key is private", Gtk::MESSAGE_INFO);
		else
			mShowRsaDialog ("Loading an invalid key", Gtk::MESSAGE_WARNING);

	}
	catch (const RSAException& ex)
	{
		mShowRsaDialog (ex.what (), Gtk::MESSAGE_ERROR);
	}
	catch (const std::exception& e)
	{
		mShowRsaDialog (e.what (), Gtk::MESSAGE_ERROR);
	}
}

void RsaController::on_buttonGenerateKey_clicked()
{
	//Gtk::TreeModel::iterator iter = m_comboboxKeyFileFormat->get_active();
	//int id = 0;

	//if(iter)
//		id = (*iter)[m_PadColumns.m_col_id];

//	int n;
//	int e;

//	switch (id)
	//{
	//case 1:
	//	m_RsaProcessor = new RsaUtil (RsaUtil::RSAPAD_PKCS1/*, 1024, 65537*/);
	//	break;
	//case 2:
	//	m_RsaProcessor = new RsaUtil (RsaUtil::RSAPAD_OAEP/*, 1024, 65537*/);
	//	break;
	//case 3:
	//	m_RsaProcessor = new RsaUtil (RsaUtil::RSAPAD_SSL/*, 1024, 65537*/);
	//	break;
	//case 4:
	//	m_RsaProcessor = new RsaUtil (RsaUtil::RSAPAD_RAW/*, 1024, 65537*/);
	//	break;
	//}

	//mShowRsaDialog ("A new key has been generated", Gtk::MESSAGE_INFO);
}



void RsaController::on_buttonBrowseKeyFile_clicked ()
{
	m_entryKeyFilePath->get_buffer ()->set_text (mGetFilePathFromUser ());
}

void RsaController::on_buttonBrowse_clicked()
{
	m_entrySrcFilePath->get_buffer ()->set_text (mGetFilePathFromUser ());
}

void RsaController::on_buttonOpenSrcFile_clicked()
{
	Glib::RefPtr<Glib::IOChannel> input;
	Glib::IOStatus iostatus;
	Glib::ustring file_content, fil_path;

	fil_path = m_entrySrcFilePath->get_buffer ()->get_text ();

	try {

		input = Glib::IOChannel::create_from_file(fil_path, "r");
		iostatus = input->set_encoding ();  // Set channel for binary reading

		if (iostatus != Glib::IO_STATUS_NORMAL)
		{
			mShowRsaDialog ("Error seting io channel for binary reading", Gtk::MESSAGE_ERROR);
			return;
		}

		iostatus = input->read_to_end(file_content);

		if (iostatus != Glib::IO_STATUS_NORMAL)
		{
			mShowRsaDialog ("Error reading source test file", Gtk::MESSAGE_ERROR);
			return;
		}
	}
	catch ( Glib::IOChannelError& io_error)
	{
		mShowRsaDialog ("Error reading source test file", Gtk::MESSAGE_ERROR);
	}
	catch (Glib::ConvertError conv_error)
	{
		mShowRsaDialog ("Error reading source test file", Gtk::MESSAGE_ERROR);
	}
	catch (Glib::FileError& ferr)
	{
		mShowRsaDialog ("Error reading source test file", Gtk::MESSAGE_ERROR);
	}

	SafeBuffer bin_data ((unsigned char*) file_content.data (), file_content.bytes ());
	m_CipherText = bin_data;

	m_textviewCipherContent->get_buffer ()->set_text (m_CipherText.GetBase64Data ());
}

void RsaController::on_buttonBrowsePlainTextFile_clicked ()
{
	m_entryResultSavePath->get_buffer ()->set_text (mGetFilePathFromUser ());
}

void RsaController::on_buttonOpenPlainTextFile_clicked ()
{
}

void RsaController::on_radiobuttonGenerateKey_clicked ()
{
	//TODO enable load key from file table layout group of widgets
}

void RsaController::on_radiobuttonLoadKey_clicked ()
{
	//TODO enable load key from file table layout group of widgets
}

void RsaController::mShowRsaDialog (const Glib::ustring& msg, const Gtk::MessageType msgType)
{
	Gtk::MessageDialog msg_dlg (
			  *window
			, "RSA util notification"
			, false
			, msgType
			, Gtk::BUTTONS_OK);

	msg_dlg.set_secondary_text (msg);
	msg_dlg.run ();
}

Glib::ustring RsaController::mGetFilePathFromUser ()
{
	Gtk::FileChooserDialog file_dialog ("Select a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	file_dialog.set_transient_for (*window);
	file_dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	file_dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_OK);

	int res = file_dialog.run ();

	switch(res)
	{
	case(Gtk::RESPONSE_OK):
		return  file_dialog.get_filename ();
	case(Gtk::RESPONSE_CANCEL):
		break;
	default:
		break;
	}

	return "";
}











