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
/**
 * @brief texview with two buttons and Scrolled window
 *
 */

#ifndef _TEXT_VIEW_COMPLEX_H_

/**
 * @brief	Gets the text view complex h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _TEXT_VIEW_COMPLEX_H_

#include <gtkmm.h>
#include "Widgets/smartmatic-button.h"
#include "Widgets/smartmatic-entry.h"
#include "Widgets/SmartmaticTextView.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class TextViewComplex: public Gtk::VBox 
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	titleText			The title text.
				 * @param	acceptButtonText	The accept button text.
				 * @param	backButtonText  	The back button text.
				 * @param	textSpacing			The text spacing.
				 * @param	buttonSpacing   	The button spacing.
				 * @param	buttonsPadding  	The buttons padding.
				 * @param	buttonsHeight   	Height of the buttons.
				 * @param	buttonsWidth		Width of the buttons.
				 * @param	showBack			true to show, false to hide the back.
				 */

				TextViewComplex(Glib::ustring titleText, Glib::ustring acceptButtonText, 
				                Glib::ustring backButtonText, int textSpacing = 30, 
				                int buttonSpacing = 20, int buttonsPadding = 10, 
				                int buttonsHeight = 100, int buttonsWidth = 100,
				                bool showTitle = false, bool showBack = false);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~TextViewComplex();

				/**
				 * @brief	definition of signals.
				 */

				typedef sigc::signal<void, std::string > type_buffer_signal;

				/**
				 * @brief	Defines an alias representing the type void signal. .
				 */

				typedef sigc::signal<void> type_void_signal;

				/**
				 * @brief	method to connect signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_buffer_signal signal_accept_clicked();

				/**
				 * @brief	Raises the back clicked event.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal signal_back_clicked();

				/**
				 * @brief	Clears the buffer.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void ClearBuffer();

				/**
				 * @brief	Gets the buffer.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The buffer.
				 */

				std::string getTextBuffer();

				/**
				 * @brief	Gets the title.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The title.
				 */

				std::string GetTitle();
				
			protected:
	            /**
        		 * declaration of signal handler
	             */
				type_buffer_signal m_accept_clicked;	///< The accept clicked
				type_void_signal m_back_clicked;	///< The back clicked

				/**
				 * @brief	Handles accept button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual void on_acceptButton_clicked();

				/**
				 * @brief	Handles back button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual void on_backButton_clicked();

				Gtk::Label* titleLabel; ///< The title label
				SmartmaticEntry* title; ///< The title
				SmartmaticTextView* textview;	///< The textview
				Gtk::HBox* hboxTitle;   ///< The hbox title
				Gtk::Alignment* buttonAlignment;	///< The button alignment
				SmartmaticButton* acceptButton; ///< The accept button
				SmartmaticButton* backButton;   ///< The back button

			};
		}
	}
}

#endif // _TEXT_VIEW_COMPLEX_H_
