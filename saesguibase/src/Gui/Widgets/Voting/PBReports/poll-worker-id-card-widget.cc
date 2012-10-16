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

#include "poll-worker-id-card-widget.h"
#include <Operation/MachineOperationManager.hxx>
#include <Voting/PBReports/id-card-info-wrapper.h>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/ValidateWidget.hxx>

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

using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::System::Exception;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::GUI::Operation;

Smartmatic::Log::ISMTTLog* PollWorkerIDCardWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.PollWorkerIDCardWidget",GETTEXT_PACKAGE);

PollWorkerIDCardWidget::PollWorkerIDCardWidget()
:IDCardWidget("", "", true)
{
	this->HideAcceptTitle();
	this->SetShowAcept(false);

	accountEntry = manage(new SmartmaticEntry()); ///< The additional entry
	accountEntry->set_size_request(entryWidth, entryHeight);
	accountEntry->set_no_show_all();

	accountLabel = manage(new Label(" ")); ///< The additional label
	accountLabel->set_alignment(0.0, 0.5);
	accountLabel->set_size_request(labelWidth, entryHeight);
	accountLabel->set_no_show_all();

    Pango::FontDescription fontDesc = accountLabel->get_style()->get_font();
    fontDesc.set_size(12*Pango::SCALE);
    accountLabel->modify_font(fontDesc);

    partyEntry = manage(new SmartmaticEntry()); ///< The additional entry
    partyEntry->set_size_request(entryWidth, entryHeight);
	partyEntry->set_no_show_all();

    partyLabel = manage(new Label(" ")); ///< The additional label
    partyLabel->set_alignment(0.0, 0.5);
    partyLabel->set_size_request(labelWidth, entryHeight);
	partyLabel->set_no_show_all();

    fontDesc = partyLabel->get_style()->get_font();
    fontDesc.set_size(12*Pango::SCALE);
    partyLabel->modify_font(fontDesc);

    phoneEntry = manage(new SmartmaticEntry(SmartmaticEntry::AllWithoutAlphabetic)); ///< The additional entry
	phoneEntry->set_size_request(entryWidth, entryHeight);
	phoneEntry->set_no_show_all();

	phoneLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.Phone"))); ///< The additional label
	phoneLabel->set_alignment(0.0, 0.5);
	phoneLabel->set_size_request(labelWidth, entryHeight);
	phoneLabel->set_no_show_all();
	phoneLabel->modify_font(fontDesc);

    allDayCheckButton = manage(new Gtk::CheckButton());
    allDayCheckButton->set_size_request(entryWidth, entryHeight);
    allDayCheckButton->set_no_show_all();
    allDayCheckButton->signal_toggled().connect(sigc::mem_fun(*this, &PollWorkerIDCardWidget::allDayChange));

	allDayLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.AllJournal"))); ///< The additional label
	allDayLabel->set_alignment(0.0, 0.5);
	allDayLabel->set_size_request(labelWidth, entryHeight);
	allDayLabel->set_no_show_all();
	allDayLabel->modify_font(fontDesc);

    initEntry = manage(new SmartmaticEntry(SmartmaticEntry::AllWithoutAlphabetic)); ///< The additional entry
    initEntry->set_size_request(entryWidth, entryHeight);
    initEntry->set_no_show_all();

	initLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.InitJournal"))); ///< The additional label
	initLabel->set_alignment(0.0, 0.5);
	initLabel->set_size_request(labelWidth, entryHeight);
	initLabel->set_no_show_all();
	initLabel->modify_font(fontDesc);
	initLabel->set_line_wrap(true);
	initLabel->set_line_wrap_mode(Pango::WRAP_WORD);

    endEntry = manage(new SmartmaticEntry(SmartmaticEntry::AllWithoutAlphabetic)); ///< The additional entry
    endEntry->set_size_request(entryWidth, entryHeight);
    endEntry->set_no_show_all();

	endLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.EndJournal"))); ///< The additional label
	endLabel->set_alignment(0.0, 0.5);
	endLabel->set_size_request(labelWidth, entryHeight);
	endLabel->set_no_show_all();
	endLabel->modify_font(fontDesc);
	endLabel->set_line_wrap(true);
	endLabel->set_line_wrap_mode(Pango::WRAP_WORD);

	bureauAssignedCheckButton = manage(new Gtk::CheckButton());
	bureauAssignedCheckButton->set_size_request(entryWidth, entryHeight);
	bureauAssignedCheckButton->set_no_show_all();

	bureauAssignedLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.BureauAssignedLabel")));
	bureauAssignedLabel->set_alignment(0.0, 0.5);
	bureauAssignedLabel->set_size_request(labelWidth, entryHeight);
	bureauAssignedLabel->set_no_show_all();
	bureauAssignedLabel->modify_font(fontDesc);
	bureauAssignedLabel->set_line_wrap(true);
	bureauAssignedLabel->set_line_wrap_mode(Pango::WRAP_WORD);

	acceptDesignationCheckButton = manage(new Gtk::CheckButton());
	acceptDesignationCheckButton->set_size_request(entryWidth, entryHeight);
	acceptDesignationCheckButton->set_no_show_all();

	acceptDesignationLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.AcceptDesignationLabel")));
	acceptDesignationLabel->set_alignment(0.0, 0.5);
	acceptDesignationLabel->set_size_request(labelWidth, entryHeight);
	acceptDesignationLabel->set_no_show_all();
	acceptDesignationLabel->modify_font(fontDesc);
	acceptDesignationLabel->set_line_wrap(true);
	acceptDesignationLabel->set_line_wrap_mode(Pango::WRAP_WORD);

	deputyCommentLabel = manage(new Label(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.ImpugnationReason")));
	deputyCommentLabel->set_alignment(0.0, 0.0);
	deputyCommentLabel->set_size_request(labelWidth, entryHeight);
	deputyCommentLabel->set_line_wrap(true);
	deputyCommentLabel->set_line_wrap_mode(Pango::WRAP_WORD);
	deputyCommentLabel->set_no_show_all();
	deputyCommentLabel->modify_font(fontDesc);

	textView = manage(new SmartmaticTextView());
	textView->set_size_request(entryWidth, entryHeight);
	textView->set_no_show_all();

	if(removeCardLabel)
	{
		removeCardLabel->hide();
	}

	backButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerMemberRegisterWidget.CleanButton")));
	backButton->signal_clicked().connect(sigc::mem_fun(*this, &PollWorkerIDCardWidget::on_backButton_clicked));
	backButton->set_size_request(180, 50);
	backButton->SetButtonType(SmartmaticButton::Cancel);
	backButton->WidgetsPosition(5,6,0);

	acceptButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Widgets.IDCardWidget.AcceptButtonMessage")));
	acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &PollWorkerIDCardWidget::on_acceptButton_clicked));
	acceptButton->set_size_request(180, 50);
	acceptButton->SetButtonType(SmartmaticButton::Ok);
	acceptButton->WidgetsPosition(5,6,0);

	if(buttonAccept != NULL)
	{
		buttonBox->remove(*buttonAccept);
		delete buttonAccept;
	}

	buttonBox->pack_start(*backButton, false, false);
	buttonBox->pack_start(*acceptButton, false, false);
}

