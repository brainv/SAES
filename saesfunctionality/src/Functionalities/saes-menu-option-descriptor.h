/**
 * @file	saes-menu-option-descriptor.h
 *
 * @brief	Declares the SAES menu option descriptor class.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SAES_MENU_OPTION_DESCRIPTOR_H_
#define _SAES_MENU_OPTION_DESCRIPTOR_H_

#include "Functionalities/menu-option-descriptor.h"
#include "saes-menu-option-type.h"
#include <glibmm/ustring.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Functionality
		{
			/**
			 * @brief	SAES menu option descriptor. 
			 */

			class SaesMenuOptionDescriptor:public Smartmatic::Functionality::MenuOptionDescriptor 
			{
			public:

					/**
					 * @brief	Constructor.
					 * @param	type	  	The SAES Menu Option type.
					 * @param	isMenuItem	true if is a menu item.
					 */

					SaesMenuOptionDescriptor(MenuType::SaesMenuOptionType type, bool isMenuItem);

					/**
					 * @brief	Gets the saes menu option type.
					 * @return	SaesMenuOptionType	the menu option type
					 */

					static MenuType::SaesMenuOptionType getSaesMenuOptionType(std::string typeString);
			protected:
					
					Glib::ustring menuDescriptor;   ///< The menu descriptor
					bool isMenu;	///< true if it is menu
			private:

			};
		}
	}
}

#endif // _SAES_MENU_OPTION_DESCRIPTOR_H_
