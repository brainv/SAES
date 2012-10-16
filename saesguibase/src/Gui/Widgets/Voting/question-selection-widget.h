/**
 * @file	question-selection-widget.h
 *
 * @brief	Declares the question selection widget class.
 */

#ifndef _QUESTION_SELECTION_WIDGET_H_
#define _QUESTION_SELECTION_WIDGET_H_

#include <gtkmm.h>
#include "selection-widget-base.h"
#include "Widgets/confirmation-dialog-widget.h"
#include "Widgets/choose-dialog-widget.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					/**
					 * @brief	Question selection widget. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class QuestionSelectionWidget: public SelectionWidgetBase
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	showConfirmation	true to show, false to hide the confirmation.
						 * @param	buttonsVertical 	true to buttons vertical.
						 * @param	switchButtons   	true to switch buttons.
						 */

						QuestionSelectionWidget(bool showConfirmation, bool buttonsVertical);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~QuestionSelectionWidget();

						/**
						 * @brief	Sets the strings.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	s_Question			 	The question.
						 * @param	s_Header			 	The header.
						 * @param	s_Footer			 	The footer.
						 * @param	s_HeaderConfirmation 	The header confirmation.
						 * @param	s_FooterConfirmation 	The footer confirmation.
						 * @param	s_AcceptButton		 	The accept button.
						 * @param	s_CancelButton		 	The cancel button.
						 * @param	s_AcceptConfirmation 	The accept confirmation.
						 * @param	s_CancelConfirmation 	The cancel confirmation.
						 * @param	s_ReconfirmButtonText	The reconfirm button text.
						 * @param	s_RetryButtonText	 	The retry button text.
						 */

						void SetStrings(Glib::ustring s_Question, Glib::ustring s_Header, Glib::ustring s_Footer,
						                Glib::ustring s_HeaderConfirmation, Glib::ustring s_FooterConfirmation,
						                Glib::ustring s_AcceptButton, Glib::ustring s_CancelButton,
						                Glib::ustring s_AcceptConfirmation = "", Glib::ustring s_CancelConfirmation = "",
						                Glib::ustring s_ReconfirmButtonText = "", Glib::ustring s_RetryButtonText = "");

						/**
						 * @brief	Sets the labels configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	headerLabelConf	The header label conf.
						 * @param	footerLabelConf	The footer label conf.
						 * @param	centerlabelConf	The centerlabel conf.
						 */

						void SetLabelsConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration headerLabelConf,
						                            Smartmatic::GUI::Configuration::LabelConfiguration footerLabelConf,
						                            Smartmatic::GUI::Configuration::LabelConfiguration centerlabelConf);

						/**
						 * @brief	Sets the labels configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	headerLabelConf 	The header label conf.
						 * @param	footerLabelConf 	The footer label conf.
						 * @param	centerlabelConf 	The centerlabel conf.
						 * @param	confirmLabelConf	The confirm label conf.
						 */

						void SetLabelsConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration headerLabelConf,
						                            Smartmatic::GUI::Configuration::LabelConfiguration footerLabelConf,
						                            Smartmatic::GUI::Configuration::LabelConfiguration centerlabelConf,
						                            Smartmatic::GUI::Configuration::LabelConfiguration confirmLabelConf);
						
						void Initialize();

						/**
						 * @brief	Raises the accept event.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @return	The signal
						 */

						void_signal signal_accept();

						/**
						 * @brief	Raises the cancel event.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @return	The signal
						 */

						void_signal signal_cancel();
					                                                
						/**
						 * @brief	refresh.
						 * @author Yadickson Soto
						 * @date	02/07/2012
						 */
						virtual void refresh();

					protected:
						void_signal m_accept_signal;	///< The accept signal
						void_signal m_cancel_signal;	///< The cancel signal

						/**
						 * @brief	Handles accept signals.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void on_accept();

						/**
						 * @brief	Handles cancel signals.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void on_cancel();

						/**
						 * @brief	Sets the strings.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						virtual void SetStrings();

						/**
						 * @brief	Sets the labels configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						virtual void SetLabelsConfiguration();

						/**
						 * @brief	Sets a base buttons.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void SetBaseButtons();
						
						Smartmatic::GUI::Widgets::ConfirmationDialogWidget* confirmationWidget; ///< The confirmation widget
						Smartmatic::GUI::Widgets::ChooseDialogWidget* chooseDialogWidget;   ///< The choose dialog widget

						bool showConfirmation;  ///< true to show, false to hide the confirmation
						bool buttonsVertical;   ///< true to buttons vertical
							
						Glib::ustring s_Question;   ///< The question
						Glib::ustring s_Header; ///< The header
						Glib::ustring s_Footer; ///< The footer
						Glib::ustring s_HeaderConfirmation; ///< The header confirmation
						Glib::ustring s_FooterConfirmation; ///< The footer confirmation
						Glib::ustring s_AcceptButton;   ///< The accept button
						Glib::ustring s_CancelButton;   ///< The cancel button
						Glib::ustring s_AcceptConfirmation; ///< The accept confirmation
						Glib::ustring s_CancelConfirmation; ///< The cancel confirmation
						Glib::ustring s_ReconfirmButtonText;	///< The reconfirm button text
						Glib::ustring s_RetryButtonText;	///< The retry button text

						Smartmatic::GUI::Configuration::LabelConfiguration headerLabelConf; ///< The header label conf
                        Smartmatic::GUI::Configuration::LabelConfiguration footerLabelConf; ///< The footer label conf
                        Smartmatic::GUI::Configuration::LabelConfiguration centerlabelConf; ///< The centerlabel conf
                        Smartmatic::GUI::Configuration::LabelConfiguration confirmLabelConf;	///< The confirm label conf

					};
				}

			}
		}
	}
}

#endif // _QUESTION_SELECTION_WIDGET_H_
