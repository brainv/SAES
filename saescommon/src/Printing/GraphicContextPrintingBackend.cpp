/**
 * @file GraphicContextPrintingBackend.cpp
 * @brief Body class graphic context printing backend
 * @date 12/03/2011
 * @author Marcel Cordovi
 */

#include <iostream>
#include "Printing/GraphicContextPrintingBackend.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"
#include <Graphics/Encoding2D/QREncoding.h>
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate


#define LINE_SEP_WIDTH 2.0

using namespace std;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::System;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Graphics::Encoding2D;


ISMTTLog* GraphicContextPrintingBackend::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.Printing.GraphicContextPrintingBackend",GETTEXT_PACKAGE);



//============= LIFE CYCLE ===============


/**
 * Creates backend
 */
GraphicContextPrintingBackend::GraphicContextPrintingBackend()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	mImageRightPadding = 0;
	mImageLeftPadding = 0;
	mInlineImageBottomBorder = 0;
	mPrintContextWidth = 0;
}

GraphicContextPrintingBackend::GraphicContextPrintingBackend (
		  Cairo::RefPtr<Cairo::Context> graphicCtx
		, Glib::RefPtr<Pango::Context> destPangoContext
		, double renderAreaWidth
		)
{
	logger->Debug("Create GraphicContextPrintingBackend");

    mCairoCtx = graphicCtx;
    mPrintContextWidth = renderAreaWidth;
    mPrintContextHeight = 0;
	mPrintPangoContext = destPangoContext;

	mImageRightPadding = 0;
	mImageLeftPadding = 0;
	mInlineImageBottomBorder = 0;

	m_CurrentColumnLayout = GraphicContentPage::GCPAGE_SINGLE_COLUMN;
}

GraphicContextPrintingBackend::GraphicContextPrintingBackend(
		  Cairo::RefPtr<Cairo::Context> cairoCtx
		, Glib::RefPtr<Pango::Context>  pangoCtx
		, double pageWidth
		, double pageHeight)
{
	logger->Debug("Create GraphicContextPrintingBackend");

	mImageRightPadding = 0;
	mImageLeftPadding = 0;
	mInlineImageBottomBorder = 0;

	mPrintContextWidth  = pageWidth;
	mPrintContextHeight = pageHeight;

	m_CurrentColumnLayout = GraphicContentPage::GCPAGE_SINGLE_COLUMN;

	mCairoCtx = cairoCtx;
	mPrintPangoContext = pangoCtx;
	//mPrintPangoContext->update_from_cairo_context (mCairoCtx);

	GraphicContentPage new_page (pageWidth, pageHeight);
	m_Pages.push (new_page);
}

GraphicContextPrintingBackend& GraphicContextPrintingBackend::operator= (const GraphicContextPrintingBackend& other)
{
	if (this != &other)
	{
		logger->Debug("Start copy GraphicContextPrintingBackend");

		mPrintContext = other.mPrintContext;
		mCairoCtx = other.mCairoCtx;

		mCurrentBlockFont = other.mCurrentBlockFont;

		mImageRightPadding = other.mImageRightPadding;
		mImageLeftPadding = other.mImageLeftPadding;
		mInlineImageBottomBorder = other.mInlineImageBottomBorder;

		mPrintContextWidth = other.mPrintContextWidth;
		mPrintContextHeight = other.mPrintContextHeight;

		mPrintPangoContext = other.mPrintPangoContext;

		//m_CurrentPage = other.m_CurrentPage;
		m_Pages = other.m_Pages;
	}

	return *this;
}

GraphicContextPrintingBackend::~GraphicContextPrintingBackend()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
}




//===================== IPRINTINGBACKEND IMPLEMENTATION ======================//


void GraphicContextPrintingBackend::Init()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
}

void GraphicContextPrintingBackend::End()
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	/*
	double cursor_x, cursor_y;

	mCairoCtx->get_current_point(cursor_x, cursor_y);
	mPrintContextHeight = cursor_y;*/
	
}

