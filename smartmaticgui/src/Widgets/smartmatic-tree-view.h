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

#ifndef _SMARTMATIC_TREE_VIEW_H_

/**
 * @brief	Gets the smartmatic tree view h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_TREE_VIEW_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticTreeView: public Gtk::TreeView 
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmartmaticTreeView();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~SmartmaticTreeView();

				/**
				 * @brief	Deletes the row selected.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void DeleteRowSelected();

				/**
				 * @brief	Query if this object is row selected.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	true if row selected, false if not.
				 */

				bool IsRowSelected();

				/**
				 * @brief	Clean all rows.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void CleanAllRows();
					
				class SmartmaticTreeModel: public Gtk::TreeModelColumnRecord 
				{
				public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					SmartmaticTreeModel()
					{
						add(customCode);
					}
						
					Gtk::TreeModelColumn<std::string> customCode;   ///< The custom code
				};
					
			protected:
				//virtual bool on_button_press_event(GdkEventButton *ev);

				/**
				 * @brief	Selection changed.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual void SelectionChanged() = 0;

				Glib::RefPtr<Gtk::ListStore> refListStore;  ///< The reference list store
				Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;  ///< The reference tree selection
			};
		}
	}
}

#endif // _SMARTMATIC_TREE_VIEW_H_
