/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * smartmaticgui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * smartmaticgui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file confirmation-dialog-widget.h
 * @brief displays a text, with cancel and accept buttons
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _CONFIRMATION_DIALOG_WIDGET_H_

/**
 * @brief	Gets the confirmation dialog widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CONFIRMATION_DIALOG_WIDGET_H_

#include <gtkmm.h>
#include "Widgets/smartmatic-button.h"
#include "Widgets/choose-dialog-widget-child-base.h"
#include "Configuration/label-configuration.h"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ConfirmationDialogWidget: public Smartmatic::GUI::Widgets::ChooseDialogWidgetChildBase, public Gtk::VBox 
			{
			public:

				/**
				 * @brief	constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	confirmationText   	confirmation text.
				 * @param	headerTitle		   	title text.
				 * @param	footerTitle		   	footer text.
				 * @param	confirmButtonText  	custom cancel button text.
				 * @param	cancelButtonText   	custom confirmation button text.
				 * @param	placeButtonVertical	if place buttons vertical.
				 * @param	skipFalse		   	if skip true selection confirmation.
				 */

				ConfirmationDialogWidget(std::string confirmationText, std::string headerTitle, std::string footerTitle,
				                         std::string confirmButtonText = "", std::string cancelButtonText = "", 
				                         bool placeButtonVertical = false, bool skipFalse = false);

				/**
				 * @brief	destructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~ConfirmationDialogWidget();					 

				/**
				 * @brief	sets a re-confirmation widget.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	acceptSelectionText	   	confirmation text.
				 * @param	cancelSelectionText	   	title text.
				 * @param	headerTitleConfirmation	footer text.
				 * @param	footerTitleConfirmation	The footer title confirmation.
				 * @param	confirmButtonText	   	custom cancel button text.
				 * @param	cancelButtonText	   	custom confirmation button text.
				 */

				void SetReconfirmation(std::string acceptSelectionText, std::string cancelSelectionText,
 			                           std::string headerTitleConfirmation, std::string footerTitleConfirmation,
				                       std::string confirmButtonText = "", std::string cancelButtonText = "");

				/**
				 * @brief	Refreshs.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	confirmButtonText	The confirm button text.
				 * @param	cancelButtonText 	The cancel button text.
				 */

				void Refresh(std::string confirmButtonText, std::string cancelButtonText);

				/**
				 * @brief	set the confirmation text.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	confirmText	confirmation text.
				 */

				void SetConfirmationText(Glib::ustring confirmText);

				/**
				 * @brief	signals definitions.
				 */

				typedef sigc::signal<void> type_void_signal;

				/**
				 * @brief	signals connect methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal confirm_clicked();

				/**
				 * @brief	Gets the cancel clicked.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal cancel_clicked();

				/**
				 * @brief	Gets the first confirm clicked.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal first_confirm_clicked();

				/**
				 * @brief	Sets a base buttons name.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	baseName	Name of the base.
				 */

				void SetBaseButtonsName(const Glib::ustring& baseName);

				/**
				 * @brief	Sets a label configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	labelCenterConfigurationA	The label center configuration a.
				 */

				void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration& labelCenterConfigurationA);

				/**
				 * @brief	Sets a label configuration reconfirmation.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	labelConfigurationReconfirmation	The label configuration reconfirmation.
				 */

				void SetLabelConfigurationReconfirmation(Smartmatic::GUI::Configuration::LabelConfiguration& labelConfigurationReconfirmation);

				/**
				 * @brief	buttons method.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_confirmButton_clicked();

				/**
				 * @brief	Gets the header confirmation title.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The header confirmation title.
				 */

				std::string GetHeaderConfirmationTitle();

				/**
				 * @brief	Gets the footer confirmation title.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	The footer confirmation title.
				 */

				std::string GetFooterConfirmationTitle();

			protected:
	            /**
        		 * @brief signals declaration
	             */
				type_void_signal m_confirm_clicked; ///< The confirm clicked
				type_void_signal m_cancel_clicked;  ///< The cancel clicked
				type_void_signal m_first_confirm_clicked;   ///< The first confirm clicked

				/**
				 * @brief	Handles cancel button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_cancelButton_clicked();

				/**
				 * @brief	Handles confirm button duplex clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_confirmButtonDuplex_clicked();

				/**
				 * @brief	Handles cancel button duplex clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_cancelButtonDuplex_clicked();

				/**
				 * @brief	Handles retry button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_retryButton_clicked();

			private:
				/**
				* Child Widgets 
				*/
				Gtk::HBox* hButtonsBox; ///< The buttons box
				Gtk::VBox* vButtonsBox; ///< The v buttons box
				Gtk::Box* externalButtonsBox;   ///< The external buttons box
				Gtk::Alignment* buttonBoxAlignment; ///< The button box alignment
				Gtk::Label* confirmationLabel;  ///< The confirmation label
				Smartmatic::GUI::Widgets::SmartmaticButton* confirmButton;  ///< The confirm button
				Smartmatic::GUI::Widgets::SmartmaticButton* cancelButton;   ///< The cancel button
				Smartmatic::GUI::Widgets::SmartmaticButton* confirmButtonDuplex;	///< The confirm button duplex
				Smartmatic::GUI::Widgets::SmartmaticButton* cancelButtonDuplex; ///< The cancel button duplex
				
				bool secondConfirm; ///< true to second confirm
				bool selectOk;  ///< true if the select operation was a success, false if it failed
				bool skipFalse; ///< true to skip false
				bool buttonVerticals;   ///< true to button verticals

				std::string confirmationText;   ///< The confirmation text
				std::string headerTitleConfirmation;	///< The header title confirmation
				std::string footerTitleConfirmation;	///< The footer title confirmation
				std::string acceptSelectionText;	///< The accept selection text
				std::string cancelSelectionText;	///< The cancel selection text
				std::string SoundConfirmationDialog;	///< The sound confirmation dialog

				/**
				 * @brief	Configure label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void ConfigureLabel();

				/**
				 * @brief	Configure reconfirmation label.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void ConfigureReconfirmationLabel();

				/**
				 * @brief Label configurations
				 */
				Smartmatic::GUI::Configuration::LabelConfiguration labelConfiguration;  ///< The label configuration
				Smartmatic::GUI::Configuration::LabelConfiguration labelConfigurationReconfirmation;	///< The label configuration reconfirmation
			};
		}
	}
}

#endif // _CONFIRMATION_DIALOG_WIDGET_H_