void GraphicContextPrintingBackend::DrawLine (SeparatorContent line)
{
	double cursor_x, cursor_y, align_x, end_x;
	end_x = 0.0;
	align_x = 0.0;

	mCairoCtx->set_source_rgb(0, 0, 0);
	mCairoCtx->get_current_point(cursor_x, cursor_y);

	switch (line.getAlignment())
	{
	case Left:
		align_x = cursor_x;
		end_x = line.getLength();
		break;
	case Center:
		align_x = (mPrintContextWidth - line.getLength()) / 2;
		end_x = align_x + line.getLength();
		break;
	case Right:
		align_x = mPrintContextWidth - line.getLength();
		end_x = mPrintContextWidth;
		break;
	case Expanded:
		align_x = 0;
		end_x = mPrintContextWidth;
		break;
	}

	mCairoCtx->set_line_width (LINE_SEP_WIDTH);
	mCairoCtx->move_to (align_x, cursor_y);
	mCairoCtx->line_to (end_x, cursor_y);
	mCairoCtx->stroke ();

	mCairoCtx->move_to (0, cursor_y + LINE_SEP_WIDTH);
}

/**
 * Controls the rendering order and position of text content units as cells in
 * graphic context.
 */
void GraphicContextPrintingBackend::DrawString(
		  std::list<Glib::ustring>& textContent
		, std::list<DocumentTextOptions>& textContentOptions)
{
	int cells_per_row = textContentOptions.size();
	int cells_in_table = textContent.size();
	int cells_rendered = 0;
	int cells_to_render = 0;

	std::vector<DocumentTextOptions> text_options (textContentOptions.begin(), textContentOptions.end());
	std::vector<Glib::ustring> text_content (textContent.begin(), textContent.end());
	std::vector<Glib::ustring>::iterator it = text_content.begin();

	while (it != text_content.end())
	{
		cells_to_render =
				  cells_rendered + cells_per_row <= cells_in_table
				? cells_per_row
				: cells_in_table % cells_per_row;

		mSetRowMargin ();
		mDrawRow (it, text_options, cells_to_render);

		cells_rendered += cells_to_render;
		it += cells_to_render;
	}
}

/**
 * When no layout info is provided the image is printed aligned to the
 * right with the non "text inline" layout option.
 */
void GraphicContextPrintingBackend::DrawImage(Glib::RefPtr<Gdk::Pixbuf> image)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	if (mCairoCtx)
	{
		double cursor_x = 0, cursor_y = 0;

		mCairoCtx->get_current_point(cursor_x, cursor_y);


		mCairoCtx->save ();

		mCairoCtx->rectangle(cursor_x, cursor_y
				, image->get_width()
				, image->get_height());

		Gdk::Cairo::set_source_pixbuf(mCairoCtx, image, cursor_x, cursor_y);

		mCairoCtx->clip ();
		mCairoCtx->paint ();

		mCairoCtx->restore ();

		mCairoCtx->move_to(0, cursor_y + image->get_height());
	}
	else
	{
		logger->Debug("ERROR - Cairo context NULL");
	}
}

void GraphicContextPrintingBackend::DrawQRCode (QRCodeContent qr)
throw (QREncodingException)
{
	Glib::RefPtr<Gdk::Pixbuf> code_image;
	Glib::RefPtr<Gdk::Bitmap> code_bitmap;
	Glib::RefPtr<Gdk::Drawable> drawable;

	gint width, height;
	width = height = 0;

	code_bitmap = QREncoding::GenerateSymbol(
			  (guchar*) qr.getData ().GetData ()
			, qr.getData().GetSize ()
			, qr.getPixelSize()
			, qr.getMargin()
			, qr.getCorrectionLevel()
			, qr.getVersion ());

	code_bitmap->get_size (width, height);
	drawable = code_bitmap;
	code_image = Gdk::Pixbuf::create(drawable, 0, 0, width, height);

	if ( qr.getImage() )
		code_image = Smartmatic::Graphics::Image::PixbufComposer::compose(qr.getImage(), code_image, qr.getPosInBackground ());

	DrawImage (code_image);
}



//=========================== PRERENDERING ===================================//

void GraphicContextPrintingBackend::RenderPage (Cairo::RefPtr<Cairo::Context> drawableCtx)
{
	if ( ! m_Pages.empty ())
	{
		GraphicContentPage current_page = m_Pages.front ();
		current_page.Render (drawableCtx);
		m_Pages.pop ();
	}
}

