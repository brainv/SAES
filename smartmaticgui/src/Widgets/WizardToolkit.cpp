/*
 * WizardToolkit.cpp
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "Environment/Configurations/resource-path-provider.h"
#include "WizardToolkit.h"
#include "System/IO/File.h"
#include "Environment/Configurations/resource-path-provider.h"

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

using namespace Gtk;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;

WizardToolkit::WizardToolkit(std::vector<MenuOption> optionsA, WizardWidgetConfiguration currentWizardConfiguration)
{
	set_shadow_type(Gtk::SHADOW_NONE);
	options = optionsA;

	table = manage(new Gtk::Table(1, options.size(), true));

	for(unsigned int i=0; i<options.size(); i++)
	{
		std::string image_path = Smartmatic::Environment::ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, options[i].imageKey);

		ToolkitElement* toolKitElement = NULL;

		if(File::canOpenFile(image_path))
			toolKitElement = manage(new ToolkitElement(image_path,
				options[i].nameKey, options[i], currentWizardConfiguration));
		else
			toolKitElement = manage(new ToolkitElement(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, "ui/image-not-found.gif"),
				options[i].nameKey, options[i], currentWizardConfiguration));

		toolKitElement->ToolkitElementClickSigc().connect(sigc::mem_fun(this,
				&WizardToolkit::on_element_click));

		table->attach(*toolKitElement, i, i+1, 0, 1, Gtk::FILL, Gtk::FILL, 1, 1);
	}

	this->add(*table);
	this->show_all_children(true);
}

void WizardToolkit::on_element_click(MenuOption option)
{
	m_wizard_toolkit_element_sigc.emit(option);
}

WizardToolkit::~WizardToolkit() {
	// TODO Auto-generated destructor stub
}
