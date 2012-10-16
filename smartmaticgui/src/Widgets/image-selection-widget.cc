/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "image-selection-widget.h"
#include "System/IO/File.h"

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::System::IO;

ImageSelectionWidget::ImageSelectionWidget(vector<string> imagesPath, vector<string> imagesCode)
{
	vector<string>::iterator it;
	vector<string>::iterator itCode;

	itCode = imagesCode.begin();
	for(it = imagesPath.begin(); it != imagesPath.end(); it++)
	{
		Frame* frame = manage(new Frame());
		EventBox* event = manage(new EventBox());
		event->set_events(Gdk::BUTTON_PRESS_MASK);
		
		string s = *it;
                string code = *itCode;

		if(File::canOpenFile(s))
		{
			Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(s);
                        Image * image = manage(new Image(pixbuf));
			frame->set_shadow_type(SHADOW_NONE);
                        image->show();
                        event->add(*image);
		}
		else
		{
                    Gtk::Label * label = manage(new Gtk::Label( s ));
		    frame->set_shadow_type(SHADOW_ETCHED_OUT);
                    label->show();
                    event->add(*label);
		}

		event->signal_button_press_event().connect( sigc::bind<std::string>( sigc::mem_fun(*this, &ImageSelectionWidget::on_image_clicked), code));
		itCode++;

		event->show();
		events.push_back(event);

		frame->add(*event);
		pack_start(*frame);
	}

	if((int)imagesPath.size() == 2)
		set_spacing (180);
	else
		set_spacing (30);

	set_homogeneous (true);
	show();
}

ImageSelectionWidget::~ImageSelectionWidget()
{

}

bool ImageSelectionWidget::on_image_clicked(GdkEventButton* event, string imagePath)
{
	m_clicked.emit(imagePath);
	return false;
}

ImageSelectionWidget::type_clicked ImageSelectionWidget::clicked()
{
	return m_clicked;
}

