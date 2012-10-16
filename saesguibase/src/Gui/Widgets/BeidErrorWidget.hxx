/**
 * @file BeidErrorWidget.hxx
 * @brief Header class beid error widget
 * @date 23/04/2012
 * @author Yadickson Soto
 */

#ifndef BEIDERRORWIDGET_HXX_
#define BEIDERRORWIDGET_HXX_

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
				/**
				 * @class BeidErrorWidget
				 * @brief Class card removed widget
				 * @date 23/04/2012
				 * @author Yadickson Soto
				 */
				class BeidErrorWidget : public Smartmatic::GUI::Widgets::StepWidget
				{
				public:

					/**
					 * @brief Class constructor
					 * @param progress progress widget
					 * @date 23/04/2012
					 * @author Yadickson Soto
					 */
					BeidErrorWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
					/**
					 * @brief Class destroy
					 * @date 23/04/2012
					 * @author Yadickson Soto
					 */
					virtual ~BeidErrorWidget();
					/**
					 * @brief method refresh widget
					 * @date 23/04/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();
					/**
					 * @brief method start timeout
					 * @date 24/04/2012
					 * @author Yadickson Soto
					 */
					void start();

				private:

					/**
					 * @brief method end timeout
					 * @date 24/04/2012
					 * @author Yadickson Soto
					 */
					void end();

					Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< principal frame
				};
			}
		}
	}
}

#endif /* BEIDERRORWIDGET_HXX_ */
