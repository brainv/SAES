/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * saesfunctionality
 * Copyright (C)  2011 <>
 * 
 * saesfunctionality is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * saesfunctionality is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <Log/SMTTLogManager.h>
#include "close-votation-functionality.h"
#include <Voting/operation-status.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
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
using namespace Smartmatic::SAES::Functionality;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::Functionality;
using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::Log;
using namespace Smartmatic::SAES::GUI::Configuration;

CloseVotationFunctionality* CloseVotationFunctionality::current_instance = NULL;

Smartmatic::Log::ISMTTLog* CloseVotationFunctionality::logger = Smartmatic::Log::SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality",GETTEXT_PACKAGE);

CloseVotationFunctionality* CloseVotationFunctionality::Current()
{
	if (!current_instance)
		current_instance = new CloseVotationFunctionality();

	return current_instance;
};

CloseVotationFunctionality::CloseVotationFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	idCardWidget = NULL;
	vbox = NULL;
	align = NULL;
	titleLabel = NULL;
	titleLabelID = NULL;
	closeVotationButton = NULL;
	externalFrame = NULL;
	confirmButton = NULL;
	cancelButton = NULL;
	buttonBox = NULL;
	labelConfirmation = NULL;
}

void CloseVotationFunctionality::deleteElement()
{
	if (idCardWidget)
	{
		delete idCardWidget;
		idCardWidget = NULL;
	}
	if (vbox)
	{
		delete vbox;
		vbox = NULL;
	}
	if (align)
	{
		delete align;
		align = NULL;
	}
	if (titleLabel)
	{
		delete titleLabel;
		titleLabel = NULL;
	}
	if (titleLabelID)
	{
		delete titleLabelID;
		titleLabelID = NULL;
	}
	if (closeVotationButton)
	{
		delete closeVotationButton;
		closeVotationButton = NULL;
	}
	if (externalFrame)
	{
		delete externalFrame;
		externalFrame = NULL;
	}
	if (confirmButton)
	{
		delete confirmButton;
		confirmButton = NULL;
	}
	if (cancelButton)
	{
		delete cancelButton;
		cancelButton = NULL;
	}
	if (buttonBox)
	{
		delete buttonBox;
		buttonBox = NULL;
	}
	if (labelConfirmation)
	{
		delete labelConfirmation;
		labelConfirmation = NULL;
	}
}

CloseVotationFunctionality::~CloseVotationFunctionality()
{
	deleteElement();
}

void CloseVotationFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.VotationWasNotClose"));
	enableExitButton();

	if(idCardWidget)
	{
		idCardWidget->initialize();
	}
};

void CloseVotationFunctionality::LoadAfterConfirmation()
{
	if (closeVotationButton) delete closeVotationButton;
	closeVotationButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.CloseVotationButton"));
	closeVotationButton->signal_clicked().connect(sigc::mem_fun(this, &CloseVotationFunctionality::on_closeVotationButton_clicked));

	align->remove();
	externalFrame->remove();

	if(SAESGUIConfigurationManager::Current()->getCloseVotationRequestForId())
	{
		idCardWidget->signal_accept_clicked().connect(sigc::mem_fun(*this, &CloseVotationFunctionality::on_IdCard_accepted));

		align->set(0.5, 0.5, 0, 0);
		align->add(*idCardWidget);

		externalFrame->add(*align);
		externalFrame->show_all_children();
		externalFrame->show();
	}
	else
	{
		if (idCardWidget)
		{
			delete idCardWidget;
			idCardWidget = NULL;
		}

		closeVotingExperience();
/*
		if (titleLabel) delete titleLabel;
		titleLabel = new Label(_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.ClosingVotation"));
		Pango::FontDescription fontTitle = titleLabel->get_style()->get_font();
		fontTitle.set_size(14*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		titleLabel->modify_font(fontTitle);

		externalFrame->add(*titleLabel);
		externalFrame->show_all_children();
		externalFrame->show();

		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &CloseVotationFunctionality::closeVotingExperience), 250);
		//this->EnableBackgroundProcess();
*/
	}
}

