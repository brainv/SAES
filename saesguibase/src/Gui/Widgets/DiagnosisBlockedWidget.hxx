/**
 * @file DiagnosisBlockedWidget.hxx
 * @brief Header class diagnosis blocked
 * @date 12/06/2012
 * @author Yadickson Soto
 */

#ifndef DIAGNOSISBLOCKEDWIDGET_HXX_
#define DIAGNOSISBLOCKEDWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include "ProgressWidget.hxx"

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
				/**
				 * @class DiagnosisBlocked
				 * @brief Class diagnosis blocked
				 * @date 12/06/2012
				 * @author Yadickson Soto
				 */
				class DiagnosisBlockedWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param progress progress
					 * @date 12/06/2012
					 * @author Yadickson Soto
					 */
					DiagnosisBlockedWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
					/**
					 * @brief Class destroy
					 * @date 12/06/2012
					 * @author Yadickson Soto
					 */
					virtual ~DiagnosisBlockedWidget();
					/**
					 * @brief Method getter signal clicked
					 * @return signal clicked
					 * @date 12/06/2012
					 * @author Yadickson Soto
					 */
					Glib::SignalProxy0<void> getSignalClicked();

				protected:

					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

				private:

					Gtk::VBox * mainVBox; ///< main vbox
					Gtk::EventBox * mainEventBox; ///< main event box
					Gtk::HButtonBox * hbuttonbox; ///< hbuttonbox
					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< progress widget
					Smartmatic::GUI::Widgets::SmartmaticButton * button; ///< button
					static Smartmatic::Log::ISMTTLog* logger;   ///< logger
				};
			}
		}
	}
}

#endif /* DIAGNOSISBLOCKEDWIDGET_HXX_ */
