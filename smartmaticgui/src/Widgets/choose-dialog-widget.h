/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * smartmaticgui
 * Copyright (C)  2011 <>
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

#ifndef _CHOOSE_DIALOG_WIDGET_H_

/**
 * @brief	Gets the choose dialog widget h.
 *
 * @author	Luiggi.mendez
 * @date	27/04/2011
 */

#define _CHOOSE_DIALOG_WIDGET_H_

#include <iostream>
#include <vector>
#include <string>
#include <gtkmm.h>
#include "Widgets/choose-dialog-button-info.h"
#include "Widgets/choose-dialog-info.h"
#include "Widgets/confirmation-dialog-widget.h"
#include "Widgets/dialog-widget-base.h"
#include "Widgets/smartmatic-button.h"
#include "Widgets/message-widget.h"
#include "Configuration/label-configuration.h"
#include "RefreshListener.hxx"

namespace Smartmatic
{
	namespace GUI
	{
		namespace Widgets
		{
			class ChooseDialogWidget: public DialogWidgetBase, public RefreshListener
			{
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	messageWidget	If non-null, the message widget.
				 */

				ChooseDialogWidget(MessageWidget* messageWidget);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	dialogInfo		  	If non-null, information describing the dialog.
				 * @param [in,out]	confirmationWidget	If non-null, the confirmation widget.
				 */

				ChooseDialogWidget(ChooseDialogInfo* dialogInfo, ConfirmationDialogWidget* confirmationWidget);

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	confirmationWidget	If non-null, the confirmation widget.
				 */

				ChooseDialogWidget(ConfirmationDialogWidget* confirmationWidget);

				/**
				 * @brief	Finaliser.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				~ChooseDialogWidget();

				/**
				 * @brief	Refreshs.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	headerLabel	The header label.
				 * @param	footerLabel	The footer label.
				 */

				void Refresh(std::string headerLabel, std::string footerLabel);

				/**
				 * @brief	signals definitions.
				 */

				typedef sigc::signal<void> type_void_signal;

				/**
				 * @brief	Defines an alias representing the type choose dialog signal. .
				 */

				typedef sigc::signal<void, ChooseDialogButtonInfo*> type_chooseDialog_signal;

				/**
				 * @brief	signals connect methods.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_accept_signal();

				/**
				 * @brief	Executes the cancel signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_cancel_signal();

				/**
				 * @brief	Executes the first confirm signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_first_confirm_signal();

				/**
				 * @brief	Executes the cancel intermediate signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_cancel_intermediate_signal();

				/**
				 * @brief	Executes the close signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_void_signal on_close_signal();

				/**
				 * @brief	Executes the accept intermediate signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_chooseDialog_signal on_accept_intermediate_signal();

				/**
				 * @brief	Executes the choose signal action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @return	.
				 */

				type_chooseDialog_signal on_choose_signal();

				/**
				 * @brief	Sets a confirmation string format.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	format	Describes the format to use.
				 */

				void SetConfirmationStringFormat(Glib::ustring& format);

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
				 * @brief	Executes the option selected action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	index	Zero-based index of the.
				 */

				void onOptionSelected(int index);

				/**
				 * @brief	Executes the option selected action.
				 *
				 * @author	Juan.Delgado
				 * @date	19/07/2011
				 *
				 * @param	index	Zero-based index of the.
				 *
				 * @return	code of option selected
				 */
				std::string onOptionSelectedSim(int index);

				/**
				 * @brief virtual method refresh
				 * @date 03/04/2012
				 * @author Yadickson Soto
				 */
				virtual void refresh();

			protected:
	            /**
        		 * @brief signals declaration
	             */
				type_void_signal m_type_accept; ///< The type accept
				type_void_signal m_type_cancel; ///< The type cancel
				type_void_signal m_type_cancel_intermediate;	///< The type cancel intermediate
				type_void_signal m_type_close;  ///< The type close
				type_chooseDialog_signal m_type_accept_intermediate;	///< The type accept intermediate
				type_chooseDialog_signal m_type_choose; ///< The type choose

					
			private:

