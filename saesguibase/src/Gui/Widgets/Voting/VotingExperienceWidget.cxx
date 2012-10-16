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

#include "VotingExperienceWidget.hxx"
#include <iostream>
#include "System/Sounds/smartmatic-sounds-manager.h"
#include <Configuration/configuration-persistence-manager.h>
#include <sstream>
#include <Operation/MachineOperationManager.hxx>
#include "Resources/election-string-resources-manager.h"
#include <Voting/VotingDevice/card-data-schema.hxx>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include <Functionalities/time-functionality.h>
#include "Printing/TimeoutPrintDocument.h"
#include "Printing/SmartcardRemovedPrintDocument.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Configuration/label-configuration.h"
#include "Functionalities/time-functionality.h"
#include <Operation/Card/CardController.hxx>
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Voting/Vote/VoteCode.hxx>
#include <Voting/Vote/VoteWrapper.hxx>
#include <Printing/PrinterStatusNotifier.h>
#include <Gui/Widgets/Voting/FactoryVotingWidget.hxx>
#include <Configuration/s-a-e-s-common-conf-manager.h>
#include <System/Exception/InvalidCardContentException.hxx>
#include <System/Exception/IOCardException.h>
#include <Operation/AlarmMessage.hxx>
#include <Operation/Voting/VotingOperation.hxx>
#include <Operation/FormatLabel.hxx>
#include <Operation/WindowsManager.hxx>
#include <Operation/Card/CardMonitor.hxx>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///< macro for gettext
#else
#define _(String) (String) ///< macro without gettext
#endif

#define N_(String) (String) ///< macro not translate

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::Environment;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::System::Sounds;
using namespace Smartmatic::SAES::Common::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::GUI::Operation;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::Operation::Card;

bool VotingExperienceWidget::simulationMode = false;

ISMTTLog* VotingExperienceWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.VotingExperienceWidget",GETTEXT_PACKAGE);

VotingExperienceWidget::VotingExperienceWidget()
:Smartmatic::GUI::Widgets::StepWidget()
{
	currentWindow = WindowsManager::getInstance()->current();

	SoundVoting=SAESGUIConfigurationManager::Current()->getVotingExperienceSound();
	IsInInterrupt = false;

	//TimeFunctionality::StartTimePrintOut();
	alreadyInTransition = false;
	detectCardExtractionEnable = true;
	isBallotOptionSelection = false;
	clientAreaWidth = 0;
	clientAreaHeight = 0;
	timeConnector = 10;
	timeConnectorLoading = 50;
	currentContestIndex = 0;
	totalContests = 0;
	welcomeShow = false;
	showBackInParty = true;
	comeFromAttrSelection = false;
	partySelectionWidget = NULL;
	ballotOptionSelectionWidget = NULL;
	ballotConfirmWidget = NULL;
	superNullSelectionWidget = NULL;
	welcomeWidget = NULL;
	customAttrWidget = NULL;
	contestNullWidget = NULL;
	interruptWidget = NULL;

	loadingFrame = NULL;
	checksumLabel = NULL;
	votePrintDocument = NULL;
	timeoutCounter = 0;
	loadingBallotsNumber = 0;
	referendumSelectionWidget = NULL;

	cardRemovedWidget = FactoryVotingWidget::createCardRemovedWidget();
	removeCardWidget = FactoryVotingWidget::createRemoveCardWidget();
	printVoteWidget = FactoryVotingWidget::createPrintVoteWidget();
	endPrintVoteWidget = FactoryVotingWidget::createEndPrintVoteWidget();
	printVoteErrorWidget = FactoryVotingWidget::createPrintVoteErrorWidget();
	printTimeOutWidget = FactoryVotingWidget::createPrintTimeOutWidget();
	interruptWidget = FactoryVotingWidget::createInterruptWidget();

	connInterruptButton = interruptWidget->getSignalEnd().connect(sigc::mem_fun(this, &VotingExperienceWidget::endVoting));

	TimeOutFinal=SAESGUIConfigurationManager::Current()->getTimeOutCard();

	success = false;
	sortAlphabetically = false;
	showPrintImage = true;
	
	currentWindow->getContentSize(clientAreaWidth, clientAreaHeight);
	currentWindow->getContentSize(windowWidth, windowHeight);

	config = SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration();
	questionConfig =SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration(); 

	sortAlphabetically = SAESGUIConfigurationManager::Current()->GetSortAlphabetically();

	timeConnector = config.getConnectTimer();
	timeConnectorLoading = config.getConnectTimerLoading(); 
	loadingBallotsNumber = config.getNumberOfBallotsToDisplayLoadingBallotMessage();
	firstExtractCard = SAESGUIConfigurationManager::Current()->getVotingExperienceConfiguration().getRemoveCardFirst();

	checksumLabel = new Label(_("Smartmatic.SAES.GUI.Windows.VotingWindow.ChecksumErrorLabel"));
	LabelConfiguration checksumLabelConf = SAESGUIConfigurationManager::Current()->GetCheckSumLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(checksumLabel, checksumLabelConf);
	
	loadingLabel = manage(new Label());
	LabelConfiguration loadingLabelConf = SAESGUIConfigurationManager::Current()->GetLoadingBallotsLabelConfiguration();
	LabelConfiguration::SetLabelConfiguration(loadingLabel, loadingLabelConf);
		
	loadingFrame = new Frame();
	loadingFrame->add(*loadingLabel);
	loadingFrame->set_shadow_type (SHADOW_NONE);

	votingWidgetManager = VotingWidgetManager::getInstance();
	electionWrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection();
}

VotingExperienceWidget::~VotingExperienceWidget()
{
	dispose();
}

void VotingExperienceWidget::dispose()
{
	this->remove();

	stopCheckCardPresent();

	simulationMode = false;
	if(votingWidgetManager) votingWidgetManager->clearBallotOptionSelectionWidget();
	connDetectExtract.disconnect();
	connAlarmAndBack.disconnect();
	connRefresh.disconnect();
	connRefreshTimeout.disconnect();
	connAlarmNotRemoveCard.disconnect ();
	connectTimeout.disconnect ();
	connection_partySelectionWidget_null_clicked.disconnect ();
	connection_partySelectionWidget_back_clicked.disconnect ();
	connection_partySelectionWidget_party_clicked.disconnect ();
	connection_ballotOptionSelectionWidget_accept_clicked.disconnect ();
	connection_ballotOptionSelectionWidget_back_clicked.disconnect ();
	connection_ballotOptionSelectionWidget_ballotOption_clicked.disconnect ();
	connInterruptButton.disconnect ();
	possibleWelcomeTimeout.disconnect ();
	connRefresh.disconnect ();
	connectionShowFinalMessage.disconnect();

	if(ballotConfirmWidget)
	{
		delete ballotConfirmWidget;
		ballotConfirmWidget = NULL;
	}
	if(superNullSelectionWidget)
	{
		delete superNullSelectionWidget;
		superNullSelectionWidget = NULL;
	}
	if(welcomeWidget)
	{
		delete welcomeWidget;
		welcomeWidget = NULL;
	}
	if(customAttrWidget)
	{
		delete customAttrWidget;
		customAttrWidget = NULL;
	}
	if(contestNullWidget)
	{
		delete contestNullWidget;
		contestNullWidget = NULL;
	}
	if(interruptWidget)
	{
		delete interruptWidget;
		interruptWidget = NULL;
	}
	if(loadingFrame)
	{
		delete loadingFrame;
		loadingFrame = NULL;
	}
	if(checksumLabel)
	{
		delete checksumLabel;
		checksumLabel = NULL;
	}
	if(votePrintDocument)
	{
		delete votePrintDocument;
		votePrintDocument = NULL;
	}
	if(referendumSelectionWidget)
	{
		delete referendumSelectionWidget;
		referendumSelectionWidget = NULL;
	}
	if(cardRemovedWidget)
	{
		delete cardRemovedWidget;
		cardRemovedWidget = NULL;
	}
	if (removeCardWidget)
	{
		delete removeCardWidget;
		removeCardWidget = NULL;
	}
	if (printVoteWidget)
	{
		delete printVoteWidget;
		printVoteWidget = NULL;
	}
	if (endPrintVoteWidget)
	{
		delete endPrintVoteWidget;
		endPrintVoteWidget = NULL;
	}
	if (printVoteErrorWidget)
	{
		delete printVoteErrorWidget;
		printVoteErrorWidget = NULL;
	}
	if (printTimeOutWidget)
	{
		delete printTimeOutWidget;
		printTimeOutWidget = NULL;
	}
}

