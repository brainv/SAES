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
 * @file ballot-option-widget-.cc
 * @brief Body of core class BallotOptionWidget
 */

#include "referendum-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include "Runtime/Environment/saes-directories.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Functionalities/time-functionality.h"
#include <iostream>

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
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Resources;
using namespace Smartmatic::Functionality;

ReferendumWidget::ReferendumWidget(Eligible_option& elegibleOption,
		Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir)
{
	isSelected = false;
	this->ballotOption = *(elegibleOption.getBallot_options().getBallot_option()).begin();
	
	InitializeWidget();
	
	string sname = elegibleOption.getBallot_name_key();
	string label_name = ElectionStringResourcesManager::Current()->getResource(sname);

	static BallotOptionWidgetConfiguration config =
		SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();

	selectedColor.set_rgb(config.getSelectedColor().getRed(), config.getSelectedColor().getGreen(), config.getSelectedColor().getBlue());
	unSelectedColor.set_rgb(config.getUnSelectedColor().getRed(), config.getUnSelectedColor().getGreen(), config.getUnSelectedColor().getBlue());
	
	eventbox = manage(new EventBox());
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &ReferendumWidget::on_ballot_clicked));
	eventbox->set_name("referendumballotoptioneventbox");
	eventbox->show();
	eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);

	votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Text, label_name, "", 0, 0, false, true));
		
	eventbox->add(*votingWidget);
	add(*eventbox);
	show();
}

void ReferendumWidget::InitializeWidget()
{

}

ReferendumWidget::~ReferendumWidget()
{

}
	
ReferendumWidget::type_ballot_clicked ReferendumWidget::signal_ballot_clicked()
{
	return m_ballot_clicked;
}

void ReferendumWidget::SetSelection(bool select, bool sendSignal)
{
	if(select)
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, selectedColor);
	}
	else
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
	}

	if(sendSignal)
	{
		m_ballot_clicked.emit(ballotOption.getCode(), select);
	}

	isSelected = select;
}

bool ReferendumWidget::on_ballot_clicked(GdkEventButton* event)
{
	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getBallotOptionSelectSound());

	if(isSelected)
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
		m_ballot_clicked.emit(ballotOption.getCode(), false);
	}
	else
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, selectedColor);
		m_ballot_clicked.emit(ballotOption.getCode(), true);
	}

	isSelected = !isSelected;

	return true;
}

string ReferendumWidget::GetBallotOptionCode()
{
	return ballotOption.getCode();
}
