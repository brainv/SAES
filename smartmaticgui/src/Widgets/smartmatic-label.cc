/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * custom-label
 * Copyright (C)  2011 <>
 * 
 * custom-label is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * custom-label is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "smartmatic-label.h"
#include <iostream>

using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

SmartmaticLabel::SmartmaticLabel()
:Label()
{
	Initialize();
}

SmartmaticLabel::SmartmaticLabel(const Glib::ustring& label, bool mnemonic)
:Label(label, mnemonic)
{
	Initialize();
}

SmartmaticLabel::SmartmaticLabel(const Glib::ustring& label, float xalign, float yalign, bool mnemonic)
:Label(label, xalign, yalign, mnemonic)
{
	Initialize();
}

SmartmaticLabel::SmartmaticLabel(const Glib::ustring& label, AlignmentEnum xalign, AlignmentEnum yalign, bool mnemonic)
:Label(label, xalign, yalign, mnemonic)
{
	Initialize();
}

SmartmaticLabel::SmartmaticLabel(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
:Glib::ObjectBase("SmartmaticLabel"),
 Gtk::Label(cobject)
{
	Initialize();
}

SmartmaticLabel::~SmartmaticLabel() { }

void SmartmaticLabel::on_size_allocate(Gtk::Allocation& allocation)
{
	if(!isRecursive)
	{
		Label::on_size_allocate(allocation);

		if(customWrapMode)
		{
			set_alignment(0.0, 0.5);
			set_padding(0, 0);

			int width = allocation.get_width();

			Pango::Rectangle rec, dummy;

			Glib::RefPtr<Pango::Layout> layout;

			layout = get_layout();
			layout->get_pixel_extents(dummy, rec);

			if(rec.get_width() <= width)
			{
				set_alignment(0.5, 0.5);
				set_line_wrap(false);
			}
			else
			{
				set_line_wrap(true);
				set_line_wrap_mode(Pango::WRAP_WORD_CHAR);
				set_justify(JUSTIFY_CENTER);

				Pango::Rectangle rec1, dummy1;
				Glib::RefPtr<Pango::Layout> layout1;
				layout1 = get_layout();
				layout1->get_pixel_extents(dummy1, rec1);

				int paddingLabel = (width - rec1.get_width()) / 2;
				if(paddingLabel > 0)
					set_padding(paddingLabel, 0);

				isRecursive = true;
			}
		}
	}
	else
	{
		isRecursive = false;
	}
}

void SmartmaticLabel::SetCustomWrapMode()
{
	customWrapMode = true;
}

void SmartmaticLabel::Initialize()
{
	customWrapMode = false;
	isRecursive = false;
}

void SmartmaticLabel::SetSize(int size)
{
	Pango::FontDescription font = get_style()->get_font();
	font.set_size(size*Pango::SCALE);
	modify_font(font);
}

void SmartmaticLabel::SetBold(bool bold)
{
	Pango::FontDescription font = get_style()->get_font();

	if(bold)
		font.set_weight(Pango::WEIGHT_BOLD);
	else
		font.set_weight(Pango::WEIGHT_NORMAL);

	modify_font(font);
}

void SmartmaticLabel::SetAutoWrap(Label &label, int width, int height)
{
	label.set_size_request(width, height);

	Pango::Rectangle rec, dummy;
	Glib::RefPtr<Pango::Layout> layout;
	layout = label.get_layout();
	layout->get_pixel_extents(dummy, rec);

	if(rec.get_width() < width)
	{
		label.set_alignment(0.5, 0.5);
	}
	else
	{
		label.set_line_wrap(true);
		label.set_justify(JUSTIFY_CENTER);

		Pango::Rectangle rec1, dummy1;
		Glib::RefPtr<Pango::Layout> layout1;
		layout1 = label.get_layout();
		layout1->get_pixel_extents(dummy1, rec1);

		int paddingLabel = (width - rec1.get_width()) / 2;
		label.set_padding(paddingLabel, 0);
	}
}
