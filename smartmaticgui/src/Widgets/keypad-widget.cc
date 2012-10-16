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

#include "keypad-widget.h"
#include <Configuration/SmartmaticGUIConfiguration-schema.hxx>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

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
using namespace std;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::Sounds;


KeypadWidget::KeypadWidget(KeypadEnum type, bool sound)
{
	keyPadTable = NULL;
	SmartmaticButton test;
	//Load the Glade file 
	Glib::RefPtr<Gtk::Builder> builder;
	
	SoundKeypad=SMTTGUIConfigurationManager::Current()->getKeypadSound();
	
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"/ui/keypad.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	for(int i = 0; i < numberKeys; i++)
		button[i] = NULL;

	switch(type)
	{
		case T9:
		case Numeric:
			builder->get_widget("Numeric", keyPadTable);
			builder->get_widget_derived("buttonZeroNumeric", button[kZero]);
			builder->get_widget_derived("buttonOneNumeric", button[kOne]);
			builder->get_widget_derived("buttonTwoNumeric", button[kTwo]);
			builder->get_widget_derived("buttonThreeNumeric", button[kThree]);
			builder->get_widget_derived("buttonFourNumeric", button[kFour]);
			builder->get_widget_derived("buttonFiveNumeric", button[kFive]);
			builder->get_widget_derived("buttonSixNumeric", button[kSix]);
			builder->get_widget_derived("buttonSevenNumeric", button[kSeven]);
			builder->get_widget_derived("buttonEightNumeric", button[kEight]);
			builder->get_widget_derived("buttonNineNumeric", button[kNine]);

			if(type == Numeric)
			{
				SetNormalImages(true);
				SubscribeNormalSignals(true);
			}
			else if(type == T9)
			{
				SetNormalImages(false);
				SubscribeNormalSignals(false);				
			}
			
			AllButtonImages();
			break;
					
		case Complete:
			builder->get_widget("Complete", keyPadTable);
			builder->get_widget_derived("buttonZeroComplete", button[kZero]);
			builder->get_widget_derived("buttonOneComplete", button[kOne]);
			builder->get_widget_derived("buttonTwoComplete", button[kTwo]);
			builder->get_widget_derived("buttonThreeComplete", button[kThree]);
			builder->get_widget_derived("buttonFourComplete", button[kFour]);
			builder->get_widget_derived("buttonFiveComplete", button[kFive]);
			builder->get_widget_derived("buttonSixComplete", button[kSix]);
			builder->get_widget_derived("buttonSevenComplete", button[kSeven]);
			builder->get_widget_derived("buttonEightComplete", button[kEight]);
			builder->get_widget_derived("buttonNineComplete", button[kNine]);
			builder->get_widget_derived("buttonBlankComplete", button[kBranco]);
			builder->get_widget_derived("buttonCorrectComplete", button[kCorrige]);
			builder->get_widget_derived("buttonConfirmComplete", button[kConfirma]);

			SetNormalImages(true);
			AllButtonImages();
			SubscribeNormalSignals(true);
			break;

		case CorrigeConfirma:
			builder->get_widget("CorrigeConfirma", keyPadTable);
			builder->get_widget_derived("buttonZeroCorrigeConfirma", button[kZero]);
			builder->get_widget_derived("buttonOneCorrigeConfirma", button[kOne]);
			builder->get_widget_derived("buttonTwoCorrigeConfirma", button[kTwo]);
			builder->get_widget_derived("buttonThreeCorrigeConfirma", button[kThree]);
			builder->get_widget_derived("buttonFourCorrigeConfirma", button[kFour]);
			builder->get_widget_derived("buttonFiveCorrigeConfirma", button[kFive]);
			builder->get_widget_derived("buttonSixCorrigeConfirma", button[kSix]);
			builder->get_widget_derived("buttonSevenCorrigeConfirma", button[kSeven]);
			builder->get_widget_derived("buttonEightCorrigeConfirma", button[kEight]);
			builder->get_widget_derived("buttonNineCorrigeConfirma", button[kNine]);
			builder->get_widget_derived("buttonCorrigeCorrigeConfirma", button[kCorrige]);
			builder->get_widget_derived("buttonConfirmaCorrigeConfirma", button[kConfirma]);

			SetNormalImages(true);
			AllButtonImages();
			SubscribeNormalSignals(true);
			break;
	}

	button[kZero]->set_name("key_pad_zero");
	button[kOne]->set_name("key_pad_one");
	button[kTwo]->set_name("key_pad_two");
	button[kThree]->set_name("key_pad_three");
	button[kFour]->set_name("key_pad_four");
	button[kFive]->set_name("key_pad_five");
	button[kSix]->set_name("key_pad_six");
	button[kSeven]->set_name("key_pad_seven");
	button[kEight]->set_name("key_pad_eight");
	button[kNine]->set_name("key_pad_nine");
	button[kCorrige]->set_name("key_pad_corrige");
	button[kConfirma]->set_name("key_pad_confirma");
	//Set special Sound type
	button[kZero]->SetSound(SoundKeypad);
	button[kOne]->SetSound(SoundKeypad);
	button[kTwo]->SetSound(SoundKeypad);
	button[kThree]->SetSound(SoundKeypad);
	button[kFour]->SetSound(SoundKeypad);
	button[kFive]->SetSound(SoundKeypad);
	button[kSix]->SetSound(SoundKeypad);
	button[kSeven]->SetSound(SoundKeypad);
	button[kEight]->SetSound(SoundKeypad);
	button[kNine]->SetSound(SoundKeypad);
	button[kCorrige]->SetSound(SoundKeypad);
	button[kConfirma]->SetSound(SoundKeypad);
	
	SetSound(sound);
			
	//show childrens
	add(*keyPadTable);
	show_all_children();

	//Initialization Function Pointer
	this->button_clicked = NULL;
	keypadinterface = NULL;

	//T9
	T9_strings[kOne] = ".,?1";
	T9_strings[kTwo] = "abc2";
	T9_strings[kThree] = "def3";
	T9_strings[kFour] = "ghi4";
	T9_strings[kFive] = "jkl5";
	T9_strings[kSix] = "mno6";
	T9_strings[kSeven] = "pqrs7";
	T9_strings[kEight] = "tuv8";
	T9_strings[kNine] = "wxyz9";
	T9_strings[kZero] = " 0";
	T9_strings[kBranco] = "*";
	T9_strings[kCorrige] = "#@";
	
	timesPressed = 0;
	keyLastPressed = kZero;
	timeElapsed = true;

	//Start TIMER
	slot = sigc::bind(sigc::mem_fun(*this,&KeypadWidget::OnTimerTimeout), 0);
}

