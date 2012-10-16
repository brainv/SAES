/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	assisted-activation-view-widget.h
 *
 * @brief	Declares the assisted activation view widget class.

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

#ifndef _ASSISTED_ACTIVATION_VIEW_WIDGET_H_
#define _ASSISTED_ACTIVATION_VIEW_WIDGET_H_
#include <gtkmm.h>
#include <Operation/MachineOperationManager.hxx>
#include "Widgets/smartmatic-tree-view.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	AssistedActivationModelColumns
				 *
				 * @brief	Assisted activation model columns. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class AssistedActivationModelColumns : public Gtk::TreeModelColumnRecord
				{
				public:

				  /**
				   * @fn	AssistedActivationModelColumns::AssistedActivationModelColumns()
				   *
				   * @brief	Default constructor.
				   *
				   * @author	Cesar.bonilla
				   * @date	4/28/2011
				   */

				  AssistedActivationModelColumns()
					{ add(m_col_presidentNames); add(m_col_witnessNames); add(m_col_voterNames);}

					Gtk::TreeModelColumn<Glib::ustring> m_col_presidentNames;   ///< List of names of the col presidents
					Gtk::TreeModelColumn<Glib::ustring> m_col_witnessNames; ///< List of names of the col witness
					Gtk::TreeModelColumn<Glib::ustring> m_col_voterNames;   ///< List of names of the col voters
				};

				/**
				 * @class	AssistedActivationTreeView
				 *
				 * @brief	Assisted activation tree view. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class AssistedActivationTreeView:public Smartmatic::GUI::Widgets::SmartmaticTreeView
				{
					public:

						/**
						 * @fn	AssistedActivationTreeView::AssistedActivationTreeView();
						 *
						 * @brief	Default constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						AssistedActivationTreeView();

						/**
						 * @fn	void AssistedActivationTreeView::Initialize();
						 *
						 * @brief	Initializes this object.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/28/2011
						 */

						void Initialize();
					protected:
					private:

					/**
					 * @fn	void AssistedActivationTreeView::SelectionChanged();
					 *
					 * @brief	Selection changed.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void SelectionChanged();
					AssistedActivationModelColumns m_Columns;   ///< The columns
				};

				/**
				 * @class	AssistedActivationViewWidget
				 *
				 * @brief	Assisted activation view widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class AssistedActivationViewWidget: public Gtk::HBox
				{
				public:

					/**
					 * @fn	AssistedActivationViewWidget::AssistedActivationViewWidget();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					AssistedActivationViewWidget();
					//sigc::signal<void,Smartmatic::SAES::Voting::PBReports::Activation> signalOk_detected;
					//sigc::signal<void> signalCancel_detected;

					/**
					 * @fn	void AssistedActivationViewWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void Initialize();

					/**
					 * @fn	void AssistedActivationViewWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void Dispose();

				protected:

				private:
						Gtk::VBox m_VBox;   ///< The v box
    					Gtk::ScrolledWindow m_ScrolledWindow;   ///< The scrolled window
						AssistedActivationTreeView assistedTreeView;	///< The assisted tree view

					

				};
			}
		}
	}
}

#endif // _ASSISTED_ACTIVATION_VIEW_WIDGET_H_
