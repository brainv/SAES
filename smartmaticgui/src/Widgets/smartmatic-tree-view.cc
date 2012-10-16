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

#include "smartmatic-tree-view.h"
#include <iostream>

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;

SmartmaticTreeView::SmartmaticTreeView()
{
	refTreeSelection = get_selection();
	refTreeSelection->signal_changed().connect(sigc::mem_fun(*this, &SmartmaticTreeView::SelectionChanged));
/*#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
	signal_button_press_event()
			.connect(sigc::mem_fun(*this, &SmartmaticTreeView::on_button_press_event), false);
#endif*/

}

SmartmaticTreeView::~SmartmaticTreeView()
{

}

/*int SmartmaticTreeView::GetRowIDSelected()
{
	return currentIndex;
}*/

/*
bool SmartmaticTreeView::on_button_press_event(GdkEventButton *ev)
{
	bool return_value = false;

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	return_value = TreeView::on_button_press_event(event);
#endif
	
	return return_value;
}
*/

void SmartmaticTreeView::DeleteRowSelected()
{
	TreeModel::iterator iter = refTreeSelection->get_selected();

	if(iter)
	{
		refListStore->erase(iter);
	}
}

bool SmartmaticTreeView::IsRowSelected()
{
	bool returnValue = false;
	
	TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter)
		returnValue = true;

	return returnValue;
}

void SmartmaticTreeView::CleanAllRows()
{
	refListStore->clear();
}
