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

#include "Gui/Widgets/Voting/welcome-message-widget.h"
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
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

WelcomeMessageWidget::WelcomeMessageWidget(std::string messageString, int closeTimer, bool showButton)
:SelectionWidgetBase()
{
	messageWidget = NULL;
	chooseDialogWidget = NULL;

	label = new Label(messageString);

	messageWidget = new MessageWidget(label, showButton, closeTimer);
	messageWidget->set_shadow_type(SHADOW_NONE);
	
	chooseDialogWidget = new ChooseDialogWidget(messageWidget);
	chooseDialogWidget->on_close_signal().connect(sigc::mem_fun(this,&WelcomeMessageWidget::on_Timeout));
	
	mainContainer.add(*chooseDialogWidget);
	show_all_children();
}

WelcomeMessageWidget::~WelcomeMessageWidget()
{
	if(label) delete label;
	if(chooseDialogWidget) delete chooseDialogWidget;
	if(messageWidget) delete messageWidget;
}

void WelcomeMessageWidget::SetBaseButtons()
{
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

void WelcomeMessageWidget::on_Timeout()
{
	m_timeout_signal.emit();
}

WelcomeMessageWidget::void_signal WelcomeMessageWidget::signal_Timeout()
{
	return m_timeout_signal;
}

void WelcomeMessageWidget::SetLabelConfiguration(LabelConfiguration labelConf)
{
	LabelConfiguration::SetLabelConfiguration(label, labelConf);
}
