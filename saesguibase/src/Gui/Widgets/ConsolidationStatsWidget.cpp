/*
 * ConsolidationStatsWidget.cpp
 *
 *  Created on: Sep 6, 2011
 *      Author: Juan Delgado
 */

#include "ConsolidationStatsWidget.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Configuration/label-configuration.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <System/Sounds/smartmatic-sounds-manager.h>
#include "Devices/barcode-device.h"
#include "Configuration/label-configuration.h"
#include <System/Utils/StringUtils.hxx>
#include <Runtime/Environment/MemoryPathController.h>

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

using namespace Gtk;
using namespace std;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::System::Utils;
using namespace Smartmatic::SAES::Runtime::Environment;

Smartmatic::Log::ISMTTLog* ConsolidationStatsWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget",GETTEXT_PACKAGE);

ConsolidationStatsWidget::ConsolidationStatsWidget(CountConfiguration & totalCountType, CountConfiguration & officialCountType)
{
	this->totalCountType = totalCountType;
	this->officialCountType = officialCountType;
	this->infoScanVoteLabel = NULL;
	this->countRecievedData = 0;

	popUpWindow = NULL;
	barcodeConnectedImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barcode_connected_small.gif");
	barcodeNotConnectedImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/barcode_noConnected_small.gif");
	oneMemoryConnectedImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/one-memory-small.gif");
	twoMemoryConnectedImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/both-memory-small.gif");
	voteResult = NULL;

	static ActivationConsolidationFunctionalityConfiguration config =
			SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration();
	static LabelConfiguration titleLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTitleFontConfiguration());
	static LabelConfiguration statLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getStatsConsolidationFontConfiguration());
	static LabelConfiguration instructionLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getInstructionFontConfiguration());
	static LabelConfiguration devicesLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getDevicesLabelConfiguration());

	std::map < string, std::map < string, string > > statisticMap;

	std::map < string, string > insideStats;

	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowTotalVotes())
	{
		insideStats["1Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalVotes"] = _("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalVotes");
	}
	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowOfficialVotes())
	{
		insideStats["2Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalOfficialVotes"] = _("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalOfficialVotes");
	}
	if(SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowDuplicatesVotes())
	{
		insideStats["3Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalDuplicateVotes"] = _("Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalDuplicateVotes");
	}
	statisticMap[_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.StatisticTitle")] = insideStats;

	statsWidget = manage(new StatisticWidget(statisticMap));
	statsWidget->show();
	statsWidget->set_size_request(-1, config.getStatsConsolidationHeight());
	statsWidget->SetTitlesSizeRequest(310, config.getTitleHeight());
	statsWidget->SetTitlesLabelConfiguration(titleLabelConfiguration);
	statsWidget->SetStatsLabelConfiguration(statLabelConfiguration);
	statsWidget->SetValuesWidth(60);
	statsWidget->set_no_show_all();
	statsWidget->show();

	pack_start(*statsWidget, false, false);

	infoScanVoteLabel = manage(new Label());
	infoScanVoteLabel->show();
	infoScanVoteLabel->set_size_request(310, -1);
	LabelConfiguration::SetLabelConfiguration(infoScanVoteLabel, instructionLabelConfiguration);
	infoScanVoteLabel->set_line_wrap(true);
	infoScanVoteLabel->set_no_show_all();
	infoScanVoteLabel->set_visible(config.getShowScanMessage());

	pack_start(*infoScanVoteLabel);

	instructionLabel = manage(new Label());
	instructionLabel->show();
	instructionLabel->set_size_request(310, -1);
	LabelConfiguration::SetLabelConfiguration(instructionLabel, instructionLabelConfiguration);
	instructionLabel->set_line_wrap(true);
	instructionLabel->set_no_show_all();
	instructionLabel->set_visible(config.getShowBarcodeMessage());
	pack_start(*instructionLabel);

	vbox = manage(new VBox());
	vbox->show();
	pack_end(*vbox,false,false,10);

	HBox* hbox1 = manage(new HBox());
	hbox1->show();
	vbox->pack_start(*hbox1, false, false, 5);

	barcodeLabel = manage(new Label());
	barcodeLabel->show();
	barcodeLabel->set_size_request(230, -1);
	barcodeLabel->set_line_wrap();
	barcodeLabel->set_justify(JUSTIFY_CENTER);
	barcodeLabel->set_no_show_all();
	LabelConfiguration::SetLabelConfiguration(barcodeLabel, devicesLabelConfiguration);
	hbox1->pack_end(*barcodeLabel);

	barcodeImage = manage(new Image());
	barcodeImage->show();
	barcodeImage->set(barcodeConnectedImage);
	hbox1->pack_start(*barcodeImage, false, false, 5);

	HBox* hbox2 = manage(new HBox());
	hbox2->show();
	vbox->pack_start(*hbox2, false, false, 5);

	memoryLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.BothMemoryConnected")));
	memoryLabel->show();
	memoryLabel->set_size_request(230, -1);
	memoryLabel->set_line_wrap();
	memoryLabel->set_justify(JUSTIFY_CENTER);
	LabelConfiguration::SetLabelConfiguration(memoryLabel, devicesLabelConfiguration);
	hbox2->pack_end(*memoryLabel);

	memoryImage = manage(new Image());
	memoryImage->show();
	memoryImage->set(twoMemoryConnectedImage);
	hbox2->pack_start(*memoryImage, false, false, 5);

	show();

	showPopUpMessage = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getVisible();
	enabledPopupChangeColor = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getEnabledChangeColor();

	if (showPopUpMessage)
	{
		Smartmatic::GUI::Configuration::LabelConfiguration labelConf = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetScanMessageLabelConfiguration();

		int timeout = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getTimeOut();
		int opacity = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getOpacity();
		int width = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getWidth();
		int height = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getHeight();

		ColorConfiguration fontVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getFontColorValid();
		ColorConfiguration fontBadVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getFontColorBad();
		ColorConfiguration fontDuplicateVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getFontColorDuplicate();
		ColorConfiguration boxVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getBoxColorValid();
		ColorConfiguration boxBadVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getBoxColorBad();
		ColorConfiguration boxDuplicateVote = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getBoxColorDuplicate();

		scanFontVoteColor.set_rgb(fontVote.getRed(), fontVote.getGreen(), fontVote.getBlue());
		scanFontBadVoteColor.set_rgb(fontBadVote.getRed(), fontBadVote.getGreen(), fontBadVote.getBlue());
		scanFontDuplicateVoteColor.set_rgb(fontDuplicateVote.getRed(), fontDuplicateVote.getGreen(), fontDuplicateVote.getBlue());

		scanBoxVoteColor.set_rgb(boxVote.getRed(), boxVote.getGreen(), boxVote.getBlue());
		scanBoxBadVoteColor.set_rgb(boxBadVote.getRed(), boxBadVote.getGreen(), boxBadVote.getBlue());
		scanBoxDuplicateVoteColor.set_rgb(boxDuplicateVote.getRed(), boxDuplicateVote.getGreen(), boxDuplicateVote.getBlue());

		PositionConfiguration position = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getPosition();

		popUpWindow = new PopUpMessageWindow(" ", labelConf, timeout, opacity);
		popUpWindow->set_name("scan_popup_window");

		if (position == PositionConfiguration::CONFIGURATION_CUSTOM)
		{
			int x = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getX();
			int y = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getY();

			popUpWindow->setPosition(x, y);
		}
		if (position != PositionConfiguration::CONFIGURATION_FULL_SCREEN)
		{
			popUpWindow->set_default_size(width, height);
			popUpWindow->set_size_request(width, height);
		}

		switch(position)
		{
			case PositionConfiguration::CONFIGURATION_TOP_RIGHT:
				popUpWindow->setPosition(BasicWindow::TOP_RIGHT);
				break;
			case PositionConfiguration::CONFIGURATION_TOP_LEFT:
				popUpWindow->setPosition(BasicWindow::TOP_LEFT);
				break;
			case PositionConfiguration::CONFIGURATION_TOP_CENTER:
				popUpWindow->setPosition(BasicWindow::TOP_CENTER);
				break;
			case PositionConfiguration::CONFIGURATION_CENTER_RIGHT:
				popUpWindow->setPosition(BasicWindow::CENTER_RIGHT);
				break;
			case PositionConfiguration::CONFIGURATION_CENTER_LEFT:
				popUpWindow->setPosition(BasicWindow::CENTER_LEFT);
				break;
			case PositionConfiguration::CONFIGURATION_CENTER_CENTER:
				popUpWindow->setPosition(BasicWindow::CENTER_CENTER);
				break;
			case PositionConfiguration::CONFIGURATION_BOTTOM_RIGHT:
				popUpWindow->setPosition(BasicWindow::BOTTOM_RIGHT);
				break;
			case PositionConfiguration::CONFIGURATION_BOTTOM_LEFT:
				popUpWindow->setPosition(BasicWindow::BOTTOM_LEFT);
				break;
			case PositionConfiguration::CONFIGURATION_BOTTOM_CENTER:
				popUpWindow->setPosition(BasicWindow::BOTTOM_CENTER);
				break;
			default:
				break;
		}

	}

	voteWrapper = MachineOperationManager::getInstance()->getVoteStatistics();

	commandsInBarcode = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getBarcodeInParams();
	commandsOutBarcode = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getBarcodeOutParams();
	consolidateVoteWithOneMemory = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getConsolidateVoteWithOneMemory();
}

