/**
 * @file PersistCodiFilesWidget.hxx
 * @brief Header class persist codi files widget
 * @date 16/02/2012
 * @author Yadickson Soto
 */

#ifndef PERSISTCODIFILESWIDGET_HXX_
#define PERSISTCODIFILESWIDGET_HXX_

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
				 * @class PersistCodiFilesWidget
				 * @brief Class persist codi files widget
				 * @date 16/02/2012
				 * @author Yadickson Soto
				 * @see WizardWidgetBase
				 */
				class PersistCodiFilesWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:
					/**
					 * @brief Class constructor
					 * @param progress widget with label and image
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					PersistCodiFilesWidget(ProgressWidget * progress);

					/**
					 * @brief Class destroy
					 * @date 16/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~PersistCodiFilesWidget();

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
					 * @date 16/02/2012
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
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void start();

					/**
					 * @brief	Method end persist codi files
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void end();

					/**
					 * @brief	Method start persist codi files
					 * @param text new text for widget
					 * @date 16/02/2012
					 * @author	Yadickson Soto
					 */
					void updateLabel(std::string text);
				};
			}
		}
	}
}
#endif /* PERSISTCODIFILESWIDGET_HXX_ */
