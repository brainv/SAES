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
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include "Functionalities/vote-demo-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <Operation/MachineOperationManager.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Operation/Card/CardController.hxx>
#include "Devices/barcode-device.h"
#include "Gui/Widgets/AbstractFactoryWidget.hxx"
#include <Log/SMTTLogManager.h>
#include <Operation/SaesEnqueuer.h>
#include <Configuration/label-configuration.h>

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
using namespace Smartmatic::Functionality;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::GUI::Windows;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Windows;
using namespace Smartmatic::SAES::HW::Devices;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Printing;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::GUI::Configuration;

ISMTTLog* VoteProcessDemoFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.VoteProcessDemoFunctionality",GETTEXT_PACKAGE);

VoteProcessDemoFunctionality* VoteProcessDemoFunctionality::current_instance = NULL;

VoteProcessDemoFunctionality* VoteProcessDemoFunctionality::Current()
{
	if (!current_instance)
		current_instance = new VoteProcessDemoFunctionality();

	return current_instance;
};

VoteProcessDemoFunctionality::VoteProcessDemoFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	framePrincipal = NULL;
	frameNormal = NULL;
	frame2 = NULL;
	vbox2 = NULL;
	imageCard = NULL;
	imageVote = NULL;
	labelResult = NULL;
	labelStatus = NULL;
	labelVoteGen = NULL;
	buttonMagnify = NULL;
	//comboSelections = NULL;
	scrolledwindowVote = NULL;
	eventboxVoteDemo = NULL;
	eventboxStepBarcode= NULL;
	printWidget = NULL;
	frameMagnify= NULL;
	vboxMagnify= NULL;
	scrolledMagnify= NULL;
	viewMagnify= NULL;
	buttonBackMagnify= NULL;
	checkbuttonIsAudio = NULL;
	viewportVote = NULL;
	outsideBox = NULL;
	barcodeDetectionWidget = NULL;
	doc = NULL;
	docMagnify = NULL;
	printWidgetMagnify = NULL;
	cardActivatorBox = NULL;
	eventbox1 = NULL;

	validVote = false;
}

VoteProcessDemoFunctionality::~VoteProcessDemoFunctionality()
{
	deleteElement();
}

void VoteProcessDemoFunctionality::cleanAttributes()
{
	std::vector<Smartmatic::SAES::Voting::VotingDevice::Custom_attribute*>::iterator it;

	for(it = atts.begin();
	    it != atts.end();
	    it++)
	{
		delete(*it);
	}

	atts.clear();
}

