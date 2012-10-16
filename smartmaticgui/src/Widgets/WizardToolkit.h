/*
 * WizardToolkit.h
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include <gtkmm.h>
#include "Widgets/menu-option.h"
#include "Widgets/ToolkitElement.h"
#include "Widgets/WizardWidgetConfiguration.h"

#ifndef WIZARDTOOLKIT_H_
#define WIZARDTOOLKIT_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardToolkit : public Gtk::Frame
			{
				public:
					WizardToolkit(std::vector<MenuOption> optionsA, WizardWidgetConfiguration currentWizardConfiguration);
					virtual ~WizardToolkit();

					/**
					 * @brief signals definitions
					 */
					typedef sigc::signal<void, MenuOption> wizard_toolkit_element_sigc;
					wizard_toolkit_element_sigc WizardToolkitElementClickSigc()
					{
						return m_wizard_toolkit_element_sigc;
					};

				protected:
					wizard_toolkit_element_sigc m_wizard_toolkit_element_sigc;

				private:
					std::vector<MenuOption> options;
					Gtk::Table* table;
					void on_element_click(MenuOption option);
			};
		}
	}
}

#endif /* WIZARDTOOLKIT_H_ */
