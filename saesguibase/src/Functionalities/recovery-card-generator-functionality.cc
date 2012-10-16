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
#include "Functionalities/recovery-card-generator-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/VotingDevice/card-data-wrapper.h"
#include <Operation/Card/CardController.hxx>
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Voting/Vote/VoteCode.hxx>
#include <Log/SMTTLogManager.h>
#include <Configuration/s-a-e-s-conf-manager.h>

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

#define IMAGE_CARD_INSERT   "ui/smartcard-recovery-insert.gif"
#define IMAGE_CARD_EXTRACT  "ui/smartcard-recovery-extract.gif"

using namespace std;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
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
using namespace Smartmatic::SAES::Configuration;

ISMTTLog* RecoveryCardGeneratorFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality",GETTEXT_PACKAGE);

RecoveryCardGeneratorFunctionality* RecoveryCardGeneratorFunctionality::current_instance = NULL;

RecoveryCardGeneratorFunctionality* RecoveryCardGeneratorFunctionality::Current()
{
	if (!current_instance)
		current_instance = new RecoveryCardGeneratorFunctionality();

	return current_instance;
};

RecoveryCardGeneratorFunctionality::RecoveryCardGeneratorFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>(),recoveryInfo("","")
{
	framePrincipal = NULL;
	recoveryWidget = NULL;
	recoveryAlignment = NULL;
	frame1 = NULL;
	frame2 = NULL;
	frame4 = NULL;
	hbox1 = NULL;
	vbox2 = NULL;
	vbuttonbox1 = NULL;
	imageCard = NULL;
	labelResult = NULL;
	buttonActivate = NULL;
	counters = NULL;
	eventboxCardActivator = NULL;
	checkbuttonIsAudio = NULL;
}

RecoveryCardGeneratorFunctionality::~RecoveryCardGeneratorFunctionality()
{
	deleteElement();
}

void RecoveryCardGeneratorFunctionality::deleteElement()
{
	if(framePrincipal)
	{
		delete(framePrincipal);
		framePrincipal = NULL;
	}
	if(recoveryWidget)
	{
		delete(recoveryWidget);
		recoveryWidget = NULL;
	}
	if(recoveryAlignment)
	{
		delete(recoveryAlignment);
		recoveryAlignment = NULL;
	}
	if(frame1)
	{
		delete(frame1);
		frame1 = NULL;
	}
	if(frame2 != NULL)
	{
		delete(frame2);
		frame2 = NULL;
	}
	if(frame4)
	{
		delete(frame4);
		frame4 = NULL;
	}
	if(hbox1)
	{
		delete(hbox1);
		hbox1 = NULL;
	}
	if(vbox2)
	{
		delete(vbox2);
		vbox2 = NULL;
	}
	if(vbuttonbox1)
	{
		delete(vbuttonbox1);
		vbuttonbox1 = NULL;
	}
	if(imageCard )
	{
		delete(imageCard);
		imageCard = NULL;
	}
	if(labelResult)
	{
		delete(labelResult);
		labelResult = NULL;
	}
	if(buttonActivate)
	{
		delete(buttonActivate);
		buttonActivate = NULL;
	}
	if(counters)
	{
		delete(counters);
		counters = NULL;
	}
	if(eventboxCardActivator)
	{
		delete(eventboxCardActivator);
		eventboxCardActivator = NULL;
	}
	if(checkbuttonIsAudio)
	{
		delete(checkbuttonIsAudio);
		checkbuttonIsAudio = NULL;
	}
}

void RecoveryCardGeneratorFunctionality::Initialize()
{
	buttonActivate->set_sensitive(false);
	CardController::getInstance()->initialize();
	int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getRecoveryCardGeneratorFunctionality();

	sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			   &RecoveryCardGeneratorFunctionality::Refresh), 0);
	conn = Glib::signal_timeout().connect(my_slot,timerRefresh);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.InsertCardToActivate"));
	wasPresent = false;
	framePrincipal->remove();
	framePrincipal->add(*hbox1);
	enableExitButton();
};


bool RecoveryCardGeneratorFunctionality::Refresh(int time_num)
{
	bool present = CardController::getInstance()->isCardPresent();

	if(present && !wasPresent)
	{
		//Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getVotingDevice("342");
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
		buttonActivate->set_sensitive(true);
		wasPresent = true;
	}
	else if (!present && wasPresent)
	{
		imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, IMAGE_CARD_INSERT));
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.InsertCardToActivate"));
		buttonActivate->set_sensitive(false);
		frame4->remove();
		frame4->add(*vbuttonbox1);
		wasPresent = false;
	}
	return true;
}


