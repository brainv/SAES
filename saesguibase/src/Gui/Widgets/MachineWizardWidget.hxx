/**
 * @file MachineWizardWidget.hxx
 * @brief Header machine wizard widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#ifndef MACHINEWIZARDWIDGET_HXX_
#define MACHINEWIZARDWIDGET_HXX_

#include "RunMachineWidget.hxx"
#include <Widgets/WizardWidget.h>
#include <Widgets/WizardWidgetConfiguration.h>

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
				 * @class MachineWizardWidget
				 * @brief Class machine wizard widget
				 * @date 31/03/2012
				 * @author Yadickson Soto
				 */
				class MachineWizardWidget : public RunMachineWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param menuWidget menu widget
					 * @param helpWidget help widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					MachineWizardWidget(Smartmatic::SAES::GUI::Widgets::MenuWidget * menuWidget,
							Smartmatic::SAES::GUI::Widgets::HelpWidget * helpWidget);
					/**
					 * @brief Class destroy
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual ~MachineWizardWidget();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief virtual method start widget
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void start();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

				protected:
					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method setter key
					 * @param value value key
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					virtual void SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value);

					std::string currentState; ///< curren state
					Smartmatic::GUI::Widgets::WizardWidget *wizard;   ///< The menu
					Gtk::Notebook* notebook; ///< notebook widget
					std::map<std::string, int> indexByState; ///< map wizard
					std::map<std::string, Smartmatic::GUI::Widgets::WizardWidget*> wizardWidgetByState; ///< map wizard
					std::vector<Smartmatic::GUI::Widgets::WizardWidgetConfiguration> wizardConfiguration; ///< wizard configuration
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger
				};
			}
		}
	}
}

#endif /* MACHINEWIZARDWIDGET_HXX_ */
