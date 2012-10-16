/*
 * EventboxSelectionWidget.cpp
 *
 *  Created on: Sep 5, 2011
 *      Author: Juan Delgado
 */

#include "EventboxSelectionWidget.h"
#include <iostream>

using namespace Gtk;
using namespace std;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;

EventboxSelectionWidget::EventboxSelectionWidget(std::map<string, std::map< string, string > > selectionMap)
{
	widthRequested = -1;
	selectedBoxColor = Gdk::Color("white");
	unselectedBoxColor = Gdk::Color("white");
	selectedFontColor = Gdk::Color("black");
	unselectedFontColor = Gdk::Color("black");

	this->selectionMap = selectionMap;
	eventboxMap.clear();
	labelMap.clear();
	namesSelected.clear();
	valuesSelected.clear();
	titleLabelList.clear();
	namesSelected.clear();
	valuesSelected.clear();

	for(std::map<string, std::map< string, string > >::iterator iter = selectionMap.begin();
			iter != selectionMap.end(); iter++)
	{
		Label* labelTitle = manage(new Label(iter->first));
		labelTitle->show();
		pack_start(*labelTitle, false, false);
		titleLabelList.push_back(labelTitle);

		VBox* insideVbox = manage(new VBox(true, 1));
		insideVbox->show();
		pack_start(*insideVbox);

		for(std::map<string, string>::iterator iter2 = iter->second.begin();
				iter2 != iter->second.end(); iter2++)
		{
			Frame* frame = manage(new Frame());
			frame->show();
			insideVbox->pack_start(*frame);

			EventBox* eventbox = manage(new EventBox());
			eventbox->show();
			eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
			eventbox->signal_button_press_event().connect(sigc::bind<std::string>(
					sigc::mem_fun(*this,&EventboxSelectionWidget::on_event_selected),
					iter2->first));
			frame->add(*eventbox);
			eventboxMap[iter2->first] = eventbox;

			Label* label = manage(new Label(iter2->second));
			label->show();
			eventbox->add(*label);
			labelMap[iter2->first] = label;
		}
	}

	show();
}

EventboxSelectionWidget::~EventboxSelectionWidget()
{

}

void EventboxSelectionWidget::SetFirstSelected()
{
	for(std::map<string, std::map< string, string > >::iterator iter = selectionMap.begin();
			iter != selectionMap.end(); iter++)
	{
		on_event_selected(NULL, iter->second.begin()->first);
	}
}

bool EventboxSelectionWidget::on_event_selected(GdkEventButton* event, string value)
{
	for(std::map<string, std::map< string, string > >::iterator iter = selectionMap.begin();
			iter != selectionMap.end(); iter++)
	{
		if(iter->second.find(value) != iter->second.end())
		{
			for(std::map<string, string>::iterator iter2 = iter->second.begin();
					iter2 != iter->second.end(); iter2++)
			{
				if(iter2->first == value)
				{
					SetEventboxSelected(true, labelMap[iter2->first], eventboxMap[iter2->first]);

					namesSelected[iter->first] = iter2->second;
					valuesSelected[iter->first] = iter2->first;
				}
				else
				{
					SetEventboxSelected(false, labelMap[iter2->first], eventboxMap[iter2->first]);
				}
			}
			break;
		}
	}

	m_type_box_clicked.emit(GetValuesSelected());

	return true;
}

void EventboxSelectionWidget::set_size_request(int width, int height)
{
	VBox::set_size_request(width, height);

	widthRequested = width -15;

	for(std::map< string, Label* >::iterator iter = labelMap.begin();
			iter != labelMap.end(); iter++)
	{
		iter->second->set_size_request(widthRequested, -1);
	}

	for(std::list <Gtk::Label* >::iterator iter = titleLabelList.begin();
			iter != titleLabelList.end(); iter++)
	{
		(*iter)->set_size_request(widthRequested, -1);
		(*iter)->set_line_wrap(true);
	}
}

void EventboxSelectionWidget::SetEventboxSelected(bool isSelected, Label* label, EventBox* eventbox)
{
	if(isSelected)
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, selectedBoxColor);
		LabelConfiguration::SetLabelConfiguration(label, selectedLabelConfiguration);
		label->modify_fg(Gtk::STATE_NORMAL, selectedFontColor);
	}
	else
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, unselectedBoxColor);
		LabelConfiguration::SetLabelConfiguration(label, unselectedLabelConfiguration);
		label->modify_fg(Gtk::STATE_NORMAL, unselectedFontColor);
	}

	label->set_alignment(0.5, 0.5);
	label->set_padding(0, 0);
	label->set_line_wrap(false);

	Pango::Rectangle rec, dummy;
	Glib::RefPtr<Pango::Layout> layout;
	layout = label->get_layout();
	layout->get_pixel_extents(dummy, rec);

	if(rec.get_width() >= widthRequested)
	{
		label->set_line_wrap(true);
		label->set_justify(JUSTIFY_CENTER);

		layout = label->get_layout();
		layout->get_pixel_extents(dummy, rec);

		int paddingLabel = (widthRequested + 15 - rec.get_width()) / 2;
		label->set_padding(paddingLabel, 0);
	}
}

list< string > EventboxSelectionWidget::GetNamesSelected()
{
	list< string > returnList;

	for(std::map< string, string >::iterator iter = namesSelected.begin();
			iter != namesSelected.end(); iter++)
	{
		returnList.push_back(iter->second);
	}

	return returnList;
}

list< string > EventboxSelectionWidget::GetValuesSelected()
{
	list< string > returnList;

	for(std::map< string, string >::iterator iter = valuesSelected.begin();
			iter != valuesSelected.end(); iter++)
	{
		returnList.push_back(iter->second);
	}

	return returnList;
}

void EventboxSelectionWidget::SetSelectedBoxColor(Gdk::Color color)
{
	selectedBoxColor = color;
}

void EventboxSelectionWidget::SetUnselectedBoxColor(Gdk::Color color)
{
	unselectedBoxColor = color;
}

void EventboxSelectionWidget::SetSelectedFontColor(Gdk::Color color)
{
	selectedFontColor = color;
}

void EventboxSelectionWidget::SetUnselectedFontColor(Gdk::Color color)
{
	unselectedFontColor = color;
}

void EventboxSelectionWidget::SetSelectedFontDescription(LabelConfiguration& labelConfiguration)
{
	selectedLabelConfiguration = labelConfiguration;
}

void EventboxSelectionWidget::SetUnselectedFontDescription(LabelConfiguration& labelConfiguration)
{
	unselectedLabelConfiguration = labelConfiguration;
}

void EventboxSelectionWidget::SetTitlesFontDescription(LabelConfiguration& labelConfiguration)
{
	for(std::list <Gtk::Label* >::iterator iter = titleLabelList.begin();
			iter != titleLabelList.end(); iter++)
	{
		LabelConfiguration::SetLabelConfiguration((*iter), labelConfiguration);
	}
}

void EventboxSelectionWidget::SetTitlesHeight(int height)
{
	for(std::list <Gtk::Label* >::iterator iter = titleLabelList.begin();
			iter != titleLabelList.end(); iter++)
	{
		(*iter)->set_size_request(widthRequested, height);
	}
}

EventboxSelectionWidget::type_box_clicked EventboxSelectionWidget::signal_box_clicked()
{
	return m_type_box_clicked;
}
