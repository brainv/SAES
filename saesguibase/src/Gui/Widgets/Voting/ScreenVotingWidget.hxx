/**
 * @file ScreenVotingWidget.hxx
 * @brief Header class screen info voting widget
 * @date 30/04/2012
 * @author Yadickson Soto
 */

#ifndef SCREENVOTINGWIDGET_HXX_
#define SCREENVOTINGWIDGET_HXX_

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
					 * @class ScreenVotingWidget
					 * @brief Class card removed widget
					 * @date 30/04/2012
					 * @author Yadickson Soto
					 */
					class ScreenVotingWidget : public Smartmatic::GUI::Widgets::StepWidget
					{
					public:

						/**
						 * @brief Class constructor
						 * @param progress progress widget
						 * @date 30/04/2012
						 * @author Yadickson Soto
						 */
						ScreenVotingWidget(Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress);
						/**
						 * @brief Class destroy
						 * @date 30/04/2012
						 * @author Yadickson Soto
						 */
						virtual ~ScreenVotingWidget();
						/**
						 * @brief method refresh widget
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						void setCenterName(std::string centerName);
						/**
						 * @brief method setter current center
						 * @param currentCenter current center
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						void setCurrentCenter(int currentCenter);
						/**
						 * @brief method setter total centers
						 * @param totalCenters total centers
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						void setTotalCenter(int totalCenters);
						/**
						 * @brief method show image error
						 * @date 01/07/2012
						 * @author Yadickson Soto
						 */
						void setImageError();
						/**
						 * @brief method show image ok
						 * @date 01/07/2012
						 * @author Yadickson Soto
						 */
						void setImageOk();
						/**
						 * @brief method refresh widget
						 * @date 30/03/2012
						 * @author Yadickson Soto
						 */
						virtual void refresh();

					private:
						Smartmatic::SAES::GUI::Widgets::ProgressWidget * progress; ///< principal frame
						int totalCenters; ///< total centers
						int currentCenter; ///< current center
						std::string centerName; ///< center name
					};
				}
			}
		}
	}
}

#endif /* SCREENVOTINGWIDGET_HXX_ */
