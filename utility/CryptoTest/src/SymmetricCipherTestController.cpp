/*
 * SymmetricCipherTestController.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#include "SymmetricCipherTestController.h"
#include <iostream>
#include <fstream>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/Compression/compression-class.h>

using namespace Gtk;
using namespace Smartmatic::System::IO;

static int set_hex(char *in, unsigned char *out, int size);


SymmetricCipherTestController::SymmetricCipherTestController()
{
	fixedContainer = NULL;
	window = NULL;
	entryTarget = NULL;
	entryOutDir = NULL;
	entryKey = NULL;
	entryIV = NULL;
	labelResult = NULL;
	checkIVBase64 = NULL;
	checkKeyBase64 = NULL;
	buttonSelectFile = NULL;
	buttonSelectDir = NULL;
	buttonEncrypt = NULL;
	buttonDecrypt = NULL;
	comboAesMode = NULL;
	comboKeySize = NULL;
	checkIsCompress = NULL;
}

SymmetricCipherTestController::~SymmetricCipherTestController()
{
  // TODO Auto-generated destructor stub
  if(fixedContainer)
    delete(fixedContainer);
  if(entryTarget)
    delete(entryTarget);
  if(entryOutDir)
    delete(entryOutDir);
  if(entryKey)
    delete(entryKey);
  if(entryIV)
    delete(entryIV);
  if(labelResult)
	delete(labelResult);
  if(checkIVBase64)
    delete(checkIVBase64);
  if(checkKeyBase64)
    delete(checkKeyBase64);
  if(buttonSelectFile)
    delete(buttonSelectFile);
  if(buttonSelectDir)
    delete(buttonSelectDir);
  if(buttonEncrypt)
    delete(buttonEncrypt);
  if(buttonDecrypt)
    delete(buttonDecrypt);
  if(comboAesMode)
    delete(comboAesMode);
  if(comboKeySize)
    delete(comboKeySize);
  if (checkIsCompress)
    delete(checkIsCompress);
}

Gtk::Fixed* SymmetricCipherTestController::GetWidget( Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("fixedSymmetricCypher",this->fixedContainer);



  //Get widgets
  builder->get_widget("entryTargetSym",this->entryTarget);
    builder->get_widget("entryTargetoutDirSym",this->entryOutDir);
    builder->get_widget("entryKeySym",this->entryKey);
    builder->get_widget("entryIVSym",this->entryIV);

	builder->get_widget("labelResult",this->labelResult);
	
    builder->get_widget("checkbuttonKeyInBase64",this->checkKeyBase64);
    builder->get_widget("checkbuttonIVBase64",this->checkIVBase64);
    builder->get_widget("checkbutton_compress",this->checkIsCompress);

    builder->get_widget("buttonSelectFileSym",this->buttonSelectFile);
    builder->get_widget("buttonOutDirSym",this->buttonSelectDir);
    builder->get_widget("buttonEncrypt",this->buttonEncrypt);
    builder->get_widget("buttonDecrypt",this->buttonDecrypt);
    builder->get_widget("comboboxAESMode",this->comboAesMode);
	builder->get_widget("comboboxKeySize",this->comboKeySize);

  //Setup widgets
    m_refTreeModelAesMode = Gtk::ListStore::create(m_Columns);
	m_refTreeModelKeySize = Gtk::ListStore::create(m_Columns);
    comboAesMode->set_model(m_refTreeModelAesMode);
	comboKeySize->set_model(m_refTreeModelKeySize);
	
    Gtk::TreeModel::Row row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "ECB";

    row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "CBC";

    row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "OFB";

    row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 4;
    row[m_Columns.m_col_name] = "CFB1";

    row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 5;
    row[m_Columns.m_col_name] = "CFB8";

    row = *(m_refTreeModelAesMode->append());
    row[m_Columns.m_col_id] = 6;
    row[m_Columns.m_col_name] = "CFB128";


    comboAesMode->pack_start(m_Columns.m_col_id);
    comboAesMode->pack_start(m_Columns.m_col_name);
    comboAesMode->set_active(0);

	Gtk::TreeModel::Row rowK = *(m_refTreeModelKeySize->append());
    rowK[m_Columns.m_col_id] = 1;
    rowK[m_Columns.m_col_name] = "KEY_AES_128";

    rowK = *(m_refTreeModelKeySize->append());
    rowK[m_Columns.m_col_id] = 2;
    rowK[m_Columns.m_col_name] = "KEY_AES_192";

    rowK = *(m_refTreeModelKeySize->append());
    rowK[m_Columns.m_col_id] = 3;
    rowK[m_Columns.m_col_name] = "KEY_AES_256";

	comboKeySize->pack_start(m_Columns.m_col_id);
    comboKeySize->pack_start(m_Columns.m_col_name);
    comboKeySize->set_active(0);

  //Connect to signals
    this->buttonSelectFile->signal_clicked().connect( sigc::mem_fun(*this,
          &SymmetricCipherTestController::on_btn_SelectFile_clicked) );
      this->buttonSelectDir->signal_clicked().connect( sigc::mem_fun(*this,
          &SymmetricCipherTestController::on_btn_SelectFolder_clicked) );
      this->buttonEncrypt->signal_clicked().connect( sigc::mem_fun(*this,
          &SymmetricCipherTestController::on_btn_Encryptt_clicked) );
      this->buttonDecrypt->signal_clicked().connect( sigc::mem_fun(*this,
          &SymmetricCipherTestController::on_btn_Dencrypt_clicked) );


  return fixedContainer;
}

void SymmetricCipherTestController::SetWindow(Gtk::Window* parentWindow)
{
  window = parentWindow;
}

void SymmetricCipherTestController::on_btn_SelectFile_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*window);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:

    /*Gtk::FileFilter filter_xml;
    filter_xml.set_name("Xml files");
    filter_xml.add_mime_type("text/xml");
    dialog.add_filter(filter_xml);*/


    Gtk::FileFilter filter_any;
    filter_any.set_name("Any files");
    filter_any.add_pattern("*");
    dialog.add_filter(filter_any);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
    case(Gtk::RESPONSE_OK):
                    {
      Glib::ustring filename = dialog.get_filename();
      this->entryTarget->set_text(filename);
      break;
                    }
    case(Gtk::RESPONSE_CANCEL):
                    {
      std::cout << "Cancel clicked." << std::endl;
      break;
                    }
    default:
      {
        std::cout << "Unexpected button clicked." << std::endl;
        break;
      }
    }
}
void SymmetricCipherTestController::on_btn_SelectFolder_clicked()
{
  Gtk::FileChooserDialog dialog("Choose a folder where to write the signed file",
        Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*window);


    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
    case(Gtk::RESPONSE_OK):
                    {

      Glib::ustring folder = dialog.get_filename();
      this->entryOutDir->set_text(folder);
      break;
                    }
    case(Gtk::RESPONSE_CANCEL):
                    {
      std::cout << "Action Canceled\n" << std::endl;
      break;
                    }
    default:
      {
        std::cout << "Unexpected button clicked." << std::endl;
        break;
      }
    }
}
void SymmetricCipherTestController::on_btn_Encryptt_clicked()
{
  Glib::ustring keystr = this->entryKey->get_text();
  Glib::ustring ivstr = this->entryIV->get_text();

  unsigned char* key;
  unsigned char* iv;
  unsigned int keyLen;
  unsigned int ivLen;

  //Get the key and IV
  if(this->checkKeyBase64->get_active())
  {
      key = g_base64_decode (keystr.c_str(), &keyLen);

  }
  else
  {
      key = static_cast<unsigned char*>(g_malloc(keystr.bytes()/2));
      keyLen = keystr.bytes()/2;

      set_hex((char*)keystr.c_str(), key, keyLen);
  }

  if(this->checkIVBase64->get_active())
  {

      iv = g_base64_decode (ivstr.c_str(), &ivLen);
  }
  else
  {
      iv = static_cast<unsigned char*>(g_malloc(ivstr.bytes()/2));
      ivLen =ivstr.bytes()/2;
      set_hex((char*)ivstr.c_str(), iv, ivLen);
  }

  bool ivNoMatchSize = false;
  switch(getKeySize())
  {
    case Smartmatic::System::Security::Crypto::KEY_AES_128:
		ivNoMatchSize = ivLen != 16;
    	break;
    case Smartmatic::System::Security::Crypto::KEY_AES_192:
		ivNoMatchSize = ivLen != 24;
		break;
    case Smartmatic::System::Security::Crypto::KEY_AES_256:
		ivNoMatchSize = ivLen != 32;
		break;
  }

  try
  {
	  if(!ivNoMatchSize)
	  {
		  Smartmatic::System::Security::Crypto crypto;
		  crypto.init(getKeySize(),getAESMode (), true);
		  std::string inputFile = entryTarget->get_text();
		  std::string outputFile = Path::Combine(this->entryOutDir->get_text(),Path::GetFileNameWithOutExtension(entryTarget->get_text())) + ".enc";

	        Smartmatic::System::SafeBuffer dataIn;
                crypto.cryptoFileToBuffer(inputFile, dataIn, key,iv);
	        Smartmatic::System::SafeBuffer dataOut;

	        if (this->checkIsCompress->get_active())
	        {
	            Smartmatic::System::SafeBuffer buffer;
                    Smartmatic::System::Compression::CompressionClass::Deflate(dataIn, buffer);
	            dataOut.AddData(buffer);
	        }
	        else
	        {
	            dataOut.AddData(dataIn);
	        }

	        Smartmatic::System::IO::File::saveBufferToFile(dataOut, outputFile);
	  }
	  else
	  {
		  labelResult->set_label("IV size does not match key size");
	  }
  }
  catch(...)
  {
	  std::cout << "Error Encrypting file" << std::endl;
  }
 g_free(key);
  g_free(iv);
}