void VotingExperienceWidget::start()
{
	votingExperienceController = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getVotingExperienceController();
	votingWidgetManager->update();
	SetLabelsText();
    int timer = electionWrapper->getElection().getVoting_time_out();

    if (timer > 0)
    {
        connectTimeout = Glib::signal_timeout().connect_seconds(sigc::bind(sigc::mem_fun(*this, &VotingExperienceWidget::onTimeout), 0), timer);
    }

	if(VotingOperation::getVoteMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R)
	{
		if(votingExperienceController->isNewRecoveryType())
		{
			if (firstExtractCard)
			{
				verifyCardRemoved(true);
			}
			else
			{
				ShowEndVotingExperience(true);
			}
			detectCardExtractionEnable = false;
		}
		else
		{
			startVoting();
		}
	}
	else
	{
		startVoting();
	}

	if(detectCardExtractionEnable && !simulationMode)
	{
		//CARD EXTRACTION LOGIC
		if(SAESGUIConfigurationManager::Current()->getDetectCardExtraction())
		{
			InvalidCard = false;
			IsInInterrupt = false;
			wasPresent = true;
			extractionCounter = 0;

			int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getVotingExperienceWindow();
			sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
						   &VotingExperienceWidget::DetectExtract), 0);
			connDetectExtract = Glib::signal_timeout().connect(my_slot,timerRefresh);
		}
	}

	//TimeFunctionality::StartTimePrintOut();
}



/*******************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
							VOTING WINDOW LOGIC
********************************************************************************
********************************************************************************
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::PerformBackStep()
{
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PerformBackStepInternal), timeConnector);
}

void VotingExperienceWidget::PerformBackStepInternal()
{
	bool canMoveBack = votingExperienceController->moveContestListBack();

	if(canMoveBack)
		PerformNextStep();
	else
	{
		if(config.getShowNullQuestionInBack())
			ShowNullVoteQuestion();
	}
}

void VotingExperienceWidget::PerformNextStep()
{
	if(!alreadyInTransition)
	{
		logger->Debug("entered transition");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PerformNextStepInternal), timeConnector);
		alreadyInTransition = true;
	}
	else
	{
		logger->Debug("already in transition");
	}
}

void VotingExperienceWidget::PerformNextStepInternal()
{
	VotingExperienceController::VotingExperienceType nextStep = votingExperienceController->getNextTypeAction();

	switch(nextStep)
	{
		case VotingExperienceController::VOTING_CONTROLLER_CONTEST:
			logger->Debug("Get next content list");
			GetContestList();			
			break;
		case VotingExperienceController::VOTING_CONTROLLER_CUSTOM_ATTRIBUTE_DEFINITION:
			logger->Debug("Get Custom Attribute definition");
			PerformQuestionAction();
			break;
		case VotingExperienceController::VOTING_CONTROLLER_CLOSE:
			logger->Debug("controller close");
			if (firstExtractCard)
			{
				verifyCardRemoved();
			}
			else
			{
				ShowEndVotingExperience();
			}
			break;
		default:
			break;
	}
	alreadyInTransition = false;
}

void VotingExperienceWidget::GetContestList()
{
	contestList = votingExperienceController->getCurrentContestList();

	if (contestList.size() > 0)
	{
		iterContest = contestList.begin();
		currentContestIndex = 0;
		totalContests = (int)contestList.size();
		GetNextContest();
	}
}

void VotingExperienceWidget::GetNextContest()
{
	if(currentContestIndex < totalContests)
	{
		currentContestIndex++;
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::ShowWelcomeContestMessage), timeConnector);
	}
	else
	{
		votingExperienceController->moveContestListForward();
		PerformNextStep();
	}
}

void VotingExperienceWidget::GetPreviousContest()
{
	currentContestIndex--;
	
	if(currentContestIndex <= 0)
	{
		currentContestIndex = 0;
		PerformBackStep();
	}
	else
	{
		SetActualContestFromIndex(currentContestIndex);
		GetPartySelection();

		if(config.getShowBallotOptionsInContestBack() && 
		   votingExperienceController->isThereAnyPartySelectedFromContest(actualContest))
		{
			actualParty = previousParty;
			ConstructAndShowBallotOptionSelection();
		}
		else
			GetAndShowPartySelection();
	}
}

void VotingExperienceWidget::SetActualContestFromIndex(int index)
{
	iterContest = contestList.begin();

	for(int i = 1; i < index; i++)
		iterContest++;
	
	actualContest = *iterContest;

	if(index > 1)
		showBackInParty = false;
	else
		showBackInParty = true;
}

void VotingExperienceWidget::setActualContest(Smartmatic::SAES::Voting::Election::Contest contestA)
{
	actualContest = contestA;
}

/*******************************************************************************
********************************************************************************
							 RECOVERY VOTE
********************************************************************************
*******************************************************************************/

bool VotingExperienceWidget::CreateVoteAndCheckIfRecovery()
{
	bool returnVariable = false;
	
	if(VotingOperation::getVoteMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R)
	{
		Smartmatic::System::SafeBuffer bufferChecksum;
		Vote::Vote * vote = votingExperienceController->getVote();
		Vote::VoteCode::generateChecksum(*vote, bufferChecksum);
		std::string calcChecksum = bufferChecksum.GetBase64Data();

		std::string recoveryChecksum = votingExperienceController->getChecksumVote();

		logger->Debug("Recovery checksum: " + recoveryChecksum);
		logger->Debug("Vote checksum: " + calcChecksum);

		if(calcChecksum != recoveryChecksum)
		{
			logger->Debug("Recovery vote is bad");
			returnVariable = true;
		}
		else
		{
			logger->Debug("recovery vote is ok");
		}
	}
	
	return returnVariable;
}

