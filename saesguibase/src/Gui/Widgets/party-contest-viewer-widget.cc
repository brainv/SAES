/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include <Voting/VotingDevice/VotingDeviceWrapper.hxx>
#include <Voting/Election/ElectionWrapper.hxx>
#include <Gui/Widgets/party-contest-viewer-widget.h>
#include <System/Exception/ElectionException.hxx>
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-conf-manager.h"
#include <Operation/Voting/VotingOperation.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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

using namespace Gtk;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::GUI::Operation::Voting;
using namespace Smartmatic::Log;

ISMTTLog* PartyContestViewerWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget",GETTEXT_PACKAGE);

PartyContestViewerWidget::PartyContestViewerWidget(Vote::Vote vote, bool showTableVertical)
: vote(vote)
{
	zoomWidget = NULL;
	partyContestLabels = NULL;

	election = MachineOperationManager::getInstance()->getElectoralConfiguration()->getElection();
	votingDev = MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice();

	//std::list<Smartmatic::SAES::Voting::Election::Contest> contests;  ///< The contests
	std::list<Smartmatic::SAES::Voting::Election::Party> parties; ///< The parties

	VotingDevice::Voting_device vd = votingDev->getFirstVotingDevice();

	if(vote.getLogicalVoterGroup().compare(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getLogicalVoterGroupCode())!=0)
	{
		std::string contestGroupCode = votingDev->getLogicalVoterGroup( vd, vote.getLogicalVoterGroup()).getContest_group_code ();
		std::list < Election::Contest > & contestsList (MachineOperationManager::getInstance()->getElectoralConfiguration()->getListContestByContestGroupCode(contestGroupCode) );
		std::list<Election::Contest>::iterator contestIt;

		contestListSize = contestsList.size();

		if(showTableVertical)
			partyContestLabels = new PartyContestWidget(false,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.PartiesContest"), true,"party","contest",PartyContestWidget::ImageType_Selected,true,false);
		else
			partyContestLabels = new PartyContestWidget(false,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.ContestParties"), true,"party","contest",PartyContestWidget::ImageType_Selected,true,false);

		partyContestLabels->set_visible(true);

		tablePartyContest.attach(* partyContestLabels,0,1,0,1,Gtk::SHRINK,Gtk::SHRINK,0,0);

		tablePartyContest.set_col_spacings(0);
		tablePartyContest.set_row_spacings(0);

		int contestsIndex = 0;
		int partyIndex = 0;

		for ( contestIt=contestsList.begin() ; contestIt != contestsList.end(); contestIt++ )
		{
			//create contest widgets
			//contests.push_back(*contestIt);

			PartyContestWidget * contestWidget = new PartyContestWidget(false,contestIt->getCustom_code(), true,"","",PartyContestWidget::ImageType_Selected,true,false);
			contestWidgetList.push_back(contestWidget);

			contestWidget->set_visible(true);
			contestWidget->setIsVisibleImage(false);

			if(showTableVertical)
				tablePartyContest.attach(*contestWidget, contestsIndex+1, contestsIndex+2, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
			else
				tablePartyContest.attach(*contestWidget, 0, 1, contestsIndex+1, contestsIndex+2, Gtk::FILL, Gtk::FILL, 0, 0);
			contestsIndex++;



			//create party widgets for each contest
			std::list<Election::Party> & partyList (MachineOperationManager::getInstance()->getElectoralConfiguration()->getListPartyByContestCode((*contestIt).getCode()));
			std::list<Election::Party>::iterator partyIt;

			for ( partyIt=partyList.begin() ; partyIt != partyList.end(); partyIt++ )
			{
				bool partyFound = false;

				std::list<Smartmatic::SAES::Voting::Election::Party>::iterator iterParty;
				for(iterParty = parties.begin(); iterParty != parties.end(); iterParty++)
				{
					if(partyIt->getAbbreviation ().get().compare(iterParty->getAbbreviation().get())==0)
					{
						partyFound = true;
						break;
					}
				}

				if(!partyFound)
				{
					parties.push_back(*partyIt);

					PartyContestWidget* partyWidget = new PartyContestWidget(false,partyIt->getName().get(), true,"","",PartyContestWidget::ImageType_Selected,true,false);
					contestWidgetList.push_back(partyWidget);

					partyWidget->set_visible(true);
					partyWidget->setIsVisibleImage(false);

					if(showTableVertical)
						tablePartyContest.attach(*partyWidget, 0, 1, partyIndex+1, partyIndex+2, Gtk::FILL, Gtk::FILL, 0, 0);
					else
						tablePartyContest.attach(*partyWidget, partyIndex+1, partyIndex+2, 0, 1, Gtk::FILL, Gtk::FILL, 0, 0);
					partyIndex++;
				}
			}
		}

		partyListSize = parties.size();

		tablePartyContest.resize(contestListSize+1,partyListSize+1);
		tablePartyContest.set_visible(true);
		scroll.add(tablePartyContest);

		FillMatrix(contestsList, parties, showTableVertical);
	}
	else
	{
		Pango::FontDescription fontSuperNull = labelVoteSuperNull.get_style()->get_font();
		fontSuperNull.set_size(16*Pango::SCALE);
		fontSuperNull.set_weight(Pango::WEIGHT_ULTRABOLD);
		labelVoteSuperNull.modify_font(fontSuperNull);	
		labelVoteSuperNull.set_visible (true);	
		labelVoteSuperNull.set_label (_("Smartmatic.SAES.GUI.Functionality.PartyContestViewerWidget.VoteIsSuperNull"));
		scroll.add(labelVoteSuperNull);
	}

	scroll.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
	scroll.set_visible(true);

	vboxPrincipal.set_homogeneous (false);
	vboxPrincipal.pack_start(labelVoteMode,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start(scroll,Gtk::PACK_EXPAND_WIDGET);
	vboxPrincipal.set_visible (true);
	vboxPrincipal.show_all_children ();
	add(vboxPrincipal);	

	Pango::FontDescription fontMessage = labelVoteMode.get_style()->get_font();
	fontMessage.set_size(12*Pango::SCALE);
	fontMessage.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelVoteMode.modify_font(fontMessage);	
	labelVoteMode.set_visible (true);	

	show_all_children ();

	switch(VotingOperation::getVoteMode())
	{
		case Vote::VoteMode::VOTE_D:
			labelVoteMode.set_label (_("Smartmatic.SAES.GUI.Functionality.PartyContestViewerWidget.VoteMarkedAsDemo"));
			break;
		case Vote::VoteMode::VOTE_O:
			labelVoteMode.set_label (_("Smartmatic.SAES.GUI.Functionality.PartyContestViewerWidget.VoteMarkedAsOfficial"));
			break;
		case Vote::VoteMode::VOTE_R:
			labelVoteMode.set_label (_("Smartmatic.SAES.GUI.Functionality.PartyContestViewerWidget.VoteMarkedAsRecovery"));
			break;
		case Vote::VoteMode::VOTE_S:
			labelVoteMode.set_label (_("Smartmatic.SAES.GUI.Functionality.PartyContestViewerWidget.VoteMarkedAsSimulated"));
			break;
	}	
}

void PartyContestViewerWidget::FillMatrix(std::list<Smartmatic::SAES::Voting::Election::Contest> & contests,
										  std::list<Smartmatic::SAES::Voting::Election::Party> & parties,
										  bool showTableVertical)
{
	std::list<Smartmatic::SAES::Voting::Election::Contest>::iterator iterContest;
	std::list<Smartmatic::SAES::Voting::Election::Party>::iterator iterParty;

	int i = 0;
	for(iterContest = contests.begin(); iterContest != contests.end(); iterContest++)
	{
		int j = 0;
		for(iterParty = parties.begin(); iterParty != parties.end(); iterParty++)
		{
			PartyContestWidget* partyContest = NULL;

			try
			{
				bool found = false;
				Election::Party dummyParty;
				if(election->getIfCanPartyAbbByContest (*iterContest, iterParty->getAbbreviation().get(), dummyParty))
				{
					//Party dummyParty = election->getPartyAbbByContest (*iterContest, iterParty->getAbbreviation().get());
					for(unsigned int k=0;k < vote.getSelections().size();k++)
					{
						try
						{
						    Election::Ballot_option ballot;
							if(vote.getSelections()[k].getBallotOptions().size()>0)
							{
								if(vote.getSelections()[k].getBallotOptions ()[0].compare(Smartmatic::SAES::Configuration::SAESConfigurationManager::Current()->getVoteDummyConfiguration().getBallotOptionCode())!=0)
								{
									ballot.setCode(vote.getSelections()[k].getBallotOptions ()[0]);
									Election::Eligible_option eOption;
									if(election->getIfCanEligibleOptionByBallotOption( *iterContest, ballot, eOption))
									{
										//Eligible_option eOption = election->getEligibleOptionByBallotOption ( *iterContest, ballot);
										if(eOption.getBallot_options ().getBallot_option()[0].getParty().getAbbreviation().get().compare(iterParty->getAbbreviation().get())==0)
										{
											partyContest = new PartyContestWidget(true,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.Selected"), true,dummyParty.getCode(),iterContest->getCode(),PartyContestWidget::ImageType_Selected,true,false);
											contestWidgetList.push_back(partyContest);
											partyContest->signalEmitted.connect(sigc::mem_fun(*this, &PartyContestViewerWidget::on_selected_clicked));
											found = true;
											break;
										}
									}
								}
							}
						}
						catch(Smartmatic::System::Exception::ElectionException ex)
						{
							std::stringstream ss;
							ss<< "FATAL - " << __func__ << " " << __LINE__ << " " << __FILE__ << ": " << ex.what();
							logger->Debug (ss.str());
						}
						if(!found)
						{
							partyContest = new PartyContestWidget(true,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.NotSelected"), true,"","",PartyContestWidget::ImageType_Unselected,true,false);
							contestWidgetList.push_back(partyContest);
						}
					}
				}
			}
			catch(Smartmatic::System::Exception::ElectionException & ex)
			{
				partyContest = new PartyContestWidget(true,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.N/A"), true,"","",PartyContestWidget::ImageType_NotApplicable,true,false);
				contestWidgetList.push_back(partyContest);
			}

			if(!partyContest)
			{
				partyContest = new PartyContestWidget(true,_("Smartmatic.SAES.GUI.Widgets.PartyContestViewerWidget.N/A"), true,"","",PartyContestWidget::ImageType_NotApplicable,true,false);
				contestWidgetList.push_back(partyContest);
			}

			partyContest->set_visible(true);

			if(showTableVertical)
				tablePartyContest.attach(*partyContest, i+1, i+2, j+1, j+2, Gtk::FILL, Gtk::FILL, 0, 0);
			else
				tablePartyContest.attach(*partyContest, j+1, j+2, i+1, i+2, Gtk::FILL, Gtk::FILL, 0, 0);

			j++;
		}
		i++;
	}
}

void PartyContestViewerWidget::on_back_partyZoom_clicked()
{
	remove();
	add(vboxPrincipal);
	vboxPrincipal.set_visible (true);
	vboxPrincipal.show_all_children ();
	show_all_children ();
}

void PartyContestViewerWidget::on_selected_clicked(std::string party, std::string contest)
{
	remove();
	if(zoomWidget) delete zoomWidget;
	zoomWidget = new PartyContestZoomWidget(party,contest,vote);
	zoomWidget->signalEmitted.connect(sigc::mem_fun(*this,&PartyContestViewerWidget::on_back_partyZoom_clicked));
	add(*zoomWidget);
	show_all_children ();
}

PartyContestViewerWidget::~PartyContestViewerWidget()
{
	if(zoomWidget) delete zoomWidget;
	if (partyContestLabels) delete partyContestLabels;

	std::list < PartyContestWidget* >::iterator it;

	for (it = contestWidgetList.begin();
		 it != contestWidgetList.end();
		 it++)
	{
		delete (*it);
	}

}