void RecoveryCardGeneratorFunctionality::on_buttonGenerate_clicked()
{
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.AreYouCompletelySureYouWantToActivate"));
	if(SAESGUIConfigurationManager::Current()->getShowConfirmationButtons())
	{
		frame4->remove();
		frame4->add(buttonBox);
		frame4->show_all_children ();
	}
	else
	{
		on_buttonOk_clicked();
	}
}

void RecoveryCardGeneratorFunctionality::on_RecoveryOk(	Smartmatic::SAES::GUI::Widgets::RecoveryCardInfo recoveryInfo)
{

}

void RecoveryCardGeneratorFunctionality::on_buttonOk_clicked()
{
	recoveryWidget->CheckAllFields();

	if (!recoveryWidget->isValidate())
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CheckTheRedError"));
		return;
	}

	try
	{
		VotingDevice::Card_data cardRecovery;
		bool cardGenerated = false;

		if(useNewVoteRecovery)
		{
			std::string recoveryCheckStatus = recoveryWidget->checkNewRecovery();
			if(recoveryCheckStatus == "")
			{
				recoveryInfo = recoveryWidget->GetFields();
				cardRecovery = GenerateRecoveryCardWithVote();
				cardGenerated = true;
			}
			else
			{
				labelResult->set_label(recoveryCheckStatus);
			}
		}
		else
		{
			std::string info = recoveryWidget->CheckFields();
			if(info.size() > 0)
			{
				labelResult->set_label(info);
				//buttonActivate->set_sensitive(false);

				if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
					CleanAll();
			}
			else
			{

				recoveryInfo = recoveryWidget->GetFields();
				std::string compressed;
				cardRecovery = GenerateRecoveryCard();
				cardGenerated = true;
			}
		}

		if(cardGenerated)
		{
			if (cardRecovery.getCard_type().compare("")==0)
			{
				labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorRecoveryData"));
				logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorRecoveryData"));
				//buttonActivate->set_sensitive(false);
				if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
					CleanAll();
			}
			else
			{
				if (!CardController::getInstance()->writeCardData(cardRecovery))
				{
					labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
					logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
					buttonActivate->set_sensitive(false);
					if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
						CleanAll();
				}
				else
				{
					labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CardWasActivated"));
					logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CardWasActivatedSuccessfully"));
					buttonActivate->set_sensitive(false);
					counters->RefreshStats(cardRecovery);
					if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnCorrectActivation())
						CleanAll();
				}
			}

			imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, IMAGE_CARD_EXTRACT));
		}
	}
	catch (const ::xsd::cxx::tree::exception< char >& e)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
		if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
			CleanAll();
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
		if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
			CleanAll();
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
		if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
			CleanAll();
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
		if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
			CleanAll();
	}
	catch(...)
	{
		labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorValidatingData"));
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ErrorActivationCard"));
		buttonActivate->set_sensitive(false);
		if(SAESGUIConfigurationManager::Current()->getRecoveryCleanOnIncorrectActivation())
			CleanAll();
	}
	if(SAESGUIConfigurationManager::Current()->getShowRecoveryConfirmationButtons())
	{
		frame4->remove();
		frame4->add(*vbuttonbox1);
	}
}

void RecoveryCardGeneratorFunctionality::on_buttonCancel_clicked()
{
	frame4->remove();
	frame4->add(*vbuttonbox1);
	labelResult->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CardInsertedPressTheButtonToActivateTheCard"));
}

void RecoveryCardGeneratorFunctionality::CleanAll()
{
	recoveryWidget->CleanFields();
}

