/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saescommon
 * Copyright (C)  2011 <>
 * 
 * saescommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saescommon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PrinterTwoColumnsElement.h"

using namespace std;
using namespace Smartmatic::SAES::Printing;

double PrinterTwoColumnsElement::get_length (
		    const Glib::RefPtr<Gtk::PrintContext>& context)
{
	Pango::Rectangle extents1;
	Pango::Rectangle extents2;
	
	_textLayoutFirstColum = context->create_pango_layout ();
	_textLayoutFirstColum->set_width (static_cast<int>((context->get_width ()-_hPadding) * Pango::SCALE/2));

	_textLayoutSecondColum = context->create_pango_layout ();
	_textLayoutSecondColum->set_width (static_cast<int>((context->get_width ()-_hPadding) * Pango::SCALE/2));
	
	setLayoutSettings ();

	extents1 = _textLayoutFirstColum->get_logical_extents ();
	extents2 = _textLayoutSecondColum->get_logical_extents ();


	if(extents1.get_height () > extents2.get_height ())
		return extents1.get_height () / Pango::SCALE;
	else
		return extents2.get_height () / Pango::SCALE;
}


void PrinterTwoColumnsElement::render_element (
    const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context ();
	
	double cursor_x, cursor_y;

	this->_height = get_length (print_context);

	cairo_ctx->set_source_rgb (0,0,0);
	cairo_ctx->get_current_point (cursor_x, cursor_y);

	cursor_x+=_hPadding;
	cairo_ctx->move_to (cursor_x, cursor_y);
	
	_textLayoutFirstColum->show_in_cairo_context (cairo_ctx);

	
	cairo_ctx->move_to (cursor_x + (_textLayoutFirstColum->get_width()/Pango::SCALE), cursor_y);
	_textLayoutSecondColum->show_in_cairo_context (cairo_ctx);
	cairo_ctx->get_current_point (cursor_x, cursor_y);

	cairo_ctx->move_to (0, cursor_y + this->_height);
}

void PrinterTwoColumnsElement::setLayoutSettings ()
{
	Pango::FontDescription fontDesc (_fontFamily);
	Pango::Alignment alignment;
	
	switch (pe_alignment)
	{
		case Gtk::ALIGN_LEFT:
			alignment = Pango::ALIGN_LEFT;
			break;
		case Gtk::ALIGN_CENTER:
			alignment = Pango::ALIGN_CENTER;
			break;
		case Gtk::ALIGN_RIGHT:
			alignment = Pango::ALIGN_RIGHT;
			break;
		default:
			alignment = Pango::ALIGN_LEFT;
			break;
	}

	fontDesc.set_stretch (this->_stretch);
	fontDesc.set_weight  (this->_weight);
	fontDesc.set_style   (this->_style);
	fontDesc.set_variant (this->_variant);
	if(_spacing>-1)
	{
		_textLayoutFirstColum->set_spacing(_spacing*1024);
	}
	_textLayoutFirstColum->set_font_description (fontDesc);
	_textLayoutFirstColum->set_alignment (alignment);
	_textLayoutFirstColum->set_justify (false);
	_textLayoutFirstColum->set_text (_contentFirstColumn);
	_textLayoutFirstColum->set_wrap (this->_wrap);


	_textLayoutSecondColum->set_font_description (fontDesc);
	_textLayoutSecondColum->set_alignment (alignment);
	_textLayoutSecondColum->set_justify (false);
	_textLayoutSecondColum->set_text (_contentSecondColumn);
	_textLayoutSecondColum->set_wrap (this->_wrap);
}

void PrinterTwoColumnsElement::setFontSize(int fontSize)
{
	stringstream s;
	s << _fontFamilyNoSize <<" "<< _fontSize;
	_fontFamily = s.str ();
	_fontSize = fontSize;
}

const int PrinterTwoColumnsElement::getFontSize(){return _fontSize;}

void PrinterTwoColumnsElement::setHPadding(const int hPadding){_hPadding = hPadding;}
const int PrinterTwoColumnsElement::getHPadding(){return _hPadding;}

void PrinterTwoColumnsElement::setSpacing(const int spacing){_spacing = spacing;}
const int PrinterTwoColumnsElement::getSpacing(){return _spacing;}

void PrinterTwoColumnsElement::setAlignment(Gtk::AlignmentEnum alignment){pe_alignment = alignment; }
Gtk::AlignmentEnum PrinterTwoColumnsElement::getAlignment(){return pe_alignment;}


void PrinterTwoColumnsElement::setFontFamily (const Glib::ustring& fontFamily)
{
	_fontFamilyNoSize = fontFamily;
	stringstream s;
	s << _fontFamilyNoSize << " " << getFontSize();
	this->_fontFamily = s.str();
}
