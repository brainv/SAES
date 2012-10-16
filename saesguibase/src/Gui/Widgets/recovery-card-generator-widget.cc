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

#include "Gui/Widgets/recovery-card-generator-widget.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "Voting/VotingDevice/card-data-wrapper.h"
#include "Voting/VotingDevice/VotingDeviceWrapper.hxx"
#include <Voting/Vote/VoteCode.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Log/SMTTLogManager.h>
#include <Log/ISMTTLog.h>
#include <Environment/Configurations/resource-path-provider.h>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include "Resources/election-string-resources-manager.h"
#include <Voting/Vote/VoteCode.hxx>
#include <Voting/Vote/VoteWrapper.hxx>
#include <Environment/Configurations/base-language-controller.h>
#include <Voting/set-language-functionality.h>
#include <Voting/VotingDevice/card-data-schema.hxx>

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

using namespace Glib;
using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::Environment;

ISMTTLog* RecoveryCardGeneratorWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget",GETTEXT_PACKAGE);

RecoveryCardGeneratorWidget::RecoveryCardGeneratorWidget(bool waitForCardToRegister, bool showButtons, bool useNewVoteRecovery)
{
	enterKey = 65293;
	checkIsOk = false;
	this->useNewVoteRecovery = useNewVoteRecovery;
	this->waitForCardToRegister = waitForCardToRegister;

	labelTitle.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.Title"));
	labelTitle.set_justify(Gtk::JUSTIFY_CENTER);
	labelTitle.set_alignment(0.5, 1);
	labelTitle.set_size_request(300, 40);

	fontLabels = labelTitle.get_style()->get_font();
	fontLabels.set_size(12*Pango::SCALE);
	fontLabels.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelTitle.modify_font(fontLabels);

	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageInitial"));
	labelMessage.set_alignment(0.5, 0.5);
	labelMessage.set_justify(Gtk::JUSTIFY_CENTER);
	labelMessage.set_size_request(300, -1);
	labelMessage.modify_font(fontLabels);
	
	goodImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/recovery_good.png");;
	badImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/recovery_bad.png");;
	noneImage = ResourcePathProvider::Current()->GetResourcePath(PACKAGE_NAME,"ui/recovery_none.png");;

	lvgCodeImage.set(Gdk::PixbufAnimation::create_from_file(noneImage));
	voteCodeImage.set(Gdk::PixbufAnimation::create_from_file(noneImage));

	int labelWidth = 140;

	labelVoteCode.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.LabelVoteCode"));
	labelVoteCode.set_alignment(0.0, 0.5);
	labelVoteCode.set_padding(10, 0);
	labelVoteCode.set_size_request(labelWidth, -1);
	labelVoteCode.set_line_wrap(true);
	labelVoteCode.modify_font(fontLabels);

	labelLVGCode.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.LabelLVGCode"));
	labelLVGCode.set_alignment(0.0, 0.5);
	labelLVGCode.set_padding(10, 0);
	labelLVGCode.set_size_request(labelWidth, -1);
	labelLVGCode.set_line_wrap(true);
	labelLVGCode.modify_font(fontLabels);

	entryLVGCode.set_size_request(180,-1);

	if(useNewVoteRecovery)
	{
		entryLVGCode.signal_key_press_event().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorWidget::on_entryLVGCode_key_pressed),false);
		entryLVGCode.signal_focus_out_event().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorWidget::on_entryLVGCode_lost_focus));
	}

	hboxLVGCode.set_homogeneous (false);
	hboxLVGCode.pack_start (labelLVGCode);//,Gtk::PACK_SHRINK);
	hboxLVGCode.pack_start (entryLVGCode,Gtk::PACK_SHRINK, 5);
	if(useNewVoteRecovery)
		hboxLVGCode.pack_start (lvgCodeImage,Gtk::PACK_SHRINK, 5);

	entryVoteCode.set_size_request (180,-1);
	entryVoteCode.signal_key_press_event().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorWidget::on_entryVoteCode_key_pressed),false);

	hboxVoteCode.set_homogeneous (false);
	hboxVoteCode.pack_start (labelVoteCode);//,Gtk::PACK_SHRINK);
	hboxVoteCode.pack_start (entryVoteCode,Gtk::PACK_SHRINK, 5);
	if(useNewVoteRecovery)
		hboxVoteCode.pack_start (voteCodeImage,Gtk::PACK_SHRINK, 5);

	okButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.ButtonOk"));
	okButton.WidgetsPosition (5,0,0);
	okButton.set_size_request (100,50);

	cancelButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.ButtonCancel"));
	cancelButton.WidgetsPosition (5,0,0);
	cancelButton.set_size_request (100,50);

	hbuttonbox.set_spacing (150);
	hbuttonbox.set_layout (Gtk::BUTTONBOX_CENTER );
	hbuttonbox.add(okButton);
	hbuttonbox.add(cancelButton);

	vboxPrincipal.pack_start (labelTitle,false,false);
	vboxPrincipal.pack_start (hboxLVGCode,false,false);
	vboxPrincipal.pack_start (hboxVoteCode,false,false);

	vboxPrincipal.set_spacing(10);
	vboxPrincipal.set_homogeneous(false);

	if(showButtons)
	{
		vboxPrincipal.pack_start (labelMessage,Gtk::PACK_SHRINK);
		vboxPrincipal.pack_start (hbuttonbox,Gtk::PACK_SHRINK);
	}

	HButtonBox* btnBox = NULL;

	if(useNewVoteRecovery)
	{
		buttonCheck = manage(new Smartmatic::GUI::Widgets::SmartmaticButton("&Check"));
		buttonCheck->signal_clicked().connect(sigc::mem_fun(*this, &RecoveryCardGeneratorWidget::on_buttonCheck_clicked));
		buttonCheck->show_all_children();
		buttonCheck->set_size_request(150, 40);
		buttonCheck->SetButtonType(Smartmatic::GUI::Widgets::SmartmaticButton::Ok);
		buttonCheck->WidgetsPosition(0,5,0);

		btnBox = manage(new HButtonBox());
		btnBox->set_layout(BUTTONBOX_CENTER);
		btnBox->pack_start(*buttonCheck, false, false);
	}

	vboxPrincipal.show_all_children ();
	vboxPrincipal.set_size_request (-1,350);
	vboxPrincipal.set_visible (true);
	
	pack_start(vboxPrincipal,false,false);
	if(useNewVoteRecovery)
		pack_end(*btnBox, false, false, 8);
	show_all_children ();
	set_visible (true);


	votingDeviceWrapper = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice();
	electionWrapper = MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection();
	voteRecovery = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVoteRecovery();

	dummyLVG = Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode();

    std::string currentLanguageCode;
	std::string	currentCountryCode;

	Smartmatic::SAES::Voting::SetLanguageFunctionality::getCurrentLanguageCountry ( currentLanguageCode, currentCountryCode );
	std::transform(currentLanguageCode.begin(), currentLanguageCode.end(),currentLanguageCode.begin(), ::tolower);
	std::transform(currentCountryCode.begin(), currentCountryCode.end(),currentCountryCode.begin(), ::toupper);

	langCode = currentLanguageCode + "-" + currentCountryCode;
}

