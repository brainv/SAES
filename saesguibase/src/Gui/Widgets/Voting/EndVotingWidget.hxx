/**
 * @file EndVotingWidget.hxx
 * @brief Header class card removed widget
 * @date 24/04/2012
 * @author Yadickson Soto
 */

#ifndef ENDVOTINGWIDGET_HXX_
#define ENDVOTINGWIDGET_HXX_

#include <Gui/Widgets/ProgressWidget.hxx>
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
					 * @class EndVotingWidget
					 * @brief Class card removed widget
					 * @date 24/04/2012
					 * @author Yadickson Soto
					 */
					class EndVotingWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						EndVotingWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~EndVotingWidget();
						/**
						 * @brief method refresh widget
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();

					private:
						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< principal frame
					};
				}
			}
		}
	}
}

#endif /* ENDVOTINGWIDGET_HXX_ */
