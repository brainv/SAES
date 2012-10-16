/*
 * VMInstallationConfirmation.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef VMINSTALLATIONCONFIRMATION_HXX_
#define VMINSTALLATIONCONFIRMATION_HXX_

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
				class VMInstallationConfirmation : public Gtk::Frame
				{
				public:
					VMInstallationConfirmation();
					virtual ~VMInstallationConfirmation();

					Glib::SignalProxy0< void > getSignalButtonOkClicked();
					Glib::SignalProxy0< void > getSignalButtonBackClicked();

					void hideButtonBack();
					void showButtonBack();

					void hideButtonOk();
					void showButtonOk();

					void setInfoWidget(Gtk::Widget * info);

				private:

					void initialize();
					void dispose();

					Gtk::Frame* mainFrame;  ///< frame configuration
					Gtk::Frame *infoFrame;  ///< information frame
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonBack; ///< back button
					Smartmatic::GUI::Widgets::SmartmaticButton * buttonOk;   ///< ok button

					static Smartmatic::Log::ISMTTLog* logger;   ///< logger
				};
			}
		}
	}
}

#endif /* VMINSTALLATIONCONFIRMATION_HXX_ */
