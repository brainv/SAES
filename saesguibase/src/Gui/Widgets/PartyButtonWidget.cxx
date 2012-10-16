/**
 * @file PartyButtonWidget.cxx
 * @brief Body class party button widget
 * @date 12/03/2012
 * @author Yadickson Soto
 */

#include "PartyButtonWidget.hxx"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
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

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

PartyButtonWidget::PartyButtonWidget(bool expand)
: ButtonsWidget(expand)
{
	int size;

	if (expand)
	{
		int spacing = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getExpandButton().getSpacing();
		size = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getExpandButton().getFontSize();

		setSpacing(spacing);
	}
	else
	{
		int backWidth = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getSeparateButton().getBackButtonWidth();
		int nullWidth = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getSeparateButton().getNullButtonWidth();
		size = SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getSeparateButton().getFontSize();

		backButton->set_size_request(backWidth, -1);
		nullButton->set_size_request(nullWidth, -1);
	}

	modifyFontSize(size);
}

PartyButtonWidget::~PartyButtonWidget()
{

}

void PartyButtonWidget::update()
{
	std::string soundPartyS = SAESGUIConfigurationManager::Current()->getPartySelectSound();

	backButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.PartySelectionWidget.Back"));
	nullButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.PartySelectionWidget.NullSelection"));

	backButton->WidgetsPosition(5,0,0);
	backButton->SetSound (soundPartyS);

	nullButton->WidgetsPosition(5,0,0);
	nullButton->SetSound (soundPartyS);

	switch(VotingOperation::getVoteMode())
	{
		case VoteMode::VOTE_S:
		case VoteMode::VOTE_O:
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			nullButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			break;
		case VoteMode::VOTE_D:
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			nullButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			break;
		case VoteMode::VOTE_R:
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			nullButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			break;
	}
}

void PartyButtonWidget::showButton(bool showBack, bool showNull)
{
	ButtonsWidget::showButton(false, false, showBack, showNull);
}
