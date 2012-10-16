/**
 * @file	DocumentOptions.h
 *
 * @brief	Declares the document options class.
 */

#ifndef DOCUMENTOPTIONS_H_
#define DOCUMENTOPTIONS_H_

#include <string>
#include <gtkmm.h>
#include <pangomm.h>
#include <qrencode.h>

#include <System/SafeBuffer.h>
#include <Graphics/Image/Compose.hxx>

namespace Smartmatic
{
namespace SAES {

namespace Printing
{

enum DocumentFontSize
{
	TinyFont,
	SmallFont,
	MediumFont,
	LargeFont,
	Biggest,
};

enum DocumentJustifitacion
{
	LeftJustified,
	Centered,
	RightJustified
};

enum DocumentFontStyle
{
	Normal = 0,
	Bold = 1,
	Italic = 2,
	Underlined = 4,
};

enum DocumentImageAlignmet
{
	Left,
	Center,
	Right,
	Expanded,
};

enum DocumentImageLayout
{
	InLineWithText,
	Exclusive
};

enum CellBorderType
{
	Border_None = 0,
	Border_Right = 1,
	Border_Left = 2,
	Border_Bottom = 4,
	Border_Top = 8,
	Border_All = Border_Right | Border_Left | Border_Bottom | Border_Top
};

/**
 * @class	DocumentTextOptions
 *
 * @brief	Document text options. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class DocumentTextOptions
{

public:

	/**
	 * @fn	DocumentTextOptions::DocumentTextOptions(DocumentFontSize fontSizeVal = MediumFont,
	 * 		DocumentJustifitacion justificationVal = LeftJustified,
	 * 		DocumentFontStyle fontStyleVal= Normal, int lineSpacingVal = -1,
	 * 		int indentationLevelVal = 0, int boldWeightVal = 700);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	fontSizeVal		   	The font size value.
	 * @param	justificationVal   	The justification value.
	 * @param	fontStyleVal	   	The font style value.
	 * @param	lineSpacingVal	   	The line spacing value.
	 * @param	indentationLevelVal	The indentation level value.
	 * @param	boldWeightVal	   	The bold weight value.
	 */

	DocumentTextOptions(DocumentFontSize fontSizeVal = MediumFont,
			DocumentJustifitacion justificationVal = LeftJustified,
			DocumentFontStyle fontStyleVal= Normal,
			int lineSpacingVal = -1,
			int indentationLevelVal = 0,
			int boldWeightVal = 700);

	/*DocumentTextOptions(DocumentTextOptions& copy);*/

	/**
	 * @fn	DocumentFontSize DocumentTextOptions::getFontSize();
	 *
	 * @brief	Gets the font size.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The font size.
	 */

	DocumentFontSize getFontSize();

	/**
	 * @fn	DocumentJustifitacion DocumentTextOptions::getJustification();
	 *
	 * @brief	Gets the justification.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The justification.
	 */

	DocumentJustifitacion getJustification();

	/**
	 * @fn	Pango::Alignment DocumentTextOptions::getGraphicAlignment();
	 *
	 * @brief	Gets the graphic alignment.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The graphic alignment.
	 */

	Pango::Alignment getGraphicAlignment();

	/**
	 * @fn	int DocumentTextOptions::getLineSpacing();
	 *
	 * @brief	Gets the line spacing.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The line spacing.
	 */

	int getLineSpacing();

	/**
	 * @fn	int DocumentTextOptions::getIndentationLevel();
	 *
	 * @brief	Gets the indentation level.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The indentation level.
	 */

	int getIndentationLevel();

	/**
	 * @fn	DocumentFontStyle DocumentTextOptions::getFontStyle();
	 *
	 * @brief	Gets the font style.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The font style.
	 */

	DocumentFontStyle getFontStyle();

	/**
	 * @fn	std::string& DocumentTextOptions::getFontFamily();
	 *
	 * @brief	Gets the font family.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The font family.
	 */

	std::string& getFontFamily();

	/**
	 * @fn	int DocumentTextOptions::getBoldWeight();
	 *
	 * @brief	Gets the bold weight.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The bold weight.
	 */

	int getBoldWeight();

	/**
	 * @fn	void DocumentTextOptions::setFontSize(DocumentFontSize val);
	 *
	 * @brief	Sets a font size.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setFontSize(DocumentFontSize  val);

	/**
	 * @fn	void DocumentTextOptions::setJustification(DocumentJustifitacion val);
	 *
	 * @brief	Sets a justification.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setJustification(DocumentJustifitacion  val);

	/**
	 * @fn	void DocumentTextOptions::setLineSpacing(int val);
	 *
	 * @brief	Sets a line spacing.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setLineSpacing(int  val);

	/**
	 * @fn	void DocumentTextOptions::setIndentationLevel(int val);
	 *
	 * @brief	Sets an indentation level.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setIndentationLevel(int val);

	/**
	 * @fn	void DocumentTextOptions::setFontStyle(DocumentFontStyle val);
	 *
	 * @brief	Sets a font style.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setFontStyle(DocumentFontStyle  val);

	/**
	 * @fn	void DocumentTextOptions::setFontFamily(std::string& val);
	 *
	 * @brief	Sets a font family.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	val	The value.
	 */