KeypadWidget::~KeypadWidget()
{
	if(keyPadTable!=NULL)
	{
		delete(keyPadTable);
	}
}

//Signal Handlers
void KeypadWidget::on_button_numbered(Keys data)
{
	if(this->button_clicked != NULL)
		this->button_clicked(data);

	if(keypadinterface != NULL)
		keypadinterface->OnKeyPress(data);	
}

void KeypadWidget::on_button_numbered_T9(Keys data)
{
	if(keypadinterface != NULL)
	{
		char c;

		if(data == keyLastPressed && !timeElapsed)
		{
			keypadinterface->OnKeyPressT9((char)8);//backspace
			int size = T9_strings[data].size();

			if(size > timesPressed)
				c = T9_strings[data][timesPressed];
			else
			{
				timesPressed = 0;
				c = T9_strings[data][0];
			}
			
			timesPressed ++;
			keypadinterface->OnKeyPressT9(c);
			timeElapsed = false;
		}
		else
		{
			c = T9_strings[data][0];
			keyLastPressed = data;
			timesPressed = 1;
			keypadinterface->OnKeyPressT9(c);
		}

		static int timeout = 1000;
		
		connector.disconnect();
		connector = Glib::signal_timeout().connect(slot, timeout);
		timeElapsed = false;
	}
}

bool KeypadWidget::OnTimerTimeout(int timer_number)
{
	timeElapsed = true;
	return false;
}

void KeypadWidget::AllButtonImages()
{
	for(int i = 0; i < numberKeys; i++)
		if(button[i] != NULL)
		{
			button[i]->WidgetsPosition(0,5,0);
		}
}

