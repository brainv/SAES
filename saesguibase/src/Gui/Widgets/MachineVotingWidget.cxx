/**
 * @file MachineVotingWidget.cxx
 * @brief Body class voting experience widget
 * @date 08/03/2012
 * @author Yadickson Soto
 */

#include "MachineVotingWidget.hxx"
#include <Gui/Widgets/Voting/FactoryVotingWidget.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/Card/CardMonitor.hxx>
#include <Operation/Card/CardController.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Operation/AlarmMessage.hxx>
#include <Devices/barcode-device.h>
#include <Devices/alarm-device.h>
#include <Operation/WindowsManager.hxx>
#include "Printing/PrinterStatusNotifier.h"
#include <Voting/VotingDevice/card-data-wrapper.h>
#include <Operation/Voting/VotingOperation.hxx>
#include <Operation/Alarm/AlarmBoxMonitor.hxx>

#include "Voting/WaitingForCardWidget.hxx"
#include "Voting/PreviewWidget.hxx"
#include "Voting/SimulationWidget.hxx"
#include "Voting/language-selection-widget.h"
#include "Voting/VotingExperienceWidget.hxx"
#include <Operation/SaesEnqueuer.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Voting;
using namespace VotingDevice;
using namespace Smartmatic::GUI::Operation;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Functionality::Configuration;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::Operation::Alarm;

ISMTTLog* MachineVotingWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.MachineVotingWidget",GETTEXT_PACKAGE);

MachineVotingWidget::MachineVotingWidget(MenuWidget * menuWidget, HelpWidget * helpWidget)
: RunMachineWidget(menuWidget, helpWidget)
{
	this->setHelp(false);
	this->setExit(false);
	this->setShowBorder(true);
	this->setTitle(false);
	setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName());

	initialize();

	simulateProcess = false;
	simulateVote = SAESFunctionalityConfigurationManager::Current()->getOperationConfiguration().getSimulateVotes();

	waitingForCardWidget->refresh();
	setWidget(waitingForCardWidget);
}

MachineVotingWidget::~MachineVotingWidget()
{
	connReceived.disconnect();
	signalPopDispatcher.disconnect();

	dispose();

	this->remove();

	if (waitingForCardWidget)
	{
		delete waitingForCardWidget;
		waitingForCardWidget = NULL;
	}
	if (menuWidget)
	{
		delete menuWidget;
		menuWidget = NULL;
	}
	if (helpWidget)
	{
		delete helpWidget;
		helpWidget = NULL;
	}
	if (votingExperienceWidget)
	{
		delete votingExperienceWidget;
		votingExperienceWidget = NULL;
	}
	if (simulationWidget)
	{
		delete simulationWidget;
		simulationWidget = NULL;
	}
	if (languageSelectionWidget)
	{
		delete languageSelectionWidget;
		languageSelectionWidget = NULL;
	}
	if (previewWidget)
	{
		delete previewWidget;
		previewWidget = NULL;
	}
}

void MachineVotingWidget::initialize()
{
	votingExperienceWidget = NULL;

	waitingForCardWidget = FactoryVotingWidget::createWaitingForCardWidget();
	waitingForCardWidget->getSignalSim().connect(sigc::mem_fun(*this, &MachineVotingWidget::simCardData));
	waitingForCardWidget->getSignalBack().connect(sigc::mem_fun(*this, &MachineVotingWidget::back));

	simulationWidget = FactoryVotingWidget::createSimulationWidget();
	simulationWidget->getSignalEnd().connect(sigc::mem_fun(*this,&MachineVotingWidget::createCardData));

	languageSelectionWidget = FactoryVotingWidget::createVotingLanguageSelectionWidget();

	previewWidget = FactoryVotingWidget::createPreviewWidget();
	previewWidget->getSignalEnd().connect(sigc::mem_fun(*this,&MachineVotingWidget::restoreWidget));

	stepVoting = NONE;
}

