/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	combo-box-choose-widget.h
 *
 * @brief	Declares the combo box choose widget class.
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COMBO_BOX_CHOOSE_WIDGET_H_
#define _COMBO_BOX_CHOOSE_WIDGET_H_
#include <gtkmm.h>
#include <iostream>
#include "Widgets/choose-dialog-button-info.h"
#include "Widgets/choose-dialog-info.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				//Tree model columns:

				/**
				 * @class	ModelColumns
				 *
				 * @brief	Model columns. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ModelColumns : public Gtk::TreeModel::ColumnRecord
				{
				public:

					/**
					 * @fn	ModelColumns::ModelColumns()
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					ModelColumns()
					{
						add(m_col_name);
					}
					 Gtk::TreeModelColumn<Glib::ustring> m_col_name;	///< Name of the col
				};

				/**
				 * @class	ComboBoxChooseWidget
				 *
				 * @brief	Combo box choose widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ComboBoxChooseWidget : public Gtk::HBox
				{
				public:

				/**
				 * @fn	ComboBoxChooseWidget::ComboBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo* dialogInfo);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	dialogInfo	If non-null, information describing the dialog.
				 */

				ComboBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo* dialogInfo);

				/**
				 * @fn	ComboBoxChooseWidget::~ComboBoxChooseWidget();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				~ComboBoxChooseWidget();

				/**
				 * @fn	std::string ComboBoxChooseWidget::getOptionValue();
				 *
				 * @brief	Gets the option value.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	The option value.
				 */

				std::string getOptionValue();

				/**
				 * @fn	std::string ComboBoxChooseWidget::getOptionName();
				 *
				 * @brief	Gets the option name.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	The option name.
				 */

				std::string getOptionName();

				/**
				 * @fn	void ComboBoxChooseWidget::ResizeOptionsWidgets(int WidgetOptionsWidth,
				 * 		int WidgetOptionsHeight);
				 *
				 * @brief	Resize options widgets.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	WidgetOptionsWidth 	Width of the widget options.
				 * @param	WidgetOptionsHeight	Height of the widget options.
				 */

				void ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight);

				/**
				 * @fn	void ComboBoxChooseWidget::Dispose();
				 *
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void Dispose();
				protected:

				private:	
				sigc::connection connCombo; ///< The connection combo
				ModelColumns choicesColumnModel;	///< The choices column model
				Glib::RefPtr<Gtk::ListStore> m_refTreeModel;	///< The reference tree model

				/**
				 * @fn	void ComboBoxChooseWidget::on_combo_changed();
				 *
				 * @brief	Handles combo changed signals.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void on_combo_changed();
				Glib::ustring optionSelected;   ///< The option selected
				Gtk::ComboBox comboChoices; ///< The combo choices
				Gtk::Label labelTitle;  ///< The label title
				Gtk::Image imageTitle;  ///< The image title
				int currentIndex;   ///< The current index

				};
			}
		}
	}
}

#endif // _COMBO_BOX_CHOOSE_WIDGET_H_
