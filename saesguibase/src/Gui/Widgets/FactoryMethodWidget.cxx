/**
 * @file FactoryMethodWidget.cxx
 * @brief Body class for create widget
 * @date 03/11/2011
 * @author Yadickson Soto
 */

#include "FactoryMethodWidget.hxx"
#include "PMInstallMachineWidget.hxx"
#include "VMInstallMachineWidget.hxx"
#include "PMProgressWidget.hxx"
#include "VMProgressWidget.hxx"
#include "PMPollingPlaceInfoWidget.hxx"
#include "VMPollingPlaceInfoWidget.hxx"
#include "PMAuthenticationPollingPlaceInfoWidget.hxx"
#include "VMAuthenticationPollingPlaceInfoWidget.hxx"
#include "FillTableColumnFixedWidget.hxx"
#include "FillTableColumnDynamicWidget.hxx"
#include "PMAuthenticationWidget.hxx"
#include "VMAuthenticationWidget.hxx"
#include "MachineWizardWidget.hxx"
#include "MachineVotingWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;

FactoryMethodWidget::FactoryMethodWidget()
{

}

FactoryMethodWidget::~FactoryMethodWidget()
{

}

InstallMachineWidget * FactoryMethodWidget::createInstallMachineWidget(ProgressWidget * progress, PollingPlaceInfoWidget * pollingPlaceInfo)
{
	InstallMachineWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			{
				ProgressWidget * removeCardWidget = FactoryMethodWidget::createProgressWidget();
				widget = new PMInstallMachineWidget(progress, removeCardWidget, pollingPlaceInfo);
			}
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new VMInstallMachineWidget(progress, pollingPlaceInfo);
			break;
	}

	return widget;
}

ProgressWidget * FactoryMethodWidget::createProgressWidget()
{
	ProgressWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			widget = new PMProgressWidget();
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new VMProgressWidget();
			break;
	}

	return widget;
}

PollingPlaceInfoWidget * FactoryMethodWidget::createPollingPlaceInfoWidget()
{
	PollingPlaceInfoWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			widget = new PMPollingPlaceInfoWidget();
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new VMPollingPlaceInfoWidget();
			break;
	}

	return widget;
}

PollingPlaceInfoWidget * FactoryMethodWidget::createAuthenticationPollingPlaceInfoWidget()
{
	PollingPlaceInfoWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			widget = new PMAuthenticationPollingPlaceInfoWidget();
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new VMAuthenticationPollingPlaceInfoWidget();
			break;
	}

	return widget;
}

BallotOptionButtonWidget * FactoryMethodWidget::createBallotOptionButtonWidget()
{
	BallotOptionButtonWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getBallotOptionButton())
	{
		case ViewButtonConfiguration::CONFIGURATION_EXPAND_BUTTONS:
			widget = new BallotOptionButtonWidget(true);
			break;
		case ViewButtonConfiguration::CONFIGURATION_SEPARATE_BUTTONS:
			widget = new BallotOptionButtonWidget(false);
			break;
	}

	widget->update();

	return widget;
}

PartyButtonWidget * FactoryMethodWidget::createPartyButtonWidget()
{
	PartyButtonWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getPartyButton())
	{
		case ViewButtonConfiguration::CONFIGURATION_EXPAND_BUTTONS:
			widget = new PartyButtonWidget(true);
			break;
		case ViewButtonConfiguration::CONFIGURATION_SEPARATE_BUTTONS:
			widget = new PartyButtonWidget(false);
			break;
	}

	widget->initialize();
	widget->update();

	return widget;
}

TableCenterWidget * FactoryMethodWidget::createTableWidget()
{
	TableCenterWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getBallotOptionTable())
	{
		case ViewTableConfiguration::CONFIGURATION_COLUMN_FIXED:
			widget = new TableCenterWidget(true);
			break;
		case ViewTableConfiguration::CONFIGURATION_COLUMN_CENTER:
			widget = new TableCenterWidget(false);
			break;
	}

	return widget;
}

FillTableWidget * FactoryMethodWidget::createFillTableWidget(TableCenterWidget * tableWidget)
{
	FillTableWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getFillPrincipal())
	{
		case FillPrincipalConfiguration::CONFIGURATION_FILL_COLUMN_FIXED:
			widget = new FillTableColumnFixedWidget(tableWidget);
			break;
		case FillPrincipalConfiguration::CONFIGURATION_FILL_COLUMN_DYNAMIC:
			widget = new FillTableColumnDynamicWidget(tableWidget);
			break;
	}

	return widget;
}

AuthenticationWidget * FactoryMethodWidget::createAuthenticationWidget(PollingPlaceInfoWidget * info)
{
	AuthenticationWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			widget = new PMAuthenticationWidget(info);
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new VMAuthenticationWidget(info);
			break;
	}

	return widget;
}

RunMachineWidget * FactoryMethodWidget::createRunMachineWidget(MenuWidget * menuWidget, HelpWidget * helpWidget)
{
	RunMachineWidget * widget = NULL;

	switch (SAESGUIConfigurationManager::Current()->getStartConfiguration().getInfoMachine())
	{
		case InfoMachineConfiguration::CONFIGURATION_PM:
			widget = new MachineWizardWidget(menuWidget, helpWidget);
			break;
		case InfoMachineConfiguration::CONFIGURATION_VM:
			widget = new MachineVotingWidget(menuWidget, helpWidget);
			break;
	}

	return widget;
}
