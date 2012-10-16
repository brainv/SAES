/*
 * SigantureTestController.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include "SigantureTestController.h"
#include <iostream>
#include <fstream>
#include <System/Security/Signed.hxx>
#include <System/Security/Cryptography/RsaUtil.h>
#include <System/XML/Serialization/DomWriter.h>
#include <System/IO/Path.h>
#include <System/IO/File.h>
#include <System/XML/DomXml.hxx>

using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::XML::Serialization;
using namespace Smartmatic::System::Security;
using namespace Smartmatic::System::Security::Cryptography;
using namespace std;

XERCES_CPP_NAMESPACE_USE

SigantureTestController::SigantureTestController():
window(NULL),
fixedContainer(NULL),
//checkIsAutoContent(NULL),
selectFile(NULL),
selectFolder(NULL),
selectCert(NULL),
entryFilePath(NULL),
entryOutFolderPath(NULL),
entryCertPath(NULL),
entryKey(NULL),
comboAlgorithm(NULL),
comboDigest(NULL),
txtView(NULL),
generateSignature(NULL),
validateSignature(NULL),
checkAutoContent(NULL)
{
  // TODO Auto-generated constructor stub

}

SigantureTestController::~SigantureTestController()
{
  // TODO Auto-generated destructor stub
  if(fixedContainer)
    delete(fixedContainer);

  if(selectFile)
    delete(selectFile);
  if(selectFolder)
    delete(selectFolder);
  if(selectCert)
    delete(selectCert);
  //if(checkIsAutoContent)
	//delete(checkIsAutoContent);
  if(entryFilePath)
    delete(entryFilePath);
  if(entryOutFolderPath)
    delete(entryOutFolderPath);
  if(entryCertPath)
    delete(entryCertPath);
  if(entryKey)
    delete(entryKey);
  if(comboAlgorithm)
    delete(comboAlgorithm);
  if(comboDigest)
      delete(comboDigest);
  if(txtView)
    delete(txtView);
  if(generateSignature)
    delete(generateSignature);
  if(validateSignature)
      delete(validateSignature);
  if(checkAutoContent)
   delete (checkAutoContent);
}

void SigantureTestController::SetWindow(Gtk::Window* parentWindow)
{
 window = parentWindow;
}

SignatureType SigantureTestController::GetSigMode()
{
  int retVal = 1;
    Gtk::TreeModel::iterator iter = comboAlgorithm->get_active();
      if(iter)
        {
          Gtk::TreeModel::Row row = *iter;
          if(row)
            {
              //Get the data for the selected row, using our knowledge of the tree
              retVal = row[m_Columns.m_col_id];
            }
        }
  return (SignatureType)retVal;
}

DigestAlgType SigantureTestController::GetDigestType()
{
  int id = 0;
  DigestAlgType retVal = DGSTUTIL_SHA1;


  Gtk::TreeModel::iterator iter = comboDigest->get_active();
  if(iter)
    {
      Gtk::TreeModel::Row row = *iter;
      if(row)
        {
          //Get the data for the selected row, using our knowledge of the tree
          id = row[m_Columns.m_col_id];
        }
    }


  if(id != 0)
    {
      if(id == 1)
        retVal = DGSTUTIL_MD5;
      else if(id == 2)
        retVal = DGSTUTIL_SHA1;
      else if(id == 3)
        retVal = DGSTUTIL_SHA256;
      else if(id == 4)
        retVal = DGSTUTIL_SHA512;
    }

  return retVal;
}

RsaUtil::RsaPaddingEnumType SigantureTestController::GetRSAPadding()
{
	int id = 0;
	RsaUtil::RsaPaddingEnumType retVal = RsaUtil::RSAPAD_PKCS1;


	  Gtk::TreeModel::iterator iter = comboboxPaddingMode->get_active();
	  if(iter)
	    {
	      Gtk::TreeModel::Row row = *iter;
	      if(row)
	        {
	          //Get the data for the selected row, using our knowledge of the tree
	          id = row[m_Columns.m_col_id];
	        }
	    }


	  if(id != 0)
	    {
	      if(id == 1)
	        retVal = RsaUtil::RSAPAD_PKCS1;
	      else if(id == 2)
	        retVal = RsaUtil::RSAPAD_OAEP;
	      else if(id == 3)
	        retVal = RsaUtil::RSAPAD_SSL;
	      else if(id == 4)
	        retVal = RsaUtil::RSAPAD_RAW;
	    }

	  return retVal;
}

Gtk::Fixed* SigantureTestController::GetWidget( Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("fixedSignature",this->fixedContainer);

 builder->get_widget("checkbuttonBinaryMode",this->checkBinaryMode);
	
  builder->get_widget("entryXmlPath",this->entryFilePath);
  builder->get_widget("entryFolderPath",this->entryOutFolderPath);
  builder->get_widget("entryCertPath",this->entryCertPath);
  builder->get_widget("entryKey",this->entryKey);

  builder->get_widget("comboboxAlgorithm",this->comboAlgorithm);
  builder->get_widget("comboboxDigestSig",this->comboDigest);
  builder->get_widget("comboboxPaddingMode",this->comboboxPaddingMode);


  builder->get_widget("buttonSelectOutDir",this->selectFolder);
  builder->get_widget("buttonSelectCert",this->selectCert);
  builder->get_widget("buttonSignFile",this->generateSignature);
  builder->get_widget("buttonSelectFileToSign",this->selectFile);
  builder->get_widget("buttonValidate",this->validateSignature);
  builder->get_widget("checkbuttonIsAutoContent",this->checkAutoContent);


  this->fixedContainer->set_visible();

  //Set up combo box
  m_refTreeModelDigest = Gtk::ListStore::create(m_Columns);

  comboDigest->set_model(m_refTreeModelDigest);

  Gtk::TreeModel::Row row = *(m_refTreeModelDigest->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "MD5";

  row = *(m_refTreeModelDigest->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "SHA1";

  row = *(m_refTreeModelDigest->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "SHA256";

  row = *(m_refTreeModelDigest->append());
  row[m_Columns.m_col_id] = 4;
  row[m_Columns.m_col_name] = "SHA512";

  comboDigest->pack_start(m_Columns.m_col_id);
  comboDigest->pack_start(m_Columns.m_col_name);

  comboDigest->set_active(1);

  m_refTreeModelAlgorithm = Gtk::ListStore::create(m_Columns);
  comboAlgorithm->set_model(m_refTreeModelAlgorithm);
  row = *(m_refTreeModelAlgorithm->append());


  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "HMAC";

  row = *(m_refTreeModelAlgorithm->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "RSA";

  row = *(m_refTreeModelAlgorithm->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "DSA";

  row = *(m_refTreeModelAlgorithm->append());
  row[m_Columns.m_col_id] = 4;
  row[m_Columns.m_col_name] = "WithCert";

  comboAlgorithm->pack_start(m_Columns.m_col_id);
  comboAlgorithm->pack_start(m_Columns.m_col_name);

  comboAlgorithm->set_active(1);


  m_refTreeModelPadding = Gtk::ListStore::create(m_Columns);
  comboboxPaddingMode->set_model(m_refTreeModelPadding);
    row = *(m_refTreeModelPadding->append());


    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "PKCS1";

    row = *(m_refTreeModelPadding->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "OAEP";

    row = *(m_refTreeModelPadding->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "SSL";

    row = *(m_refTreeModelPadding->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "NO PAD";

    comboboxPaddingMode->pack_start(m_Columns.m_col_id);
    comboboxPaddingMode->pack_start(m_Columns.m_col_name);

    comboboxPaddingMode->set_active(1);



  //connect to the button signals
  this->selectFile->signal_clicked().connect( sigc::mem_fun(*this,
      &SigantureTestController::on_btn_SelectFile_clicked) );
  this->selectFolder->signal_clicked().connect( sigc::mem_fun(*this,
      &SigantureTestController::on_btn_SelectFolder_clicked) );
  this->selectCert->signal_clicked().connect( sigc::mem_fun(*this,
      &SigantureTestController::on_btn_SelectCert_clicked) );
  this->generateSignature->signal_clicked().connect( sigc::mem_fun(*this,
      &SigantureTestController::on_btn_Sign_clicked) );

  this->validateSignature->signal_clicked().connect( sigc::mem_fun(*this,
        &SigantureTestController::on_btn_Validate_clicked) );


  return fixedContainer;
}

void SigantureTestController::on_btn_SelectFile_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a file to Sig",
      Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*window);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_xml;
  filter_xml.set_name("Xml files");
  filter_xml.add_mime_type("text/xml");
  dialog.add_filter(filter_xml);


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
    this->entryFilePath->set_text(filename);
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
void SigantureTestController::on_btn_SelectFolder_clicked()
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
      this->entryOutFolderPath->set_text(folder);
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
void SigantureTestController::on_btn_SelectCert_clicked()
{
  Gtk::FileChooserDialog dialog("Please choose a file to Sig",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*window);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:

    Gtk::FileFilter filter_p12;
    filter_p12.set_name("PKCS#12 files");
    filter_p12.add_mime_type("application/x-pkcs12");
    dialog.add_filter(filter_p12);

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
      this->entryCertPath->set_text(filename);
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
void SigantureTestController::on_btn_Sign_clicked()
{

  SignatureType signMode = GetSigMode();
  DigestAlgType digestType = GetDigestType();

  std::string password = this->entryKey->get_text();
  std::string certPath = this->entryCertPath->get_text();
  Signed signer;
  RsaUtil rsautl;
  Smartmatic::System::SafeBuffer signature;
    //Load xml file
  std::string filePath = this->entryFilePath->get_text();
  Glib::ustring error = "";
  Smartmatic::System::XML::DomXml domXml;
  xercesc_3_1::DOMDocument *doc = NULL;

  Signed::SignedType signType;
  if(checkAutoContent->get_active())
    {
      signType = Signed::FULL_SIGNED;

    }
  else
    {
      signType = Signed::SIMPLE_SIGNED;
    }


  try
  {
	  if(checkBinaryMode->get_active())
	  {
		  rsautl.SetPrivateKey_PKCS12(certPath,password);
		  rsautl.SetPaddingType(GetRSAPadding());
		  Smartmatic::System::SafeBuffer bufferFile;
		  Smartmatic::System::IO::File::openFileToBuffer(filePath, bufferFile);
		  rsautl.SignData(bufferFile,signature,(MsgDigestUtil::DigestAlgType) digestType );
	  }
	  else
	  {
		  doc =  domXml.fileToDom(filePath);
		  //set hash method
		    signer.SetHashAlgorithm(digestType);
		  //sign file
		  if(signMode == SINGTYPE_HMAC)
		  {
			  signer.SetPrivateKey((unsigned char*)password.c_str(),password.size());
			  signer.signedHMACDOM(doc, signType);
		  }
		  else if (signMode == SINGTYPE_DSA)
		  {
			  signer.loadPKCS12(password,certPath);
			  signer.signDOMWithDSA(doc,signType);
		  }
		  else if(signMode == SINGTYPE_RSA)
		  {
			  signer.loadPKCS12(password,certPath);
			  signer.signedRSADOM(doc,signType);
		  }
		  else if(signMode == SINGTYPE_CERT)
		  {
			  signer.loadPKCS12(password,certPath);
			  signer.signDOMWithCertificate(doc,signType);
		  }
	  }
  }
  catch(exception& exc)
  {
      error = "Exception message is: \n";
       error.append(exc.what());
  }

  if(error.bytes() >2)
    {
        Gtk::MessageDialog dialog(*window, "Error Signing file");
          dialog.set_secondary_text(error);
          dialog.run();
          return;
    }

  try
  {
  //Save file


	  Glib::ustring signedFile = Path::Combine(this->entryOutFolderPath->get_text(),Path::GetFileNameWithOutExtension(filePath)) + ".sig";

	  if(checkBinaryMode->get_active())
	  {
		  std::string name = signedFile;
		  Smartmatic::System::IO::File::saveBufferToFile(signature,name);
	  }
	  else
	  {
		  std::ofstream outfile(signedFile.c_str(),std::ios_base::out | std::ios_base::trunc );

		  DomWriter xmlWriter(outfile);

		  xmlWriter.Write(doc);

		  outfile.flush();
		  outfile.close();
	  }

  }
  catch(exception& exc2)
  {
      error = "Exception message is: \n";
             error.append(exc2.what());
  }

  if(error.bytes() >2)
  {
          Gtk::MessageDialog dialog(*window, "Error Saving signed file");
            dialog.set_secondary_text(error);
            dialog.run();

  }
}

void SigantureTestController::on_btn_Validate_clicked()
{
	SignatureType signMode = GetSigMode();
	DigestAlgType digestType = GetDigestType();

	std::string password = this->entryKey->get_text();
	std::string certPath = this->entryCertPath->get_text();
	Signed signer;

	//Load xml file
	std::string filePath = this->entryFilePath->get_text();
	std::string signaturefilePath = Path::Combine(this->entryOutFolderPath->get_text(),Path::GetFileNameWithOutExtension(filePath)) + ".sig";



	Glib::ustring error = "";
	Smartmatic::System::XML::DomXml domXml;
	xercesc_3_1::DOMDocument *doc = NULL;



	Signed::ValidateType validMode;
	if(checkAutoContent->get_active())
	{

		validMode = Smartmatic::System::Security::Signed::VALIDATE_INTERNAL;
	}
	else
	{
		validMode = Smartmatic::System::Security::Signed::VALIDATE_PKCS12;

	}

	bool validate = false;

	try
	{

		if(checkBinaryMode->get_active())
		{
			RsaUtil rsautl;
			Smartmatic::System::SafeBuffer bufferFile;
			Smartmatic::System::IO::File::openFileToBuffer(filePath, bufferFile);
			Smartmatic::System::SafeBuffer signature;
			Smartmatic::System::IO::File::openFileToBuffer(signaturefilePath, signature);

			rsautl.SetPublicKey_FromCert(certPath,password,CertUtil::CertFormat_PKCS12);
			rsautl.SetPaddingType(GetRSAPadding());

			if(rsautl.VerifySignature(bufferFile,signature,(MsgDigestUtil::DigestAlgType) digestType ) == false)
			{

				throw runtime_error("Invalid Signature");
			}
		}
		else
		{
			//set hash method
			signer.SetHashAlgorithm(digestType);
			doc =  domXml.fileToDom(filePath);
			//Load p12 file if necessary
			//validate file
			if(signMode == SINGTYPE_HMAC)
			{
				signer.SetPrivateKey((unsigned char*)password.c_str(),password.size());
				validate = signer.validateSignedHMACDOM(doc);
			}
			else if (signMode == SINGTYPE_DSA)
			{
				if(validMode == Signed::VALIDATE_PKCS12)
					signer.loadPKCS12(password,certPath);
				validate = signer.validateXmlDigitalSignature(doc,validMode);
			}
			else if(signMode == SINGTYPE_RSA)
			{
				if(validMode == Signed::VALIDATE_PKCS12)
					signer.loadPKCS12(password,certPath);
				validate = signer.validateXmlDigitalSignature(doc,validMode);
			}
			else if(signMode == SINGTYPE_CERT)
			{
				if(validMode == Signed::VALIDATE_PKCS12)
					signer.loadPKCS12(password,certPath);
				validate = signer.validateXmlDigitalSignature(doc,validMode);
			}
		}
	}
	catch(exception& signExc)
	{
		error = "Exception message is: \n";
		error.append(signExc.what());
	}
	if(error.bytes() >2 || !validate)
	{
		Gtk::MessageDialog dialog(*window, "Error Validating file");
		dialog.set_secondary_text(error);
		dialog.run();

	}
	else
	{
		Gtk::MessageDialog dialog(*window, "Validation OK");
		dialog.set_secondary_text("No error found");
		dialog.run();
	}


}
