/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C)  2010 <>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "menu-widgetmm.h"
#include "Environment/Configurations/resource-path-provider.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

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
using namespace std;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::GUI::Windows;

MenuWidgetmm::~MenuWidgetmm()
{
	if(principalOptionsFrame != NULL)
	{
		delete(principalOptionsFrame);
	}
	if(levelsOptionsFrame != NULL)
	{
		delete(levelsOptionsFrame);
	}
	if(main_label != NULL)
	{
		delete(main_label);
	}
	if(menuConfiguration != NULL)
	{
		delete(menuConfiguration);
	}
}

void OptionsList::Add(MenuOption option)
{
	options.push_back(option);
}

void OptionsList::Remove(MenuOption option)
{
}

OptionsList::OptionsList(string name)
{
	this->name = name;
}

OptionsList::OptionsList(){};

OptionsList::~OptionsList()
{
	
}

OptionByKeyItem::OptionByKeyItem()
{

}

OptionByKeyItem::OptionByKeyItem(int _keyCode, std::string keyCodeName, MenuOption _option)
{
	Set(_keyCode, keyCodeName, _option);
}

OptionByKeyItem::~OptionByKeyItem()
{

}

void OptionByKeyItem::Set(int _keyCode, std::string _keyCodeName,  MenuOption _option)
{
	keyCode = _keyCode;
	keyName = _keyCodeName;
	option = _option;
}

OptionByKeyCollection::OptionByKeyCollection()
{

}

OptionByKeyCollection::OptionByKeyCollection(OptionByKeyItem _option)
{
	Add(_option);
}

OptionByKeyCollection::~OptionByKeyCollection()
{

}

void OptionByKeyCollection::Add(OptionByKeyItem _option)
{
	options.push_back(_option);
}

void OptionByKeyCollection::Remove(OptionByKeyItem _option)
{

}

MenuWidgetmm::MenuWidgetmm()
{
	menuConfiguration = NULL;
	menu_init();
	buttonIndex = 0;
}

MenuWidgetmm::MenuWidgetmm(vector<MenuOption> _firstLevelOptions,  std::map<string, OptionsList> _secondLevelOptions)
{
	menuConfiguration = NULL;
	firstLeveloptions = _firstLevelOptions;
	secondLevelOptions = _secondLevelOptions;	
	menu_init();
	buttonIndex = 0;
}

MenuWidgetmm::MenuWidgetmm(vector<MenuOption> options, FunctionalityManager<MenuOptionDescriptor> *menu_manager, void (*_gtk_ptr_set_key)(int),MenuWidgetConfiguration *conf)
{
	menuConfiguration = NULL;
	initOptions = options;
	withOnlyOptions = true;
	funct_manager = menu_manager;
	menuConfiguration = conf;
	menu_init();
	buttonIndex = 0;
}

void MenuWidgetmm::Dispose()
{
	//mapa de opciones por el boton que le corresponde
	optionsBybuttonList.clear();

	//mapa de opciones agrupadas de segundo nivel
	hBoxByOption.clear();

	//lista de opciones de primer nivel
	firstLeveloptions.clear();

	//lista de buttonBoxes
	buttonBoxes.clear();

	//lista de opciones de segundo nivel odenadas por su nombre
	secondLevelOptions.clear();

	initOptions.clear();

	secondLevelInitOptions.clear();

	buttonsByKey.clear();
}

vector<HelpItem> MenuWidgetmm::GetHelpConfiguration()
{
	vector<HelpItem> collection;

	//Opciones de primer nivel
	for(unsigned int index(0); index<initOptions.size(); index++)
	{
		HelpItem item (initOptions[index].mappingKeyName, initOptions[index].nameKey);	
		collection.push_back(item);
	}		

	if(currentFirstLevelMenuOption.nameKey != "0")
	{
		std::map<string, OptionsList>::iterator iter = secondLevelOptions.begin();
		iter = secondLevelOptions.find(currentFirstLevelMenuOption.nameKey);
	
		if( iter != secondLevelOptions.end() )
		{

			for(unsigned int mapIndex(0); mapIndex < iter->second.options.size(); mapIndex++)
			{
				HelpItem secondLevelitem (iter->second.options[mapIndex].mappingKeyName, iter->second.options[mapIndex].nameKey);	
				collection.push_back(secondLevelitem);							
			}
		}
	}	

	return collection;
}


