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

#include "smartmatic-button.h"
#include <Configuration/SmartmaticGUIConfiguration-schema.hxx>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include <Configuration/configuration-persistence-manager.h>
#include <System/IO/File.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace std;


unsigned long Smartmatic::GUI::Widgets::SmartmaticButton::buttonCount(1);


SmartmaticButton::SmartmaticButton()
:Glib::ObjectBase("SmartmaticButton"),
Gtk::Button(),
table(3,3),
alignFather(),
alignLabel(),
alignImage(),
alignHelp()
{
	soundOnClick = true;
	insideButton = NULL;

	if(get_child() != 0)
		remove();

	typeButton = GetButtonType("Custom");
	SetDefaultImages();
	SetVisual();
	InitWidgets();
	buttonSound = SMTTGUIConfigurationManager::Current()->getSmartmaticButtonSound();
//		soundType = SoundType::CONFIGURATION_NORMAL;
}

SmartmaticButton::SmartmaticButton(std::string label)
:Glib::ObjectBase("SmartmaticButton"),
Gtk::Button(),
table(3,3),
alignFather(),
alignLabel(),
alignImage(),
alignHelp()
{
	soundOnClick = true;
	insideButton = NULL;

	if(get_child() != 0)
		remove();

	typeButton = GetButtonType("Custom");
	SetDefaultImages();
	SetVisual();
	InitWidgets();
	buttonSound = SMTTGUIConfigurationManager::Current()->getSmartmaticButtonSound();
//		soundType = SoundType::CONFIGURATION_NORMAL;

	this->label.set_text(label);
}

SmartmaticButton::SmartmaticButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
:Glib::ObjectBase("SmartmaticButton"),
Gtk::Button(cobject),
table(3,3),
alignFather(),
alignLabel(),
alignImage(),
alignHelp()
{
	soundOnClick = true;
	insideButton = NULL;

	buttonSound = SMTTGUIConfigurationManager::Current()->getSmartmaticButtonSound();
//		soundType = SoundType::CONFIGURATION_NORMAL;
	if(get_child() != 0)
		remove();

	typeButton = GetButtonType("Custom");
	SetDefaultImages();
	SetVisual();
	InitWidgets();
}

SmartmaticButton::SmartmaticButton(SBType type)
:Glib::ObjectBase("SmartmaticButton"),
Gtk::Button(),
table(3,3),
alignFather(),
alignLabel(),
alignImage(),
alignHelp()
{
	soundOnClick = true;
	insideButton = NULL;

	buttonSound = SMTTGUIConfigurationManager::Current()->getSmartmaticButtonSound();
//		soundType = SoundType::CONFIGURATION_NORMAL;
	typeButton = type;
	SetDefaultImages();
	SetVisual();
	InitWidgets();

}

SmartmaticButton::~SmartmaticButton()
{
	if (insideButton) delete insideButton;
}


Glib::ustring SmartmaticButton::GetButtonSuffix()
{
   std::stringstream out;
		   out << SmartmaticButton::buttonCount++;
   string retVal = out.str();
   return retVal;
}

 void SmartmaticButton::SetCustomName(const Glib::ustring& baseName)
 {
	 Glib::ustring realName= baseName + SmartmaticButton::GetButtonSuffix();
	 this->set_name(realName);
 }
void SmartmaticButton::SetNavigationKey(KeysActionsCode keyAction)
{
	std::string letterToShow = Smartmatic::GUI::Widgets::keywordNavigationInterface::GetStringFromKeysActionsCode(keyAction);
	Pango::FontDescription fontLetter = help.get_style()->get_font();
	fontLetter.set_size(11*Pango::SCALE);
	fontLetter.set_weight(Pango::WEIGHT_BOLD);
	help.modify_font(fontLetter);

	help.set_label(letterToShow);
	help.set_visible(true);
	/*
	switch(keyAction)
	{
		case PK_0:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/0_30x30.png"));
			break;
		case PK_1:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/1_30x30.png"));
			break;
		case PK_2:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/2_30x30.png"));
			break;
		case PK_3:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/3_30x30.png"));
			break;
		case PK_4:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/4_30x30.png"));
			break;
		case PK_5:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/5_30x30.png"));
			break;
		case PK_6:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/6_30x30.png"));
			break;
		case PK_7:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/7_30x30.png"));
			break;
		case PK_8:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/8_30x30.png"));
			break;
		case PK_9:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/9_30x30.png"));
			break;
		case PK_Asterisk:

			break;
		case PK_Plus:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/confirma_30.png"));
			break;
		case PK_Minus:
			help.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/corrige_30.png"));
			break;
		default: break;
	}*/
}

