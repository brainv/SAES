/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * bullet
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * bullet is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bullet is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "circle-widget.h"

using namespace Smartmatic::GUI::Widgets;

CircleWidget::CircleWidget()
{
	setFirst = false;

	backRed1 = 0.5;
	backGreen1 = 0.5;
	backBlue1 = 0.5;
	backAlpha1 = 20000;
	backRed2 = 65000;
	backGreen2 = 65000;
	backBlue2 = 65000;
	backAlpha2 = 65000;
}

CircleWidget::CircleWidget(float red1, float green1, float blue1, float alpha1,
                           float red2, float green2, float blue2, float alpha2)
{
	setFirst = false;

	backRed1 = red1;
	backGreen1 = green1;
	backBlue1 = blue1;
	backAlpha1 = alpha1;
	backRed2 = red2;
	backGreen2 = green2;
	backBlue2 = blue2;
	backAlpha2 = alpha2;
}

CircleWidget::~CircleWidget()
{

}

bool CircleWidget::on_expose_event(GdkEventExpose* event)
{
	// This is where we draw on the window
	Glib::RefPtr<Gdk::Window> window = get_window();
	if(window)
	{
		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();
		int lesser = MIN(width, height);

		
		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;

	    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
	    cr->set_line_width(lesser * 0.01);  // outline thickness changes
		                                    // with window size

		// clip to the area indicated by the expose event so that we only redraw
		// the portion of the window that needs to be redrawn
		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();

		cr->set_source_rgba(1, 1, 1, 0.9);
		
		// now draw a circle
		cr->save();
		cr->arc(xc, yc, lesser / 3, 0.0, 2.0 * M_PI); // full circle

		if(setFirst)
			cr->set_source_rgb(backRed1, backGreen1, backBlue1);
		else
			cr->set_source_rgba(backRed2, backGreen2, backBlue2, backAlpha2);
		
		cr->fill_preserve();
		cr->restore();  // back to opaque black
		cr->stroke();

		 cr->save();

	}

	return true;
}

void CircleWidget::SetMark(bool setFirst)
{
	this->setFirst = setFirst;
	
    // force our program to redraw the entire circle.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}