void MachineVotingWidget::start()
{
	currentCardDataCode = "";
	stepVoting = WAITING;

	startCheckAlarmButton();
	startCheckAlarmBoxEvent();
	startCheckCardPresent();
	startCheckBarcode();

	setWidget(waitingForCardWidget);
	refresh();
}

void MachineVotingWidget::dispose()
{
	stopCheckAlarmButton();
	stopCheckAlarmBoxEvent();
	stopCheckCardPresent();
	stopCheckBarcode();

	currentCardDataCode = "";
	stepVoting = NONE;
	listWidget.clear();
}

void MachineVotingWidget::restoreWidget()
{
	start();
	remove();
	viewWidget(waitingForCardWidget);
}

void MachineVotingWidget::viewWidget(StepWidget * widget)
{
	BasicWindow * window = WindowsManager::getInstance()->current();
	window->popPushStepWidget(widget);
}

void MachineVotingWidget::startCheckCardPresent()
{
	logger->Debug("Start check card present");

	connCardInsertEvent.disconnect();
	connCardRemoveEvent.disconnect();

	connCardInsertEvent = CardMonitor::getInstance()->signalCardInsert.connect(sigc::mem_fun(*this, &MachineVotingWidget::cardInsertEvent));
	connCardRemoveEvent = CardMonitor::getInstance()->signalCardRemove.connect(sigc::mem_fun(*this, &MachineVotingWidget::cardRemoveEvent));
  connCardReaderUnresponsiveEvent = CardMonitor::getInstance()->signalCardReaderUnresponsive.connect(sigc::mem_fun(*this, &MachineVotingWidget::cardReaderUnresponsiveEvent));

	unsigned int pollingTime = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getWaitingCardWidget();

	CardMonitor::getInstance()->start(pollingTime);
}

void MachineVotingWidget::stopCheckCardPresent()
{
	logger->Debug("Stop check card present");

	CardMonitor::getInstance()->stop();

	connCardInsertEvent.disconnect();
	connCardRemoveEvent.disconnect();
  connCardReaderUnresponsiveEvent.disconnect();
}

void MachineVotingWidget::cardInsertEvent()
{
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MachineVotingWidget::cardInsert), 10);
}

void MachineVotingWidget::cardRemoveEvent()
{
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MachineVotingWidget::cardRemove), 10);
}

void MachineVotingWidget::cardReaderUnresponsiveEvent()
{
   	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MachineVotingWidget::cardReaderUnresponsive), 10);
}

void MachineVotingWidget::cardInsert()
{
	Glib::Mutex::Lock lock(syncCard);

	switch (stepVoting)
	{
		case WAITING:
			stepVoting = VALIDATE;
			startValidateCardData();
			break;

		case VALIDATE:
			break;

		case ERROR_VALIDATE:
			startValidateCardData();
			break;

		case SHOW_LANGUAGE:
			startValidateCardData();
			break;

		case VOTING:
			break;

		default:
			break;
	}
}

void MachineVotingWidget::cardRemove()
{
	Glib::Mutex::Lock lock(syncCard);

	remove();

	switch (stepVoting)
	{
		case WAITING:
			startCheckBarcode();
			viewWidget(waitingForCardWidget);
			currentCardDataCode = "";
			break;

		case VALIDATE:
			startCheckBarcode();
			viewWidget(waitingForCardWidget);
			break;

		case ERROR_VALIDATE:
			startCheckBarcode();
			currentCardDataCode = "";
			viewWidget(waitingForCardWidget);
			break;

		case SHOW_LANGUAGE:
			startCheckBarcode();
			viewWidget(waitingForCardWidget);
			break;

		case VOTING:
			currentCardDataCode = "";
			break;

		default:
			break;
	}
}

void MachineVotingWidget::cardReaderUnresponsive()
{
	// Glib::Mutex::Lock lock(syncCard);

	// Reset machine message
  setAlarm(AlarmEnum::CONFIGURATION_CARDREADERUNRESPONSIVE);
}

