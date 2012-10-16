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

#include "Gui/Widgets/Voting/super-null-selection-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/Voting/VotingOperation.hxx>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

SuperNullSelectionWidget::SuperNullSelectionWidget(bool showConfirmation, bool buttonsVertical)
:QuestionSelectionWidget(showConfirmation, buttonsVertical)
{
	SetStrings();
	SetLabelsConfiguration();
	Initialize();
}

SuperNullSelectionWidget::~SuperNullSelectionWidget()
{
	
}

void SuperNullSelectionWidget::SetStrings()
{
	switch(VotingOperation::getVoteMode())
	{
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
		s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteQuestion");
		s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeader");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooter");
		s_HeaderConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeaderConfirmation");
		s_FooterConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooterConfirmation");
		s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNullButton");
		s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNormalButton");
		s_AcceptConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteConfirmation");
		s_CancelConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NormalVoteConfirmation");
		s_ReconfirmButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReconfirmButtonText");
		s_RetryButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.RetryButtonText");
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
		s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteQuestion.Demo");
		s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeader.Demo");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooter.Demo");
		s_HeaderConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeaderConfirmation.Demo");
		s_FooterConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooterConfirmation.Demo");
		s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNullButton.Demo");
		s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNormalButton.Demo");
		s_AcceptConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteConfirmation.Demo");
		s_CancelConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NormalVoteConfirmation.Demo");
		s_ReconfirmButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReconfirmButtonText.Demo");
		s_RetryButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.RetryButtonText.Demo");
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
		s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteQuestion.Recovery");
		s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeader.Recovery");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooter.Recovery");
		s_HeaderConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteHeaderConfirmation.Recovery");
		s_FooterConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteFooterConfirmation.Recovery");
		s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNullButton.Recovery");
		s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteNormalButton.Recovery");
		s_AcceptConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.BlankVoteConfirmation.Recovery");
		s_CancelConfirmation = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NormalVoteConfirmation.Recovery");
		s_ReconfirmButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.ReconfirmButtonText.Recovery");
		s_RetryButtonText = _("Smartmatic.SAES.GUI.Windows.VotingWindow.RetryButtonText.Recovery");
		break;
	}
}

void SuperNullSelectionWidget::SetLabelsConfiguration()
{
	headerLabelConf = SAESGUIConfigurationManager::Current()->GetSuperWhiteHeaderLabelConfiguration();
	footerLabelConf = SAESGUIConfigurationManager::Current()->GetSuperWhiteBottomLabelConfiguration();
	centerlabelConf = SAESGUIConfigurationManager::Current()->GetSuperWhiteCenterLabelConfiguration();
	confirmLabelConf = SAESGUIConfigurationManager::Current()->GetSuperWhiteConfirmationCenterLabelConfiguration();
}

void SuperNullSelectionWidget::SimulateNullClicked()
{
	confirmationWidget->on_confirmButton_clicked();
}
