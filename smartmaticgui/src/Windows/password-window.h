/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * BasicWindow
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * BasicWindow is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BasicWindow is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PASSWORD_WINDOW_H_

/**
 * @brief	Gets the password window h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _PASSWORD_WINDOW_H_

#include <gtkmm.h>
#include "Windows/basic-window.h"
#include "Configuration/label-configuration.h"
#include "Widgets/smartmatic-button.h"
#include <Functionalities/FunctionalityChallengeConfiguration.h>
#include <Widgets/smartmatic-entry-divided.h>

namespace Smartmatic
{
	namespace GUI  
	{
		namespace Windows
		{
			class PasswordWindow: public BasicWindow
			{
			public:

				/**
				 * @brief	Values that represent PasswordTypeEnum. 
				 */

				enum PasswordTypeEnum
				{
					Password_Keypad,	///< Value that represent Password Keypad. 
					Password_Keyboard,  ///< Value that represent Password Keyboard. 
					Password_Entry  ///< Value that represent Password Entry. 
				};

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	config		 	The configuration.
				 * @param	okButtonLabel	The ok button label.
				 * @param	type		 	The type.
				 */

				PasswordWindow(bool isRole,const Smartmatic::Functionality::FunctionalityChallengeConfiguration& config, std::string okButtonLabel = "",
				               PasswordTypeEnum type = Password_Entry);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~PasswordWindow ();

				/**
				 * @brief	Gets the password correct.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool GetPasswordCorrect();

				/**
				 * @brief	Sets the labels configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	titleConf	  	The title conf.
				 * @param	okAndWrongConf	The ok and wrong conf.
				 * @param	titleFrameConf	The title frame conf.
				 */

				void SetLabelsConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration titleConf,
				                            Smartmatic::GUI::Configuration::LabelConfiguration okAndWrongConf,
				                            Smartmatic::GUI::Configuration::LabelConfiguration titleFrameConf);

				/**
				 * @brief	Sets the divided entry params.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	div	  	The divisions.
				 * @param	maxChar	The maximum characters.
				 * @param	width	The division width.
				 */
				static void SetDividedEntryParams(int div, int maxChar, int width);
					
			protected:

				/**
				 * @brief	Handles ok button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_okButton_clicked();

				/**
				 * @brief	Check pass.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void CheckPass();

			private:
				Gtk::Entry* entryPass;  ///< The entry pass
				Gtk::Alignment* align;  ///< The align
				Gtk::Label* passlabel;  ///< The passlabel
				Gtk::Label* label;  ///< The label
				Gtk::Label* titleLabel; ///< The title label
				Smartmatic::GUI::Widgets::SmartmaticButton* okButton;   ///< The ok button
				Smartmatic::GUI::Widgets::SmartmaticEntryDivided *password;   ///< The password
				Smartmatic::Functionality::FunctionalityChallengeConfiguration config;  ///< The configuration

				//std::string passToCheck;
				std::string messagetitle;   ///< The messagetitle
				std::string messageOk;  ///< The message ok
				std::string messageWrong;   ///< The message wrong
				bool passIsOk;  ///< true if the pass is operation was a success, false if it failed
				bool isRole;  ///< true if it is role

				static int div;
				static int maxChar;
				static int width;

				Smartmatic::GUI::Configuration::LabelConfiguration titleConf;   ///< The title conf
				Smartmatic::GUI::Configuration::LabelConfiguration okAndWrongConf;  ///< The ok and wrong conf
				Smartmatic::GUI::Configuration::LabelConfiguration titleFrameConf;  ///< The title frame conf

				/**
				 * @brief	Gets the label title configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The label title configuration.
				 */

				Smartmatic::GUI::Configuration::LabelConfiguration GetLabelTitleConfiguration();

				/**
				 * @brief	Gets the label ok and wrong configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The label ok and wrong configuration.
				 */

				Smartmatic::GUI::Configuration::LabelConfiguration GetLabelOkAndWrongConfiguration();

				/**
				 * @brief	Gets the label title frame configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The label title frame configuration.
				 */

				Smartmatic::GUI::Configuration::LabelConfiguration GetLabelTitleFrameConfiguration();

			};
		}
	}
}
#endif // _PASSWORD_FORM_H_
