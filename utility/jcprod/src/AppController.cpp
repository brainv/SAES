/*
 * AppController.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: Marcel Cordoví
 */


#include "AppController.h"
#include "Exceptions/GpCommandException.h"
#include "InstallationDiagnosis.h"
#include "CardInstallationWrapper.h"


#include <iostream>
#include <fstream>


#define POLL_INTERVAL 1000

#define GUI_NOTIFY(x) \
	    mGuiMsg = ( x ); \
		on_message_changed_dsp (); \
		sleep (2);

#define TRACE(x) std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": " << ( x ) << std::endl;



//=======================================================
//=================== Life Cycle ========================
//=======================================================

AppController::AppController()
: mGuiMsg ("")
{
	connCheckCard = Glib::signal_timeout().connect(sigc::mem_fun(*this, &AppController::CardInssertionEvent), POLL_INTERVAL);
	on_message_changed_dsp.connect (sigc::mem_fun (*this, &AppController::mNotify));
}

AppController::~AppController()
{
	connRemoveCard.disconnect ();
	connCheckCard.disconnect ();
}


//========================================================
//================ Event Handling ========================
//========================================================

void AppController::mNotify ()
{
	on_message_changed.emit (mGuiMsg);
}

bool AppController::CardInssertionEvent ()
{
	if ( CardInstallationWrapper::isCardPresent () )
	{
		GUI_NOTIFY ("Card detected");
//		TRACE ("Card insertion");

		Glib::Thread::create (sigc::mem_fun (*this, &AppController::installApp), false);

		return false;
	}
	else
		return true;
}

bool AppController::CardRemotionEvent ()
{
	if ( ! CardInstallationWrapper::isCardPresent () )
	{
		GUI_NOTIFY ("Waiting for card insertion");
//		TRACE ("Card remotion");

		connCheckCard = Glib::signal_timeout().connect (
				sigc::mem_fun(*this, &AppController::CardInssertionEvent), POLL_INTERVAL);

		return false;
	}
	else
		return true;
}


//===============================================================
//================== Controller Operations ======================
//===============================================================


void AppController::installApp ()
{
	bool success = false;

	try
	{
//		if ( ! CardInstallationWrapper::IsCardInitialized () )
//		{
//			GUI_NOTIFY ("Initializing the card...");
//			CardInstallationWrapper::InitializeCard();
//			GUI_NOTIFY ("Card Initialized");
//		}
//
//		if ( CardInstallationWrapper::IsCardFused() )
//		{
//			GUI_NOTIFY ("Card is fused");
//		}
//		else
//		{
//			GUI_NOTIFY ("Fusing the card");
//			CardInstallationWrapper::FuseCard();
//			GUI_NOTIFY ("The card is now fused");
//		}

		if ( ! CardInstallationWrapper::IsAppletInstalled () )
		{
			GUI_NOTIFY ("Installing the applet");
			CardInstallationWrapper::InstallApplet ();
			GUI_NOTIFY ("Applet's installation ended");
		}

		GUI_NOTIFY ("Performing applet's diagnosis");
		success = InstallationDiagnosis::TestInstallation();
		GUI_NOTIFY ( (success ? "Diagnosis successfull" : "Diagnosis Unsuccessfull" ) );
	}
	catch ( GpCommandException& e )
	{
		Glib::ustring error_msg;
		error_msg.assign (e.what());
		GUI_NOTIFY (error_msg);
		TRACE ( e.what() );
	}

	if ( CardInstallationWrapper::isCardPresent () )
	{
		connRemoveCard = Glib::signal_timeout().connect (
				sigc::mem_fun(*this, &AppController::CardRemotionEvent), POLL_INTERVAL);
	}
	else
	{
		connCheckCard = Glib::signal_timeout().connect (
				sigc::mem_fun(*this, &AppController::CardInssertionEvent), POLL_INTERVAL);
	}
}

