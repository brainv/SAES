/*
 * CFEncryptorController.h
 *
 *  Created on: Apr 21, 2011
 *      Author: fgomez
 */

#ifndef CFENCRYPTORCONTROLLER_H_
#define CFENCRYPTORCONTROLLER_H_

#include <gtkmm.h>
#include "CFEncryptor.h"

class CFEncryptorController {
public:
	CFEncryptorController();
	virtual ~CFEncryptorController();

	Gtk::Fixed* GetWidget( Glib::RefPtr<Gtk::Builder> builder);
	void SetWindow(Gtk::Window* parentWindow);
private:


	void RegisterMessage(Glib::ustring& line);
	void on_encryption_finished();
	void on_encryption_update(CFEncryptor * cfe);

	void on_inputbuton_clicked();
	void on_outputbutton_clicked();
	void on_cert_clicked();
	void on_runbutton_clicked();

	Gtk::Fixed* fixedContainer;
	Gtk::Window* window;
	Gtk::CheckButton* checkbuttonSign;
	Gtk::CheckButton* checkbuttonEncryptFiles;
	Gtk::CheckButton* checkbuttonProtectSecretKey;

	Gtk::Entry*     entryInputDir;
	Gtk::Entry*     entryOutPutDir;
	Gtk::Entry*     entrySingP12;
	Gtk::Entry*     entryProtectionKey;

	Gtk::Button* buttonSelectinputDir;
	Gtk::Button* buttonSelectOutDi;
	Gtk::Button* buttonSelectCer;
	Gtk::Button* buttonRun;

	Gtk::TextView* textviewLog;
	CFEncryptor encryptorClass;
};

#endif /* CFENCRYPTORCONTROLLER_H_ */
