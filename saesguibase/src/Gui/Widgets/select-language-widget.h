/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	select-language-widget.h
 *
 * @brief	Declares the select language widget class.
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

#ifndef _SELECT_LANGUAGE_WIDGET_H_
#define _SELECT_LANGUAGE_WIDGET_H_

#include "Gui/Widgets/basic-diagnostic-widget.h"
#include <gtkmm.h>
#include <iostream>
#include "Voting/operation-status.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	SelectLanguageWidget
				 *
				 * @brief	Select language widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class SelectLanguageWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	SelectLanguageWidget::SelectLanguageWidget()
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					SelectLanguageWidget()
					{
					}

					/**
					 * @fn	SelectLanguageWidget::~SelectLanguageWidget()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~SelectLanguageWidget()
					{
						
					}

					/**
					 * @fn	void SelectLanguageWidget::Dispose();
					 *
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Dispose();

					/**
					 * @fn	void SelectLanguageWidget::Initialize();
					 *
					 * @brief	Initializes this object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void Initialize();
				protected:

				private:

					
					Gtk::Frame* framePrincipal; ///< The frame principal
					//Gtk::HBox* bottomBox;
					Gtk::HButtonBox* buttonBox; ///< The button box
					Smartmatic::GUI::Widgets::SmartmaticButton* button1;	///< The first button
					Smartmatic::GUI::Widgets::SmartmaticButton* button2;	///< The second button
					
					
					
					//AQUI VAN LOS METODOS QUE GENERE

				};

			}
		}
	}
}

#endif // _SELECT_LANGUAGE_WIDGET_H_
