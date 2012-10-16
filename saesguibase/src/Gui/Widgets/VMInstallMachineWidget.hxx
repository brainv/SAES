/*
 * VMInstallMachineWidget.hxx
 *
 *  Created on: 02/11/2011
 *      Author: soto
 */

#ifndef VMINSTALLMACHINEWIDGET_HXX_
#define VMINSTALLMACHINEWIDGET_HXX_

#include <Gui/Widgets/InstallMachineWidget.hxx>
#include <Widgets/vm-installation-widget.h>
#include <Gui/Widgets/ProgressWidget.hxx>
#include <Gui/Widgets/VMInstallationConfirmation.hxx>
#include <Gui/Widgets/PollingPlaceInfoWidget.hxx>

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
				class VMInstallMachineWidget : public InstallMachineWidget
				{
				public:
					VMInstallMachineWidget(ProgressWidget * progressWidget, PollingPlaceInfoWidget * pollingPlaceInfoWidget);
					virtual ~VMInstallMachineWidget();
					virtual void stop();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				private:

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

					void login();
					void authentication(std::string password);
					void showProgressLogin();
					void checkData();
					bool checkCard();
					void readCard();
					void showInfo();
					void end();

					std::string center;
					std::string password;
					bool loginOk;
					bool wasPresent;
					sigc::connection conn;
					Gtk::Label * messageError;
					Smartmatic::GUI::Widgets::VMInstallationWidget * installWidget;
					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget;
					Smartmatic::SAES::GUI::Widgets::VMInstallationConfirmation * infoMessage;
					Smartmatic::SAES::GUI::Widgets::PollingPlaceInfoWidget * pollingPlaceInfoWidget;

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* VMINSTALLMACHINEWIDGET_HXX_ */
