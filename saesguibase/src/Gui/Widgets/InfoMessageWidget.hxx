/*
 * InfoMessageWidget.hxx
 *
 *  Created on: 17/10/2011
 *      Author: soto
 */

#ifndef INFOMESSAGEWIDGET_HXX_
#define INFOMESSAGEWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>

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
				class InfoMessageWidget: public Gtk::Frame
				{
				public:
					InfoMessageWidget();
					virtual ~InfoMessageWidget();

					Glib::SignalProxy0< void > getSignalButtonOkClicked();
					Glib::SignalProxy0< void > getSignalButtonBackClicked();
					Glib::SignalProxy0< void > getSignalButtonPrintClicked();

					void setInfoWidget(Gtk::Widget * info);
					void enableButtonBack(bool enable);
					void enableButtonOk(bool enable);
					void enableButtonPrint(bool enable);

					void hideButtonBack();
					void showButtonBack();

					void hideButtonOk();
					void showButtonOk();

					void hideButtonPrint();
					void showButtonPrint();

					void hideText();
					void showText();

				private:
					Gtk::Frame * mainFrame;
					Gtk::Frame * infoFrame;
					Gtk::VBox * mainVBox;
					Gtk::VButtonBox * vbuttonboxPrint;

					Smartmatic::GUI::Widgets::SmartmaticButton * buttonBack;
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonOk;
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonPrint;

					static Smartmatic::Log::ISMTTLog* logger;   ///< logger

				protected:
					void initialize();
					void dispose();
				};
			}
		}
	}
}

#endif /* INFOMESSAGEWIDGET_HXX_ */
