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

#include "pop-up-message-window.h"

using namespace std;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Configuration;

PopUpMessageWindow::PopUpMessageWindow(
		Glib::ustring text,
		LabelConfiguration & labelConf,
		int timerToClose,
		int opacity)
:BasicWindow(false, false, true, Gtk::WINDOW_POPUP)
{
	eventbox = new Gtk::EventBox();
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &PopUpMessageWindow::hideWindow));
	eventbox->show();

	label = new Gtk::Label(text);
	eventbox->add(*label);

	hideTitle();
	hideBottom();

	setLabelConfig(labelConf);

	setContainer(eventbox, timerToClose);
	refreshText(text);
	this->set_opacity(opacity / 100.0);
}

PopUpMessageWindow::PopUpMessageWindow(Gtk::Widget* child, int timerToClose)
:BasicWindow(false, false, true, Gtk::WINDOW_POPUP)
{
	eventbox = NULL;
	label = NULL;
	setContainer(child, timerToClose);
}

PopUpMessageWindow::~PopUpMessageWindow()
{
	conn_hide.disconnect();
	this->remove();

	if (eventbox)
	{
		delete eventbox;
	}

	if (label)
	{
		delete label;
	}

	BasicWindow::dispose();
}

void PopUpMessageWindow::setContainer(Gtk::Widget* child, int timerToClose)
{
	this->child = child;
	this->timerToClose = timerToClose;
	setWidget(child);

}

void PopUpMessageWindow::refreshText(Glib::ustring text)
{
	conn_hide.disconnect();
	label->set_text(text);
	conn_hide = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PopUpMessageWindow::myHide), timerToClose);
}

void PopUpMessageWindow::setLabelConfig(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf)
{
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfiguration(label, labelConf);
}

void PopUpMessageWindow::setFontColorLabel(Gdk::Color & color)
{
	label->modify_fg(Gtk::STATE_NORMAL, color);
}

void PopUpMessageWindow::setBoxColorLabel(Gdk::Color & color)
{
	eventbox->modify_bg(Gtk::STATE_NORMAL, color);
}

void PopUpMessageWindow::on_show()
{
	set_modal(false);
	set_keep_above(true);
	set_can_focus(true);
	conn_hide.disconnect();
	conn_hide = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PopUpMessageWindow::myHide), timerToClose);
	BasicWindow::on_show();
}

bool PopUpMessageWindow::hideWindow(GdkEventButton* event)
{
	conn_hide.disconnect();
	QuitDialog();
	return true;
}

void PopUpMessageWindow::ShowDialog()
{
	this->show();
}

void PopUpMessageWindow::QuitDialog()
{
	hide();
}

bool PopUpMessageWindow::myHide()
{
	QuitDialog();
	return false;
}
