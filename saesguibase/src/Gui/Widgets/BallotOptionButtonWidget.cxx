/**
 * @file BallotOptionButtonWidget.cxx
 * @brief Body class ballot option button widget
 * @date 12/03/2012
 * @author Yadickson Soto
 */

#include "BallotOptionButtonWidget.hxx"
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

BallotOptionButtonWidget::BallotOptionButtonWidget(bool expand)
: ButtonsWidget(expand)
{
	int size;

	if (expand)
	{
		int spacing = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getExpandButton().getSpacing();
		setSpacing(spacing);

		size = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getExpandButton().getFontSize();
	}
	else
	{
		int clearWidth = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getSeparateButton().getClearButtonWidth();
		int acceptWidth = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getSeparateButton().getAcceptButtonWidth();
		int backWidth = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getSeparateButton().getBackButtonWidth();

		clearButton->set_size_request(clearWidth, -1);
		acceptButton->set_size_request(acceptWidth, -1);
		backButton->set_size_request(backWidth, -1);

		size = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getSeparateButton().getFontSize();
	}

	modifyFontSize(size);
}

BallotOptionButtonWidget::~BallotOptionButtonWidget()
{

}

void BallotOptionButtonWidget::update()
{
	std::string soundBallotS = SAESGUIConfigurationManager::Current()->getBallotOptionSelectSound();

	clearButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.ClearSelection"));
	acceptButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.AcceptSelection"));
	backButton->SetLabel(_("Smartmatic.SAES.GUI.Widgets.BallotOptionSelectionWidget.Back"));

	clearButton->WidgetsPosition(5,0,0);
	clearButton->SetSound (soundBallotS);

	acceptButton->WidgetsPosition(5,0,0);
	acceptButton->SetSound (soundBallotS);

	backButton->WidgetsPosition(5,0,0);
	backButton->SetSound (soundBallotS);

	switch(VotingOperation::getVoteMode())
	{
		case VoteMode::VOTE_S:
		case VoteMode::VOTE_O:
			clearButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			acceptButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonName());
			break;
		case VoteMode::VOTE_D:
			clearButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			acceptButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonDemoName());
			break;
		case VoteMode::VOTE_R:
			clearButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			acceptButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			backButton->SetCustomName(SAESGUIConfigurationManager::Current()->GetVotingWindowButtonRecoveryName());
			break;
	}
}
