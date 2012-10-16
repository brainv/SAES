/*
 * HelpExitButtons.cc
 *
 *  Created on: May 31, 2011
 *      Author: Juan Carlos Delgado
 */

#include "Widgets/HelpExitButtons.h"
#include <Environment/Configurations/resource-path-provider.h>

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

using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;

HelpExitButtons::HelpExitButtons(ExitButtonListener *exitListener, bool showExitButton,
								 HelpButtonListener* helpListener, bool showHelpButton)
{
	exitButton = NULL;
	helpButton = NULL;

	this->exitListener = exitListener;
	this->helpListener = helpListener;

	helpButton = new SmartmaticButton();
	helpButton->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/help.jpg"));
	helpButton->WidgetsPosition(0,5,0);
	helpButton->signal_clicked().connect( sigc::mem_fun(*this,&HelpExitButtons::on_helpButton_clicked) );
	helpButton->set_sensitive(false);
	helpButton->set_visible(showHelpButton);
	helpButton->set_no_show_all();
	pack_start(*helpButton, false, false);

	exitButton = new SmartmaticButton();
	exitButton->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/exit.jpg"));
	exitButton->WidgetsPosition(0,5,0);
	exitButton->signal_clicked().connect( sigc::mem_fun(*this,&HelpExitButtons::on_exitButton_clicked) );
	exitButton->set_sensitive(false);
	exitButton->set_visible(showExitButton);
	exitButton->set_no_show_all();
	pack_start(*exitButton, false, false);

	show_all_children();
	show();
}

HelpExitButtons::~HelpExitButtons()
{
	if(exitButton)
	{
		delete exitButton;
		exitButton = NULL;
	}

	if(helpButton)
	{
		delete helpButton;
		helpButton = NULL;
	}
}

void HelpExitButtons::on_exitButton_clicked()
{
	if(exitListener)
	{
		exitListener->Exit();
	}
}

void HelpExitButtons::on_helpButton_clicked()
{
	if(helpListener)
		helpListener->ShowHelp();
}

void HelpExitButtons::ExitButton_SetSensitive(bool sensitive)
{
	if(exitButton)
		exitButton->set_sensitive(sensitive);
}

void HelpExitButtons::ExitButton_SetVisible(bool visible)
{
	if(exitButton)
		exitButton->set_visible(visible);
}

void HelpExitButtons::ExitButton_SetName(std::string name)
{
	if(exitButton)
		exitButton->set_name (name);
}

void HelpExitButtons::HelpButton_SetSensitive(bool sensitive)
{
	if(helpButton)
		helpButton->set_sensitive(sensitive);
}

void HelpExitButtons::HelpButton_SetVisible(bool visible)
{
	if(helpButton)
		helpButton->set_visible(visible);
}

void HelpExitButtons::HelpButton_SetName(std::string name)
{
	if(helpButton)
		helpButton->set_name (name);
}
