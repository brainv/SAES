/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	custom-attributes-combo-selections-widget.h
 *
 * @brief	Declares the custom attributes combo selections widget class.
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

#ifndef _CUSTOM_ATTRIBUTES_COMBO_SELECTIONS_WIDGET_H_
#define _CUSTOM_ATTRIBUTES_COMBO_SELECTIONS_WIDGET_H_
#include <gtkmm.h>
#include <iostream>
#include "Widgets/choose-dialog-button-info.h"
#include "Widgets/choose-dialog-info.h"
#include "Gui/Widgets/combo-box-choose-widget.h"
#include "Gui/Widgets/event-box-choose-widget.h"
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	ComboInfo
				 *
				 * @brief	Information about the combo. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ComboInfo
				{
				public:

					/**
					 * @fn	ComboInfo::ComboInfo(std::string name, std::string value)
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	name 	The name.
					 * @param	value	The value.
					 */

					ComboInfo(std::string name, std::string value)
					{
						optionName = name;
						optionValue = value;
					}

					/**
					 * @fn	std::string ComboInfo::getValue()
					 *
					 * @brief	Gets the value.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The value.
					 */

					std::string getValue()
					{
						return optionValue;
					}

					/**
					 * @fn	std::string ComboInfo::getName()
					 *
					 * @brief	Gets the name.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The name.
					 */

					std::string getName()
					{
						return optionName;
					}	
				private:
					std::string optionValue;	///< The option value
					std::string optionName; ///< Name of the option
				};

				/**
				 * @class	CustomAttributesComboSelectionsWidget
				 *
				 * @brief	Custom attributes combo selections widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class CustomAttributesComboSelectionsWidget:public Gtk::VBox
				{
				public:						

				/**
				 * @fn	CustomAttributesComboSelectionsWidget::CustomAttributesComboSelectionsWidget(std::string labelTitle,
				 * 		std::string imagePath, bool isEventType);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param	labelTitle 	The label title.
				 * @param	imagePath  	Full pathname of the image file.
				 * @param	isEventType	true if is event type.
				 */

				CustomAttributesComboSelectionsWidget(std::string labelTitle,std::string imagePath, bool isEventType);

				/**
				 * @fn	void CustomAttributesComboSelectionsWidget::addComboWidget(ComboBoxChooseWidget* comboWidget);
				 *
				 * @brief	Adds a combo widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	comboWidget	If non-null, the combo widget.
				 */

				void addComboWidget(ComboBoxChooseWidget* comboWidget);	

				/**
				 * @fn	void CustomAttributesComboSelectionsWidget::addBoxWidget(EventBoxChooseWidget* comboWidget);
				 *
				 * @brief	Adds a box widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @param [in,out]	comboWidget	If non-null, the combo widget.
				 */

				void addBoxWidget(EventBoxChooseWidget* comboWidget);	

				/**
				 * @fn	void CustomAttributesComboSelectionsWidget::ResizeOptionsWidgets(int WidgetOptionsWidth,
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
				 * @fn	CustomAttributesComboSelectionsWidget::~CustomAttributesComboSelectionsWidget();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				~CustomAttributesComboSelectionsWidget();

				/**
				 * @fn	void CustomAttributesComboSelectionsWidget::Dispose();
				 *
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				void Dispose();

				/**
				 * @fn	std::vector<ComboInfo> CustomAttributesComboSelectionsWidget::getOptionsSelected();
				 *
				 * @brief	Gets the options selected.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 *
				 * @return	The options selected.
				 */

				std::vector<ComboInfo> getOptionsSelected();
				protected:

				private:	
				bool isEvent;   ///< true if is event
				std::vector<ComboBoxChooseWidget*> listOfCombos;	///< The list of combos
				std::vector<EventBoxChooseWidget*> listOfBoxes; ///< The list of boxes
				Gtk::Label labelTitle;  ///< The label title
				Gtk::EventBox eventBoxTitle;	///< The event box title
				Gtk::HBox hboxHeader;   ///< The hbox header
				Gtk::Image imageTitle;  ///< The image title
				std::vector<Smartmatic::GUI::Widgets::ChooseDialogInfo*> listOfChoices; ///< The list of choices
				};
			}
		}
	}
}

#endif // _CUSTOM_ATTRIBUTES_COMBO_SELECTIONS_WIDGET_H_