ConsolidationStatsWidget::~ConsolidationStatsWidget()
{
	showPopUpMessage = false;

	if(!disposeExecuted)
	{
		barcodeConnected = false;
		Dispose();
	}

	if (popUpWindow)
	{
		delete popUpWindow;
		popUpWindow = NULL;
	}
}

void ConsolidationStatsWidget::Initialize()
{
	disposeExecuted = false;
	sendingCommands = false;

	showPopUpMessage = SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getScanConsolidationConfiguration().getScanPopUpMessageConfiguration().getVisible();
	barcodeConnected = BarcodeDevice::Current()->Resync();

	oneMemory = false;

	if(barcodeConnected)
	{
		BarcodeDevice::Current()->SendConfigurationCommands(commandsInBarcode,false,false);
	}

	UpdateBarcodePresence();
	UpdateMemoryPresence();

	UpdateInstructionLabel();
	UpdateStats();
	ConnectSignals();
}

void ConsolidationStatsWidget::ConnectSignals()
{
	if(!conn_barcodeReceivedData.connected())
	{
		conn_barcodeReceivedData = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::ReceivedData));
	}
	if(!conn_barcodeConnected.connected())
	{
		conn_barcodeConnected = BarcodeDevice::Current()->signalConnected().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::BarcodeConnected));
	}
	if(!conn_barcodeDisconnected.connected())
	{
		conn_barcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::BarcodeDisconnected));
	}
	if(!conn_saesEnqueuerDispatcher.connected())
	{
		conn_saesEnqueuerDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::SignalSaesEnqueuerDispatch));
	}

	MachineOperationManager::getInstance()->getSaesEnqueuer()->flush();
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();
}

