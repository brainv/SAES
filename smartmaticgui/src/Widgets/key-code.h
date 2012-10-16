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

#ifndef _KEY_CODE_H_

/**
 * @brief	Gets the key code h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEY_CODE_H_

#include <Widgets/keyword-navigation-interface.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			namespace CustomKeys
			{
				/**
				 * @brief	Values that represent KeysCode. 
				 */

				enum KeysCode
				{
					Key_BS = 65288, Key_ESC = 27, Key_DEL = 127, Key_space = 32, Key_ENTER = 13,	///< Values that represent KeysCode BS, ESC, DEL, space and ENTER. 
					Key_Numeral = 35,   ///< Value that represent KeyCode Numeral. 
					Key_Dollar = 36,	///< Value that represent KeyCode Dollar. 
					Key_Percent = 37,   ///< Value that represent KeyCode Percent. 
					Key_Asterisk = 42,  ///< Value that represent KeyCode Asterisk. 
					Key_Plus = 43,  ///< Value that represent KeyCode Plus. 
					Key_Comma = 44, ///< Value that represent KeyCode Comma. 
					Key_Minus = 45, ///< Value that represent KeyCode Minus. 
					Key_Point = 46, ///< Value that represent KeyCode Point. 
					Key_Slash = 47, ///< Value that represent KeyCode Slash. 
					Key_0 = 48, Key_1 = 49, Key_2 = 50, Key_3 = 51, Key_4 = 52, Key_5 = 53, ///< Values that represent KeysCode 0, 1, 2, 3, 4 and 5. 
					Key_6 = 54,  Key_7 = 55, Key_8 = 56, Key_9 = 57,	///< Values that represent KeysCode 6, 7, 8 and 9. 
					Key_TwoPoints = 58, Key_PointComma = 59,	///< Values that represent KeysCode Twopoints and Pointcomma. 
					Key_Equal  = 61,	///< Value that represent KeyCode equal. 
					Key_Question = 63,  ///< Value that represent KeyCode Question. 
					Key_Arroba = 64,	///< Value that represent KeyCode Arroba. 
					Key_A = 65, Key_B = 66, Key_C = 67, Key_D = 68, Key_E = 69, Key_F = 70, Key_G = 71, ///< Values that represent KeysCode A, B, C, D, E, F and G. 
					Key_H = 72, Key_I = 73, Key_J = 74, Key_K = 75, Key_L = 76, Key_M = 77, Key_N = 78, ///< Values that represent KeysCode H, I, J, K, L, M and N. 
					Key_O = 79, Key_P = 80, Key_Q = 81, Key_R = 82, Key_S = 83, Key_T = 84, Key_U = 85, ///< Values that represent KeysCode O, P, Q, R, S, T and U. 
					Key_V = 86, Key_W = 87, Key_X = 88, Key_Y = 89, Key_Z = 90, ///< Values that represent KeysCode V, W, X, Y and Z. 
					Key_BackSlash = 92, ///< Value that represent KeyCode Backslash. 
					Key_a = 97, Key_b = 98, Key_c = 99, Key_d = 100, Key_e = 101, Key_f = 102, Key_g = 103, ///< Values that represent KeysCode a, b, c, d, e, f and g. 
					Key_h = 104, Key_i = 105, Key_j = 106, Key_k = 107, Key_l = 108, Key_m = 109, Key_n = 110,  ///< Values that represent KeysCode h, i, j, k, l, m and n. 
					Key_o = 111, Key_p = 112, Key_q = 113, Key_r = 114, Key_s = 115, Key_t = 116, Key_u = 117,  ///< Values that represent KeysCode o, p, q, r, s, t and u. 
					Key_v = 118, Key_w = 119, Key_x = 120, Key_y = 121, Key_z = 122,	///< Values that represent KeysCode v, w, x, y and z. 
					Key_Pad0 = 65456,   ///< Value that represent KeyCode Pad0. 
					Key_Pad1 = 65457,   ///< Value that represent KeyCode Pad1. 
					Key_Pad2 = 65458,   ///< Value that represent KeyCode Pad2. 
					Key_Pad3 = 65459,   ///< Value that represent KeyCode Pad3. 
					Key_Pad4 = 65460,   ///< Value that represent KeyCode Pad4. 
					Key_Pad5 = 65461,   ///< Value that represent KeyCode Pad5. 
					Key_Pad6 = 65462,   ///< Value that represent KeyCode Pad6. 
					Key_Pad7 = 65463,   ///< Value that represent KeyCode Pad7. 
					Key_Pad8 = 65464,   ///< Value that represent KeyCode Pad8. 
					Key_Pad9 = 65465,   ///< Value that represent KeyCode Pad9. 
					Key_PadAsterisk = 65450,	///< Value that represent KeyCode PadAsterisk. 
					Key_PadPlus = 65451,	///< Value that represent KeyCode PadPlus. 
					Key_PadMinus = 65453,   ///< Value that represent KeyCode PadMinus. 
					Key_Invalid = 65530,	///< Value that represent KeyCode Invalid. 
				};
			};

			class KeyCodeClass
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	key	The key.
				 */

				KeyCodeClass(KeysActionsCode key);

				std::vector<CustomKeys::KeysCode> vectorKeysCode;   ///< The vector keys code
				KeysActionsCode keyActionCode;  ///< The key action code

				/**
				 * @brief	Gets a key code from string.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	keyCodeStr	The key code string.
				 *
				 * @return	The key code from string.
				 */

				static CustomKeys::KeysCode GetKeyCodeFromString(std::string keyCodeStr);

			protected:
	
			private:
	
			};
		}
	}
}

#endif // _KEY_CODE_H_