void GraphicContextPrintingBackend::PreDrawString(
		  std::list<Glib::ustring>& textContent
		, std::list<DocumentTextOptions>& textContentOptions)
{
	int cells_per_row = textContentOptions.size();
	int cells_in_table = textContent.size();
	int cells_rendered = 0;
	int cells_to_render = 0;

	std::vector<DocumentTextOptions> text_options (textContentOptions.begin(), textContentOptions.end());
	std::vector<Glib::ustring> text_content (textContent.begin(), textContent.end());
	std::vector<Glib::ustring>::iterator it = text_content.begin();

	while (it != text_content.end())
	{
		cells_to_render =
				  cells_rendered + cells_per_row <= cells_in_table
				? cells_per_row
				: cells_in_table % cells_per_row;

		if ( ! PreDrawRow (it, text_options, cells_to_render) ) // need page brake
		{
			GraphicContentPage new_page (mPrintContextWidth, mPrintContextHeight);

			switch (m_CurrentColumnLayout)
			{
			case GraphicContentPage::GCPAGE_SINGLE_COLUMN:
				new_page.SetSingleLayout ();
				break;
			case GraphicContentPage::GCPAGE_DOUBLE_COLUMN:
				new_page.SetTwoColumnsLayout ();
				break;
			default:
				break;
			}

			m_Pages.push (new_page);

			// TODO: this tries to render the row in the new page if it still doesn't fit it is bigger than
			// the page so we are simply skiping it.
			PreDrawRow (it, text_options, cells_to_render);
		}

		cells_rendered += cells_to_render;
		it += cells_to_render;
	}
}

bool GraphicContextPrintingBackend::PreDrawRow (
		  std::vector<Glib::ustring>::iterator pRowContent
		, std::vector<DocumentTextOptions> textContentOptions
		, int numCellsToRender)
{
	double cell_height = 0, row_height = 0;
	int i, indent, column_width = 0;

	GraphicContentPage& current_page = m_Pages.back ();

	std::vector<Glib::RefPtr<Pango::Layout> > row_content (numCellsToRender);
	std::vector<int> cell_indent (numCellsToRender);

	for (i = 0; i < numCellsToRender; i++, pRowContent++)
	{
		Glib::RefPtr<Pango::Layout> cellLayout = Pango::Layout::create (mCairoCtx);

		mPreApplyTextFormat(cellLayout, textContentOptions[i]);

		indent =  textContentOptions[i].getIndentationLevel()  // TODO: verify if the unit is absolute
				* mCurrentBlockFont.get_size() / Pango::SCALE;

		column_width =   current_page.GetCurrentTextAreaWidth()
					   / textContentOptions.size()
					   - indent;

		cellLayout->set_width(column_width * Pango::SCALE);
		cellLayout->set_wrap(Pango::WRAP_WORD_CHAR);
		cellLayout->set_alignment(textContentOptions[i].getGraphicAlignment());
		cellLayout->set_text(*pRowContent);

		row_content[i] = cellLayout;
		cell_indent[i] = indent;

		cell_height = cellLayout->get_logical_extents().get_height() / Pango::SCALE;
		row_height = cell_height > row_height ? cell_height : row_height;
	}

	if (current_page.IsBeyondEndOfPage (row_height))
		return false;

	current_page.AddTextRow (row_content, cell_indent, (int)column_width, (int)row_height);

	return true;
}

