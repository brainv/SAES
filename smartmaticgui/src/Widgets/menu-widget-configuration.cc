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

#include "menu-widget-configuration.h"
using namespace Smartmatic::GUI::Widgets;

MenuWidgetConfiguration::MenuWidgetConfiguration(int firstWidth, int firstHeight, int firstSpacing, int firstBrdrWidth, int firstFrmWidth,
			                        int firstFrmHeight, int secondWidth, int secondHeight, int secondSpacing, int secondBrdrWidth,
			                        int secondFrmPadding, bool hasShortcut)
{
	FirstLevel_Width = firstWidth;
	FirstLevel_Height = firstHeight;
	FirstLevel_Spacing = firstSpacing;
	FirstLevel_BorderWidth = firstBrdrWidth;
	FirstLevel_Frame_Width = firstFrmWidth;
	FirstLevel_Frame_Height = firstFrmHeight;
	SecondLevel_Width = secondWidth;
	SecondLevel_Height = secondHeight;
	SecondLevel_Spacing = secondSpacing;
	SecondLevel_BorderWidth = secondBrdrWidth;
	SecondLevel_Frame_Padding = secondFrmPadding;
	HasButton_Shortcut = hasShortcut;
}