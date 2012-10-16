/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * trunk
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	LogTreeViewWidget.h
 *
 * @brief	Declares the log tree view widget class.
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

#ifndef _LOGTREEVIEWWIDGET_H_
#define _LOGTREEVIEWWIDGET_H_

#include <Widgets/smartmatic-tree-view.h>
#include <Log/LogLine.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	LogTreeViewWidget
				 *
				 * @brief	Log tree view widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class LogTreeViewWidget: public Smartmatic::GUI::Widgets::SmartmaticTreeView 
				{
					public:

						/**
						 * @fn	LogTreeViewWidget::LogTreeViewWidget();
						 *
						 * @brief	Default constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						LogTreeViewWidget();

						/**
						 * @fn	LogTreeViewWidget::~LogTreeViewWidget();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						~LogTreeViewWidget();

						/**
						 * @fn	void LogTreeViewWidget::AddRow(Smartmatic::SAES::Log::LogLine logLine);
						 *
						 * @brief	Adds a row. 
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	logLine	The log line.
						 */

						void AddRow(Smartmatic::SAES::Log::LogLine logLine);

						/**
						 * @fn	void LogTreeViewWidget::GetRow(std::string customCode,
						 * 		Smartmatic::SAES::Log::LogLine & logLine);
						 *
						 * @brief	Gets a row.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	customCode	   	The custom code.
						 * @param [in,out]	logLine	The log line.
						 */

						void GetRow(std::string customCode, Smartmatic::SAES::Log::LogLine & logLine);

						/**
						 * @fn	void LogTreeViewWidget::ModifyRow(Smartmatic::SAES::Log::LogLine logLine);
						 *
						 * @brief	Modify row.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	logLine	The log line.
						 */

						void ModifyRow(Smartmatic::SAES::Log::LogLine logLine);

						/**
						 * @fn	void LogTreeViewWidget::DeleteRowSelected();
						 *
						 * @brief	Deletes the row selected.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void DeleteRowSelected();

						/**
						 * @fn	bool LogTreeViewWidget::IsRowSelected();
						 *
						 * @brief	Query if this object is row selected.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if row selected, false if not.
						 */

						bool IsRowSelected();

						/**
						 * @fn	std::string LogTreeViewWidget::GetCodeSelected();
						 *
						 * @brief	Gets the code selected.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The code selected.
						 */

						std::string GetCodeSelected();

						/**
						 * @fn	static std::vector<Glib::ustring> LogTreeViewWidget::GetVectorStringFromEnum();
						 *
						 * @brief	Gets the vector string from enum.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	The vector string from enum.
						 */

						static std::vector<Glib::ustring> GetVectorStringFromEnum();

					protected:

						/**
						 * @fn	void LogTreeViewWidget::SelectionChanged();
						 *
						 * @brief	Selection changed.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						void SelectionChanged();

					/**
					 * @class	LogLineTreeModel
					 *
					 * @brief	Log line tree model. 
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					class LogLineTreeModel :

						/**
						 * @property	public Smartmatic::GUI::Widgets::SmartmaticTreeView::SmartmaticTreeModel
						 *
						 * @brief	Gets the smartmatic tree model.
						 *
						 * @value	.
						 */

						public Smartmatic::GUI::Widgets::SmartmaticTreeView::SmartmaticTreeModel
					{
						public:

							/**
							 * @fn	LogLineTreeModel::LogLineTreeModel()
							 *
							 * @brief	Default constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 */

							LogLineTreeModel()
						{
							/**
							 * @fn	LogLineTreeModel::add(date);
							 *
							 * @brief	Constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 *
							 * @param		The date to add.
							 */

							add(date); 

							/**
							 * @fn	LogLineTreeModel::add(library);
							 *
							 * @brief	Constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 *
							 * @param		The library to add.
							 */

							add(library); 

							/**
							 * @fn	LogLineTreeModel::add(message);
							 *
							 * @brief	Constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 *
							 * @param		The message to add.
							 */

							add(message);

							/**
							 * @fn	LogLineTreeModel::add(level);
							 *
							 * @brief	Constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 *
							 * @param		The level to add.
							 */

							add(level); 

							/**
							 * @fn	LogLineTreeModel::add(sinceStart);
							 *
							 * @brief	Constructor.
							 *
							 * @author	Cesar.bonilla
							 * @date	4/29/2011
							 *
							 * @param		The sinceStart to add.
							 */

							add(sinceStart);
						}

							Gtk::TreeModelColumn<Glib::ustring> date;   ///< The date
							Gtk::TreeModelColumn<Glib::ustring> library;	///< The library
							Gtk::TreeModelColumn<Glib::ustring> message;	///< The message
							Gtk::TreeModelColumn<Glib::ustring> level;  ///< The level
							Gtk::TreeModelColumn<Glib::ustring> sinceStart; ///< The since start
					};

					private:
						LogLineTreeModel logLineTreeModel;  ///< The log line tree model
						std::string currentCustomCode;  ///< The current custom code
				};
			}
		}
	}
}

#endif // _LOGTREEVIEWWIDGET_H_
