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

#include "Gui/Widgets/Voting/question-selection-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/Voting/VotingOperation.hxx>

using namespace std;
using namespace Gtk;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

QuestionSelectionWidget::QuestionSelectionWidget(bool showConfirmation, bool buttonsVertical)
:SelectionWidgetBase()
{
	confirmationWidget = NULL;
	chooseDialogWidget = NULL;

	s_Question.clear();
	s_Header.clear();
	s_Footer.clear();
	s_HeaderConfirmation.clear();
	s_FooterConfirmation.clear();
	s_AcceptButton.clear();
	s_CancelButton.clear();
	s_AcceptConfirmation.clear();
	s_CancelConfirmation.clear();
	s_ReconfirmButtonText.clear();
	s_RetryButtonText.clear();
	
	this->showConfirmation = showConfirmation;
	this->buttonsVertical = buttonsVertical;
}

QuestionSelectionWidget::~QuestionSelectionWidget()
{
	remove();

	if(chooseDialogWidget)
	{
		delete chooseDialogWidget;
		chooseDialogWidget = NULL;
	}
	if(confirmationWidget)
	{
		delete confirmationWidget;
		confirmationWidget = NULL;
	}
}

void QuestionSelectionWidget::Initialize()
{
	SetStrings();

	confirmationWidget = new ConfirmationDialogWidget(s_Question, s_Header, s_Footer,
	                                                  s_AcceptButton, s_CancelButton,
	                                                  buttonsVertical, true);

	confirmationWidget->SetLabelConfiguration(centerlabelConf);

	if(showConfirmation)
	{
		confirmationWidget->SetLabelConfigurationReconfirmation(confirmLabelConf);

		confirmationWidget->SetReconfirmation(s_AcceptConfirmation, s_CancelConfirmation, 
		                                      s_HeaderConfirmation, s_FooterConfirmation,
		                                      s_ReconfirmButtonText, s_RetryButtonText);
	}

	chooseDialogWidget = new ChooseDialogWidget(confirmationWidget);
	chooseDialogWidget->on_accept_signal().connect(sigc::mem_fun(*this,&QuestionSelectionWidget::on_accept));
	chooseDialogWidget->on_cancel_signal().connect(sigc::mem_fun(*this,&QuestionSelectionWidget::on_cancel));

	chooseDialogWidget->SetLabelConfiguration(headerLabelConf, footerLabelConf);

	SetBaseButtons();

	mainContainer.add(*chooseDialogWidget);
	show_all_children();
}

void QuestionSelectionWidget::SetStrings(Glib::ustring s_Question, Glib::ustring s_Header, Glib::ustring s_Footer,
                                         Glib::ustring s_HeaderConfirmation, Glib::ustring s_FooterConfirmation,
										 Glib::ustring s_AcceptButton, Glib::ustring s_CancelButton,
										 Glib::ustring s_AcceptConfirmation, Glib::ustring s_CancelConfirmation,
										 Glib::ustring s_ReconfirmButtonText, Glib::ustring s_RetryButtonText)
{
	this->s_Question = s_Question;
	this->s_Header = s_Header;
	this->s_Footer = s_Footer;
	this->s_HeaderConfirmation = s_HeaderConfirmation;
	this->s_FooterConfirmation = s_FooterConfirmation;
	this->s_AcceptButton = s_AcceptButton;
	this->s_CancelButton = s_CancelButton;
	this->s_AcceptConfirmation =  s_AcceptConfirmation;
	this->s_CancelConfirmation = s_CancelConfirmation;
	this->s_ReconfirmButtonText = s_ReconfirmButtonText;
	this->s_RetryButtonText = s_RetryButtonText;
}

void QuestionSelectionWidget::SetLabelsConfiguration(LabelConfiguration headerLabelConf,
                                                     LabelConfiguration footerLabelConf,
                                                     LabelConfiguration centerlabelConf)
{
	this->headerLabelConf = headerLabelConf;
	this->footerLabelConf = footerLabelConf;
	this->centerlabelConf = centerlabelConf;
}

void QuestionSelectionWidget::SetLabelsConfiguration(LabelConfiguration headerLabelConf,
                                                     LabelConfiguration footerLabelConf,
                                                     LabelConfiguration centerlabelConf,
                                                     LabelConfiguration confirmLabelConf)
{
	this->headerLabelConf = headerLabelConf;
	this->footerLabelConf = footerLabelConf;
	this->centerlabelConf = centerlabelConf;
	this->confirmLabelConf = confirmLabelConf;
}

void QuestionSelectionWidget::SetBaseButtons()
{
	if(confirmationWidget)
	{
		switch(VotingOperation::getVoteMode())
		{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			confirmationWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			confirmationWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			confirmationWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			break;
		}
			
	}

	if(chooseDialogWidget)
	{
		switch(VotingOperation::getVoteMode())
		{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			chooseDialogWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			chooseDialogWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			chooseDialogWidget->SetBaseButtonsName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			break;
		}
	}
}

void QuestionSelectionWidget::SetStrings()
{

}
	
void QuestionSelectionWidget::SetLabelsConfiguration()
{

}

void QuestionSelectionWidget::on_accept()
{
	m_accept_signal.emit();
}

void QuestionSelectionWidget::on_cancel()
{
	m_cancel_signal.emit();
}

QuestionSelectionWidget::void_signal QuestionSelectionWidget::signal_accept()
{
	return m_accept_signal;
}

QuestionSelectionWidget::void_signal QuestionSelectionWidget::signal_cancel()
{
	return m_cancel_signal;
}
    
void QuestionSelectionWidget::refresh()
{
	SetStrings();
	
	if (confirmationWidget)
	{
		if(showConfirmation)
		{
			confirmationWidget->SetLabelConfigurationReconfirmation(confirmLabelConf);

			confirmationWidget->SetReconfirmation(s_AcceptConfirmation, s_CancelConfirmation, 
							      s_HeaderConfirmation, s_FooterConfirmation,
							      s_ReconfirmButtonText, s_RetryButtonText);
		}
		
		confirmationWidget->SetConfirmationText(s_Question);
		confirmationWidget->Refresh(s_AcceptButton, s_CancelButton);
		confirmationWidget->setHeaderTitle(s_Header);
		confirmationWidget->setFooterTitle(s_Footer);
	}
	
	if (chooseDialogWidget)
	{
		chooseDialogWidget->Refresh(s_Header, s_Footer);
	}
}
