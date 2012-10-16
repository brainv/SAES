/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CryptoTest
 * Copyright (C)  2011 <>
 * 
 * CryptoTest is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CryptoTest is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CERTIFICATE_VALIDATION_CONTROLLER_H_
#define _CERTIFICATE_VALIDATION_CONTROLLER_H_
#include "PBETestController.h"
#include <System/Security/Cryptography/CertificateValidator.h>
#include <System/Security/Cryptography/CertUtil.h>
#include <glibmm.h>

enum PURPOSEENUM
{
  PURPOSEENUM_SSLCLIENT = 1,
  PURPOSEENUM_SSLSERVER,
  PURPOSEENUM_NSSSLSERVER,
  PURPOSEENUM_SMIMESIGN,
  PURPOSEENUM_SMIMEENCRYPT
};

class CertificateFileChooseWidget: public Gtk::VBox
{
	public:
	CertificateFileChooseWidget(Glib::ustring Title);
	~CertificateFileChooseWidget();
	int getSelectedType();
	Glib::ustring getPassword();
	Glib::ustring getFile();
	void SetWindow(Gtk::Window* parentWindow);
	protected:
	private:
	Gtk::Window* window;
	Gtk::HBox hboxPrincipal;
	Gtk::HBox hboxPassword;
	Gtk::Label labelTitle;
	Gtk::Label labelPass;
	Gtk::ComboBox comboType;
	Gtk::Entry entryPass;
	Gtk::Entry entryFile;
	Gtk::Button buttonSelectFile;

	ModelColumns m_Columns;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModelType;
		
	void on_btn_SelectFile_clicked();
	void on_combo_changed();
};

class CertificateValidationController
{
public:
  CertificateValidationController();
  virtual
  ~CertificateValidationController();

  Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);
  void SetWindow(Gtk::Window* parentWindow);

private:

  Glib::ustring GetMessage(Smartmatic::System::Security::Cryptography::TrustResultEnum verifyResult);

  void on_btn_Validate_clicked();
  int getPurpose();
  Smartmatic::System::Security::Cryptography::CertificateValidationFlags GetValidationFlags();

  CertificateFileChooseWidget* certificateToValidate;
  CertificateFileChooseWidget* intermediateCA;
  CertificateFileChooseWidget* trustedCertificate;
  CertificateFileChooseWidget* RootCA;
	
  Gtk::Fixed* fixedContainer;
	
  Gtk::Window* window;

  Gtk::CheckButton* checkbuttonIgnoreCritical;
  Gtk::CheckButton* checkbuttonCBIssuerCheck; 
  Gtk::CheckButton* checkbuttonCRLCheck;
  Gtk::CheckButton* checkbuttonCRLCheckAll;
  Gtk::CheckButton* checkbuttonPolicyCheck;
  Gtk::CheckButton* checkbuttonExplicitPolicy;
  Gtk::CheckButton* checkbuttonInhibitAny;
  Gtk::CheckButton* checkbuttonX509Strict;
  Gtk::CheckButton* checkbuttonExtendedCRLSupport;
  Gtk::CheckButton* checkbuttonUseDeltas;
  Gtk::CheckButton* checkbuttonNotifyPolicy;
  Gtk::CheckButton* checkbuttonCheckSSSignature;
  Gtk::CheckButton* checkbuttonInhibitMap;

  Gtk::CheckButton* checkbuttonNoValidate;
  Gtk::CheckButton* checkbuttonCheckTime;
  Gtk::CheckButton* checkbuttonAllowProxyCert;
	
  Gtk::Button* buttonValidate;
  Gtk::Entry*  entryTime;
	
  Gtk::ComboBox* comboPurpose;

  ModelColumns m_Columns;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelPurpose;

};

#endif // _CERTIFICATE_VALIDATION_CONTROLLER_H_
