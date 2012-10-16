/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
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

#include "label-configuration.h"
#include <iostream>

using namespace Smartmatic::GUI::Configuration;

LabelConfiguration::LabelConfiguration()
{
	labelAlignment = CenterAlignment;
	verticalPadding = 50;
	horizontalPadding = 150;
	fontFamily = "Verdana";
	style = NormalStyle;
	weight = NormalWeight;
	size = 20;
};

/*LabelConfiguration::LabelConfiguration(LabelConfiguration& x)
{
  this->labelAlignment = x.labelAlignment;
          this->verticalPadding = x.verticalPadding;
          this->horizontalPadding = x.horizontalPadding;
          this->fontFamily = x.fontFamily;
          this->style = x.style;
          this->weight = x.weight;
          this->size = x.size;
}*/

LabelConfiguration::LabelConfiguration(LabelAlignmentEnum labelAlignmentA, int verticalPaddingA, int horizontalPaddingA, 
                   std::string fontFamilyA, LabelStyleEnum styleA, LabelWeightEnum weightA,	int sizeA) 
{
	this->labelAlignment = labelAlignmentA;
	this->verticalPadding = verticalPaddingA;
	this->horizontalPadding = horizontalPaddingA;
	this->fontFamily = fontFamilyA;
	this->style = styleA;
	this->weight = weightA;
	this->size = sizeA;
};

LabelAlignmentEnum LabelConfiguration::GetLabelAlignment()
{
	return labelAlignment;
};

int LabelConfiguration::GetVerticalPadding()
{
	return verticalPadding;
};

int LabelConfiguration::GetHorizontalPadding()
{
	return horizontalPadding;
};

std::string LabelConfiguration::GetFontFamily()
{
	return fontFamily;
};

LabelStyleEnum LabelConfiguration::GetStyle()
{
	return style;
};

LabelWeightEnum LabelConfiguration::GetWeight()
{
	return weight;	
};

int LabelConfiguration::GetSize()
{
	return size;
};

void LabelConfiguration::SetLabelAlignment(LabelAlignmentEnum labelAlignmentA)
{
	labelAlignment = labelAlignmentA;
};

void LabelConfiguration::SetVerticalPadding(int verticalPaddingA)
{
	verticalPadding = verticalPaddingA;
};

void LabelConfiguration::SetHorizontalPadding(int horizontalPaddingA)
{
	horizontalPadding = horizontalPaddingA;
};

void LabelConfiguration::SetFontFamily(std::string forntFamilyA)
{
	fontFamily = forntFamilyA;
};

void LabelConfiguration::SetStyle(LabelStyleEnum styleA)
{
	style = styleA;
};

void LabelConfiguration::SetWeight(LabelWeightEnum weightA)
{
	weight = weightA;
};

void LabelConfiguration::SetSize(int sizeA)
{
	size = sizeA;
};

void LabelConfiguration::SetLabelConfiguration(Gtk::Label* label, LabelConfiguration& configuration)
{
	if(!label) return;
	
	label->set_padding(configuration.GetVerticalPadding(), configuration.GetHorizontalPadding());
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(configuration.GetSize()*Pango::SCALE);

	switch(configuration.GetStyle())
	{
		case Smartmatic::GUI::Configuration::NormalStyle:
		{
			fontTitle.set_style(Pango::STYLE_NORMAL);			
		}
		break;
		case Smartmatic::GUI::Configuration::ObliqueStyle:
		{
			fontTitle.set_style(Pango::STYLE_OBLIQUE);		
		}
		break;
		case Smartmatic::GUI::Configuration::ItalicStyle:
		{
			fontTitle.set_style(Pango::STYLE_ITALIC);		
		}
		break;
	}

	switch(configuration.GetWeight())
	{
		case Smartmatic::GUI::Configuration::LightWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_LIGHT);			
		}
		break;
		case Smartmatic::GUI::Configuration::NormalWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_NORMAL);		
		}
		break;
		case Smartmatic::GUI::Configuration::BoldWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_BOLD);		
		}
		break;
	}

	fontTitle.set_family(configuration.GetFontFamily());

	switch(configuration.GetLabelAlignment())
	{
		case Smartmatic::GUI::Configuration::LeftAlignment:
		{
			label->set_alignment(0, 0.5);			
		}
		break;
		case Smartmatic::GUI::Configuration::CenterAlignment:
		{
			label->set_alignment(0.5, 0.5);		
		}
		break;
		case Smartmatic::GUI::Configuration::RigthAlignment:
		{
			label->set_alignment(1, 0.5);		
		}
		break;
	}
	
	label->modify_font(fontTitle);
}

void LabelConfiguration::SetLabelConfigurationWithoutAlignment(Gtk::Label* label, Smartmatic::GUI::Configuration::LabelConfiguration& configuration)
{
	if(!label) return;	
	
	label->set_padding(configuration.GetVerticalPadding(), configuration.GetHorizontalPadding());
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(configuration.GetSize()*Pango::SCALE);

	switch(configuration.GetStyle())
	{
		case Smartmatic::GUI::Configuration::NormalStyle:
		{
			fontTitle.set_style(Pango::STYLE_NORMAL);			
		}
		break;
		case Smartmatic::GUI::Configuration::ObliqueStyle:
		{
			fontTitle.set_style(Pango::STYLE_OBLIQUE);		
		}
		break;
		case Smartmatic::GUI::Configuration::ItalicStyle:
		{
			fontTitle.set_style(Pango::STYLE_ITALIC);		
		}
		break;
	}

	switch(configuration.GetWeight())
	{
		case Smartmatic::GUI::Configuration::LightWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_LIGHT);			
		}
		break;
		case Smartmatic::GUI::Configuration::NormalWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_NORMAL);		
		}
		break;
		case Smartmatic::GUI::Configuration::BoldWeight:
		{
			fontTitle.set_weight(Pango::WEIGHT_BOLD);		
		}
		break;
	}

	fontTitle.set_family(configuration.GetFontFamily());
	
	label->modify_font(fontTitle);
};