void SmartmaticButton::SetButtonType(SBType type)
{
	remove();
	add(alignFather);
	typeButton = type;
	SetDefaultImages();
	SetVisual();
}

void SmartmaticButton::SetLabel(std::string text)
{
	label.set_text(text);
}

void SmartmaticButton::set_label(std::string text)
{
	label.set_text(text);
}

void SmartmaticButton::SetImage(std::string path)
{
	switch(typeButton)
	{
		case KeyPad:
		case ArrowLeft:
		case ArrowRight:
		case ArrowTop:
		case ArrowBottom:
		case Error:
		case Exit:
			break;

		case Status_Enum:
		case Menu:
		case Custom:
		case SpecialAction:
		case Print:
		case MenuOption:
		case MenuOptionImage:
		case MenuOptionText:
			if (File::canOpenFile(path))
			{
				image.set(path);
			}
			break;
		default: break;
	}
}

void SmartmaticButton::SetSoundOnClick()
{
	soundOnClick = true;
}

void SmartmaticButton::on_clicked()
{
	if(soundOnClick)
	{
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(buttonSound);

		//SMTTSoundsManager::Current()->Sound(SoundButton);


		/*
		switch (soundType)
		{
			case SoundType::CONFIGURATION_AUTHENTICATION:
				SAESSoundsManager::Current()->AuthenticationSound();
			break;
			case SoundType::CONFIGURATION_ELECTION:
				SAESSoundsManager::Current()->ElectionSound();
			break;
			case SoundType::CONFIGURATION_MENU:
				SAESSoundsManager::Current()->MenuSound();
			break;
			case SoundType::CONFIGURATION_NORMAL:
				SAESSoundsManager::Current()->NormalSound();
			break;
			case SoundType::CONFIGURATION_OK:
				SAESSoundsManager::Current()->OkSound();
			break;
			case SoundType::CONFIGURATION_ERROR:
				SAESSoundsManager::Current()->ErrorSound();
			break;
			case SoundType::CONFIGURATION_KEYPAD:
				SAESSoundsManager::Current()->KeypadSound();
			break;
			case SoundType::CONFIGURATION_ACTIVATION:
				SAESSoundsManager::Current()->ActivationSound();
			break;
		}*/
	}
	Gtk::Button::on_clicked();
}

void SmartmaticButton::SetImage(const Glib::ustring& icon_name, Gtk::IconSize size)
{
	image.set_from_icon_name(icon_name,size);
}


