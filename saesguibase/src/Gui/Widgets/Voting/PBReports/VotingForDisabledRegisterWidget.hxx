/**
 * @file VotingForDisabledRegisterWidget.hxx
 * @brief Header class voting for disabled
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDREGISTERWIDGET_HXX_
#define VOTINGFORDISABLEDREGISTERWIDGET_HXX_

#include <Widgets/smartmatic-button.h>
#include <Widgets/RegisterWidget.hxx>
#include <Widgets/RegisterActionWidget.hxx>
#include "VotingForDisabledRegisterInfoWidget.hxx"

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
					namespace PBReports
					{
						/**
						 * @class VotingForDisabledWidget
						 * @brief class voting for disabled
						 * @data 18/05/2012
						 * @author Yadickson Soto
						 */
						class VotingForDisabledRegisterWidget : public Smartmatic::GUI::Widgets::RegisterActionWidget<VotingForDisabledRegisterInfoWidget *>
						{
						public:
							/**
							 * @brief class constructor
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledRegisterWidget();
							/**
							 * @brief class destroy
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~VotingForDisabledRegisterWidget();
							/**
							 * @brief virtual method init
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual void initialize();
							/**
							 * @brief virtual method stop
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual void dispose();
							/**
							 * @brief method getter signal add info
							 * @return signal add info
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							Glib::SignalProxy0< void > getSignalAddInfoButton();

						private:

							Smartmatic::GUI::Widgets::SmartmaticButton * addInfoButton; ///< add info
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDREGISTERWIDGET_HXX_ */
