/**
 * @file	KeypadVotingPasswordWidget.hxx
 * @brief	Key pad password widget.
 * @author	Yadickson Soto
 * @date	17/04/2012
 */

#ifndef _KEY_PAD_VOTING_PASSWORD_WIDGET_H_
#define _KEY_PAD_VOTING_PASSWORD_WIDGET_H_

#include <Gui/Widgets/VMAuthenticationWidget.hxx>

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
					 * @class	KeypadVotingPasswordWidget
					 * @brief	Key pad password widget.
					 * @author	Yadickson Soto
					 * @date	17/04/2012
					 */
					class KeypadVotingPasswordWidget: public Smartmatic::SAES::GUI::Widgets::VMAuthenticationWidget
					{

					public:

						/**
						 * @brief	Class constructor
						 * @author	Yadickson Soto
						 * @date	17/04/2012
						 */
						 KeypadVotingPasswordWidget();
						/**
						 * @brief	Class destroy
						 * @author	Yadickson Soto
						 * @date	17/04/2012
						 */
						~KeypadVotingPasswordWidget();
						/**
						 * @brief method getter signal ok
						 * @return signal
						 * @date 22/04/2012
						 * @author Yadickson Soto
						 */
						sigc::signal<void> getSignalOk();

					protected:

						sigc::signal<void> signalOk; ///< signal password ok
						Gtk::Label * infoLabel; ///< info label

					protected:

						/**
						 * @brief method check password
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						virtual void checkPassword();
					};
				}
			}
		}
	}
}

#endif // _KEY_PAD_VOTING_PASSWORD_WIDGET_H_
