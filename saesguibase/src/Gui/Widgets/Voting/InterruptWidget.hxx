/**
 * @file InterruptWidget.hxx
 * @brief Header class interrupt voting widget
 * @date 24/04/2012
 * @author Yadickson Soto
 */

#ifndef _INTERRUPTWIDGET_H_
#define _INTERRUPTWIDGET_H_

#include <gtkmm.h>
#include <Widgets/StepWidget.hxx>
#include "InterruptVotingWidget.hxx"
#include "KeypadVotingPasswordWidget.hxx"
#include "EndVotingWidget.hxx"

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
					 * @class	InterruptWidget
					 * @brief	Interrupt voting widget.
					 * @date 	17/04/2012
					 * @author 	Yadickson Soto
					 */
					class InterruptWidget: public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief	Class constructor.
						 * @param	progress progress widget
						 * @date 	17/04/2012
						 * @author 	Yadickson Soto
						 */
						InterruptWidget();
						/**
						 * @brief	Class destroy
						 * @date 	17/04/2012
						 * @author 	Yadickson Soto
						 */
						~InterruptWidget();
						/**
						 * @brief method refresh widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();
						/**
						 * @brief method show card counter
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						void showCardCounter();
						/**
						 * @brief method show cancel process
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						void showCancelProcess();

					private:

						/**
						 * @brief method action click
						 * @date 17/04/2012
						 * @author Yadikson Soto
						 */
						void onActionClicked();
						/**
						 * @brief method show end
						 * @date 24/04/2012
						 * @author Yadikson Soto
						 */
						void showEnd();
						/**
						 * @brief method close
						 * @date 24/04/2012
						 * @author Yadikson Soto
						 */
						void close();

						InterruptVotingWidget * interruptVotingWidget; ///< interrupt voting widget
						KeypadVotingPasswordWidget * keypassWidget;	///< keypass widget
						EndVotingWidget * endVotingWidget; ///< end voting widget
					};
				}
			}
		}
	}
}

#endif // _INTERRUPTWIDGET_H_
