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

#include "menu-option.h"

using namespace Smartmatic::GUI::Widgets;

MenuOption::MenuOption()
{
	this->mappingKey = 0;
}

MenuOption::MenuOption(std::string nameKey)
{
	this->nameKey = nameKey;
	this->mappingKey = 0;
}

std::vector<MenuOption> MenuOption::GetDefaultConfiguration()
{
		std::vector<MenuOption> options;
		LoadMenuLabels(options);
		return options;
};

void MenuOption::LoadMenuLabels(std::vector<MenuOption> &v_Option)
{
	std::string labelName;
	
	for(std::vector<MenuOption>::iterator iter = v_Option.begin(); iter < v_Option.end(); iter++)
	{
		labelName = iter->nameKey;
		if(!labelName.empty())
			iter->nameKey = labelName.c_str();
		if(iter->v_MenuOption.size() > 0)
		{
			LoadMenuLabels(iter->v_MenuOption);
		}
	}
}
/*
MenuOptionDescriptor MenuOption::GetOptionTypeFromString(std::string option_str)
{
	if(option_str == "Menu")
		return MenuType::Menu;
	return MenuType::Menu;
}
*/
