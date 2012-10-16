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

#ifndef _WIZARD_WIDGET_BASE_H_

/**
 * @brief	Gets the wizard widget base h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _WIZARD_WIDGET_BASE_H_

#include <gtkmm.h>
#include "StepWidget.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class WizardWidgetBase: public Smartmatic::GUI::Widgets::StepWidget
			{
			public:

				/**
				 * @brief Class constructor
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				WizardWidgetBase();

				/**
				 * @brief Class destroy
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				virtual ~WizardWidgetBase();

				/**
				 * @brief	return the widgets name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The widget name.
				 */

				virtual Glib::ustring GetWidgetName() = 0;

				/**
				 * @brief	signal emitted when widget is done.
				 * 			
				 * 			author	Luiggi.mendez. date	27/04/2011.
				 */

				typedef sigc::signal<void> type_done_signal;

				/**
				 * @brief	method to connect signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	<void> type_done_signal.
				 */

				type_done_signal on_done_signal_emit();

				/**
				 * @brief	Executes the stop signal emit action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_done_signal on_stop_signal_emit();

				/**
				 * @brief	Executes the disable close signal emit action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_done_signal on_disable_close_signal_emit();

				/**
				 * @brief Method getter is stop wizard
				 * @return true is stop wizard
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				virtual bool StopWizard();

				/**
				 * @brief Method getter is enabled button exit wizard
				 * @return true is enabled button exit wizard
				 * @date 22/02/2012
				 * @author Yadickson Soto
				 */
				virtual bool isEnabledButtonExitWizard();

			protected:

				type_done_signal m_done_signal; ///< The done signal

				type_done_signal m_stop_signal; ///< The stop signal

				type_done_signal m_disable_close_signal; ///< The stop signal
			};
		}
	}
}

#endif // _WIZARD_WIDGET_BASE_H_
