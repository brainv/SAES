/**
 * @file PrintVoteWidget.hxx
 * @brief Header class print vote widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef PRINTVOTEWIDGET_HXX_
#define PRINTVOTEWIDGET_HXX_

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
					 * @class PrintVoteWidget
					 * @brief Class print vote widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class PrintVoteWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						PrintVoteWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~PrintVoteWidget();
						/**
						 * @brief method refresh widget
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();
						/**
						 * @brief method setter text
						 * @param text new text
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						void setText(std::string text);

					private:

						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< principal frame
					};
				}
			}
		}
	}
}

#endif /* PRINTVOTEWIDGET_HXX_ */
