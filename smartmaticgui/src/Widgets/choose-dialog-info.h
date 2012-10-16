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

#ifndef _CHOOSE_DIALOG_INFO_H_

/**
 * @brief	Gets the choose dialog information h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CHOOSE_DIALOG_INFO_H_
#include <iostream>
#include <vector>
#include "Widgets/choose-dialog-button-info.h"
#include "Widgets/choose-dialog-info-interface.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ChooseDialogInfo: public ChooseDialogInfoInterface
			{
	
			public:

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	title				 	The title.
					 * @param	titleImagePath		 	Full pathname of the title image file.
					 * @param	footer				 	The footer.
					 * @param [in,out]	listOfButtons	[in,out] If non-null, the list of buttons.
					 * @param	activateCancelButton 	true to activate cancel button.
					 */

					ChooseDialogInfo(std::string title, std::string titleImagePath, std::string footer, std::vector<ChooseDialogButtonInfo *> & listOfButtons, bool activateCancelButton);

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	title				 	The title.
					 * @param	code				 	The code.
					 * @param	titleImagePath		 	Full pathname of the title image file.
					 * @param	footer				 	The footer.
					 * @param [in,out]	listOfButtons	[in,out] If non-null, the list of buttons.
					 * @param	activateCancelButton 	true to activate cancel button.
					 */

					ChooseDialogInfo(std::string title, std::string code, std::string titleImagePath, std::string footer, std::vector<ChooseDialogButtonInfo *> & listOfButtons, bool activateCancelButton);

					/**
					 * @brief	Finaliser.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~ChooseDialogInfo();

					/**
					 * @brief	Gets the list of choices.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else the list of choices.
					 */

					std::vector<ChooseDialogButtonInfo *> & getListOfChoices();

					/**
					 * @brief	Gets the title.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The title.
					 */

					std::string getTitle();

					/**
					 * @brief	Gets the title image path.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The title image path.
					 */

					std::string getTitleImagePath();

					/**
					 * @brief	Gets the footer.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The footer.
					 */

					std::string getFooter();

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
					 * @brief	Activates the cancel button.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool activateCancelButton();
			};
		}
	}
}

#endif // _CHOOSE_DIALOG_INFO_H_
