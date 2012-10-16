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

#ifndef _REFERENDUM_SELECTION_WIDGET_H_
#define _REFERENDUM_SELECTION_WIDGET_H_

#include <gtkmm.h>
#include "Configuration/SaesGUIConfiguration-schema.hxx"
#include <Voting/Election/election-schema.hxx>
#include <Widgets/smartmatic-button.h>
#include "referendum-widget.h"
#include "Operation/Voting/VotingExperienceController.hxx"
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
				/**
				 * @class	ReferendumSelectionWidget
				 *
				 * @brief	Header class ReferendumSelectionWidget.
				 *
				 * @author	Juan delgado &lt;juan.delgado@smartmatic.com&gt;
				 * @date	4/29/2011
				 */

				class ReferendumSelectionWidget: public VotingFrameBase
				{
				public:

					/**
					 * @brief	class constructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	contest	contest that hold ballot options to be displayed.
					 */

					ReferendumSelectionWidget(Smartmatic::SAES::Voting::Election::Contest& contest);

					/**
					 * @fn	ReferendumSelectionWidget::~ReferendumSelectionWidget();
					 *
					 * @brief	class destructor.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					~ReferendumSelectionWidget();

					/**
					 * @fn	void ReferendumSelectionWidget::Initialize(std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & principalBallotList,
					 * 		Smartmatic::SAES::Runtime::Environment::SaesDirectories saesDir);
					 *
					 * @brief	calculate position and size of ballot option widgets.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param [in,out]	principalBallotList	list of all principal ballots to be displayed.
					 * @param	saesDir					   	The saes dir.
					 */

					void Initialize(std::list<Smartmatic::SAES::Voting::Election::Eligible_option> & principalBallotList, 
							Smartmatic::SAES::Runtime::Environment::SaesDirectories& saesDir);

					/**
					 * @fn	Smartmatic::SAES::Voting::Election::Contest ReferendumSelectionWidget::getContest();
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
					 * @brief method refresh widget
					 * @date 30/03/2012
					 * @author Yadickson Soto
					 */
					virtual void refresh();

					/**
					 * @fn	void ReferendumSelectionWidget::RefreshLabels();
					 *
					 * @brief	Refresh labels.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void RefreshLabels();

					/**
					 * @fn	void ReferendumSelectionWidget::SetBackButton(bool show);
					 *
					 * @brief	Sets a back button.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	show	true to show, false to hide.
					 */

					void SetBackButton(bool show);

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

					typedef sigc::signal<void, std::string, bool> type_ballotOption_clicked;

					/**
					 * @fn	type_back_clicked ReferendumSelectionWidget::back_clicked();
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
					 * @fn	type_back_clicked ReferendumSelectionWidget::accept_clicked();
					 *
					 * @brief	Gets the accept clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_back_clicked accept_clicked();

					/**
					 * @fn	type_back_clicked ReferendumSelectionWidget::null_clicked();
					 *
					 * @brief	Gets the null clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */
					type_back_clicked null_clicked();

					/**
					 * @fn	type_ballotOption_clicked ReferendumSelectionWidget::ballotOption_clicked();
					 *
					 * @brief	Gets the ballot option clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @return	.
					 */

					type_ballotOption_clicked ballotOption_clicked();
					
					void SetWidgetEnabled(bool enabled = true);

				protected:
		            /**
	        		 * @brief signals declaration
		             */
					type_ballotOption_clicked m_ballotOption_clicked;   ///< The ballot option clicked
					type_back_clicked m_back_clicked;   ///< The back clicked
					type_back_clicked m_accept_clicked;   ///< The back clicked
					type_back_clicked m_null_clicked;   ///< The back clicked

					/**
					 * @fn	void ReferendumSelectionWidget::on_backButton_clicked();
					 *
					 * @brief	send back signal.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_backButton_clicked();

					/**
					 * @fn	void ReferendumSelectionWidget::on_acceptButton_clicked();
					 *
					 * @brief	handles accept button signal
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_acceptButton_clicked();

					/**
					 * @fn	void ReferendumSelectionWidget::on_nullOption_clicked();
					 *
					 * @brief	handles null option signal
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */

					void on_nullOption_clicked();

					/**
					 * @fn	void ReferendumSelectionWidget::on_clearButton_clicked();
					 *
					 * @brief	handles clear button signal
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 */
					void on_clearButton_clicked();

					/**
					 * @fn	void ReferendumSelectionWidget::on_ballot_option_clicked(std::string ballotOptionCode,
					 * 		bool isSelected, bool isPrincipal);
					 *
					 * @brief	method that receives ballot option clicked.
					 *
					 * @author	Cesar.bonilla
					 * @date	4/29/2011
					 *
					 * @param	ballotOptionCode	ballot option clicked.
					 * @param	isSelected			true if is selected
					 */

					void on_ballot_option_clicked(std::string ballotOptionCode, bool isSelected);
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

					std::string ComposeQuestionText();

					/**
					 * Child Widgets 
					 */
					Gtk::EventBox* labelEventBox; ///< The label event box
					Gtk::VBox* externalBox; ///< The external box
					Gtk::VBox* internalBox; ///< The internal box
					Gtk::HBox* bottomBox;   ///< The bottom box
					Gtk::Box* ballotsBox;   ///< The ballots box
					Gtk::Frame* clientAreaFrame;	///< The client area frame
					Gtk::Frame* bottomFrame;	///< The bottom frame
					Smartmatic::GUI::Widgets::SmartmaticButton* backButton; ///< The back button
					Smartmatic::GUI::Widgets::SmartmaticButton* clearButton; ///< The clear button
					Smartmatic::GUI::Widgets::SmartmaticButton* acceptButton; ///< The accept button
					std::string SoundBallotS;   ///< The sound ballot s
					std::list<ReferendumWidget*> referendumWidgetList;	///< The referendum widget list

					/**
					 * SAES voting objects
					 */
					Smartmatic::SAES::Voting::Election::Contest contest;	///< The contest
						
					/**
					 * Variables
					 */
					bool showBackButton;	///< The show back button
					int bottomHeigth;   ///< The bottom heigth
					bool oneSelected;	///< True if any ballot is selected
					bool m_widgetEnabled;

					std::list<Smartmatic::SAES::Voting::Election::Eligible_option>::iterator it;	///< The iterator

					Smartmatic::SAES::Configuration::ReferendumConfiguration config;///< The configuration

				};
			}
		}
	}
}

#endif // _REFERENDUM_SELECTION_WIDGET_H_
