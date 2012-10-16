/**
 * @file ContingencyWidget.hxx
 * @brief Header class contingency widget
 * @date 17/10/2011
 * @author Yadickson Soto
 */

#ifndef CONTINGENCYWIDGET_HXX_
#define CONTINGENCYWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/smartmatic-entry-divided.h>
#include <Widgets/smartmatic-button.h>
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <Widgets/StepWidget.hxx>

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
				class ContingencyWidget: public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					ContingencyWidget(bool onlyIcons, Smartmatic::SAES::Configuration::EntryDividedWidgetConfiguration & config);
					virtual ~ContingencyWidget();

					Glib::SignalProxy0< void > getSignalButtonOkClicked();
					Glib::SignalProxy0< void > getSignalButtonBackClicked();
					void getText(std::string & text);
					void clear();

				private:
					Gtk::Frame * mainFrame;
					Gtk::Table * tablePin;
					Gtk::Label * labelTitle;
					Gtk::Label * labelPin;
					Gtk::Image * imagePin;
					Gtk::Image * imageHelp;

					Smartmatic::GUI::Widgets::SmartmaticEntryDivided * pin;
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonBack;
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

#endif /* CONTINGENCYWIDGET_HXX_ */
