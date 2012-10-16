/**
 * @file	GraphicContextPrintingBackend.h
 *
 * @brief	Declares the graphic context printing backend class.
 */

#ifndef GRAPHICCONTEXTPRINTINGBACKEND_H_
#define GRAPHICCONTEXTPRINTINGBACKEND_H_

#include <queue>
#include <gtkmm.h>
#include <gdkmm.h>
#include <qrencode.h>

#include <System/SafeBuffer.h>
#include <System/Exception/QREncodingException.h>

#include "Printing/IPrintingBackend.h"
#include "Printing/DocumentOptions.h"
#include "Printing/GraphicContentPage.h"


namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}
	
namespace SAES
{

namespace Printing
{
/**
 * @class	GraphicContextPrintingBackend
 *
 * @brief	Graphic context printing backend. 
 *
 * @author	Cesar.bonilla
 * @date	4/28/2011
 */

class GraphicContextPrintingBackend : IPrintingBackend
{

public:


	// Lifecycle

	/**
	 * @fn	GraphicContextPrintingBackend::GraphicContextPrintingBackend ( const Cairo::RefPtr<Cairo::Context>& graphicCtx ,
	 * 		Glib::RefPtr<Pango::Context> destPangoContext , double renderAreaWidth )
	 *
	 * @brief	Constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	graphicCtx			Context for the graphic.
	 * @param	destPangoContext	Context for the destination pango.
	 * @param	renderAreaWidth 	Width of the render area.
	 */

	GraphicContextPrintingBackend (
			  Cairo::RefPtr<Cairo::Context> graphicCtx
			, Glib::RefPtr<Pango::Context> destPangoContext
			, double renderAreaWidth);

	GraphicContextPrintingBackend(
			  Cairo::RefPtr<Cairo::Context> cairoCtx
			, Glib::RefPtr<Pango::Context>  pangoCtx
			, double pageWidth
			, double pageHeight);

	/**
	 * @fn	virtual GraphicContextPrintingBackend::~GraphicContextPrintingBackend();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual ~GraphicContextPrintingBackend();


	GraphicContextPrintingBackend& operator= (const GraphicContextPrintingBackend& other);



	// IPrintingBackend implementation

	/**
	 * @fn	virtual void GraphicContextPrintingBackend::Init();
	 *
	 * @brief	Initialises this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void Init();

	/**
	 * @fn	virtual void GraphicContextPrintingBackend::End();
	 *
	 * @brief	Ends this object.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	virtual void End();

	/**
	 * @fn	void GraphicContextPrintingBackend::DrawString(std::list<Glib::ustring>& textContent ,
	 * 		std::list<DocumentTextOptions>& textContentOptionList);
	 *
	 * @brief	Draw string.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param [in,out]	textContent			 	The text content.
	 * @param [in,out]	textContentOptionList	List of text content options.
	 */

	void DrawString(std::list<Glib::ustring>& textContent
			, std::list<DocumentTextOptions>& textContentOptionList);

	/**
	 * @fn	void GraphicContextPrintingBackend::DrawImage (Glib::RefPtr<Gdk::Pixbuf> image);
	 *
	 * @brief	Draw image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	image	The image.
	 */

	void DrawImage (Glib::RefPtr<Gdk::Pixbuf> image);

	/**
	 * @fn	void GraphicContextPrintingBackend::DrawImage (ImageContent content);
	 *
	 * @brief	Draw image.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	content	The content.
	 */

	void DrawImage (ImageContent content);

	// gtkBackend owns

	/**
	 * @fn	void GraphicContextPrintingBackend::DrawLine (SeparatorContent line);
	 *
	 * @brief	Draw line.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	line	The line.
	 */

	void DrawLine (SeparatorContent line);

	void DrawQRCode (QRCodeContent qr)
		throw (Smartmatic::System::Exception::QREncodingException);