void GraphicContextPrintingBackend::mPreApplyTextFormat(
		  Glib::RefPtr<Pango::Layout> textLayout
		, DocumentTextOptions& options)
{
	mCurrentBlockFont.set_family(options.getFontFamily());

	 switch (options.getFontSize ())
	 {
	 case TinyFont:
		 mCurrentBlockFont.set_size( 6 * Pango::SCALE );
		 break;
	 case SmallFont:
		 mCurrentBlockFont.set_size( 7 * Pango::SCALE );
		 break;
	 case MediumFont:
		 mCurrentBlockFont.set_size( 8 * Pango::SCALE );
		 break;
	 case LargeFont:
		 mCurrentBlockFont.set_size( 10 * Pango::SCALE );
		 break;
	 case Biggest:
		 mCurrentBlockFont.set_size( 11 * Pango::SCALE );
		 break;
	 }


	switch (options.getFontStyle())
	{
	case Normal:
		mCurrentBlockFont.set_style(Pango::STYLE_NORMAL);
		break;
	case Bold:
		mCurrentBlockFont.set_weight(Pango::WEIGHT_BOLD);
		break;
	case Italic:
		mCurrentBlockFont.set_style(Pango::STYLE_ITALIC);
		break;
	case Underlined:
		//font_desc.set_ (Pango::UNDERLINE_SINGLE);
		break;
	}

	switch (options.getJustification())
	{
	case LeftJustified:
		textLayout->set_alignment(Pango::ALIGN_LEFT);
		break;
	case Centered:
		textLayout->set_alignment(Pango::ALIGN_CENTER);
		break;
	case RightJustified:
		textLayout->set_alignment(Pango::ALIGN_RIGHT);
		break;
	}

	textLayout->set_font_description(mCurrentBlockFont);
	//textLayout->set_spacing(options.getLineSpacing ());
	//options.getIndentationLevel ();

	/*
	 options.getBoldWeight ()

	 Pango::WEIGHT_ULTRALIGHT   // The ultralight weight (= 200)
	 Pango::WEIGHT_LIGHT        // The light weight (=300)
	 Pango::WEIGHT_NORMAL       // The default weight (= 400)
	 Pango::WEIGHT_BOLD         // The bold weight (= 700)
	 Pango::WEIGHT_ULTRABOLD    // The ultrabold weight (= 800)
	 Pango.WEIGHT_HEAVY         // The heavy weight (= 900)
	 */
}

bool GraphicContextPrintingBackend::PreDrawImage(ImageContent content)
{
	Glib::RefPtr<Gdk::Pixbuf> image = content.getImage();
	DocumentImageAlignmet alignment = content.getAligment();
	DocumentImageLayout img_layout = content.getLauyout();

	int cursor_x = 0, cursor_y = 0;
	int align_x = 0, align_y = 0, init_y = 0;

	double image_total_width = image->get_width() + content.getRightPadding () + content.getLeftPadding ();
	double image_total_height = image->get_height () + content.getTopPadding () + content.getBottomPadding ();
	GraphicContentPage::PageAlignmentEnumType page_alignment;

	GraphicContentPage& current_page = m_Pages.back ();

	if ( current_page.IsBeyondEndOfPage ( image_total_height ) )
			return false;

	current_page.GetCurrentPosition (cursor_x, cursor_y);

	//init_x = cursor_x;
	init_y = cursor_y;

	align_y = init_y + content.getTopPadding();
	page_alignment = GraphicContentPage::GCPAGE_CENTER;

	switch (alignment)
	{
	case Left:

		page_alignment = GraphicContentPage::GCPAGE_LEFT;
		align_x = cursor_x + content.getLeftPadding();

		break;

	case Center:

		page_alignment = GraphicContentPage::GCPAGE_CENTER;

		align_x = (current_page.GetWidth ()
				  - image->get_width ()
				  + content.getLeftPadding ()
				  - content.getRightPadding ())
				  / 2;

		break;

	case Right:

		page_alignment = GraphicContentPage::GCPAGE_RIGHT;

		align_x =  mPrintContextWidth
		         - image->get_width ()
		         - content.getRightPadding ();

		break;

	case Expanded:

		page_alignment = GraphicContentPage::GCPAGE_EXPANDED;

		image = image->scale_simple (mPrintContextWidth, image->get_height(), Gdk::INTERP_BILINEAR);

		if (img_layout == InLineWithText)
		{
			mImageRightPadding = 0;
			mImageLeftPadding = 0;
		}
		break;
	}

	current_page.AddImageContent(
			  image
			, align_x
			, align_y
			, image_total_width
			, image_total_height
			, page_alignment
			, img_layout == InLineWithText);

	if (alignment != Expanded)
	{
		int start_x = 0, start_y = 0, end_x = 0, end_y = 0;

		if ( (content.getBorders () & Border_Right) != 0 )
		{
			start_x = align_x + image->get_width () + content.getRightPadding();
			start_y = align_y;
			end_x   = start_x;
			end_y   = align_y + image->get_height ();
		}

		if ( (content.getBorders () & Border_Left) != 0 )
		{
			start_x = align_x - content.getLeftPadding();
			start_y = align_y;
			end_x   = start_x;
			end_y   = align_y + image->get_height ();
		}

		if ( (content.getBorders () & Border_Bottom) != 0 )
		{
			start_x = align_x;
			start_y = init_y + image->get_height () + content.getBottomPadding() + content.getTopPadding();
			end_x   = align_x + image->get_width ();
			end_y   = start_y;
		}

		if ( (content.getBorders () & Border_Top) != 0 )
		{
			start_x = align_x;
			start_y = init_y;
			end_x   = align_x + image->get_width ();
			end_y   = start_y;
		}

		current_page.AddSepContent (start_x, start_y, end_x, end_y, 1.0);
	}

	return true;
}