	void setFontFamily(std::string& val);

	/**
	 * @fn	void DocumentTextOptions::setBoldWeight(int val);
	 *
	 * @brief	Sets a bold weight.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void setBoldWeight(int val);

	/**
	 * @fn	void DocumentTextOptions::Indent(int val);
	 *
	 * @brief	Indents.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void Indent(int val);

	/**
	 * @fn	void DocumentTextOptions::UnIndent(int val);
	 *
	 * @brief	Un indent.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	val	The value.
	 */

	void UnIndent(int val);

private:

	std::string	fontFamily; ///< The font family
	DocumentFontSize fontSize;  ///< Size of the font
	DocumentJustifitacion justification;	///< The justification
	DocumentFontStyle fontStyle;	///< The font style
	int boldWeight; ///< The bold weight
	int lineSpacing;	///< The line spacing
	int indentationLevel;   ///< The indentation level
};


class ColumnLayoutOptions
{
public:

	ColumnLayoutOptions (int numColumns, double sepPercent)
	: m_NumColumns (numColumns)
	, m_SepPercent (sepPercent)
	{}

	~ColumnLayoutOptions ();

private:

	int m_NumColumns;
	int m_SepPercent;

};


/**
 * @class	TextContent
 *
 * @brief	Text content. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class TextContent
{
	//friend class BasePrintDocument;
public:

	/**
	 * @fn	TextContent::TextContent(std::list<Glib::ustring>& text,
	 * 		std::list<DocumentTextOptions>& textOptionList );
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	text		  	The text.
	 * @param [in,out]	textOptionList	List of text options.
	 */

	TextContent(std::list<Glib::ustring>& text,std::list<DocumentTextOptions>& textOptionList );
	/*TextContent(TextContent& copy);*/

	/**
	 * @fn	TextContent::~TextContent();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	~TextContent();

	/**
	 * @fn	std::list<Glib::ustring>& TextContent::getContent();
	 *
	 * @brief	Gets the content.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The content.
	 */

	std::list<Glib::ustring>& getContent();

	/**
	 * @fn	std::list<DocumentTextOptions>& TextContent::getContentOptions();
	 *
	 * @brief	Gets the content options.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The content options.
	 */

	std::list<DocumentTextOptions>& getContentOptions();
private:
	std::list<Glib::ustring> content;   ///< The content
	std::list<DocumentTextOptions> contentOptions;  ///< Options for controlling the content
};

/**
 * @class	ImageContent
 *
 * @brief	Image content. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class ImageContent
{
public:

	/**
	 * @fn	ImageContent::ImageContent( Glib::RefPtr<Gdk::Pixbuf> image ,
	 * 		Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment ,
	 * 		Smartmatic::SAES::Printing::DocumentImageLayout imgLayout = Exclusive ,
	 * 		CellBorderType border = Border_None , int leftPadding = 0 , int rightPadding = 0 ,
	 * 		int topPadding = 0 , int bottomPadding = 0);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	image		 	The image.
	 * @param	imgAligment  	The image aligment.
	 * @param	imgLayout	 	The image layout.
	 * @param	border		 	The border.
	 * @param	leftPadding  	The left padding.
	 * @param	rightPadding 	The right padding.
	 * @param	topPadding   	The top padding.
	 * @param	bottomPadding	The bottom padding.
	 */

	ImageContent() {};

	ImageContent(
			  Glib::RefPtr<Gdk::Pixbuf> image
			, Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment
			, Smartmatic::SAES::Printing::DocumentImageLayout imgLayout = Exclusive
			, CellBorderType border = Border_None
			, int leftPadding = 0
			, int rightPadding = 0
			, int topPadding = 0
			, int bottomPadding = 0);

	/**
	 * @fn	Glib::RefPtr<Gdk::Pixbuf> ImageContent::getImage();
	 *
	 * @brief	Gets the image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The image.
	 */

	Glib::RefPtr<Gdk::Pixbuf> getImage();

	/**
	 * @fn	Smartmatic::SAES::Printing::DocumentImageAlignmet ImageContent::getAligment();
	 *
	 * @brief	Gets the aligment.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The aligment.
	 */

	Smartmatic::SAES::Printing::DocumentImageAlignmet getAligment();

	/**
	 * @fn	Smartmatic::SAES::Printing::DocumentImageLayout ImageContent::getLauyout();
	 *
	 * @brief	Gets the lauyout.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The lauyout.
	 */

