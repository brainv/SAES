/**
 * @file	super-null-selection-widget.h
 *
 * @brief	Declares the super null selection widget class.
 */

#ifndef _SUPER_NULL_SELECTION_WIDGET_H_
#define _SUPER_NULL_SELECTION_WIDGET_H_

#include <gtkmm.h>
#include "question-selection-widget.h"

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
					 * @brief	Super null selection widget. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class SuperNullSelectionWidget: public QuestionSelectionWidget
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType  	Type of the voting mode.
						 * @param	showConfirmation	true to show, false to hide the confirmation.
						 * @param	buttonsVertical 	true to buttons vertical.
						 */

						SuperNullSelectionWidget(bool showConfirmation, bool buttonsVertical);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~SuperNullSelectionWidget();

						/**
						 * @brief	Simulate null button clicked.
						 *
						 * @author	Juan.Delgado
						 * @date	14/07/2011
						 */
						void SimulateNullClicked();

					private:

						/**
						 * @brief	Sets the strings.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType	Type of the voting mode.
						 */

						virtual void SetStrings();

						/**
						 * @brief	Sets the labels configuration.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						virtual void SetLabelsConfiguration();
							
					};
				}

			}
		}
	}
}

#endif // _SUPER_NULL_SELECTION_WIDGET_H_