void VoteProcessDemoFunctionality::deleteElement()
{
	if(cardActivatorBox)
	{
		delete(cardActivatorBox);
		cardActivatorBox = NULL;
	}
	if(framePrincipal)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(frameNormal)
	{
		delete(frameNormal);
		frameNormal = NULL;
	}
	if(frame2)
	{
		delete(frame2);
		frame2 = NULL;
	}
	if(vbox2 != NULL)
	{
		delete(vbox2);
		vbox2 = NULL;
	}
	if(imageCard != NULL)
	{
		delete(imageCard);
		imageCard = NULL;
	}
	if (imageVote)
	{
		delete imageVote;
		imageVote = NULL;
	}
	if (labelResult)
	{
		delete labelResult;
		labelResult = NULL;
	}
	if(labelStatus)
	{
		delete(labelStatus);
		labelStatus = NULL;
	}
	if(labelVoteGen)
	{
		delete(labelVoteGen);
		labelVoteGen = NULL;
	}
	if(buttonMagnify)
	{
		delete(buttonMagnify);
		buttonMagnify = NULL;
	}
	if(eventbox1)
	{
		delete(eventbox1);
		eventbox1 = NULL;
	}
	if(scrolledwindowVote)
	{
		delete(scrolledwindowVote);
		scrolledwindowVote = NULL;
	}
	if(eventboxVoteDemo)
	{
		delete(eventboxVoteDemo);
		eventboxVoteDemo = NULL;
	}
	if(eventboxStepBarcode)
	{
		delete(eventboxStepBarcode);
		eventboxStepBarcode = NULL;
	}
	if(printWidget)
	{
		delete(printWidget);
		printWidget = NULL;
	}
	if(frameMagnify)
	{
		delete(frameMagnify);
		frameMagnify = NULL;
	}
	if(vboxMagnify)
	{
		delete(vboxMagnify);
		vboxMagnify = NULL;
	}
	if(scrolledMagnify)
	{
		delete(scrolledMagnify);
		scrolledMagnify = NULL;
	}
	if(viewMagnify)
	{
		delete(viewMagnify);
		viewMagnify = NULL;
	}
	if(buttonBackMagnify)
	{
		delete(buttonBackMagnify);
		buttonBackMagnify = NULL;
	}
	if(checkbuttonIsAudio)
	{
		delete(checkbuttonIsAudio);
		checkbuttonIsAudio = NULL;
	}
	if(viewportVote)
	{
		delete(viewportVote);
		viewportVote = NULL;
	}
	if (outsideBox)
	{
		delete outsideBox;
		outsideBox = NULL;
	}
	if (barcodeDetectionWidget)
	{
		delete barcodeDetectionWidget;
		barcodeDetectionWidget = NULL;
	}
	if (doc)
	{
		delete doc;
		doc = NULL;
	}
	if (docMagnify)
	{
		delete docMagnify;
		docMagnify = NULL;
	}
	if (printWidgetMagnify)
	{
		delete printWidgetMagnify;
		printWidgetMagnify = NULL;
	}

	cleanAttributes();
}

void VoteProcessDemoFunctionality::SaveVote()
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
		labelStatus->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorSaveVote"));
		buttonMagnify->set_sensitive (false);
	}
}

void VoteProcessDemoFunctionality::ProcessVote()
{
	refresh();

	if(SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration().getPersistVote())
	{
		if(!voteStats->IsVoteProcessed(vote))
		{
			BarcodeRefreshDemo(true);
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.SuccessfullProcessVote"));
			SaveVote();
		}
		else
		{
			validVote = false;
			refresh();

			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.VoteAlreadyProcessed"));
			labelStatus->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteProcessDemoFunctionality.VoteAlreadyProcessed"));
		}
	}
	else
	{
		BarcodeRefreshDemo(true);
	}
}

void VoteProcessDemoFunctionality::RecievedData(Smartmatic::System::SafeBuffer * received)
{
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pushObject(received);
}

void VoteProcessDemoFunctionality::Initialize()
{
	magnify = false;
	validVote = false;
	docMagnify = false;
	reconfigure = false;

	framePrincipal->remove();
	framePrincipal->add(*frameNormal);
	buttonMagnify->set_sensitive (false);
	viewportVote->remove();
	CardController::getInstance()->initialize();
	labelStatus->set_label("");

	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getRecoveryCardGeneratorFunctionality();

	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			   &VoteProcessDemoFunctionality::Refresh), 0);
	conn = Glib::signal_timeout().connect(my_slot,timerRefresh);
	labelResult->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.PleaseInsertCardToActivate"));
	labelVoteGen->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.WaitingForCard"));
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StartEnqueuerProcess();
	signalPopDispatcher = MachineOperationManager::getInstance()->getSaesEnqueuer()->popDispatcher.connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::signalingPopDispatcher));
	labelStatus->set_label("");
	wasPresent = false;

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();

	signalStartSendCommand = BarcodeDevice::Current()->getSignalStartSendCommand().connect(sigc::mem_fun(*this , &VoteProcessDemoFunctionality::reconfigureBarcode));
	signalEndSendCommand = BarcodeDevice::Current()->getSignalEndSendCommand().connect(sigc::mem_fun(*this , &VoteProcessDemoFunctionality::endReconfigureBarcode));

	connReceived.disconnect();
	connReceived = BarcodeDevice::Current()->signalDetected().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::RecievedData));

	string barcodeInParams = SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration().getBarcodeInParams();

	if(BarcodeDevice::Current()->sendPing() && !barcodeInParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeInParams,false,false);
	}
	else
	{
		enableExitButton();
	}
}

