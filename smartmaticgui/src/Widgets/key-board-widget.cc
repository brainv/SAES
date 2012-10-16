/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Key-Board
 * Copyright (C)  2010 <>
 * 
 * Key-Board is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Key-Board is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "key-board-widget.h"
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
#include <gtkmm.h>
#include <string>
#include <iostream>

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

using namespace std;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;
Keyboard::Keyboard()
{
	SmartmaticButton test;
	//Load the Glade file 
	Glib::RefPtr<Gtk::Builder> builder;
	//int window_width = MachineApplicationConfiguration::Current()->Get_BaseWindow_Width();
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/key-board.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	/*Este string debe estar correlacionado con el enum KeysKeyboard
	 *definido en "key-board-widget.h" */
	Glib::ustring stringButtonKeys[] =
	{
		"button0", "button1", "button2", "button3", "button4", "button5", 
		"button6", "button7", "button8", "button9", 

		"buttonA", "buttonB", "buttonC", "buttonD", "buttonE", "buttonF", 
		"buttonG", "buttonH", "buttonI", "buttonJ", "buttonK", "buttonL", 
		"buttonM", "buttonN", "buttonO", "buttonP", "buttonQ", "buttonR", 
		"buttonS", "buttonT", "buttonU", "buttonV", "buttonW", "buttonX", 
		"buttonY", "buttonZ", 

		"buttonBackspace", "buttonEnter", "buttonEsc", "buttonSpace", 
		"buttonComa", "buttonPoint", "buttonDest", "buttonUnder", 
		"buttonEqual", "buttonBrace1", "buttonBrace2", "buttonBackslash", 
		"buttonApostrophe", "buttonShift", "buttonÑ", "buttonSlash",
		"buttonUp", "buttonDown", "buttonLeft", "buttonRight"
	};
	Glib::ustring sKeys[] =
	{
		_("Smartmatic.GUI.Glade.Key-board.0Message"), _("Smartmatic.GUI.Glade.Key-board.1Message"), _("Smartmatic.GUI.Glade.Key-board.2Message"), _("Smartmatic.GUI.Glade.Key-board.3Message"), _("Smartmatic.GUI.Glade.Key-board.4Message"), _("Smartmatic.GUI.Glade.Key-board.5Message"), _("Smartmatic.GUI.Glade.Key-board.6Message"), _("Smartmatic.GUI.Glade.Key-board.7Message"), _("Smartmatic.GUI.Glade.Key-board.8Message"), _("Smartmatic.GUI.Glade.Key-board.9Message"), 
		_("Smartmatic.GUI.Glade.Key-board.AMessage"), _("Smartmatic.GUI.Glade.Key-board.BMessage"), _("Smartmatic.GUI.Glade.Key-board.CMessage"), _("Smartmatic.GUI.Glade.Key-board.DMessage"), _("Smartmatic.GUI.Glade.Key-board.EMessage"), _("Smartmatic.GUI.Glade.Key-board.FMessage"), _("Smartmatic.GUI.Glade.Key-board.GMessage"), _("Smartmatic.GUI.Glade.Key-board.HMessage"), _("Smartmatic.GUI.Glade.Key-board.IMessage"), _("Smartmatic.GUI.Glade.Key-board.JMessage"), _("Smartmatic.GUI.Glade.Key-board.KMessage"), _("Smartmatic.GUI.Glade.Key-board.LMessage"), _("Smartmatic.GUI.Glade.Key-board.MMessage"),
		_("Smartmatic.GUI.Glade.Key-board.NMessage"), _("Smartmatic.GUI.Glade.Key-board.OMessage"), _("Smartmatic.GUI.Glade.Key-board.PMessage"), _("Smartmatic.GUI.Glade.Key-board.QMessage"), _("Smartmatic.GUI.Glade.Key-board.RMessage"), _("Smartmatic.GUI.Glade.Key-board.SMessage"), _("Smartmatic.GUI.Glade.Key-board.TMessage"), _("Smartmatic.GUI.Glade.Key-board.UMessage"), _("Smartmatic.GUI.Glade.Key-board.VMessage"), _("Smartmatic.GUI.Glade.Key-board.WMessage"), _("Smartmatic.GUI.Glade.Key-board.XMessage"), _("Smartmatic.GUI.Glade.Key-board.YMessage"), _("Smartmatic.GUI.Glade.Key-board.ZMessage")
	};
	
	//Instiate its widgets:
	//builder->get_widget("frame", frame);
	//builder->get_widget("keyboard", keyboard);
	//builder->get_widget("vbox",bottomBox);
	builder->get_widget("table1", keyBoardTable);

	
	for(int i = 0; i < 56; i++)
		builder->get_widget_derived(stringButtonKeys[i], buttonArray[i]);

	//Subscribe to signal events
	for(int i = 0; i < 36; i++)//Numbers and Letters
	{
		buttonArray[i]->SetLabel(sKeys[i]);
		buttonArray[i]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), sKeys[i]));
		buttonArray[i]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
	}
	//Especials
		buttonArray[kbBackspace]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE1Message")));//BS
		buttonArray[kbEnter]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE2Message")));//LF
		buttonArray[kbEsc]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE6Message")));//Esc
		buttonArray[kbSpace]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE5Message")));//Space
		buttonArray[kbComa]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE3Message")));
		buttonArray[kbPoint]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE4Message")));
		buttonArray[kbDest]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE7Message")));
		buttonArray[kbUnder]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE8Message")));
		buttonArray[kbEqual]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE9Message")));
		buttonArray[kbBrace1]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE10Message")));
		buttonArray[kbBrace2]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE11Message"))); 
		buttonArray[kbBackslash]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE12Message")));
		buttonArray[kbApostrophe]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE13Message")));
		buttonArray[kbNN]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.ÑMessage")));
		buttonArray[kbSlash]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE14Message")));
		buttonArray[kbUp]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE15Message")));
		buttonArray[kbDown]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE16Message")));
		buttonArray[kbLeft]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE17Message")));
		buttonArray[kbRight]->signal_clicked().connect(sigc::bind<string>(sigc::mem_fun(*this, &Keyboard::on_button_keynumbered), _("Smartmatic.GUI.Glade.Key-board.CE18Message")));

		buttonArray[kbBackspace]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbEnter]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbEsc]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbSpace]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbComa]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbPoint]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbDest]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbUnder]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbEqual]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbBrace1]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbBrace2]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbBackslash]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbApostrophe]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbNN]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbSlash]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbUp]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbDown]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbLeft]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		buttonArray[kbRight]->SetSound(SMTTGUIConfigurationManager::Current()->getAzertyKeypadSound());
		
		buttonArray[kbBackspace]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE1Message"));//BS
		buttonArray[kbEnter]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE2Message"));//LF
		buttonArray[kbEsc]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE6Message"));//Esc
		buttonArray[kbSpace]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE5Message"));//Space
		buttonArray[kbComa]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE3Message"));
		buttonArray[kbPoint]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE4Message"));
		buttonArray[kbDest]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE7Message"));
		buttonArray[kbUnder]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE8Message"));
		buttonArray[kbEqual]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE9Message"));
		buttonArray[kbBrace1]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE10Message"));
		buttonArray[kbBrace2]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE11Message")); 
		buttonArray[kbBackslash]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE12Message"));
		buttonArray[kbApostrophe]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE13Message"));
		buttonArray[kbNN]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.ÑMessage"));
		buttonArray[kbSlash]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE14Message"));
		buttonArray[kbUp]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE15Message"));
		buttonArray[kbDown]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE16Message"));
		buttonArray[kbLeft]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE17Message"));
		buttonArray[kbRight]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.CE18Message"));
	
		buttonArray[kbShift]->signal_clicked().connect(sigc::mem_fun(*this, &Keyboard::on_button_shift));
		buttonArray[kbShift]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.SHIFTMessage"));
	//Properties of TextView
	//keyBoardText->modify_base(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
	//textBuffer = Gtk::TextBuffer::create();
	///keyBoardText->set_buffer(textBuffer);

	//show children	
	
	add(*keyBoardTable);
	show_all_children();

	//Initialization Function Pointer
	isShifted = false;
}

