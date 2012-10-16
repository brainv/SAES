/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	change-language-widget.h
 *
 * @brief	Declares the change language widget class.
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

#include <gtkmm.h>
#include <vector>
#include "Widgets/image-selection-widget.h"
#include "Runtime/Environment/saes-directories.h"
#include <Voting/Election/ElectionInstalationLanguages.h>

#ifndef _CHANGE_LANGUAGE_WIDGET_H_
#define _CHANGE_LANGUAGE_WIDGET_H_

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
				 * @class	ChangeLanguageWidget
				 *
				 * @brief	Change language widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ChangeLanguageWidget : public Gtk::Frame
				{
				public:

						/**
						 * @fn	ChangeLanguageWidget::ChangeLanguageWidget(Smartmatic::SAES::Runtime::Environment::SaesDirectories & directories);
						 *
						 * @brief	Constructor.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param [in,out]	directories	The directories.
						 */

						ChangeLanguageWidget();

						/**
						 * @fn	ChangeLanguageWidget::~ChangeLanguageWidget();
						 *
						 * @brief	Finaliser.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 */

						~ChangeLanguageWidget();

						void init (Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories);

                        void initialize(std::list<Smartmatic::SAES::Voting::Election::Language>& listLang, bool showOnOneLanguage);

						/**
						 * @fn	bool ChangeLanguageWidget::loadDefaultLanguage();
						 *
						 * @brief	Loads the default language.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool loadDefaultLanguage();

						/**
						 * @typedef	sigc::signal<void> language_changed
						 *
						 * @brief	signals definitions.
						 */

						typedef sigc::signal<void> language_changed;

						/**
						 * @fn	language_changed ChangeLanguageWidget::LanguageChanged();
						 *
						 * @brief	Gets the language changed.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @return	.
						 */

						language_changed LanguageChanged();			

						/**
						 * @fn	void ChangeLanguageWidget::SetSaveFile(bool saveFileA);
						 *
						 * @brief	Sets a save file.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	saveFileA	true to save file a.
						 */

						void SetSaveFile(bool saveFileA);

						/**
						 * @fn	void ChangeLanguageWidget::SetShowMessage(bool shoMessageA);
						 *
						 * @brief	Sets a show message.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	shoMessageA	true to sho message a.
						 */

						void SetShowMessage(bool shoMessageA);

				protected:

						/**
						 * @fn	void ChangeLanguageWidget::on_image_selected(std::string imageCode);
						 *
						 * @brief	Handles image selected signals.
						 *
						 * @author	Cesar.bonilla
						 * @date	4/29/2011
						 *
						 * @param	imageCode	The image code.
						 */

						void on_image_selected(std::string imageCode);


				private:
						bool saveFile;  ///< true to save file
						bool showMessage;   ///< true to show, false to hide the message
						Gtk::Label* labelMessage; ///< message
						Smartmatic::GUI::Widgets::ImageSelectionWidget* imageWidget;	///< The image widget
						Gtk::Alignment* clientAreaAlignment;	///< The client area alignment
						Smartmatic::SAES::Runtime::Environment::SaesDirectories * directories;	///< The directories
						language_changed m_language_changed;	///< The language changed
						static Smartmatic::Log::ISMTTLog* logger;
				};
			}
		}
	}
}

#endif // _CHANGE_LANGUAGE_WIDGET_H_
