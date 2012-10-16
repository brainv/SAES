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
 * @file ballot-option-selection-widget.h
 * @brief ballot option selection container in voting experience
 */

#ifndef _BALLOT_OPTION_SELECTION_WIDGET_H_
#define _BALLOT_OPTION_SELECTION_WIDGET_H_

#include <gtkmm.h>
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include <Voting/Election/election-schema.hxx>
#include <Widgets/smartmatic-button.h>
#include "Runtime/Environment/saes-directories.h"
#include "Gui/Widgets/voting-frame-base.h"

namespace Smartmatic
{
	namespace SAES
	{
		namespace GUI
		{
			namespace Widgets
			{
				class BallotOptionWidget;
				class ComplexBallotOptionWidget;
				class BallotOptionTableWidget;
				class BallotOptionButtonWidget;

				/**
				 * @class	BallotOptionSelectionWidget
				 *
				 * @brief	Header class BallotOptionSelectionWidget.
				 *
				 * @author	Juan delgado &lt;juan.delgado@smartmatic.com&gt;
				 * @date	4/29/2011
				 */

				class BallotOptionSelectionWidget: public VotingFrameBase
				{
				public:

					/**
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	contest	contest that hold ballot options to be displayed.
					 * @param	votingModeType 	Type of the voting mode.
					 */

					BallotOptionSelectionWidget(Smartmatic::SAES::Voting::Election::Contest& contest);

					/**
					 * @fn	BallotOptionSelectionWidget::~BallotOptionSelectionWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~BallotOptionSelectionWidget();

					/**
					 * @fn	void BallotOptionSelectionWidget::Initialize(std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & principalBallotList,
					 * 		std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & standInBallotList,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir);
					 *
					 * @brief	calculate position and size of ballot option widgets.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	principalBallotList	list of all principal ballots to be displayed.
					 * @param [in,out]	standInBallotList  	list of all stand in ballots to be displayed.
					 * @param	saesDir					   	The saes dir.
					 */

					void Initialize(std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & ballotList,
                                    std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & principalBallotList,
					                std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & standInBallotList,
					                Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir);

					/**
					 * @fn	void BallotOptionSelectionWidget::SetBallots(std::list<Smartmatic::SAES::Voting::Election::Ballot_option> & ballotList);
					 *
					 * @brief	set ballots selection.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	ballotList	ballots to be selected.
					 */

					void SetBallots(std::list<Smartmatic::SAES::Voting::Election::Ballot_option> & ballotList);

					/**
					 * @fn	Smartmatic::SAES::Voting::Election::Contest BallotOptionSelectionWidget::getContest();
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
					 * @fn	int BallotOptionSelectionWidget::GetTotalBallotsDisplayed();
					 *
					 * @brief	Gets the total ballots displayed.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	The total ballots displayed.
					 */

					int GetTotalBallotsDisplayed();

					/**
					 * @fn	void BallotOptionSelectionWidget::RefreshLabels();
					 *
					 * @brief	Refresh labels.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void RefreshLabels();

					/**
					 * @typedef	sigc::signal<void> type_accept_clicked
					 *
					 * @brief	signals definitions.
					 */

					typedef sigc::signal<void> type_accept_clicked;

					/**
					 * @typedef	sigc::signal<void> type_back_clicked
					 *
					 * @brief	Defines an alias representing the type back clicked. .
					 */

					typedef sigc::signal<void> type_back_clicked;

					/**
					 * @typedef	sigc::signal<void, std::string, bool > type_ballotOption_clicked
					 *
					 * @brief	Defines an alias representing the type ballot option clicked. .
					 */

					typedef sigc::signal<void, std::string, bool > type_ballotOption_clicked;

					/**
					 * @fn	void BallotOptionSelectionWidget::ClearVisualSelection();
					 *
					 * @brief	Clears the visual selection.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void ClearVisualSelection();

					/**
					 * @fn	type_accept_clicked BallotOptionSelectionWidget::accept_clicked();
					 *
					 * @brief	signals connect methods.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_accept_clicked accept_clicked();

					/**
					 * @fn	type_back_clicked BallotOptionSelectionWidget::back_clicked();
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
					 * @fn	type_ballotOption_clicked BallotOptionSelectionWidget::ballotOption_clicked();
					 *
					 * @brief	Gets the ballot option clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_ballotOption_clicked ballotOption_clicked();
					
					unsigned int GetTallyPosition() { return tallyPosition; }

					virtual void SetWidgetEnabled(bool enabled = true);

					/**
					 * @brief	refresh widget
					 * @author	Yadickson Soto
					 * @date	22/04/2012
					 */
					virtual void refresh();

				protected:
		            /**
	        		 * @brief signals declaration
		             */
					type_ballotOption_clicked m_ballotOption_clicked;   ///< The ballot option clicked
					type_accept_clicked m_accept_clicked;   ///< The accept clicked
					type_back_clicked m_back_clicked;   ///< The back clicked