RecoveryCardGeneratorWidget::~RecoveryCardGeneratorWidget()
{
	DeleteHBox();
}

void RecoveryCardGeneratorWidget::CleanImages()
{
	for(unsigned int i = 0; i < hboxMap.size(); i++)
	{
		ChangeImageState(*imageMap[i], noneImage);
	}

	ChangeImageState(lvgCodeImage, noneImage);
	ChangeImageState(voteCodeImage, noneImage);
}

void RecoveryCardGeneratorWidget::CheckAllFields()
{
	logger->Debug("Start check all fields");

	checkIsOk = false;
	std::map<std::string, std::string> recoverySelections;
	CleanImages();

	string voteCode = getVoteCode();
	string lvgCode = entryLVGCode.get_text();

	if(lvgCode == dummyLVG && !voteCode.empty())
	{
		ChangeImageState(lvgCodeImage, goodImage);
		CreateSuperNullVote(voteCode);
	}
	else if(!votingDeviceWrapper->IsLogicalVoterGroupPresent(lvgCode))
	{
		ChangeImageState(lvgCodeImage, badImage);
		entryLVGCode.grab_focus();
		statusRecovery = _("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CheckTheRedError");
		checkIsOk = false;
	}
	else
	{
		ChangeImageState(lvgCodeImage, goodImage);
		int totalContest = hboxMap.size();

		bool allGood = true;
		bool focusGrabbed = false;

		for(int i = 0; i < totalContest; i++)
		{
			string contesCode = contestCodeMap[i];
			string entryCode = entryMap[i]->get_text();

			try
			{
				bool codeIsValid = voteRecovery->IsCodeValid(contesCode, entryCode);

				if(codeIsValid)
				{
					ChangeImageState(*imageMap[i], goodImage);
				}
				else
				{
					ChangeImageState(*imageMap[i], badImage);
					if(!focusGrabbed)
					{
						entryMap[i]->grab_focus();
						focusGrabbed = true;
					}
					allGood = false;
				}
			}
			catch(...)
			{
				std::stringstream ss;
				ss<<__func__<< " "<<__LINE__<<"  EXCEPTION - voteRecovery->IsCodeValid";
				logger->Debug(ss.str());

				ChangeImageState(*imageMap[i], badImage);
				if(!focusGrabbed)
				{
					entryMap[i]->grab_focus();
					focusGrabbed = true;
				}
				allGood = false;
			}

			recoverySelections[contesCode] = entryCode;
		}

		if(allGood && !voteCode.empty())
		{
			voteRecovery->RecoveryToLogical(recoverySelections, voteRecovered);
			voteRecovered.setCode(voteCode);
			voteRecovered.setLogicalVoterGroup(lvgCode);
			voteRecovered.setVotingDeviceCode(MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice().getCode());
			voteRecovered.setLan_code(langCode);
			voteRecovered.setMode(Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R);
			checkIsOk = ValidateRecoveredVote();
		}
		else
			statusRecovery = _("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CheckTheRedError");

		CheckIfVoteAlreadyRecovered(voteCode);
	}

	logger->Debug("End check all fields - " + std::string(checkIsOk ? "success":"error"));
}