/*******************************************************************************
********************************************************************************
							 END VOTING EXPERIENCE
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::verifyCardRemoved(bool skipRecovery)
{
	this->skipRecovery = skipRecovery;
	connectTimeout.disconnect();
	stopCheckCardPresent();
	detectCardExtractionEnable = false;

	//CARD EXTRACTION LOGIC
	if(!CardMonitor::getInstance()->isCardPresent())
	{
		//sleep(1);
		logger->Debug("card removed");
		success=true;
		initializePrintVote();
	}
	else
	{
		//CARD NO EXTRACT
		//INTERFACE

		showStepWidget(removeCardWidget);

		//CALL RefreshTimeout
		int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getEndVotingExperienceWindow();
		sigc::slot<bool> my_slot6 = sigc::bind(sigc::mem_fun(*this,
		&VotingExperienceWidget::RefreshTimeout), 0);
		connRefreshTimeout.disconnect();
		connRefreshTimeout = Glib::signal_timeout().connect(my_slot6,timerRefresh);
	}
}

void VotingExperienceWidget::ShowEndVotingExperience(bool skipRecovery)
{
	this->skipRecovery = skipRecovery;
	initializePrintVote();
}

void VotingExperienceWidget::initializePrintVote()
{
	if(!skipRecovery)
	{
		if(!CreateVoteAndCheckIfRecovery())
		{
			connectTimeout.disconnect();
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PerformEndVotingExperience), timeConnector);
		}
		else
		{
			ShowErrorChecksum();
		}
	}
	else
	{
		connectTimeout.disconnect();
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PerformEndVotingExperience), timeConnector);
	}
}

void VotingExperienceWidget::ShowErrorChecksum()
{
	connectTimeout.disconnect();
	setWidget(checksumLabel);

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::ShowErrorChecksumInternal), timeConnector);
}

void VotingExperienceWidget::ShowErrorChecksumInternal()
{
	sleep(SAESGUIConfigurationManager::Current()->getCheckSumFailTimerMessage());
	switch(SAESGUIConfigurationManager::Current()->getCheckSumFailOption())
	{
		case CheckSumFailOption::CONFIGURATION_CLEANSELECTIONS:
		{
			votingWidgetManager->clearBallotOptionSelectionWidget();
			currentContestIndex = 0;
			GetNextContest();
		}
			break;
		case CheckSumFailOption::CONFIGURATION_MAINTAINSELECTIONS:
			votingWidgetManager->clearBallotOptionSelectionWidget();
            currentContestIndex = 0;
			GetNextContest();
			break;
		case CheckSumFailOption::CONFIGURATION_CLOSEVOTINGEXPERIENCE:
			FinalEndVotingExperience();
			break;
	}
}

void VotingExperienceWidget::PerformEndVotingExperience()
{
	detectCardExtractionEnable = false;
	showStepWidget(printVoteWidget);

	try
	{
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(SoundVoting);

		if (votePrintDocument) delete votePrintDocument;

		Vote::Vote * vote = votingExperienceController->getVote();
		votePrintDocument = new VotePrintDocument(
				Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),
                *vote);

		if(!Glib::thread_supported()) Glib::thread_init();
		Glib::Thread::create(sigc::mem_fun(*this, &VotingExperienceWidget::LaunchPrintThread), false);

		bool doPowerCycle =SAESCommonConfigurationManager::Current()->getSmartCardConfiguration().getSuspendResumeEachVote();
		if(doPowerCycle)
		{
			logger->Debug("trying to power cycle the reader");
			Smartmatic::SAES::Operation::Card::CardController::getInstance()->doReaderPowerCycle();
			logger->Debug("Command Done");
		}
	}
	catch(Smartmatic::System::Exception::ElectionException & ex)
	{   
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
        AlarmMessage::alarm(AlarmEnum::CONFIGURATION_UNEXPECTED);
		ChangeErrorImage();
		FinalEndVotingExperience( N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote"));
	}
	catch(...)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__;
        logger->Debug(ss.str());
        AlarmMessage::alarm(AlarmEnum::CONFIGURATION_UNEXPECTED);
		ChangeErrorImage();
		FinalEndVotingExperience( N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote"));
	}
}

/*******************************************************************************
********************************************************************************
							 PRINT TICKET
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::PrintTicketDone()
{
	bool printResult;
	Glib::ustring msg;
	PrinterStatusNotifier notifier;

	detectCardExtractionEnable = false;
	
	printDocumentResult.getResult(printResult, msg);
	logger->Debug("Print " + std::string (printResult ? "ok":"error"));
	logger->Debug("Print Msg: " + msg);

	if(!printResult)
	{
		AlarmMessage::alarm(AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE);
		ChangeErrorImage();
		FinalEndVotingExperience( N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote"));
	}
	else if (firstExtractCard)
	{
		FinalEndVotingExperience();
	}
	else
	{
		//CARD EXTRACTION LOGIC
		if(!CardMonitor::getInstance()->isCardPresent())
		{
			sleep(1);
			logger->Debug("card removed");
			success=true;
			FinalEndVotingExperience();
		}
		else
		{
			//CARD NO EXTRACT
			//INTERFACE

			showStepWidget(removeCardWidget);

			//CALL RefreshTimeout
			int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getEndVotingExperienceWindow();
			sigc::slot<bool> my_slot6 = sigc::bind(sigc::mem_fun(*this,
			&VotingExperienceWidget::RefreshTimeout), 0);
			connRefreshTimeout = Glib::signal_timeout().connect(my_slot6,timerRefresh);
		}
	}	
}

void VotingExperienceWidget::LaunchPrintThread()
{
	votePrintDocument->Print();
	printDocumentResult = votePrintDocument->getDocumentResult ();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PrintTicketDone), 1000);
}

void VotingExperienceWidget::ChangeErrorImage()
{
	showStepWidget(printVoteErrorWidget);
}

void VotingExperienceWidget::FinalEndVotingExperience(string alarm)
{
	if(showPrintImage)
	{
		showStepWidget(endPrintVoteWidget);
		sigc::slot<bool> my_slotFinal = sigc::bind(sigc::mem_fun(*this,	&VotingExperienceWidget::FinalEndVotingExperienceThread), 0, alarm);
		int timeToShow = SAESGUIConfigurationManager::Current()->getTimeToShowFinalMessage();
		connectionShowFinalMessage = Glib::signal_timeout().connect(my_slotFinal,timeToShow*1000);
	}
	else
	{
		sigc::slot<bool> my_slotFinal = sigc::bind(sigc::mem_fun(*this,	&VotingExperienceWidget::FinalEndVotingExperienceThread), 0, alarm);
		int timeToShow = SAESGUIConfigurationManager::Current()->getTimeToShowFinalMessage();
		connectionShowFinalMessage = Glib::signal_timeout().connect(my_slotFinal,timeToShow*1000);
	}
}

bool VotingExperienceWidget::FinalEndVotingExperienceThread(int timer_num, std::string alarm)
{
	logger->Debug("Final end voting experience thread");
	CheckComposeString(alarm);

	votingExperienceController->dispose();
	
	if(!alarm.empty())
	{
		signalAlarm_detected.emit( _(alarm.c_str()));
	}
	else
	{
		PrinterStatusNotifier notifier;
		PrinterStatusNotifier::PhysichalStateEnumType state = notifier.getPrinterState();
		bool neop_state = ((state &  PrinterStatusNotifier::PSTATE_NEAR_END_OF_PAPER) == PrinterStatusNotifier::PSTATE_NEAR_END_OF_PAPER);
		bool is_neop_blocking = SAESGUIConfigurationManager::Current ()->getWaitingForCardWindowConfiguration ().getIsNeopBlockingCondition ();

		if ( neop_state && is_neop_blocking )
		{
			AlarmMessage::alarm(AlarmEnum::CONFIGURATION_PRINTERNEOPAFTERVOTE);
			signalAlarm_detected.emit( _("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterNearEndOfPaper"));
		}
	}

    currentWindow->setTitleLabelConfiguration(SAESGUIConfigurationManager::Current()->GetEmptyWindowTitleFormConfiguration());

	signalEndVotingExperinece.emit();
	return false;
}

void VotingExperienceWidget::showVotingFrameBase(VotingFrameBase * widget)
{
	currentWindow->setTitleLabelConfiguration(widget->getTitleLabelConfig());
	currentWindow->setBottomLabelConfiguration(widget->getBottomLabelConfig());
	showStepWidget(widget);
}

void VotingExperienceWidget::showStepWidget(StepWidget * widget)
{
	SetLabelsText();
	widget->setName(VotingOperation::getWindowName());
	currentWindow->popPushStepWidget(widget);
}

void VotingExperienceWidget::GetCurrentContestReources(Glib::ustring& contestClassName,
        Glib::ustring& contestClassDescription,
        Glib::ustring& contestTitle,
        Glib::ustring& contestAbstract,
        Glib::ustring& contestHelp)
{
  Election::Contest_class contestClass=  electionWrapper->getContestClass(actualContest.getContest_class_code());

  contestClassName = ElectionStringResourcesManager::Current()->getResource(contestClass.getName_key());
  contestClassDescription = ElectionStringResourcesManager::Current()->getResource(contestClass.getDescription_key());

  contestTitle = ElectionStringResourcesManager::Current()->getResource(actualContest.getTitle_key());
  contestAbstract= ElectionStringResourcesManager::Current()->getResource(actualContest.getAbstract_key());
  contestHelp= ElectionStringResourcesManager::Current()->getResource(actualContest.getHelp_key());
}

void VotingExperienceWidget::startVoting()
{
	SetLabelsText();
	ShowNullVoteQuestion();
}

/*******************************************************************************
********************************************************************************
							SPUER NULL VOTE WINDOW
********************************************************************************
*******************************************************************************/ 