PollWorkerIDCardWidget::~PollWorkerIDCardWidget()
{

}

bool PollWorkerIDCardWidget::ShowEntryDataAndEmitSignal(int timer)
{
	acceptButton->show();
	backButton->show();
	return IDCardWidget::ShowEntryDataAndEmitSignal(timer);
}

IDCardWidget::signal_void PollWorkerIDCardWidget::signal_button_accept_clicked()
{
	return m_accept_button_clicked;
}

IDCardWidget::signal_void PollWorkerIDCardWidget::signal_button_back_clicked()
{
	return m_back_button_clicked;
}

void PollWorkerIDCardWidget::on_acceptButton_clicked()
{
	GetData();

	if(CheckCompleteData())
		m_accept_button_clicked.emit();
	else
	{
		acceptButton->hide();
		backButton->hide();
		ShowInCompleteData();
	}
}

void PollWorkerIDCardWidget::on_backButton_clicked()
{
	m_back_button_clicked.emit();
}

void PollWorkerIDCardWidget::Initialize(Smartmatic::SAES::Voting::PBReports::WorkerMemberType::Value member)
{
	this->member = member;

	idConfig = SAESGUIConfigurationManager::Current()->getPollWorkerIDConfiguration(member);

	ShowElements();

	accountLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.Account"));
	partyLabel->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerDialogWidget.Party"));

	allDayCheckButton->set_active(false);
	acceptDesignationCheckButton->set_active(false);
	bureauAssignedCheckButton->set_active(false);

	allDayChange();

	switch(member)
	{
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_PRESIDENT:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.PresidentId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_SECRETARY:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.SecretaryId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_ASSISTENT:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.AssistentId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_WITNESS:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.WitnessId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_POLICE:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.PoliceId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_ASSISTANT_SECRETARY:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.AssistantSecretaryId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_PRESIDENT:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputyPresidentId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_SECRETARY:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputySecretaryId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTENT:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputyAssistentId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_WITNESS:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputyWitnessId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_POLICE:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputySecretaryId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY_ASSISTANT_SECRETARY:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.DeputyAssistantSecretaryId"));
			break;
		case Smartmatic::SAES::Configuration::WorkerMemberType::POLLWORKERS_DEPUTY:
			labelMessage->set_text(_("Smartmatic.SAES.GUI.Widgets.Voting.PBReports.PollWorkerIDCardWidget.Deputy"));
			break;
	}

	dataTable->show_all_children();

	ClearNames();
	removeCardLabel->hide();
}