void VoteProcessDemoFunctionality::signalingPopDispatcher()
{
	std::list <VoteResult *> list;
	std::list <VoteResult *>::iterator it;

	MachineOperationManager::getInstance()->getSaesEnqueuer()->getVoteResultList(list);

	for (it = list.begin();
		 it != list.end();
		 it++)
	{
		VoteResult * voteResult = (*it);

		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ScannedVote"));
		switch(voteResult->getResult())
		{
			case MachineOperationManager::VOTE_FROM_BUFFER_SUCCESS:
				vote = (*(voteResult->getVote()));
				validVote = true;
				BarcodeRefresh();
				break;
			case MachineOperationManager::VOTE_FROM_BUFFER_DECOMPRESSION_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_DECRYPTO_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_SIGNATURE_TRUST_ERROR:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_VOTING_DEVICE:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_LVG:
			case MachineOperationManager::VOTE_FROM_BUFFER_INVALID_PROCESS_INSTANCE:
			case MachineOperationManager::VOTE_FROM_BUFFER_UNEXPECTED_ERROR:
				BarcodeError(false);
				break;
		}

		delete voteResult;
		voteResult = NULL;
	}
}

void VoteProcessDemoFunctionality::onOptionButton(ChooseDialogButtonInfo* info)
{
	temporalValue.clear();
	temporalValue.append(info->getName());
}

std::string VoteProcessDemoFunctionality::getCodeByName(std::string optionName)
{
	for(list<VotingDevice::Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		if((*l).getName_key().compare(optionName)==0)
	   {
		   return (*l).getCode();
	   }
	}
	return "";
}

std::string VoteProcessDemoFunctionality::getNameByCode(std::string optionCode)
{
	for(list<VotingDevice::Custom_attribute_definition>::iterator
		 l (listCAD.begin());
		 l != listCAD.end();
		 ++l)
	{
		if((*l).getCode().compare(optionCode)==0)
	   {
		   return (*l).getName_key();
	   }
	}
	return "";
}

void VoteProcessDemoFunctionality::BarcodeError(bool enabledMagnify)
{
	validVote = false;

	labelStatus->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.BarcodeErrorTryAgain"));
	refresh();
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ScannedVoteWithErrors"));

	if (buttonMagnify)
	{
		buttonMagnify->set_sensitive (enabledMagnify);
	}
}

void VoteProcessDemoFunctionality::BarcodeRefreshDemo(bool enabledMagnify)
{
	labelStatus->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.VoteMarkedAsDemoGenerateCardWhenReady"));
	labelVoteGen->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.WaitingForCard"));

	refresh();
}

void VoteProcessDemoFunctionality::BarcodeRefreshNotDemo()
{
	validVote = false;
	refresh();
	labelStatus->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.VoteNotMarkedAsDemoTryAgain"));
	logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.VoteNotMarkedAsDemoTryAgain"));
}

void VoteProcessDemoFunctionality::BarcodeRefresh()
{
	logger->Debug("Vote code is:" + vote.getCode());

	if(vote.getMode() == Vote::VoteMode::VOTE_D)
	{
		logger->Debug("Vote is DEMO!!!!");
		ProcessVote();
	}
	else
	{
		logger->Debug("Vote is NOT DEMO!!!!");
		buttonMagnify->set_sensitive (false);

		BarcodeRefreshNotDemo();
	}
}

bool VoteProcessDemoFunctionality::Refresh(int time_num)
{
	bool present = CardController::getInstance()->isCardPresent();

	if(present && !wasPresent )
	{
		wasPresent = true;
		activateCardData();
	}
	else if (!present && wasPresent)
	{
		labelResult->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.PleaseInsertCardToActivate"));
		imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif"));
		wasPresent = false;
	}

	return true;
}