Smartmatic::SAES::Voting::VotingDevice::Card_data RecoveryCardGeneratorFunctionality::GenerateRecoveryCardWithVote()
{
	 // The data must be already checked here
	VotingDevice::Logical_voter_group clvg;
	VotingDevice::Card_data cardData;

	vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();

	try
	{

		std::string voteCode = recoveryInfo.getVoteCode ();

		cardData.setActivation_code(VotingDevice::CardDataWrapper::GenerateCypheredActivationCode());
		cardData.setCode (voteCode);
		cardData.setCard_type (Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_RECOVERY_VOTE_CARD);
		cardData.setCard_status (Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_NOT_USED);
		cardData.setIsAudio(false);

		clvg.setCode(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration ().getLogicalVoterGroupCode());
		clvg.setContest_group_code ("");
		clvg.setOperation_mode_code (vd.getOperation_modes ().getOperation_mode ()[0].getCode());
		clvg.setVoting_booth_code (vd.getVoting_booths ().getVoting_booth ()[0].getCode());

		std::list < Smartmatic::SAES::Voting::VotingDevice::Region_category > & regionCategoryList (
		MachineOperationManager::getInstance()->getElectoralConfiguration()->getRegionCategoryList());

		if (regionCategoryList.size() > 0)
		{
			Smartmatic::SAES::Voting::VotingDevice::Region_category region = (*(regionCategoryList.rbegin()));
			clvg.setRegion_code (region.getRegion().getCode ());
		}
		else
		{
			clvg.setRegion_code ("");
		}

		clvg.setName_key("");
		clvg.setCustom_code ("");

		cardData.setLogical_voter_group(clvg);
		cardData.setVote(recoveryWidget->GetVote());

	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		cardData.setCard_type("");
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		cardData.setCard_type("");
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		cardData.setCard_type("");
	}
	catch(...)
	{
		cardData.setCard_type("");
	}
	return cardData;
}

Smartmatic::SAES::Voting::VotingDevice::Card_data RecoveryCardGeneratorFunctionality::GenerateRecoveryCard()
{
	// The data must be already checked here
	VotingDevice::Logical_voter_group clvg;
	VotingDevice::Card_data cardData;

	try
	{

		std::string voteCode = recoveryInfo.getVoteCode ();

		cardData.setActivation_code(VotingDevice::CardDataWrapper::GenerateCypheredActivationCode());
		cardData.setCode (voteCode);
		cardData.setCard_type (Smartmatic::SAES::Voting::VotingDevice::Card_type::CARD_DATA_RECOVERY_VOTE_CARD);
		cardData.setCard_status (Smartmatic::SAES::Voting::VotingDevice::Card_status::CARD_DATA_NOT_USED);
		cardData.setIsAudio(false);



		//Set LVG
		if(recoveryInfo.getLVGCode().compare(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration ().getLogicalVoterGroupCode())==0)
		{ // Super blank card
			clvg.setCode(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration ().getLogicalVoterGroupCode());
			VotingDevice::Custom_attribute attribute ;
			attribute.setCode("");
			attribute.setValue("");
			VotingDevice::Custom_attributes customAtts;
			VotingDevice::Custom_attributes::Custom_attributeSequence customAttseq;
			clvg.setContest_group_code ("");
			clvg.setOperation_mode_code ("");
			clvg.setVoting_booth_code ("");
			customAttseq.push_back(attribute);
			customAtts.setCustom_attribute (customAttseq);
			clvg.setCustom_attributes (customAtts);
			clvg.setRegion_code ("");
			clvg.setName_key("");
			clvg.setCustom_code ("");
		}
		else
		{
			vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
			clvg = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getLogicalVoterGroup(vd,recoveryInfo.getLVGCode());
			cardData.setLogical_voter_group (clvg);
		}
	}
	catch (Smartmatic::System::Exception::CryptoException & ex)
	{
		cardData.setCard_type("");
	}
	catch(Smartmatic::System::Exception::SignedException & ex)
	{
		cardData.setCard_type("");
	}
	catch(Smartmatic::System::Exception::XmlException & ex)
	{
		cardData.setCard_type("");
	}
	catch(...)
	{
		cardData.setCard_type("");
	}
	return cardData;
}


void RecoveryCardGeneratorFunctionality::on_RecoveryCancel()
{
	//recoveryWidget->Dispose();
	framePrincipal->remove();
	framePrincipal->add(*hbox1);
	on_buttonCancel_clicked();
}

