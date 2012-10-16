/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 * saesguibase
 * Copyright (C) Juan Delgado 2011 <juan.delgado@smartmatic.com>
 * 
 * @file	party-widget.h
 *
 * @brief	Declares the party widget class.
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
 
 /*
  * DUMMY COMMENT FOR TESTS PURPOSES
	* DUMMY COMMENT FOR TESTS PURPOSES  2
	*/
 
 
#ifndef _PARTY_WIDGET_H_
#define _PARTY_WIDGET_H_


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
				 * @class	PartyWidget
				 *
				 * @brief	Header class PartyWidget.
				 *
				 * @author	Juan delgado &lt;juan.delgado@smartmatic.com&gt;
				 * @date	4/29/2011
				 */

				class PartyWidget: public Gtk::Frame
				{
				public:

					/**
					 * @fn	PartyWidget::PartyWidget(Smartmatic::SAES::Voting::Election::Ballot_option& ballotParty,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	ballotParty	ballot option party to be displayed.
					 * @param	saesDir			   	The saes dir.
					 * @param	width	widget's width
					 * @param	height 	widget's height
					 */

					PartyWidget(Smartmatic::SAES::Voting::Election::Ballot_option& ballotParty,
					            Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir,
					            int width, int height);

					/**
					 * @fn	PartyWidget::PartyWidget(std::string text);
					 *
					 * @brief	class constructor for null party.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	text	to be displayed.
					 * @param	width	widget's width
					 * @param	height 	widget's height
					 */

					PartyWidget(std::string text, int width, int height);

					/**
					 * @fn	void PartyWidget::RefreshLabel(std::string text);
					 *
					 * @brief	Refresh label.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	text	The text.
					 */

					void RefreshLabel(std::string text);

					/**
					 * @fn	PartyWidget::~PartyWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PartyWidget();

					/**
					 * @typedef	sigc::signal<void, Smartmatic::SAES::Voting::Election::Party&> type_party_clicked
					 *
					 * @brief	definition of signals.
					 */

					typedef sigc::signal<void, Smartmatic::SAES::Voting::Election::Party&> type_party_clicked;

					/**
					 * @typedef	sigc::signal<void> type_party_null_clicked
					 *
					 * @brief	Defines an alias representing the type party null clicked. .
					 */

					typedef sigc::signal<void> type_party_null_clicked;

					/**
					 * @fn	type_party_clicked PartyWidget::signal_party_clicked();
					 *
					 * @brief	method to connect signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_party_clicked signal_party_clicked();

					/**
					 * @fn	type_party_null_clicked PartyWidget::signal_party_null_clicked();
					 *
					 * @brief	Raises the party null clicked event.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_party_null_clicked signal_party_null_clicked();
					
				protected:
		            /**
	        		 * declaration of signal handler
		             */
					type_party_clicked m_party_clicked; ///< The party clicked
					type_party_null_clicked m_party_null_clicked;   ///< The party null clicked

					/**
					 * @fn	virtual bool PartyWidget::on_party_clicked(GdkEventButton* event);
					 *
					 * @brief	methods that receives event box button press mask.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	event	If non-null, the event.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool on_party_clicked(GdkEventButton* event);

					/**
					 * @fn	virtual bool PartyWidget::on_party_null_clicked(GdkEventButton* event);
					 *
					 * @brief	Executes the party null clicked action.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	event	If non-null, the event.
					 *
					 * @return	true if it succeeds, false if it fails.
					 */

					virtual bool on_party_null_clicked(GdkEventButton* event);

				private:
					/**
					 * Child Widgets 
					 */
					Gtk::EventBox* eventbox;	///< The eventbox
					VotingWidgetBase* votingWidget; ///< The voting widget
					Gtk::Label* labelString;	///< The label string
					bool 			m_widgetEnabled;
					/**
					 * SAES voting objects
					 */
					Smartmatic::SAES::Voting::Election::Party party;	///< The party
					Smartmatic::SAES::Voting::Election::Ballot_option ballotParty;  ///< The ballot party

				};
			}
		}
	}
}

#endif // _PARTY_WIDGET_H_
