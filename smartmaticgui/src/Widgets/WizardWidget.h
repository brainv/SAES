/*
 * WizardWidget.h
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include <vector>
#include <gtkmm.h>
#include "Widgets/WizardWidgetConfiguration.h"
#include "Widgets/WizardTimeline.h"
#include "Widgets/WizardToolkit.h"
#include "Functionalities/functionality-manager.h"
#include "Widgets/keyword-navigation-interface.h"
#include "Widgets/smartmatic-button.h"

#ifndef WIZARDWIDGET_H_
#define WIZARDWIDGET_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardWidget : public Gtk::Frame, public keywordNavigationInterface
			{
				public:
					WizardWidget(std::vector<WizardWidgetConfiguration> configuration, std::string currentState,
							Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor> *menu_manager,
							MenuWidgetConfiguration* menuConfigurationA, std::string languagePackageA = "");
					virtual ~WizardWidget();

					typedef sigc::signal<void> show_menu_sigc;
					show_menu_sigc ShowMenuSigc()
					{
						return m_show_menu_sigc;
					};

					typedef sigc::signal<void> functionality_executed_sigc;
					functionality_executed_sigc FunctionalityExecuteSigc()
					{
						return m_functionality_executed;
					};


					void SetKey(KeysActionsCode value);

					void RefreshLanguage();

				protected:
					show_menu_sigc m_show_menu_sigc;
					functionality_executed_sigc m_functionality_executed;

				private:
					std::vector<WizardWidgetConfiguration> wizardWidgetConfiguration;
					Gtk::VBox* boxPrincipal;
					WizardToolkit* toolbox;
					WizardTimeline* timeline;
					Gtk::HBox* boxCentral;
					Gtk::VBox* principalButtonBox;
					Gtk::Label* helpTitle;
					Gtk::Label* helpDetail;
					Gtk::EventBox* eventBoxTimeLine;
					Gtk::EventBox* eventBoxPrincipalButtons;
					Gtk::EventBox* eventBoxToolbox;
					Gtk::EventBox* eventBoxHelpPanel;
					Gtk::Table* principalButtonTable;
					Gtk::VBox* heplBox;
					int buttonIndex;
					std::string state;
					std::string languagePackage;
					sigc::connection toolBoxConnection;
					WizardWidgetConfiguration currentWizardConfiguration;

					MenuWidgetConfiguration* menuConfiguration;

					/**
					 * @brief	Gets a button name.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	suffix	The suffix.
					 *
					 * @return	The button name.
					 */

					std::string GetButtonName(std::string suffix);

					/**
					 * @brief	Executes the button clicked action.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	widget	If non-null, the widget.
					 * @param	_option		  	The option.
					 */
					void on_button_clicked(SmartmaticButton *widget, MenuOption _option);

					void on_toolbox_element_clicked(MenuOption option);

					std::map<SmartmaticButton*, MenuOption> optionsBybuttonList;  ///< List of options by correspond buttons

					Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor> *funct_manager;	///< Manager for funct
			};
		}
	}
}

#endif /* WIZARDWIDGET_H_ */