void PollWorkerIDCardWidget::ShowElements()
{
	IDCardWidget::ShowElements();

	phoneLabel->set_visible(idConfig.getPhone().present());
	phoneEntry->set_visible(idConfig.getPhone().present());

	accountLabel->set_visible(idConfig.getAccount().present());
	accountEntry->set_visible(idConfig.getAccount().present());

	partyLabel->set_visible(idConfig.getParty().present());
	partyEntry->set_visible(idConfig.getParty().present());

	allDayLabel->set_visible(idConfig.getAllDay().present());
	allDayCheckButton->set_visible(idConfig.getAllDay().present());

	initLabel->set_visible(idConfig.getAllDay().present());
	initEntry->set_visible(idConfig.getAllDay().present());

	endLabel->set_visible(idConfig.getAllDay().present());
	endEntry->set_visible(idConfig.getAllDay().present());

	bureauAssignedCheckButton->set_visible(idConfig.getBureauAssigned().present());
	bureauAssignedLabel->set_visible(idConfig.getBureauAssigned().present());

	acceptDesignationCheckButton->set_visible(idConfig.getInfoDeputy().present());
	acceptDesignationLabel->set_visible(idConfig.getInfoDeputy().present());

	textView->set_visible(idConfig.getInfoDeputy().present());
	deputyCommentLabel->set_visible(idConfig.getInfoDeputy().present());

	if (idConfig.getPhone().present())
	{
		dataTable->put(phoneLabel, countElement, 0);
		dataTable->put(phoneEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getPhone().get(), phoneEntry);
	}

	if (idConfig.getAccount().present())
	{
		dataTable->put(accountLabel, countElement, 0);
		dataTable->put(accountEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getAccount().get(), accountEntry);
	}

	if (idConfig.getParty().present())
	{
		dataTable->put(partyLabel, countElement, 0);
		dataTable->put(partyEntry, countElement++, 1);
		ValidateWidget::setProperties(idConfig.getParty().get(), partyEntry);
	}

	if (idConfig.getAllDay().present())
	{
		dataTable->put(allDayLabel, countElement, 0);
		dataTable->put(allDayCheckButton, countElement++, 1);

		dataTable->put(initLabel, countElement, 0);
		dataTable->put(initEntry, countElement++, 1);

		dataTable->put(endLabel, countElement, 0);
		dataTable->put(endEntry, countElement++, 1);

		ValidateWidget::setProperties(idConfig.getAllDay().get(), initEntry);
		ValidateWidget::setProperties(idConfig.getAllDay().get(), endEntry);
	}

	if (idConfig.getBureauAssigned().present())
	{
		dataTable->put(bureauAssignedLabel, countElement, 0);
		dataTable->put(bureauAssignedCheckButton, countElement++, 1);
	}

	if (idConfig.getInfoDeputy().present())
	{
		dataTable->put(acceptDesignationLabel, countElement, 0);
		dataTable->put(acceptDesignationCheckButton, countElement++, 1);

		dataTable->put(deputyCommentLabel, countElement, 0);
		dataTable->put(textView, countElement++, 1);

		ValidateWidget::setProperties(idConfig.getInfoDeputy().get(), textView);
	}
}

