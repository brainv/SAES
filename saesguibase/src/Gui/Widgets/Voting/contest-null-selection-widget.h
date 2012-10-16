/**
 * @file	contest-null-selection-widget.h
 *
 * @brief	Declares the contest null selection widget class.
 */

#ifndef _CONTEST_NULL_SELECTION_WIDGET_H_
#define _CONTEST_NULL_SELECTION_WIDGET_H_

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
					 * @brief	Contest null selection widget. 
					 *
					 * @author	Eduardo.campione
					 * @date	28/04/2011
					 */

					class ContestNullSelectionWidget: public QuestionSelectionWidget
					{
					public:

						/**
						 * @brief	Constructor.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 *
						 * @param	votingModeType	Type of the voting mode.
						 * @param isReferendum is referendum
						 */

						ContestNullSelectionWidget(bool isReferendum = false);

						/**
						 * @brief	Finaliser.
						 *
						 * @author	Eduardo.campione
						 * @date	28/04/2011
						 */

						~ContestNullSelectionWidget();

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

						bool isReferendum;
					};
				}

			}
		}
	}
}

#endif // _CONTEST_NULL_SELECTION_WIDGET_H_
