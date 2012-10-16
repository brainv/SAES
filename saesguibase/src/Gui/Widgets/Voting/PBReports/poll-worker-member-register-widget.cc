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

#include "poll-worker-member-register-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <iostream>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>

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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

ISMTTLog* PollWorkerMemberRegisterWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerMemberRegisterWidget",GETTEXT_PACKAGE);

PollWorkerMemberRegisterWidget::PollWorkerMemberRegisterWidget()
: StepWidget()
{
	RegisterWidgetConfiguration registerConfig = SAESGUIConfigurationManager::Current()->GetPollWorkerRegisterFunctionalityConfiguration().getRegisterWidgetConfiguration();

	int row = registerConfig.getMaxRow();
	int col = registerConfig.getMaxColumn();
	int spacing = registerConfig.getSpacingBox();
	int width = registerConfig.getWidthBox();
	int height = registerConfig.getHeigthBox();
	bool verticalFilling = registerConfig.getVerticalFilling();

	registerWidget = new RegisterWidget(false, NULL);
	registerWidget->setConfig(row, col, spacing, spacing, width, height, verticalFilling);

	pollID = NULL;
	alignChoose = NULL;
	idBox = NULL;
	deleteWidget = NULL;
	isModified = false;
	showConfirmationDelete = false;

	pollWrapper = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getPollworkers();

	config = SAESGUIConfigurationManager::Current()->GetPollWorkerRegisterFunctionalityConfiguration();

	showConfirmationDelete = config.getShowDeleteConfirmation();

	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationSequence sepPollWorker = SAESGUIConfigurationManager::Current()->GetPollWorkerRegisterFunctionalityConfiguration().getPollWorkerRegisterConfiguration();
	PollWorkerRegisterFunctionalityConfiguration::PollWorkerRegisterConfigurationIterator itp;

	int currentBox = 0;

	for (itp = sepPollWorker.begin();
			itp != sepPollWorker.end();
			itp++)
	{
		for(unsigned int i = 0; i < (*itp).getRegisterMax(); i++, currentBox++)
		{
			Smartmatic::SAES::Voting::PBReports::WorkerMemberType member = (*itp).getWorkerMemberType();

			pollMember = manage(new PollWorkerMemberWidget());
			pollMember->signal_pollworker_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_pollWorker_clicked), currentBox));
			pollMember->Initialize(member);

			mapPollWorker[currentBox] = pollMember;
			registerWidget->addWidget(pollMember, " ");
		}
	}

	registerWidget->setCurrentPage(0);

	//end comment
	int wbtn = 250;
	int hbtn = 70;

	pollID = new PollWorkerIDCardWidget();
	pollID->signal_button_accept_clicked().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_pollWorker_ready));
	pollID->signal_button_back_clicked().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_cleanButton_clicked));

	Alignment* pollIDAlign = manage(new Alignment());
	pollIDAlign->set(0.5, 0.5, 0.0, 0.0);
	pollIDAlign->add(*pollID);

	idBox = manage(new VBox(false, 20));
	idBox->pack_start(*pollIDAlign);

	// CHOOSE
	VButtonBox* chooseBox = manage(new VButtonBox());
	chooseBox->set_layout(BUTTONBOX_SPREAD);

	for (itp = sepPollWorker.begin();
			itp != sepPollWorker.end();
			itp++)
	{
		for(unsigned int i = 0; i < (*itp).getRegisterMax(); i++)
		{
			SmartmaticButton* button = manage(new SmartmaticButton());
			button->signal_clicked().connect(sigc::bind<Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value>(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_choose_clicked),(*itp).getWorkerMemberType()));
			button->set_size_request(wbtn, hbtn);
			chooseBox->pack_start(*button);
		}
	}

	chooseBox->set_spacing(10);

	alignChoose = manage(new Alignment());
	alignChoose->set(0.5, 0.5, 0.0, 0.0);
	alignChoose->add(*chooseBox);
	alignChoose->show_all_children();

	addButton = manage(new SmartmaticButton("&add"));
	addButton->signal_clicked().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_addButton_clicked));
	addButton->set_size_request(100, 50);

	deleteButton = manage(new SmartmaticButton("&delete"));
	//deleteButton->signal_clicked().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_deleteButton_clicked));
	deleteButton->set_size_request(100, 50);

	modifyButton = manage(new SmartmaticButton("&modify"));
	//modifyButton->signal_clicked().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_modifyButton_clicked));
	modifyButton->set_size_request(100, 50);

	HButtonBox* btnBox = manage(new HButtonBox());
	btnBox->set_spacing(30);
	btnBox->set_layout(BUTTONBOX_CENTER);
	btnBox->pack_start(*deleteButton, false, false);
	btnBox->pack_start(*addButton, false, false);

	deleteWidget = manage(new ConfirmationDeleteWidget());
	deleteWidget->on_answer_emit().connect(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::on_confirmationDelete_send));

	setWidget(registerWidget);
}

