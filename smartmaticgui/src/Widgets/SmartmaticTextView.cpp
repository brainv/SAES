/*
 * SmartmaticTextView.cpp
 *
 *  Created on: Jul 23, 2011
 *      Author: Juan.Delgado
 */

#include "SmartmaticTextView.h"
#include <gdk/gdkkeysyms.h>

using namespace Smartmatic::GUI::Widgets;

SmartmaticTextView::SmartmaticTextView()
: Gtk::ScrolledWindow(),
  ISmartmaticText()
{
	initialize();
}

SmartmaticTextView::SmartmaticTextView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
:Glib::ObjectBase("SmartmaticTextView"),
 Gtk::ScrolledWindow(cobject),
 ISmartmaticText()
{
	initialize();
}

SmartmaticTextView::~SmartmaticTextView()
{
	remove();

	if (textView)
	{
		delete textView;
		textView = NULL;
	}
}

void SmartmaticTextView::initialize()
{
	textBuffer = Gtk::TextBuffer::create();
	textBuffer->signal_insert().connect(sigc::mem_fun(*this, &SmartmaticTextView::insertText));
	textBuffer->signal_erase().connect(sigc::mem_fun(*this, &SmartmaticTextView::deleteText));
	textBuffer->signal_changed().connect(sigc::mem_fun(*this, &SmartmaticTextView::changeText));

	textView = new Gtk::TextView();
	textView->set_buffer(textBuffer);
	textView->set_wrap_mode(Gtk::WRAP_WORD);
	textView->signal_button_press_event().connect(sigc::mem_fun(this, &SmartmaticTextView::on_button_press_event));
	textView->signal_key_press_event().connect(sigc::mem_fun(this, &SmartmaticTextView::on_key_press_event));

	set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	set_shadow_type(Gtk::SHADOW_IN);

	remove();
	add(*textView);
	show_all_children();
}

bool SmartmaticTextView::on_button_press_event(GdkEventButton* event)
{
	return event->button != 3;
}

bool SmartmaticTextView::on_key_press_event(GdkEventKey* event)
{
	bool result = false;

#ifdef GDK_KEY_Menu
	if (event->keyval != GDK_KEY_Menu)
	{
		result = true;
	}
#else
	if (event->keyval != 0xff67)
	{
		result = true;
	}
#endif

	return result;
}

void SmartmaticTextView::setText(std::string text)
{
	textView->set_name("");
	textBuffer->set_text(text);
}

std::string SmartmaticTextView::getText()
{
	return (std::string)textBuffer->get_text();
}

void SmartmaticTextView::setBGError()
{
	textView->set_name("entry_error_frame");
}

void SmartmaticTextView::setBGNormal()
{
	textView->set_name("");
}

void SmartmaticTextView::insertText(const Gtk::TextBuffer::iterator& a, const Glib::ustring& b, int c)
{
	if (max != -1 && getText().size() > (unsigned int)max)
	{
		setText(getText().substr(0, max));
		return;
	}

	setBGNormal();
	validate();
}

void SmartmaticTextView::deleteText(const Gtk::TextBuffer::iterator& a, const Gtk::TextBuffer::iterator& b)
{
	setBGNormal();
	validate();
}

void SmartmaticTextView::changeText()
{
	setBGNormal();
	validate();
}
