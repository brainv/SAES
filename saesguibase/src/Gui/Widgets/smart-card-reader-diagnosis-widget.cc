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

#include "smart-card-reader-diagnosis-widget.h"
#include "Configuration/label-configuration.h"
#include "Voting/operation-status.h"
#include <Configuration/SaesGUIConfiguration-schema.hxx>
#include "Configuration/s-a-e-s-g-u-i-conf-manager.h"
#include <Operation/Card/CardController.hxx>
#include <Operation/MachineOperationManager.hxx>
#include <Gui/Widgets/FactoryMethodWidget.hxx>

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

using namespace Smartmatic::GUI::Configuration;
using namespace Smartmatic::SAES::GUI::Widgets;
using namespace Smartmatic::SAES::GUI::Configuration;
using namespace Smartmatic::SAES::Configuration;
using namespace Smartmatic::SAES::Voting;	
using namespace Smartmatic::SAES::Operation::Card;
using namespace Smartmatic::Environment;
using namespace Smartmatic::SAES::Operation;

SmartCardReaderDiagnosisWidget::SmartCardReaderDiagnosisWidget(std::string Title, bool hasOk, bool hasCancel, bool hasMessage, bool showButtons)
: BasicDiagnosticWidget(Title, Smartmatic::SAES::Voting::OperationStatus::SmartCard, hasOk,hasCancel,hasMessage,showButtons)
{
	progressWidget = FactoryMethodWidget::createProgressWidget();

	LabelConfiguration diagConf = SAESGUIConfigurationManager::Current()->GetDiagnosisLabelConfiguration();
	progressWidget->setTextConfig(diagConf);
	progressWidget->setImage(ProgressWidget::SMARTCARD);

	setDiagnosticFrame(*progressWidget);
	this->show_all_children();
}

SmartCardReaderDiagnosisWidget::~SmartCardReaderDiagnosisWidget()
{
	remove();

	if(progressWidget)
	{
		delete progressWidget;
		progressWidget = NULL;
	}
}

void SmartCardReaderDiagnosisWidget::Initialize()
{
	timeout = 0;
	progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.SmartSmartCardReaderDiagnosisWidget.InitializingDiagnostic"));
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::SendTest), 1000);
}

void SmartCardReaderDiagnosisWidget::SendTest()
{
	progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.PleaseInsertCard"));
	if(!Glib::thread_supported()) Glib::thread_init();
	Glib::Thread::create(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::findReader), false);
}

void SmartCardReaderDiagnosisWidget::findReader()
{
	if(CardController::getInstance()->initialize())
	{
		int timerRefresh = SAESGUIConfigurationManager::Current()->getPollingCardConfiguration().getSmartCardReaderDiagnosisWidget();
		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::Refresh), 0);
		connRefresh.disconnect();
		connRefresh = Glib::signal_timeout().connect(my_slot,timerRefresh);
	}
	else
	{
		status = false;
		message = _("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.NotReachReaderDiagnosticFailed");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::showResult), 100);
	}
}

bool SmartCardReaderDiagnosisWidget::Refresh(int time_num)
{
	if(CardController::getInstance()->isCardPresent())
	{
		progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.CardInserted"));
	    if(!Glib::thread_supported()) Glib::thread_init();
	    Glib::Thread::create(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::test), false);
		return false;
	}

	timeout++;

	if(timeout == SAESGUIConfigurationManager::Current()->getSCReaderDiagnosisTimeout())
	{
		status = false;
		message = _("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.DiagnosticFailed");
		Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::showResult), 100);
		return false;
	}

	return true;
}

void SmartCardReaderDiagnosisWidget::test()
{
	status = CardController::getInstance()->test();
	Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &SmartCardReaderDiagnosisWidget::showResult), 1000);
}

void SmartCardReaderDiagnosisWidget::showResult()
{
	if (status)
	{
		progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.DiagnosticSuccessFul"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::SmartCard, OperationStatus::Ok);
	}
	else
	{
		progressWidget->setText(_("Smartmatic.SAES.GUI.Widgets.SmartCardReaderDiagnosisWidget.DiagnosticFailed"));
		MachineOperationManager::getInstance()->getOperationStatus()->changeDiagnosisStatus(OperationStatus::SmartCard, OperationStatus::Error);
	}

	signalContinue_detected.emit();
}

void SmartCardReaderDiagnosisWidget::Dispose()
{
	connRefresh.disconnect();
	CardController::getInstance()->dispose();
};