void GraphicContextPrintingBackend::PreDrawQRCode (QRCodeContent qr)
throw (QREncodingException)
{
	Glib::RefPtr<Gdk::Pixbuf> code_image;
	Glib::RefPtr<Gdk::Bitmap> code_bitmap;
	Glib::RefPtr<Gdk::Drawable> drawable;

	gint width, height;
	width = height = 0;

	code_bitmap = QREncoding::GenerateSymbol(
			   (guchar*) qr.getData ().GetData ()
			, qr.getData().GetSize ()
			, qr.getPixelSize()
			, qr.getMargin()
			, qr.getCorrectionLevel()
			, qr.getVersion ());

	code_bitmap->get_size (width, height);
	drawable = code_bitmap;
	code_image = Gdk::Pixbuf::create(drawable, 0, 0, width, height);

	if ( qr.getImage() )
		code_image = Smartmatic::Graphics::Image::PixbufComposer::compose(qr.getImage(), code_image, qr.getPosInBackground ());

	ImageContent image_ctn (code_image, Left);

//	qr->SetImage (image);
//
//	PreDrawImage (qr);

//	PreDrawImage (image_ctn);
	PreDrawImage (qr);
}


bool GraphicContextPrintingBackend::PreDrawSeparator (SeparatorContent line)
{
	int cursor_x, cursor_y, align_x, end_x;
	end_x = 0.0;
	align_x = 0.0;

	GraphicContentPage& current_page = m_Pages.back ();

	if ( current_page.IsBeyondEndOfPage(LINE_SEP_WIDTH) )
		return false;

	current_page.GetCurrentPosition (cursor_x, cursor_y);

	switch (line.getAlignment())
	{
	case Left:
		align_x = cursor_x;
		end_x = line.getLength();
		break;
	case Center:
		align_x = (mPrintContextWidth - line.getLength()) / 2;
		end_x = align_x + line.getLength();
		break;
	case Right:
		align_x = mPrintContextWidth - line.getLength();
		end_x = mPrintContextWidth;
		break;
	case Expanded:
		align_x = 0.0;
		end_x = mPrintContextWidth;
		break;
	}

	current_page.AddSepContent (align_x, cursor_y, end_x, cursor_y, LINE_SEP_WIDTH);

	return true;
}

void GraphicContextPrintingBackend::PreJumpInlineImage ()
{
	GraphicContentPage& current_page = m_Pages.back ();

	current_page.JumpInlineImage();
}

void GraphicContextPrintingBackend::PreSetSingleColumn ()
{
	GraphicContentPage& current_page = m_Pages.back ();
	m_CurrentColumnLayout = GraphicContentPage::GCPAGE_SINGLE_COLUMN;
	current_page.SetSingleLayout();
}

void GraphicContextPrintingBackend::PreSetDoubleColumn ()
{
	GraphicContentPage& current_page = m_Pages.back ();
	m_CurrentColumnLayout = GraphicContentPage::GCPAGE_DOUBLE_COLUMN;

	current_page.SetTwoColumnsLayout();
}



//============================= AUXILIARS ====================================//

void GraphicContextPrintingBackend::mSetRowMargin ()
{
	double cursor_x, cursor_y;

	mCairoCtx->get_current_point(cursor_x, cursor_y);

	if (cursor_y > mInlineImageBottomBorder)
	{
		mImageRightPadding = 0;
		mImageLeftPadding = 0;
	}
}

