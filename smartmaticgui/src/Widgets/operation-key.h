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

#ifndef _OPERATION_KEY_H_

/**
 * @brief	Gets the operation key h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _OPERATION_KEY_H_

#include <gtkmm.h>
#include "Widgets/keyword-navigation-interface.h"
#include "Widgets/key-code.h"
namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class OperationKey
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

				static OperationKey* Current();

				/**
				 * @brief	Gets a key action code.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	tempKeyval	The temp keyval.
				 *
				 * @return	The key action code.
				 */

				KeysActionsCode GetKeyActionCode(CustomKeys::KeysCode tempKeyval);

			private:
				static OperationKey *current_instance;  ///< The current instance

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				OperationKey();

				std::vector<KeyCodeClass> v_KeyCode;	///< The v key code
			};
		}
	}
}

#endif // _OPERATION_KEY_H_
