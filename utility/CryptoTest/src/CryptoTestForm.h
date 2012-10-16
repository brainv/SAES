/*
 * CryptoTestForm.h
 *
 *  Created on: Apr 5, 2011
 *      Author: freddyg
 */

#ifndef CRYPTOTESTFORM_H_
#define CRYPTOTESTFORM_H_

#include <gtkmm.h>
#include <Windows/basic-window.h>
#include "SymmetricCipherTestController.h"
#include "PBETestController.h"
#include "SigantureTestController.h"
#include "CertificateValidationController.h"
#include "CFEncryptorController.h"
#include "RsaController.h"


class CryptoTestForm : public Smartmatic::GUI::Windows::BasicWindow
{
public:
  CryptoTestForm();
  virtual
  ~CryptoTestForm();

private:
  void on_exit_clicked();
  Gtk::Label title_label;
  Gtk::Notebook m_Notebook;
  Gtk::Fixed* fixedPBE;
  Gtk::Fixed* fixedSignature;
  Gtk::Fixed* fixedSymmetricCypher;
  Gtk::Fixed* fixedCertificateValidation;
  Gtk::Fixed* fixedCFEncryptor;
  Gtk::HBox 	hbox;
  Gtk::Button 	exit;

  SymmetricCipherTestController symmTest;
  PBETestController             pbeTest;
  SigantureTestController       signTest;
  CertificateValidationController certTest;
  CFEncryptorController			cfencryptor;
  RsaController                 rsaTest;

};

#endif /* CRYPTOTESTFORM_H_ */
