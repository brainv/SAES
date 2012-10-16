/**
 * @file RemoveCardWidget.hxx
 * @brief Header class card removed widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef REMOVECARDWIDGET_HXX_
#define REMOVECARDWIDGET_HXX_

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
					 * @class RemoveCardWidget
					 * @brief Class card removed widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class RemoveCardWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						RemoveCardWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~RemoveCardWidget();
						/**
						 * @brief method refresh widget
						 * @date 30/03/2012
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

#endif /* REMOVECARDWIDGET_HXX_ */
