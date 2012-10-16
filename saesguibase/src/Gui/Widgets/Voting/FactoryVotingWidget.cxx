/**
 * @file FactoryVotingWidget.cxx
 * @brief Body class for create widget
 * @date 29/02/2012
 * @author Yadickson Soto
 */

#include "FactoryVotingWidget.hxx"
#include <Gui/Widgets/FactoryMethodWidget.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Voting::VotingDevice;

FactoryVotingWidget::FactoryVotingWidget()
{

}

FactoryVotingWidget::~FactoryVotingWidget()
{

}

LanguageSelectionWidget * FactoryVotingWidget::createViewLanguageSelectionWidget()
{
	bool showC = false;
	bool sortA = SAESGUIConfigurationManager::Current()->GetSortLanguagesAlphabetical();
	LanguageSelectionWidget * widget = new LanguageSelectionWidget(showC, sortA);
	return widget;
}

LanguageSelectionWidget * FactoryVotingWidget::createVotingLanguageSelectionWidget()
{
	bool showC = SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowLanguageConfirmation();
	bool sortA = SAESGUIConfigurationManager::Current()->GetSortLanguagesAlphabetical();
	LanguageSelectionWidget * widget = new LanguageSelectionWidget(showC, sortA);
	return widget;
}

SimulationWidget * FactoryVotingWidget::createSimulationWidget()
{
	return new SimulationWidget();
}

PreviewWidget * FactoryVotingWidget::createPreviewWidget()
{
	return new PreviewWidget();
}

VotePreviewWidget * FactoryVotingWidget::createVotePreviewWidget()
{
	return new VotePreviewWidget();
}

TimeOutPreviewWidget * FactoryVotingWidget::createTimeOutPreviewWidget()
{
	return new TimeOutPreviewWidget();
}

WaitingForCardWidget * FactoryVotingWidget::createWaitingForCardWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	WaitingForCardWidget * widget = new WaitingForCardWidget(progress);
	return widget;
}

PrintTimeOutWidget * FactoryVotingWidget::createPrintTimeOutWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PrintTimeOutWidget * widget = new PrintTimeOutWidget(progress);
	return widget;
}

PrintVoteErrorWidget * FactoryVotingWidget::createPrintVoteErrorWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PrintVoteErrorWidget * widget = new PrintVoteErrorWidget(progress);
	return widget;
}

RemoveCardWidget * FactoryVotingWidget::createRemoveCardWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	RemoveCardWidget * widget = new RemoveCardWidget(progress);
	return widget;
}

EndPrintVoteWidget * FactoryVotingWidget::createEndPrintVoteWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	EndPrintVoteWidget * widget = new EndPrintVoteWidget(progress);
	return widget;
}

CardRemovedWidget * FactoryVotingWidget::createCardRemovedWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	CardRemovedWidget * widget = new CardRemovedWidget(progress);
	return widget;
}

PrintVoteWidget * FactoryVotingWidget::createPrintVoteWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	PrintVoteWidget * widget = new PrintVoteWidget(progress);
	return widget;
}

InterruptVotingWidget * FactoryVotingWidget::createInterruptVotingWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	InterruptVotingWidget * widget = new InterruptVotingWidget(progress);
	return widget;
}

KeypadVotingPasswordWidget * FactoryVotingWidget::createKeypadVotingPasswordWidget()
{
	KeypadVotingPasswordWidget * widget = new KeypadVotingPasswordWidget();
	return widget;
}

EndVotingWidget * FactoryVotingWidget::createEndVotingWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	EndVotingWidget * widget = new EndVotingWidget(progress);
	return widget;
}

InterruptWidget * FactoryVotingWidget::createInterruptWidget()
{
	return new InterruptWidget();
}

VotingExperienceValidationWidget * FactoryVotingWidget::createVotingExperineceValidationWidget()
{
	return new VotingExperienceValidationWidget();
}

SuperNullSelectionWidget * FactoryVotingWidget::createSuperNullSelectionWidget()
{
	bool buttonVertical = SAESGUIConfigurationManager::Current()->GetConfirmationWindowConfiguration().getNullButtonsVertical();
	bool showConfirmation = SAESGUIConfigurationManager::Current()->GetVotingWindowConfiguration().getShowBlankVoteConfirmation();
	return new SuperNullSelectionWidget(showConfirmation, buttonVertical);
}

ContestNullSelectionWidget * FactoryVotingWidget::createContestNullSelectionWidget()
{
	return new ContestNullSelectionWidget();
}

CustomAttributeWidget * FactoryVotingWidget::createCustomAttributeWidget(Custom_attribute_definition & customAttribute)
{
	bool sort = SAESGUIConfigurationManager::Current()->GetSortAlphabetically();
	bool showConfirmation = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getShowQuestionConfirmation();
	return new CustomAttributeWidget(customAttribute, showConfirmation, sort);
}

ScreenVotingWidget * FactoryVotingWidget::createScreenVotingWidget()
{
	ProgressWidget * progress = FactoryMethodWidget::createProgressWidget();
	ScreenVotingWidget * widget = new ScreenVotingWidget(progress);
	return widget;
}

VotingExperienceWidget * FactoryVotingWidget::createVotingExperienceWidget()
{
	return new VotingExperienceWidget();
}
