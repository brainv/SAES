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

#include "custom-attributes-combo-selections-widget.h"
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;

CustomAttributesComboSelectionsWidget::CustomAttributesComboSelectionsWidget(std::string labelTitleKey,std::string imagePath,bool isEventType)
{
	isEvent = isEventType;

	labelTitle.set_label(labelTitleKey);
	labelTitle.set_alignment(0.5, 0.5);//TODO configuration
	labelTitle.set_size_request(-1, 65);
	Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	fontTitle.set_size(11*Pango::SCALE);
	labelTitle.modify_font(fontTitle);	

	imageTitle.set(imagePath);

	if(imagePath.compare("")!=0)
	{
		hboxHeader.pack_start (imageTitle,Gtk::PACK_SHRINK);
	}

	eventBoxTitle.add(labelTitle);
	eventBoxTitle.set_name(SAESGUIConfigurationManager::Current()->GetCustomAttributeComboSelectionsWidgetTitleName());

	hboxHeader.pack_start (eventBoxTitle);

	pack_start(hboxHeader,false,false);
	show_all_children ();
	set_visible (true);
	set_size_request(400, -1);
}

void CustomAttributesComboSelectionsWidget::addComboWidget(ComboBoxChooseWidget* comboWidget)
{
	pack_start(*comboWidget,Gtk::PACK_SHRINK);
	listOfCombos.push_back (comboWidget);
	show_all_children ();
}

void CustomAttributesComboSelectionsWidget::addBoxWidget(EventBoxChooseWidget* eventWidget)
{
	pack_start(*eventWidget,Gtk::PACK_SHRINK);
	listOfBoxes.push_back (eventWidget);
	show_all_children ();
}

CustomAttributesComboSelectionsWidget::~CustomAttributesComboSelectionsWidget()
{

}

void CustomAttributesComboSelectionsWidget::ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight)
{
	if(isEvent)
	{
		for(unsigned int l=0;l<listOfBoxes.size();l++)
		{
			listOfBoxes[l]->ResizeOptionsWidgets(WidgetOptionsWidth,WidgetOptionsHeight);
		}
	}
	else
	{
		for(unsigned int l=0;l<listOfCombos.size();l++)
		{
			listOfCombos[l]->ResizeOptionsWidgets(WidgetOptionsWidth,WidgetOptionsHeight);
		}
	}
}

void CustomAttributesComboSelectionsWidget::Dispose()
{	
	if(isEvent)
	{
		for(unsigned int l=0;l<listOfBoxes.size();l++)
		{
			listOfBoxes[l]->Dispose();
			remove(*listOfBoxes[l]);
			delete(listOfBoxes[l]);
		}
		listOfBoxes.clear();
	}
	else
	{
		for(unsigned int l=0;l<listOfCombos.size();l++)
		{
			listOfCombos[l]->Dispose();
			remove(*listOfCombos[l]);
			delete(listOfCombos[l]);
		}
		listOfCombos.clear();
	}
}

std::vector<ComboInfo> CustomAttributesComboSelectionsWidget::getOptionsSelected()
{
	std::vector<ComboInfo> choicesSelected;

	if(isEvent)
	{
		for(unsigned int i=0;i < listOfBoxes.size();i++)
		{
			ComboInfo info(listOfBoxes[i]->getOptionName (),listOfBoxes[i]->getOptionValue ());
			choicesSelected.push_back(info);
		}
	}
	else
	{
		for(unsigned int i=0;i < listOfCombos.size();i++)
		{
			ComboInfo info(listOfCombos[i]->getOptionName (),listOfCombos[i]->getOptionValue ());
			choicesSelected.push_back(info);
		}
	}
	return choicesSelected;
}
