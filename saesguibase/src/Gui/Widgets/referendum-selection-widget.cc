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
/**
 * @file ballot-option-selection-widget.cc
 * @brief BallotOptionSelectionWidget body
 */

#include "referendum-selection-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/ElectoralConfiguration.hxx"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/party-widget.h>
#include <Operation/MachineOperationManager.hxx>
#include "Functionalities/time-functionality.h"
#include "Configuration/label-configuration.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/Election/ElectionWrapper.hxx"
#include <Operation/Voting/VotingOperation.hxx>
#include <Operation/FormatLabel.hxx>

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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation;

ReferendumSelectionWidget::ReferendumSelectionWidget(Contest& contest)
{
	showBackButton = false;
	m_widgetEnabled = true;
	SoundBallotS = SAESGUIConfigurationManager::Current()->getBallotOptionSelectSound();

	config = SAESGUIConfigurationManager::Current()->GetReferendumConfiguration();

	this->contest = contest;
	oneSelected = false;
	
	clearButton = manage(new SmartmaticButton());
	clearButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.ClearSelection"));
	clearButton->WidgetsPosition(5,0,0);
	clearButton->show_all_children();
	clearButton->set_no_show_all();
	clearButton->SetSound (SoundBallotS);

	acceptButton = manage(new SmartmaticButton());
	acceptButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.AcceptSelection"));
	acceptButton->WidgetsPosition(5,0,0);
	acceptButton->show_all_children();
	acceptButton->set_no_show_all();
	acceptButton->SetSound (SoundBallotS);

	backButton = manage(new SmartmaticButton());
	backButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.Back"));
	backButton->WidgetsPosition(5,0,0);
	backButton->set_no_show_all();
	backButton->show();
	backButton->SetSound (SoundBallotS);

	bottomBox = manage(new HBox(true, 0));
	bottomBox->show();
	bottomBox->pack_start(*backButton, true, true);
	bottomBox->pack_start(*clearButton, true, true);
	bottomBox->pack_start(*acceptButton, true, true);

	bottomHeigth = config.getFrameBottomHeight();
	bottomFrame = manage (new Frame());
	bottomFrame->show();
	bottomFrame->add(*bottomBox);
	bottomFrame->set_size_request(-1, bottomHeigth);

	string question = ComposeQuestionText();

	Label* labelQuestion = manage(new Label());
	labelQuestion->set_size_request(config.getQuestionWidth(),config.getQuestionHeight());
	labelQuestion->set_text(question);

	static Smartmatic::GUI::Configuration::LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->GetReferendumQuestionLabelConfiguration();

	LabelConfiguration::SetLabelConfiguration(labelQuestion, labelConf);

	labelEventBox = manage(new EventBox());
	labelEventBox->set_name("referendumquestioneventbox");
	labelEventBox->add(*labelQuestion);

	internalBox = manage(new VBox(false));
	internalBox->pack_start(*labelEventBox,false,false);

	clientAreaFrame = manage(new Frame());
	clientAreaFrame->add(*internalBox);
	clientAreaFrame->show();
	
	externalBox = manage(new VBox());
	externalBox->show();
	externalBox->pack_start(*clientAreaFrame);
	externalBox->pack_start(*bottomFrame, false, false);
	
	if (SAESGUIConfigurationManager::Current()->GetReferendumConfiguration().getEnableClick())
	{
		clearButton->signal_clicked().connect(sigc::mem_fun(this,&ReferendumSelectionWidget::on_clearButton_clicked));
		acceptButton->signal_clicked().connect(sigc::mem_fun(this,&ReferendumSelectionWidget::on_acceptButton_clicked));
		backButton->signal_clicked().connect(sigc::mem_fun(this,&ReferendumSelectionWidget::on_backButton_clicked));
	}

	refresh();

	setWidget(externalBox);

	setBottom(false);
	setTitle(true);
}

