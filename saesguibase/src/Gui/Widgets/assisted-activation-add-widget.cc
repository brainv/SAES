/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesguibase
 * Copyright (C)  2011 <>
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

#include "Gui/Widgets/assisted-activation-add-widget.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include <Voting/PBReports/id-card-info-schema.hxx>
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

using namespace Glib;
using namespace std;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::Log;

ISMTTLog* AssistedActivationAddWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget",GETTEXT_PACKAGE);

AssistedActivationAddWidget::AssistedActivationAddWidget(bool waitForCardToRegister):vboxPrincipal(20),hboxWitness(10),hboxPresident(10),hboxVoter(10)
{
	this->waitForCardToRegister = waitForCardToRegister;
	//bool isChoose = true;
	chooseByCombo = Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getAssistedActivationBySelection();
	labelTitle.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.Title"));
	//labelTitle.set_label(_("Assisted Activation"));
	labelTitle.set_justify(Gtk::JUSTIFY_CENTER);
	labelTitle.set_alignment(0.5, 0.5);
	//labelTitle.set_padding(10, 0);
	labelTitle.set_size_request(600, -1);
	//labelTitle.set_line_wrap(true);
	Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelTitle.modify_font(fontTitle);	


	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.MessageInitial"));
	//labelMessage.set_label(_("Press Ok when ready to generate the card, or Cancel to go back"));
	labelMessage.set_alignment(0.5, 0.5);
	labelMessage.set_justify(Gtk::JUSTIFY_CENTER);
	//labelMessage.set_padding(10, 0);
	labelMessage.set_size_request(600, -1);
	//labelMessage.set_line_wrap(true);
	Pango::FontDescription fontMessage = labelMessage.get_style()->get_font();
	fontMessage.set_size(12*Pango::SCALE);
	fontMessage.set_weight(Pango::WEIGHT_ULTRABOLD);
	labelMessage.modify_font(fontMessage);	
	
	Pango::FontDescription fontLabels = labelWitness.get_style()->get_font();
	fontLabels.set_size(12*Pango::SCALE);
	fontLabels.set_weight(Pango::WEIGHT_ULTRABOLD);

	labelWitness.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.LabelWitness"));
	//labelWitness.set_label(_("Witness:"));
	labelWitness.set_alignment(0.0, 0.5);
	labelWitness.set_padding(10, 0);
	labelWitness.set_size_request(100, -1);
	labelWitness.set_line_wrap(true);
	labelWitness.modify_font(fontLabels);

	labelPresident.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.LabelPresident"));
	//labelPresident.set_label(_("President:"));
	labelPresident.set_alignment(0.0, 0.5);
	labelPresident.set_padding(10, 0);
	labelPresident.set_size_request(100, -1);
	labelPresident.set_line_wrap(true);
	labelPresident.modify_font(fontLabels);

	labelVoter.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.LabelVoter"));
	//labelVoter.set_label(_("Voter:"));
	labelVoter.set_alignment(0.0, 0.5);
	labelVoter.set_padding(10, 0);
	labelVoter.set_size_request(100, -1);
	labelVoter.set_line_wrap(true);
	labelVoter.modify_font(fontLabels);

	hboxPresident.pack_start (labelPresident,Gtk::PACK_SHRINK);
	if(!chooseByCombo)
	{
		entryPresident.set_size_request(300,-1);
		hboxPresident.pack_start (entryPresident,Gtk::PACK_SHRINK);
	}
	else
	{
		comboPresident.set_size_request (300,-1);
		comboPresident.m_combo_changed.connect( sigc::mem_fun(this, &AssistedActivationAddWidget::onPresidentComboChanged));
		hboxPresident.pack_start (comboPresident,Gtk::PACK_SHRINK);
	}

	
	hboxWitness.pack_start (labelWitness,Gtk::PACK_SHRINK);
	if(!chooseByCombo)
	{
		entryWitness.set_size_request (300,-1);
		hboxWitness.pack_start (entryWitness,Gtk::PACK_SHRINK);
	}
	else
	{
		comboWitness.set_size_request (300,-1);
		comboWitness.m_combo_changed.connect( sigc::mem_fun(this, &AssistedActivationAddWidget::onWitnessComboChanged));
		hboxWitness.pack_start (comboWitness,Gtk::PACK_SHRINK);
	}

	hboxVoter.pack_start (labelVoter,Gtk::PACK_SHRINK);
	entryVoter.set_size_request (300,-1);
	hboxVoter.pack_start (entryVoter,Gtk::PACK_SHRINK);

	okButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.ButtonOk"));
	//okButton.SetLabel(_("Ok"));
	okButton.WidgetsPosition (5,0,0);
	okButton.set_size_request (100,50);	

	cancelButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.ButtonCancel"));
	//cancelButton.SetLabel(_("Cancel"));
	cancelButton.WidgetsPosition (5,0,0);
	cancelButton.set_size_request (100,50);

	
	hbuttonbox.set_spacing (100);
	hbuttonbox.set_layout (Gtk::BUTTONBOX_CENTER );
	hbuttonbox.add(okButton);
	hbuttonbox.add(cancelButton);	
	
	vboxPrincipal.pack_start (labelTitle,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (hboxPresident,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (hboxWitness,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (hboxVoter,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (labelMessage,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (hbuttonbox,Gtk::PACK_SHRINK);	
	vboxPrincipal.show_all_children ();
	vboxPrincipal.set_size_request (-1,400);
	vboxPrincipal.set_visible (true);
	
	pack_start(vboxPrincipal,Gtk::PACK_SHRINK);
	show_all_children ();
	set_visible (true);
}

void AssistedActivationAddWidget::onWitnessComboChanged(ustring selected)
{
	witnessSelection = selected;
}

void AssistedActivationAddWidget::onPresidentComboChanged(ustring selected)
{
	presidentSelection = selected;
}

void AssistedActivationAddWidget::Initialize()
{
	
	labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.MessageInitial"));
	//labelMessage.set_label(_("Press Ok when ready to generate the card, or Cancel to go back"));
	connOk = okButton.signal_clicked().connect( sigc::mem_fun(this, &AssistedActivationAddWidget::on_buttonOk_clicked));
	connCancel = cancelButton.signal_clicked().connect( sigc::mem_fun(this, &AssistedActivationAddWidget::on_buttonCancel_clicked));
	if(!chooseByCombo)
	{
		entryPresident.set_text ("");
		entryWitness.set_text ("");
	}
	else
	{
		Workers workers = MachineOperationManager::getInstance()->getPollworkers()->getWorkers();
		vector<ustring> comboWitnessOptions;
		vector<ustring> comboPresidentOptions;

		Workers::WorkerIterator it;

		for ( it = workers.getWorker().begin();
				it != workers.getWorker().end();
			 ++it)
		{
			Worker w = (*it);

			if (w.getMember_type() == WorkerMemberType::POLLWORKERS_PRESIDENT)
			{
				ustring presidentName = w.getPersonal_info().getFirstName() + " " + w.getPersonal_info().getSurname();
				comboPresidentOptions.push_back (presidentName);
			}
			else if (w.getMember_type() == WorkerMemberType::POLLWORKERS_WITNESS)
			{
				ustring witnessName = w.getPersonal_info().getFirstName() + " " + w.getPersonal_info().getSurname();
				comboWitnessOptions.push_back (witnessName);
			}
		}

		comboWitness.SetOptions(comboWitnessOptions);
		comboPresident.SetOptions(comboPresidentOptions);	
		comboWitness.set_active(0);
		comboPresident.set_active(0);
	}
	entryVoter.set_text ("");
}

void AssistedActivationAddWidget::Dispose()
{
	connRefresh.disconnect();
	connOk.disconnect();
	connCancel.disconnect();
}

void AssistedActivationAddWidget::on_buttonOk_clicked()
{	
	if(!chooseByCombo)
	{
		if(entryPresident.get_text().compare("")==0)
		{
			labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.MessagePresidentEmpty"));
			return;
		}
		else if(entryWitness.get_text().compare("")==0)
		{
			labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.MessageWitnessEmpty"));
			return;
		}
		
	}
	if(entryVoter.get_text().compare("")==0)
	{
		labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.MessageVoterEmpty"));
	}
	else
	{				
		if(!waitForCardToRegister)
		{
			Activation activation;
			if(!chooseByCombo)
			{
				IDCardInfo idCardPresident;
				idCardPresident.setFirstName((string)entryPresident.get_text());
				idCardPresident.setSurname(" ");

				IDCardInfo idCardWitness;
				idCardWitness.setFirstName((string)entryWitness.get_text());
				idCardWitness.setSurname(" ");
				
				activation.setPollworker(idCardPresident);
				activation.setPropossedPerson(idCardWitness);
			}
			else
			{
				IDCardInfo idCardPresident;
				idCardPresident.setFirstName((string)presidentSelection);
				idCardPresident.setSurname(" ");

				IDCardInfo idCardWitness;
				idCardWitness.setFirstName((string)witnessSelection);
				idCardWitness.setSurname(" ");
				
				activation.setPollworker(idCardPresident);
				activation.setPropossedPerson(idCardWitness);
			}

			IDCardInfo idCardElection;
			idCardElection.setFirstName((string)entryVoter.get_text());
			idCardElection.setSurname(" ");
			activation.setVoter(idCardElection);
			
			logger->Debug("Don't wait for card to register");
			labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.AssistedActRegistered"));

			MachineOperationManager::getInstance()->getAssistedActivation()->AddActivation(activation);
			MachineOperationManager::getInstance()->getAssistedActivation()->Persist();
			signalOk_detected.emit(activation);
		}
		else
		{
			logger->Debug("Wait for card to register");
			labelMessage.set_label(_("Smartmatic.SAES.GUI.Widgets.AssistedActivationAddWidget.GeneratingCard"));

			sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
			       &AssistedActivationAddWidget::Refresh), 0);
			connRefresh = Glib::signal_timeout().connect(my_slot,300);
		}
		
	}
}

bool AssistedActivationAddWidget::Refresh(int time_num)
{
	Activation activation;
	if(!chooseByCombo)
	{
		IDCardInfo idCardPresident;
		idCardPresident.setFirstName((string)entryPresident.get_text());
		idCardPresident.setSurname(" ");

		IDCardInfo idCardWitness;
		idCardWitness.setFirstName((string)entryWitness.get_text());
		idCardWitness.setSurname(" ");

		activation.setPollworker(idCardPresident);
		activation.setPropossedPerson(idCardWitness);
	}
	else
	{
		IDCardInfo idCardPresident;
		idCardPresident.setFirstName((string)entryPresident.get_text());
		idCardPresident.setSurname(" ");

		IDCardInfo idCardWitness;
		idCardWitness.setFirstName((string)entryWitness.get_text());
		idCardWitness.setSurname(" ");

		activation.setPollworker(idCardPresident);
		activation.setPropossedPerson(idCardWitness);
	}
	
	IDCardInfo idCardElection;
	idCardElection.setFirstName((string)entryVoter.get_text());
	idCardElection.setSurname(" ");
	activation.setVoter(idCardElection);

	signalOk_detected.emit(activation);
	return false;
}

void AssistedActivationAddWidget::on_buttonCancel_clicked()
{
	signalCancel_detected.emit();
}
AssistedActivationAddWidget::~AssistedActivationAddWidget()
{
}
