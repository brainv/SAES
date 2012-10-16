/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	party-contest-viewer-widget.h
 *
 * @brief	Declares the party contest viewer widget class.
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

#ifndef _PARTY_CONTEST_VIEWER_WIDGET_H_
#define _PARTY_CONTEST_VIEWER_WIDGET_H_
#include <gtkmm.h>
#include "Voting/Vote/vote-schema.hxx"
#include "Gui/Widgets/party-contest-zoom-widget.h"
#include <Gui/Widgets/party-contest-widget.h>

namespace Smartmatic
{
	namespace Log
	{
		class ISMTTLog;
	}

	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	PartyContestViewerWidget
				 *
				 * @brief	Header class PartyContestViewerWidget.
				 *
				 * @author	Marcel Mancini &lt;marcel.mancini@smartmatic.com&gt;
				 * @date	4/29/2011
				 */

				class PartyContestViewerWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	PartyContestViewerWidget::PartyContestViewerWidget(Smartmatic::SAES::Voting::Vote::Vote &vote);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	vote	The vote.
					 */

					PartyContestViewerWidget(Smartmatic::SAES::Voting::Vote::Vote vote, bool showTableVertical);

					/**
					 * @fn	PartyContestViewerWidget::~PartyContestViewerWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PartyContestViewerWidget();
		    		           			
				protected:

					/**
					 * @fn	void PartyContestViewerWidget::on_back_partyZoom_clicked();
					 *
					 * @brief	Handles back party zoom clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_back_partyZoom_clicked();
		          		          
				private:

					/**
					 * @fn	void PartyContestViewerWidget::on_selected_clicked(std::string party,
					 * 		std::string contest);
					 *
					 * @brief	Executes the selected clicked action.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	party  	The party.
					 * @param	contest	The contest.
					 */

					void on_selected_clicked(std::string party, std::string contest);

					/**
					 * @fn	void PartyContestViewerWidget::FillMatrix();
					 *
					 * @brief	Fill matrix.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void FillMatrix(std::list<Smartmatic::SAES::Voting::Election::Contest> & contests,
									std::list<Smartmatic::SAES::Voting::Election::Party> & parties,
									bool showTableVertical);

					Gtk::ScrolledWindow scroll; ///< The scroll
					Gtk::Table tablePartyContest;   ///< The table party contest
					Gtk::Label labelVoteMode;   ///< The label of the vote mode
					Gtk::Label labelVoteSuperNull;   ///< The label of the vote mode
					Gtk::VBox vboxPrincipal;   ///< The principal vbox
					//std::vector<Smartmatic::SAES::Voting::Election::Contest> contests;  ///< The contests
					//std::vector<Smartmatic::SAES::Voting::Election::Party> parties; ///< The parties
					Smartmatic::SAES::Voting::Election::ElectionWrapper* election;  ///< The election
					Smartmatic::SAES::Voting::VotingDevice::VotingDeviceWrapper *votingDev; ///< The voting development
					Smartmatic::SAES::Voting::Vote::Vote vote;  ///< The vote
					static Smartmatic::Log::ISMTTLog* logger;   ///< The logger

					PartyContestWidget* partyContestLabels;
					PartyContestZoomWidget*  zoomWidget;	///< The zoom widget
					std::list < PartyContestWidget* > contestWidgetList;

					int contestListSize;   ///< The contest list size
					int partyListSize;   ///< The party list size
				};
			}
		}
	}
}

#endif // _PARTY_CONTEST_VIEWER_WIDGET_H_
