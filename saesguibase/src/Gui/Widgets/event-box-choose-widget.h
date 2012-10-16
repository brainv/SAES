/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	event-box-choose-widget.h
 *
 * @brief	Declares the event box choose widget class.
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

#ifndef _EVENT_BOX_CHOOSE_WIDGET_H_
#define _EVENT_BOX_CHOOSE_WIDGET_H_
#include <gtkmm.h>
#include <iostream>
#include "Widgets/choose-dialog-button-info.h"
#include "Widgets/choose-dialog-info.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	EventBoxChooseWidget
				 *
				 * @brief	Event box choose widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class EventBoxChooseWidget : public Gtk::Frame
				{
				public:

				/**
				 * @fn	EventBoxChooseWidget::EventBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo* dialogInfo);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	dialogInfo	If non-null, information describing the dialog.
				 */

				EventBoxChooseWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo* dialogInfo);

				/**
				 * @fn	EventBoxChooseWidget::~EventBoxChooseWidget();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				~EventBoxChooseWidget();

				/**
				 * @fn	std::string EventBoxChooseWidget::getOptionValue();
				 *
				 * @brief	Gets the option value.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	The option value.
				 */

				std::string getOptionValue();

				/**
				 * @fn	std::string EventBoxChooseWidget::getOptionName();
				 *
				 * @brief	Gets the option name.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	The option name.
				 */

				std::string getOptionName();

				/**
				 * @fn	void EventBoxChooseWidget::ResizeOptionsWidgets(int WidgetOptionsWidth,
				 * 		int WidgetOptionsHeight);
				 *
				 * @brief	Resize options widgets.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	WidgetOptionsWidth 	Width of the widget options.
				 * @param	WidgetOptionsHeight	Height of the widget options.
				 */

				void ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight);

				/**
				 * @fn	void EventBoxChooseWidget::Dispose();
				 *
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void Dispose();
				protected:

				private:	

				/**
				 * @fn	bool EventBoxChooseWidget::on_option_clicked(GdkEventButton* event,
				 * 		std::string optionMarked);
				 *
				 * @brief	Executes the option clicked action.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	event	If non-null, the event.
				 * @param	optionMarked 	The option marked.
				 *
				 * @return	true if it succeeds, false if it fails.
				 */

				bool on_option_clicked(GdkEventButton* event, std::string optionMarked);	
				std::string code;   ///< The code

				/**
				 * @fn	void EventBoxChooseWidget::SetSelection(std::string optionMarked);
				 *
				 * @brief	Sets a selection.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	optionMarked	The option marked.
				 */

				void SetSelection(std::string optionMarked);
				Gdk::Color selectedColor;   ///< The selected color
				Gdk::Color unSelectedColor; ///< The un selected color
				Gtk::Frame* frameEvent; ///< The frame event
				Gtk::VBox* vboxEvents;  ///< The vbox events
				Gtk::HBox* hboxPrincipal;   ///< The hbox principal
				Gtk::EventBox* eventbox;	///< The eventbox
				std::vector<Gtk::EventBox*> eventboxList;   ///< List of eventboxes
				Gtk::Label* eventLabel; ///< The event label
				Glib::ustring optionSelected;   ///< The option selected
				Gtk::Label labelTitle;  ///< The label title
				Gtk::Image imageTitle;  ///< The image title
				int currentIndex;   ///< The current index
				int labelWidth;   ///< The label width

				};
			}
		}
	}
}



#endif // _EVENT_BOX_CHOOSE_WIDGET_H_