void VoteProcessDemoFunctionality::activateCardData()
{
	try
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.StartingToActivateVoteDemoCard"));

		viewportVote->remove();
		buttonMagnify->set_sensitive (false);

		for(unsigned int k=0;k<attributes.size();k++)
		{
			VotingDevice::Custom_attribute* attribute = new VotingDevice::Custom_attribute(attributes[k].getCode(), attributes[k].getValue());
			atts.push_back(attribute);
		}

		VotingDevice::Card_data cardData;
		VotingDevice::CardDataWrapper::GenerateCardData(MachineOperationManager::getInstance()->getElectoralConfiguration(), atts, cardData, true, Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_DEMOSTRATION_VOTE_CARD,checkbuttonIsAudio->get_active());

		if (!CardController::getInstance()->writeCardData(cardData))
		{
			labelResult->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
			imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card_error.gif"));
		}
		else
		{
			labelResult->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.CardActivatedRemoveCard"));
			logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.CardDemoWasActivatedSuccessfully"));
			labelVoteGen->set_label (_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.NowScanPrintedVoteToView"));
			lastCardGUUID = cardData.getCode();

			Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->RefreshStats(cardData);
			imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/wiz_extract_identity_card.gif"));
		}

	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
	}
	catch(...)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorValidatingDataCheckPositionOfCard"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ErrorActivationCard"));
	}

	cleanAttributes();
}

void VoteProcessDemoFunctionality::on_buttonBackMagnify_clicked()
{
	magnify = false;
	enableExitButton();
	refresh();
}

void VoteProcessDemoFunctionality::on_buttonMagnify_clicked()
{
	magnify = true;
	disableExitButton();
	refresh();
}

void VoteProcessDemoFunctionality::CreateNormalFrame()
{
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/vote-process-demo.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - VoteProcessDemoFunctionality CreateNormalFrame");
	}

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("frameNormal", frameNormal);
	builder->get_widget("frame2", frame2);
	builder->get_widget("eventboxVoteProcessDemo", eventboxVoteDemo);
	builder->get_widget("eventboxStepBarcode", eventboxStepBarcode);
	builder->get_widget("vbox2", vbox2);
	builder->get_widget("imageCard", imageCard);
	builder->get_widget("labelResult", labelResult);
	builder->get_widget("labelStatus", labelStatus);
	builder->get_widget("checkbuttonIsAudio", checkbuttonIsAudio);
	builder->get_widget_derived("buttonMagnify", buttonMagnify);
	builder->get_widget("labelVoteGen", labelVoteGen);
	builder->get_widget("scrolledwindowVote", scrolledwindowVote);
	builder->get_widget("viewportVote", viewportVote);
	//builder->get_widget("imageVote", imageVote);
	builder->get_widget_derived("buttonBackMagnify", buttonBackMagnify);
	builder->get_widget("frameMagnify", frameMagnify);
	builder->get_widget("vboxMagnify", vboxMagnify);
	builder->get_widget("scrolledwindowMagnify", scrolledMagnify);
	builder->get_widget("viewportMagnify", viewMagnify);
	builder->get_widget("eventbox1", eventbox1);

	eventboxStepBarcode->set_name(SAESGUIConfigurationManager::Current()->GetEventboxStepBarcodeName());

	labelVoteGen->set_alignment(0.5, 0.5);
	labelStatus->set_alignment(0.5, 0.5);
	labelResult->set_alignment(0.5, 0.5);

	checkbuttonIsAudio->set_label(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.IsAudio"));
	checkbuttonIsAudio->set_sensitive (false);
	buttonMagnify->SetLabel(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.Magnify"));
	buttonMagnify->WidgetsPosition (5,0,0);
	buttonMagnify->set_size_request (100,50);
	buttonMagnify->signal_clicked ().connect(sigc::mem_fun(*this,&VoteProcessDemoFunctionality::on_buttonMagnify_clicked));

	buttonBackMagnify->SetLabel(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.BackMagnify"));
	buttonBackMagnify->WidgetsPosition (5,0,0);
	buttonBackMagnify->set_size_request (200,50);
	buttonBackMagnify->signal_clicked ().connect(sigc::mem_fun(*this,&VoteProcessDemoFunctionality::on_buttonBackMagnify_clicked));

	eventboxVoteDemo->set_name(SAESGUIConfigurationManager::Current()->GetVoteDemoFunctionalityMessageName());

	//comboSelections = new CustomAttributesComboSelectionsWidget(_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.CustomAttributeSelection"),"",true);

	cardActivatorBox = new CardActivatorEventBox(300);
	cardActivatorBox->signal_vectorCustomAttribute_changed().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::SetCustomAttributeVector));

	static VoteDemoFunctionalityConfiguration config =
			SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration();

	static LabelConfiguration selectedLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getLabelSelectedConfiguration());

	static LabelConfiguration unselectedLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getLabelUnselectedConfiguration());

	static LabelConfiguration titleLabelConfiguration =
			SAESGUIConfigurationManager::ConvertToLabelConfiguration(config.getTitleFontConfiguration());

	cardActivatorBox->setFont(titleLabelConfiguration, selectedLabelConfiguration, unselectedLabelConfiguration);

	LabelConfiguration::SetLabelConfiguration(labelResult, titleLabelConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelStatus, titleLabelConfiguration);
	LabelConfiguration::SetLabelConfiguration(labelVoteGen, titleLabelConfiguration);

	eventbox1->add(*cardActivatorBox);
	eventbox1->show_all_children();

	imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/smartcard_activation.gif"));

	///Here Comes the initialization of many Widgets, which can be translated to Initialize if needed to "refresh" the status every time the window is opened
	Smartmatic::SAES::Voting::VotingDevice::Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
	listCAD = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getCustomAttributeDefinitionList(vd, VotingDevice::Machine_type::VOTING_DEVICES_PM);

	voteStats = MachineOperationManager::getInstance()->getVoteStatistics();
	normalFrameWidget =  framePrincipal;
}

