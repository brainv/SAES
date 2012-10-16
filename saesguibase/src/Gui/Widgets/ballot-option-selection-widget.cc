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

#include "ballot-option-selection-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/ElectoralConfiguration.hxx"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Resources/election-string-resources-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include "Functionalities/time-functionality.h"
#include "FactoryMethodWidget.hxx"
#include "AbstractFactoryWidget.hxx"
#include "ballot-option-widget.h"
#include "complex-ballot-option-widget.h"
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
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation;

BallotOptionSelectionWidget::BallotOptionSelectionWidget(Contest& contest)
{
	m_widgetEnabled = true;

	tallyPosition = 0;
	ballotOptionTableWidget = NULL;
	ballotOptionButtonWidget = NULL;
	showBackButton = false;

	SoundBallotS=SAESGUIConfigurationManager::Current()->getBallotOptionSelectSound();

	static BallotOptionSelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();
	
	HideStandInLabelIfEmpty = config.getHideStandInLabelIfEmpty();

	this->contest = contest;
	this->ballotOptionListWidget = NULL;

	principalBallotsSelected = 0;
	standInBallotsSelected = 0;
	totalPrincipalBallots = 0;
	totalStandInBallots = 0;
	ballotOptionListWidget = NULL;
	selectedListColor.set_rgb(config.getListSelectedColor().getRed(), config.getListSelectedColor().getGreen(), config.getListSelectedColor().getBlue());
	unSelectedListColor.set_rgb(config.getListUnSelectedColor().getRed(), config.getListUnSelectedColor().getGreen(), config.getListUnSelectedColor().getBlue());
	StandInColor.set_rgb(config.getStandInColor().getRed(), config.getStandInColor().getGreen(), config.getStandInColor().getBlue());
	//standInEventBox->modify_bg(Gtk::STATE_NORMAL, StandInColor);

	headerHeigth = config.getFrameHeaderHeight();
	headerFrame = manage(new Frame());
	headerFrame->show();
	headerFrame->set_size_request(-1, headerHeigth);

	ballotOptionButtonWidget = FactoryMethodWidget::createBallotOptionButtonWidget();
	ballotOptionButtonWidget->update();

	ballotOptionTableWidget = AbstractFactoryWidget::createBallotOptionTableWidget();

	bottomHeigth = config.getFrameBottomHeight();
	bottomFrame = manage (new Frame());
	bottomFrame->show();
	bottomFrame->add(*ballotOptionButtonWidget);
	bottomFrame->set_size_request(-1, bottomHeigth);

	clientAreaFrame = manage(new Frame());
	clientAreaFrame->show();
	
	externalBox = manage(new VBox());
	externalBox->show();
	externalBox->pack_start(*headerFrame, false, false);
	externalBox->pack_start(*clientAreaFrame);
	externalBox->pack_start(*bottomFrame, false, false);
	
	add(*externalBox);
	show();

	if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
	{
		ballotOptionButtonWidget->getSignalClearButtonClicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_clearButton_clicked));
		ballotOptionButtonWidget->getSignalAcceptButtonClicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_acceptButton_clicked));
		ballotOptionButtonWidget->getSignalBackButtonClicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_backButton_clicked));
	}

	setBottom(SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBallotOptionFooter());
	setTitle(true);
}

void BallotOptionSelectionWidget::RefreshLabels()
{
	ballotOptionTableWidget->update();
	ballotOptionButtonWidget->update();
}

void BallotOptionSelectionWidget::ClearVisualSelection()
{
	for(itWidget = ballotOptionTableWidget->getPrincipalList().begin(); itWidget != ballotOptionTableWidget->getPrincipalList().end(); itWidget++)
		if(*itWidget)
			(*itWidget)->SetSelection(false);

	principalBallotsSelected = 0;
	
	ballotOptionListWidget->SetSelection(false);

	for(itWidget = ballotOptionTableWidget->getStandInList().begin(); itWidget != ballotOptionTableWidget->getStandInList().end(); itWidget++)
		if(*itWidget)
			(*itWidget)->SetSelection(false);

	standInBallotsSelected = 0;

	CheckButtonsLogic();
}

