/**
 * @file PrintTimeOutWidget.hxx
 * @brief Header class print timeout widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef PRINTTIMEOUTWIDGET_HXX_
#define PRINTTIMEOUTWIDGET_HXX_

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
					 * @class PrintTimeOutWidget
					 * @brief Class print time out widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class PrintTimeOutWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						PrintTimeOutWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~PrintTimeOutWidget();
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

#endif /* PRINTTIMEOUTWIDGET_HXX_ */
