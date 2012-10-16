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

#include "keyword-navigation-interface.h"

using namespace Smartmatic::GUI::Widgets;

keywordNavigationInterface::keywordNavigationInterface()
{

}

keywordNavigationInterface::~keywordNavigationInterface()
{

}

KeysActionsCode keywordNavigationInterface::GetKeysActionsCodeFromString(std::string keyActionCodeStr)
{
	/*
	if(keyActionCodeStr.compare("PK_0") == 0)
		return PK_0;
	else if(keyActionCodeStr.compare("PK_1") == 0)
		return PK_1;
	else if(keyActionCodeStr.compare("PK_2") == 0)
		return PK_2;
	else if(keyActionCodeStr.compare("PK_3") == 0)
		return PK_3;
	else if(keyActionCodeStr.compare("PK_4") == 0)
		return PK_4;
	else if(keyActionCodeStr.compare("PK_5") == 0)
		return PK_5;
	else if(keyActionCodeStr.compare("PK_6") == 0)
		return PK_6;
	else if(keyActionCodeStr.compare("PK_7") == 0)
		return PK_7;
	else if(keyActionCodeStr.compare("PK_8") == 0)
		return PK_8;
	else if(keyActionCodeStr.compare("PK_9") == 0)
		return PK_9;
	else if(keyActionCodeStr.compare("PK_Asterisk") == 0)
		return PK_Asterisk;
	else if(keyActionCodeStr.compare("PK_Plus") == 0)
		return PK_Plus;
	else if(keyActionCodeStr.compare("PK_Minus") == 0)
		return PK_Minus;
	else if(keyActionCodeStr.compare("PK_Invalid") == 0)
		return PK_Invalid;
	else
		return PK_Invalid;
	*/
	if(keyActionCodeStr.compare("BS") == 0)
		return Key_BS;
	else if(keyActionCodeStr.compare("ESC") == 0)
		return Key_ESC;
	else if(keyActionCodeStr.compare("DEL") == 0)
		return Key_DEL;
	else if(keyActionCodeStr.compare("ENTER") == 0)
		return Key_ENTER;
	else if(keyActionCodeStr.compare("SPACE") == 0)
		return Key_space;
	else if(keyActionCodeStr.compare("#") == 0)
		return Key_Numeral;
	else if(keyActionCodeStr.compare("$") == 0)
		return Key_Dollar;
	else if(keyActionCodeStr.compare("%") == 0)
		return Key_Percent;
	else if(keyActionCodeStr.compare("*") == 0)
		return Key_Asterisk;
	else if(keyActionCodeStr.compare("+") == 0)
		return Key_Plus;
	else if(keyActionCodeStr.compare(",") == 0)
		return Key_Comma;
	else if(keyActionCodeStr.compare("-") == 0)
		return Key_Minus;
	else if(keyActionCodeStr.compare(".") == 0)
		return Key_Point;
	else if(keyActionCodeStr.compare("/") == 0)
		return Key_Slash;
	else if(keyActionCodeStr.compare("0") == 0)
		return Key_0;
	else if(keyActionCodeStr.compare("1") == 0)
		return Key_1;
	else if(keyActionCodeStr.compare("2") == 0)
		return Key_2;
	else if(keyActionCodeStr.compare("3") == 0)
		return Key_3;
	else if(keyActionCodeStr.compare("4") == 0)
		return Key_4;
	else if(keyActionCodeStr.compare("5") == 0)
		return Key_5;
	else if(keyActionCodeStr.compare("6") == 0)
		return Key_6;
	else if(keyActionCodeStr.compare("7") == 0)
		return Key_7;
	else if(keyActionCodeStr.compare("8") == 0)
		return Key_8;
	else if(keyActionCodeStr.compare("9") == 0)
		return Key_9;
	else if(keyActionCodeStr.compare(":") == 0)
		return Key_TwoPoints;
	else if(keyActionCodeStr.compare(";") == 0)
		return Key_PointComma;
	else if(keyActionCodeStr.compare("=") == 0)
		return Key_Equal;
	else if(keyActionCodeStr.compare("?") == 0)
		return Key_Question;
	else if(keyActionCodeStr.compare("@") == 0)
		return Key_Arroba;
	else if(keyActionCodeStr.compare("A") == 0)
		return Key_A;
	else if(keyActionCodeStr.compare("B") == 0)
		return Key_B;
	else if(keyActionCodeStr.compare("C") == 0)
		return Key_C;
	else if(keyActionCodeStr.compare("D") == 0)
		return Key_D;
	else if(keyActionCodeStr.compare("E") == 0)
		return Key_E;
	else if(keyActionCodeStr.compare("F") == 0)
		return Key_F;
	else if(keyActionCodeStr.compare("G") == 0)
		return Key_G;
	else if(keyActionCodeStr.compare("H") == 0)
		return Key_H;
	else if(keyActionCodeStr.compare("I") == 0)
		return Key_I;
	else if(keyActionCodeStr.compare("J") == 0)
		return Key_J;
	else if(keyActionCodeStr.compare("K") == 0)
		return Key_K;
	else if(keyActionCodeStr.compare("L") == 0)
		return Key_L;
	else if(keyActionCodeStr.compare("M") == 0)
		return Key_M;
	else if(keyActionCodeStr.compare("N") == 0)
		return Key_N;
	else if(keyActionCodeStr.compare("O") == 0)
		return Key_O;
	else if(keyActionCodeStr.compare("P") == 0)
		return Key_P;
	else if(keyActionCodeStr.compare("Q") == 0)
		return Key_Q;
	else if(keyActionCodeStr.compare("R") == 0)
		return Key_R;
	else if(keyActionCodeStr.compare("S") == 0)
		return Key_S;
	else if(keyActionCodeStr.compare("T") == 0)
		return Key_T;
	else if(keyActionCodeStr.compare("U") == 0)
		return Key_U;
	else if(keyActionCodeStr.compare("V") == 0)
		return Key_V;
	else if(keyActionCodeStr.compare("W") == 0)
		return Key_W;
	else if(keyActionCodeStr.compare("X") == 0)
		return Key_X;
	else if(keyActionCodeStr.compare("Y") == 0)
		return Key_Y;
	else if(keyActionCodeStr.compare("Z") == 0)
		return Key_Z;
	else if(keyActionCodeStr.compare("\\") == 0)
		return Key_BackSlash;
	else if(keyActionCodeStr.compare("a") == 0)
		return Key_a;
	else if(keyActionCodeStr.compare("b") == 0)
		return Key_b;
	else if(keyActionCodeStr.compare("c") == 0)
		return Key_c;
	else if(keyActionCodeStr.compare("d") == 0)
		return Key_d;
	else if(keyActionCodeStr.compare("e") == 0)
		return Key_e;
	else if(keyActionCodeStr.compare("f") == 0)
		return Key_f;
	else if(keyActionCodeStr.compare("g") == 0)
		return Key_g;
	else if(keyActionCodeStr.compare("h") == 0)
		return Key_h;
	else if(keyActionCodeStr.compare("i") == 0)
		return Key_i;
	else if(keyActionCodeStr.compare("j") == 0)
		return Key_j;
	else if(keyActionCodeStr.compare("k") == 0)
		return Key_k;
	else if(keyActionCodeStr.compare("l") == 0)
		return Key_l;
	else if(keyActionCodeStr.compare("m") == 0)
		return Key_m;
	else if(keyActionCodeStr.compare("n") == 0)
		return Key_n;
	else if(keyActionCodeStr.compare("o") == 0)
		return Key_o;
	else if(keyActionCodeStr.compare("p") == 0)
		return Key_p;
	else if(keyActionCodeStr.compare("q") == 0)
		return Key_q;
	else if(keyActionCodeStr.compare("r") == 0)
		return Key_r;
	else if(keyActionCodeStr.compare("s") == 0)
		return Key_s;
	else if(keyActionCodeStr.compare("t") == 0)
		return Key_t;
	else if(keyActionCodeStr.compare("u") == 0)
		return Key_u;
	else if(keyActionCodeStr.compare("v") == 0)
		return Key_v;
	else if(keyActionCodeStr.compare("w") == 0)
		return Key_w;
	else if(keyActionCodeStr.compare("x") == 0)
		return Key_x;
	else if(keyActionCodeStr.compare("y") == 0)
		return Key_y;
	else if(keyActionCodeStr.compare("z") == 0)
		return Key_z;
	else if(keyActionCodeStr.compare("KP0") == 0)
		return Key_Pad0;
	else if(keyActionCodeStr.compare("KP1") == 0)
		return Key_Pad1;
	else if(keyActionCodeStr.compare("KP2") == 0)
		return Key_Pad2;
	else if(keyActionCodeStr.compare("KP3") == 0)
		return Key_Pad3;
	else if(keyActionCodeStr.compare("KP4") == 0)
		return Key_Pad4;
	else if(keyActionCodeStr.compare("KP5") == 0)
		return Key_Pad5;
	else if(keyActionCodeStr.compare("KP6") == 0)
		return Key_Pad6;
	else if(keyActionCodeStr.compare("KP7") == 0)
		return Key_Pad7;
	else if(keyActionCodeStr.compare("KP8") == 0)
		return Key_Pad8;
	else if(keyActionCodeStr.compare("KP9") == 0)
		return Key_Pad9;
	else if(keyActionCodeStr.compare("KP*") == 0)
		return Key_PadAsterisk;
	else if(keyActionCodeStr.compare("KP+") == 0)
		return Key_PadPlus;
	else if(keyActionCodeStr.compare("KP-") == 0)
		return Key_PadMinus;

	return Key_Invalid;
}

