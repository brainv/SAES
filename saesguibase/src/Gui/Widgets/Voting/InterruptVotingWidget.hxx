/**
 * @file InterruptVotingWidget.hxx
 * @brief Header class interrupt voting widget
 * @date 17/04/2012
 * @author Yadickson Soto
 */

#ifndef _INTERRUPT_VOTING_WIDGET_H_
#define _INTERRUPT_VOTING_WIDGET_H_

#include <gtkmm.h>
#include <Widgets/StepWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include <Gui/Widgets/ProgressWidget.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				namespace Voting
				{
					/**
					 * @class	InterruptVotingWidget
					 * @brief	Interrupt voting widget.
					 * @date 	17/04/2012
					 * @author 	Yadickson Soto
					 */
					class InterruptVotingWidget: public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @enum InterrupVotingState
						 * @brief state widget
						 */
						enum InterrupVotingState
						{
							 INTERRUPTVOTING_CARDCOUNTER ///< step card counter
							,INTERRUPTVOTING_CANCELPROCESS ///< step cancel process
						};

						/**
						 * @brief	Class constructor.
						 * @param	progress progress widget
						 * @date 	17/04/2012
						 * @author 	Yadickson Soto
						 */
						InterruptVotingWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief	Class destroy
						 * @date 	17/04/2012
						 * @author 	Yadickson Soto
						 */
						~InterruptVotingWidget();
						/**
						 * @brief method refresh widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();
						/**
						 * @brief method change step widget
						 * @param state state widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						void changeState(InterrupVotingState state);
						/**
						 * @brief method egtter signal click
						 * @return signal click
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						Glib::SignalProxy0<void> getSignalClick();

					private:

						InterrupVotingState currentState; ///< current state
						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< progress widget
						Gtk::EventBox * mainFrame; ///< main frame
						Gtk::VBox * mainVBox; ///< main vbox
						Gtk::EventBox * centerFrame; ///< center frame
						Gtk::HBox * hboxButton; //< hbox button
						Smartmatic::GUI::Widgets::SmartmaticButton * button; ///< button
						static Smartmatic::Log::ISMTTLog* logger;   ///< logger
					};
				}
			}
		}
	}
}

#endif // _INTERRUPT_VOTING_WIDGET_H_
