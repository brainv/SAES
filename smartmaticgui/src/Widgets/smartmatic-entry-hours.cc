/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#include "smartmatic-entry-hours.h"
#include <iostream>

using namespace std;
using namespace Gtk;
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;

SmartmaticEntryHours::SmartmaticEntryHours()
{
	entry_hour = manage(new SmartmaticEntryNumber(23,0));
	entry_hour->set_size_request(100, -1);
	entry_hour->setMax(2);
	entry_hour->signal_inserted().connect(sigc::mem_fun(*this, &SmartmaticEntryHours::TextInserted));
	
	entry_min = manage(new SmartmaticEntryNumber(59,0));
	entry_min->set_size_request(100, -1);
	entry_min->setMax(2);
	entry_min->signal_inserted().connect(sigc::mem_fun(*this, &SmartmaticEntryHours::TextInserted));
	
	entry_sec = manage(new SmartmaticEntryNumber(59,0));
	entry_sec->set_size_request(100 , -1);
	entry_sec->setMax(2);
	entry_sec->signal_inserted().connect(sigc::mem_fun(*this, &SmartmaticEntryHours::TextInserted));
	
	label_hour = manage(new Label());
	
	label_min = manage(new Label());
	
	label_sec = manage(new Label());

	pack_start(*label_hour, false, false);
	pack_start(*entry_hour, false, false);
	pack_start(*label_min, false, false);
	pack_start(*entry_min, false, false);
	pack_start(*label_sec, false, false);
	pack_start(*entry_sec, false, false);
	show_all_children();
}

void SmartmaticEntryHours::Initialize(int hours, int mins, int secs)
{
	
	std::stringstream sHours;
	std::stringstream sMins;
	std::stringstream sSecs;
	sHours << hours;
	sMins << mins;
	sSecs << secs;
	entry_hour->set_text(sHours.str());
	entry_min->set_text(sMins.str());
	entry_sec->set_text(sSecs.str());
	
}

int SmartmaticEntryHours::getHours()
{
	ustring str_hour = entry_hour->get_text();
	std::stringstream s;
	int result = 0;
	s << str_hour.raw();
	s >> result;
	return result;

}

	 
int SmartmaticEntryHours::getMins()
{
	ustring str_min = entry_min->get_text();
	std::stringstream s;
	int result = 0;
	s << str_min.raw();
	s >> result;
	return result;
}

int SmartmaticEntryHours::getSecs()
{
	ustring str_sec = entry_sec->get_text();
	std::stringstream s;
	int result = 0;
	s << str_sec.raw();
	s >> result;
	return result;
}

bool SmartmaticEntryHours::CheckFields()
{
	bool fieldsEmpty = false;

	if(entry_hour->get_text() == "" ||
			entry_min->get_text() == "" ||
			entry_sec->get_text() == "")
	{
		fieldsEmpty = true;
	}

	return fieldsEmpty;
}

SmartmaticEntryHours::fields_complete SmartmaticEntryHours::fields_complete_signal()
{
	return m_fields_complete;
}

void SmartmaticEntryHours::SetLabels(ustring str_hour, ustring str_min, ustring str_sec)
{
	label_hour->set_text(str_hour);
	label_min->set_text(str_min);
	label_sec->set_text(str_sec);
}

void SmartmaticEntryHours::TextInserted()
{
	m_fields_complete.emit(CheckFields());
}
