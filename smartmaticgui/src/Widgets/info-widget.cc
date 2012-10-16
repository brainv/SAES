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

#include "info-widget.h"

using namespace std;
using namespace Smartmatic::GUI::Widgets;

InfoWidget::InfoWidget (std::vector< std::vector<std::string> > & info)
{
	vbox = NULL;
	vbox = new Gtk::VBox();	
	eventBox = manage(new Gtk::EventBox());
	
	for(unsigned int i=0;i<info.size();i++) 
    {		
		hbox = manage(new Gtk::HBox());
		information = manage(new Gtk::Label()); 
		vectorLabel.push_back(information);
		information->set_name("mainwidowinformation");
		
		Pango::FontDescription font = information->get_style()->get_font();
		font.set_size(12*Pango::SCALE);
		information->modify_font(font);							
		information->set_label(info[i][0] + " " + info[i][1]);  
		hbox->add(*information);  
		hbox->set_size_request (-1,-1);

		informationeventBox = manage(new Gtk::EventBox());

		std::stringstream ss;
		ss << "main_window_information_event_box_" << i;
		informationeventBox->set_name(ss.str());
		informationeventBox->add(*hbox);
		vbox->add(*informationeventBox);  
	}

	eventBox->set_name("eventBoxmainwidowinformation");
	eventBox->add(*vbox);
	eventBox->show_all();

	add(*eventBox);
}

void InfoWidget::SetVector (std::vector< std::vector<std::string> > & info)
{
	std::vector<Gtk::Label*>::iterator iter = vectorLabel.begin();

	Gtk::Label* label = NULL;
	//vectorLabel; ///< The vector label

	for(unsigned int i=0;i<info.size();i++)
    {
		label = *iter;
		label->set_label(info[i][0] + " " + info[i][1]);

		iter++;
	}
}

InfoWidget::~InfoWidget()
{
	if(vbox!=NULL)
	{
		delete(vbox);
	}
}

