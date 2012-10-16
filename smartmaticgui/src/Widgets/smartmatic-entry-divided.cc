/**
 * @file smartmatic-entry-divided.cc
 * @brief Body smartmatic entry divided
 * @date 27/04/2011
 * @author Juan Delgado
 */

#include "smartmatic-entry-divided.h"
#include "smartmatic-entry.h"
#include <iostream>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"

using namespace Smartmatic::GUI::Widgets;

SmartmaticEntryDivided::SmartmaticEntryDivided(int divisions, int maxChar, int width, bool visibility)
:Glib::ObjectBase("SmartmaticEntryDivided"), Gtk::HBox()
{
	this->divisions = divisions;
	this->maxChar = maxChar;
	this->currentEntry = 0;

	current.clear();
	entriesVector.clear();

	inputType = Smartmatic::GUI::Configuration::SMTTGUIConfigurationManager::Current()->getEntryConfiguration();

	for(int i = 0; i < divisions; i++)
	{
		SmartmaticEntry* smttEntry = manage(new SmartmaticEntry());
		smttEntry->setMax(maxChar);
		smttEntry->signal_key_release_event().connect(sigc::mem_fun(*this, &SmartmaticEntryDivided::on_my_insert_at_cursor));
		smttEntry->signal_focus_in_event().connect(sigc::mem_fun(*this, &SmartmaticEntryDivided::on_my_focus_cursor));
		smttEntry->set_visibility(visibility);
		smttEntry->set_size_request(width, -1);

		Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::Value getEntryConfiguration();

		g_signal_connect((gpointer) smttEntry->gobj(), "paste-clipboard", G_CALLBACK(SmartmaticEntryDivided::on_clipboard_received), this);

		if(inputType != Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::CONFIGURATION_CASESENSITIVE)
		{
			Glib::PropertyProxy<bool> caps = smttEntry->property_caps_lock_warning();
			caps = false;
		}

		pack_start(*smttEntry, false, false);

		entriesVector.push_back(smttEntry);
	}

	if (divisions > 0)
	{
		iter = entriesVector.begin();
		(*iter)->grab_focus();
	}

	set_spacing(7);
	show_all_children();
}

bool SmartmaticEntryDivided::on_my_insert_at_cursor(GdkEventKey * event)
{
	if (currentEntry < divisions - 1)
	{
		this->currentEntry = currentEntry;
		Glib::ustring toCompare = entriesVector[currentEntry]->get_text();

		if((int)toCompare.size() == maxChar)
		{
			entriesVector[currentEntry + 1]->grab_focus();
		}
	}

	return true;
}

bool SmartmaticEntryDivided::on_my_focus_cursor(GdkEventFocus * event)
{
	for (unsigned int i = 0; i < entriesVector.size(); i++)
	{
		if (entriesVector[i]->is_focus())
		{
			currentEntry = i;
			break;
		}
	}

	return true;
}

SmartmaticEntryDivided::~SmartmaticEntryDivided()
{

}

Glib::ustring SmartmaticEntryDivided::GetText()
{
	Glib::ustring toReturn ="";

	for(iter = entriesVector.begin(); iter != entriesVector.end(); iter++)
	{
		toReturn.append((*iter)->get_text());
	}

	if(inputType == Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::CONFIGURATION_LOWERCASE)
		toReturn = toReturn.lowercase();
	else if(inputType == Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::CONFIGURATION_UPPERCASE)
		toReturn = toReturn.uppercase();

	return toReturn;
}

void SmartmaticEntryDivided::Clean()
{
	for(iter = entriesVector.begin(); iter != entriesVector.end(); iter++)
	{
		(*iter)->set_text("");
	}
}

int SmartmaticEntryDivided::getCurrentPos()
{
	return currentEntry;
}

int SmartmaticEntryDivided::getMaxChar()
{
	return maxChar;
}

std::vector <SmartmaticEntry * > & SmartmaticEntryDivided::getEntriesVector()
{
	return entriesVector;
}

void SmartmaticEntryDivided::on_clipboard_received(GtkEntry *entry, gpointer user_data)
{
	if (Gtk::Clipboard::get()->wait_is_text_available())
	{
		SmartmaticEntryDivided * parent = (SmartmaticEntryDivided*)user_data;
		std::string text = Gtk::Clipboard::get()->wait_for_text();
		unsigned int current = parent->getCurrentPos();

		for (unsigned int i = current; i >=0 && i < parent->getEntriesVector().size(); i++)
		{
			if ((unsigned int)text.length() >= (unsigned int)parent->getMaxChar())
			{
				std::string input = text.substr(0, parent->getMaxChar());
				gtk_entry_set_text(parent->getEntriesVector()[i]->gobj(), input.c_str());
				parent->getEntriesVector()[i]->grab_focus();
				text = text.substr(parent->getMaxChar());
			}
		}
	}
}
