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

#include "smartmatic-entry.h"
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <gdk/gdkkeysyms.h>
#include <System/Utils/StringUtils.hxx>

using namespace std;
using namespace Gtk;
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

SmartmaticEntry::SmartmaticEntry(EntryType type)
: ISmartmaticText()
{
	this->type = type;
	initialize();
}

SmartmaticEntry::SmartmaticEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Glib::ObjectBase("SmartmaticEntry"),
 Gtk::Entry(cobject),
 ISmartmaticText()
{
	this->type = All;
	initialize();
}

SmartmaticEntry::~SmartmaticEntry()
{

}

void SmartmaticEntry::initialize()
{
	signal_changed().connect(sigc::mem_fun(*this, &SmartmaticEntry::changeText));
	signal_insert_text().connect(sigc::mem_fun(*this, &SmartmaticEntry::insertText));
	signal_delete_text().connect(sigc::mem_fun(*this, &SmartmaticEntry::deleteText));

	this->pos = 0;
}

bool SmartmaticEntry::on_button_press_event(GdkEventButton* event)
{
	bool returnValue = false;

	if(event->button != 3)
	{
		returnValue = Entry::on_button_press_event(event);
	}

	return returnValue;
}

void SmartmaticEntry::SetType(EntryType type)
{
	this->type = type;
}

void SmartmaticEntry::setText(std::string text)
{
	set_text(text);
}

std::string SmartmaticEntry::getText()
{
	return (std::string)get_text();
}

void SmartmaticEntry::on_insert_text(const Glib::ustring& text, int* position)
{
	if(max != -1 && getText().size() >= (unsigned int)max)
	{
		return;
	}

	if(text.validate())
	{
		switch(type)
		{
			case Alphabetic:
				if(isalpha(text[0]))
				{
					Entry::on_insert_text(text, position);
				}
				break;
			case Decimal:
				if(isdigit(text[0]))
				{
					Entry::on_insert_text(text, position);
					DeleteLeftZero();
				}
				break;
			case AlphaNumeric:
				if(isalnum(text[0]))
				{
					Entry::on_insert_text(text, position);
				}
				break;
			case All:
				Entry::on_insert_text(text, position);
				break;
			case AllWithoutNumber:
				if(!isdigit(text[0]))
				{
					Entry::on_insert_text(text, position);
				}
				break;
			case AllWithoutAlphabetic:
				if(!isalpha(text[0]))
				{
					Entry::on_insert_text(text, position);
				}
				break;
			case Mask:
				if (mask.empty() || StringUtils::isFound(mask, text[0]))
				{
					Entry::on_insert_text(text, position);
				}
				break;
			default:
				break;
		}
	}

	m_signal_inserted.emit();
}

bool SmartmaticEntry::DeleteLeftZero()
{
	string text = get_text();

	if(text.size() > 1)
	{
		if(text[0] == '0')
		{
			text = text.substr(1);
			set_text(text);
			return true;
		}
	}

	return false;
}

bool SmartmaticEntry::on_focus_in_event(GdkEventFocus * event)
{
	if(type == Decimal)
	{
		bool deleteZero = false;

		do
		{
			deleteZero = DeleteLeftZero();
		}while(deleteZero);
	}

	return Entry::on_focus_in_event(event);
}

SmartmaticEntry::text_inserted SmartmaticEntry::signal_inserted()
{
	return m_signal_inserted;
}

void SmartmaticEntry::SetNumber(int number)
{
	stringstream ss;
	ss << number;
	set_text(ss.str());
}

bool SmartmaticEntry::GetNumber(int& number)
{
	bool returnValue = false;

	if(type == Decimal)
	{
		returnValue = true;

		ustring value = get_text();
		number = StringUtils::stringToInt(value.c_str());
	}
	
	return returnValue;
}

bool SmartmaticEntry::on_key_press_event(GdkEventKey* event)
{
	bool result = false;

#ifdef GDK_KEY_Menu
	if (event->keyval != GDK_KEY_Menu)
	{
		result = Entry::on_key_press_event(event);
	}
#else
	if (event->keyval != 0xff67)
	{
		result = Entry::on_key_press_event(event);
	}
#endif

	return result;
}

void SmartmaticEntry::setPosition(unsigned int pos)
{
	this->pos = pos;
}

unsigned int SmartmaticEntry::getPosition()
{
	return this->pos;
}

void SmartmaticEntry::setMax(int max)
{
	set_max_length(max);
	ISmartmaticText::setMax(max);
}

void SmartmaticEntry::setBGError()
{
	set_name("entry_error_frame");
}

void SmartmaticEntry::setBGNormal()
{
	set_name("");
}

void SmartmaticEntry::changeText()
{
	setBGNormal();
	validate();
}

void SmartmaticEntry::insertText(const Glib::ustring& text, int* position)
{
	setBGNormal();
	validate();
}

void SmartmaticEntry::deleteText(int i, int j)
{
	setBGNormal();
	validate();
}
