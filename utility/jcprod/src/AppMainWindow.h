/*
 * AppMainWindow.h
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#ifndef APPMAINWINDOW_H_
#define APPMAINWINDOW_H_

#include <gtkmm.h>
#include <AppController.h>

class AppMainWindow : public Gtk::Window
{

public:

	AppMainWindow(AppController* controller);
	virtual ~AppMainWindow();

private:

	AppController* mController;

	Gtk::Label mMsgLabel;
	Gtk::Frame mFrame;

	void InitializeComponents ();

	void on_message_changed (Glib::ustring msg);
};

#endif /* APPMAINWINDOW_H_ */
