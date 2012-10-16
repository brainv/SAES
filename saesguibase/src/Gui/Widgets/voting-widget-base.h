/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
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
 * @file voting-widget-base.h
 * @brief widget base in voting experience
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _VOTING_WIDGET_BASE_H_
#define _VOTING_WIDGET_BASE_H_

#include <gtkmm.h>
#include "Configuration/label-configuration.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	VotingWidgetBase
				 *
				 * @brief	Voting widget base. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class VotingWidgetBase: public Gtk::Container 
				{
				public:

					/**
					 * @enum	VotingWidgetBase_Display
					 *
					 * @brief	enum for shown widgets.
					 */

					enum VotingWidgetBase_Display
					{
						VotingWidgetBase_Image,
						VotingWidgetBase_Text,
						VotingWidgetBase_DualText
					};

					/**
					 * @fn	VotingWidgetBase::VotingWidgetBase(VotingWidgetBase_Display display,
					 * 		std::string displayString, std::string number, int padding, int numberWidth,
					 * 		bool showNumberA = true);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	display		 	widget type.
					 * @param	displayString	if widget is Text is label name, if Image is image path.
					 * @param	number		 	number.
					 * @param	padding		 	widget padding.
					 * @param	numberWidth  	Number of widths.
					 * @param	width  			Widget's width.
					 * @param	height  		Widget's height.
					 * @param	showNumberA  	true to show, false to hide the number a.
  					 * @param	isReferendum  	true to set referendum mode.
					 */

					VotingWidgetBase(VotingWidgetBase_Display display, std::string displayString, std::string number, int padding, int numberWidth, int width, int height, bool showNumberA = true, bool isReferendum = false);

					/**
					 * @fn	VotingWidgetBase::VotingWidgetBase(VotingWidgetBase_Display display,
					 * 		std::string displayString, std::string number, int padding, int numberWidth,
					 * 		Smartmatic::GUI::Configuration::LabelConfiguration labelChildConfigurationA,
					 * 		bool showNumberA = true);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	display						The display.
					 * @param	displayString				The display string.
					 * @param	number						Number of.
					 * @param	padding						The padding.
					 * @param	numberWidth					Number of widths.
					 * @param	labelChildConfigurationA	The label child configuration a.
					 * @param	width  						Widget's width.
					 * @param	height  					Widget's height.
					 * @param	showNumberA					true to show, false to hide the number a.
					 */

					VotingWidgetBase(VotingWidgetBase_Display display, std::string displayString, std::string number, int padding, int numberWidth,
                                   Smartmatic::GUI::Configuration::LabelConfiguration labelChildConfigurationA, int width, int height, bool showNumberA = true);

					/**
					 * @fn	VotingWidgetBase::VotingWidgetBase(std::string topString, std::string bottomString,
					 * 		std::string number, int padding, int numberWidth, bool showNumberA = true);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	topString   	top string to be displayed.
					 * @param	bottomString	bottom string to be displayed.
					 * @param	number			number.
					 * @param	padding			widget padding.
					 * @param	numberWidth 	Number of widths.
					 * @param	width  			Widget's width.
					 * @param	height  		Widget's height.
					 * @param	showNumberA 	true to show, false to hide the number a.
					 */

					VotingWidgetBase(std::string topString, std::string bottomString, std::string number, int padding, int numberWidth, int width, int height, bool showNumberA = true);

					/*void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration labelChildConfigurationA,
												Smartmatic::GUI::Configuration::LabelConfiguration topChildConfigurationA,
												Smartmatic::GUI::Configuration::LabelConfiguration bottomChildConfigurationA,
												Smartmatic::GUI::Configuration::LabelConfiguration numberChildConfigurationA);

					void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration labelChildConfigurationA);*/

					/**
					 * @fn	VotingWidgetBase::~VotingWidgetBase();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~VotingWidgetBase();

					/**
					 * @fn	void VotingWidgetBase::Initialize();
					 *
					 * @brief	create child widgets.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	width  	Widget's width.
					 * @param	height  Widget's height.
					 */

					void Initialize(int width, int height);

					/**
					 * @brief	set size elements.
					 *
					 * @author	Yadickson Soto
					 * @date	16/03/2012
					 *
					 * @param	width  	Widget's width.
					 * @param	height  Widget's height.
					 */
					void setSize(int width, int height);

				protected:
				    /**
					 * Overrided virtual method from Gtk::Container
		             */
					//virtual void on_size_request(Gtk::Requisition* requisition);

					/**
					 * @fn	virtual void VotingWidgetBase::on_size_allocate(Gtk::Allocation& allocation);
					 *
					 * @brief	Handles size allocate signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	allocation	The allocation.
					 */

					virtual void on_size_allocate(Gtk::Allocation& allocation);

					/**
					 * @fn	virtual void VotingWidgetBase::forall_vfunc(gboolean include_internals,
					 * 		GtkCallback callback, gpointer callback_data);
					 *
					 * @brief	Forall vfunc.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	include_internals	The include internals.
					 * @param	callback		 	The callback.
					 * @param	callback_data	 	Information describing the callback.
					 */

					virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);

					/**
					 * @fn	virtual void VotingWidgetBase::on_add(Gtk::Widget* child);
					 *
					 * @brief	Handles add signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	child	If non-null, the child.
					 */

					virtual void on_add(Gtk::Widget* child);

					/**
					 * @fn	virtual void VotingWidgetBase::on_remove(Gtk::Widget* child);
					 *
					 * @brief	Handles remove signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	child	If non-null, the child.
					 */

					virtual void on_remove(Gtk::Widget* child);

					/**
					 * @fn	virtual GType VotingWidgetBase::child_type_vfunc() const;
					 *
					 * @brief	Gets the child type vfunc.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					virtual GType child_type_vfunc() const;

				private:
					/**
					 * Child Widgets
					 */
					Glib::RefPtr<Gdk::Pixbuf> pixbuf;   ///< The pixbuf
					Gtk::Image* image_child;	///< The image child
					Gtk::Label* label_child;	///< The label child
					Gtk::Label* top_child;  ///< The top child
					Gtk::Label* bottom_child;   ///< The bottom child
					Gtk::Label* number_child;   ///< Number of childs

					/**
					 * Variables
					 */
					bool showNumber;	///< true to show, false to hide the number
					bool isReferendum;	///< true to show, false to hide the number
					int numberWidth;	///< Number of widths
					int padding;	///< The padding
					bool sizeAllocateCallback;  ///< true to size allocate callback
					VotingWidgetBase_Display display;   ///< The display
					std::string number; ///< Number 
					std::string displayString;  ///< The display string
					std::string topString;  ///< The top string
					std::string bottomString;   ///< The bottom string
					
				};
			}
		}
	}
}

#endif // _VOTING_WIDGET_BASE_H_