void ConsolidationStatsWidget::DisconnectSignals()
{
	conn_barcodeReceivedData.disconnect();
	conn_barcodeConnected.disconnect();
	conn_barcodeDisconnected.disconnect();
	conn_updateLabelInstruction.disconnect();
	conn_saesEnqueuerDispatcher.disconnect();
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();
	MachineOperationManager::getInstance()->getSaesEnqueuer()->flush();
}

bool ConsolidationStatsWidget::UpdateInstructionLabel()
{
	if(!oneMemory && barcodeConnected)
	{
		instructionLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionBarcodeBothMemory"));
		infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.WaitScanVoteBarcodeBothMemory"));
	}
	else if(oneMemory && barcodeConnected)
	{
		instructionLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionBarcodeOneMemory"));
		infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.WaitScanVoteBarcodeOneMemory"));
	}
	else if(oneMemory && !barcodeConnected)
	{
		instructionLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionNoBarcodeOneMemory"));
		infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.WaitScanVoteNoBarcodeOneMemory"));
	}
	else
	{
		instructionLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionNoBarcodeBothMemory"));
		infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.WaitScanVoteNoBarcodeBothMemory"));
	}

	return false;
}

void ConsolidationStatsWidget::BarcodeConnected()
{
	countRecievedData = 0;

	stopOperationAfterSend = false;

	if(BarcodeDevice::Current()->Resync())
	{
		sendingCommands = true;
		conn_barcodeCommandsSend.disconnect();
		conn_barcodeCommandsSend = BarcodeDevice::Current()->signalCommandsSent().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::BarcodeCommandsSent));
		BarcodeDevice::Current()->SendConfigurationCommands("baseconfiguration",true,false);
	}
	else
	{
		BarcodeCommandsSent(false);
	}
}

