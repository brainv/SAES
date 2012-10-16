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

#ifndef _EXIT_BUTTON_LISTENER_H_

/**
 * @brief	Gets the exit button listener h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _EXIT_BUTTON_LISTENER_H_
namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{

			class ExitButtonListener
			{
			public:

				ExitButtonListener();

				virtual ~ExitButtonListener();

					/**
					 * @brief	Exits this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					virtual void Exit()=0;

			protected:

			private:

			};
		}
	}
}

#endif // _EXIT_BUTTON_LISTENER_H_
