/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * trunk
 * Copyright (C)  2011 <>
 * 
 * trunk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * trunk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogTreeViewWidget.h"
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
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Log;


LogTreeViewWidget::LogTreeViewWidget()
{
	string sDate = _("Smartmatic.SAES.GUI.Widgets.LogTreeViewWidget.Date");
	string sLibrary = _("Smartmatic.SAES.GUI.Widgets.LogTreeViewWidget.Library");
	string sMessage = _("Smartmatic.SAES.GUI.Widgets.LogTreeViewWidget.Message");
	string sLevel = _("Smartmatic.SAES.GUI.Widgets.LogTreeViewWidget.Level");
	string sSinceStart = _("Smartmatic.SAES.GUI.Widgets.LogTreeViewWidget.SinceStart");
	
	
	currentCustomCode = "";
	refListStore = ListStore::create(logLineTreeModel);

	set_model(refListStore);

	TreeViewColumn* column = manage(new TreeViewColumn(sDate, logLineTreeModel.date));
	column->set_resizable(false);
	column->set_min_width(200);
	column->set_max_width(200);
	column->set_alignment(0.5);
	column->set_visible(true);
	append_column(*column);

	column = manage(new TreeViewColumn(sLibrary, logLineTreeModel.library));
	column->set_resizable(false);
	column->set_min_width(100);
	column->set_max_width(100);
	column->set_alignment(0.5);
	column->set_visible(false);
	append_column(*column);

	column = manage(new TreeViewColumn(sMessage, logLineTreeModel.message));
	column->set_resizable(false);
	column->set_min_width(500);
	column->set_max_width(500);
	column->set_alignment(0.5);
	column->set_visible(true);
	append_column(*column);

	column = manage(new TreeViewColumn(sLevel, logLineTreeModel.level));
	column->set_resizable(false);
	column->set_min_width(100);
	column->set_max_width(100);
	column->set_alignment(0.5);
	column->set_visible(false);
	append_column(*column);

	column = manage(new TreeViewColumn(sSinceStart, logLineTreeModel.sinceStart));
	column->set_resizable(false);
	column->set_min_width(100);
	column->set_max_width(100);
	column->set_alignment(0.5);
	column->set_visible(false);
	append_column(*column);
	//set_size_request (800,380);
}

LogTreeViewWidget::~LogTreeViewWidget()
{

}

void LogTreeViewWidget::AddRow(LogLine logLine)
{
	TreeModel::Row row;
	row = *(refListStore->append());
	row[logLineTreeModel.date] = logLine.getDate();
	row[logLineTreeModel.library] = logLine.getLibrary();
	row[logLineTreeModel.message] = logLine.getMessage();
	row[logLineTreeModel.level] = "Level";
	row[logLineTreeModel.sinceStart] = "1234";
}


bool LogTreeViewWidget::IsRowSelected()
{
	return currentCustomCode == "" ? false : true;
}

void LogTreeViewWidget::GetRow(string customCode, LogLine  &logLine)
{

}

void LogTreeViewWidget::SelectionChanged()
{

}

string LogTreeViewWidget::GetCodeSelected()
{
	return currentCustomCode;
}

void LogTreeViewWidget::DeleteRowSelected()
{
	TreeModel::iterator iter = refTreeSelection->get_selected();

	if(iter)
	{
		refListStore->erase(iter);
	}
}
