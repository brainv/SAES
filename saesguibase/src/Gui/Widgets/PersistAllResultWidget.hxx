/**
 * @file PersistAllResultWidget.hxx
 * @brief Header class persist all result files widget
 * @date 17/02/2012
 * @author Yadickson Soto
 */

#ifndef PERSISTALLRESULTWIDGET_HXX_
#define PERSISTALLRESULTWIDGET_HXX_

#include <Widgets/wizard-widget-base.h>
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
				 * @class PersistAllResultWidget
				 * @brief Class persist all result files widget
				 * @date 17/02/2012
				 * @author Yadickson Soto
				 * @see WizardWidgetBase
				 */
				class PersistAllResultWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:
					/**
					 * @brief Class constructor
					 * @param progress widget with label and image
					 * @date 17/02/2012
					 * @author Yadickson Soto
					 */
					PersistAllResultWidget(ProgressWidget * progress);

					/**
					 * @brief Class destroy
					 * @date 17/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~PersistAllResultWidget();

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

					/**
					 * @brief	Method getter widget name
					 * @return widget name
					 * @date 17/02/2012
					 * @author	Yadickson Soto
					 */
					virtual Glib::ustring GetWidgetName();

					/**
					 * @brief Method getter is enabled button exit wizard
					 * @return true is enabled button exit wizard
					 * @date 22/02/2012
					 * @author Yadickson Soto
					 */
					virtual bool isEnabledButtonExitWizard();

				private:

					ProgressWidget * progress; ///< widget with label and image
					static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					/**
					 * @brief	Method start persist codi files
					 * @date 17/02/2012
					 * @author	Yadickson Soto
					 */
					void start();

					/**
					 * @brief	Method end persist codi files
					 * @date 17/02/2012
					 * @author	Yadickson Soto
					 */
					void end();

					/**
					 * @brief	Method start persist codi files
					 * @param text new text for widget
					 * @date 17/02/2012
					 * @author	Yadickson Soto
					 */
					void updateLabel(std::string text);
				};
			}
		}
	}
}
#endif /* PERSISTALLRESULTWIDGET_HXX_ */
