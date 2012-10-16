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

#ifndef _CHOOSE_DIALOG_INFO_INTERFACE_H_

/**
 * @brief	Gets the choose dialog information interface h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CHOOSE_DIALOG_INFO_INTERFACE_H_
#include <iostream>
#include <vector>
#include "Widgets/choose-dialog-button-info.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ChooseDialogInfoInterface
			{
			public:

				ChooseDialogInfoInterface();

				virtual ~ChooseDialogInfoInterface();

					/**
					 * @brief	Gets the list of choices.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	null if it fails, else the list of choices.
					 */

					virtual std::vector<ChooseDialogButtonInfo * > & getListOfChoices() = 0;

					/**
					 * @brief	Gets the title.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The title.
					 */

					virtual std::string getTitle() = 0;

					/**
					 * @brief	Gets the title image path.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The title image path.
					 */

					virtual std::string getTitleImagePath() = 0;

					/**
					 * @brief	Gets the footer.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The footer.
					 */

					virtual std::string getFooter() = 0;

					/**
					 * @brief	Activates the cancel button.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool activateCancelButton() = 0;

					void setTitle(std::string title);
					void setTitleImagePath(std::string titleImagePath);
					void setCode(std::string code);
					void setFooter(std::string footer);

			protected:

					std::string title;  ///< The title
					std::string code;   ///< The code
					std::string titleImagePath; ///< Full pathname of the title image file
					std::string footer; ///< The footer
					bool activateCancel;	///< true to activate cancel
					std::vector<ChooseDialogButtonInfo *> listOfChoices;	///< The list of choices

			};
		}
	}
}

#endif // _CHOOSE_DIALOG_INFO_INTERFACE_H_