					/**
					 * @fn	void BallotOptionSelectionWidget::on_clearButton_clicked();
					 *
					 * @brief	signal button clear, clear all ballots selected.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_clearButton_clicked();

					/**
					 * @fn	void BallotOptionSelectionWidget::on_acceptButton_clicked();
					 *
					 * @brief	send the ballots selected.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_acceptButton_clicked();

					/**
					 * @fn	void BallotOptionSelectionWidget::on_backButton_clicked();
					 *
					 * @brief	send back signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_backButton_clicked();

					/**
					 * @fn	void BallotOptionSelectionWidget::raise_option_clicked(std::string& optionCode,
					 *  bool isPrincipal);
					 *
					 * @brief	method that signals the ballot option clicked.
					 *
					 * @author	Freddy.Gomez
					 * @date	10/15/2011
					 *
					 * @param	ballotOptionCode	ballot option clicked.
					 * @param	isPrincipal			true if ballot is principal.
					 */
					void raise_option_clicked(std::string& optionCode, bool isSelected);

					/**
					 * @fn	void BallotOptionSelectionWidget::on_ballot_option_clicked(std::string ballotOptionCode,
					 * 		bool isSelected, bool isPrincipal);
					 *
					 * @brief	method that receives ballot option clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	ballotOptionCode	ballot option clicked.
					 * @param	isSelected			true if ballot is selected.
					 * @param	isPrincipal			true if ballot is principal.
					 */

					void on_ballot_option_clicked(std::string ballotOptionCode, bool isSelected, bool isPrincipal);

					/**
					 * @fn	void BallotOptionSelectionWidget::on_ballotList_clicked(std::string ballotOptionCode,
					 * 		bool isSelected, bool isPrincipal);
					 *
					 * @brief	method that receives ballot option list clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	ballotOptionCode	ballot option list clicked.
					 * @param	isSelected			true if list is selected.
					 * @param	isPrincipal			always true.
					 */

					void on_ballotList_clicked(std::string ballotOptionCode, bool isSelected, bool isPrincipal);
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
					 * @fn	void BallotOptionSelectionWidget::SelectAllBallots(bool principal, bool standIn);
					 *
					 * @brief	select ballots requested.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	principal	select all principal ballots.
					 * @param	standIn  	select all stand in ballots.
					 */

					void SelectAllBallots(bool principal, bool standIn);

					/**
					 * @fn	void BallotOptionSelectionWidget::ClearAllBallots(bool principal, bool standIn);
					 *
					 * @brief	unselect ballots requested.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	principal	unselect all principal ballots.
					 * @param	standIn  	unselect all stand in ballots.
					 */

					void ClearAllBallots(bool principal, bool standIn);

					/**
					 * @fn	void BallotOptionSelectionWidget::CheckButtonsLogic();
					 *
					 * @brief	check the visual logic buttons.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void CheckButtonsLogic();

					/**
					 * @fn	void BallotOptionSelectionWidget::ButtonsLogicShowHide(bool clear, bool accept,
					 * 		bool back);
					 *
					 * @brief	hide or show the buttons.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	clear 	if true show button clear, else hide button.
					 * @param	accept	if true show button accept, else hide button.
					 * @param	back  	if true show button back, else hide button.
					 */

					void ButtonsLogicShowHide(bool clear, bool accept, bool back);
					
					/**
					 * Child Widgets 
					 */
					Gtk::VBox* externalBox; ///< The external box
					//Gtk::HBox* bottomBox;   ///< The bottom box
					Gtk::Frame* headerFrame;	///< The header frame
					Gtk::Frame* clientAreaFrame;	///< The client area frame
					Gtk::Frame* bottomFrame;	///< The bottom frame
					Gdk::Color selectedListColor;   ///< The selected list color
					Gdk::Color unSelectedListColor; ///< The un selected list color
					Gdk::Color StandInColor;	///< The stand in color
					BallotOptionTableWidget * ballotOptionTableWidget;	///< The client area table
					BallotOptionButtonWidget * ballotOptionButtonWidget; ///< ballot option button widget

					std::string SoundBallotS;   ///< The sound ballot s
					unsigned int tallyPosition;	///< The tally position
					bool showBackButton; ///< flag show back bottom
					/**
					 * SAES voting objects
					 */
					Smartmatic::SAES::Voting::Election::Contest contest;	///< The contest
					ComplexBallotOptionWidget* ballotOptionListWidget;  ///< The ballot option list widget
					//std::list<Smartmatic::SAES::Voting::Election::Eligible_option> principalBallotList;
					//std::list<Smartmatic::SAES::Voting::Election::Eligible_option> standInBallotList;
						
					/**
					 * Variables
					 */
					int headerHeigth;   ///< The header heigth
					int bottomHeigth;   ///< The bottom heigth
					int principalBallotsSelected;   ///< The principal ballots selected
					int standInBallotsSelected; ///< The stand in ballots selected
					int totalPrincipalBallots;  ///< The total principal ballots
					int totalStandInBallots;	///< The total stand in ballots
					bool loopbackSelection; ///< true to loopback selection
					bool HideStandInLabelIfEmpty; ///< true if hide stand in label if there are no stand in candidate
					std::list<Smartmatic::SAES::Voting::Election::Eligible_option>::iterator it;	///< The iterator
					std::list<BallotOptionWidget*>::iterator itWidget;  ///< The iterator widget

					//Glib::Mutex		m_signalMutex;
					bool 			m_widgetEnabled;
					bool 			m_skipAcceptSignal;

				};
			}
		}
	}
}

#endif // _BALLOT_OPTION_SELECTION_WIDGET_H_
