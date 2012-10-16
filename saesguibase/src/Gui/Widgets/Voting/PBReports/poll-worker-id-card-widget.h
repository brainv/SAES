/**
 * @file	poll-worker-id-card-widget.h
 *
 * @brief	Declares the poll worker identifier card widget class.
 */

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

#ifndef _POLL_WORKER_ID_CARD_WIDGET_H_
#define _POLL_WORKER_ID_CARD_WIDGET_H_

#include <gtkmm.h>
#include "Gui/Widgets/id-card-widget.h"
#include <Voting/PBReports/pollworkers-schema.hxx>
#include <Widgets/smartmatic-entry.h>
#include <Widgets/SmartmaticTextView.h>

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
				namespace Voting
				{
					namespace PBReports
					{
						/**
						 * @brief	Poll worker identifier card widget. 
						 *
						 * @author	Fsilva
						 * @date	28/04/2011
						 */

						class PollWorkerIDCardWidget: public Smartmatic::SAES::GUI::Widgets::IDCardWidget
						{
						public:

							/**
							 * @brief	Default constructor.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							PollWorkerIDCardWidget();

							/**
							 * @brief	Finaliser.
							 *
							 * @author	Fsilva
							 * @date	28/04/2011
							 */

							~PollWorkerIDCardWidget();

							virtual void Initialize(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member);
							virtual void GetParams(Smartmatic::SAES::Voting::PBReports::Worker& worker);
							virtual void SetParams(Smartmatic::SAES::Voting::PBReports::Worker &worker);

							/**
							 * @brief	Raises the accept clicked event.
							 *
							 * @author	Juan.Delgado
							 * @date	18/07/2011
							 *
							 * @return	The signal
							 */

							signal_void signal_button_accept_clicked();


							/**
							 * @brief	Raises the accept clicked event.
							 *
							 * @author	Juan.Delgado
							 * @date	18/07/2011
							 *
							 * @return	The signal
							 */

							signal_void signal_button_back_clicked();
				
						protected:
							signal_void m_accept_button_clicked;   ///< The accept clicked signal
							signal_void m_back_button_clicked;   ///< The back clicked signal

							void on_acceptButton_clicked();
							void on_backButton_clicked();

							bool CheckCompleteData();

							/**
							 * @brief method change checkbox
							 * @date 09/05/2012
							 * @author Yadickson Soto
							 */
							void allDayChange();

							/**
							 * @brief	Shows the entry data and emit the back signal.
							 *
							 * @author	Juan.Delgado
							 * @date	18/07/2011
							 */
							virtual bool ShowEntryDataAndEmitSignal(int timer);
							/**
							 * @brief	Shows elements
							 * @author	Yadickson Soto
							 * @date	04/06/2012
							 */
							virtual void ShowElements();

						private:

							Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member;
							std::string customCode; ///< The custom code

							static Smartmatic::Log::ISMTTLog* logger; ///< The logger

							Smartmatic::GUI::Widgets::SmartmaticEntry* accountEntry; ///< The account entry
							Gtk::Label* accountLabel; ///< The account label

							Smartmatic::GUI::Widgets::SmartmaticEntry* partyEntry; ///< The party entry
							Gtk::Label* partyLabel; ///< The party label

							Smartmatic::GUI::Widgets::SmartmaticEntry* phoneEntry; ///< The phone entry
							Gtk::Label* phoneLabel; ///< The phone label

							Smartmatic::GUI::Widgets::SmartmaticButton* backButton;
							Smartmatic::GUI::Widgets::SmartmaticButton* acceptButton;

							Gtk::CheckButton * allDayCheckButton; ///< all day journal
							Gtk::Label* allDayLabel; ///< The all journal label

							Smartmatic::GUI::Widgets::SmartmaticEntry* initEntry; ///< The init journal entry
							Gtk::Label* initLabel; ///< The init journal label

							Smartmatic::GUI::Widgets::SmartmaticEntry* endEntry; ///< The end journal entry
							Gtk::Label* endLabel; ///< The end journal label

							Gtk::CheckButton * bureauAssignedCheckButton; ///< bureau assigned entry
							Gtk::Label* bureauAssignedLabel; ///< bureau assigned label

							Gtk::CheckButton * acceptDesignationCheckButton; ///< deputy accept designation
							Gtk::Label* acceptDesignationLabel; ///< deputy accept designation label

							Gtk::Label* deputyCommentLabel; ///< deputy comment label
							Smartmatic::GUI::Widgets::SmartmaticTextView * textView; ///< text view
						};
					}
				}
			}
		}
	}
}



#endif // _POLL_WORKER_ID_CARD_WIDGET_H_
