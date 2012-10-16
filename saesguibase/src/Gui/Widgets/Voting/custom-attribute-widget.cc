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

#include "Gui/Widgets/Voting/custom-attribute-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
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
using namespace Smartmatic::SAES::Voting::VotingDevice;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Operation::Voting;

CustomAttributeWidget::CustomAttributeWidget(Custom_attribute_definition & customAttr, bool showConfirmation, bool sortAlphabetically)
:SelectionWidgetBase()
{
	confirmationWidget = NULL;
	chooseDialogWidget = NULL;
	chooseDialogInfo = NULL;
	dialogButtonInfoList.clear();
	
	SetStrings();
	
	Custom_attribute_definition::ValueSequence attrList = customAttr.getValue();
	Custom_attribute_definition::ValueIterator it;

	CustomAtributtesWindowConfiguration questionConfig = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration();

	for(it = attrList.begin(); it != attrList.end(); it++)
	{
		string name = ElectionStringResourcesManager::Current()->getResource(*it);
		customAttrNameList.push_back(name);
	}

	if(sortAlphabetically)
		customAttrNameList.sort();

	for(list<string>::iterator iter1 = customAttrNameList.begin(); iter1 != customAttrNameList.end(); iter1++)
	{
		string toCompare = *iter1;

		for(it = attrList.begin(); it != attrList.end(); it++)
		{
			string name = ElectionStringResourcesManager::Current()->getResource(*it);
			if(toCompare == name)
			{
				string code = *it;
				ChooseDialogButtonInfo * buttonInfo = new ChooseDialogButtonInfo(name, "", code, "");
				dialogButtonInfoList.push_back(buttonInfo);
			}
		}
	}

	//Question window
	string header = ElectionStringResourcesManager::Current()->getResource(customAttr.getName_key());
	string footer = ElectionStringResourcesManager::Current()->getResource(customAttr.getDescription_key());

	if(header.empty() || questionConfig.getForceQuestionHeader())
		header = s_HeaderQuestion;
	if(footer.empty() || questionConfig.getForceQuestionFooter())
		footer = s_FooterQuestion;

	//Question window confirmation
	string headerConfirmation = header;
	string footerConfirmation = footer;
	
	if(headerConfirmation.empty() || questionConfig.getForceQuestionHeaderConfirmation())
		headerConfirmation = s_HeaderQuestionConfirm;
	if(footerConfirmation.empty() || questionConfig.getForceQuestionFooterConfirmation())
		footerConfirmation = s_FooterQuestionConfirm;
	
	if(showConfirmation)
	{
		chooseDialogInfo = new ChooseDialogInfo(header, "", footer, dialogButtonInfoList, false);
		confirmationWidget = new ConfirmationDialogWidget("", headerConfirmation, footerConfirmation);
		chooseDialogWidget = new ChooseDialogWidget(chooseDialogInfo, confirmationWidget);
		
        chooseDialogWidget->SetConfirmationStringFormat(s_CustomAttributeConfirmationFormat);
	}
	else
	{
		chooseDialogInfo = new ChooseDialogInfo(header, "", footer, dialogButtonInfoList, false);
		chooseDialogWidget = new ChooseDialogWidget(chooseDialogInfo);
	}

	chooseDialogWidget->on_choose_signal().connect(sigc::mem_fun(*this,&CustomAttributeWidget::on_questionAnswered));
	//chooseDialogWidget->on_cancel_signal().connect(sigc::mem_fun(*this,&VotingExperienceWindow::chooseDialogWidget_on_questionBack)); TODO implementar*//*	messageWidget = NULL;

	SetBaseButtons();
	SetLabelsConfiguration();
	
	mainContainer.add(*chooseDialogWidget);
}

CustomAttributeWidget::~CustomAttributeWidget()
{
	remove();

	vector<ChooseDialogButtonInfo*>::iterator it;

	for(it = dialogButtonInfoList.begin(); it != dialogButtonInfoList.end(); it++)
	{
		ChooseDialogButtonInfo* buttonInfo = (*it);
		if (buttonInfo) delete buttonInfo;
	}
	
	if(chooseDialogWidget)
	{
		delete chooseDialogWidget;
		chooseDialogWidget = NULL;
	}
	if(chooseDialogInfo)
	{
		delete chooseDialogInfo;
		chooseDialogInfo = NULL;
	}
	if(confirmationWidget)
	{
		delete confirmationWidget;
		confirmationWidget = NULL;
	}
}

void CustomAttributeWidget::SetBaseButtons()
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

void CustomAttributeWidget::SetLabelsConfiguration()
{
	CustomAtributtesWindowConfiguration questionConfig = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowConfiguration();
	
	if(confirmationWidget)
	{
		LabelConfiguration labelConf =  SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowCenterLabelConfiguration();
		confirmationWidget->SetLabelConfiguration(labelConf);
	}

	if(chooseDialogWidget)
	{
		LabelConfiguration headerConf =  SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowHeaderLabelConfiguration();
		LabelConfiguration footerConf = SAESGUIConfigurationManager::Current()->GetCustomAtributtesWindowBottomLabelConfiguration();	
		chooseDialogWidget->SetLabelConfiguration(headerConf, footerConf);
	
		LabelConfiguration labelConf1 =  SAESGUIConfigurationManager::Current()->GetConfirmationWindowBottomLabelConfiguration();
		LabelConfiguration labelConf2 =  SAESGUIConfigurationManager::Current()->GetConfirmationWindowHeaderLabelConfiguration();
		chooseDialogWidget->SetLabelConfirmationConfiguration(labelConf1, labelConf2);
	}
}

void CustomAttributeWidget::on_questionAnswered(ChooseDialogButtonInfo* info)
{
	if(info)
		m_answer_signal.emit(info->getCode());
}

CustomAttributeWidget::string_signal CustomAttributeWidget::signal_Answer()
{
	return m_answer_signal;
}

void CustomAttributeWidget::SetStrings()
{
	switch(VotingOperation::getVoteMode())
	{	
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
		s_HeaderQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestion");
		s_FooterQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestion");
		s_HeaderQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestionConfirm");
		s_FooterQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestionConfirm");
		s_CustomAttributeConfirmationFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeConfirmationFormat");
		break;

	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
		s_HeaderQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestion.Demo");
		s_FooterQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestion.Demo");
		s_HeaderQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestionConfirm.Demo");
		s_FooterQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestionConfirm.Demo");
		s_CustomAttributeConfirmationFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeConfirmationFormat.Demo");
		break;

	case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
		s_HeaderQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestion.Recovery");
		s_FooterQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestion.Recovery");
		s_HeaderQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.HeaderQuestionConfirm.Recovery");
		s_FooterQuestionConfirm = _("Smartmatic.SAES.GUI.Windows.VotingWindow.FooterQuestionConfirm.Recovery");
		s_CustomAttributeConfirmationFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.CustomAttributeConfirmationFormat.Recovery");
		break;
	}
}

void CustomAttributeWidget::ForceSelectedOption(std::string option)
{
	std::list<std::string>::iterator iter;
	int index = 0;

	for(iter = customAttrNameList.begin(); iter != customAttrNameList.end(); iter++)
	{
		if(*iter == option)
		{
			chooseDialogWidget->onOptionSelected(index);
			break;
		}
		index++;
	}
}
