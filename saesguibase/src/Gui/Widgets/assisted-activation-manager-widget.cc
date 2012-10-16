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

#include "assisted-activation-manager-widget.h"
#include <Voting/PBReports/assisted-activation-wrapper.h>
#include <Operation/MachineOperationManager.hxx>
#include <Voting/PBReports/id-card-info-wrapper.h>
#include <eid/CitizenInfo.h>
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
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::EID;

Smartmatic::Log::ISMTTLog* AssistedActivationManagerWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget",GETTEXT_PACKAGE);

AssistedActivationManagerWidget::AssistedActivationManagerWidget()
{
	set_shadow_type(SHADOW_NONE);
	wizardWidget = NULL;
	nextButton = NULL;
	backButton = NULL;
	voterID = NULL;
	helperID = NULL;
	presidentID = NULL;
	challengerID = NULL;
	finalHelperID = NULL;
	proxyQuestion = NULL;
	challengeQuestion = NULL;
	impugnWidget = NULL;
	vbox = NULL;
	labelWait = NULL;

	/*int width = 130;
	int height = 50;

	nextButton = manage(new SmartmaticButton("& next"));
	nextButton->signal_clicked().connect(sigc::mem_fun(this, &AssistedActivationManagerWidget::on_nextButton_clicked));
	nextButton->set_size_request(width, height);


	backButton = manage(new SmartmaticButton("& back"));
	backButton->signal_clicked().connect(sigc::mem_fun(this, &AssistedActivationManagerWidget::on_backButton_clicked));
	backButton->set_size_request(width, height);

	HButtonBox* btnBox = manage(new HButtonBox());
	btnBox->set_layout(BUTTONBOX_SPREAD);
	btnBox->pack_start(*nextButton, false, false);
	btnBox->pack_start(*backButton, false, false);
	btnBox->set_size_request(-1, 100);*/

	voterID = new AssistedActivationIDCardWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.VoterInfo"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.VoterInfoInstruction"));

	helperID = new AssistedActivationIDCardWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.PropossedInfo") ,
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.PropossedInfoInstruction"));

	presidentID = new AssistedActivationIDCardWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.PollworkerInfo"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.PollworkerInfoInstruction"));

	challengerID = new AssistedActivationIDCardWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ImpugnatorInfo"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ImpugnatorInfoInstruction"));

	finalHelperID = new AssistedActivationIDCardWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.DesignatedPersonInfo"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.DesignatedInfoInstruction"));

	proxyQuestion = new AssistedActivationQuestionWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ProxyQuestion"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ProxyButton"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.PresentialButton"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ProxyQuestionInstruction"), true);

	challengeQuestion = new AssistedActivationQuestionWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ChallengeQuestion"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.YesButton"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.NoButton"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ChallengeQuestionInstruction"), false);
	challengeQuestion->SendStopWizardOnCancel();

	impugnWidget = new AssistedActivationImpugnationWidget(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ChallengeTitle"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.AcceptButton"),
			_("Smartmatic.SAES.GUI.Widgets.AssistedActivationManagerWidget.ChallengeInstruction"));

	vector<WizardWidgetBase*> widgetsVector;
	widgetsVector.push_back(voterID);
	widgetsVector.push_back(helperID);
	widgetsVector.push_back(presidentID);
	widgetsVector.push_back(proxyQuestion);
	widgetsVector.push_back(challengeQuestion);
	widgetsVector.push_back(challengerID);
	widgetsVector.push_back(impugnWidget);
	widgetsVector.push_back(finalHelperID);

	wizardWidget = new WizardWidgetManager(widgetsVector);
	wizardWidget->set_shadow_type(SHADOW_NONE);
	wizardWidget->on_finish_signal_emit().connect(sigc::mem_fun(*this, &AssistedActivationManagerWidget::on_finishSignal_emitted));

	//vbox = new VBox(false, 20);
	//vbox->pack_start(*wizardWidget, false, false);
	//vbox->pack_start(*btnBox, false, false);

	add(*wizardWidget);
}

