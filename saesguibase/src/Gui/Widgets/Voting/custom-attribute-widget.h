/**
 * @file	custom-attribute-widget.h
 * @brief	Declares the custom attribute widget class.
 * @author	Yadickson Soto
 * @date	28/04/2011
 */

#ifndef _CUSTOM_ATTRIBUTE_WIDGET_H_
#define _CUSTOM_ATTRIBUTE_WIDGET_H_

#include <gtkmm.h>
#include "selection-widget-base.h"
#include "Widgets/confirmation-dialog-widget.h"
#include "Widgets/choose-dialog-widget.h"
#include "Widgets/choose-dialog-button-info.h"
#include <Voting/VotingDevice/voting-devices-schema.hxx>

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
					 * @class 	CustomAttributeWidget
					 * @brief	Custom attribute widget. 
					 * @author	Yadickson Soto
					 * @date	28/04/2011
					 */
					class CustomAttributeWidget: public SelectionWidgetBase
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType  	Type of the voting mode.
						 * @param	customAttr			The custom attribute.
						 * @param	showConfirmation	true to show, false to hide the confirmation.
						 */

						CustomAttributeWidget(Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition & customAttr,
												bool showConfirmation, bool sortAlphabetically);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~CustomAttributeWidget();

						/**
						 * @brief	Defines an alias representing the string signal. .
						 */

						typedef sigc::signal<void, std::string> string_signal;

						/**
						 * @brief	Raises the answer event.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @return	.
						 */

						string_signal signal_Answer();

						/**
						 * @brief	Raises the answer event.
						 *
						 * @author	Juan.Delgado
						 * @date	19/07/2011
						 *
						 * @param	option to be selected.
						 */
						void ForceSelectedOption(std::string option);

					protected:
						string_signal m_answer_signal;  ///< The answer signal

						/**
						 * @brief	Handles question answered signals.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param [in,out]	info	If non-null, the information.
						 */

						void on_questionAnswered(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* info);

					private:

						/**
						 * @brief	Sets the strings.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType	Type of the voting mode.
						 */

						void SetStrings();

						/**
						 * @brief	Sets a base buttons.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType	Type of the voting mode.
						 */

						void SetBaseButtons();

						/**
						 * @brief	Sets the labels configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void SetLabelsConfiguration();
						
						Smartmatic::GUI::Widgets::ConfirmationDialogWidget* confirmationWidget; ///< The confirmation widget
						Smartmatic::GUI::Widgets::ChooseDialogWidget* chooseDialogWidget;   ///< The choose dialog widget
						Smartmatic::GUI::Widgets::ChooseDialogInfo* chooseDialogInfo;   ///< Information describing the choose dialog
						std::vector<Smartmatic::GUI::Widgets::ChooseDialogButtonInfo*> dialogButtonInfoList;	///< List of dialog button informations

						Glib::ustring s_HeaderQuestion; ///< The header question
						Glib::ustring s_FooterQuestion; ///< The footer question
						Glib::ustring s_HeaderQuestionConfirm;  ///< The header question confirm
						Glib::ustring s_FooterQuestionConfirm;  ///< The footer question confirm
						Glib::ustring s_CustomAttributeConfirmationFormat;  ///< The custom attribute confirmation format
						std::list<std::string> customAttrNameList;  ///< The custom attribute name list

					};
				}

			}
		}
	}
}

#endif // _CUSTOM_ATTRIBUTE_WIDGET_H_
