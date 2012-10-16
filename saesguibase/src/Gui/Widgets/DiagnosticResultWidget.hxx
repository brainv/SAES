/*
 * DiagnosticResultWidget.hxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#ifndef DIAGNOSTICRESULTWIDGET_HXX_
#define DIAGNOSTICRESULTWIDGET_HXX_

#include <gtkmm.h>
#include <Operation/Diagnosis/IDiagnosis.hxx>
#include <Widgets/smartmatic-button.h>
#include "DeviceResultWidget.hxx"
#include <list>
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
				class DiagnosticResultWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					DiagnosticResultWidget(std::vector <Smartmatic::SAES::Operation::Diagnosis::IDiagnosis *> & diagnosis);
					virtual ~DiagnosticResultWidget();

					void start();

				protected:
					void end();
					void fail();
					void shutDown();
					void initialize();
					void dispose();

				private:
					std::vector <Smartmatic::SAES::Operation::Diagnosis::IDiagnosis *> & diagnosis;
					std::list < DeviceResultWidget * > deviceList;
					bool mandatoryFail;
					Gtk::Frame * mainFrame;
					Gtk::Frame * centerFrame;
					Gtk::VBox * mainVbox;
					Gtk::VBox * centerVbox;
					Gtk::HBox * centerHbox;
					Gtk::Label * infoLabel;
					Gtk::VButtonBox * buttonbox;
					Smartmatic::GUI::Widgets::SmartmaticButton * actionButton;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* DIAGNOSTICRESULTWIDGET_HXX_ */
