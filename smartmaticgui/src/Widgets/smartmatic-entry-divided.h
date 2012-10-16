/**
 * @file smartmatic-entry-divided.h
 * @brief Header smartmatic entry divided
 * @date 27/04/2011
 * @author Juan Delgado
 */

#ifndef _SMARTMATIC_ENTRY_DIVIDED_H_
#define _SMARTMATIC_ENTRY_DIVIDED_H_

#include <gtkmm.h>
#include "Configuration/SmartmaticGUIConfiguration-schema.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticEntry;

			/**
			 * @class SmartmaticEntryDivided
			 * @brief Class entry divided
			 * @date 27/03/2012
			 * @author Yadickson Soto
			 */
			class SmartmaticEntryDivided: public Gtk::HBox
			{
			public:

				/**
				 * @brief	Constructor.
				 * @param	divisions Total divisions
				 * @param	maxChar	maximun chars in every entry.
				 * @param	width width of every entry.
				 * @param visibility flag visibility char
				 * @date	27/03/2012
				 * @author	Yadickson Soto
				 */
				SmartmaticEntryDivided(int divisions, int maxChar, int width = -1, bool visibility = false);
				/**
				 * @brief Class destroy
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				virtual ~SmartmaticEntryDivided();
				/**
				 * @brief Method getter text
				 * @return text
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				Glib::ustring GetText();
				/**
				 * @brief Method clear all entry
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				void Clean();
				/**
				 * @brief Method getter current entry pos
				 * @return current entry pos
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				int getCurrentPos();
				/**
				 * @brief Method getter max char
				 * @return max char
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				int getMaxChar();
				/**
				 * @brief Method getter entries
				 * @return entries
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				std::vector<SmartmaticEntry*> & getEntriesVector();

			protected:
				
				Glib::ustring current; ///< current text

				int divisions;	///< The maximum
				int maxChar;	///< The minimum
				int currentEntry; ///< current cursor pos

				std::vector<SmartmaticEntry*> entriesVector; ///< entries
				std::vector<SmartmaticEntry*>::iterator iter; ///< iterator

				Smartmatic::GUI::Configuration::EntryPassPhraseConfiguration::Value inputType; ///< input type

				/**
				 * @brief Method manager insert cursor in entry
				 * @param event event cursor entry pos
				 * @return result event (true)
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				bool on_my_insert_at_cursor(GdkEventKey * event);
				/**
				 * @brief Method manager getter focus entry
				 * @param event event cursor entry pos
				 * @return result event (true)
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				bool on_my_focus_cursor(GdkEventFocus * event);
				/**
				 * @brief Method manager event clipboard reveived
				 * @param entry element entry
				 * @param user_data user data
				 * @date 27/03/2012
				 * @author Yadickson Soto
				 */
				static void on_clipboard_received(GtkEntry *entry, gpointer user_data);
			};
		}
	}
}

#endif // _SMARTMATIC_ENTRY_DIVIDED_H_
