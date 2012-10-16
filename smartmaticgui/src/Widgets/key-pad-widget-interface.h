/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Key-Pad
 * Copyright (C)  2010 <>
 * 
 * Key-Pad is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Key-Pad is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _KEYPAD_INTERFACE_H_

/**
 * @brief	Gets the keypad interface h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEYPAD_INTERFACE_H_
namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			const int numberKeys = 13;  ///< Number of keys

			/**
			 * @brief	Values that represent Keys. 
			 */

			enum Keys
			{
				kZero = 0, kOne, kTwo, kThree, kFour, kFive, kSix, kSeven, kEight, kNine,   ///< Values that represent Keys zero, one, two, three, four, five, six, seven, eight and nine. 
				kBranco, kCorrige, kConfirma	///< Values that represent Keys Branco, Corrige and Confirma. 
			};
			class KeypadInterface
			{
			public:

				KeypadInterface();

				virtual ~KeypadInterface();

				/**
				 * @brief	Executes the key press action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				virtual void OnKeyPress(int data) = 0;

				/**
				 * @brief	Executes the key press t 9 action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				virtual void OnKeyPressT9(char data) = 0;
			};		

			class KeypadCompleteInterface
			{
			public:

				KeypadCompleteInterface();

				virtual ~KeypadCompleteInterface();

				/**
				 * @brief	Handles button numbered t 9 signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				virtual void on_button_numbered_T9(Keys data) = 0;

				/**
				 * @brief	Handles button numbered signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	data	The data.
				 */

				virtual void on_button_numbered(Keys data) = 0;
			};
		}
	};
};

#endif // _KEYPAD_INTERFACE_H_