//Destructor
Keyboard::~Keyboard()
{
}

void Keyboard::on_button_shift()
{
	std::string strLabel;
	char cLabel;

	for(int i = 10; i < 36; i++)//Letters
	{
		strLabel = buttonArray[i]->GetLabel();
		
		if(!isShifted)
		{
			cLabel = strLabel[0] + 32;
			buttonArray[50]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.ñoMessage"));
		}
		else
		{
			cLabel = strLabel[0] - 32;
			buttonArray[50]->SetLabel(_("Smartmatic.GUI.Glade.Key-board.ÑMessage"));
		}

		strLabel.assign(1, cLabel);
		buttonArray[i]->SetLabel(strLabel);
	}
	isShifted = !isShifted;
}

//Signal Handlers
void Keyboard::on_button_keynumbered(string data)
{
	char cLabel;

	if(data.compare(_("Smartmatic.GUI.Glade.Key-board.CE1Message")) == 0)
	{
		signalDelete_detected.emit();
		return;
	}
	else if(data.compare(_("Smartmatic.GUI.Glade.Key-board.CE2Message")) == 0)
	{
		signalEnter_detected.emit();
		return;
	}
	else if(data.compare(_("Smartmatic.GUI.Glade.Key-board.CE5Message")) == 0)
	{
		data = " ";
	}	
	else if(
	   data.compare(_("Smartmatic.GUI.Glade.Key-board.CE6Message")) == 0 ||
	   data.compare(_("Smartmatic.GUI.Glade.Key-board.CE15Message")) == 0 ||
	   data.compare(_("Smartmatic.GUI.Glade.Key-board.CE16Message")) == 0 ||
	   data.compare(_("Smartmatic.GUI.Glade.Key-board.CE17Message")) == 0 ||
	   data.compare(_("Smartmatic.GUI.Glade.Key-board.CE18Message")) == 0)
	{
	
		return;
	}

	else if(isShifted)
	{
		size_t found;
		found = data.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZÑ?");
		if(found == string::npos)
		{
			cLabel = data[0] + 32;
			data.assign(1, cLabel);
		}
	}

	signal_detected.emit(data);
	
}

	void Keyboard::buttonArraySetNames (std::string prefixName)
	{				
		std::stringstream out;
		
		for(int i = 0; i < 56; i++)
		{			
			out << i;		
			buttonArray[i]->set_name(prefixName + "_" + out.str());
		}
	}