Smartmatic::System::Security::Crypto::KeySize SymmetricCipherTestController::getKeySize()
{
	int id = 0;
	Smartmatic::System::Security::Crypto::KeySize retVal = Smartmatic::System::Security::Crypto::KEY_AES_128;
	TreeModel::iterator iterK = comboKeySize->get_active();
	if(iterK)
	{
		TreeModel::Row rowK = *iterK;
		if(rowK)
		{
			id = rowK[m_Columns.m_col_id];
		}
	}

	if(id != 0)
    {
      if(id == 1)
        retVal = Smartmatic::System::Security::Crypto::KEY_AES_128;
      else if(id == 2)
        retVal = Smartmatic::System::Security::Crypto::KEY_AES_192;
      else if(id == 3)
        retVal = Smartmatic::System::Security::Crypto::KEY_AES_256;
    }
  return retVal;
}

Smartmatic::System::Security::Crypto::Mode SymmetricCipherTestController::getAESMode()
{
	int id = 0;
	Smartmatic::System::Security::Crypto::Mode retVal = Smartmatic::System::Security::Crypto::MODE_AES_ECB;
	TreeModel::iterator iterA = comboAesMode->get_active();
	if(iterA)
	{
		TreeModel::Row rowA = *iterA;
		if(rowA)
		{
			id = rowA[m_Columns.m_col_id];
		}
	}

	if(id != 0)
    {
      if(id == 1)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_ECB;
      else if(id == 2)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_CBC;
      else if(id == 3)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_OFB;
      else if(id == 4)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_CFB1;
	  else if(id == 5)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_CFB8;
	  else if(id == 6)
        retVal = Smartmatic::System::Security::Crypto::MODE_AES_CFB128;
    }

  return retVal;
}

