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
 * See BallotOptionthe GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file referendum-widget.h
 * @brief referendum widget in voting experience
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _REFERENDUM_WIDGET_H_
#define _REFERENDUM_WIDGET_H_

#include <gtkmm.h>
#include "voting-widget-base.h"
#include "Voting/Election/election-schema.hxx"
#include "Runtime/Environment/saes-directories.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	ReferendumWidget
				 *
				 * @brief	Referendum widget.
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class ReferendumWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	ReferendumWidget::ReferendumWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir, bool isPrincipal,
					 * 		bool showNumber= true);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	elegibleOption	ballot option to be displayed.
					 * @param	saesDir				  	The saes dir.
					 */

					ReferendumWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption,
							Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir);

					/**
					 * @fn	ReferendumWidget::~ReferendumWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~ReferendumWidget();

					/**
					 * @fn	std::string ReferendumWidget::GetBallotOptionCode();
					 *
					 * @brief	method to obtain the ballot option code.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	ballot option code.
					 */

					std::string GetBallotOptionCode();

					/**
					 * @typedef	sigc::signal<void, std::string, bool, bool> type_ballot_clicked
					 *
					 * @brief	definition of ballot clicked signal.
					 *
					 * ### param	_sent	string ballot option code licked.
					 * ### param	_sent	bool if ballot is selected.
					 */

					typedef sigc::signal<void, std::string, bool> type_ballot_clicked;

					/**
					 * @fn	type_ballot_clicked ReferendumWidget::signal_ballot_clicked();
					 *
					 * @brief	method to connect to receive the signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	signal.
					 */

					type_ballot_clicked signal_ballot_clicked();
					
					/**
					 * @fn	virtual void ReferendumWidget::SetSelection(bool select, bool sendSignal = false);
					 *
					 * @brief	select the ballot option widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	select	  	if ballot is selected.
					 * @param	sendSignal	if send click signal or just change visual color.
					 */

					void SetSelection(bool select, bool sendSignal = false);

				protected:
		            /**
	        		 * declaration of signal handler
		             */
					type_ballot_clicked m_ballot_clicked;   ///< The ballot clicked

					/**
					 * @fn	virtual bool ReferendumWidget::on_ballot_clicked(GdkEventButton* event);
					 *
					 * @brief	method that receives event box button press mask.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	event	importance, only sintax requirement.
					 *
					 * @return	without importance, only sintax requirement.
					 */

					virtual bool on_ballot_clicked(GdkEventButton* event);
						
				//private:

					/**
					 * @fn	void ReferendumWidget::InitializeWidget();
					 *
					 * @brief	initialize widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void InitializeWidget();
						
					/**
					 * Child Widgets 
					 */
					Gtk::EventBox* eventbox;	///< The eventbox
					VotingWidgetBase* votingWidget; ///< The voting widget
					Gdk::Color selectedColor;   ///< The selected color
					Gdk::Color unSelectedColor; ///< The un selected color
					bool isSelected;	///< Is selected flag

					/**
					 * SAES voting objects
					 */
   					Smartmatic::SAES::Voting::Election::Ballot_option ballotOption; ///< The ballot option
  					Smartmatic::SAES::Voting::Election::Contest contest;	///< The contest

					/**
					 * Variables
					 */
					std::string SoundBallot;	///< The sound ballot
					
				};
			}
		}
	}
}

#endif // _REFERENDUM_WIDGET_H_