void MachineVotingWidget::startCheckBarcode()
{
	signalPopDispatcher.disconnect();
	connReceived.disconnect();
	connBarcodeConnected.disconnect();
	connBarcodeDisconnected.disconnect();
	signalCommandsSentResponse.disconnect();

	if(SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getAllowVotePreview())
	{
		logger->Debug("Check barcode event.");

    	if(!BarcodeDevice::Current()->sendPing())
    	{
    		BarcodeDevice::Current()->Resync();
    	}

		connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &MachineVotingWidget::recievedData));
		connBarcodeConnected = BarcodeDevice::Current()->signalConnected().connect(sigc::mem_fun(*this, &MachineVotingWidget::connectBarcode));
		connBarcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &MachineVotingWidget::disconnectBarcode));

		MachineOperationManager::getInstance()->getSaesEnqueuer()->flush();
		MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();

		signalPopDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &MachineVotingWidget::signalingPopDispatcher));
	}
}

void MachineVotingWidget::stopCheckBarcode()
{
	signalPopDispatcher.disconnect();
	connReceived.disconnect();
	connBarcodeConnected.disconnect();
	connBarcodeDisconnected.disconnect();
	signalCommandsSentResponse.disconnect();

	if(SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getAllowVotePreview())
	{
		logger->Debug("Stop check barcode");
		MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();
		MachineOperationManager::getInstance()->getSaesEnqueuer()->flush();
	}
}

void MachineVotingWidget::connectBarcode()
{
	stopCheckCardPresent();

	logger->Debug("Start reconfigure barcode.");

	std::string commandNames = SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getBarcodeCommandsName();

	BarcodeDevice::Current()->Resync();
	BarcodeDevice::Current()->SendConfigurationCommands(commandNames,true,false);

	signalCommandsSentResponse.disconnect();
	signalCommandsSentResponse = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &MachineVotingWidget::stopReconfigureBarcode));

	waitingForCardWidget->viewReconfigureBarcode();
}

void MachineVotingWidget::disconnectBarcode()
{
	refresh();
	startCheckCardPresent();
}

void MachineVotingWidget::refreshAll()
{

}

void MachineVotingWidget::stopReconfigureBarcode(int status)
{
	startCheckCardPresent();

	if (status)
	{
		logger->Debug("Reconfigure barcode success.");

	}
	else
	{
		logger->Debug("Reconfigure barcode fail.");
		BarcodeDevice::Current()->Close();
	}

	refresh();
}

void MachineVotingWidget::startCheckAlarmButton()
{
	logger->Debug("Start check alarm button");

	connAlarm.disconnect();
	connAlarm = AlarmDevice::Current()->signal_button_press_detected().connect(sigc::mem_fun(*this, &MachineVotingWidget::back));
}

void MachineVotingWidget::stopCheckAlarmButton()
{
	logger->Debug("Stop check alarm button");
	connAlarm.disconnect();
}

void MachineVotingWidget::startCheckAlarmBoxEvent()
{
	logger->Debug("Start check alarm box event");
	connAlarmMonitor.disconnect();

	if (AlarmBoxMonitor::getInstance()->isConnect())
	{
		connAlarmMonitor = AlarmBoxMonitor::getInstance()->signalDisconnect.connect(sigc::mem_fun(*this, &MachineVotingWidget::alarmBoxDisconnect));
	}
	else if (AlarmBoxMonitor::getInstance()->isRunning())
	{
		alarmBoxDisconnect();
	}
}

void MachineVotingWidget::stopCheckAlarmBoxEvent()
{
	logger->Debug("Stop check alarm box event");
	connAlarmMonitor.disconnect();
}

void MachineVotingWidget::refresh()
{
	waitingForCardWidget->refresh();
}

void MachineVotingWidget::simCardData()
{
	logger->Debug("Simulate card data");

	stopCheckCardPresent();
	stopCheckBarcode();
	simulationWidget->initialize();
	viewWidget(simulationWidget);
}

