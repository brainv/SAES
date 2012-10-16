/**
 * @file vote-consolidation-functionality.cc
 * @brief Body class vote consolidation functionality
 */

/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Log/SMTTLogManager.h>
#include "vote-consolidation-functionality.h"
#include <Voting/operation-status.h>
#include "Devices/barcode-device.h"
#include <Operation/MachineOperationManager.hxx>
#include <Voting/ElectoralConfiguration.hxx>
#include <Environment/Configurations/resource-path-provider.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Functionalities/time-functionality.h>
#include <Configuration/smartmatic-conf-manager.h>
#include <System/Sounds/smartmatic-sounds-manager.h>
#include "Gui/Widgets/AbstractFactoryWidget.hxx"
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

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::HW::Commands;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Configuration;

VoteConsolidationFunctionality* VoteConsolidationFunctionality::current_instance = NULL;
Smartmatic::Log::ISMTTLog* VoteConsolidationFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality",GETTEXT_PACKAGE);

VoteConsolidationFunctionality::VoteConsolidationFunctionality()
:GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	votePrint = NULL;
	printPreviewWidget = NULL;
	printPreviewAlign = NULL;
	scrolledMagnify = NULL;
	viewMagnify = NULL;
	partyViewerWidget = NULL;
	barcodeDetectionWidget = NULL;
	outsideBox = NULL;

	labelTemp = NULL;
	widgetPreviewFrame = NULL;
	previewBox = NULL;
	previewAligment = NULL;
	previewButtonHBox = NULL;
	activatePreviewBoxButton = NULL;
	previewBoxMessage = NULL;
	buttonFixedMessage = NULL;
	postButtonFixedMessage = NULL;
	previewButtonEventBox = NULL;
	normalFrameWidget = NULL;
	voteStatsWidget = NULL;

	scanNormal = "ScanNormalVoteSound";
	scanDuplicated = "ScanDuplicatedVoteSound";
	scanBad = "ScanBadVoteSound";
	scanReceivedData = "BarcodeDataReceivedVoteSound";

	isAudit = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getAuditModeResources();
	thereIsAVote = false;
}

VoteConsolidationFunctionality::~VoteConsolidationFunctionality()
{
	deleteElement();
}

VoteConsolidationFunctionality* VoteConsolidationFunctionality::Current()
{
	if (!current_instance)
		current_instance = new VoteConsolidationFunctionality();

	return current_instance;
};