std::string keywordNavigationInterface::GetStringFromKeysActionsCode(KeysActionsCode keyActionCode)
{
	std::string toReturn;
	switch(keyActionCode)
	{
		case	Key_BS:
			toReturn = "";
			break;
		case 	Key_ESC:
			toReturn = "";
			break;
		case 	Key_DEL:
			toReturn = "";
			break;
		case 	Key_space:
			toReturn = "";
			break;
		case 	Key_ENTER:
			toReturn = "";
			break;
		case 	Key_Numeral:
			toReturn = "#";
			break;
		case 	Key_Dollar:
			toReturn = "$";
			break;
		case 	Key_Percent:
			toReturn = "%";
			break;
		case 	Key_Asterisk:
			toReturn = "*";
			break;
		case 	Key_Plus:
			toReturn = "+";
			break;
		case 	Key_Comma:
			toReturn = ",";
			break;
		case 	Key_Minus:
			toReturn = "-";
			break;
		case 	Key_Point:
			toReturn = ".";
			break;
		case 	Key_Slash:
			toReturn = "/";
			break;
		case 	Key_0: 
			toReturn = "0";
			break;
		case 	Key_1:
			toReturn = "1";
			break;
		case 	Key_2:
			toReturn = "2";
			break;
		case 	Key_3:
			toReturn = "3";
			break;
		case 	Key_4:
			toReturn = "4";
			break;
		case 	Key_5: 
			toReturn = "5";
			break;
		case 	Key_6:
			toReturn = "6";
			break;
		case 	Key_7:
			toReturn = "7";
			break;
		case 	Key_8:
			toReturn = "8";
			break;
		case 	Key_9: 
			toReturn = "9";
			break;
		case 	Key_TwoPoints:
			toReturn = ":";
			break;
		case 	Key_PointComma:
			toReturn = ";";
			break;
		case 	Key_Equal:
			toReturn = "=";
			break;
		case 	Key_Question:
			toReturn = "?";
			break;
		case 	Key_Arroba:
			toReturn = "@";
			break;
		case 	Key_A:
			toReturn = "A";
			break;
		case 	Key_B:
			toReturn = "B";
			break;
		case 	Key_C:
			toReturn = "C";
			break;
		case 	Key_D:
			toReturn = "D";
			break;
		case 	Key_E:
			toReturn = "E";
			break;
		case 	Key_F:
			toReturn = "F";
			break;
		case 	Key_G:
			toReturn = "G";
			break;
		case 	Key_H:
			toReturn = "H";
			break;
		case	Key_I:
			toReturn = "I";
			break;
		case	Key_J:
			toReturn = "J";
			break;
		case	Key_K:
			toReturn = "K";
			break;
		case	Key_L:
			toReturn = "L";
			break;
		case	Key_M:
			toReturn = "M";
			break;
		case	Key_N:
			toReturn = "N";
			break;
		case	Key_O:
			toReturn = "O";
			break;
		case	Key_P:
			toReturn = "P";
			break;
		case	Key_Q:
			toReturn = "Q";
			break;
		case	Key_R:
			toReturn = "R";
			break;
		case	Key_S: 
			toReturn = "S";
			break;
		case	Key_T: 
			toReturn = "T";
			break;
		case	Key_U:
			toReturn = "U";
			break;
		case	Key_V:
			toReturn = "V";
			break;
		case	Key_W: 
			toReturn = "W";
			break;
		case	Key_X:
			toReturn = "X";
			break;
		case	Key_Y:
			toReturn = "Y";
			break;
		case	Key_Z:
			toReturn = "Z";
			break;
		case	Key_BackSlash:
			toReturn = "\\";
			break;
		case	Key_a:
			toReturn = "a";
			break;
		case	Key_b:
			toReturn = "b";
			break;
		case	Key_c:
			toReturn = "c";
			break;
		case	Key_d:
			toReturn = "d";
			break;
		case	Key_e:
			toReturn = "e";
			break;
		case	Key_f:
			toReturn = "f";
			break;
		case	Key_g:
			toReturn = "g";
			break;
		case	Key_h:
			toReturn = "h";
			break;
		case	Key_i:
			toReturn = "i";
			break;
		case	Key_j:
			toReturn = "j";
			break;
		case	Key_k:
			toReturn = "k";
			break;
		case	Key_l:
			toReturn = "l";
			break;
		case	Key_m:
			toReturn = "m";
			break;
		case	Key_n:
			toReturn = "n";
			break;
		case	Key_o:
			toReturn = "o";
			break;
		case	Key_p: 
			toReturn = "p";
			break;
		case	Key_q:
			toReturn = "q";
			break;
		case	Key_r:
			toReturn = "r";
			break;
		case	Key_s:
			toReturn = "s";
			break;
		case	Key_t:
			toReturn = "t";
			break;
		case	Key_u:
			toReturn = "u";
			break;
		case	Key_v:
			toReturn = "v";
			break;
		case	Key_w:
			toReturn = "w";
			break;
		case	Key_x:
			toReturn = "x";
			break;
		case	Key_y:
			toReturn = "y";
			break;
		case	Key_z:
			toReturn = "z";
			break;
		case	Key_Pad0:
			toReturn = "KP0";
			break;
		case	Key_Pad1:
			toReturn = "KP1";
			break;
		case	Key_Pad2:
			toReturn = "KP2";
			break;
		case	Key_Pad3:
			toReturn = "KP3";
			break;
		case	Key_Pad4:
			toReturn = "KP4";
			break;
		case	Key_Pad5:
			toReturn = "KP5";
			break;
		case	Key_Pad6:
			toReturn = "KP6";
			break;
		case	Key_Pad7:
			toReturn = "KP7";
			break;
		case	Key_Pad8:
			toReturn = "KP8";
			break;
		case	Key_Pad9:
			toReturn = "KP9";
			break;
		case	Key_PadAsterisk:
			toReturn = "KP*";
			break;
		case	Key_PadPlus:
			toReturn = "KP+";
			break;
		case	Key_PadMinus:
			toReturn = "KP-";
			break;
		case	Key_Invalid:
			toReturn = "Invalid";
			break;
		default:
            toReturn = "Invalid";
            break;
	}
	return toReturn;
}