	Smartmatic::SAES::Printing::DocumentImageLayout getLauyout();

	/**
	 * @fn	CellBorderType ImageContent::getBorders ()
	 *
	 * @brief	Gets the borders.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The borders.
	 */

	CellBorderType getBorders () { return mBorder; }

	/**
	 * @fn	int ImageContent::getLeftPadding ()
	 *
	 * @brief	Gets the left padding.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The left padding.
	 */

	int getLeftPadding () {return mLeftPadding; }

	/**
	 * @fn	int ImageContent::getRightPadding ()
	 *
	 * @brief	Gets the right padding.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The right padding.
	 */

	int getRightPadding () {return mRightPadding;}

	/**
	 * @fn	int ImageContent::getTopPadding ()
	 *
	 * @brief	Gets the top padding.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The top padding.
	 */

	int getTopPadding () {return mTopPadding;}

	/**
	 * @fn	int ImageContent::getBottomPadding ()
	 *
	 * @brief	Gets the bottom padding.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The bottom padding.
	 */

	int getBottomPadding () {return mBottomPadding;}

protected:
	Glib::RefPtr<Gdk::Pixbuf> imageToShow;  ///< The image to show
	Smartmatic::SAES::Printing::DocumentImageAlignmet currentAligment;  ///< The current aligment
	Smartmatic::SAES::Printing::DocumentImageLayout currentImgLayout;   ///< The current image layout

	CellBorderType mBorder; ///< The border
	int mLeftPadding;   ///< The left padding
	int mRightPadding;  ///< The right padding
	int mTopPadding;	///< The top padding
	int mBottomPadding; ///< The bottom padding
};

class QRCodeContent : public ImageContent
{
public:

	QRCodeContent ()
	{};

	QRCodeContent (

			  const Smartmatic::System::SafeBuffer& data
			, gint pixelSize
			, gint margin
			, QRecLevel level
			, gint symbolVersion

			// Image parameters
			, Glib::RefPtr<Gdk::Pixbuf> backgroundImage

			, Smartmatic::SAES::Printing::DocumentImageAlignmet imgAligment = Left
			, Smartmatic::SAES::Printing::DocumentImageLayout imgLayout = Exclusive
			, CellBorderType border = Border_None
			, int leftPadding = 0
			, int rightPadding = 0
			, int topPadding = 0
			, int bottomPadding = 0

			// Image composing parameters
			, Smartmatic::Graphics::Image::PixbufComposer::ComposePosition position = Smartmatic::Graphics::Image::PixbufComposer::MIDDLE_CENTER
			)

	: ImageContent (backgroundImage, imgAligment, imgLayout, border, leftPadding, rightPadding, topPadding, bottomPadding)
	, mData (data)
	, mPixelSize (pixelSize)
	, mMargin (margin)
	, mLevel (level)
	, mSymbolVersion (symbolVersion)
	, mPositionInBackground (position)
	{ }

	const Smartmatic::System::SafeBuffer& getData () { return mData; }
	gint getPixelSize () { return mPixelSize; }
	gint getMargin () { return mMargin; }
	QRecLevel getCorrectionLevel () { return mLevel; }
	gint getVersion () { return mSymbolVersion; }
	Smartmatic::Graphics::Image::PixbufComposer::ComposePosition getPosInBackground () { return mPositionInBackground; }
	void SetImage (Glib::RefPtr<Gdk::Pixbuf> image) { this->imageToShow = image; }

private:

	Smartmatic::System::SafeBuffer mData;
	gint mPixelSize;
	gint mMargin;
	QRecLevel mLevel;
	gint mSymbolVersion;
	Smartmatic::Graphics::Image::PixbufComposer::ComposePosition mPositionInBackground;
};

/**
 * @class	SeparatorContent
 *
 * @brief	Separator content. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class SeparatorContent
{
public:

	/**
	 * @fn	SeparatorContent::SeparatorContent (double length, DocumentImageAlignmet alignment)
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	length   	The length.
	 * @param	alignment	The alignment.
	 */

	SeparatorContent (double length, DocumentImageAlignmet alignment)
	{
		mLength = length;
		mAlignment = alignment;
	}

	/**
	 * @fn	DocumentImageAlignmet SeparatorContent::getAlignment ()
	 *
	 * @brief	Gets the alignment.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The alignment.
	 */

	DocumentImageAlignmet getAlignment () {return mAlignment;}

	/**
	 * @fn	double SeparatorContent::getLength ()
	 *
	 * @brief	Gets the length.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	The length.
	 */

	double getLength () {return mLength;}

private:
	DocumentImageAlignmet mAlignment;   ///< The alignment
	double mLength; ///< The length
};


}}}


#endif /* DOCUMENTOPTIONS_H_ */
