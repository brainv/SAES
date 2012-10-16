/*
 * ToolkitElement.h
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "Widgets/WizardWidgetConfiguration.h"

#ifndef TOOLKITELEMENT_H_
#define TOOLKITELEMENT_H_

#include <gtkmm.h>
#include "Widgets/menu-option.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ToolkitElement : public Gtk::Frame
			{
				public:
					ToolkitElement(std::string imagepath, std::string messageA, MenuOption optionA,
							WizardWidgetConfiguration currentWizardConfiguration,  bool useMessage = false);
					virtual ~ToolkitElement();

					/**
					 * @brief signals definitions
					 */
					typedef sigc::signal<void, MenuOption> toolkit_element_sigc;
					toolkit_element_sigc ToolkitElementClickSigc()
					{
						return m_toolkit_element_sigc;
					};

				protected:
					toolkit_element_sigc m_toolkit_element_sigc;
					virtual bool on_eventbox_clicked(GdkEventButton* event);

				private:
					Gtk::Image* image;
					std::string message;
					Gtk::VBox* vbox;
					Gtk::EventBox* clickEventBox;
					Gtk::Label* title;
					MenuOption option;

			};
		}
	}
}

#endif /* TOOLKITELEMENT_H_ */
