/**
 * @file BallotOptionButtonWidget.hxx
 * @brief Header class ballot option button widget
 * @date 12/03/2012
 * @author Yadickson Soto
 */

#ifndef BALLOTOPTIONBUTTONWIDGET_HXX_
#define BALLOTOPTIONBUTTONWIDGET_HXX_

#include <Widgets/ButtonsWidget.hxx>

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class BallotOptionButtonWidget
				 * @brief Class BallotOptionButtonWidget
				 * @author Yadickson Soto
				 * @date 12/03/2012
				 */
				class BallotOptionButtonWidget : public Smartmatic::GUI::Widgets::ButtonsWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param expand expand all button
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					BallotOptionButtonWidget(bool expand = true);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					virtual ~BallotOptionButtonWidget();
					/**
					 * @brief method update button
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					void update();
				};
			}
		}
	}
}

#endif /* BALLOTOPTIONBUTTONWIDGET_HXX_ */
