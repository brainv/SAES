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

#include "Gui/Widgets/Voting/language-selection-widget.h"
#include "Voting/set-language-functionality.h"
#include "Resources/election-string-resources-manager.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include <Voting/VotingDevice/voting-devices-schema.hxx>
#include "Configuration/s-m-t-t-g-u-i-conf-manager.h"
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

using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

LanguageSelectionWidget::LanguageSelectionWidget(bool showConfirmation, bool sortAlphabetically)
: ChooseSelectionWidget()
{
	this->showConfirmation = showConfirmation;
	this->sortAlphabetically = sortAlphabetically;
	this->chooseDialogWidget = NULL; // not delete
	this->showWidget = false;
	this->confirmationWidget = NULL;
	this->chooseDialogInfo = NULL;
	this->dialogButtonInfoList.clear();

	Smartmatic::SAES::Voting::Election::Languages languages = MachineOperationManager::getInstance()->getElectoralConfiguration()->getLanguages();
	Smartmatic::SAES::Voting::Election::Languages::LanguageSequence langSequence = languages.getLanguage();
	Smartmatic::SAES::Voting::Election::Languages::LanguageIterator it;

	if(langSequence.size() != 1)
	{
		showWidget = true;

		for(it = langSequence.begin(); it != langSequence.end(); it++)
		{
			std::string name = ElectionStringResourcesManager::Current()->getResource(it->getName_key());
			languagesList.push_back(name);
		}

		if(sortAlphabetically)
		{
			languagesList.sort();
		}

		std::list<std::string>::iterator iter1;

		for(iter1 = languagesList.begin(); iter1 != languagesList.end(); iter1++)
		{
			std::string toCompare = *iter1;

			for(it = langSequence.begin(); it != langSequence.end(); it++)
			{
				std::string name = ElectionStringResourcesManager::Current()->getResource(it->getName_key());

				if(toCompare == name)
				{
					std::string language = it->getLanguage();
					std::string country = it->getCountry();
					ChooseDialogButtonInfo* buttonInfo = new ChooseDialogButtonInfo(name, "", language, country);
					dialogButtonInfoList.push_back(buttonInfo);
					break;
				}
			}
		}

		if(showConfirmation)
		{
			chooseDialogInfo = new ChooseDialogInfo("", "", "", dialogButtonInfoList, false);
			confirmationWidget = new ConfirmationDialogWidget("", "", "", "", "");

			LabelConfiguration CenterConf = SAESGUIConfigurationManager::Current()->GetSelectionLanguageConfirmationCenterLabelConfiguration();
			confirmationWidget->SetLabelConfiguration(CenterConf);
		}
		else
		{
			chooseDialogInfo = new ChooseDialogInfo("", "", "", dialogButtonInfoList, false);
			confirmationWidget = NULL;
		}

		LabelConfiguration headerConf = SAESGUIConfigurationManager::Current()->GetSelectionLanguageHeaderLabelConfiguration();
		LabelConfiguration footerConf = SAESGUIConfigurationManager::Current()->GetSelectionLanguageBottomLabelConfiguration();
		LabelConfiguration headerConfirmConf = SAESGUIConfigurationManager::Current()->GetSelectionLanguageConfirmationHeaderLabelConfiguration();
		LabelConfiguration footerConfirmConf = SAESGUIConfigurationManager::Current()->GetSelectionLanguageConfirmationBottomLabelConfiguration();

		setLabelConfig(headerConf, footerConf);
		setLabelConfirmationConfig(headerConfirmConf, footerConfirmConf);
	}

	setTitle(false);
	setShowBorder(true);

	initialize();
}

LanguageSelectionWidget::~LanguageSelectionWidget()
{
	remove();

	if (chooseDialogInfo)
	{
		delete chooseDialogInfo;
		chooseDialogInfo = NULL;
	}

	if (confirmationWidget)
	{
		delete confirmationWidget;
		confirmationWidget = NULL;
	}

	std::vector<ChooseDialogButtonInfo*>::iterator it;

	for(it = dialogButtonInfoList.begin(); it != dialogButtonInfoList.end(); it++)
	{
		ChooseDialogButtonInfo* buttonInfo = (*it);
		if (buttonInfo) delete buttonInfo;
	}

	dialogButtonInfoList.clear();

	ChooseSelectionWidget::dispose();
}