PollWorkerMemberRegisterWidget::~PollWorkerMemberRegisterWidget()
{
	this->remove();

	if(pollID)
	{
		delete pollID;
		pollID = NULL;
	}
	if (registerWidget)
	{
		delete registerWidget;
		registerWidget = NULL;
	}
}

void PollWorkerMemberRegisterWidget::Dispose()
{
	if(pollID)
	{
		pollID->dispose();
	}
}

void PollWorkerMemberRegisterWidget::on_confirmationDelete_send(bool deleteWorker)
{
	if(deleteWorker)
	{
		DeleteWorker();
	}
	else
	{
		setWidget(idBox);
	}
}

void PollWorkerMemberRegisterWidget::on_cleanButton_clicked()
{
	if(showConfirmationDelete)
	{
		setWidget(deleteWidget);
	}
	else
	{
		DeleteWorker();
	}
}

void PollWorkerMemberRegisterWidget::DeleteWorker()
{
	if(pollMember->getHasWoker())
	{
		Worker worker = pollMember->getWorker();
		pollWrapper->RemoveWorker(worker);
		Persist();
	}
	pollMember->ClearData();
	pollID->dispose();

	setWidget(registerWidget);
	signalEnabled.emit();
}

void PollWorkerMemberRegisterWidget::on_pollWorker_clicked(bool hasInfo, int position)
{
	signalDisabled.emit();

	logger->Debug("poll worker click");

	pollMember = mapPollWorker[position];
	if(!hasInfo)
	{
		isModified = false;
		on_choose_clicked(pollMember->GetMember());
	}
	else
	{
		isModified = true;
		Worker worker = pollMember->getWorker();
		on_choose_clicked(worker.getMember_type());
		pollID->SetParams(worker);
	}
}

void PollWorkerMemberRegisterWidget::on_addButton_clicked()
{
	setWidget(alignChoose);
}

void PollWorkerMemberRegisterWidget::on_pollWorker_ready()
{
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &PollWorkerMemberRegisterWidget::SetPollWorker), 100);
}

void PollWorkerMemberRegisterWidget::SetPollWorker()
{
	logger->Debug("poll worker exit");

	pollID->dispose();

	Worker worker;

	//AddNewWorkerBox();
	if(!isModified)
	{
		pollID->GetParams(worker);
		pollWrapper->AddWorker(worker);
	}
	else
	{
		worker = pollMember->getWorker();
		pollID->GetParams(worker);
		pollWrapper->ModifyWorker(worker);
	}

	Persist();

	pollMember->setWorker(worker);
	setWidget(registerWidget);

	signalEnabled.emit();
}

void PollWorkerMemberRegisterWidget::CleanSelections()
{
	std::map<int, PollWorkerMemberWidget*>::iterator iter;

	for(iter = mapPollWorker.begin(); iter != mapPollWorker.end(); iter++)
	{
		iter->second->setIsSelected(false);
	}
	logger->Audit(N_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerMemberRegisterWidget.CleanedSelections"));
}

void PollWorkerMemberRegisterWidget::on_choose_clicked(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member)
{
	signalDisabled.emit();
	setWidget(idBox);

	pollID->Initialize(member);
	pollID->initialize();
}

bool PollWorkerMemberRegisterWidget::Persist()
{
	try
	{
		pollWrapper->Persist();
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool PollWorkerMemberRegisterWidget::checkNewStatus()
{
	return SAESGUIConfigurationManager::Current()->checkPollworkerRegister();
}

void PollWorkerMemberRegisterWidget::Load()
{
	logger->Debug("Load pollworker");

	Workers::WorkerSequence workers = pollWrapper->getWorkers().getWorker();
	Workers::WorkerIterator it;

	std::map<int, PollWorkerMemberWidget*>::iterator iterPoll;

	for(iterPoll = mapPollWorker.begin();
			iterPoll != mapPollWorker.end();
			iterPoll++)
	{
		for ( it = workers.begin();
				it != workers.end();
			 ++it)
		{
			if (iterPoll->second->GetMember() == (*it).getMember_type())
			{
				iterPoll->second->setWorker(*it);
				workers.erase(it);
				break;
			}
		}
	}
}

sigc::signal<void> PollWorkerMemberRegisterWidget::getSignalEnabled()
{
	return signalEnabled;
}

sigc::signal<void> PollWorkerMemberRegisterWidget::getSignalDisabled()
{
	return signalDisabled;
}
