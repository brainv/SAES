/**
 * @file VotingForDisabledRegisterInfoWidget.hxx
 * @brief Header voting for disabled register info widget
 * @date 21/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDREGISTERINFOWIDGET_HXX_
#define VOTINGFORDISABLEDREGISTERINFOWIDGET_HXX_

#include <gtkmm.h>
#include <Widgets/RegisterInfoWidget.hxx>
#include <Voting/PBReports/voting-disabled-information-schema.hxx>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

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
						 * @class VotingForDisabledRegisterInfoWidget
						 * @brief class voting for disabled
						 * @data 21/05/2012
						 * @author Yadickson Soto
						 */
						class VotingForDisabledRegisterInfoWidget : public Smartmatic::GUI::Widgets::RegisterInfoWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @param votingDisabled voting disabled information
							 * @data 21/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledRegisterInfoWidget(Smartmatic::SAES::Voting::PBReports::VotingDisabled & votingDisabled);
							/**
							 * @brief class destroy
							 * @param votingDisabled voting disabled
							 * @data 21/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~VotingForDisabledRegisterInfoWidget();
							/**
							 * @brief method refresh elements
							 * @data 21/05/2012
							 * @author Yadickson Soto
							 */
							void refresh();
							/**
							 * @brief method getter voting disabled information
							 * @return voting disabled information
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							Smartmatic::SAES::Voting::PBReports::VotingDisabled & getVotingDisabled();
							/**
							 * @brief method getter signal clicked
							 * @return signal clicked
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void, VotingForDisabledRegisterInfoWidget *> getSignalClicked();

						protected:

							/**
							 * @brief method process clicked
							 * @param state signal clicked
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							void clicked(bool state);
							/**
							 * @brief method process clicked
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							void emitClicked();

						private:

							sigc::signal<void, VotingForDisabledRegisterInfoWidget *> signalClicked; ///< signal clicked info
							Smartmatic::SAES::Voting::PBReports::VotingDisabled votingDisabled; ///< voting disabled information
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDREGISTERINFOWIDGET_HXX_ */
