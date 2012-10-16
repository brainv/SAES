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

#ifndef _NOTEBOOK_CONTAINER_H_
#define _NOTEBOOK_CONTAINER_H_

#include <gtkmm.h>
#include "smartmatic-button.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class NotebookContainer: public Gtk::EventBox
			{
			public:

				/**
				 * @brief class constructor
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				NotebookContainer();
				NotebookContainer(std::vector<Gtk::Widget*> & pageWidgets, std::vector<std::string> & titlesTabs);
				~NotebookContainer();
				
				void ShowTabs(bool showTabs);
				void AppendPage(Gtk::Widget* widget, std::string titleTab = "");
				void SetCurrentPage(int page_num);

				/**
				 * @brief Method getter current page
				 * @return current page
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				int getCurrentPage();
				/**
				 * @brief Method getter total pages
				 * @return total pages
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				int getTotalPages();

				void AddBottomWidget(Gtk::Widget* widget);

				typedef sigc::signal<void> void_signal;

				void_signal signal_all_pages_viewed();

				void EnableMapRefresh();

				/**
				 * @brief Method getter current page widget
				 * @return current page widget
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				Gtk::Widget * getCurrentPageWidget();

			protected:
				/**
				 * @brief initialize
				 * @param pageWidgets widgets
				 * @param titlesTabs titles
				 * @date 18/05/2012
				 * @author Yadickson Soto
				 */
				void initialize(std::vector<Gtk::Widget*> & pageWidgets, std::vector<std::string> & titlesTabs);

				void on_nextButton_clicked();
				void on_backButton_clicked();
				void on_notebook_switch_page(GtkNotebookPage* page, guint page_num);

				void_signal m_pages_viewed;   ///< The pages viewed signal

				void switch_page_connect();

			private:

				Gtk::Notebook* notebook;
				Gtk::Label* pageLabel;
				Gtk::VBox* notebox;
				Gtk::HBox* bottomBox;
				Gtk::HBox* buttonsBox;
				Smartmatic::GUI::Widgets::SmartmaticButton* nextButton;
				Smartmatic::GUI::Widgets::SmartmaticButton* backButton;
				std::vector<Gtk::Widget*> pageList;

				void SetPageLabelText();

				void RefreshMap();

				std::string pageLabelText;

				std::map<int, int> pagesNotShown;
				bool enableMap;
			};
		}
	}
}

#endif // _NOTEBOOK_CONTAINER_H_
