/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include "Gui/Widgets/party-contest-widget.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <iostream>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Environment;


PartyContestWidget::PartyContestWidget(bool isVisibleImage,std::string labeltext, bool isVisibleLabel,std::string party,std::string contest,ImageType imageType,bool isImagenTextoR,bool isHorizontalR)
{
	this->party = party;
	this->contest = contest;
	//labelTitle
	labelTitle.set_alignment(0.5, 0.5);	//TODO configuration
	labelTitle.set_padding(10, 0);
	labelTitle.set_size_request(-1, 30);
	labelTitle.set_line_wrap(true);
		Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
		fontTitle.set_size(10*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelTitle.modify_font(fontTitle);
	labelTitle.set_label(labeltext);

	if(!isVisibleLabel)
		labelTitle.set_no_show_all();
	
	colorEventBox.set_rgb (0xFFFF,0xFFFF,0xFFFF);
	
	switch (imageType) 
	{
      case  ImageType_Selected:
    	 imageTitle.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/selected.png"));
         break;
     case  ImageType_Unselected:
         imageTitle.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/unselected.png"));
         break;
	 case ImageType_NotApplicable:
		imageTitle.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/notapplicable.png"));
         break;
	}

	alignImage.add(imageTitle);
	
	if(!isVisibleImage)
		alignImage.set_no_show_all();
	
	//IF THE GUIDANCE OF THE COMPONENTS IS HORIZONTAL
	if(isHorizontalR)
	{
		//IF THE ELEMENT IS UP IMAGE AND TEXT
		if(isImagenTextoR)
		{
			hboxEvents.pack_start (alignImage,Gtk::PACK_SHRINK);
			hboxEvents.pack_start (labelTitle,Gtk::PACK_SHRINK);
		}
		else
		{
			hboxEvents.pack_start (labelTitle,Gtk::PACK_SHRINK);
			hboxEvents.pack_start (alignImage,Gtk::PACK_SHRINK);	
		}

		alignImage.set_padding(0,0,10,0);
		Align.add(hboxEvents);
		//ALIGN CENTER
		//Align.set(0.5, 0.5, 0.0, 0.0);
	}
	else
	{
		if(isImagenTextoR)
		{
			vboxEvents.pack_start (alignImage,Gtk::PACK_SHRINK);
			vboxEvents.pack_start (labelTitle,Gtk::PACK_SHRINK);
		}
		else
		{
			vboxEvents.pack_start (labelTitle,Gtk::PACK_SHRINK);
			vboxEvents.pack_start (alignImage,Gtk::PACK_SHRINK);
		}
		alignImage.set_padding(10,0,0,0);
		Align.add(vboxEvents);
	}
	
	
	setColorEventBox(colorEventBox);
	
	//set_label_align (0.5,0.5);
	Align.set(0.5, 0.5, 0.0, 0.0);

	event.add(Align);

	add(event);
	show_all_children();
	set_size_request (-1,-1);
	set_events(Gdk::BUTTON_PRESS_MASK);
	signal_button_press_event().connect(sigc::mem_fun(*this, &PartyContestWidget::on_zone_clicked));
}

void PartyContestWidget::Initialize ()
{
}

void PartyContestWidget::Dispose()
{	
}

/**
* @brief method to set visibility of the image
*/
void PartyContestWidget::setIsVisibleImage(bool isVisibleImageR)
{
	alignImage.set_visible(isVisibleImageR);
	alignImage.set_no_show_all();
}
/**
* @brief method to set visibility of the label
*/
void PartyContestWidget::setIsVisibleLabel(bool isVisibleLabelR)
{
	labelTitle.set_visible (isVisibleLabelR);
}
/**
* @brief method to set THE GUIDANCE OF THE COMPONENTS
*/
void PartyContestWidget::setIsHorizontalR(bool isHorizontal)
{   
	this->isHorizontal=isHorizontal;	
}

void PartyContestWidget::setIsImagenTextoR(bool isImagenText)
{   
	this->isImageTexto=isImagenText;	
}

void PartyContestWidget::setLabelText(std::string labeltextR)
{
	labelTitle.set_label(labeltextR);
}

bool  PartyContestWidget::on_zone_clicked(GdkEventButton* event )
{	
	signalEmitted.emit(party,contest);
	return true;
};

void PartyContestWidget::setColorEventBox(Gdk::Color selectedColor)
{
	event.modify_bg(Gtk::STATE_NORMAL, selectedColor);
}

void PartyContestWidget::setSizeWidget(int width,int height)
{
	set_size_request (width,height);
}

PartyContestWidget::~PartyContestWidget()
{

}
