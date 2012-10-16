/**
 * @file CardRemovedWidget.hxx
 * @brief Header class card removed widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef CARDREMOVEDWIDGET_HXX_
#define CARDREMOVEDWIDGET_HXX_

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
					 * @class CardRemovedWidget
					 * @brief Class card removed widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class CardRemovedWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						CardRemovedWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~CardRemovedWidget();
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

#endif /* CARDREMOVEDWIDGET_HXX_ */
