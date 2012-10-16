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
#include <Voting/PBReports/PVFormWrapper.hxx>
#include <Operation/MachineOperationManager.hxx>
#include "Gui/Widgets/duration-verification-widget.h"
#include <Configuration/s-a-e-s-g-u-i-conf-manager.h>
#include "Voting/VotingDevice/card-data-wrapper.h"
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

ISMTTLog* DurationVerificationWidget::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget",GETTEXT_PACKAGE);

DurationVerificationWidget::DurationVerificationWidget()
: WizardWidgetBase(), vboxPrincipal(20),hboxCloseElection(5),hboxDuration(5)
{
	Glib::TimeVal timeValOpen;
	timeValOpen.assign_from_iso8601 (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getOpenElectionDate());

	Glib::TimeVal timeValClose;
	timeValClose.assign_from_iso8601 (Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getCloseVotingDate());

	Glib::TimeVal timeValDuration;
    timeValDuration = timeValClose - timeValOpen;
	int hours = (int)timeValDuration.as_double()/3600;
	int mins = ((int)timeValDuration.as_double()%3600)/60;
	int seconds = (((int)timeValDuration.as_double()%3600)%60);

	std::stringstream ss;
	ss << "hours: " << hours;
	ss << " mins: " << mins;
	ss << " secs: " << seconds;

	logger->Debug(ss.str());

	Pango::FontDescription fontTitle = labelTitle.get_style()->get_font();
	fontTitle.set_size(12*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_ULTRABOLD);

	labelTitle.set_alignment(0.5, 0.5);
	labelTitle.set_label(_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.Title"));
	labelTitle.set_justify(Gtk::JUSTIFY_CENTER);
	labelTitle.set_size_request(300, -1);
	labelTitle.modify_font(fontTitle);	

	
	Pango::FontDescription fontLabels = labelOpenElection.get_style()->get_font();
	fontLabels.set_size(12*Pango::SCALE);
	fontLabels.set_weight(Pango::WEIGHT_ULTRABOLD);

	labelOpenElection.set_alignment(0.5, 0.5);

	Glib::ustring ElectionOpenDuration = Glib::ustring::compose (_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelOpenElectionDuration"),
	                                      Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getOpenElectionDate(),
			                              Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getCloseElectionDate(),
			                              hours,mins,seconds);

	labelOpenElection.set_justify(Gtk::JUSTIFY_CENTER);
	labelOpenElection.set_size_request(500, -1);
	labelOpenElection.set_single_line_mode (false);
//	labelOpenElection.set_line_wrap(true);
//	labelOpenElection.set_line_wrap_mode (Pango::WRAP_CHAR );
	labelOpenElection.modify_font(fontLabels);
//	labelOpenElection.set_padding(10, 15);

	/*
	labelCloseElection.set_label(_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelCloseElection"));
	labelCloseElection.set_alignment(0.0, 0.5);
	labelCloseElection.set_padding(10, 0);
	labelCloseElection.set_size_request(200, -1);
	labelCloseElection.set_line_wrap(true);
	labelCloseElection.modify_font(fontLabels);
*/
	labelDuration.set_label(_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelDuration"));
	labelDuration.set_alignment(0.0, 0.5);
	labelDuration.set_justify(Gtk::JUSTIFY_CENTER);
	labelDuration.set_padding(10, 0);
	labelDuration.set_size_request(200, -1);
	labelDuration.set_line_wrap(true);
	labelDuration.modify_font(fontLabels);

	/*
	labelOpenElectionValue.set_label(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getOpenElectionDate());
	labelOpenElectionValue.set_alignment(0.0, 0.5);
	labelOpenElectionValue.set_padding(10, 0);
	labelOpenElectionValue.set_size_request(400, -1);
	labelOpenElectionValue.set_line_wrap(true);
	labelOpenElectionValue.modify_font(fontLabels);

	labelCloseElectionValue.set_label(Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getOperationStatus ()->getElectionStatusWrapper ()->getCloseElectionDate());
	labelCloseElectionValue.set_alignment(0.0, 0.5);
	labelCloseElectionValue.set_padding(10, 0);
	labelCloseElectionValue.set_size_request(400, -1);
	labelCloseElectionValue.set_line_wrap(true);
	labelCloseElectionValue.modify_font(fontLabels);
	*/
//	hboxOpenElection.pack_end (labelOpenElection,Gtk::PACK_EXPAND_WIDGET);
//	hboxOpenElection.set_homogeneous (true);
	//hboxOpenElection.pack_start (labelOpenElectionValue,Gtk::PACK_SHRINK);
	
	//hboxCloseElection.pack_start (labelCloseElection,Gtk::PACK_SHRINK);
	//hboxCloseElection.set_homogeneous (false);
	//hboxCloseElection.pack_start (labelCloseElectionValue,Gtk::PACK_SHRINK);





	labelOpenElection.set_label(ElectionOpenDuration);
	if(!Smartmatic::SAES::GUI::Configuration::SAESGUIConfigurationManager::Current()->getDurationLeaveFieldsBlank())
	{
		hoursWidget.Initialize(hours,mins,seconds);
	}
	hoursWidget.SetLabels(_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelHour"),_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelMin"),
	                      _("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.LabelSec"));
	hoursWidget.fields_complete_signal().connect(sigc::mem_fun(*this, &DurationVerificationWidget::CheckFields));


	hboxDuration.pack_start (labelDuration,Gtk::PACK_SHRINK);
	hboxDuration.pack_start (hoursWidget,Gtk::PACK_SHRINK);
	hboxDuration.set_homogeneous (false);
	
	okButton.SetLabel(_("Smartmatic.SAES.GUI.Widgets.DurationVerificationWidget.ButtonOk"));
	okButton.WidgetsPosition (5,0,0);
	okButton.set_size_request (300,50);


	
	hbuttonbox.set_spacing (10);
	hbuttonbox.set_layout (Gtk::BUTTONBOX_CENTER );
	hbuttonbox.add(okButton);

	vboxPrincipal.pack_start (labelTitle,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (labelOpenElection,Gtk::PACK_EXPAND_WIDGET);
//	vboxPrincipal.pack_start (hboxOpenElection,Gtk::PACK_EXPAND_WIDGET);
//	vboxPrincipal.pack_start (hboxCloseElection,Gtk::PACK_SHRINK);
	vboxPrincipal.pack_start (hboxDuration,Gtk::PACK_SHRINK);

	vboxPrincipal.pack_end (hbuttonbox,Gtk::PACK_SHRINK);

	vboxPrincipal.show_all_children ();
	vboxPrincipal.set_size_request (-1,350);
	vboxPrincipal.set_visible (true);
	
	hbuttonboxprincipal.add(vboxPrincipal);

	add(hbuttonboxprincipal);
	show_all_children ();
	set_visible (true);

	okButton.set_sensitive(false);
}

void DurationVerificationWidget::CheckFields(bool disableButton)
{
	okButton.set_sensitive(!disableButton);
}

void DurationVerificationWidget::initialize()
{
	okButton.signal_clicked().connect( sigc::mem_fun(this, &DurationVerificationWidget::on_buttonOk_clicked));
}

void DurationVerificationWidget::dispose()
{

}


void DurationVerificationWidget::on_buttonOk_clicked()
{	
	if(!hoursWidget.CheckFields())
	{
		std::stringstream sDuration;
		sDuration << hoursWidget.getHours();
		sDuration << ":";
		sDuration << hoursWidget.getMins();
		sDuration << ":";
		sDuration << hoursWidget.getSecs();
		Smartmatic::SAES::Voting::PBReports::PVFormWrapper::getInstance()->setDurationElection(sDuration.str());
		m_done_signal.emit();
	}
	else
	{
		okButton.set_sensitive(false);
	}
}

Glib::ustring DurationVerificationWidget::GetWidgetName()
{
	Glib::ustring name("DurationVerificationWidget");
	return name;
}