void ConsolidationStatsWidget::BarcodeCommandsSent(bool commandsOk)
{
	sendingCommands = false;

	m_signal_sendCommands.emit(commandsOk);

	if(commandsOk)
	{
		logger->Debug("Send barcode command ok");

		barcodeConnected = true;

		UpdateBarcodePresence();

		vbox->show();

		if (SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowBarcodeMessage())
		{
			instructionLabel->show();
		}
		if (SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowScanMessage())
		{
			infoScanVoteLabel->show();
		}

		statsWidget->show();

		UpdateInstructionLabel();
		UpdateStats();

		if(stopOperationAfterSend)
		{
			stopOperationAfterSend = false;
			StopOperation();
		}
	}
	else
	{
		logger->Debug("Send barcode command error");

		BarcodeDevice::Current()->Close();
		BarcodeDisconnected();
	}

	conn_barcodeCommandsSend.disconnect();
}

void ConsolidationStatsWidget::ShowNormalState()
{
	m_signal_sendCommands.emit(true);

	vbox->show();
	if (SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowBarcodeMessage())
	{
		instructionLabel->show();
	}
	if (SAESGUIConfigurationManager::Current()->GetActivationConsolidationFunctionalityConfiguration().getShowScanMessage())
	{
		infoScanVoteLabel->show();
	}
	statsWidget->show();

	//ConnectSignals();
}

void ConsolidationStatsWidget::BarcodeDisconnected()
{
	countRecievedData = 0;
	barcodeConnected = false;

	UpdateBarcodePresence();
	UpdateInstructionLabel();

	Glib::signal_timeout().connect_once(sigc::mem_fun(*this,&ConsolidationStatsWidget::ShowNormalState), 3000);
}

void ConsolidationStatsWidget::Dispose()
{
	Glib::Mutex::Lock lock(mutex);

	disposeExecuted = true;
	showPopUpMessage = false;

	DisconnectSignals();

	conn_barcodeCommandsSend.disconnect();

	if(barcodeConnected)
	{
		BarcodeDevice::Current()->SendConfigurationCommands(commandsOutBarcode, false,true);
	}
}

void ConsolidationStatsWidget::SignalSaesEnqueuerDispatch()
{
	Glib::Mutex::Lock lock(mutex);

	std::list <VoteResult *> list;
	std::list <VoteResult *>::iterator it;

	MachineOperationManager::getInstance()->getSaesEnqueuer()->getVoteResultList(list);

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		VoteResult * voteResult = (*it);
		Vote * vote = voteResult->getVote();

		switch(voteResult->getResult())
		{
			case MachineOperationManager::VOTE_FROM_BUFFER_SUCCESS:
				ProccesVote(*vote);
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE:
			case MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR:

				flagStateVote = BAD;
				infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionBadProccesedVote"));

				conn_updateLabelInstruction.disconnect();
				conn_updateLabelInstruction = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::UpdateInstructionLabel), 5000);

				Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound("ScanBadVoteSound");

				showPopUp();

				break;
		}

		delete voteResult;
		voteResult = NULL;
	}
}

