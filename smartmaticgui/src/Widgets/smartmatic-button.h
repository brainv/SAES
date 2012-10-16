/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticbutton
 * Copyright (C) Juan Delgado 2010 <juan.delgado@smartmatic.com>
 * 
 * smartmaticbutton is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticbutton is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SMARTMATIC_BUTTON_H_

/**
 * @brief	Gets the smartmatic button h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_BUTTON_H_

#include <gtkmm.h>
#include <iostream>
#include "System/Sounds/beep-manager.h"
#include "System/Sounds/beep-descriptor.h"
#include "Widgets/keyword-navigation-interface.h"
#include "Environment/Configurations/resource-path-provider.h"
#include <Configuration/SmartmaticGUIConfiguration-schema.hxx>
//#include "Sounds/s-a-e-s-sounds-manager.h"



namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticButton : public Gtk::Button
			{
			public:

				/**
				 * @brief	Values that represent SBType. 
				 */

				enum SBType
				{
					KeyPad, ///< Value that represent keypad type. 
					Menu,   ///< Value that represent menu type. 
					Status_Enum,	///< Value that represent status_enum type. 
					ArrowLeft,  ///< Value that represent arrowleft type. 
					ArrowRight, ///< Value that represent arrowright type. 
					ArrowTop,   ///< Value that represent arrowtop type. 
					ArrowBottom,	///< Value that represent arrowbottom type. 
					Custom, ///< Value that represent custom type. 
					Ok, ///< Value that represent ok type. 
					Cancel, ///< Value that represent cancel type.
					Error,  ///< Value that represent error type. 
					Exit,   ///< Value that represent exit type. 
					SpecialAction,  ///< Value that represent specialaction type. 
					Print,  ///< Value that represent print type. 
					MenuOption, ///< Value that represent menuoption type. 
					MenuOptionImage,	///< Value that represent menuoptionimage type. 
					MenuOptionText  ///< Value that represent menuoptiontext type. 
				};

				/**
				 * @brief	constructors.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				SmartmaticButton();

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	label	The label.
				 */

				SmartmaticButton(std::string label);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type	The type.
				 */

				SmartmaticButton(SBType type);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	cobject	If non-null, the cobject.
				 * @param	refBuilder	   	The reference builder.
				 */

				SmartmaticButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder=Gtk::Builder::create());

				/**
				 * @brief	destructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~SmartmaticButton();

				/**
				 * @brief	properties.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type	The type.
				 */

				void SetButtonType(SBType type);

				/**
				 * @brief	Sets a label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	text	The text.
				 */

				void SetLabel(std::string text);

				/**
				 * @brief	Override default set label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	text	The text.
				 */

				void set_label(std::string text);

				/**
				 * @brief	Sets an image.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	path	Full pathname of the file.
				 */

				void SetImage(std::string path);

				/**
				 * @brief	Sets an image.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	icon_name	Name of the icon.
				 * @param	size	 	The size.
				 */

				void SetImage(const Glib::ustring& icon_name, Gtk::IconSize size);

				/**
				 * @brief	Sets a menu option.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	hasShortcut	true if has shortcut.
				 * @param	keyAction  	The key action.
				 * @param	label	   	The label.
				 * @param	path	   	Full pathname of the file.
				 */

				void SetMenuOption(bool hasShortcut, KeysActionsCode keyAction,std::string label, std::string path);//MenuOption,

				/**
				 * @brief	Sets a menu option label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	hasShortcut	true if has shortcut.
				 * @param	keyAction  	The key action.
				 * @param	label	   	The label.
				 */

				void SetMenuOptionLabel(bool hasShortcut, KeysActionsCode keyAction,std::string label);//MenuOptionText,

				/**
				 * @brief	Sets a navigation key.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	keyAction	The key action.
				 */

				void SetNavigationKey(KeysActionsCode keyAction);

				/**
				 * @brief	Modify size inside button.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	size	The size.
				 */

				void ModifySizeInsideButton(int size);

				/**
				 * @brief	child position.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	labelPos	The label position.
				 * @param	imagePos	The image position.
				 * @param	helpPos 	The help position.
				 */

				void WidgetsPosition(int labelPos, int imagePos, int helpPos);

				/**
				 * @brief	Widgets position.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	labelPosX1	The first label position x coordinate.
				 * @param	labelPosX2	The second label position x coordinate.
				 * @param	labelPosY1	The first label position y coordinate.
				 * @param	labelPosY2	The second label position y coordinate.
				 * @param	imagePosX1	The first image position x coordinate.
				 * @param	imagePosX2	The second image position x coordinate.
				 * @param	imagePosY1	The first image position y coordinate.
				 * @param	imagePosY2	The second image position y coordinate.
				 * @param	helpPosX1 	The first help position x coordinate.
				 * @param	helpPosX2 	The second help position x coordinate.
				 * @param	helpPosY1 	The first help position y coordinate.
				 * @param	helpPosY2 	The second help position y coordinate.
				 */

				void WidgetsPosition(int labelPosX1, int labelPosX2, int labelPosY1, int labelPosY2,
							         int imagePosX1, int imagePosX2, int imagePosY1, int imagePosY2,
							         int helpPosX1, int helpPosX2, int helpPosY1, int helpPosY2);

				/**
				 * @brief	child alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Label_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign=Gtk::ALIGN_CENTER, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Label alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Label_Alignment(float xalign=0.5, float yalign=0.5, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Label padding.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	padding_top   	The padding top.
				 * @param	padding_bottom	The padding bottom.
				 * @param	padding_left  	The padding left.
				 * @param	padding_right 	The padding right.
				 */

				void Label_Padding(guint padding_top=0, guint padding_bottom=0, guint padding_left=0, guint padding_right=0);

				/**
				 * @brief	Image alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Image_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign=Gtk::ALIGN_CENTER, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Image alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Image_Alignment(float xalign=0.5, float yalign=0.5, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Image padding.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	padding_top   	The padding top.
				 * @param	padding_bottom	The padding bottom.
				 * @param	padding_left  	The padding left.
				 * @param	padding_right 	The padding right.
				 */

				void Image_Padding(guint padding_top=0, guint padding_bottom=0, guint padding_left=0, guint padding_right=0);

				/**
				 * @brief	Navigation key alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void NavigationKey_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign=Gtk::ALIGN_CENTER, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Navigation key alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void NavigationKey_Alignment(float xalign=0.5, float yalign=0.5, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Navigation key padding.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	padding_top   	The padding top.
				 * @param	padding_bottom	The padding bottom.
				 * @param	padding_left  	The padding left.
				 * @param	padding_right 	The padding right.
				 */

				void NavigationKey_Padding(guint padding_top=0, guint padding_bottom=0, guint padding_left=0, guint padding_right=0);

				/**
				 * @brief	Global alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Global_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign=Gtk::ALIGN_CENTER, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Global alignment.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	xalign	The xalign.
				 * @param	yalign	The yalign.
				 * @param	xscale	The xscale.
				 * @param	yscale	The yscale.
				 */

				void Global_Alignment(float xalign=0.5, float yalign=0.5, float xscale=0.0, float yscale=0.0);

				/**
				 * @brief	Global padding.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	padding_top   	The padding top.
				 * @param	padding_bottom	The padding bottom.
				 * @param	padding_left  	The padding left.
				 * @param	padding_right 	The padding right.
				 */

				void Global_Padding(guint padding_top=0, guint padding_bottom=0, guint padding_left=0, guint padding_right=0);	

				/**
				 * @brief	label methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	font	The font.
				 * @param	size	The size.
				 */

				void ModifyFont(std::string font, int size);

				/**
				 * @brief	label methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	font	The font.
				 */

				void ModifyFontSize(int size);

				/**
				 * @brief	Gets the label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The label.
				 */

				std::string GetLabel(){return label.get_text();}

				/**
				 * @brief	sound properties.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetSoundOnClick();

				/**
				 * @brief	Sets a sound.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type	The type.
				 */

				void SetSound(std::string type);

				/**
				 * @brief	theme properties.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	baseName	Name of the base.
				 */

				void SetCustomName(const Glib::ustring& baseName);

				/**
				 * @brief	Gets the button suffix.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The button suffix.
				 */

				static Glib::ustring GetButtonSuffix();
				
			protected:

				/**
				 * @brief	Handles clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual void on_clicked();
				
			private:
				/**
				 * @brief child widgets
				 */
				Gtk::Table table;   ///< The table
				Gtk::Alignment alignFather; ///< The align father
				Gtk::Alignment alignLabel;  ///< The align label
				Gtk::Alignment alignImage;  ///< The align image
				Gtk::Alignment alignHelp;   ///< The align help
				Gtk::Label label;   ///< The label
				Gtk::Image image;   ///< The image
				Gtk::Label help;	///< The help
				SmartmaticButton* insideButton; ///< The inside button

				/**
				 * @brief variables
				 */
				bool soundOnClick;  ///< true to sound on click
				std::string SoundButton;	///< The sound button
				SBType typeButton;  ///< The type button
				static unsigned long buttonCount;   ///< Number of buttons
				Pango::FontDescription fontDesc;	///< Information describing the font
				Pango::Attribute attribute; ///< The attribute
				Pango::AttrList attrList;   ///< List of attributes

				/**
				 * @brief	internal methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	buttontype	The buttontype.
				 *
				 * @return	The button type.
				 */

				SBType GetButtonType(std::string buttontype);

				/**
				 * @brief	Sets the default images.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetDefaultImages();

				/**
				 * @brief	Sets the visual.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetVisual();

				/**
				 * @brief	Initialises the widgets.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void InitWidgets();

				/**
				 * @brief	Clean up.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void CleanUp();
				std::string buttonSound;	///< The button sound
			};
		}
	}
}

#endif // _SMARTMATIC_BUTTON_H_
