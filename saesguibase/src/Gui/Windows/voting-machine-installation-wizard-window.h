/**
 * @file	voting-machine-installation-wizard-window.h
 *
 * @brief	Declares the voting machine installation wizard Windows Form.
 */

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

#ifndef _VOTING_MACHINE_INSTALLATION_WIZARD_WINDOW_H_
#define _VOTING_MACHINE_INSTALLATION_WIZARD_WINDOW_H_
#include <string.h>
#include <Gui/Windows/empty-window.h>
#include <Gui/Widgets/voting-machine-installation-wizard-widget.h>
namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Windows
			{
				/**
				 * @brief	Form for viewing the voting machine installation wizard. 
				 */

				class VotingMachineInstallationWizardWindow: public EmptyWindow
				{
					private:

						/**
						 * @brief	Builds automatic.
						 */

						void BuildAutomatic();

						Gtk::Frame* framePrincipal; ///< principal frame 
						sigc::connection connHide;  ///< hide connection 
						Smartmatic::SAES::GUI::Widgets::VotingMachineInstallationWizardWidget* wizardWidget;	///< wizard widget

						/**
						 * @brief	Hides on finish.
						 */

						void HideOnFinish();
					public:

						/**
						 * @brief	Finaliser.
						 */

						~VotingMachineInstallationWizardWindow();

						/**
						 * @brief	Default constructor.
						 */

						VotingMachineInstallationWizardWindow();

						/**
						 * @brief	Dispose of this object, cleaning up any resources it uses.
						 */

						void Dispose();

						/**
						 * @brief	Initializes this object.
						 */

						void Initialize();
						


				};
			}
		}
	}
}



#endif // _VOTING_MACHINE_INSTALLATION_WIZARD_WINDOW_H_