int BallotOptionSelectionWidget::GetTotalBallotsDisplayed()
{
	return totalPrincipalBallots + totalStandInBallots;
}

void BallotOptionSelectionWidget::SetWidgetEnabled(bool enabled)
{
	m_widgetEnabled = enabled;
}

void BallotOptionSelectionWidget::Initialize(list<Eligible_option> & ballotList,
                                             list<Eligible_option> & principalBallotList,
                                             list<Eligible_option> & standInBallotList,
                                             Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir)
{
	static BallotOptionSelectionConfiguration config = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();

	totalPrincipalBallots = (int)principalBallotList.size();
	totalStandInBallots = (int)standInBallotList.size();

	clientAreaFrame->add(*ballotOptionTableWidget);

	if (ballotList.size() > 0)
	{
        ballotOptionListWidget = manage(new ComplexBallotOptionWidget((*(ballotList.begin())), saesDir, true));
        if(config.getShowImageInList())
        {
            static float listRelation = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getImageRelation();
            ballotOptionListWidget->ForceShowImage(headerHeigth, listRelation);
        }
        if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
        {
        	ballotOptionListWidget->signal_ballot_clicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_ballotList_clicked));
        }
        ballotOptionListWidget->show();
        headerFrame->add(*ballotOptionListWidget);

        tallyPosition = ballotList.begin()->getBallot_options().getBallot_option().begin()->getTally_position();
	}

	//ballot_option principal
	for(it = principalBallotList.begin(); it != principalBallotList.end(); it++)
	{
        BallotOptionWidget* ballot = manage(new BallotOptionWidget(*it, saesDir, true, 100, 10));
        if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
        {
        	ballot->signal_ballot_clicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_ballot_option_clicked));
        }
        ballotOptionTableWidget->addPrincipal(ballot);
	}

	//ballot_option substitute
	for(it = standInBallotList.begin(); it != standInBallotList.end(); it++)
	{
		BallotOptionWidget* ballot = manage(new BallotOptionWidget(*it, saesDir, false, 100, 10));
		if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
		{
			ballot->signal_ballot_clicked().connect(sigc::mem_fun(this,&BallotOptionSelectionWidget::on_ballot_option_clicked));
		}
        ballotOptionTableWidget->addStandIn(ballot);
	}

	int totalW, totalH;
	get_size_request(totalW, totalH);

	ballotOptionTableWidget->fill(contest, totalW, totalH);

	show();
}

void BallotOptionSelectionWidget::SetBallots(list<Ballot_option> & ballotList)
{
	list<Ballot_option>::iterator iterBallotList;
	for(iterBallotList = ballotList.begin(); iterBallotList != ballotList.end(); iterBallotList++)
	{
		Ballot_option ballot = *iterBallotList;
		
		if(ballot.getCategory() == Category::ELECTION_PRINCIPAL)
			for(itWidget = ballotOptionTableWidget->getPrincipalList().begin(); itWidget != ballotOptionTableWidget->getPrincipalList().end(); itWidget++)
            {
                if((*itWidget)->GetBallotOptionCode() == ballot.getCode())
				{
					(*itWidget)->SetSelection(true, true);
					break;
				}
				
                if(ballotOptionListWidget->GetBallotOptionCode() == ballot.getCode())
				{
					ballotOptionListWidget->SetSelection(true,true);					
				}
            }
		else
			for(itWidget = ballotOptionTableWidget->getStandInList().begin(); itWidget != ballotOptionTableWidget->getStandInList().end(); itWidget++)
            {
                if((*itWidget)->GetBallotOptionCode() == ballot.getCode())
				{
					(*itWidget)->SetSelection(true, true);
					break;
				}
             }
	}
	CheckButtonsLogic();
}

