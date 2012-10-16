/**
 * @file	language-selection-widget.h
 * @brief	Declares the language selection widget class.
 * @author	Yadickson Soto
 * @date	28/04/2011
 */

#ifndef _LANGUAGE_SELECTION_WIDGET_H_
#define _LANGUAGE_SELECTION_WIDGET_H_

#include "Voting/Election/ElectionWrapper.hxx"
#include <Widgets/ChooseSelectionWidget.hxx>

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
					 * @class LanguageSelectionWidget
					 * @brief	Language selection widget. 
					 * @author	Yadickson Soto
					 * @date	28/04/2011
					 */
					class LanguageSelectionWidget: public Smartmatic::GUI::Widgets::ChooseSelectionWidget
					{
					public:

						/**
						 * @brief	Class constructor.
						 * @param	showConfirmation	   	true to show confirmation.
						 * @param	sortAlphabetically	   	true to sort alphabetically
						 * @author	Yadickson Soto
						 * @date	13/04/2012
						 */
						LanguageSelectionWidget(bool showConfirmation, bool sortAlphabetically = false);
						/**
						 * @brief	Class destroy
						 * @author	Yadickson Soto
						 * @date	13/04/2012
						 */
						virtual ~LanguageSelectionWidget();
						/**
						 * @brief	Method reload language
						 * @author	Yadickson Soto
						 * @date	13/04/2012
						 */
						void  reload();
						/**
						 * @brief	Shows the widget.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool ShowWidget();

						/**
						 * @brief	Sets the back language.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void SetBackLanguage();

						/**
						 * @brief	Simulate the press of the button indexed in N
						 *
						 * @author	Juan.delgado
						 * @date	13/07/2011
						 *
						 * @param code 		code of the language
						 * @param option 	option of the language
						 *
						 * @return code of language simulated
						 */
						std::string SimulateButtonNPressed(int index);//;std::string code, std::string option);
						/**
						 * @brief virtual method init
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						virtual void initialize();
						/**
						 * @brief virtual method stop
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						virtual void dispose();
						/**
						 * @brief method refresh widget
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();

					protected:

						/**
						 * @brief Method getter language selected
						 * @param choose option selected
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						virtual void onSelected(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* choose);
						/**
						 * @brief method signal option pre selected
						 * @param choose option selected
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						virtual void onPreSelected(Smartmatic::GUI::Widgets::ChooseDialogButtonInfo* choose);
						/**
						 * @brief method signal option pre selected back
						 * @date 13/04/2012
						 * @author Yadickson Soto
						 */
						virtual void onPreSelectedBack();

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

						Smartmatic::GUI::Widgets::ConfirmationDialogWidget* confirmationWidget; ///< The confirmation widget
						Smartmatic::GUI::Widgets::ChooseDialogInfo* chooseDialogInfo;   ///< Information describing the choose dialog
						std::vector<Smartmatic::GUI::Widgets::ChooseDialogButtonInfo*> dialogButtonInfoList;	///< List of dialog button informations
						std::list<std::string> languagesList; ///< language list

						bool showWidget;	///< true to show, false to hide the widget
						bool showConfirmation; ///< flag show confirmation
						bool sortAlphabetically; ///< flag sort alphabetically
						std::string previousLanguage;   ///< The previous language
		                std::string previousCountry;	///< The previous country

						Glib::ustring s_Title;  ///< The title
						Glib::ustring s_Footer; ///< The footer
						Glib::ustring s_ConfirmationTitle;  ///< The confirmation title
						Glib::ustring s_ConfirmationFooter; ///< The confirmation footer
						Glib::ustring s_ConfirmationFormat; ///< The confirmation format
						Glib::ustring s_ConfirmationAcceptButton;   ///< The confirmation accept button
						Glib::ustring s_ConfirmationRetryButton;	///< The confirmation retry button

					};
				}
			}
		}
	}
}

#endif // _LANGUAGE_SELECTION_WIDGET_H_