void GraphicContextPrintingBackend::mDrawRow (
		  std::vector<Glib::ustring>::iterator pRowContent
		, std::vector<DocumentTextOptions> textContentOptions
		, int numCellsToRender)
{
	double cursor_x, cursor_y, cell_height = 0, row_height = 0;
	int i, indent, column_width;

	mCairoCtx->set_source_rgb(0, 0, 0);

	for (i = 0; i < numCellsToRender; i++, pRowContent++)
	{
		//Glib::RefPtr<Pango::Layout> cellLayout = Pango::Layout::create (mCairoCtx);
		Glib::RefPtr<Pango::Layout> cellLayout = Pango::Layout::create (mPrintPangoContext);

		mCairoCtx->get_current_point(cursor_x, cursor_y);

		// Cell's text formatting

		mApplyTextFormat(cellLayout, textContentOptions[i]);

		// Cell dimensioning and positioning

		indent =  textContentOptions[i].getIndentationLevel()  // TODO: verify if the unit is absolute
				* mCurrentBlockFont.get_size() / Pango::SCALE;

		column_width = ( mPrintContextWidth
				       - mImageLeftPadding
				       - mImageRightPadding)
					   / textContentOptions.size()
					   - indent;

		cellLayout->set_width(column_width * Pango::SCALE);
		//cellLayout->set_wrap(Pango::WRAP_WORD_CHAR);
		cellLayout->set_alignment(textContentOptions[i].getGraphicAlignment());
		cellLayout->set_text(*pRowContent);

		//TRACE (*pRowContent);

		mCairoCtx->move_to ( cursor_x + mImageRightPadding + indent, cursor_y);

		// Cell rendering

		cellLayout->show_in_cairo_context(mCairoCtx);

		// Subsequent position calculation

		cell_height = cellLayout->get_logical_extents().get_height() / Pango::SCALE;
		row_height = cell_height > row_height ? cell_height : row_height;

		//TRACE (column_width);
		//TRACE (row_height);

		mCairoCtx->move_to ( cursor_x + column_width
				           , cursor_y);
	}

	mCairoCtx->move_to (0, cursor_y + row_height);
	mPrintContextHeight += row_height;
	//TRACE (mPrintContextHeight);
}


void GraphicContextPrintingBackend::mApplyTextFormat(
		  Glib::RefPtr<Pango::Layout> textLayout
		, DocumentTextOptions& options)
{
	mCurrentBlockFont.set_family(options.getFontFamily());

	 switch (options.getFontSize ())
	 {
	 case TinyFont:
		 mCurrentBlockFont.set_size( 6 * Pango::SCALE );
		 break;
	 case SmallFont:
		 mCurrentBlockFont.set_size( 8 * Pango::SCALE );
		 break;
	 case MediumFont:
		 mCurrentBlockFont.set_size( 10 * Pango::SCALE );
		 break;
	 case LargeFont:
		 mCurrentBlockFont.set_size( 12 * Pango::SCALE );
		 break;
	 case Biggest:
		 mCurrentBlockFont.set_size( 14 * Pango::SCALE );
		 break;
	 }


	switch (options.getFontStyle())
	{
	case Normal:
		mCurrentBlockFont.set_style(Pango::STYLE_NORMAL);
		break;
	case Bold:
		mCurrentBlockFont.set_weight(Pango::WEIGHT_BOLD);
		break;
	case Italic:
		mCurrentBlockFont.set_style(Pango::STYLE_ITALIC);
		break;
	case Underlined:
		//font_desc.set_ (Pango::UNDERLINE_SINGLE);
		break;
	}

	switch (options.getJustification())
	{
	case LeftJustified:
		textLayout->set_alignment(Pango::ALIGN_LEFT);
		break;
	case Centered:
		textLayout->set_alignment(Pango::ALIGN_CENTER);
		break;
	case RightJustified:
		textLayout->set_alignment(Pango::ALIGN_RIGHT);
		break;
	}

	textLayout->set_font_description(mCurrentBlockFont);
	//textLayout->set_spacing(options.getLineSpacing ());
	//options.getIndentationLevel ();

	/*
	 options.getBoldWeight ()

	 Pango::WEIGHT_ULTRALIGHT   // The ultralight weight (= 200)
	 Pango::WEIGHT_LIGHT        // The light weight (=300)
	 Pango::WEIGHT_NORMAL       // The default weight (= 400)
	 Pango::WEIGHT_BOLD         // The bold weight (= 700)
	 Pango::WEIGHT_ULTRABOLD    // The ultrabold weight (= 800)
	 Pango.WEIGHT_HEAVY         // The heavy weight (= 900)
	 */
}


