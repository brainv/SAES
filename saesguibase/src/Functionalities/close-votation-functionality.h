/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
* saesfunctionality
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _CLOSE_VOTATION_FUNCTIONALITY_H_

/**
 * @brief	Closes the votation functionality h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define _CLOSE_VOTATION_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Widgets/smartmatic-button.h>
#include "Gui/Widgets/IDCardWidgetCloseVotation.hxx"
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class CloseVotationFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{

				public:

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static CloseVotationFunctionality* Current();
					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

				protected:
					Smartmatic::GUI::Widgets::SmartmaticButton* closeVotationButton;	///< The close votation button

					/**
					 * @brief	Handles identifier card accepted signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_IdCard_accepted();

					/**
					 * @brief	Handles close votation button clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_closeVotationButton_clicked();

					/**
					 * @brief	Gets the logger.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the logger.
					 */

					Smartmatic::Log::ISMTTLog* getLogger();

					/**
					 * @brief	Gets the start log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The start log message.
					 */

					Glib::ustring getStartLogMessage();

					/**
					 * @brief	Gets the finish log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finish log message.
					 */

					Glib::ustring getFinishLogMessage();

					/**
					 * @brief	Handles confirm button clicked signals.
					 *
					 * @author	Juan.Delgado
					 * @date	29/06/2011
					 */
					void on_confirmButton_clicked();

					/**
					 * @brief	Handles cancel button clicked signal.
					 *
					 * @author	Juan.Delgado
					 * @date	29/06/2011
					 */
					void on_cancelButton_clicked();

				private:

					Gtk::Frame* externalFrame;  ///< The external frame
					Gtk::Label* titleLabel;
					Gtk::Alignment* align;  ///< The alignment
					Smartmatic::GUI::Widgets::SmartmaticButton* confirmButton;
					Smartmatic::GUI::Widgets::SmartmaticButton* cancelButton;
					Gtk::HButtonBox* buttonBox;
					Gtk::Label* labelConfirmation;
					Gtk::Label* titleLabelID;
					Smartmatic::SAES::GUI::Widgets::IDCardWidgetCloseVotation* idCardWidget; ///< The identifier card widget

					static CloseVotationFunctionality *current_instance;	///< The current instance

					Gtk::VBox* vbox;

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					CloseVotationFunctionality();

					~CloseVotationFunctionality();

					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initializes this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Initialize();

					/**
					 * @brief	Gets the frame.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else the frame.
					 */

					Gtk::Widget* GetFrame();

					/**
					 * @brief	Gets the window title.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The window title.
					 */

					std::string GetWindowTitle();

					/**
					 * @brief	Gets the menu option type.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The menu option type.
					 */

					Smartmatic::Functionality::MenuOptionDescriptor GetMenuOptionType();

					/**
					 * @brief	Execute background process for close votation functionality.
					 *
					 * @author	Gerardo.Hernandez
					 * @date	10/06/2011
					 *
					 */
					void closeVotingExperience();

					/**
					 * @brief	Load frame widget after confirmation
					 *
					 * @author	Juan.Delgado
					 * @date	29/06/2011
					 *
					 */
					void LoadAfterConfirmation();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

				};
			}
		}
	}
}


#endif // _CLOSE_VOTATION_FUNCTIONALITY_H_