void MenuWidgetmm::on_button_clicked(Smartmatic::GUI::Widgets::SmartmaticButton *widget, MenuOption _option)
{
	MenuOption currentMenuOption;
	if(widget == NULL)
	{
		currentMenuOption = _option;
	}
	else
	{		
		std::map<Smartmatic::GUI::Widgets::SmartmaticButton*, MenuOption>::iterator iter = optionsBybuttonList.begin();
		iter = optionsBybuttonList.find(widget);
		if( iter != optionsBybuttonList.end() )
		{
			currentMenuOption = iter->second;		
		}	
	}
	 //Detectamos si es una opcion de primer nivel
	bool isFirstLevelOption = false;


	for(unsigned int index(0); index<firstLeveloptions.size(); index++)
	{
		if(firstLeveloptions[index].optionDescriptor.getMenuOption().compare(currentMenuOption.optionDescriptor.getMenuOption()) == 0)
		{
			isFirstLevelOption = true;
		}
	}

	if(isFirstLevelOption)
	{
		std::map<string, Gtk::ButtonBox*>::iterator boxIter = hBoxByOption.begin();
		boxIter = hBoxByOption.find(currentMenuOption.nameKey);
		currentFirstLevelMenuOption = currentMenuOption;
			
		if( boxIter != hBoxByOption.end() )
		{
			update_h_box_state();

			boxIter->second->set_child_visible(true);	

			if(main_label != NULL)
			{
				if(boxIter->first.find(">>") != string::npos)
				{
					string temp = boxIter->first;
					temp.erase(boxIter->first.find(">>"), 2);

					main_label->set_label(main_label->get_label() + " -> " + temp);
				}
				else
				{
					main_label->set_label(boxIter->first);
				}
			}
		}
			
	}
	else
	{
		if(funct_manager->ExecuteOptionSelected(currentMenuOption.optionDescriptor))
		{
			
		}
	}		    
}

bool MenuWidgetmm::CurrentLevelContainThisSecondOption(MenuOption currentOption, int secondOptionCode)
{
	bool returnValue = FALSE;
	
	if(currentOption.v_MenuOption.size() > 0)
	{
		
		for(unsigned int index(0); index<currentOption.v_MenuOption.size(); index++)
		{
			if(currentOption.v_MenuOption[index].code == secondOptionCode)
			{
				return TRUE;
			}
		}
		
	}
	else
	{
		returnValue = FALSE;
	}	
	
	return returnValue;
}


void MenuWidgetmm::SetKey(KeysActionsCode value)
{
	bool buttonClicked = FALSE;

	if(menuConfiguration->Get_Has_Button_Shortcut())
	{
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getMenuSound());
		std::map<OptionsType, OptionByKeyCollection>::iterator iter = buttonsByKey.begin();
		iter = buttonsByKey.find(FirstLevel);
		if( iter != buttonsByKey.end() )
		{

			for(unsigned int index(0); index < iter->second.options.size(); index++)
			{
				int keyCode = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetKeysActionsCodeFromString(iter->second.options[index].keyName);
				//if(iter->second.options[index].keyCode == value)
				if(keyCode == value)
				{
					buttonClicked = TRUE;
					on_button_clicked(NULL, iter->second.options[index].option);
				}
			}	
		}
		if(buttonClicked == FALSE)
		{	
			if(currentFirstLevelMenuOption.nameKey != "0")
			{	
				std::map<OptionsType, OptionByKeyCollection>::iterator secondLevelIter = buttonsByKey.begin();
				secondLevelIter = buttonsByKey.find(SecondLevel);
	
				if(secondLevelIter != buttonsByKey.end() )
				{
			
					for(unsigned int index(0); index < secondLevelIter->second.options.size(); index++)
					{
						int keyCode = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetKeysActionsCodeFromString(secondLevelIter->second.options[index].keyName);
						//if(secondLevelIter->second.options[index].keyCode == value)
						if(keyCode == value)
						{
							//verificamos que esta pagina es la que se encuentra activa					
							if(CurrentLevelContainThisSecondOption(currentFirstLevelMenuOption, secondLevelIter->second.options[index].option.code))
							{
								on_button_clicked(NULL, secondLevelIter->second.options[index].option);
								break;
							}
						}
					}	
				}	
			}
		}
	}
	 
}