Gtk::Widget* VoteProcessDemoFunctionality::GetFrame()
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

	barcodeDetectionWidget->signal_barcode_connected().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::on_barcode_connected));

	outsideBox->show_all_children();

	connBarcodeDisconnected.disconnect();
	connBarcodeDisconnected = BarcodeDevice::Current()->signalDisconnected().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::BarcodeDisconnected));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::setExitButtonSensitive));
	barcodeDetectionWidget->enable_exit().connect(sigc::mem_fun(*this, &VoteProcessDemoFunctionality::setHelpButtonSensitive));

	return outsideBox;

};

void VoteProcessDemoFunctionality::SetCustomAttributeVector(std::vector< Smartmatic::SAES::Voting::VotingDevice::Custom_attribute > vecCA)
{
	attributes = vecCA;
}

void VoteProcessDemoFunctionality::BarcodeDisconnected()
{
	reconfigure = false;
	enableExitButton();
	disableHelpButton();
	barcodeDetectionWidget->SetDefault();

	if(normalFrameWidget->get_parent())
	{
		outsideBox->remove(*normalFrameWidget);
		outsideBox->add(*barcodeDetectionWidget);
		outsideBox->show_all_children();
	}
}

void VoteProcessDemoFunctionality::on_barcode_connected(bool isConnected)
{
	if(isConnected && barcodeDetectionWidget->get_parent())
	{
		outsideBox->remove(*barcodeDetectionWidget);
		outsideBox->add(*normalFrameWidget);
		outsideBox->show_all_children();
	}
}

string VoteProcessDemoFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.WindowTitle");
};

MenuOptionDescriptor VoteProcessDemoFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MVoteProcessDemoFunctionality,false);
}

void VoteProcessDemoFunctionality::BeforeExit()
{
	if(SAESGUIConfigurationManager::Current()->getMinimumDemoCounterToAllowActivation() == 0 ||
			!SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration().getPersistVote() ||
			MachineOperationManager::getInstance()->getVoteStatistics()->getDemoVotes() >= SAESGUIConfigurationManager::Current()->getMinimumDemoCounterToAllowActivation())
	{
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ExitFunctionality"));
	}
	else
	{
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ElectionStatusNotChanged"));
	}

	AdjustElectionStatus();
}

