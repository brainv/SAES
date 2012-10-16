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

#ifndef _MENU_WIDGETMM_H_
#define _MENU_WIDGETMM_H_

#include <map>
#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtkadjustment.h>
#include "Functionalities/functionality-manager.h"
#include "Windows/help-item.h"
#include "Widgets/menu-option.h"
#include "Widgets/smartmatic-button.h"
#include "Widgets/keyword-navigation-interface.h"
#include "Widgets/menu-widget-configuration.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
		
			class OptionsList
			{	
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					OptionsList();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~OptionsList();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	_name	The name.
					 */

					OptionsList(std::string _name);		
					std::string name;   ///< The name
					std::vector<MenuOption> options;	///< Options for controlling the operation

					/**
					 * @brief	Adds option..
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	option	The MenuOption to add.
					 */

					void Add(MenuOption option);	

					/**
					 * @brief	Removes the given option.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	option	The MenuOption to remove.
					 */

					void Remove(MenuOption option);	
			};

			/**
			 * @brief	Values that represent OptionsType. 
			 */

			enum OptionsType
			{
				FirstLevel, ///< Value that represent firstlevel type. 
				SecondLevel ///< Value that represent secondlevel type. 
			};

			class OptionByKeyItem
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					OptionByKeyItem();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	_keyCode	The key code.
					 * @param	keyName 	Name of the key.
					 * @param	_option 	The option.
					 */

					OptionByKeyItem(int _keyCode, std::string keyName, MenuOption _option);

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~OptionByKeyItem();
					int keyCode;	///< The key code
					std::string keyName;	///< Name of the key
					MenuOption option;  ///< The option

					/**
					 * @brief	Sets.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	_keyCode	The key code.
					 * @param	keyName 	Name of the key.
					 * @param	_option 	The option.
					 */

					void Set(int _keyCode, std::string keyName, MenuOption _option);	
			};

			class OptionByKeyCollection
			{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					OptionByKeyCollection();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	option	The option.
					 */

					OptionByKeyCollection(OptionByKeyItem option);

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~OptionByKeyCollection();
					std::vector<OptionByKeyItem> options;   ///< Options for controlling the operation

					/**
					 * @brief	Adds option..
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	option	The OptionByKeyItem to add.
					 */

					void Add(OptionByKeyItem option);	

					/**
					 * @brief	Removes the given option.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	option	The OptionByKeyItem to remove.
					 */

					void Remove(OptionByKeyItem option);	
			};

			class MenuWidgetmm : public Gtk::Table, public keywordNavigationInterface
			{
	
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					MenuWidgetmm();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	_firstLevelOptions 	Options for controlling the first level.
					 * @param	_secondLevelOptions	Options for controlling the second level.
					 */

					MenuWidgetmm(std::vector<MenuOption> _firstLevelOptions,  std::map<std::string, OptionsList> _secondLevelOptions);

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	options						Options for controlling the operation.
					 * @param [in,out]	menu_manager		If non-null, manager for menu.
					 * @param [in,out]	_gtk_ptr_set_key	If non-null, the gtk pointer set key.
					 */

					MenuWidgetmm(std::vector<MenuOption> options, Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor> *menu_manager, void (*_gtk_ptr_set_key)(int),MenuWidgetConfiguration *conf);

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~MenuWidgetmm();

					/**
					 * @brief	Gets the gtk saesmenu get type.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	GtkType.
					 */

					GtkType gtk_saesmenu_get_type(void);

					/**
					 * @brief	Gets the saesmenu new.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else a GtkWidget.
					 */

					GtkWidget* saesmenu_new(void);

					/**
					 * @brief	Gets the help configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The help configuration.
					 */

					std::vector<Smartmatic::GUI::Windows::HelpItem> GetHelpConfiguration(void);

					/**
					 * @brief	Gtk initialise menu.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	_firstLevelOptions 	Options for controlling the first level.
					 * @param	_secondLevelOptions	Options for controlling the second level.
					 */

					void gtk_init_menu(std::vector<MenuOption>   _firstLevelOptions, std::map<std::string, OptionsList> _secondLevelOptions);

					/**
					 * @brief	Sets a menu label.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	title_label	If non-null, the title label.
					 */

					void SetMenuLabel(Gtk::Label* title_label);

					/**
					 * @brief	Sets a key.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	value	The value.
					 */

					virtual void SetKey(KeysActionsCode value);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Sets a principal frame title.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	title	The title.
					 */

					void SetPrincipalFrameTitle(std::string title);

					/**
					 * @brief	Sets a second level title.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	title	The title.
					 */

					void SetSecondLevelTitle(std::string title);

					/**
					 * @brief	Sets a menu configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	conf	If non-null, the conf.
					 */

					void SetMenuConfiguration(MenuWidgetConfiguration *conf);
		
				protected:
							
					std::map<Smartmatic::GUI::Widgets::SmartmaticButton*, MenuOption> optionsBybuttonList; ///< List of options by correspond buttons
					std::map<std::string, Gtk::ButtonBox*> hBoxByOption;	///< List of options agrupped for second level
					//lista de opciones de primer nivel
					std::vector<MenuOption> firstLeveloptions;  ///< List of options agrupped for first level					
					std::vector<Gtk::ButtonBox*> buttonBoxes;   ///< List of button boxes					
					std::map<std::string, OptionsList> secondLevelOptions;  ///< Options for controlling the second level sorted by their names
					bool withOnlyOptions;   ///< true to with only options
					std::vector<MenuOption> initOptions;	///< Options for controlling the initialise
					std::map<std::string, OptionsList> secondLevelInitOptions;  ///< Options for controlling the second level initialise
					std::map<OptionsType, OptionByKeyCollection> buttonsByKey;  ///< The buttons by key
					Gtk::Label* main_label; ///< The main label
					MenuOption currentFirstLevelMenuOption; ///< The current first level menu option

					/**
					 * @brief	Menu initialise.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void menu_init();

					/**
					 * @brief	Builds a children.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	fatherName	Name of the father.
					 * @param	options   	Options for controlling the operation.
					 */

					void BuildChildren(std::string fatherName, std::vector<MenuOption> options);

					/**
					 * @brief	Builds the first level options.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void BuildFirstLevelOptions();

					/**
					 * @brief	Gets a second initialise option list.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	optionNameKey	The option name key.
					 * @param	option		 	The option.
					 *
					 * @return	The second initialise option list.
					 */

					OptionsList GetSecondInitOptionList(std::string optionNameKey, MenuOption option);

					/**
					 * @brief	Gets an option list.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	optionNameKey	The option name key.
					 * @param	option		 	The option.
					 *
					 * @return	The option list.
					 */

					OptionsList GetOptionList(std::string optionNameKey, MenuOption option);

					/**
					 * @brief	Creates a bounding box.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	horizontal	  	The horizontal.
					 * @param	spacing		  	The spacing.
					 * @param	layout		  	The layout.
					 * @param	buttonWidth   	Width of the button.
					 * @param	buttonHeight  	Height of the button.
					 * @param	options		  	Options for controlling the operation.
					 * @param	boxBorderWidth	Width of the box border.
					 * @param	useImage	  	true to use image.
					 *
					 * @return	null if it fails, else.
					 */

					Gtk::ButtonBox *create_bbox( gint  horizontal,                               
						                   gint  spacing/*espacio entre los botones del box de botones*/,
						                   Gtk::ButtonBoxStyle  layout/*layout del button box*/, 
										   gint buttonWidth/*width de los botones*/, 
										   gint buttonHeight, std::vector<MenuOption> options, 
										   int boxBorderWidth,
										   bool useImage);

					/**
					 * @brief	Current level contain this second option.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	currentOption   	The current option.
					 * @param	secondOptionCode	The second option code.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool CurrentLevelContainThisSecondOption(MenuOption currentOption, int secondOptionCode);

					/**
					 * @brief	Executes the button clicked action.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	widget	If non-null, the widget.
					 * @param	_option		  	The option.
					 */

					void on_button_clicked(Smartmatic::GUI::Widgets::SmartmaticButton *widget, MenuOption _option);
		
				private:

					int buttonIndex;	///< Zero-based index of the button
					MenuWidgetConfiguration* menuConfiguration; ///< The menu configuration
					Smartmatic::Functionality::FunctionalityManager<Smartmatic::Functionality::MenuOptionDescriptor> *funct_manager;	///< Manager for funct
					Gtk::Frame* principalOptionsFrame;  ///< The principal options frame
					Gtk::Frame* levelsOptionsFrame; ///< The levels options frame
					Gtk::ButtonBox *vBox;   ///< The v box
					//Gtk::ButtonBox *hBox[];
					std::string principalOptionsFrameTitle; ///< The principal options frame title
					std::string levelsOptionsFrameTitle;	///< The levels options frame title

					/**
					 * @brief	Updates the h box state.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void update_h_box_state();

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

			};
		}
	}
}

#endif // _MENU_WIDGETMM_H_