void GraphicContextPrintingBackend::DrawImage(ImageContent content)
{
	std::stringstream ss;
	ss<<__FILE__ <<" "<< __func__<<" Line "<<__LINE__;
	logger->Debug(ss.str());
	
	Glib::RefPtr<Gdk::Pixbuf> image = content.getImage();
	DocumentImageAlignmet alignment = content.getAligment();
	DocumentImageLayout img_layout = content.getLauyout();

	double cursor_x = 0, cursor_y = 0;
	double align_x = 0, align_y = 0, init_x = 0, init_y = 0;

	mCairoCtx->get_current_point (cursor_x, cursor_y);

	init_x = cursor_x;
	init_y = cursor_y;

	align_y = init_y + content.getTopPadding();

	switch (alignment)
	{
	case Left:
		align_x = cursor_x + content.getLeftPadding();

		if (img_layout == InLineWithText)
			mImageRightPadding = image->get_width() + content.getRightPadding () + content.getLeftPadding ();

		break;
	case Center:
		align_x = (mPrintContextWidth
				  - image->get_width ()
				  + content.getLeftPadding ()
				  - content.getRightPadding ())
				  / 2;

		if (img_layout == InLineWithText)
		{
			mImageRightPadding = 0;
			mImageLeftPadding = 0;
		}

		break;
	case Right:
		align_x =  mPrintContextWidth
		         - image->get_width ()
		         - content.getRightPadding ();

		if (img_layout == InLineWithText)
			mImageLeftPadding = image->get_width() + content.getRightPadding () + content.getLeftPadding ();

		break;
	case Expanded:
		image = image->scale_simple (mPrintContextWidth, image->get_height(), Gdk::INTERP_BILINEAR);
		if (img_layout == InLineWithText)
		{
			mImageRightPadding = 0;
			mImageLeftPadding = 0;
		}
		break;
	}

	mCairoCtx->save ();
	Gdk::Cairo::set_source_pixbuf(mCairoCtx, image, align_x, align_y);
	mCairoCtx->rectangle(align_x, align_y, image->get_width(), image->get_height());
	mCairoCtx->clip ();
	mCairoCtx->paint();
	mCairoCtx->restore ();

	mCairoCtx->set_source_rgb(0, 0, 0);

	if (alignment != Expanded)
	{
		if ( (content.getBorders () & Border_Right) != 0 )
		{
			mCairoCtx->set_line_width(1.0);
			mCairoCtx->move_to (align_x + image->get_width () + content.getRightPadding(), align_y);
			mCairoCtx->line_to (align_x + image->get_width () + content.getRightPadding(), align_y + image->get_height ());
			mCairoCtx->stroke();
		}

		if ( (content.getBorders () & Border_Left) != 0 )
		{
			mCairoCtx->set_line_width(1.0);
			mCairoCtx->move_to (align_x - content.getLeftPadding(), align_y);
			mCairoCtx->line_to (align_x - content.getLeftPadding(), align_y + image->get_height ());
			mCairoCtx->stroke();
		}

		if ( (content.getBorders () & Border_Bottom) != 0 )
		{
			mCairoCtx->set_line_width(1.0);
			mCairoCtx->move_to (align_x, init_y + image->get_height () + content.getBottomPadding() + content.getTopPadding());
			mCairoCtx->line_to (align_x + image->get_width (), init_y + image->get_height () + content.getBottomPadding() + content.getTopPadding());
			mCairoCtx->stroke();
		}

		if ( (content.getBorders () & Border_Top) != 0 )
		{
			mCairoCtx->set_line_width(1.0);
			mCairoCtx->move_to (align_x, init_y);
			mCairoCtx->line_to(align_x + image->get_width (), init_y);
			mCairoCtx->stroke();
		}
	}

	if (img_layout == InLineWithText && (alignment == Left || alignment == Right ))
	{
		mCairoCtx->move_to(init_x, init_y); // Cairo Bug: cursor rockets to the top of the page after rendering an image so we need to bring it back
		mInlineImageBottomBorder = cursor_y + image->get_height() + content.getBottomPadding() + content.getTopPadding();
		mPrintContextHeight += image->get_height() + content.getBottomPadding() + content.getTopPadding();
	}
	else
	{
		mCairoCtx->move_to(0, init_y + image->get_height() + content.getBottomPadding() + content.getTopPadding());
		mPrintContextHeight += image->get_height() + content.getBottomPadding() + content.getTopPadding();
	}
}
