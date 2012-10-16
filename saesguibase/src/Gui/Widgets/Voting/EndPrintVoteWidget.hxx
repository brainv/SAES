/**
 * @file EndPrintVoteWidget.hxx
 * @brief Header class print vote widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef ENDPRINTVOTEWIDGET_HXX_
#define ENDPRINTVOTEWIDGET_HXX_

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
					 * @class EndPrintVoteWidget
					 * @brief Class end print vote widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class EndPrintVoteWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						EndPrintVoteWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~EndPrintVoteWidget();
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

#endif /* ENDPRINTVOTEWIDGET_HXX_ */
