/**
 * @file	poll-worker-widget.h
 *
 * @brief	Declares the poll worker widget class.
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

#ifndef _POLL_WORKER_MEMBER_REGISTER_WIDGET_H_
#define _POLL_WORKER_MEMBER_REGISTER_WIDGET_H_

#include <gtkmm.h>
#include "poll-worker-member-widget.h"
#include "poll-worker-id-card-widget.h"
#include <Widgets/smartmatic-button.h>
#include <Voting/PBReports/pollworkers-schema.hxx>
#include "Voting/PBReports/pollworkers-wrapper.h"
#include <Widgets/notebook-container.h>
#include <Widgets/RegisterWidget.hxx>
#include "Gui/Widgets/confirmation-delete-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Widgets/StepWidget.hxx>

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
						class PollWorkerMemberRegisterWidget : public Smartmatic::GUI::Widgets::StepWidget
						{
						public:
							PollWorkerMemberRegisterWidget();

							~PollWorkerMemberRegisterWidget();

							bool Persist();
							void Load();
							void Dispose();
							bool checkNewStatus();
							/**
							 * @brief method getter signal enabled
							 * @return signal
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalEnabled();
							/**
							 * @brief method getter signal disabled
							 * @return signal
							 * @data 22/05/2012
							 * @author Yadickson Soto
							 */
							sigc::signal<void> getSignalDisabled();

						protected:
							void on_addButton_clicked();
							void on_pollWorker_ready();
							void on_choose_clicked(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member);
							void on_pollWorker_clicked(bool hasInfo, int position);
							void on_cleanButton_clicked();
							void on_confirmationDelete_send(bool deleteWorker);

						private:

							sigc::signal<void> signalEnabled; ///< signal enabled
							sigc::signal<void> signalDisabled; ///< signal disabled

							Smartmatic::GUI::Widgets::RegisterWidget * registerWidget; ///< register container widget

							Gtk::Alignment* alignChoose;
							Gtk::VBox* idBox;
							PollWorkerMemberWidget* pollMember;
							PollWorkerIDCardWidget* pollID;
							Smartmatic::GUI::Widgets::SmartmaticButton* addButton;
							Smartmatic::GUI::Widgets::SmartmaticButton* deleteButton;
							Smartmatic::GUI::Widgets::SmartmaticButton* modifyButton;
							Smartmatic::SAES::GUI::Widgets::ConfirmationDeleteWidget* deleteWidget;

							std::map<int, PollWorkerMemberWidget*> mapPollWorker;
							//std::vector<PollWorkerMemberWidget*> vecPollWorker;
							Smartmatic::SAES::Voting::PBReports::PollworkersWrapper* pollWrapper;   ///< The poll wrapper

							void CleanSelections();
							void SetPollWorker();
							void DeleteWorker();

							bool isModified;
							bool showConfirmationDelete;

							static Smartmatic::Log::ISMTTLog* logger; /**<logger*/  ///< The logger

							Smartmatic::SAES::Configuration::PollWorkerRegisterFunctionalityConfiguration config; ///< The pollworker configuratio
						};
					}
				}
			}
		}
	}
}

#endif // _POLL_WORKER_MEMBER_REGISTER_WIDGET_H_
