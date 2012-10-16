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

#include "operation-key.h"
using namespace Smartmatic::GUI::Widgets;

OperationKey* OperationKey::current_instance = NULL;
OperationKey* OperationKey::Current()
{
	if (!current_instance)
		current_instance = new OperationKey();

	return current_instance;
}

OperationKey::OperationKey()
{
	/*
	KeysActionsCode keyAction0 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_0");
	KeyCodeClass actualKeyCode0(keyAction0);
	CustomKeys::KeysCode keyCode00 = KeyCodeClass::GetKeyCodeFromString("Key_0");
	actualKeyCode0.vectorKeysCode.push_back(keyCode00);
	CustomKeys::KeysCode keyCode01 = KeyCodeClass::GetKeyCodeFromString("Key_Pad0");
	actualKeyCode0.vectorKeysCode.push_back(keyCode01);
	v_KeyCode.push_back(actualKeyCode0);
	
	KeysActionsCode keyAction1 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_1");
	KeyCodeClass actualKeyCode1(keyAction1);
	CustomKeys::KeysCode keyCode10 = KeyCodeClass::GetKeyCodeFromString("Key_1");
	actualKeyCode1.vectorKeysCode.push_back(keyCode10);
	CustomKeys::KeysCode keyCode11 = KeyCodeClass::GetKeyCodeFromString("Key_Pad1");
	actualKeyCode1.vectorKeysCode.push_back(keyCode11);
	v_KeyCode.push_back(actualKeyCode1);

	KeysActionsCode keyAction2 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_2");
	KeyCodeClass actualKeyCode2(keyAction2);
	CustomKeys::KeysCode keyCode20 = KeyCodeClass::GetKeyCodeFromString("Key_2");
	actualKeyCode2.vectorKeysCode.push_back(keyCode20);
	CustomKeys::KeysCode keyCode21 = KeyCodeClass::GetKeyCodeFromString("Key_Pad2");
	actualKeyCode2.vectorKeysCode.push_back(keyCode21);
	v_KeyCode.push_back(actualKeyCode2);

	KeysActionsCode keyAction3 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_3");
	KeyCodeClass actualKeyCode3(keyAction3);
	CustomKeys::KeysCode keyCode30 = KeyCodeClass::GetKeyCodeFromString("Key_3");
	actualKeyCode3.vectorKeysCode.push_back(keyCode30);
	CustomKeys::KeysCode keyCode31 = KeyCodeClass::GetKeyCodeFromString("Key_Pad3");
	actualKeyCode3.vectorKeysCode.push_back(keyCode31);
	v_KeyCode.push_back(actualKeyCode3);

	KeysActionsCode keyAction4 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_4");
	KeyCodeClass actualKeyCode4(keyAction4);
	CustomKeys::KeysCode keyCode40 = KeyCodeClass::GetKeyCodeFromString("Key_4");
	actualKeyCode4.vectorKeysCode.push_back(keyCode40);
	CustomKeys::KeysCode keyCode41 = KeyCodeClass::GetKeyCodeFromString("Key_Pad4");
	actualKeyCode4.vectorKeysCode.push_back(keyCode41);
	v_KeyCode.push_back(actualKeyCode4);

	KeysActionsCode keyAction5 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_5");
	KeyCodeClass actualKeyCode5(keyAction5);
	CustomKeys::KeysCode keyCode50 = KeyCodeClass::GetKeyCodeFromString("Key_5");
	actualKeyCode5.vectorKeysCode.push_back(keyCode50);
	CustomKeys::KeysCode keyCode51 = KeyCodeClass::GetKeyCodeFromString("Key_Pad5");
	actualKeyCode5.vectorKeysCode.push_back(keyCode51);
	v_KeyCode.push_back(actualKeyCode5);

	KeysActionsCode keyAction6 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_6");
	KeyCodeClass actualKeyCode6(keyAction6);
	CustomKeys::KeysCode keyCode60 = KeyCodeClass::GetKeyCodeFromString("Key_6");
	actualKeyCode6.vectorKeysCode.push_back(keyCode60);
	CustomKeys::KeysCode keyCode61 = KeyCodeClass::GetKeyCodeFromString("Key_Pad6");
	actualKeyCode6.vectorKeysCode.push_back(keyCode61);
	v_KeyCode.push_back(actualKeyCode6);

	KeysActionsCode keyAction7 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_7");
	KeyCodeClass actualKeyCode7(keyAction7);
	CustomKeys::KeysCode keyCode70 = KeyCodeClass::GetKeyCodeFromString("Key_7");
	actualKeyCode7.vectorKeysCode.push_back(keyCode70);
	CustomKeys::KeysCode keyCode71 = KeyCodeClass::GetKeyCodeFromString("Key_Pad7");
	actualKeyCode7.vectorKeysCode.push_back(keyCode71);
	v_KeyCode.push_back(actualKeyCode7);

	KeysActionsCode keyAction8 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_8");
	KeyCodeClass actualKeyCode8(keyAction8);
	CustomKeys::KeysCode keyCode80 = KeyCodeClass::GetKeyCodeFromString("Key_8");
	actualKeyCode8.vectorKeysCode.push_back(keyCode80);
	CustomKeys::KeysCode keyCode81 = KeyCodeClass::GetKeyCodeFromString("Key_Pad8");
	actualKeyCode8.vectorKeysCode.push_back(keyCode81);
	v_KeyCode.push_back(actualKeyCode8);

	KeysActionsCode keyAction9 = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_9");
	KeyCodeClass actualKeyCode9(keyAction9);
	CustomKeys::KeysCode keyCode90 = KeyCodeClass::GetKeyCodeFromString("Key_9");
	actualKeyCode9.vectorKeysCode.push_back(keyCode90);
	CustomKeys::KeysCode keyCode91 = KeyCodeClass::GetKeyCodeFromString("Key_Pad9");
	actualKeyCode9.vectorKeysCode.push_back(keyCode91);
	v_KeyCode.push_back(actualKeyCode9);

	KeysActionsCode keyActionAstk = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_Asterisk");
	KeyCodeClass actualKeyCodeAstk(keyActionAstk);
	CustomKeys::KeysCode keyCodeAstk0  = KeyCodeClass::GetKeyCodeFromString("Key_Asterisk");
	actualKeyCodeAstk.vectorKeysCode.push_back(keyCodeAstk0);
	CustomKeys::KeysCode keyCodeAstk1 = KeyCodeClass::GetKeyCodeFromString("Key_PadAsterisk");
	actualKeyCodeAstk.vectorKeysCode.push_back(keyCodeAstk1);
	v_KeyCode.push_back(actualKeyCodeAstk);

	KeysActionsCode keyActionPlus = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_Plus");
	KeyCodeClass actualKeyCodePlus(keyActionPlus);
	CustomKeys::KeysCode keyCodePlus0 = KeyCodeClass::GetKeyCodeFromString("Key_Plus");
	actualKeyCodePlus.vectorKeysCode.push_back(keyCodePlus0);
	CustomKeys::KeysCode keyCodePlus1 = KeyCodeClass::GetKeyCodeFromString("Key_PadPlus");
	actualKeyCodePlus.vectorKeysCode.push_back(keyCodePlus1);
	v_KeyCode.push_back(actualKeyCodePlus);

	KeysActionsCode keyActionMinus = keywordNavigationInterface::GetKeysActionsCodeFromString("PK_Minus");
	KeyCodeClass actualKeyCodeMinus(keyActionMinus);
	CustomKeys::KeysCode keyCodeMinus0 = KeyCodeClass::GetKeyCodeFromString("Key_Minus");
	actualKeyCodeMinus.vectorKeysCode.push_back(keyCodeMinus0);
	CustomKeys::KeysCode keyCodeMinus1 = KeyCodeClass::GetKeyCodeFromString("Key_PadMinus");
	actualKeyCodeMinus.vectorKeysCode.push_back(keyCodeMinus1);
	v_KeyCode.push_back(actualKeyCodeMinus);*/
	
}

KeysActionsCode OperationKey::GetKeyActionCode(CustomKeys::KeysCode tempKeyval)
{
	//std::vector<KeyCodeClass> normal_v_KeyCode = v_KeyCode;
	//std::vector<KeyCodeClass>::iterator iter = v_KeyCode.begin();

	//for(; iter!=v_KeyCode.end(); iter++)
	//{
		//for(std::vector<CustomKeys::KeysCode>::iterator iter2 = iter->vectorKeysCode.begin(); iter2!=iter->vectorKeysCode.end(); iter2++)
		//{
			//if(*iter2 == tempKeyval)
				//return iter->keyActionCode;
		//}
	//}

	//return PK_Invalid;
	return KeysActionsCode(tempKeyval);
}






