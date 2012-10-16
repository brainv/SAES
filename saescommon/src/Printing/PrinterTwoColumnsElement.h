/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saescommon
 * Copyright (C)  SmartMatic 2011 <>
 * 
 * @file	PrinterTwoColumnsElement.h
 *
 * @brief	Declares the printer two columns element class.
 * 
 * saescommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saescommon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PRINTER_TWO_COLUMS_ELEMENT_H_
#define _PRINTER_TWO_COLUMS_ELEMENT_H_

#include "printer-element.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace Printing
		{
			/**
			 * @class	PrinterTwoColumnsElement
			 *
			 * @brief	Printer two columns element. 
			 *
			 * @author	Cesar.bonilla
			 * @date	4/28/2011
			 */

			class PrinterTwoColumnsElement : public PrinterElement
			{
				public:

					/* constructors */

					/**
					 * @fn	PrinterTwoColumnsElement::PrinterTwoColumnsElement ()
					 *
					 * @brief	Default constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					PrinterTwoColumnsElement (): PrinterElement ()
					{
						_height =0;
						_fontSize = 8;
						_wrap = Pango::WRAP_WORD_CHAR;
						_stretch = Pango::STRETCH_NORMAL;
						_weight = Pango::WEIGHT_NORMAL;
						_style = Pango::STYLE_NORMAL;
						_variant = Pango::VARIANT_NORMAL;
						
						_hPadding = 0;
						pe_alignment = Gtk::ALIGN_LEFT;
						_spacing = 1;

						_fontFamilyNoSize = ((*Smartmatic::SAES::Common::Configuration::SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter()).getDefaultPrinterFontFamily();
						std::stringstream s;
						s << _fontFamilyNoSize << " " << _fontSize;
						_fontFamily = s.str ();
					}

					/* interface implementation */

					/**
					 * @fn	virtual void PrinterTwoColumnsElement::render_element ( const Glib::RefPtr<Gtk::PrintContext>& print_context);
					 *
					 * @brief	Renders the element described by print_context.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	print_context	Context for the print.
					 */

					virtual void render_element (
						const Glib::RefPtr<Gtk::PrintContext>& print_context);

					/**
					 * @fn	virtual double PrinterTwoColumnsElement::get_length ( const Glib::RefPtr<Gtk::PrintContext>& context);
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

					virtual double get_length (
						const Glib::RefPtr<Gtk::PrintContext>& context);
					


					/* access methods */

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontFamily (const Glib::ustring& font_family);
					 *
					 * @brief	Sets a font family.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	font_family	The font family.
					 */

					void setFontFamily (const Glib::ustring& font_family);

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontStretch (Pango::Stretch stretch)
					 *
					 * @brief	Sets a font stretch.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	stretch	The stretch.
					 */

					void setFontStretch (Pango::Stretch stretch) { this->_stretch  = stretch; }

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontVariant (Pango::Variant variant)
					 *
					 * @brief	Sets a font variant.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	variant	The variant.
					 */

					void setFontVariant (Pango::Variant variant) { this->_variant  = variant; }

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontWeight (Pango::Weight weight)
					 *
					 * @brief	Sets a font weight.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	weight	The weight.
					 */

					void setFontWeight (Pango::Weight weight)    { this->_weight   = weight;  }

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontStyle (Pango::Style style)
					 *
					 * @brief	Sets a font style.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	style	The style.
					 */

					void setFontStyle (Pango::Style style)       { this->_style    = style;   }

					/**
					 * @fn	void PrinterTwoColumnsElement::setWrapMode (Pango::WrapMode wrap)
					 *
					 * @brief	Sets a wrap mode.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	wrap	The wrap.
					 */

					void setWrapMode (Pango::WrapMode wrap)      { this->_wrap     = wrap;    }

					/**
					 * @fn	void PrinterTwoColumnsElement::setFontSize(const int fontSize);
					 *
					 * @brief	Sets a font size.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	fontSize	Size of the font.
					 */

					void setFontSize(const int fontSize);

					/**
					 * @fn	const int PrinterTwoColumnsElement::getFontSize();
					 *
					 * @brief	Gets the font size.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The font size.
					 */

					const int getFontSize();

					/**
					 * @fn	void PrinterTwoColumnsElement::setHPadding(const int hPadding);
					 *
					 * @brief	Sets a h padding.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	hPadding	The padding.
					 */

					void setHPadding(const int hPadding);

					/**
					 * @fn	const int PrinterTwoColumnsElement::getHPadding();
					 *
					 * @brief	Gets the h padding.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The h padding.
					 */

					const int getHPadding();

					/**
					 * @fn	void PrinterTwoColumnsElement::setSpacing(const int Spacing);
					 *
					 * @brief	Sets a spacing.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	Spacing	The spacing.
					 */

					void setSpacing(const int Spacing);

					/**
					 * @fn	const int PrinterTwoColumnsElement::getSpacing();
					 *
					 * @brief	Gets the spacing.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The spacing.
					 */

					const int getSpacing();

					/**
					 * @fn	void PrinterTwoColumnsElement::setAlignment(Gtk::AlignmentEnum alignment);
					 *
					 * @brief	Sets an alignment.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	alignment	The alignment.
					 */

					void setAlignment(Gtk::AlignmentEnum alignment);

					/**
					 * @fn	Gtk::AlignmentEnum PrinterTwoColumnsElement::getAlignment();
					 *
					 * @brief	Gets the alignment.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The alignment.
					 */

					Gtk::AlignmentEnum getAlignment();

					/**
					 * @fn	Glib::ustring& PrinterTwoColumnsElement::getFontFamily ()
					 *
					 * @brief	Gets the font family.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The font family.
					 */

					Glib::ustring& getFontFamily () { return this->_fontFamily; }

					/**
					 * @fn	Glib::ustring& PrinterTwoColumnsElement::getContentFirstColumn ()
					 *
					 * @brief	Gets the content first column.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The content first column.
					 */

					Glib::ustring& getContentFirstColumn () { return this->_contentFirstColumn; }

					/**
					 * @fn	Glib::ustring& PrinterTwoColumnsElement::getContentSecondColumn ()
					 *
					 * @brief	Gets the content second column.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The content second column.
					 */

					Glib::ustring& getContentSecondColumn () { return this->_contentSecondColumn; }

					/**
					 * @fn	void PrinterTwoColumnsElement::setContentFirstColumn(Glib::ustring contentFirstColumn)
					 *
					 * @brief	Sets a content first column.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	contentFirstColumn	The content first column.
					 */

					void setContentFirstColumn(Glib::ustring contentFirstColumn){_contentFirstColumn = contentFirstColumn;}

					/**
					 * @fn	void PrinterTwoColumnsElement::setContentSecondColumn(Glib::ustring contentSecondColumn)
					 *
					 * @brief	Sets a content second column.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	contentSecondColumn	The content second column.
					 */

					void setContentSecondColumn(Glib::ustring contentSecondColumn){_contentSecondColumn = contentSecondColumn;}
					
		
				protected:

				private:

					/* auxiliars */

					/**
					 * @fn	void PrinterTwoColumnsElement::setLayoutSettings ();
					 *
					 * @brief	Sets the layout settings.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					void setLayoutSettings ();

					/* fields */
		
					Glib::RefPtr<Pango::Layout> _textLayoutFirstColum;  ///< The text layout first colum
					Glib::RefPtr<Pango::Layout> _textLayoutSecondColum; ///< The text layout second colum
					Glib::ustring _contentFirstColumn;  ///< The content first column
					Glib::ustring _contentSecondColumn; ///< The content second column
					Glib::ustring _fontFamily;  ///< The font family
					Glib::ustring _fontFamilyNoSize;	///< Size of the font family no
					double _height; ///< The height
					int _fontSize;  ///< Size of the font
					int _spacing;   ///< The spacing
					int _hPadding;  ///< The padding
					Pango::WrapMode _wrap;  ///< The wrap
					Pango::Stretch  _stretch;   ///< The stretch
					Pango::Weight   _weight;	///< The weight
					Pango::Style    _style; ///< The style
					Pango::Variant  _variant;   ///< The variant
			};
		}
	}
}

#endif // _PRINTER_TWO_COLUMS_ELEMENT_H_
