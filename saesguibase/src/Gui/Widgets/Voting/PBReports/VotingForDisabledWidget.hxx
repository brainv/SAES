/**
 * @file VotingForDisabledWidget.hxx
 * @brief Header class voting for disabled
 * @data 18/05/2012
 * @author Yadickson Soto
 */

#ifndef VOTINGFORDISABLEDWIDGET_HXX_
#define VOTINGFORDISABLEDWIDGET_HXX_

#include <Widgets/StepWidget.hxx>
#include <Widgets/smartmatic-button.h>
#include "VotingForDisabledRegisterWidget.hxx"
#include "VotingForDisabledQuestionWidget.hxx"
#include "VotingForDisabledInfoWidget.hxx"
#include "VotingForDisabledRegisterInfoWidget.hxx"
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
						 * @class VotingForDisabledWidget
						 * @brief class voting for disabled
						 * @data 18/05/2012
						 * @author Yadickson Soto
						 */
						class VotingForDisabledWidget : public Smartmatic::GUI::Widgets::StepWidget
						{
						public:
							/**
							 * @brief class constructor
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							VotingForDisabledWidget();
							/**
							 * @brief class destroy
							 * @data 18/05/2012
							 * @author Yadickson Soto
							 */
							virtual ~VotingForDisabledWidget();
							/**
							 * @brief method getter signal enabled
							 * @return signal
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalEnabled();
							/**
							 * @brief method getter signal disabled
							 * @return signal
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalDisabled();

						protected:
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
							 * @brief method show question
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							void showQuestion();
							/**
							 * @brief method load all info info
							 * @date 21/05/2012
							 * @author Yadickson Soto
							 */
							void load();
							/**
							 * @brief method add assisted info
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							void addAssistedInfo();
							/**
							 * @brief method add accompanied info
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							void addAccompaniedInfo();
							/**
							 * @brief method save info
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							void saveInfo();
							/**
							 * @brief method cancel info
							 * @date 18/05/2012
							 * @author Yadickson Soto
							 */
							void cancelInfo();
							/**
							 * @brief method process signal clicked
							 * @param widget widget
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							void editInfo(VotingForDisabledRegisterInfoWidget * widget);
							/**
							 * @brief method create voting disable empty
							 * @param votingDisabled voting disable empty
							 * @date 22/05/2012
							 * @author Yadickson Soto
							 */
							void createVotingDisabled(Smartmatic::SAES::Voting::PBReports::VotingDisabled & votingDisabled);

						private:

							sigc::signal<void> signalEnabled; ///< signal enabled
							sigc::signal<void> signalDisabled; ///< signal disabled
							VotingForDisabledRegisterWidget * votingForDisabledRegisterWidget; ///< register widget
							VotingForDisabledQuestionWidget * votingForDisabledQuestionWidget; ///< question widget
							VotingForDisabledInfoWidget * votingForDisabledInfoWidget; ///< info widget
							static Smartmatic::Log::ISMTTLog* logger; ///< The logger
						};
					}
				}
			}
		}
	}
}

#endif /* VOTINGFORDISABLEDWIDGET_HXX_ */
