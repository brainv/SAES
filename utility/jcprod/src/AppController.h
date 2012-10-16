/*
 * AppController.h
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */

#ifndef APPCONTROLLER_H_
#define APPCONTROLLER_H_

#include <gtkmm.h>

class AppController {

public:

	AppController();
	virtual ~AppController();

	bool isCardPresent ();
	void installApp ();

	typedef sigc::signal<void, Glib::ustring> signal_message_type;
	signal_message_type get_signal_message () { return this->on_message_changed; }

private:

	signal_message_type on_message_changed;
	Glib::Dispatcher on_message_changed_dsp;

	std::string mCapPath;
	std::string mGuiMsg;

	bool CardRemotionEvent ();
	bool CardInssertionEvent ();
	bool IsCardInitialized ();
	bool IsAppletInstalled ();

	sigc::connection connCheckCard;
	sigc::connection connRemoveCard;

	void mNotify ();

};

#endif /* APPCONTROLLER_H_ */
