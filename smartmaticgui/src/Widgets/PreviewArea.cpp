/*
 * PreviewArea.cpp
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include "PreviewArea.h"

using namespace Smartmatic::GUI::Widgets;

PreviewArea::PreviewArea()
{
	if( !ImagePixbuf )
		set_size_request(0,0);
}

PreviewArea::~PreviewArea()
{
	ImagePixbuf.clear();
}

void PreviewArea::load( Glib::ustring filename, bool loadable )
{
	if( !loadable )
	{
		set_size_request(0,0);
		ImagePixbuf.clear();

		Glib::RefPtr<Gdk::Window> window = get_window();
		if (window)
		{
			Gdk::Rectangle r(0, 0, get_allocation().get_width(),
					get_allocation().get_height());
			window->invalidate_rect(r, false);
		}
			return;
	}
	else
	{
		set_size_request( 100,100 );
		int width;
		int height;

		get_size_request( width, height );

		width = (int)(width*0.98);
		height = (int)(height*0.98);

		PixbufLoad( filename, width, height );

		// force a redraw
		Glib::RefPtr<Gdk::Window> window = get_window();
		if (window)
		{
			Gdk::Rectangle r(0, 0, get_allocation().get_width(),
					get_allocation().get_height());
			window->invalidate_rect(r, false);
		}
	}
}

void PreviewArea::PixbufLoad( Glib::ustring filename, int width, int height )
{
	try
	{
		ImagePixbuf.clear();
		ImagePixbuf = Gdk::Pixbuf::create_from_file(
			filename,
			width,
			height );
	}
	catch(Gdk::PixbufError & error)
	{
		std::cerr << "PIXBUFLOAD: PixbufError\n";
	}
	catch(Glib::FileError & error)
	{
		std::cerr << "PIXBUFLOAD: FileError\n";
	}
}

bool PreviewArea::on_expose_event(GdkEventExpose *event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();

	if(window)
	{
		Cairo::RefPtr<Cairo::Context> cairoContext = window->create_cairo_context();
		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();

		cairoContext->rectangle(event->area.x, event->area.y,
				event->area.width, event->area.height);
		cairoContext->clip();

		if( ImagePixbuf )
		{
			ImagePixbuf->render_to_drawable( get_window(),
										get_style()->get_black_gc(),
										0,
										0,
										(width-ImagePixbuf->get_width())/2,
										(height-ImagePixbuf->get_height())/2,
										ImagePixbuf->get_width(),
										ImagePixbuf->get_height(),
										Gdk::RGB_DITHER_NONE,0,0 );
		}

		return true;
	}

	return false;
}
