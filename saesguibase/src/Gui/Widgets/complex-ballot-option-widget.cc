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

#include "Configuration/label-configuration.h"
#include "Gui/Widgets/ballot-option-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include "Gui/Widgets/complex-ballot-option-widget.h"
#include "Configuration/GeneratedClasses/Configuration/SaesGUIConfiguration-schema.hxx"
#include "Runtime/Environment/saes-directories.h"
#include "System/IO/File.h"

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Voting::Election;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::System::IO;

ComplexBallotOptionWidget::ComplexBallotOptionWidget(Eligible_option& eligibleOption, 
                                                     Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
                                                     bool isPrincipal)
:BallotOptionWidget(eligibleOption, saesDir, isPrincipal, -1, -1, false, true)
{
	circle = new CircleWidget();
	circle->set_size_request(30, -1);
	
	stringstream ss;
	ss << this->ballotOption.getTally_position();

	static BallotOptionWidgetConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();

	static LabelConfiguration numberChildConfiguration = SAESGUIConfigurationManager::Current()->GetVotingWidgetNumberChildLabelConfiguration();;
	
	string number = ss.str();
	int numberWidth = config.getNumberWidth();

	numberLabel = manage(new Gtk::Label());
	numberLabel->set_text(number);
	numberLabel->set_size_request(numberWidth, -1);
	Smartmatic::GUI::Configuration::LabelConfiguration::SetLabelConfigurationWithoutAlignment(numberLabel, numberChildConfiguration);
	
	hbox = manage(new HBox(false, 10));
	eventbox->remove();
	eventbox->add(*hbox);
	hbox->pack_start(*numberLabel, false, false);	
	hbox->pack_start(*circle, false, false);
	hbox->pack_start(*votingWidget);
	
	show_all_children();
}

ComplexBallotOptionWidget::~ComplexBallotOptionWidget()
{
	
}

void ComplexBallotOptionWidget::ForceShowImage(int imageHeight, float imageRelation)
{
	static BallotOptionWidgetConfiguration config = 
		SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();
	
	SaesDirectories saesDir;
	string image_path = ballotOption.getImage_file_name() != NULL ?  saesDir.getImageElectoralResource(ballotOption.getImage_file_name().get())  : "";

	if(File::canOpenFile(image_path))
	{
		if(votingWidget)
		{
			hbox->remove(*votingWidget);
			delete votingWidget;
		}

		BallotOptionWidgetConfiguration config2 = SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();
	
		int numberWidth = config2.getNumberWidth();
		int spacing = config2.getPadding();
		int spacing2 = SAESGUIConfigurationManager::Current()->GetBallotOptionSelectionConfiguration().getImageInListPadgging();



		//calculate widget size
		float imageWidth = imageHeight * imageRelation;
	
		votingWidget = manage(new VotingWidgetBase(VotingWidgetBase::VotingWidgetBase_Image, image_path, "0", spacing, numberWidth, imageWidth, (int)imageHeight, false));
		votingWidget->set_size_request(imageWidth, imageHeight);
	
		eventbox->remove();
	
		HBox* newHbox = manage(new HBox(false, spacing2));
		newHbox->pack_start(*hbox, false, false);
		newHbox->pack_start(*votingWidget, false, false);

		eventbox->add(*newHbox);
	}
}

bool ComplexBallotOptionWidget::on_ballot_clicked(GdkEventButton* event)
{
	BallotOptionWidget::on_ballot_clicked(event);
	circle->SetMark(isSelected);
	return true;
}

void ComplexBallotOptionWidget::SetSelection(bool select, bool sendSignal)
{
	BallotOptionWidget::SetSelection(select, sendSignal);
	circle->SetMark(isSelected);
}
