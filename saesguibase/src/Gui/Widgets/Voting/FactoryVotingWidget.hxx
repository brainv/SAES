/**
 * @file FactoryVotingWidget.hxx
 * @brief Header class for create widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#ifndef FACTORYVOTINGWIDGET_HXX_
#define FACTORYVOTINGWIDGET_HXX_

#include "language-selection-widget.h"
#include "SimulationWidget.hxx"
#include "PreviewWidget.hxx"
#include "VotePreviewWidget.hxx"
#include "TimeOutPreviewWidget.hxx"
#include "WaitingForCardWidget.hxx"
#include "PrintTimeOutWidget.hxx"
#include "PrintVoteErrorWidget.hxx"
#include "RemoveCardWidget.hxx"
#include "EndPrintVoteWidget.hxx"
#include "CardRemovedWidget.hxx"
#include "PrintVoteWidget.hxx"
#include "InterruptVotingWidget.hxx"
#include "KeypadVotingPasswordWidget.hxx"
#include "EndVotingWidget.hxx"
#include "InterruptWidget.hxx"
#include "VotingExperienceValidationWidget.hxx"
#include "super-null-selection-widget.h"
#include "contest-null-selection-widget.h"
#include "custom-attribute-widget.h"
#include "ScreenVotingWidget.hxx"
#include "VotingExperienceWidget.hxx"

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
					 * @class FactoryVotingWidget
					 * @brief Class for create widget
					 * @date 29/02/2012
					 * @author Yadickson Soto
					 */
					class FactoryVotingWidget
					{
					protected:

						/**
						 * @brief Class constructor
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						FactoryVotingWidget();

					public:

						/**
						 * @brief Class destroy
						 * @date 29/02/2012
						 * @author Yadickson Soto
						 */
						virtual ~FactoryVotingWidget();
						/**
						 * @brief Method for create view language selection widget
						 * @return new widget
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						static LanguageSelectionWidget * createViewLanguageSelectionWidget();
						/**
						 * @brief Method for create voting language selection widget
						 * @return new widget
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						static LanguageSelectionWidget * createVotingLanguageSelectionWidget();
						/**
						 * @brief Method for create simulation custom attributes widget
						 * @return new widget
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						static SimulationWidget * createSimulationWidget();
						/**
						 * @brief Method for create vote preview widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static PreviewWidget * createPreviewWidget();
						/**
						 * @brief Method for create vote preview widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static VotePreviewWidget * createVotePreviewWidget();
						/**
						 * @brief Method for create timeout preview widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static TimeOutPreviewWidget * createTimeOutPreviewWidget();
						/**
						 * @brief Method for create waiting card widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static WaitingForCardWidget * createWaitingForCardWidget();
						/**
						 * @brief Method for create print timeout widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static PrintTimeOutWidget * createPrintTimeOutWidget();
						/**
						 * @brief Method for create print vote error widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static PrintVoteErrorWidget * createPrintVoteErrorWidget();
						/**
						 * @brief Method for create remove card widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static RemoveCardWidget * createRemoveCardWidget();
						/**
						 * @brief Method for create end print vote widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static EndPrintVoteWidget * createEndPrintVoteWidget();
						/**
						 * @brief Method for create card removed widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static CardRemovedWidget * createCardRemovedWidget();
						/**
						 * @brief Method for create print vote widget
						 * @return new widget
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						static PrintVoteWidget * createPrintVoteWidget();
						/**
						 * @brief Method for create interrupt voting widget
						 * @return new widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						static InterruptVotingWidget * createInterruptVotingWidget();
						/**
						 * @brief Method for create keypad voting password widget
						 * @return new widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						static KeypadVotingPasswordWidget * createKeypadVotingPasswordWidget();
						/**
						 * @brief Method for create end voting widget
						 * @return new widget
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						static EndVotingWidget * createEndVotingWidget();
						/**
						 * @brief Method for create interrupt widget
						 * @return new widget
						 * @date 24/04/2012
						 * @author Yadickson Soto
						 */
						static InterruptWidget * createInterruptWidget();
						/**
						 * @brief Method for create voting experience validation widget
						 * @return new widget
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						static VotingExperienceValidationWidget * createVotingExperineceValidationWidget();
						/**
						 * @brief Method for create super null selection widget
						 * @return new widget
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						static SuperNullSelectionWidget * createSuperNullSelectionWidget();
						/**
						 * @brief Method for create contest null selection widget
						 * @return new widget
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						static ContestNullSelectionWidget * createContestNullSelectionWidget();
						/**
						 * @brief Method for create custom attribute widget
						 * @param customAttribute custom attribute definition
						 * @return new widget
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						static CustomAttributeWidget * createCustomAttributeWidget(Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition & customAttribute);
						/**
						 * @brief Method for create screen voting widget
						 * @return new widget
						 * @date 30/04/2012
						 * @author Yadickson Soto
						 */
						static ScreenVotingWidget * createScreenVotingWidget();
						/**
						 * @brief Method for create voting experience widget
						 * @return new widget
						 * @date 15/05/2012
						 * @author Yadickson Soto
						 */
						static VotingExperienceWidget * createVotingExperienceWidget();
					};
				}
			}
		}
	}
}

#endif /* FACTORYVOTINGWIDGET_HXX_ */
