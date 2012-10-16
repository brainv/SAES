/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file voting-widget-base.cxx
 * @brief Body of core class VotingWidgetBase
 */

#include "voting-widget-base.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Environment/Configurations/resource-path-provider.h"
#include "Configuration/label-configuration.h"
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include "Functionalities/time-functionality.h"

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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Functionality;

#include "Functionalities/time-functionality.h"
using namespace Smartmatic::Functionality;

VotingWidgetBase::VotingWidgetBase(VotingWidgetBase_Display display, string displayString, std::string number, int padding, int numberWidth, int width, int height, bool showNumberA, bool isReferendum)
{
	this->numberWidth = numberWidth;
	this->number = number;
	this->display = display;
	this->padding = padding;
	this->displayString = displayString;
	this->topString = "";
	this->bottomString = "";
	this->showNumber = showNumberA;
	this->isReferendum = isReferendum;

	Initialize(width, height);
}

VotingWidgetBase::VotingWidgetBase(VotingWidgetBase_Display display, string displayString, std::string number, int padding, int numberWidth,
                                   Smartmatic::GUI::Configuration::LabelConfiguration labelChildConfigurationA, int width, int height, bool showNumberA)
{
	this->numberWidth = numberWidth;
	this->number = number;
	this->display = display;
	this->padding = padding;
	this->displayString = displayString;
	this->topString = "";
	this->bottomString = "";
	this->showNumber = showNumberA;
	this->isReferendum = false;

	Initialize(width, height);
}

VotingWidgetBase::VotingWidgetBase(string topString, string bottomString, std::string number, int padding, int numberWidth, int width, int height, bool showNumberA)
{

	this->numberWidth = numberWidth;
	this->number = number;
	this->display = VotingWidgetBase_DualText;
	this->padding = padding;
	this->displayString = "";
	this->topString = topString;
	this->bottomString = bottomString;
	this->showNumber = showNumberA;
	this->isReferendum = false;

	Initialize(width, height);
}

VotingWidgetBase::~VotingWidgetBase()
{
	if(image_child) delete(image_child);
	if(label_child) delete(label_child);
	if(top_child) delete(top_child);
	if(bottom_child) delete(bottom_child);
	if(number_child) delete(number_child);

	image_child = 0;
	label_child = 0;
	top_child = 0;
	bottom_child = 0;
	number_child = 0;
}

void VotingWidgetBase::Initialize(int width, int height)
{
	static LabelConfiguration labelChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetLabelChildLabelConfiguration();
	static LabelConfiguration topChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetTopChildLabelConfiguration();
	static LabelConfiguration bottomChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetBottomChildLabelConfiguration();
	static LabelConfiguration numberChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetNumberChildLabelConfiguration();
	static LabelConfiguration referendumConfiguration = SAESGUIConfigurationManager::Current()->GetReferendumBallotsLabelConfiguration();

	image_child = 0;
	label_child = 0;
	top_child = 0;
	bottom_child = 0;
	number_child = 0;	
		
	sizeAllocateCallback = false;
	
	set_flags(NO_WINDOW);
	set_redraw_on_allocate(false);

	static Smartmatic::SAES::Configuration::BallotOptionWidgetConfiguration config = 
		Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();

	switch(display)
	{
		case VotingWidgetBase_Text:
		{
			label_child = new Label(displayString);
			label_child->set_line_wrap(true);
			label_child->set_parent(*this);
			label_child->set_alignment(0, 0);
			label_child->show();

			if(!isReferendum)
				Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(label_child, labelChildConfiguration);
			else
				Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(label_child, referendumConfiguration);
		}
			break;

		case VotingWidgetBase_DualText:
		{
			top_child = new Label(topString);
			top_child->set_line_wrap(true);
			top_child->set_parent(*this);
			top_child->set_alignment(0, 0);
			Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(top_child, topChildConfiguration);
			top_child->show();

			if(!bottomString.empty())
			{
				bottom_child = new Label(bottomString);
				bottom_child->set_line_wrap(true);
				bottom_child->set_parent(*this);
				bottom_child->set_alignment(0, 0);
				Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(bottom_child, bottomChildConfiguration);
				bottom_child->show();
			}
		}
			break;
			
		case VotingWidgetBase_Image:
		{
			image_child = new Image();
			image_child->set_parent(*this);
			
			try
			{
				pixbuf = Gdk::Pixbuf::create_from_file(displayString);
			}
			catch(...)
			{
				string s = Smartmatic::Environment::ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/image-not-found.gif");
				pixbuf = Gdk::Pixbuf::create_from_file(s);
			}
			image_child->set(pixbuf);
			image_child->show();
		}
			break;
			
		default:
			break;
	}

	if(this->showNumber)
	{
		number_child = new Label(number);
		number_child->set_line_wrap(true);
		number_child->set_parent(*this);
		number_child->set_alignment(0, 0);
		Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(number_child, numberChildConfiguration);
		number_child->show();
	}
	
	setSize(width, height);
	show();
}

