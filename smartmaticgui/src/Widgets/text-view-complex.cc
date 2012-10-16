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

#include "text-view-complex.h"

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

TextViewComplex::TextViewComplex(Glib::ustring titleText, Glib::ustring acceptButtonText,
                                 Glib::ustring backButtonText,
                                 int textSpacing,int buttonSpacing, 
                                 int buttonsPadding, int buttonsHeight,
                                 int buttonsWidth, bool showTitle,
                                 bool showBack)
{
	titleLabel = manage(new Label(titleText));
	Pango::FontDescription fontTitle = titleLabel->get_style()->get_font();
	fontTitle.set_size(14*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	titleLabel->modify_font(fontTitle);


	title = manage(new SmartmaticEntry());

	if(!showTitle)
	{
		titleLabel->set_no_show_all();
		titleLabel->hide();

		title->set_no_show_all();
		title->hide();
	}

	hboxTitle = manage(new HBox(false, 20));
	hboxTitle->pack_start(*titleLabel, false, false);
	hboxTitle->pack_start(*title);
	
	textview = manage(new SmartmaticTextView());
	acceptButton = manage(new SmartmaticButton(acceptButtonText));
	acceptButton->signal_clicked().connect(sigc::mem_fun(this, &TextViewComplex::on_acceptButton_clicked));
	acceptButton->set_size_request(buttonsWidth, -1);
	
	backButton = manage(new SmartmaticButton(backButtonText));
	backButton->signal_clicked().connect(sigc::mem_fun(this, &TextViewComplex::on_backButton_clicked));
	backButton->set_size_request(buttonsWidth, -1);
	if(!showBack)
		backButton->set_no_show_all();

	HBox* hbox = manage(new HBox(true, buttonSpacing));
	hbox->pack_start(*backButton,false,false);
	hbox->pack_start(*acceptButton,false,false);
	hbox->set_size_request(-1, buttonsHeight);

	buttonAlignment = manage(new Alignment());
	buttonAlignment->set_padding(0,0, buttonsPadding, buttonsPadding);
	buttonAlignment->add(*hbox);

	set_spacing(textSpacing);
	pack_start(*hboxTitle, false, false);
	pack_start(*textview);
	pack_start(*buttonAlignment, false, false);

}

TextViewComplex::~TextViewComplex()
{

}

string TextViewComplex::GetTitle()
{
	return title->get_text();
}

void TextViewComplex::on_acceptButton_clicked()
{
	m_accept_clicked.emit(textview->getText());
}

void TextViewComplex::on_backButton_clicked()
{
	m_back_clicked.emit();
}

TextViewComplex::type_buffer_signal TextViewComplex::signal_accept_clicked()
{
	return m_accept_clicked;
}

TextViewComplex::type_void_signal TextViewComplex::signal_back_clicked()
{
	return m_back_clicked;
}

void TextViewComplex::ClearBuffer()
{
	textview->setText("");
	titleLabel->set_text("");	
}

std::string TextViewComplex::getTextBuffer()
{
	return textview->getText();
}


