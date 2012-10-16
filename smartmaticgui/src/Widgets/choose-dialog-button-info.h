/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CHOOSE_DIALOG_BUTTON_INFO_H_

/**
 * @brief	Gets the choose dialog button information h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CHOOSE_DIALOG_BUTTON_INFO_H_

#include <iostream>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ChooseDialogButtonInfo
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	name	 	The name.
				 * @param	imagePath	Full pathname of the image file.
				 * @param	code	 	The code.
				 * @param	option   	The option.
				 */

				ChooseDialogButtonInfo(std::string name, std::string imagePath, std::string code, std::string option);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~ChooseDialogButtonInfo();

				/**
				 * @brief	Gets the name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The name.
				 */

				std::string getName();	

				/**
				 * @brief	Gets the image path.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The image path.
				 */

				std::string getImagePath();

				/**
				 * @brief	Gets the code.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The code.
				 */

				std::string getCode();

				/**
				 * @brief	Gets the option.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The option.
				 */

				std::string getOption();

			private:
				std::string name;   ///< The name
				std::string imagePath;  ///< Full pathname of the image file
				std::string code;   ///< The code
				std::string option; ///< The option
			};
		}
	}
}

#endif // _CHOOSE_DIALOG_BUTTON_INFO_H_