void VoteConsolidationFunctionality::deleteElement()
{
	if(votePrint)
	{
		delete votePrint;
		votePrint = NULL;
	}
	if(printPreviewWidget)
	{
		delete printPreviewWidget;
		printPreviewWidget = NULL;
	}
	if(printPreviewAlign)
	{
		delete printPreviewAlign;
		printPreviewAlign = NULL;
	}
	if(scrolledMagnify)
	{
		delete scrolledMagnify;
		scrolledMagnify = NULL;
	}
	if(viewMagnify)
	{
		delete viewMagnify;
		viewMagnify = NULL;
	}
	if(partyViewerWidget)
	{
		delete partyViewerWidget;
		partyViewerWidget = NULL;
	}
	if(barcodeDetectionWidget)
	{
		delete barcodeDetectionWidget;
		barcodeDetectionWidget = NULL;
	}
	if(outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
	if(labelTemp)
	{
		delete labelTemp;
		labelTemp = NULL;
	}
	if(widgetPreviewFrame)
	{
		delete widgetPreviewFrame;
		widgetPreviewFrame = NULL;
	}
	if(previewBox)
	{
		delete previewBox;
		previewBox = NULL;
	}
	if(previewAligment)
	{
		delete previewAligment;
		previewAligment = NULL;
	}
	if(previewButtonHBox)
	{
		delete previewButtonHBox;
		previewButtonHBox = NULL;
	}
	if(activatePreviewBoxButton)
	{
		delete activatePreviewBoxButton;
		activatePreviewBoxButton = NULL;
	}
	if(previewBoxMessage)
	{
		delete previewBoxMessage;
		previewBoxMessage = NULL;
	}
	if(buttonFixedMessage)
	{
		delete buttonFixedMessage;
		buttonFixedMessage = NULL;
	}
	if(postButtonFixedMessage)
	{
		delete postButtonFixedMessage;
		postButtonFixedMessage = NULL;
	}
	if(previewButtonEventBox)
	{
		delete previewButtonEventBox;
		previewButtonEventBox = NULL;
	}
	if(normalFrameWidget)
	{
		delete normalFrameWidget;
		normalFrameWidget = NULL;
	}
	if(voteStatsWidget)
	{
		delete voteStatsWidget;
		voteStatsWidget = NULL;
	}
}

void VoteConsolidationFunctionality::signalingPopDispatcher()
{
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
				thereIsAVote = true;
				vote = (*(voteResult->getVote()));
				ProccesVote();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE:
			case MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR:

				thereIsAVote = false;
				Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(scanBad);

				if(isAudit)
				{
					RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.BadProcessedVote.Audit"));

					signalRefreshLabel = Glib::signal_timeout().connect(sigc::bind<string>(sigc::mem_fun(*this, &VoteConsolidationFunctionality::RefreshLabelText),
							_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote.Audit")), 2000);
				}
				else
				{
					RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.BadProcessedVote"));

					signalRefreshLabel = Glib::signal_timeout().connect(sigc::bind<string>(sigc::mem_fun(*this, &VoteConsolidationFunctionality::RefreshLabelText),
							_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote")), 2000);
				}

				break;
		}

		delete voteResult;
		voteResult = NULL;
	}
}

void VoteConsolidationFunctionality::ReceivedData(Smartmatic::System::SafeBuffer * received)
{
	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(scanReceivedData);
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pushObject(received);
}

void VoteConsolidationFunctionality::CreatePartyViewerWidget()
{
	bool tableVertical = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getUseVerticalTableInPreview();

	if(partyViewerWidget) delete partyViewerWidget;
	partyViewerWidget = new PartyContestViewerWidget(vote, tableVertical);

	widgetPreviewFrame->remove();
	widgetPreviewFrame->add(*partyViewerWidget);
	widgetPreviewFrame->show_all_children();
}

void VoteConsolidationFunctionality::CreateVotePrintDocument()
{
	bool showBarcode = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getShowBarcodeInPreview();

	if(votePrint) delete votePrint;
	votePrint = new VotePrintDocument(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),vote,true, showBarcode);

	CreatePrintPreview();
}

void VoteConsolidationFunctionality::CreatePrintPreview()
{
	viewMagnify->remove();

	if(printPreviewWidget) delete printPreviewWidget;
	printPreviewWidget = new PrintPreviewWidget(votePrint);

	ShowPrintPreview();
}

void VoteConsolidationFunctionality::ShowPrintPreview()
{
	LoadGTKBuilder();
	
	viewMagnify->add(*printPreviewWidget);

	scrolledMagnify->set_size_request(380, 500);

	if(printPreviewAlign) delete(printPreviewAlign);
	printPreviewAlign = new Alignment();
	
	printPreviewAlign->set(0.5, 0.5, 0, 0);
	printPreviewAlign->add(*scrolledMagnify);
	
	widgetPreviewFrame->remove();                                    
	widgetPreviewFrame->add(*printPreviewAlign);
	widgetPreviewFrame->show_all_children();
}

void VoteConsolidationFunctionality::SaveVote()
{
	bool success = false;

    try
    {
        success = MachineOperationManager::getInstance()->persistenceVote(vote);
    }
    catch (...)
    {
    	success = false;
	}

    if (!success)
    {
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(scanBad);

		if(isAudit)
		{
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ErrorSaveVote.Audit"));

			signalRefreshLabel = Glib::signal_timeout().connect(sigc::bind<string>(sigc::mem_fun(*this, &VoteConsolidationFunctionality::RefreshLabelText),
					_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote")), 2000);
		}
		else
		{
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ErrorSaveVote"));

			signalRefreshLabel = Glib::signal_timeout().connect(sigc::bind<string>(sigc::mem_fun(*this, &VoteConsolidationFunctionality::RefreshLabelText),
					_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote")), 2000);
		}
    }
}

void VoteConsolidationFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.FinalMessage"));

	previewIsActivated = false;
	thereIsAVote = false;

	//if(!BarcodeDevice::Current()->sendPing())
		//BarcodeDevice::Current()->Resync();

	connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::ReceivedData));
	//processingData = false;

	if(isAudit)
	{
		RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote.Audit"));
	}
	else
	{
		RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote"));
	}
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();
	UpdateStats();
	signalPopDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::signalingPopDispatcher));

	//connBarcodeConnected = BarcodeDevice::Current()->signalConnected.connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::reconnectedBarcode));
	connBarcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::BarcodeDisconnected));

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();

	signalStartSendCommand = BarcodeDevice::Current()->getSignalStartSendCommand().connect(sigc::mem_fun(*this , &VoteConsolidationFunctionality::disableExitButton));
	signalEndSendCommand = BarcodeDevice::Current()->getSignalEndSendCommand().connect(sigc::mem_fun(*this , &VoteConsolidationFunctionality::enableExitButton));

	string barcodeInParams = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getBarcodeInParams();

	if(BarcodeDevice::Current()->sendPing() && !barcodeInParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeInParams, false, false);
	}
	else
	{
		enableExitButton();
	}
}

