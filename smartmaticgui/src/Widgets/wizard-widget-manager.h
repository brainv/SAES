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

#ifndef _WIZARD_WIDGET_MANAGER_H_

/**
 * @brief	Gets the wizard widget manager h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _WIZARD_WIDGET_MANAGER_H_

#include <gtkmm.h>
#include "wizard-widget-base.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardWidgetManager: public Gtk::Frame 
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	widgetsVector	If non-null, the widgets vector.
				 */

				WizardWidgetManager(std::vector<WizardWidgetBase*> widgetsVector);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~WizardWidgetManager();

				void Start();

				/**
				 * @brief	Defines an alias representing the type void signal. .
				 */

				typedef sigc::signal<void> type_void_signal;

				/**
				 * @brief	Executes the finish signal emit action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_finish_signal_emit();

				/**
				 * @brief	Executes the transition signal emit action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_transition_signal_emit();

				/**
				 * @brief Method getter current widget
				 * @return current widget
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				WizardWidgetBase * getCurrentWidget();

			protected:
				type_void_signal m_finish_signal; ///< The finish signal
				type_void_signal m_transition_signal; ///< The finish signal

				sigc::connection widgetConnect; ///< The widget connect
				
				std::vector<WizardWidgetBase*> widgetsVector;   ///< The widgets vector
				std::vector<WizardWidgetBase*>::iterator iter;  ///< The iterator

			private:

				/**
				 * @brief	Shows the widget.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void ShowWidget();

				/**
				 * @brief	Next widget.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void NextWidget();

				/**
				 * @brief	Initializes the widget.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void InitializeWidget();

				/**
				 * @brief Method process next widget
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				void NextWidgetInternal();

			};
		}
	}
}

#endif // _WIZARD_WIDGET_MANAGER_H_