void LanguageSelectionWidget::dispose()
{
}

void LanguageSelectionWidget::initialize()
{
	reload();

	if (!showWidget)
	{
		return;
	}

	int width = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowWith();
	int height = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration().getQuestionWindowHeight();

	setChooseInfo(chooseDialogInfo, confirmationWidget);
	setInternalSizeWidget(width, height);

	refresh();
}

bool LanguageSelectionWidget::ShowWidget()
{
	return showWidget;
}

void LanguageSelectionWidget::SetBaseButtons()
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

void LanguageSelectionWidget::reload()
{
	SetLanguageFunctionality::getCurrentLanguageCountry ( previousLanguage, previousCountry );
}

void LanguageSelectionWidget::SetBackLanguage()
{
	SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(previousLanguage, previousCountry);
}

void LanguageSelectionWidget::onSelected(ChooseDialogButtonInfo* choose)
{
	if(choose)
	{
		SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(choose->getCode(), choose->getOption());
	}

	signalEnd.emit();
}

void LanguageSelectionWidget::onPreSelected(ChooseDialogButtonInfo* choose)
{
	if(choose)
	{
		SetLanguageFunctionality::setNewVotingLanguageByLanguageCountry(choose->getCode(), choose->getOption());
	}

	refresh();
}

void LanguageSelectionWidget::onPreSelectedBack()
{
	SetBackLanguage();
	refresh();
}

void LanguageSelectionWidget::refresh()
{
	SetBaseButtons();
	SetStrings();

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowDemoName());
			break;
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			setName(SAESGUIConfigurationManager::Current()->GetVotingExperienceWindowRecoveryName());
			break;
	}

	if (chooseDialogWidget)
	{
		Glib::ustring text = _(s_ConfirmationFormat.c_str());
		chooseDialogWidget->SetConfirmationStringFormat(text);
		chooseDialogWidget->Refresh(_(s_ConfirmationTitle.c_str()), _(s_ConfirmationFooter.c_str()));
	}

	if (confirmationWidget)
	{
		confirmationWidget->Refresh(_(s_ConfirmationAcceptButton.c_str()), _(s_ConfirmationRetryButton.c_str()));
		confirmationWidget->setHeaderTitle(s_Title);
		confirmationWidget->setFooterTitle(s_Footer);
	}

	if (chooseDialogInfo)
	{
		chooseDialogInfo->setTitle(s_Title);
		chooseDialogInfo->setFooter(s_Footer);
	}
	
	if (chooseDialogWidget)
	{
		chooseDialogWidget->refresh();
	}
}

void LanguageSelectionWidget::SetStrings()
{
	switch(VotingOperation::getVoteMode())
	{
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
		s_Title = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionTitle");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionFooter");
		s_ConfirmationTitle = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationTitle");
		s_ConfirmationFooter = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFooter");
		s_ConfirmationFormat = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFormat");
		s_ConfirmationAcceptButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationButton");
		s_ConfirmationRetryButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionCancelButton");
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
		s_Title = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionTitle.Demo");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionFooter.Demo");
		s_ConfirmationTitle = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationTitle.Demo");
		s_ConfirmationFooter = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFooter.Demo");
		s_ConfirmationFormat = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFormat.Demo");
		s_ConfirmationAcceptButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationButton.Demo");
		s_ConfirmationRetryButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionCancelButton.Demo");
		break;
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
		s_Title = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionTitle.Recovery");
		s_Footer = _("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionFooter.Recovery");
		s_ConfirmationTitle = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationTitle.Recovery");
		s_ConfirmationFooter = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFooter.Recovery");
		s_ConfirmationFormat = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationFormat.Recovery");
		s_ConfirmationAcceptButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionConfirmationButton.Recovery");
		s_ConfirmationRetryButton = N_("Smartmatic.SAES.GUI.Windows.VotingWindow.LanguageSelectionCancelButton.Recovery");
		break;
	}
}

std::string LanguageSelectionWidget::SimulateButtonNPressed(int index)
{
	return (chooseDialogWidget ? chooseDialogWidget->onOptionSelectedSim(index) : previousLanguage + "_" + previousCountry);
}