ReferendumSelectionWidget::~ReferendumSelectionWidget()
{

}

void ReferendumSelectionWidget::refresh()
{
	switch(VotingOperation::getVoteMode())
	{
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
		backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
		backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
		backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
		break;
	}

	RefreshLabels();
}

void ReferendumSelectionWidget::RefreshLabels()
{
	backButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.Back"));
}

std::string ReferendumSelectionWidget::ComposeQuestionText()
{
	Contest_class contestClass =
			Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection()->getContestClass(contest.getContest_class_code());

	Glib::ustring contestClassName = ElectionStringResourcesManager::Current()->getResource(contestClass.getName_key());
	Glib::ustring contestClassDescription = ElectionStringResourcesManager::Current()->getResource(contestClass.getDescription_key());
	Glib::ustring contestTitle = ElectionStringResourcesManager::Current()->getResource(contest.getTitle_key());
	Glib::ustring contestAbstract = ElectionStringResourcesManager::Current()->getResource(contest.getAbstract_key());
	Glib::ustring contestHelp = ElectionStringResourcesManager::Current()->getResource(contest.getHelp_key());

	string format =  _("Smartmatic.SAES.GUI.Widgets.ReferendumSelectionWidget.QuestionPlaceHolder");

	Glib::ustring newFormat = Glib::ustring::compose(format, contestClassName, contestClassDescription,
													 contestTitle, contestAbstract, contestHelp);

	return newFormat;
}

void ReferendumSelectionWidget::Initialize(list<Eligible_option> & principalBallotList,
		Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir)
{
	Display_info disInfo = contest.getDisplay_info();

	disInfo.getImage_width_height_relation();
	
	int totalW, totalH;
	get_size_request(totalW, totalH);

	totalH -= bottomHeigth;
	totalW -= 11;

	bool displayVertical = config.getButtonsVertical();

	if(displayVertical)
	{
		ballotsBox = manage(new VBox());
	}
	else
	{
		ballotsBox = manage(new HBox());
	}

	ballotsBox->show();
	ballotsBox->set_spacing(config.getBallotBoxSpacing());

	int w = config.getBallotWidth();
	int h = config.getBallotHeight();

	for(it = principalBallotList.begin(); it != principalBallotList.end(); it++)
	{
		ReferendumWidget* referendumWidget = manage(new ReferendumWidget(*it, saesDir));
		referendumWidget->set_size_request(w, h);

		if (SAESGUIConfigurationManager::Current()->GetReferendumConfiguration().getEnableClick())
		{
			referendumWidget->signal_ballot_clicked().connect(sigc::mem_fun(*this, &ReferendumSelectionWidget::on_ballot_option_clicked));
		}

		referendumWidget->show();

		referendumWidgetList.push_back(referendumWidget);

		ballotsBox->pack_start(*referendumWidget, false, false);
	}
	
	if(config.getShowNullOption())
	{
		PartyWidget* partyWidget = manage(new PartyWidget(_("Smartmatic.SAES.GUI.Widgets.ReferendumSelectionWidget.NullSelection"), w, h));

		if (SAESGUIConfigurationManager::Current()->GetReferendumConfiguration().getEnableClick())
		{
			partyWidget->signal_party_null_clicked().connect(sigc::mem_fun(this,&ReferendumSelectionWidget::on_nullOption_clicked));
		}

		partyWidget->show();

		ballotsBox->pack_start(*partyWidget, false, false);
	}

	int top = config.getBallotBoxTopPadding();
	int left = config.getBallotBoxLeftPadding();

	Alignment* align = manage(new Alignment());
	align->set_padding(top,0,left,0);
	align->set(0.5,0.5,0,0);

	align->add(*ballotsBox);

	internalBox->pack_start(*align, false, false);

	show();
	show_all_children();
}

