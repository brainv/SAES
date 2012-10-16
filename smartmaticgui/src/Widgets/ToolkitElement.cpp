/*
 * ToolkitElement.cpp
 *
 *  Created on: May 28, 2011
 *      Author: gerardohernandez
 */

#include "ToolkitElement.h"

using namespace Smartmatic::GUI::Widgets;

ToolkitElement::ToolkitElement(std::string imagepath, std::string messageA, MenuOption optionA,
		WizardWidgetConfiguration currentWizardConfiguration,  bool useMessage)
{
	option = optionA;

	int width = currentWizardConfiguration.getToolboxElementWidth();
	int height = currentWizardConfiguration.getToolboxElementHeight();
	Glib::RefPtr<Gdk::Pixbuf> im = Gdk::Pixbuf::create_from_file(imagepath, width,
			height, false);
	image = manage(new Gtk::Image(im));
	vbox = manage(new Gtk::VBox());
	title = manage(new Gtk::Label());
	clickEventBox = manage(new Gtk::EventBox());
	title->set_label(messageA);
	vbox->pack_start(*image, false, false, 3);
	if(useMessage)
		vbox->pack_end(*title, false, false, 1);
	clickEventBox->add(*vbox);
	clickEventBox->signal_button_press_event().connect(sigc::mem_fun(*this, &ToolkitElement::on_eventbox_clicked));
	add(*clickEventBox);
	show_all_children(true);
}

bool ToolkitElement::on_eventbox_clicked(GdkEventButton* event)
{
	m_toolkit_element_sigc.emit(option);
	return true;
}

ToolkitElement::~ToolkitElement()
{
	// TODO Auto-generated destructor stub
}