bool PollWorkerIDCardWidget::CheckCompleteData()
{
	bool returnVariable = true;

	GetData();

	idConfig = SAESGUIConfigurationManager::Current()->getPollWorkerIDConfiguration(member);

	if (!IDCardWidget::CheckCompleteData())
	{
		returnVariable = false;
	}
	else if (idConfig.getPhone().present() && !ValidateWidget::validate(idConfig.getPhone().get(), phoneEntry))
	{
		returnVariable = false;
	}
	else if (idConfig.getAccount().present() && !ValidateWidget::validate(idConfig.getAccount().get(), accountEntry))
	{
		returnVariable = false;
	}
	else if (idConfig.getParty().present() && !ValidateWidget::validate(idConfig.getParty().get(), partyEntry))
	{
		returnVariable = false;
	}
	else if (idConfig.getAllDay().present() && !allDayCheckButton->get_active())
	{
		std::string data1 = initEntry->get_text();
		std::string data2 = endEntry->get_text();

		if (!ValidateWidget::validate(idConfig.getAllDay().get(), initEntry) || !ValidateWidget::validate(idConfig.getAllDay().get(), endEntry))
		{
			returnVariable = false;
		}
		else if (data2.compare(data1) <= 0)
		{
			endEntry->setBGError();
			returnVariable = false;
		}
	}

	if (returnVariable && idConfig.getInfoDeputy().present() && !ValidateWidget::validate(idConfig.getInfoDeputy().get(), textView))
	{
		returnVariable = false;
	}

	return returnVariable;
}

void PollWorkerIDCardWidget::GetParams(Worker& worker)
{
	GetData();
	IDCardInfo info;
	IDCardInfoWrapper::generateIdCardInfoWrapper(citizenInfo, info);
	worker.setPersonal_info(info);
	worker.setMember_type(member);
	worker.setAccount_number("" + (std::string)accountEntry->get_text());
	worker.setParty("" + (std::string)partyEntry->get_text());
	worker.setCustom_code(customCode);
	worker.setPhone("" + (std::string)phoneEntry->get_text());

	if (allDayCheckButton->is_visible())
	{
		worker.setAll_day(allDayCheckButton->get_active());

		if (!allDayCheckButton->get_active())
		{
			worker.setStart_time("" + (std::string)initEntry->get_text());
			worker.setEnd_time("" + (std::string)endEntry->get_text());
		}
	}

	if (bureauAssignedCheckButton->is_visible())
	{
		worker.setBureau_assigned(bureauAssignedCheckButton->get_active());
	}

	if (acceptDesignationCheckButton->is_visible())
	{
		worker.setAccept_designation(acceptDesignationCheckButton->get_active());
		worker.setImpugnation_reason("" + (std::string)textView->getText());
	}
}

void PollWorkerIDCardWidget::SetParams(Worker & worker)
{
	Initialize(worker.getMember_type());
	Smartmatic::SAES::EID::CitizenInfo info;
	IDCardInfoWrapper::generateCitizenInfo(worker.getPersonal_info(), info);
	setCitizenInfo(info);
	worker.setMember_type(member);

	customCode = worker.getCustom_code();

	accountEntry->set_text(worker.getAccount_number());
	partyEntry->set_text("" + worker.getParty());
	phoneEntry->set_text(worker.getPhone());

	allDayCheckButton->set_active(worker.getAll_day().present() ? worker.getAll_day().get() : false);
	initEntry->set_text(worker.getStart_time().present() ? worker.getStart_time().get() : "");
	endEntry->set_text(worker.getEnd_time().present() ? worker.getEnd_time().get() : "");

	bureauAssignedCheckButton->set_active(worker.getBureau_assigned().present() ? worker.getBureau_assigned().get() : false);

	acceptDesignationCheckButton->set_active(worker.getAccept_designation().present() ? worker.getAccept_designation().get() : false);
	textView->setText(worker.getImpugnation_reason().present() ? worker.getImpugnation_reason().get() : "");
}

void PollWorkerIDCardWidget::allDayChange()
{
	bool active = !allDayCheckButton->get_active();

	initLabel->set_sensitive(active);
	endLabel->set_sensitive(active);
	initEntry->set_sensitive(active);
	endEntry->set_sensitive(active);
}