void VotingExperienceWidget::ShowNullVoteQuestion()
{
	if(config.getShowBlankVoteQuestion())
	{
		if (superNullSelectionWidget)
		{
			delete superNullSelectionWidget;
			superNullSelectionWidget = NULL;
		}

		superNullSelectionWidget = FactoryVotingWidget::createSuperNullSelectionWidget();
		superNullSelectionWidget->signal_cancel().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_NormalVote));
		superNullSelectionWidget->signal_accept().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_SuperNullVote));

		showStepWidget(superNullSelectionWidget);
	}
	else
	{
		on_NormalVote();
	}
}

void VotingExperienceWidget::on_NormalVote()
{
	PerformNextStep();
}

void VotingExperienceWidget::on_SuperNullVote()
{
    votingExperienceController->sendBlankVoteResponse();

	if (firstExtractCard)
	{
		verifyCardRemoved();
	}
	else
	{
		ShowEndVotingExperience();
	}
}



/*******************************************************************************
********************************************************************************
						WELCOME QUESTION DIALOG
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::PerformQuestionAction()
{
	currentcustomAttribute = votingExperienceController->getNextCustomAttributeDefinition();
	
	if(questionConfig.getShowWelcomeQuestion())
		ShowQuestionWelcome();
	else
		CreateQuestionDialog();
}

void VotingExperienceWidget::ShowQuestionWelcome()
{
	Glib::ustring name = ElectionStringResourcesManager::Current()->getResource(currentcustomAttribute.getName_key());
	Glib::ustring description = ElectionStringResourcesManager::Current()->getResource(currentcustomAttribute.getDescription_key());
	Glib::ustring toShow = Glib::ustring::compose(s_CustomAttributeQuestionFormat, name, description);
	int closeTimer = questionConfig.getWelcomeMessageQuestionTimer();
	bool showButton = questionConfig.getShowWelcomeMessageQuestionCloseButton();
	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->GetWelcomeContestCenterLabelConfiguration();

	if(welcomeWidget) delete welcomeWidget;
	
	welcomeWidget = new WelcomeMessageWidget(toShow, closeTimer, showButton);
	welcomeWidget->SetLabelConfiguration(labelConf);
	possibleWelcomeTimeout =  welcomeWidget->signal_Timeout().connect(sigc::mem_fun(this,&VotingExperienceWidget::on_TimeoutQuestionWelcome));

	welcomeShow = true;
	showStepWidget(welcomeWidget);
}

void VotingExperienceWidget::on_TimeoutQuestionWelcome()
{
	CreateQuestionDialog();
}
/*******************************************************************************
********************************************************************************
							 QUESTION DIALOG
********************************************************************************
*******************************************************************************/ 

void VotingExperienceWidget::CreateQuestionDialog()
{
	bool showConfirmation = questionConfig.getShowQuestionConfirmation();
	
	if (customAttrWidget) delete customAttrWidget;
	customAttrWidget = new CustomAttributeWidget(currentcustomAttribute, showConfirmation, sortAlphabetically);
	connection_question = customAttrWidget->signal_Answer().connect(sigc::mem_fun(this,&VotingExperienceWidget::on_QuestionAnswered));

	showStepWidget(customAttrWidget);
}

void VotingExperienceWidget::on_QuestionAnswered(string code)
{
	connection_question.disconnect();
	votingExperienceController->setCustomAttributeDefinitionResponse(currentcustomAttribute.getCode(), code);
	PerformNextStep();
}

/*******************************************************************************
********************************************************************************
							WELCOME CONTEST
********************************************************************************
*******************************************************************************/ 

void VotingExperienceWidget::ShowWelcomeContestMessage()
{
	if(config.getShowWelcomeContest() && !welcomeShow)
	{
		SetActualContestFromIndex(currentContestIndex);

		Glib::ustring toShow = FormatLabel::contestText(actualContest, s_ContestWelcomeFormat);
		int closeTimer = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getWelcomeMessageQuestionTimer();
		bool showButton = false;
		LabelConfiguration centerConf =  SAESGUIConfigurationManager::Current()->GetWelcomeContestCenterLabelConfiguration();

		if(welcomeWidget) delete welcomeWidget;
		welcomeWidget = new WelcomeMessageWidget(toShow, closeTimer, showButton);
		welcomeWidget->SetLabelConfiguration(centerConf);
		possibleWelcomeTimeout= welcomeWidget->signal_Timeout().connect(sigc::mem_fun(this,&VotingExperienceWidget::on_TimeoutContestWelcome));

		welcomeShow = false;
		showStepWidget(welcomeWidget);
	}
	else
	{
		welcomeShow = false;
		GetReferendumOrPartySelection();
	}
}

void VotingExperienceWidget::on_TimeoutContestWelcome()
{
	GetReferendumOrPartySelection();
}

