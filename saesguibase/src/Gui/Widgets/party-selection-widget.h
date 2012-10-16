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
 * @file party-selection-widget.h
 * @brief party selection container in voting experience
 * @author Juan delgado <juan.delgado@smartmatic.com>
 */

#ifndef _PARTY_SELECTION_WIDGET_H_
#define _PARTY_SELECTION_WIDGET_H_

#include <gtkmm.h>
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include "Voting/Election/election-schema.hxx"
#include "Gui/Widgets/party-widget.h"
#include "Widgets/smartmatic-button.h"
#include "Operation/Voting/VotingExperienceController.hxx"
#include "Runtime/Environment/saes-directories.h"
#include "Gui/Widgets/voting-frame-base.h"
#include <Voting/Vote/vote-schema.hxx>
#include "PartyButtonWidget.hxx"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				/**
				 * @class	PartySelectionWidget
				 *
				 * @brief	Party selection widget. 
				 *
				 * @author	Cesar.bonilla
				 * @date	4/29/2011
				 */

				class PartySelectionWidget: public VotingFrameBase
				{
				public:

					/**
					 * @fn	PartySelectionWidget::PartySelectionWidget(Smartmatic::SAES::Voting::Election::Contest& contest,
					 * 		bool viewBackButton = false);
					 *
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	contest	contest that hold parties to be displayed.
					 * @param	viewBackButton 	flag view back button.
					 * @param	votingModeType 	Type of the voting mode.
					 *
					 * ### param	partyList	list of all ballot option parties to be displayed.
					 */

					PartySelectionWidget(Smartmatic::SAES::Voting::Election::Contest& contest,
					                     bool viewBackButton = false);

					/** @brief class destructor */

					/**
					 * @fn	PartySelectionWidget::~PartySelectionWidget();
					 *
					 * @brief	Finaliser.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~PartySelectionWidget();

					/**
					 * @fn	void PartySelectionWidget::Initialize(std::list<Smartmatic::SAES::Voting::Election::Ballot_option>& partyList,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir);
					 *
					 * @brief	calculate position and size of parties widgets.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	partyList	List of parties.
					 * @param	saesDir			 	The saes dir.
					 */

					void Initialize(std::list<Smartmatic::SAES::Voting::Election::Ballot_option>& partyList,
					                Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir);

					/**
					 * @fn	void PartySelectionWidget::ShowBackButton();
					 *
					 * @brief	Shows the back button.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ShowBackButton();

					/**
					 * @fn	void PartySelectionWidget::HideBackButton();
					 *
					 * @brief	Hides the back button.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void HideBackButton();

					/**
					 * @fn	void PartySelectionWidget::SetBackButton(bool show);
					 *
					 * @brief	Sets a back button.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	show	true to show, false to hide.
					 */

					virtual void SetBackButton(bool show);
					/**
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

					/**
					 * @fn	std::string PartySelectionWidget::GetContestName();
					 *
					 * @brief	search the contest name in the contest object.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	name of the contest.
					 */

					std::string GetContestName();

					void RefreshLabels();

					/**
					 * @fn	Smartmatic::SAES::Voting::Election::Contest PartySelectionWidget::getContest();
					 *
					 * @brief	get contest.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The contest.
					 */

					Smartmatic::SAES::Voting::Election::Contest getContest();

					/**
					 * @typedef	sigc::signal<void> type_null_clicked
					 *
					 * @brief	signals definitions.
					 */

					typedef sigc::signal<void> type_null_clicked;

					/**
					 * @typedef	sigc::signal<void> type_back_clicked
					 *
					 * @brief	Defines an alias representing the type back clicked. .
					 */

					typedef sigc::signal<void> type_back_clicked;

					/**
					 * @typedef	sigc::signal<void, Smartmatic::SAES::Voting::Election::Party&> type_party_clicked
					 *
					 * @brief	Defines an alias representing the type party clicked. .
					 */

					typedef sigc::signal<void, Smartmatic::SAES::Voting::Election::Party&> type_party_clicked;

					/**
					 * @fn	type_null_clicked PartySelectionWidget::null_clicked();
					 *
					 * @brief	signals connect methods.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_null_clicked null_clicked();

					/**
					 * @fn	type_back_clicked PartySelectionWidget::back_clicked();
					 *
					 * @brief	Gets the back clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_back_clicked back_clicked();

					/**
					 * @fn	type_party_clicked PartySelectionWidget::party_clicked();
					 *
					 * @brief	Gets the party clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_party_clicked party_clicked();
					

					virtual void SetWidgetEnabled(bool enabled = true);

				protected:
		            /**
	        		 * @brief signals declaration
		             */
					type_null_clicked m_null_clicked;   ///< The null clicked
					type_back_clicked m_back_clicked;   ///< The back clicked
					type_party_clicked m_party_clicked; ///< The party clicked

					//Glib::Mutex		m_signalMutex;
					bool m_widgetEnabled;

					/**
					 * @fn	void PartySelectionWidget::on_party_clicked(Smartmatic::SAES::Voting::Election::Party& partySelected);
					 *
					 * @brief	method that receives party selection signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	partySelected	The party selected.
					 */

					void on_party_clicked(Smartmatic::SAES::Voting::Election::Party& partySelected);

					/**
					 * @fn	void PartySelectionWidget::on_nullButton_clicked();
					 *
					 * @brief	buttons method.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_nullButton_clicked();

					/**
					 * @fn	void PartySelectionWidget::on_backButton_clicked();
					 *
					 * @brief	Handles back button clicked signals.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_backButton_clicked();
					/**
					 * @brief virtual method getter label config
					 * @return title label config
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual Smartmatic::GUI::Configuration::LabelConfiguration getTitleLabelConfig();
					/**
					 * @brief virtual method getter label config
					 * @return bottom label config
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual Smartmatic::GUI::Configuration::LabelConfiguration getBottomLabelConfig();
					/**
					 * @brief virtual method getter title
					 * @return title
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getTitleText();
					/**
					 * @brief virtual method getter title
					 * @return bottom
					 * @date 25/04/2012
					 * @author Yadickson Soto
					 */
					virtual std::string getBottomText();

				private:
					/**
					 * Child Widgets 
					 */
					Gtk::VBox* externalBox; ///< The external box
					Gtk::Frame* bottomFrame;	///< The bottom frame
					Gtk::Table* tableClientArea;	///< The table client area
					PartyButtonWidget * partyButtomWidget; ///< The party button widget
					PartyWidget* ptrPartyWidget;	///< The pointer party widget
					bool flagShowNullButton; ///< Flag show null button
					bool showBackButton; ///< flag show back button
					/**
					 * SAES voting objects
					 */
					Smartmatic::SAES::Voting::Election::Contest contest;	///< The contest

					/**
					 * Variables
					 */
					std::list<Smartmatic::SAES::Voting::Election::Ballot_option>::iterator it;  ///< The iterator
					std::string contestName;	///< Name of the contest

					Smartmatic::SAES::Voting::Vote::VoteMode votingMode; ///< The voting mode
				};
			}
		}
	}
}

#endif // _PARTY_SELECTION_WIDGET_H_