void SmartmaticButton::Label_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign, float xscale, float yscale)
{ alignLabel.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::Image_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign, float xscale, float yscale)
{ alignImage.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::NavigationKey_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign, float xscale, float yscale)
{ alignHelp.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::Global_Alignment(Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign, float xscale, float yscale)
{ alignFather.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::Label_Alignment(float xalign, float yalign, float xscale, float yscale)
{ alignLabel.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::Image_Alignment(float xalign, float yalign, float xscale, float yscale)
{ alignImage.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::NavigationKey_Alignment(float xalign, float yalign, float xscale, float yscale)
{ alignHelp.set(xalign, yalign, xscale, yscale); }

void SmartmaticButton::Global_Alignment(float xalign, float yalign, float xscale, float yscale)
{ alignFather.set(xalign, yalign, xscale, yscale); }
void SmartmaticButton::Label_Padding(guint padding_top, guint padding_bottom, guint padding_left, guint padding_right)
{ alignLabel.set_padding(padding_top, padding_bottom, padding_left, padding_right); }

void SmartmaticButton::Image_Padding(guint padding_top, guint padding_bottom, guint padding_left, guint padding_right)
{ alignImage.set_padding(padding_top, padding_bottom, padding_left, padding_right); }

void SmartmaticButton::NavigationKey_Padding(guint padding_top, guint padding_bottom, guint padding_left, guint padding_right)
{ alignHelp.set_padding(padding_top, padding_bottom, padding_left, padding_right); }

void SmartmaticButton::Global_Padding(guint padding_top, guint padding_bottom, guint padding_left, guint padding_right)
{ alignFather.set_padding(padding_top, padding_bottom, padding_left, padding_right); }

void SmartmaticButton::WidgetsPosition(int labelPos, int imagePos, int helpPos)
{
	CleanUp();

	switch(labelPos)
	{
		case 1:
			table.attach(alignLabel, 0, 1, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 2:
			table.attach(alignLabel, 1, 2, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 3:
			table.attach(alignLabel, 2, 3, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 4:
			table.attach(alignLabel, 0, 1, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 5:
			table.attach(alignLabel, 1, 2, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 6:
			table.attach(alignLabel, 2, 3, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 7:
			table.attach(alignLabel, 0, 1, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 8:
			table.attach(alignLabel, 1, 2, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 9:
			table.attach(alignLabel, 2, 3, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
	}

	switch(imagePos)
	{
		case 1:
			table.attach(alignImage, 0, 1, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 2:
			table.attach(alignImage, 1, 2, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 3:
			table.attach(alignImage, 2, 3, 0, 1, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 4:
			table.attach(alignImage, 0, 1, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 5:
			table.attach(alignImage, 1, 2, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 6:
			table.attach(alignImage, 2, 3, 1, 2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 7:
			table.attach(alignImage, 0, 1, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 8:
			table.attach(alignImage, 1, 2, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
		case 9:
			table.attach(alignImage, 2, 3, 2, 3, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
			break;
	}

	if(helpPos != 0)
	{
		if (insideButton) delete insideButton;
		insideButton = new SmartmaticButton();
		insideButton->remove();
		insideButton->add(alignHelp);
		insideButton->set_size_request(46, -1);

		switch(helpPos)
		{
			case 1:
				table.attach(*insideButton, 0, 1, 0, 1,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 2:
				table.attach(*insideButton, 1, 2, 0, 1,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 3:
				table.attach(*insideButton, 2, 3, 0, 1,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 4:
				table.attach(*insideButton, 0, 1, 1, 2,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 5:
				table.attach(*insideButton, 1, 2, 1, 2,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 6:
				table.attach(*insideButton, 2, 3, 1, 2,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 7:
				table.attach(*insideButton, 0, 1, 2, 3,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 8:
				table.attach(*insideButton, 1, 2, 2, 3,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
			case 9:
				table.attach(*insideButton, 2, 3, 2, 3,~Gtk::EXPAND, ~Gtk::EXPAND);
				break;
		}
	}
	show_all_children();
}

void SmartmaticButton::ModifySizeInsideButton(int size)
{
	insideButton->set_size_request(size, -1);
}

void SmartmaticButton::WidgetsPosition(int labelPosX1, int labelPosX2, int labelPosY1, int labelPosY2,
									   int imagePosX1, int imagePosX2, int imagePosY1, int imagePosY2,
									   int helpPosX1, int helpPosX2, int helpPosY1, int helpPosY2)
{
	CleanUp();

	table.attach(alignLabel, labelPosX1, labelPosX2, labelPosY1, labelPosY2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
	table.attach(alignImage, imagePosX1, imagePosX2, imagePosY1, imagePosY2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
	table.attach(alignHelp, helpPosX1, helpPosX2, helpPosY1, helpPosY2, Gtk::FILL|Gtk::EXPAND, Gtk::FILL|Gtk::EXPAND, 0, 0);
	show_all_children();
}

void SmartmaticButton::ModifyFont(std::string font, int size)
{
	fontDesc.set_size(size);
	if(font != "")
		fontDesc.set_family(font);
	attribute = Pango::Attribute::create_attr_font_desc(fontDesc);
	attrList.change(attribute);
	label.set_attributes(attrList);
}

void SmartmaticButton::ModifyFontSize(int size)
{
	Pango::FontDescription fontTitle = label.get_style()->get_font();
	fontTitle.set_size(size*Pango::SCALE);
	label.modify_font(fontTitle);
}

void SmartmaticButton::SetVisual()
{
	string dummy = _("Smartmatic.GUI.Widgets.SmartmaticButton.Ok");
	dummy = _("Smartmatic.GUI.Widgets.SmartmaticButton.Cancel");

	int size = SMTTGUIConfigurationManager::Current()->getAllButtonsSize();
	ModifyFontSize(size);

	switch(typeButton)
	{
		case Ok:
			WidgetsPosition(0, 5, 0);
			break;
		case Cancel:
			WidgetsPosition(0, 5, 0);
			break;
		case ArrowLeft:
		case ArrowRight:
		case ArrowTop:
		case ArrowBottom:
		case Error:
		case Exit:
		case Print:
			WidgetsPosition(0, 5, 0);
			break;

		case Menu:
		{
			int sizeMenu = SMTTGUIConfigurationManager::Current()->getMenuButtonsSize();
			ModifyFontSize(sizeMenu);
			WidgetsPosition(5, 0, 0);
		}
			break;
		case KeyPad:
		case Status_Enum:
		case Custom:
		case SpecialAction:
			WidgetsPosition(5, 0, 0);
			break;
		default: break;
	}
}

void SmartmaticButton::SetDefaultImages()
{
	switch(typeButton)
	{
		case ArrowLeft:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/ArrowLeft_30.png"));
			break;

		case ArrowRight:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/ArrowRight_30.png"));
			break;

		case ArrowTop:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/ArrowTop_30.png"));
			break;

		case ArrowBottom:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/ArrowBottom_30.png"));
			break;

		case Ok:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/btn_ok.png"));
			break;

		case Cancel:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/btn_cancel.gif"));
			break;

		case Error:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/Error_30.png"));
			break;

		case Exit:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/Exit_30.png"));
			break;

		case Print:
			image.set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/Print_30.png"));
			break;
		default: break;
	}
}

SmartmaticButton::SBType SmartmaticButton::GetButtonType(std::string buttontype)
{
	if(buttontype == "KeyPad")
		return KeyPad;
	if(buttontype == "Menu")
		return Menu;
	if(buttontype == "Status")
		return Status_Enum;
	if(buttontype == "ArrowLeft")
		return ArrowLeft;
	if(buttontype == "ArrowRight")
		return ArrowRight;
	if(buttontype == "ArrowTop")
		return ArrowTop;
	if(buttontype == "ArrowBottom")
		return ArrowBottom;
	if(buttontype == "Ok")
		return Ok;
	if(buttontype == "Cancel")
		return Cancel;
	if(buttontype == "Error")
		return Error;
	if(buttontype == "Exit")
		return Exit;
	if(buttontype == "SpecialAction")
		return SpecialAction;
	if(buttontype == "Print")
		return Print;
	if(buttontype == "MenuOption")
		return MenuOption;
	if(buttontype == "MenuOptionImage")
		return MenuOptionImage;
	if(buttontype == "MenuOptionText")
		return MenuOptionText;

	return Custom;
}

void SmartmaticButton::InitWidgets()
{
	add(alignFather);
	alignLabel.add(label);
	alignImage.add(image);
	alignHelp.add(help);
	alignFather.add(table);
	//set_use_underline(true);
	show_all_children();
}

void SmartmaticButton::SetMenuOption(bool hasShortcut,KeysActionsCode keyAction,std::string label_text, std::string path)
{
	CleanUp();

	if(label_text.compare("NULL") != 0)
		SetLabel(label_text);
	SetImage(path);
	if(hasShortcut)
	{
		SetNavigationKey(keyAction);
	}
	typeButton = MenuOption;
	
	buttonSound = SMTTGUIConfigurationManager::Current()->getMenuSound();
	if (insideButton) delete insideButton;
	insideButton = new SmartmaticButton();
	insideButton->remove();
	if(hasShortcut)
	{
		insideButton->add(alignHelp);
	}
	insideButton->set_size_request(46, -1);

	if(hasShortcut)
	{
		table.attach(*insideButton, 2, 3, 0, 2, ~Gtk::EXPAND, Gtk::EXPAND | Gtk::FILL);
	}
	table.attach(alignLabel, 1, 2, 1, 2, ~Gtk::EXPAND, ~Gtk::EXPAND);
	table.attach(alignImage, 1, 2, 0, 1, Gtk::EXPAND, ~Gtk::EXPAND);
	show_all_children();
}

void SmartmaticButton::SetMenuOptionLabel(bool hasShortcut,KeysActionsCode keyAction, std::string label_text)
{
	CleanUp();
	SetLabel(label_text);
	if(hasShortcut)
	{
		SetNavigationKey(keyAction);
	}
	buttonSound = SMTTGUIConfigurationManager::Current()->getMenuSound();
	typeButton = MenuOptionText;

	if (insideButton) delete insideButton;
	insideButton = new SmartmaticButton();
	insideButton->remove();
	if(hasShortcut)
	{
		insideButton->add(alignHelp);
	}
	insideButton->set_size_request(46, -1);

	if(hasShortcut)
	{
		table.attach(*insideButton, 2, 3, 0, 3,~Gtk::EXPAND, ~Gtk::EXPAND);
	}
	table.attach(alignLabel, 1, 2, 0, 3,Gtk::EXPAND, Gtk::EXPAND);
	show_all_children();
}


void SmartmaticButton::CleanUp()
{
	if(alignLabel.get_parent() != 0)
		table.remove(alignLabel);
	if(alignImage.get_parent() != 0)
		table.remove(alignImage);
	if(alignHelp.get_parent() != 0)
		table.remove(alignHelp);
}

void SmartmaticButton::SetSound(std::string sound)
{
	buttonSound = sound;
};
