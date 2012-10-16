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

#include "activator-card-counter-widget.h"
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

using namespace Gtk;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Resources;


ActivatorCardCounterWidget::ActivatorCardCounterWidget(std::string title, std::string value, std::string counter)
{
	this->code = code;
	this->value = value;
	
	std::string codeFormatted = title;
	std::string valueFormatted = value;

	set_spacing(3);

	codeFormatted.append(":");

	Pango::FontDescription fontCode = labelCode.get_style()->get_font();
	fontCode.set_size(10*Pango::SCALE);
	fontCode.set_weight(Pango::WEIGHT_BOLD);
	labelCode.modify_font(fontCode);	

	Pango::FontDescription fontValue = labelCode.get_style()->get_font();
	fontValue.set_size(10*Pango::SCALE);
	fontValue.set_weight(Pango::WEIGHT_NORMAL);
	fontValue.set_style (Pango::STYLE_ITALIC);
	labelValue.modify_font(fontValue);
	
	labelCode.set_label(codeFormatted);
	labelValue.set_label(valueFormatted);
	labelCounter.set_label(counter);
	pack_start(labelCode,Gtk::PACK_SHRINK); 
	pack_start(labelValue,Gtk::PACK_SHRINK); 
	pack_start(labelCounter,Gtk::PACK_SHRINK); 
	
	show_all_children ();
	set_visible (true);
}

ActivatorCardCounterWidget::~ActivatorCardCounterWidget()
{

}

void ActivatorCardCounterWidget::ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight)
{

}




std::string ActivatorCardCounterWidget::getCode()
{
	return code;
}

std::string ActivatorCardCounterWidget::getValue()
{
	return value;
}


void ActivatorCardCounterWidget::Dispose()
{

}