void VoteConsolidationFunctionality::BarcodeDisconnected()
{
	enableExitButton();

	barcodeDetectionWidget->SetDefault();

	if(normalFrameWidget->get_parent())
	{
		outsideBox->remove(*normalFrameWidget);
		outsideBox->add(*barcodeDetectionWidget);
		outsideBox->show_all_children();
	}
}

void VoteConsolidationFunctionality::LoadGTKBuilder()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/vote-consolidation-functionality.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	builder->get_widget("scrolledwindowMagnify", scrolledMagnify);
	builder->get_widget("viewportMagnify", viewMagnify);

}

void VoteConsolidationFunctionality::CreateNormalFrame()
{
	LoadGTKBuilder();

	Smartmatic::SAES::Voting::ElectoralConfiguration* elecConf = MachineOperationManager::getInstance()->getElectoralConfiguration();
	VotingDeviceWrapper* votingDeviceWrapper = elecConf->getVotingDevice();
	Voting_device vd = votingDeviceWrapper->getFirstVotingDevice();
	Logical_voter_groups lvgs = votingDeviceWrapper->getLogicalVoterGroups(vd);

	voteStats = MachineOperationManager::getInstance()->getVoteStatistics();

	if(isAudit)
	{
		labelTemp = new Label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote.Audit"));
	}
	else
	{
		labelTemp = new Label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.WaitingVote"));
	}

	Pango::FontDescription fontTitle = labelTemp->get_style()->get_font();
	fontTitle.set_size(16*Pango::SCALE);
	labelTemp->modify_font(fontTitle);

	widgetPreviewFrame = new Frame();
	widgetPreviewFrame->add(*labelTemp);
	widgetPreviewFrame->set_shadow_type(SHADOW_NONE);

	previewAligment = new Gtk::Alignment(1.0, 0.5, 1.0, 1.0);
	previewBox = new Gtk::VBox();
	previewButtonHBox = new Gtk::HBox();
	activatePreviewBoxButton = new Smartmatic::GUI::Widgets::SmartmaticButton();
	previewBoxMessage = new Gtk::Label();
	previewBoxMessage->modify_font(fontTitle);

	if(isAudit)
	{
		previewBoxMessage->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFFMessage.Audit"));
	}
	else
	{
		previewBoxMessage->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFFMessage"));
	}

	previewAligment->set_padding(10, 10 , 0, 0);
	activatePreviewBoxButton->set_size_request(130, 60);

	if(isAudit)
	{
		activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFF.Audit"));
	}
	else
	{
		activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFF"));
	}

	activatePreviewBoxButton->signal_clicked ().connect(sigc::mem_fun(*this,&VoteConsolidationFunctionality::on_buttonActivatePreview_clicked));

	buttonFixedMessage = new Gtk::Fixed();
	postButtonFixedMessage = new Gtk::Fixed();

	previewButtonHBox->add(*buttonFixedMessage);
	previewButtonHBox->add(*activatePreviewBoxButton);
	previewButtonHBox->add(*postButtonFixedMessage);

	previewButtonEventBox = new EventBox();
	previewButtonEventBox->set_name("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.EventBox");

	previewButtonEventBox->add(*previewButtonHBox);

	previewAligment->add(*previewButtonEventBox);
	previewBox->pack_start(*widgetPreviewFrame, true, true, 0);
	previewBox->pack_end(*previewAligment, false, false, 0);

	HBox * normalHBox = new HBox();

	if (lvgs.getCustom_attribute_definitions() != NULL)
	{
		Custom_attribute_definitions caDefs = lvgs.getCustom_attribute_definitions().get();
		CountConfiguration totalCountType = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidationTotalCountConfiguration();
		CountConfiguration officialCountType = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidationOfficialCountConfiguration();
		voteStatsWidget = new VoteStatisticsWidget(voteStats, caDefs, totalCountType, officialCountType);
		voteStatsWidget->SetSensitive(false);
		normalHBox->pack_start(*voteStatsWidget, false, false);
	}
	else
	{
		logger->Debug("ERROR - Custom attribute definitions not found.");
	}

	normalHBox->pack_start(*previewBox);
	normalHBox->show_all_children();

	normalFrameWidget = normalHBox;
}

Gtk::Widget* VoteConsolidationFunctionality::GetFrame()
{
	CreateNormalFrame();

	outsideBox = new HBox();
	barcodeDetectionWidget = AbstractFactoryWidget::createBarcodeDetectionWidget();
	barcodeDetectionWidget->ConnectSignals();

	if(barcodeDetectionWidget->CheckBarcodeConnected() || true)
	{
		outsideBox->add(*normalFrameWidget);
	}
	else
	{
		outsideBox->add(*barcodeDetectionWidget);
	}

	barcodeDetectionWidget->signal_barcode_connected().connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::on_barcode_connected));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::setExitButtonSensitive));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &VoteConsolidationFunctionality::setHelpButtonSensitive));

	outsideBox->show_all_children();

	return outsideBox;
};

