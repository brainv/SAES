/**
 * @file RunMachineWidget.cxx
 * @brief Body machine wizard widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#include "RunMachineWidget.hxx"
#include <Operation/WindowsManager.hxx>
#include <Operation/MachineOperationManager.hxx>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Operation;
using namespace Smartmatic::SAES::Operation;

RunMachineWidget::RunMachineWidget(MenuWidget * menuWidget, HelpWidget * helpWidget)
: StepWidget()
{
	this->menuWidget = menuWidget;
	this->helpWidget = helpWidget;
	this->setHelpWidget(helpWidget);
}

RunMachineWidget::~RunMachineWidget()
{
	remove();
}

void RunMachineWidget::blockMachine()
{
	if (!MachineOperationManager::getInstance()->getAlarmController()->isAlarmPending())
	{
		MachineOperationManager::getInstance()->getAlarmController()->setMessage(N_("Smartmatic.SAES.GUI.Widgets.WaitingCardWidget.BackButtonPressed"));
	}

	signalBlock.emit();
}

void RunMachineWidget::runMenu()
{
	signalRunMenu.emit();
}

sigc::signal<void> RunMachineWidget::getSignalBlock()
{
	return signalBlock;
}

sigc::signal<void> RunMachineWidget::getSignalRunMenu()
{
	return signalRunMenu;
}
