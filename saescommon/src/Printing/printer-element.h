/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * MachineApplication
 * Copyright (C) Marcel Cordoví Solés 2010 <marcel.cordovi@smartmatic.com>
 *
 * @file	printer-element.h
 *
 * @brief	Declares the printer element class.
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

#ifndef _PRINTER_ELEMENT_H_
#define _PRINTER_ELEMENT_H_


#include <gtkmm.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class	PrinterElement
			 *
			 * @brief	Printer element. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class PrinterElement
			{
			public:

				/**
				 * @fn	PrinterElement::PrinterElement ()
				 *
				 * @brief	Default constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				PrinterElement();

				virtual ~PrinterElement();

				/**
				 * @fn	virtual void PrinterElement::render_element (const Glib::RefPtr<Gtk::PrintContext>& print_context) = 0;
				 *
				 * @brief	Renders the element described by print_context.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	print_context	Context for the print.
				 */

				virtual void render_element (const Glib::RefPtr<Gtk::PrintContext>& print_context) = 0;

				/**
				 * @fn	virtual double PrinterElement::get_length (const Glib::RefPtr<Gtk::PrintContext>& context) = 0;
				 *
				 * @brief	Gets a length.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	context	The context.
				 *
				 * @return	The length.
				 */

				virtual double get_length (const Glib::RefPtr<Gtk::PrintContext>& context) = 0;
				
	
			protected:

				Gtk::AlignmentEnum pe_alignment;	///< The pe alignment
				Gdk::Rectangle bounds;  ///< The bounds
				double pe_length;   ///< Length of the pe
				double pe_padding;  ///< The pe padding
	
			private:
	
			};
		}
	}
}

#endif // _PRINTER_ELEMENT_H_
