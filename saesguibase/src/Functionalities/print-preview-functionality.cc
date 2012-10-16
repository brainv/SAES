/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
* saesguibase
* Copyright (C)  2011 <>
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
#include <sstream>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include "Functionalities/print-preview-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "System/Compression/compression-class.h"
#include <Devices/barcode-device.h>
#include "Gui/Widgets/AbstractFactoryWidget.hxx"
#include <Log/SMTTLogManager.h>
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

using namespace Smartmatic::SAES::Functionality;
using namespace std;
using namespace Smartmatic::System::Compression;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::Environment;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Gtk;


ISMTTLog* PrintPreviewFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality",GETTEXT_PACKAGE);

PrintPreviewFunctionality* PrintPreviewFunctionality::current_instance = NULL;

PrintPreviewFunctionality* PrintPreviewFunctionality::Current()
{
	if (!current_instance)
		current_instance = new PrintPreviewFunctionality();

	return current_instance;
};

PrintPreviewFunctionality::PrintPreviewFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	partyViewerWidget = NULL;
	docMagnify = NULL;
	printWidgetMagnify = NULL;
	labelMessage = NULL;
	frameMagnify = NULL;
	vboxMagnify = NULL;
	scrolledMagnify = NULL;
	viewMagnify = NULL;
	barcodeDetectionWidget = NULL;
	outsideBox = NULL;

	validVote = false;
}

PrintPreviewFunctionality::~PrintPreviewFunctionality()
{
	deleteElement();
}

void PrintPreviewFunctionality::RecievedData(Smartmatic::System::SafeBuffer * received)
{
	logger->Debug("Recieved Data");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pushObject(received);
}

void PrintPreviewFunctionality::Initialize()
{
	validVote = false;
	labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.WaitingForBarcode"));
	Pango::FontDescription fontTitle = labelMessage->get_style()->get_font();
	fontTitle.set_size(13*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelMessage->modify_font(fontTitle);

	connReceived.disconnect();
	connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::RecievedData));

	viewMagnify->remove();
	viewMagnify->show_all_children ();
	vboxMagnify->show_all_children ();
	frameMagnify->show_all_children ();

	MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();
	signalPopDispatcher.disconnect();
	signalPopDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::signalingPopDispatcher));

	string barcodeInParams = SAESGUIConfigurationManager::Current()->getPrintPreviewFunctionalityConfiguration().getBarcodeInParams();

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();

	signalStartSendCommand = BarcodeDevice::Current()->getSignalStartSendCommand().connect(sigc::mem_fun(*this , &PrintPreviewFunctionality::disableExitButton));
	signalEndSendCommand = BarcodeDevice::Current()->getSignalEndSendCommand().connect(sigc::mem_fun(*this , &PrintPreviewFunctionality::enableExitButton));

	if(BarcodeDevice::Current()->sendPing() && !barcodeInParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeInParams,false,false);
	}
	else
	{
		enableExitButton();
	}
}

void PrintPreviewFunctionality::signalingPopDispatcher()
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
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_SUCCESS");
				vote = (*(voteResult->getVote()));
				validVote = true;
				refresh();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_DECOMPRESSION_ERROR");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_DECRYPTO_ERROR");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_SIGNATURE_ERROR");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_INVALID_LVG");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE");
				BarcodeError();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR:
				logger->Debug("PrintPreviewFunctionality VOTE_FROM_BUFFER_UNEXPECTED_ERROR");
				BarcodeError();
				break;
		}

		delete voteResult;
		voteResult = NULL;
	}
}

void PrintPreviewFunctionality::BarcodeError()
{
	validVote = false;
	viewMagnify->remove();
	labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.BarcodeErrorTryAgain"));
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.BarcodeError"));
}

bool PrintPreviewFunctionality::BarcodeRefreshVoteMode(int time_num)
{
	switch(voteMode)
	{
	case Vote::VoteMode::VOTE_D:
		labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsDemo"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsDemo"));
		break;
	case Vote::VoteMode::VOTE_O:
		labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsOfficial"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsOfficial"));
		break;
	case Vote::VoteMode::VOTE_R:
		labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsRecovery"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsRecovery"));
		break;
	case Vote::VoteMode::VOTE_S:
		labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsSimulated"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsSimulated"));
		break;
	}

	return false;
}

void PrintPreviewFunctionality::CreateNormalFrame()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/vote-preview-functionality.glade"));
	}
	catch (const Glib::FileError & ex)
	{
        std::stringstream ss;
        ss  << "FATAL - " << __func__ << " " << ex.what();
        logger->Debug(ss.str());
	}

	builder->get_widget("labelMessage", labelMessage);
	builder->get_widget("frameMagnify", frameMagnify);
	builder->get_widget("vboxMagnify", vboxMagnify);
	builder->get_widget("scrolledwindowMagnify", scrolledMagnify);
	builder->get_widget("viewportMagnify", viewMagnify);
	//viewMagnify->add(printWidgetMagnify);
	labelMessage->set_size_request (600,50);
	labelMessage->set_alignment(0.5, 0.5);
	normalFrameWidget = frameMagnify;
}

Gtk::Widget* PrintPreviewFunctionality::GetFrame()
{
	CreateNormalFrame();
	outsideBox = new HBox();

	barcodeDetectionWidget = AbstractFactoryWidget::createBarcodeDetectionWidget();
	barcodeDetectionWidget->ConnectSignals();

	if(barcodeDetectionWidget->CheckBarcodeConnected())
	{
		outsideBox->add(*normalFrameWidget);
	}
	else
	{
		outsideBox->add(*barcodeDetectionWidget);
	}

	barcodeDetectionWidget->signal_barcode_connected().connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::on_barcode_connected));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::setExitButtonSensitive));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::setHelpButtonSensitive));

	outsideBox->show_all_children();

	connBarcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &PrintPreviewFunctionality::BarcodeDisconnected));

	return outsideBox;
};