void MachineVotingWidget::startValidateCardData()
{
	logger->Debug("Start validate card data");

	stopCheckBarcode();
	waitingForCardWidget->viewCardValidate();
	simulateProcess = false;

	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &MachineVotingWidget::readCardData), false);
}

void MachineVotingWidget::startVotingExperience()
{
	Glib::Mutex::Lock lock (syncVoting);
	stopCheckAlarmButton();
	stopCheckAlarmBoxEvent();

	logger->Debug("Start voting experience");
	currentCardDataCode = "";

	signalEndVoting.disconnect();

	if (votingExperienceWidget)
	{
		delete votingExperienceWidget;
		votingExperienceWidget = NULL;
	}

	votingExperienceWidget = FactoryVotingWidget::createVotingExperienceWidget();
	signalEndVoting = votingExperienceWidget->signalEndVotingExperineceDetected().connect(sigc::mem_fun(*this, &MachineVotingWidget::stopVotingExperience));
	votingExperienceWidget->start();

	stepVoting = VOTING;
}

void MachineVotingWidget::stopVotingExperience()
{
	Glib::Mutex::Lock lock (syncVoting);

	if (!votingExperienceWidget)
	{
		return;
	}

	startCheckAlarmButton();
	startCheckAlarmBoxEvent();

	logger->Debug("Stop voting experience");
	signalEndVoting.disconnect();

	if (votingExperienceWidget)
	{
		delete votingExperienceWidget;
		votingExperienceWidget = NULL;
	}

	languageSelectionWidget->SetBackLanguage();
	connLanguage.disconnect();

	stepVoting = WAITING;

	if(MachineOperationManager::getInstance()->getAlarmController()->isGoToAuthentication())
	{
		logger->Debug("Alarm go to Authentication");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::blockMachine),100);
	}
	else
	{
		remove();

		viewWidget(waitingForCardWidget);

		startCheckCardPresent();
		startCheckBarcode();
	}
}

void MachineVotingWidget::readCardData()
{
	logger->Debug("Start read card data");

	if(!checkPrinter())
	{
		return;
	}

	VotingExperienceWidget::setSimulationMode(false);

	bool validate = false;

	try
	{
		validate = CardController::getInstance()->readCardData(currentCardData);
	}
	catch(...)
	{
		logger->Debug("Error read card data");
	}

	if (!validate)
	{
		if (SAESGUIConfigurationManager::Current()->getWaitingForCardWindowConfiguration().getBlockOnCardInsertionError())
		{
			setAlarm(AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA);
		}
		else
		{
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::cardNotProperlyInserted),100);
		}
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::validateCardData),100);
	}
}

void MachineVotingWidget::createCardData()
{
	logger->Debug("Create card data");

	simulateProcess = true;
	VotingExperienceWidget::setSimulationMode(true);

	simulationWidget->getCardData(currentCardData);

	validateCardData();
}

