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

#ifndef _KEY_BOARD_WIDGET_INTERFACE_H_

/**
 * @brief	Gets the key board widget interface h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _KEY_BOARD_WIDGET_INTERFACE_H_

#include <iostream>

class KeyboardInterface
{
public:

	KeyboardInterface();

	virtual ~KeyboardInterface();

	/**
	 * @brief	Executes the keyboard press action.
	 *
	 * @author	Luiggi.mendez
	 * @date	27/04/2011
	 *
	 * @param	data	The data.
	 */

	virtual void OnKeyboardPress(std::string data) = 0;
};

#endif // _KEY_BOARD_WIDGET_INTERFACE_H_
