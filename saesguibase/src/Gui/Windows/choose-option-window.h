/**
 * @file	choose-option-window.h
 *
 * @brief	Declares the choose option Windows Form.
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#ifndef _CHOOSE_OPTION_WINDOW_H_
#define _CHOOSE_OPTION_WINDOW_H_

#include <gtkmm.h>
#include <string.h>
#include <Gui/Windows/empty-window.h>
#include "Widgets/keyword-navigation-interface.h"
#include "Widgets/choose-dialog-widget.h"
#include "Widgets/choose-dialog-info.h"
#include "Widgets/choose-dialog-button-info.h"
#include <iostream>
#include "Environment/Configurations/resource-path-provider.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @brief	Form for viewing the choose option window. 
				 */

				class ChooseOptionWindow : public EmptyWindow, public Smartmatic::GUI::Widgets::keywordNavigationInterface
				{
	
				public:

					/**
					 * @brief	Constructor.
					 * @param [in,out]	info	If non-null, the information.
					 */

					ChooseOptionWindow(Smartmatic::GUI::Widgets::ChooseDialogInfo *info);

					/**
					 * @brief	Override Constructor.
					 * @param [in,out]	info	If non-null, the information.
					 * @param	showCancel  	true to show, false to hide the cancel.
					 */

					ChooseOptionWindow(Smartmatic::GUI::Widgets::ChooseDialogInfo *info, bool showCancel);

					/**
					 * @brief	Finaliser.
					 */

					~ChooseOptionWindow();

					/**
					 * @brief	Gets the option selected.
					 *
					 * @return	null if it fails, else the option selected.
					 */

					Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* GetOptionSelected();
					sigc::signal<void,Smartmatic::GUI::Widgets::ChooseDialogButtonInfo*> signal_detected;   ///< The signal detected
											
				protected:

					Gtk::Frame* frameContainer; ///< frame container
					Gtk::Alignment framePrincipal;  ///< principal frame 
					Smartmatic::GUI::Widgets::ChooseDialogWidget *dialogWidget; ///< dialog widget
						
				private:

					/**
					 * @brief	Executes on option button action.
					 * @param [in,out]	info	If non-null, the information.
					 */

					void onOptionButton(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* info);

					/**
					 * @brief	Sets the key.
					 *
					 * @param	value	The value.
					 */

					void SetKey(Smartmatic::GUI::Widgets::KeysActionsCode value);

					/**
					 * @brief	Builds the initialization.
					 */

					void BuildInitialization();

					Smartmatic::GUI::Widgets::ChooseDialogInfo *info; ///< info
					Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* infoSelected; ///< information selected
				};
			}
		}
	}
}


#endif // _CHOOSE_OPTION_WINDOW_H_
