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

#ifndef _POLL_WORKER_MEMBER_WIDGET_H_
#define _POLL_WORKER_MEMBER_WIDGET_H_

#include <gtkmm.h>
#include <Voting/PBReports/pollworkers-schema.hxx>
#include <Widgets/RegisterInfoWidget.hxx>

namespace Smartmatic
{
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
						class PollWorkerMemberWidget : public Smartmatic::GUI::Widgets::RegisterInfoWidget
						{
						public:
							PollWorkerMemberWidget();

							~PollWorkerMemberWidget();

							void Initialize(Smartmatic::SAES::Voting::PBReports::WorkerMemberType member);
							Smartmatic::SAES::Voting::PBReports::WorkerMemberType GetMember();

							void ClearData();

							void setWorker(Smartmatic::SAES::Voting::PBReports::Worker worker);
							Smartmatic::SAES::Voting::PBReports::Worker getWorker() const;

							bool getHasWoker() const;

							bool getHasInfo() const;
							void setHasInfo(bool hasInfo);

						    bool getIsSelected() const;
						    void setIsSelected(bool isSelected);

						    int getPosition() const;
						    void setPosition(int position);

							sigc::signal<void, bool> signal_pollworker_clicked();

							static std::string GetStringFromEnum(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member);

						protected:

						private:

							void SetFramesBackGround(bool isSelected);

							bool isSelected;
							int position;
							bool hasInfo;
							bool hasWorker;

							Smartmatic::SAES::Voting::PBReports::WorkerMemberType member;
							Smartmatic::SAES::Voting::PBReports::Worker worker;
						};
					}
				}
			}
		}
	}
}

#endif // _POLL_WORKER_MEMBER_WIDGET_H_
