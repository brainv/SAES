/*
 * InitiatorWidget.hxx
 *
 *  Created on: 24/10/2011
 *      Author: soto
 */

#ifndef INITIATORWIDGET_HXX_
#define INITIATORWIDGET_HXX_

#include <gtkmm.h>
#include <Gui/Widgets/ProgressWidget.hxx>
#include <Operation/Initiator/InitializationStatus.hxx>
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
				class InitiatorWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					InitiatorWidget(ProgressWidget * progress);
					virtual ~InitiatorWidget();

					void start();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				protected:
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

                    void end();
                    void statusReport(Smartmatic::SAES::Operation::Initiator::InitializationStatus & status, bool finalized);
                    void showMessage();
                    void showEndMessage();

				private:
					ProgressWidget * progress;
					Smartmatic::SAES::Operation::Initiator::InitializationStatus status;
					sigc::connection conn;
					static Smartmatic::Log::ISMTTLog* logger; /***<logger*/
				};
			}
		}
	}
}

#endif /* INITIATORWIDGET_HXX_ */
