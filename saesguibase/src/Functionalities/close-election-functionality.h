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
#ifndef _CLOSE_ELECTION_FUNCTIONALITY_H_

/**
 * @brief	Closes the election functionality h.
 *
 * @author	Luiggi.mendez
 * @date	28/04/2011
 */

#define _CLOSE_ELECTION_FUNCTIONALITY_H_

#include <gtkmm.h>
#include <iostream>
#include <string.h>
#include <Functionalities/menu-option-descriptor.h>
#include <Functionalities/graphic-display-functionality.h>
#include "Gui/Widgets/id-card-widget-close-election.h"
#include <Widgets/wizard-widget-manager.h>
#include <Widgets/wizard-widget-base.h>
#include "Gui/Widgets/persist-transmission-package-widget.h"
#include "Gui/Widgets/PersistCodiFilesWidget.hxx"
#include "Gui/Widgets/sign-transmission-package-widget.h"
#include "Gui/Widgets/close-election-status-widget.h"
#include "Gui/Widgets/report-printing-close-widget.h"
#include "Gui/Widgets/generate-pv-report-widget.h"
#include "Gui/Widgets/Voting/PBReports/CloseNoteWidget.hxx"
#include "Gui/Widgets/Voting/PBReports/statistic-counter-register-widget.h"
#include "Gui/Widgets/duration-verification-widget.h"
#include "Gui/Widgets/sign-election-resource-widget.h"
#include "Gui/Widgets/close-election-confirmation-widget.h"
#include "Gui/Widgets/PersistAllResultWidget.hxx"
#include <Log/ISMTTLog.h>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Functionality
			{
				class CloseElectionFunctionality: public GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>
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

					static CloseElectionFunctionality* Current();

					/**
					 * @brief method delete all element
					 * @date 03/04/2012
					 * @author Yadickson Soto
					 */
					virtual void deleteElement();

					virtual bool CanExecute();
				protected:

					/**
					 * @brief	Handles cancel button clicked signal.
					 *
					 * @author	Juan.Delgado
					 * @date	30/06/2011
					 */
					void on_cancelButton_clicked();

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

				private:
					void ErrorHappen();
					Gtk::Frame* closeFrame;
					Smartmatic::SAES::GUI::Widgets::PersistTransmissionPackageWidget* persistPackage;
					Smartmatic::SAES::GUI::Widgets::SignTransmissionPackageWidget* signPackage;
					Smartmatic::SAES::GUI::Widgets::CloseElectionStatusWidget* closeStatus;
					Smartmatic::SAES::GUI::Widgets::ReportPrintingCloseWidget* printWidget;
					Smartmatic::SAES::GUI::Widgets::GeneratePVReportWidget* generatePVReport;
					Smartmatic::SAES::GUI::Widgets::Voting::PBReports::CloseNoteWidget* noteRegisterWidget;
					Smartmatic::SAES::GUI::Widgets::Voting::PBReports::StatisticCounterRegisterWidget* statCounterWidget;
					Smartmatic::SAES::GUI::Widgets::DurationVerificationWidget* durationWidget;
					Smartmatic::SAES::GUI::Widgets::SignElectionResourceWidget* signElection;
					Smartmatic::SAES::GUI::Widgets::CloseElectionConfirmationWidget* closeConfirmation;
					Smartmatic::SAES::GUI::Widgets::PersistCodiFilesWidget * persistCodiFilesWidget; ///<widget for persist codi files widget
					Smartmatic::SAES::GUI::Widgets::PersistAllResultWidget * persistAllResultWidget; ///<widget persist all result files
					Smartmatic::GUI::Widgets::WizardWidgetManager* manager;

					int count; ///< count state
					Gtk::Alignment* questionAlign; 	///< The question align

					/**
					 * @brief	Gets the check if can close by date.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					bool checkIfCanCloseByDate();

					/**
					 * @brief	Sets the label in election was closed
					 *
					 * @author	Juan.Delgado
					 * @date	15/08/2011
					 */

					void ElectionWasClosed();

					Smartmatic::SAES::GUI::Widgets::IDCardWidgetCloseElection* idCardWidget;	///< The identifier card widget

					/**
					 * @brief	Finishs this object.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void Finish();
					
					/**
					 * @brief	Transition signal
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */
					void TransitionSignal();

					static CloseElectionFunctionality *current_instance;	///< The current instance

					/**
					 * @brief	Default constructor.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					CloseElectionFunctionality();

					~CloseElectionFunctionality();

					/**
					 * @brief	Handles close clicked signals.
					 *
					 * @author	Luiggi.mendez
					 * @date	28/04/2011
					 */

					void on_close_clicked();

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
					 * @brief	Load the Wizard Frame.
					 *
					 * @author	Juan.Delgado
					 * @date	30/06/2011
					 */
					void LoadWizardFrame();

					static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

					std::vector<Smartmatic::GUI::Widgets::WizardWidgetBase*> wizardVector;

					int countGeneratePV; ///< count pv
					int countGenerateAllResult; ///< count all result
				};
			}
		}
	}
}

#endif // _CLOSE_ELECTION_FUNCTIONALITY_H_
