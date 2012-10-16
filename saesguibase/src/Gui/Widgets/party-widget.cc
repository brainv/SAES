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
 * @file party-widget-.cc
 * @brief Body of core class PartyWidget
 */
 
#include "party-widget.h"
#include "Configuration/label-configuration.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "System/Sounds/smartmatic-sounds-manager.h"
#include "Environment/Configurations/resource-path-provider.h"
#include "Resources/election-string-resources-manager.h"
#include "System/IO/File.h"
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
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Resources;

PartyWidget::PartyWidget(Ballot_option& ballotParty, 
              Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
              int width, int height)
{

	m_widgetEnabled = true;
	set_size_request(width, height);
	set_name("voting_experience_party_widget");
	this->ballotParty = ballotParty;
	this->party = this->ballotParty.getParty();

	string image_path = party.getImage_file_name() != NULL ?  saesDir.getImageElectoralResource(party.getImage_file_name().get())  : "";

	//default SaesDirectories
	SaesDirectories defaultSaesDir;
	string second_image_path = party.getImage_file_name() != NULL ?  defaultSaesDir.getImageElectoralResource(party.getImage_file_name().get())  : "";

	static PartyWidgetConfiguration config = SAESGUIConfigurationManager::Current()->GetPartyWidgetConfiguration();
	if(!config.getShowFrame()) 
		set_shadow_type (SHADOW_NONE);
	else
		set_shadow_type (SHADOW_IN);
	
	bool useAbreviation = config.getUseAbbreviation();
	string label_name;
	if(useAbreviation)
        label_name = ElectionStringResourcesManager::Current()->getResource(party.getAbbreviation() != NULL ? party.getAbbreviation().get() : "null");
	else
        label_name = ElectionStringResourcesManager::Current()->getResource(party.getName() != NULL ? party.getName().get() : "null");

	stringstream ss;
	ss << ballotParty.getTally_position();
	
	string number = ss.str();
	int numberWidth = config.getNumberWidth();

	bool showImage = config.getDisplay() == "IMAGE";

	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->GetVotingWidgetPartySelectionLabelChildLabelConfiguration();
	
	if(showImage)
	{
		if(File::canOpenFile(image_path))
		{
			votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Image, image_path, number, config.getPadding(), numberWidth, labelConf, width, height));
		}
		else if(File::canOpenFile(second_image_path))
		{
			votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Image, second_image_path, number, config.getPadding(), numberWidth, labelConf, width, height));
		}
		else
		{
			votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Text, label_name, number, config.getPadding(), numberWidth, labelConf, width, height));
		}
	}
	else
		votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Text, label_name, number, config.getPadding(), numberWidth, labelConf, width, height));

	eventbox = manage(new EventBox());
	eventbox->set_name("party_widget_event_box");
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	
	if (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getEnableClick())
	{
		eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &PartyWidget::on_party_clicked));
	}

	eventbox->add(*votingWidget);
	add(*eventbox);
	show();
}

PartyWidget::PartyWidget(string text, int width, int height)
{
	set_size_request(width, height);
	set_name("voting_experience_party_widget");
	
	PartyWidgetConfiguration config = SAESGUIConfigurationManager::Current()->GetPartyWidgetConfiguration();
	if(!config.getShowFrame()) 
		set_shadow_type (SHADOW_NONE);
	else
		set_shadow_type (SHADOW_IN);

	LabelConfiguration labelConf = SAESGUIConfigurationManager::Current()->GetPartyNullLabelConfiguration();
	
	labelString = manage(new Label(text));
	LabelConfiguration::SetLabelConfiguration(labelString, labelConf);
	eventbox = manage(new EventBox());
	eventbox->set_name("party_widget_event_box");
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	
	if (SAESGUIConfigurationManager::Current()->GetPartySelectionConfiguration().getEnableClick())
	{
		eventbox->signal_button_press_event().connect(sigc::mem_fun(*this, &PartyWidget::on_party_null_clicked));
	}

	eventbox->add(*labelString);
	add(*eventbox);
	show();
}

void PartyWidget::RefreshLabel(string text)
{
	labelString->set_text(text);
}

PartyWidget::~PartyWidget()
{

}

PartyWidget::type_party_clicked PartyWidget::signal_party_clicked()
{
  return m_party_clicked;
}

PartyWidget::type_party_null_clicked PartyWidget::signal_party_null_clicked()
{
  return m_party_null_clicked;
}

bool PartyWidget::on_party_clicked(GdkEventButton* event)
{
	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getPartySelectSound());
	m_party_clicked.emit(party);
	return true;
}

bool PartyWidget::on_party_null_clicked(GdkEventButton* event)
{
	Smartmatic::System::Sounds::SMTTSoundsManager::Current()->Sound(SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getPartySelectSound());
	m_party_null_clicked.emit();
	return true;
}
