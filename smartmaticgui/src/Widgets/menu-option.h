/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2010 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MENU_OPTION_H_

/**
 * @brief	Gets the menu option h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _MENU_OPTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <Functionalities/menu-option-descriptor.h>
#include <glibmm/ustring.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class MenuOption
			{	
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					MenuOption();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	nameKey	The name key.
					 */

					MenuOption(std::string nameKey);

					std::string nameKey;	///< The name key
					std::string imageKey;   ///< The image key
					int code;   ///< The code
					int mappingKey; ///< The mapping key
					std::string mappingKeyName; ///< Name of the mapping key
					Smartmatic::Functionality::MenuOptionDescriptor optionDescriptor;   ///< The option descriptor
					std::vector<MenuOption> v_MenuOption;   ///< The v menu option

					/**
					 * @brief	Sets an option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	option	The option.
					 */

					void SetOptionType(Smartmatic::Functionality::MenuOptionDescriptor& option){ optionDescriptor = option; };

					/**
					 * @brief	Gets the default configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The default configuration.
					 */

					static std::vector<MenuOption> GetDefaultConfiguration();		
					//static MenuOptionDescriptor GetOptionTypeFromString(std::string option_str);
				protected:

				private:

					/**
					 * @brief	Loads a menu labels.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	v_Option	The v option.
					 */

					static void LoadMenuLabels(std::vector<MenuOption> &v_Option);

			};
		}
	}
}

#endif // _MENU_OPTION_H_
