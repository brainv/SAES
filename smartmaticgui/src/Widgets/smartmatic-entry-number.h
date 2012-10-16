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

#ifndef _SMARTMATIC_ENTRY_NUMBER_H_

/**
 * @brief	Gets the smartmatic entry number h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_ENTRY_NUMBER_H_

#include <gtkmm.h>
#include "smartmatic-entry.h"
#include <locale.h>
#include <time.h>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticEntryNumber: public SmartmaticEntry
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	max	The maximum.
				 * @param	min	The minimum.
				 */

				SmartmaticEntryNumber(int max, int min);
								
			protected:

				/**
				 * @brief	Executes the insert text action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	text				The text.
				 * @param [in,out]	position	If non-null, the position.
				 */

				virtual void on_insert_text(const Glib::ustring& text, int* position);
				
				int max;	///< The maximum
				int min;	///< The minimum
			};
		}
	}
}

#endif // _SMARTMATIC_ENTRY_NUMBER_H_
