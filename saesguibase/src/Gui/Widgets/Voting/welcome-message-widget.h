/**
 * @file	welcome-message-widget.h
 *
 * @brief	Declares the welcome message widget class.
 */

#ifndef _WELCOME_MESSAGE_WIDGET_H_
#define _WELCOME_MESSAGE_WIDGET_H_

#include <gtkmm.h>
#include "selection-widget-base.h"
#include "Widgets/confirmation-dialog-widget.h"
#include "Widgets/choose-dialog-widget.h"
#include "Configuration/label-configuration.h"

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
					 * @brief	Welcome message widget. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class WelcomeMessageWidget: public SelectionWidgetBase
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	messageString 	The message string.
						 * @param	closeTimer	  	The close timer.
						 * @param	showButton	  	true to show, false to hide the button.
						 */

						WelcomeMessageWidget(std::string messageString, int closeTimer, bool showButton);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~WelcomeMessageWidget();

						/**
						 * @brief	Sets a label configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	labelConf	The label conf.
						 */

						void SetLabelConfiguration(Smartmatic::GUI::Configuration::LabelConfiguration labelConf);

						/**
						 * @brief	Raises the timeout event.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @return	The signal
						 */

						void_signal signal_Timeout();

					protected:
						void_signal m_timeout_signal;   ///< The timeout signal

						/**
						 * @brief	Handles timeout signals.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						void on_Timeout();

					private:
						/**
						 * @brief	Sets a base buttons.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType	Type of the voting mode.
						 */

						void SetBaseButtons();
						
						Smartmatic::GUI::Widgets::MessageWidget* messageWidget; ///< The message widget
						Smartmatic::GUI::Widgets::ChooseDialogWidget* chooseDialogWidget;   ///< The choose dialog widget

						Gtk::Label* label;  ///< The label

					};
				}

			}
		}
	}
}

#endif // _WELCOME_MESSAGE_WIDGET_H_