void KeypadWidget::SetNormalImages(bool normal)
{

	
	if(button[kZero] != NULL)		button[kZero]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/0_60x60.png"));
	if(button[kOne] != NULL)		button[kOne]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/1_60x60.png"));
	if(button[kTwo] != NULL)		button[kTwo]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/2_60x60.png"));
	if(button[kThree] != NULL)		button[kThree]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/3_60x60.png"));
	if(button[kFour] != NULL)		button[kFour]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/4_60x60.png"));
	if(button[kFive] != NULL)		button[kFive]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/5_60x60.png"));
	if(button[kSix] != NULL)		button[kSix]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/6_60x60.png"));
	if(button[kSeven] != NULL)		button[kSeven]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/7_60x60.png"));
	if(button[kEight] != NULL)		button[kEight]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/8_60x60.png"));
	if(button[kNine] != NULL)		button[kNine]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/9_60x60.png"));
	if(button[kBranco] != NULL)		button[kBranco]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/branco_02_60px.png"));
	if(button[kCorrige] != NULL)	button[kCorrige]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/corrige_02_60px.png"));
	if(button[kConfirma] != NULL)	button[kConfirma]->SetImage(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/confirma_60.png"));
}

void KeypadWidget::SubscribeNormalSignals(bool normal)
{
	if(normal)
	{
		if(button[kZero] != NULL)		button[kZero]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kZero));
		if(button[kOne] != NULL)		button[kOne]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kOne));
		if(button[kTwo] != NULL)		button[kTwo]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kTwo));
		if(button[kThree] != NULL)		button[kThree]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kThree));
		if(button[kFour] != NULL)		button[kFour]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kFour));
		if(button[kFive] != NULL)		button[kFive]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kFive));
		if(button[kSix] != NULL)		button[kSix]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kSix));
		if(button[kSeven] != NULL)		button[kSeven]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kSeven));
		if(button[kEight] != NULL)		button[kEight]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kEight));
		if(button[kNine] != NULL)		button[kNine]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kNine));
		if(button[kBranco] != NULL)		button[kBranco]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kBranco));
		if(button[kCorrige] != NULL)	button[kCorrige]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kCorrige));
		if(button[kConfirma] != NULL)	button[kConfirma]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered), kConfirma));
	}
	else
	{
		if(button[kZero] != NULL)		button[kZero]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kZero));
		if(button[kOne] != NULL)		button[kOne]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kOne));
		if(button[kTwo] != NULL)		button[kTwo]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kTwo));
		if(button[kThree] != NULL)		button[kThree]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kThree));
		if(button[kFour] != NULL)		button[kFour]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kFour));
		if(button[kFive] != NULL)		button[kFive]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kFive));
		if(button[kSix] != NULL)		button[kSix]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kSix));
		if(button[kSeven] != NULL)		button[kSeven]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kSeven));
		if(button[kEight] != NULL)		button[kEight]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kEight));
		if(button[kNine] != NULL)		button[kNine]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kNine));
		if(button[kBranco] != NULL)		button[kBranco]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kBranco));
		if(button[kCorrige] != NULL)	button[kCorrige]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kCorrige));
		if(button[kConfirma] != NULL)	button[kConfirma]->signal_clicked().connect(sigc::bind<Keys>( sigc::mem_fun(*this,&KeypadWidget::on_button_numbered_T9), kConfirma));
	}
}

void KeypadWidget::SetSound(bool sound)
{
	if(sound)
	{
		if(button[kZero] != NULL)		button[kZero]->SetSoundOnClick();
		if(button[kOne] != NULL)		button[kOne]->SetSoundOnClick();
		if(button[kTwo] != NULL)		button[kTwo]->SetSoundOnClick();
		if(button[kThree] != NULL)		button[kThree]->SetSoundOnClick();
		if(button[kFour] != NULL)		button[kFour]->SetSoundOnClick();
		if(button[kFive] != NULL)		button[kFive]->SetSoundOnClick();
		if(button[kSix] != NULL)		button[kSix]->SetSoundOnClick();
		if(button[kSeven] != NULL)		button[kSeven]->SetSoundOnClick();
		if(button[kEight] != NULL)		button[kEight]->SetSoundOnClick();
		if(button[kNine] != NULL)		button[kNine]->SetSoundOnClick();
		if(button[kBranco] != NULL)		button[kBranco]->SetSoundOnClick();
		if(button[kCorrige] != NULL)	button[kCorrige]->SetSoundOnClick();
		if(button[kConfirma] != NULL)	button[kConfirma]->SetSoundOnClick();
	}
}


void KeypadWidget::buttonSetNames (std::string prefixName)
	{				
		std::stringstream out;
		
		for(int i = 0; i < numberKeys; i++)
		{			
			out << i;		
			button[i]->set_name(prefixName + "_" + out.str());
		}
	}
