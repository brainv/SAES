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

#include "close-election-confirmation-widget.h"
#include <Log/ISMTTLog.h>
#include <System/Exception/XmlException.hxx>
#include <Log/ISMTTLog.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Widgets/smartmatic-button.h>
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
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Log;

Smartmatic::Log::ISMTTLog* CloseElectionConfirmationWidget::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Widgets.CloseElectionConfirmationWidget",GETTEXT_PACKAGE);

CloseElectionConfirmationWidget::CloseElectionConfirmationWidget()
{
	SmartmaticButton* confirmButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.ConfirmButton")));
	confirmButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseElectionConfirmationWidget::on_confirmButton_clicked));
	confirmButton->set_size_request(170, 70);
	confirmButton->SetButtonType(SmartmaticButton::Ok);
	confirmButton->WidgetsPosition(5,6,0);

	SmartmaticButton* cancelButton = manage(new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.CancelButton")));
	cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseElectionConfirmationWidget::on_cancelButton_clicked));
	cancelButton->set_size_request(170, 70);
	cancelButton->SetButtonType(SmartmaticButton::Cancel);
	cancelButton->WidgetsPosition(5,6,0);

	HButtonBox* buttonBox = manage(new HButtonBox());
	buttonBox->set_size_request(300, 200);
	buttonBox->set_layout(BUTTONBOX_SPREAD);
	buttonBox->pack_start(*cancelButton, false, false);
	buttonBox->pack_start(*confirmButton, false, false);

	label = manage(new Label(_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.CloseConfirmation")));
	label->set_size_request(980, 200);
	Pango::FontDescription fontTitle = label->get_style()->get_font();
	fontTitle.set_size(20*Pango::SCALE);
	fontTitle.set_weight(Pango::WEIGHT_BOLD);
	label->modify_font(fontTitle);
	label->set_alignment(0.5, 0.5);

	VBox* vbox = manage(new VBox());
	vbox->pack_start(*label, false, false);
	vbox->pack_start(*buttonBox, false, false);

	Alignment* questionAlign = manage(new Alignment());
	questionAlign->set(0.5, 0.5, 0, 0);
	questionAlign->add(*vbox);

	setWidget(questionAlign);
}

CloseElectionConfirmationWidget::~CloseElectionConfirmationWidget()
{

}

void CloseElectionConfirmationWidget::on_confirmButton_clicked()
{
	m_done_signal.emit();
}

void CloseElectionConfirmationWidget::on_cancelButton_clicked()
{
	m_stop_signal.emit();
}

void CloseElectionConfirmationWidget::initialize()
{
	unsigned int totalOfficialScannedVotes = MachineOperationManager::getInstance()->getVoteStatistics()->getOfficialVotes();

	if(totalOfficialScannedVotes > 0)
	{
		if(!SAESGUIConfigurationManager::Current()->GetCloseElectionFunctionalityConfiguration().getShowConfirmation())
		{
			set_no_show_all();
			hide();
			m_done_signal.emit();
		}
		label->set_text(_("Smartmatic.SAES.GUI.Functionality.CloseElectionFunctionality.CloseConfirmationMessage"));
	}
}

void CloseElectionConfirmationWidget::dispose()
{

}
