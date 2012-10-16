/*
 * MenuWidget.cxx
 *
 *  Created on: 29/03/2012
 *      Author: yadickson
 */

#include "MenuWidget.hxx"
#include "Environment/Configurations/resource-path-provider.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Functionalities/saes-functionality-manager.h"
#include "Functionalities/menu-option-descriptor.h"
#include <Functionalities/change-language-functionality.h>
#include <vector>

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
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Functionality;

bool MenuWidget::reloadMenu = true;

MenuWidget::MenuWidget()
: StepWidget()
{
	menu = NULL;

	initialize();
	refresh();

	this->show();
}

MenuWidget::~MenuWidget()
{
	dispose();
}

void MenuWidget::refresh()
{
	if (reloadMenu)
	{
		reloadMenu = false;
		dispose();

		std::vector < MenuOption > options = SAESGUIConfigurationManager::Current()->GetMenuOptionConfiguration();
		SaesFunctionalityManager * menu_manager = SaesFunctionalityManager::Current();
		MenuWidgetConfiguration * conf = SAESGUIConfigurationManager::Current()->GetMachineWidgetConfiguration(SAESGUIConfigurationManager::votingMachine);

		menu = new MenuWidgetmm(options, menu_manager, NULL, conf);
		setWidget(menu);
	}
}

void MenuWidget::initialize()
{

}

void MenuWidget::dispose()
{
	this->remove();

	if (menu)
	{
		delete menu;
		menu = NULL;
	}
}

void MenuWidget::SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value)
{
	menu->SetKey(value);
}

std::string MenuWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Windows.MenuWindow.Title");
}