void BallotOptionSelectionWidget::on_ballotList_clicked(string ballotOptionCode, bool isSelected, bool isPrincipal)
{
	static BallotOptionSelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();
	
	if(m_widgetEnabled == false)
		return;

	if(!isSelected)
	{
		if(config.getOptionListLinked())
			ClearAllBallots(true, true);
	}
	else
	{
		if(config.getOptionListLinked())
		{
			SelectAllBallots(true, config.getSelectListImpliesSelectStandIn());
			ClearAllBallots(false, !config.getSelectListImpliesSelectStandIn());
		}
	}

	raise_option_clicked(ballotOptionCode, isSelected);
	CheckButtonsLogic();
}

void BallotOptionSelectionWidget::SelectAllBallots(bool principal, bool standIn)
{
	if(principal)
		for(itWidget = ballotOptionTableWidget->getPrincipalList().begin(); itWidget != ballotOptionTableWidget->getPrincipalList().end(); itWidget++)
			if(!(*itWidget)->IsSelected())
			{
				(*itWidget)->SetSelection(true);
				string s = (*itWidget)->GetBallotOptionCode();
				raise_option_clicked(s, true);
				principalBallotsSelected++;
			}

	if(standIn)
		for(itWidget = ballotOptionTableWidget->getStandInList().begin(); itWidget != ballotOptionTableWidget->getStandInList().end(); itWidget++)
			if(!(*itWidget)->IsSelected())
			{
				(*itWidget)->SetSelection(true);
				string s = (*itWidget)->GetBallotOptionCode();
				raise_option_clicked(s, true);
				standInBallotsSelected++;
			}
}

void BallotOptionSelectionWidget::refresh()
{
	RefreshLabels();
	CheckButtonsLogic();
}

void BallotOptionSelectionWidget::CheckButtonsLogic()
{
	static BallotOptionSelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();
	
	if(ballotOptionListWidget)
	{
		if(principalBallotsSelected + standInBallotsSelected > 0 || ballotOptionListWidget->IsSelected())
			ButtonsLogicShowHide(true, true, config.getAllowBackWithBallotSelected());
		else
			ButtonsLogicShowHide(false, false, true);
	}
}

void BallotOptionSelectionWidget::ButtonsLogicShowHide(bool clear, bool accept, bool back)
{
	ballotOptionButtonWidget->showButton(clear, accept, back);
	m_skipAcceptSignal = !accept;
}

void BallotOptionSelectionWidget::on_ballot_option_clicked(string ballotOptionCode, bool isSelected, bool isPrincipal)
{
	static BallotOptionSelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration();
	
	if(m_widgetEnabled == false)
			return;

	if(isSelected && isPrincipal)
		principalBallotsSelected++;
	else if(isSelected && !isPrincipal)
		standInBallotsSelected++;
	else if(!isSelected && isPrincipal)
		principalBallotsSelected--;
	else
		standInBallotsSelected--;

	if(config.getOptionListLinked())
	{
		if(ballotOptionListWidget->IsSelected())
			ballotOptionListWidget->SetSelection(false);
		else
		{
			if(isSelected && principalBallotsSelected == totalPrincipalBallots)
			{
				if(config.getSelectStandInImpliesSelectList())
				{
					if(standInBallotsSelected == totalStandInBallots)
						ballotOptionListWidget->SetSelection(true);
				}
				else
				{
					if(standInBallotsSelected == 0)
						ballotOptionListWidget->SetSelection(true);
				}
			}
		}
	}

	CheckButtonsLogic();
	raise_option_clicked(ballotOptionCode, isSelected);
}

