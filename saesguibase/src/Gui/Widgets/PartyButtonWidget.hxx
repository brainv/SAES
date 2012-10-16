/**
 * @file PartyButtonWidget.hxx
 * @brief Header class party button widget
 * @date 12/03/2012
 * @author Yadickson Soto
 */

#ifndef PARTYBUTTONWIDGET_HXX_
#define PARTYBUTTONWIDGET_HXX_

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
				 * @class PartyButtonWidget
				 * @brief Class PartyOptionButtonWidget
				 * @author Yadickson Soto
				 * @date 12/03/2012
				 */
				class PartyButtonWidget : public Smartmatic::GUI::Widgets::ButtonsWidget
				{
				public:
					/**
					 * @brief Class constructor
					 * @param expand expand all button
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					PartyButtonWidget(bool expand = true);
					/**
					 * @brief Class destroy
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					virtual ~PartyButtonWidget();
					/**
					 * @brief method update button
					 * @author Yadickson Soto
					 * @date 12/03/2012
					 */
					void update();
					/**
					 * @brief method show button
					 * @param showBack flag show back button
					 * @param showNull flag show null button
					 * @author Yadickson Soto
					 * @date 13/03/2012
					 */
					virtual void showButton(bool showBack, bool showNull);
				};
			}
		}
	}
}

#endif /* PARTYBUTTONWIDGET_HXX_ */
