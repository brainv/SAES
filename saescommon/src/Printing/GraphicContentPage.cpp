/*
 * GraphicContentPage.cpp
 *
 *  Created on: May 2, 2011
 *      Author: root
 */


#include <iostream>
#include "GraphicContentPage.h"

#define INTER_COLUMN_SPACE 20.0;

using namespace std;

namespace Smartmatic
{

namespace SAES
{

namespace Printing
{

int GraphicContentPage::PageCount = 0;

// ============================ LIFE CYCLE ===================================//

GraphicContentPage::GraphicContentPage()
{
	m_PageNum = ++PageCount;
}

GraphicContentPage::~GraphicContentPage()
{
}

GraphicContentPage::GraphicContentPage (double pageWidth, double pageHeight)
{
	m_Width = pageWidth;
	m_Height = pageHeight;
	m_Cursor_X = 0;
	m_Cursor_Y = 0;
	m_TextLeftMargin = 0;
	m_TextRightMargin = pageWidth;
	m_CurrentColumn = 0;
	m_DoubleColumnStartPos = 0;
	m_CurrentColumnMode = GCPAGE_SINGLE_COLUMN;
	m_CurrentImageBottom = 0;
	m_PageNum = ++PageCount;
}

GraphicContentPage::GraphicContentPage(const GraphicContentPage& other)
{
	m_Width = other.m_Width;
	m_Height = other.m_Height;

	m_Cursor_X = other.m_Cursor_X;
	m_Cursor_Y = other.m_Cursor_Y;

	m_TextLeftMargin = other.m_TextLeftMargin;
	m_TextRightMargin = other.m_TextRightMargin;
	m_CurrentImageBottom = other.m_CurrentImageBottom;

	m_CurrentColumnMode = other.m_CurrentColumnMode;
	m_DoubleColumnStartPos = other.m_DoubleColumnStartPos;
	m_CurrentColumn = other.m_CurrentColumn;

	m_TextElements = other.m_TextElements;
	m_ImageElements = other.m_ImageElements;
	m_SepElements = other.m_SepElements;

	m_PageNum = other.m_PageNum;
}

// ========================= PUBLIC INTERFACE ================================//

void GraphicContentPage::GetCurrentPosition (int& x, int& y)
{
	x = m_Cursor_X;
	y = m_Cursor_Y;
}

double GraphicContentPage::GetCurrentTextAreaWidth ()
{
	return m_TextRightMargin - m_TextLeftMargin;
}

bool GraphicContentPage::IsBeyondEndOfPage (double elementHeight)
{
	bool end_of_page = false;

	if ( m_CurrentColumnMode == GCPAGE_SINGLE_COLUMN ||
		(m_CurrentColumnMode == GCPAGE_DOUBLE_COLUMN && m_CurrentColumn > 0)
	   )
	{
		end_of_page = m_Cursor_Y + elementHeight > m_Height;
	}
	else
	{
		if (m_Cursor_Y + elementHeight > m_Height)
		{
			m_Cursor_Y = m_DoubleColumnStartPos;
			m_TextLeftMargin = m_Width - (m_Width / 2) + INTER_COLUMN_SPACE;
			m_TextRightMargin = m_Width;
			m_CurrentColumn++;
		}

		end_of_page = false;
	}

	return end_of_page;
}

void GraphicContentPage::AddTextContent (
		    Glib::RefPtr<Pango::Layout> textContent
		  , int initX
		  , int initY)
{
	GraphicContextTextCell cell (textContent, initX, initY);
	m_TextElements.push_back (cell);
}

void GraphicContentPage::AddTextRow (
		  const std::vector<Glib::RefPtr<Pango::Layout> >& row_content
		, const std::vector<int>& cell_indent
		, int column_width
		, int row_height)
{
	for (size_t i=0; i < cell_indent.size(); i++)
	{
		AddTextContent (
				  row_content[i]
				, m_Cursor_X + cell_indent[i] + m_TextLeftMargin + i * column_width
				, m_Cursor_Y);
	}

	m_Cursor_X = 0;
	m_Cursor_Y += row_height;

	if (m_Cursor_Y > m_CurrentImageBottom)
	{
		if (m_CurrentColumnMode == GCPAGE_DOUBLE_COLUMN)
		{
			if (m_CurrentColumn > 0)
			{
				m_TextLeftMargin = m_Width - (m_Width / 2) + INTER_COLUMN_SPACE;
				m_TextRightMargin = m_Width;
			}
			else
			{
				m_TextLeftMargin = 0;
				m_TextRightMargin = m_Width / 2 - INTER_COLUMN_SPACE;
			}
		}
		else
		{
			m_TextLeftMargin = 0;
			m_TextRightMargin = m_Width;
		}
	}
}

void GraphicContentPage::AddImageContent (
		  Glib::RefPtr<Gdk::Pixbuf> image
		, int init_x
		, int init_y
		, double element_width
		, double element_height
		, PageAlignmentEnumType alignment
		, bool floating)
{
	GraphicContextImage picture (image, init_x, init_y, (int)element_width, (int)element_height, alignment);

	if (floating)
	{
		switch (alignment)
		{
		case GCPAGE_LEFT:
			m_TextLeftMargin += element_width;
			//m_TextRightMargin = m_Width;
			break;
		case GCPAGE_CENTER:
			//m_TextLeftMargin = 0;
			//m_TextRightMargin = m_Width;
			break;
		case GCPAGE_RIGHT:
			//m_TextLeftMargin = 0;
			m_TextRightMargin -= element_width;
			break;
		case GCPAGE_EXPANDED:
			//m_TextLeftMargin = 0;
			//m_TextRightMargin = m_Width;
			break;
		}

		m_Cursor_X = 0;
		m_CurrentImageBottom = m_Cursor_Y + element_height;
	}
	else
	{
		m_Cursor_X = 0;
		m_Cursor_Y += element_height;
	}

	m_ImageElements.push_back (picture);
}

void GraphicContentPage::AddSepContent (int initX, int initY, int endX, int endY, double weight)
{
	GraphicContextSep sep (initX, initY, endX, endY, weight);
	m_SepElements.push_back (sep);
}

void GraphicContentPage::JumpInlineImage ()
{
	if (m_Cursor_Y < m_CurrentImageBottom)
	{
		m_Cursor_Y = m_CurrentImageBottom;

		if (m_CurrentColumn > 0)
		{
			m_TextLeftMargin = m_Width - (m_Width / 2) + INTER_COLUMN_SPACE;
			m_TextRightMargin = m_Width;
		}
		else
		{
			m_TextLeftMargin = 0;
			m_TextRightMargin = m_Width / 2 - INTER_COLUMN_SPACE;
		}
	}
}

void GraphicContentPage::Render (Cairo::RefPtr<Cairo::Context> drawableCtx)
{
	drawableCtx->save ();

	// Image

	for (std::list<GraphicContextImage>::const_iterator it = m_ImageElements.begin ()
	    ; it != m_ImageElements.end ()
	    ; it++)
	{
		double x = it->init_x;
		double y = it->init_y;

		drawableCtx->save ();

//		drawableCtx->user_to_device (x, y);

		Gdk::Cairo::set_source_pixbuf(drawableCtx, it->Image, x, y);
		drawableCtx->rectangle(x, y, it->Image->get_width (), it->Image->get_height());
		drawableCtx->clip ();
		drawableCtx->paint ();

		drawableCtx->restore ();
	}

	// Text

	for (std::list<GraphicContextTextCell>::const_iterator it = m_TextElements.begin ()
	    ; it != m_TextElements.end ()
	    ; it++)
	{
		double x = it->init_x;
		double y = it->init_y;

//		drawableCtx->user_to_device (x, y);

		drawableCtx->move_to (x, y);
		it->CellLayout->show_in_cairo_context (drawableCtx);
	}

	// Separator

	for (std::list<GraphicContextSep>::const_iterator it = m_SepElements.begin ()
	    ; it != m_SepElements.end ()
	    ; it ++)
	{
		double x = it->init_x;
		double y = it->init_y;
		double ex = it->end_x;
		double ey = it->end_y;

//		drawableCtx->user_to_device (x, y);
//		drawableCtx->user_to_device (ex, ey);

		drawableCtx->set_line_width(it->m_weight);
		drawableCtx->move_to (x, y);
		drawableCtx->line_to (ex, ey);
		drawableCtx->stroke();
	}

	drawableCtx->restore ();
}

void GraphicContentPage::SetSingleLayout ()
{
	m_CurrentColumnMode = GCPAGE_SINGLE_COLUMN;
	m_CurrentColumn = 0;
	m_TextRightMargin = m_Width;
}

void GraphicContentPage::SetTwoColumnsLayout ()
{
	m_CurrentColumnMode = GCPAGE_DOUBLE_COLUMN;
	m_CurrentColumn = 0;
	m_DoubleColumnStartPos = m_Cursor_Y;
	m_TextLeftMargin = 0;
	m_TextRightMargin = m_Width / 2 - INTER_COLUMN_SPACE;
}


}
}
}
