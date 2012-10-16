/*
 * SmartmaticTextView.h
 *
 *  Created on: Jul 23, 2011
 *      Author: Juan.Delgado
 */

#ifndef SMARTMATICTEXTVIEW_H_
#define SMARTMATICTEXTVIEW_H_

#include <gtkmm.h>
#include "ISmartmaticText.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class SmartmaticTextView: public Gtk::ScrolledWindow, public ISmartmaticText
			{
			public:
				/**
				 * @brief	Constructor.
				 *
				 * @author	Juan.Delgado
				 * @date	23/07s/2011
				 */
				SmartmaticTextView();

				/**
				 * @brief	Constructor.
				 *
				 * @author	Juan.Delgado
				 * @date	23/07s/2011
				 *
				 * @param [in,out]	cobject	If non-null, the cobject.
				 * @param	refBuilder	   	The reference builder.
				 */
				SmartmaticTextView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder=Gtk::Builder::create());

				/**
				 * @brief	Finalizer.
				 *
				 * @author	Juan.Delgado
				 * @date	23/07s/2011
				 */
				virtual ~SmartmaticTextView();

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

				Gtk::TextView * textView; ///< text view
				Glib::RefPtr<Gtk::TextBuffer> textBuffer; ///< text buffer

				/**
				 * @brief Method initialize
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void initialize();

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
				 * @param a iterator
				 * @param b string
				 * @param c position
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void insertText(const Gtk::TextBuffer::iterator& a, const Glib::ustring& b, int c);
				/**
				 * @brief method validate delete text
				 * @param a iterator
				 * @param b iterator
				 * @date 03/06/2012
				 * @author Yadickson Soto
				 */
				void deleteText(const Gtk::TextBuffer::iterator& a, const Gtk::TextBuffer::iterator& b);
			};
		}
	}
}

#endif /* SMARTMATICTEXTVIEW_H_ */
