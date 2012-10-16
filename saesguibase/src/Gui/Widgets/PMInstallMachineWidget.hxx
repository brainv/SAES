/*
 * PMInstallMachineWidget.hxx
 *
 *  Created on: 19/10/2011
 *      Author: soto
 */

#ifndef PMINSTALLMACHINEWIDGET_HXX_
#define PMINSTALLMACHINEWIDGET_HXX_

#include <Gui/Widgets/InstallMachineWidget.hxx>
#include <Gui/Widgets/LoginWidget.hxx>
#include <Gui/Widgets/InfoMessageWidget.hxx>
#include <Gui/Widgets/PollingPlaceInfoWidget.hxx>
#include <Gui/Widgets/ContingencyWidget.hxx>
#include <Gui/Widgets/ProgressWidget.hxx>
#include <Gui/Widgets/LanguageInstallWidget.hxx>
#include <Gui/Widgets/ReportInstallWidget.hxx>

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
				class PMInstallMachineWidget : public InstallMachineWidget
				{

				public:
					PMInstallMachineWidget(ProgressWidget * progressWidget,
							ProgressWidget * removeCardWidget,
							PollingPlaceInfoWidget * pollingPlaceInfoWidget);

					virtual ~PMInstallMachineWidget();
					virtual void stop();
					/**
					 * @brief virtual method getter is visible title frame
					 * @return true is title frame visible
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual bool isTitle();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();

				protected:

                    void contingency();
                    void authentication();
                    void error();
                    void language();
                    void info();
                    void print();
                    void install();
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

					Gtk::Widget * getMessageLoginError();
					Gtk::Widget * getMessageLoginOk();

                    void login();
                    void showProgressLogin();
                    void checkData();
                    bool checkCard();
                    void end();

				private:

					bool firstTime;
					bool showImages;
					bool forceText;
					bool loginOk;
					bool usedContingencyCardData;
					bool isPresent;

					std::string center;
					std::string password;
					std::string openingCode;
					bool centerCaseSensitive;

                	Gtk::Label * message;
                	Gtk::Image * image;

					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progressWidget;
					Smartmatic::SAES::GUI::Widgets::PollingPlaceInfoWidget * pollingPlaceInfoWidget;
					Smartmatic::SAES::GUI::Widgets::LoginWidget * loginWidget;
					Smartmatic::SAES::GUI::Widgets::InfoMessageWidget * infoMessage;
					Smartmatic::SAES::GUI::Widgets::ContingencyWidget * contingencyWidget;
					Smartmatic::SAES::GUI::Widgets::ProgressWidget * removeCardWidget;
					Smartmatic::SAES::GUI::Widgets::LanguageInstallWidget * languageWidget;
					Smartmatic::SAES::GUI::Widgets::ReportInstallWidget * reportInstall;

					sigc::connection cardConn;
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/
				};
			}
		}
	}
}

#endif /* PMINSTALLMACHINEWIDGET_HXX_ */
