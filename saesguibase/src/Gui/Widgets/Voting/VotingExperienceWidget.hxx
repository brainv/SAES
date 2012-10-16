/**
 * @file	VotingExperienceWindow.hxx
 *
 * @brief	Declares the voting experience Windows Form.
 */


/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * saesguibase is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesguibase is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _VOTING_EXPERIENCE_WIDGET_H_
#define _VOTING_EXPERIENCE_WIDGET_H_

#include <gtkmm.h>
#include "Gui/Widgets/party-selection-widget.h"
#include "Gui/Widgets/ballot-option-selection-widget.h"
#include "Operation/Voting/VotingExperienceController.hxx"
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include "Printing/printer-client.h"
#include "Printing/printer-status.h"
#include "Voting/Election/election-schema.hxx"
#include "Voting/Election/ElectionWrapper.hxx"
#include <Windows/basic-window.h>
#include "Operation/Voting/VotingWidgetManager.hxx"
#include "Gui/Widgets/Voting/question-selection-widget.h"
#include "Gui/Widgets/Voting/super-null-selection-widget.h"
#include "Gui/Widgets/Voting/contest-null-selection-widget.h"
#include "Gui/Widgets/Voting/welcome-message-widget.h"
#include "Gui/Widgets/Voting/custom-attribute-widget.h"
#include "Printing/VotePrintDocument.h"
#include "Gui/Widgets/voting-frame-base.h"
#include "Gui/Widgets/referendum-selection-widget.h"
#include <Gui/Widgets/Voting/CardRemovedWidget.hxx>
#include <Gui/Widgets/Voting/RemoveCardWidget.hxx>
#include <Gui/Widgets/Voting/PrintVoteWidget.hxx>
#include <Gui/Widgets/Voting/EndPrintVoteWidget.hxx>
#include <Gui/Widgets/Voting/PrintVoteErrorWidget.hxx>
#include <Gui/Widgets/Voting/PrintTimeOutWidget.hxx>
#include <Gui/Widgets/Voting/InterruptWidget.hxx>

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
					/**
					 * @brief	Form for viewing the voting experience.
					 * @author	Juan delgado <juan.delgado@smartmatic.com>
					 * @date	28/04/2011
					 */

					class VotingExperienceWidget: public Smartmatic::GUI::Widgets::StepWidget, Smartmatic::SAES::Printing::PrinterClient
					{
					public:

						/**
						 * @brief	Default constructor.
						 */

						VotingExperienceWidget();
						sigc::signal<void,std::string> signalAlarm_detected;	///< The signal alarm detected

						typedef sigc::signal<void> signal_back;	///< The signal alarm detected

						/**
						 * @brief	method to get signal end voting
						 * @return	the signal
						 */
						signal_back signalEndVotingExperineceDetected();

						/**
						 * @brief	class destructor.
						 */

						~VotingExperienceWidget();

						/**
						 * @brief	Sets an actual contest.
						 * @param	contestA	The contest.
						 */

						void setActualContest(Smartmatic::SAES::Voting::Election::Contest contestA);

						/**
						 * @brief	Sets detect card extraction enable.
						 * @param	enable	true to enable, false to disable.
						 */

						void setDetectCardExtractionEnable(bool enable);
						static void setSimulationMode(bool enable);

						void setCardWrited(bool result);
						/**
						 * @brief method start check card data
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						void startCheckCardPresent();
						/**
						 * @brief method stop check card data
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						void stopCheckCardPresent();

						void dispose();

						/**
						 * @brief Method start process
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						void start();

					protected:

						signal_back signalEndVotingExperinece;

						/**
						 * @brief	Referendum selecton signal back clicked.
						 */
						void referendumSelection_on_back_clicked();

						/**
						 * @brief	Referendum selecton signal accept clicked.
						 */
						void referendumSelection_on_accept_clicked();

						/**
						 * @brief	Referendum selecton signal null clicked.
						 */
						void referendumSelection_on_null_clicked();

						/**
						 * @brief	Referendum selecton normal vote.
						 */
						void on_ReferendumNormalVote();

						/**
						 * @brief	Referendum selecton signal ballot option clicked.
						 * @param	ballotOptionCode	The ballot option code.
						 *
						 */
						void referendumSelection_on_ballotOption_clicked(std::string ballotOptionCode, bool isSelected);

						/**
						 * @brief	Party selection signal on clicked.
						 */

						void partySelection_on_null_clicked();

						/**
						 * @brief	Party selection signal on back clicked.
						 */

						void partySelection_on_back_clicked();

						/**
						 * @brief	Party selection signal on party clicked.
						 * @param	partySelected	The party selected.
						 */

						void partySelection_on_party_clicked(Smartmatic::SAES::Voting::Election::Party partySelected);

						/**
						 * @brief	ballot option selection signal on accept clicked.
						 */

						void ballotOptionSelection_on_accept_clicked();

						/**
						 * @brief	Ballot option selection signal on back clicked.
						 */

						void ballotOptionSelection_on_back_clicked();

						/**
						 * @brief	Ballot option selection signal on ballot option clicked.
						 * @param	ballotOptionCode	The ballot option code.
						 * @param	isSelected			true if is selected.
						 */

						void ballotOptionSelection_on_ballotOption_clicked(std::string ballotOptionCode, bool isSelected);

						/**
						 * @brief	Handles accept vote signals.
						 */

						void on_AcceptVote();

						/**
						 * @brief	Handles back vote signals.
						 */

						void on_BackVote();

						/**
						 * @brief	printer client method: Callback, called when job event.
						 * @param	job_id	  	Identifier for the job.
						 * @param	error_code	The error code.
						 */

						void job_event_callback (int job_id, int error_code);

						/**
						 * @brief	printer client method: Handles status reported signals.
						 * @param [in,out]	status	If non-null, the status.
						 */

						void on_status_reported (Smartmatic::SAES::Printing::PrinterStatus *status);

						/**
						 * @brief	printer client method: Handles ticket printed signals.
						 * @param	result	The result.
						 */

						void on_ticket_printed (Gtk::PrintOperationResult result);

						/**
						 * @brief	printer client method: Handles job finished signals.
						 * @param	operation	The operation.
						 */

						void on_job_finished (const Glib::RefPtr<Gtk::PrintOperation>& operation);

						/**
						 * @brief	method called on timeout.
						 * @param	timer	counter timer.
						 * @return	true for continue.
						 */

						bool onTimeout (int timer);

						/**
						 * @brief	timeout method: Handles timeout contest welcome signals.
						 */

						void on_TimeoutContestWelcome();

						/**
						 * @brief	timeout method: Handles timeout question welcome signals.
						 */

						void on_TimeoutQuestionWelcome();

						/**
						 * @brief method card insert event
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						void cardInsertEvent();
						/**
						 * @brief method card remove event
						 * @date 08/03/2012
						 * @author Yadickson Soto
						 */
						void cardRemoveEvent();

						sigc::connection connectTimeout;	///< connection timeout
						sigc::connection connection_partySelectionWidget_null_clicked;  ///< connection party selection widget null clicked
						sigc::connection connection_partySelectionWidget_back_clicked;  ///< connection party selection widget back clicked
						sigc::connection connection_partySelectionWidget_party_clicked; ///< connection party selection widget party clicked
						sigc::connection connection_referendumSelectionWidget_null_clicked; ///< connection referendum selection widget null clicked
						sigc::connection connection_referendumSelectionWidget_back_clicked; ///< connection referendum selection widget back clicked
						sigc::connection connection_referendumSelectionWidget_accept_clicked; ///< connection referendum selection widget accept clicked
						sigc::connection connection_ballotOptionSelectionWidget_accept_clicked; ///< connection ballot option selection widget accept clicked
						sigc::connection connection_ballotOptionSelectionWidget_back_clicked;   ///< connection ballot option selection widget back clicked
						sigc::connection connection_ballotOptionSelectionWidget_ballotOption_clicked;   ///< connection ballot option selection widget ballot option clicked
						sigc::connection connectionShowFinalMessage;
						sigc::connection connection_null_voteclicked;  ///< connection vote null clicked
						sigc::connection connection_question;   ///< connection question

						/**
						 * @brief	null question method: Handles normal vote signals.
						 */

						void on_NormalVote();

						/**
						 * @brief	null question method: Handles super null vote signals.
						 */

						void on_SuperNullVote();

						/**
						 * @brief	question method: Handles question answered signals.
						 * @param	code	The code.
						 */

						void on_QuestionAnswered(std::string code);

						/**
						 * @brief	null contest question method: Handles contest normal vote signals.
						 */

						void on_ContestNormalVote();

						/**
						 * @brief	null contest question method: Handles contest null vote signals.
						 */

						void on_ContestNullVote();

						Smartmatic::SAES::Voting::Election::ElectionWrapper* electionWrapper;   ///< election wrapper

						/**
						 * @brief Start voting experience
						 * @date 16/04/2012
						 * @author Yadickson Soto
						 */
						void startVoting();

					protected:

						Gtk::Frame* loadingFrame;   ///< loading frame
						Gtk::Label* loadingLabel;   ///< loading label
						Gtk::Label* checksumLabel;  ///< checksum label

						Smartmatic::SAES::GUI::Widgets::Voting::CardRemovedWidget * cardRemovedWidget;	///< card removed widget
						Smartmatic::SAES::GUI::Widgets::Voting::RemoveCardWidget * removeCardWidget; ///< remove the card widget
						Smartmatic::SAES::GUI::Widgets::Voting::PrintVoteWidget * printVoteWidget; ///< print vote widget
						Smartmatic::SAES::GUI::Widgets::Voting::EndPrintVoteWidget * endPrintVoteWidget; ///< end print vote widget
						Smartmatic::SAES::GUI::Widgets::Voting::PrintVoteErrorWidget * printVoteErrorWidget; ///< print vote error widget
						Smartmatic::SAES::GUI::Widgets::Voting::PrintTimeOutWidget * printTimeOutWidget; ///< print time out widget

						Smartmatic::SAES::Operation::Voting::VotingExperienceController* votingExperienceController;	///< voting experience controller
						Smartmatic::SAES::GUI::Operation::Voting::VotingWidgetManager* votingWidgetManager; ///< Manager for voting widget

						Smartmatic::SAES::GUI::Widgets::ReferendumSelectionWidget* referendumSelectionWidget; ///< referendum selection widget
						Smartmatic::SAES::GUI::Widgets::PartySelectionWidget* partySelectionWidget; ///< party selection widget
						Smartmatic::SAES::GUI::Widgets::BallotOptionSelectionWidget* ballotOptionSelectionWidget;   ///< ballot option selection widget
						Smartmatic::SAES::GUI::Widgets::Voting::QuestionSelectionWidget* ballotConfirmWidget;   ///< ballot confirm widget
						Smartmatic::SAES::GUI::Widgets::Voting::SuperNullSelectionWidget* superNullSelectionWidget; ///< super null selection widget
						Smartmatic::SAES::GUI::Widgets::Voting::WelcomeMessageWidget* welcomeWidget;	///< welcome widget
						Smartmatic::SAES::GUI::Widgets::Voting::CustomAttributeWidget* customAttrWidget;	///< custom attribute widget
						Smartmatic::SAES::GUI::Widgets::Voting::ContestNullSelectionWidget* contestNullWidget;  ///< contest null widget
						Smartmatic::SAES::GUI::Widgets::Voting::InterruptWidget* interruptWidget; ///< interrupt widget

						Smartmatic::SAES::Voting::Election::Contest actualContest;  ///< actual contest
						std::list<Smartmatic::SAES::Voting::Election::Contest> contestList; ///< List of contests
						Smartmatic::SAES::Voting::Election::Party actualParty;  ///< actual party
						Smartmatic::SAES::Voting::Election::Party previousParty;	///< previous party
						Smartmatic::SAES::Voting::VotingDevice::Custom_attribute_definition currentcustomAttribute; ///< current custom attribute

						/**
						 * @brief	core logic method: Gets the current contest reources.
						 * @param [in,out]	contestClassName	   	Name of the contest class.
						 * @param [in,out]	contestClassDescription	Information describing the contest class.
						 * @param [in,out]	contestTitle		   	The contest title.
						 * @param [in,out]	contestAbstract		   	The contest abstract.
						 * @param [in,out]	contestHelp			   	The contest help.
						 */

						void GetCurrentContestReources(Glib::ustring& contestClassName,
								Glib::ustring& contestClassDescription,
								Glib::ustring& contestTitle,
								Glib::ustring& contestAbstract,
								Glib::ustring& contestHelp);

						/**
						 * @brief	core logic method: Gets the contest list.
						 */

						void GetContestList();

						/**
						 * @brief	core logic method: Gets the next contest.
						 *
						 */

						void GetNextContest();

						/**
						 * @brief	core logic method: Gets the previous contest.
						 */

						void GetPreviousContest();

						/**
						 * @brief	core logic method: Gets the party selection.
						 */

						void GetPartySelection();

						/**
						 * @brief	core logic method: Gets the ballot option selection.
						 */

						void GetBallotOptionSelection();

						/**
						 * @brief	core logic method: Gets and shows the party selection.
						 */

						void GetAndShowPartySelection();

						/**
						 * @brief	core logic method: Gets referendum or party selection.
						 */

						void GetReferendumOrPartySelection();

						/**
						 * @brief	core logic method: Gets and shows the referendum.
						 */
						void GetAndShowReferendum();

						/**
						 * @brief	core logic method: Gets the referendum.
						 */
						void GetReferendum();

						/**
						 * @brief	core logic method: Shows the referendum.
						 */
						void ShowReferendum();

						/**
						 * @brief	core logic method: Construct and shows ballot option selection.
						 */

						void ConstructAndShowBallotOptionSelection();

						/**
						 * @brief	core logic method: Sets an actual contest from index.
						 *
						 * @param	index	Zero-based index of the.
						 */

						void SetActualContestFromIndex(int index);

						/**
						 * @brief	core logic method: Creates the question dialog.
						 */

						void CreateQuestionDialog();

						/**
						 * @brief	core logic method: Final end voting experience.
						 * @param	alarm	The alarm.
						 */

						void FinalEndVotingExperience(std::string alarm = "");

						/**
						 * @brief	core logic method: Executes the print thread operation.
						 */

						void LaunchPrintThread();

						std::string SoundVoting;	///< The sound voting

						/**
						 * @brief	Shows the null vote question.
						 */

						void ShowNullVoteQuestion();

						/**
						 * @brief	Shows the question welcome.
						 */

						void ShowQuestionWelcome();

						/**
						 * @brief	Shows the party selection.
						 */

						void ShowPartySelection();

						/**
						 * @brief	Shows the ballot option selection.
						 */

						void ShowBallotOptionSelection();

						/**
						 * @brief	Shows the welcome contest message.
						 */

						void ShowWelcomeContestMessage();

						/**
						 * @brief	Show verify card removed
						 * @param 	skipRecovery skip recovery
						 * @date 01/06/2012
						 * @author Yadickson Soto
						 */
						void verifyCardRemoved(bool skipRecovery = false);
						/**
						 * @brief	Show end voting experience
						 * @param 	skipRecovery skip recovery
						 * @date 01/06/2012
						 * @author Yadickson Soto
						 */
						void ShowEndVotingExperience(bool skipRecovery = false);
						/**
						 * @brief	initialize print vote
						 * @date 01/06/2012
						 * @author Yadickson Soto
						 */
						void initializePrintVote();

						/**
						 * @brief	Shows the time out end voting experience.
						 */

						void ShowTimeOutEndVotingExperience();
						/**
						 * @brief method view voting frame base
						 * @param widget voting frame base
						 * @date 25/04/2012
						 * @author Yadickson Soto
						 */
						void showVotingFrameBase(Smartmatic::SAES::GUI::Widgets::VotingFrameBase * widget);
						/**
						 * @brief method view step widget
						 * @param widget step widget
						 * @date 17/04/2012
						 * @author Yadickson Soto
						 */
						void showStepWidget(Smartmatic::GUI::Widgets::StepWidget * widget);

						/**
						 * @brief	Shows the loading ballot.
						 */

						void ShowLoadingBallot();

						/**
						 * @brief	Shows the error checksum.
						 */

						void ShowErrorChecksum();

						/**
						 * @brief	Shows the error checksum internal.
						 */

						void ShowErrorChecksumInternal();

						/**
						 * @brief	voting window logic: Perform question action.
						 */

						void PerformQuestionAction();

						/**
						 * @brief	voting window logic: Perform back step.
						 */

						void PerformBackStep();

						/**
						 * @brief	voting window logic: Perform back step internal.
						 */

						void PerformBackStepInternal();

						/**
						 * @brief	voting window logic: Perform next step.
						 */

						virtual void PerformNextStep();

						/**
						 * @brief	voting window logic: Perform next step internal.
						 */

						void PerformNextStepInternal();

						/**
						 * @brief	voting window logic: Perform end voting experience.
						 */

						void PerformEndVotingExperience();

						/**
						 * @brief	voting window logic: Perform time out end voting experience.
						 */

						void PerformTimeOutEndVotingExperience();

						/**
						 * @brief	voting window logic: Print ticket.
						 */

						void PrintTicket();

						/**
						 * @brief	voting window logic: Print ticket done.
						 */

						void PrintTicketDone();

						/**
						 * @brief	Creates the vote and check if recovery.
						 * @return	true if it succeeds, false if it fails.
						 */

						bool CreateVoteAndCheckIfRecovery();

						Smartmatic::SAES::Printing::VotePrintDocument* votePrintDocument;   ///< vote print document

						sigc::connection connDetectExtract; ///< connection detect extract
						sigc::connection connInterruptButton;   ///< connection interrupt button
						sigc::connection connAlarmAndBack;  ///< connection alarm and back
						sigc::connection connAlarmNotRemoveCard;	///< connection alarm not remove card
						sigc::connection possibleWelcomeTimeout;	///< possible welcome timeout

						bool IsInInterrupt; ///< true if is in interrupt
						bool InvalidCard;   ///< true to invalid card
						unsigned int extractionCounter; ///< extraction counter
						bool wasPresent;	///< true if was present
						bool detectCardExtractionEnable;	///< true if detect card extraction enable
						bool sortAlphabetically;	///< true if sor question alphabetically
						bool isBallotOptionSelection;	///< true if showing ballot option selection
						static bool simulationMode;
						/**
						 * @brief	card detection: queries if the card is valid.
						 * @return	true if it succeeds, false if it fails.
						 */

						bool CardIsValid();

						/**
						 * @brief	card detection: Alarm and back.
						 * @param	timer	The timer.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						void AlarmExtractionCounter ();

						/**
						 * @brief	card detection: Alarm not remove card.
						 * @param	timer	The timer.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool AlarmNotRemoveCard(int timer);

						/**
						 * @brief	card detection: Detect extract.
						 *
						 * @param	timer	The timer.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool DetectExtract (int timer);

						/**
						 * @brief	card detection: Refresh by too many extracts.
						 * @param	timer	The timer.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						void RefreshByTooManyExtracts ();

						/**
						 * @brief	card detection: Initialises the stop by extract procedure.
						 */

						bool InitStopByExtractProcedure(int timer);

						/**
						 * @brief card detection: Handles pass ok signals.
						 * @date 17/04/2012
						 * @date Yadickson Soto
						 */
						void endVoting();
						
						Smartmatic::SAES::Configuration::VotingWindowConfiguration config;  ///< The configuration
						Smartmatic::SAES::Configuration::CustomAtributtesWindowConfiguration questionConfig;	///< The question configuration

						/**
						 * @brief	mode of visual theme: Sets the labels text.
						 */

						void SetLabelsText();

						/**
						 * @brief	mode of visual theme: Gets the idle function.
						 * @return	true if it succeeds, false if it fails.
						 */

						bool idleFunc();

						/**
						 * @brief	mode of visual theme: Check compose u string.
						 * @param [in,out]	stringToCheck	The string to check.
						 */

						void CheckComposeUString(Glib::ustring& stringToCheck);

						/**
						 * @brief	mode of visual theme: Check compose string.
						 * @param [in,out]	stringToCheck	The string to check.
						 */

						void CheckComposeString(std::string& stringToCheck);

						//bool CheckPrintFinished(int timer);

						Smartmatic::SAES::Printing::PrintDocumentResult printDocumentResult;	///< print document result

						
						int timeoutCounter; ///< The timeout counter
						int TimeOutFinal;   ///< The time out final
						bool success;   ///< true if the operation was a success, false if it failed
						bool alreadyInTransition;   ///< true if already in transition


						/**
						 * @brief	Change error image.
						 */
						void ChangeErrorImage();

						/**
						 * @brief	variables: Refreshs.
						 * @param	timer_num	The timer number.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool Refresh(int timer_num);

						/**
						 * @brief	variables: Refresh timeout.
						 * @param	timer_num	The timer number.
						 *
						 * @return	true if it succeeds, false if it fails.
						 */

						bool RefreshTimeout(int timer_num);
						bool FinalEndVotingExperienceThread(int timer_num,  std::string alarm);
						sigc::connection connRefreshTimeout;	///< connection refresh timeout
						sigc::connection connRefresh;   ///< connection refresh

						int clientAreaWidth;	///< Width of the client area
						int clientAreaHeight;   ///< Height of the client area
						int timeConnector;  ///< time connector
						unsigned int timeConnectorLoading;  ///< time connector loading
						int currentContestIndex;	///< current contest index
						int totalContests;  ///< The total contests
						bool welcomeShow;   ///< true if welcome show
						bool showBackInParty;   ///< true if show, false if hide the back in party
						bool comeFromAttrSelection;   ///< true if come from attribute selection
						int windowWidth;	///< Width of the window
						int windowHeight;   ///< Height of the window
						unsigned int loadingBallotsNumber;  ///< loading ballots number
						bool showPrintImage;  ///< show print image

						std::list<Smartmatic::SAES::Voting::Election::Contest>::iterator  iterContest;  ///< iterator contest
						Glib::Thread * thread;  ///< The thread
						Glib::ustring s_CustomAttributeQuestionFormat;  ///< custom attribute question format
						Glib::ustring s_PartyHeaderFormat;  ///< party header format
						Glib::ustring s_PartyHeaderFormatNoQuestion;  ///< party header format no question
						Glib::ustring s_PartyFooterFormat;  ///< party footer format
						Glib::ustring s_FooterPartySelection;   ///<  party selection footer
						Glib::ustring s_ContestWelcomeFormat;   ///< contest welcome format
						Glib::ustring s_BallotHeaderFormat; ///< ballot header format
						Glib::ustring s_BallotHeaderFormatNoQuestion; ///< ballot header format no question
						Glib::ustring s_BallotFooterFormat; ///< ballot footer format
						Glib::ustring s_FooterBallotSelection;  ///< footer ballot selection
						Glib::ustring s_ConfirmSelectionMessage;	///< confirm selection message
						Glib::ustring s_ConfirmSelectionMessageHeader;  ///< confirm selection message header
						Glib::ustring s_ConfirmSelectionMessageFooter;  ///< confirm selection message footer
						Glib::ustring s_ConfirmSelectionMessageBackButton;  ///< confirm selection message back button
						Glib::ustring s_ConfirmSelectionMessageAcceptButton;	///< confirm selection message accept button
						Glib::ustring s_TimeOutVotingExperience;	///< time out voting experience
						Glib::ustring s_PrinterErrorOnVote; ///< printer error on vote
						Glib::ustring s_TimeOutEndVotingExperience; ///< time out end voting experience
						Glib::ustring s_bottomLabel;	///< bottom label
						Glib::ustring s_endVotExpLabel; ///< end voting experience label
						Glib::ustring s_finalVotExpLabel; ///< final voting experience label
						Glib::ustring s_timeOutEndVotExpLabel;  ///< time out end voting experience label
						Glib::ustring s_PrinterErrorOnSmartcardRemoved; ///< printer error on smartcard removed
						Glib::ustring s_LoadingBallotOption;	///< loading ballot option
						Glib::ustring s_checksumLabel;  ///< checksum label
						Glib::ustring s_referendumHeaderFormat; ///< referendum header format
						Glib::ustring s_referendumHeaderFormatNoQuestion; ///< referendum header format no question
						Glib::ustring s_referendumFooterFormat; ///< referendum footer format
						Glib::ustring s_errorWritingCard; ///< referendum footer format


						/**
						 * @brief	Creates the pix buffer from bitmap and save iterator.
						 */

						void CreatePixBufFromBitmapAndSaveIt();

						/**
						 * @brief	Sends the pix buffer to vote.
						 */

						void SendPixBufToVote();

						Glib::Mutex syncCard;
						bool skipRecovery; ///< skip recovery mode
						bool firstExtractCard; ///< flag config first extract card before print ticket
						Smartmatic::GUI::Windows::BasicWindow * currentWindow; ///< current window
						static Smartmatic::Log::ISMTTLog* logger; ///< The logger

					};
				}
			}
		}
	}
}

#endif // _VOTING_EXPERIENCE_WIDGET_H_