void VoteProcessDemoFunctionality::Dispose()
{
	if (buttonMagnify)
	{
		buttonMagnify->set_sensitive(false);
	}

	signalStartSendCommand.disconnect();
	signalEndSendCommand.disconnect();
	connReceived.disconnect();

	connBarcodeDisconnected.disconnect();
	CardController::getInstance()->dispose();

	viewMagnify->remove();
	viewportVote->remove();

	string barcodeOutParams = SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration().getBarcodeOutParams();
	if(BarcodeDevice::Current()->sendPing() && !barcodeOutParams.empty())
	{
		BarcodeDevice::Current()->SendConfigurationCommands(barcodeOutParams, false, true);
	}
	else
	{
		BarcodeDevice::Current()->Close();
	}

	conn.disconnect();
	signalPopDispatcher.disconnect();
	MachineOperationManager::getInstance()->getSaesEnqueuer()->StopEnqueuerProcess();
}

void VoteProcessDemoFunctionality::AdjustElectionStatus()
{
	try
	{
		if(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->isNotDemostrationVote())
		{
			Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->demostrationVote();
			exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.ElectionStatusChanged"));
		}
	}
	catch(...)
	{
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.VoteDemoFunctionality.UnexpectedErrorChangingElectionStatus"));
	}
}

Smartmatic::Log::ISMTTLog* VoteProcessDemoFunctionality::getLogger()
{
	return logger;
}

Glib::ustring VoteProcessDemoFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VoteProcessDemoFunctionality.LogStartFunctionality");
}

Glib::ustring VoteProcessDemoFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.VoteProcessDemoFunctionality.LogCloseFunctionality");
}

void VoteProcessDemoFunctionality::refresh()
{
	Glib::Mutex::Lock lock(mutex);

	if (reconfigure)
	{
		return;
	}

	viewMagnify->remove();
	viewportVote->remove();

	if (printWidget)
	{
		delete(printWidget);
		printWidget = NULL;
	}
	if (doc)
	{
		delete doc;
		doc = NULL;
	}
	if (docMagnify)
	{
		delete docMagnify;
		docMagnify = NULL;
	}

	buttonMagnify->set_sensitive(!magnify);

	framePrincipal->remove();

	if (magnify)
	{
		framePrincipal->add(*frameMagnify);
	}
	else
	{
		framePrincipal->add(*frameNormal);
	}

	if (!validVote)
	{
		magnify = false;
		framePrincipal->remove();
		framePrincipal->add(*frameNormal);
		buttonMagnify->set_sensitive(false);
		enableExitButton();
		return;
	}

	bool showBarcode = SAESGUIConfigurationManager::Current()->getVoteDemoFunctionalityConfiguration().getShowBarcodeInPreview();

	doc = new VotePrintDocument(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),vote,true, showBarcode);
	docMagnify= new VotePrintDocument(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration(),vote,true, showBarcode);

	printWidget = new PrintPreviewWidget(doc);

	if (magnify)
	{
		viewMagnify->add(*printWidget);
		viewMagnify->show_all_children();
	}
	else
	{
		viewportVote->add(*printWidget);
		viewportVote->show_all_children ();
	}
}

void VoteProcessDemoFunctionality::block()
{
	logger->Debug("Block functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->pauseProcess();
}

void VoteProcessDemoFunctionality::partial()
{
	logger->Debug("Partial functionality");
}

void VoteProcessDemoFunctionality::resume()
{
	logger->Debug("Resume functionality");
	MachineOperationManager::getInstance()->getSaesEnqueuer()->resumeProcess();
}

void VoteProcessDemoFunctionality::reconfigureBarcode()
{
	reconfigure = true;
	disableExitButton();
}

void VoteProcessDemoFunctionality::endReconfigureBarcode()
{
	reconfigure = false;
	enableExitButton();
}
