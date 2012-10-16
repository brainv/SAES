/**
 * @file DeviceResultWidget.hxx
 * @brief Body class device result widget
 * @date 24/10/2011
 * @author Yadickson Soto
 */

#ifndef DEVICERESULTWIDGET_HXX_
#define DEVICERESULTWIDGET_HXX_

#include <gtkmm.h>
#include <Operation/Diagnosis/IDiagnosis.hxx>
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
				class DeviceResultWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					DeviceResultWidget(Smartmatic::SAES::Operation::Diagnosis::IDiagnosis * diagnosis);
					virtual ~DeviceResultWidget();
					Smartmatic::SAES::Operation::Diagnosis::IDiagnosis * getDiagnosis();
					void update();

				protected:
					void initialize();
					void dispose();

				private:
					Gtk::Frame * mainFrame;
					Gtk::Label * label;
					Gtk::Image * image;
					Smartmatic::SAES::Operation::Diagnosis::IDiagnosis * diagnosis;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* DEVICERESULTWIDGET_HXX_ */
