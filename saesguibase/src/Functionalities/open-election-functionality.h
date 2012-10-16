/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
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

#ifndef _OPEN_ELECTION_FUNCTIONALITY_H_

/**
 * @brief	Opens the election functionality h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define _OPEN_ELECTION_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Widgets/menu-option.h>
#include <Gui/Widgets/id-card-widget-open-election.h>
#include <Functionalities/graphic-display-functionality.h>
#include <Widgets/wizard-widget-manager.h>
#include <Widgets/wizard-widget-base.h>
#include <Log/ISMTTLog.h>
#include <Gui/Widgets/OpenNoteWidget.hxx>
#include <Gui/Widgets/OpenElectionStatusWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class OpenElectionFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
				{

				public:
					/**
					 * @brief Class destroy
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					virtual ~OpenElectionFunctionality();

					/**
					 * @brief	Gets the current.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	null if it fails, else.
					 */

					static OpenElectionFunctionality* Current();

				protected:

					/**
					 * @brief method finish functionality
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void finish();
					/**
					 * @brief method error functionality
					 * @date 10/05/2012
					 * @author Yadickson Soto
					 */
					void errorHappen();

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
					 * @brief	Gets the finis ah log message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	The finis ah log message.
					 */

					Glib::ustring getFinishLogMessage();
						
				private:
					Gtk::Frame* openFrame; ///< open frame

					Smartmatic::SAES::GUI::Widgets::IDCardWidgetOpenElection* idCard;   ///< The identifier card
					Smartmatic::SAES::GUI::Widgets::OpenNoteWidget * openNoteWidget;	///< The open note widget
					Smartmatic::SAES::GUI::Widgets::OpenElectionStatusWidget * openElectionWidget; ///< open election widget

					Smartmatic::GUI::Widgets::WizardWidgetManager* manager; ///< manage wizard
					std::vector<Smartmatic::GUI::Widgets::WizardWidgetBase*> wizardVector; ///< wizard vector

					/**
					 * @brief	Shows the message.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @param	message	The message.
					 */

					void ShowMessage(std::string message);

					/**
					 * @brief	Shows the note.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void ShowNote();

					/**
					 * @brief	Gets the check if can open by date.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool checkIfCanOpenByDate();

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					OpenElectionFunctionality();


					/**
					 * @brief	Dispose of this object, cleaning up any resources it uses.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Dispose();

					/**
					 * @brief	Initia alize.
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
					 * @brief	Enables this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool Enable();

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
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

					static OpenElectionFunctionality *current_instance; ///< The current instance
					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger
				};
			}
		}
	}
}




#endif // _OPEN_ELECTION_FUNCTIONALITY_H_
