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

#include "smartmatic-entry-number.h"
#include <System/Utils/StringUtils.hxx>
#include <iostream>

using namespace std;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Utils;

SmartmaticEntryNumber::SmartmaticEntryNumber(int max, int min)
:SmartmaticEntry(SmartmaticEntry::Decimal)
{
	this->max = max;
	this->min = min;
	this->set_alignment( Gtk::ALIGN_RIGHT );
	this->mask = "0123456789";
}

void SmartmaticEntryNumber::on_insert_text(const Glib::ustring& text, int* position)
{
	if(max != -1 && get_text().size() >= (unsigned int)max)
	{
		return;
	}

	if(isdigit(text[0]))
	{
		Entry::on_insert_text(text, position);

		Glib::ustring check = get_text();

		int number;
		number = StringUtils::stringToInt(check);
		if(number > max)
		{
			set_text(StringUtils::intToString(max));
		}
		else if(number < min)
		{
			set_text(StringUtils::intToString(min));
		}

		m_signal_inserted.emit();
	}
}