void RecoveryCardGeneratorWidget::on_buttonCheck_clicked()
{
	CheckAllFields();
}

void RecoveryCardGeneratorWidget::CreateSuperNullVote(std::string voteCode)
{
	try
	{
		MachineOperationManager::getInstance()->getVotingExperienceController()->sendBlankVoteResponse();

		Smartmatic::SAES::Voting::Vote::Vote * vote = MachineOperationManager::getInstance()->getVotingExperienceController()->getVote();

		if (vote)
		{
			voteRecovered = *vote;
		}

		voteRecovered.setLan_code(langCode);
		voteRecovered.setMode(Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R);
		voteRecovered.setCode(voteCode);
		voteRecovered.setLogicalVoterGroup(dummyLVG);
		voteRecovered.setVotingDeviceCode(MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice().getCode());

		//Vote::Vote::SSequence& sseq(voteRecovered.getSelections());
		//Smartmatic::SAES::Voting::Vote::Selection selection;

		//selection.setContest(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getContestCode());
		//sseq.push_back(selection);

		//Smartmatic::SAES::Voting::Vote::Selection::BSequence & bseq (selection.getBallotOptions());
		//bseq.push_back(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getBallotOptionCode());

		if(Smartmatic::SAES::Voting::Vote::VoteWrapper::validateVoteCode(voteRecovered))
		{
			ChangeImageState(voteCodeImage, goodImage);
			checkIsOk = true;
		}
		else
		{
			ChangeImageState(voteCodeImage, badImage);
			entryVoteCode.grab_focus();
			statusRecovery = _("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CheckTheRedError");
		}
	}
	catch(...)
	{
		std::stringstream ss;
		ss<<__func__<< " "<<__LINE__<<" EXCEPTION - VotingExperienceController()->getVote()";
		logger->Debug(ss.str());
		ChangeImageState(voteCodeImage, badImage);
		entryVoteCode.grab_focus();
	}

	CheckIfVoteAlreadyRecovered(voteCode);
}