string MenuWidgetmm::GetButtonName(string suffix)
{	
	std::stringstream out;
	out << "" << (buttonIndex++);
	string buttonName = suffix + out.str();
	return buttonName;
}

Gtk::ButtonBox *MenuWidgetmm::create_bbox( gint  horizontal,                               
                               gint  spacing/*espacio entre los botones del box de botones*/,
                               Gtk::ButtonBoxStyle  layout/*layout del button box*/, 
							   gint buttonWidth/*width de los botones*/, 
							   gint buttonHeight, vector<MenuOption> options, 
							   int boxBorderWidth,
							   bool useImage)
{
	//Gtk::Frame *frame;
	Gtk::ButtonBox *bbox;
	SmartmaticButton *button;
	 
	  if (horizontal)
		bbox = manage(new Gtk::HButtonBox());
	  else
		bbox = manage(new Gtk::VButtonBox());

	bbox->set_border_width(boxBorderWidth);

	bbox->set_layout(layout);

	bbox->set_spacing(spacing);

	

	for(guint i (0); i<options.size(); i++)
	{		
		//instaciamos un nuevo boton
		if(useImage)
		{
			button = manage(new SmartmaticButton(SmartmaticButton::Menu));
			int keyCode = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetKeysActionsCodeFromString(options[i].mappingKeyName);
			button->SetMenuOption(menuConfiguration->Get_Has_Button_Shortcut(),(KeysActionsCode)keyCode, options[i].nameKey.c_str(),
			                     ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/" + options[i].imageKey));
			button->show();			
			
			button->set_name(GetButtonName("theme_menu_widget_principal_button"));
		}
		else
		{
			button = manage(new SmartmaticButton(SmartmaticButton::Menu));
			int keyCode = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetKeysActionsCodeFromString(options[i].mappingKeyName);
			button->SetMenuOptionLabel(menuConfiguration->Get_Has_Button_Shortcut(), (KeysActionsCode)keyCode,options[i].nameKey.c_str());

			button->set_name(GetButtonName("theme_menu_widget_secondary_button"));
		}
		
		//agregamos el boton mapeado con su opcion
		optionsBybuttonList.insert(pair<Smartmatic::GUI::Widgets::SmartmaticButton*, MenuOption>(button, options[i]));

		//agregamos la señal al boton
		button->signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &MenuWidgetmm::on_button_clicked), button, options[i]) );
		
		//asignamos el tamaño del boton
		button->set_size_request(buttonWidth, buttonHeight);

		//agregamos el boton al box
		bbox->add(*button);

		if(options[i].optionDescriptor.getIsMenu())
		{
			std::map<OptionsType, OptionByKeyCollection>::iterator iter = buttonsByKey.begin();
			iter = buttonsByKey.find(FirstLevel);

			if( iter != buttonsByKey.end() )
			{
				for(unsigned int index( 0); index < iter->second.options.size(); index++)
				{
					if(iter->second.options[index].keyCode ==  options[i].mappingKey)
					{
						iter->second.options[index].option = options[i];
					}
				}
			}
		}
	}
	
    return bbox;
}

OptionsList MenuWidgetmm::GetOptionList(string optionNameKey, MenuOption option)
{
	OptionsList options;
	bool exist = false;
	std::map<string, OptionsList> ::iterator iter = secondLevelOptions.begin();
	iter = secondLevelOptions.find(optionNameKey);
	
	if( iter != secondLevelOptions.end() )
	{
		exist = true;
		iter->second.Add(option);
	}

	if(exist == false)
	{
		options.Add(option);
		secondLevelOptions.insert(pair<string, OptionsList>(optionNameKey, options));		 
	}	

	return options;
}

OptionsList MenuWidgetmm::GetSecondInitOptionList(string optionNameKey, MenuOption option )
{	
	OptionsList options;
	bool exist = false;

	std::map<string, OptionsList> ::iterator iter = secondLevelInitOptions.begin();
	iter = secondLevelInitOptions.find(optionNameKey);
	if( iter != secondLevelInitOptions.end() )
	{
		exist = true;
		iter->second.Add(option);
	}
	
	if(exist == false)
	{		
		options.Add(option);
		pair<std::map<string,OptionsList>::iterator,bool> ret;
		ret = secondLevelInitOptions.insert(pair<string, OptionsList>(optionNameKey, options));		

		if(ret.second == false)
		{
			//throw exception 
		}
	}

	exist = false;

	return options;
}

