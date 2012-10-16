/*
 * AppMainWindow.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#include "config.h"
#include "AppMainWindow.h"


AppMainWindow::AppMainWindow(AppController* controller)
{
	mController = controller;
	InitializeComponents ();
}

AppMainWindow::~AppMainWindow()
{
	// TODO Auto-generated destructor stub
}

void AppMainWindow::InitializeComponents ()
{
	mController->get_signal_message().connect (sigc::mem_fun (*this, &AppMainWindow::on_message_changed));

	Pango::FontDescription font_desc ("serif 22");
	font_desc.set_weight (Pango::WEIGHT_BOLD);
	Gdk::Color cl ("black");

	mMsgLabel.modify_font(font_desc);
	mMsgLabel.modify_fg (Gtk::STATE_NORMAL, cl);

	mMsgLabel.set_text ("Waiting for card insertion");
	mFrame.add (mMsgLabel);

	this->add (mFrame);
	this->set_default_size (700, 400);
	this->set_position (Gtk::WIN_POS_CENTER);
	this->show_all_children ();
}

void AppMainWindow::on_message_changed (Glib::ustring msg)
{
	if (msg == "Diagnosis successfull")
	{
		Gdk::Color cl ("darkgreen");
		mMsgLabel.modify_fg (Gtk::STATE_NORMAL, cl);
	}
	else if (msg == "Diagnosis Unsuccessfull")
	{
		Gdk::Color cl ("red");
		mMsgLabel.modify_fg (Gtk::STATE_NORMAL, cl);
	}
	else
	{
		Gdk::Color cl ("black");
		mMsgLabel.modify_fg (Gtk::STATE_NORMAL, cl);
	}

	mMsgLabel.set_text (msg);
}
