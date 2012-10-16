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

#include "poll-worker-member-widget.h"
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_NLS
#include <libintl.h>
#define _(String) dgettext (GETTEXT_PACKAGE, String) ///<macro for gettext
#else
#define _(String) (String) ///<macro without gettext
#endif

#define N_(String) (String) ///<macro for gettext not translate

using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::GUI::Widgets;

PollWorkerMemberWidget::PollWorkerMemberWidget()
: RegisterInfoWidget()
{
	isSelected = false;
	hasInfo = false;
	hasWorker = false;

	RegisterWidgetConfiguration registerConfig = SAESGUIConfigurationManager::Current()->GetPollWorkerRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();

	showHeader(registerConfig.getShowHeader());
	showCenter(registerConfig.getShowCenter());
	showBottom(registerConfig.getShowBottom());
}

PollWorkerMemberWidget::~PollWorkerMemberWidget()
{

}

void PollWorkerMemberWidget::Initialize(Smartmatic::SAES::Configuration::WorkerMemberType member)
{
	IDConfig idConfig = SAESGUIConfigurationManager::Current()->getPollWorkerIDConfiguration(member);

	std::string title = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.Member");
	title.append(" : ");

	clearAll();
	addHeader(title, GetStringFromEnum(member));
	putCenterMessage(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerMemberWidget.ClickToAdd"));

	this->member = member;
}

string PollWorkerMemberWidget::GetStringFromEnum(Smartmatic::SAES::Configuration::WorkerMemberType::Value member)
{
	string returnValue = "";

	switch(member)
	{
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_PRESIDENT:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.President");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_SECRETARY:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.Secretary");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_ASSISTENT:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.Assistent");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_WITNESS:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.Witness");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_POLICE:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.Police");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_ASSISTANT_SECRETARY:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.AssistantSecretary");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputyPresident");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputySecretary");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTENT:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputyAssistent");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_WITNESS:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputyWitness");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_POLICE:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputySecretary");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTANT_SECRETARY:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.DeputyAssistantSecretary");
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY:
			returnValue = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerRegisterWidget.Deputy");
			break;
	}

	return returnValue;
}

Smartmatic::SAES::Voting::PBReports::WorkerMemberType PollWorkerMemberWidget::GetMember()
{
	return member;
}

void PollWorkerMemberWidget::ClearData()
{
	hasInfo = false;
	hasWorker = false;

	putCenterMessage(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerMemberWidget.ClickToAdd"));
	clearBottom();
}

void PollWorkerMemberWidget::setWorker(Worker worker)
{
	string fnameText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.FirstName");
	fnameText.append(" :");
	string snameText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.LastName");
	snameText.append(" :");

	clearCenter();
	addCenter(fnameText, worker.getPersonal_info().getFirstName());
	addCenter(snameText, worker.getPersonal_info().getSurname());

	hasWorker = true;

	IDConfig idConfig = SAESGUIConfigurationManager::Current()->getPollWorkerIDConfiguration(member);

	if (idConfig.getPhone().present() && !worker.getPhone().empty())
	{
		std::string phoneText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.PhoneNumber");
		phoneText.append(" :");
		addCenter(phoneText, worker.getPhone());
	}

	if(idConfig.getAccount().present() && !worker.getAccount_number().empty())
	{
		std::string accountText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.Account");
		accountText.append(" :");
		addBottom(accountText, worker.getAccount_number());
	}
	else if(idConfig.getParty().present() && !worker.getParty().empty())
	{
		std::string partyText = _("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.Party");
		partyText.append(" :");

		addBottom(partyText, worker.getParty());
	}

	this->worker = worker;
	hasInfo = true;
}

Smartmatic::SAES::Voting::PBReports::Worker PollWorkerMemberWidget::getWorker() const
{
	return worker;
}

bool PollWorkerMemberWidget::getHasWoker() const
{
	return hasWorker;
}

bool PollWorkerMemberWidget::getIsSelected() const
{
    return isSelected;
}

void PollWorkerMemberWidget::setIsSelected(bool isSelected)
{
    this->isSelected = isSelected;
    SetFramesBackGround(isSelected);
}

bool PollWorkerMemberWidget::getHasInfo() const
{
	return hasInfo;
}

void PollWorkerMemberWidget::setHasInfo(bool hasInfo)
{
	this->hasInfo = hasInfo;
}

void PollWorkerMemberWidget::SetFramesBackGround(bool isSelected)
{
/*	if(isSelected)
	{
		topEvent->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("Orange"));
		bottomEvent->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("Orange"));
	}
	else
	{
		topEvent->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("White"));
		bottomEvent->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("White"));
	}
	*/
}

int PollWorkerMemberWidget::getPosition() const
{
    return position;
}

void PollWorkerMemberWidget::setPosition(int position)
{
    this->position = position;
}

sigc::signal<void, bool> PollWorkerMemberWidget::signal_pollworker_clicked()
{
	return getSignalClick();
}

