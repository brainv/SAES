/*
 * WizardWidget.cpp
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "WizardWidget.h"

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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;

WizardWidget::WizardWidget(std::vector<WizardWidgetConfiguration> configuration, std::string currentState,
		Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor> *menu_manager,
		MenuWidgetConfiguration* menuConfigurationA, std::string languagePackageA)
{
	languagePackage = languagePackageA;
	set_shadow_type(Gtk::SHADOW_NONE);
	buttonIndex = 0;
	menuConfiguration = menuConfigurationA;
	state = currentState;
	wizardWidgetConfiguration = configuration;
	funct_manager = menu_manager;
	currentWizardConfiguration =
			WizardWidgetConfiguration::GetWizardWidgetConfigurationByState(configuration, currentState);

	boxPrincipal = manage(new Gtk::VBox());
	toolbox = manage(new WizardToolkit(WizardWidgetConfiguration::GetCurrentToolbox(configuration, currentState), currentWizardConfiguration));
	toolBoxConnection = toolbox->WizardToolkitElementClickSigc().connect(sigc::mem_fun(this, &WizardWidget::on_toolbox_element_clicked));
	std::vector<std::string> timelineImagesPath;
	timelineImagesPath.push_back(currentWizardConfiguration.gettimelineRelativeImagePath());
	timeline = manage(new WizardTimeline(timelineImagesPath));
	boxCentral = manage(new Gtk::HBox());
	principalButtonBox = manage(new Gtk::VBox());
	helpTitle = manage(new Gtk::Label());
	helpDetail = manage(new Gtk::Label());

	eventBoxTimeLine = manage(new Gtk::EventBox());
	eventBoxPrincipalButtons = manage(new Gtk::EventBox());
	eventBoxToolbox = manage(new Gtk::EventBox());
	eventBoxHelpPanel = manage(new Gtk::EventBox());

	eventBoxToolbox->add(*toolbox);
	eventBoxTimeLine->add(*timeline);

	principalButtonTable = new Gtk::Table();

	std::vector<MenuOption> principalMenuOption = WizardWidgetConfiguration::GetCurrentPrincipaButtonBox(configuration, currentState);

	Smartmatic::GUI::Widgets::SmartmaticButton *button;

	for(unsigned int i=0; i<principalMenuOption.size(); i++)
	{
		button = manage(new Smartmatic::GUI::Widgets::SmartmaticButton(SmartmaticButton::Menu));
		int keyCode = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetKeysActionsCodeFromString(principalMenuOption[i].mappingKeyName);

		if (!languagePackage.empty())
		{
			button->SetMenuOptionLabel(false, (KeysActionsCode)keyCode, dgettext(languagePackage.c_str(), principalMenuOption[i].nameKey.c_str()));
		}
		else
		{
			button->SetMenuOptionLabel(false, (KeysActionsCode)keyCode, _(principalMenuOption[i].nameKey.c_str()));
		}

		button->set_name(GetButtonName("theme_menu_widget_secondary_button"));

		//agregamos el boton mapeado con su opcion
		optionsBybuttonList.insert(std::pair<SmartmaticButton*, MenuOption>(button, principalMenuOption[i]));

		button->signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &WizardWidget::on_button_clicked), button, principalMenuOption[i]) );

		//asignamos el tamaño del boton
		button->set_size_request(500,  menuConfiguration->Get_FirstLevel_Height());

		principalButtonTable->attach(*button, 0, 1, i, i + 1, Gtk::SHRINK, Gtk::SHRINK, 3, 3);
	}

	boxCentral->pack_start(*principalButtonTable, true, false, 5);

	heplBox = manage(new Gtk::VBox(false, 10));

	helpTitle->set_line_wrap(true);
	helpTitle->set_line_wrap_mode(Pango::WRAP_WORD);

	Pango::FontDescription fontBack = helpTitle->get_style()->get_font();
	fontBack.set_size(16*Pango::SCALE);
	fontBack.set_weight(Pango::WEIGHT_BOLD);
	helpTitle->modify_font(fontBack);

	helpDetail->set_alignment(0.50, 0.10);
	helpDetail->set_line_wrap(true);
	helpDetail->set_line_wrap_mode(Pango::WRAP_WORD);

	heplBox->pack_start(*helpTitle, false, false, 3);
	heplBox->pack_start(*helpDetail, false, false, 3);

	eventBoxHelpPanel->add(*heplBox);
	boxCentral->pack_end(*eventBoxHelpPanel, false, false, 5);

	boxPrincipal->pack_start(*eventBoxTimeLine, false, false, 0);
	boxPrincipal->pack_start(*boxCentral, true, true, 0);

	Gtk::Alignment* aligment = manage(new Gtk::Alignment());
	aligment->set(0.5, 0.5, 0, 0);
	aligment->add(*eventBoxToolbox);

	boxPrincipal->pack_start(*aligment, false, false, 0);

	this->add(*boxPrincipal);

	show_all_children(true);
}

std::string WizardWidget::GetButtonName(std::string suffix)
{
	std::stringstream out;
	out << buttonIndex++;
	std::string buttonName = suffix + out.str();
	return buttonName;
}

void WizardWidget::RefreshLanguage()
{
	std::map<SmartmaticButton*, MenuOption>::iterator buttonIter;

	for (buttonIter=optionsBybuttonList.begin(); buttonIter != optionsBybuttonList.end(); buttonIter++ )
	{
		if(!languagePackage.empty())
		{
			helpTitle->set_label(dgettext(languagePackage.c_str(), currentWizardConfiguration.getHelpTitle().c_str()));
			helpDetail->set_label(dgettext(languagePackage.c_str(), currentWizardConfiguration.getHelpContent().c_str()));
			buttonIter->first->set_label(dgettext(languagePackage.c_str(), buttonIter->second.nameKey.c_str()));
		}
		else
		{
			helpTitle->set_label(_(currentWizardConfiguration.getHelpTitle().c_str()));
			helpDetail->set_label(_(currentWizardConfiguration.getHelpContent().c_str()));
			buttonIter->first->set_label(_(buttonIter->second.mappingKeyName.c_str()));
		}
	}
}

void WizardWidget::SetKey(KeysActionsCode value)
{

}

void WizardWidget::on_button_clicked(SmartmaticButton *widget, MenuOption _option)
{
	MenuOption currentMenuOption;
	if(widget == NULL)
	{
		currentMenuOption = _option;
	}
	else
	{
		std::map<SmartmaticButton*, MenuOption>::iterator iter = optionsBybuttonList.begin();
		iter = optionsBybuttonList.find(widget);
		if( iter != optionsBybuttonList.end() )
		{
			currentMenuOption = iter->second;
		}
	}

	if(currentMenuOption.optionDescriptor.getIsMenu())
	{
		m_show_menu_sigc.emit();
	}
	else
	{
		if(funct_manager->ExecuteOptionSelected(currentMenuOption.optionDescriptor))
		{
			//TODO Log Error
		}

		m_functionality_executed.emit();
	}
}

void WizardWidget::on_toolbox_element_clicked(MenuOption option)
{
	if(option.optionDescriptor.getIsMenu())
	{
		m_show_menu_sigc.emit();

	}else
	{
		if(funct_manager->ExecuteOptionSelected(option.optionDescriptor))
		{
			//TODO Log Error
		}

		m_functionality_executed.emit();
	}
}

WizardWidget::~WizardWidget()
{
	if(boxPrincipal)
		delete(boxPrincipal);
	if(toolbox)
		delete(toolbox);
	if(timeline)
		delete(timeline);
	if(boxCentral)
		delete(boxCentral);
	if(boxPrincipal)
		delete(boxPrincipal);
	if(principalButtonBox)
		delete(principalButtonBox);
	if(helpTitle)
		delete(helpTitle);
	if(helpDetail)
		delete(helpDetail);
	if(helpDetail)
		delete(helpDetail);
	if(eventBoxTimeLine)
		delete(eventBoxTimeLine);
	if(eventBoxPrincipalButtons)
		delete(eventBoxPrincipalButtons);
	if(eventBoxToolbox)
		delete(eventBoxToolbox);
	if(eventBoxHelpPanel)
		delete(eventBoxHelpPanel);
	if(principalButtonTable)
		delete(principalButtonTable);
	if(heplBox)
		delete(heplBox);
	if(menuConfiguration)
		delete(menuConfiguration);
}
