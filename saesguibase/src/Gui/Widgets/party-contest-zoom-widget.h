/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C) SmartMatic 2011 <>
 * 
 * @file	party-contest-zoom-widget.h
 *
 * @brief	Declares the party contest zoom widget class.
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

#ifndef _PARTY_CONTEST_ZOOM_WIDGET_H_
#define _PARTY_CONTEST_ZOOM_WIDGET_H_

#include <gtkmm.h>
#include "Voting/Vote/vote-schema.hxx"
#include "Widgets/smartmatic-button.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	PartyContestZoomWidget
				 *
				 * @brief	Party contest zoom widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class PartyContestZoomWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	PartyContestZoomWidget::PartyContestZoomWidget(std::string partyCode,
					 * 		std::string contestCode,Smartmatic::SAES::Voting::Vote::Vote vote);
					 *
					 * @brief	Constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	partyCode  	The party code.
					 * @param	contestCode	The contest code.
					 * @param	vote	   	The vote.
					 */

					PartyContestZoomWidget(std::string partyCode, std::string contestCode,Smartmatic::SAES::Voting::Vote::Vote & vote);

					/**
					 * @fn	PartyContestZoomWidget::~PartyContestZoomWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PartyContestZoomWidget();

					/**
					 * @fn	void PartyContestZoomWidget::on_buttonBack_clicked();
					 *
					 * @brief	Handles button back clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_buttonBack_clicked();
					sigc::signal<void> signalEmitted;   ///< The signal emitted
				protected:

				private:
					Gtk::EventBox eventFP;  ///< The event fp
					Gtk::EventBox eventPrincipal;   ///< The event principal
					Gtk::EventBox eventStandIn; ///< The event stand in
					Gtk::ScrolledWindow scroll; ///< The scroll
					// Gtk::HBox hboxPrincipal; 
					Gtk::Table tablePrincipal;  ///< The table principal
					//Gtk::HBox hboxPrincipal2;
					Gtk::Table tableStandIn;	///< The table stand in
					Gtk::HBox hboxTituloPrincipal;  ///< The hbox titulo principal
					Gtk::HBox hboxTituloStandIn;	///< The hbox titulo stand in
					Gtk::VBox vboxTotal;	///< The vbox total
					Gtk::VBox vboxScroll;   ///< The vbox scroll
					Gtk::HBox hboxFP;   ///< The hbox fp
					Gtk::Frame FrameFP; ///< The frame fp
						
					
					//Gtk::Frame FrameStyle;
					Gtk::Frame FramePrincipal;  ///< The frame principal
					Gtk::Frame FrameStandIn;	///< The frame stand in
					Smartmatic::SAES::Voting::Vote::Vote vote;  ///< The vote
					Gdk::Color colorFrame;  ///< The color frame
					Gtk::Alignment Align;   ///< The align
					Smartmatic::GUI::Widgets::SmartmaticButton buttonback;  ///< The buttonback
					Gtk::HButtonBox hboxButton; ///< The hbox button
				};
			}
		}
	}
}

#endif // _PARTY_CONTEST_ZOOM_WIDGET_H_