void VotingWidgetBase::setSize(int width, int height)
{
	set_size_request(width, height);

	switch(display)
	{
		case VotingWidgetBase_Text:
		{
			int innerNumberWidth = 	showNumber ? numberWidth : 0;
			label_child->set_size_request(width - padding - innerNumberWidth, height - 2*padding);
			break;
		}

		case VotingWidgetBase_DualText:
		{
			if(bottomString.empty())
			{
				int innerNumberWidth = 	showNumber ? numberWidth : 0;
				top_child->set_size_request(width - padding - innerNumberWidth, height - 2*padding);
			}
		}
			break;

		default:
			break;
	}
}

void VotingWidgetBase::on_size_allocate(Gtk::Allocation& allocation)
{
	if(!sizeAllocateCallback)
	{
		set_allocation(allocation);
		Allocation child_allocation;

		int innerNumberWidth = 	this->showNumber ? numberWidth : 0;

		int width = allocation.get_width() - innerNumberWidth;
		int height = allocation.get_height();	

		float position_x(0.0), position_y(0.0);

		Pango::Rectangle rec, dummy;
		Glib::RefPtr<Pango::Layout> layout;
		
		switch(display)
		{
			case VotingWidgetBase_Text:
			{
				if(label_child)
				{
					layout = label_child->get_layout();
					layout->get_pixel_extents(dummy, rec);

					child_allocation.set_width(width - padding);
					child_allocation.set_height(height - 2 * padding);

					int originalSizeFont = SAESGUIConfigurationManager::Current()->GetVotingWidgetLabelChildLabelConfiguration().GetSize();

					while(rec.get_width() > width - padding - 10)
					{
						originalSizeFont--;

						Pango::FontDescription fontTitle = label_child->get_style()->get_font();
						fontTitle.set_size(originalSizeFont*Pango::SCALE);
						label_child->modify_font(fontTitle);

						layout = label_child->get_layout();
						layout->get_pixel_extents(dummy, rec);
					}

					if(!isReferendum)
					{
						static Smartmatic::GUI::Configuration::LabelAlignmentEnum labelAlignment =
								SAESGUIConfigurationManager::Current()->GetVotingWidgetLabelChildLabelConfiguration().GetLabelAlignment();

						switch(labelAlignment)
						{
							case Smartmatic::GUI::Configuration::LeftAlignment:
								position_x = allocation.get_x() + innerNumberWidth;
								break;
							case Smartmatic::GUI::Configuration::CenterAlignment:
								position_x = allocation.get_x() + innerNumberWidth + width / 2 - rec.get_width() / 2;
								break;
							case Smartmatic::GUI::Configuration::RigthAlignment:
								position_x = allocation.get_x() + innerNumberWidth + width - padding - rec.get_width();
								break;
							default:
								break;
						}
					}
					else
					{
						static Smartmatic::GUI::Configuration::LabelAlignmentEnum labelAlignment =
								SAESGUIConfigurationManager::Current()->GetReferendumBallotsLabelConfiguration().GetLabelAlignment();

						switch(labelAlignment)
						{
							case Smartmatic::GUI::Configuration::LeftAlignment:
								position_x = allocation.get_x() + innerNumberWidth;
								break;
							case Smartmatic::GUI::Configuration::CenterAlignment:
								position_x = allocation.get_x() + innerNumberWidth + width / 2 - rec.get_width() / 2;
								break;
							case Smartmatic::GUI::Configuration::RigthAlignment:
								position_x = allocation.get_x() + innerNumberWidth + width - padding - rec.get_width();
								break;
							default:
								break;
						}
					}
					
					position_y = allocation.get_y() + (height/ 2) - ((rec.get_height() / 2));

					child_allocation.set_x(position_x);
					child_allocation.set_y(position_y);

					label_child->size_allocate(child_allocation);
					label_child->set_size_request(child_allocation.get_width(), child_allocation.get_height());
				}
			}	
				break;

			case VotingWidgetBase_DualText:
			{
				if(top_child && bottom_child)
				{
					//label top
   					layout = top_child->get_layout();
					layout->get_pixel_extents(dummy, rec);

					child_allocation.set_width(width - padding);
					child_allocation.set_height(height / 2 - padding);

					static LabelConfiguration topChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetTopChildLabelConfiguration();
					switch(topChildConfiguration.GetLabelAlignment())//top
					{
						case Smartmatic::GUI::Configuration::LeftAlignment:
							position_x = allocation.get_x() + innerNumberWidth;
							break;
						case Smartmatic::GUI::Configuration::CenterAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width / 2 - rec.get_width() / 2;
							break;
						case Smartmatic::GUI::Configuration::RigthAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width - padding - rec.get_width();
							break;
						default:
							break;
					}

					//TODO tamaño de la letra
					child_allocation.set_x(position_x);
					child_allocation.set_y(allocation.get_y() + padding);

					top_child->size_allocate(child_allocation);
					top_child->set_size_request(child_allocation.get_width(), child_allocation.get_height());
					
					//label bottom
   					layout = bottom_child->get_layout();
					layout->get_pixel_extents(dummy, rec);

					child_allocation.set_width(width - padding);
					child_allocation.set_height(height / 2 - padding);

					static LabelConfiguration bottomChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetBottomChildLabelConfiguration();
					switch(bottomChildConfiguration.GetLabelAlignment())//bottom
					{
						case Smartmatic::GUI::Configuration::LeftAlignment:
							position_x = allocation.get_x() + innerNumberWidth;
							break;
						case Smartmatic::GUI::Configuration::CenterAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width / 2 - rec.get_width() / 2;
							break;
						case Smartmatic::GUI::Configuration::RigthAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width - padding - rec.get_width();
							break;
						default:
							break;
					}

					child_allocation.set_x(position_x);
					child_allocation.set_y(allocation.get_y() + height - padding - rec.get_height());

					bottom_child->size_allocate(child_allocation);
					bottom_child->set_size_request(child_allocation.get_width(), child_allocation.get_height());
				}
				else if(top_child)
				{
					layout = top_child->get_layout();
					layout->get_pixel_extents(dummy, rec);

					child_allocation.set_width(width - padding);
					child_allocation.set_height(height - 2 * padding);

					int originalSizeFont = SAESGUIConfigurationManager::Current()->GetVotingWidgetTopChildLabelConfiguration().GetSize();

					while(rec.get_width() > width - padding)
					{
						originalSizeFont--;

						Pango::FontDescription fontTitle = top_child->get_style()->get_font();
						fontTitle.set_size(originalSizeFont*Pango::SCALE);
						top_child->modify_font(fontTitle);

						layout = top_child->get_layout();
						layout->get_pixel_extents(dummy, rec);
					}

					static Smartmatic::GUI::Configuration::LabelAlignmentEnum labelAlignment =
							SAESGUIConfigurationManager::Current()->GetReferendumBallotsLabelConfiguration().GetLabelAlignment();

					switch(labelAlignment)
					{
						case Smartmatic::GUI::Configuration::LeftAlignment:
							position_x = allocation.get_x() + innerNumberWidth;
							break;
						case Smartmatic::GUI::Configuration::CenterAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width / 2 - rec.get_width() / 2;
							break;
						case Smartmatic::GUI::Configuration::RigthAlignment:
							position_x = allocation.get_x() + innerNumberWidth + width - padding - rec.get_width();
							break;
						default:
							break;
					}

					position_y = allocation.get_y() + (height/ 2) - ((rec.get_height() / 2));

					child_allocation.set_x(position_x);
					child_allocation.set_y(position_y);

					top_child->size_allocate(child_allocation);
					top_child->set_size_request(child_allocation.get_width(), child_allocation.get_height());
				}
			}
				break;

			case VotingWidgetBase_Image:
			{
				if(image_child)
				{
					//image
					child_allocation.set_width(width - padding);
					child_allocation.set_height(height -  2 * padding);
					child_allocation.set_x(allocation.get_x() + innerNumberWidth);
					child_allocation.set_y(allocation.get_y() + padding);

					image_child->size_allocate(child_allocation);

					Glib::RefPtr<Gdk::Pixbuf> tempPixbuf = image_child->get_pixbuf();
					tempPixbuf = tempPixbuf->scale_simple(child_allocation.get_width(), child_allocation.get_height(), Gdk::INTERP_HYPER);
					image_child->set(tempPixbuf);
				}
			}
				break;

			default:
				break;
		}

		
		//number
		if(this->showNumber)
		{
		layout = number_child->get_layout();
		layout->get_pixel_extents(dummy, rec);

		position_x = allocation.get_x() + innerNumberWidth / 2 - rec.get_width() / 2;
		position_y = allocation.get_y() + height / 2  - rec.get_height() / 2;

		if(position_x < allocation.get_x() + padding) position_x = allocation.get_x() + padding;
		if(position_y < allocation.get_y() + padding) position_y = allocation.get_y() + padding;


		child_allocation.set_width(innerNumberWidth - padding);
		
		child_allocation.set_height(height - 2 * padding);
		child_allocation.set_x(position_x);
		child_allocation.set_y(position_y);

		number_child->size_allocate(child_allocation);
		number_child->set_size_request(child_allocation.get_width(), child_allocation.get_height());
		}
		sizeAllocateCallback = true;
		
	}
	//else
		//sizeAllocateCallback = false;
}

void VotingWidgetBase::forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data)
{
	if(image_child)	callback(GTK_WIDGET(image_child->gobj()), callback_data);
	if(label_child) callback(GTK_WIDGET(label_child->gobj()), callback_data);
	if(top_child) callback(GTK_WIDGET(top_child->gobj()), callback_data);
	if(bottom_child) callback(GTK_WIDGET(bottom_child->gobj()), callback_data);
	if(number_child) callback(GTK_WIDGET(number_child->gobj()), callback_data);
}

void VotingWidgetBase::on_add(Gtk::Widget* child)
{
	//No more widgets can be added.
}

void VotingWidgetBase::on_remove(Gtk::Widget* child)
{
	if(image_child)	image_child->unparent();
	if(label_child)	label_child->unparent();
	if(top_child) top_child->unparent();
	if(bottom_child) bottom_child->unparent();
	if(number_child) number_child->unparent();
}

GType VotingWidgetBase::child_type_vfunc() const
{
	//No more widgets can be added.
	return G_TYPE_NONE;
}
