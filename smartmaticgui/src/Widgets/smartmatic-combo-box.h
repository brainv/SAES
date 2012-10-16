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

#ifndef _SMARTMATIC_COMBO_BOX_H_

/**
 * @brief	Gets the smartmatic combo box h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_COMBO_BOX_H_

#include <gtkmm.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticComboBox: public Gtk::ComboBox 
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmartmaticComboBox();

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~SmartmaticComboBox();

				/**
				 * @brief	Sets the options.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	options	Options for controlling the operation.
				 */

				void SetOptions(std::vector<Glib::ustring> &options);

				/**
				 * @brief	Gets the selection.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The selection.
				 */

				Glib::ustring GetSelection();

				/**
				 * @brief	Sets a selection.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	option	The option.
				 */

				void SetSelection(Glib::ustring option);

				/**
				 * @brief	Defines an alias representing the type combo changed. .
				 */

				typedef sigc::signal<void, Glib::ustring> type_combo_changed;

				/**
				 * @brief	Raises the combo changed event.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_combo_changed signal_combo_changed();
				type_combo_changed m_combo_changed; ///< The combo changed
			protected:

				/**
				 * @brief	Handles combo changed signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_combo_changed();


				//Tree model columns:

				/**
				 * @brief	Model columns. 
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				class ModelColumns : public Gtk::TreeModel::ColumnRecord
				{
					public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					ModelColumns()
					{ add(name); }

					Gtk::TreeModelColumn<Glib::ustring> name;   ///< The name
				};

				ModelColumns modelColumns;  ///< The model columns

				Glib::RefPtr<Gtk::ListStore> refTreeModel;  ///< The reference tree model

				Glib::ustring optionName;   ///< Name of the option

			};
		}
	}
}

#endif // _SMARTMATIC_COMBO_BOX_H_