void MachineVotingWidget::validateCardData()
{
	logger->Debug("Validate card data");

	try
	{
		bool notCompletelyUsed = false;

		bool cond1 = (currentCardData.getCard_type() == VotingDevice::Card_type::CARD_DATA_OFFICIAL_VOTE_CARD) ||
				(currentCardData.getCard_type() == VotingDevice::Card_type::CARD_DATA_RECOVERY_VOTE_CARD) ||
				(currentCardData.getCard_type() == VotingDevice::Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD);

		bool cond2 = true;

		if(currentCardData.getCard_status() == VotingDevice::Card_status::CARD_DATA_USED)
		{
			if(currentCardDataCode == currentCardData.getActivation_code())
			{
				notCompletelyUsed = true;
				cond2 = true;
			}
			else
			{
				notCompletelyUsed = false;
				cond2 = false;
			}
		}

		cond2 |= !Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getMarkCardAsUsed ();

		currentCardDataCode = currentCardData.getActivation_code();

		if (cond1 && cond2)
		{
			logger->Debug("Check activation code.");
			std::string verifCode = currentCardData.getActivation_code ();
			std::string uncypheredDate = CardDataWrapper::GetUncypheredActivationCode(verifCode);

			if(uncypheredDate.compare("")!=0 && CardDataWrapper::checkIfCardTimeIsValid (uncypheredDate))
			{
				bool condition1 = (currentCardData.getCard_type() == Card_type::CARD_DATA_RECOVERY_VOTE_CARD) &&
						checkRecoveryCard();
				bool condition2 = currentCardData.getCard_type() != Card_type::CARD_DATA_RECOVERY_VOTE_CARD;

				bool condition3 = currentCardData.getCard_type() == Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD;

				if ( (condition1 ||  condition2) && (notCompletelyUsed || simulateProcess || markUsedCardData()))
				{
					VotingExperienceController * votingExperienceController;
					votingExperienceController = MachineOperationManager::getInstance()->getVotingExperienceController();

					if ( votingExperienceController->init(currentCardData) )
					{
						if (simulateVote && condition3)
						{
							logger->Debug("Demo Simulate");
							votingExperienceController->setVotingMode(VoteMode::VOTE_D);
						}
						else if(simulateVote && condition2)
						{
							logger->Debug("Any Simulate");
							votingExperienceController->setVotingMode(VoteMode::VOTE_S);
						}
						else if (condition1)
						{
							logger->Debug("Recovery Vote");
						}
						else
						{
							logger->Debug("Init Vote");
						}

						VotingOperation::refresh();

						Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::showSelectionLanguage), 10);
					}
					else
					{
						setAlarm(AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA);
					}
				}
				else
				{
					logger->Debug("ERROR - Problem write data card");
					setAlarm(AlarmEnum::CONFIGURATION_UNABLETOWRITE);
				}
			}
			else
			{
				logger->Debug("ERROR - Time of card has been expired");
				setAlarm(AlarmEnum::CONFIGURATION_CARDVALIDITYPERIODEXPIRED);
			}
		}
		else
		{
			currentCardDataCode = "";
			setAlarm(AlarmEnum::CONFIGURATION_CARDUSED);
		}
	}
	catch (...)
	{
		setAlarm(AlarmEnum::CONFIGURATION_INVALIDVOTINGDATA);
	}
}

void MachineVotingWidget::showSelectionLanguage()
{
	logger->Debug("Show selection language");

	if (languageSelectionWidget->ShowWidget())
	{
		stepVoting = SHOW_LANGUAGE;
		languageSelectionWidget->initialize();
		connLanguage.disconnect();
		connLanguage = languageSelectionWidget->getSignalEnd().connect(sigc::mem_fun(*this,&MachineVotingWidget::languageSelected));
		viewWidget(languageSelectionWidget);
	}
	else
	{
		languageSelected();
	}
}

void MachineVotingWidget::languageSelected()
{
	connLanguage.disconnect();
	logger->Debug("Language selected");
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::startVotingExperience), 10);
}

void MachineVotingWidget::setAlarm(AlarmEnum alarmType)
{
	AlarmMessage::alarm(alarmType);

	if(MachineOperationManager::getInstance()->getAlarmController()->isGoToAuthentication())
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::back), 100);
	}
	else
	{
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &MachineVotingWidget::refresh), 100);
	}
}

std::string MachineVotingWidget::getTitleText()
{
	return N_("Smartmatic.SAES.GUI.Widget.MachineVotingWidget.Title");
}

bool MachineVotingWidget::isTitle()
{
	return false;
}

void MachineVotingWidget::cardNotProperlyInserted()
{
	stepVoting = ERROR_VALIDATE;
	startCheckBarcode();
	waitingForCardWidget->viewErrorCardValidate();
}

void MachineVotingWidget::recievedData(Smartmatic::System::SafeBuffer * received)
{
	logger->Debug("Receive data");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pushObject(received);
}