/*******************************************************************************
********************************************************************************
						REFERENDUM WIDGET
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::GetReferendumOrPartySelection()
{
	SetActualContestFromIndex(currentContestIndex);

	if(actualContest.getIs_question())
	{
		GetAndShowReferendum();
	}
	else
		GetAndShowPartySelection();
}

void VotingExperienceWidget::GetAndShowReferendum()
{
	GetReferendum();
	ShowReferendum();
}

void VotingExperienceWidget::GetReferendum()
{
	if(referendumSelectionWidget) delete referendumSelectionWidget;

	connection_referendumSelectionWidget_null_clicked.disconnect();
	connection_referendumSelectionWidget_back_clicked.disconnect();
	connection_referendumSelectionWidget_accept_clicked.disconnect();

	referendumSelectionWidget = new ReferendumSelectionWidget(actualContest);
	referendumSelectionWidget->SetWidgetEnabled(true);
	connection_referendumSelectionWidget_null_clicked = referendumSelectionWidget->null_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::referendumSelection_on_null_clicked));
	connection_referendumSelectionWidget_back_clicked = referendumSelectionWidget->back_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::referendumSelection_on_back_clicked));
	connection_referendumSelectionWidget_accept_clicked = referendumSelectionWidget->accept_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::referendumSelection_on_accept_clicked));

	referendumSelectionWidget->ballotOption_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::referendumSelection_on_ballotOption_clicked));
	referendumSelectionWidget->set_size_request(clientAreaWidth, clientAreaHeight);
	referendumSelectionWidget->show();
	referendumSelectionWidget->show_all_children();

	static bool showBackInReferendum = SAESGUIConfigurationManager::Current()->GetReferendumConfiguration().getShowBackButton();

	bool showBack = votingExperienceController->canMoveBack(actualContest.getCode()) && showBackInReferendum;
	comeFromAttrSelection = votingExperienceController->canMoveBack(actualContest.getCode());
	referendumSelectionWidget->SetBackButton(showBack);

	list<Election::Eligible_option> principalBallotList;

	try
	{
		electionWrapper->fillAllEligibleOptionsByContest(actualContest, principalBallotList);
	}
	catch(...)
	{
		logger->Debug("ERROR - electionWrapper->fillAllEligibleOptionsByContest");
	}

	Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir;

	referendumSelectionWidget->Initialize(principalBallotList, saesDir);
}

void VotingExperienceWidget::ShowReferendum()
{
	isBallotOptionSelection = false;
	showVotingFrameBase(referendumSelectionWidget);
}

void VotingExperienceWidget::referendumSelection_on_back_clicked()
{
	connection_referendumSelectionWidget_back_clicked.disconnect();

	GetPreviousContest();
}

void VotingExperienceWidget::referendumSelection_on_accept_clicked()
{
	connection_referendumSelectionWidget_accept_clicked.disconnect();

	GetNextContest();
}

void VotingExperienceWidget::referendumSelection_on_null_clicked()
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - referendumSelection_on_null_clicked");
		return;
	}

	if(contestNullWidget) delete contestNullWidget;
//TODO change resources
	contestNullWidget = new ContestNullSelectionWidget(true);
	connection_null_voteclicked = contestNullWidget->signal_accept().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_ReferendumNormalVote));
	contestNullWidget->signal_cancel().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_ContestNullVote));

	showStepWidget(contestNullWidget);
}
void VotingExperienceWidget::on_ReferendumNormalVote()
{
	ShowReferendum();
}

void VotingExperienceWidget::referendumSelection_on_ballotOption_clicked(string ballotOptionCode, bool isSelected)
{
	votingExperienceController->setBallotOptionState(actualContest.getCode(), "x", ballotOptionCode, isSelected);
}

/*******************************************************************************
********************************************************************************
						PARTY SELECTION WIDGET
********************************************************************************
*******************************************************************************/
void VotingExperienceWidget::GetAndShowPartySelection()
{
	GetPartySelection();
	ShowPartySelection();
}

void VotingExperienceWidget::GetPartySelection()
{	
	SetActualContestFromIndex(currentContestIndex);

	if(partySelectionWidget)
	{
		connection_partySelectionWidget_null_clicked.disconnect();
		connection_partySelectionWidget_back_clicked.disconnect();
		connection_partySelectionWidget_party_clicked.disconnect();
	}

	partySelectionWidget = votingWidgetManager->getPartySelectionWidgetByContest(actualContest.getCode());
	connection_partySelectionWidget_null_clicked = partySelectionWidget->null_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::partySelection_on_null_clicked));
	connection_partySelectionWidget_back_clicked = partySelectionWidget->back_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::partySelection_on_back_clicked));
	connection_partySelectionWidget_party_clicked = partySelectionWidget->party_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::partySelection_on_party_clicked));
	partySelectionWidget->SetWidgetEnabled(true);

	bool showBack = votingExperienceController->canMoveBack(actualContest.getCode());//  && showBackInParty;
	comeFromAttrSelection = votingExperienceController->canMoveBack(actualContest.getCode());
	partySelectionWidget->SetBackButton(showBack);
	partySelectionWidget->refresh();
}

void VotingExperienceWidget::ShowPartySelection()
{
	isBallotOptionSelection = false;

	connection_partySelectionWidget_back_clicked.disconnect();
	connection_partySelectionWidget_back_clicked = partySelectionWidget->back_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::partySelection_on_back_clicked));

	connection_partySelectionWidget_null_clicked.disconnect();
	connection_partySelectionWidget_null_clicked = partySelectionWidget->null_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::partySelection_on_null_clicked));

	if(actualContest.getIs_question())
	{
		ShowReferendum();
	}
	else
	{
		showVotingFrameBase(partySelectionWidget);
	}
}

void VotingExperienceWidget::partySelection_on_back_clicked()
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - partySelection_on_back_clicked");
		return;
	}

	connection_partySelectionWidget_back_clicked.disconnect();
	logger->Debug("partySelection_on_back_clicked ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	GetPreviousContest();
	logger->Debug("partySelection_on_back_clicked EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}

void VotingExperienceWidget::partySelection_on_party_clicked(Election::Party partySelected)
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - partySelection_on_party_clicked");
		return;
	}

	logger->Debug("partySelection_on_party_clicked ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	try
	{
		actualParty = partySelected;

		if(config.getEraseBallotOptionsInPartyChanged())
		{

			if(actualContest.getCode() != "")
			{
				if(votingExperienceController->isThereAnyPartySelectedFromContest(actualContest))
				{
					previousParty = votingExperienceController->getPartySelectedFromContest(actualContest);

					if(actualParty.getCode() !=  previousParty.getCode())
					{
						if(previousParty.getCode() != "")
							votingExperienceController->clearBallotOptionsSelectedByContestParty(actualContest, previousParty);
					}
				}
			}
		}

		ShowLoadingBallot();
	}
	catch(...)
	{
		logger->Debug("FATAL - party selection on party clicked");
	}
	logger->Debug("partySelection_on_party_clicked EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();

}



/*******************************************************************************
********************************************************************************
							NULL PARTY SELECTION 
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::partySelection_on_null_clicked()
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - partySelection_on_null_clicked");
		return;
	}

	connection_partySelectionWidget_null_clicked.disconnect();
	logger->Debug("partySelection_on_null_clicked ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	if(contestNullWidget) delete contestNullWidget;
	
	contestNullWidget = new ContestNullSelectionWidget();
	contestNullWidget->signal_cancel().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_ContestNormalVote));
	connection_null_voteclicked = contestNullWidget->signal_accept().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_ContestNullVote));

	showStepWidget(contestNullWidget);
	logger->Debug("partySelection_on_null_clicked EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}

void VotingExperienceWidget::on_ContestNormalVote()
{
	logger->Debug("on_ContestNormalVote ENTER, null cancelled");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	partySelectionWidget->SetWidgetEnabled(true);
	ShowPartySelection();
	logger->Debug("on_ContestNormalVote EXIT, null cancelled");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}

void VotingExperienceWidget::on_ContestNullVote()
{
	connection_null_voteclicked.disconnect();
	logger->Debug("on_ContestNullVote ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
    votingExperienceController->clearBallotOptionsSelectedByContest(actualContest);
	votingExperienceController->setNullPartyResponse(actualContest);
	GetNextContest();
	logger->Debug("on_ContestNullVote EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}



/*******************************************************************************
********************************************************************************
					LOADING BALLOT OPTION SELECTION WIDGET 
********************************************************************************
*******************************************************************************/ 

void VotingExperienceWidget::ShowLoadingBallot()
{
	loadingLabel->set_text(_(s_LoadingBallotOption.c_str()));
	
	switch(config.getLoadingBallotMessage())
	{
		case LoadingBallotMessage::CONFIGURATION_NEVER:
			ConstructAndShowBallotOptionSelection();
			break;
		case LoadingBallotMessage::CONFIGURATION_ALWAYS:
			setWidget(loadingFrame);
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::ConstructAndShowBallotOptionSelection), timeConnectorLoading);
			break;
		case LoadingBallotMessage::CONFIGURATION_SELECTIVE:
			if(loadingBallotsNumber <= 
			   votingWidgetManager->getBallotOptionSelectionTotalBallotsWidgetByContestParty(actualContest.getCode(), actualParty.getCode()))
			{
				setWidget(loadingFrame);
				Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::ConstructAndShowBallotOptionSelection), timeConnectorLoading);
			}
			else
			{
				ConstructAndShowBallotOptionSelection();
			}
			break;
		default:
			break;
	}
}

