/*
 * RsaController.h
 *
 *  Created on: May 26, 2011
 *      Author: mcordovi
 */

#ifndef RSACONTROLLER_H_
#define RSACONTROLLER_H_

#include <gtkmm.h>
#include <System/SafeBuffer.h>
#include <System/Security/Cryptography/RsaUtil.h>

class MyModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:

	MyModelColumns()
	{ add(m_col_id); add(m_col_name); }

	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
};

class RsaController
{

public:

	RsaController();
	virtual ~RsaController();

	Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);
	void SetWindow(Gtk::Window* parentWindow);

private:


	Smartmatic::System::Security::Cryptography::RsaUtil* m_RsaProcessor;

	Smartmatic::System::SafeBuffer m_PlainText;
	Smartmatic::System::SafeBuffer m_CipherText;


	// Top container

	Gtk::Fixed* m_fixedRsa;
	Gtk::Window* window;

	// Key loading

	Gtk::Entry* m_entryPassphrase;
	Gtk::Entry* m_entryKeyFilePath;
	Gtk::ComboBox* m_comboboxKeyFileFormat;
	Gtk::Button* m_buttonBrowseKeyFile;
	Gtk::Button* m_buttonLoadKeyFromFile;

	Gtk::Entry* m_entryModulus;
	Gtk::Entry* m_entryPublicExponent;
	Gtk::ComboBox* m_comboboxPaddingType;
	Gtk::Button* m_buttonGenerateKey;

	Gtk::RadioButton* m_radiobuttonLoadKey;
	Gtk::RadioButton* m_radiobuttonGenKey;

	MyModelColumns m_PadColumns;
	Glib::RefPtr<Gtk::ListStore> m_refPadTreeModel;

	MyModelColumns m_FmtColumns;
	Glib::RefPtr<Gtk::ListStore> m_refFormatTreeModel;

	// Key labels

	Gtk::Label* m_labelPrivateKeyValue;
	Gtk::Label* m_labelPublicKeyValue;

	// Rsa Operation display

	Gtk::Entry* m_entrySrcFilePath;
	Gtk::Button* m_buttonBrowse;
	Gtk::Button* m_buttonOpenSrcFile;
	Gtk::TextView* m_textviewCipherContent;

	Gtk::Entry* m_entryResultSavePath;
	Gtk::Button* m_buttonBrowsePlainTextFile;
	Gtk::Button* m_buttonOpenPlainTextFile;
	Gtk::TextView* m_textviewPlainContent;

	Gtk::Button* m_buttonEncrypt;
	Gtk::Button* m_buttonDecrypt;
	Gtk::Button* m_buttonSign;
	Gtk::Button* m_buttonVerify;


	// Event handling

	void on_radiobuttonGenerateKey_clicked ();
	void on_radiobuttonLoadKey_clicked ();

	void on_buttonBrowseKeyFile_clicked ();
	void on_buttonLoadKeyFromFile_clicked ();
	void on_buttonGenerateKey_clicked ();
	void on_buttonBrowse_clicked ();
	void on_buttonOpenSrcFile_clicked ();
	void on_buttonOpenPlainTextFile_clicked ();
	void on_buttonBrowsePlainTextFile_clicked ();

	void on_buttonEncrypt_clicked ();
	void on_buttonDecrypt_clicked ();
	void on_buttonSign_clicked ();
	void on_buttonVerify_clicked ();


	// Auxiliars

	void mShowRsaDialog (const Glib::ustring& msg, const Gtk::MessageType msgType);
	Glib::ustring mGetFilePathFromUser ();

};

#endif /* RSACONTROLLER_H_ */
