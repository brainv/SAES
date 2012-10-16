/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * MachineApplication
 * Copyright (C)  2010 <>
 * 
 * MachineApplication is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MachineApplication is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _KEYPAD_WIDGET_H_

/**
 * @brief	Gets the keypad widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEYPAD_WIDGET_H_

#include <gtkmm.h>
#include <iostream>
#include "Widgets/key-pad-widget-interface.h"
#include "Widgets/smartmatic-button.h"
#include "Environment/Configurations/resource-path-provider.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @brief	Values that represent KeypadEnum. 
			 */

			enum KeypadEnum
			{
				Numeric,	///< Value that represent KeypadEnum Numeric. 
				Complete,   ///< Values that represent KeypadEnum Complete. 
				CorrigeConfirma,	///< Values that represent KeypadEnum CorrigeConfirma. 
				T9  ///< Values that represent KeypadEnum T9. 
			};


			class KeypadWidget : public Gtk::Table, public KeypadCompleteInterface
			{
			public:		

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type 	The type.
				 * @param	sound	true to sound.
				 */

				KeypadWidget(KeypadEnum type, bool sound = false);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~KeypadWidget();
	
				//Signal Handlers

				/**
				 * @brief	Button clicked.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				void (*button_clicked)(int data);
				KeypadInterface* keypadinterface;   ///< The keypadinterface

				/**
				 * @brief	Button set names.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	prefix	The prefix.
				 */

				void buttonSetNames(std::string prefix);
	
			protected:
				//Signal Handlers

				/**
				 * @brief	Handles button numbered signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				void on_button_numbered(Keys data);

				/**
				 * @brief	Handles button numbered t 9 signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				void on_button_numbered_T9(Keys data);

			private:
				//Widgets of the Glade file
				Gtk::Table* keyPadTable;	///< The key pad table
				SmartmaticButton* button[numberKeys];   ///< The button

				/**
				 * @brief	Sets a sound.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	sound	true to sound.
				 */

				void SetSound(bool sound);

				/**
				 * @brief	All button images.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void AllButtonImages();

				/**
				 * @brief	Sets a normal images.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	normal	true to normal.
				 */

				void SetNormalImages(bool normal);

				/**
				 * @brief	Subscribe normal signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	normal	true to normal.
				 */

				void SubscribeNormalSignals(bool normal);
	
				//T9
				std::string T9_strings[numberKeys]; ///< The 9 strings
				Keys keyLastPressed;	///< The key last pressed
				int timesPressed;   ///< The times pressed
				bool timeElapsed;   ///< true to time elapsed
				std::string SoundKeypad;	///< The sound keypad
				sigc::connection connector; ///< The connector
				sigc::slot<bool> slot;  ///< The slot

				/**
				 * @brief	Executes the timer timeout action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	timer_number	The timer number.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool OnTimerTimeout(int timer_number);
			};
		}
	}
}

#endif // _KEYPAD_WIDGET_H_
