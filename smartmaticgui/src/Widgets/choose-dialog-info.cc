/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "choose-dialog-info.h"

using namespace Smartmatic::GUI::Widgets;

ChooseDialogInfo::ChooseDialogInfo(std::string title, std::string titleImagePath, std::string footer, std::vector<ChooseDialogButtonInfo *> &listOfButtons, bool activateCancelButton)
{
	this->title = title;
	this->titleImagePath = titleImagePath;
	this->footer = footer;
	this->listOfChoices = listOfButtons;
	this->activateCancel = activateCancelButton;
}

ChooseDialogInfo::ChooseDialogInfo(std::string title, std::string code, std::string titleImagePath, std::string footer, std::vector<ChooseDialogButtonInfo *> & listOfButtons, bool activateCancelButton)
{
	this->title = title;
	this->code = code;
	this->titleImagePath = titleImagePath;
	this->footer = footer;
	this->listOfChoices = listOfButtons;
	this->activateCancel = activateCancelButton;
}

ChooseDialogInfo::~ChooseDialogInfo()
{

}

std::vector<ChooseDialogButtonInfo *> & ChooseDialogInfo::getListOfChoices()
{
	return listOfChoices;
}

std::string ChooseDialogInfo::getTitle()
{
	return title;
}

std::string ChooseDialogInfo::getCode()
{
	return code;
}

std::string ChooseDialogInfo::getTitleImagePath()
{
	return titleImagePath;
}

std::string ChooseDialogInfo::getFooter()
{
	return footer;
}

bool ChooseDialogInfo::activateCancelButton()
{
	return activateCancel;
}

