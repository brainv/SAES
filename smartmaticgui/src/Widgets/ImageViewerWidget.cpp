/*
 * ImageViewerWidget.cpp
 *
 *  Created on: Apr 9, 2011
 *      Author: Gerardo Hernandez
 */

#include "ImageViewerWidget.h"

extern "C" {
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk-2.0/gdk/gdkkeysyms.h>
}

using namespace Smartmatic::GUI::Widgets;

ImageViewerWidget::ImageViewerWidget() :
		Hand(Gdk::FLEUR),
		Watch(Gdk::WATCH)
{
	this->hScroller = imageScroller->get_hadjustment();
	this->vScroller = imageScroller->get_vadjustment();

	this->hScroller->set_step_increment( 10 );
	this->vScroller->set_step_increment( 10 );

	imageScroller->set_shadow_type(Gtk::SHADOW_NONE);

	imageScroller->set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

	imageScroller->add(imageBox);

	if( this->imageBox.isLoaded() )
	{
		this->vScroller->set_upper( imageBox.get_height() - vScroller->get_page_size() );
		this->hScroller->set_upper( imageBox.get_width() - hScroller->get_page_size() );
	}
}

ImageViewerWidget::~ImageViewerWidget() {

}

void ImageViewerWidget::setScalefactor(double scale)
{

};

void ImageViewerWidget::setButtonsActive(bool active)
{

};

void ImageViewerWidget::busy(bool)
{

};

void ImageViewerWidget::on_button_next(void)
{

};

void ImageViewerWidget::on_button_previous(void)
{

};

void ImageViewerWidget::on_button_zoom_in(void)
{

};

void ImageViewerWidget::on_button_zoom_out(void)
{

};

void ImageViewerWidget::on_button_zoom_1to1(void)
{

};

void ImageViewerWidget::adjust_adjustment_on_zoom(double oldscale)
{

};

void ImageViewerWidget::on_button_rotate_anticlockwise(void)
{

};

void ImageViewerWidget::on_button_rotate_clockwise(void)
{

};

void ImageViewerWidget::adjust_adjustment_on_rotate(int angle,double h_old, double v_old)
{

};

void ImageViewerWidget::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>&, int, int, const Gtk::SelectionData&, guint, guint)
{

};
