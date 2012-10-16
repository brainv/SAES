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

#include "smartmatic-combo-box.h"

using namespace std;
using namespace Gtk;
using namespace Glib;
using namespace Smartmatic::GUI::Widgets;

SmartmaticComboBox::SmartmaticComboBox()
{
	//Create the Tree model:
	refTreeModel = Gtk::ListStore::create(modelColumns);
	set_model(refTreeModel);

	signal_changed().connect(sigc::mem_fun(*this, &SmartmaticComboBox::on_combo_changed));

}

SmartmaticComboBox::~SmartmaticComboBox()
{
	
}

void SmartmaticComboBox::SetOptions(vector<ustring> &options)
{
	vector<ustring>::iterator it;
	clear();
	refTreeModel->clear();

	for(it = options.begin(); it != options.end(); it++)
	{
		//Fill the ComboBox's Tree Model:
		TreeModel::Row row = *(refTreeModel->append());
		row[modelColumns.name] = *it;

	}

	//Add the model columns to the Combo
	//pack_start(modelColumns.id);
	pack_start(modelColumns.name);

}

void SmartmaticComboBox::on_combo_changed()
{
	TreeModel::iterator iter = get_active();
	if(iter)
	{
		TreeModel::Row row = *iter;
		if(row)
		{
			Glib::ustring name = row[modelColumns.name];
			optionName = name;
			m_combo_changed.emit(name);
		}
	}
	//TODO else throw exception
}

SmartmaticComboBox::type_combo_changed SmartmaticComboBox::signal_combo_changed()
{
	return m_combo_changed;
}

Glib::ustring SmartmaticComboBox::GetSelection()
{
	return optionName;
}

void SmartmaticComboBox::SetSelection(ustring option)
{
	int index = 0;
	TreeModel::Children child = refTreeModel->children();
	
	TreeModel::Children::iterator iter;
	for(iter = child.begin(); iter != child.end(); iter++)
	{
		TreeModel::Row row = *iter;
		ustring name = row[modelColumns.name];

		if(name == option)
			set_active(index);
		index++;
	}
}

