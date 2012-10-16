/*
 * WizardWidgetConfiguration.cpp
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "WizardWidgetConfiguration.h"

using namespace Smartmatic::GUI::Widgets;

WizardWidgetConfiguration::WizardWidgetConfiguration() {
	// TODO Auto-generated constructor stub

}

WizardWidgetConfiguration::~WizardWidgetConfiguration() {
	// TODO Auto-generated destructor stub
}

std::vector<MenuOption> WizardWidgetConfiguration::GetCurrentToolbox(std::vector<WizardWidgetConfiguration> configuration,
		std::string currentState)
{
	for(unsigned int i=0; i<configuration.size(); i++)
	{
		if(configuration[i].isState(currentState))
			return configuration[i].getToolbox();
	}
	std::vector<MenuOption> empty;
	return empty;
}

std::vector<MenuOption> WizardWidgetConfiguration::GetCurrentPrincipaButtonBox(std::vector<WizardWidgetConfiguration> configuration,
		std::string currentState)
{
	for(unsigned int i=0; i<configuration.size(); i++)
	{
		if(configuration[i].isState(currentState))
			return configuration[i].getPrincipalOptions();
	}
	std::vector<MenuOption> empty;
		return empty;
}

WizardWidgetConfiguration WizardWidgetConfiguration::GetWizardWidgetConfigurationByState(std::vector<WizardWidgetConfiguration> configuration, std::string currentState)
{
	for(unsigned int i=0; i<configuration.size(); i++)
	{
		if(configuration[i].isState(currentState))
			return configuration[i];
	}
	WizardWidgetConfiguration empty;
	return empty;
}


bool WizardWidgetConfiguration::isState(std::string value)
{
	if(value == getStateEnum())
		return true;

	return false;
}

std::vector<MenuOption> WizardWidgetConfiguration::getPrincipalOptions()
{
	return options;
}

std::vector<MenuOption>  WizardWidgetConfiguration::getToolbox()
{
	return toolkit;
}

void WizardWidgetConfiguration::setToolbox(std::vector<MenuOption> value)
{
	toolkit = value;
}

void WizardWidgetConfiguration::setPrincipalOptions(std::vector<MenuOption> value)
{
	options = value;
}

std::string WizardWidgetConfiguration::getStateName() { return state_Name; }
void WizardWidgetConfiguration::setStateName(std::string value) { state_Name = value; }

std::string WizardWidgetConfiguration::getStateDescription() { return state_Description; }
void WizardWidgetConfiguration::setStateDescription(std::string value) { state_Description = value; }

std::string WizardWidgetConfiguration::getStateHelpTitleKey() { return stateHelp_TitleKey; }
void WizardWidgetConfiguration::setStateHelpTitleKey(std::string value) { stateHelp_TitleKey = value; }

std::string WizardWidgetConfiguration::getStateHelpContentKey() { return stateHelp_ContentKey; }
void WizardWidgetConfiguration::setStateHelpContentKey(std::string value) { stateHelp_ContentKey = value; }

std::string WizardWidgetConfiguration::getStateHelpRelativeImagePath() { return stateHelp_RelativeImagePath; }
void WizardWidgetConfiguration::setStateHelpRelativeImagePath(std::string value) { stateHelp_RelativeImagePath = value; }

std::string WizardWidgetConfiguration::getTimelineNameKey() { return timeline_NameKey; }
void WizardWidgetConfiguration::setTimelineNameKey(std::string value) { timeline_NameKey = value; }

std::string WizardWidgetConfiguration::getTimelineDescriptionKey() { return timeline_DescriptionKey; }
void WizardWidgetConfiguration::setTimelineDescriptionKey(std::string value) { timeline_DescriptionKey = value; }

std::string WizardWidgetConfiguration::gettimelineRelativeImagePath() { return timeline_RelativeImagePath; }
void WizardWidgetConfiguration::settimelineRelativeImagePath(std::string value) { timeline_RelativeImagePath = value; }

std::string WizardWidgetConfiguration::getStateEnum() { return stateEnum; }
void WizardWidgetConfiguration::setStateEnum(std::string value) { stateEnum = value; }

std::string WizardWidgetConfiguration::getHelpTitle() { return getStateHelpTitleKey(); }
std::string WizardWidgetConfiguration::getHelpContent() { return getStateHelpContentKey(); }

int WizardWidgetConfiguration::getToolboxElementWidth(){ return toolboxElementWidth; }
int WizardWidgetConfiguration::getToolboxElementHeight(){ return toolboxElementHeight; }

void WizardWidgetConfiguration::setToolboxElementWidth(int value){toolboxElementWidth = value;}
void WizardWidgetConfiguration::setToolboxElementHeight(int value){toolboxElementHeight = value;};

int WizardWidgetConfiguration::getEnumIntState() { return enumIntState; }
void WizardWidgetConfiguration::setEnumIntState(int value) { enumIntState = value; }
bool WizardWidgetConfiguration::isEnumIntState(int value)
{
	if(value == enumIntState)
		return true;

	return false;
}

void WizardWidgetConfiguration::setButtonsLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value)
{
	buttonsLabelConfiguration = value;
}
void WizardWidgetConfiguration::setTitleHelpLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value)
{
	titleHelpLabelConfiguration = value;
}
void WizardWidgetConfiguration::setHelpLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration value)
{
	helpLabelConfiguration = value;
}

Smartmatic::GUI::Configuration::LabelConfiguration WizardWidgetConfiguration::getButtonsLabelConfiguration()
{
	return buttonsLabelConfiguration;
}

Smartmatic::GUI::Configuration::LabelConfiguration WizardWidgetConfiguration::getTitleHelpLabelConfiguration()
{
	return titleHelpLabelConfiguration;
}

Smartmatic::GUI::Configuration::LabelConfiguration WizardWidgetConfiguration::getHelpLabelConfiguration()
{
	return helpLabelConfiguration;
}

std::string WizardWidgetConfiguration::getImageHelp() {return helpWindow_ImageHelp;}
void WizardWidgetConfiguration::setImageHelp(std::string value) { helpWindow_ImageHelp = value; }

std::string WizardWidgetConfiguration::getPdfHelp() {return helpWindow_PdfHelp;}
void WizardWidgetConfiguration::setPdfHelp(std::string value) { helpWindow_PdfHelp = value; }

std::string WizardWidgetConfiguration::getTitleKey() {return helpWindow_TitleKey;}
void WizardWidgetConfiguration::setTitleKey(std::string value) { helpWindow_TitleKey = value; }

bool WizardWidgetConfiguration::getUseHelp() {return helpWindow_UseHelp;}
void WizardWidgetConfiguration::setUseHelp(bool value) { helpWindow_UseHelp = value; }
