/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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
/**
 * @file chooose-dialog-widget-child-base.h
 * @brief base class for child widgets of choose dialog widget class
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _CHOOSE_DIALOG_WIDGET_CHILD_BASE_H_

/**
 * @brief	Gets the choose dialog widget child base h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CHOOSE_DIALOG_WIDGET_CHILD_BASE_H_

#include <iostream>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ChooseDialogWidgetChildBase
			{
			public:

				ChooseDialogWidgetChildBase();

				virtual ~ChooseDialogWidgetChildBase();

				/**
				 * @brief	Gets the header title.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The header title.
				 */

				virtual std::string GetHeaderTitle();

				/**
				 * @brief	Gets the footer title.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The footer title.
				 */

				virtual std::string GetFooterTitle();

				void setHeaderTitle(std::string headerTitle);

				void setFooterTitle(std::string footerTitle);

			protected:
				std::string headerTitle;	///< The header title
				std::string footerTitle;	///< The footer title

			private:

			};
		}
	}
}

#endif // _CHOOSE_DIALOG_WIDGET_CHILD_BASE_H_