void ConsolidationStatsWidget::showPopUp()
{
	if (showPopUpMessage && popUpWindow)
	{
		popUpWindow->refreshText(infoScanVoteLabel->get_text());

		if (enabledPopupChangeColor)
		{
			switch(flagStateVote)
			{
				case GOOD:
					popUpWindow->setFontColorLabel(scanFontVoteColor);
					popUpWindow->setBoxColorLabel(scanBoxVoteColor);
					break;
				case DUPLICATE:
					popUpWindow->setFontColorLabel(scanFontDuplicateVoteColor);
					popUpWindow->setBoxColorLabel(scanBoxDuplicateVoteColor);
					break;
				case BAD:
					popUpWindow->setFontColorLabel(scanFontBadVoteColor);
					popUpWindow->setBoxColorLabel(scanBoxBadVoteColor);
					break;
			}
		}

		if (!popUpWindow->is_visible())
		{
			Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &ConsolidationStatsWidget::ShowMessageWindow), 10);
		}
	}
}

void ConsolidationStatsWidget::ProccesVote(Vote& vote)
{
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.StartingProcessVote"));

	static bool proccesDemoVote =
			SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidateDemoVotes();

	if(vote.getMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D && !proccesDemoVote)
	{
		logger->Debug("Not Process Vote Demo");
		return;
	}

	static bool proccesSimulatedVote =
			SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidateSimulatedVotes();

	if(vote.getMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S && !proccesSimulatedVote)
	{
		logger->Debug("Not Process Vote Simulated");
		return;
	}

	bool success = false;
	bool isVoteProcessed = false;

    try
    {
    	isVoteProcessed = voteWrapper->IsVoteProcessed(vote);
    	success = MachineOperationManager::getInstance()->persistenceVote(vote);
    }
    catch (...)
    {
    	success = false;
    }

    if (success)
	{

        if(!isVoteProcessed)
		{
			Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound("ScanNormalVoteSound");
			infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionGoodProccesedVote"));
			flagStateVote = GOOD;
		}
		else
		{
			Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound("ScanDuplicatedVoteSound");
			infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionDuplicatedProccesedVote"));
			flagStateVote = DUPLICATE;
		}

    	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.VoteSaved"));
    	UpdateStats();
	}
    else
    {
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound("ScanBadVoteSound");
		infoScanVoteLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.InstructionErrorProccesedVote"));
		flagStateVote = BAD;
    }

	conn_updateLabelInstruction.disconnect();
	conn_updateLabelInstruction = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::UpdateInstructionLabel), 5000);

	showPopUp();
}

void ConsolidationStatsWidget::ShowMessageWindow()
{
	if (showPopUpMessage && popUpWindow)
	{
		popUpWindow->show();
	}
}

std::string ConsolidationStatsWidget::getValue(CountConfiguration::CountTypeSequence & seq)
{
	CountConfiguration::CountTypeIterator it;
	int total = 0;

	for (it = seq.begin();
		 it != seq.end();
		 it++)
	{
		switch (*it)
		{
			case CountTypeConfig::CONFIGURATION_TOTAL:
				total += voteWrapper->getTotalVotes();
				break;
			case CountTypeConfig::CONFIGURATION_OFFICIAL:
				total += voteWrapper->getOfficialVotes();
				break;
			case CountTypeConfig::CONFIGURATION_DEMO:
				total += voteWrapper->getDemoVotes();
				break;
			case CountTypeConfig::CONFIGURATION_RECOVERY:
				total += voteWrapper->getSecurityCopyVotes();
				break;
			case CountTypeConfig::CONFIGURATION_SIMULATE:
				total += voteWrapper->getSimulatedVotes();
				break;
		}
	}

	return StringUtils::intToString(total);
}