Gtk::Widget* RecoveryCardGeneratorFunctionality::GetFrame()
{
	useNewVoteRecovery = SAESConfigurationManager::Current()->isUseShortVoteCode();

	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/recovery-card-activator.glade"));
	}
	catch (const Glib::FileError & ex)
	{
		logger->Debug("FATAL - RecoveryCardGeneratorFunctionality GetFrame");
	}

	builder->get_widget("framePrincipal", framePrincipal);
	builder->get_widget("frame1", frame1);
	builder->get_widget("frame2", frame2);
	builder->get_widget("frame4", frame4);
	builder->get_widget("hbox1", hbox1);
	builder->get_widget("vbuttonbox1", vbuttonbox1);
	builder->get_widget("eventboxCardActivator",eventboxCardActivator);
	builder->get_widget("CardActivatorMessageEventBox",cardActivatorMessageEventBox);
	//builder->get_widget("eventboxcardactivatorfunctionality",cardActivatorFunctionalityEventBox);
	builder->get_widget("CardActivatorValuesEventBox",cardActivatorValuesEventBox);
	builder->get_widget("vbox2", vbox2);
	builder->get_widget("checkbuttonIsAudio", checkbuttonIsAudio);
	builder->get_widget("imageCard", imageCard);
	builder->get_widget("labelResult", labelResult);
	builder->get_widget_derived("buttonActivate", buttonActivate);
	if(useNewVoteRecovery)
		labelResult->set_size_request(250, 40);
	else
		labelResult->set_size_request(330, 40);

	checkbuttonIsAudio->set_label(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.IsAudio"));
	checkbuttonIsAudio->set_sensitive (false);
	checkbuttonIsAudio->hide();
	checkbuttonIsAudio->set_no_show_all();
	buttonActivate->SetLabel(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.ActivateCard"));
	buttonActivate->WidgetsPosition (5,0,0);
	buttonActivate->set_size_request (200,40);
	buttonActivate->signal_clicked ().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorFunctionality::on_buttonGenerate_clicked));

	recoveryAlignment = new Gtk::HButtonBox();
	recoveryWidget = new RecoveryCardGeneratorWidget(true, false, useNewVoteRecovery);
	recoveryWidget->signalOk_detected.connect( sigc::mem_fun(this, &RecoveryCardGeneratorFunctionality::on_RecoveryOk));
	recoveryWidget->signalCancel_detected.connect( sigc::mem_fun(this, &RecoveryCardGeneratorFunctionality::on_RecoveryCancel));

	buttonBox.set_spacing (5);

	buttonOk.SetLabel(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.Ok"));
	buttonOk.set_size_request (70,50);

	buttonCancel.SetLabel(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.Cancel"));
	buttonCancel.set_size_request (70,50);

	buttonOk.signal_clicked ().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorFunctionality::on_buttonOk_clicked));
	buttonCancel.signal_clicked ().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorFunctionality::on_buttonCancel_clicked));

	buttonBox.pack_start(buttonOk);
	buttonBox.pack_start(buttonCancel);

	frame4->set_size_request (200,100);
	eventboxCardActivator->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityMessageName());
	cardActivatorMessageEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorMessageEventboxName());
	//cardActivatorFunctionalityEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityEventboxName());
	cardActivatorValuesEventBox->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorValuesEventboxName());
	frame1->set_name(SAESGUIConfigurationManager::Current()->GetCardActivatorFunctionalityCenterFrameName());
	//eventboxCardActivator->set_size_request (200,50);

	if(useNewVoteRecovery)
		frame1->set_size_request (430,490);
	else
		frame1->set_size_request (400,350);

	frame1->remove();
	frame1->add(*recoveryWidget);
	frame1->show_all_children ();

	counters = new CustomAttributesCounterWidget(_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.GeneratedCards"),"",Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCardRecoveryStatisticsConfiguration(),
												 Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getCardRecoveryStatisticsTitleColor(),Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetCardRecoveryStatisticsTitleLabelConfiguration());
	vbox2->add(*counters);
	imageCard->set(ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME, IMAGE_CARD_INSERT));
	//counters->ResizeOptionsWidgets (-1,80/counter);
	return framePrincipal;
};


bool RecoveryCardGeneratorFunctionality::Enable()
{
	bool enableFunctionality = true;

	if (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalDemoActivated()
			< Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getMinimumDemoCounterToAllowRecovery())
	{
		enableFunctionality = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.UnableKeyMessageDemostrationVoteNotPrinted"));
	}

	return enableFunctionality;
};

string RecoveryCardGeneratorFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CardActivatorFunctionality");

};

MenuOptionDescriptor RecoveryCardGeneratorFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MRecoveryCardGeneratorFunctionality,false);
};

void RecoveryCardGeneratorFunctionality::Dispose()
{
	CardController::getInstance()->dispose();
	conn.disconnect();
	frame4->remove();
	frame4->add(*vbuttonbox1);
};

Smartmatic::Log::ISMTTLog* RecoveryCardGeneratorFunctionality::getLogger()
{
	return logger;
}
Glib::ustring RecoveryCardGeneratorFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.LogStartFunctionality");
}

Glib::ustring RecoveryCardGeneratorFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.LogCloseFunctionality");
}
