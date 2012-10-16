/**
 * @file RunMachineWindow.hxx
 * @brief Header class run machine window
 * @date 02/11/2011
 * @author Yadickson Soto
 */

#ifndef RUNMACHINEWINDOW_HXX_
#define RUNMACHINEWINDOW_HXX_

#include <Gui/Windows/empty-window.h>
#include <Gui/Widgets/InstallMachineWidget.hxx>
#include <Gui/Widgets/AutomaticDiagnosticWidget.hxx>
#include <Gui/Widgets/InitiatorWidget.hxx>
#include <Gui/Widgets/id-card-widget-pm-install.h>
#include <Gui/Widgets/ContingencyCardGenWidget.h>
#include <Gui/Widgets/ReportInstallWidget.hxx>
#include <Gui/Widgets/AuthenticationWidget.hxx>
#include <Gui/Widgets/MenuWidget.hxx>
#include <Gui/Widgets/RunMachineWidget.hxx>
#include <Gui/Widgets/HelpWidget.hxx>

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
			namespace Windows
			{
				/**
				 * @class RunMachineWindow
				 * @brief class run machine window
				 * @date 02/11/2011
				 * @author Yadickson Soto
				 */
				class RunMachineWindow : public EmptyWindow
				{
				public:
					/**
					 * @brief class constructor
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					RunMachineWindow();
					/**
					 * @brief class destroy
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual ~RunMachineWindow();

				protected:

					/**
					 * @enum Step
					 * @brief enum step widgets
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					enum Step
					{
						 INSTALL_MACHINE ///< instrall machine
						,AUTOMATIC_DIAGNOSTIC ///< automatic diagnosis
						,INITIATOR ///< initiator
						,REPORT_INSTALL ///< install report
						,CONTINGENCY_CARD ///< create contingency card
						,ID_CARD_INSTALL ///< getter id member install
						,PROCESS ///< run process (wizard or voting machine)
						,END ///< end window
					};

					std::vector <Step> wizardStep; ///< wizard step

					/**
					 * @brief method step next widget
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void nextStep();

				private:

					unsigned int step;
					int authenticationPosition; ///< authentication position
					sigc::connection startHelpPrintConn;	///< The start print connection
					sigc::connection stopHelpPrintConn;	///< The stop print connection

					sigc::connection connContingency; ///< connect contingency
					sigc::connection connIdCard; ///< connect id member install
					Smartmatic::SAES::GUI::Widgets::HelpWidget * helpWidget; ///< help widget
					Smartmatic::SAES::GUI::Widgets::InstallMachineWidget * installWidget; ///< install machine widget
					Smartmatic::SAES::GUI::Widgets::AutomaticDiagnosticWidget * diagnosticWidget; ///< automatic diagnosis widget
					Smartmatic::SAES::GUI::Widgets::InitiatorWidget * initiatorWidget; ///< initiator widget
					Smartmatic::SAES::GUI::Widgets::ReportInstallWidget * reportInstallWidget; ///< report install widget
					Smartmatic::SAES::GUI::Widgets::ContingencyCardGenWidget* contingencyCardWidget; ///< contingency card generation widget
					Smartmatic::SAES::GUI::Widgets::IDCardWidgetPMInstall* idCardWidget; ///< id member card install
					Smartmatic::SAES::GUI::Widgets::MenuWidget * menuWidget; ///< menu widget
					Smartmatic::SAES::GUI::Widgets::RunMachineWidget * runMachineWidget; ///< run machine widget

					static Smartmatic::Log::ISMTTLog* logger; ///<logger

					/**
					 * @brief method run install machine
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void install();
					/**
					 * @brief method run diagnosis
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void diagnostic();
					/**
					 * @brief method run initialization
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void initialization();
					/**
					 * @brief method run report install
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
                    void reportInstall();
					/**
					 * @brief method run contingentcy generation card
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
                    void contingencyCard();
					/**
					 * @brief method run getter id member installation
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void idCardInstall();
					/**
					 * @brief method run authentication and process (wizard or voting)
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void process();
					/**
					 * @brief method block machine
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void blockMachine();
					/**
					 * @brief method run menu
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void runMenu();
					/**
					 * @brief method run machine process (wizard or voting)
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void runMachine();
					/**
					 * @brief method end getter id member install machine
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void endIdCardInstall();
					/**
					 * @brief method end generation contingency card
					 * @param type result generation card
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void endContingency(Smartmatic::SAES::GUI::Widgets::ContingencyCardGenWidget::ContingencyErrorEnumType type);
					/**
					 * @brief method execute next step widget
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void executeNextStep();
					/**
					 * @brief method end window
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void end();
					/**
					 * @brief method dispose element
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					void dispose();
					/**
					 * @brief method start
					 * @return true is start success
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual bool start();
					/**
					 * @brief method pause
					 * @date 16/05/2012
					 * @author Yadickson Soto
					 */
					virtual void pause();
					/**
					 * @brief method stop
					 * @date 02/11/2011
					 * @author Yadickson Soto
					 */
					virtual void stop();
					/**
					 * @brief method load machine widget
					 * @date 17/05/2012
					 * @author Yadickson Soto
					 */
					void load();

				protected:

					Smartmatic::SAES::GUI::Widgets::AuthenticationWidget * authenticationWidget; ///< authentication widget
				};
			}
		}
	}
}

#endif /* RUNMACHINEWINDOW_HXX_ */