void ConsolidationStatsWidget::UpdateStats()
{
	std::string total = getValue(totalCountType.getCountType());
	std::string official = getValue(officialCountType.getCountType());

	statsWidget->SetValue("1Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalVotes", total);
	statsWidget->SetValue("2Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalOfficialVotes", official);
	statsWidget->SetValue("3Smartmatic.SAES.GUI.Widgets.Voting.VoteStatisticsWidget.TotalDuplicateVotes", StringUtils::intToString(voteWrapper->getDuplicatedVotes()));
}

void ConsolidationStatsWidget::ReceivedData(Smartmatic::System::SafeBuffer* received)
{
	{
		std::stringstream ss;
		ss << "Fase # 3 : Get signal barcode data - size : " << received->GetSize() << " - count data : " << ++countRecievedData;
		logger->Debug(ss.str());
	}

	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound("BarcodeDataReceivedVoteSound");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pushObject(received);
}

void ConsolidationStatsWidget::SetOneMemoryMode(bool oneMemory)
{
	this->oneMemory = oneMemory;

	UpdateMemoryPresence();

	UpdateInstructionLabel();

	if(oneMemory)
	{
		if(consolidateVoteWithOneMemory)
		{
			try
			{
				MachineOperationManager::getInstance()->saveVoteInOneMemory();
			}
			catch(...)
			{
				//TODO handle exception
			}
		}
		else
		{
			instructionLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.ConnectMemoryToConsolidate"));
		}
	}
}

void ConsolidationStatsWidget::ContinueOperation()
{
	stopOperationAfterSend = false;

	if((!oneMemory || consolidateVoteWithOneMemory) && !sendingCommands)
	{
		if(!conn_saesEnqueuerDispatcher.connected())
		{
			conn_saesEnqueuerDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &ConsolidationStatsWidget::SignalSaesEnqueuerDispatch));
		}

		MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();

		if(barcodeConnected)
		{
			BarcodeDevice::Current()->SendConfigurationCommands(commandsInBarcode,false,false);
		}
	}

	countRecievedData = 0;
}

void ConsolidationStatsWidget::StopOperation()
{
	if(!sendingCommands)
	{
		conn_saesEnqueuerDispatcher.disconnect();
		MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();

		if(barcodeConnected)
		{
			BarcodeDevice::Current()->SendConfigurationCommands(commandsOutBarcode,false,false);
		}

		stopOperationAfterSend = false;
	}
	else
	{
		stopOperationAfterSend = true;
	}

	countRecievedData = 0;
}

void ConsolidationStatsWidget::pauseOperation()
{
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pauseProcess();
}

void ConsolidationStatsWidget::resumeOperation()
{
	MachineOperationManager::getInstance()->getSaesEnqueuer()->resumeProcess();
}

ConsolidationStatsWidget::signal_void_bool ConsolidationStatsWidget::barcode_SendCommands()
{
	return m_signal_sendCommands;
}

void ConsolidationStatsWidget::UpdateMemoryPresence()
{
	if(!MemoryPathController::getInstance()->isAllDevices())
	{
		memoryLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.OneMemoryConnected"));
		memoryImage->set(oneMemoryConnectedImage);
	}
	else
	{
		memoryLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.BothMemoryConnected"));
		memoryImage->set(twoMemoryConnectedImage);
	}
}

void ConsolidationStatsWidget::UpdateBarcodePresence()
{
	if(BarcodeDevice::Current()->sendPing())
	{
		barcodeLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.BarcodeConnected"));
		barcodeImage->set(barcodeConnectedImage);
	}
	else
	{
		barcodeLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.ConsolidationStatsWidget.BarcodeNotConnected"));
		barcodeImage->set(barcodeNotConnectedImage);
	}
}
