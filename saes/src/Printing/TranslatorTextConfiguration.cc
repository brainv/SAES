/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saes
 * Copyright (C)  2011 <>
 * 
 * saes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TranslatorTextConfiguration.h"

using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;

DocumentTextOptions TranslatorTextConfiguration::TextConfigurationToDocumentTextOptions(TextConfiguration textConfiguration)
{
	//TextConfiguration
	int size = textConfiguration.getSize ();
	AlignType alignType = textConfiguration.getAlign();
	bool bold = textConfiguration.getBold();
	bool italic = textConfiguration.getItalic();
	// TODO pasar a configuracion
	bool underline = false;
	int vPandding = textConfiguration.getVPandding();
	//int hPandding = textConfiguration.getHPandding();
	int levelPaddin = textConfiguration.getLevelPaddingSpaceChar();
	
	
	DocumentFontSize documentFontSize = TinyFont;
	DocumentJustifitacion documentJustifitacion = LeftJustified;
	DocumentFontStyle documentFontStyle = Normal;
	int lineSpacingVal = vPandding;
	int indentationLevelVal = levelPaddin;
	int boldWeightVal = 700;

	// FONT SIZE
	switch(size)
	{
		case 5:
		case 6:
			documentFontSize = TinyFont;
			break;
		case 7:
		case 8:	
			documentFontSize = SmallFont;
			break;
		case 9:
		case 10:
			documentFontSize = MediumFont;
			break;
		case 11:
		case 12:
			documentFontSize = LargeFont;
			break;
		default:
			if(size < 5)
				documentFontSize = TinyFont;
				
			if(size > 12)
				documentFontSize = Biggest;
			break;
	}
	// ALIGN
	switch(alignType)
	{
		case AlignType::CONFIGURATION_CENTER:
			documentJustifitacion = Centered;
			break;
		case AlignType::CONFIGURATION_LEFT:
			documentJustifitacion = LeftJustified;
			break;
		case AlignType::CONFIGURATION_RIGHT:
			documentJustifitacion = RightJustified;
			break;			
	}

	//STYLE
	if(bold)
		documentFontStyle = static_cast<DocumentFontStyle>(documentFontStyle | Bold);
	if(italic)
		documentFontStyle = static_cast<DocumentFontStyle>(documentFontStyle | Italic);
	if(underline)
		documentFontStyle = static_cast<DocumentFontStyle>(documentFontStyle | Underlined);

		
	DocumentTextOptions documentTextOptions(documentFontSize,documentJustifitacion,documentFontStyle,lineSpacingVal,indentationLevelVal,boldWeightVal);
	return documentTextOptions;
}