/*******************************************************************************
********************************************************************************
						BALLOT OPTION SELECTION WIDGET
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::GetBallotOptionSelection()
{
	if(ballotOptionSelectionWidget)
	{
		connection_ballotOptionSelectionWidget_accept_clicked.disconnect();
		connection_ballotOptionSelectionWidget_back_clicked.disconnect();
		connection_ballotOptionSelectionWidget_ballotOption_clicked.disconnect();
	}
	ballotOptionSelectionWidget = votingWidgetManager->getBallotOptionSelectionWidgetByContestParty(actualContest.getCode(), actualParty.getCode());
	ballotOptionSelectionWidget->RefreshLabels();
	connection_ballotOptionSelectionWidget_accept_clicked = ballotOptionSelectionWidget->accept_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::ballotOptionSelection_on_accept_clicked));
	connection_ballotOptionSelectionWidget_back_clicked = ballotOptionSelectionWidget->back_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::ballotOptionSelection_on_back_clicked));
	connection_ballotOptionSelectionWidget_ballotOption_clicked = ballotOptionSelectionWidget->ballotOption_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::ballotOptionSelection_on_ballotOption_clicked));
	ballotOptionSelectionWidget->SetWidgetEnabled(true);
	
	list <Election::Ballot_option> ballotsPreviousSelected = votingExperienceController->getBallotOptionsSelectedByContestParty(actualContest, actualParty);
	ballotOptionSelectionWidget->SetBallots(ballotsPreviousSelected);	
}

void VotingExperienceWidget::ShowBallotOptionSelection()
{
	isBallotOptionSelection = true;

	connection_ballotOptionSelectionWidget_back_clicked.disconnect();
	connection_ballotOptionSelectionWidget_back_clicked = ballotOptionSelectionWidget->back_clicked().connect(sigc::mem_fun(this,&VotingExperienceWidget::ballotOptionSelection_on_back_clicked));
	
	showVotingFrameBase(ballotOptionSelectionWidget);
}

void VotingExperienceWidget::ConstructAndShowBallotOptionSelection()
{
	GetBallotOptionSelection();
	ShowBallotOptionSelection();
}

void VotingExperienceWidget::ballotOptionSelection_on_back_clicked()
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - ballotOptionSelection_on_back_clicked");
		return;
	}

	connection_ballotOptionSelectionWidget_back_clicked.disconnect();
	logger->Debug("ballotOptionSelection_on_back_clicked ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	partySelectionWidget->SetWidgetEnabled(true);
	ShowPartySelection();
	logger->Debug("ballotOptionSelection_on_back_clicked EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}

void VotingExperienceWidget::ballotOptionSelection_on_ballotOption_clicked(string ballotOptionCode, bool isSelected)
{
	votingExperienceController->setBallotOptionState(actualContest.getCode(), actualParty.getCode(), ballotOptionCode, isSelected);
}

/*******************************************************************************
********************************************************************************
						VOTE CONFIRMATION DIALOG
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::ballotOptionSelection_on_accept_clicked()
{
	if (!simulationMode && !CardMonitor::getInstance()->isCardPresent())
	{
		logger->Debug("Card not present in - ballotOptionSelection_on_accept_clicked");
		return;
	}

	connection_ballotOptionSelectionWidget_accept_clicked.disconnect();
	logger->Debug("ballotOptionSelection_on_accept_clicked ENTER");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
	bool showBallotConfirmation = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getShowConfirmation();
	if(showBallotConfirmation)
	{
		LabelConfiguration headerConf =  SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionHeaderLabelConfiguration();
		LabelConfiguration footerConf =  SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionBottomLabelConfiguration();
		LabelConfiguration centerConf =  SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionCenterLabelConfiguration();

		if(ballotConfirmWidget) delete ballotConfirmWidget;

		ballotConfirmWidget = new QuestionSelectionWidget(false, false);
		
		ballotConfirmWidget->SetStrings(s_ConfirmSelectionMessage, s_ConfirmSelectionMessageHeader, s_ConfirmSelectionMessageFooter, "", "",
		                                s_ConfirmSelectionMessageAcceptButton, s_ConfirmSelectionMessageBackButton);
		ballotConfirmWidget->SetLabelsConfiguration(headerConf, footerConf, centerConf);

		ballotConfirmWidget->Initialize();
		ballotConfirmWidget->signal_accept().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_AcceptVote));
		ballotConfirmWidget->signal_cancel().connect(sigc::mem_fun(*this,&VotingExperienceWidget::on_BackVote));

		showStepWidget(ballotConfirmWidget);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::on_AcceptVote), timeConnector);
	}
	logger->Debug("ballotOptionSelection_on_accept_clicked EXIT");
	//TimeFunctionality::GetStartTimeDifferencePrintOut();
}

void VotingExperienceWidget::on_AcceptVote()
{
	if(currentContestIndex != totalContests)
	{
		logger->Debug("on_AcceptVote NEXT CONTEST");
		GetNextContest();
	}
	else
	{
		logger->Debug("on_AcceptVote NEXT STEP");
		votingExperienceController->moveContestListForward();
		PerformNextStep();
	}
	logger->Debug("on_AcceptVote EXIT");
}

void VotingExperienceWidget::on_BackVote()
{
	ShowBallotOptionSelection();
}

/*******************************************************************************
********************************************************************************
							PRINTING INTERFACE
********************************************************************************
*******************************************************************************/

void VotingExperienceWidget::job_event_callback (int job_id, int error_code)
{

}
void VotingExperienceWidget::on_status_reported (PrinterStatus *status)
{

}
void VotingExperienceWidget::on_ticket_printed (Gtk::PrintOperationResult result)
{
    sleep(2);
    FinalEndVotingExperience();
}
void VotingExperienceWidget::on_job_finished (const Glib::RefPtr<Gtk::PrintOperation>& operation)
{

}

void VotingExperienceWidget::ShowTimeOutEndVotingExperience()
{
	showStepWidget(printTimeOutWidget);
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::PerformTimeOutEndVotingExperience), timeConnector);
}

