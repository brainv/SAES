/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	sign-transmission-package-widget.h
 *
 * @brief	Declares the sign transmission package widget class.
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

#ifndef _CLOSE_ELECTION_CONFIRMATION_WIDGET_H_
#define _CLOSE_ELECTION_CONFIRMATION_WIDGET_H_
#include <gtkmm.h>
#include <Widgets/wizard-widget-base.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	CloseElectionConfirmationWidget
				 *
				 * @brief	Confirmation for close election
				 *
				 * @author	Juan.delgado
				 * @date	07/07/2011
				 */

				class CloseElectionConfirmationWidget: public Smartmatic::GUI::Widgets::WizardWidgetBase
				{
				public:

					/**
					 * @fn	CloseElectionConfirmationWidget::CloseElectionConfirmationWidget();
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Juan.delgado
					 * @date	07/07/2011
					 */

					CloseElectionConfirmationWidget();

					/**
					 * @fn	CloseElectionConfirmationWidget::~CloseElectionConfirmationWidget();
					 *
					 * @brief	Destructor
					 *
					 * @author	Juan.delgado
					 * @date	07/07/2011
					 */

					virtual ~CloseElectionConfirmationWidget();
					/**
					 * @brief virtual method init
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void initialize();
					/**
					 * @brief virtual method stop
					 * @date 08/03/2012
					 * @author Yadickson Soto
					 */
					virtual void dispose();

					/**
					 * @fn	Glib::ustring CloseElectionConfirmationWidget::GetWidgetName()
					 *
					 * @brief	Gets the widget name.
					 *
					 * @author	Juan.delgado
					 * @date	07/07/2011
					 *
					 * @return	The widget name.
					 */

					Glib::ustring GetWidgetName() { return ""; };

				private:

					/**
					 * @fn	void CloseElectionConfirmationWidget::on_confirmButton_clicked();
					 *
					 * @brief	Handles confirm button signal.
					 *
					 * @author	Juan.delgado
					 * @date	07/07/2011
					 */
					void on_confirmButton_clicked();

					/**
					 * @fn	void CloseElectionConfirmationWidget::on_cancelButton_clicked();
					 *
					 * @brief	Handles cancel button signal.
					 *
					 * @author	Juan.delgado
					 * @date	07/07/2011
					 */
					void on_cancelButton_clicked();

					Gtk::Label* label;  ///< The label
					Gtk::Image* loadImage;

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}

#endif // _CLOSE_ELECTION_CONFIRMATION_WIDGET_H_
