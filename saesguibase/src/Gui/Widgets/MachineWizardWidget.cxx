/**
 * @file MachineWizardWidget.cxx
 * @brief Body machine wizard widget
 * @date 31/03/2012
 * @author Yadickson Soto
 */

#include "MachineWizardWidget.hxx"
#include <Functionalities/saes-functionality-manager.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include <Functionalities/saes-functionality-manager.h>
#include <Functionalities/change-language-functionality.h>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::Log;

ISMTTLog* MachineWizardWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.MachineWizardWidget",GETTEXT_PACKAGE);

MachineWizardWidget::MachineWizardWidget(MenuWidget * menuWidget, HelpWidget * helpWidget)
: RunMachineWidget(menuWidget, helpWidget)
{
	this->notebook = NULL;

	this->setHelp(true);
	this->setExit(true);

	initialize();
	refresh();
	setWidget(notebook);
}

MachineWizardWidget::~MachineWizardWidget()
{
	dispose();

	this->remove();

	if (notebook)
	{
		delete notebook;
		notebook = NULL;
	}
}

void MachineWizardWidget::initialize()
{
	notebook = new Gtk::Notebook();
	notebook->set_show_tabs(false);
	notebook->set_show_border(false);

	wizardConfiguration = SAESGUIConfigurationManager::Current()->GetFunctionalityWizardConfiguration();

	SaesFunctionalityManager *menu_manager = SaesFunctionalityManager::Current();
	MenuWidgetConfiguration * conf = SAESGUIConfigurationManager::Current()->GetMachineWidgetConfiguration(SAESGUIConfigurationManager::votingMachine);
	currentState = "";

	std::vector<std::string> status;

	for(unsigned int j = 0; j < wizardConfiguration.size(); j++)
	{
		status.push_back(wizardConfiguration[j].getStateEnum());
	}

	int index = 0;

	for(unsigned int i=0; i<status.size(); i++)
	{
		wizard = new WizardWidget(wizardConfiguration, status[i], menu_manager, conf, GETTEXT_PACKAGE);
		wizard->ShowMenuSigc().connect(sigc::mem_fun(this, &MachineWizardWidget::runMenu));
		wizard->set_visible(true);
		notebook->append_page(*wizard);

		indexByState.insert(std::pair<std::string, int>(status[i], index));
		wizardWidgetByState.insert(std::pair<std::string, WizardWidget*>(status[i], wizard));
		index++;
	}
}

void MachineWizardWidget::start()
{

}

void MachineWizardWidget::dispose()
{

}

void MachineWizardWidget::refresh()
{
	std::string status = MachineOperationManager::getInstance()->getOperationStatus()->getElectionStatusWrapper()->getStringStatus();

	if(status != currentState)
	{
		currentState = status;
		WizardWidgetConfiguration config = WizardWidgetConfiguration::GetWizardWidgetConfigurationByState(wizardConfiguration, currentState);
		helpWidget->setInfo(config.getTitleKey(), config.getImageHelp(), config.getPdfHelp());
		notebook->set_current_page(indexByState[currentState]);
	}

	(wizardWidgetByState[currentState])->RefreshLanguage();

	logger->Debug ("CurrentStatus is: " + currentState);
}

std::string MachineWizardWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.WizardWindow.Title");
}

void MachineWizardWidget::SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value)
{
	wizard->SetKey(value);
}
