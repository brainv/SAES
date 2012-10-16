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

#ifndef _POP_UP_MESSAGE_WINDOW_H_

/**
 * @brief	Pops the up message window h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _POP_UP_MESSAGE_WINDOW_H_

#include <gtkmm.h>
#include "basic-window.h"
#include <Configuration/label-configuration.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Windows
		{
			class PopUpMessageWindow: public BasicWindow
			{
			public:

				PopUpMessageWindow(
						Glib::ustring text,
						Smartmatic::GUI::Configuration::LabelConfiguration & labelConf,
						int timerToClose,
						int opacity = 100);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	child	If non-null, the child.
				 * @param	timerToClose 	The timer to close.
				 */

				PopUpMessageWindow(Gtk::Widget* child, int timerToClose);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~PopUpMessageWindow();

				void refreshText(Glib::ustring text);

				void setLabelConfig(Smartmatic::GUI::Configuration::LabelConfiguration & labelConf);

				void setFontColorLabel(Gdk::Color & color);

				void setBoxColorLabel(Gdk::Color & color);
				/**
				 * @brief	Method  show the dialog.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				virtual void ShowDialog();
				/**
				 * @brief	Method quit dialog.
				 * @author	Yadickson Soto
				 * @date	27/04/2011
				 */
				virtual void QuitDialog();

			protected:

				void setContainer(Gtk::Widget* child, int timerToClose);
				bool hideWindow(GdkEventButton* event);

				sigc::connection conn_hide;
				Gtk::EventBox * eventbox;
				Gtk::Label * label;

				/**
				 * @brief	Handles show signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual void on_show();
				/**
				 * @brief method hide window
				 * @return false
				 * @date 30/03/2012
				 * @author Yadickson Soto
				 */
				bool myHide();

			private:

				Gtk::Widget* child; ///< The child
				int timerToClose;   ///< The timer to close
			};
		}
	}
}

#endif // _POP_UP_MESSAGE_WINDOW_H_
