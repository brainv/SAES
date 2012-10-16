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

#include "help-item.h"
using namespace Smartmatic::GUI::Windows;

	HelpItem::HelpItem()
	{
	}

	HelpItem::HelpItem(std::string key, std::string action)
	{
		key_value = key;
		key_action = action;
	}

	std::string HelpItem::Get_Key()
	{
		return key_value;
	}

	std::string HelpItem::Get_Action()
	{
		return key_action;
	}

	HelpItem::~HelpItem()
	{
	}
	

