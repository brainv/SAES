/*
 * GraphicContentPage.h
 *
 *  Created on: May 2, 2011
 *      Author: root
 */

#ifndef GRAPHICCONTENTPAGE_H_
#define GRAPHICCONTENTPAGE_H_


#include <list>
#include <gtkmm.h>
#include <gdkmm.h>

namespace Smartmatic
{

namespace SAES
{

namespace Printing
{

class GraphicContentPage
{
public:

	typedef enum PageAlignmentEnum
	{
		GCPAGE_LEFT,
		GCPAGE_CENTER,
		GCPAGE_RIGHT,
		GCPAGE_EXPANDED

	} PageAlignmentEnumType;

	typedef enum ColumnModeEnum
	{
		GCPAGE_SINGLE_COLUMN,
		GCPAGE_DOUBLE_COLUMN

	} ColumnModeEnumType;

	//Life Cycle

	/** Constructor
	 */
	GraphicContentPage();

	GraphicContentPage(const GraphicContentPage& other);

	/** Constructor
	 */
	GraphicContentPage(double pageWidth, double pageHeight);

	/** Destructor
	 */
	virtual ~GraphicContentPage();


	// Interface

	void GetCurrentPosition (int& x, int& y);

	double GetCurrentTextAreaWidth ();

	double GetWidth () { return m_Width; }

	bool IsBeyondEndOfPage (double elementHeight);

	void AddTextRow (
			  const std::vector<Glib::RefPtr<Pango::Layout> >& row_content
			, const std::vector<int>& cell_indent
			, int column_width
			, int row_height);

	void AddTextContent (
			    Glib::RefPtr<Pango::Layout> textContent
			  , int initX
			  , int initY);

	void AddImageContent (
			  Glib::RefPtr<Gdk::Pixbuf> image
			, int init_x
			, int init_y
			, double element_width
			, double element_height
			, PageAlignmentEnumType alignment
			, bool floating);

	void AddSepContent (int initX, int initY, int endX, int endY, double weight);

	void JumpInlineImage ();

	void Render (Cairo::RefPtr<Cairo::Context> drawableContext);

	void SetSingleLayout ();

	void SetTwoColumnsLayout ();

private:


	class GraphicContextTextCell
	{
	public:

		GraphicContextTextCell (
			    Glib::RefPtr<Pango::Layout> textContent
			  , int initX
			  , int initY)
		      : CellLayout (textContent)
		      , init_x (initX)
		      , init_y (initY) { }

		GraphicContextTextCell (const GraphicContextTextCell& other)
		{
			CellLayout = other.CellLayout;
			init_x = other.init_x;
			init_y = other.init_y;
		}

		~GraphicContextTextCell () {};

		Glib::RefPtr<Pango::Layout> CellLayout;

		int init_x;
		int init_y;
	};

	class GraphicContextImage
	{
	public:

		GraphicContextImage (
			  Glib::RefPtr<Gdk::Pixbuf> image
			, int initX
			, int initY
			, int width
			, int height
			, PageAlignmentEnumType align)
		    : Image (image)
		    , init_x (initX)
		    , init_y (initY)
		    , element_width (width)
		    , element_height (height)
		    , alignment (align)
		 { }

		~GraphicContextImage () {};

		Glib::RefPtr<Gdk::Pixbuf> Image;

		int init_x;
		int init_y;
		int element_width;
		int element_height;

		PageAlignmentEnumType alignment;
	};

	class GraphicContextSep
	{
	public:

		GraphicContextSep (
			  int initX, int initY, int endX, int endY, double weight)
		    : init_x (initX)
		    , init_y (initY)
		    , end_x  (endX)
		    , end_y  (endY)
		    , m_weight (weight)
		{ }

		~GraphicContextSep () {};

		int init_x;
		int init_y;
		int end_x;
		int end_y;
		double m_weight;
	};


	static int PageCount;
	int m_PageNum;

	double m_DoubleColumnStartPos;
	int m_CurrentColumn;
	ColumnModeEnumType m_CurrentColumnMode;

	double m_Width;
	double m_Height;

	double m_Cursor_X;
	double m_Cursor_Y;

	double m_TextLeftMargin;
	double m_TextRightMargin;
	double m_CurrentImageBottom;

	std::list<GraphicContextTextCell> m_TextElements;
	std::list<GraphicContextImage> m_ImageElements;
	std::list<GraphicContextSep> m_SepElements;

};

}
}
}

#endif /* GRAPHICCONTENTPAGE_H_ */
