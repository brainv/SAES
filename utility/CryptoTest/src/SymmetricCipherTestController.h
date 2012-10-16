/*
 * SymmetricCipherTestController.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef SYMMETRICCIPHERTESTCONTROLLER_H_
#define SYMMETRICCIPHERTESTCONTROLLER_H_

#include <gtkmm.h>
#include <System/Security/Crypto.hxx>
#include "PBETestController.h"



    enum AESMODEENUM
    {
      AESMODEENUM_ECB = 1,
      AESMODEENUM_CBC,
      AESMODEENUM_OFB,
      AESMODEENUM_CFB1,
      AESMODEENUM_CFB8,
      AESMODEENUM_CFB128,
    };

    enum KEYSIZEENUM
    {
      KEYSIZEENUM_128 = 1,
      KEYSIZEENUM_192,
      KEYSIZEENUM_256,
    };


class SymmetricCipherTestController
{
public:
  SymmetricCipherTestController();
  virtual
  ~SymmetricCipherTestController();

  Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);
  void SetWindow(Gtk::Window* parentWindow);

private:

  void on_btn_SelectFile_clicked();
  void on_btn_SelectFolder_clicked();
  void on_btn_Encryptt_clicked();
  void on_btn_Dencrypt_clicked();

  Smartmatic::System::Security::Crypto::KeySize getKeySize();
  Smartmatic::System::Security::Crypto::Mode getAESMode();	
  Gtk::Fixed* fixedContainer;
  Gtk::Window* window;

  Gtk::Entry* entryTarget;
  Gtk::Entry* entryOutDir;
  Gtk::Entry* entryKey;
  Gtk::Entry* entryIV;
  Gtk::CheckButton* checkKeyBase64;
  Gtk::CheckButton* checkIVBase64;
  Gtk::CheckButton* checkIsCompress;

  Gtk::Label* labelResult;
	
  Gtk::Button* buttonSelectFile;
  Gtk::Button* buttonSelectDir;
  Gtk::Button* buttonEncrypt;
  Gtk::Button* buttonDecrypt;
  Gtk::ComboBox* comboAesMode;
  Gtk::ComboBox* comboKeySize;

  ModelColumns m_Columns;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelAesMode;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelKeySize;
};

#endif /* SYMMETRICCIPHERTESTCONTROLLER_H_ */
