/*
 * SigantureTestController.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef SIGANTURETESTCONTROLLER_H_
#define SIGANTURETESTCONTROLLER_H_

#include <gtkmm.h>
#include "PBETestController.h"
#include <System/Security/Cryptography/RsaUtil.h>

enum SignatureType
{
  SINGTYPE_HMAC = 1,
  SINGTYPE_RSA = 2,
  SINGTYPE_DSA = 3,
  SINGTYPE_CERT = 4
};

class SigantureTestController
{
public:
  SigantureTestController();
  virtual
  ~SigantureTestController();


  void SetWindow(Gtk::Window* parentWindow);
  Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);

private:
  void on_btn_SelectFile_clicked();
  void on_btn_SelectFolder_clicked();
  void on_btn_SelectCert_clicked();
  void on_btn_Sign_clicked();
  void on_btn_Validate_clicked();
  SignatureType GetSigMode();
  Smartmatic::System::Security::Cryptography::DigestAlgType GetDigestType();
  Smartmatic::System::Security::Cryptography::RsaUtil::RsaPaddingEnumType GetRSAPadding();
  Gtk::Window* window;
  Gtk::Fixed* fixedContainer;

  //Gtk::CheckButton* checkIsAutoContent;
  Gtk::CheckButton* checkBinaryMode;
  Gtk::Button* selectFile;
  Gtk::Button* selectFolder;
  Gtk::Button* selectCert;

  Gtk::Entry*     entryFilePath;
  Gtk::Entry*     entryOutFolderPath;
  Gtk::Entry*     entryCertPath;
  Gtk::Entry*     entryKey;

  Gtk::ComboBox* comboAlgorithm;
  Gtk::ComboBox* comboDigest;
  Gtk::ComboBox* comboboxPaddingMode;
  Gtk::TextView* txtView;
  Gtk::Button* generateSignature;
  Gtk::Button* validateSignature;

  ModelColumns m_Columns;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelAlgorithm;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelDigest;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelPadding;

  Gtk::CheckButton* checkAutoContent;

};

#endif /* SIGANTURETESTCONTROLLER_H_ */
