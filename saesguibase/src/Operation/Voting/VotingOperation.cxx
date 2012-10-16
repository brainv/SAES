/**
 * @file VotingOperation.cxx
 * @brief Body class operation voting mode
 * @date 23/04/2012
 * @author Yadickson Soto
 */

#include "VotingOperation.hxx"
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Widgets/choose-dialog-info.h>
#include <Widgets/choose-dialog-widget.h>

using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::Vote;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;

VotingOperation::VotingOperation()
{

}

VotingOperation::~VotingOperation()
{

}

void VotingOperation::refresh()
{
	switch(getVoteMode())
	{
	case VoteMode::VOTE_S:
	case VoteMode::VOTE_O:
		ChooseDialogWidget::SetBaseWidgetsBaseName("dialog_widget_base");
		DialogWidgetBase::SetBaseWidgetsBaseName("dialog_widget_base");
		break;

	case VoteMode::VOTE_D:
		ChooseDialogWidget::SetBaseWidgetsBaseName("dialog_widget_demo_base");
		DialogWidgetBase::SetBaseWidgetsBaseName("dialog_widget_demo_base");
		break;

	case VoteMode::VOTE_R:
		ChooseDialogWidget::SetBaseWidgetsBaseName("dialog_widget_recovery_base");
		DialogWidgetBase::SetBaseWidgetsBaseName("dialog_widget_recovery_base");
		break;
	}
}

std::string VotingOperation::getWindowName()
{
	std::string name;

	switch(getVoteMode())
	{
		case VoteMode::VOTE_S:
		case VoteMode::VOTE_O:
			name = SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName();;
			break;
		case VoteMode::VOTE_D:
			name = SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowDemoName();
			break;
		case VoteMode::VOTE_R:
			name = SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowRecoveryName();
			break;
	}

	return name;
}

VoteMode VotingOperation::getVoteMode()
{
	VoteMode mode = VoteMode::VOTE_O;

	if(MachineOperationManager::getInstance()->getVotingExperienceController())
	{
		mode = MachineOperationManager::getInstance()->getVotingExperienceController()->getVotingMode();
	}

	return mode;
}
