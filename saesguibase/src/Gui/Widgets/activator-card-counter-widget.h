/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	activator-card-counter-widget.h
 *
 * @brief	Declares the activator card counter widget class.
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

#ifndef _ACTIVATOR_CARD_COUNTER_WIDGET_H_
#define _ACTIVATOR_CARD_COUNTER_WIDGET_H_
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
				 * @class	CounterWidgetLabelCode
				 *
				 * @brief	Counter widget label code. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class CounterWidgetLabelCode
				{
					private:
					Gtk::Label* value;  ///< The value
					Gtk::Label* counter;	///< The counter
					std::string code;   ///< The code
					public:

					/**
					 * @fn	CounterWidgetLabelCode::CounterWidgetLabelCode(Gtk::Label* valueL, Gtk::Label* counterL,
					 * 		std::string codeL)
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param [in,out]	valueL  	If non-null, the value l.
					 * @param [in,out]	counterL	If non-null, the counter l.
					 * @param	codeL				The code l.
					 */

					CounterWidgetLabelCode(Gtk::Label* valueL, Gtk::Label* counterL, std::string codeL)
					{
						code = codeL;
						value = valueL;
						counter = counterL;
					}

					/**
					 * @fn	CounterWidgetLabelCode::~CounterWidgetLabelCode()
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 */

					~CounterWidgetLabelCode()
					{
						if(value!=NULL)
						{
							delete(value);
						}
						if(counter!=NULL)
						{
							delete(counter);
						}
					}

					/**
					 * @fn	std::string CounterWidgetLabelCode::getCode()
					 *
					 * @brief	Gets the code.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	The code.
					 */

					std::string getCode()
					{
						return code;
					}

					/**
					 * @fn	Gtk::Label* CounterWidgetLabelCode::getValue()
					 *
					 * @brief	Gets the value.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	null if it fails, else the value.
					 */

					Gtk::Label* getValue()
					{
						return value;
					}

					/**
					 * @fn	Gtk::Label* CounterWidgetLabelCode::getCounter()
					 *
					 * @brief	Gets the counter.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @return	null if it fails, else the counter.
					 */

					Gtk::Label* getCounter()
					{
						return counter;
					}

					/**
					 * @fn	void CounterWidgetLabelCode::setCode(std::string codeL)
					 *
					 * @brief	Sets a code.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param	codeL	The code l.
					 */

					void setCode(std::string codeL)
					{
						code = codeL;
					}

					/**
					 * @fn	void CounterWidgetLabelCode::setValue(Gtk::Label* valueL)
					 *
					 * @brief	Sets a value.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param [in,out]	valueL	If non-null, the value l.
					 */

					void setValue(Gtk::Label* valueL)
					{
						value = valueL;
					}

					/**
					 * @fn	void CounterWidgetLabelCode::setCounter(Gtk::Label* counterL)
					 *
					 * @brief	Sets a counter.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/28/2011
					 *
					 * @param [in,out]	counterL	If non-null, the counter l.
					 */

					void setCounter(Gtk::Label* counterL)
					{
						counter = counterL;
					}
				};

				/**
				 * @class	ActivatorCardCounterWidget
				 *
				 * @brief	Activator card counter widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				class ActivatorCardCounterWidget:public Gtk::HBox
				{
				public:

				/**
				 * @fn	ActivatorCardCounterWidget::ActivatorCardCounterWidget(Smartmatic::GUI::Widgets::ChooseDialogInfo* dialogInfo);
				 *
				 * @brief	Constructor.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param [in,out]	dialogInfo	If non-null, information describing the dialog.
				 */

				ActivatorCardCounterWidget(std::string code, std::string value,std::string counter);

				/**
				 * @fn	ActivatorCardCounterWidget::~ActivatorCardCounterWidget();
				 *
				 * @brief	Finaliser.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				~ActivatorCardCounterWidget();

				/**
				 * @fn	void ActivatorCardCounterWidget::Dispose();
				 *
				 * @brief	Dispose of this object, cleaning up any resources it uses.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 */

				void Dispose();

				/**
				 * @fn	std::string ActivatorCardCounterWidget::getName();
				 *
				 * @brief	Gets the name.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The name.
				 */

				std::string getCode();

				/**
				 * @fn	std::string ActivatorCardCounterWidget::getValue();
				 *
				 * @brief	Gets the value.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	The Value.
				 */						 
				std::string getValue();

				/**
				 * @fn	std::vector<CounterWidgetLabelCode*> ActivatorCardCounterWidget::getValueList();
				 *
				 * @brief	Gets the value list.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @return	null if it fails, else the value list.
				 */

				//std::vector<CounterWidgetLabelCode*> getValueList();
				//std::vector<Gtk::Label*> getCounterList();

				/**
				 * @fn	void ActivatorCardCounterWidget::ResizeOptionsWidgets(int WidgetOptionsWidth,
				 * 		int WidgetOptionsHeight);
				 *
				 * @brief	Resize options widgets.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/28/2011
				 *
				 * @param	WidgetOptionsWidth 	Width of the widget options.
				 * @param	WidgetOptionsHeight	Height of the widget options.
				 */

				void ResizeOptionsWidgets(int WidgetOptionsWidth, int WidgetOptionsHeight);
				protected:

				private:	
				std::string code;	   //// < the code
				std::string value;   /// < the value
				Gtk::Label labelCode;  ///< The label code
				Gtk::Label labelValue;  ///< The label code
				Gtk::Label labelCounter;  ///< The label code
				//std::vector<Gtk::Label*> labelCounterList;		

				};
			}
		}
	}
}

#endif // _ACTIVATOR_CARD_COUNTER_WIDGET_H_
