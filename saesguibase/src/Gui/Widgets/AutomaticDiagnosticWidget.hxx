/*
 * AutomaticDiagnosticWidget.hxx
 *
 *  Created on: 20/10/2011
 *      Author: soto
 */

#ifndef AUTOMATICDIAGNOSTICWIDGET_HXX_
#define AUTOMATICDIAGNOSTICWIDGET_HXX_

#include "ProgressWidget.hxx"
#include "DiagnosticResultWidget.hxx"
#include "DiagnosisBlockedWidget.hxx"
#include <vector>
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
				class AutomaticDiagnosticWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					AutomaticDiagnosticWidget(ProgressWidget * progress);
					virtual ~AutomaticDiagnosticWidget();

					void start();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				protected:

					void block();

					void unblock();

					void end();
					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

                    void diagnostic();
					void nextPage();
					void checkEndDiagnosis();
					void showMessage();
					void showResult();

				private:

					void getPixbufBarcode();

					unsigned int current;
					ProgressWidget * progress;
					DiagnosticResultWidget * resultWidget;
					DiagnosisBlockedWidget * diagnosisBlockedWidget; ///< diagnosis blocked widget
					Glib::Mutex mutex; ///< mutex

					std::vector <Smartmatic::SAES::Operation::Diagnosis::IDiagnosis *> diagnosisList;
					std::vector <sigc::connection> diagnosisConnectionList;
					Glib::RefPtr<Gdk::Pixbuf> pixbuffBarcode;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* AUTOMATICDIAGNOSTICWIDGET_HXX_ */