void VotingExperienceWidget::PerformTimeOutEndVotingExperience()
{
	detectCardExtractionEnable = false;

	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_TIMEOUT);
    sleep(2);
    bool printResult = false;
    Glib::ustring msg;

    try
    {

        TimeoutPrintDocument timeoutPrintDocument( Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(), ""/*votingExperienceController->getVoteCode()*/ );
        timeoutPrintDocument.Print();
        PrintDocumentResult res = timeoutPrintDocument.getDocumentResult ();
        res.getResult(printResult, msg);

		 if(!printResult)
		{
			AlarmMessage::alarm(AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE);
			ChangeErrorImage();
			FinalEndVotingExperience( _(s_PrinterErrorOnVote.c_str()));
		}
        else
        {
	        FinalEndVotingExperience( _(s_TimeOutEndVotingExperience.c_str()));
        }
	}
    catch(Smartmatic::System::Exception::ElectionException & ex)
    {
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
        ChangeErrorImage();
		FinalEndVotingExperience( _(s_PrinterErrorOnVote.c_str()));
    }

}

bool VotingExperienceWidget::onTimeout (int timer)
{
    ShowTimeOutEndVotingExperience();
    return false;
}

void VotingExperienceWidget::SetLabelsText()
{
	switch(VotingOperation::getVoteMode())
	{
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:

		s_CustomAttributeQuestionFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeQuestionFormat");
		s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat");
		s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion");
		s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat");
		s_FooterPartySelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterPartySelection");
		s_ContestWelcomeFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ContestWelcomeFormat");
		s_BallotHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat");
		s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion");
		s_BallotFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat");
		s_FooterBallotSelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterBallotSelection");
		s_ConfirmSelectionMessage = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessage");
		s_ConfirmSelectionMessageHeader = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageHeader");
		s_ConfirmSelectionMessageFooter = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageFooter");
		s_ConfirmSelectionMessageBackButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageBackButton");
		s_ConfirmSelectionMessageAcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageAcceptButton");
		s_TimeOutVotingExperience = _("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience");
		s_PrinterErrorOnVote = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote");
		s_TimeOutEndVotingExperience = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutEndVotingExperience");
		s_bottomLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BottomMessage");
		s_endVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.WaitPrintingTicket");
		s_finalVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BendPrintedTicket");
		s_timeOutEndVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience");
		s_PrinterErrorOnSmartcardRemoved = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnSmartcardRemoved");
		s_LoadingBallotOption = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LoadingBallotOption");
		s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat");
		s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion");
		s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat");
		break;

	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:

		s_CustomAttributeQuestionFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeQuestionFormat.Demo");
		s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat.Demo");
		s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion.Demo");
		s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat.Demo");
		s_FooterPartySelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterPartySelection.Demo");
		s_ContestWelcomeFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ContestWelcomeFormat.Demo");
		s_BallotHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat.Demo");
		s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion.Demo");
		s_BallotFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat.Demo");
		s_FooterBallotSelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterBallotSelection.Demo");
		s_ConfirmSelectionMessage = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessage.Demo");
		s_ConfirmSelectionMessageHeader = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageHeader.Demo");
		s_ConfirmSelectionMessageFooter = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageFooter.Demo");
		s_ConfirmSelectionMessageBackButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageBackButton.Demo");
		s_ConfirmSelectionMessageAcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageAcceptButton.Demo");
		s_TimeOutVotingExperience = _("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.Demo");
		s_PrinterErrorOnVote = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote.Demo");
		s_TimeOutEndVotingExperience = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutEndVotingExperience.Demo");
		s_bottomLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BottomMessage.Demo");
		s_endVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.WaitPrintingTicket.Demo");
		s_finalVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BendPrintedTicket.Demo");
		s_timeOutEndVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.Demo");
		s_PrinterErrorOnSmartcardRemoved = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnSmartcardRemoved.Demo");
		s_LoadingBallotOption = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LoadingBallotOption.Demo");
		s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat.Demo");
		s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion.Demo");
		s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat.Demo");
		break;

	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:

		s_CustomAttributeQuestionFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeQuestionFormat.Recovery");
		s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat.Recovery");
		s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion.Recovery");
		s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat.Recovery");
		s_FooterPartySelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterPartySelection.Recovery");
		s_ContestWelcomeFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ContestWelcomeFormat.Recovery");
		s_BallotHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat.Recovery");
		s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion.Recovery");
		s_BallotFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat.Recovery");
		s_FooterBallotSelection = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterBallotSelection.Recovery");
		s_ConfirmSelectionMessage = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessage.Recovery");
		s_ConfirmSelectionMessageHeader = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageHeader.Recovery");
		s_ConfirmSelectionMessageFooter = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageFooter.Recovery");
		s_ConfirmSelectionMessageBackButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageBackButton.Recovery");
		s_ConfirmSelectionMessageAcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ConfirmSelectionMessageAcceptButton.Recovery");
		s_TimeOutVotingExperience = _("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.Recovery");
		s_PrinterErrorOnVote = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnVote.Recovery");
		s_TimeOutEndVotingExperience = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutEndVotingExperience.Recovery");
		s_bottomLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BottomMessage.Recovery");
		s_endVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.WaitPrintingTicket.Recovery");
		s_finalVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.BendPrintedTicket.Recovery");
		s_timeOutEndVotExpLabel = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.TimeOutVotingExperience.Recovery");
		s_PrinterErrorOnSmartcardRemoved = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.PrinterErrorOnSmartcardRemoved.Recovery");
		s_LoadingBallotOption = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LoadingBallotOption.Recovery");
		s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat.Recovery");
		s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion.Recovery");
		s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat.Recovery");
		break;
	}

	s_errorWritingCard = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.ErrorWritingCard");;

	printVoteWidget->setText(_(s_endVotExpLabel.c_str()));
	endPrintVoteWidget->setText(_(s_finalVotExpLabel.c_str()));
	printTimeOutWidget->setText(_(s_timeOutEndVotExpLabel.c_str()));

	setBottomText(_(s_bottomLabel.c_str()));

	set_name(VotingOperation::getWindowName());
}

/*******************************************************************************
********************************************************************************
********************************************************************************
********************************************************************************
							CARD EXTRACTION DETECTION LOGIC
********************************************************************************
********************************************************************************
********************************************************************************
*******************************************************************************/ 

bool VotingExperienceWidget::CardIsValid()
{
	VotingDevice::Card_data cardDataCheck;
	bool isGood = false;

	try
	{
		if (Smartmatic::SAES::Operation::Card::CardController::getInstance()->readCardData(cardDataCheck))
		{
			if(cardDataCheck.getCard_status().compare("")==0)
			{
				logger->Debug("invalid data: card status could not be resolved");
				isGood = false;
			}
			else
			{
				bool cardUsed = !SAESGUIConfigurationManager::Current()->getMarkCardAsUsed () ||
						(cardDataCheck.getCard_status() == Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_USED) ||
						SAESFunctionalityConfigurationManager::Current()->getOperationConfiguration().getSimulateVotes();
				if (cardUsed && cardDataCheck.getActivation_code().compare( votingExperienceController->getActivationCode())==0)
				{
					logger->Debug("card is Good");
					isGood = true;
				}
				else if (votingExperienceController->getVotingMode() != Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S)
				{
					logger->Debug("error: card not used");
					isGood = false;
				}
				else
				{
					logger->Debug("Card simulate");
					isGood = true;
				}
			}
		}
	}
	catch (InvalidCardContentException& e )
	{
		isGood = false;
		logger->Debug (e.getMessage());
	}
	catch (IOCardException& e )
	{
		isGood = false;
		logger->Debug (e.getMessage());
	}
	catch (...)
	{
		isGood = false;
		logger->Debug ("Error read card data");
	}

	return isGood;
}