void ReferendumSelectionWidget::on_ballot_option_clicked(string ballotOptionCode, bool isSelected)
{
	oneSelected = isSelected;

	std::list<ReferendumWidget*>::iterator iter;

	for(iter = referendumWidgetList.begin(); iter != referendumWidgetList.end(); iter++)
	{
		if(ballotOptionCode != (*iter)->GetBallotOptionCode())
		{
			(*iter)->SetSelection(false, false);
			m_ballotOption_clicked.emit((*iter)->GetBallotOptionCode(), false);
		}
	}

	m_ballotOption_clicked.emit(ballotOptionCode, isSelected);

	if(oneSelected)
	{
		clearButton->show();
		acceptButton->show();
		backButton->hide();
	}
	else
	{
		clearButton->hide();
		acceptButton->hide();

		if(showBackButton)
			backButton->show();
	}
}

ReferendumSelectionWidget::type_back_clicked ReferendumSelectionWidget::back_clicked()
{
	return m_back_clicked;
}

ReferendumSelectionWidget::type_ballotOption_clicked ReferendumSelectionWidget::ballotOption_clicked()
{
	return m_ballotOption_clicked;
}

ReferendumSelectionWidget::type_back_clicked ReferendumSelectionWidget::accept_clicked()
{
	return m_accept_clicked;
}

Smartmatic::SAES::Voting::Election::Contest ReferendumSelectionWidget::getContest()
{
	return contest;
}

void ReferendumSelectionWidget::on_nullOption_clicked()
{
	on_clearButton_clicked();
	m_null_clicked.emit();
}

void ReferendumSelectionWidget::on_clearButton_clicked()
{
	std::list<ReferendumWidget*>::iterator iter;

	for(iter = referendumWidgetList.begin(); iter != referendumWidgetList.end(); iter++)
	{
		(*iter)->SetSelection(false, true);
	}

	clearButton->hide();
	acceptButton->hide();

	if(showBackButton)
		backButton->show();
}

void ReferendumSelectionWidget::on_acceptButton_clicked()
{
	m_accept_clicked.emit();
}

void ReferendumSelectionWidget::on_backButton_clicked()
{
	m_back_clicked.emit();
}

ReferendumSelectionWidget::type_back_clicked ReferendumSelectionWidget::null_clicked()
{
	return m_null_clicked;
}

void ReferendumSelectionWidget::SetBackButton(bool show)
{
	this->showBackButton = show;
	if(backButton)
	{
		if(show)
			backButton->show();
		else
		{
			backButton->set_no_show_all();
			backButton->hide();
		}
	}
}

Smartmatic::GUI::Configuration::LabelConfiguration ReferendumSelectionWidget::getTitleLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetReferendumHeaderLabelConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration ReferendumSelectionWidget::getBottomLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetReferendumBottomLabelConfiguration();
}

std::string ReferendumSelectionWidget::getTitleText()
{
	std::string title;

	Glib::ustring s_referendumHeaderFormat;
	Glib::ustring s_referendumHeaderFormatNoQuestion;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat");
			s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat.Demo");
			s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_referendumHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormat.Recovery");
			s_referendumHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumHeaderFormatNoQuestion.Recovery");
			break;
	}

	if(showBackButton)
	{
		title = FormatLabel::contestText(contest, s_referendumHeaderFormat);
	}
	else
	{
		title = FormatLabel::contestText(contest, s_referendumHeaderFormatNoQuestion);
	}

	FormatLabel::checkComposeString(title);

	return title;
}

std::string ReferendumSelectionWidget::getBottomText()
{
	std::string bottom;

	Glib::ustring s_referendumFooterFormat;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_referendumFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReferendumFooterFormat.Recovery");
			break;
	}

	bottom = FormatLabel::contestText(contest, s_referendumFooterFormat);

	FormatLabel::checkComposeString(bottom);

	return bottom;
}

void ReferendumSelectionWidget::SetWidgetEnabled(bool enabled)
{
	m_widgetEnabled = enabled;
}
