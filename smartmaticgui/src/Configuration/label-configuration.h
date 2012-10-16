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

#ifndef _LABEL_CONFIGURATION_H_

/**
 * @brief	Gets the label configuration h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _LABEL_CONFIGURATION_H_

#include <gtkmm.h>
#include <string>

namespace Smartmatic
{
	namespace GUI
	{
		namespace Configuration
		{
			/**
			 * @brief	Values that represent LabelAlignmentEnum. 
			 */

			enum LabelAlignmentEnum
			{
				LeftAlignment,  ///< Value that represent a left alignment. 
				CenterAlignment,	///< Value that represent a center alignment. 
				RigthAlignment  ///< Value that represent a rigth alignment. 
			};

			/**
			 * @brief	Values that represent LabelStyleEnum. 
			 */

			enum LabelStyleEnum
			{
				NormalStyle,	///< Value that represent a normal style. 
				ObliqueStyle,   ///< Value that represent a oblique style. 
				ItalicStyle ///< Value that represent a Italic style. 
			};

			/**
			 * @brief	Values that represent LabelWeightEnum. 
			 */

			enum LabelWeightEnum
			{
				LightWeight,	///< Value that represent a light weight. 
				NormalWeight,   ///< Value that represent a normal weight. 
				BoldWeight  ///< Value that represent a bold weight. 
			};

			class LabelConfiguration
			{
			public:

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					LabelConfiguration();

					/**
					 * @brief	Constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	labelAlignmentA   	The label alignment a.
					 * @param	verticalPaddingA  	The vertical padding a.
					 * @param	horizontalPaddingA	The horizontal padding a.
					 * @param	fontFamilyA		  	The font family a.
					 * @param	styleA			  	The style a.
					 * @param	weightA			  	The weight a.
					 * @param	sizeA			  	The size a.
					 */

					LabelConfiguration(LabelAlignmentEnum labelAlignmentA, int verticalPaddingA, int horizontalPaddingA, 
					                   std::string fontFamilyA, LabelStyleEnum styleA, LabelWeightEnum weightA,	int sizeA); ///< The size a)

					/**
					 * @brief	Gets the label alignment.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The label alignment.
					 */

					LabelAlignmentEnum GetLabelAlignment();

					/**
					 * @brief	Gets the vertical padding.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The vertical padding.
					 */

					int GetVerticalPadding();

					/**
					 * @brief	Gets the horizontal padding.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The horizontal padding.
					 */

					int GetHorizontalPadding();

					/**
					 * @brief	Gets the font family.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The font family.
					 */

					std::string GetFontFamily();

					/**
					 * @brief	Gets the style.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The style.
					 */

					LabelStyleEnum GetStyle();

					/**
					 * @brief	Gets the weight.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The weight.
					 */

					LabelWeightEnum GetWeight();

					/**
					 * @brief	Gets the size.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @return	The size.
					 */

					int GetSize();		

					/**
					 * @brief	Sets a label alignment.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	labelAlignmentA	The label alignment a.
					 */

					void SetLabelAlignment(LabelAlignmentEnum labelAlignmentA);

					/**
					 * @brief	Sets a vertical padding.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	verticalPaddingA	The vertical padding a.
					 */

					void SetVerticalPadding(int verticalPaddingA);

					/**
					 * @brief	Sets a horizontal padding.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	horizontalPaddingA	The horizontal padding a.
					 */

					void SetHorizontalPadding(int horizontalPaddingA);

					/**
					 * @brief	Sets a font family.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	forntFamilyA	The fornt family a.
					 */

					void SetFontFamily(std::string forntFamilyA);

					/**
					 * @brief	Sets a style.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	styleA	The style a.
					 */

					void SetStyle(LabelStyleEnum styleA);

					/**
					 * @brief	Sets a weight.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	weightA	The weight a.
					 */

					void SetWeight(LabelWeightEnum weightA);

					/**
					 * @brief	Sets a size.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	sizeA	The size a.
					 */

					void SetSize(int sizeA);

					/**
					 * @brief	Sets a label configuration.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	label		 	If non-null, the label.
					 * @param [in,out]	configuration	The configuration.
					 */

					static void SetLabelConfiguration(Gtk::Label* label, Smartmatic::GUI::Configuration::LabelConfiguration& configuration);

					/**
					 * @brief	Sets a label configuration without alignment.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param [in,out]	label		 	If non-null, the label.
					 * @param [in,out]	configuration	The configuration.
					 */

					static void SetLabelConfigurationWithoutAlignment(Gtk::Label* label, Smartmatic::GUI::Configuration::LabelConfiguration& configuration);
					//static void SetLabelConfiguration(Gtk::Label& label, Smartmatic::GUI::Configuration::LabelConfiguration& configuration);

			protected:

			private:
					LabelAlignmentEnum labelAlignment;  ///< The label alignment
					int verticalPadding;	///< The vertical padding
					int horizontalPadding;  ///< The horizontal padding
					std::string fontFamily; ///< The font family
					LabelStyleEnum style;   ///< The style
					LabelWeightEnum weight; ///< The weight
					int size;   ///< The size
			};
		}
	}
}

#endif // _LABEL_CONFIGURATION_H_
