/*
 * LoginWidget.hxx
 *
 *  Created on: 17/10/2011
 *      Author: soto
 */

#ifndef LOGINWIDGET_HXX_
#define LOGINWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/smartmatic-entry.h>
#include <Widgets/smartmatic-entry-divided.h>
#include <Widgets/smartmatic-button.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class LoginWidget: public Gtk::Frame
				{
				public:
					LoginWidget(bool onlyIcons, Smartmatic::SAES::Configuration::EntryDividedWidgetConfiguration & config);
					virtual ~LoginWidget();

					Glib::SignalProxy0< void > getSignalButtonOkClicked();

					void enabledLogin(bool enabled);
					void getLoginText(std::string & text);
					void setLoginText(std::string & text);
					void getPasswordText(std::string & text);
					void clearLogin();
					void clearPassword();

				private:
					Gtk::Frame * mainFrame;
					Gtk::Table * tableLogin;
					Gtk::Label * labelTitle;
					Gtk::Label * labelLogin;
					Gtk::Label * labelPassword;
					Gtk::Image * imageLogin;
					Gtk::Image * imagePassword;

					Smartmatic::GUI::Widgets::SmartmaticEntry * login;
					Smartmatic::GUI::Widgets::SmartmaticEntryDivided * password;
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonOk;

					bool onlyIcons;
					int entryDivisions;
					int entryMaxChar;
					int entryWidth;
					bool entryVisibility;
					static Smartmatic::Log::ISMTTLog* logger;   ///< logger

				protected:
					void initialize();
					void dispose();
				};
			}
		}
	}
}

#endif /* LOGINWIDGET_HXX_ */
