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

#include "Gui/Widgets/Voting/contest-null-selection-widget.h"
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

ContestNullSelectionWidget::ContestNullSelectionWidget(bool isReferendum)
:QuestionSelectionWidget(false, false)
{
	this->isReferendum = isReferendum;
	SetStrings();
	SetLabelsConfiguration();
	Initialize();
}

ContestNullSelectionWidget::~ContestNullSelectionWidget()
{

}

void ContestNullSelectionWidget::SetStrings()
{
	if(isReferendum)
	{
		switch(VotingOperation::getVoteMode())
		{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteQuestion");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteHeader");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteFooter");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNullButton");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNormalButton");
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteQuestion.Demo");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteHeader.Demo");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteFooter.Demo");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNullButton.Demo");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNormalButton.Demo");
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteQuestion.Recovery");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteHeader.Recovery");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteFooter.Recovery");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNullButton.Recovery");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullReferendumVoteNormalButton.Recovery");
			break;
		}
	}
	else
	{
		switch(VotingOperation::getVoteMode())
		{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteQuestion");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteHeader");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteFooter");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNullButton");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNormalButton");
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteQuestion.Demo");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteHeader.Demo");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteFooter.Demo");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNullButton.Demo");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNormalButton.Demo");
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_Question = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteQuestion.Recovery");
			s_Header = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteHeader.Recovery");
			s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteFooter.Recovery");
			s_AcceptButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNullButton.Recovery");
			s_CancelButton = _("Smartmatic.SAES.GUI.Windows.VotingWindow.NullPartyVoteNormalButton.Recovery");
			break;
		}
	}
}

void ContestNullSelectionWidget::SetLabelsConfiguration()
{
	headerLabelConf = SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionHeaderLabelConfiguration();
	footerLabelConf = SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionBottomLabelConfiguration();
	centerlabelConf = SAESGUIConfigurationManager::Current()->GetContestWhiteSelectionCenterLabelConfiguration();
	confirmLabelConf = SAESGUIConfigurationManager::Current()->GetSuperWhiteConfirmationCenterLabelConfiguration();
}