void AssistedActivationManagerWidget::on_nextButton_clicked()
{

}

void AssistedActivationManagerWidget::on_backButton_clicked()
{

}

void AssistedActivationManagerWidget::Dispose()
{
	if(voterID)
		voterID->dispose();

	if(helperID)
		helperID->dispose();

	if(presidentID)
		presidentID->dispose();

	if(challengerID)
		challengerID->dispose();
	
	if(finalHelperID)
		finalHelperID->dispose();

}

AssistedActivationManagerWidget::~AssistedActivationManagerWidget()
{
	if(labelWait) delete labelWait;
	if(backButton) delete backButton;
	if(nextButton) delete nextButton;
	if(vbox) delete vbox;
	if(voterID) delete voterID;
	if(helperID) delete helperID;
	if(presidentID) delete presidentID;
	if(challengerID) delete challengerID;
	if(finalHelperID) delete finalHelperID;
	if(proxyQuestion) delete proxyQuestion;
	if(challengeQuestion) delete challengeQuestion;
	if(impugnWidget) delete impugnWidget;
	if(wizardWidget) delete wizardWidget;
}

void AssistedActivationManagerWidget::Start()
{

	wizardWidget->Start();
	/*if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &CloseElectionStatusWidget::ThreadStart), true);
	//Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &CloseElectionStatusWidget::on_done),5000);*/
}

void AssistedActivationManagerWidget::on_finishSignal_emitted()
{
	Activation activation;

	CitizenInfo voterCI = voterID->GetCitizenInfo();
	IDCardInfo voterInfo;
	IDCardInfoWrapper::generateIdCardInfoWrapper(voterCI, voterInfo);

	CitizenInfo helperCI = helperID->GetCitizenInfo();
	IDCardInfo helperInfo;
	IDCardInfoWrapper::generateIdCardInfoWrapper(helperCI, helperInfo);

	CitizenInfo presidentCI = presidentID->GetCitizenInfo();
	IDCardInfo presidentInfo;
	IDCardInfoWrapper::generateIdCardInfoWrapper(presidentCI, presidentInfo);

	bool isProxy = proxyQuestion->GetAnswer();
	bool hasChallenge = challengeQuestion->GetAnswer();

	challengeQuestion->reset();
	challengeQuestion->SendStopWizardOnCancel();

	activation.setVoter(voterInfo);
	activation.setPropossedPerson(helperInfo);
	activation.setPollworker(presidentInfo);

	if(isProxy)
		activation.setActivationMode(ActivationMode::ASSISTED_ACTIVATION_PROXY);
	else
		activation.setActivationMode(ActivationMode::ASSISTED_ACTIVATION_PRESENTIAL);

	activation.setWasImpugned(hasChallenge);

	if(hasChallenge)
	{
		CitizenInfo challengerCI = challengerID->GetCitizenInfo();
		IDCardInfo challengerInfo;
		IDCardInfoWrapper::generateIdCardInfoWrapper(challengerCI, challengerInfo);

		CitizenInfo finalHelperCI = finalHelperID->GetCitizenInfo();
		IDCardInfo finalHelperInfo;
		IDCardInfoWrapper::generateIdCardInfoWrapper(finalHelperCI, finalHelperInfo);

		string reason = impugnWidget->GetReason();

		activation.setImpugnator(challengerInfo);
		activation.setDesignatedPerson(finalHelperInfo);
		activation.setImpugnationReason(reason);
	}

	EmitFinish(activation);
}

void AssistedActivationManagerWidget::EmitFinish(Activation activation)
{
	m_activation_signal.emit(activation);
}

AssistedActivationManagerWidget::type_activation_signal AssistedActivationManagerWidget::on_activation_signal_emit()
{
	return m_activation_signal;
}
