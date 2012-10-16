/**
 * @file	selection-widget-base.h
 *
 * @brief	Declares the selection widget base class.
 */

#ifndef _SELECTION_WIDGET_BASE_H_
#define _SELECTION_WIDGET_BASE_H_

#include <Widgets/StepWidget.hxx>

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
					 * @brief	Selection widget base. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class SelectionWidgetBase: public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 */

						SelectionWidgetBase();

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~SelectionWidgetBase();

						/**
						 * @brief	Defines an alias representing the void signal. .
						 */

						typedef sigc::signal<void> void_signal;

					protected:

						Gtk::EventBox mainContainer; ///< main frame

					private:

						Gtk::Alignment* clientAreaAlignment;	///< The client area alignment
					};
				}
			}
		}
	}
}

#endif // _SELECTION_WIDGET_BASE_H_
