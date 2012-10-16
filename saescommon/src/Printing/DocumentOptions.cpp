/*
 * DocumentOptions.cpp
 *
 *  Created on: Mar 7, 2011
 *      Author: freddyg
 */

#include "Printing/DocumentOptions.h"


using namespace Smartmatic::SAES::Printing;


DocumentTextOptions::DocumentTextOptions(DocumentFontSize fontSizeVal ,
		DocumentJustifitacion justificationVal ,
		DocumentFontStyle fontStyleVal,
		int lineSpacingVal ,
		int indentationLevelVal ,
		int boldWeightVal )
{
	fontFamily = "serif 10"; //use default. Get default from global configuration
	fontSize = fontSizeVal;
	justification = justificationVal;
	fontStyle = fontStyleVal;
	boldWeight = boldWeightVal;
	lineSpacing = lineSpacingVal;
	indentationLevel = indentationLevelVal;
}

/*DocumentTextOptions::DocumentTextOptions(DocumentTextOptions& copy)
{
	fontFamily = copy.getFontFamily();
	fontSize = copy.getFontSize();
	justification = copy.getJustification();
	fontStyle = copy.getFontStyle();
	boldWeight = copy.getBoldWeight();
	lineSpacing = copy.getLineSpacing();
	indentationLevel = copy.getLineSpacing();
}*/

DocumentFontSize DocumentTextOptions::getFontSize()
{
	return fontSize;
}
DocumentJustifitacion DocumentTextOptions::getJustification()
{
	return justification;
}

Pango::Alignment DocumentTextOptions::getGraphicAlignment()
{
	switch (justification)
	{
	case LeftJustified:
		return Pango::ALIGN_LEFT;
	case Centered:
		return Pango::ALIGN_CENTER;
	case RightJustified:
		return Pango::ALIGN_LEFT;
	}

	return Pango::ALIGN_LEFT;
}

int DocumentTextOptions::getLineSpacing()
{
	return lineSpacing;
}
int DocumentTextOptions::getIndentationLevel()
{
	return indentationLevel;
}
DocumentFontStyle DocumentTextOptions::getFontStyle()
{
	return fontStyle;
}
std::string& DocumentTextOptions::getFontFamily()
{
	return fontFamily;
}
int DocumentTextOptions::getBoldWeight()
{
	return boldWeight;
}

void DocumentTextOptions::setFontSize(DocumentFontSize  val)
{
	fontSize = val;
}
void DocumentTextOptions::setJustification(DocumentJustifitacion  val)
{
	justification = val;
}

void DocumentTextOptions::setLineSpacing(int  val)
{
	lineSpacing = val;
}
void DocumentTextOptions::setIndentationLevel(int val)
{
	indentationLevel = val;
}
void DocumentTextOptions::setFontStyle(DocumentFontStyle  val)
{
	fontStyle = val;
}
void DocumentTextOptions::setFontFamily(std::string& val)
{
	fontFamily = val;
}
void DocumentTextOptions::setBoldWeight(int val)
{
	boldWeight = val;
}

void DocumentTextOptions::Indent(int val)
{
	indentationLevel +=val;
}
void DocumentTextOptions::UnIndent(int val)
{
	indentationLevel -=val;
	if(indentationLevel<0)
		indentationLevel = 0;
}


TextContent::TextContent(std::list<Glib::ustring>& text,std::list<DocumentTextOptions>& textOptionList )
{

	std::_List_const_iterator<Glib::ustring> iterator = text.begin();
	while(iterator != text.end())
	{
		content.push_back(*iterator++);
	}
	std::_List_const_iterator<DocumentTextOptions> iteratorOptions = textOptionList.begin();
	while(iteratorOptions != textOptionList.end())
	{
		contentOptions.push_back(*iteratorOptions++);
	}

}

/*BasePrintDocument::TextContent::TextContent(BasePrintDocument::TextContent& copy)
{
	this->content = copy.content;
	this->contentOptions= copy.contentOptions;
}*/

TextContent::~TextContent()
{
	content.clear();
	contentOptions.clear();
}

std::list<Glib::ustring>& TextContent::getContent()
{
	return this->content;
}
std::list<DocumentTextOptions>& TextContent::getContentOptions()
{
	return this->contentOptions;
}




ImageContent::ImageContent(
		  Glib::RefPtr<Gdk::Pixbuf> image
		, Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment
		, Smartmatic::SAES::Printing::DocumentImageLayout imgLayout
		, CellBorderType border
        , int leftPadding
		, int rightPadding
		, int topPadding
		, int bottomPadding)
{
	imageToShow = image;
	currentAligment = imgAligment;
	currentImgLayout = imgLayout;
	mBorder = border;

	mLeftPadding = leftPadding;
	mRightPadding = rightPadding;
	mTopPadding = topPadding;
	mBottomPadding = bottomPadding;
}
Glib::RefPtr<Gdk::Pixbuf> ImageContent::getImage()
{
	return this->imageToShow;
}
Smartmatic::SAES::Printing::DocumentImageAlignmet ImageContent::getAligment()
{
	return this->currentAligment;
}
Smartmatic::SAES::Printing::DocumentImageLayout ImageContent::getLauyout()
{
	return this->currentImgLayout;
}