void BallotOptionSelectionWidget::ClearAllBallots(bool principal, bool standIn)
{
	if(principal)
	{
		for(itWidget = ballotOptionTableWidget->getPrincipalList().begin(); itWidget != ballotOptionTableWidget->getPrincipalList().end(); itWidget++)
		{
			(*itWidget)->SetSelection(false);
			string s = (*itWidget)->GetBallotOptionCode();
			raise_option_clicked(s, false);
		}
		principalBallotsSelected = 0;

		ballotOptionListWidget->SetSelection(false);
		string s = ballotOptionListWidget->GetBallotOptionCode();
		raise_option_clicked(s, false);
	}

	if(standIn)
	{
		for(itWidget = ballotOptionTableWidget->getStandInList().begin(); itWidget != ballotOptionTableWidget->getStandInList().end(); itWidget++)
		{
			(*itWidget)->SetSelection(false);
			string s = (*itWidget)->GetBallotOptionCode();
			raise_option_clicked(s, false);
		}
		standInBallotsSelected = 0;
	}
}

void BallotOptionSelectionWidget::on_clearButton_clicked()
{
	if(m_widgetEnabled == false)
				return;

	ClearAllBallots(true, true);

	CheckButtonsLogic();
}

void BallotOptionSelectionWidget::on_acceptButton_clicked()
{
	if(m_widgetEnabled == false)
			return;

	if(m_skipAcceptSignal)
		return;

	if(m_accept_clicked.empty() == false)
		m_widgetEnabled = false;

	m_accept_clicked.emit();
}

void BallotOptionSelectionWidget::raise_option_clicked(std::string& optionCode, bool isSelected)
{
	m_ballotOption_clicked.emit(optionCode, isSelected);
}

void BallotOptionSelectionWidget::on_backButton_clicked()
{
	if(m_widgetEnabled == false)
				return;

	if(m_back_clicked.empty() == false)
		m_widgetEnabled = false;
	m_back_clicked.emit();
}

BallotOptionSelectionWidget::type_accept_clicked BallotOptionSelectionWidget::accept_clicked()
{
	return m_accept_clicked;
}

BallotOptionSelectionWidget::type_back_clicked BallotOptionSelectionWidget::back_clicked()
{
	return m_back_clicked;
}

BallotOptionSelectionWidget::type_ballotOption_clicked BallotOptionSelectionWidget::ballotOption_clicked()
{
	return m_ballotOption_clicked;
}

Smartmatic::SAES::Voting::Election::Contest BallotOptionSelectionWidget::getContest()
{
	return contest;
}

BallotOptionSelectionWidget::~BallotOptionSelectionWidget()
{
	this->remove();

	if (ballotOptionButtonWidget)
	{
		delete ballotOptionButtonWidget;
		ballotOptionButtonWidget = NULL;
	}
	if (ballotOptionTableWidget)
	{
		delete ballotOptionTableWidget;
		ballotOptionTableWidget = NULL;
	}
}

Smartmatic::GUI::Configuration::LabelConfiguration BallotOptionSelectionWidget::getTitleLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionWindowHeaderLabelConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration BallotOptionSelectionWidget::getBottomLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionWindowBottomLabelConfiguration();
}

std::string BallotOptionSelectionWidget::getTitleText()
{
	std::string title;

	Glib::ustring s_BallotHeaderFormat;
	Glib::ustring s_BallotHeaderFormatNoQuestion;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_BallotHeaderFormat =  _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat");
			s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_BallotHeaderFormat =  _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat.Demo");
			s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_BallotHeaderFormat =  _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormat.Recovery");
			s_BallotHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotHeaderFormatNoQuestion.Recovery");
			break;
	}

	if(showBackButton)
	{
		title = FormatLabel::contestText(contest, s_BallotHeaderFormat);
	}
	else
	{
		title = FormatLabel::contestText(contest, s_BallotHeaderFormatNoQuestion);
	}

	FormatLabel::checkComposeString(title);

	return title;
}

std::string BallotOptionSelectionWidget::getBottomText()
{
	std::string bottom;

	Glib::ustring s_BallotFooterFormat;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_BallotFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_BallotFooterFormat =_("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_BallotFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BallotFooterFormat.Recovery");
			break;
	}

	bottom = FormatLabel::contestText(contest, s_BallotFooterFormat);

	FormatLabel::checkComposeString(bottom);

	return bottom;
}
