/*
 * WizardWidgetConfiguration.h
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include <vector>
#include "Widgets/menu-option.h"
#include "Widgets/smartmatic-button.h"
#include "Widgets/menu-widget-configuration.h"
#include "Configuration/label-configuration.h"

#ifndef WIZARDWIDGETCONFIGURATION_H_
#define WIZARDWIDGETCONFIGURATION_H_

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardWidgetConfiguration
			{
				public:
					WizardWidgetConfiguration();
					virtual ~WizardWidgetConfiguration();

					static std::vector<MenuOption> GetCurrentToolbox(std::vector<WizardWidgetConfiguration> configuration, std::string currentState);

					static std::vector<MenuOption> GetCurrentPrincipaButtonBox(std::vector<WizardWidgetConfiguration> configuration, std::string currentState);

					static WizardWidgetConfiguration GetWizardWidgetConfigurationByState(std::vector<WizardWidgetConfiguration> configuration, std::string currentState);

					bool isState(std::string value);
					std::vector<MenuOption>  getToolbox();
					std::vector<MenuOption> getPrincipalOptions();

					std::string getStateEnum();
					std::string getStateName();
					std::string getStateDescription();
					std::string getStateHelpTitleKey();
					std::string getStateHelpContentKey();
					std::string getStateHelpRelativeImagePath();
					std::string getTimelineNameKey();
					std::string getTimelineDescriptionKey();
					std::string gettimelineRelativeImagePath();
					int getToolboxElementWidth();
					int getToolboxElementHeight();
					Smartmatic::GUI::Configuration::LabelConfiguration getButtonsLabelConfiguration();
					Smartmatic::GUI::Configuration::LabelConfiguration getTitleHelpLabelConfiguration();
					Smartmatic::GUI::Configuration::LabelConfiguration getHelpLabelConfiguration();

					std::string getHelpTitle();
					std::string getHelpContent();

					void setToolbox(std::vector<MenuOption> value);
					void setPrincipalOptions(std::vector<MenuOption> value);

					void setStateEnum(std::string value);
					void setStateName(std::string value);
					void setStateDescription(std::string value);
					void setStateHelpTitleKey(std::string value);
					void setStateHelpContentKey(std::string value);
					void setStateHelpRelativeImagePath(std::string value);
					void setTimelineNameKey(std::string value);
					void setTimelineDescriptionKey(std::string value);
					void settimelineRelativeImagePath(std::string value);
					void setToolboxElementWidth(int value);
					void setToolboxElementHeight(int value);

					int getEnumIntState();
					void setEnumIntState(int value);
					bool isEnumIntState(int value);

					void setButtonsLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value);
					void setTitleHelpLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value);
					void setHelpLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value);

					std::string getImageHelp();
					std::string getPdfHelp();
					std::string getTitleKey();
					bool getUseHelp();

					void setImageHelp(std::string value);
					void setPdfHelp(std::string value);
					void setTitleKey(std::string value);
					void setUseHelp(bool value);

				private:
					std::vector<MenuOption> options;
					std::vector<MenuOption> toolkit;

					std::string stateEnum;
					std::string state_Name;
					std::string state_Description;

					std::string stateHelp_TitleKey;
					std::string stateHelp_ContentKey;
					std::string stateHelp_RelativeImagePath;

					std::string timeline_NameKey;
					std::string timeline_DescriptionKey;
					std::string timeline_RelativeImagePath;

					std::string helpWindow_ImageHelp;
					std::string helpWindow_PdfHelp;
					std::string helpWindow_TitleKey;
					bool helpWindow_UseHelp;

					int toolboxElementWidth;
					int toolboxElementHeight;

					int enumIntState;

					Smartmatic::GUI::Configuration::LabelConfiguration buttonsLabelConfiguration;
					Smartmatic::GUI::Configuration::LabelConfiguration titleHelpLabelConfiguration;
					Smartmatic::GUI::Configuration::LabelConfiguration helpLabelConfiguration;
			};
		}
	}
}


#endif /* WIZARDWIDGETCONFIGURATION_H_ */
