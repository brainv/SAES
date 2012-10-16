/**
 * @file	language-selection-window.h
 *
 * @brief	Declares the language selection Windows Form.
 * 			
 * @author	Juan delgado <juan.delgado@smartmatic.com>
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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

#ifndef _LANGUAGE_SELECTION_WINDOW_H_
#define _LANGUAGE_SELECTION_WINDOW_H_

#include <Gui/Windows/empty-window.h>
#include "Widgets/image-selection-widget.h"
#include "Voting/Election/ElectionInstalationLanguages.h"
#include "Gui/Widgets/change-language-widget.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @brief	Form for viewing the language selection. 
				 */

				class LanguageSelectionWindow : public Smartmatic::SAES::GUI::Windows::EmptyWindow
				{
				public:

					/**
					 * @brief	Constructor.
					 * @param [in,out]	directories	The directories.
					 */

					LanguageSelectionWindow();

					/**
					 * @brief	Finaliser.
					 */

					~LanguageSelectionWindow();

					void setSaveFile(bool saveFile);

					/**
					 * @brief	method for load default language.
					 * @return	true if load default success.
					 */

					bool loadDefaultLanguage();

                    /**
                     * @brief	method for load widgets in windows.
                     * @param	saveFile	true to save file.
                     */

                    void initialize();

				protected:
					
 
				private:

                    Smartmatic::SAES::GUI::Widgets::ChangeLanguageWidget* changeLanguageWidget;

					/**
					 * @brief	Handles signals on close window.
					 *
					 * @author	Michelle.garcia
					 * @date	28/04/2011
					 */

					void OncloseWindow();
					sigc::connection exit_connector;	///< exit connector
					sigc::slot<bool> exit_slot; ///< exit slot

					/**
					 * @brief	Executes the exit language selection window action.
					 * @param	timer_number	The timer number.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool on_exit_language_selection_window(int timer_number);
				};
			}
		}
	}
}

#endif // _LANGUAGE_SELECTION_WINDOW_H_