void VoteConsolidationFunctionality::on_barcode_connected(bool isConnected)
{
	if(isConnected && barcodeDetectionWidget->get_parent())
	{
		outsideBox->remove(*barcodeDetectionWidget);
		outsideBox->add(*normalFrameWidget);
		outsideBox->show_all_children();
	}
}

void VoteConsolidationFunctionality::on_buttonActivatePreview_clicked()
{
	if(thereIsAVote)
	{
		if(previewIsActivated)
		{
			widgetPreviewFrame->remove();
			viewMagnify->remove();
			if(printPreviewWidget) delete printPreviewWidget;
			printPreviewWidget = NULL;
		}
		else
		{
			refresh();
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VotePreviewShowed"));
			//thereIsAVote = false;
		}
	}

	if(previewIsActivated)
	{
		if(isAudit)
		{
			activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFF.Audit"));
		}
		else
		{
			activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewOFF"));
		}
		previewIsActivated = false;
	}
	else
	{
		if(isAudit)
		{
			activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewON.Audit"));
		}
		else
		{
			activatePreviewBoxButton->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ActivatePreviewON"));
		}
		previewIsActivated = true;
	}
}

void VoteConsolidationFunctionality::ProccesVote()
{
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.StartingProcessVote"));

	logger->Debug("Vote code is:" + vote.getCode());

	bool proccesDemoVote = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidateDemoVotes();

	if(vote.getMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D &&
			!proccesDemoVote)
	{
		logger->Debug("Not Process Vote Demo.");
		thereIsAVote = false;
		return;
	}

	bool proccesSimulatedVote = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getConsolidateSimulatedVotes();

	if(vote.getMode() == Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S && !proccesSimulatedVote)
	{
		logger->Debug("Not Process Vote Simulated");
		return;
	}

	if(!voteStats->IsVoteProcessed(vote))
	{
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(scanNormal);

		thereIsAVote = true;

		if(isAudit)
		{
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ProcessingVote.Audit"));
		}
		else
		{
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ProcessingVote"));
		}

		if(previewIsActivated)
		{
			refresh();
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VotePreviewShowed"));
		}

		SaveVote();
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VoteSaved"));
	}
	else
	{
		Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(scanDuplicated);

		if(isAudit)
		{
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VoteAlreadyProcessed.Audit"));

			if(previewIsActivated)
			{
				refresh();
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VotePreviewShowed.Audit"));
			}

		}
		else
		{
			thereIsAVote = false;
			RefreshLabelText(_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.VoteAlreadyProcessed"));
		}

		SaveVote();
	}

	UpdateStats();
}

bool VoteConsolidationFunctionality::RefreshLabelText(string text)
{
	widgetPreviewFrame->remove();
	widgetPreviewFrame->add(*labelTemp);
	labelTemp->set_text(text);

	return false;
}

void VoteConsolidationFunctionality::UpdateStats()
{
	voteStatsWidget->RefreshStats();
}

string VoteConsolidationFunctionality::GetWindowTitle()
{
	if(isAudit)
	{
		return N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ConsolidateVotes.Audit");
	}
	else
	{
		return N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.ConsolidateVotes");
	}
};

Smartmatic::Functionality::MenuOptionDescriptor VoteConsolidationFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MVoteConsolidationFunctionality,false);
};	

void VoteConsolidationFunctionality::Dispose()
{
	signalRefreshLabel.disconnect();
	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();

	connReceived.disconnect();
	signalPopDispatcher.disconnect();
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();
	connBarcodeDisconnected.disconnect();

	string barcodeOutParams = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getBarcodeOutParams();
	if(BarcodeDevice::Current()->sendPing() && !barcodeOutParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeOutParams, false, true);
	}
	else
	{
		BarcodeDevice::Current()->Close();
	}
};

Smartmatic::Log::ISMTTLog* VoteConsolidationFunctionality::getLogger()
{
	return logger;
}

Glib::ustring VoteConsolidationFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.LogStartFunctionality");
}

Glib::ustring VoteConsolidationFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VoteConsolidationFunctionality.LogCloseFunctionality");
}	

void VoteConsolidationFunctionality::block()
{
	logger->Debug("Block functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pauseProcess();
}

void VoteConsolidationFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void VoteConsolidationFunctionality::resume()
{
	logger->Debug("Resume functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->resumeProcess();
}

void VoteConsolidationFunctionality::refresh()
{
	Glib::Mutex::Lock lock(mutex);

	if (!thereIsAVote)
	{
		return;
	}

	bool showVotePrintPreview = SAESGUIConfigurationManager::Current()->GetVoteConsolidationFunctionalityConfiguration().getUsePrintPreview();

	if(showVotePrintPreview)
	{
		CreateVotePrintDocument();
	}
	else
	{
		CreatePartyViewerWidget();
	}
}
