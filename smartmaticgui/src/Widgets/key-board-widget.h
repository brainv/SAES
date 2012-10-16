/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Key-Board
 * Copyright (C)  2010 <>
 * 
 * Key-Board is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Key-Board is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _KEY_BOARD_WIDGET_H_

/**
 * @brief	Gets the key board widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEY_BOARD_WIDGET_H_

#include <gtkmm.h>
#include <iostream>
#include "key-board-widget-interface.h"
#include "smartmatic-button.h"
//#include "Operation/saes-directory.h"

//#define UI_FILE_Key_Board "src/ui/key-board.ui"


namespace Smartmatic
{
	namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @brief	Values that represent KeysKeyboard. 
				 */

				enum KeysKeyboard
					{
						kbZero, kbOne, kbTwo, kbThree, kbFour, kbFive, kbSix, kbSeven,  ///< Values that represent Keys Zero, One, Two, Three, Four, Five, Six and Seven. 
						kbEight, kbNine,	///< Values that represent Keys Eight and Nine. 
	
						kbA, kbB, kbC, kbD, kbE, kbF, kbG, kbH, kbI, kbJ, kbK, kbL, kbM,	///< Values that represent Keys A, B, C, D, E, F, G, H, I, J, K, L and M. 
						kbN, kbO, kbP, kbQ, kbR, kbS, kbT, kbU, kbV, kbW, kbX, kbY, kbZ,	///< Values that represent Keys N, O, P, Q, R, S, T, U, V, W, X, Y and Z. 

						kbBackspace, kbEnter, kbEsc, kbSpace, kbComa, kbPoint,  ///< Values that represent Keys Backspace, Enter, Esc, Space, Coma and Point. 
						kbDest, kbUnder, kbEqual, kbBrace1, kbBrace2, kbBackslash, kbApostrophe,	///< Values that represent Keys Dest, Under, Equal, Brace1, Brace2, Backslash and Apostrophe. 
						kbShift, kbNN, kbSlash, kbUp, kbDown, kbLeft, kbRight   ///< Values that represent Keys Shift, NN, Slash, Up, Down, Left and Right. 
					};

				class Keyboard: public Gtk::Table 
					{
				public:
					//Constructor

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					Keyboard();
	
					//Destructor	

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~Keyboard();

					//Signal Handlers
					sigc::signal<void,std::string> signal_detected; ///< The signal detected
					sigc::signal<void> signalDelete_detected;   ///< The signal delete detected
					sigc::signal<void> signalEnter_detected;	///< The signal enter detected

					/**
					 * @brief	Button array set names.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	prefixName	Name of the prefix.
					 */

					void buttonArraySetNames(std::string prefixName);
	
				protected:
					//Signal Handlers

					/**
					 * @brief	Handles button keynumbered signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void on_button_keynumbered(std::string data);

				private:
					//Widgets of the Glade file
					Gtk::Table* keyBoardTable;  ///< The key board table
					SmartmaticButton* buttonArray[56];  ///< Array of buttons
					//Gtk::Frame* frame;
					//Gtk::Frame* keyboard;
					//Gtk::VBox* bottomBox;

					/**
					 * @brief	Handles button shift signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void on_button_shift();
					bool isShifted; ///< true if is shifted
				};


			}
	}
}

#endif // _KEY_BOARD_WIDGET_H_
