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

#include "notebook-container.h"

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
using namespace Smartmatic::GUI::Widgets;

NotebookContainer::NotebookContainer()
{
	std::vector<Gtk::Widget*> pageWidgets;
	std::vector<std::string> titlesTabs;

	initialize(pageWidgets, titlesTabs);
}

NotebookContainer::NotebookContainer(std::vector<Gtk::Widget*> & pageWidgets, std::vector<std::string> & titlesTabs)
{
	initialize(pageWidgets, titlesTabs);
}

void NotebookContainer::initialize(std::vector<Gtk::Widget*> & pageWidgets, std::vector<std::string> & titlesTabs)
{
	notebook = NULL;
	pageLabel = NULL;
	notebox = NULL;
	bottomBox = NULL;
	buttonsBox = NULL;
	nextButton = NULL;
	backButton = NULL;

	enableMap = false;

	pageLabelText = _("Smartmatic.GUI.Widgets.NotebookContainer.PlaceHolderPage");

	pageLabel = new Label();

	nextButton = new SmartmaticButton(_("Smartmatic.GUI.Widgets.NotebookContainer.Next"));
	nextButton->signal_clicked().connect(sigc::mem_fun(*this, &NotebookContainer::on_nextButton_clicked));
	nextButton->set_size_request(100, -1);
	nextButton->set_sensitive(false);

	backButton = new SmartmaticButton(_("Smartmatic.GUI.Widgets.NotebookContainer.Back"));
	backButton->signal_clicked().connect(sigc::mem_fun(*this, &NotebookContainer::on_backButton_clicked));
	backButton->set_size_request(100, -1);
	backButton->set_sensitive(false);

	buttonsBox = new HBox();
	buttonsBox->pack_start(*backButton, false, false);
	buttonsBox->pack_start(*pageLabel);
	buttonsBox->pack_end(*nextButton, false, false);
	buttonsBox->set_size_request(-1, 50);

	bottomBox = new HBox();
	bottomBox->pack_start(*buttonsBox);

	notebook = new Notebook();
	notebook->set_show_tabs(false);
	notebook->set_scrollable(true);
	
	vector<Widget*>::iterator iter;
	vector<string>::iterator iterTitle;

	pagesNotShown.clear();

	notebox = new VBox();
	notebox->pack_start(*notebook);
	notebox->pack_start(*bottomBox, false, false);

	int i = 0;

	for(iterTitle = titlesTabs.begin(), iter = pageWidgets.begin(); iter != pageWidgets.end() && iterTitle != titlesTabs.end(); iter++, iterTitle++)
	{
		AppendPage((*iter), *iterTitle);
		pagesNotShown[i] = i;
		i++;
	}

	add(*notebox);
	show_all_children();

	notebook->signal_switch_page().connect(sigc::mem_fun(*this, &NotebookContainer::on_notebook_switch_page) );
}

NotebookContainer::~NotebookContainer()
{
	this->remove();

	if (notebook)
	{
		delete notebook;
		notebook = NULL;
	}
	if (pageLabel)
	{
		delete pageLabel;
		pageLabel = NULL;
	}
	if (notebox)
	{
		delete notebox;
		notebox = NULL;
	}
	if (bottomBox)
	{
		delete bottomBox;
		bottomBox = NULL;
	}
	if (buttonsBox)
	{
		delete buttonsBox;
		buttonsBox = NULL;
	}
	if (nextButton)
	{
		delete nextButton;
		nextButton = NULL;
	}
	if (backButton)
	{
		delete backButton;
		backButton = NULL;
	}

	pageList.clear();
}

void NotebookContainer::EnableMapRefresh()
{
	enableMap = true;
}

void NotebookContainer::RefreshMap()
{
	if(!enableMap)
		return;

	std::map<int, int>::iterator it;

	it = pagesNotShown.find(getCurrentPage());

	if(it != pagesNotShown.end())
	{
		pagesNotShown.erase(it);
	}

	if(pagesNotShown.empty())
	{
		m_pages_viewed.emit();
	}
}

void NotebookContainer::on_notebook_switch_page(GtkNotebookPage* page, guint page_num)
{
	switch_page_connect();
}

void NotebookContainer::switch_page_connect()
{
	nextButton->set_sensitive(getCurrentPage() < getTotalPages() - 1);
	backButton->set_sensitive(getCurrentPage() != 0 && getTotalPages() > 0);

	RefreshMap();
	SetPageLabelText();
}

NotebookContainer::void_signal NotebookContainer::signal_all_pages_viewed()
{
	return m_pages_viewed;
}

void NotebookContainer::SetCurrentPage(int page_num)
{
	if (page_num < 0)
	{
		page_num = 0;
	}

	notebook->set_current_page(page_num);
	switch_page_connect();
}

int NotebookContainer::getCurrentPage()
{
	return notebook->get_current_page();
}

int NotebookContainer::getTotalPages()
{
	return pageList.size();
}

void NotebookContainer::ShowTabs(bool showTabs)
{
	notebook->set_show_tabs(showTabs);
}

void NotebookContainer::on_nextButton_clicked()
{
	notebook->next_page();
	switch_page_connect();
}

void NotebookContainer::on_backButton_clicked()
{
	notebook->prev_page();
	switch_page_connect();
}

void NotebookContainer::AppendPage(Widget* widget, std::string titleTab)
{
	if(titleTab != "")
	{
		notebook->append_page(*widget, titleTab);
	}
	else
	{
		notebook->append_page(*widget);
	}

	pageList.push_back(widget);
	show_all_children();

	switch_page_connect();
}

void NotebookContainer::SetPageLabelText()
{
	if (getTotalPages() > 0)
	{
		string labelText = Glib::ustring::compose(pageLabelText, getCurrentPage() + 1, getTotalPages());
		pageLabel->set_text(labelText);
	}
	else
	{
		pageLabel->set_text(" ");
	}
}

void NotebookContainer::AddBottomWidget(Gtk::Widget* widget)
{
	bottomBox->pack_start(*widget, false, false);
}

Gtk::Widget * NotebookContainer::getCurrentPageWidget()
{
	Gtk::Widget * widget = NULL;

	if (getTotalPages() != 0)
	{
		widget = pageList[getCurrentPage()];
	}

	return widget;
}
