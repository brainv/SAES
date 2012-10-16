/**
 * @file RunMachineWidget.hxx
 * @brief Header machine wizard widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#ifndef RUMMACHINEWIDGET_HXX_
#define RUMMACHINEWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include "HelpWidget.hxx"
#include "MenuWidget.hxx"

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
				 * @class RunMachineWidget
				 * @brief Class machine wizard widget
				 * @date 31/03/2012
				 * @author Yadickson Soto
				 */
				class RunMachineWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param menuWidget menu widget
					 * @param helpWidget help widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					RunMachineWidget(Smartmatic::SAES::GUI::Widgets::MenuWidget * menuWidget,
							Smartmatic::SAES::GUI::Widgets::HelpWidget * helpWidget);
					/**
					 * @brief Class destroy
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~RunMachineWidget();
					/**
					 * @brief method start
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void start() = 0;
					/**
					 * @brief method getter signal block
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalBlock();
					/**
					 * @brief method getter signal run menu
					 * @return signal
					 * @date 22/04/2012
					 * @author Yadickson Soto
					 */
					sigc::signal<void> getSignalRunMenu();

				protected:

					sigc::signal<void> signalBlock; ///< signal block
					sigc::signal<void> signalRunMenu; ///< signal menu

				protected:
					/**
					 * @brief method block widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void blockMachine();
					/**
					 * @brief method run menu
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					void runMenu();

					Smartmatic::SAES::GUI::Widgets::MenuWidget * menuWidget; ///< menu widget
					Smartmatic::SAES::GUI::Widgets::HelpWidget * helpWidget; ///< help widget
				};
			}
		}
	}
}

#endif /* RUMMACHINEWIDGET_HXX_ */
