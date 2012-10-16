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
/**
 * @file party-selection-widget.cc
 * @brief PartySelectionWidget body
 */

#include "party-selection-widget.h"
#include <iostream>
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
#include "Voting/Election/ElectionWrapper.hxx"
#include <Operation/MachineOperationManager.hxx>
#include <Operation/Voting/VotingOperation.hxx>
#include <Operation/FormatLabel.hxx>
#include "FactoryMethodWidget.hxx"

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
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Operation::Voting;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::SAES::GUI::Operation;

PartySelectionWidget::PartySelectionWidget(Contest &contest, bool viewBackButton)
{
	static PartySelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration();
	
	m_widgetEnabled = true;
	this->contest = contest;
	showBackButton = false;

	contestName = contest.getDistrict().getName_key();
	ptrPartyWidget = NULL;
	
	flagShowNullButton = config.getShowNullButton();

	partyButtomWidget = FactoryMethodWidget::createPartyButtonWidget();
	partyButtomWidget->update();
	partyButtomWidget->showButton(viewBackButton, flagShowNullButton);

	if (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getEnableClick())
	{
		partyButtomWidget->getSignalBackButtonClicked().connect(sigc::mem_fun(this,&PartySelectionWidget::on_backButton_clicked));
		partyButtomWidget->getSignalNullButtonClicked().connect(sigc::mem_fun(this,&PartySelectionWidget::on_nullButton_clicked));
	}
	
	bottomFrame = manage(new Frame());
	bottomFrame->set_shadow_type(Gtk::SHADOW_NONE);
    bottomFrame->add(*partyButtomWidget);
	bottomFrame->set_size_request(-1, config.getFrameBottomHeight());

	externalBox = manage(new VBox(false , 0));
	externalBox->pack_end(*bottomFrame, false, false);
	
	add(*externalBox);
	
	show_all_children();

	setBottom(true);
	setTitle(true);
}

PartySelectionWidget::~PartySelectionWidget()
{
	if (partyButtomWidget)
	{
		delete partyButtomWidget;
		partyButtomWidget = NULL;
	}
}

void PartySelectionWidget::SetWidgetEnabled(bool enabled)
{
	m_widgetEnabled = enabled;
}
void PartySelectionWidget::refresh()
{
	RefreshLabels();
}

void PartySelectionWidget::ShowBackButton()
{
	showBackButton = true;
	partyButtomWidget->showButton(true, flagShowNullButton);
}

std::string PartySelectionWidget::GetContestName()
{
	return ElectionStringResourcesManager::Current()->getResource(contestName);
}

void PartySelectionWidget::HideBackButton()
{
	showBackButton = false;
	partyButtomWidget->showButton(false, flagShowNullButton);
}

void PartySelectionWidget::SetBackButton(bool show)
{
	showBackButton = show;
	partyButtomWidget->showButton(show, flagShowNullButton);
}

void PartySelectionWidget::RefreshLabels()
{
	partyButtomWidget->update();

	if(ptrPartyWidget)
	{
		ptrPartyWidget->RefreshLabel(_("Smartmatic.SAES.GUI.Widgets.PartySelectionWidget.NullParty"));
	}
}

void PartySelectionWidget::Initialize(std::list<Ballot_option>& partyList,
          Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir)
{	
	static  PartySelectionConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration();
	
	float imageRelation = config.getImageRelation();
	int nCol = config.getSizeToColumns();
	int rowSpacing = config.getPartiesMargin();
	int colSpacing = config.getPartiesMargin();
	int rowsToFill = 0;

	float numberW = SAESGUIConfigurationManager::Current()->GetPartyWidgetConfiguration().getNumberWidth();

	int totalW, totalH;
	get_size_request(totalW, totalH);
	totalH -= (2*config.getFrameBottomHeight() + 2*rowSpacing);
	totalW -= 11;

	//calculate columns of table
	float boxW = totalW / (float)nCol;
	float widgetW = boxW - colSpacing * ((nCol - 1) / (float)nCol);
	float imageW = widgetW - numberW;

	float imageH = imageW / imageRelation;
	float widgetH = imageH;
	float boxH = imageH + rowSpacing;

	nCol = config.getColumns();

	int nRow = totalH / boxH;

	int totalBoxes = (int)partyList.size() + 1;

	bool useMaxPartyNumber = config.getUseMaxPartyNumerFromAllContest();
	if(useMaxPartyNumber)
	{
//		totalBoxes = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection()->getMaxPartysAllContests();

		totalBoxes = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getMaxPartiesByAllContest();
		totalBoxes += 1;
	}

	if(nRow * nCol < totalBoxes)
	{
		nRow = totalBoxes / nCol;
		float rest = totalBoxes % nCol;
		nRow = rest > 0.0 ? nRow + 1 : nRow;

		boxH = totalH / (float) nRow;
		widgetH = boxH - rowSpacing;
		imageH = widgetH;

		imageW = imageH * imageRelation;
		widgetW = imageW + numberW;
		boxW = widgetW;

		colSpacing = (totalW - boxW * nCol) / (nCol - 1);
	}

	rowsToFill = totalBoxes / nCol;
	float rem = totalBoxes % nCol;
	rowsToFill = rem > 0.0 ? rowsToFill + 1 : rowsToFill;
	
	tableClientArea = manage(new Table(rowsToFill, nCol, true));
	tableClientArea->set_row_spacings(rowSpacing);
	tableClientArea->set_col_spacings(colSpacing);

	static float partyAlign = config.getPartySelectionAlignment();
	
	Alignment* alig = manage(new Alignment());
	alig->set(0.5,partyAlign,0,0);
	alig->add(*tableClientArea);
	
	int i = 0;
	int j = 0;

	for(it = partyList.begin(); it != partyList.end(); it++)
	{
		ptrPartyWidget = manage(new PartyWidget(*it, saesDir, widgetW, widgetH));

		if (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getEnableClick())
		{
			ptrPartyWidget->signal_party_clicked().connect(sigc::mem_fun(this,&PartySelectionWidget::on_party_clicked));
		}

		ptrPartyWidget->show();

		bool fillByRows = SAESGUIConfigurationManager::Current()->GetPartyWidgetConfiguration().getUseFillByRows();

		if(fillByRows)
		{
			tableClientArea->attach(*ptrPartyWidget, j, j + 1, i, i + 1, Gtk::SHRINK, Gtk::SHRINK);

			j++;
			if(j == nCol)
			{
				j = 0;
				i++;
			}
		}
		else
		{
			tableClientArea->attach(*ptrPartyWidget, j, j + 1, i, i + 1, Gtk::SHRINK, Gtk::SHRINK);


			i++;
			if(i == rowsToFill)
			{
				i = 0;
				j++;
			}
			if(j == nCol)
			{
				j = 0;
			}
		}
	}

	if(config.getShowNullParty())
	{
		ptrPartyWidget = manage(new PartyWidget(_("Smartmatic.SAES.GUI.Widgets.PartySelectionWidget.NullParty"), widgetW, widgetH));

		if (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getEnableClick())
		{
			ptrPartyWidget->signal_party_null_clicked().connect(sigc::mem_fun(this,&PartySelectionWidget::on_nullButton_clicked));
		}

		ptrPartyWidget->show();

		tableClientArea->attach(*ptrPartyWidget, j, j + 1, i, i + 1, SHRINK, SHRINK);
	}
	
	externalBox->pack_start(*alig);
	tableClientArea->show_all_children();
}

