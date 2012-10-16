/**
 * @file FactoryMethodWidget.hxx
 * @brief Header class for create widget
 * @date 03/11/2011
 * @author Yadickson Soto
 */

#ifndef FACTORYMETHODWIDGET_HXX_
#define FACTORYMETHODWIDGET_HXX_


#include "InstallMachineWidget.hxx"
#include "ProgressWidget.hxx"
#include "PollingPlaceInfoWidget.hxx"
#include "BallotOptionButtonWidget.hxx"
#include "PartyButtonWidget.hxx"
#include <Widgets/TableCenterWidget.hxx>
#include "FillTableWidget.hxx"
#include "AuthenticationWidget.hxx"
#include "RunMachineWidget.hxx"
#include "MenuWidget.hxx"
#include "HelpWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class FactoryMethodWidget
				 * @brief Class for create widget
				 * @date 03/11/2011
				 * @author Yadickson Soto
				 */
				class FactoryMethodWidget
				{
				protected:

					/**
					 * @brief Class constructor
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					FactoryMethodWidget();

				public:

					/**
					 * @brief Class destroy
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					virtual ~FactoryMethodWidget();
					/**
					 * @brief Method for create install machine widget
					 * @param progress progress widget
					 * @param pollingPlaceInfo polling place info
					 * @return new widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static InstallMachineWidget * createInstallMachineWidget(ProgressWidget * progress, PollingPlaceInfoWidget * pollingPlaceInfo);
					/**
					 * @brief Method for create progress widget
					 * @return progress widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static ProgressWidget * createProgressWidget();
					/**
					 * @brief Method for create polling place info widget
					 * @return polling place info widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static PollingPlaceInfoWidget * createPollingPlaceInfoWidget();
					/**
					 * @brief Method for create authentication polling place info widget
					 * @return authentication polling place info widget
					 * @date 03/11/2011
					 * @author Yadickson Soto
					 */
					static PollingPlaceInfoWidget * createAuthenticationPollingPlaceInfoWidget();
					/**
					 * @brief Method for create ballot option button widget
					 * @return ballot option button widget
					 * @date 12/03/2012
					 * @author Yadickson Soto
					 */
					static BallotOptionButtonWidget * createBallotOptionButtonWidget();
					/**
					 * @brief Method for create party button widget
					 * @return party button widget
					 * @date 13/03/2012
					 * @author Yadickson Soto
					 */
					static PartyButtonWidget * createPartyButtonWidget();
					/**
					 * @brief Method for create table widget
					 * @return table widget
					 * @date 15/03/2012
					 * @author Yadickson Soto
					 */
					static Smartmatic::GUI::Widgets::TableCenterWidget * createTableWidget();
					/**
					 * @brief Method for create fill table widget
					 * @param tableWidget table widget
					 * @return fill table widget
					 * @date 15/03/2012
					 * @author Yadickson Soto
					 */
					static FillTableWidget * createFillTableWidget(Smartmatic::GUI::Widgets::TableCenterWidget * tableWidget);
					/**
					 * @brief Method for create authentication widget
					 * @param info info widget
					 * @return authentication widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					static AuthenticationWidget * createAuthenticationWidget(PollingPlaceInfoWidget * info);
					/**
					 * @brief Method for create machine process widget
					 * @param menuWidget manu widget
					 * @param helpWidget help widget
					 * @return machine process widget
					 * @date 31/03/2012
					 * @author Yadickson Soto
					 */
					static RunMachineWidget * createRunMachineWidget(MenuWidget * menuWidget, HelpWidget * helpWidget);
				};
			}
		}
	}
}

#endif /* FACTORYMETHODWIDGET_HXX_ */
