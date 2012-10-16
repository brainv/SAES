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
#include "open-election-functionality.h"
#include <Voting/operation-status.h>
#include <Voting/Status/ElectionStatusWrapper.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include <glibmm/timeval.h>
#include <Log/SMTTLogManager.h>
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/AbstractFactoryWidget.hxx>

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

using namespace Smartmatic::SAES::GUI::Functionality;
using namespace Smartmatic::Functionality;
using namespace std;
using namespace Gtk;
using namespace Smartmatic::SAES::Voting;
using namespace Smartmatic::SAES::Operation;
using namespace Smartmatic::SAES::Voting::Status;
using namespace Smartmatic::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Widgets::Voting::PBReports;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::Runtime::Environment;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::Log;

OpenElectionFunctionality* OpenElectionFunctionality::current_instance = NULL;

ISMTTLog* OpenElectionFunctionality::logger = SMTTLogManager::GetLogger("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality",GETTEXT_PACKAGE);

OpenElectionFunctionality* OpenElectionFunctionality::Current()
{
	if (!current_instance)
		current_instance = new OpenElectionFunctionality();

	return current_instance;
};

OpenElectionFunctionality::OpenElectionFunctionality()
: GraphicDisplayFunctionality<Smartmatic::Functionality::MenuOptionDescriptor>()
{
	openFrame = NULL;
	openNoteWidget = NULL;
	idCard = NULL;
	openElectionWidget = NULL;
	manager = NULL;
}

OpenElectionFunctionality::~OpenElectionFunctionality()
{
	deleteElement();
}

void OpenElectionFunctionality::deleteElement()
{
	wizardVector.clear();

	if (openElectionWidget)
	{
		delete openElectionWidget;
		openElectionWidget = NULL;
	}
	if (idCard)
	{
		delete idCard;
		idCard = NULL;
	}
	if (openNoteWidget)
	{
		delete openNoteWidget;
		openNoteWidget = NULL;
	}
	if (manager)
	{
		delete manager;
		manager = NULL;
	}
	if (openFrame)
	{
		delete openFrame;
		openFrame = NULL;
	}
}

void OpenElectionFunctionality::Initialize()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ElectionWasNotOpen"));
	enableExitButton();

	if(manager)
	{
		manager->Start();
	}
}

bool OpenElectionFunctionality::checkIfCanOpenByDate()
{
	try
	{
		Smartmatic::SAES::Voting::VotingDevice::Voting_device vd = Smartmatic::SAES::Operation::MachineOperationManager::getInstance()->getElectoralConfiguration()->getVotingDevice()->getFirstVotingDevice();
		std::string dateOpen = vd.getOperation_modes().getOperation_mode()[0].getOpening_date_time ();
		Glib::TimeVal timeValOpen;
		bool checkDates = timeValOpen.assign_from_iso8601 (dateOpen);
		Glib::TimeVal timeValNow;
		timeValNow.assign_current_time ();
		if(timeValNow > timeValOpen || checkDates == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch(...)
	{
		//TODO handle exception if any
	}

	return false;
}

Gtk::Widget* OpenElectionFunctionality::GetFrame()
{
	openFrame = new Gtk::Frame();

	OpenElectionFunctionalityConfiguration::OpenElectionStepsSequence  seq =
				SAESGUIConfigurationManager::Current()->GetOpenElectionFunctionalityConfiguration().getOpenElectionSteps();

	OpenElectionFunctionalityConfiguration::OpenElectionStepsIterator iter;

	for(iter = seq.begin(); iter != seq.end(); iter++)
	{
		switch(*iter)
		{
			case OpenElectionSteps::CONFIGURATION_REGISTERNOTE:
				openNoteWidget = new OpenNoteWidget();
				openNoteWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::errorHappen));
				openNoteWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::disableExitButton));
				wizardVector.push_back(openNoteWidget);
				break;
			case OpenElectionSteps::CONFIGURATION_REQUESTIDCARD:
				idCard = new IDCardWidgetOpenElection();
				idCard->on_stop_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::errorHappen));
				idCard->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::disableExitButton));
				wizardVector.push_back(idCard);
				break;
			case OpenElectionSteps::CONFIGURATION_OPENELECTION:
				openElectionWidget = AbstractFactoryWidget::createOpenElectionStatusWidget();
				openElectionWidget->on_stop_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::errorHappen));
				openElectionWidget->on_disable_close_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::disableExitButton));
				wizardVector.push_back(openElectionWidget);
				break;
		}
	}

	manager = new WizardWidgetManager(wizardVector);
	manager->on_finish_signal_emit().connect(sigc::mem_fun(*this, &OpenElectionFunctionality::finish));
	manager->set_shadow_type(SHADOW_NONE);

	openFrame->remove();
	openFrame->add(*manager);
	openFrame->set_shadow_type(SHADOW_NONE);
	openFrame->show_all_children();
	openFrame->show();

	return openFrame;
}

void OpenElectionFunctionality::finish()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ElectionWasOpen"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &OpenElectionFunctionality::ExitFunctionality),50);
}

void OpenElectionFunctionality::errorHappen()
{
	exitWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.ErrorOpenElection"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &OpenElectionFunctionality::ExitFunctionality),50);
}

bool OpenElectionFunctionality::Enable()
{
	bool enableFunctionality = true;

	if(!checkIfCanOpenByDate())
	{
		logger->Audit(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.CannotOpenBecauseDateCheckFailed")); 
		enableFunctionality = false;
		initWidget.setInfo(N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.UnableKeyMessageIsNotOpenDateYet"));
	}
	
	return enableFunctionality;
};

std::string OpenElectionFunctionality::GetWindowTitle()
{
	return N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.OpenElection");
};

MenuOptionDescriptor OpenElectionFunctionality::GetMenuOptionType()
{
	return Smartmatic::SAES::Functionality::SaesMenuOptionDescriptor(Smartmatic::SAES::Functionality::MenuType::MOpenElectionFunctionality,false);
};	

void OpenElectionFunctionality::Dispose()
{
	if(idCard)
	{
	    idCard->dispose();
	}
}

Smartmatic::Log::ISMTTLog* OpenElectionFunctionality::getLogger()
{
	return logger;
}

Glib::ustring OpenElectionFunctionality::getStartLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.LogStartFunctionality");
}

Glib::ustring OpenElectionFunctionality::getFinishLogMessage()
{
	return N_("Smartmatic.SAES.GUI.Functionality.OpenElectionFunctionality.LogCloseFunctionality");
}
