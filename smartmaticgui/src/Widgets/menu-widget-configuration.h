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

#ifndef _MENU_WIDGET_CONFIGURATION_H_

/**
 * @brief	Gets the menu widget configuration h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _MENU_WIDGET_CONFIGURATION_H_
namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class MenuWidgetConfiguration
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	firstWidth			Width of the first.
				 * @param	firstHeight			Height of the first.
				 * @param	firstSpacing		The first spacing.
				 * @param	firstBrdrWidth  	Width of the first brdr.
				 * @param	firstFrmWidth   	Width of the first frm.
				 * @param	firstFrmHeight  	Height of the first frm.
				 * @param	secondWidth			Width of the second.
				 * @param	secondHeight		Height of the second.
				 * @param	secondSpacing   	The second spacing.
				 * @param	secondBrdrWidth 	Width of the second brdr.
				 * @param	secondFrmPadding	The second frm padding.
				 * @param	hasShortcut			true if has shortcut.
				 */

				MenuWidgetConfiguration(int firstWidth, int firstHeight, int firstSpacing, int firstBrdrWidth, int firstFrmWidth,
					                    int firstFrmHeight, int secondWidth, int secondHeight, int secondSpacing, int secondBrdrWidth,
					                    int secondFrmPadding, bool hasShortcut);

				/**
				 * @brief	Gets the first level width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level width.
				 */

				int Get_FirstLevel_Width()			{ return FirstLevel_Width;			}

				/**
				 * @brief	Gets the first level height.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level height.
				 */

				int Get_FirstLevel_Height()			{ return FirstLevel_Height;			}

				/**
				 * @brief	Gets the first level spacing.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level spacing.
				 */

				int Get_FirstLevel_Spacing()		{ return FirstLevel_Spacing;		}

				/**
				 * @brief	Gets the first level border width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level border width.
				 */

				int Get_FirstLevel_BorderWidth()	{ return FirstLevel_BorderWidth;	}

				/**
				 * @brief	Gets the first level frame width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level frame width.
				 */

				int Get_FirstLevel_Frame_Width()	{ return FirstLevel_Frame_Width;	}

				/**
				 * @brief	Gets the first level frame height.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The first level frame height.
				 */

				int Get_FirstLevel_Frame_Height()   { return FirstLevel_Frame_Height;   }

				/**
				 * @brief	Gets the second level width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The second level width.
				 */

				int Get_SecondLevel_Width()			{ return SecondLevel_Width;			}

				/**
				 * @brief	Gets the second level height.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The second level height.
				 */

				int Get_SecondLevel_Height()		{ return SecondLevel_Height;		}

				/**
				 * @brief	Gets the second level spacing.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The second level spacing.
				 */

				int Get_SecondLevel_Spacing()		{ return SecondLevel_Spacing;		}

				/**
				 * @brief	Gets the second level border width.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The second level border width.
				 */

				int Get_SecondLevel_BorderWidth()   { return SecondLevel_BorderWidth;   }

				/**
				 * @brief	Gets the second level frame padding.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The second level frame padding.
				 */

				int Get_SecondLevel_Frame_Padding() { return SecondLevel_Frame_Padding; }

				/**
				 * @brief	Gets the has button shortcut.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool Get_Has_Button_Shortcut()	    { return HasButton_Shortcut;		 }

			private:
				int FirstLevel_Width;   ///< Width of the first level
				int FirstLevel_Height;  ///< Height of the first level
				int FirstLevel_Spacing; ///< The first level spacing
				int FirstLevel_BorderWidth; ///< Width of the first level border
				int FirstLevel_Frame_Width; ///< Width of the first level frame
				int FirstLevel_Frame_Height;	///< Height of the first level frame
				int SecondLevel_Width;  ///< Width of the second level
				int SecondLevel_Height; ///< Height of the second level
				int SecondLevel_Spacing;	///< The second level spacing
				int SecondLevel_BorderWidth;	///< Width of the second level border
				int SecondLevel_Frame_Padding;  ///< The second level frame padding
				bool HasButton_Shortcut;	///< true if has button shortcut

			};
		}
	}
}

#endif // _MENU_WIDGET_CONFIGURATION_H_
