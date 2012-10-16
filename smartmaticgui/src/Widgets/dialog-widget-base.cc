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

#include "dialog-widget-base.h"
#include <iostream>
using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

std::string DialogWidgetBase::widgetBaseName = "";

DialogWidgetBase::DialogWidgetBase()
{	
	set_visible (true);
	set_border_width(0);
	set_homogeneous (false);
	
    int headerHeigth = 80;//TODO configuration
	frameHeader.set_size_request(-1, headerHeigth);
	
	int footerHeigth = 80;//TODO configuration
	frameFooter.set_size_request(-1, footerHeigth);

	borderFrameHeader.set_size_request(-1, headerHeigth);
	borderframeFooter.set_size_request(-1, footerHeigth);

	borderFrameHeader.set_shadow_type(Gtk::SHADOW_IN);
	borderframeClientArea.set_shadow_type(Gtk::SHADOW_IN);
	borderframeFooter.set_shadow_type(Gtk::SHADOW_IN);

	frameHeader.set_shadow_type(Gtk::SHADOW_IN);
	frameClientArea.set_shadow_type(Gtk::SHADOW_IN);
	frameFooter.set_shadow_type(Gtk::SHADOW_IN);
	
	borderFrameHeader.add(frameHeader);
	borderframeClientArea.add(frameClientArea);
	borderframeFooter.add(frameFooter);

	Initialize();

	frameHeaderEventBox.add(borderFrameHeader);
	frameClientAreaEventBox.add(borderframeClientArea);
	frameFooterEventBox.add(borderframeFooter);

	pack_start(frameHeaderEventBox,false,false);
	pack_start(frameClientAreaEventBox);
	pack_start(frameFooterEventBox,false,false);
	
	show_all_children ();
}

void DialogWidgetBase::SetFrameHeaderName(std::string frameHeaderName)
{
	frameHeader.set_name(frameHeaderName);
};

void DialogWidgetBase::SetFrameClientAreaName(std::string frameClientAreaName)
{
	frameClientArea.set_name(frameClientAreaName);
};

void DialogWidgetBase::SetFrameFooterName(std::string frameFooterName)
{
	frameFooter.set_name(frameFooterName);
};

void DialogWidgetBase::SetBorderFrameHeaderName(std::string borderFrameHeaderName)
{
	borderFrameHeader.set_name(borderFrameHeaderName);
};

void DialogWidgetBase::SetBorderframeClientAreaName(std::string borderframeClientAreaName)
{
	borderframeClientArea.set_name(borderframeClientAreaName);
};

void DialogWidgetBase::SetBorderframeFooterName(std::string borderframeFooterName)
{
	borderframeFooter.set_name(borderframeFooterName);
};

void DialogWidgetBase::SetWidgetName(Gtk::Widget & widget, std::string baseName, std::string name)
{
	std::string nameFinally = baseName + name;
	widget.set_name(nameFinally);
};

DialogWidgetBase::~DialogWidgetBase()
{

};

void DialogWidgetBase::Initialize()
{

	if(DialogWidgetBase::widgetBaseName == "")
	{		
		DialogWidgetBase::widgetBaseName = "dialog_widget_base";
	}
	
	SetWidgetName(frameHeader, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameframeHeader");
	SetWidgetName(frameClientArea, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameframeClientArea");
	SetWidgetName(frameFooter, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameframeFooter");
	SetWidgetName(borderFrameHeader, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameborderFrameHeader");
	SetWidgetName(borderframeClientArea, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameborderframeClientArea");
	SetWidgetName(borderframeFooter, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameborderframeFooter");
	SetWidgetName(frameHeaderEventBox, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameHeaderEventBox");
	SetWidgetName(frameClientAreaEventBox, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameClientAreaEventBox");
	SetWidgetName(frameFooterEventBox, DialogWidgetBase::widgetBaseName, "DialogWidgetBaseFrameFooterEventBox");
}

void DialogWidgetBase::SetBaseWidgetsBaseName(std::string baseName)
{
	widgetBaseName = baseName;
}
