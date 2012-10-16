/*
 * PrintPreviewWidget.cpp
 *
 *  Created on: Mar 23, 2011
 *      Author: marcel
 */


#include <iostream>
#include <cstring>

#include "Printing/PrintPreviewWidget.h"
#include "Configuration/s-a-e-s-common-conf-manager.h"

//#define MV_TICKET_WIDTH 450;
#define EMPTY_DOCUMENT_HEIGHT 10.0
#define EMPTY_DOCUMENT_WIDTH 10.0

using namespace std;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Common::Configuration;

PrintPreviewWidget::PrintPreviewWidget()
    : Glib::ObjectBase("custom_print_preview")
    , Gtk::Widget()
{
	release = true;

	set_has_window(false);

	gtk_widget_class_install_style_property(GTK_WIDGET_CLASS(
			G_OBJECT_GET_CLASS(gobj())), g_param_spec_int("print_preview_scale",
			"Scale of print preview Drawing",
			"The scale to use when drawing.",
			G_MININT, G_MAXINT, 0, G_PARAM_READABLE));

	gtk_rc_parse("custom_gtkrc");

	mrDoc = NULL;

	mDocHeight = EMPTY_DOCUMENT_HEIGHT;
	mDocWidth = EMPTY_DOCUMENT_WIDTH;

	mrDocSurface = Cairo::ImageSurface::create (
			Cairo::FORMAT_ARGB32
			, (int) mDocWidth
			, (int) mDocHeight
			);
}

PrintPreviewWidget::PrintPreviewWidget(BasePrintDocument* doc)
    : Glib::ObjectBase("custom_print_preview")
    , Gtk::Widget()
    , mrDoc (doc)
{
	release = true;
	set_has_window(false);

	/*
	gtk_widget_class_install_style_property(GTK_WIDGET_CLASS(
			G_OBJECT_GET_CLASS(gobj())), g_param_spec_int("print_preview_scale",
			"Scale of print preview Drawing",
			"The scale to use when drawing.",
			G_MININT, G_MAXINT, 0, G_PARAM_READABLE));

	gtk_rc_parse("custom_gtkrc");
	*/
}

PrintPreviewWidget::~PrintPreviewWidget()
{
	// TODO Auto-generated destructor stub
}

void PrintPreviewWidget::on_size_request(Gtk::Requisition* requisition)
{
	try
	{
		*requisition = Gtk::Requisition();

		requisition->width  = mDocWidth;
		requisition->height = mDocHeight;
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::on_size_allocate(Gtk::Allocation& allocation)
{
	try
	{
		if (mrGdkWindow)
		{
			set_allocation(allocation);
			mrGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
					allocation.get_width(), allocation.get_height());
		}
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::on_map()
{
	if (!release)
	{
		return;
	}

	try
	{
		Gtk::Widget::on_map();
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::on_unmap()
{
	try
	{
		Gtk::Widget::on_unmap();
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::on_realize()
{
	if (!release)
	{
		return;
	}

	try
	{
		if (!mrGdkWindow)
		{
			Gtk::Widget::on_realize();
			ensure_style();

			GdkWindowAttr attributes;
			memset(&attributes, 0, sizeof(attributes));

			Gtk::Allocation allocation = get_allocation();

			// Set initial position and size of the Gdk::Window:
			attributes.x      = allocation.get_x();
			attributes.y      = allocation.get_y();
			attributes.width  = allocation.get_width();
			attributes.height = allocation.get_height();

			attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
			attributes.window_type = GDK_WINDOW_CHILD;
			attributes.wclass = GDK_INPUT_OUTPUT;

			mrGdkWindow = Gdk::Window::create(get_window() /* parent */,
					&attributes, GDK_WA_X | GDK_WA_Y);
			mrGdkWindow->reference();
			set_has_window();
			set_window(mrGdkWindow);

			//set colors
			modify_bg(Gtk::STATE_NORMAL , Gdk::Color("white"));

			mrGdkWindow->set_user_data(gobj());

			if (mrDoc != NULL)
			{
				Cairo::RefPtr<Cairo::Context> cr = mrGdkWindow->create_cairo_context();
				Glib::RefPtr<Pango::Context>  pg = this->get_pango_context();

				mDocWidth = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getScreenPreviewWidth();
				mrDoc->CalculatePreviewDimensions (cr, pg, mDocWidth);
				mDocHeight = mrDoc->GetHeight ();

				set_size_request (mDocWidth, mDocHeight);

				mrDocSurface = Cairo::ImageSurface::create (
						  Cairo::FORMAT_ARGB32
						, (int) mDocWidth
						, (int) mDocHeight);

				Cairo::RefPtr<Cairo::Context> cr_buffer = Cairo::Context::create (mrDocSurface);
				mrDoc->PrintPreview (cr_buffer, pg, mDocWidth);
			}
		}
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::SetDocument (BasePrintDocument* newDoc)
{
	try
	{
		if (mrGdkWindow)
		{
			Cairo::RefPtr<Cairo::Context> cr = mrGdkWindow->create_cairo_context ();
			Glib::RefPtr<Pango::Context>  pg = this->get_pango_context ();

			newDoc->CalculatePreviewDimensions (cr, pg, mDocWidth);

			mDocWidth  = (*SAESCommonConfigurationManager::Current()->getConfiguration())->getConfigurationPrinter().getScreenPreviewWidth(); //newDoc->GetWidth();
			mDocHeight = newDoc->GetHeight ();

			set_size_request (mDocWidth, mDocHeight);

			mrGdkWindow->clear (); // Clears the window's graphic content

			mrDocSurface.clear (); // Explicitly destroy the surface by clearing it's reference

			mrDocSurface = Cairo::ImageSurface::create (
					Cairo::FORMAT_ARGB32
					, (int)mDocWidth
					, (int)mDocHeight);

			Cairo::RefPtr<Cairo::Context> cr_buffer = Cairo::Context::create (mrDocSurface);
			newDoc->PrintPreview (cr_buffer, pg, mDocWidth);
		}
	}
	catch(...)
	{

	}
}

void PrintPreviewWidget::on_unrealize()
{
	try
	{
		release = false;
		mrGdkWindow.clear();
		Gtk::Widget::on_unrealize();
	}
	catch(...)
	{

	}
}

bool PrintPreviewWidget::on_expose_event(GdkEventExpose* event)
{
	try
	{
		if (mrGdkWindow)
		{
			Cairo::RefPtr<Cairo::Context> cr = mrGdkWindow->create_cairo_context();
			cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
			cr->clip();
			cr->set_source(mrDocSurface, 0.0, 0.0);
			cr->paint ();
		}
	}
	catch(...)
	{

	}

	return true;
}
