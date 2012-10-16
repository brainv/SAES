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

#ifndef _VM_INSTALLATION_WIDGET_H_

/**
 * @brief	Gets the virtual memory installation widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _VM_INSTALLATION_WIDGET_H_


#include <gtkmm.h>
#include <Widgets/smartmatic-button.h>
#include "key-board-widget.h"
#include "Configuration/label-configuration.h"
//#include "Widgets/info-widget.h"
#include "Widgets/smartmatic-entry.h"



namespace Smartmatic
{
	namespace GUI
		{
			namespace Widgets
			{

				/**
				 * @brief	Values that represent VMInstallationWidgetType.
				 */

				enum VMInstallationWidgetType
				{
					OnlyKeyWord,  ///< Value that represent only keyword message.
					OnlyToken,	///< Value that represent only token message.
					keywordAndToken  ///< Value that represent keyword and token message.
				};

				class VMInstallationWidget: public Gtk::Frame
				{
				public:

					/**
					 * @brief	Default constructor, initialize all variables less 'builder' in null.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					VMInstallationWidget()
					{
						keyboard = NULL;
						frameKeyboard = NULL;
						bottomBox = NULL;
						labelMensaje = NULL;
						password = NULL;
						buttonOk = NULL;
						type = keywordAndToken;
					}

					/**
					 * @brief	Finaliser to release every variables.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					~VMInstallationWidget()
					{
						if(frameKeyboard != NULL)
						{
							delete(frameKeyboard);
						}
						if(bottomBox != NULL)
						{
							delete(bottomBox);
						}
						if(labelMensaje != NULL)
						{
							delete(labelMensaje);
						}
						if(password != NULL)
						{
							delete(password);
						}
						if(keyboard != NULL)
						{
							delete(keyboard);
						}
						if(buttonOk != NULL)
						{
							delete(buttonOk);
						}
						
					}

					/**
					 * @brief	Sets a message font.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	labelMessageConfiguration	The label message configuration.
					 */

					void SetMessageFont(Smartmatic::GUI::Configuration::LabelConfiguration labelMessageConfiguration);

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Clears the password.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void ClearPassword();

					/**
					 * @brief	Button ok set name.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	name	The name.
					 */

					void buttonOKSetName(std::string name);

					/**
					 * @brief	Set VMIntallation Type.
					 *
					 * @author	gerardo.hernandez
					 * @date	20/05/2011
					 *
					 * @param	typeA	The type.
					 */
					void setVMInstallationWidgetType(VMInstallationWidgetType typeA);

					/**
					 * @brief	Show progress.
					 *
					 * @author	gerardo.hernandez
					 * @date	20/05/2011
					 *
					 * @param	typeA	The type.
					 */
					void showProgress();

					void ResetWidgets();

					void setProgressMessage(std::string message);

					void SetButtonSize(int buttonWidth, int buttonHeight);

					sigc::signal<void,std::string> signalEnter_detected;	///< The signal enter detected
				protected:

				private:
				
					Glib::RefPtr<Gtk::Builder> builder; ///< The builder
					Gtk::Frame* framePrincipal; ///< The frame principal
					Gtk::Frame* frameKeyboard;  ///< The frame keyboard
					Gtk::VBox* bottomBox;   ///< The bottom box
					Gtk::Label *labelMensaje;   ///< The label mensaje
					SmartmaticEntry *password;   ///< The password
					SmartmaticButton *buttonOk;  ///< The button ok
					Gtk::Image* waitingTokenImage;
					Gtk::Label* waitingTokenLabel;
					Gtk::VBox* waitingTokenVBox;
					Gtk::Label*	progressLabel;
					Gtk::HButtonBox* labelhbuttonbox1;
					Gtk::HButtonBox* textEntryhbuttonbox2;
					VMInstallationWidgetType type; /// the type widget
					//Smartmatic::GUI::Widgets::SmartmaticButton* buttonOk; //I don't know if this button will be able to enter (press key)
					Smartmatic::GUI::Widgets::Keyboard* keyboard;   ///< The keyboard

					/**
					 * @brief	Handles key press signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 *
					 * @param	data	The data.
					 */

					void on_key_press(std::string data);

					/**
					 * @brief	Handles key delete press signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void on_keyDelete_press();

					/**
					 * @brief	Handles key enter press signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	27/04/2011
					 */

					void on_keyEnter_press();

					Gtk::Frame* GetProgressFrame();
					

				};

			}
	}
}

#endif // _VM_INSTALLATION_WIDGET_H_