void MachineVotingWidget::signalingPopDispatcher()
{
	logger->Debug("signaling pop dispatcher");

	stopCheckCardPresent();

	std::list <VoteResult *> list;
	std::list <VoteResult *>::iterator it;

	MachineOperationManager::getInstance()->getSaesEnqueuer()->getVoteResultList(list);

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		VoteResult * voteResult = (*it);

		switch(voteResult->getResult())
		{
			case MachineOperationManager::VOTE_FROM_BUFFER_SUCCESS:
				{
					Smartmatic::SAES::Voting::Vote::Vote * vote = voteResult->getVote();
					viewWidget(previewWidget);
					previewWidget->preview(*vote);
				}
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE:
			case MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR:
				viewWidget(previewWidget);
				previewWidget->error();
				break;
			}

		delete voteResult;
		voteResult = NULL;
	}

	previewWidget->refresh();
}


bool MachineVotingWidget::checkPrinter()
{
	bool ok = false, neop_state = false, is_neop_blocking = false;

	PrinterStatusNotifier::runPrintBlank();

	sleep(1);

	PrinterStatusNotifier printNotifier;
	PrinterStatusNotifier::PhysichalStateEnumType printerState;

	printerState = printNotifier.getPrinterState();

	std::stringstream ss;
	ss << "Printer state is: " << printerState;
	logger->Debug(ss.str());

	neop_state = ((printerState & PrinterStatusNotifier::PSTATE_NEAR_END_OF_PAPER) == PrinterStatusNotifier::PSTATE_NEAR_END_OF_PAPER);
	is_neop_blocking = SAESGUIConfigurationManager::Current ()->getWaitingForCardWindowConfiguration ().getIsNeopBlockingCondition ();

	if ( printerState & printNotifier.getErrorCondition() )
	{
		ok = false;
		setAlarm(AlarmEnum::CONFIGURATION_PRINTERNOTREADYFORVOTE);
	}
	else if ( is_neop_blocking )
	{
		ok = ! neop_state;

		if (!ok)
		{
			setAlarm(AlarmEnum::CONFIGURATION_PRINTERNEOPBEFOREVOTE);
		}
	}
	else
	{
		ok = true;
	}

	return ok;
}

bool MachineVotingWidget::checkRecoveryCard()
{
	bool success = false;

	try
	{
		Voting_device vd;
		vd = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
		VotingDevice::Logical_voter_group clvg = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getLogicalVoterGroup(vd,currentCardData.getLogical_voter_group ().getCode());
		success = true;
	}
	catch (System::Exception::VotingDeviceException & ex)
	{
		if(currentCardData.getLogical_voter_group ().getCode().compare(SAESConfigurationManager::Current()->getVoteDummyConfiguration ().getLogicalVoterGroupCode())==0 )
		{
			success = true;
		}
	}
	catch(...)
	{

	}

	return success;
}

bool MachineVotingWidget::markUsedCardData()
{
	bool validate = true;

	try
	{
		if(SAESGUIConfigurationManager::Current()->getMarkCardAsUsed ())
		{
			if(simulateVote)
			{
				currentCardData.setCard_status ( Card_status::CARD_DATA_SIMULATED );
			}
			else
			{
				currentCardData.setCard_status ( Card_status::CARD_DATA_USED );
			}

			if (!CardController::getInstance()->writeCardData(currentCardData))
			{
				logger->Debug("FATAL - check used card data");
				validate = false;
			}
		}
	}
	catch(...)
	{
		logger->Debug("FATAL - error write card data");
		validate = false;
	}

    return validate;
}

void MachineVotingWidget::back()
{
	stopCheckAlarmButton();
	stopCheckAlarmBoxEvent();
	stopCheckBarcode();
	stopCheckCardPresent();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this , &MachineVotingWidget::blockMachine), 100);
}

void MachineVotingWidget::alarmBoxDisconnect()
{
	setAlarm(AlarmEnum::CONFIGURATION_ALARMBOXDISCONNECTED);
}