void MenuWidgetmm::BuildFirstLevelOptions()
{
	unsigned int i, j = 0;

	for(i=0; i<initOptions.size(); i++)
	{
		firstLeveloptions.push_back(initOptions[i]);

		if(initOptions[i].mappingKey != 0)
		{
			OptionByKeyItem currentoptionByKey (initOptions[i].mappingKey,initOptions[i].mappingKeyName, initOptions[i]);
			std::map<OptionsType, OptionByKeyCollection>::iterator iter = buttonsByKey.begin();
			iter = buttonsByKey.find(FirstLevel);

			if( iter != buttonsByKey.end() )
			{
				iter->second.Add(currentoptionByKey);
			}
			else
			{	
				OptionByKeyCollection collection (currentoptionByKey);		
				buttonsByKey.insert(pair<OptionsType, OptionByKeyCollection>(FirstLevel, collection));			 
			}	
		}

		if(initOptions[i].v_MenuOption.size() > 0)
		{
			for(j=0; j<initOptions[i].v_MenuOption.size(); j++)
			{	
				GetSecondInitOptionList(initOptions[i].nameKey, initOptions[i].v_MenuOption[j]);			   
			}
		}
	}
}

void MenuWidgetmm::BuildChildren(string fatherName, vector<MenuOption> options)
{

	

	for(unsigned int i(0); i<options.size(); i++)
	{
		OptionsList optionsList;
		
		if(options[i].v_MenuOption.size() > 0)
		{				
			//agregamos al nombre la guia de que es un menu
			options[i].nameKey.append( " >>");
			//agregamos la opcion a las opciones de primer nivel
			firstLeveloptions.push_back(options[i]);
			//agregamos la opcion a las opciones de segundo nivel para que se agregue el boton
			GetOptionList(fatherName, options[i]);
			BuildChildren(options[i].nameKey, options[i].v_MenuOption); 
		}
		else
		{
			//agregamos la opcion a las opciones de segundo nivel para que se agregue el boton			
			GetOptionList(fatherName, options[i]);			
		}
	}
}

void MenuWidgetmm::SetPrincipalFrameTitle(string title)
{
	principalOptionsFrameTitle  = title ;
}	

void MenuWidgetmm::SetSecondLevelTitle(string title)
{
	levelsOptionsFrameTitle = title ;
}	

void MenuWidgetmm::SetMenuConfiguration(MenuWidgetConfiguration *conf)
{
	menuConfiguration = conf ;
}	