bool RecoveryCardGeneratorWidget::ValidateRecoveredVote()
{
	try
	{
		if(Smartmatic::SAES::Voting::Vote::VoteWrapper::validateVote(MachineOperationManager::getInstance()->getElectoralConfiguration(),
				voteRecovered))
		{
			ChangeImageState(voteCodeImage, goodImage);
			checkIsOk = true;
		}
		else
		{
			ChangeImageState(voteCodeImage, badImage);
			entryVoteCode.grab_focus();
			checkIsOk = false;
		}
	}
	catch(...)
	{
		std::stringstream ss;
		ss<<__func__<< " "<<__LINE__<< " EXCEPTION - VoteWrapper::validateVote ";
		logger->Debug(ss.str());
		ChangeImageState(voteCodeImage, badImage);
		entryVoteCode.grab_focus();
		checkIsOk = false;
	}

	return checkIsOk;
}

bool RecoveryCardGeneratorWidget::on_entryVoteCode_key_pressed(GdkEventKey* event)
{
	if((int)event->keyval == enterKey && !entryMap.empty())
	{
		fieldIndex = 0;
		entryMap[0]->grab_focus();
	}

	return false;
}

bool RecoveryCardGeneratorWidget::on_entryLVGCode_lost_focus(GdkEventFocus *focus)
{
	GdkEventKey event;
	event.keyval = enterKey;
	on_entryLVGCode_key_pressed(&event);

	return true;
}

bool RecoveryCardGeneratorWidget::on_entryLVGCode_key_pressed(GdkEventKey* event)
{
	if((int)event->keyval == enterKey)
	{
		DeleteHBox();

		if(votingDeviceWrapper->IsLogicalVoterGroupPresent(entryLVGCode.get_text()))
		{
			try
			{
				CreateEntries();
				entryVoteCode.grab_focus();
				ChangeImageState(lvgCodeImage, goodImage);
			}
			catch(...)
			{
				entryLVGCode.set_text("");
				ChangeImageState(lvgCodeImage, badImage);
			}
		}
		else if(dummyLVG == entryLVGCode.get_text())
		{
			entryVoteCode.grab_focus();
			ChangeImageState(lvgCodeImage, goodImage);
		}
		else
		{
			entryLVGCode.set_text("");
			ChangeImageState(lvgCodeImage, badImage);
		}
	}
	ChangeImageState(voteCodeImage, noneImage);

	return false;
}

void RecoveryCardGeneratorWidget::ChangeImageState(Gtk::Image& image, std::string state)
{
	image.set(Gdk::PixbufAnimation::create_from_file(state));
}

void RecoveryCardGeneratorWidget::DeleteHBox()
{
	for(hboxMapIter = hboxMap.begin(); hboxMapIter != hboxMap.end(); hboxMapIter++)
	{
		if(hboxMapIter->second)
			delete hboxMapIter->second;
	}

	hboxMap.clear();
	entryMap.clear();
	imageMap.clear();
	contestCodeMap.clear();
}