bool VotingExperienceWidget::DetectExtract (int timer)
{
	if(detectCardExtractionEnable == false)
		return false;

	bool present = CardMonitor::getInstance()->isCardPresent();

	if(present && !wasPresent)
	{
		wasPresent = true;
		cardInsertEvent();
	}
	else if (!present && wasPresent)
	{
		wasPresent = false;
		cardRemoveEvent();
	}

	return true;
}

void VotingExperienceWidget::cardInsertEvent()
{
	logger->Debug("Card insert event.");

	if (detectCardExtractionEnable)
	{
		if(IsInInterrupt && !InvalidCard)
		{
			bool cardValid = CardIsValid();
			if(cardValid)
			{
				if (ballotOptionSelectionWidget)
				{
					ballotOptionSelectionWidget->SetWidgetEnabled(true);
				}

				if (partySelectionWidget)
				{
					partySelectionWidget->SetWidgetEnabled(true);
				}

				if (referendumSelectionWidget)
				{
					referendumSelectionWidget->SetWidgetEnabled(true);
				}

				currentWindow->popStepWidget();

				InvalidCard = false;
				IsInInterrupt = false;
			}
			else
			{
				InvalidCard = true;
				interruptWidget->showCancelProcess();
			}
		}
		else if(IsInInterrupt && InvalidCard)
		{
			bool cardValid = CardIsValid();
			if(cardValid)
			{
				InvalidCard = false;
				IsInInterrupt = false;
				currentWindow->popStepWidget();
			}
		}

	}
}

void VotingExperienceWidget::cardRemoveEvent()
{
	logger->Debug("Card remove event.");

	if (detectCardExtractionEnable)
	{
		if(!IsInInterrupt)
		{
			possibleWelcomeTimeout.disconnect();
			extractionCounter++;
			if((SAESGUIConfigurationManager::Current()->getNumberOfExtractionsBeforeStop() != 0) && (extractionCounter == SAESGUIConfigurationManager::Current()->getNumberOfExtractionsBeforeStop()))
			{
				detectCardExtractionEnable = false;
				RefreshByTooManyExtracts();
			}
			else
			{
				IsInInterrupt = true;
				interruptWidget->showCardCounter();
				interruptWidget->setName(VotingOperation::getWindowName());
				currentWindow->pushStepWidget(interruptWidget);
			}
		}
	}
}

void VotingExperienceWidget::endVoting()
{
	showPrintImage = false;
	FinalEndVotingExperience ("");
}

void VotingExperienceWidget::RefreshByTooManyExtracts ()
{
	showPrintImage = false;

	showStepWidget(cardRemovedWidget);

	sigc::slot<bool> my_slot1 = sigc::bind(sigc::mem_fun(*this,
					   &VotingExperienceWidget::InitStopByExtractProcedure), 0);
	Glib::signal_timeout().connect(my_slot1,500);
}

bool VotingExperienceWidget::InitStopByExtractProcedure(int timer)
{	
	try
    {
		bool printResult = false;
		Glib::ustring msg = "";
		
        SmartcardRemovedPrintDocument smartcardRemovedPrintDocument( Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),
                                                                    "", //votingExperienceController->getVoteCode(),
                                                                    extractionCounter);
        smartcardRemovedPrintDocument.Print();
        PrintDocumentResult res = smartcardRemovedPrintDocument.getDocumentResult ();
        res.getResult(printResult, msg);

		 if(!printResult)
		{
			 AlarmMessage::alarm(AlarmEnum::CONFIGURATION_VOTEPRINTINGFAILURE);
		}
	}
    catch(Smartmatic::System::Exception::ElectionException & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
    }
	
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &VotingExperienceWidget::AlarmExtractionCounter),1000);

	return false;
}

void VotingExperienceWidget::AlarmExtractionCounter()
{
	logger->Debug("AlarmExtractionCounter");
	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_CARDEXTRACTIONCOUNTER);
	FinalEndVotingExperience(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.SmartCardExtracted"));
}

bool VotingExperienceWidget::AlarmNotRemoveCard(int timer)
{
	logger->Debug("AlarmNotRemoveCard");
	AlarmMessage::alarm(AlarmEnum::CONFIGURATION_CARDNOTREMOVEDAFTERVOTING);
	FinalEndVotingExperience(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.CardNotExtracted"));
	return false;		
}

bool VotingExperienceWidget::RefreshTimeout(int timer_num)
{
	timeoutCounter++;

	if ( ! CardMonitor::getInstance()->isCardPresent() )
	{
		if (firstExtractCard)
		{
			initializePrintVote();
		}
		else
		{
			connRefreshTimeout.disconnect();
			FinalEndVotingExperience();
		}
		return false;
	}
	else if (timeoutCounter == TimeOutFinal && !success)
	{
		if (firstExtractCard)
		{
			showPrintImage = false;
		}
		else
		{
			connRefreshTimeout.disconnect();
		}

		logger->Debug("TimeOutFinal CardNotRemovedAfterVoting");
		AlarmMessage::alarm(AlarmEnum::CONFIGURATION_CARDNOTREMOVEDAFTERVOTING);
		FinalEndVotingExperience(N_("Smartmatic.SAES.GUI.Windows.VotingWindow.CardNotExtracted"));
		return false;
	}
	return true;
}

void VotingExperienceWidget::setSimulationMode(bool enable)
{
	simulationMode = enable;
}

void VotingExperienceWidget::setDetectCardExtractionEnable(bool enable)
{
	detectCardExtractionEnable = enable;
}

bool VotingExperienceWidget::idleFunc()
{
	return false;
}

void VotingExperienceWidget::CheckComposeUString(Glib::ustring& stringToCheck)
{
	if(stringToCheck.size() > 2)
	{
		if(stringToCheck[stringToCheck.size() - 1] == ' ' &&
		   stringToCheck[stringToCheck.size() - 2] == '-')
		{
			size_t pos = stringToCheck.size();
			stringToCheck.erase(pos - 3, 3);
		}
	}
}

void VotingExperienceWidget::CheckComposeString(std::string& stringToCheck)
{
	if(stringToCheck.size() > 2)
	{
		if(stringToCheck[stringToCheck.size() - 1] == ' ' &&
		   stringToCheck[stringToCheck.size() - 2] == '-')
		{
			size_t pos = stringToCheck.size();
			stringToCheck.erase(pos - 3, 3);
		}
	}
}

VotingExperienceWidget::signal_back VotingExperienceWidget::signalEndVotingExperineceDetected()
{
	return signalEndVotingExperinece;
}

void VotingExperienceWidget::startCheckCardPresent()
{
	logger->Debug("Start polling card");

	connDetectExtract.disconnect();

	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getVotingExperienceWindow();
	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
				   &VotingExperienceWidget::DetectExtract), 0);

	connDetectExtract = Glib::signal_timeout().connect(my_slot,timerRefresh);
}

void VotingExperienceWidget::stopCheckCardPresent()
{
	logger->Debug("Stop polling card");
	connDetectExtract.disconnect();
}
