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

#include "key-code.h"
using namespace Smartmatic::GUI::Widgets;

KeyCodeClass::KeyCodeClass(KeysActionsCode key)
:keyActionCode(key)
{
	
}

CustomKeys::KeysCode KeyCodeClass::GetKeyCodeFromString(std::string keyCodeStr)
{
	if(keyCodeStr.compare("Key_BS") == 0)
		return CustomKeys::Key_BS;
	else if(keyCodeStr.compare("Key_ESC") == 0)
		return CustomKeys::Key_ESC;
	else if(keyCodeStr.compare("Key_DEL") == 0)
		return CustomKeys::Key_DEL;
	else if(keyCodeStr.compare("Key_ENTER") == 0)
		return CustomKeys::Key_ENTER;
	else if(keyCodeStr.compare("Key_space") == 0)
		return CustomKeys::Key_space;
	else if(keyCodeStr.compare("Key_Numeral") == 0)
		return CustomKeys::Key_Numeral;
	else if(keyCodeStr.compare("Key_Dollar") == 0)
		return CustomKeys::Key_Dollar;
	else if(keyCodeStr.compare("Key_Percent") == 0)
		return CustomKeys::Key_Percent;
	else if(keyCodeStr.compare("Key_Asterisk") == 0)
		return CustomKeys::Key_Asterisk;
	else if(keyCodeStr.compare("Key_Plus") == 0)
		return CustomKeys::Key_Plus;
	else if(keyCodeStr.compare("Key_Comma") == 0)
		return CustomKeys::Key_Comma;
	else if(keyCodeStr.compare("Key_Minus") == 0)
		return CustomKeys::Key_Minus;
	else if(keyCodeStr.compare("Key_Point") == 0)
		return CustomKeys::Key_Point;
	else if(keyCodeStr.compare("Key_Slash") == 0)
		return CustomKeys::Key_Slash;
	else if(keyCodeStr.compare("Key_0") == 0)
		return CustomKeys::Key_0;
	else if(keyCodeStr.compare("Key_1") == 0)
		return CustomKeys::Key_1;
	else if(keyCodeStr.compare("Key_2") == 0)
		return CustomKeys::Key_2;
	else if(keyCodeStr.compare("Key_3") == 0)
		return CustomKeys::Key_3;
	else if(keyCodeStr.compare("Key_4") == 0)
		return CustomKeys::Key_4;
	else if(keyCodeStr.compare("Key_5") == 0)
		return CustomKeys::Key_5;
	else if(keyCodeStr.compare("Key_6") == 0)
		return CustomKeys::Key_6;
	else if(keyCodeStr.compare("Key_7") == 0)
		return CustomKeys::Key_7;
	else if(keyCodeStr.compare("Key_8") == 0)
		return CustomKeys::Key_8;
	else if(keyCodeStr.compare("Key_9") == 0)
		return CustomKeys::Key_9;
	else if(keyCodeStr.compare("Key_TwoPoints") == 0)
		return CustomKeys::Key_TwoPoints;
	else if(keyCodeStr.compare("Key_PointComma") == 0)
		return CustomKeys::Key_PointComma;
	else if(keyCodeStr.compare("Key_Equal ") == 0)
		return CustomKeys::Key_Equal;
	else if(keyCodeStr.compare("Key_Question") == 0)
		return CustomKeys::Key_Question;
	else if(keyCodeStr.compare("Key_Arroba") == 0)
		return CustomKeys::Key_Arroba;
	else if(keyCodeStr.compare("Key_A") == 0)
		return CustomKeys::Key_A;
	else if(keyCodeStr.compare("Key_B") == 0)
		return CustomKeys::Key_B;
	else if(keyCodeStr.compare("Key_C") == 0)
		return CustomKeys::Key_C;
	else if(keyCodeStr.compare("Key_D") == 0)
		return CustomKeys::Key_D;
	else if(keyCodeStr.compare("Key_E") == 0)
		return CustomKeys::Key_E;
	else if(keyCodeStr.compare("Key_F") == 0)
		return CustomKeys::Key_F;
	else if(keyCodeStr.compare("Key_G") == 0)
		return CustomKeys::Key_G;
	else if(keyCodeStr.compare("Key_H") == 0)
		return CustomKeys::Key_H;
	else if(keyCodeStr.compare("Key_I") == 0)
		return CustomKeys::Key_I;
	else if(keyCodeStr.compare("Key_J") == 0)
		return CustomKeys::Key_J;
	else if(keyCodeStr.compare("Key_K") == 0)
		return CustomKeys::Key_K;
	else if(keyCodeStr.compare("Key_L") == 0)
		return CustomKeys::Key_L;
	else if(keyCodeStr.compare("Key_M") == 0)
		return CustomKeys::Key_M;
	else if(keyCodeStr.compare("Key_N") == 0)
		return CustomKeys::Key_N;
	else if(keyCodeStr.compare("Key_O") == 0)
		return CustomKeys::Key_O;
	else if(keyCodeStr.compare("Key_P") == 0)
		return CustomKeys::Key_P;
	else if(keyCodeStr.compare("Key_Q") == 0)
		return CustomKeys::Key_Q;
	else if(keyCodeStr.compare("Key_R") == 0)
		return CustomKeys::Key_R;
	else if(keyCodeStr.compare("Key_S") == 0)
		return CustomKeys::Key_S;
	else if(keyCodeStr.compare("Key_T") == 0)
		return CustomKeys::Key_T;
	else if(keyCodeStr.compare("Key_U") == 0)
		return CustomKeys::Key_U;
	else if(keyCodeStr.compare("Key_V") == 0)
		return CustomKeys::Key_V;
	else if(keyCodeStr.compare("Key_W") == 0)
		return CustomKeys::Key_W;
	else if(keyCodeStr.compare("Key_X") == 0)
		return CustomKeys::Key_X;
	else if(keyCodeStr.compare("Key_Y") == 0)
		return CustomKeys::Key_Y;
	else if(keyCodeStr.compare("Key_Z") == 0)
		return CustomKeys::Key_Z;
	else if(keyCodeStr.compare("Key_BackSlash") == 0)
		return CustomKeys::Key_BackSlash;
	else if(keyCodeStr.compare("Key_a") == 0)
		return CustomKeys::Key_a;
	else if(keyCodeStr.compare("Key_b") == 0)
		return CustomKeys::Key_b;
	else if(keyCodeStr.compare("Key_c") == 0)
		return CustomKeys::Key_c;
	else if(keyCodeStr.compare("Key_d") == 0)
		return CustomKeys::Key_d;
	else if(keyCodeStr.compare("Key_e") == 0)
		return CustomKeys::Key_e;
	else if(keyCodeStr.compare("Key_f") == 0)
		return CustomKeys::Key_f;
	else if(keyCodeStr.compare("Key_g") == 0)
		return CustomKeys::Key_g;
	else if(keyCodeStr.compare("Key_h") == 0)
		return CustomKeys::Key_h;
	else if(keyCodeStr.compare("Key_i") == 0)
		return CustomKeys::Key_i;
	else if(keyCodeStr.compare("Key_j") == 0)
		return CustomKeys::Key_j;
	else if(keyCodeStr.compare("Key_k") == 0)
		return CustomKeys::Key_k;
	else if(keyCodeStr.compare("Key_l") == 0)
		return CustomKeys::Key_l;
	else if(keyCodeStr.compare("Key_m") == 0)
		return CustomKeys::Key_m;
	else if(keyCodeStr.compare("Key_n") == 0)
		return CustomKeys::Key_n;
	else if(keyCodeStr.compare("Key_o") == 0)
		return CustomKeys::Key_o;
	else if(keyCodeStr.compare("Key_p") == 0)
		return CustomKeys::Key_p;
	else if(keyCodeStr.compare("Key_q") == 0)
		return CustomKeys::Key_q;
	else if(keyCodeStr.compare("Key_r") == 0)
		return CustomKeys::Key_r;
	else if(keyCodeStr.compare("Key_s") == 0)
		return CustomKeys::Key_s;
	else if(keyCodeStr.compare("Key_t") == 0)
		return CustomKeys::Key_t;
	else if(keyCodeStr.compare("Key_u") == 0)
		return CustomKeys::Key_u;
	else if(keyCodeStr.compare("Key_v") == 0)
		return CustomKeys::Key_v;
	else if(keyCodeStr.compare("Key_w") == 0)
		return CustomKeys::Key_w;
	else if(keyCodeStr.compare("Key_x") == 0)
		return CustomKeys::Key_x;
	else if(keyCodeStr.compare("Key_y") == 0)
		return CustomKeys::Key_y;
	else if(keyCodeStr.compare("Key_z") == 0)
		return CustomKeys::Key_z;
	else if(keyCodeStr.compare("Key_Pad0") == 0)
		return CustomKeys::Key_Pad0;
	else if(keyCodeStr.compare("Key_Pad1") == 0)
		return CustomKeys::Key_Pad1;
	else if(keyCodeStr.compare("Key_Pad2") == 0)
		return CustomKeys::Key_Pad2;
	else if(keyCodeStr.compare("Key_Pad3") == 0)
		return CustomKeys::Key_Pad3;
	else if(keyCodeStr.compare("Key_Pad4") == 0)
		return CustomKeys::Key_Pad4;
	else if(keyCodeStr.compare("Key_Pad5") == 0)
		return CustomKeys::Key_Pad5;
	else if(keyCodeStr.compare("Key_Pad6") == 0)
		return CustomKeys::Key_Pad6;
	else if(keyCodeStr.compare("Key_Pad7") == 0)
		return CustomKeys::Key_Pad7;
	else if(keyCodeStr.compare("Key_Pad8") == 0)
		return CustomKeys::Key_Pad8;
	else if(keyCodeStr.compare("Key_Pad9") == 0)
		return CustomKeys::Key_Pad9;
	else if(keyCodeStr.compare("Key_PadAsterisk") == 0)
		return CustomKeys::Key_PadAsterisk;
	else if(keyCodeStr.compare("Key_PadPlus") == 0)
		return CustomKeys::Key_PadPlus;
	else if(keyCodeStr.compare("Key_PadMinus") == 0)
		return CustomKeys::Key_PadMinus;

	return CustomKeys::Key_Invalid;
}