void SymmetricCipherTestController::on_btn_Dencrypt_clicked()
{
	Glib::ustring keystr = this->entryKey->get_text();
	Glib::ustring ivstr = this->entryIV->get_text();

	unsigned char* key;
	unsigned char* iv;
	unsigned int keyLen;
	unsigned int ivLen;

	//Get the key and IV
	  if(this->checkKeyBase64->get_active())
	  {
	      key = g_base64_decode (keystr.c_str(), &keyLen);

	  }
	  else
	  {
	      key = static_cast<unsigned char*>(g_malloc(keystr.bytes()/2));
	      keyLen = keystr.bytes()/2;

	      set_hex((char*)keystr.c_str(), key, keyLen);
	  }

	  if(this->checkIVBase64->get_active())
	  {

	      iv = g_base64_decode (ivstr.c_str(), &ivLen);
	  }
	  else
	  {
	      iv = static_cast<unsigned char*>(g_malloc(ivstr.bytes()));
	      ivLen =ivstr.bytes();
	      set_hex((char*)ivstr.c_str(), iv, ivLen);
	  }

	bool ivNoMatchSize = false;
    switch(getKeySize())
    {
      case Smartmatic::System::Security::Crypto::KEY_AES_128:
		ivNoMatchSize = ivLen != 16;
    	break;
      case Smartmatic::System::Security::Crypto::KEY_AES_192:
		ivNoMatchSize = ivLen != 16;
		break;
      case Smartmatic::System::Security::Crypto::KEY_AES_256:
		ivNoMatchSize = ivLen != 16;
		break;
    }
try
{
	if(!ivNoMatchSize)  
	{		
		Smartmatic::System::Security::Crypto crypto;
		crypto.init(getKeySize(),getAESMode (), true);
		std::string inputFile = entryTarget->get_text();
		std::string outputFile = Path::Combine(this->entryOutDir->get_text(),Path::GetFileNameWithOutExtension(entryTarget->get_text())) + ".dec";

        Smartmatic::System::SafeBuffer dataIn;
        crypto.decryptoFileToBuffer(inputFile, dataIn, key,iv);
        Smartmatic::System::SafeBuffer dataOut;

        if (this->checkIsCompress->get_active())
		{
            Smartmatic::System::SafeBuffer buffer;
            Smartmatic::System::Compression::CompressionClass::Inflate(dataIn, buffer);
            dataOut.AddData(buffer);


		}
        else
        {
            dataOut.AddData(dataIn);
        }

        Smartmatic::System::IO::File::saveBufferToFile(dataOut, outputFile);
		//Get the data

	}
    else
    {
	    labelResult->set_label("IV size does not match key size");
    }
}
catch(...)
{
	  std::cout << "Error Decrypting file" << std::endl;
}
        g_free(key);
        g_free(iv);
}


static int set_hex(char *in, unsigned char *out, int size)
{
  int i,n;
  unsigned char j;

  n=strlen(in);
  if (n > (size*2))
    {
      std::cout <<"hex string is too long" << std::endl;
      return(0);
    }
  memset(out,0,size);
  for (i=0; i<n; i++)
    {
      j=(unsigned char)*in;
      *(in++)='\0';
      if (j == 0) break;
      if ((j >= '0') && (j <= '9'))
        j-='0';
      else if ((j >= 'A') && (j <= 'F'))
        j=j-'A'+10;
      else if ((j >= 'a') && (j <= 'f'))
        j=j-'a'+10;
      else
        {
          std::cout <<"non-hex digit" << std::endl;
          return(0);
        }
      if (i&1)
        out[i/2]|=j;
      else
        out[i/2]=(j<<4);
    }
  return(1);
}
