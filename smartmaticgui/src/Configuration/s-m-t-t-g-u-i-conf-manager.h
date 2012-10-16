/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
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

#ifndef _S_M_T_T_G_U_I_CONFIGURATION_MANAGER_H_

/**
 * @brief	Gets the m t g u i configuration manager h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _S_M_T_T_G_U_I_CONFIGURATION_MANAGER_H_
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <Configuration/SmartmaticGUIConfiguration-schema.hxx>
#include "System/Sounds/beep-descriptor.h"

namespace Smartmatic
{
    namespace Log
    {
        class ISMTTLog;
    }

	namespace GUI
	{
		namespace Configuration
		{
			class SMTTGUIConfigurationManager
			{
			public:

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static SMTTGUIConfigurationManager *Current();

					/**
					 * @brief	Gets the configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else the configuration.
					 */

					std::auto_ptr<Smartmatic::GUI::Configuration::SmartmaticGUIConfiguration>* getConfiguration();

					/**
					 * @brief	Loads the default.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void LoadDefault();
//					Smartmatic::System::Sounds::BeepDescriptor GetSoundDescriptor(SoundType soundType);

					/**
					 * @brief	Gets the smartmatic button sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The smartmatic button sound.
					 */

					std::string getSmartmaticButtonSound();

					/**
					 * @brief	Gets the keypad sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The keypad sound.
					 */

					std::string getKeypadSound();

					/**
					 * @brief	Gets the confirmation dialog sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The confirmation dialog sound.
					 */

					std::string getConfirmationDialogSound();

					/**
					 * @brief	Gets the choose dialog sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The choose dialog sound.
					 */

					std::string getChooseDialogSound();

					/**
					 * @brief	Gets the azerty keypad sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The azerty keypad sound.
					 */

					std::string getAzertyKeypadSound();

					/**
					 * @brief	Gets the menu sound.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The menu sound.
					 */

					std::string getMenuSound();

					/**
					 * @brief	Gets a zerty show pass.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool getAZERTYShowPass();

					/**
					 * @brief	Get all buttons size.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The button size.
					 */
					int getAllButtonsSize();

					/**
					 * @brief	Get menu buttons size.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The button size.
					 */
					int getMenuButtonsSize();

					/**
					 * @brief	Gets the entry configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	value for entry configuration
					 */
					Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::Value getEntryConfiguration();

					/**
					 * @brief Method getter buttons question configuration
					 * @return buttons question configuration
					 * @date 17/05/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::GUI::Configuration::ButtonsQuestionConfiguration::Value getButtonsQuestionConfiguration();
					/**
					 * @brief Method getter gender configuration
					 * @return gender configuration
					 * @date 05/06/2012
					 * @author Yadickson Soto
					 */
					Smartmatic::GUI::Configuration::GenderConfiguration getGenderConfiguration();
					/**
					 * @brief Method getter gender female configuration
					 * @param list
					 * @date 05/06/2012
					 * @author Yadickson Soto
					 */
					void getGenderFemaleConfiguration(std::list <std::string> & list);
					/**
					 * @brief Method getter gender male configuration
					 * @param list
					 * @date 05/06/2012
					 * @author Yadickson Soto
					 */
					void getGenderMaleConfiguration(std::list <std::string> & list);

			protected:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					SMTTGUIConfigurationManager();

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~SMTTGUIConfigurationManager();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void Initialize();
					std::auto_ptr<Smartmatic::GUI::Configuration::SmartmaticGUIConfiguration> *configuration;   ///< The configuration
					static SMTTGUIConfigurationManager * singleton_instance;	///< The singleton instance
			private:
					static Smartmatic::Log::ISMTTLog* logger;/**logger*/	///< The logger
			};
		}
	}
}

#endif // _S_M_T_T_G_U_I_CONFIGURATION_MANAGER_H_