void MenuWidgetmm::menu_init()
{
	buttonIndex = 0;
	principalOptionsFrame = NULL;
	levelsOptionsFrame = NULL;
	main_label = NULL;
	Gtk::Fixed *fixed;
	Gtk::Fixed *secondLevelfixed;
	fixed = manage(new Gtk::Fixed());
	secondLevelfixed = manage(new Gtk::Fixed());

	currentFirstLevelMenuOption = MenuOption("0");
	
	resize(/*rows*/ 1,  /*columns*/2);

	set_homogeneous(FALSE);

	//Instaciamos cada frame principal
	principalOptionsFrame = new Gtk::Frame(principalOptionsFrameTitle) ;
	levelsOptionsFrame  = new Gtk::Frame(levelsOptionsFrameTitle);
	
	//************************Opciones de Primer Nivel****************************//

	if(withOnlyOptions)
	{
		BuildFirstLevelOptions();
	}

	vBox = create_bbox(FALSE, menuConfiguration->Get_FirstLevel_Spacing(), Gtk::BUTTONBOX_SPREAD, menuConfiguration->Get_FirstLevel_Width(), 
	                   menuConfiguration->Get_FirstLevel_Height(), firstLeveloptions, menuConfiguration->Get_FirstLevel_BorderWidth(), TRUE);
	principalOptionsFrame->set_size_request (menuConfiguration->Get_FirstLevel_Frame_Width(), menuConfiguration->Get_FirstLevel_Frame_Height());
	
	fixed->put(*vBox, 0, 0);
	
	//agregamos el fixed al frame de las opciones principales
	principalOptionsFrame->add(*fixed);
    
    //agregamos el frame de las opciones principales a la tabla
    attach(*principalOptionsFrame,  0, 1, 0,  1, Gtk::FILL, Gtk::FILL, 0, 0);

			
	//****************************************************************************//
	//************************Opciones de Segundo Nivel**************************//
		
	levelsOptionsFrame->add(*secondLevelfixed);
		
	if(withOnlyOptions)
	{
		unsigned int index = 0;

		std::map<string,OptionsList>::iterator initSeconLevelIter;
		
		for (initSeconLevelIter=secondLevelInitOptions.begin(); initSeconLevelIter != secondLevelInitOptions.end(); initSeconLevelIter++ )
		{			
			if(initSeconLevelIter->second.options.size() > 0)
			{			
				for(index=0; index < initSeconLevelIter->second.options.size(); index++)
				{	
					OptionsList options;
					MenuOption tempOption = initSeconLevelIter->second.options[index];
					
					if(tempOption.v_MenuOption.size() > 0)
					{				
						//agregamos al nombre la guia de que es un menu
						tempOption.nameKey.append(" >>");
						//agregamos la opcion a las opciones de primer nivel
						firstLeveloptions.push_back(tempOption);
						//agregamos la opcion a las opciones de segundo nivel para que se agregue el boton
						options = GetOptionList(initSeconLevelIter->first, tempOption);

						BuildChildren(tempOption.nameKey, tempOption.v_MenuOption); 
					}
					else
					{
						//agregamos la opcion a las opciones de segundo nivel para que se agregue el boton
						options = GetOptionList(initSeconLevelIter->first, tempOption);						
					}
				}
			}
		}
		 
	}
	
//	gint i;
	std::map<string,OptionsList>::iterator iter;
	
	for ( iter=secondLevelOptions.begin(); iter != secondLevelOptions.end(); iter++ )
	{
		unsigned int tempOptionsIndex = 0;
		vector<MenuOption> tempOptions;

		for(tempOptionsIndex=0; tempOptionsIndex< iter->second.options.size(); tempOptionsIndex++)
		{
			tempOptions.push_back(iter->second.options[tempOptionsIndex]);

			//agregamos a la tabla de teclas la opcion

			if(iter->second.options[tempOptionsIndex].mappingKey != 0)
			{
				OptionByKeyItem currentoptionByKey (iter->second.options[tempOptionsIndex].mappingKey,iter->second.options[tempOptionsIndex].mappingKeyName, iter->second.options[tempOptionsIndex]);
				std::map<OptionsType, OptionByKeyCollection>::iterator iter = buttonsByKey.begin();
				iter = buttonsByKey.find(SecondLevel);

				if( iter != buttonsByKey.end() )
				{
					iter->second.Add(currentoptionByKey);
				}
				else
				{	
					OptionByKeyCollection collection (currentoptionByKey);		
					buttonsByKey.insert(pair<OptionsType, OptionByKeyCollection>(SecondLevel, collection));			 
				}	
			}
		}

		Gtk::ButtonBox *tempWidget;

		tempWidget = create_bbox (FALSE, menuConfiguration->Get_SecondLevel_Spacing(), Gtk::BUTTONBOX_SPREAD, 
		                          menuConfiguration->Get_SecondLevel_Width(), menuConfiguration->Get_SecondLevel_Height(), 
		                          tempOptions, menuConfiguration->Get_SecondLevel_BorderWidth(), FALSE);	

		//insertamos el part opcion de primer nivel con su box correspondiente de botones
		buttonBoxes.push_back(tempWidget);
		hBoxByOption.insert(pair<string, Gtk::ButtonBox*>(iter->first, tempWidget)); 

		tempWidget->set_child_visible(false);     
		secondLevelfixed->put(*tempWidget, menuConfiguration->Get_SecondLevel_Frame_Padding(), 0);
		
		 
	}
	
	//agregamos el frame de las opciones de segundo nivel a la tabla 
	attach(*levelsOptionsFrame,  1, 2, 0,  1);
	
	//***************************************************************************//
			
	principalOptionsFrame->show();      	
}


void MenuWidgetmm::update_h_box_state()
{
	unsigned int i = 0;
	for(i=0; i<buttonBoxes.size(); i++)
	{		
		buttonBoxes[i]->set_child_visible(false);	
	}
}

void MenuWidgetmm::SetMenuLabel(Gtk::Label* title_label)
{
	main_label = title_label;
}

