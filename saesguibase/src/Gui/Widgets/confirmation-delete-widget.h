/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	id-card-widget-close-election.h
 *
 * @brief	Declares the identifier card widget close election class.
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

#ifndef _CONFIRMATION_DELETE_WIDGET_H_
#define _CONFIRMATION_DELETE_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class ConfirmationDeleteWidget : public Gtk::Frame
				{
				public:
					ConfirmationDeleteWidget();

					~ConfirmationDeleteWidget();
					
					typedef sigc::signal<void, bool> type_bool_signal;

					type_bool_signal on_answer_emit();

				protected:
					type_bool_signal m_answer_signal; ///< The done signal
					Gtk::Label* label; ///< label message
					Gtk::HButtonBox* btnBox;
					Gtk::VBox* vbox;
					Gtk::Alignment* align;
					Smartmatic::GUI::Widgets::SmartmaticButton* deleteButton; ///< delete button
					Smartmatic::GUI::Widgets::SmartmaticButton* backButton; ///< back button

					void on_deleteButton_clicked();

					void on_backButton_clicked();

				private:

				};
			}
		}
	}
}



#endif // _CONFIRMATION_DELETE_WIDGET_H_
