/**
 * @file InfoStepWidget.hxx
 * @brief Header message widget
 * @date 29/03/2012
 * @author Yadickson Soto
 */

#ifndef INFOSTEPWIDGET_HXX_
#define INFOSTEPWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/StepWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class InfoStepWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					InfoStepWidget();
					/**
					 * @brief Class constructor
					 * @param info info
					 * @param timeout exit
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					InfoStepWidget(std::string info, int timeout);
					/**
					 * @brief Class destroy
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~InfoStepWidget();
					/**
					 * @brief method setter info
					 * @param info info
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					void setInfo(std::string info);
					/**
					 * @brief method setter timeout
					 * @param timeout
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					void setTimeout(int timeout);
					/**
					 * @brief method getter timeout
					 * @return timeout
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					int getTimeout();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

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

				private:

					std::string info; ///< info message
					int timeout; ///< timeout message
					Gtk::Label * labelInfo; ///< message language
				};
			}
		}
	}
}

#endif /* INFOSTEPWIDGET_HXX_ */