void PrintPreviewFunctionality::BarcodeDisconnected()
{
	enableExitButton();

	barcodeDetectionWidget->SetDefault();
	if(normalFrameWidget->get_parent())
	{
		labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.WaitingForBarcode"));
		viewMagnify->remove();
		outsideBox->remove(*normalFrameWidget);
		outsideBox->add(*barcodeDetectionWidget);
	}
	outsideBox->show_all_children();
}

void PrintPreviewFunctionality::on_barcode_connected(bool isConnected)
{
	if(isConnected && barcodeDetectionWidget->get_parent())
	{
		outsideBox->remove(*barcodeDetectionWidget);
		outsideBox->add(*normalFrameWidget);
		outsideBox->show_all_children();
	}
}

string PrintPreviewFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.WindowTitle");
};

MenuOptionDescriptor PrintPreviewFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MPrintPreviewFunctionality,false);
};

void PrintPreviewFunctionality::Dispose()
{
	validVote = false;
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();
	connBarcodeDisconnected.disconnect();
	signalPopDispatcher.disconnect();
	viewMagnify->remove();
	
	connReceived.disconnect();
	connBarcode.disconnect();

	string barcodeOutParams = SAESGUIConfigurationManager::Current()->getPrintPreviewFunctionalityConfiguration().getBarcodeOutParams();

	if(BarcodeDevice::Current()->sendPing() && !barcodeOutParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeOutParams, false, true);
	}
	else
	{
		BarcodeDevice::Current()->Close();
	}
};

Smartmatic::Log::ISMTTLog* PrintPreviewFunctionality::getLogger()
{
	return logger;
}

Glib::ustring PrintPreviewFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.LogStartFunctionality");
}

Glib::ustring PrintPreviewFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.LogCloseFunctionality");
}

void PrintPreviewFunctionality::refresh()
{
	Glib::Mutex::Lock lock(mutex);

	if (!validVote)
	{
		return;
	}

	if(!SAESGUIConfigurationManager::Current()->getPrintPreviewFunctionalityConfiguration().getUsePrintPreview())
	{
		try
		{
			if(partyViewerWidget) delete partyViewerWidget;
			bool tableVertical = SAESGUIConfigurationManager::Current()->getPrintPreviewFunctionalityConfiguration().getUseVerticalTableInPreview();
			partyViewerWidget = new Smartmatic::SAES::GUI::Widgets::PartyContestViewerWidget(vote, tableVertical);
			viewMagnify->remove();
			viewMagnify->add(*partyViewerWidget);
			viewMagnify->show_all_children ();
		}
		catch(...)
		{
			labelMessage->set_label (_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.BarcodeErrorTryAgain"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.BarcodeError"));
		}
	}
	else
	{
		if(docMagnify)
		{
			delete (docMagnify);
			docMagnify = NULL;
		}
		bool showBarcode = SAESGUIConfigurationManager::Current()->getPrintPreviewFunctionalityConfiguration().getShowBarcodeInPreview();

		docMagnify= new VotePrintDocument(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),vote,true, showBarcode);
		viewMagnify->remove();

		if(printWidgetMagnify != NULL)
		{
			delete(printWidgetMagnify);
			printWidgetMagnify = NULL;
		}
		printWidgetMagnify = new PrintPreviewWidget(docMagnify);

		viewMagnify->remove();
		viewMagnify->add(*printWidgetMagnify);
		viewMagnify->show_all_children ();


		switch(vote.getMode())
		{
			case Vote::VoteMode::VOTE_D:
				voteMode = Vote::VoteMode::VOTE_D;
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsDemo"));
				break;
			case Vote::VoteMode::VOTE_O:
				voteMode = Vote::VoteMode::VOTE_O;
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsOfficial"));
				break;
			case Vote::VoteMode::VOTE_R:
				voteMode = Vote::VoteMode::VOTE_R;
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsRecovery"));
				break;
			case Vote::VoteMode::VOTE_S:
				voteMode = Vote::VoteMode::VOTE_S;
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.PrintPreviewFunctionality.VoteMarkedAsSimulated"));
				break;
		}

		BarcodeRefreshVoteMode(0);
	}
}

void PrintPreviewFunctionality::deleteElement()
{
	if(partyViewerWidget)
	{
		delete (partyViewerWidget);
		partyViewerWidget = NULL;
	}
	if(docMagnify)
	{
		delete (docMagnify);
		docMagnify = NULL;
	}
	if(printWidgetMagnify)
	{
		delete(printWidgetMagnify);
		printWidgetMagnify = NULL;
	}
	if(labelMessage != NULL)
	{
		delete(labelMessage);
		labelMessage = NULL;
	}
	if(frameMagnify != NULL)
	{
		delete(frameMagnify);
		frameMagnify = NULL;
	}
	if(vboxMagnify != NULL)
	{
		delete(vboxMagnify);
		vboxMagnify = NULL;
	}
	if(scrolledMagnify != NULL)
	{
		delete(scrolledMagnify);
		scrolledMagnify = NULL;
	}
	if(viewMagnify != NULL)
	{
		delete(viewMagnify);
		viewMagnify = NULL;
	}
	if (barcodeDetectionWidget)
	{
		delete barcodeDetectionWidget;
		barcodeDetectionWidget = NULL;
	}
	if (outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
}

void PrintPreviewFunctionality::block()
{
	logger->Debug("Block functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pauseProcess();
}

void PrintPreviewFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void PrintPreviewFunctionality::resume()
{
	logger->Debug("Resume functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->resumeProcess();
}
