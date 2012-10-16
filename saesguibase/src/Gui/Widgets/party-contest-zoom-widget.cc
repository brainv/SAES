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

#include "Gui/Widgets/party-contest-zoom-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::Election;

PartyContestZoomWidget::PartyContestZoomWidget(std::string partyCode, std::string contestCode,Smartmatic::SAES::Voting::Vote::Vote & vote)
{
	Label* labelPrincipal = manage(new Label());
	labelPrincipal->set_alignment(0.5, 0.5);	//TODO configuration
	labelPrincipal->set_padding(10, 0);
	labelPrincipal->set_size_request(-1,-1);
	labelPrincipal->set_line_wrap(true);	
	labelPrincipal->set_label(_("Smartmatic.SAES.GUI.Widgets.PartyContestZoomWidget.TextPrincipal"));
	Pango::FontDescription fontTitle = labelPrincipal->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelPrincipal->modify_font(fontTitle);

	Label* labelStandIn = manage(new Label());
	labelStandIn->set_alignment(0.5, 0.5);	//TODO configuration
	labelStandIn->set_padding(10, 0);
	labelStandIn->set_size_request(-1, -1);
	labelStandIn->set_line_wrap(true);	
	labelStandIn->set_label(_("Smartmatic.SAES.GUI.Widgets.PartyContestZoomWidget.TextStandIN"));
	fontTitle = labelStandIn->get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	labelStandIn->modify_font(fontTitle);
	
	hboxButton.set_layout(BUTTONBOX_CENTER);
	hboxButton.set_size_request (100,60);
	hboxButton.add(buttonback);
	buttonback.WidgetsPosition (5,0,0);	
	buttonback.signal_clicked().connect( sigc::mem_fun(this, &PartyContestZoomWidget::on_buttonBack_clicked));
	buttonback.set_size_request (100,60);	
	buttonback.SetLabel(_("Smartmatic.SAES.GUI.Widgets.PartyContestZoomWidget.Back"));

	bool hasListSelected = false;
	
	try
	{
		Contest contest = MachineOperationManager::getInstance()->getElectoralConfiguration()->getContestByCode(contestCode);

		std::list < Ballot_option > & ballotList (MachineOperationManager::getInstance()->getElectoralConfiguration()->getBallotOptionsListByContestParty(contestCode, partyCode));
		std::list < Ballot_option > & ballotsInContestPartyPrincipal (MachineOperationManager::getInstance()->getElectoralConfiguration()->getBallotOptionsPrincipalByContestParty(contestCode, partyCode));
		std::list < Ballot_option > & ballotsInContestPartyStandIn (MachineOperationManager::getInstance()->getElectoralConfiguration()->getBallotOptionsStandInByContestParty(contestCode, partyCode));
		list<Ballot_option>::iterator ballotIt;

		//hboxPrincipal.set_spacing(10);
		tablePrincipal.set_homogeneous(true);

		//table parameters
		unsigned int totalPrincipals = 0;
		for(unsigned int k=0;k < vote.getSelections().size();k++)
		{
			for(unsigned int l=0;l < vote.getSelections()[k].getBallotOptions().size();l++)
			{
				for ( ballotIt=ballotsInContestPartyPrincipal.begin() ; ballotIt != ballotsInContestPartyPrincipal.end(); ballotIt++ )
				{
					if(vote.getSelections()[k].getBallotOptions()[l].compare(ballotIt->getCode())==0)
					{
						totalPrincipals++;
//						Eligible_option eOption = MachineOperationManager::getInstance()->getElectoralConfiguration()->getEligibleOptionFromBallotOptionCode (contestCode, (*ballotIt).getCode());
//						if(eOption.getParent_code().compare("")==0)
//							totalPrincipals--;
					}
				}
			}
		}

		bool selectList = false;

        for(unsigned int k=0;k < vote.getSelections().size() && !selectList;k++)
        {
            for(unsigned int l=0;l < vote.getSelections()[k].getBallotOptions().size() && !selectList;l++)
            {
                for ( ballotIt=ballotList.begin() ; ballotIt != ballotList.end() && !selectList; ballotIt++ )
                {
                    if(vote.getSelections()[k].getBallotOptions()[l].compare(ballotIt->getCode())==0)
                    {
                        selectList = true;
                    }
                }
            }
        }

		unsigned int totalStandIn = 0;
		for(unsigned int k=0;k < vote.getSelections().size();k++)
		{
			for(unsigned int l=0;l < vote.getSelections()[k].getBallotOptions().size();l++)
			{
				for ( ballotIt=ballotsInContestPartyStandIn.begin() ; ballotIt != ballotsInContestPartyStandIn.end(); ballotIt++ )
				{
					if(vote.getSelections()[k].getBallotOptions()[l].compare(ballotIt->getCode())==0)
					{
						totalStandIn++;
					}
				}
			}
		}

		bool principal=false;
		bool standin=false;

		unsigned int pRow = 0;
		unsigned int pCol = 7;

		//table calculation
		if(totalStandIn == 0)
		{
			pCol = 11;
		}
		
		pRow = totalPrincipals / pCol;
		float rest = totalPrincipals % pCol;
		pRow = rest > 0.0 ? pRow + 1 : pRow;

		unsigned int pColTable = 0;
		unsigned int pRowTable = 0;
		
        if(selectList)
        {
            Label* labelChoice = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.PartyContestZoomWidget.FullPartySelected")));
            colorFrame.set_rgb (0xFFFF,0xFFFF,0xFFFF);
            //colorFrame.set_rgb (35500,35500,35500);
            eventFP.modify_bg(Gtk::STATE_NORMAL, colorFrame);
            //FONT
            Pango::FontDescription fontTitle = labelChoice->get_style()->get_font();
            fontTitle.set_size(12*Pango::SCALE);
            fontTitle.set_weight(Pango::WEIGHT_BOLD);
            labelChoice->modify_font(fontTitle);

            eventFP.add(*labelChoice);
            FrameFP.add(eventFP);
            FrameFP.show_all_children ();
            hasListSelected = true;
        }

		for(unsigned int k=0;k < vote.getSelections().size();k++)
		{
			for(unsigned int l=0;l < vote.getSelections()[k].getBallotOptions().size();l++)
			{
				for ( ballotIt=ballotsInContestPartyPrincipal.begin() ; ballotIt != ballotsInContestPartyPrincipal.end(); ballotIt++ )
				{
					if(vote.getSelections()[k].getBallotOptions()[l].compare(ballotIt->getCode())==0)
					{						
						Eligible_option eOption = MachineOperationManager::getInstance()->getElectoralConfiguration()->getEligibleOptionFromBallotOptionCode (contestCode, (*ballotIt).getCode());

						static Smartmatic::SAES::Configuration::BallotOptionWidgetConfiguration config = 
						Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();
						
						string label_name = eOption.getBallot_name_key ();
						string separator = config.getSeparatorCharacter();
						size_t found = label_name.find_first_of(separator);

						if(found != string::npos)
						{
							string label1,label2;
							if(config.getNameIsBeforeSeparator())
							{
								label1 = label_name.substr(0, found);
								label2 = label_name.substr(found + 1);
							}
							else
							{
								label2 = label_name.substr(0, found);
								label1 = label_name.substr(found + 1);
							}
							label_name = label1 + label2;
						}
						
                        Label* labelChoice = manage(new Label(label_name));
                        if(!principal)
                        {
                            colorFrame.set_rgb (0xFFFF,0xFFFF,0xFFFF);
                            eventPrincipal.modify_bg(Gtk::STATE_NORMAL, colorFrame);
                            eventPrincipal.add(*labelPrincipal);

                            FramePrincipal.show_all_children ();
                            FramePrincipal.add(eventPrincipal);
                            hboxTituloPrincipal.pack_start (FramePrincipal,Gtk::PACK_SHRINK);
                            vboxScroll.pack_start (hboxTituloPrincipal,false,false,8);

                            principal=true;
                        }

                        labelChoice->set_padding(5, 0);
                        Frame* FrameStyle=manage(new Frame());
                        FrameStyle->show_all_children ();
                        FrameStyle->add(*labelChoice);

                        tablePrincipal.attach(*FrameStyle, pRowTable, pRowTable + 1, pColTable, pColTable + 1, FILL,SHRINK, 3, 0);

                        pRowTable++;

                        if(pRowTable == pRow)
                        {
                            pRowTable = 0;
                            pColTable++;
                        }

                        break;
					}
				}
			}
		}
		if(principal)
		{
			vboxScroll.pack_start (tablePrincipal,false,false);
		}

		unsigned int sRow = 0;
		unsigned int sCol = 3;

		sRow = totalStandIn / sCol;
		rest = totalStandIn % sCol;
		sRow = rest > 0.0 ? sRow + 1 : sRow;

		if(sRow < pRow)
		{
			sRow = pRow;
			sCol = 1;

			sCol = totalStandIn / sRow;
			rest = totalStandIn % sRow;
			sCol = rest > 0.0 ? sCol + 1 : sCol;
		}

		unsigned int sColTable = 0;
		unsigned int sRowTable = 0;

		tableStandIn.set_homogeneous(true);

		if(totalStandIn != 0)
		{
			for(unsigned int k=0;k < vote.getSelections().size();k++)
			{
				for(unsigned int l=0;l < vote.getSelections()[k].getBallotOptions().size();l++)
				{
					for ( ballotIt=ballotsInContestPartyStandIn.begin() ; ballotIt != ballotsInContestPartyStandIn.end(); ballotIt++ )
					{
						if(vote.getSelections()[k].getBallotOptions()[l].compare(ballotIt->getCode())==0)
						{						
							Eligible_option eOption = MachineOperationManager::getInstance()->getElectoralConfiguration()->getEligibleOptionFromBallotOptionCode (contestCode, (*ballotIt).getCode());;

							static Smartmatic::SAES::Configuration::BallotOptionWidgetConfiguration config = 
							Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->GetBallotOptionWidgetConfiguration();
							
							string label_name = eOption.getBallot_name_key ();
							string separator = config.getSeparatorCharacter();
							size_t found = label_name.find_first_of(separator);

							if(found != string::npos)
							{
								string label1,label2;
								if(config.getNameIsBeforeSeparator())
								{
									label1 = label_name.substr(0, found);
									label2 = label_name.substr(found + 1);
								}
								else
								{
									label2 = label_name.substr(0, found);
									label1 = label_name.substr(found + 1);
								}
								label_name = label1 + label2;
							}
							
							Label* labelChoice = manage(new Label(label_name));
						
							if(!standin)
							{
								colorFrame.set_rgb (0xFFFF,0xFFFF,0xFFFF);
								eventStandIn.modify_bg(Gtk::STATE_NORMAL, colorFrame);
								eventStandIn.add(*labelStandIn);
								FrameStandIn.add(eventStandIn);																			
								FrameStandIn.show_all_children ();
								hboxTituloStandIn.pack_start (FrameStandIn,Gtk::PACK_SHRINK);			
								vboxScroll.pack_start (hboxTituloStandIn,false,false,8);
								standin=true;
							}	
							labelChoice->set_padding(5, 0);
							Frame* FrameStyle=manage(new Frame ());									
							FrameStyle->add(*labelChoice);
							FrameStyle->show_all_children ();									

							tableStandIn.attach(*FrameStyle, sRowTable, sRowTable + 1, sColTable, sColTable + 1, FILL,SHRINK, 3, 0);

							sRowTable++;
					
							if(sRowTable == sRow)
							{
								sRowTable = 0;
								sColTable++;
							}
							break;
						}
					}
				}
			}
		}
		if(standin)//TODO configurable
		{
			vboxScroll.pack_start(tableStandIn,false,false);
		}
	}
	catch(Smartmatic::System::Exception::ElectionException & ex)
	{
		
	}
	//vboxScroll.set_size_request (-1,150);
	
	Align.add(vboxScroll);
	Align.set_padding(10, 10, 10, 10);
	Align.show_all_children ();
	scroll.add(Align);
	scroll.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);
	scroll.show_all_children ();
	vboxTotal.add(scroll);

	if(hasListSelected)
	{
		FrameFP.set_size_request(300,-1);
		hboxFP.pack_start(FrameFP,false,false);
	}
	
	hboxFP.add(hboxButton);
	hboxFP.set_size_request(-1,70);
	vboxTotal.pack_start(hboxFP,false,false);
	vboxScroll.show_all_children ();
	add(vboxTotal);
	show_all_children ();
}

void PartyContestZoomWidget::on_buttonBack_clicked()
{
	signalEmitted.emit();	
}

PartyContestZoomWidget::~PartyContestZoomWidget()
{
	
}
