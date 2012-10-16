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


#ifndef _HELP_ITEM_H_

/**
 * @brief	Gets the help item h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _HELP_ITEM_H_

#include <string>



namespace Smartmatic
{
	namespace GUI
	{
		namespace Windows
		{
			class HelpItem
			{
			public:

				/**
				 * @brief	Default constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				HelpItem();

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	key   	The key.
				 * @param	action	The action.
				 */

				HelpItem(std::string key, std::string action);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~HelpItem();

				/**
				 * @brief	Gets the key.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The key.
				 */

				std::string Get_Key();

				/**
				 * @brief	Gets the action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The action.
				 */

				std::string Get_Action();
	
			protected:
				std::string key_value;  ///< The key value
				std::string key_action; ///< The key action
	
			private:

			};
		}
	}
}

#endif // _HELP_ITEM_H_