				/**
				 * @brief	Sends the on accept signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_accept_signal();

				/**
				 * @brief	Sends the on cancel signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_cancel_signal();

				/**
				 * @brief	Sends the on first confirm signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_first_confirm_signal();

				/**
				 * @brief	Sends the on cancel intermediate signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_cancel_intermediate_signal();

				/**
				 * @brief	Sends the on choose signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_choose_signal();

				/**
				 * @brief	Sends the on close signal.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void send_on_close_signal();

				/**
				 * @brief	Sets the labels properties.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetLabelsProperties();

				/**
				 * @brief	Sets the confirmation label properties.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void SetConfirmationLabelProperties();

				MessageWidget* messageWidget;   ///< The message widget
				ChooseDialogInfo* chooseDialogInfo; ///< Information describing the choose dialog
				ConfirmationDialogWidget* confirmationWidget;   ///< The confirmation widget
				Glib::ustring _format;  ///< Describes the format to use

				int currentIndex;   ///< The current index
					
				/**
				 * @brief	Executes the option button action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	index	Zero-based index of the.
				 */

				void onOptionButton(int index);

				/**
				 * @brief	Executes the cancel button action.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void onCancelButton();

				/**
				 * @brief	Handles back button clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_backButton_clicked();

				/**
				 * @brief	Handles accept clicked signals.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 */

				void on_accept_clicked();

				/**
				 * @brief	Sets a label configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	label	The label.
				 * @param	configuration	The configuration.
				 */

				void SetLabelConfiguration(Gtk::Label & label, Smartmatic::GUI::Configuration::LabelConfiguration configuration);
					
				Gtk::HBox hboxHeader;   ///< The hbox header
				Gtk::Frame frameOptions;	///< Options for controlling the frame
				Gtk::HBox hboxFooter;   ///< The hbox footer
				Gtk::Image imageTitle;  ///< The image title
				Gtk::Label labelTitle;  ///< The label title
				Gtk::Label labelFooter; ///< The label footer
				Gtk::VButtonBox buttonOptionsBox;   ///< The button options box
				SmartmaticButton buttonCancel;  ///< The button cancel
				SmartmaticButton backButton;	///< The back button
				bool showBack;  ///< true to show, false to hide the back
				Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConfiguration; ///< The label title configuration
				Smartmatic::GUI::Configuration::LabelConfiguration labelFooterConfiguration;	///< The label footer configuration

				Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConfigurationConfirmation; ///< The label title configuration confirmation
				Smartmatic::GUI::Configuration::LabelConfiguration labelFooterConfigurationConfirmation;	///< The label footer configuration confirmation
				std::string SoundChooseDialog;  ///< The sound choose dialog
					
			public:

				/**
				 * @brief	Constructor.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param [in,out]	dialogInfo	If non-null, information describing the dialog.
				 * @param	showBack		  	true to show, false to hide the back.
				 */

				ChooseDialogWidget(ChooseDialogInfo* dialogInfo, bool showBack = false);
				sigc::signal<void,ChooseDialogButtonInfo*> signal_detected; ///< The signal detected

				sigc::signal<void> signal_back_clicked; ///< The signal back clicked

				/**
				 * @brief	Sets a label configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	labelTitleConfiguration 	The label title configuration.
				 * @param	labelFooterConfiguration	The label footer configuration.
				 */

				void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConfiguration,
				                           Smartmatic::GUI::Configuration::LabelConfiguration labelFooterConfiguration);

				/**
				 * @brief	Sets a label confirmation configuration.
				 *
				 * @author	Luiggi.mendez
				 * @date	27/04/2011
				 *
				 * @param	labelTitleConfiguration 	The label title configuration.
				 * @param	labelFooterConfiguration	The label footer configuration.
				 */

				void SetLabelConfirmationConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration labelTitleConfiguration,
				                                       Smartmatic::GUI::Configuration::LabelConfiguration labelFooterConfiguration);
					
			};
		}
	}
}

#endif // _CHOOSE_DIALOG_WIDGET_H_

