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
#ifndef _KEYWORD_NAVIGATION_INTERFACE_H_

/**
 * @brief	Gets the keyword navigation interface h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEYWORD_NAVIGATION_INTERFACE_H_

#include <vector>
#include "Windows/help-item.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			/**
			 * @brief	Values that represent KeysActionsCode. 
			 */

			enum KeysActionsCode
			{
				/*
				PK_0 = 0,
				PK_1 = 1,
				PK_2 = 2,
				PK_3 = 3, 
				PK_4 = 4,
				PK_5 = 5,
				PK_6 = 6,
				PK_7 = 7,
				PK_8 = 8,
				PK_9 = 9,
				PK_Asterisk,
				PK_Plus,
				PK_Minus,
				PK_Invalid = 999,
				 */
				Key_BS = 65288, Key_ESC = 27, Key_DEL = 127, Key_space = 32, Key_ENTER = 13,	///< Values that represent the code of the keysActions BS, ESC, DEL, space and enter.
				Key_Quote = 34,  ///< Value that represent the code of the keyAction ".
				Key_Numeral = 35,   ///< Value that represent the code of the keyAction Numeral. 
				Key_Dollar = 36,	///< Value that represent the code of the keyAction Dollar. 
				Key_Percent = 37,   ///< Value that represent the code of the keyAction Percent.
				Key_And = 38,  ///< Value that represent the code of the keyAction &.
				Key_SingleQuote = 39,  ///< Value that represent the code of the keyAction single quote.
				Key_OpenParentheses = 40,  ///< Value that represent the code of the keyAction Open Parentheses
				Key_Asterisk = 42,  ///< Value that represent the code of the keyAction Asterisk. 
				Key_Plus = 43,  ///< Value that represent the code of the keyAction Plus. 
				Key_Comma = 44, ///< Value that represent the code of the keyAction Comma. 
				Key_Minus = 45, ///< Value that represent the code of the keyAction Minus. 
				Key_Point = 46, ///< Value that represent the code of the keyAction Point. 
				Key_Slash = 47, ///< Value that represent the code of the keyAction Slash. 
				Key_0 = 48, Key_1 = 49, Key_2 = 50, Key_3 = 51, Key_4 = 52, Key_5 = 53, ///< Values that represent the code of the keysActions 0, 1, 2, 3, 4 and 5. 
				Key_6 = 54,  Key_7 = 55, Key_8 = 56, Key_9 = 57,	///< Values that represent the code of the keysActions 6, 7, 8 and 9. 
				Key_TwoPoints = 58, Key_PointComma = 59,	///< Values that represent the code of the keysActions twopoints, pointcomma. 
				Key_Equal  = 61,	///< Value that represent the code of the keyAction Equal. 
				Key_Question = 63,  ///< Value that represent the code of the keyAction Question. 
				Key_Arroba = 64,	///< Value that represent the code of the keyAction Arroba. 
				Key_A = 65, Key_B = 66, Key_C = 67, Key_D = 68, Key_E = 69, Key_F = 70, Key_G = 71, ///< Values that represent the code of the keysActions A, B, C, D, E, F and G. 
				Key_H = 72, Key_I = 73, Key_J = 74, Key_K = 75, Key_L = 76, Key_M = 77, Key_N = 78, ///< Values that represent the code of the keysActions H, I, J, K, L, M and N. 
				Key_O = 79, Key_P = 80, Key_Q = 81, Key_R = 82, Key_S = 83, Key_T = 84, Key_U = 85, ///< Values that represent the code of the keysActions O, P, Q, R, S, T and U. 
				Key_V = 86, Key_W = 87, Key_X = 88, Key_Y = 89, Key_Z = 90, ///< Values that represent the code of the keysActions V, W, X, Y and Z.
				Key_OpenBrace = 91,	///< Value that represent the code of the keyAction open brace.
				Key_BackSlash = 92, ///< Value that represent the code of the keyAction Backslash.
				Key_InversedV = 94, ///< Value that represent the code of the keyAction inversed v.
				Key_MinusBig = 95,	///< Value that represent the code of the keyAction minus big.
				Key_Accent2 = 96,	///< Value that represent the code of the keyAction accent 2.
				Key_a = 97, Key_b = 98, Key_c = 99, Key_d = 100, Key_e = 101, Key_f = 102, Key_g = 103, ///< Values that represent the code of the keysActions a, b, c, d, e, f and g. 
				Key_h = 104, Key_i = 105, Key_j = 106, Key_k = 107, Key_l = 108, Key_m = 109, Key_n = 110,  ///< Values that represent the code of the keysActions h, i, j, k, l, m and n. 
				Key_o = 111, Key_p = 112, Key_q = 113, Key_r = 114, Key_s = 115, Key_t = 116, Key_u = 117,  ///< Values that represent the code of the keysActions o, p, q, r, s, t and u. 
				Key_v = 118, Key_w = 119, Key_x = 120, Key_y = 121, Key_z = 122,	///< Values that represent the code of the keysActions v, w, x, y and z.
				Key_OpenKey = 123,	///< Value that represent the code of the keyAction open key.
				Key_Or = 124,	///< Value that represent the code of the keyAction or.
				Key_Alt2 = 126,	///< Value that represent the code of the keyAction alt 2.
				Key_Alt1 = 185,	///< Value that represent the code of the keyAction alt 1.
				Key_Caps0 = 192,	///< Value that represent the code of the keyAction caps 0.
				Key_Caps9 = 199,	///< Value that represent the code of the keyAction caps 9.
				Key_Caps7 = 200,	///< Value that represent the code of the keyAction caps 7.
				Key_Caps2 = 201,	///< Value that represent the code of the keyAction caps 2.
				Key_Caccent = 231,	///< Value that represent the code of the keyAction c acccent.
				Key_Eaccent2 = 232,	///< Value that represent the code of the keyAction e accent 2.
				Key_Eaccent = 233,	///< Value that represent the code of the keyAction e accent.
				Key_Aaccent = 224,	///< Value that represent the code of the keyAction a accent.
				Key_Pad0 = 65456,   ///< Value that represent the code of the keyAction Pad0. 
				Key_Pad1 = 65457,   ///< Value that represent the code of the keyAction Pad1. 
				Key_Pad2 = 65458,   ///< Value that represent the code of the keyAction Pad2. 
				Key_Pad3 = 65459,   ///< Value that represent the code of the keyAction Pad3. 
				Key_Pad4 = 65460,   ///< Value that represent the code of the keyAction Pad4. 
				Key_Pad5 = 65461,   ///< Value that represent the code of the keyAction Pad5. 
				Key_Pad6 = 65462,   ///< Value that represent the code of the keyAction Pad6. 
				Key_Pad7 = 65463,   ///< Value that represent the code of the keyAction Pad7. 
				Key_Pad8 = 65464,   ///< Value that represent the code of the keyAction Pad8. 
				Key_Pad9 = 65465,   ///< Value that represent the code of the keyAction Pad9.
				Key_F1 = 65470,	///< Value that represent the code of the keyAction F1.
				Key_F2 = 65471,	///< Value that represent the code of the keyAction F2.
				Key_F3 = 65472,	///< Value that represent the code of the keyAction F3.
				Key_F4 = 65473,	///< Value that represent the code of the keyAction F4.
				Key_F5 = 65474,	///< Value that represent the code of the keyAction F5.
				Key_F6 = 65475,	///< Value that represent the code of the keyAction F6.
				Key_F7 = 65476,	///< Value that represent the code of the keyAction F7.
				Key_F8 = 65477,	///< Value that represent the code of the keyAction F8.
				Key_F9 = 65478,	///< Value that represent the code of the keyAction F9.
				Key_PadAsterisk = 65450,	///< Value that represent the code of the keyAction PadAsterisk. 
				Key_PadPlus = 65451,	///< Value that represent the code of the keyAction PadPlus. 
				Key_PadMinus = 65453,   ///< Value that represent the code of the keyAction PadMinus. 
				Key_Invalid = 65530,	///< Value that represent the code of the keyAction Invalid. 
			};

			/**
			 * @brief	Values that represent NavigationMode.
			 */

			enum NavigationMode
			{
				SimpleNavigation,   ///< Navigation using the arrows of the keyboard. 
				ShortcutNavigation  ///< Navigation using the direct actions for the keys. 
			};

			class keywordNavigationInterface
			{
			public:

				keywordNavigationInterface();

				virtual ~keywordNavigationInterface();

				/**
				 * @brief	Sets a key.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	value	The value.
				 */

				virtual void SetKey(KeysActionsCode value) = 0;
				//virtual void SetKey(char* value) = 0;

				/**
				 * @brief	Gets the keys actions code from string.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	keyActionCodeStr	The key action code string.
				 *
				 * @return	The keys actions code from string.
				 */

				static KeysActionsCode GetKeysActionsCodeFromString(std::string keyActionCodeStr);

				/**
				 * @brief	Gets a string from keys actions code.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	keyActionCode	The key action code.
				 *
				 * @return	The string from keys actions code.
				 */

				static std::string GetStringFromKeysActionsCode(KeysActionsCode keyActionCode);	
			protected:

			private:

			};
		}
	}
}

#endif // _KEYWORD_NAVIGATION_INTERFACE_H_
