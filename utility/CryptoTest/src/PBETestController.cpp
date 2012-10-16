/*
 * PBETestController.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#include "PBETestController.h"
#include <iostream>
#include <System/Security/Cryptography/PBEKeyDerivatorHMAC.h>
#include <System/Security/Cryptography/MsgDigestUtil.h>
#include <System/SafeBuffer.h>

using namespace Smartmatic::System;
using namespace Smartmatic::System::Security::Cryptography;



static int set_hex(char *in, unsigned char *out, int size);







PBETestController::PBETestController():
 fixedContainer(NULL),
 hmacAlgorithm(NULL),
 digestMD5(NULL),
 digestSHA1(NULL),
 digestSHA256(NULL),
 digestSHA512(NULL),
 digest(NULL),
 phrase(NULL),
 keySize(NULL),
 iterations(NULL),
 salt(NULL),
 compute(NULL),
 outPut(NULL)
{
  // TODO Auto-generated constructor stub

}


DigestAlgType PBETestController::GetDigestType()
{
  int id = 0;
  DigestAlgType retVal = DGSTUTIL_SHA1;


  Gtk::TreeModel::iterator iter = digest->get_active();
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

Glib::ustring PBETestController::GetDigestName()
{
  Glib::ustring retVal = "";
  Gtk::TreeModel::iterator iter = digest->get_active();
    if(iter)
      {
        Gtk::TreeModel::Row row = *iter;
        if(row)
          {
            //Get the data for the selected row, using our knowledge of the tree
            retVal = row[m_Columns.m_col_name];
          }
      }
    return retVal;
}

void PBETestController::on_compute_clicked()
{
  DigestAlgType md = GetDigestType();
  int ites = atoi(this->iterations->get_text().c_str());
  int keySize = atoi(this->keySize->get_text().c_str());
  SafeBuffer saltDigest;

  if(keySize > 1024)
    keySize = 1024; //dummy check

  unsigned char key[keySize];

  Glib::ustring saltStr = this->salt->get_text();
  Glib::ustring userPhrase = this->phrase->get_text();

  char saltBufferStr[saltStr.bytes()+1];
  char saltBufferStrCopy[saltStr.bytes()+1];
  unsigned char saltBufferHex[saltStr.bytes()/2 +1];

  saltBufferStr[saltStr.bytes()] = 0;//a guard for cout
  saltBufferStrCopy[saltStr.bytes()] = 0;//a guard for cout
  saltBufferHex[saltStr.bytes()/2] = 0;//a guard for cout

  unsigned char* salt;
  int saltSize = 0;

  if(saltStr.bytes() > 0)
  {
	  saltStr.copy(saltBufferStr, saltStr.bytes(),0 );
	  saltStr.copy(saltBufferStrCopy, saltStr.bytes(),0 );

	  if(set_hex(saltBufferStrCopy,saltBufferHex, saltStr.bytes()/2 )==0)
	  {
		  salt = (unsigned char*)saltBufferStr;
		  saltSize = saltStr.bytes();
	  }
	  else
	  {
		  salt = saltBufferHex;
		  saltSize = saltStr.bytes()/2;
	  }
  }
  else
  {
	  saltDigest = MsgDigestUtil::Digest((const unsigned char*)userPhrase.c_str(), userPhrase.bytes(), MsgDigestUtil::DGSTUTIL_SHA256);
	  salt = (unsigned char*)saltDigest.GetData();
	  saltSize = saltDigest.GetSize();
  }


  //Clear text
  outPut->get_buffer()->set_text("");

  Glib::ustring message = "Generating password..\n";
  outPut->get_buffer()->insert_at_cursor(message);

  message = "Passphrase: " + userPhrase +"\n";
  outPut->get_buffer()->insert_at_cursor(message);

  message = "Salt: " + saltStr+"\n";
  outPut->get_buffer()->insert_at_cursor(message);

  message = "Using Digest: " + GetDigestName() +"\n";
  outPut->get_buffer()->insert_at_cursor(message);

  message = "Using Iterations: " + Glib::ustring::compose("%1 \n",ites);
  outPut->get_buffer()->insert_at_cursor(message);

  message = "Using key Size: " + Glib::ustring::compose("%1 \n",keySize);
  outPut->get_buffer()->insert_at_cursor(message);

  PBEKeyDerivatorHMAC derivator;



  derivator.SetSalt(salt,saltSize);
  derivator.GenerateKey(userPhrase,key, keySize,ites,md);

  char * keybase64 = g_base64_encode(key, keySize);
  message = "base 64 key... \n";
  outPut->get_buffer()->insert_at_cursor(message);
  message.assign(keybase64);
  outPut->get_buffer()->insert_at_cursor(message);
  g_free(keybase64);

  message = "generated Key bytes... \n";
    outPut->get_buffer()->insert_at_cursor(message);

    message = "";
   for(int i = 0;i < keySize;i++)
   {
       message += Glib::ustring::compose("%1\n",key[i]);
   }
   outPut->get_buffer()->insert_at_cursor(message);
}

Gtk::Fixed* PBETestController::GetWidget( Glib::RefPtr<Gtk::Builder> builder)
{
  builder->get_widget("fixedPBE",this->fixedContainer);

  //TODO: get widgets
  /*builder->get_widget("radiobuttonHMAC",this->hmacAlgorithm);
  builder->get_widget("radiobuttonMD5",this->digestMD5);
  builder->get_widget("radiobuttonSHA1",this->digestSHA1);
  builder->get_widget("radiobuttonSHA256",this->digestSHA256);
  builder->get_widget("radiobuttonSHA512",this->digestSHA512);*/
  builder->get_widget("comboboxDigest",this->digest);

  builder->get_widget("entryPassPhrase",this->phrase);
  builder->get_widget("entryKeySize",this->keySize);
  builder->get_widget("entryIterations",this->iterations);
  builder->get_widget("buttonCompute",this->compute);
  builder->get_widget("textviewOutput",this->outPut);
  builder->get_widget("entrySalt",this->salt);



  Gtk::WrapMode wrapMode =Gtk::WRAP_WORD;
  this->outPut->set_wrap_mode(wrapMode);
  //this->digest->

  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  digest->set_model(m_refTreeModel);

  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "MD5";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "SHA1";


  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "SHA256";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 4;
  row[m_Columns.m_col_name] = "SHA512";

  digest->pack_start(m_Columns.m_col_id);
  digest->pack_start(m_Columns.m_col_name);

  digest->set_active(1);

  //connect to signals

  this->compute->signal_clicked().connect( sigc::mem_fun(*this,
      &PBETestController::on_compute_clicked) );


  return fixedContainer;
}



PBETestController::~PBETestController()
{
  // TODO Auto-generated destructor stub
  if(fixedContainer)
  delete( fixedContainer);
  if(hmacAlgorithm)
  delete(hmacAlgorithm);
  if(digestMD5)
  delete(digestMD5);
  if(digestSHA1)
  delete( digestSHA1);
  if(digestSHA256)
  delete( digestSHA256);
  if(digestSHA512)
  delete( digestSHA512);
  if(digest)
  delete(digest);
  if(phrase)
  delete(  phrase);
  if(keySize)
  delete(  keySize);
  if(iterations)
  delete(  iterations);
  if(salt)
    delete (salt);
  if(compute)
  delete( compute);
  if(outPut)
  delete( outPut);
}

static  int set_hex(char *in, unsigned char *out, int size)
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
