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

#include "event-box-choose-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"

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
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;

EventBoxChooseWidget::EventBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo * dialogInfo)
{
	code = dialogInfo->getCode();

	CardActivatorFunctionalityConfiguration* config = SAESGUIConfigurationManager::Current()->GetCardActivatorWidgetConfiguration();

	selectedColor.set_rgb(config->getSelectedColor().getRed(), config->getSelectedColor().getGreen(), config->getSelectedColor().getBlue());
	unSelectedColor.set_rgb(config->getUnSelectedColor().getRed(), config->getUnSelectedColor().getGreen(), config->getUnSelectedColor().getBlue());

	labelTitle.set_label(dialogInfo->getTitle());
	labelTitle.set_alignment(0.0, 0.5);//TODO configuration
	labelTitle.set_padding(5, 0);
	labelTitle.set_size_request(140, 30);
	labelTitle.set_line_wrap(true);
	Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	labelTitle.modify_font(fontTitle);

	imageTitle.set(dialogInfo->getTitleImagePath());

	hboxPrincipal = manage(new HBox(false, 5));

	if(dialogInfo->getTitleImagePath().compare("")!=0)
	{
		hboxPrincipal->pack_start (imageTitle,Gtk::PACK_SHRINK);
	}

	hboxPrincipal->pack_start (labelTitle,false,false);

	vboxEvents = manage(new VBox(true, 5));

	labelWidth = 175;
	for(unsigned int i=0;i < (dialogInfo->getListOfChoices()).size(); i++)
	{
		eventbox = manage(new EventBox());
		eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
		eventbox->set_size_request(labelWidth,100);

		eventLabel = manage(new Label());
		Pango::FontDescription fontEvent = eventLabel->get_style()->get_font();
		fontEvent.set_size(9*Pango::SCALE);
		eventLabel->modify_font(fontEvent);	
		eventLabel->set_label (dialogInfo->getListOfChoices()[i]->getName());
		eventLabel->set_size_request(labelWidth,-1);

		Pango::Rectangle rec, dummy;
		Glib::RefPtr<Pango::Layout> layout;
		layout = eventLabel->get_layout();
		layout->get_pixel_extents(dummy, rec);

		if(rec.get_width() < labelWidth)
		{
			eventLabel->set_alignment(0.5, 0.5);
		}
		else
		{
			eventLabel->set_line_wrap(true);
			eventLabel->set_justify(JUSTIFY_CENTER);

			Pango::Rectangle rec1, dummy1;
			Glib::RefPtr<Pango::Layout> layout1;
			layout1 = eventLabel->get_layout();
			layout1->get_pixel_extents(dummy1, rec1);

			int paddingLabel = (labelWidth - rec1.get_width()) / 2;
			eventLabel->set_padding(paddingLabel, 0);
		}

		eventbox->add(*eventLabel);
		eventbox->signal_button_press_event().connect(sigc::bind<std::string>( sigc::mem_fun(*this,&EventBoxChooseWidget::on_option_clicked), dialogInfo->getListOfChoices()[i]->getCode()));

		eventboxList.push_back(eventbox);

		frameEvent = manage(new Frame());
		frameEvent->set_name(SAESGUIConfigurationManager::Current()->GetEventboxChooseWidgetFrameName());
		frameEvent->add(*eventbox);

		vboxEvents->pack_start(*frameEvent,Gtk::PACK_SHRINK);
	}	

	hboxPrincipal->pack_start(*vboxEvents);
	add(*hboxPrincipal);

	// Using pretty much the same model as the one used in the election process
	on_option_clicked(NULL,dialogInfo->getListOfChoices()[0]->getCode());
	show_all_children ();
	set_visible (true);
}

void EventBoxChooseWidget::ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight)
{
	for(unsigned int i=0;i<eventboxList.size();i++)
	{
		eventboxList[i]->set_size_request (WidgetOptionsWidth,WidgetOptionsHeight);
	}
}

bool EventBoxChooseWidget::on_option_clicked(GdkEventButton* event, std::string optionMarked)
{
	optionSelected = optionMarked;
	SetSelection(ElectionStringResourcesManager::Current()->getResource(optionMarked));
	return true;
}

void EventBoxChooseWidget::SetSelection(std::string optionMarked)
{	
	for(unsigned int i=0;i<eventboxList.size();i++)
	{
		vector<Gtk::Widget*> list = eventboxList[i]->get_children();
		Gtk::Label* labelTemp = (Gtk::Label*)list[0];
		if(labelTemp->get_label().compare(optionMarked)==0)
	   {
			Pango::FontDescription fontEvent = labelTemp->get_style()->get_font();
			fontEvent.set_weight(Pango::WEIGHT_ULTRABOLD);
			eventboxList[i]->modify_bg(Gtk::STATE_NORMAL, selectedColor);
			labelTemp->modify_font(fontEvent);
	   }
	   else
	   {
		   Pango::FontDescription fontEvent = labelTemp->get_style()->get_font();
			fontEvent.set_weight(Pango::WEIGHT_ULTRALIGHT);
			labelTemp->modify_font(fontEvent);	
		   eventboxList[i]->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
	   }

		if(labelTemp->get_line_wrap())
		{
			Pango::Rectangle rec1, dummy1;
			Glib::RefPtr<Pango::Layout> layout1;
			layout1 = labelTemp->get_layout();
			layout1->get_pixel_extents(dummy1, rec1);
			int paddingLabel = (150 - rec1.get_width()) / 2;
			labelTemp->set_padding(paddingLabel, 0);
		}
	}

}

EventBoxChooseWidget::~EventBoxChooseWidget()
{

}

std::string EventBoxChooseWidget::getOptionName()
{
	return code;
	//return labelTitle.get_label();
}

std::string EventBoxChooseWidget::getOptionValue()
{
	return optionSelected;
}

void EventBoxChooseWidget::Dispose()
{
	//connCombo.disconnect();
}
