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

#include "ballot-option-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Resources/election-string-resources-manager.h"
#include <Operation/MachineOperationManager.hxx>
#include "Runtime/Environment/saes-directories.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Functionalities/time-functionality.h"
#include <System/Utils/StringUtils.hxx>
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
using namespace Smartmatic::System::Utils;

BallotOptionWidget::BallotOptionWidget(Eligible_option& elegibleOption,
                                       Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
                                       bool isPrincipal, int width, int height, bool showNumber, bool isList)
{
	static BallotOptionWidgetConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();

	m_widgetEnabled = true;

	this->ballotOption = *(elegibleOption.getBallot_options().getBallot_option()).begin();
	this->isPrincipal = isPrincipal;
	isSelected = false;
	votingWidget = NULL;
	
	InitializeWidget();

	//static BallotOptionWidgetConfiguration config = SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();

	if(!config.getShowFrame())
		set_shadow_type (SHADOW_NONE);
	else
		set_shadow_type (SHADOW_IN);
	
	string sname = elegibleOption.getBallot_name_key();
	string label_name = ElectionStringResourcesManager::Current()->getResource(sname);
	
	selectedColor.set_rgb(config.getSelectedColor().getRed(), config.getSelectedColor().getGreen(), config.getSelectedColor().getBlue());
	unSelectedColor.set_rgb(config.getUnSelectedColor().getRed(), config.getUnSelectedColor().getGreen(), config.getUnSelectedColor().getBlue());

	eventbox = manage(new EventBox());
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	eventbox->show();

	stringstream ss;
	ss << ballotOption.getTally_position();
	
	string number = ss.str();
	int numberWidth = config.getNumberWidth();
	
	bool showImage = config.getDisplay() == "IMAGE";

	if(showImage)
	{
		string image_path = ballotOption.getImage_file_name() != NULL ?  saesDir.getImageElectoralResource(ballotOption.getImage_file_name().get())  : "";

		votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Image, image_path, number, config.getPadding(), numberWidth, width, height, showNumber));
	}
	else
	{
		string separator = config.getSeparatorCharacter();
		std::vector <std::string> parts;

		StringUtils::split(label_name, separator, parts);
		
		if(parts.size() >= 2)
		{
			string label1,label2;
			if(config.getNameIsBeforeSeparator())
			{
				label1 = parts[0];
				label2 = parts[1];
			}
			else
			{
				label2 = parts[0];
				label1 = parts[1];
			}
			votingWidget = manage(new VotingWidgetBase(label1, label2, number, config.getPadding(), numberWidth, width, height, showNumber));
		}
		else if(isList)
		{
			votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Text, label_name, number, config.getPadding(), numberWidth, width, height, showNumber));
		}
		else
		{
			votingWidget = manage(new VotingWidgetBase(label_name, "", number, config.getPadding(), numberWidth, width, height, showNumber));
		}
		
		eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
	}

	if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
	{
		eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &BallotOptionWidget::on_ballot_clicked));
	}

	eventbox->add(*votingWidget);
	add(*eventbox);
	show();
}

void BallotOptionWidget::setSize(int width, int height)
{
	set_size_request(width, height);

	if (votingWidget)
	{
		votingWidget->setSize(width, height);
		votingWidget->show();
	}

	show();
}

BallotOptionWidget::BallotOptionWidget(Eligible_option& elegibleOption)
{
	static BallotOptionWidgetConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();
	
	this->ballotOption = *(elegibleOption.getBallot_options().getBallot_option()).begin();
	this->isPrincipal = true;
	isSelected = false;

	InitializeWidget();

	if(!config.getShowFrame())
		set_shadow_type (SHADOW_NONE);
	else
		set_shadow_type (SHADOW_IN);
	
    string sname = elegibleOption.getBallot_name_key();
	string label_name = ElectionStringResourcesManager::Current()->getResource(sname);

	SaesDirectories saesDir;
	string image_path = ballotOption.getImage_file_name() != NULL ?  saesDir.getImageElectoralResource(ballotOption.getImage_file_name().get())  : "";
	
	selectedColor.set_rgb(config.getSelectedColor().getRed(), config.getSelectedColor().getGreen(), config.getSelectedColor().getBlue());
	unSelectedColor.set_rgb(config.getUnSelectedColor().getRed(), config.getUnSelectedColor().getGreen(), config.getUnSelectedColor().getBlue());
	
	eventbox = manage(new EventBox());
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);

	if (SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getEnableClick())
	{
		eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &BallotOptionWidget::on_ballot_clicked));
	}

	stringstream ss;
	ss << ballotOption.getTally_position();
	
	string number = ss.str();
	int numberWidth = config.getNumberWidth();
	
	bool showImage = config.getDisplay() == "IMAGE";
	if(showImage)
		votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Image, image_path, number, config.getPadding(), numberWidth, -1, -1));
	else
	{
		string separator = config.getSeparatorCharacter();
		size_t found = label_name.find_first_of(separator);

		while(found!=string::npos)
		{
			label_name[found] = ' ';
			found = label_name.find_first_of(separator, found + 1);
		}
		
		votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Text, label_name, number, config.getPadding(), numberWidth, -1, -1));
		
		eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
	}
		
	eventbox->add(*votingWidget);
	add(*eventbox);
	show();
}

void BallotOptionWidget::InitializeWidget()
{
	set_name(SAESGUIConfigurationManager::Current()->GetVotingExperienceSelectBallotOptionWidgetName());
	//TODO simplify both constructors
}

BallotOptionWidget::~BallotOptionWidget()
{

}
	
BallotOptionWidget::type_ballot_clicked BallotOptionWidget::signal_ballot_clicked()
{
	return m_ballot_clicked;
}

bool BallotOptionWidget::on_ballot_clicked(GdkEventButton* event)
{
	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getBallotOptionSelectSound());
	if(isSelected)
		SetSelection(false, true);
	else
		SetSelection(true, true);

	return true;
}

bool BallotOptionWidget::IsSelected()
{
	return isSelected;
}

bool BallotOptionWidget::IsPrincipal()
{
	return isPrincipal;
}

void BallotOptionWidget::SetSelection(bool select, bool sendSignal)
{
	if(select)
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, selectedColor);
		isSelected = true;
	}
	else
	{
		eventbox->modify_bg(Gtk::STATE_NORMAL, unSelectedColor);
		isSelected = false;
	}
	
	if(sendSignal) m_ballot_clicked.emit(ballotOption.getCode(), isSelected, isPrincipal);
}

string BallotOptionWidget::GetBallotOptionCode()
{
	return ballotOption.getCode();
}