Gtk::Widget* CloseVotationFunctionality::GetFrame()
{
	align = new Alignment();
	externalFrame = new Frame();
	externalFrame->set_shadow_type(Gtk::SHADOW_NONE);

	if(SAESGUIConfigurationManager::Current()->getCloseVotationRequestForId())
	{
		idCardWidget = new IDCardWidgetCloseVotation();
	}

	unsigned int totalOfficialActivacion = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getActivatedCardStatistics()->getTotalOfficialActivated();

	unsigned int numberForConfirmation = SAESGUIConfigurationManager::Current()->getCloseVotationMinimumOfficialsActivationForConfirmation();

	string confirmationText;

	bool showConfirmation = false;

	if((totalOfficialActivacion < numberForConfirmation && numberForConfirmation != 0))
	{
		confirmationText = _("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.CloseConfirmation");
		showConfirmation = true;
	}
	else if(SAESGUIConfigurationManager::Current()->getCloseVotationShowConfirmationMessageWhenClosing())
	{
		confirmationText = _("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.CloseConfirmationMessage");
		showConfirmation = true;
	}

	if(showConfirmation)
	{
		confirmButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.ConfirmButton"));
		confirmButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseVotationFunctionality::on_confirmButton_clicked));
		confirmButton->set_size_request(170, 70);
		confirmButton->SetButtonType(SmartmaticButton::Ok);
		confirmButton->WidgetsPosition(5,6,0);

		cancelButton = new SmartmaticButton(_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.CancelButton"));
		cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &CloseVotationFunctionality::on_cancelButton_clicked));
		cancelButton->set_size_request(170, 70);
		cancelButton->SetButtonType(SmartmaticButton::Cancel);
		cancelButton->WidgetsPosition(5,6,0);

		buttonBox = new HButtonBox();
		buttonBox->set_size_request(300, 200);
		buttonBox->set_layout(BUTTONBOX_SPREAD);
		buttonBox->pack_start(*cancelButton, false, false);
		buttonBox->pack_start(*confirmButton, false, false);

		labelConfirmation = new Label(confirmationText);
		labelConfirmation->set_size_request(980, 200);
		Pango::FontDescription fontTitle = labelConfirmation->get_style()->get_font();
		fontTitle.set_size(20*Pango::SCALE);
		fontTitle.set_weight(Pango::WEIGHT_BOLD);
		labelConfirmation->modify_font(fontTitle);
		labelConfirmation->set_alignment(0.5, 0.5);

		vbox = new VBox();
		vbox->pack_start(*labelConfirmation, false, false);
		vbox->pack_start(*buttonBox, false, false);

		align->set(0.5, 0.5, 0, 0);
		align->add(*vbox);

		externalFrame->add(*align);
		externalFrame->show_all_children();
		externalFrame->show();
	}
	else
	{
		LoadAfterConfirmation();
	}

	return externalFrame;		
};

void CloseVotationFunctionality::CloseVotationFunctionality::on_confirmButton_clicked()
{
	LoadAfterConfirmation();
}

void CloseVotationFunctionality::CloseVotationFunctionality::on_cancelButton_clicked()
{
	ExitFunctionality();
}

void CloseVotationFunctionality::closeVotingExperience()
{
	logger->Debug("Execute close voting experience");

	try
	{
		MachineOperationManager::getInstance()->closeVotingExperience();
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.VotationWasClose"));
	}
	catch(...)
	{
		exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.ErrorClosingVotation"));
	}

	enableExitButton();
	ExitFunctionality();
}

void CloseVotationFunctionality::on_IdCard_accepted()
{
	Smartmatic::SAES::EID::CitizenInfo citizen = idCardWidget->getCitizenInfo();
	MachineOperationManager::getInstance()->PersistenceVotingCloserData(citizen);
	closeVotingExperience();
}

void CloseVotationFunctionality::on_closeVotationButton_clicked()
{

}

string CloseVotationFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.CloseVotation");
};

Smartmatic::Functionality::MenuOptionDescriptor CloseVotationFunctionality::GetMenuOptionType()
{
	return SaesMenuOptionDescriptor(MenuType::MCloseVotationFunctionality,false);
};	

void CloseVotationFunctionality::Dispose()
{
	if(idCardWidget)
		idCardWidget->dispose();
};

Smartmatic::Log::ISMTTLog* CloseVotationFunctionality::getLogger()
{
	return logger;
}
Glib::ustring CloseVotationFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.LogStartFunctionality");
}

Glib::ustring CloseVotationFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.CloseVotationFunctionality.LogCloseFunctionality");
}