void RecoveryCardGeneratorWidget::CreateEntries()
{
	Logical_voter_group lvg = votingDeviceWrapper->getLogicalVoterGroup( votingDeviceWrapper->getFirstVotingDevice(), entryLVGCode.get_text());
	string contestGroupCode = lvg.getContest_group_code();

	list<Contest> contestList;
	list<Contest>::iterator iter;

	electionWrapper->getContestOrderByContestClassByContestGroup (contestGroupCode, contestList);

	fieldIndex = contestList.size();

	int i = 0;
	for(iter = contestList.begin(); iter != contestList.end();iter++)
	{
        contestCodeMap[i] = iter->getCode();

        Contest_class contestClass = electionWrapper->getContestClass(iter->getContest_class_code());

		Glib::ustring contestClassName = ElectionStringResourcesManager::Current()->getResource(contestClass.getName_key());
		Glib::ustring contestClassDescription = ElectionStringResourcesManager::Current()->getResource(contestClass.getDescription_key());
		Glib::ustring contestTitle = ElectionStringResourcesManager::Current()->getResource(iter->getTitle_key());
		Glib::ustring contestAbstract = ElectionStringResourcesManager::Current()->getResource(iter->getAbstract_key());
		Glib::ustring contestHelp = ElectionStringResourcesManager::Current()->getResource(iter->getHelp_key());

		string format =  _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.FormatRecoveryLabel");

		Glib::ustring newFormat = Glib::ustring::compose(format, contestClassName, contestClassDescription,
		                                                 contestTitle, contestAbstract, contestHelp);

		newFormat.append(":");

		Label* label = manage(new Label(newFormat));
		label->set_alignment(0.0, 0.5);
		label->set_padding(10, 0);
		label->set_size_request(140, -1);
		label->set_line_wrap(true);
		label->modify_font(fontLabels);

		labelMap[i] = label;

		Smartmatic::GUI::Widgets::SmartmaticEntry* entry = manage(new Smartmatic::GUI::Widgets::SmartmaticEntry());
		entry->set_size_request(180,-1);
		entry->signal_key_press_event().connect(sigc::mem_fun(*this,&RecoveryCardGeneratorWidget::on_contestEntry_key_pressed),false);
		entry->signal_grab_focus().connect(sigc::bind<int>(sigc::mem_fun(*this,&RecoveryCardGeneratorWidget::on_contestEntry_focus_grabbed), i));

		entryMap[i] = entry;

		Image* image = manage(new Image());
		image->set(Gdk::PixbufAnimation::create_from_file(noneImage));

		imageMap[i] = image;

		HBox* hbox = new HBox();
		hbox->pack_start(*label);//, Gtk::PACK_SHRINK);
		hbox->pack_start(*entry, Gtk::PACK_SHRINK, 5);
		hbox->pack_start(*image, Gtk::PACK_SHRINK, 5);

		hboxMap[i] = hbox;

		vboxPrincipal.pack_start(*hbox, false, false);

		i++;
	}

	vboxPrincipal.show_all_children();
}


bool RecoveryCardGeneratorWidget::on_contestEntry_lost_focus(GdkEventFocus *focus)
{
	GdkEventKey event;
	event.keyval = enterKey;
	on_contestEntry_key_pressed(&event);

	return true;
}

void RecoveryCardGeneratorWidget::on_contestEntry_focus_grabbed(int index)
{
	fieldIndex = index;
}

bool RecoveryCardGeneratorWidget::on_contestEntry_key_pressed(GdkEventKey* event)
{
	if((int)event->keyval == enterKey)
	{
		if(fieldIndex < (int)(hboxMap.size() - 1))
		{
			fieldIndex++;
			entryMap[fieldIndex]->grab_focus();
		}
		else
			buttonCheck->grab_focus();
	}

	return false;
}


void RecoveryCardGeneratorWidget::Initialize()
{
	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageInitial"));

	connOk = okButton.signal_clicked().connect( sigc::mem_fun(this, &RecoveryCardGeneratorWidget::on_buttonOk_clicked));
	connCancel = cancelButton.signal_clicked().connect( sigc::mem_fun(this, &RecoveryCardGeneratorWidget::on_buttonCancel_clicked));

	entryVoteCode.set_text ("");
	entryLVGCode.set_text ("");
}

void RecoveryCardGeneratorWidget::CleanFields()
{
	entryVoteCode.set_text ("");
	entryLVGCode.set_text ("");
	ChangeImageState(lvgCodeImage, noneImage);
	ChangeImageState(voteCodeImage, noneImage);
	DeleteHBox();
}

void RecoveryCardGeneratorWidget::Dispose()
{
	connRefresh.disconnect();
	connOk.disconnect();
	connCancel.disconnect();
}