void PartySelectionWidget::on_party_clicked(Party& partySelected)
{
	if(m_widgetEnabled == false)
					return;

	{
		//Glib::Mutex::Lock sync(m_signalMutex);
		if(m_party_clicked.empty() == false)
			m_widgetEnabled = false;


		m_party_clicked.emit(partySelected);
	}
}

void PartySelectionWidget::on_nullButton_clicked()
{
	if(m_widgetEnabled == false)
					return;
	{
		//Glib::Mutex::Lock sync(m_signalMutex);
		if(m_null_clicked.empty() == false)
			m_widgetEnabled = false;

		m_null_clicked.emit();
	}
}

void PartySelectionWidget::on_backButton_clicked()
{
	if(m_widgetEnabled == false)
					return;
	{
		//Glib::Mutex::Lock sync(m_signalMutex);

		if(m_back_clicked.empty() == false)
			m_widgetEnabled = false;

		m_back_clicked.emit();
	}
}

PartySelectionWidget::type_null_clicked PartySelectionWidget::null_clicked()
{
	return m_null_clicked;
}

PartySelectionWidget::type_back_clicked PartySelectionWidget::back_clicked()
{
	return m_back_clicked;
}

PartySelectionWidget::type_party_clicked PartySelectionWidget::party_clicked()
{
	return m_party_clicked;
}

Smartmatic::SAES::Voting::Election::Contest PartySelectionWidget::getContest()
{
	return contest;
}

Smartmatic::GUI::Configuration::LabelConfiguration PartySelectionWidget::getTitleLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetPartySelectionWindowHeaderLabelConfiguration();
}

Smartmatic::GUI::Configuration::LabelConfiguration PartySelectionWidget::getBottomLabelConfig()
{
	return SAESGUIConfigurationManager::Current()->GetPartySelectionWindowBottomLabelConfiguration();
}

std::string PartySelectionWidget::getTitleText()
{
	std::string title;

	Glib::ustring s_PartyHeaderFormat;
	Glib::ustring s_PartyHeaderFormatNoQuestion;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat");
			s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat.Demo");
			s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_PartyHeaderFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormat.Recovery");
			s_PartyHeaderFormatNoQuestion = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyHeaderFormatNoQuestion.Recovery");
			break;
	}

	if(showBackButton)
	{
		title = FormatLabel::contestText(contest, s_PartyHeaderFormat);
	}
	else
	{
		title = FormatLabel::contestText(contest, s_PartyHeaderFormatNoQuestion);
	}

	FormatLabel::checkComposeString(title);

	return title;
}

std::string PartySelectionWidget::getBottomText()
{
	std::string bottom;

	Glib::ustring s_PartyFooterFormat;

	switch(VotingOperation::getVoteMode())
	{
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_S:
		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_O:
			s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_D:
			s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat.Demo");
			break;

		case Smartmatic::SAES::Voting::Vote::VoteMode::VOTE_R:
			s_PartyFooterFormat = _("Smartmatic.SAES.GUI.Windows.VotingWindow.PartyFooterFormat.Recovery");
			break;
	}

	bottom = FormatLabel::contestText(contest, s_PartyFooterFormat);

	FormatLabel::checkComposeString(bottom);

	return bottom;
}
