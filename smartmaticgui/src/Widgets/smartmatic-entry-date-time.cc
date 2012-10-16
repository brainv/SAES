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

#include "smartmatic-entry-date-time.h"
#include <iostream>

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

using namespace std;
using namespace Gtk;
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;

SmartmaticEntryDateTime::SmartmaticEntryDateTime(bool complete, int widthEntry, int spacing)
{
	str_year = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Year");
	str_mon = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Month");
	str_day = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Day");
	str_hour = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Hour");
	str_min = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Min");
	str_sec = _("Smartmatic.GUI.Widgets.SmartmaticEntryDateTime.Sec");
	
	Initialize(complete, widthEntry, spacing);	
}

void SmartmaticEntryDateTime::Initialize(bool complete, int widthEntry, int spacing)
{
	int width = widthEntry;
	int height = -1;
	
	entry_year = manage(new SmartmaticEntryNumber(2100,1900));
	entry_year->set_size_request(width * 2, height);
	if(!complete) entry_year->set_no_show_all();
	
	entry_mon = manage(new SmartmaticEntryNumber(12,0));
	entry_mon->set_size_request(width, height);
	if(!complete) entry_mon->set_no_show_all();

	entry_day = manage(new SmartmaticEntryNumber(31,0));
	entry_day->set_size_request(width, height);
	if(!complete) entry_day->set_no_show_all();
	
	entry_hour = manage(new SmartmaticEntryNumber(23,0));
	entry_hour->setMax(2);
	entry_hour->set_size_request(width, height);
	
	entry_min = manage(new SmartmaticEntryNumber(59,0));
	entry_min->setMax(2);
	entry_min->set_size_request(width, height);
	
	entry_sec = manage(new SmartmaticEntryNumber(59,0));
	entry_sec->setMax(2);
	entry_sec->set_size_request(width , height);

	label_year = manage(new Label());
	if(!complete) label_year->set_no_show_all();
	
	label_mon = manage(new Label());
	if(!complete) label_mon->set_no_show_all();
	
	label_day = manage(new Label());
	if(!complete) label_day->set_no_show_all();
	
	label_hour = manage(new Label());
	
	label_min = manage(new Label());
	
	label_sec = manage(new Label());

	SetLabels();

	pack_start(*label_year, false, false);
	pack_start(*entry_year, false, false);
	pack_start(*label_mon, false, false);
	pack_start(*entry_mon, false, false);
	pack_start(*label_day, false, false);
	pack_start(*entry_day, false, false);
	pack_start(*label_hour, false, false);
	pack_start(*entry_hour, false, false);
	pack_start(*label_min, false, false);
	pack_start(*entry_min, false, false);
	pack_start(*label_sec, false, false);
	pack_start(*entry_sec, false, false);
	set_spacing(spacing);
	
	show_all_children();
}

void SmartmaticEntryDateTime::Clear()
{
	entry_year->set_text("");
	entry_mon->set_text("");
	entry_mon->set_text("");
	entry_hour->set_text("");
	entry_min->set_text("");
	entry_sec->set_text("");
}

void SmartmaticEntryDateTime::SetTime(struct tm timeFormat)
{
	entry_year->SetNumber(1900 + timeFormat.tm_year);
	entry_mon->SetNumber(timeFormat.tm_mon);
	entry_mon->SetNumber(timeFormat.tm_mday);
	entry_hour->SetNumber(timeFormat.tm_hour);
	entry_min->SetNumber(timeFormat.tm_min);
	entry_sec->SetNumber(timeFormat.tm_sec);
}

struct tm SmartmaticEntryDateTime::GetTime()
{
	struct tm returnTime;

	entry_sec->GetNumber(returnTime.tm_sec);
	entry_min->GetNumber(returnTime.tm_min);
	entry_hour->GetNumber(returnTime.tm_hour);
	entry_day->GetNumber(returnTime.tm_mday);
	entry_mon->GetNumber(returnTime.tm_mon);
	entry_year->GetNumber(returnTime.tm_year);
	
	return returnTime;
}

void SmartmaticEntryDateTime::SetLabels(ustring str_year, ustring str_mon,
                                        ustring str_day, ustring str_hour,
                                        ustring str_min, ustring str_sec)
{
	this->str_year = str_year;
	this->str_mon = str_mon;
	this->str_day = str_day;
	this->str_hour = str_hour;
	this->str_min = str_min;
	this->str_sec = str_sec;
}

void SmartmaticEntryDateTime::SetLabels()
{
	label_year->set_text(str_year);
	label_mon->set_text(str_mon);
	label_day->set_text(str_day);
	label_hour->set_text(str_hour);
	label_min->set_text(str_min);
	label_sec->set_text(str_sec);
}

void SmartmaticEntryDateTime::SetSensitive(bool isSensitive)
{
	entry_year->set_sensitive(isSensitive);
	entry_mon->set_sensitive(isSensitive);
	entry_day->set_sensitive(isSensitive);
	entry_hour->set_sensitive(isSensitive);
	entry_min->set_sensitive(isSensitive);
	entry_sec->set_sensitive(isSensitive);

	entry_year->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entry_mon->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entry_day->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entry_hour->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entry_min->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
	entry_sec->modify_text(Gtk::STATE_INSENSITIVE,Gdk::Color("black"));
}