std::string RecoveryCardGeneratorWidget::CheckFields()
{
	std::string info;
	info.clear();

	if(entryLVGCode.get_text().compare("")==0)
	{
		info = _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageLVGEmpty");
	}
	else if(entryVoteCode.get_text().compare("")==0)
	{
		info = _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageVoteEmpty");
	}
	else
	{
		Smartmatic::SAES::Voting::ElectoralConfiguration *elecConf = MachineOperationManager::getInstance()->getElectoralConfiguration();
		Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper *votingDeviceWrapper = elecConf->getVotingDevice();

		//The logical voter group must match the configuration
		std::string testingLVG = entryLVGCode.get_text();

		if( testingLVG != dummyLVG && votingDeviceWrapper->IsLogicalVoterGroupPresent(testingLVG) == false)
		{
			info = _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageLVGInvalid");
			logger->Debug("Checksum Format failed");
		}

		//Validate code
		std::string voteCode = getVoteCode();

		if( info.size() == 0)
		{
			if(!Smartmatic::SAES::Voting::Vote::VoteCode::validateCode(voteCode))
			{
				info = _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageVoteCodeInvalid");
				logger->Debug("Vote code Failed");
			}
		}

		// The vote code should not be already used, check with vote statistic. Place this in a configuration parameter whether the machine allow this case.
		if( info.size() == 0)
		{
			if(CheckIfVoteAlreadyRecovered(voteCode))
			{
				info = _("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.MessageVoteWasConsolidated");
			}
		}
	}

	return info;
}

Smartmatic::SAES::Voting::Vote::Vote RecoveryCardGeneratorWidget::GetVote()
{
	return voteRecovered;
}

RecoveryCardInfo RecoveryCardGeneratorWidget::GetFields()
{
	RecoveryCardInfo recoveryInfo(getVoteCode(),entryLVGCode.get_text());
	return recoveryInfo;
} 

void RecoveryCardGeneratorWidget::on_buttonOk_clicked()
{
	std::string info = CheckFields();
	if(info.compare("")!=0)
	{
		labelMessage.set_label(info);
	}
	else
	{
		if(waitForCardToRegister)
		{
			labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.RecoveryCardGeneratorWidget.GeneratingCard"));
			sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
				   &RecoveryCardGeneratorWidget::Refresh), 0);
			connRefresh = Glib::signal_timeout().connect(my_slot,300);
		}
	}
}

std::string RecoveryCardGeneratorWidget::checkNewRecovery()
{
	checkIsOk = false;

	statusRecovery = "";

	on_buttonCheck_clicked();

	return statusRecovery;
}

bool RecoveryCardGeneratorWidget::Refresh(int time_num)
{
	RecoveryCardInfo recoveryInfo(getVoteCode(),entryLVGCode.get_text());
	signalOk_detected.emit(recoveryInfo);
	return false;
}

void RecoveryCardGeneratorWidget::on_buttonCancel_clicked()
{
	checkIsOk = false;
	signalCancel_detected.emit();
}

bool RecoveryCardGeneratorWidget::CheckIfVoteAlreadyRecovered(std::string voteCode)
{
	bool voteAlreadyRecovered = false;

	if(!Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getAllowRecoveryCardGenerationOfConsolidatedVotes())
	{
		Smartmatic::SAES::Voting::PBReports::VoteStatisticsWrapper* voteStats = MachineOperationManager::getInstance()->getVoteStatistics();

		if(voteStats->IsVoteProcessed(voteCode))
		{
			voteAlreadyRecovered = true;
			logger->Debug("Vote Already processed");
		}
	}

	if(voteAlreadyRecovered || voteCode.empty())
	{
		checkIsOk = false;
		ChangeImageState(voteCodeImage, badImage);
		entryVoteCode.grab_focus();
		statusRecovery = _("Smartmatic.SAES.GUI.Functionality.RecoveryCardGeneratorFunctionality.CheckTheRedError");
	}

	return voteAlreadyRecovered;
}


std::string RecoveryCardGeneratorWidget::getVoteCode()
{
	std::string voteCodeInput = entryVoteCode.get_text();
	std::string voteCodeOutput = voteCodeInput;

	Smartmatic::SAES::Voting::Vote::VoteCode::decode( voteCodeInput );
	Smartmatic::SAES::Voting::Vote::VoteCode::encode( voteCodeInput );

	if (voteCodeOutput == voteCodeInput)
	{
		Smartmatic::SAES::Voting::Vote::VoteCode::decode( voteCodeOutput );
	}
	else
	{
		voteCodeOutput = "";
	}

	return voteCodeOutput;
}

bool RecoveryCardGeneratorWidget::isValidate()
{
	CheckAllFields();
	return checkIsOk;
}
