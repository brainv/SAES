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

#include "help-window.h"
#include <libintl.h>
#define _(String) gettext (String) 

using namespace std;
using namespace Smartmatic::GUI::Windows;

	HelpWindow::HelpWindow(string title, vector<HelpItem> content)
	{
		set_title(title);
		set_decorated(false);
		//set_has_frame(false);
		BuildHelp(content);
	};

	HelpWindow::~HelpWindow()
	{
	};
	
	void HelpWindow::BuildHelp(vector<HelpItem> content)
	{
		SetInitialConfiguration();
		
		//Load the Glade file and instiate its widgets:
		Glib::RefPtr<Gtk::Builder> builder;

		try
		{
			builder = Gtk::Builder::create_from_file(UI_FILE);
		}
		catch (const Glib::FileError & ex)
		{
			std::cerr << ex.what() << std::endl;
		}

		builder->get_widget("main_table", main_table);
		builder->get_widget("label_instructions", label_instructions);
		builder->get_widget("key_value_table", key_value_table);
		builder->get_widget("label_navigation_text", label_navigation_text);
		builder->get_widget("label_navigation_type", label_navigation_type);
		builder->get_widget("image_keyboard", simple_navigation_image);
		
		label_instructions->set_label(_("Smartmatic.GUI.Windows.HelpWindow.InstructionMessage"));
		
		//Build Help Table Content with Help-Item pairs...
		if(content.size() > 0)
		{
			key_value_table->resize(content.size() + 1, 2);	
			int size = content.size();
			for(int i = 0; i < size; i++)
			{
				Gtk::Label key_label;
				Gtk::Label action_label;

				key_label.set_label(content[i].Get_Key());
				action_label.set_label(content[i].Get_Action());

				key_value_table->attach(key_label, 0, 1, i+1, i+2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
				key_value_table->attach(action_label, 1, 2, i+1, i+2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			}
		}
		
		signal_key_press_event().connect(sigc::mem_fun(*this, &HelpWindow::key_pressed));
		
		add(*main_table);
		show_all_children();
	};
	
	bool HelpWindow::key_pressed(GdkEventKey *event)
	{
        return false;
	}

	void HelpWindow::SetInitialConfiguration()
	{
		//Initialize Window Properties
		set_border_width(0);
		set_position(Gtk::WIN_POS_CENTER);
		set_modal(true);				//If TRUE, other windows are not usable while this one is up	
		set_skip_taskbar_hint(true);	//Hides the window from the lower task bar
		set_skip_pager_hint(true);
		set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG) ; 
		//set_resizable(false);
	};


