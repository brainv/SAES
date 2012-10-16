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

#ifndef _SMARTMATIC_ENTRY_H_

/**
 * @brief	Gets the smartmatic entry h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _SMARTMATIC_ENTRY_H_

#include <gtkmm.h>
#include "ISmartmaticText.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticEntry: public Gtk::Entry, public ISmartmaticText
			{
			public:

				/**
				 * @brief	Values that represent EntryType. 
				 */

				enum EntryType
				{
					Alphabetic, ///< Value that represent an alphabetic entry. 
					Decimal,	///< Value that represent a decimal entry. 
					AlphaNumeric,   ///< Value that represent an alphanumeric entry. 
					All, ///< Value that represent whatever entry.
					AllWithoutNumber, ///< Value that represent whatever entry without number.
					AllWithoutAlphabetic, ///< Value that represent whatever entry without alphabetic.
					Mask ///< Mask
				};

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type	The type.
				 */

				SmartmaticEntry(EntryType type = All);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	cobject	If non-null, the cobject.
				 * @param	refBuilder	   	The reference builder.
				 */

				SmartmaticEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder=Gtk::Builder::create());

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				virtual ~SmartmaticEntry();

				/**
				 * @brief	Set entry type.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	type	Type of.
				 */

				void SetType(EntryType type);

				/**
				 * @brief	Sets a number.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	number	Number of.
				 */

				void SetNumber(int number);

				/**
				 * @brief	Gets a number.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	number	Number of.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool GetNumber(int& number);

				typedef sigc::signal<void> text_inserted;

				text_inserted signal_inserted();

				void setPosition(unsigned int pos);
				unsigned int getPosition();

				/**
				 * @brief Method setter text
				 * @param text text
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setText(std::string text);
				/**
				 * @brief Method getter text
				 * @return text
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual std::string getText();
				/**
				 * @brief	Set entry max elements
				 * @param	max max
				 * @author	Yadickson Soto
				 * @date	04/05/2012
				 */
				virtual void setMax(int max);
				/**
				 * @brief Method set background error
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setBGError();
				/**
				 * @brief method set bg normal
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				virtual void setBGNormal();

			protected:
				text_inserted m_signal_inserted;   ///< The ballot clicked

				/**
				 * @brief method initialize
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void initialize();
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

				/**
				 * @brief	Deletes the left zero
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */
				bool DeleteLeftZero();

				EntryType type; ///< The type
				unsigned int pos;

				/**
				 * @brief	Focus in event
				 *
				 * @author	Juan.Delgado
				 * @date	08/07/2011
				 * @param	event				The event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */
				bool on_focus_in_event(GdkEventFocus * event);

				/**
				 * @brief	Handles on button press event
				 *
				 * @author	Juan.Delgado
				 * @date	23/07/2011
				 * @param	event			The event.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */
				virtual bool on_button_press_event(GdkEventButton* event);

				virtual bool on_key_press_event(GdkEventKey* event);
				/**
				 * @brief method validate change text
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void changeText();
				/**
				 * @brief method validate insert text
				 * @param text text
				 * @param position position
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void insertText(const Glib::ustring& text, int* position);
				/**
				 * @brief method validate delete text
				 * @param i
				 * @param j
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void deleteText(int i, int j);
			};
		}
	}
}

#endif // _SMARTMATIC_ENTRY_H_