	/**
	 * @fn	double GraphicContextPrintingBackend::Height ()
	 *
	 * @brief	Gets the height.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	double Height (){return mPrintContextHeight;}

	/**
	 * @fn	double GraphicContextPrintingBackend::Width ()
	 *
	 * @brief	Gets the width.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @return	.
	 */

	double Width  (){return mPrintContextWidth;}


	int GetNumPages () { return (int)m_Pages.size(); }

	void RenderPage (Cairo::RefPtr<Cairo::Context> drawableCtx);

	void PreDrawString(
			  std::list<Glib::ustring>& textContent
			, std::list<DocumentTextOptions>& textContentOptions);

	bool PreDrawRow (
			  std::vector<Glib::ustring>::iterator pRowContent
			, std::vector<DocumentTextOptions> textContentOptions
			, int numCellsToRender);

	bool PreDrawImage(ImageContent content);

	void PreDrawQRCode (QRCodeContent qr)
	throw (Smartmatic::System::Exception::QREncodingException);

	bool PreDrawSeparator (SeparatorContent line);

	void PreJumpInlineImage ();

	void PreSetSingleColumn ();

	void PreSetDoubleColumn ();

	/**
	 * @fn	GraphicContextPrintingBackend::GraphicContextPrintingBackend();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	GraphicContextPrintingBackend();

protected:


private:

	static Smartmatic::Log::ISMTTLog* logger; /**<logger*/

	Glib::RefPtr<Gtk::PrintContext> mPrintContext;  ///< Context for the print
	Cairo::RefPtr<Cairo::Context> mCairoCtx;	///< Context for the cairo

	Pango::FontDescription mCurrentBlockFont;   ///< The current block font

	int mImageRightPadding; ///< The image right padding
	int mImageLeftPadding;  ///< The image left padding
	int mInlineImageBottomBorder;   ///< The inline image bottom border

	// print context related properties

	double mPrintContextWidth;  ///< Width of the print context
	double mPrintContextHeight; ///< Height of the print context

	Smartmatic::SAES::Printing::GraphicContentPage::ColumnModeEnumType m_CurrentColumnLayout;

	Glib::RefPtr<Pango::Context> mPrintPangoContext;	///< Context for the print pango


	// GraphicContentPage m_CurrentPage;
	std::queue<Smartmatic::SAES::Printing::GraphicContentPage> m_Pages;


	/**
	 * @fn	void GraphicContextPrintingBackend::mDrawRow ( std::vector<Glib::ustring>::iterator pRowContent ,
	 * 		std::vector<DocumentTextOptions> textContentOptions , int numCellsToRender);
	 *
	 * @brief	Draw row.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	pRowContent		  	The row content.
	 * @param	textContentOptions	Options for controlling the text content.
	 * @param	numCellsToRender  	Number of cells to renders.
	 */

	void mDrawRow (
			  std::vector<Glib::ustring>::iterator pRowContent
			, std::vector<DocumentTextOptions> textContentOptions
			, int numCellsToRender);

	/**
	 * @fn	void GraphicContextPrintingBackend::mApplyTextFormat ( Glib::RefPtr<Pango::Layout> textLayout ,
	 * 		DocumentTextOptions& options);
	 *
	 * @brief	Applies the text format.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 *
	 * @param	textLayout	   	The text layout.
	 * @param [in,out]	options	Options for controlling the operation.
	 */

	void mApplyTextFormat (
			  Glib::RefPtr<Pango::Layout> textLayout
			, DocumentTextOptions& options);

	/**
	 * @fn	void GraphicContextPrintingBackend::mSetRowMargin ();
	 *
	 * @brief	Ms the row margin.
	 *
	 * @author	Cesar.bonilla
	 * @date	4/28/2011
	 */

	void mSetRowMargin ();

	void mPreApplyTextFormat(
			  Glib::RefPtr<Pango::Layout> textLayout
			, DocumentTextOptions& options);

};

}

}

}

#endif /* GRAPHICCONTEXTPRINTINGBACKEND_H_ */
