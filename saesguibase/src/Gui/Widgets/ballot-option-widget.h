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
 * @file ballot-option-widget.h
 * @brief ballot option widget in voting experience
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _BALLOT_OPTION_WIDGET_H_
#define _BALLOT_OPTION_WIDGET_H_

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
				 * @class	BallotOptionWidget
				 *
				 * @brief	Ballot option widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class BallotOptionWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	BallotOptionWidget::BallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption,
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
					 * @param	isPrincipal			  	is ballot option is principal.
					 * @param	width			  		Widget's width.
					 * @param	height			  		Widget's height.
					 * @param	showNumber			  	true to show, false to hide the number.
					 */

					BallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption,
					                   Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
					                   bool isPrincipal, int width, int height, bool showNumber= true,
					                   bool isList = false);

					/**
					 * @fn	BallotOptionWidget::BallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption);
					 *
					 * @brief	class constructor for list ballot option.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	elegibleOption	list ballot option to be displayed.
					 */

					BallotOptionWidget(Smartmatic::SAES::Voting::Election::Eligible_option& elegibleOption);

					/**
					 * @fn	BallotOptionWidget::~BallotOptionWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~BallotOptionWidget();

					/**
					 * @fn	bool BallotOptionWidget::IsSelected();
					 *
					 * @brief	method to obtain if ballot is selected.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	if ballot is selected.
					 */

					bool IsSelected();

					/**
					 * @fn	bool BallotOptionWidget::IsPrincipal();
					 *
					 * @brief	method to obtain if ballot is principal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	if ballot is principal.
					 */

					bool IsPrincipal();

					/**
					 * @fn	virtual void BallotOptionWidget::SetSelection(bool select, bool sendSignal = false);
					 *
					 * @brief	select the ballot option widget.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	select	  	if ballot is selected.
					 * @param	sendSignal	if send click signal or just change visual color.
					 */

					virtual void SetSelection(bool select, bool sendSignal = false);

					/**
					 * @fn	std::string BallotOptionWidget::GetBallotOptionCode();
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
					 * ### param	_sent	first bool if ballot is selected.
					 * ### param	_sent	second bool if ballot is principal.
					 */

					typedef sigc::signal<void, std::string, bool, bool> type_ballot_clicked;

					/**
					 * @fn	type_ballot_clicked BallotOptionWidget::signal_ballot_clicked();
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
					 * @brief	set size elements.
					 *
					 * @author	Yadickson Soto
					 * @date	16/03/2012
					 *
					 * @param	width  	Widget's width.
					 * @param	height  Widget's height.
					 */
					void setSize(int width, int height);

				protected:
		            /**
	        		 * declaration of signal handler
		             */
					type_ballot_clicked m_ballot_clicked;   ///< The ballot clicked

					/**
					 * @fn	virtual bool BallotOptionWidget::on_ballot_clicked(GdkEventButton* event);
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
					 * @fn	void BallotOptionWidget::InitializeWidget();
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

					/**
					 * SAES voting objects
					 */
   					Smartmatic::SAES::Voting::Election::Ballot_option ballotOption; ///< The ballot option
  					Smartmatic::SAES::Voting::Election::Contest contest;	///< The contest

					/**
					 * Variables
					 */
					bool isSelected;	///< true if is selected
					bool isPrincipal;   ///< true if is principal
					std::string SoundBallot;	///< The sound ballot
					bool m_widgetEnabled; ///< enable
				};
			}
		}
	}
}

#endif // _BALLOT_OPTION_WIDGET_H_
